// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x5D5F30: a VC6 function-local static guard (`TEST byte
//   [0xABFD70],1`, `OR CL,1`) wrapping a DynamicVectorClass at 0xABFDA0
//   (vptr 0xABFDA0 = 0x7EED20, Items 0xABFDA4, Capacity 0xABFDA8, IsValid
//   0xABFDAC, IsAllocated 0xABFDAD, Count 0xABFDB0, GrowthStep 0xABFDB4 =
//   10), constructed through the VectorClass base ctor CALL 0x5D89F0 with
//   (0, 0) pushed and registered with atexit CALL 0x7C978A for the teardown
//   0x5D5B20 (which restores the base vtable 0x7EED40 and frees Items through
//   0x7C8B3D). The element compare is `CMP [EAX+0x28],ECX` against the
//   __fastcall argument. YRpp (consult-only, no LICENSE) names the function
//   `MPGameModeClass::Get`; every offset re-derived here.
//
//   CLASS NAME CORRECTED (whole-image RTTI sweep, docs/rtti_sweep.md).
//   `MPGameModeClass` does not exist in this binary -- it is YRpp's own
//   spelling, not Westwood's. The locators under the two vtables name the
//   retail class, re-read here with `ghidra memory read` rather than taken on
//   the sweep's word:
//     [0x7EED3C] = 0x00806F58 -> TD 0x008307C0
//                  `.?AV?$VectorClass@PAVMultiplayerGameMode@@@@`
//     [0x7EED1C] = 0x00806F28 -> TD 0x008307F8
//                  `.?AV?$DynamicVectorClass@PAVMultiplayerGameMode@@@@`
//   so the element class is `MultiplayerGameMode`. Its concrete modes in the
//   image are FreeForAll, Megawealth, UnholyAlliance, MultiplayerSiege,
//   MPCooperative, MultiplayerBattle and MultiplayerManBattle, with the nested
//   MultiplayerGameMode::Initializer<T> / ::InitializerBase. Layout agrees with
//   match/core/vector_array_init_methods.h (VectorClass 0x10, +0x10 count,
//   +0x14 growth step).
#ifndef GG_MATCH_NETWORK_MP_GAME_MODE_CLASS_GET_METHODS_H
#define GG_MATCH_NETWORK_MP_GAME_MODE_CLASS_GET_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// One game mode. Only the member the lookup compares is modelled.
struct MultiplayerGameMode_005D5F30
{
    char _pad000[0x28];   // +0x0000
    int  At_28;           // +0x0028  the identifier Get() searches for
};
GG_STATIC_ASSERT(offsetof(MultiplayerGameMode_005D5F30, At_28) == 0x28);

// VTABLE: GAMEMD 0x7EED40 — VectorClass<MultiplayerGameMode*>.
extern void* const VTBL_007EED40[];
// VTABLE: GAMEMD 0x7EED20 — DynamicVectorClass<MultiplayerGameMode*>.
extern void* const VTBL_007EED20[];

// FUNCTION: GAMEMD 0x7C8E17 (decl; reloc) — operator new.
extern "C" void* __cdecl FUN_007C8E17(unsigned int size);
// FUNCTION: GAMEMD 0x7C8B3D (decl; reloc) — CRT free.
extern "C" void __cdecl FUN_007C8B3D(void* block);

// VectorClass<MultiplayerGameMode*> (sizeof 0x10). The constructor body is read
// off retail's out-of-line 0x5D89F0 (zero Items, take the size, set IsValid,
// clear IsAllocated, install the base vtable, then adopt or allocate the
// array); it is defined inline because retail's second guard expansion has it
// folded in with size == 0. The destructor lives on the derived class so the
// derived constructor stays inlinable under /GX (a base with a destructor
// makes cl 8804 emit the derived constructor out of line).
struct ModeVectorBase_005D5F30
{
    void*                   Vptr;          // +0x0000
    MultiplayerGameMode_005D5F30**   Items;         // +0x0004
    int                     Capacity;      // +0x0008
    char                    IsValid;       // +0x000C
    char                    IsAllocated;   // +0x000D
    char                    _pad00E[2];    // +0x000E

    // FUNCTION: GAMEMD 0x5D89F0 (decl; body per the retail disassembly,
    // expanded inline here) — VectorClass(size, array).
    ModeVectorBase_005D5F30(int size, MultiplayerGameMode_005D5F30** array)
    {
        Items = 0;
        Capacity = size;
        IsValid = 1;
        IsAllocated = 0;
        Vptr = (void*)VTBL_007EED40;
        if (size != 0) {
            if (array != 0) {
                Items = array;
            } else {
                Items = (MultiplayerGameMode_005D5F30**)FUN_007C8E17(size * 4);
                IsAllocated = 1;
            }
        }
    }
};
GG_STATIC_ASSERT(offsetof(ModeVectorBase_005D5F30, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(ModeVectorBase_005D5F30, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(ModeVectorBase_005D5F30, IsValid) == 0x0C);
GG_STATIC_ASSERT(offsetof(ModeVectorBase_005D5F30, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(sizeof(ModeVectorBase_005D5F30) == 0x10);

// DynamicVectorClass<MultiplayerGameMode*> (sizeof 0x18). The constructor stores
// in retail's order (vtable, GrowthStep, Count); the destructor is what the
// atexit teardown 0x5D5B20 inlines.
struct ModeVector_005D5F30 : ModeVectorBase_005D5F30
{
    int Count;        // +0x0010
    int GrowthStep;   // +0x0014

    __forceinline ModeVector_005D5F30()
        : ModeVectorBase_005D5F30(0, 0)
    {
        Vptr = (void*)VTBL_007EED20;
        GrowthStep = 10;
        Count = 0;
    }

    ~ModeVector_005D5F30()
    {
        Vptr = (void*)VTBL_007EED40;
        if (Items != 0 && IsAllocated != 0) {
            FUN_007C8B3D(Items);
            Items = 0;
        }
        IsAllocated = 0;
        Capacity = 0;
    }
};
GG_STATIC_ASSERT(offsetof(ModeVector_005D5F30, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(ModeVector_005D5F30, GrowthStep) == 0x14);
GG_STATIC_ASSERT(sizeof(ModeVector_005D5F30) == 0x18);

// FUNCTION: GAMEMD 0x5D5F30 — MultiplayerGameMode::Get (static).
MultiplayerGameMode_005D5F30* __fastcall MultiplayerGameMode_Get(int index);

#endif  // GG_MATCH_NETWORK_MP_GAME_MODE_CLASS_GET_METHODS_H
