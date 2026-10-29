// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   More TActionClass action handlers read off retail gamemd.exe v1.001 (TAction.CPP,
//   code range 0x6dcd70-0x6e4b4f). The class is a view that carries only the members these
//   bodies touch; callees and globals are declared as needed. Every handler is
//   __thiscall (house, object, trigger, cell) and returns true after its effect.
//   Functions are in ascending retail address order.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/abstract_class.h"
#include "taction_class_methods.h"
#include "../_layout/team_type_class.h"
#include "../_layout/cell.h"
#include "../_layout/map_0087f7e8.h"

class HouseClass;
class ObjectClass;
class TriggerClass;
class TeamTypeClass;

// The house type, as far as the colour scheme index.
struct TActionHouseType
{
    char unknown_00[0xB8];
    int ColorSchemeIndex;   // +0xB8
};

// The local player's house, seen through the methods these handlers call.
struct TActionHouse
{
    char unknown_00[0x34];
    TActionHouseType* Type;   // +0x34

    // FUNCTION: GAMEMD 0x4FC9E0 (decl; reloc)
    void FUN_004FC9E0(int a);
    // FUNCTION: GAMEMD 0x4FCBD0 (decl; reloc)
    void FUN_004FCBD0(int a);
    // FUNCTION: GAMEMD 0x4FCDC0 (decl; reloc)
    void FUN_004FCDC0();
};
GG_STATIC_ASSERT(offsetof(TActionHouse, Type) == 0x34);



// A super weapon, as far as the call and the flag these handlers use.
struct TActionSuper
{
    char unknown_00[0x60];
    bool CanHold;   // +0x60
    // FUNCTION: GAMEMD 0x6CB560 (decl; reloc)
    void FUN_006CB560(int a, int b, int c);
};
GG_STATIC_ASSERT(offsetof(TActionSuper, CanHold) == 0x60);

// A house, as far as its super weapon list.
struct TActionSuperHouse
{
    char unknown_00[0x258];
    TActionSuper** SuperItems;   // +0x258 (Supers.Items)
};
GG_STATIC_ASSERT(offsetof(TActionSuperHouse, SuperItems) == 0x258);

// The map object's sidebar refresh calls (0x6A6300 and 0x6A60A0).
struct TActionSidebar
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x6A6300 (decl; reloc)
    void FUN_006A6300(int a, int b);
    // FUNCTION: GAMEMD 0x6A60A0 (decl; reloc)
    void FUN_006A60A0(int a);
};
// GLOBAL: GAMEMD 0x87F7E8 -- the map object, whose sidebar refresh the handlers call.
extern TActionSidebar DAT_0087F7E8_Sidebar;
// FUNCTION: GAMEMD 0x6ABC60 (decl; reloc)
int __fastcall FUN_006ABC60(int a, int b, int c);

// GLOBAL: GAMEMD 0xA83D4C -- HouseClass::CurrentPlayer.
extern TActionHouse* DAT_00A83D4C;
// GLOBAL: GAMEMD 0xA8E7AC -- nonzero while a team is being created by an action.
extern int DAT_00A8E7AC;
// GLOBAL: GAMEMD 0x88098C / 0x880990 / 0x880994 / 0x88099A / 0x88099B / 0x88099C -- tactical-view state reset by action 0x24.
extern int DAT_0088098C;
extern int DAT_00880990;
extern int DAT_00880994;
extern bool DAT_0088099A;
extern bool DAT_0088099B;
extern bool DAT_0088099C;
// FUNCTION: GAMEMD 0x684240 (decl; reloc)
void __cdecl FUN_00684240();

// The view-rate controller object whose two dwords (a double) the pause handlers set.
struct TActionRate
{
    char unknown_00[0xC0];
    int unknown_C0;   // +0xC0 low half of a double
    int unknown_C4;   // +0xC4 high half
};
GG_STATIC_ASSERT(offsetof(TActionRate, unknown_C4) == 0xC4);
// GLOBAL: GAMEMD 0x887324
extern TActionRate* DAT_00887324;

struct TActionSlowObject
{
    // FUNCTION: GAMEMD 0x54F720 (decl; reloc)
    void FUN_0054F720();
};
// GLOBAL: GAMEMD 0x87F770
extern TActionSlowObject* DAT_0087F770;

// The object whose virtual slots the pause handlers call.
class TActionPauseTarget
{
public:
    virtual void vf_0();
    virtual void vf_1();
    virtual void vf_2();
    virtual void vf_3();
    virtual void vf_4();
};
// GLOBAL: GAMEMD 0x887640
extern TActionPauseTarget* DAT_00887640;
// GLOBAL: GAMEMD 0x8871E0 -- holder of the stored rate (+0x550, two dwords).
struct TActionRateSource { char unknown_00[0x550]; int unknown_550; int unknown_554; };
extern TActionRateSource* DAT_008871E0;
// GLOBAL: GAMEMD 0xA8ED9C
extern bool DAT_00A8ED9C;
// GLOBAL: GAMEMD 0xA8B230
#include "../core/scenario_class_methods.h"
extern ScenarioClass* DAT_00A8B230;
// FUNCTION: GAMEMD 0x53AD00 (decl; reloc)
void FUN_0053AD00(int a, int b, int c, int d);
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);


// FUNCTION: GAMEMD 0x6E0480
// Run the local player's house through its 0x4FCDC0 step.
bool TActionClass::FUN_006E0480(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    DAT_00A83D4C->FUN_004FCDC0();
    return true;
}

// FUNCTION: GAMEMD 0x6E0F90
// Run the map's 0x4ACAC0 step.
bool TActionClass::FUN_006E0F90(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    DAT_0087F7E8.FUN_004ACAC0();
    return true;
}

// FUNCTION: GAMEMD 0x6E1BD0
// Give the house its super weapon, and refresh the sidebar when the house is the local player.
bool TActionClass::FUN_006E1BD0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    reinterpret_cast<TActionSuperHouse*>(house)->SuperItems[unknown_90]->FUN_006CB560(1, 0, 0);
    if (reinterpret_cast<HouseClass*>(DAT_00A83D4C) == house) {
        DAT_0087F7E8_Sidebar.FUN_006A6300(0x1f, unknown_90);
        DAT_0087F7E8_Sidebar.FUN_006A60A0(FUN_006ABC60(0x1f, unknown_90, 0));
    }
    return true;
}

// FUNCTION: GAMEMD 0x6E1C40
// Take the super weapon away and clear its hold flag, refreshing the sidebar for the local player.
bool TActionClass::FUN_006E1C40(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    reinterpret_cast<TActionSuperHouse*>(house)->SuperItems[unknown_90]->FUN_006CB560(0, 0, 0);
    reinterpret_cast<TActionSuperHouse*>(house)->SuperItems[unknown_90]->CanHold = false;
    if (reinterpret_cast<HouseClass*>(DAT_00A83D4C) == house) {
        DAT_0087F7E8_Sidebar.FUN_006A6300(0x1f, unknown_90);
        DAT_0087F7E8_Sidebar.FUN_006A60A0(FUN_006ABC60(0x1f, unknown_90, 0));
    }
    return true;
}

// FUNCTION: GAMEMD 0x6E1DC0
// Apply one local-player step when the parameter names the player's colour scheme, the other if not.
bool TActionClass::FUN_006E1DC0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    if (unknown_90 == DAT_00A83D4C->Type->ColorSchemeIndex) {
        DAT_00A83D4C->FUN_004FC9E0(0);
    } else {
        DAT_00A83D4C->FUN_004FCBD0(0);
    }
    return true;
}

// FUNCTION: GAMEMD 0x6E1E00
// The mirror of the previous handler: the second step when the colour scheme matches.
bool TActionClass::FUN_006E1E00(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    if (unknown_90 != DAT_00A83D4C->Type->ColorSchemeIndex) {
        DAT_00A83D4C->FUN_004FC9E0(0);
    } else {
        DAT_00A83D4C->FUN_004FCBD0(0);
    }
    return true;
}

// FUNCTION: GAMEMD 0x6E1F60
// Create the action's team while the setup flag is raised.
bool TActionClass::FUN_006E1F60(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    DAT_00A8E7AC++;
    if (unknown_30) {
        unknown_30->CreateTeam(0);
    }
    DAT_00A8E7AC--;
    return true;
}

// FUNCTION: GAMEMD 0x6E2660
// Reset the tactical view state.
bool TActionClass::FUN_006E2660(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    DAT_0088098C = 0;
    DAT_00880990 = 0;
    DAT_00880994 = -1;
    DAT_0087F7E8.FUN_004A8BF0(0);
    DAT_0087F7E8.FUN_004AC8C0(0);
    DAT_0087F7E8.FUN_004AC660(0);
    DAT_0088099A = false;
    DAT_0088099B = false;
    DAT_0088099C = false;
    FUN_00684240();
    return true;
}

// FUNCTION: GAMEMD 0x6E2860
// Pause: store the saved rate into the controller, then redraw and sleep a second.
bool TActionClass::FUN_006E2860(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    int* rate = &DAT_008871E0->unknown_550;
    DAT_00887324->unknown_C0 = rate[0];
    DAT_00887324->unknown_C4 = rate[1];
    DAT_00A8ED9C = true;
    DAT_0087F770->FUN_0054F720();
    DAT_00887640->vf_3();
    DAT_0087F7E8.FUN_006938C0();
    DAT_0087F7E8.FUN_004F42F0(0);
    DAT_0087F7E8.FUN_004F4480();
    Sleep(1000);
    return true;
}

// FUNCTION: GAMEMD 0x6E28E0
// Resume: restore a rate of 1.0, mirror the session flag, and redraw.
bool TActionClass::FUN_006E28E0(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    DAT_00887324->unknown_C0 = 0;
    DAT_00887324->unknown_C4 = 0x3ff00000;
    DAT_0087F770->FUN_0054F720();
    DAT_00A8ED9C = DAT_00A8B230->unknown_35A2;
    DAT_00887640->vf_4();
    DAT_0087F7E8.FUN_004F42F0(0);
    DAT_0087F7E8.FUN_004F4480();
    return true;
}

// FUNCTION: GAMEMD 0x6E2F00
// Record the action's parameter in the session and scroll to it.
bool TActionClass::FUN_006E2F00(HouseClass* house, ObjectClass* object, TriggerClass* trigger, CellStruct* cell)
{
    FUN_0053AD00(DAT_00A8B230->unknown_3534 * 10, DAT_00A8B230->unknown_3538 * 10, unknown_90 * 10, 0);
    DAT_00A8B230->unknown_353C = unknown_90;
    return true;
}
