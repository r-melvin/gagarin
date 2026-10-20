// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and slots read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x4FB6B0. On the house (EDI):
//   `MOV byte [EDI+0x246],1`, `MOV [EDI+0x26C]/[0x270]/[0x274]/[0x278],EAX`,
//   `LEA ECX,[EDI+0x55A0]/[0x55B4]/[0x55C8]/[0x55DC]` feeding CALL 0x49FA00,
//   and `MOV byte [EDI+0x1FC],1`. On the object (EBP): the two virtual calls
//   `CALL [EAX+0x84]` (GetTechnoType) and `CALL [EDX+0x2C]` (WhatAmI), and
//   `ADD EBP,0x9C` with three dword loads — the coordinate triple at +0x9C.
//   On the type (ESI): `CALL [EDX+0x40]` (GetArrayIndex), the byte
//   `MOV AL,[ESI+0xC9F]`, and `MOV ESI,[ESI+0x534]` (the type's own creation
//   sound, -1 when it has none). The rules singleton is the pointer global
//   `MOV ECX,[0x8871E0]` read at +0x178, +0x17C and +0x180. The switch is a
//   jump table: `DEC EAX; CMP EAX,0xE; JA default; MOV CL,[EAX+0x4FB82C];
//   JMP [ECX*4+0x4FB818]`, with the dword table 0x4FB818 = {0x4FB6F5,
//   0x4FB794, 0x4FB768, 0x4FB730, 0x4FB7CA} and the 15-byte index table
//   0x4FB82C = 00 01 04 04 04 02 04 04 04 04 04 04 04 04 03 — i.e. cases 1,
//   2, 6 and 15 with the block bodies laid out in the source order 1, 15, 6,
//   2. Names cross-checked against YRpp HouseClass::RegisterJustBuilt,
//   AbstractType (Unit=1, Aircraft=2, Building=6, Infantry=15), the
//   VocClass::PlayAt declaration in match/combat/capture_manager_free_unit_methods.h
//   and the GetArrayIndex slot in match/ai/ai_trigger_type_house_owns_methods.h,
//   all re-derived here from the disassembly. (YRpp is consult-only, NO LICENSE.)
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_REGISTER_BUILT_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_REGISTER_BUILT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Coord_004FB6B0 { int X; int Y; int Z; };
GG_STATIC_ASSERT(sizeof(Coord_004FB6B0) == 0xC);

// FUNCTION: GAMEMD 0x7509E0 (decl; reloc) — VocClass::PlayAt(index, coords,
// controller). __fastcall: the index in ECX, the coordinate address in EDX.
void* __fastcall VocClass_PlayAt_004FB6B0(int index, const Coord_004FB6B0& coords,
                                          void* controller);

struct RulesClass_004FB6B0
{
    char _pad000[0x178];   // +0x0000
    int  At_178;           // +0x0178  the "new unit ready" voice
    int  At_17C;           // +0x017C  the "new infantry ready" voice
    int  At_180;           // +0x0180  the "new aircraft ready" voice
};
GG_STATIC_ASSERT(offsetof(RulesClass_004FB6B0, At_178) == 0x178);
GG_STATIC_ASSERT(offsetof(RulesClass_004FB6B0, At_17C) == 0x17C);
GG_STATIC_ASSERT(offsetof(RulesClass_004FB6B0, At_180) == 0x180);

// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance (a pointer).
extern RulesClass_004FB6B0* RulesInstance_004FB6B0;

// A per-index tally; the house keeps one per object category.
struct Counter_004FB6B0
{
    char _pad000[0x14];   // +0x0000

    // FUNCTION: GAMEMD 0x49FA00 (decl; reloc) — CounterClass::Increment.
    int Increment(int index);
};
GG_STATIC_ASSERT(sizeof(Counter_004FB6B0) == 0x14);

struct TypeVtbl_004FB6B0;

struct TechnoType_004FB6B0
{
    TypeVtbl_004FB6B0* Vtbl;                      // +0x0000
    char               _pad004[0x534 - 0x4];      // +0x0004
    int                At_534;                    // +0x0534  creation sound
    char               _pad538[0xC9F - 0x538];    // +0x0538
    char               At_C9F;                    // +0x0C9F  suppress the tally
};
GG_STATIC_ASSERT(offsetof(TechnoType_004FB6B0, At_534) == 0x534);
GG_STATIC_ASSERT(offsetof(TechnoType_004FB6B0, At_C9F) == 0xC9F);

typedef int (TechnoType_004FB6B0::*Fn40_004FB6B0)();

struct TypeVtbl_004FB6B0
{
    char           _pad000[0x40];   // +0x0000
    Fn40_004FB6B0  GetArrayIndex;   // +0x0040
};
GG_STATIC_ASSERT(offsetof(TypeVtbl_004FB6B0, GetArrayIndex) == 0x40);

struct ObjVtbl_004FB6B0;

struct Techno_004FB6B0
{
    ObjVtbl_004FB6B0* Vtbl;                    // +0x0000
    char              _pad004[0x9C - 0x4];     // +0x0004
    Coord_004FB6B0    Location;                // +0x009C
};
GG_STATIC_ASSERT(offsetof(Techno_004FB6B0, Location) == 0x9C);

typedef int (Techno_004FB6B0::*Fn2C_004FB6B0)();
typedef TechnoType_004FB6B0* (Techno_004FB6B0::*Fn84_004FB6B0)();

struct ObjVtbl_004FB6B0
{
    char            _pad000[0x2C];             // +0x0000
    Fn2C_004FB6B0   WhatAmI;                   // +0x002C
    char            _pad030[0x84 - 0x30];      // +0x0030
    Fn84_004FB6B0   GetTechnoType;             // +0x0084
};
GG_STATIC_ASSERT(offsetof(ObjVtbl_004FB6B0, WhatAmI)       == 0x2C);
GG_STATIC_ASSERT(offsetof(ObjVtbl_004FB6B0, GetTechnoType) == 0x84);

struct House_004FB6B0
{
    char            _pad0000[0x1FC];              // +0x0000
    char            At_1FC;                       // +0x01FC
    char            _pad1FD[0x246 - 0x1FD];       // +0x01FD
    char            At_246;                       // +0x0246
    char            _pad247[0x26C - 0x247];       // +0x0247
    int             At_26C;                       // +0x026C  last building type
    int             At_270;                       // +0x0270  last infantry type
    int             At_274;                       // +0x0274  last unit type
    int             At_278;                       // +0x0278  last aircraft type
    char            _pad27C[0x55A0 - 0x27C];      // +0x027C
    Counter_004FB6B0 BuildingCounter;             // +0x55A0
    Counter_004FB6B0 UnitCounter;                 // +0x55B4
    Counter_004FB6B0 InfantryCounter;             // +0x55C8
    Counter_004FB6B0 AircraftCounter;             // +0x55DC

    // FUNCTION: GAMEMD 0x4FB6B0 — HouseClass::RegisterJustBuilt.
    void RegisterJustBuilt(Techno_004FB6B0* pTechno);
};
GG_STATIC_ASSERT(offsetof(House_004FB6B0, At_1FC)          == 0x1FC);
GG_STATIC_ASSERT(offsetof(House_004FB6B0, At_246)          == 0x246);
GG_STATIC_ASSERT(offsetof(House_004FB6B0, At_26C)          == 0x26C);
GG_STATIC_ASSERT(offsetof(House_004FB6B0, At_270)          == 0x270);
GG_STATIC_ASSERT(offsetof(House_004FB6B0, At_274)          == 0x274);
GG_STATIC_ASSERT(offsetof(House_004FB6B0, At_278)          == 0x278);
GG_STATIC_ASSERT(offsetof(House_004FB6B0, BuildingCounter) == 0x55A0);
GG_STATIC_ASSERT(offsetof(House_004FB6B0, UnitCounter)     == 0x55B4);
GG_STATIC_ASSERT(offsetof(House_004FB6B0, InfantryCounter) == 0x55C8);
GG_STATIC_ASSERT(offsetof(House_004FB6B0, AircraftCounter) == 0x55DC);

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_REGISTER_BUILT_METHODS_H
