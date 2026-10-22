// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and slots read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x50D170: the team vector at 0x8B40E8
//   through its Items `[0x8B40EC]` and Count `[0x8B40F8]`, the team's owner
//   `CMP [ECX+0x2C],EDI` against `this`, CALL 0x645BB0 with the type in ECX
//   (a __fastcall taking the target type, no receiver), CALL 0x6EC3D0 with
//   the team in ECX (a receiver-only member), the vtable slots
//   `CALL [EDI+0x48]` (GetCoords, one out pointer, returned in EAX) and
//   `CALL [EDI+0x3C4]` (GreatestThreat: threat, coord pointer, 1), the
//   signed divide by 256 (`CDQ; AND EDX,0xFF; ADD; SAR 8`) into two words
//   at the parameter's home slot, and the 4-byte sentinel at 0xA8EF98 copied
//   through the hidden result pointer (RET 8: hidden pointer + type). The
//   vector at 0x8B40E8 is TeamClass::Array and +0x2C its Owner per YRpp
//   (names only, offsets reconfirmed here); the
//   method name is YRpp's HouseClass::PickTargetByType.
#ifndef GG_MATCH_AI_HOUSE_CLASS_PICK_TARGET_METHODS_H
#define GG_MATCH_AI_HOUSE_CLASS_PICK_TARGET_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// CellStruct. The user-declared constructor selects the hidden-pointer
// return convention retail uses for this 4-byte struct.
struct Cell_0050D170
{
    short X;   // +0x0000
    short Y;   // +0x0002

    Cell_0050D170() {}
};
GG_STATIC_ASSERT(sizeof(Cell_0050D170) == 4);

struct Coord_0050D170
{
    int X;     // +0x0000
    int Y;     // +0x0004
    int Z;     // +0x0008
};
GG_STATIC_ASSERT(sizeof(Coord_0050D170) == 0xC);

// GLOBAL: GAMEMD 0xA8EF98 — the "no cell" CellStruct sentinel.
extern Cell_0050D170 DAT_00A8EF98;

// FUNCTION: GAMEMD 0x645BB0 (decl; reloc) — maps a target-type index to the
// ThreatType mask used by GreatestThreat (a switch on 2..11).
int FUN_00645BB0(int targetType);

struct House_0050D170;

// Declaration order matters — see match/_rt/gg_vslot.h. The class must be
// complete before the member-function-pointer types.
struct Vtbl_0050D170;

// Any AbstractClass-derived object: the team member the threat search is run
// on and the target it finds both only need GetCoords and GreatestThreat.
struct Obj_0050D170
{
    Vtbl_0050D170* Vtbl;      // +0x0000
};

typedef Coord_0050D170* (Obj_0050D170::*Fn48_0050D170)(Coord_0050D170* out);
typedef Obj_0050D170*   (Obj_0050D170::*Fn3C4_0050D170)(int threat,
                                                        Coord_0050D170* coord,
                                                        int onlyTargetHouseEnemy);

struct Vtbl_0050D170
{
    char            _pad000[0x48];            // +0x0000
    Fn48_0050D170   GetCoords;                // +0x0048
    char            _pad04C[0x3C4 - 0x4C];    // +0x004C
    Fn3C4_0050D170  GreatestThreat;           // +0x03C4
};
GG_STATIC_ASSERT(offsetof(Vtbl_0050D170, GetCoords)      == 0x48);
GG_STATIC_ASSERT(offsetof(Vtbl_0050D170, GreatestThreat) == 0x3C4);

struct Team_0050D170
{
    char             _pad000[0x2C];   // +0x0000
    House_0050D170*  Owner;           // +0x002C

    // FUNCTION: GAMEMD 0x6EC3D0 (decl; reloc) — picks the team member to run
    // the threat search on (walks the member chain from +0x54).
    Obj_0050D170* FUN_006EC3D0();
};
GG_STATIC_ASSERT(offsetof(Team_0050D170, Owner) == 0x2C);

// DynamicVectorClass<TeamClass*> — TeamClass::Array at 0x8B40E8.
struct TeamVector_0050D170
{
    void*            _vtable;            // +0x0000
    Team_0050D170**  Items;              // +0x0004
    int              Capacity;           // +0x0008
    bool             IsInitialized;      // +0x000C
    bool             IsAllocated;        // +0x000D
    int              Count;              // +0x0010
    int              CapacityIncrement;  // +0x0014

    Team_0050D170*& operator[](int i) { return this->Items[i]; }
};
GG_STATIC_ASSERT(offsetof(TeamVector_0050D170, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(TeamVector_0050D170, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(TeamVector_0050D170) == 0x18);

// GLOBAL: GAMEMD 0x8B40E8 — TeamClass::Array.
extern TeamVector_0050D170 DAT_008B40E8;

struct House_0050D170
{
    // FUNCTION: GAMEMD 0x50D170 — HouseClass::PickTargetByType.
    Cell_0050D170 PickTargetByType(int targetType);
};

#endif  // GG_MATCH_AI_HOUSE_CLASS_PICK_TARGET_METHODS_H
