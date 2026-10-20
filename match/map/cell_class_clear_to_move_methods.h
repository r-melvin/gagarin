// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4834A0: `LEA EAX,[ESI+0x24]` (MapCoords, pushed to
//   0x56D230), `MOVSX ECX,byte [ESI+0x11B]` (the signed cell level),
//   `MOV EAX,[ESI+0x44]` (the overlay-type index) indexing the array pointer
//   at 0xA83D84 and the type byte `[ESI+0x2A8]` plus `[ESI+0x22D]`,
//   `MOV AL,byte [ESI+0x124]` and `[ESI+0x128]` (the ground and bridge
//   occupation bytes), `TEST dword [ESI+0x140],EDX` with EDX = 0x100 (the
//   bridge flag), and `MOV EAX,[ESI+0xEC]` (LandType). The cost table is
//   `FLD float [EAX*4+0x89EA40]` with the index folded as
//   `LEA EDX,[EDX+EAX*8]; ADD EAX,EDX` = speed + landType*9, so each entry is
//   eight floats plus one dword — the same table whose Buildable column is
//   read at 0x89EA60 in match/map/cell_class_tiberium_germinate_methods.h.
//   The comparison constant is the float at 0x7E1748 (0.0f), compared
//   `FCOMP float ptr` / `TEST AH,0x40`. Offsets 0x44, 0x11B, 0x140 and 0xEC
//   agree with match/map/cell_class_methods.h, cell_class_fog_methods.h,
//   cell_class_shroud_methods.h and cell_class_tiberium_germinate_methods.h.
//   The parameter list and its names are YRpp's CellClass::IsClearToMove
//   (consult-only, NO LICENSE), re-derived here from the 0x1C-byte `RET`.
#ifndef GG_MATCH_MAP_CELL_CLASS_CLEAR_TO_MOVE_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_CLEAR_TO_MOVE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Cell_004834A0 { short X; short Y; };
GG_STATIC_ASSERT(sizeof(Cell_004834A0) == 4);

struct Map_004834A0
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x56D230 (decl; reloc) — MapClass::GetMovementZoneType.
    int GetMovementZoneType(const Cell_004834A0& cell, int movementZone, bool isBridge);
};
// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance (an object, not a pointer).
extern Map_004834A0 DAT_0087F7E8;

struct OverlayType_004834A0
{
    char _pad000[0x22D];      // +0x0000
    char At_22D;              // +0x022D
    char _pad22E[0x2A8 - 0x22E]; // +0x022E
    char Wall;                // +0x02A8
};
GG_STATIC_ASSERT(offsetof(OverlayType_004834A0, At_22D) == 0x22D);
GG_STATIC_ASSERT(offsetof(OverlayType_004834A0, Wall)   == 0x2A8);

// GLOBAL: GAMEMD 0xA83D84 — OverlayTypeClass::Array.Items.
extern OverlayType_004834A0** DAT_00A83D84;

// One row of the terrain table: the per-speed-type movement cost plus the
// buildable flag.
struct Ground_004834A0
{
    float Cost[8];       // +0x0000
    int   Buildable;     // +0x0020
};
GG_STATIC_ASSERT(sizeof(Ground_004834A0) == 0x24);

// GLOBAL: GAMEMD 0x89EA40 — RulesClass::Instance.Grounds (the terrain table).
extern Ground_004834A0 Grounds_004834A0[];
// GLOBAL: GAMEMD 0x7E1748 — the 0.0f the movement cost is compared against.
extern const float DAT_007E1748;

struct Cell_Class_004834A0
{
    char           _pad0000[0x24];              // +0x0000
    Cell_004834A0  MapCoords;                   // +0x0024
    char           _pad0028[0x44 - 0x28];       // +0x0028
    int            OverlayTypeIndex;            // +0x0044
    char           _pad0048[0xEC - 0x48];       // +0x0048
    int            LandType;                    // +0x00EC
    char           _pad00F0[0x11B - 0xF0];      // +0x00F0
    char           Level;                       // +0x011B
    char           _pad011C[0x124 - 0x11C];     // +0x011C
    unsigned char  OccupationFlags;             // +0x0124
    char           _pad0125[0x128 - 0x125];     // +0x0125
    unsigned char  AltOccupationFlags;          // +0x0128
    char           _pad0129[0x140 - 0x129];     // +0x0129
    int            Flags;                       // +0x0140

    // FUNCTION: GAMEMD 0x4834A0 — CellClass::IsClearToMove.
    bool IsClearToMove(int speedType, bool ignoreInfantry, bool ignoreVehicles,
                       int zone, int movementZone, int level, bool isBridge);
};
GG_STATIC_ASSERT(offsetof(Cell_Class_004834A0, MapCoords)          == 0x24);
GG_STATIC_ASSERT(offsetof(Cell_Class_004834A0, OverlayTypeIndex)   == 0x44);
GG_STATIC_ASSERT(offsetof(Cell_Class_004834A0, LandType)           == 0xEC);
GG_STATIC_ASSERT(offsetof(Cell_Class_004834A0, Level)              == 0x11B);
GG_STATIC_ASSERT(offsetof(Cell_Class_004834A0, OccupationFlags)    == 0x124);
GG_STATIC_ASSERT(offsetof(Cell_Class_004834A0, AltOccupationFlags) == 0x128);
GG_STATIC_ASSERT(offsetof(Cell_Class_004834A0, Flags)              == 0x140);

#endif  // GG_MATCH_MAP_CELL_CLASS_CLEAR_TO_MOVE_METHODS_H
