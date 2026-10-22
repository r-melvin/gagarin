// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and slots read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x4FF550. On the object (ESI):
//   `MOV byte [ESI+0x3CC],0`, `MOV AL,byte [ESI+0x438]` /
//   `MOV byte [ESI+0x438],0`, `MOV EAX,[ESI+0x520]` then `MOV EAX,[EAX+0x408]`
//   and `MOV CL,byte [EAX+0x5EC]`, plus the virtual calls `CALL [EAX+0x84]`
//   (GetTechnoType), `CALL [EAX+0x2C]` (WhatAmI) and `CALL [EDX+0x80]`.
//   On the type (EAX from slot 0x84): `MOV CL,byte [EAX+0x232]`,
//   `MOV CL,byte [EAX+0xC9F]`, `MOV CL,byte [EAX+0xCCE]`,
//   `MOV ECX,[EAX+0x5E0]`, and `CALL [EDX+0x40]` (GetArrayIndex).
//   On the house (EDI): `DEC dword [EDI+0x2E8]` / `[0x2EC]` / `[0x2F0]`,
//   `MOV EAX,[EDI+0x2F4]; DEC; MOV [EDI+0x2F4],EAX`, the same read-dec-store
//   on `[EDI+0x2F8]`, and `LEA ECX,[EDI+0x5500]/[0x5514]/[0x5528]/[0x553C]`
//   feeding CALL 0x49FA70. The switch is a jump table:
//   `DEC EAX; CMP EAX,0xE; JA default; XOR ECX,ECX; MOV CL,[EAX+0x4FF6E8];
//   JMP [ECX*4+0x4FF6D4]`, with the dword table 0x4FF6D4 = {0x4FF676,
//   0x4FF607, 0x4FF5AF, 0x4FF636, 0x4FF6CE} and the 15-byte index table
//   0x4FF6E8 = 00 01 04 04 04 02 04 04 04 04 04 04 04 04 03 — i.e. cases 1,
//   2, 6 and 15, with the block bodies laid out ascending 6, 2, 15, 1, which
//   is therefore the source order. Names cross-checked against YRpp
//   HouseClass::RemoveTracking, AbstractType (Unit=1, Aircraft=2,
//   Building=6, Infantry=15) and the GetArrayIndex slot already confirmed in
//   match/economy/house_class_register_built_methods.h, all re-derived here
//   from the disassembly.
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_REMOVE_TRACKING_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_REMOVE_TRACKING_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// A per-index tally; the house keeps one per object category. Same 0x14-byte
// CounterClass as match/economy/house_class_register_built_methods.h, but this
// function calls the decrement entry rather than the increment one.
struct Counter_004FF550
{
    char _pad000[0x14];   // +0x0000

    // FUNCTION: GAMEMD 0x49FA70 (decl; reloc) — CounterClass::Decrement.
    int Decrement(int index);
};
GG_STATIC_ASSERT(sizeof(Counter_004FF550) == 0x14);

struct TypeVtbl_004FF550;

struct TechnoType_004FF550
{
    TypeVtbl_004FF550* Vtbl;                      // +0x0000
    char               _pad004[0x232 - 0x4];      // +0x0004
    bool               At_232;                    // +0x0232  never tracked
    char               _pad233[0x5E0 - 0x233];    // +0x0233
    int                At_5E0;                    // +0x05E0
    char               _pad5E4[0xC9F - 0x5E4];    // +0x05E4
    bool               At_C9F;                    // +0x0C9F  suppress the tally
    char               _pad_CA0[0xCCE - 0xCA0];   // +0x0CA0
    bool               At_CCE;                    // +0x0CCE
};
GG_STATIC_ASSERT(offsetof(TechnoType_004FF550, At_232) == 0x232);
GG_STATIC_ASSERT(offsetof(TechnoType_004FF550, At_5E0) == 0x5E0);
GG_STATIC_ASSERT(offsetof(TechnoType_004FF550, At_C9F) == 0xC9F);
GG_STATIC_ASSERT(offsetof(TechnoType_004FF550, At_CCE) == 0xCCE);

typedef int (TechnoType_004FF550::*Fn40_004FF550)();

struct TypeVtbl_004FF550
{
    char           _pad000[0x40];   // +0x0000
    Fn40_004FF550  GetArrayIndex;   // +0x0040
};
GG_STATIC_ASSERT(offsetof(TypeVtbl_004FF550, GetArrayIndex) == 0x40);

// The object reached from the building through +0x520 then +0x408; only its
// byte at +0x5EC is read here.
struct Obj_004FF550_5EC
{
    char _pad000[0x5EC];   // +0x0000
    bool At_5EC;           // +0x05EC
};
GG_STATIC_ASSERT(offsetof(Obj_004FF550_5EC, At_5EC) == 0x5EC);

struct Obj_004FF550_408
{
    char              _pad000[0x408];   // +0x0000
    Obj_004FF550_5EC* At_408;           // +0x0408
};
GG_STATIC_ASSERT(offsetof(Obj_004FF550_408, At_408) == 0x408);

struct ObjVtbl_004FF550;

struct Techno_004FF550
{
    ObjVtbl_004FF550* Vtbl;                       // +0x0000
    char              _pad004[0x3CC - 0x4];       // +0x0004
    bool              At_3CC;                     // +0x03CC  "is tracked"
    char              _pad3CD[0x438 - 0x3CD];     // +0x03CD
    bool              At_438;                     // +0x0438  counted as active
    char              _pad439[0x520 - 0x439];     // +0x0439
    Obj_004FF550_408* At_520;                     // +0x0520
};
GG_STATIC_ASSERT(offsetof(Techno_004FF550, At_3CC) == 0x3CC);
GG_STATIC_ASSERT(offsetof(Techno_004FF550, At_438) == 0x438);
GG_STATIC_ASSERT(offsetof(Techno_004FF550, At_520) == 0x520);

typedef int  (Techno_004FF550::*Fn2C_004FF550)();
typedef bool (Techno_004FF550::*Fn80_004FF550)();
typedef TechnoType_004FF550* (Techno_004FF550::*Fn84_004FF550)();

struct ObjVtbl_004FF550
{
    char            _pad000[0x2C];             // +0x0000
    Fn2C_004FF550   WhatAmI;                   // +0x002C
    char            _pad030[0x80 - 0x30];      // +0x0030
    Fn80_004FF550   At_80;                     // +0x0080
    Fn84_004FF550   GetTechnoType;             // +0x0084
};
GG_STATIC_ASSERT(offsetof(ObjVtbl_004FF550, WhatAmI)       == 0x2C);
GG_STATIC_ASSERT(offsetof(ObjVtbl_004FF550, At_80)         == 0x80);
GG_STATIC_ASSERT(offsetof(ObjVtbl_004FF550, GetTechnoType) == 0x84);

struct House_004FF550
{
    char             _pad0000[0x2E8];              // +0x0000
    int              At_2E8;                       // +0x02E8  units owned
    int              At_2EC;                       // +0x02EC
    int              At_2F0;                       // +0x02F0
    int              At_2F4;                       // +0x02F4  infantry owned
    int              At_2F8;                       // +0x02F8  aircraft owned
    char             _pad2FC[0x5500 - 0x2FC];      // +0x02FC
    Counter_004FF550 BuildingCounter;              // +0x5500
    Counter_004FF550 UnitCounter;                  // +0x5514
    Counter_004FF550 InfantryCounter;              // +0x5528
    Counter_004FF550 AircraftCounter;              // +0x553C

    // FUNCTION: GAMEMD 0x4FF550 — HouseClass::RemoveTracking.
    void RemoveTracking(Techno_004FF550* pTechno);
};
GG_STATIC_ASSERT(offsetof(House_004FF550, At_2E8)          == 0x2E8);
GG_STATIC_ASSERT(offsetof(House_004FF550, At_2EC)          == 0x2EC);
GG_STATIC_ASSERT(offsetof(House_004FF550, At_2F0)          == 0x2F0);
GG_STATIC_ASSERT(offsetof(House_004FF550, At_2F4)          == 0x2F4);
GG_STATIC_ASSERT(offsetof(House_004FF550, At_2F8)          == 0x2F8);
GG_STATIC_ASSERT(offsetof(House_004FF550, BuildingCounter) == 0x5500);
GG_STATIC_ASSERT(offsetof(House_004FF550, UnitCounter)     == 0x5514);
GG_STATIC_ASSERT(offsetof(House_004FF550, InfantryCounter) == 0x5528);
GG_STATIC_ASSERT(offsetof(House_004FF550, AircraftCounter) == 0x553C);

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_REMOVE_TRACKING_METHODS_H
