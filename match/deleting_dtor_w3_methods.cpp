// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Scalar deleting destructors (primary slot 8) of Tube, WaypointPath, SuperWeaponType,
//   UnitType, VoxelAnimType and Wave, read off retail gamemd.exe v1.001. The destructor
//   is only reached through the deleting form, so it is expanded in place.
//   Address index: 0x728710 TubeClass.

#include "FUNCTION.H"
#include "_layout/abstract_class.h"
#include "vector_class_operations.h"

#include "_layout/tube_class.h"
#include "ccini_class_methods.h"
#include "cell_step_tables.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// GLOBAL: GAMEMD 0x8B4138 -- the tube registry.
extern DynamicVectorClass<TubeClass*> DAT_008B4138;

// Registry append, expanded in place: the growth increment is tested before the sum.
static inline bool TubeRegistryAdd(DynamicVectorClass<TubeClass*>* vector, TubeClass* item)
{
    if (vector->Count >= vector->Capacity) {
        if (!vector->IsAllocated && vector->Capacity != 0)
            return false;
        if (vector->CapacityIncrement <= 0)
            return false;
        if (!vector->SetCapacity(vector->Capacity + vector->CapacityIncrement, 0))
            return false;
    }
    int index = vector->Count++;
    vector->Items[index] = item;
    return true;
}

// Position of a tube in the registry, or -1.
static inline int TubeIndexOf(TubeClass* tube)
{
    int n = DAT_008B4138.Count;
    for (int i = 0; i < n; i++) {
        if (DAT_008B4138.Items[i] == tube)
            return i;
    }
    return -1;
}

// FUNCTION: GAMEMD 0x727FD0
// Registers a tube and points its start cell at the new registry index.
TubeClass::TubeClass(const CellStruct* cell, int direction)
    : StartCell(*cell), EndCell(*cell), Direction(direction), StepCount(0)
{
    vf_rtti_5();
    for (int i = 0; i < 100; i++) {
        Steps[i] = -1;
    }
    TubeRegistryAdd(&DAT_008B4138, this);
    if (cell->X != 0 || cell->Y != 0) {
        CellClass* mapCell = DAT_0087F7E8.FUN_005657A0(cell);
        int index = TubeIndexOf(this);
        mapCell->TubeIndex = (short)index;
    }
}

// FUNCTION: GAMEMD 0x7280D0
TubeClass::~TubeClass()
{
    AnnounceExpiredPointer(1);
    CellClass* cell = DAT_0087F7E8.FUN_005657A0(&StartCell);
    if (cell) {
        int index = TubeIndexOf(this);
        if (cell->TubeIndex == index) {
            cell->TubeIndex = -1;
        }
    }
    DAT_008B4138.RemoveItem(this);
}

// GLOBAL: GAMEMD 0x844A60 -- pointer to the section name ("Tubes" at 0x844A64).
extern const char* DAT_00844A60;
// STRING: GAMEMD 0x817F6C -- "%d"
extern const char STR_00817F6C[];
// STRING: GAMEMD 0x844A88 -- "%d,%d,%d,%d,%d"
extern const char STR_00844A88[];
// STRING: GAMEMD 0x8190DC -- ",%d"
extern const char STR_008190DC[];
// STRING: GAMEMD 0x817F70 -- ","
extern const char STR_00817F70[];

// FUNCTION: GAMEMD 0x728200
// Drops the tubes whose start cell does not map back to them and renumbers the survivors.
void TubeClass::FUN_00728200()
{
    int valid = -1;
    int count = DAT_008B4138.Count;
    for (int i = 0; i < count; i++) {
        TubeClass* tube = DAT_008B4138.Items[i];
        CellClass* cell = DAT_0087F7E8.FUN_005657A0(&tube->StartCell);
        if (!cell->InRange()) {
            delete tube;
            count--;
            cell->TubeIndex = -1;
            i--;
        } else {
            valid++;
            cell->TubeIndex = valid;
        }
    }
}

// FUNCTION: GAMEMD 0x728280
// Writes the [Tubes] section: one line per tube, start cell, direction, end cell and the facings.
void __fastcall FUN_00728280(CCINIClass* ini)
{
    char key[12];
    char line[0x200];
    ini->Clear(DAT_00844A60, 0);
    TubeClass::FUN_00728200();
    for (int i = 0; i < DAT_008B4138.Count; i++) {
        TubeClass* tube = DAT_008B4138.Items[i];
        if (tube) {
            sprintf(key, STR_00817F6C, i);
            sprintf(line, STR_00844A88, tube->StartCell.X, tube->StartCell.Y, tube->Direction, tube->EndCell.X, tube->EndCell.Y);
            for (int j = 0; j < 100; j++) {
                sprintf(line + strlen(line), STR_008190DC, tube->Steps[j]);
            }
            ini->WriteString(DAT_00844A60, key, line);
        }
    }
}

// FUNCTION: GAMEMD 0x7283C0
// Reads the [Tubes] section: each entry builds a tube and points its start cell at the new index.
void __fastcall FUN_007283C0(CCINIClass* ini)
{
    char line[0x200];
    ini->Reset();
    int count = ini->GetKeyCount(DAT_00844A60);
    for (int i = 0; i < count; i++) {
        const char* key = ini->GetKeyName(DAT_00844A60, i);
        ini->FUN_00528A10(DAT_00844A60, key, 0, line, sizeof(line));
        TubeClass* tube = new TubeClass(&Cell(0, 0), 0);
        tube->StartCell.X = (short)atoi(strtok(line, STR_00817F70));
        tube->StartCell.Y = (short)atoi(strtok(0, STR_00817F70));
        tube->Direction = atoi(strtok(0, STR_00817F70));
        tube->EndCell.X = (short)atoi(strtok(0, STR_00817F70));
        tube->EndCell.Y = (short)atoi(strtok(0, STR_00817F70));
        tube->StepCount = -1;
        for (int j = 0; j < 100; j++) {
            tube->Steps[j] = atoi(strtok(0, STR_00817F70));
            tube->StepCount++;
            if (tube->Steps[j] == -1)
                break;
        }
        DAT_0087F7E8.FUN_005657A0(&tube->StartCell)->TubeIndex = i;
    }
}

// SYNTHETIC: GAMEMD 0x728710
// TubeClass scalar deleting destructor (primary slot 8), the destructor expanded in place.
