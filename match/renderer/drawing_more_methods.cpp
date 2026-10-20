// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Every offset
//   and vtable slot reconfirmed from the member-access disassembly at 0x7BCF50 /
//   0x7BD130; names cross-checked against YRpp Surface.h / Drawing.h
//   (consult-only, no LICENSE). Both targets are byte-for-byte identical to the
//   already-matched ABuffer::Fill (0x4112D0) / ABuffer::GetBuffer (0x4114B0).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x7BCF50   AlphaBuffer::Fill        (__thiscall)
//   FUNCTION: GAMEMD 0x7BD130   AlphaBuffer::GetBuffer   (__thiscall)

#include "drawing_more_methods.h"

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x7BCF50  (__thiscall)
// Fill the whole buffer: build a full-extent rect {0,0,Width,Height} and hand
// it to the surface's FillRect virtual (slot 0x14) with the 16-bit colour
// (zero-extended -> AND EDX,0xffff).
// ---------------------------------------------------------------------------
bool AlphaBuffer::Fill(unsigned short Color)
{
    RectangleStruct rect;
    rect.X = 0;
    rect.Y = 0;
    rect.Width = this->Width;
    rect.Height = this->Height;
    return this->Surface->FillRect(&rect, Color);
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x7BD130  (__thiscall)
// Compute a circular-buffer pointer: BufferPosition + Surface->GetOffset(X,Y),
// wrapped down by BufferSize once it reaches BufferTail (unsigned compare).
// Surface->Lock() (slot 0x60) is called for its side effect; its return is
// discarded.
// ---------------------------------------------------------------------------
void* AlphaBuffer::GetBuffer(int X, int Y)
{
    unsigned int offset = (unsigned int)this->Surface->GetOffset(X, Y);
    this->Surface->Lock();
    unsigned int pos = (unsigned int)this->BufferPosition + offset;
    if (pos >= (unsigned int)this->BufferTail)
        pos -= (unsigned int)this->BufferSize;
    return (void*)pos;
}
