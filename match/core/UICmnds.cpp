// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit UICmnds.cpp. The name is the source-file string at 0x845598
//   in retail gamemd.exe v1.001, passed by the assert at 0x731b01 inside this object's
//   code range (0x730780-0x73442f). Functions are in ascending retail address order.
//
//   cross-checked against YRpp. Each function is
//
// reccmp annotations:

#include "../_layout/techno_class.h"
#include "../_layout/house_class.h"
#include "../_layout/techno_type_class.h"
#include "vector_class_operations.h"
#include <stdlib.h>
#include <string.h>
#include "../audio/voc_class_play_global_methods.h"
#include "../_layout/infantry_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/unit_class.h"
#include "../ai/planning_manager.h"
#include "../network/beacon_manager_class.h"
#include "../_layout/building_class.h"
#include "../_layout/building_type_class_layout.h"
#include "../_layout/unit_type_class.h"
#include <stdio.h>
#include "../ui/message_list_class_methods.h"
#include "../platform/input_manager_class_methods.h"
#include "rules_class.h"
#include "../network/event_queue.h"
#include "../_layout/tactical.h"
#include "../ui/input_controls/ui_display_chain.h"

// Sidebar "tab object" globals @ 0x00B0FE5C / 0x00B0FE60. Declared-only so cl
// emits reloc-normalised absolute stores/compares.
extern TechnoClass* SidebarTabObjectA;   // 0x00B0FE5C
extern TechnoClass* SidebarTabObjectB;   // 0x00B0FE60

#include "trivial_tu256_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F5C08
extern const double DAT_007F5C08;
// GLOBAL: GAMEMD 0xB0FDF8
extern double DAT_00B0FDF8;
// GLOBAL: GAMEMD 0xB0FE30
extern double DAT_00B0FE30;
// GLOBAL: GAMEMD 0xB0FE38
extern int DAT_00B0FE38;
// GLOBAL: GAMEMD 0xB0FE3C
extern int DAT_00B0FE3C;
// GLOBAL: GAMEMD 0xB0FE40
extern int DAT_00B0FE40;
// GLOBAL: GAMEMD 0xB0FE48
extern double DAT_00B0FE48;


// STRING: GAMEMD 0x00845598
extern const char DAT_00845598[] = "D:\\ra2mdpost\\UICmnds.cpp";
// STRING: GAMEMD 0x00845584
extern const char DAT_00845584[] = "MSG:NothingSelected";
// STRING: GAMEMD 0x008455C8
extern const char DAT_008455C8[] = "MSG:SelAcrossMap";
// STRING: GAMEMD 0x008455B4
extern const char DAT_008455B4[] = "MSG:SelAcrossScreen";
// STRING: GAMEMD 0x00845638
extern const char DAT_00845638[] = "MSG:Critical";
// STRING: GAMEMD 0x00845624
extern const char DAT_00845624[] = "MSG:HeavilyDamaged";
// STRING: GAMEMD 0x00845618
extern const char DAT_00845618[] = "MSG:Healthy";
// STRING: GAMEMD 0x00887734
extern const wchar_t DAT_00887734[] = L"";

// STRING: GAMEMD 0x00845568
extern const char DAT_00845568[] = "MSG:AttackMoveUnsupported";
// STRING: GAMEMD 0x008455DC
extern const char DAT_008455DC[] = "MSG:NavEmpty";
// STRING: GAMEMD 0x008455EC
extern const char DAT_008455EC[] = "MSG:UnitsWorth";
// STRING: GAMEMD 0x008455FC
extern const char DAT_008455FC[] = "MSG:NoUnitsSel";

// STRING: GAMEMD 0x0084560C
extern const char DAT_0084560C[] = "MSG:Mixed";
// STRING: GAMEMD 0x00845648
extern const char DAT_00845648[] = "MSG:LittleExperience";
// STRING: GAMEMD 0x00845660
extern const char DAT_00845660[] = "MSG:Veteran";
// STRING: GAMEMD 0x0084566C
extern const char DAT_0084566C[] = "MSG:Elite";


//   0x732D00 via the local Ghidra disassembly.
//
// Global query leaves, ordered ascending by retail address.

#include "global_getter_family_methods.h"

#include "../platform/system_query_methods.h"

// Win32 import reached through the IAT (`CALL dword ptr [0x007E1530]`).
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

// FUNCTION: GAMEMD 0x7307B0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_007307B0()
{
    DAT_00B0FE48 = DAT_00B0FDF8 / DAT_007F5C08;
}

// FUNCTION: GAMEMD 0x7307D0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_007307D0()
{
    DAT_00B0FE30 = DAT_007E1718 / DAT_00B0FE48;
}

// FUNCTION: GAMEMD 0x730950
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_00730950()
{
    DAT_00B0FE40 = 0;
    DAT_00B0FE38 = 0x80;
    DAT_00B0FE3C = 0x80;
}

// FUNCTION: GAMEMD 0x730970
void __cdecl FUN_00730970()
{
    if (DAT_00B0FE6C) {
        delete DAT_00B0FE6C;
        DAT_00B0FE6C = 0;
    }
}

// FUNCTION: GAMEMD 0x730990
bool FUN_00730990(int group)
{
    int count = DAT_00A8EC78.Count;
    for (int i = 0; i < count; ++i) {
        TechnoClass* object = DAT_00A8EC78.Items[i];
        if (object && !object->InLimbo) {
            bool controlled = DAT_00A8B238 == 0 ? object->Owner->IsInPlayerControl : object->Owner->IsControlledByCurrentPlayer();
            if (controlled && !object->IsSelected && object->Group == group - 1)
                return false;
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x730A10
int FUN_00730A10(int group)
{
    int result = 0;
    int count = DAT_00A8EC78.Count;
    for (int i = 0; i < count; ++i) {
        TechnoClass* object = DAT_00A8EC78.Items[i];
        if (object && !object->InLimbo) {
            bool controlled = DAT_00A8B238 == 0 ? object->Owner->IsInPlayerControl : object->Owner->IsControlledByCurrentPlayer();
            if (controlled && object->Group == group - 1)
                ++result;
        }
    }
    return result;
}

// FUNCTION: GAMEMD 0x730A90
void FUN_00730A90(const wchar_t* text, int duration)
{
    if (duration == -1) duration = 240;
    int color = 3;
    if (DAT_00A83D4C) color = DAT_00A83D4C->ColorSchemeIndex;
    DAT_00A8BC60.FUN_005D3BA0(0, 0, text, color, 0x4046, duration, true);
}

// FUNCTION: GAMEMD 0x730AD0
// Returns a constant.
int __cdecl FUN_00730AD0()
{
    return 0x4046;
}

// FUNCTION: GAMEMD 0x730AE0
// Returns a constant.
int __cdecl FUN_00730AE0()
{
    return 0xF0;
}

// FUNCTION: GAMEMD 0x730AF0
void __cdecl FUN_00730AF0()
{
    bool result = false;
    if (DAT_00A8ECB8.Count <= 0) return;
    TechnoClass* first = DAT_00A8ECB8.Items[0];
    if (first && first->vf_11() == 6 && first->vf_258() > 0 && first->Owner->IsControlledByCurrentPlayer()) {
        TechnoClass* object = DAT_00A8ECB8.Items[0];
        if (!object || !object->Flags.IsTechno || !object->vf_221(9)) return;
        result = true;
    } else {
        int count = DAT_00A8ECB8.Count;
        bool deployed = false;
        bool undeployed = false;
        int i;
        for (i = 0; i < count; ++i) {
            TechnoClass* object = DAT_00A8ECB8.Items[i];
            if (!object) continue;
            bool state;
            if (object->vf_11() == 15 && static_cast<InfantryClass*>(object)->FUN_005224E0())
                state = static_cast<InfantryClass*>(object)->FUN_00522510() != 0;
            else if (object->vf_11() == 1 && static_cast<UnitTypeClass*>(static_cast<UnitClass*>(object)->Type)->IsSimpleDeployer)
                state = static_cast<UnitClass*>(object)->FUN_00746D90() != 0;
            else continue;
            if (state) { deployed = true; if (undeployed) break; }
            else { undeployed = true; if (deployed) break; }
        }
        for (i = 0; i < count; ++i) {
            TechnoClass* object = DAT_00A8ECB8.Items[i];
            if (!object || !(object->vf_40() || object->vf_39()) || !object->Flags.IsTechno ||
                !object->vf_196() || !object->vf_197() || object->Berzerk) continue;
            InfantryClass* infantry = object->vf_11() == 15 ? static_cast<InfantryClass*>(object) : 0;
            UnitClass* unit = object->vf_11() == 1 ? static_cast<UnitClass*>(object) : 0;
            if (infantry && infantry->FUN_005224E0() && deployed && undeployed && infantry->FUN_00522510()) continue;
            if (unit && static_cast<UnitTypeClass*>(unit->Type)->IsSimpleDeployer && deployed && undeployed && unit->FUN_00746D90()) continue;
            if (object->vf_221(9)) result = true;
        }
    }
    if (result) VocClass::PlayGlobal(RulesInstance->unknown_72C, 0x2000, 1.0f, 0);
}

// FUNCTION: GAMEMD 0x730D60
void __cdecl FUN_00730D60()
{
    if (FUN_00637AA0()) { FUN_0063A0D0(); return; }
    int count = DAT_00A8ECB8.Count;
    if (count > 0) {
        bool result = true;
        for (int i = 0; i < count; ++i) {
            TechnoClass* object = DAT_00A8ECB8.Items[i];
            if (object && object->Flags.IsTechno) {
                bool eligible = object->vf_40() && object->vf_39() && object->vf_11() != 6;
                if (!eligible && object->vf_11() == 1) {
                    UnitClass* unit = object->vf_11() == 1 ? static_cast<UnitClass*>(object) : 0;
                    if (unit->SlaveManager) eligible = true;
                    else {
                        unit = object->vf_11() == 1 ? static_cast<UnitClass*>(object) : 0;
                        eligible = static_cast<UnitTypeClass*>(unit->Type)->Harvester;
                    }
                }
                if (eligible) {
                    result = object->vf_222(11, object->vf_113(), 0, 0);
                    if (!result) return;
                }
            }
        }
        if (result) VocClass::PlayGlobal(RulesInstance->unknown_724, 0x2000, 1.0f, 0);
    }
}

// FUNCTION: GAMEMD 0x730EA0
void __cdecl FUN_00730EA0()
{
    int count = DAT_00A8ECB8.Count;
    if (count > 0) {
        bool result = true;
        for (int i = 0; i < count; ++i) {
            TechnoClass* object = DAT_00A8ECB8.Items[i];
            if (object && object->Flags.IsTechno && (object->vf_40() || object->vf_39())) {
                result = object->vf_221(6);
                if (!result) return;
            }
        }
        if (result) VocClass::PlayGlobal(RulesInstance->unknown_728, 0x2000, 1.0f, 0);
    }
}

// FUNCTION: GAMEMD 0x730F30
void __cdecl FUN_00730F30()
{
    if (DAT_00A8B538 == 0 && RulesInstance->unknown_580 + DAT_0084555C < CurrentFrame) {
        EventClass event(DAT_00A83D4C->ArrayIndex, 0x2D);
        if (DAT_00A802C8.Count < 128) {
            DAT_00A802C8.List[DAT_00A802C8.Head] = event;
            DAT_00A802C8.Time[DAT_00A802C8.Head] = timeGetTime();
            DAT_00A802C8.Head = (DAT_00A802C8.Head + 1) & 127;
            ++DAT_00A802C8.Count;
        }
        DAT_0084555C = CurrentFrame;
    }
}

// FUNCTION: GAMEMD 0x730FE0
void __cdecl FUN_00730FE0()
{
    int count = DAT_00A8ECB8.Count;
    if (count > 0) {
        bool result = true;
        for (int i = 0; i < count; ++i) {
            TechnoClass* object = DAT_00A8ECB8.Items[i];
            if (object && object->Flags.IsTechno && object->vf_40()) {
                result = object->vf_221(7);
                if (!result) return;
            }
        }
        if (result) VocClass::PlayGlobal(RulesInstance->unknown_728, 0x2000, 1.0f, 0);
    }
}

// FUNCTION: GAMEMD 0x731060
void FUN_00731060(int group)
{
    int count = DAT_00A8EC78.Count;
    for (int i = 0; i < count; ++i) {
        TechnoClass* object = DAT_00A8EC78.Items[i];
        if (object) {
            bool controlled = DAT_00A8B238 == 0 ? object->Owner->IsInPlayerControl : object->Owner->IsControlledByCurrentPlayer();
            if (controlled) {
                if (object->Group == group - 1) object->Group = -1;
                if (object->IsSelected) object->Group = group - 1;
            }
        }
    }
}

// FUNCTION: GAMEMD 0x7310D0
void FUN_007310D0(int group)
{
    int count = DAT_00A8EC78.Count;
    for (int i = 0; i < count; ++i) {
        TechnoClass* object = DAT_00A8EC78.Items[i];
        if (object) {
            bool controlled = DAT_00A8B238 == 0 ? object->Owner->IsInPlayerControl : object->Owner->IsControlledByCurrentPlayer();
            if (controlled && object->Group == group - 1)
                object->Group = -1;
        }
    }
}

// FUNCTION: GAMEMD 0x731130
bool FUN_00731130(int group)
{
    for (int i = DAT_00A8EC78.Count - 1; i >= 0; --i) {
        TechnoClass* object = DAT_00A8EC78.Items[i];
        if (object && !object->InLimbo) {
            bool controlled = DAT_00A8B238 == 0 ? object->Owner->IsInPlayerControl : object->Owner->IsControlledByCurrentPlayer();
            if (controlled) {
                if (object->Group == group - 1 && !object->IsSelected) return false;
                if (object->Group != group - 1 && object->IsSelected) return false;
            }
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x7313A0
void FUN_007313A0(int group)
{
    Map_0087F7E8.SetPowerMode_004AC820(0);
    Map_0087F7E8.SetWaypointMode_004AC700(0, 0);
    Map_0087F7E8.SetRepairMode_004AC8C0(0);
    Map_0087F7E8.SetSellMode_004AC660(0);
    Map_0087F7E8.SetBeaconMode_004AC960(0);
    if (DAT_00A8ECB8.Count && (!DAT_00A8ECB8.Items[0] || !DAT_00A8ECB8.Items[0]->Flags.IsFoot || DAT_00A8ECB8.Items[0]->Group != group - 1))
        DAT_00887324->FUN_006DA740();
    for (int i = 0; i < DAT_00A8EC78.Count; ++i) {
        TechnoClass* object = DAT_00A8EC78.Items[i];
        if (object && !object->InLimbo && object->Group == group - 1) {
            bool controlled = DAT_00A8B238 == 0 ? object->Owner->IsInPlayerControl : object->Owner->IsControlledByCurrentPlayer();
            if (controlled && !object->IsSelected) {
                object->vf_83();
                DAT_00822CF2 = false;
            }
        }
    }
    Map_0087F7E8.FUN_004AE290();
    Map_0087F7E8.GScreenClass::FlagToRedraw(1);
    DAT_00822CF2 = true;
}

// FUNCTION: GAMEMD 0x7314C0
void FUN_007314C0(int group)
{
    Map_0087F7E8.SetPowerMode_004AC820(0);
    Map_0087F7E8.SetWaypointMode_004AC700(0, 0);
    Map_0087F7E8.SetRepairMode_004AC8C0(0);
    Map_0087F7E8.SetSellMode_004AC660(0);
    Map_0087F7E8.SetBeaconMode_004AC960(0);
    DAT_00822CF2 = true;
    for (int i = 0; i < DAT_00A8EC78.Count; ++i) {
        TechnoClass* object = DAT_00A8EC78.Items[i];
        if (object && !object->InLimbo && object->Group == group - 1) {
            bool controlled = DAT_00A8B238 == 0 ? object->Owner->IsInPlayerControl : object->Owner->IsControlledByCurrentPlayer();
            if (controlled && !object->IsSelected) {
                object->vf_83();
                DAT_00822CF2 = false;
            }
        }
    }
    DAT_00822CF2 = true;
}

// FUNCTION: GAMEMD 0x7315A0
void __cdecl FUN_007315A0()
{
    CoordStruct first = DAT_00B0FE10;
    CoordStruct second = DAT_00B0FE10;
    bool found = false;
    for (int i = DAT_00A83D4C->Buildings.Count - 1; i >= 0; --i) {
        BuildingClass* object = static_cast<BuildingClass**>(DAT_00A83D4C->Buildings.Items)[i];
        if (object && !object->InLimbo) {
            if (object->Type->bools_16A4[0x15]) {
                second = object->vf_18();
                if (object->IsPrimaryFactory) break;
            } else if (first.X == DAT_00B0FE10.X && first.Y == DAT_00B0FE10.Y && first.Z == DAT_00B0FE10.Z) {
                first = object->vf_18();
            }
        }
    }
    if (first.X == DAT_00B0FE10.X && first.Y == DAT_00B0FE10.Y && first.Z == DAT_00B0FE10.Z &&
        second.X == DAT_00B0FE10.X && second.Y == DAT_00B0FE10.Y && second.Z == DAT_00B0FE10.Z && DAT_00A83D4C->OwnedUnits) {
        for (int i = DAT_008B4108.Count - 1; i >= 0 && !found; --i) {
            UnitClass* object = DAT_008B4108.Items[i];
            if (object && !object->InLimbo && object->Owner->IsControlledByCurrentPlayer()) {
                for (int j = 0; j < RulesInstance->unknown_B20.Count; ++j)
                    if (RulesInstance->unknown_B20.Items[j] == object->Type) { second = object->vf_18(); found = true; break; }
            }
        }
    }
    CoordStruct center = DAT_00A83D4C->FUN_0050DF30();
    if ((center.X != DAT_00B0FE10.X || center.Y != DAT_00B0FE10.Y || center.Z != DAT_00B0FE10.Z) &&
        (center.X != DAT_00B0FE38 || center.Y != DAT_00B0FE3C || center.Z != DAT_00B0FE40)) first = center;
    if (second.X != DAT_00B0FE10.X || second.Y != DAT_00B0FE10.Y || second.Z != DAT_00B0FE10.Z)
        DAT_00887324->FUN_006D6070(&second);
    else if (first.X != DAT_00B0FE10.X || first.Y != DAT_00B0FE10.Y || first.Z != DAT_00B0FE10.Z)
        DAT_00887324->FUN_006D6070(&first);
    CellStruct cell;
    if (DAT_00880990) Map_0087F7E8.FUN_004A91B0(&cell, &DAT_00B0FDF0);
    Map_0087F7E8.FUN_004AEB30(0);
    Map_0087F7E8.GScreenClass::FlagToRedraw(1);
}

// FUNCTION: GAMEMD 0x731840
void FUN_00731840(int data)
{
    if (DAT_00A8B238 != 0 && !(*DAT_00A8B230 & 0x400) && RulesInstance->unknown_14B5 && RulesInstance->unknown_14BB) {
        EventClass event(DAT_00A83D4C->ArrayIndex, 3, data);
        if (DAT_00A802C8.Count < 128) {
            DAT_00A802C8.List[DAT_00A802C8.Head] = event;
            DAT_00A802C8.Time[DAT_00A802C8.Head] = timeGetTime();
            DAT_00A802C8.Head = (DAT_00A802C8.Head + 1) & 127;
            ++DAT_00A802C8.Count;
        }
    }
}

// FUNCTION: GAMEMD 0x7318F0
void __cdecl FUN_007318F0()
{
    if (DAT_00A8ECB8.Count && !DAT_00A83D4C->Defeated &&
        reinterpret_cast<HouseClass*>(DAT_00A8ECB8.Items[0]->vf_15()) != DAT_00A83D4C &&
        reinterpret_cast<HouseClass*>(DAT_00A8ECB8.Items[0]->vf_15())->IsHumanPlayer) {
        int id = DAT_00A8ECB8.Items[0]->vf_14();
        if (DAT_00A8B238 && !(*DAT_00A8B230 & 0x400) && RulesInstance->unknown_14B5 && RulesInstance->unknown_14BB) {
            EventClass event(DAT_00A83D4C->ArrayIndex, 3, id);
            if (DAT_00A802C8.Count < 128) {
                DAT_00A802C8.List[DAT_00A802C8.Head] = event;
                DAT_00A802C8.Time[DAT_00A802C8.Head] = timeGetTime();
                DAT_00A802C8.Head = (DAT_00A802C8.Head + 1) & 127;
                ++DAT_00A802C8.Count;
            }
        }
    }
}

// FUNCTION: GAMEMD 0x731A10
void __cdecl FUN_00731A10()
{
    PlanningNodeClass* node = reinterpret_cast<PlanningNodeClass*>(FUN_0063AC60());
    if (node) node->FUN_00637D00();
    else DAT_0089C3B0.DeleteBeacon(-1, -1);
}

// FUNCTION: GAMEMD 0x731A30
// Branching.
void FUN_00731A30(int a1, int a2)
{
    if (DAT_00A8B538 == 0)
    {
        FUN_004AC960(DAT_0087F7E8, a2, -1);
    }
}

// FUNCTION: GAMEMD 0x731A50
void FUN_00731A50(bool value)
{
    if (DAT_00A8B538 == 0) {
        FUN_006379C0();
        FUN_0063A120(value, true);
    }
}

// FUNCTION: GAMEMD 0x731A70
void FUN_00731A70(bool value)
{
    FUN_00637A10();
    if (DAT_00A8B538 == 0)
        FUN_0063A120(value, false);
}

// FUNCTION: GAMEMD 0x731A90
// Tail-forwards to another function.
void __cdecl FUN_00731A90()
{
    FUN_00637AA0();
}

// FUNCTION: GAMEMD 0x731AA0
bool __cdecl FUN_00731AA0()
{
    int count = DAT_00A8ECB8.Count;
    for (int i = 0; i < count; ++i) {
        TechnoClass* object = DAT_00A8ECB8.Items[i];
        if (object && object->Flags.IsTechno && !object->CanAttackOnTheMove())
            return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x731AF0
void __cdecl FUN_00731AF0()
{
    int count = DAT_00A8ECB8.Count;
    if (!count) {
        const wchar_t* text = FUN_00734E60(DAT_00845584, 0, DAT_00845598, 0x358);
        int color = 3;
        if (DAT_00A83D4C) color = DAT_00A83D4C->ColorSchemeIndex;
        DAT_00A8BC60.FUN_005D3BA0(0, 0, text, color, 0x4046, 240, true);
    } else {
        for (int i = 0; i < count; ++i) {
            TechnoClass* object = DAT_00A8ECB8.Items[i];
            if (object && object->Flags.IsTechno && !object->CanAttackOnTheMove()) {
                const wchar_t* text = FUN_00734E60(DAT_00845568, 0, DAT_00845598, 0x35E);
                int color = 3;
                if (DAT_00A83D4C) color = DAT_00A83D4C->ColorSchemeIndex;
                DAT_00A8BC60.FUN_005D3BA0(0, 0, text, color, 0x4046, 240, true);
                return;
            }
        }
    }
    DAT_00B0FE58 = 1;
}

// FUNCTION: GAMEMD 0x731BE0
// Stores to a global.
void __cdecl FUN_00731BE0()
{
    DAT_00B0FE58 = 0;
}

// FUNCTION: GAMEMD 0x731BF0
bool __cdecl FUN_00731BF0()
{
    if (DAT_00B0FE58) return true;
    bool first = DAT_0087F770->IsKeyPressed(DAT_00A8EC00) || DAT_0087F770->IsKeyPressed(DAT_00A8EC04);
    bool second = DAT_0087F770->IsKeyPressed(DAT_00A8EC08) || DAT_0087F770->IsKeyPressed(DAT_00A8EC0C);
    if (!first || !second) return false;
    int count = DAT_00A8ECB8.Count;
    for (int i = 0; i < count; ++i) {
        TechnoClass* object = DAT_00A8ECB8.Items[i];
        if (object && object->Flags.IsTechno && !object->CanAttackOnTheMove()) return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x00731CB0
int FUN_00731CB0()
{
    return (int)&DAT_00000047;
}

// FUNCTION: GAMEMD 0x00731CC0
int FUN_00731CC0()
{
    return (int)&DAT_00000016;
}

// FUNCTION: GAMEMD 0x731CF0
// Stores to a global.
void __cdecl FUN_00731CF0()
{
    DAT_00B0FE58 = 0;
}

// FUNCTION: GAMEMD 0x731D10
void FUN_00731D10(wchar_t* text)
{
    if (DAT_00A8ECB8.Count == 0) {
        wcscpy(text, FUN_00734E60(DAT_00845584, 0, DAT_00845598, 0x3F1));
    } else if (DAT_00B0FE64) {
        wcscpy(text, FUN_00734E60(DAT_008455C8, 0, DAT_00845598, 0x3F3));
    } else {
        wcscpy(text, FUN_00734E60(DAT_008455B4, 0, DAT_00845598, 0x3F5));
    }
}

// FUNCTION: GAMEMD 0x731D90
void FUN_00731D90(wchar_t* text, const wchar_t* value)
{
    if (DAT_00B0FE6C->Count && value) {
        wchar_t buffer[100];
        wcscpy(buffer, value);
        FUN_007DDCD6(buffer);
        int count = DAT_00A8ECB8.Count;
        if (!count) {
            swprintf(text, FUN_00734E60(DAT_008455FC, 0, DAT_00845598, 0x408), buffer);
            return;
        }
        int total = 0;
        for (int i = 0; i < count; ++i) {
            TechnoClass* object = DAT_00A8ECB8.Items[i];
            if (object && object->Flags.IsTechno)
                // The canonical slot still has an opaque int argument; retail
                // 0x731E2B/0x731E3B passes the 32-bit Owner pointer there.
                total += object->vf_34()->vf_33(reinterpret_cast<int>(object->Owner));
        }
        swprintf(text, FUN_00734E60(DAT_008455EC, 0, DAT_00845598, 0x41C), count, buffer, total);
    } else {
        wcscpy(text, FUN_00734E60(DAT_008455DC, 0, DAT_00845598, 0x3FE));
    }
}

// FUNCTION: GAMEMD 0x731EB0
UICmndsVector* FUN_00731EB0(bool (__fastcall *predicate)(TechnoClass*, void*), void* context)
{
    UICmndsVector* result = new UICmndsVector;
    int count = DAT_00A8EC78.Count;
    for (int i = 0; i < count; ++i) {
        TechnoClass* object = DAT_00A8EC78.Items[i];
        if (predicate(object, context)) result->AddItem(object);
    }
    return result;
}

// FUNCTION: GAMEMD 0x731F70
UICmndsVector* FUN_00731F70(bool (__fastcall *predicate)(TechnoClass*, void*), void* context)
{
    UICmndsVector* result = new UICmndsVector;
    int count = DAT_00887324->FUN_006DC420();
    for (int i = 0; i < count; ++i) {
        ObjectClass* object = DAT_00887324->FUN_006DC430(i);
        if (object && object->Flags.IsTechno) {
            TechnoClass* techno = static_cast<TechnoClass*>(object);
            if (predicate(techno, context)) result->AddItem(techno);
        }
    }
    return result;
}

// FUNCTION: GAMEMD 0x732050
UICmndsVector* __cdecl FUN_00732050()
{
    UICmndsVector* result = new UICmndsVector;
    int count = DAT_00A8ECB8.Count;
    for (int i = 0; i < count; ++i) {
        TechnoClass* object = DAT_00A8ECB8.Items[i];
        if (object && object->Flags.IsTechno) result->AddItem(object);
    }
    return result;
}

// FUNCTION: GAMEMD 0x732110
void FUN_00732110(UICmndsVector* list, void (__fastcall *callback)(TechnoClass*, void*), void* context)
{
    int count = list->Count;
    for (int i = 0; i < count; ++i)
        callback(list->Items[i], context);
}

// FUNCTION: GAMEMD 0x732140
void FUN_00732140(UICmndsVector* list, bool (__fastcall *predicate)(TechnoClass*, void*),
                 void (__fastcall *callback)(TechnoClass*, void*), void* condition, void* context)
{
    int count = list->Count;
    for (int i = 0; i < count; ++i) {
        TechnoClass* object = list->Items[i];
        if (predicate(object, condition)) callback(object, context);
    }
}

// FUNCTION: GAMEMD 0x732190
bool FUN_00732190(UICmndsVector* list, bool (__fastcall *callback)(TechnoClass*, void*), void* context)
{
    int count = list->Count;
    for (int i = 0; i < count; ++i)
        if (!callback(list->Items[i], context)) return false;
    return true;
}

// FUNCTION: GAMEMD 0x7321D0
bool FUN_007321D0(UICmndsVector* list, bool (__fastcall *callback)(TechnoClass*, void*), void* context)
{
    int count = list->Count;
    for (int i = 0; i < count; ++i)
        if (callback(list->Items[i], context)) return true;
    return false;
}

// FUNCTION: GAMEMD 0x732210
int FUN_00732210(DynamicVectorClass<const char*>* list, const char* text)
{
    int count = list->Count;
    for (int i = 0; i < count; ++i)
        if (strcmp(text, list->Items[i]) == 0) return i;
    return -1;
}

// FUNCTION: GAMEMD 0x732280
void FUN_00732280(bool clear)
{
    if (DAT_00A8B538) return;
    DAT_00887324->FUN_006DA770();
    if (DAT_00B0FE54 != 1) DAT_00B0FE64 = 0;
    UICmndsVector* list = new UICmndsVector;
    int i;
    if (DAT_00B0FE64) {
        int count = DAT_00A8EC78.Count;
        for (i = 0; i < count; ++i) {
            TechnoClass* object = DAT_00A8EC78.Items[i];
            if (FUN_00732580(object)) list->AddItem(object);
        }
    } else {
        int count = DAT_00887324->FUN_006DC420();
        for (i = 0; i < count; ++i) {
            ObjectClass* object = DAT_00887324->FUN_006DC430(i);
            if (FUN_007342C0(object)) {
                TechnoClass* techno = static_cast<TechnoClass*>(object);
                if (FUN_00732580(techno)) list->AddItem(techno);
            }
        }
        bool found = false;
        count = list->Count;
        for (i = 0; i < count; ++i) {
            TechnoClass* object = list->Items[i];
            if (object->vf_11() != 6 && object->vf_33()->IsSelectableCombatant && object->vf_79() && !object->IsSelected) {
                found = true;
                break;
            }
        }
        if (!found) DAT_00B0FE64 = 1;
        if (DAT_00B0FE64) {
            delete list;
            list = new UICmndsVector;
            count = DAT_00A8EC78.Count;
            for (i = 0; i < count; ++i) {
                TechnoClass* object = DAT_00A8EC78.Items[i];
                if (FUN_00732580(object)) list->AddItem(object);
            }
        }
    }
    if (clear) DAT_00887324->FUN_006DA740();
    int count = list->Count;
    for (i = 0; i < count; ++i) {
        TechnoClass* object = list->Items[i];
        if (FUN_007325C0(object)) object->vf_83();
    }
    const wchar_t* text;
    if (DAT_00A8ECB8.Count == 0) text = FUN_00734E60(DAT_00845584, 0, DAT_00845598, 0x3F1);
    else if (!DAT_00B0FE64) text = FUN_00734E60(DAT_008455B4, 0, DAT_00845598, 0x3F5);
    else text = FUN_00734E60(DAT_008455C8, 0, DAT_00845598, 0x3F3);
    wchar_t buffer[256];
    wcscpy(buffer, text);
    int color = 3;
    if (DAT_00A83D4C) color = DAT_00A83D4C->ColorSchemeIndex;
    DAT_00A8BC60.FUN_005D3BA0(0, 0, buffer, color, 0x4046, 240, true);
    delete list;
    DAT_00B0FE58 = 0;
    DAT_00B0FE54 = 1;
}

// FUNCTION: GAMEMD 0x732580
int FUN_00732580(TechnoClass* object)
{
    if (object && object->IsAlive) {
        bool controlled = DAT_00A8B238 == 0 ? object->Owner->IsInPlayerControl : object->Owner->IsControlledByCurrentPlayer();
        if (controlled) return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7325C0
int FUN_007325C0(TechnoClass* object)
{
    if (object->vf_11() != 6 && object->vf_33()->IsSelectableCombatant && object->vf_79())
        return 1;
    return 0;
}

// FUNCTION: GAMEMD 0x732600
void FUN_00732600(const char* text)
{
    UICmndsVector* list = new UICmndsVector;
    if (DAT_00B0FE64) {
        int count = DAT_00A8EC78.Count;
        for (int i = 0; i < count; ++i) {
            TechnoClass* object = DAT_00A8EC78.Items[i];
            if (FUN_00732770(object, text)) list->AddItem(object);
        }
    } else {
        int count = DAT_00887324->FUN_006DC420();
        for (int i = 0; i < count; ++i) {
            ObjectClass* object = DAT_00887324->FUN_006DC430(i);
            if (object && object->Flags.IsTechno) {
                TechnoClass* techno = static_cast<TechnoClass*>(object);
                if (FUN_00732770(techno, text)) list->AddItem(techno);
            }
        }
    }
    int count = list->Count;
    for (int i = 0; i < count; ++i) list->Items[i]->vf_84();
    delete list;
}

// FUNCTION: GAMEMD 0x732770
int FUN_00732770(TechnoClass* object, const char* text)
{
    if (object && object->IsAlive) {
        bool controlled = DAT_00A8B238 == 0 ? object->Owner->IsInPlayerControl : object->Owner->IsControlledByCurrentPlayer();
        if (controlled && object->FUN_005F3E50(text)) return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7327D0
void FUN_007327D0(const char* text)
{
    bool saved = DAT_00822CF2;
    DAT_00822CF2 = false;
    UICmndsVector* list = new UICmndsVector;
    if (DAT_00B0FE64) {
        int count = DAT_00A8EC78.Count;
        for (int i = 0; i < count; ++i) {
            TechnoClass* object = DAT_00A8EC78.Items[i];
            if (FUN_00732770(object, text)) list->AddItem(object);
        }
    } else {
        int count = DAT_00887324->FUN_006DC420();
        for (int i = 0; i < count; ++i) {
            ObjectClass* object = DAT_00887324->FUN_006DC430(i);
            if (object && object->Flags.IsTechno) {
                TechnoClass* techno = static_cast<TechnoClass*>(object);
                if (FUN_00732770(techno, text)) list->AddItem(techno);
            }
        }
    }
    int count = list->Count;
    for (int i = 0; i < count; ++i) list->Items[i]->vf_83();
    delete list;
    DAT_00822CF2 = saved;
}

// FUNCTION: GAMEMD 0x732950
void __cdecl FUN_00732950()
{
    if (DAT_00A8B538) return;
    DAT_00887324->FUN_006DA770();
    if (DAT_00B0FE54 != 2) DAT_00B0FE64 = 0;
    DynamicVectorClass<const char*>* types = FUN_00732D10();
    UICmndsVector* list = new UICmndsVector;
    int i;
    if (DAT_00B0FE64) {
        int count = DAT_00A8EC78.Count;
        for (i = 0; i < count; ++i) {
            TechnoClass* object = DAT_00A8EC78.Items[i];
            if (FUN_00732580(object)) list->AddItem(object);
        }
    } else {
        int count = DAT_00887324->FUN_006DC420();
        for (i = 0; i < count; ++i) {
            ObjectClass* object = DAT_00887324->FUN_006DC430(i);
            if (FUN_007342C0(object)) {
                TechnoClass* techno = static_cast<TechnoClass*>(object);
                if (FUN_00732580(techno)) list->AddItem(techno);
            }
        }
        bool found = false;
        count = list->Count;
        for (i = 0; i < count; ++i) {
            TechnoClass* object = list->Items[i];
            if (FUN_00732C30(object, types) && !object->IsSelected) { found = true; break; }
        }
        if (!found) DAT_00B0FE64 = 1;
        if (DAT_00B0FE64) {
            delete list;
            list = new UICmndsVector;
            count = DAT_00A8EC78.Count;
            for (i = 0; i < count; ++i) {
                TechnoClass* object = DAT_00A8EC78.Items[i];
                if (FUN_00732580(object)) list->AddItem(object);
            }
        }
    }
    int count = list->Count;
    for (i = 0; i < count; ++i) {
        TechnoClass* object = list->Items[i];
        if (FUN_00732C30(object, types)) object->vf_83();
    }
    const wchar_t* text;
    if (!DAT_00A8ECB8.Count) text = FUN_00734E60(DAT_00845584, 0, DAT_00845598, 0x3F1);
    else if (!DAT_00B0FE64) text = FUN_00734E60(DAT_008455B4, 0, DAT_00845598, 0x3F5);
    else text = FUN_00734E60(DAT_008455C8, 0, DAT_00845598, 0x3F3);
    wchar_t buffer[256];
    wcscpy(buffer, text);
    int color = 3;
    if (DAT_00A83D4C) color = DAT_00A83D4C->ColorSchemeIndex;
    DAT_00A8BC60.FUN_005D3BA0(0, 0, buffer, color, 0x4046, 240, true);
    DAT_00B0FE54 = 2;
    DAT_00B0FE58 = 0;
    delete types;
    delete list;
}

// FUNCTION: GAMEMD 0x732C30
bool FUN_00732C30(TechnoClass* object, DynamicVectorClass<const char*>* list)
{
    int count = list->Count;
    for (int i = 0; i < count; ++i) {
        if (object->FUN_005F3E50(list->Items[i])) {
            if (object->vf_79()) return 1;
            if (object && object->vf_11() == 6 && object->vf_33()->UndeploysInto) return 1;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x732CA0
// Branching.
void __cdecl FUN_00732CA0()
{
    if (DAT_00B0FE65 == 0)
    {
        unsigned char t1 = DAT_00B0FE65;
        DAT_00B0FE65 = 1;
        int c0 = timeGetTime();
        DAT_00B0FE68 = c0;
    }
}


// FUNCTION: GAMEMD 0x732CC0
void __cdecl FUN_00732CC0()
{
    if (DAT_00B0FE65) {
        DAT_00B0FE65 = 0;
        if (abs(int(timeGetTime() - DAT_00B0FE68)) <= 500) {
            FUN_00732950();
            Map_0087F7E8.GScreenClass::FlagToRedraw(1);
        }
    }
}

// FUNCTION: GAMEMD 0x732D00  Unsorted::IsTypeSelecting (__fastcall)
bool Unsorted_IsTypeSelecting()
{
    return IsTypeSelectingFlag;
}

// FUNCTION: GAMEMD 0x732D10
DynamicVectorClass<const char*>* __cdecl FUN_00732D10()
{
    DynamicVectorClass<const char*>* result = new DynamicVectorClass<const char*>;
    int count = DAT_00A8ECB8.Count;
    for (int i = 0; i < count; ++i) {
        TechnoClass* object = DAT_00A8ECB8.Items[i];
        const char* text = object->vf_34()->ID;
        int j;
        for (j = 0; j < result->Count; ++j)
            if (strcmp(text, result->Items[j]) == 0) break;
        if (j < result->Count && j != -1) continue;
        result->AddItem(text);
        if (object->vf_33()->DeploysInto) {
            text = object->vf_33()->DeploysInto->ID;
            for (j = 0; j < result->Count; ++j)
                if (strcmp(text, result->Items[j]) == 0) break;
            if (j == result->Count || j == -1) result->AddItem(text);
        }
        if (object->vf_33()->UndeploysInto) {
            text = object->vf_33()->UndeploysInto->ID;
            for (j = 0; j < result->Count; ++j)
                if (strcmp(text, result->Items[j]) == 0) break;
            if (j == result->Count || j == -1) result->AddItem(text);
        }
    }
    return result;
}

// FUNCTION: GAMEMD 0x732FF0
void FUN_00732FF0(void (__fastcall *callback)(TechnoClass*, void*), const char* text, void* context)
{
    UICmndsVector* list = new UICmndsVector;
    if (DAT_00B0FE64) {
        int count = DAT_00A8EC78.Count;
        for (int i = 0; i < count; ++i) {
            TechnoClass* object = DAT_00A8EC78.Items[i];
            if (FUN_00732770(object, text)) list->AddItem(object);
        }
    } else {
        int count = DAT_00887324->FUN_006DC420();
        for (int i = 0; i < count; ++i) {
            ObjectClass* object = DAT_00887324->FUN_006DC430(i);
            if (object && object->Flags.IsTechno) {
                TechnoClass* techno = static_cast<TechnoClass*>(object);
                if (FUN_00732770(techno, text)) list->AddItem(techno);
            }
        }
    }
    int count = list->Count;
    for (int i = 0; i < count; ++i) callback(list->Items[i], context);
    delete list;
}

// FUNCTION: GAMEMD 0x733160
void FUN_00733160(TechnoClass* object)
{
    if (DAT_00B0FE6C) {
        for (int i = DAT_00B0FE6C->Count - 1; i >= 0; --i) {
            if (DAT_00B0FE6C->Items[i] == object) {
                DAT_00B0FE6C->Delete(i);
                return;
            }
        }
    }
}

// FUNCTION: GAMEMD 0x7331B0
void __cdecl FUN_007331B0()
{
    if (DAT_00B0FE6C) { delete DAT_00B0FE6C; DAT_00B0FE6C = 0; }
    UICmndsVector* list = new UICmndsVector;
    int count = DAT_00A8ECB8.Count;
    for (int i = 0; i < count; ++i) {
        TechnoClass* object = DAT_00A8ECB8.Items[i];
        if (object && object->Flags.IsTechno) list->AddItem(object);
    }
    if (list->Count == 0) {
        DAT_00B0FE6C = list;
        delete list;
        DAT_00B0FE6C = 0;
        list = new UICmndsVector;
        int count = DAT_00887324->FUN_006DC420();
        for (int i = 0; i < count; ++i) {
            ObjectClass* object = DAT_00887324->FUN_006DC430(i);
            if (object && object->Flags.IsTechno) {
                TechnoClass* techno = static_cast<TechnoClass*>(object);
                if (techno->IsAlive) {
                    bool controlled = DAT_00A8B238 == 0 ? techno->Owner->IsInPlayerControl : techno->Owner->IsControlledByCurrentPlayer();
                    if (controlled && techno->vf_11() != 6) list->AddItem(techno);
                }
            }
        }
    }
    DAT_00B0FE6C = list;
}

// FUNCTION: GAMEMD 0x733380
void FUN_00733380(bool clear)
{
    if (DAT_00A8B538) return;
    int state;
    if (DAT_00B0FE54 == 3) {
        if (DAT_00845560 == -1) state = 0;
        else if (DAT_00845560 == 0) state = 1;
        else state = DAT_00845560 == 1 ? 2 : 0;
        if (clear) DAT_00887324->FUN_006DA740();
    } else {
        if (DAT_00B0FE6C) { delete DAT_00B0FE6C; DAT_00B0FE6C = 0; }
        DAT_00B0FE6C = FUN_00732050();
        if (DAT_00B0FE6C->Count == 0) {
            delete DAT_00B0FE6C;
            DAT_00B0FE6C = 0;
            // Retail passes 0x7335F0 as a callback at this callsite. The
            // target returns EAX 0/1 and ignores EDX; 0x731F70 consumes AL.
            // This cast adapts that observed callback ABI to its shared type.
            DAT_00B0FE6C = FUN_00731F70(reinterpret_cast<bool (__fastcall *)(TechnoClass*, void*)>(FUN_007335F0), 0);
        }
        DAT_00887324->FUN_006DA740();
        state = 0;
    }
    int count = DAT_00B0FE6C->Count;
    int i;
    for (i = 0; i < count; ++i) {
        TechnoClass* object = DAT_00B0FE6C->Items[i];
        if (object->GetHealthStatus() == state) object->vf_83();
    }
    const wchar_t* text = 0;
    if (state == 0) text = FUN_00734E60(DAT_00845638, 0, DAT_00845598, 0x644);
    else if (state == 1) text = FUN_00734E60(DAT_00845624, 0, DAT_00845598, 0x646);
    else if (state == 2) text = FUN_00734E60(DAT_00845618, 0, DAT_00845598, 0x648);
    UICmndsVector* selected = new UICmndsVector;
    count = DAT_00A8ECB8.Count;
    for (i = 0; i < count; ++i) {
        TechnoClass* object = DAT_00A8ECB8.Items[i];
        if (object && object->Flags.IsTechno) selected->AddItem(object);
    }
    count = selected->Count;
    for (i = 0; i < count; ++i) {
        TechnoClass* object = selected->Items[i];
        if (object->GetHealthStatus() != state) { text = FUN_00734E60(DAT_0084560C, 0, DAT_00845598, 0x62f); break; }
    }
    delete selected;
    wchar_t buffer[256];
    FUN_00731D90(buffer, text);
    int color = 3;
    if (DAT_00A83D4C) color = DAT_00A83D4C->ColorSchemeIndex;
    DAT_00A8BC60.FUN_005D3BA0(0, 0, buffer, color, 0x4046, 240, true);
    DAT_00845560 = state;
    DAT_00B0FE54 = DAT_00B0FE6C->Count ? 3 : 0;
    DAT_00B0FE58 = 0;
}

// FUNCTION: GAMEMD 0x7335F0
int FUN_007335F0(TechnoClass* object)
{
    if (object && object->IsAlive) {
        bool controlled = DAT_00A8B238 == 0 ? object->Owner->IsInPlayerControl : object->Owner->IsControlledByCurrentPlayer();
        if (controlled && object->vf_11() != 6) return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x733640
const wchar_t* FUN_00733640(int value)
{
    if (value == 0) return FUN_00734E60(DAT_00845638, 0, DAT_00845598, 0x644);
    if (value == 1) return FUN_00734E60(DAT_00845624, 0, DAT_00845598, 0x646);
    if (value == 2) return FUN_00734E60(DAT_00845618, 0, DAT_00845598, 0x648);
    return DAT_00887734;
}

// FUNCTION: GAMEMD 0x7336A0
int FUN_007336A0(int value)
{
    if (value == -1) return 0;
    if (value == 0) return 1;
    return value == 1 ? 2 : 0;
}

// FUNCTION: GAMEMD 0x7336C0
void FUN_007336C0(bool clear)
{
    if (DAT_00A8B538) return;
    int state;
    if (DAT_00B0FE54 == 4) {
        if (DAT_00845564 == -1) state = 0;
        else if (DAT_00845564 == 0) state = 1;
        else state = DAT_00845564 == 1 ? 2 : 0;
        if (clear) DAT_00887324->FUN_006DA740();
    } else {
        if (DAT_00B0FE6C) { delete DAT_00B0FE6C; DAT_00B0FE6C = 0; }
        DAT_00B0FE6C = FUN_00732050();
        if (DAT_00B0FE6C->Count == 0) {
            delete DAT_00B0FE6C;
            DAT_00B0FE6C = 0;
            // Retail passes 0x7335F0 as a callback at this callsite. The
            // target returns EAX 0/1 and ignores EDX; 0x731F70 consumes AL.
            // This cast adapts that observed callback ABI to its shared type.
            DAT_00B0FE6C = FUN_00731F70(reinterpret_cast<bool (__fastcall *)(TechnoClass*, void*)>(FUN_007335F0), 0);
        }
        DAT_00887324->FUN_006DA740();
        state = 0;
    }
    int count = DAT_00B0FE6C->Count;
    int i;
    for (i = 0; i < count; ++i) {
        TechnoClass* object = DAT_00B0FE6C->Items[i];
        if (object->Veterancy.FUN_00750030() == state) object->vf_83();
    }
    const wchar_t* text = 0;
    if (state == 0) text = FUN_00734E60(DAT_0084566C, 0, DAT_00845598, 0x68e);
    else if (state == 1) text = FUN_00734E60(DAT_00845660, 0, DAT_00845598, 0x690);
    else if (state == 2) text = FUN_00734E60(DAT_00845648, 0, DAT_00845598, 0x692);
    UICmndsVector* selected = new UICmndsVector;
    count = DAT_00A8ECB8.Count;
    for (i = 0; i < count; ++i) {
        TechnoClass* object = DAT_00A8ECB8.Items[i];
        if (object && object->Flags.IsTechno) selected->AddItem(object);
    }
    count = selected->Count;
    for (i = 0; i < count; ++i) {
        TechnoClass* object = selected->Items[i];
        if (object->Veterancy.FUN_00750030() != state) { text = FUN_00734E60(DAT_0084560C, 0, DAT_00845598, 0x67a); break; }
    }
    delete selected;
    wchar_t buffer[256];
    FUN_00731D90(buffer, text);
    int color = 3;
    if (DAT_00A83D4C) color = DAT_00A83D4C->ColorSchemeIndex;
    DAT_00A8BC60.FUN_005D3BA0(0, 0, buffer, color, 0x4046, 240, true);
    DAT_00845564 = state;
    DAT_00B0FE54 = DAT_00B0FE6C->Count ? 4 : 0;
    DAT_00B0FE58 = 0;
}

// FUNCTION: GAMEMD 0x733990
int FUN_00733990(int value)
{
    if (value == -1) return 0;
    if (value == 0) return 1;
    return value == 1 ? 2 : 0;
}

// FUNCTION: GAMEMD 0x7339B0
void FUN_007339B0(bool clear)
{
    if (DAT_00A8B538) return;
    int value;
    char* text;
    if (DAT_00B0FE54 == 5) {
        text = FUN_00733E10(DAT_00B0FE6C, DAT_00B0FD70, DAT_00B0FE70, &value);
        if (clear) DAT_00887324->FUN_006DA740();
    } else {
        if (DAT_00B0FE6C) { delete DAT_00B0FE6C; DAT_00B0FE6C = 0; }
        DAT_00B0FE6C = FUN_00732050();
        if (!DAT_00B0FE6C->Count) {
            delete DAT_00B0FE6C;
            DAT_00B0FE6C = 0;
            // 0x733A07 passes target 0x7335F0; callback 0x731F70 consumes
            // AL and EDX is an unused context in the 0/1-valued target.
            DAT_00B0FE6C = FUN_00731F70(reinterpret_cast<bool (__fastcall *)(TechnoClass*, void*)>(FUN_007335F0), 0);
        }
        DAT_00887324->FUN_006DA740();
        text = FUN_00733E10(DAT_00B0FE6C, 0, 0x7FFFFFFF, &value);
    }
    int count = DAT_00B0FE6C->Count;
    int i;
    for (i = 0; i < count; ++i) {
        TechnoClass* object = DAT_00B0FE6C->Items[i];
        const char* id = object->vf_34()->ID;
        if (text && strcmp(id, text) == 0 && object->vf_79()) object->vf_83();
    }
    const wchar_t* label = 0;
    UICmndsVector* selected = new UICmndsVector;
    count = DAT_00A8ECB8.Count;
    for (i = 0; i < count; ++i) {
        TechnoClass* object = DAT_00A8ECB8.Items[i];
        if (object && object->Flags.IsTechno) selected->AddItem(object);
    }
    count = selected->Count;
    for (i = 0; i < count; ++i)
        if (!FUN_00733C60(selected->Items[i], text)) { label = FUN_00734E60(DAT_0084560C, 0, DAT_00845598, 0x6C3); break; }
    if (!label && DAT_00A8ECB8.Count > 0) label = DAT_00A8ECB8.Items[0]->vf_34()->UIName;
    wchar_t buffer[256];
    FUN_00731D90(buffer, label);
    int color = 3;
    if (DAT_00A83D4C) color = DAT_00A83D4C->ColorSchemeIndex;
    DAT_00A8BC60.FUN_005D3BA0(0, 0, buffer, color, 0x4046, 240, true);
    DAT_00B0FE70 = value;
    strcpy(DAT_00B0FD70, text);
    delete[] text;
    DAT_00B0FE54 = selected->Count ? 5 : 0;
    DAT_00B0FE58 = 0;
    delete selected;
}

// FUNCTION: GAMEMD 0x733C60
int FUN_00733C60(TechnoClass* object, const char* text)
{
    const char* id = object->vf_34()->ID;
    if (text && strcmp(id, text) == 0 && object->vf_79()) return 1;
    return 0;
}

// FUNCTION: GAMEMD 0x733CD0
DynamicVectorClass<const char*>* FUN_00733CD0(UICmndsVector* list)
{
    DynamicVectorClass<const char*>* result = new DynamicVectorClass<const char*>;
    int count = list->Count;
    for (int i = 0; i < count; ++i) {
        const char* text = list->Items[i]->vf_34()->ID;
        int j;
        for (j = 0; j < result->Count; ++j)
            if (strcmp(text, result->Items[j]) == 0) break;
        if (j == result->Count || j == -1) result->AddItem(text);
    }
    return result;
}

// FUNCTION: GAMEMD 0x733E10
char* FUN_00733E10(UICmndsVector* list, const char* previous, int limit, int* value)
{
    DynamicVectorClass<const char*>* types = new DynamicVectorClass<const char*>;
    int i;
    int count = list->Count;
    for (i = 0; i < count; ++i) {
        const char* text = list->Items[i]->vf_34()->ID;
        if (FUN_00732210(types, text) == -1) types->AddItem(text);
    }
    DynamicVectorClass<int>* totals = new DynamicVectorClass<int>;
    int size = types->Count;
    for (int n = size; n > 0; --n) { int zero = 0; totals->AddItem(zero); }
    count = list->Count;
    for (i = 0; i < count; ++i) {
        TechnoClass* object = list->Items[i];
        const char* text = object->vf_34()->ID;
        int index = -1;
        for (int j = 0; j < types->Count; ++j)
            if (strcmp(text, types->Items[j]) == 0) { index = j; break; }
        int prior = totals->Items[index];
        totals->Items[index] = object->vf_34()->vf_33(reinterpret_cast<int>(object->Owner)) + prior;
    }
    int best = -1;
    *value = 0;
    if (previous) {
        for (i = 0; i < size; ++i) {
            if (strcmp(previous, types->Items[i]) && totals->Items[i] < limit && *value < totals->Items[i]) {
                *value = totals->Items[i]; best = i;
            }
        }
    }
    if (!*value) {
        int maximum = 0;
        best = -1;
        for (i = 0; i < size; ++i)
            if (maximum < totals->Items[i]) { maximum = totals->Items[i]; best = i; }
        *value = maximum;
    }
    const char* text = previous;
    if (best != -1) text = types->Items[best];
    char* result = new char[100];
    if (text) strcpy(result, text);
    delete types;
    delete totals;
    return result;
}

// FUNCTION: GAMEMD 0x734120
void __cdecl FUN_00734120()
{
    CellStruct cell;
    CellStruct result;
    if (timeGetTime() - DAT_00845558 < 1600)
        cell = *FUN_00660BE0(&result);
    else
        cell = *FUN_00660BB0(&result);
    DAT_00845558 = timeGetTime();
    if (cell.X != DAT_00B0FDF0.X || cell.Y != DAT_00B0FDF0.Y) {
        CoordStruct coord;
        coord.X = cell.X * 256 + 128;
        coord.Y = cell.Y * 256 + 128;
        coord.Z = 0;
        int lift = (Map_0087F7E8.FUN_00565730(coord)->Level * 256) / 2;
        coord.X -= lift;
        coord.Y -= lift;
        DAT_00887324->FUN_006D6070(&coord);
        if (DAT_00880990) Map_0087F7E8.FUN_004A91B0(&cell, &DAT_00B0FDF0);
    }
}

// FUNCTION: GAMEMD 0x734210
void __cdecl FUN_00734210()
{
    DAT_00845550 = timeGetTime() - 1601;
    DAT_00845554 = -1;
    DAT_00845558 = timeGetTime() - 1601;
    DAT_0084555C = -100;
}

// FUNCTION: GAMEMD 0x734250
void FUN_00734250(BuildingClass* object)
{
    if (object->Type->BuildCat == 5) {
        SidebarTabObjectB = object;
        return;
    }
    SidebarTabObjectA = object;
}

// FUNCTION: GAMEMD 0x734270
// Removes this object from the two sidebar tab-object slots. A null this clears
// both slots; otherwise only the slot(s) that point at this object are cleared.
void TechnoClass::ClearSidebarTabObject()
{
    if (this == NULL) {
        SidebarTabObjectA = NULL;
        SidebarTabObjectB = NULL;
        return;
    }
    if (this == SidebarTabObjectA) {
        SidebarTabObjectA = NULL;
        return;
    }
    if (this == SidebarTabObjectB) {
        SidebarTabObjectB = NULL;
        return;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x007342A0
int FUN_007342A0()
{
    return DAT_00B0FE5C;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x007342B0
int FUN_007342B0()
{
    return DAT_00B0FE60;
}

// FUNCTION: GAMEMD 0x7342C0
bool FUN_007342C0(AbstractClass* object)
{
    if (!object) return false;
    return object->Flags.IsTechno;
}
