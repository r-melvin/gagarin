// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and vtable slots read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x6FBC90: the techno's
//   slots `[EAX+0x288]` (IsCloakable), `[EDX+0x37C]`, `[EAX+0x380]`,
//   `[EDX+0x1D4]`, `[EAX+0x1D8]` (all no-argument, AL), `[EDX+0x84]`
//   (GetTechnoType) and `[EAX+0x48]` (GetCoords, hidden 12-byte buffer at
//   [ESP+0x14], X / Y divided by 256 into a CellStruct built at [ESP+0xC]
//   and copied to [ESP+0x10]); `byte [ESI+0x3D2]` (Cloakable); `LEA
//   EBX,[ESI+0x150]` (Veterancy, handed in ECX to 0x74FF90 / 0x750010);
//   `[ESI+0x21C]` (Owner) and the owner's `[EAX+0x30]` (pushed to the
//   cell's 0x4870B0); on the type `byte [EDI+0x2A2]` and `byte [EDI+0x2B4]`
//   (the cloak ability at index 6 of the veteran / elite tables); the map
//   object 0x87F7E8 with GetCellAt 0x5657A0. Every offset agrees with the
//   spine match/_layout/techno_class.h (included). Method name from YRpp
//   (ShouldNotBeCloaked).
#ifndef GG_MATCH_COMBAT_TECHNO_CLASS_CLOAK_CHECK_METHODS_H
#define GG_MATCH_COMBAT_TECHNO_CLASS_CLOAK_CHECK_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "../_layout/techno_class.h"   // TechnoClass (Veterancy @0x150, Owner @0x21C, Cloakable @0x3D2)

// The two veterancy gauge tests, reached by a direct CALL with the
// VeterancyStruct in ECX (a single-pointer __fastcall has the same call
// shape as a 0-arg __thiscall).
// FUNCTION: GAMEMD 0x74FF90 (decl; reloc) — gauge is in the veteran band.
bool FUN_0074FF90(VeterancyStruct* vet);
// FUNCTION: GAMEMD 0x750010 (decl; reloc) — gauge is in the elite band.
bool FUN_00750010(VeterancyStruct* vet);

// CellStruct — the user-declared constructor selects the hidden-pointer
// return convention for the inline coordinate-to-cell helper.
struct Cell_006FBC90
{
    short X;   // +0x0000
    short Y;   // +0x0002
    Cell_006FBC90() {}
};
GG_STATIC_ASSERT(sizeof(Cell_006FBC90) == 0x4);

struct Coord_006FBC90
{
    int X;   // +0x0000
    int Y;   // +0x0004
    int Z;   // +0x0008
};
GG_STATIC_ASSERT(sizeof(Coord_006FBC90) == 0xC);

// Coordinate to cell (signed division by 256 per axis), by value.
inline Cell_006FBC90 CoordToCell_006FBC90(const Coord_006FBC90* c)
{
    Cell_006FBC90 r;
    r.X = (short)(c->X / 256);
    r.Y = (short)(c->Y / 256);
    return r;
}

// HouseClass view: only the array index is read.
struct House_006FBC90
{
    char _pad000[0x30];   // +0x0000
    int  ArrayIndex;      // +0x0030
};
GG_STATIC_ASSERT(offsetof(House_006FBC90, ArrayIndex) == 0x30);

struct CellClass_006FBC90
{
    // FUNCTION: GAMEMD 0x4870B0 (decl; reloc) — is this cell under the
    // given house's sensors.
    bool FUN_004870B0(int houseIndex);
};

struct Map_006FBC90
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) — MapClass::GetCellAt.
    CellClass_006FBC90* GetCellAt(const Cell_006FBC90& cell);
};
// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance (an object, not a pointer).
extern Map_006FBC90 DAT_0087F7E8;

// TechnoTypeClass view: only the two per-ability bool tables touched here.
struct TechnoType_006FBC90
{
    char          _pad000[0x29C];         // +0x0000
    unsigned char VeteranAbilities[0x12]; // +0x029C (bool[18]; index 6 = cloak)
    unsigned char EliteAbilities[0x12];   // +0x02AE (bool[18]; index 6 = cloak)
};
GG_STATIC_ASSERT(offsetof(TechnoType_006FBC90, VeteranAbilities) == 0x29C);
GG_STATIC_ASSERT(offsetof(TechnoType_006FBC90, EliteAbilities)   == 0x2AE);
// Index 6 of each table is the byte retail reads: 0x29C + 6 = 0x2A2 and
// 0x2AE + 6 = 0x2B4.

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_006FBC90;

// The spine's TechnoClass is data-only; this view adds the matched method on
// the identical layout. The vptr @0 is reached by a raw cast on `this`.
struct Techno_006FBC90 : TechnoClass
{
    // FUNCTION: GAMEMD 0x6FBC90 — TechnoClass::ShouldNotBeCloaked
    bool ShouldNotBeCloaked();
};
GG_STATIC_ASSERT(offsetof(Techno_006FBC90, Veterancy) == 0x150);
GG_STATIC_ASSERT(offsetof(Techno_006FBC90, Owner)     == 0x21C);
GG_STATIC_ASSERT(offsetof(Techno_006FBC90, Cloakable) == 0x3D2);
GG_STATIC_ASSERT(sizeof(Techno_006FBC90)              == 0x520);

typedef Coord_006FBC90* (IPersistStream::*Fn048_006FBC90)(Coord_006FBC90* out);
typedef TechnoType_006FBC90* (IPersistStream::*Fn084_006FBC90)();
typedef bool (IPersistStream::*FnBool_006FBC90)();

struct Vtbl_006FBC90
{
    char             _pad000[0x48];           // +0x0000
    Fn048_006FBC90   GetCoords;               // +0x0048
    char             _pad04C[0x84 - 0x4C];    // +0x004C
    Fn084_006FBC90   GetTechnoType;           // +0x0084
    char             _pad088[0x1D4 - 0x88];   // +0x0088
    FnBool_006FBC90  At_1D4;                  // +0x01D4
    FnBool_006FBC90  At_1D8;                  // +0x01D8
    char             _pad1DC[0x288 - 0x1DC];  // +0x01DC
    FnBool_006FBC90  IsCloakable;             // +0x0288
    char             _pad28C[0x37C - 0x28C];  // +0x028C
    FnBool_006FBC90  At_37C;                  // +0x037C
    FnBool_006FBC90  At_380;                  // +0x0380
};
GG_STATIC_ASSERT(offsetof(Vtbl_006FBC90, GetCoords)     == 0x48);
GG_STATIC_ASSERT(offsetof(Vtbl_006FBC90, GetTechnoType) == 0x84);
GG_STATIC_ASSERT(offsetof(Vtbl_006FBC90, At_1D4)        == 0x1D4);
GG_STATIC_ASSERT(offsetof(Vtbl_006FBC90, At_1D8)        == 0x1D8);
GG_STATIC_ASSERT(offsetof(Vtbl_006FBC90, IsCloakable)   == 0x288);
GG_STATIC_ASSERT(offsetof(Vtbl_006FBC90, At_37C)        == 0x37C);
GG_STATIC_ASSERT(offsetof(Vtbl_006FBC90, At_380)        == 0x380);

#endif  // GG_MATCH_COMBAT_TECHNO_CLASS_CLOAK_CHECK_METHODS_H
