// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   TActionClass effect handlers read off retail gamemd.exe v1.001 (TAction.CPP, code range
//   0x6dcd70-0x6e4b4f), round 16. The class is a view named for this TU (TActionView_r16) that
//   carries only the members these bodies touch; the handlers are __thiscall
//   (house, object, trigger, cell) and return true after their effect.
//
// Address index (ascending):
//   0x6E0110 0x6E1FF0 0x6E26D0 0x6E2790

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/cell.h"
#include "../_layout/coord_struct.h"
#include "team_type_class_methods.h"
#include "../combat/particles/system_class.h"

class HouseClass;
class ObjectClass;
class TriggerClass;

// The map object, as far as the calls these handlers make.
struct TActionCellView_r16
{
    char unknown_00[0x140];
    unsigned int Flags;   // +0x140
};
GG_STATIC_ASSERT(offsetof(TActionCellView_r16, Flags) == 0x140);

struct TActionMap_r16
{
    // FUNCTION: GAMEMD 0x578080 (decl; reloc) -- the height at a coordinate.
    int FUN_00578080(CoordStruct* where);
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) -- the cell record at a cell.
    TActionCellView_r16* FUN_005657A0(const CellStruct* cell);
};
// GLOBAL: GAMEMD 0x87F7E8 -- the map object.
extern TActionMap_r16 DAT_0087F7E8_r16;

// The tactical view, as far as the scroll calls.
struct TActionTactical_r16
{
    // FUNCTION: GAMEMD 0x6D2420 (decl; reloc)
    void FUN_006D2420(CoordStruct* where, int a);
    // FUNCTION: GAMEMD 0x6D6070 (decl; reloc)
    void FUN_006D6070(CoordStruct* where);
};
// GLOBAL: GAMEMD 0x887324 -- the tactical view.
extern TActionTactical_r16* DAT_00887324_r16;

// GLOBAL: GAMEMD 0xB0E6D4 -- extra height added over bridge cells.
extern int DAT_00B0E6D4_r16;
// GLOBAL: GAMEMD 0xB0E6A0 -- the owner coordinate handed to a new particle system.
extern ParticleCoord DAT_00B0E6A0_r16;

// The house lookups behind a house index (0x6E45E0 inlined).
// FUNCTION: GAMEMD 0x726910 (decl; reloc)
HouseClass* TActionR16_Sub726910(void* trigger);
// FUNCTION: GAMEMD 0x510F60 (decl; reloc)
bool TActionR16_Sub510F60(int index);
// FUNCTION: GAMEMD 0x510ED0 (decl; reloc)
HouseClass* TActionR16_Sub510ED0(int index);
// FUNCTION: GAMEMD 0x502D30 (decl; reloc)
HouseClass* TActionR16_Sub502D30(int index);

// A COM-style interface pointer at HouseClass+0x24, called through its raw table.
struct TActionIface_r16;
struct TActionIfaceVtbl_r16
{
    void* slots[14];
    void (__stdcall* Slot14)(TActionIface_r16* self);   // +0x38
};
struct TActionIface_r16
{
    TActionIfaceVtbl_r16* lpVtbl;
};
struct TActionHouseView_r16
{
    char unknown_00[0x24];
    TActionIface_r16 Iface;   // +0x24
};
GG_STATIC_ASSERT(offsetof(TActionHouseView_r16, Iface) == 0x24);

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
    bool FUN_006E1FF0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    bool FUN_006E26D0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);
    bool FUN_006E2790(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell);

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

// FUNCTION: GAMEMD 0x6E1FF0
// Call the interface of the house named by the parameter, if there is one.
bool TActionView_r16::FUN_006E1FF0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    int index = Param1;
    HouseClass* target = 0;
    if (trigger) {
        if (index == 0x2325) {
            target = TActionR16_Sub726910(trigger);
        } else if (index != -1) {
            if (TActionR16_Sub510F60(index))
                target = TActionR16_Sub510ED0(index);
            else
                target = TActionR16_Sub502D30(index);
        }
    }
    if (!target) return false;
    TActionIface_r16* iface = &reinterpret_cast<TActionHouseView_r16*>(target)->Iface;
    iface->lpVtbl->Slot14(iface);
    return true;
}

// FUNCTION: GAMEMD 0x6E26D0
// Scroll the tactical view to the waypoint, lifted over bridge cells, with the parameter.
bool TActionView_r16::FUN_006E26D0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    CellStruct local;
    CellStruct at = *WaypointLocatorPtr->GetCoords(&local, Waypoint);
    CoordStruct where = TActionR16_CellToCoord(at);
    where.Z = DAT_0087F7E8_r16.FUN_00578080(&where);
    if ((DAT_0087F7E8_r16.FUN_005657A0(&at)->Flags & 0x100) ||
        (DAT_0087F7E8_r16.FUN_005657A0(&at)->Flags & 0x400))
        where.Z += DAT_00B0E6D4_r16;
    DAT_00887324_r16->FUN_006D2420(&where, Param1);
    return true;
}

// FUNCTION: GAMEMD 0x6E2790
// Centre the tactical view on the waypoint, lifted over bridge cells.
bool TActionView_r16::FUN_006E2790(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    CellStruct local;
    CellStruct at = *WaypointLocatorPtr->GetCoords(&local, Waypoint);
    CoordStruct where = TActionR16_CellToCoord(at);
    where.Z = DAT_0087F7E8_r16.FUN_00578080(&where);
    if ((DAT_0087F7E8_r16.FUN_005657A0(&at)->Flags & 0x100) ||
        (DAT_0087F7E8_r16.FUN_005657A0(&at)->Flags & 0x400))
        where.Z += DAT_00B0E6D4_r16;
    DAT_00887324_r16->FUN_006D6070(&where);
    return true;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x887324
TActionTactical_r16* DAT_00887324_r16;
// GLOBAL: GAMEMD 0xA8B230
WaypointLocator* WaypointLocatorPtr;
// END defined globals
