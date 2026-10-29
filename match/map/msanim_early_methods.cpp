// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes compared against the user's retail gamemd.exe v1.001 across
//   0x5CB6C0..0x5CCE82, the earlier half of the map-stage animation family
//   whose later half lives in msanim_family_methods.cpp (types from its header).
// Address index: 0x5CB790 0x5CBCB0 0x5CC760 0x5CC820 0x5CC850 0x5CC880 0x5CCA10 0x5CCC30 0x5CCE40 0x5CEC70 0x5CECB0

#include "msanim_family_methods.h"
#include "../_layout/memory_buffer.h"

// GLOBAL: GAMEMD 0x88730C -- the blitter the shape animations redraw through.
extern MSBlitSurface* DAT_0088730C;

__forceinline static bool MSRectEqual(const RectangleStruct& a, const RectangleStruct& b)
{
    return a.X == b.X && a.Y == b.Y && a.Width == b.Width
        && a.Height == b.Height;
}

// FUNCTION: GAMEMD 0x5CB790
// Jump to a frame. When the rectangle moves, the screen is redrawn over the
// old position; the frame is then clamped to the last one in the file.
void MSShapeAnim::SetFrame(unsigned int frame)
{
    RectangleStruct old;
    old = GetRect();
    Frame = frame;

    if (!MSRectEqual(old, GetRect())) {
        DAT_0088730C->Blit(&old, MSScreenSurface, &old, 0, 1);
    }

    if (Frame >= (unsigned int)Buffer->Frames) {
        Frame = Buffer->Frames - 1;
    }
}

// FUNCTION: GAMEMD 0x5CB840
// Store the +0x2C index, clamped below the shape's frame count.
void MSShapeAnim::FUN_005CB840(unsigned int value)
{
    Field2C = value;
    int limit = Buffer->Frames;
    if (value >= (unsigned int)limit)
        Field2C = limit - 1;
}

// FUNCTION: GAMEMD 0x5CB860
// Store the last-frame index, clamped below the shape's frame count.
void MSShapeAnim::FUN_005CB860(unsigned int value)
{
    LastFrame = value;
    int limit = Buffer->Frames;
    if (value >= (unsigned int)limit)
        LastFrame = limit - 1;
}

// FUNCTION: GAMEMD 0x5CBCB0
// PARTIAL: 83.3% -- the same instructions as retail; cl orders the four frame-rectangle
// loads differently (retail loads X, then the Y offset, then Y, W, H, then the X offset).
// The rectangle of the current frame, moved to where the animation sits and,
// when the centring flag is set, pulled back by half the shape's size.
RectangleStruct MSShapeAnim::GetRect()
{
    RectangleStruct tmp;
    RectangleStruct* frame = Buffer->GetFrameRect(&tmp, Frame);

    RectangleStruct r;
    r.X = frame->X;
    r.Y = frame->Y;
    r.Width = frame->Width;
    r.Height = frame->Height;
    r.Y += Field08;
    r.X += Field04;

    if (Flags & 0x200) {
        r.X -= Buffer->Width / 2;
        r.Y -= Buffer->Height / 2;
    }

    return r;
}

// FUNCTION: GAMEMD 0x5CC760
// PARTIAL: 56.7% -- the same instructions as retail (multiset identical), but cl keeps the caller's flags in EBP
// and re-reads the name where retail holds the name in EBP and the flags in EBX, and spills the new object
// into a dead argument slot. Reading the corner from the stored box rather than the argument scores better.
// Remember the caller's numbers and box; when the file name is not empty, open it as a Bink player and
// move it to the box's corner.
MSBinkAnim::MSBinkAnim(Wstring* name, int flags, int field34, const RectangleStruct* rect, bool field38)
    : MSAnim(rect->X, rect->Y), Player(0), Field20(flags), Bounds(*rect), Field34(field34), Field38(field38)
{
    if ((unsigned int)name->Length() > 0) {
        Player = new MSBinkPlayer(name->FUN_007B5440(), flags);
        Player->Move(Bounds.X, Bounds.Y);
    }
}

// FUNCTION: GAMEMD 0x5CC820
// The Bink animation's destructor, out of line (the scalar deleting destructor expands it inline).
MSBinkAnim::~MSBinkAnim()
{
    delete Player;
}

// FUNCTION: GAMEMD 0x5CC850
// Slot 6: the box the player was opened in.
RectangleStruct MSBinkAnim::GetRect()
{
    return Bounds;
}

// FUNCTION: GAMEMD 0x5CC880
// Slot 7: true when there is no player, or the player reports it has finished.
bool MSBinkAnim::vf_7()
{
    return Player == 0 || Player->IsDone();
}

// FUNCTION: GAMEMD 0x5CCA10
// Slot 8: an empty hook.
void MSBinkAnim::Attach(void* target)
{
}

// FUNCTION: GAMEMD 0x5CCC30
// Build a VQA animation. When there is a name and a surface, the movie is opened with an empty clip pair and
// the volume scale, its destination box is centred (640x400) on the caller's surface and its source box on
// the screen surface; the backdrop is then looked up as "<stem>.PCX" through a stack file object which is
// torn down inline.
MSVQAnim::MSVQAnim(MSStringClass* name, MSSurface* surface, int field24, bool field2c)
    : Player(0), Surface(surface), Field24(field24), Movie(0), Field2C(field2c), Finished(false)
{
    if (name->FUN_007B47F0(0) && surface != 0) {
        MSBounds none2;
        MSBounds none1;
        Player = FUN_005BFAA0(name->FUN_007B5440(), surface, none1, none2, (int)(DAT_00A8EB98 * 255.0), 0);

        if (Player != 0) {
            int y = (surface->Limit() - 400) / 2;
            int x = (surface->Slot31() - 640) / 2;
            RectangleStruct dest = { x, y, 640, 400 };
            Player->Dest = dest;

            y = (DAT_0088730C->Slot32() - 400) / 2;
            x = (DAT_0088730C->Slot31() - 640) / 2;
            RectangleStruct source = { x, y, 640, 400 };
            Player->Source = source;
        }

        MSStringClass stem;
        stem.Init();
        name->Split(0, ".", &stem);

        MSStringClass full;

        MSFileClass file;
        file.Construct(stem.Concat(&full, ".PCX"));
        full.Destruct();

        if (file.Exists(0)) {
            Movie = (MSDeletable*)MSReadPCXFile(&file, 0, 0, 0);
        }

        file.Vtbl    = &VT_007E16B0;
        file.Reset64 = 0;
        ((MemoryBuffer*)file.Sub58)->Clear();
        file.Vtbl    = &VT_007E1668;
        FUN_00431B80(&file);

        stem.Destruct();
    }
}

// FUNCTION: GAMEMD 0x5CCE40
// The VQA animation's destructor, out of line: the movie goes through its own slot-zero deleting
// destructor, then the player is stopped and deleted. The compiler emits its scalar deleting destructor
// 0x5CECB0 beside the constructor above.
MSVQAnim::~MSVQAnim()
{
    if (Movie != 0) {
        Movie->DeletingDtor(1);
    }

    if (Player != 0) {
        Player->Stop();
        delete Player;
    }
}

// Compiler-generated scalar deleting destructor of MSBinkAnim (destructor and base destructor expanded inline).
// SYNTHETIC: GAMEMD 0x5CEC70 -- MSBinkAnim::`scalar deleting destructor'

// Compiler-generated scalar deleting destructor of MSVQAnim, emitted with the vtable 0x7EE9B0 by the constructor.
// SYNTHETIC: GAMEMD 0x5CECB0 -- MSVQAnim::`scalar deleting destructor'
