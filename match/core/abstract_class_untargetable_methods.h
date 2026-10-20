// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals, slots and offsets read off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x70D4A0: the flag byte at +0x14 (bit
//   0 = TechnoClass), TechnoClass::Array at 0xA8EC78 (Items 0xA8EC7C, Count
//   0xA8EC88), the techno's +0x294 pointer whose +0x50 is compared with
//   `this`, Health at +0x6C, the byte at +0x90, Target at +0x2B4,
//   CurrentMission at +0xAC, the dword at +0xBC and byte at +0x6D2, the
//   zero-argument slots +0x1F8 and +0x2C (WhatAmI, 2 = infantry) and the
//   one-argument slot +0x3C8, and a second array at 0x8B40E8 (Items
//   0x8B40EC, Count 0x8B40F8) whose entries hold two pointers at +0x3C/+0x40.
//   YRpp (consult-only, no LICENSE) names BecomeUntargetable; every offset
//   reconfirmed here.
#ifndef GG_MATCH_CORE_ABSTRACT_CLASS_UNTARGETABLE_METHODS_H
#define GG_MATCH_CORE_ABSTRACT_CLASS_UNTARGETABLE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Abstract_0070D4A0;
struct Vtbl_0070D4A0;

// Whatever targets this object through +0x294; only its +0x50 owner is read.
struct Link_0070D4A0
{
    char _pad0000[0x50];          // +0x0000
    Abstract_0070D4A0* At_50;     // +0x0050
};
GG_STATIC_ASSERT(offsetof(Link_0070D4A0, At_50) == 0x50);

struct Techno_0070D4A0
{
    Vtbl_0070D4A0* Vptr;              // +0x0000
    char _pad0004[0x6C - 0x04];       // +0x0004
    int  Health;                      // +0x006C
    char _pad0070[0x90 - 0x70];       // +0x0070
    char At_90;                       // +0x0090
    char _pad0091[0xAC - 0x91];       // +0x0091
    int  CurrentMission;              // +0x00AC
    char _pad00B0[0xBC - 0xB0];       // +0x00B0
    int  At_BC;                       // +0x00BC
    char _pad00C0[0x294 - 0xC0];      // +0x00C0
    Link_0070D4A0* At_294;            // +0x0294
    char _pad0298[0x2B4 - 0x298];     // +0x0298
    Abstract_0070D4A0* Target;        // +0x02B4
    char _pad02B8[0x6D2 - 0x2B8];     // +0x02B8
    char At_6D2;                      // +0x06D2
};
GG_STATIC_ASSERT(offsetof(Techno_0070D4A0, Health) == 0x6C);
GG_STATIC_ASSERT(offsetof(Techno_0070D4A0, At_90) == 0x90);
GG_STATIC_ASSERT(offsetof(Techno_0070D4A0, CurrentMission) == 0xAC);
GG_STATIC_ASSERT(offsetof(Techno_0070D4A0, At_BC) == 0xBC);
GG_STATIC_ASSERT(offsetof(Techno_0070D4A0, At_294) == 0x294);
GG_STATIC_ASSERT(offsetof(Techno_0070D4A0, Target) == 0x2B4);
GG_STATIC_ASSERT(offsetof(Techno_0070D4A0, At_6D2) == 0x6D2);

typedef void (Techno_0070D4A0::*Fn1F8_0070D4A0)();
typedef int  (Techno_0070D4A0::*Fn2C_0070D4A0)();
typedef void (Techno_0070D4A0::*Fn3C8_0070D4A0)(Abstract_0070D4A0* target);

struct Vtbl_0070D4A0
{
    char _pad000[0x2C];             // +0x0000
    Fn2C_0070D4A0 WhatAmI;          // +0x002C
    char _pad030[0x1F8 - 0x30];     // +0x0030
    Fn1F8_0070D4A0 At_1F8;          // +0x01F8
    char _pad1FC[0x3C8 - 0x1FC];    // +0x01FC
    Fn3C8_0070D4A0 At_3C8;          // +0x03C8
};
GG_STATIC_ASSERT(offsetof(Vtbl_0070D4A0, WhatAmI) == 0x2C);
GG_STATIC_ASSERT(offsetof(Vtbl_0070D4A0, At_1F8) == 0x1F8);
GG_STATIC_ASSERT(offsetof(Vtbl_0070D4A0, At_3C8) == 0x3C8);

// GLOBAL: GAMEMD 0xA8EC7C — TechnoClass::Array.Items.
extern Techno_0070D4A0** DAT_00A8EC7C;
// GLOBAL: GAMEMD 0xA8EC88 — TechnoClass::Array.Count.
extern int DAT_00A8EC88;

// An entry of the second array; two object references at +0x3C / +0x40.
struct Ref_0070D4A0
{
    char _pad0000[0x3C];          // +0x0000
    Abstract_0070D4A0* At_3C;     // +0x003C
    Abstract_0070D4A0* At_40;     // +0x0040
};
GG_STATIC_ASSERT(offsetof(Ref_0070D4A0, At_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(Ref_0070D4A0, At_40) == 0x40);

// GLOBAL: GAMEMD 0x8B40EC — the second array's Items.
extern Ref_0070D4A0** DAT_008B40EC;
// GLOBAL: GAMEMD 0x8B40F8 — the second array's Count.
extern int DAT_008B40F8;

struct Abstract_0070D4A0
{
    void* Vptr;              // +0x0000
    char _pad0004[0x10];     // +0x0004
    char AbstractFlags;      // +0x0014  bit 0 = TechnoClass

    // FUNCTION: GAMEMD 0x70D4A0 — AbstractClass::BecomeUntargetable.
    void BecomeUntargetable();
};
GG_STATIC_ASSERT(offsetof(Abstract_0070D4A0, AbstractFlags) == 0x14);

#endif  // GG_MATCH_CORE_ABSTRACT_CLASS_UNTARGETABLE_METHODS_H
