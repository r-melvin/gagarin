// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x56BEC0: the inlined MapClass::GetCellAt (the flat
//   index `MOVSX word[ESP+0xE]; SHL 9; ADD` bounds-checked against 0x40000,
//   the item base `[0x87F924]`, and the miss fallback stamping the cell dword
//   into `[0xABDC74]` and returning 0xABDC50); the land-type test
//   `CMP dword [EAX+0xEC],2`; the crate-slot scan `LEA ECX,[EDI+0x164]` /
//   `ADD ECX,0x10` / `CMP EAX,0x100` (so the crate array starts at +0x158 and
//   each crate is 0x10 bytes with its CellStruct at +0xC); the slot call
//   `SHL EAX,4; LEA ECX,[EAX+EDI+0x158]; CALL 0x4A17C0`; the fifteen-argument
//   `MOV ECX,0x87F7E8; CALL 0x56DC20` (NearByLocation); and the powerup store
//   `MOV byte [EAX+0x11E],DL`. The free-slot sentinel is the CellStruct at
//   0xABD480 (`MOV EDX,[0xABD480]` / `MOV SI,[0xABD482]`). Names
//   cross-checked against YRpp MapClass::PlacePowerupCrate / MapClass::Crates
//   (Crate = CDTimerClass + CellStruct Location) and CellClass LandType@0xEC /
//   OverlayData@0x11E, re-derived here from the disassembly. The sibling
//   match/economy/house_class_dropped_flag_methods.h supplies the
//   NearByLocation declaration shape; match/map/cell_class_tiberium_*.h the
//   LandType/OverlayData offsets.
#ifndef GG_MATCH_MAP_MAP_CLASS_POWERUP_CRATE_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_POWERUP_CRATE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Cell_0056BEC0
{
    short X;   // +0x00
    short Y;   // +0x02
};
GG_STATIC_ASSERT(sizeof(Cell_0056BEC0) == 4);

struct CellClass_0056BEC0
{
    char          _pad000[0xEC];              // +0x0000
    int           LandType;                   // +0x00EC
    char          _pad0F0[0x11E - 0xF0];      // +0x00F0
    unsigned char OverlayData;                // +0x011E
};
GG_STATIC_ASSERT(offsetof(CellClass_0056BEC0, LandType)    == 0xEC);
GG_STATIC_ASSERT(offsetof(CellClass_0056BEC0, OverlayData) == 0x11E);

// GLOBAL: GAMEMD 0x87F924 — MapClass::Instance.Cells item base.
extern CellClass_0056BEC0** Cells_0056BEC0;
// GLOBAL: GAMEMD 0xABDC50 — MapClass::InvalidCell (MapCoords at 0xABDC74).
extern CellClass_0056BEC0 InvalidCell_0056BEC0;
// GLOBAL: GAMEMD 0xABDC74 — InvalidCell::MapCoords, stamped on every miss.
extern Cell_0056BEC0 InvalidCellCoords_0056BEC0;
// GLOBAL: GAMEMD 0xABD480 — the "slot is free" CellStruct sentinel.
extern Cell_0056BEC0 DAT_00ABD480;

// One powerup-crate slot: a CDTimerClass (0xC bytes) plus the cell it sits in.
struct Crate_0056BEC0
{
    char           _pad000[0xC];   // +0x0000  CDTimerClass
    Cell_0056BEC0  Location;       // +0x000C

    // FUNCTION: GAMEMD 0x4A17C0 (decl; reloc) — move this crate to the cell,
    // re-arming its timer; false when the cell will not take it.
    bool FUN_004A17C0(Cell_0056BEC0& cell);
};
GG_STATIC_ASSERT(offsetof(Crate_0056BEC0, Location) == 0xC);
GG_STATIC_ASSERT(sizeof(Crate_0056BEC0) == 0x10);

struct Map_0056BEC0
{
    char          _pad0000[0x158];       // +0x0000
    Crate_0056BEC0 Crates[0x100];        // +0x0158

    // FUNCTION: GAMEMD 0x56DC20 (decl; reloc) — MapClass::NearByLocation.
    Cell_0056BEC0* NearByLocation(Cell_0056BEC0* out, const Cell_0056BEC0& position,
                                  int speedType, int a4, int movementZone, bool alt,
                                  int spaceSizeX, int spaceSizeY, bool a9, bool a10,
                                  bool a11, bool ignoreOccupied,
                                  const Cell_0056BEC0& closeTo, bool a14, bool buildable);
    // The by-value wrapper (YRpp's spelling), expanded inline at the call
    // site: its constant parameters become the shared 1/0 registers and the
    // result is read back through the returned pointer.
    Cell_0056BEC0 NearByLocation(const Cell_0056BEC0& position, int speedType, int a4,
                                 int movementZone, bool alt, int spaceSizeX,
                                 int spaceSizeY, bool a9, bool a10, bool a11,
                                 bool ignoreOccupied, const Cell_0056BEC0& closeTo,
                                 bool a14, bool buildable)
    {
        Cell_0056BEC0 outBuffer;
        return *NearByLocation(&outBuffer, position, speedType, a4, movementZone, alt,
                               spaceSizeX, spaceSizeY, a9, a10, a11, ignoreOccupied,
                               closeTo, a14, buildable);
    }

    // FUNCTION: GAMEMD 0x56BEC0 — MapClass::PlacePowerupCrate.
    bool PlacePowerupCrate(Cell_0056BEC0 cell, int type);
};
GG_STATIC_ASSERT(offsetof(Map_0056BEC0, Crates) == 0x158);

// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance (an object, not a pointer).
extern Map_0056BEC0 DAT_0087F7E8;

#endif  // GG_MATCH_MAP_MAP_CLASS_POWERUP_CRATE_METHODS_H
