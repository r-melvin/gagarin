// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// The six hash-bucket index functions, ordered ascending by retail address.
//
// Binding the hash result to a named local before the mask expression is the
// whole phrasing lever here. Retail computes the call first and builds the mask
// afterwards in EAX, ANDing the saved hash in EDX into it. Written inline --
// in either operand order, `mask & self->Hash(key)` or `self->Hash(key) & mask`
// -- cl builds the mask in EDX and ANDs into EAX, which reverses every register
// in the tail and scores 50%. The named local fixes the evaluation order and
// takes it to 100%.

#include "hash_bucket_mask_sweep.h"

// FUNCTION: GAMEMD 0x624C80
int __fastcall FUN_00624C80(HashTableIndex* self, int, const void* key)
{
    int hash = self->Hash(key);

    return ((1 << self->BitWidth) - 1) & hash;
}

// FUNCTION: GAMEMD 0x625070
int __fastcall FUN_00625070(HashTableIndex* self, int, const void* key)
{
    int hash = self->Hash(key);

    return ((1 << self->BitWidth) - 1) & hash;
}

// FUNCTION: GAMEMD 0x625390
int __fastcall FUN_00625390(HashTableIndex* self, int, const void* key)
{
    int hash = self->Hash(key);

    return ((1 << self->BitWidth) - 1) & hash;
}

// FUNCTION: GAMEMD 0x7AE0C0
int __fastcall FUN_007AE0C0(HashTableIndex* self, int, const void* key)
{
    int hash = self->Hash(key);

    return ((1 << self->BitWidth) - 1) & hash;
}

// FUNCTION: GAMEMD 0x7AE5B0
int __fastcall FUN_007AE5B0(HashTableIndex* self, int, const void* key)
{
    int hash = self->Hash(key);

    return ((1 << self->BitWidth) - 1) & hash;
}

// FUNCTION: GAMEMD 0x7AECB0
int __fastcall FUN_007AECB0(HashTableIndex* self, int, const void* key)
{
    int hash = self->Hash(key);

    return ((1 << self->BitWidth) - 1) & hash;
}

