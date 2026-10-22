// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// The four seven-byte constant stores, ordered ascending by retail address.

#include "const_store_leaf_sweep.h"

// FUNCTION: GAMEMD 0x5D8FC0
void __fastcall FUN_005D8FC0(ConstStoreObject* self)
{
    self->Head = 0;
}


// FUNCTION: GAMEMD 0x65D660
// VTABLE: GAMEMD 0x7F0954
void __fastcall FUN_0065D660(ConstStoreObject* self)
{
    self->Head = VTABLE_007F0954;
}

