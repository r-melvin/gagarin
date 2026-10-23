// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   All instruction order and field accesses follow the full retail entry at
//   0x434A40..0x434AA1. The call at +0x11 targets 0x7C93E8; the four calls at
//   +0x29/+0x39/+0x42/+0x54 target 0x7C8B3D, confirmed from rel32 bytes and
//   each target's entry disassembly. The member ABI is confirmed by the
//   vtable slot and one stack flags parameter; both helpers use caller cleanup.
#include "bit_font_scalar_dtor_00434a40.h"

// LIBRARY: GAMEMD 0x7C93E8 (decl; reloc) -- CRT free (the project-wide free symbol is
// bound to operator delete 0x7C8B3D by its other callers).
extern "C" void __cdecl FUN_007C93E8(void* block);

// FUNCTION: GAMEMD 0x434A40
// PARTIAL: retail also re-seats the vtable (0x7E3A78) before freeing; that store
// belongs to a real BitFont class destructor, which this view does not model.
void* BitFontScalarDtorView_00434A40::ScalarDeletingDestructor(unsigned int flags)
{
    void* cachedPixels = unknown_08;
    if (cachedPixels != 0) {
        FUN_007C93E8(cachedPixels);
    }

    BitFontPayload_00434A40* payload = unknown_04;
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
        ::operator delete(this);
    }
    return this;
}
