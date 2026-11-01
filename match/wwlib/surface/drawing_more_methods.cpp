// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// Legacy GetBuffer ABI retained at7BD130. Caller ownership is ZBuffer887644;
// migration to canonical Surface::Lock(Point2D)/Unlock is held at65.2%.
// Fill7BCF50 now belongs to zbuffer_class_methods.cpp after exact proof.
#include "drawing_more_methods.h"

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x7BD130  (__thiscall)
// Compute a circular-buffer pointer: BufferPosition + Surface->vf_23(X,Y),
// wrapped down by BufferSize once it reaches BufferTail (unsigned compare).
// Surface->Lock() (slot 0x60) is called for its side effect; its return is
// discarded.
// ---------------------------------------------------------------------------
void* AlphaBuffer::GetBuffer(int X, int Y)
{
    unsigned int offset = (unsigned int)this->Surface->vf_23(X, Y);
    this->Surface->Lock();
    unsigned int pos = (unsigned int)this->BufferPosition + offset;
    if (pos >= (unsigned int)this->BufferTail)
        pos -= (unsigned int)this->BufferSize;
    return (void*)pos;
}
