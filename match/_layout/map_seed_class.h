// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: TypeDescriptor 0x0082BA10 `.?AVMapSeedClass@@`; class hierarchy descriptor 0x00805930.
//   Bases in RTTI (declaration) order: LoadOptionsClass +0x0.
// VTABLE: GAMEMD 0x7ED8E4 (9 slots)
//   Allocation: operator new (0x7C8E17) of 0x178 bytes at 0x5961BF, 0x596715.
//   Virtual slots are named vf_<slot>; the binary attests no names. Argument counts come from each target's RET n;
//   return types are not recovered (void placeholder). Member offsets come from constructor stores only.
#ifndef GG_MATCH_LAYOUT_MAP_SEED_CLASS_H
#define GG_MATCH_LAYOUT_MAP_SEED_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../ui/load_options_class_methods.h"

class MapSeedClass : public LoadOptionsClass
{
public:
    // 0  0x5AC270: deleting destructor; no destructor of its own is attested (calls the base destructor 0x558790 directly)
    virtual bool Slot1(char const *);                           // 1  0x597A30: override of LoadOptionsClass
    virtual bool Slot2(char const *, unsigned short const *);   // 2  0x597760: override of LoadOptionsClass
    virtual bool DeleteMission(char const *);                   // 3  0x597D50: override of LoadOptionsClass
    virtual bool Slot4(void *, void *);                         // 4  0x597D60: override of LoadOptionsClass
    virtual unsigned short const * Slot5();                     // 5  0x597F80: override of LoadOptionsClass
    virtual unsigned short const * Slot6();                     // 6  0x597FA0: override of LoadOptionsClass
    virtual unsigned short const * Slot7();                     // 7  0x597FC0: override of LoadOptionsClass
    virtual unsigned short const * Slot8();                     // 8  0x597FE0: override of LoadOptionsClass
    unsigned char unknown_10[40];  // +0x10
    int unknown_38;  // +0x38 store at 0x595693
    int unknown_3C;  // +0x3C store at 0x595696
    int unknown_40;  // +0x40 store at 0x595699
    int unknown_44;  // +0x44 store at 0x59569C
    int unknown_48;  // +0x48 store at 0x59569F
    int unknown_4C;  // +0x4C store at 0x5956A2
    int unknown_50;  // +0x50 store at 0x5956A5
    int unknown_54;  // +0x54 store at 0x5956AC
    int unknown_58;  // +0x58 store at 0x5956AF
    int unknown_5C;  // +0x5C store at 0x5956B2
    int unknown_60;  // +0x60 store at 0x5956B5
    int unknown_64;  // +0x64 store at 0x5956B8
    int unknown_68;  // +0x68 store at 0x5956BB
    int unknown_6C;  // +0x6C store at 0x5956BE
    int unknown_70;  // +0x70 store at 0x5956C1
    int unknown_74;  // +0x74 store at 0x5956C4
    unsigned short unknown_78;  // +0x78 store at 0x5956D8
    unsigned char unknown_7A[254];  // +0x7A
};
GG_STATIC_ASSERT(offsetof(MapSeedClass, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(MapSeedClass, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(MapSeedClass, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(MapSeedClass, unknown_44) == 0x44);
GG_STATIC_ASSERT(offsetof(MapSeedClass, unknown_48) == 0x48);
GG_STATIC_ASSERT(offsetof(MapSeedClass, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(MapSeedClass, unknown_50) == 0x50);
GG_STATIC_ASSERT(offsetof(MapSeedClass, unknown_54) == 0x54);
GG_STATIC_ASSERT(offsetof(MapSeedClass, unknown_58) == 0x58);
GG_STATIC_ASSERT(offsetof(MapSeedClass, unknown_5C) == 0x5C);
GG_STATIC_ASSERT(offsetof(MapSeedClass, unknown_60) == 0x60);
GG_STATIC_ASSERT(offsetof(MapSeedClass, unknown_64) == 0x64);
GG_STATIC_ASSERT(offsetof(MapSeedClass, unknown_68) == 0x68);
GG_STATIC_ASSERT(offsetof(MapSeedClass, unknown_6C) == 0x6C);
GG_STATIC_ASSERT(offsetof(MapSeedClass, unknown_70) == 0x70);
GG_STATIC_ASSERT(offsetof(MapSeedClass, unknown_74) == 0x74);
GG_STATIC_ASSERT(offsetof(MapSeedClass, unknown_78) == 0x78);
GG_STATIC_ASSERT(sizeof(MapSeedClass) == 0x178);

#endif  // GG_MATCH_LAYOUT_MAP_SEED_CLASS_H
