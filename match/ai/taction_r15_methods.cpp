// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   More TActionClass handlers (TAction.CPP, code range 0x6dcd70-0x6e4b4f) read off the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI at the address in each annotation.
//   Address index: 0x6E01C0, 0x6E0930, 0x6E0AA0, 0x6E0B60, 0x6E0EF0, 0x6E16D0, 0x6E1830, 0x6E18B0, 0x6E1980,
//   0x6E2600, 0x6E2970, 0x6E2BB0, 0x6E4040.

#include "taction_class_methods.h"
#include "../core/scenario_class_methods.h"
#include "../_layout/house_class.h"
#include "../_layout/tag_class.h"
#include "../_layout/techno_class.h"
#include "../_layout/infantry_class.h"
#include "../_layout/building_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/coord_struct.h"
#include "../core/building_light_class.h"
#include "../core/id_resolve_command_sweep.h"
#include "../_layout/map_0087f7e8.h"

#include "../_layout/scenario_ptr_00a8b230.h"
// GLOBAL: GAMEMD 0xA8EC7C / 0xA8EC88 -- TechnoClass array items and count.
extern TechnoClass** DAT_00A8EC7C;
extern int DAT_00A8EC88;
// GLOBAL: GAMEMD 0xA83DEC / 0xA83DF8 -- InfantryClass array items and count.
extern InfantryClass** DAT_00A83DEC;
extern int DAT_00A83DF8;

// FUNCTION: GAMEMD 0x726910 (decl; reloc) -- the house a trigger belongs to.
HouseClass* FUN_00726910(TriggerClass* trigger);
// FUNCTION: GAMEMD 0x510F60 (decl; reloc)
bool FUN_00510F60(int index);

// The house named by an action's parameter (same lookup as 0x6E45E0, which retail inlines here).
static __inline HouseClass* FindActionHouseR15(TriggerClass* trigger, int index)
{
    if (trigger == 0)
        return 0;
    if (index == 0x2325)
        return FUN_00726910(trigger);
    if (index == -1)
        return 0;
    if (FUN_00510F60(index))
        return FUN_00510ED0(index);
    return FUN_00502D30(index);
}

// The rules object (GLOBAL 0x8871E0); only the dword at +0x1794 is read here.
struct TActionR15Rules
{
    unsigned char unknown_00[0x1794];
    int unknown_1794;   // +0x1794
};
GG_STATIC_ASSERT(offsetof(TActionR15Rules, unknown_1794) == 0x1794);
// GLOBAL: GAMEMD 0x8871E0
extern TActionR15Rules* DAT_008871E0_R15;

// GLOBAL: GAMEMD 0xB0E680 -- the undefined cell.
extern CellStruct DAT_00B0E680;

// The view-control object (GLOBAL 0x887640) whose slots 5 and 6 bracket a redraw.
class TActionR15Display
{
public:
    virtual void vf_0();
    virtual void vf_1();
    virtual void vf_2();
    virtual void vf_3();
    virtual void vf_4();
    virtual void vf_5();
    virtual void vf_6();
};
// GLOBAL: GAMEMD 0x887640
extern TActionR15Display* DAT_00887640_R15;

// A team, as far as the dword at +0x54.
struct TActionR15Team
{
    unsigned char unknown_00[0x54];
    void* unknown_54;   // +0x54
};
GG_STATIC_ASSERT(offsetof(TActionR15Team, unknown_54) == 0x54);

// FUNCTION: GAMEMD 0x53A100 (decl; reloc) -- a global byte flag, read without a receiver.
bool __cdecl FUN_0053A100();
// FUNCTION: GAMEMD 0x539EB0 (decl; reloc)
void __fastcall FUN_00539EB0(int a, int b, CellStruct cell, void* c);
// FUNCTION: GAMEMD 0x65FA70 (decl; reloc)
void __fastcall FUN_0065FA70(int a, CellStruct cell);
// FUNCTION: GAMEMD 0x6F1F70 (decl; reloc) -- the first live team of a team type.
TActionR15Team* __fastcall FUN_006F1F70(TeamTypeClass* teamType);
// FUNCTION: GAMEMD 0x70F120 (decl; reloc)
void __fastcall FUN_0070F120(void* a, int b);
// FUNCTION: GAMEMD 0x72DDB0 (decl; reloc)
void __cdecl FUN_0072DDB0();
// FUNCTION: GAMEMD 0x6842F0 (decl; reloc)
void __fastcall FUN_006842F0(bool flag);
// FUNCTION: GAMEMD 0x5BF260 (decl; reloc)
void __fastcall FUN_005BF260(int a, int b, int c, int d, int e);
// FUNCTION: GAMEMD 0x72DEF0 (decl; reloc)
void __cdecl FUN_0072DEF0();

// FUNCTION: GAMEMD 0x6E01C0
// Order every live foot-soldier or unit-less tagged object carrying this trigger to mission 5.
bool TActionClass::FUN_006E01C0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    for (int i = 0; i < DAT_00A8EC88; i++) {
        TechnoClass* t = DAT_00A8EC7C[i];
        if (t->vf_11() != 6 && t->IsAlive && t->IsOnMap && t->AttachedTag && t->AttachedTag->ContainsTrigger(trigger)
            && (t->vf_97() == 0 || t->vf_97() == 0x17)) {
            t->vf_122(5, false);
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x6E0930
// Run slot 325 on every live, mapped infantry carrying this trigger.
bool TActionClass::FUN_006E0930(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    bool result = false;
    for (int i = 0; i < DAT_00A83DF8; i++) {
        InfantryClass* inf = DAT_00A83DEC[i];
        if (inf->IsAlive && inf->IsOnMap && !inf->InLimbo && inf->AttachedTag
            && inf->AttachedTag->ContainsTrigger(trigger)) {
            inf->vf_325();
            result = true;
        }
    }
    return result;
}

// FUNCTION: GAMEMD 0x6E0AA0
// Give the named house to every live, mapped techno carrying this trigger (slot 245).
bool TActionClass::FUN_006E0AA0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    HouseClass* target = FindActionHouseR15(trigger, unknown_90);
    if (target == 0)
        return false;
    bool result = false;
    for (int i = 0; i < DAT_00A8EC88; i++) {
        TechnoClass* t = DAT_00A8EC7C[i];
        if (t->IsAlive && t->IsOnMap && !t->InLimbo && t->AttachedTag && t->AttachedTag->ContainsTrigger(trigger)) {
            t->vf_245(target, false);
            result = true;
        }
    }
    return result;
}

// FUNCTION: GAMEMD 0x6E16D0
// Bracket a redraw of the view around a 0x5BF260 step on the action's parameter.
bool TActionClass::FUN_006E16D0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    FUN_0072DDB0();
    DAT_00887640_R15->vf_5();
    FUN_006842F0(false);
    FUN_005BF260(unknown_90, -1, 1, 1, 1);
    FUN_006842F0(true);
    DAT_00887640_R15->vf_6();
    FUN_0072DEF0();
    return true;
}

// FUNCTION: GAMEMD 0x6E2600
// Unless the lightning flag is raised, run the 0x539EB0 step on the action's parameter.
bool TActionClass::FUN_006E2600(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    if (FUN_0053A100())
        return false;
    FUN_00539EB0(unknown_90, DAT_008871E0_R15->unknown_1794, DAT_00B0E680, 0);
    return true;
}

// FUNCTION: GAMEMD 0x6E2BB0
// Hand the action's parameter and its waypoint cell to 0x65FA70.
bool TActionClass::FUN_006E2BB0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    FUN_0065FA70(unknown_90, DAT_00A8B230->GetWaypointCoords(unknown_44));
    return true;
}

// FUNCTION: GAMEMD 0x6E4040
// Run the 0x70F120 step on the team type's first live team (or on nothing).
bool TActionClass::FUN_006E4040(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    if (unknown_30) {
        TActionR15Team* team = FUN_006F1F70(unknown_30);
        if (team) {
            FUN_0070F120(team->unknown_54, unknown_90);
            return true;
        }
    } else {
        FUN_0070F120(0, 0);
    }
    return true;
}


// An object found in a cell, as far as the 0x5F6CB0 step.
struct TActionR15Object
{
    // FUNCTION: GAMEMD 0x5F6CB0 (decl; reloc) -- one stack argument.
    void FUN_005F6CB0(int a);
};
// FUNCTION: GAMEMD 0x750E20 (decl; reloc)
void __fastcall FUN_00750E20(int sound, CoordStruct* where, int unused);
// FUNCTION: GAMEMD 0x750F40 (decl; reloc)
void __fastcall FUN_00750F40(CoordStruct* where, int flag);

// FUNCTION: GAMEMD 0x6E0B60
// Hand the named house to every techno of the given owner, buildings last (those that act as a yard
// are handed over after the rest and then given their 0x4549B0 step).
bool TActionClass::FUN_006E0B60(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    bool result = false;
    HouseClass* target = FindActionHouseR15(trigger, unknown_90);
    if (target == 0)
        return false;
    for (int i = 0; i < DAT_00A8EC88; i++) {
        TechnoClass* t = DAT_00A8EC7C[i];
        if (t->Owner == house) {
            if (t == 0 || t->vf_11() != 6 || ((BuildingClass*)t)->Type == 0
                || (!((BuildingClass*)t)->Type->bools_1570[3] && !((BuildingClass*)t)->Type->bools_1570[4])) {
                DAT_00A8EC7C[i]->vf_245(target, false);
                result = true;
            }
        }
    }
    for (int j = 0; j < DAT_00A8EC88; j++) {
        TechnoClass* t = DAT_00A8EC7C[j];
        if (t->Owner == house && t != 0 && t->vf_11() == 6 && ((BuildingClass*)t)->Type != 0
            && (((BuildingClass*)t)->Type->bools_1570[3] || ((BuildingClass*)t)->Type->bools_1570[4])) {
            DAT_00A8EC7C[j]->vf_245(target, false);
            ((BuildingClass*)t)->FUN_004549B0();
            result = true;
        }
    }
    return result;
}

// FUNCTION: GAMEMD 0x6E1830
// The object standing in the cell under a coordinate: its building, else the first other occupant.
ObjectClass* __fastcall FUN_006E1830(CoordStruct* coord)
{
    CellStruct tmp;
    tmp.X = (short)(coord->X / 256);
    tmp.Y = (short)(coord->Y / 256);
    CellStruct at = tmp;
    ObjectClass* o = 0;
    if (at.X != DAT_00B0E680.X || at.Y != DAT_00B0E680.Y) {
        CellClass* c = DAT_0087F7E8.FUN_005657A0(&at);
        o = c->GetBuilding();
        if (o == 0)
            o = c->FUN_0047C550(false);
    }
    return o;
}

// FUNCTION: GAMEMD 0x6E18B0
// Run the 0x5F6CB0 step on the occupant of the waypoint's cell, or play the sound at the spot if none.
bool TActionClass::FUN_006E18B0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    CoordStruct where = DAT_00A8B230->FUN_0068BD00(unknown_44);
    CellStruct tmp;
    tmp.X = (short)(where.X / 256);
    tmp.Y = (short)(where.Y / 256);
    CellStruct at = tmp;
    if (at.X != DAT_00B0E680.X || at.Y != DAT_00B0E680.Y) {
        CellClass* c = DAT_0087F7E8.FUN_005657A0(&at);
        ObjectClass* o = c->GetBuilding();
        if (o == 0)
            o = c->FUN_0047C550(false);
        if (o != 0) {
            ((TActionR15Object*)o)->FUN_005F6CB0(unknown_90);
            return true;
        }
    }
    FUN_00750E20(unknown_90, &where, 1);
    return true;
}

// FUNCTION: GAMEMD 0x6E1980
// Run the 0x5F6CB0 step (with -1) on the occupant of the waypoint's cell, or the 0x750F40 step if none.
bool TActionClass::FUN_006E1980(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    CoordStruct where = DAT_00A8B230->FUN_0068BD00(unknown_44);
    CellStruct tmp;
    tmp.X = (short)(where.X / 256);
    tmp.Y = (short)(where.Y / 256);
    CellStruct at = tmp;
    if (at.X != DAT_00B0E680.X || at.Y != DAT_00B0E680.Y) {
        CellClass* c = DAT_0087F7E8.FUN_005657A0(&at);
        ObjectClass* o = c->GetBuilding();
        if (o == 0)
            o = c->FUN_0047C550(false);
        if (o != 0) {
            ((TActionR15Object*)o)->FUN_005F6CB0(-1);
            return true;
        }
    }
    FUN_00750F40(&where, 1);
    return true;
}

// GLOBAL: GAMEMD 0xA8EB44 / 0xA8EB50 -- BuildingClass array items and count.
extern BuildingClass** DAT_00A8EB44;
extern int DAT_00A8EB50;

// FUNCTION: GAMEMD 0x6E2970
// Give the spotlight of every live, mapped building carrying this trigger its 0x436BE0 step.
bool TActionClass::FUN_006E2970(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    bool result = false;
    for (int i = 0; i < DAT_00A8EB50; i++) {
        BuildingClass* b = DAT_00A8EB44[i];
        if (b->Health > 0 && b->IsAlive && b->IsOnMap && !b->InLimbo && b->Type->bools_154B[0] && b->Spotlight
            && b->AttachedTag && b->AttachedTag->ContainsTrigger(trigger)) {
            ((BuildingLightClass*)b->Spotlight)->FUN_00436BE0(unknown_90);
            result = true;
        }
    }
    return result;
}

// FUNCTION: GAMEMD 0x50C210 (decl; reloc) -- a step on the house.
void __fastcall FUN_0050C210(HouseClass* house);

// FUNCTION: GAMEMD 0x6E0EF0
// PARTIAL: 96.1% -- identical instruction multiset; retail stores the auto-base flag before loading
// the construction-yard count, this build loads the count first.
// Switch the house's automatic base building on (re-centring its base on its first construction
// yard) or off.
bool TActionClass::FUN_006E0EF0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    if (*(char*)&unknown_90 != 0) {
        house->AutoBaseBuilding = 1;
        int yards = house->ConYards.Count;
        if (yards > 0) {
            CoordStruct where = house->ConYards.Items[0]->Location;
            Cell base;
            base.X = (short)(where.X / 256);
            base.Y = (short)(where.Y / 256);
            house->FUN_0050E000(base);
            *(Cell*)((char*)house + 0x5750) = base;
        }
        if (*(int*)((char*)house + 0x5714) == 0)
            FUN_0050C210(house);
    } else {
        house->AutoBaseBuilding = 0;
    }
    return true;
}
