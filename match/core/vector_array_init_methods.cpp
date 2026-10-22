// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x412870.

#include "vector_array_init_methods.h"

// FUNCTION: GAMEMD 0x412870
//
// Static initialiser for 0x190 growable vectors plus one more, and the atexit
// registration that tears them down again.
//
// The array entries call their base constructor; the trailing instance has it
// inlined instead — its four base stores appear literally (+0x4, +0x8, +0xC,
// +0xD) with no call. That asymmetry is retail's, and it is what an empty size
// argument allows: with the size known to be zero the base's only branch folds
// away and nothing is left to call.
//
// Every zero comes from one register, so it is written as a named variable.
void FUN_00412870()
{
    int zero = 0;

    Vec_00412870* entry = DAT_00887888;
    int remaining = 0x190;
    do {
        entry->BaseCtor(zero, (const void*)zero);
        entry->Vptr = (Vtbl_00412870*)VTBL_007E17AC;
        entry->CapacityIncrement = 10;
        entry->Count = zero;
        entry++;
        remaining--;
    } while (remaining != 0);

    DAT_00889E08.Vector = (const void*)zero;
    DAT_00889E08.Capacity = zero;
    DAT_00889E08.IsValid = 1;
    DAT_00889E08.IsAllocated = (char)zero;
    DAT_00889E08.Vptr = (Vtbl_00412870*)VTBL_007E17AC;
    DAT_00889E08.CapacityIncrement = 10;
    DAT_00889E08.Count = zero;

    FUN_007C978A(FUN_004128F0_atexit);
}

// FUNCTION: GAMEMD 0x4128F0
//
// The teardown 0x412870 registers with atexit. Two passes over the same array:
// first every element is emptied through its own vtable, then every element is
// destroyed — and the second pass runs backwards, which is how an array of
// objects is destroyed.
//
// The capacity is read out of each element *before* the first call and handed to
// the second, so the emptying is "release, then re-establish the old capacity at
// zero fill" rather than two independent calls.
//
// The destruction pass walks a cursor that starts one element past the end and
// steps back before each use, so every access is a negative displacement off it.
// That is retail's shape (`MOV EAX,[ESI-0x18]` then `SUB ESI,0x18`), not an
// artifact.
void __cdecl FUN_004128F0()
{
    int zero = 0;

    Vec_00412870* entry = DAT_00887888;
    int remaining = 0x190;
    do {
        int capacity = entry->Capacity;
        (entry->*entry->Vptr->At_0C)();
        (entry->*entry->Vptr->At_08)(capacity, zero);
        entry++;
        remaining--;
    } while (remaining != 0);

    int capacity = DAT_00889E08.Capacity;
    (DAT_00889E08.*DAT_00889E08.Vptr->At_0C)();
    (DAT_00889E08.*DAT_00889E08.Vptr->At_08)(capacity, zero);

    Vtbl_00412870* dead = (Vtbl_00412870*)VTBL_007E180C;

    DAT_00889E08.Vptr = dead;
    if (DAT_00889E08.Vector != 0 && DAT_00889E08.IsAllocated != (char)zero) {
        FUN_007C8B3D((void*)DAT_00889E08.Vector);
        DAT_00889E08.Vector = (const void*)zero;
    }
    DAT_00889E08.IsAllocated = (char)zero;
    DAT_00889E08.Capacity = zero;

    Vec_00412870* cursor = &DAT_00889E08;
    int left = 0x190;
    do {
        cursor--;
        cursor->Vptr = dead;
        if (cursor->Vector != 0 && cursor->IsAllocated != (char)zero) {
            FUN_007C8B3D((void*)cursor->Vector);
            cursor->Vector = (const void*)zero;
        }
        left--;
        cursor->IsAllocated = (char)zero;
        cursor->Capacity = zero;
    } while (left != 0);
}
