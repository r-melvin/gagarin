// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Each offset,
//   vtable slot and global reconfirmed below from the member-access disassembly;
//   names cross-checked against YRpp.
//
// Function address overview (definitions below carry reccmp markers):
//   0x410E50   ABuffer::ReleaseSurface  (__thiscall)
//   0x4112D0   ABuffer::Fill            (__thiscall)
//   0x411310   ABuffer::FillRect        (__thiscall)
//   0x4114B0   ABuffer::GetBuffer       (__thiscall)
//   0x4355D0   Drawing::RGB_To_Int      (__fastcall)

#include "pixel_shift_view.h"
#include "drawing.h"

// Pixel shift cells are owned by the shared reconstruction storage.

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x410DC0  (__thiscall, RET 0x14)
// Copy a width x height block of 16-bit pixels out of the ring buffer into the
// surface at (x, y): the source wraps back by BufferSize each time it reaches
// BufferTail, and the destination advances by the surface's row pitch less the
// copied width after each row.
//
// PARTIAL: 93.1% -- the instruction multiset is identical; the residual is the
// first four instructions' register naming (retail loads x into EAX and the
// surface vtable into EDX, cl does the reverse). Variants tried: the offset in
// its own int local, the position sum written the other way round, and plain
// value temporaries for x and y (all 93.1% or worse).
// ---------------------------------------------------------------------------
void ABuffer::FUN_00410DC0(BSurfaceLayout* dest, int x, int y, int width, int height)
{
    unsigned short* target = (unsigned short*)dest->vf_23(x, y);
    unsigned int source = (unsigned int)this->BufferHead + this->BufferPosition;
    int skip = dest->vf74() / 2 - width;
    if (target && height > 0) {
        for (int row = height; row > 0; row--) {
            for (int col = width; col > 0; col--) {
                *target++ = *(unsigned short*)source;
                source += 2;
                if (source >= (unsigned int)this->BufferTail)
                    source -= this->BufferSize;
            }
            target += skip;
        }
    }
    dest->Lock();
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x410E50  (__thiscall)
// Release the backing surface (virtual slot 0, "delete this" flag = 1) and
// null the pointer. The null-store is unconditional in retail.
// ---------------------------------------------------------------------------
void ABuffer::ReleaseSurface()
{
    if (this->Surface)
        this->Surface->Destroy(1);
    this->Surface = 0;
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x4112D0  (__thiscall)
// Fill the whole buffer: build a full-extent rect {0,0,Width,Height} and hand
// it to the surface's FillRect virtual (slot 0x14) with the 16-bit colour.
// ---------------------------------------------------------------------------
bool ABuffer::Fill(unsigned short Color)
{
    RectangleStruct rect;
    rect.X = 0;
    rect.Y = 0;
    rect.Width = this->Width;
    rect.Height = this->Height;
    return this->Surface->FillRect(&rect, Color);
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x411310  (__thiscall)
// Forward a by-value rect straight to the surface's FillRect virtual.
// ---------------------------------------------------------------------------
bool ABuffer::FillRect(unsigned short Color, RectangleStruct Rect)
{
    return this->Surface->FillRect(&Rect, Color);
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x4114B0  (__thiscall)
// Compute a circular-buffer pointer: BufferPosition + Surface->vf_23(X,Y),
// wrapped down by BufferSize once it reaches BufferTail (unsigned compare).
// Surface->Lock() (slot 0x60) is called for its side effect; its return is
// discarded.
// ---------------------------------------------------------------------------
void* ABuffer::GetBuffer(int X, int Y)
{
    unsigned int offset = (unsigned int)this->Surface->vf_23(X, Y);
    this->Surface->Lock();
    unsigned int pos = (unsigned int)this->BufferPosition + offset;
    if (pos >= (unsigned int)this->BufferTail)
        pos -= (unsigned int)this->BufferSize;
    return (void*)pos;
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x4355D0  (__fastcall: red=ECX, green=EDX, blue=stack)
// Pack (r,g,b) into the surface's current packed-colour format by quantising
// each channel (>> shiftRight) then repositioning it (<< shiftLeft).
// ---------------------------------------------------------------------------
int Drawing::RGB_To_Int(int red, int green, int blue)
{
    return (red >> gg_b_translucent_pixel_format.loss0 << gg_b_translucent_pixel_format.pos0)
         | (green >> gg_b_translucent_pixel_format.loss1 << gg_b_translucent_pixel_format.pos1)
         | (blue >> gg_b_translucent_pixel_format.loss2 << gg_b_translucent_pixel_format.pos2);
}
