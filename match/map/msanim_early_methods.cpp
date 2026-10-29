// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes compared against the user's retail gamemd.exe v1.001 across
//   0x5CB6C0..0x5CCE82, the earlier half of the map-stage animation family
//   whose later half lives in msanim_family_methods.cpp (types from its header).
// Address index: 0x5CB790 0x5CBCB0 0x5CC760 0x5CC820 0x5CC850 0x5CC880 0x5CCA10 0x5CCE40 0x5CEC70

#include "msanim_family_methods.h"

// GLOBAL: GAMEMD 0x88730C -- the blitter the shape animations redraw through.
extern MSBlitSurface* DAT_0088730C;

__forceinline static bool MSRectEqual(const MSRect& a, const MSRect& b)
{
    return a.X == b.X && a.Y == b.Y && a.Width == b.Width
        && a.Height == b.Height;
}

// FUNCTION: GAMEMD 0x5CB790
// Jump to a frame. When the rectangle moves, the screen is redrawn over the
// old position; the frame is then clamped to the last one in the file.
void MSShapeAnim::SetFrame(unsigned int frame)
{
    MSRect old;
    old = GetRect();
    Frame = frame;

    if (!MSRectEqual(old, GetRect())) {
        DAT_0088730C->Blit(&old, MSScreenSurface, &old, 0, 1);
    }

    if (Frame >= (unsigned int)Buffer->Frames) {
        Frame = Buffer->Frames - 1;
    }
}

// FUNCTION: GAMEMD 0x5CBCB0
// PARTIAL: 83.3% -- the same instructions as retail; cl orders the four frame-rectangle
// loads differently (retail loads X, then the Y offset, then Y, W, H, then the X offset).
// The rectangle of the current frame, moved to where the animation sits and,
// when the centring flag is set, pulled back by half the shape's size.
MSRect MSShapeAnim::GetRect()
{
    MSRect tmp;
    MSRect* frame = Buffer->GetFrameRect(&tmp, Frame);

    MSRect r;
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
MSBinkAnim::MSBinkAnim(Wstring* name, int flags, int field34, const MSRect* rect, bool field38)
    : MSAnim(rect->X, rect->Y), Player(0), Field20(flags), Bounds(*rect), Field34(field34), Field38(field38)
{
    if ((unsigned int)name->Length() > 0) {
        Player = new MSBinkPlayer(name->FUN_007B5440(), flags);
        Player->Move(Bounds.X, Bounds.Y);
    }
}

// FUNCTION: GAMEMD 0x5CC820
// The out-of-line copy of the Bink animation's destructor.
void MSBinkAnim_Destroy(MSBinkAnim* self)
{
    self->MSBinkAnim::~MSBinkAnim();
}

// FUNCTION: GAMEMD 0x5CC850
// Slot 6: the box the player was opened in.
MSRect MSBinkAnim::GetRect()
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

// FUNCTION: GAMEMD 0x5CCE40
// The out-of-line copy of the VQA animation's destructor.
void MSVQAnim_Destroy(MSVQAnim* self)
{
    self->MSVQAnim::~MSVQAnim();
}

// Compiler-generated scalar deleting destructor of MSBinkAnim (destructor and base destructor expanded inline).
// SYNTHETIC: GAMEMD 0x5CEC70 -- MSBinkAnim::`scalar deleting destructor'
