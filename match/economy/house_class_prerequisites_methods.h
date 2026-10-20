// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x505360: the techno type's Prerequisite list
//   `[ECX+0x63C]` (Items) / `[EAX+0x648]` (Count), the owned-building
//   vector's Items `[EBP+0x4]`, BuildingTypeClass::Array.Items at 0xA83C6C,
//   and the six generic prerequisite lists on RulesClass 0x8871E0 reached
//   through a jump table on the negative index (-1 +0x8C8, -2 +0x938,
//   -3 +0x900, -4 +0xA34, -5 +0x91C, -6 +0x8E4), each read through Count
//   +0x10 and vtable slot +0x18 (one pushed index). `this` (ECX) is unused;
//   YRpp still models the method as a member. Names cross-checked against
//   YRpp HouseClass.h / RulesClass.h (consult-only; NO LICENSE).
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_PREREQUISITES_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_PREREQUISITES_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct BuildingType_00505360;

struct ListVtbl_00505360;

// A generic prerequisite list (TypeList<int>): only Count and the item
// accessor slot are used.
struct List_00505360
{
    ListVtbl_00505360* Vptr;      // +0x0000
    char               _pad004[0xC]; // +0x0004
    int                Count;     // +0x0010
};
GG_STATIC_ASSERT(offsetof(List_00505360, Count) == 0x10);

typedef BuildingType_00505360* (List_00505360::*Fn18_00505360)(int index);

struct ListVtbl_00505360
{
    char           _pad000[0x18];   // +0x0000
    Fn18_00505360  At_18;           // +0x0018
};
GG_STATIC_ASSERT(offsetof(ListVtbl_00505360, At_18) == 0x18);

// RulesClass — the six generic prerequisite lists.
struct Rules_00505360
{
    char            _pad000[0x8C8];            // +0x0000
    List_00505360   PrerequisitePower;         // +0x08C8
    char            _pad8DC[0x8E4 - 0x8DC];    // +0x08DC
    List_00505360   PrerequisiteFactory;       // +0x08E4
    char            _pad8F8[0x900 - 0x8F8];    // +0x08F8
    List_00505360   PrerequisiteBarracks;      // +0x0900
    char            _pad914[0x91C - 0x914];    // +0x0914
    List_00505360   PrerequisiteRadar;         // +0x091C
    char            _pad930[0x938 - 0x930];    // +0x0930
    List_00505360   PrerequisiteTech;          // +0x0938
    char            _pad94C[0xA34 - 0x94C];    // +0x094C
    List_00505360   At_A34;                    // +0x0A34
};
GG_STATIC_ASSERT(offsetof(Rules_00505360, PrerequisitePower)    == 0x8C8);
GG_STATIC_ASSERT(offsetof(Rules_00505360, PrerequisiteFactory)  == 0x8E4);
GG_STATIC_ASSERT(offsetof(Rules_00505360, PrerequisiteBarracks) == 0x900);
GG_STATIC_ASSERT(offsetof(Rules_00505360, PrerequisiteRadar)    == 0x91C);
GG_STATIC_ASSERT(offsetof(Rules_00505360, PrerequisiteTech)     == 0x938);
GG_STATIC_ASSERT(offsetof(Rules_00505360, At_A34)               == 0xA34);
// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance.
extern Rules_00505360* DAT_008871E0;

// GLOBAL: GAMEMD 0xA83C6C — BuildingTypeClass::Array.Items.
extern BuildingType_00505360** DAT_00A83C6C;

// TechnoTypeClass — the Prerequisite list (Items +0x63C, Count +0x648).
struct TechnoType_00505360
{
    char  _pad000[0x63C];   // +0x0000
    int*  PrerequisiteItems; // +0x063C
    char  _pad640[8];       // +0x0640
    int   PrerequisiteCount; // +0x0648
};
GG_STATIC_ASSERT(offsetof(TechnoType_00505360, PrerequisiteItems) == 0x63C);
GG_STATIC_ASSERT(offsetof(TechnoType_00505360, PrerequisiteCount) == 0x648);

// DynamicVectorClass<BuildingTypeClass*> — only Items is read; the length
// comes in as a separate argument.
struct BuildingVector_00505360
{
    void*                    Vptr;    // +0x0000
    BuildingType_00505360**  Items;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(BuildingVector_00505360, Items) == 0x4);

struct House_00505360
{
    char opaque[4];

    // FUNCTION: GAMEMD 0x505360 — HouseClass::AllPrerequisitesAvailable.
    bool AllPrerequisitesAvailable(TechnoType_00505360* type,
                                   BuildingVector_00505360* owned, int count);
};

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_PREREQUISITES_METHODS_H
