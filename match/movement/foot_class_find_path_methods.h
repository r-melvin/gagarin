// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x4CBBA0: the coordinate slot `CALL [EAX+0x4C]` with the
//   out-pointer and a zero pushed, `LEA EAX,[ESI+0x5E0]` (PathDirections in
//   the committed FootClass spine), the __fastcall walker at 0x429780 taking
//   its hidden return pointer in ECX (RET 8), and the AStarClass global
//   `MOV ECX,0x87E8B8` whose FindPath at 0x42C900 takes seven stack args.
//   Method names from YRpp FootClass.h / AStarClass.h (consult-only).
#ifndef GG_MATCH_MOVEMENT_FOOT_CLASS_FIND_PATH_METHODS_H
#define GG_MATCH_MOVEMENT_FOOT_CLASS_FIND_PATH_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "../_layout/foot_class.h"   // FootClass: PathDirections @0x5E0; CoordStruct

// A 2D cell coordinate with a user-declared constructor: that is what makes
// VC6 return it through a hidden pointer (a POD of this size would come back in
// EAX), which is how retail's walker at 0x429780 hands it back.
struct Cell_004CBBA0
{
    short X;   // +0x00
    short Y;   // +0x02
    Cell_004CBBA0() {}
};
GG_STATIC_ASSERT(sizeof(Cell_004CBBA0) == 4);

// FUNCTION: GAMEMD 0x429780 (decl; reloc) — walk `count` path directions from
// `from` and return the cell reached. __fastcall: hidden return in ECX, `from`
// in EDX, the rest on the stack.
Cell_004CBBA0 __fastcall FUN_00429780(Cell_004CBBA0* from, int count, int* dirs);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct PathVtbl;

// No-data host over the committed FootClass spine; layout identical.
struct FootPath : FootClass
{
    // FUNCTION: GAMEMD 0x4CBBA0
    void* FindPath(Cell_004CBBA0* dest, int* buffer, int unused1, int unused2,
                   int dirCount, int mode);
};

typedef CoordStruct* (IPersistStream::*Fn04C_Path)(CoordStruct* out, int ctx);

struct PathVtbl
{
    char       _pad000[0x4C];    // +0x0000
    Fn04C_Path GetCoords;        // +0x004C
};
GG_STATIC_ASSERT(offsetof(PathVtbl, GetCoords) == 0x4C);

// AStarClass — opaque; only its FindPath is called on the global instance.
struct AStar_004CBBA0
{
    char opaque[4];

    // FUNCTION: GAMEMD 0x42C900 (decl; reloc) — AStarClass::FindPath.
    void* FindPath(Cell_004CBBA0* start, Cell_004CBBA0* end, FootPath* foot,
                   int* dirs, int maxSteps, int movementZone, int mode);
};
// GLOBAL: GAMEMD 0x87E8B8 — AStarClass::Instance.
extern AStar_004CBBA0 DAT_0087E8B8;

#endif  // GG_MATCH_MOVEMENT_FOOT_CLASS_FIND_PATH_METHODS_H
