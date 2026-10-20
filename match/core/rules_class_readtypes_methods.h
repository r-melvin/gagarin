// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Behaviour + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly @ 0x672280 / 0x672360 /
//   0x6723D0), cross-checked against YRpp RulesClass.h (consult-only, no LICENSE;
//   every address + calling convention reconfirmed below from the disasm).
//
// RulesClass::Read_{Infantry,Vehicle,Aircraft}Types — the P4 INI list parsers.
// Each enumerates every key of its [*Types] INI section and, for each non-empty
// value, FindOrAllocate()s the matching *TypeClass. NONE of the three touches a
// RulesClass member (the incoming `this`/ECX is ignored), so no class layout or
// offset is modelled here: only the calling conventions of the forwarded INI
// helpers + the per-type FindOrAllocate callees matter for a byte match.
#ifndef GG_MATCH_CORE_RULES_CLASS_READTYPES_METHODS_H
#define GG_MATCH_CORE_RULES_CLASS_READTYPES_METHODS_H

// ---------------------------------------------------------------------------
// Opaque INI parser model. We never read a member of it; the three methods are
// declared (no body) so cl emits __thiscall `call rel32`s that the differ
// reloc-normalises against retail.
//   GetKeyCount @0x526960  __thiscall(const char* section)               -> int
//   GetKeyName  @0x526CC0  __thiscall(const char* section, int index)    -> char*
//   ReadString  @0x528A10  __thiscall(sec, key, def, char* buf, int len) -> int
// ---------------------------------------------------------------------------
class CCINIClass
{
public:
    int         GetKeyCount(const char* pSection);
    const char* GetKeyName(const char* pSection, int index);
    int         ReadString(const char* pSection, const char* pKey,
                           const char* pDefault, char* pBuffer, int size);
};

// ---------------------------------------------------------------------------
// Per-type allocator callees (declared only; relocation-normalised). Each takes
// the freshly-read key value in ECX (retail compiles these as a single-pointer
// __fastcall: `lea ecx,[buffer]; call rel32`).
//   InfantryTypeClass::FindOrAllocate @0x524CB0  (called by Read_InfantryTypes)
//   UnitTypeClass::FindOrAllocate     @0x7480D0  (called by Read_VehicleTypes)
//   AircraftTypeClass::FindOrAllocate @0x41CEF0  (called by Read_AircraftTypes)
// CORRECTION (2026-08-07): the last two addresses were previously listed as
// 0x512680 and 0x7480D0. Re-reading the CALL targets in all three parsers shows
// Read_VehicleTypes goes to 0x7480D0 and Read_AircraftTypes to 0x41CEF0, while
// 0x512680 is HouseTypeClass::FindOrAllocate — the callee of Read_Countries
// (see rules_class_readtypes_more_methods.h). The comment was wrong, not the
// code: the differ reloc-normalises direct calls, so each parser still matched
// 100% against the right symbol name. Corrected here so the addresses stay
// usable as repo facts.
// ---------------------------------------------------------------------------
int __fastcall InfantryType_FindOrAllocate(const char* pID);
int __fastcall UnitType_FindOrAllocate(const char* pID);
int __fastcall AircraftType_FindOrAllocate(const char* pID);

// RulesClass: only the three list-parsers are modelled; `this` is unused so no
// members/base are needed for a byte-exact match.
struct RulesClass
{
    // FUNCTION: GAMEMD 0x672280  RulesClass::Read_InfantryTypes  (__thiscall)
    bool Read_InfantryTypes(CCINIClass* pINI);
    // FUNCTION: GAMEMD 0x672360  RulesClass::Read_VehicleTypes   (__thiscall)
    bool Read_VehicleTypes(CCINIClass* pINI);
    // FUNCTION: GAMEMD 0x6723D0  RulesClass::Read_AircraftTypes  (__thiscall)
    bool Read_AircraftTypes(CCINIClass* pINI);
};

#endif  // GG_MATCH_CORE_RULES_CLASS_READTYPES_METHODS_H
