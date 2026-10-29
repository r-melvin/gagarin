// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x4F9AF0 (CanOverpower)
//   and 0x50C8C0 (Cheer), via the local Ghidra CLI. Cross-checked vs YRpp
//   (every
//   offset, vtable slot and global address reconfirmed against the disasm).
//
// Only the members/slots these two methods touch are modelled:
//   HouseClass: ArrayIndex @0x30, Allies bitfield dword @0x5788.
//   TechnoClass: AbstractFlags @0x14 (byte test &2), Owner @0x21C, and two
//     virtuals — GetOwningHouse @vtable+0x3C (slot 15) and the cheer hook
//     @vtable+0x388 (slot 226). The filler virtuals are declared (never
//     defined) only to place the indirect calls at the exact vtable byte
//     offsets; a real virtual member is the only construct that both puts
//     `this` in ECX and emits `call [vtable+N]`.
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_OVERPOWER_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_OVERPOWER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/house_class.h"

class HouseClass;  // forward declaration (TechnoClass::GetOwningHouse / Owner)

// ---------------------------------------------------------------------------
// TechnoClass — modelled as the polymorphic game object whose primary vtable
// carries GetOwningHouse() at slot 15 (+0x3C) and the per-house cheer hook
// at slot 226 (+0x388). Data members: AbstractFlags @0x14, Owner @0x21C.
// ---------------------------------------------------------------------------
#include "../_layout/techno_class.h"


#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(TechnoClass, Flags) == 0x14);
GG_STATIC_ASSERT(offsetof(TechnoClass, Owner)         == 0x21C);
#endif

// ---------------------------------------------------------------------------
// HouseClass — only ArrayIndex (+0x30) and the Allies bitfield dword (+0x5788)
// are touched (by CanOverpower). Cheer uses `this` only as an identity value.
// ---------------------------------------------------------------------------


#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(HouseClass, ArrayIndex) == 0x30);
GG_STATIC_ASSERT(offsetof(HouseClass, Allies)     == 0x5788);
#endif

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_OVERPOWER_METHODS_H
