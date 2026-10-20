// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check

#include "locomotion_com_helpers.h"

// FUNCTION: GAMEMD 0x70F0B0
//
// Map a locomotor kind onto its expansion replacement. Only two kinds are
// remapped, and only while the expansion's rule set is active; everything
// else is handed back unchanged.
int __fastcall FUN_0070F0B0(int kind, int, int)
{
    bool expansion = FUN_00731BF0();
    if (kind == 1) {
        if (expansion) {
            return 0x3E;
        }
    } else if (kind == 5) {
        if (expansion) {
            return 0x3F;
        }
    }
    return kind;
}

// FUNCTION: GAMEMD 0x719EE0
//
// Hand the pending object over to the caller, clearing the two fields the
// secondary COM base uses to remember it. Answers the no-interface code for a
// null destination, zero on a successful hand-off and one when there was
// nothing pending.
long __stdcall FUN_00719EE0(Owner_00719EE0* self, void** out)
{
    if (out == 0) {
        return 0x80004003;
    }

    ComBase_00719EE0* base = *(ComBase_00719EE0**)((char*)self - 0xC);
    if (base != 0) {
        base->Pending428 = 0;
        (*(ComBase_00719EE0**)((char*)self - 0xC))->Pending42C = 0;
    }

    void* pending = self->Pending;
    if (pending != 0) {
        *out = pending;
        self->Pending = 0;
        return 0;
    }
    return 1;
}
