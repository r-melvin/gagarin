// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at the addresses annotated
//   below. The blit helpers it calls are in bink_player_blit_methods.cpp, so they
//   stay real calls.
//
// Functions are ordered ascending by retail address.

#include <windows.h>
#include "bink_player_teardown_methods.h"
#include "input_manager_class_methods.h"

// Bink imports, declared dllimport so the calls go through the IAT as retail does.
extern "C" __declspec(dllimport) const char* __stdcall BinkGetError(void);                 // IAT 0x7E1598
extern "C" __declspec(dllimport) int __stdcall BinkSetVolume(void* bink, int volume);      // IAT 0x7E15A0
extern "C" __declspec(dllimport) int __stdcall BinkPause(void* bink, int pause);           // IAT 0x7E15B0
extern "C" __declspec(dllimport) void __stdcall BinkNextFrame(void* bink);                 // IAT 0x7E15B4
extern "C" __declspec(dllimport) int __stdcall BinkCopyToBuffer(void* bink, void* dest, unsigned int pitch,
    unsigned int height, int x, int y, unsigned int flags);                                  // IAT 0x7E15B8
extern "C" __declspec(dllimport) int __stdcall BinkDoFrame(void* bink);                    // IAT 0x7E15BC

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);
// FUNCTION: GAMEMD 0x53E770 (decl; reloc) -- fetch or peek one message into *msg; 0 when none.
int __fastcall FUN_0053E770(MSG* msg, HWND hwnd, unsigned int filterMin, unsigned int filterMax, int remove);
// FUNCTION: GAMEMD 0x53E730 (decl; reloc) -- wait for a message; 0 for WM_QUIT.
int __fastcall FUN_0053E730(MSG* msg, HWND hwnd, unsigned int filterMin, unsigned int filterMax);

// GLOBAL: GAMEMD 0x87F770
extern InputManagerClass* DAT_0087F770;
// GLOBAL: GAMEMD 0x887308
extern Surface* DAT_00887308;
// GLOBAL: GAMEMD 0xB73550 -- the game window.
extern HWND DAT_00B73550;
// GLOBAL: GAMEMD 0xA8ED80 -- set while the game window is active.
extern bool DAT_00A8ED80;
// GLOBAL: GAMEMD 0xAA0430 -- count of message-pump calls.
extern int DAT_00AA0430;
// GLOBAL: GAMEMD 0xA8EB9C -- the movie volume scale.
extern float DAT_00A8EB9C;
// GLOBAL: GAMEMD 0x89C490 -- the scale last handed to the player.
extern float DAT_0089C490;

// FUNCTION: GAMEMD 0x432C70
// Play the movie to its end (or until escape): pump messages, and when none are
// waiting draw the next frame. Both exits leave the three loops for the closing call at 0x432E27.
void MSBinkPlayer::FUN_00432C70()
{
    if (Bink == 0) {
        FUN_004068E0("Bink Error: %s\n", BinkGetError());
        return;
    }
    DAT_0087F770->DoSomething();
    Playing = true;
    unknown_2D = false;
    do {
        do {
            for (;;) {
                if (Bink->CurrentFrame >= Bink->Frames || Bink->CurrentFrame < LastFrame)
                    goto done;
                DAT_00AA0430++;
                MSG msg;
                if (FUN_0053E770(&msg, 0, 0, 0, 0) == 0)
                    break;
                if (FUN_0053E730(&msg, 0, 0, 0) == 0)
                    goto done;
                TranslateMessage(&msg);
                DispatchMessageA(&msg);
            }
            if (!Playing)
                Sleep(0x21);
            if (Screen == DAT_00887308) {
                RECT rect;
                GetClientRect(DAT_00B73550, &rect);
                ClientToScreen(DAT_00B73550, (POINT*)&rect);
                FUN_00432E40(Screen, Area.X + rect.left, Area.Y + rect.top);
            } else {
                if (FUN_00432E40(Screen, Area.X, Area.Y)) {
                    RECT rect;
                    GetClientRect(DAT_00B73550, &rect);
                    ClientToScreen(DAT_00B73550, (POINT*)&rect);
                    RectangleStruct dest = Area;
                    dest.X += rect.left;
                    dest.Y += rect.top;
                    DAT_00887308->CopyFromPart(&dest, Screen, &Area, false, true);
                }
            }
        } while (DAT_0087F770->FUN_0054F000() == 0 || StopRequested);
    } while (DAT_0087F770->FUN_0054F050() != 0x81B);
done:
    DAT_0087F770->DoSomething();
}
