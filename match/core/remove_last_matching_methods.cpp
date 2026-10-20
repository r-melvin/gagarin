// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x471F90.

#include "remove_last_matching_methods.h"

// FUNCTION: GAMEMD 0x471F90
//
// REGISTER-ALLOCATION DELTA (status partial, 60.5% - 26/43). Everything from
// the key comparison onward is exact, erase loop included. The difference is
// which register carries the key: retail shrink-wraps `PUSH EBX` into the
// guarded block and holds it in EBX, which lets the test be
// `CMP dword ptr [EAX],EBX`; we keep it in the scratch EDX and load the item's
// word separately (`MOV ECX,[EAX]; CMP ECX,EDX`). EBX is not live across the
// free, so nothing in the source demands a callee-saved register - VC6 simply
// picks differently. Seven phrasings were tried: the key held in a local before
// and inside the guard, the comparison written both ways round, the item's word
// hoisted into its own local, the items pointer held, an early-return shape,
// and a volatile key (11.6%, much worse). All land on 60.5%. The cause is NOT
// the toolchain: our objects stamp @comp.id 0x000b20ff, i.e. build 8447.
void Obj_00471F90::FUN_00471F90(void* key)
{
    int index = Count - 1;

    if (index >= 0) {
        void* item = Items[index];

        if (*(void**)item == key) {
            if (item) {
                FUN_007C8B3D(item);
            }

            if (index < Count) {
                int last = Count - 1;

                Count = last;

                for (int j = index; j < Count; j++) {
                    Items[j] = Items[j + 1];
                }
            }
        }
    }
}
