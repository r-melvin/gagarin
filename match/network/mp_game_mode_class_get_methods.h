// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x5D5F30: a VC6 function-local static guard (`TEST byte
//   [0xABFD70],1`, `OR CL,1`) wrapping a DynamicVectorClass at 0xABFDA0
//   (vptr 0xABFDA0 = 0x7EED20, Items 0xABFDA4, Capacity 0xABFDA8, IsValid
//   0xABFDAC, IsAllocated 0xABFDAD, Count 0xABFDB0, CapacityIncrement 0xABFDB4 =
//   10), constructed through the VectorClass base ctor CALL 0x5D89F0 with
//   (0, 0) pushed and registered with atexit CALL 0x7C978A for the teardown
//   0x5D5B20 (which restores the base vtable 0x7EED40 and frees Items through
//   0x7C8B3D). The element compare is `CMP [EAX+0x28],ECX` against the
//   __fastcall argument. YRpp names the function
//   `MPGameModeClass::Get`; every offset re-derived here.
//
//   CLASS NAME CORRECTED (whole-image RTTI sweep).
//   `MPGameModeClass` does not exist in this binary -- it is YRpp's own
//   spelling. The locators under the two vtables name the
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
#include "../core/vector_class_operations.h"

// One game mode. Only the member the lookup compares is modelled.
struct MultiplayerGameMode_005D5F30
{
    char _pad000[0x28];   // +0x0000
    int  At_28;           // +0x0028  the identifier Get() searches for
};
GG_STATIC_ASSERT(offsetof(MultiplayerGameMode_005D5F30, At_28) == 0x28);

// VTABLE: GAMEMD 0x7EED40 — VectorClass<MultiplayerGameMode*>.
// VTABLE: GAMEMD 0x7EED20 — DynamicVectorClass<MultiplayerGameMode*>.
// FUNCTION: GAMEMD 0x5D89F0 (decl) — VectorClass(size, array), out-of-line
// instance of the canonical template constructor.
typedef DynamicVectorClass<MultiplayerGameMode_005D5F30*> ModeVector_005D5F30;
GG_STATIC_ASSERT(sizeof(ModeVector_005D5F30) == 0x18);
GG_STATIC_ASSERT(offsetof(ModeVector_005D5F30, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(ModeVector_005D5F30, CapacityIncrement) == 0x14);

// FUNCTION: GAMEMD 0x5D5F30 — MultiplayerGameMode::Get (static).
MultiplayerGameMode_005D5F30* __fastcall MultiplayerGameMode_Get(int index);

#endif  // GG_MATCH_NETWORK_MP_GAME_MODE_CLASS_GET_METHODS_H
