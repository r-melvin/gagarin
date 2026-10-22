// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, slots and conventions read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x65EAB0. Convention:
//   `MOV EBP,ECX` and `MOV ECX,[EAX+EDX*4]` with `RET 0x10` — a __fastcall
//   taking the house in ECX, an aircraft-type index in EDX and four stack
//   arguments, read back as `[ESP+0x1C]`..`[ESP+0x28]` relative to the
//   0x18-byte frame. Globals: the aircraft-type item array 0xA8B21C (indexed
//   `[EAX+EDX*4]`, the same array as match/core/find_by_name_methods.h),
//   Unsorted::ScenarioInit 0xA8E7AC (read/INC/store around each creating
//   call and read/DEC/store after it, as in
//   match/economy/factory_class_abandon_methods.cpp), MapClass::Instance as
//   the immediate 0x87F7E8, and the cell global 0xB04C38 pushed twice into
//   0x4AA440. On the house (EBP): `MOV EAX,[EBP+0x1E0]` bounds-checked
//   against 0 and 3 before falling back to the __fastcall 0x50DA80. On the
//   created object (ESI): `MOV byte [ESI+0x3D4],1` and the vtable slots
//   `CALL [EDX+0x1E8]` (two pushed arguments), `CALL [EDX+0x480]` (two),
//   `CALL [EDX+0x3C8]` (one), `CALL [EDX+0xD8]` (the coordinate address and
//   0, result masked with `AND EAX,0xFF`), `CALL [EDX+0x1EC]` (none) and
//   `CALL [EAX+0x20]` with `PUSH 1` — the scalar deleting destructor, which
//   on this hierarchy sits at slot 8, so it is spelled as an explicit
//   null-guarded slot call. On the type (ECX from the array):
//   `CALL [EDX+0x8C]` with the house pushed. The cell coordinates are
//   `MOVSX EAX,DI` and `MOVSX ECX,word [ESP+0x3A]` — one half out of the
//   register and the other out of the whole-dword spill, scaled
//   `SHL 8; ADD 0x80` into a three-dword CoordStruct whose Z is stored 0.
//   Names cross-checked against YRpp HouseClass / AircraftTypeClass.
#ifndef GG_MATCH_AI_HOUSE_CLASS_SPY_PLANES_METHODS_H
#define GG_MATCH_AI_HOUSE_CLASS_SPY_PLANES_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Cell_0065EAB0 { short X; short Y; };
GG_STATIC_ASSERT(sizeof(Cell_0065EAB0) == 4);

struct Coord_0065EAB0
{
    int X;
    int Y;
    int Z;
    Coord_0065EAB0(int x, int y, int z) : X(x), Y(y), Z(z) {}
};
GG_STATIC_ASSERT(sizeof(Coord_0065EAB0) == 0xC);

// GLOBAL: GAMEMD 0xA8E7AC — Unsorted::ScenarioInit.
extern int DAT_00A8E7AC;
// GLOBAL: GAMEMD 0xB04C38 — the cell handed to the spawn-edge search twice.
extern Cell_0065EAB0 DAT_00B04C38;

struct House_0065EAB0;

// FUNCTION: GAMEMD 0x50DA80 (decl; reloc) — the house's fallback map side.
int __fastcall FUN_0050DA80(House_0065EAB0* house);

struct MapClass_0065EAB0
{
    char _opaque[4];
    // FUNCTION: GAMEMD 0x4AA440 (decl; reloc) — pick a cell on the given map
    // edge; returns the cell through the hidden out pointer.
    Cell_0065EAB0* FUN_004AA440(Cell_0065EAB0* out, int side, Cell_0065EAB0* a,
                                Cell_0065EAB0* b, int c, int d, int e);
};
// GLOBAL: GAMEMD 0x87F7E8 — the MapClass instance itself.
extern MapClass_0065EAB0 MapInstance_0065EAB0;

struct PlaneVtbl_0065EAB0;

struct Techno_0065EAB0
{
    PlaneVtbl_0065EAB0* Vtbl;                  // +0x0000
    char                _pad004[0x3D4 - 0x4];  // +0x0004
    char                At_3D4;                // +0x03D4
};
GG_STATIC_ASSERT(offsetof(Techno_0065EAB0, At_3D4) == 0x3D4);

typedef void (Techno_0065EAB0::*Fn20_0065EAB0)(int flag);
typedef bool (Techno_0065EAB0::*FnD8_0065EAB0)(const Coord_0065EAB0& coord, int dir);
typedef void (Techno_0065EAB0::*Fn1E8_0065EAB0)(int a, int b);
typedef void (Techno_0065EAB0::*Fn1EC_0065EAB0)();
typedef void (Techno_0065EAB0::*Fn3C8_0065EAB0)(int a);
typedef void (Techno_0065EAB0::*Fn480_0065EAB0)(void* a, int b);

struct PlaneVtbl_0065EAB0
{
    char            _pad000[0x20];                // +0x0000
    Fn20_0065EAB0   ScalarDeletingDtor;           // +0x0020
    char            _pad024[0xD8 - 0x24];         // +0x0024
    FnD8_0065EAB0   Unlimbo;                      // +0x00D8
    char            _pad0DC[0x1E8 - 0xDC];        // +0x00DC
    Fn1E8_0065EAB0  At_1E8;                       // +0x01E8
    Fn1EC_0065EAB0  At_1EC;                       // +0x01EC
    char            _pad1F0[0x3C8 - 0x1F0];       // +0x01F0
    Fn3C8_0065EAB0  At_3C8;                       // +0x03C8
    char            _pad3CC[0x480 - 0x3CC];       // +0x03CC
    Fn480_0065EAB0  At_480;                       // +0x0480
};
GG_STATIC_ASSERT(offsetof(PlaneVtbl_0065EAB0, ScalarDeletingDtor) == 0x20);
GG_STATIC_ASSERT(offsetof(PlaneVtbl_0065EAB0, Unlimbo)            == 0xD8);
GG_STATIC_ASSERT(offsetof(PlaneVtbl_0065EAB0, At_1E8)             == 0x1E8);
GG_STATIC_ASSERT(offsetof(PlaneVtbl_0065EAB0, At_1EC)             == 0x1EC);
GG_STATIC_ASSERT(offsetof(PlaneVtbl_0065EAB0, At_3C8)             == 0x3C8);
GG_STATIC_ASSERT(offsetof(PlaneVtbl_0065EAB0, At_480)             == 0x480);

struct TypeVtbl_0065EAB0;

struct AircraftType_0065EAB0
{
    TypeVtbl_0065EAB0* Vtbl;   // +0x0000
};
typedef Techno_0065EAB0* (AircraftType_0065EAB0::*Fn8C_0065EAB0)(House_0065EAB0* owner);

struct TypeVtbl_0065EAB0
{
    char           _pad000[0x8C];   // +0x0000
    Fn8C_0065EAB0  CreateObject;    // +0x008C
};
GG_STATIC_ASSERT(offsetof(TypeVtbl_0065EAB0, CreateObject) == 0x8C);

// GLOBAL: GAMEMD 0xA8B21C — the aircraft-type item array.
extern AircraftType_0065EAB0** DAT_00A8B21C;

struct House_0065EAB0
{
    char _pad0000[0x1E0];   // +0x0000
    int  At_1E0;            // +0x01E0  the house's map side

    // FUNCTION: GAMEMD 0x65EAB0 — HouseClass::SendSpyPlanes. A member, not a
    // free function: the house arrives in ECX and the aircraft-type index in
    // EDX, which is `__fastcall` on a member (this in ECX, the first explicit
    // argument in EDX, the remaining four on the stack and `RET 0x10`). A
    // plain __thiscall member would push the index too and return `RET 0x14`,
    // so the convention is kept.
    int __fastcall SendSpyPlanes(int typeIndex, int count, int a2, int a3,
                                 void* a4);
};
GG_STATIC_ASSERT(offsetof(House_0065EAB0, At_1E0) == 0x1E0);

#endif  // GG_MATCH_AI_HOUSE_CLASS_SPY_PLANES_METHODS_H
