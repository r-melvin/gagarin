// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// The AITriggerTypeClass block of retail .text (0x41E190..0x420360) that the
// other ai_trigger_* units leave open: the unit's run-time initialisers, the
// constructor and destructor, the stream and checksum slots, two of the
// condition tests, the scenario list reader, the INI slots 25 and 26, the
// pointer setters and the size/kind slots, in retail address order.
// AITriggerTypeClass is declared in _layout/ai_trigger_type_class.h.
//   /Ob2: the scalar deleting destructor 0x41FFF0 expands the destructor.

#include <new.h>
#include "../_layout/session_class.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define _CTYPE_DISABLE_MACROS
#include <ctype.h>
#include "../_layout/ai_trigger_type_class.h"
#include "../_layout/obj_004a1d30.h"
#include "../platform/ccini_class_methods.h"
#include "../core/vector_class_operations.h"
#include "../movement/locomotion_load_support.h"
#include "../core/header_tuning_globals.h"
#include "../economy/house_building/house_views.h"
#include "../_layout/foot_class.h"
#include "../_layout/team_type_class.h"

// ---- run-time initialised copies of the shared tuning globals -----------------------------------------------------

// GLOBAL: GAMEMD 0x88A020
extern double DAT_0088A020;
// GLOBAL: GAMEMD 0x7E2A08
const double DAT_007E2A08 = 60.0;

// SYNTHETIC: GAMEMD 0x41E190
// GLOBAL: GAMEMD 0x88A070
double DAT_0088A070 = DAT_0088A020 / DAT_007E2A08;
// SYNTHETIC: GAMEMD 0x41E1B0
// GLOBAL: GAMEMD 0x88A058
double DAT_0088A058 = 1.0 / DAT_0088A070;
// SYNTHETIC: GAMEMD 0x41E330
// GLOBAL: GAMEMD 0x88A060
TuningCoordInit DAT_0088A060(128, 128, 0);

// GLOBAL: GAMEMD 0x7E2A18 -- pointer to the list section name ("AITriggerTypes").
extern const char* DAT_007E2A18;
// GLOBAL: GAMEMD 0x7E2A1C -- pointer to the enable section name ("AITriggerTypesEnable").
extern const char* DAT_007E2A1C;
// STRING: GAMEMD 0x817474 -- "<none>"
extern const char STR_00817474[];
// STRING: GAMEMD 0x817694 -- "none"
extern const char STR_00817694[];
// LIBRARY: GAMEMD 0x7C8D20 -- _stricmp.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t).
// LIBRARY: GAMEMD 0x7C8EF4 -- sprintf.
// GLOBAL: GAMEMD 0x818114 -- pointer to "<none>" (0x817474).
extern const char* DAT_00818114;
// GLOBAL: GAMEMD 0x818118 -- pointer to the "all houses" name (0x81811C).
extern const char* DAT_00818118;
// GLOBAL: GAMEMD 0xA83C98 -- the house-type registry.
extern DynamicVectorClass<AbstractTypeClass*> DAT_00A83C98;



// GLOBAL: GAMEMD 0x87F7E8 -- the map object.
#include "../_layout/map_0087f7e8.h"

// STRING: GAMEMD 0x889F64 -- the shared empty default string.
extern const char STR_00889F64[];
// STRING: GAMEMD 0x817F70 -- ","
extern const char STR_00817F70[];
// LIBRARY: GAMEMD 0x7C9CC2 -- strtok; 0x7C91D0 -- strncpy; 0x7C99E1 -- isspace;
// 0x7C9DBD -- strtol; 0x7C9D66 -- atof; 0x7C5F00 -- _ftol; 0x7C9BFD -- atoi.

// FUNCTION: GAMEMD 0x727CF0 (decl; reloc) -- in-place whitespace trim.
void FUN_00727CF0(char* buffer);
// FUNCTION: GAMEMD 0x6F0FC0 (decl; reloc) -- team type by name.
TeamTypeClass* FUN_006F0FC0(const char* name);
// FUNCTION: GAMEMD 0x5117D0 (decl; reloc) -- house-type name -> index, -1 if absent.
int FUN_005117D0(const char* name);
// FUNCTION: GAMEMD 0x523C90 (decl; reloc) -- first type registry: name -> index.
int FUN_00523C90(const char* name);
// FUNCTION: GAMEMD 0x747370 (decl; reloc) -- second type registry: name -> index.
int FUN_00747370(const char* name);
// FUNCTION: GAMEMD 0x41CAA0 (decl; reloc) -- third type registry: name -> index.
int FUN_0041CAA0(const char* name);
// FUNCTION: GAMEMD 0x45E7B0 (decl; reloc) -- fourth type registry: name -> index.
int FUN_0045E7B0(const char* name);
// GLOBAL: GAMEMD 0xA8E348 -- the first type registry.
extern DynamicVectorClass<TechnoTypeClass*> DAT_00A8E348;
// GLOBAL: GAMEMD 0xA83CE0 -- the second type registry.
extern DynamicVectorClass<TechnoTypeClass*> DAT_00A83CE0;
// GLOBAL: GAMEMD 0xA8B218 -- the third type registry.
extern DynamicVectorClass<TechnoTypeClass*> DAT_00A8B218;
// GLOBAL: GAMEMD 0xA83C68 -- the fourth type registry.
extern DynamicVectorClass<TechnoTypeClass*> DAT_00A83C68;

// GLOBAL: GAMEMD 0xA80220 -- the house registry.
extern DynamicVectorClass<AITriggerHouse*> DAT_00A80220;
// STRING: GAMEMD 0x818164 -- "Civilian"
extern const char STR_00818164[];
// FUNCTION: GAMEMD 0x6A46D0 (decl; reloc) -- name -> index, -1 if absent.
int FUN_006A46D0(const char* name);

// The append to AITriggerTypes, in the free-function shape of the inlined
// DynamicVectorClass::AddItem (as EMPulse_AddItem in combat/empulse_class.cpp).
static inline bool AITriggerType_AddItem(DynamicVectorClass<AITriggerTypeClass*>& v, AITriggerTypeClass* item)
{
    if (v.Count >= v.Capacity)
    {
        if (!v.IsAllocated && v.Capacity != 0)
            return false;
        if (v.CapacityIncrement <= 0)
            return false;
        if (!v.SetCapacity(v.Capacity + v.CapacityIncrement, 0))
            return false;
    }
    int i = v.Count++;
    v.Items[i] = item;
    return true;
}

// CounterClass: only the per-type count is read.
struct Counter_0049FAE0
{
    unsigned char opaque[0x14];
    // FUNCTION: GAMEMD 0x49FAE0 (decl; reloc) -- the count for one type index.
    int FUN_0049FAE0(int index);
};
GG_STATIC_ASSERT(sizeof(Counter_0049FAE0) == 0x14);

// The house type: only the side index at +0xBC is compared.
struct HouseType_0041EC90
{
    unsigned char _pad_000[0xBC];   // +0x00
    int           unknown_BC;       // +0xBC (CMP [EDX+0xBC],EAX @0x41ECC6)
};
GG_STATIC_ASSERT(offsetof(HouseType_0041EC90, unknown_BC) == 0xBC);

// A house as the condition tests see it: the AbstractClass part, the IHouse
// interface at +0x24 (RTTI locator base offset 0x24, table 0x7EA834), the
// type and the four owned-type counters.
struct AITriggerHouse : public AbstractClass, public HouseIHouseBase
{
    unsigned char       _pad_028[0x34 - 0x28];        // +0x28
    HouseType_0041EC90* Type;                         // +0x34
    unsigned char       _pad_038[0x5550 - 0x38];      // +0x38
    Counter_0049FAE0    unknown_5550;                 // +0x5550 buildings (WhatAmI 7)
    Counter_0049FAE0    unknown_5564;                 // +0x5564 units (0x28)
    Counter_0049FAE0    unknown_5578;                 // +0x5578 infantry (0x10)
    Counter_0049FAE0    unknown_558C;                 // +0x558C aircraft (3)

    // Output less drain through IHouse slots 8 and 9, expanded in 0x41F030
    // and 0x41F080 (the house stays in ECX, as for a member).
    // FUNCTION: GAMEMD 0x50DEF0 (decl; reloc) -- the house's base cell.
    Cell FUN_0050DEF0();

    int IHouseSurplus()
    {
        HouseIHouseBase* house = this;
        int drain = house->GetPowerDrain();
        return house->GetPowerOutput() - drain;
    }
};

// FUNCTION: GAMEMD 0x41E350
AITriggerTypeClass::AITriggerTypeClass(const char* id)
    : AbstractTypeClass(id),
      unknown_98(-1), IsGlobal(0), unknown_A0(0), IsEnabled(false),
      unknown_A8(-1), unknown_AC(0), unknown_B0(0),
      Weight_Current(1.0), Weight_Minimum(1.0), Weight_Maximum(1.0),
      unknown_D0(false), unknown_D1(false), unknown_D2(true), unknown_D3(true), unknown_D4(true),
      ConditionObject(0), unknown_DC(0), unknown_E0(0),
      Successes(0), Attempts(0)
{
    memset(&Condition, 0, sizeof(Condition));
    AITriggerType_AddItem(AITriggerTypes, this);
}

// FUNCTION: GAMEMD 0x41E480
AITriggerTypeClass::~AITriggerTypeClass()
{
    AITriggerTypes.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x41E540
HRESULT __stdcall AITriggerTypeClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) AITriggerTypeClass(AbstractNoInit());
    DAT_00B0C110.SwizzleManagerClass::vf_4(&ConditionObject);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_DC);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_E0);
    return 0;
}

// FUNCTION: GAMEMD 0x41E5C0
HRESULT __stdcall AITriggerTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x41E5E0
void AITriggerTypeClass::vf_13(Obj_004A1D30* crc)
{
    AbstractTypeClass::vf_13(crc);
    crc->FUN_004A1D50(unknown_98);
    crc->FUN_004A1D50(IsGlobal);
    crc->FUN_004A1D50(unknown_A0);
    crc->FUN_004A1D50(unknown_A8);
    crc->FUN_004A1D50(unknown_B0);
    switch (unknown_98) {
    case 0:
    case 1:
    case 4:
    case 7:
        crc->FUN_004A1D50(Condition.Number);
        crc->FUN_004A1D50(Condition.ComparatorOperand);
        break;
    }
    crc->FUN_004A1D90(Weight_Current);
    crc->FUN_004A1D90(Weight_Minimum);
    crc->FUN_004A1D90(Weight_Maximum);
    crc->FUN_004A1CA0(unknown_D0);
    crc->FUN_004A1CA0(unknown_D2);
    crc->FUN_004A1CA0(unknown_D3);
    crc->FUN_004A1CA0(unknown_D4);
    crc->FUN_004A1D50(unknown_AC);
    crc->FUN_004A1CA0(unknown_D1);
}

// FUNCTION: GAMEMD 0x41EC90
//
// Condition test: does the first house whose type has the "Civilian" index
// own the condition object in the amount the comparator asks for? The two
// argument houses are ignored; no such house, or no object, fails.
//
// PARTIAL (5.9% over the code prefix, aligned 41.8%): the residual of the
// 0x41EAF0 / 0x41EE90 twins (ai_trigger_type_house_owns_methods.cpp): retail
// saves EBP inside the type branch and keeps a call tail per counter arm.
bool AITriggerTypeClass::FUN_0041EC90(AITriggerHouse* calling, AITriggerHouse* target)
{
    bool result = false;
    for (int i = 0; i < DAT_00A80220.Count; i++) {
        if (DAT_00A80220.Items[i]->Type->unknown_BC == FUN_006A46D0(STR_00818164)) {
            AITriggerHouse* house = DAT_00A80220.Items[i];
            if (house == 0) {
                break;
            }
            AbstractTypeClass* type = (AbstractTypeClass*)ConditionObject;
            int count;
            if (type == 0) {
                count = 0;
            } else {
                int index = type->vf_16();
                count = 0;
                switch (type->vf_11()) {
                case 7:    count = house->unknown_5550.FUN_0049FAE0(index); break;
                case 0x28: count = house->unknown_5564.FUN_0049FAE0(index); break;
                case 0x10: count = house->unknown_5578.FUN_0049FAE0(index); break;
                case 3:    count = house->unknown_558C.FUN_0049FAE0(index); break;
                }
            }
            switch (Condition.ComparatorOperand) {
            case 0: return count < Condition.Number;
            case 1: return count <= Condition.Number;
            case 2: return count == Condition.Number;
            case 3: return count >= Condition.Number;
            case 4: return count > Condition.Number;
            case 5: result = count != Condition.Number; break;
            }
            break;
        }
    }
    return result;
}

// FUNCTION: GAMEMD 0x41F030
//
// Condition test: is the target house's power surplus (output less drain,
// through IHouse slots 8 and 9) below 100? The calling house is ignored.
//
// PARTIAL (11.1%, aligned 66.7%): retail keeps the house in ECX and sets
// AL=0 before the null test; this build uses EAX and returns constants.
// Tried early return, a result variable, nested if/else and the inline
// surplus helper.
bool AITriggerTypeClass::FUN_0041F030(AITriggerHouse* calling, AITriggerHouse* target) const
{
    if (target == 0) {
        return false;
    }
    int surplus = target->IHouseSurplus();
    return surplus < 100.0;
}

// FUNCTION: GAMEMD 0x41F080
//
// The same test against zero: is the target house short of power?
// PARTIAL (11.1%) as 0x41F030.
bool AITriggerTypeClass::FUN_0041F080(AITriggerHouse* calling, AITriggerHouse* target) const
{
    if (target == 0) {
        return false;
    }
    int surplus = target->IHouseSurplus();
    return surplus < 0.0;
}

// The lookup-or-create of 0x41FCA0 (core/find_or_allocate_methods.cpp),
// which 0x41F2E0 expands in place.
static inline AITriggerTypeClass* AITriggerType_FindOrAllocate(const char* name)
{
    if (_stricmp(STR_00817474, name) == 0) {
        return 0;
    }
    if (_stricmp(STR_00817694, name) == 0) {
        return 0;
    }
    for (int i = 0; i < AITriggerTypes.Count; i++) {
        if (_stricmp(AITriggerTypes.Items[i]->ID, name) == 0) {
            return AITriggerTypes.Items[i];
        }
    }
    return new AITriggerTypeClass(name);
}

// FUNCTION: GAMEMD 0x41F2E0
//
// Read the scenario's AI trigger list: every key of the list section names a
// trigger type, found or created (the 0x41FCA0 lookup, expanded here), which
// then reads its own section and takes the global flag; a global read marks
// it enabled. A map read then applies the enable section to the types it
// names (a type is enabled when its key is true or the game is not a
// campaign).
void AITriggerTypeClass::FUN_0041F2E0(CCINIClass* ini, int isGlobal)
{
    int count = ini->GetKeyCount(DAT_007E2A18);
    int i;
    for (i = 0; i < count; i++) {
        const char* key = ini->GetKeyName(DAT_007E2A18, i);
        AITriggerTypeClass* type = AITriggerType_FindOrAllocate(key);
        if (type != 0) {
            type->vf_25(ini);
            type->IsGlobal = isGlobal;
        }
        if (isGlobal == 1) {
            type->IsEnabled = true;
        }
    }

    if (isGlobal == 0) {
        count = ini->GetKeyCount(DAT_007E2A1C);
        for (i = 0; i < count; i++) {
            const char* key = ini->GetKeyName(DAT_007E2A1C, i);
            for (int j = 0; j < AITriggerTypes.Count; j++) {
                if (_stricmp(AITriggerTypes.Items[j]->ID, key) == 0) {
                    AITriggerTypeClass* type = AITriggerTypes.Items[j];
                    if (type != 0) {
                        if (ini->FUN_005295F0(DAT_007E2A1C, key, false) || Session_00A8B238.GameMode != 0) {
                            type->IsEnabled = true;
                        } else {
                            type->IsEnabled = false;
                        }
                    }
                    break;
                }
            }
        }
    }
}

// FUNCTION: GAMEMD 0x41FEE0
//
// Can the team reach between the two houses' base cells? A team without the
// +0xF0 flag, or no second house, passes. Otherwise the two cells' zones for
// the team's movement zone are compared; with the +0xF1 flag the zones must
// differ while the zones for movement zone 5 agree.
bool AITriggerTypeClass::FUN_0041FEE0(TeamTypeClass* team, AITriggerHouse* first, AITriggerHouse* second)
{
    if (!team->Flag_F0 || second == 0) {
        return true;
    }
    CellStruct a = first->FUN_0050DEF0();
    CellStruct b = second->FUN_0050DEF0();
    int zone = team->unknown_EC;
    if (team->Flag_F1) {
        int zoneB = DAT_0087F7E8.FUN_0056D230(b, zone, false);
        if (DAT_0087F7E8.FUN_0056D230(a, zone, false) != zoneB) {
            int zoneB5 = DAT_0087F7E8.FUN_0056D230(b, 5, false);
            if (DAT_0087F7E8.FUN_0056D230(a, 5, false) == zoneB5) {
                return true;
            }
        }
        return false;
    }
    int zoneB = DAT_0087F7E8.FUN_0056D230(b, zone, false);
    if (DAT_0087F7E8.FUN_0056D230(a, zone, false) == zoneB) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x41F580
//
// Slot 25: read the trigger type back from the comma-separated value under
// its ID in the list section, in vf_26's field order. Any missing field up to
// the condition block fails the read; the later ones are optional. The
// team-count field is skipped (the count is recomputed from the two teams'
// task forces at the end, the larger one winning), as is the field after
// the first flag.
bool AITriggerTypeClass::vf_25(CCINIClass* ini)
{
    char team1[0x18];
    char team2[0x18];
    char name[0x31];
    char buffer[0x200];

    ini->Reset();
    if (ini->FUN_00528A10(DAT_007E2A18, ID, STR_00889F64, buffer, sizeof(buffer))) {
        char* token = strtok(buffer, STR_00817F70);
        if (token != 0) {
            strncpy(name, token, 0x30);
            name[0x30] = 0;
            if (name != Name) {
                memcpy(Name, name, sizeof(Name));
            }

            token = strtok(0, STR_00817F70);
            if (token != 0) {
                strncpy(team1, token, sizeof(team1));
                team1[sizeof(team1) - 1] = 0;
                FUN_00727CF0(team1);
                unknown_DC = 0;
                if (_stricmp(team1, DAT_00818114) != 0) {
                    unknown_DC = FUN_006F0FC0(team1);
                }

                token = strtok(0, STR_00817F70);
                if (token != 0) {
                    strncpy(team1, token, sizeof(team1));
                    team1[sizeof(team1) - 1] = 0;
                    FUN_00727CF0(team1);
                    unknown_A0 = 0;
                    unknown_A8 = -1;
                    if (_stricmp(team1, DAT_00818118) == 0) {
                        unknown_A0 = 2;
                    } else if (_stricmp(team1, DAT_00818114) != 0) {
                        unknown_A8 = FUN_005117D0(team1);
                        if (unknown_A8 != -1) {
                            unknown_A0 = 1;
                        }
                    }

                    if (strtok(0, STR_00817F70) != 0) {
                        unknown_B0 = 0;
                        token = strtok(0, STR_00817F70);
                        if (token != 0) {
                            unknown_98 = atoi(token);

                            token = strtok(0, STR_00817F70);
                            if (token != 0) {
                                strncpy(team1, token, sizeof(team1));
                                team1[sizeof(team1) - 1] = 0;
                                FUN_00727CF0(team1);
                                TechnoTypeClass* object = 0;
                                int index = FUN_00523C90(team1);
                                if (index != -1) {
                                    object = DAT_00A8E348.Items[index];
                                } else if ((index = FUN_00747370(team1)) != -1) {
                                    object = DAT_00A83CE0.Items[index];
                                } else if ((index = FUN_0041CAA0(team1)) != -1) {
                                    object = DAT_00A8B218.Items[index];
                                } else if ((index = FUN_0045E7B0(team1)) != -1) {
                                    object = DAT_00A83C68.Items[index];
                                }
                                ConditionObject = object;

                                token = strtok(0, STR_00817F70);
                                if (token != 0) {
                                    {
                                        char* digits = token;
                                        // STRING: GAMEMD 0x818170
                                        char pair[3] = "00";
                                        char* end = 0;
                                        unsigned int i = 0;
                                        while (*digits != 0) {
                                            while (isspace(*digits)) {
                                                digits++;
                                            }
                                            pair[0] = *digits++;
                                            if (*digits != 0) {
                                                pair[1] = *digits++;
                                            } else {
                                                pair[1] = 0;
                                            }
                                            if (i >= sizeof(Condition)) {
                                                break;
                                            }
                                            ((unsigned char*)&Condition)[i] = (unsigned char)strtol(pair, &end, 16);
                                            i++;
                                        }
                                    }

                                    token = strtok(0, STR_00817F70);
                                    if (token != 0) {
                                        Weight_Current = (unsigned int)atof(token);
                                    }
                                    token = strtok(0, STR_00817F70);
                                    if (token != 0) {
                                        Weight_Minimum = (unsigned int)atof(token);
                                    }
                                    token = strtok(0, STR_00817F70);
                                    if (token != 0) {
                                        Weight_Maximum = (unsigned int)atof(token);
                                    }
                                    token = strtok(0, STR_00817F70);
                                    if (token != 0) {
                                        unknown_D0 = atoi(token) != 0;
                                    }
                                    strtok(0, STR_00817F70);
                                    token = strtok(0, STR_00817F70);
                                    if (token != 0) {
                                        unknown_AC = atoi(token);
                                    }
                                    token = strtok(0, STR_00817F70);
                                    if (token != 0) {
                                        unknown_D1 = atoi(token) != 0;
                                    }
                                    token = strtok(0, STR_00817F70);
                                    if (token != 0) {
                                        strncpy(team2, token, sizeof(team2));
                                        team2[sizeof(team2) - 1] = 0;
                                        FUN_00727CF0(team2);
                                        unknown_E0 = 0;
                                        if (_stricmp(team2, DAT_00818114) != 0) {
                                            unknown_E0 = FUN_006F0FC0(team2);
                                        }
                                    }
                                    token = strtok(0, STR_00817F70);
                                    if (token != 0) {
                                        unknown_D2 = atoi(token) != 0;
                                    }
                                    token = strtok(0, STR_00817F70);
                                    if (token != 0) {
                                        unknown_D3 = atoi(token) != 0;
                                    }
                                    token = strtok(0, STR_00817F70);
                                    if (token != 0) {
                                        unknown_D4 = atoi(token) != 0;
                                    }

                                    if (unknown_DC != 0) {
                                        unknown_B0 = (unknown_B0 > unknown_DC->TaskForce->FUN_006E8780())
                                              ? unknown_B0 : unknown_DC->TaskForce->FUN_006E8780();
                                    }
                                    if (unknown_E0 != 0) {
                                        unknown_B0 = (unknown_B0 > unknown_E0->TaskForce->FUN_006E8780())
                                              ? unknown_B0 : unknown_E0->TaskForce->FUN_006E8780();
                                    }
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x41FB10
//
// Slot 26: write the trigger type as one comma-separated value under its ID
// in the list section: name, the two teams, the house (a house type, the
// "all" name or none), the condition, the condition object, the condition
// block as 64 hex digits, the three weights and the flags.
bool AITriggerTypeClass::vf_26(CCINIClass* ini)
{
    char buffer[512];
    char hex[512];
    const char* team1 = DAT_00818114;
    const char* team2 = DAT_00818114;
    const char* house = DAT_00818114;
    const char* object = DAT_00818114;

    if (unknown_DC != 0) {
        team1 = unknown_DC->ID;
    }
    if (unknown_E0 != 0) {
        team2 = unknown_E0->ID;
    }
    switch (unknown_A0) {
    case 1:
        if (unknown_A8 != -1) {
            house = DAT_00A83C98.Items[unknown_A8]->ID;
        }
        break;
    case 2:
        house = DAT_00818118;
        break;
    }
    if (ConditionObject != 0) {
        // TechnoTypeClass is AbstractTypeClass-derived (RTTI). Its layout
        // header cannot be included beside _layout/foot_class.h (both define
        // TurretControl), so the ID is read through the base.
        object = ((AbstractTypeClass*)ConditionObject)->ID;
    }

    unsigned int i;
    char* digits;
    for (i = 0, digits = hex; i < sizeof(Condition); i++, digits += 2) {
        sprintf(digits, "%02x", ((unsigned char*)&Condition)[i]);
    }
    *digits = 0;

    sprintf(buffer, "%s,%s,%s,%d,%d,%s,%s,%lf,%lf,%lf,%d,%d,%d,%d,%s,%d,%d,%d",
            Name.Data, team1, house, unknown_B0, unknown_98, object, hex,
            Weight_Current, Weight_Minimum, Weight_Maximum,
            unknown_D0 != 0, 0, unknown_AC, unknown_D1 != 0, team2,
            unknown_D2 != 0, unknown_D3 != 0, unknown_D4 != 0);
    return ini->WriteString(DAT_007E2A18, ID, buffer);
}

// FUNCTION: GAMEMD 0x41FD30
void AITriggerTypeClass::FUN_0041FD30(TechnoTypeClass* object)
{
    ConditionObject = object;
}

// FUNCTION: GAMEMD 0x41FD40
void AITriggerTypeClass::FUN_0041FD40(TeamTypeClass* team)
{
    unknown_DC = team;
}

// FUNCTION: GAMEMD 0x41FD50
void AITriggerTypeClass::FUN_0041FD50(TeamTypeClass* team)
{
    unknown_E0 = team;
}

// FUNCTION: GAMEMD 0x41FFD0
int AITriggerTypeClass::vf_11()
{
    return 0x3B;
}

// FUNCTION: GAMEMD 0x41FFE0
int AITriggerTypeClass::vf_12()
{
    return sizeof(AITriggerTypeClass);
}

// FUNCTION: GAMEMD 0x41FFF0
// The scalar deleting destructor the compiler emits for ~AITriggerTypeClass (slot 8).

// FUNCTION: GAMEMD 0x420130
// An empty body; 0x40AD80 tail-jumps to it.
void FUN_00420130()
{
}

// FUNCTION: GAMEMD 0x420360
// An empty body with no recovered caller.
void FUN_00420360()
{
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA83C68
DynamicVectorClass<TechnoTypeClass*> DAT_00A83C68;
// GLOBAL: GAMEMD 0xA83C98
DynamicVectorClass<AbstractTypeClass*> DAT_00A83C98;
// GLOBAL: GAMEMD 0xA83CE0
DynamicVectorClass<TechnoTypeClass*> DAT_00A83CE0;
// GLOBAL: GAMEMD 0xA8B200
DynamicVectorClass<AITriggerTypeClass*> AITriggerTypes;
// GLOBAL: GAMEMD 0xA8B218
DynamicVectorClass<TechnoTypeClass*> DAT_00A8B218;
// GLOBAL: GAMEMD 0xA8E348
DynamicVectorClass<TechnoTypeClass*> DAT_00A8E348;
// GLOBAL: GAMEMD 0x817474
extern const char STR_00817474[] = "<none>";
// GLOBAL: GAMEMD 0x817694
extern const char STR_00817694[] = "none";
// GLOBAL: GAMEMD 0x817F70
extern const char STR_00817F70[] = ",";
// GLOBAL: GAMEMD 0x817474
extern const char STR_00817474[];
// GLOBAL: GAMEMD 0x8180E0
extern const char STR_008180E0[] = "AITriggerTypesEnable";
// GLOBAL: GAMEMD 0x8180F8
extern const char STR_008180F8[] = "AITriggerTypes";
// GLOBAL: GAMEMD 0x81811C
extern const char STR_0081811C[] = "<all>";
// GLOBAL: GAMEMD 0x817474
extern const char STR_00817474[];
// GLOBAL: GAMEMD 0x8180E0
extern const char STR_008180E0[];
// GLOBAL: GAMEMD 0x8180F8
extern const char STR_008180F8[];
// GLOBAL: GAMEMD 0x81811C
extern const char STR_0081811C[];
// GLOBAL: GAMEMD 0x817474
extern const char STR_00817474[];
// GLOBAL: GAMEMD 0x8180E0
extern const char STR_008180E0[];
// GLOBAL: GAMEMD 0x8180F8
extern const char STR_008180F8[];
// GLOBAL: GAMEMD 0x81811C
extern const char STR_0081811C[];
// END defined globals
