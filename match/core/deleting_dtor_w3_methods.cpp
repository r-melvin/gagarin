// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Scalar deleting destructors (primary slot 8) of Tube, WaypointPath, SuperWeaponType,
//   UnitType, VoxelAnimType and Wave, read off retail gamemd.exe v1.001. The destructor
//   is only reached through the deleting form, so it is expanded in place.
//   Address index: 0x728710 TubeClass.

#include "../FUNCTION.H"
#include "../_layout/abstract_class.h"
#include "../core/vector_class_operations.h"

#include "../_layout/tube_class.h"

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

// SYNTHETIC: GAMEMD 0x728710
// TubeClass scalar deleting destructor (primary slot 8), the destructor expanded in place.
