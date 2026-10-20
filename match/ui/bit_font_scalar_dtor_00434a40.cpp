// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   All instruction order and field accesses follow the full retail entry at
//   0x434A40..0x434AA1. The call at +0x11 targets 0x7C93E8; the four calls at
//   +0x29/+0x39/+0x42/+0x54 target 0x7C8B3D, confirmed from rel32 bytes and
//   each target's entry disassembly. The member ABI is confirmed by the
//   vtable slot and one stack flags parameter; both helpers use caller cleanup.
#include "bit_font_scalar_dtor_00434a40.h"

// FUNCTION: GAMEMD 0x434A40
void* BitFontScalarDtorView_00434A40::ScalarDeletingDestructor(unsigned int flags)
{
    BitFontScalarDtorView_00434A40* self = this;
    void* cachedPixels = self->unknown_08;
    self->unknown_00 = (void*)0x7E3A78;
    if (cachedPixels != 0) {
        ::free(cachedPixels);
    }

    BitFontPayload_00434A40* payload = self->unknown_04;
    if (payload != 0) {
        if (payload->unknown_18 != 0) {
            ::operator delete(payload->unknown_18);
        }
        if (payload->unknown_1C != 0) {
            ::operator delete(payload->unknown_1C);
        }
        ::operator delete(payload);
    }

    if ((flags & 1) != 0) {
        ::operator delete(self);
    }
    return self;
}
