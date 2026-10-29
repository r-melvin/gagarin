// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.

#include "ebolt_fire_methods.h"

void __cdecl operator delete(void*);

// The object an EBolt links back to: its +0x6DC member points at the bolt's slot.
struct EBoltOwner_004C29E0
{
    char  _pad0000[0x6DC];   // +0x0000
    void* At_6DC;            // +0x06DC
};
GG_STATIC_ASSERT(offsetof(EBoltOwner_004C29E0, At_6DC) == 0x6DC);

// FUNCTION: GAMEMD 0x4C29E0
//
// Destroy every live bolt, unhooking each from the object it is linked to, then
// free the list's storage if it owns it and reset the list.
void FUN_004C29E0()
{
    for (int i = 0; i < DAT_008A0E88.Count; i++) {
        EBolt* bolt = DAT_008A0E88.Items[i];
        if (bolt != 0) {
            if (bolt->At_20 != 0) {
                bolt->At_20->At_6DC = 0;
                bolt->At_20 = 0;
            }
            delete bolt;
        }
    }
    DAT_008A0E88.Count = 0;
    if (DAT_008A0E88.Items != 0 && DAT_008A0E88.IsAllocated != 0) {
        delete DAT_008A0E88.Items;
        DAT_008A0E88.Items = 0;
    }
    DAT_008A0E88.IsAllocated = 0;
    DAT_008A0E88.Capacity = 0;
}
