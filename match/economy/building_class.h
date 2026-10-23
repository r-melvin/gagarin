// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x451E40, 0x4521C0, 0x452210,
//   0x4525F0, 0x457630, 0x457690), cross-checked against YRpp
//   (every offset
//   reconfirmed numerically against the user's binary below).
//
// BuildingClass, AnimClass and BuildingTypeClass come from the canonical
// headers; the methods touch Owner +0x21C, UnloadTimer +0x350 (0x4A51B0),
// Type +0x520, Anims[0x15] +0x55C and HasPower +0x660.
#ifndef GG_MATCH_ECONOMY_BUILDING_CLASS_H
#define GG_MATCH_ECONOMY_BUILDING_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/building_class.h"
#include "../_layout/anim_class.h"

// HouseClass — only the super-weapon-slots sub-object at +0x5550 is modelled
// (First/SecondActiveSWIdx call `lea ecx,[Owner+0x5550]; call 0x49FAE0(arg)`).
struct SWSlotsClass
{
    int IsActive_49FAE0(int swType);     // GAMEMD 0x49FAE0 __thiscall (declared; reloc)
};
class HouseClass
{
public:
    char         _pad_0000[0x5550];      // +0x0000  (full layout is P2)
    SWSlotsClass SWSlots;                // +0x5550
};
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(HouseClass, SWSlots) == 0x5550);
#endif




// SuperWeapon chain reached by First/SecondActiveSWIdx, via the global array at
// 0x00A83CBC (a SWTypeClass** array). node->[0x28]->[0xC8]->[0xDF8].
struct SWChainC8 { char _p[0xDF8]; int field_DF8; };          // +0xDF8
struct SWChain28 { char _p[0xC8];  SWChainC8* field_C8; };    // +0xC8
struct SWChainNode { char _p[0x28]; SWChain28* field_28; };   // +0x28

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(SWChainNode, field_28) == 0x28);
GG_STATIC_ASSERT(offsetof(SWChain28,  field_C8) == 0xC8);
GG_STATIC_ASSERT(offsetof(SWChainC8,  field_DF8) == 0xDF8);
#endif

// GLOBAL: GAMEMD 0x00A83CBC — pointer to the SWTypeClass* array (Items).
extern SWChainNode** g_SWArray;


#endif  // GG_MATCH_ECONOMY_BUILDING_CLASS_H
