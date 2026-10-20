// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x703590: the GetTechnoType slot `[EAX+0x84]` and
//   the type's `[EAX+0x67C]` (SpeedType, 4 mapped to 1) and `[EAX+0x5B4]`
//   (MovementZone); the GetCoords slot `[EDX+0x48]` (hidden 12-byte
//   buffer) whose X / Y are divided by 256 into a CellStruct; the object's
//   `[ESI+0x8C]` (OnBridge byte); the map object 0x87F7E8 with
//   GetMovementZoneType 0x56D230 (cell, zone, bridge) and NearByLocation
//   0x56DC20 (fifteen pushed arguments). The hidden result pointer is the
//   first stack argument (RET 8). Names cross-checked against YRpp
//   TechnoClass.h / MapClass.h (consult-only; NO LICENSE).
#ifndef GG_MATCH_COMBAT_TECHNO_CLASS_NEARBY_LOCATION_METHODS_H
#define GG_MATCH_COMBAT_TECHNO_CLASS_NEARBY_LOCATION_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// CellStruct — the user-declared constructor selects the hidden-pointer
// return convention (see the banked "Struct returns" rule).
struct Cell_00703590
{
    short X;   // +0x0000
    short Y;   // +0x0002
    Cell_00703590() {}
    Cell_00703590(int x, int y) { X = (short)x; Y = (short)y; }
};

inline Cell_00703590 ZeroCell_00703590()
{
    Cell_00703590 r;
    r.X = 0;
    r.Y = 0;
    return r;
}
GG_STATIC_ASSERT(sizeof(Cell_00703590) == 0x4);

struct Coord_00703590
{
    int X;   // +0x0000
    int Y;   // +0x0004
    int Z;   // +0x0008
};
GG_STATIC_ASSERT(sizeof(Coord_00703590) == 0xC);

// Coordinate to cell (signed division by 256 per axis), by value.
inline Cell_00703590 CoordToCell_00703590(const Coord_00703590* c)
{
    Cell_00703590 r;
    r.X = (short)(c->X / 256);
    r.Y = (short)(c->Y / 256);
    return r;
}

// TechnoTypeClass — MovementZone and SpeedType.
struct TechnoType_00703590
{
    char _pad000[0x5B4];          // +0x0000
    int  MovementZone;            // +0x05B4
    char _pad5B8[0x67C - 0x5B8];  // +0x05B8
    int  SpeedType;               // +0x067C
};
GG_STATIC_ASSERT(offsetof(TechnoType_00703590, MovementZone) == 0x5B4);
GG_STATIC_ASSERT(offsetof(TechnoType_00703590, SpeedType)    == 0x67C);

struct Vtbl_00703590;

// TechnoClass / ObjectClass — the vtable and the OnBridge byte.
struct Obj_00703590
{
    Vtbl_00703590* Vptr;           // +0x0000
    char           _pad004[0x88];  // +0x0004
    bool           OnBridge;       // +0x008C

    // FUNCTION: GAMEMD 0x703590 — TechnoClass::NearbyLocation.
    Cell_00703590 NearbyLocation(Obj_00703590* object);
};
GG_STATIC_ASSERT(offsetof(Obj_00703590, OnBridge) == 0x8C);

typedef Coord_00703590* (Obj_00703590::*Fn48_00703590)(Coord_00703590* out);
typedef TechnoType_00703590* (Obj_00703590::*Fn84_00703590)();

struct Vtbl_00703590
{
    char           _pad000[0x48];   // +0x0000
    Fn48_00703590  GetCoords;       // +0x0048
    char           _pad04C[0x38];   // +0x004C
    Fn84_00703590  GetTechnoType;   // +0x0084
};
GG_STATIC_ASSERT(offsetof(Vtbl_00703590, GetCoords)     == 0x48);
GG_STATIC_ASSERT(offsetof(Vtbl_00703590, GetTechnoType) == 0x84);

// MapClass — the zone lookup and the nearby-cell search.
struct Map_00703590
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x56D230 (decl; reloc) — MapClass::GetMovementZoneType.
    int GetMovementZoneType(const Cell_00703590& cell, int movementZone, bool isBridge);
    // FUNCTION: GAMEMD 0x56DC20 (decl; reloc) — MapClass::NearByLocation.
    Cell_00703590* NearByLocation(Cell_00703590* out, const Cell_00703590& position,
                                  int speedType, int a4, int movementZone, bool alt,
                                  int spaceSizeX, int spaceSizeY, bool a9, bool a10,
                                  bool a11, bool ignoreOccupied,
                                  const Cell_00703590& closeTo, bool a14, bool buildable);
    // The by-value form, expanded inline at the call site.
    Cell_00703590 NearByLocation(const Cell_00703590& position, int speedType, int a4,
                                 int movementZone, bool alt, int spaceSizeX,
                                 int spaceSizeY, bool a9, bool a10, bool a11,
                                 bool ignoreOccupied, const Cell_00703590& closeTo,
                                 bool a14, bool buildable)
    {
        Cell_00703590 outBuffer;
        return *NearByLocation(&outBuffer, position, speedType, a4, movementZone, alt,
                               spaceSizeX, spaceSizeY, a9, a10, a11, ignoreOccupied,
                               closeTo, a14, buildable);
    }
};
// GLOBAL: GAMEMD 0x87F7E8 — the map instance.
extern Map_00703590 MapInstance_00703590;

#endif  // GG_MATCH_COMBAT_TECHNO_CLASS_NEARBY_LOCATION_METHODS_H
