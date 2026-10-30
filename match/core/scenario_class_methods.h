// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/addresses derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x4AE4C0 / 0x68BD80),
//   cross-checked against YRpp (reconfirmed here).
//
// ScenarioClass — the global scenario/mission record. Only two methods are
// matched here, so the class is hand-padded to the single member they touch
// (the Waypoints array at +0x632); the full layout is P2.
#ifndef GG_MATCH_CORE_SCENARIO_CLASS_METHODS_H
#define GG_MATCH_CORE_SCENARIO_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/cell.h"
#include "../_layout/object_class.h"
#include "frame_counter.h"
#include "randomizer.h"
#include "type_list.h"
#include "../_layout/elapsed_timer.h"
#include "../_rt/gg_istream.h"

// ---- iterator singleton + cell, used only by UpdateCellLighting ----
#include "../_layout/cell_class.h"

// The global map/radar singleton at 0x87F7E8. UpdateCellLighting drives its
// spiral cell iterator (begin @0x578350, next @0x578290).
class CCINIClass;
class HouseClass;

class WaypointClass;
struct MapInstanceClass
{
    // FUNCTION: GAMEMD 0x5865E0 (decl; reloc). Native returns AL=false, RET4;
    // Tactical6D8FDA/6D965D passes a coordinate snapshot, ECX=87F7E8.
    bool FUN_005865E0(const CoordStruct* coordinate);
    // Declaration: GAMEMD 0x4A94F0, hidden CellStruct result + foundation, RET8
    CellStruct FUN_004A94F0(const CellStruct* foundation) const;
    // Declaration: GAMEMD 0x568300, one cell pointer, AL result, RET4
    bool FUN_00568300(const CellStruct* cell) const;
    // Declaration: GAMEMD 0x56BD40
    void FUN_0056BD40();
    // Declaration: GAMEMD 0x4AC4F0
    void FUN_004AC4F0();
    // FUNCTION: GAMEMD 0x577F30 (decl; 0x6849E7, null house argument).
    void FUN_00577F30(HouseClass* house);
    // FUNCTION: GAMEMD 0x6D0F00 (decl; reloc)
    void FUN_006D0F00();
    // FUNCTION: GAMEMD 0x6AC5F0 (decl; reloc)
    void FUN_006AC5F0(void* item, int value);
    // FUNCTION: GAMEMD 0x6A7590 (decl; reloc)
    void FUN_006A7590(int index);
    // FUNCTION: GAMEMD 0x578080 (decl; reloc) -- the height at a coordinate.
    int FUN_00578080(CoordStruct* where);
    // Declaration: GAMEMD 0x586360, reads original waypoint XYZ, AL result, RET4.
    bool FUN_00586360(const WaypointClass* where);
    // FUNCTION: GAMEMD 0x57B790 (decl; reloc)
    void FUN_0057B790(CellStruct* cell);
    // FUNCTION: GAMEMD 0x56BEC0 (decl; reloc)
    bool FUN_0056BEC0(CellStruct cell, int value);
    void FUN_004AD7E0(CCINIClass* ini); // GAMEMD 0x4AD7E0
    // Hidden Cell result precedes fourteen explicit stack arguments at 0x6885B5.
    Cell FUN_0056DC20(const CellStruct& from, int speedType, int a4,
                     int zone, bool alt, int sizeX, int sizeY,
                     bool a9, bool a10, bool a11, bool ignoreOccupied,
                     const CellStruct& closeTo, bool a14, bool buildable); // GAMEMD 0x56DC20
    // FUNCTION: GAMEMD 0x5657a0 (decl; reloc)
    // ?FUN_005657A0@MapInstanceClass@@QAEPAVCellClass@@PBUCellStruct@@@Z
    CellClass* FUN_005657A0(const CellStruct* cell);
    // Declaration: GAMEMD 0x565730, two-int world position, CellClass* result, RET4.
    CellClass* FUN_00565730(const Point2D* location);
    // Same native entry565730: callers6D6DCF/6D72A2 pass a12-byte coordinate;
    // callee consumes only X/Y at0/4, never reads Z or writes the input.
    CellClass* FUN_00565730(const CoordStruct* location);
    void FUN_005BDA80(int a, int b); // GAMEMD 0x5BDA80, __thiscall
    void FUN_004F4480(); // GAMEMD 0x4F4480, __thiscall
    void FUN_00655B20(); // GAMEMD 0x655B20, __thiscall
    void FUN_004F42F0(int value); // GAMEMD 0x4F42F0, __thiscall
    void FUN_00565B00(); // GAMEMD 0x565B00
    void FUN_005BDF50(); // GAMEMD 0x5BDF50
    bool FUN_00578460(const CellStruct* cell, int flag); // GAMEMD 0x578460
    void FUN_006D04F0(int value); // GAMEMD 0x6D04F0
    void FUN_00653F70(CoordStruct* where); // GAMEMD 0x653F70
    void FUN_004ADCD0(int first, int second); // GAMEMD 0x4ADCD0
    void FUN_0056D6E0(); // GAMEMD 0x56D6E0
    void FUN_0056C510(); // GAMEMD 0x56C510
    void FUN_00581F50(); // GAMEMD 0x581F50
    void FUN_00586BF0(); // GAMEMD 0x586BF0
    void FUN_006938C0(); // GAMEMD 0x6938C0, __thiscall
    void       IteratorBegin_578350();   // GAMEMD 0x578350  __thiscall
    CellClass* IteratorNext_578290();    // GAMEMD 0x578290  __thiscall
};

// GLOBAL: GAMEMD 0x87F7E8  MapClass::Instance (the map singleton).
extern MapInstanceClass MapInstance;

// GLOBAL: GAMEMD 0x00B05458  the "undefined" waypoint sentinel cell.
extern CellStruct WaypointUndefined;

// STRING: GAMEMD 0x0083D868
// "Toggle display mode to %d x %d\n"
extern const char STR_0083D868[];
// STRING: GAMEMD 0x0083D924
// "Toggle display mode back to shell res\n"
extern const char STR_0083D924[];
// STRING: GAMEMD 0x0083D824
// "VariableNames"
extern const char STR_0083D824[];
// STRING: GAMEMD 0x00817F70
// ","
extern const char STR_00817F70[];
// STRING: GAMEMD 0x00817F6C
// "%d"
extern const char STR_00817F6C[];
// STRING: GAMEMD 0x0083DE1C
// "%s,%d"
extern const char STR_0083DE1C[];
// STRING: GAMEMD 0x0082DB0C
// "Waypoints"
extern const char STR_0082DB0C[];
// STRING: GAMEMD 0x00889F64
// ""
extern const char STR_00889F64[];


#include "scenario_class.h"

#endif  // GG_MATCH_CORE_SCENARIO_CLASS_METHODS_H
