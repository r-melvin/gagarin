// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   TActionClass effect handlers read off retail gamemd.exe v1.001 (TAction.CPP, code range
//   0x6dcd70-0x6e4b4f), round 16. The class is a view named for this TU (TActionView_r16) that
//   carries only the members these bodies touch; the handlers are __thiscall
//   (house, object, trigger, cell) and return true after their effect.
//
// Address index (ascending):
//   0x6E0110

#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "_layout/cell.h"
#include "_layout/coord_struct.h"
#include "team_type_class_methods.h"
#include "system_class.h"

class HouseClass;
class ObjectClass;
class TriggerClass;

// The map object, as far as the height query.
struct TActionMap_r16
{
    // FUNCTION: GAMEMD 0x578080 (decl; reloc) -- the height at a coordinate.
    int FUN_00578080(CoordStruct* where);
};
// GLOBAL: GAMEMD 0x87F7E8 -- the map object.
extern TActionMap_r16 DAT_0087F7E8_r16;

// GLOBAL: GAMEMD 0xB0E6A0 -- the owner coordinate handed to a new particle system.
extern ParticleCoord DAT_00B0E6A0_r16;

inline CoordStruct TActionR16_CellToCoord(const CellStruct& cell)
{
    CoordStruct result;
    result.X = cell.X * 256 + 128;
    result.Y = cell.Y * 256 + 128;
    result.Z = 0;
    return result;
}

class TActionView_r16
{
public:
    bool FUN_006E0110(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);

    char unknown_00[0x44];
    int Waypoint;          // +0x44
    char unknown_48[0x90 - 0x48];
    int Param1;            // +0x90
};
GG_STATIC_ASSERT(offsetof(TActionView_r16, Waypoint) == 0x44);
GG_STATIC_ASSERT(offsetof(TActionView_r16, Param1) == 0x90);

// FUNCTION: GAMEMD 0x6E0110
// Create the particle system named by the parameter at the waypoint's cell centre.
bool TActionView_r16::FUN_006E0110(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    CellStruct at;
    at = *WaypointLocatorPtr->GetCoords(&at, Waypoint);
    CoordStruct where = TActionR16_CellToCoord(at);
    CoordStruct height = TActionR16_CellToCoord(at);
    where.Z = DAT_0087F7E8_r16.FUN_00578080(&height);
    new ParticleSystemClass(((ParticleSystemTypeClass**)DAT_00A83D68.Items)[Param1],
                            *reinterpret_cast<ParticleCoord*>(&where), 0, 0, DAT_00B0E6A0_r16, 0);
    return true;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA8B230
WaypointLocator* WaypointLocatorPtr;
// END defined globals
