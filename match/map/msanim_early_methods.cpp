// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes compared against the user's retail gamemd.exe v1.001 across
//   0x5CB6C0..0x5CCE82, the earlier half of the map-stage animation family
//   whose later half lives in msanim_family_methods.cpp (types from its header).
// Address index: 0x5CB790 0x5CBCB0 0x5CC820 0x5CC880 0x5CCE40

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
void MSShapeAnimView::SetFrame(unsigned int frame)
{
    MSRect old;
    old = GetRectSlot();
    Frame = frame;

    if (!MSRectEqual(old, GetRectSlot())) {
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
MSRect MSShapeAnimView::GetRectSlot()
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

// FUNCTION: GAMEMD 0x5CC820
// The out-of-line copy of the Bink animation's destructor.
void MSBinkAnim_Destroy(MSBinkAnim* self)
{
    self->MSBinkAnim::~MSBinkAnim();
}

// FUNCTION: GAMEMD 0x5CC880
// True when there is no player, or the player reports it has finished.
int MSBinkAnim_IsDone(MSBinkAnim* self)
{
    if (self->Player != 0) {
        if (!self->Player->IsDone()) {
            return 0;
        }
    }

    return 1;
}

// FUNCTION: GAMEMD 0x5CCE40
// The out-of-line copy of the VQA animation's destructor.
void MSVQAnim_Destroy(MSVQAnim* self)
{
    self->MSVQAnim::~MSVQAnim();
}
