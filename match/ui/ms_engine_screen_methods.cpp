// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x5D1C20 .. 0x5D25D0 (the MSEngine animation list, dirty rectangles and frame loop);
//   the debug strings at 0x8305B0 / 0x8305D0 / 0x8305E8; callers 0x4F1CA0, 0x4F2300 and 0x76xxxx; layout in
//   match/_layout/ms_engine.h.
// Address index: 0x5D1C20 0x5D1C90 0x5D1D80 0x5D1DF0 0x5D1E70 0x5D1FD0 0x5D2260 0x5D2350 0x5D2410 0x5D2530
//   0x5D25D0
// Not matched here: 0x5D1FD0 (AddDirtyRect), 0x5D2260 (FlushDirtyRects), 0x5D2350 (PresentRect); 0x5D2410 (Run) is
//   in ms_engine_run_methods.cpp because cl inlines PauseWhileInactive into it when both share a unit.
#include <string.h>
#include <windows.h>
#include "../core/vector_class_operations.h"
#include "../_layout/ms_engine.h"
#include "input_controls/mouse_ww_mouse_class.h"

// GLOBAL: GAMEMD 0x88730C -- the back surface the screens draw on.
extern MouseSurfaceView* DAT_0088730C;
// GLOBAL: GAMEMD 0x887310 -- the screen background picture surface.
extern MouseSurfaceView* DAT_00887310;
// GLOBAL: GAMEMD 0x887308 -- the primary (visible) surface.
extern MouseSurfaceView* DAT_00887308;
// GLOBAL: GAMEMD 0xB73550 -- the main window.
extern HWND DAT_00B73550;
// GLOBAL: GAMEMD 0x8A00A0 -- raised to make the engine repaint everything on its next draw.
extern bool DAT_008A00A0;
// GLOBAL: GAMEMD 0xA8ED80 -- whether the program is the active application.
extern bool DAT_00A8ED80;

// FUNCTION: GAMEMD 0x48D080 (decl; reloc)
void CallBack();
// FUNCTION: GAMEMD 0x4A4830 (decl; reloc)
void FUN_004A4830();
// FUNCTION: GAMEMD 0x5D4D50 (decl; reloc)
void FUN_005D4D50();
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc)
void __cdecl MenusDebugLog(const char* format, ...);

// FUNCTION: GAMEMD 0x5D1C20
// Append an animation; answers where it landed.
int MSEngine::AddAnim(MSAnim* anim)
{
    if (anim != 0 && Anims.AddItem(anim))
        return Anims.FindItemIndex(anim);
    return -1;
}

// FUNCTION: GAMEMD 0x5D1D80
// Take an animation out of the list and delete it.
void MSEngine::RemoveAnim(MSAnim* anim)
{
    if (anim != 0 && Anims.FindItemIndex(anim) != -1) {
        Anims.RemoveItem(anim);
        delete anim;
    }
}

// FUNCTION: GAMEMD 0x5D1C90
// Insert the new animation right after the old one, then remove and delete the old one.
void MSEngine::ReplaceAnim(MSAnim* added, MSAnim* replaced)
{
    Anims.InsertAfter(Anims.FindItemIndex(replaced), added);
    RemoveAnim(replaced);
}

// FUNCTION: GAMEMD 0x5D1DF0
// Run one-millisecond frames while the animation is still queued and unfinished (and the delay is not zero).
void MSEngine::WaitForAnim(MSAnim* anim, unsigned int milliseconds)
{
    MSTimer timer;
    timer.Remaining = milliseconds;
    while (true) {
        int index = Anims.FindItemIndex(anim);
        if (index == -1)
            break;
        if (Anims.Items[index]->vf_7())
            break;
        if (milliseconds <= 0)
            break;
        Run(1);
    }
}

// FUNCTION: GAMEMD 0x5D25D0
// Make a sound effect and queue it; the effect is leaked when the list cannot grow.
bool MSEngine::AddSfx(const char* name, const char* unused)
{
    if (name == 0 || unused == 0)
        return false;
    MSSfx* sfx = new MSSfx(name, unused);
    if (!Sfxs.AddItem(sfx))
        return false;
    return true;
}

// FUNCTION: GAMEMD 0x5D2530
// While the program is not the active application: pause the animations, sleep half a second at a time while
// pumping messages until it is active again, then resume them.
void MSEngine::PauseWhileInactive()
{
    if (DAT_00A8ED80 != true) {
        MenusDebugLog("MSEngine - Pausing animations\n");
        for (int i = 0; i < Anims.Count; i++)
            Anims.Items[i]->PauseTimer();
        while (!DAT_00A8ED80) {
            MenusDebugLog("MSEngine - Sleeping\n");
            Sleep(500);
            FUN_005D4D50();
        }
        MenusDebugLog("MSEngine - Resuming animations\n");
        for (int j = 0; j < Anims.Count; j++)
            Anims.Items[j]->ResumeTimer();
    }
}

// FUNCTION: GAMEMD 0x5D1E70
// With the redraw flag up: clear the surface, paint the background picture centred on it, draw every animation
// and queue the whole surface as dirty. Then step every animation, dropping and deleting the finished ones, and
// queue the rectangle each one touched.
void MSEngine::Draw(MouseSurfaceView* surface)
{
    if (DAT_008A00A0 == true) {
        DAT_008A00A0 = false;
        surface->vf_06(0);
        RectangleStruct centred;
        centred = DAT_00887310->GetRect();
        centred.X = (surface->GetWidth() - centred.Width) / 2;
        centred.Y = (surface->GetHeight() - centred.Height) / 2;
        surface->Blt(DAT_00887310->GetRect(), DAT_00887310, centred, 0, 1);
        for (int i = 0; i < Anims.Count; i++)
            Anims.Items[i]->Draw(surface, 0);
        DirtyRectCount = 0;
        AddDirtyRect(surface->GetRect());
        OnRedraw(surface);
    }
    for (int j = 0; j < Anims.Count; j++) {
        RectangleStruct touched;
        if (Anims.Items[j]->Update(surface, &touched) == true) {
            delete Anims.Items[j];
            Anims.Delete(j);
        }
        AddDirtyRect(touched);
    }
}
