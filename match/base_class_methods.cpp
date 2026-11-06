// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every displacement, constant and callee below was read off the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI at the address in each annotation.
//   BaseClass (the AI base node list embedded in HouseClass at +0x5700) is named by
//   RTTI; its vtable is at 0x7E3880.
//
// BaseClass members between 0x42E780 and 0x42EB50. Ordered ascending by retail address.
#include <windows.h>
#include <ocidl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "_rt/gg_static_assert.h"
#include "_layout/cell.h"
#include "_layout/base_node_class.h"
#include "_layout/house_class.h"
#include "_layout/building_class.h"
#include "_layout/cell_class.h"
#include "_layout/map_0087f7e8.h"
#include "_layout/overlay_type_class.h"
#include "_layout/session_class.h"
#include "_layout/swizzle_manager_class.h"
#include <new.h>
#include "ccini_class_methods.h"
#include "vector_class_operations.h"

extern BuildingTypeClass** DAT_00A83C6C;   // GLOBAL: GAMEMD 0xA83C6C
extern Cell DAT_0089C310;                  // GLOBAL: GAMEMD 0x89C310
// FUNCTION: GAMEMD 0x45E7B0 (decl; reloc) -- the building type index named by a text.
int FUN_0045E7B0(const char* name);

inline BaseClass::BaseClass(const AbstractNoInit&)
    : unknown_04(0, 0), unknown_20(0, 0), unknown_38(0, 0)
{
}

// FUNCTION: GAMEMD 0x42E780
// Whether node `index` is already covered: it has a live building, or its cell shows the
// overlay of its type, or a building stands on the cell.
bool BaseClass::FUN_0042E780(int index)
{
    if (FUN_0042E820(index)) {
        return true;
    }
    int type = unknown_04.Items[index].unknown_00;
    if (type >= 0) {
        BuildingTypeClass* buildingType = DAT_00A83C6C[type];
        if (buildingType->Wall) {
            CellClass* cell = DAT_0087F7E8.FUN_005657A0(&unknown_04.Items[index].unknown_04);
            int overlay = buildingType->ToOverlay->ArrayIndex;
            if (cell->OverlayTypeIndex == overlay) {
                return true;
            }
            BuildingClass* building = cell->GetBuilding();
            if (building) {
                return true;
            }
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x42EA30
// The node matching this building's type and cell, when the building belongs to this base's house.
BaseNodeClass* BaseClass::FUN_0042EA30(BuildingClass* building)
{
    if (building->Owner == unknown_74) {
        for (int i = 0; i < unknown_04.Count; i++) {
            if (building->Type->ArrayIndex == unknown_04.Items[i].unknown_00) {
                if (building->vf_110() == unknown_04.Items[i].unknown_04) {
                    return &unknown_04.Items[i];
                }
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x42EB50
// First node of `type` (any type for -1) that is not yet covered; -1 when none.
int BaseClass::FUN_0042EB50(int type)
{
    for (int i = 0; i < unknown_04.Count; i++) {
        if (type == -1) {
            if (!FUN_0042E780(i)) {
                if (Session_00A8B238.GameMode == 0 || !unknown_04.Items[i].unknown_08) {
                    return i;
                }
                if (unknown_74->FUN_0050CAD0(&unknown_04.Items[i])) {
                    unknown_04.Items[i].unknown_04 = DAT_0089C310;
                    return i;
                }
            }
        } else if (unknown_04.Items[i].unknown_00 == type && !FUN_0042E780(i)) {
            return i;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x42EBE0
// Read the completion value, the node count and one "type,x,y" line per node, appending each node.
void BaseClass::FUN_0042EBE0(CCINIClass* ini, const char* section)
{
    ini->Reset();
    unknown_1C = ini->FUN_005276D0(section, "PercentBuilt", unknown_1C);
    int count = ini->FUN_005276D0(section, "NodeCount", 0);
    for (int i = 0; i < count; i++) {
        char key[12];
        char value[128];
        sprintf(key, "%03d", i);
        ini->FUN_00528A10(section, key, 0, value, 128);
        int type;
        if (value[0] == '-') {
            type = atoi(strtok(value, ","));
        } else {
            type = FUN_0045E7B0(strtok(value, ","));
        }
        Cell cell;
        cell.X = (short)atoi(strtok(0, ","));
        cell.Y = (short)atoi(strtok(0, ","));
        BaseNodeClass node;
        node.unknown_00 = type;
        node.unknown_04 = cell;
        unknown_04.AddItem(node);
    }
}

// FUNCTION: GAMEMD 0x42ED60
// Write the completion value, the node count and one "type,x,y" line per node.
void BaseClass::FUN_0042ED60(CCINIClass* ini, const char* section)
{
    char key[12];
    char value[128];
    ini->WriteInteger(section, "PercentBuilt", unknown_1C, 0);
    ini->WriteInteger(section, "NodeCount", unknown_04.Count, 0);
    for (int i = 0; i < unknown_04.Count; i++) {
        sprintf(key, "%03d", i);
        if (unknown_04[i].unknown_00 >= 0) {
            sprintf(value, "%s,%d,%d", DAT_00A83C6C[unknown_04[i].unknown_00]->ID.Data, unknown_04[i].unknown_04.X, unknown_04[i].unknown_04.Y);
        } else {
            sprintf(value, "%d,%d,%d", unknown_04[i].unknown_00, unknown_04[i].unknown_04.X, unknown_04[i].unknown_04.Y);
        }
        ini->WriteString(section, key, value);
    }
}

// FUNCTION: GAMEMD 0x42EE30
// Read the object image, rebuild the three vectors, then refill them from the stream (each as a
// count followed by its elements) and register the owning house for swizzling.
HRESULT __stdcall BaseClass::LoadFromStream(IStream* stream)
{
    if (stream->Read(this, 0x78, 0) < 0) {
        return 0;
    }
    new(this) BaseClass(AbstractNoInit());
    int count = 0;
    if (stream->Read(&count, 4, 0) < 0) {
        return 0;
    }
    for (int i = 0; i < count; i++) {
        BaseNodeClass node;
        if (stream->Read(&node, 0x10, 0) < 0) {
            return 0;
        }
        unknown_04.AddItem(node);
    }
    if (stream->Read(&count, 4, 0) < 0) {
        return 0;
    }
    for (int j = 0; j < count; j++) {
        Cell cell;
        if (stream->Read(&cell, 4, 0) < 0) {
            return 0;
        }
        unknown_20.AddItem(cell);
    }
    if (stream->Read(&count, 4, 0) < 0) {
        return 0;
    }
    for (int k = 0; k < count; k++) {
        Cell cell;
        if (stream->Read(&cell, 4, 0) < 0) {
            return 0;
        }
        unknown_38.AddItem(cell);
    }
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_74);
    return 0;
}

// FUNCTION: GAMEMD 0x42F260
// Re-arm the node that stands for this building (or the first idle node of its type).
void BaseClass::FUN_0042F260(BuildingClass* building)
{
    BaseNodeClass* node = FUN_0042EA30(building);
    if (!node) {
        BuildingTypeClass* type = building->Type;
        if (type->UndeploysInto) {
            int count = unknown_04.Count;
            int index = type->ArrayIndex;
            int i;
            BaseNodeClass* walk;
            for (i = 0, walk = unknown_04.Items; i < count; i++, walk++) {
                if (walk->unknown_00 == index && !walk->unknown_08) {
                    node = walk;
                    break;
                }
            }
        }
    }
    if (node) {
        node->unknown_08 = 1;
        node->Attempts = 0;
    }
}
