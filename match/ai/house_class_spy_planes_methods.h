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
#include "../_layout/house_class.h"
#include "../_layout/aircraft_class.h"
#include "../_layout/aircraft_type_class.h"
#include "../_layout/cell.h"

// A coordinate built as a temporary in the argument list.
struct Coord_0065EAB0 : public CoordStruct
{
    Coord_0065EAB0(int x, int y, int z) { X = x; Y = y; Z = z; }
};

// GLOBAL: GAMEMD 0xA8E7AC — Unsorted::ScenarioInit.
extern int DAT_00A8E7AC;
// GLOBAL: GAMEMD 0xB04C38 — the cell handed to the spawn-edge search twice.
extern CellStruct DAT_00B04C38;

struct MapClass_0065EAB0
{
    char _opaque[4];
    // FUNCTION: GAMEMD 0x4AA440 (decl; reloc) — pick a cell on the given map
    // edge; returns the cell through the hidden out pointer.
    CellStruct* FUN_004AA440(CellStruct* out, int side, CellStruct* a,
                             CellStruct* b, int c, int d, int e);
};
// GLOBAL: GAMEMD 0x87F7E8 — the MapClass instance itself.
extern MapClass_0065EAB0 MapInstance_0065EAB0;

// GLOBAL: GAMEMD 0xA8B21C — the aircraft-type item array.
extern AircraftTypeClass** DAT_00A8B21C;

#endif  // GG_MATCH_AI_HOUSE_CLASS_SPY_PLANES_METHODS_H
