// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4FBF60: on the house `[ESI+0x34]` (the house type)
//   and `[ESI+0x53DC]` (the flag cell, pushed to 0x4FBE40 and stored at the
//   end); on the type `[EAX+0xB8]` (pushed to 0x483410); the map singleton
//   as the immediate `MOV ECX,0x87F7E8` feeding CALL 0x568300
//   (CoordinatesLegal, one pushed cell pointer, AL), CALL 0x5657A0
//   (GetCellAt, one pushed cell pointer) and CALL 0x56DC20 (NearByLocation,
//   fifteen pushed arguments: out pointer, cell pointer, 1, -1, 0, 0, 1, 1,
//   0, 0, 0, 1, close-to pointer, 0, 0); the 4-byte sentinel at 0xA8EF98
//   compared word-wise (`CMP AX,[0xA8EF98]` / `CMP CX,[0xA8EF9A]`); and the
//   cell's own 0x483410 (__thiscall, one pushed int, AL). The cell copy
//   lives in the first parameter's home slot ([ESP+0x14]) and the zeroed
//   close-to cell in the second's ([ESP+0x58]/[ESP+0x5A]); the
//   NearByLocation out buffer is the one real local. Names cross-checked
//   against YRpp HouseClass::DroppedFlag / UpdateFlagCoords,
//   MapClass::CoordinatesLegal / NearByLocation
//   and the sibling match/economy/house_class_flag_methods.h (Type @0x34,
//   the +0x53DC slot, ColorSchemeIndex @0xB8), re-derived here.
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_DROPPED_FLAG_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_DROPPED_FLAG_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Cell_004FBF60
{
    short X;   // +0x00
    short Y;   // +0x02
};
GG_STATIC_ASSERT(sizeof(Cell_004FBF60) == 4);

// GLOBAL: GAMEMD 0xA8EF98 — the "no cell" CellStruct sentinel.
extern Cell_004FBF60 DAT_00A8EF98;

struct CellClass_004FBF60
{
    // FUNCTION: GAMEMD 0x483410 (decl; reloc) — plant the flag in this cell
    // for the given colour index; false when the cell already holds one or
    // cannot take it.
    bool FUN_00483410(int colorIndex);
};

struct Map_004FBF60
{
    // FUNCTION: GAMEMD 0x568300 (decl; reloc) — MapClass::CoordinatesLegal.
    bool CoordinatesLegal(const Cell_004FBF60& cell);
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) — MapClass::GetCellAt.
    CellClass_004FBF60* GetCellAt(const Cell_004FBF60& cell);
    // FUNCTION: GAMEMD 0x56DC20 (decl; reloc) — MapClass::NearByLocation.
    Cell_004FBF60* NearByLocation(Cell_004FBF60* out, const Cell_004FBF60& position,
                                  int speedType, int a4, int movementZone, bool alt,
                                  int spaceSizeX, int spaceSizeY, bool a9, bool a10,
                                  bool a11, bool ignoreOccupied,
                                  const Cell_004FBF60& closeTo, bool a14, bool buildable);
    // The by-value form (YRpp's wrapper), expanded inline at the call site:
    // its parameters become constant-initialised locals, which is what puts
    // the repeated 1 in EAX (with a copy in ECX for SpaceSizeY) and the
    // zeros in EDX, and reads the result back through the returned pointer.
    Cell_004FBF60 NearByLocation(const Cell_004FBF60& position, int speedType, int a4,
                                 int movementZone, bool alt, int spaceSizeX,
                                 int spaceSizeY, bool a9, bool a10, bool a11,
                                 bool ignoreOccupied, const Cell_004FBF60& closeTo,
                                 bool a14, bool buildable)
    {
        Cell_004FBF60 outBuffer;
        NearByLocation(&outBuffer, position, speedType, a4, movementZone, alt,
                       spaceSizeX, spaceSizeY, a9, a10, a11, ignoreOccupied,
                       closeTo, a14, buildable);
        return outBuffer;
    }
};
// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance (an object, not a pointer).
extern Map_004FBF60 DAT_0087F7E8;

struct HouseType_004FBF60
{
    char _pad000[0xB8];      // +0x0000
    int  ColorSchemeIndex;   // +0x00B8
};
GG_STATIC_ASSERT(offsetof(HouseType_004FBF60, ColorSchemeIndex) == 0xB8);

struct House_004FBF60
{
    char                 _pad0000[0x34];               // +0x0000
    HouseType_004FBF60*  Type;                         // +0x0034
    char                 _pad0038[0x53DC - 0x38];      // +0x0038
    CellClass_004FBF60*  FlagLocation;                 // +0x53DC

    // FUNCTION: GAMEMD 0x4FBE40 (decl; reloc) — HouseClass::UpdateFlagCoords.
    void UpdateFlagCoords(CellClass_004FBF60* cell, unsigned long dwUnk);

    // FUNCTION: GAMEMD 0x4FBF60
    bool DroppedFlag(const Cell_004FBF60& cell, unsigned long dwUnk);
};
GG_STATIC_ASSERT(offsetof(House_004FBF60, Type) == 0x34);
GG_STATIC_ASSERT(offsetof(House_004FBF60, FlagLocation) == 0x53DC);

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_DROPPED_FLAG_METHODS_H
