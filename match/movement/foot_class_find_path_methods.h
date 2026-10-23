// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x4CBBA0: the coordinate slot `CALL [EAX+0x4C]` with the
//   out-pointer and a zero pushed, `LEA EAX,[ESI+0x5E0]` (PathDirections in
//   the committed FootClass spine), the __fastcall walker at 0x429780 taking
//   its hidden return pointer in ECX (RET 8), and the AStarClass global
//   `MOV ECX,0x87E8B8` whose FindPath at 0x42C900 takes seven stack args.
//   Method names from YRpp.
#ifndef GG_MATCH_MOVEMENT_FOOT_CLASS_FIND_PATH_METHODS_H
#define GG_MATCH_MOVEMENT_FOOT_CLASS_FIND_PATH_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/foot_class.h"   // FootClass: PathDirections @0x5E0; CoordStruct

// FUNCTION: GAMEMD 0x429780 (decl; reloc) — walk `count` path directions from
// `from` and return the cell reached. __fastcall: hidden return in ECX, `from`
// in EDX, the rest on the stack.
Cell FUN_00429780(Cell* from, int count, int* dirs);

// AStarClass — opaque; only its FindPath is called on the global instance.
struct AStar_004CBBA0
{
    char opaque[4];

    // FUNCTION: GAMEMD 0x42C900 (decl; reloc) — AStarClass::FindPath.
    void* FindPath(Cell* start, Cell* end, FootClass* foot,
                   int* dirs, int maxSteps, int movementZone, int mode);
};
// GLOBAL: GAMEMD 0x87E8B8 — AStarClass::Instance.
extern AStar_004CBBA0 DAT_0087E8B8;

#endif  // GG_MATCH_MOVEMENT_FOOT_CLASS_FIND_PATH_METHODS_H
