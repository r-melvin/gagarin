// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly), cross-checked against YRpp
//   (every offset reconfirmed
//   numerically from the disasm below).
//
// BuildingTypeClass — the type/template descriptor for a building. Only the
// members the four matched methods touch are modelled here; the rest of the
// (very large) TechnoTypeClass-derived layout is P2. Every modelled offset is
// proven by a member-access instruction at the cited retail address.
#ifndef GG_MATCH_ECONOMY_BUILDING_TYPE_CLASS_H
#define GG_MATCH_ECONOMY_BUILDING_TYPE_CLASS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

class UnitTypeClass;  // BuildingTypeClass::UndeploysInto target
struct SHPStruct;      // BuildingTypeClass::Buildup image

// ---------------------------------------------------------------------------
// BuildingTypeClass — partial, offset-pinned model.
//
// Confirmed member offsets (from the disasm of the four methods below):
//   +0x408  UndeploysInto  UnitTypeClass*  (MOV EAX,[ECX+0x408] @0x465D40 IsVehicle)
//   +0xE00  Buildup        SHPStruct*      (MOV EAX,[ESI+0xE00]  @0x465AF0 ClearBuildUp)
//   +0xE04  BuildupLoaded  bool            (MOV byte[ESI+0xE04],0 @0x465B1A)
//   +0xEF0  Foundation     int  (enum)     (MOV EAX,[ECX+0xEF0] @0x45EC90 / @0x45ECA0 / @0x465D40)
//   +0x1570 Bib            bool            (MOV AL,[ECX+0x1570] @0x45ECA8 GetFoundationHeight)
//   +0x1762 FreeBuildup    bool            (MOV AL,[ESI+0x1762] @0x465AF3 ClearBuildUp)
// ---------------------------------------------------------------------------
class BuildingTypeClass
{
public:
    void           ClearBuildUp();                       // GAMEMD 0x465AF0 __thiscall
    bool           IsVehicle() const;                    // GAMEMD 0x465D40 __thiscall
    // YRpp declares these `short`; retail codegen loads the full dword and
    // returns it in EAX with no truncation (the caller narrows to AX), i.e.
    // the byte-exact return type is `int`. The bytes are the oracle.
    int            GetFoundationWidth() const;           // GAMEMD 0x45EC90 __thiscall
    int            GetFoundationHeight(bool bIncludeBib) const; // GAMEMD 0x45ECA0 __thiscall

    char           unknown_0x000[0x408];                 // +0x000
    UnitTypeClass* UndeploysInto;                        // +0x408
    char           unknown_0x40C[0xE00 - 0x40C];         // +0x40C
    SHPStruct*     Buildup;                              // +0xE00
    bool           BuildupLoaded;                         // +0xE04
    char           unknown_0xE05[0xEF0 - 0xE05];         // +0xE05
    int            Foundation;                           // +0xEF0
    char           unknown_0xEF4[0x1570 - 0xEF4];        // +0xEF4
    bool           Bib;                                  // +0x1570
    char           unknown_0x1571[0x1762 - 0x1571];      // +0x1571
    bool           FreeBuildup;                          // +0x1762
};

GG_STATIC_ASSERT(offsetof(BuildingTypeClass, Foundation)    == 0xEF0);   // pointer-free
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, BuildupLoaded) == 0xE04);   // pointer-free
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, Bib)           == 0x1570);  // pointer-free
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, FreeBuildup)   == 0x1762);  // pointer-free
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, UndeploysInto) == 0x408);   // pointer-width-sensitive
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, Buildup)       == 0xE00);
#endif

#endif  // GG_MATCH_ECONOMY_BUILDING_TYPE_CLASS_H
