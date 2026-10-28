// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Target bytes: user's retail gamemd.exe v1.001 (disasm from each entry).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4DB260  FootClass::vf_53 (__thiscall)
//   FUNCTION: GAMEMD 0x4DB9B0  FootClass::vf_321 (__thiscall)
//   FUNCTION: GAMEMD 0x4D4200  FootClass::vf_139 (__thiscall)
//   FUNCTION: GAMEMD 0x4DAF10  FootClass::vf_324 (__thiscall)
//   FUNCTION: GAMEMD 0x4DB1A0  FootClass::vf_334 (__thiscall)
//   FUNCTION: GAMEMD 0x4DC790  FootClass::vf_311 (__thiscall)

#include "../_layout/foot_class.h"
#include "../_layout/building_class.h"
#include "../_layout/techno_type_class.h"
#include "../core/mission_class_methods.h"
#include "loco_com.h"
#include "../_layout/unit_class.h"
#include "../_layout/matrix3d.h"
#include "../_layout/cell_class.h"
#include "../_layout/aircraft_tracker_class.h"

// The eight one-cell steps, indexed by facing.
struct StepCell_004DB260
{
    short X;
    short Y;
};
// GLOBAL: GAMEMD 0x89F688
#define StepTable_004DB260 (reinterpret_cast<StepCell_004DB260 const*>(0x89F688))

// GLOBAL: GAMEMD 0x8B3D88 -- the "no cell" sentinel.
extern CellStruct DAT_008B3D88;
// GLOBAL: GAMEMD 0xA8E7AC -- nonzero while the scenario is being set up.
extern int DAT_00A8E7AC;
// GLOBAL: GAMEMD 0x887888
extern AircraftTrackerClass AircraftTracker;

// The TechnoClass removal reached by the qualified base call.
struct TechnoView_004DB260 : TechnoClass
{
    // FUNCTION: GAMEMD 0x6F6AC0 (decl; reloc) -- the base-class removal.
    bool FUN_006F6AC0();
};

// The FootClass seen as a bare vtable pointer, so the member-pointer call is
// the plain single-inheritance form.
struct Vtbl_004DB260;
struct FootView_004DB260
{
    Vtbl_004DB260* Vtbl;
};
// Slot 189 hands back a Cell through a hidden result pointer.
struct FootView_004DB260;
typedef Cell (FootView_004DB260::*Slot189_004DB260)();
struct Vtbl_004DB260
{
    char              _pad000[0x2F4];
    Slot189_004DB260  At_2F4;       // +0x2F4
};

// The owning house; only the speed-bias query is called.
struct HouseView_004DB1A0
{
    // FUNCTION: GAMEMD 0x50C050 (decl; reloc) -- speed bias for a type.
    double FUN_0050C050(TechnoTypeClass* type);
};

// The rules object, seen through its double at +0x678.
struct Rules_004DB1A0
{
    char   _pad000[0x678];    // +0x0000
    double unknown_678;       // +0x0678
};
GG_STATIC_ASSERT(offsetof(Rules_004DB1A0, unknown_678) == 0x678);
// GLOBAL: GAMEMD 0x8871E0
extern Rules_004DB1A0* DAT_008871E0;

// The scenario randomizer; only the ranged draw is called.
struct Random_004D4200
{
    // FUNCTION: GAMEMD 0x65C7E0 (decl; reloc) -- a value in [min, max].
    int RandomRanged(int min, int max);
};

// ScenarioClass -- only Random @0x218 is touched.
struct Scenario_004D4200
{
    char             _pad000[0x218];    // +0x0000
    Random_004D4200  Random;            // +0x0218
};
GG_STATIC_ASSERT(offsetof(Scenario_004D4200, Random) == 0x218);

// GLOBAL: GAMEMD 0xA8B230 -- ScenarioClass::Instance.
extern Scenario_004D4200* DAT_00A8B230;

// FUNCTION: GAMEMD 0x6EC300 (declaration) -- whether the linked team accepts the move.
char FUN_006EC300(int linked);

class MapClass
{
public:
    // FUNCTION: GAMEMD 0x5785F0 (declaration) -- whether a coordinate is in the usable area.
    bool FUN_005785F0(const CoordStruct& coord);
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) -- the cell at a coordinate.
    CellClass* FUN_005657A0(const CellStruct* cell);
};
// GLOBAL: GAMEMD 0x87F7E8
extern MapClass DAT_0087F7E8;

// The building type seen through its flag at +0x16A9.
struct BuildingTypeView_4DB9B0
{
    char unknown_0000[0x16A9];
    bool unknown_16A9;               // +0x16A9
};
GG_STATIC_ASSERT(offsetof(BuildingTypeView_4DB9B0, unknown_16A9) == 0x16A9);

// The building seen through its type at +0x520.
struct BuildingView_4DB9B0 : TechnoClass
{
    BuildingTypeView_4DB9B0* unknown_520;   // +0x520
};
GG_STATIC_ASSERT(offsetof(BuildingView_4DB9B0, unknown_520) == 0x520);

// FUNCTION: GAMEMD 0x4D4200
// Update delay. A stationary object with no destination and no queued
// mission goes idle and answers 1; otherwise the mission rate times 900 plus a scenario random draw.
int FootClass::vf_139()
{
    if (Destination == 0 && !(*(ILocomotionPtr*)&Locomotor)->IsMoving()
        && QueuedMission == -1) {
        EnterIdleMode(false, true);
        return 1;
    }
    int base = (int)(FUN_005B3A00()->Rate * 900.0);
    return base + DAT_00A8B230->Random.RandomRanged(0, 2);
}

// FUNCTION: GAMEMD 0x4DB260
// Take a placed object off the map. Release the eight neighbour-cell blocked
// counters around its last cell, stop and unmark its locomotor, silence the
// move sound, and drop it from the aircraft tracker when it has a cell.
bool FootClass::vf_53()
{
    if (!InLimbo && vf_33() != 0) {
        CellStruct base = LastMapCoords;
        for (int i = 0; i < 8; i++) {
            CellStruct neighbour = base + *(CellStruct const*)&StepTable_004DB260[i & 7];
            CellClass* around = DAT_0087F7E8.FUN_005657A0(&neighbour);
            around->BlockedNeighbours--;
        }
        if (!DAT_00A8E7AC) {
            vf_320();
        }
        if (Locomotor != 0) {
            (*(ILocomotionPtr*)&Locomotor)->MarkAllOccupationBits(0);
            (*(ILocomotionPtr*)&Locomotor)->ClearCoords();
        }
        MoveSoundAudioController.FUN_00405FD0();
        if (vf_33()->SensorsSight != 0) {
            vf_315(*(int*)&DAT_008B3D88);
        }
        FootView_004DB260* self = (FootView_004DB260*)this;
        if ((self->*self->Vtbl->At_2F4)() != *(Cell const*)&DAT_008B3D88) {
            AircraftTracker.Remove(this);
        }
    }
    return ((TechnoView_004DB260*)this)->FUN_006F6AC0();
}

// FUNCTION: GAMEMD 0x4DB9B0
// With no destination or target, go idle; the second flag is set unless this
// is mission 7 and the first radio link is a building whose type has +0x16A9.
bool FootClass::vf_321()
{
    if (Destination != 0 || Target != 0) {
        return false;
    }
    TechnoClass* link = FUN_0065AD30(0);
    BuildingView_4DB9B0* building = 0;
    if (link != 0 && link->vf_11() == 6) {
        building = (BuildingView_4DB9B0*)link;
    }
    bool hold = CurrentMission == 7 && building != 0
                && building->unknown_520->unknown_16A9;
    return EnterIdleMode(false, !hold);
}

// FUNCTION: GAMEMD 0x4D5660
// Clears the destination, resets the first path direction, then runs slot 320 and the TechnoClass base.
void FootClass::vf_232()
{
    this->SetDestination(0, true);
    this->PathDirections[0] = -1;
    this->vf_320();
    this->TechnoClass::vf_232();
}

// FUNCTION: GAMEMD 0x4D8F80
// When movement is possible, re-issues the stored last destination.
bool FootClass::vf_126()
{
    if (FUN_007013E0()) {
        this->SetDestination((AbstractClass*)this->LastDestination, true);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x4DB0A0
// The locomotor's ZGradient, or 2 without a locomotor.
int FootClass::vf_188()
{
    if (this->Locomotor != 0) {
        return (*(ILocomotionPtr*)&this->Locomotor)->ZGradient();
    }
    return 2;
}

// FUNCTION: GAMEMD 0x4DB7E0
// The locomotor's layer.
int FootClass::vf_30()
{
    return (*(ILocomotionPtr*)&this->Locomotor)->InWhichLayer();
}

// FUNCTION: GAMEMD 0x4DE770
// True while the paralysis timer has time left.
bool FootClass::vf_224()
{
    return this->ParalysisTimer.GetTimeLeft() != 0;
}

// FUNCTION: GAMEMD 0x4DAF10
// PARTIAL 88.7%: only the register order of the draw-point addition differs.
// Forward to TechnoClass slot 273 with the screen point shifted by the
// locomotor's draw point; the point and the matrix go on as local copies.
void FootClass::vf_324(int a1, int a2, int a3, int a4, int a5, Point2D* a6,
                       Matrix3D* a7, int a8, int a9, int a10)
{
    Matrix3D matrix = *a7;
    Point2D point;
    point.X = a6->X;
    point.Y = a6->Y;
    if (Locomotor != 0) {
        LocoPoint2D draw = (*(ILocomotionPtr*)&Locomotor)->DrawPoint();
        Point2D sum;
        sum.Y = a6->Y + draw.Y;
        sum.X = a6->X + draw.X;
        point = sum;
    }
    TechnoClass::vf_273(a1, a2, a3, a4, a5, (int)&point, (int)&matrix, a8, a10, a9);
}

// FUNCTION: GAMEMD 0x4DB1A0
// Move delay: the type's speed scaled by the house bias, the speed multiplier
// and an ability factor, then by the speed percentage; halved for a unit with
// a flag house set.
int FootClass::vf_334()
{
    int delay = (int)(vf_227() * ((HouseView_004DB1A0*)Owner)->FUN_0050C050(vf_33())
                      * SpeedMultiplier);
    if (FUN_0070D0D0(0)) {
        delay = (int)(delay * DAT_008871E0->unknown_678);
    }
    int result = (int)(delay * SpeedPercentage);
    if (vf_11() == 1) {
        int flagHouse = ((UnitClass*)this)->FlagHouseIndex;
        if (flagHouse != -1) {
            result /= 2;
        }
    }
    return result;
}

// FUNCTION: GAMEMD 0x4DC790
// True when in the playfield, the team (if any) agrees, and the destination
// of a type with flag +0xC94 is still inside the usable map area.
bool FootClass::vf_311()
{
    if (!IsInPlayfield) {
        return false;
    }
    if (Team != 0 && !FUN_006EC300((int)Team)) {
        return false;
    }
    if (vf_33()->bools_C8C[8] && Destination != 0) {
        if (DAT_0087F7E8.FUN_005785F0(((AbstractClass*)Destination)->vf_18())) {
            return false;
        }
    }
    return true;
}
