// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, tables and offsets read off the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI at 0x50BD30. The dispatch is a byte index table at
//   0x0050BDC4 (0x26 entries, values 0..4) feeding a five-entry jump table at
//   0x0050BDB0, indexed by `WhatAmI() - 3`:
//
//     WhatAmI 0x03 -> +0x108     WhatAmI 0x10 -> +0x100
//     WhatAmI 0x07 -> +0x110 / +0x10C (see below)
//     WhatAmI 0x28 -> +0x104     default -> the constant at 0x007E2AC8
//
// The case-7 arm splits on the subject's [+0xE08] == 5.
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_ARMOR_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_ARMOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// AbstractType discriminants this dispatch tests.
#define ABS_UNIT_3      0x03
#define ABS_KIND_7      0x07
#define ABS_KIND_10     0x10
#define ABS_KIND_28     0x28

class TechnoClass;

// WhatAmI() at primary-vtable slot +0x2C — zero-argument, so the tree's
// __fastcall-fn-pointer idiom is the right tool.
typedef int (* WhatAmIFunc)(TechnoClass*);
#define TECHNO_WHAT_AM_I(o) ((*(WhatAmIFunc*)(*(char**)(o) + 0x2c))(o))

// Retail RTTI 0x817B58 establishes the class key; public access preserves this ABI view.
class TechnoClass
{
public:
    char _pad000[0xE08];   // +0x0000
    int  unknown_E08;      // +0x0E08  selects between the two case-7 answers
};
GG_STATIC_ASSERT(offsetof(TechnoClass, unknown_E08) == 0xE08);

// The multiplier block on the house's side/country record.
struct HouseArmorRecord
{
    char  _pad000[0x100];  // +0x0000
    float Mult_100;        // +0x0100
    float Mult_104;        // +0x0104
    float Mult_108;        // +0x0108
    float Mult_10C;        // +0x010C
    float Mult_110;        // +0x0110
};
GG_STATIC_ASSERT(offsetof(HouseArmorRecord, Mult_110) == 0x110);

// GLOBAL: GAMEMD 0x007E2AC8 — the default multiplier constant.
extern float DefaultArmorMultiplier;

class HouseClass
{
public:
    char              _pad00[0x34];   // +0x0000
    HouseArmorRecord* Armor;          // +0x0034

    float GetArmorMultiplier(TechnoClass* subject);   // GAMEMD 0x50BD30
};
GG_STATIC_ASSERT(offsetof(HouseClass, Armor) == 0x34);

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_ARMOR_METHODS_H
