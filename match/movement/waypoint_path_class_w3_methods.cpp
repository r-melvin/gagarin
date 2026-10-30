// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   WaypointPathClass construction, destruction and stream loading, read off retail
//   gamemd.exe v1.001 (vtable 0x7F6E70). /Ob2: the scalar deleting destructor carries the
//   destructor body inline. The layout is movement/waypoint_path_class_methods.h.
//   Address index: 0x763730 default ctor, 0x7637D0 no-init ctor, 0x763810 ctor, 0x7638C0 dtor, 0x763C70 Load, 0x763E20 deleting dtor.

#include <new.h>
#include "waypoint_path_class_methods.h"
#include "../core/vector_class_operations.h"

// GLOBAL: GAMEMD 0xB72608 -- the waypoint path registry.
extern DynamicVectorClass<WaypointPathClass*> DAT_00B72608;

// Registry append, expanded in place: the growth increment is tested before the sum.
static inline bool PathRegistryAdd(DynamicVectorClass<WaypointPathClass*>* vector, WaypointPathClass* item)
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

// Waypoint append, expanded in place: the growth increment is tested before the sum.
static inline bool WaypointAdd(DynamicVectorClass<WaypointClass>* vector, const WaypointClass& item)
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

// FUNCTION: GAMEMD 0x763730
// A path made without an index is always registered.
WaypointPathClass::WaypointPathClass()
    : CurrentWaypointIndex(-1)
{
    PathRegistryAdd(&DAT_00B72608, this);
}

// FUNCTION: GAMEMD 0x7637D0
WaypointPathClass::WaypointPathClass(const AbstractNoInit& noInit) throw()
    : AbstractClass(noInit), Waypoints(noInit)
{
}

// FUNCTION: GAMEMD 0x763810
// A path made with an index from 0 to 11 is registered; any other starts unregistered.
WaypointPathClass::WaypointPathClass(int index) throw()
    : CurrentWaypointIndex(-1)
{
    if (index >= 0 && index < 12) {
        PathRegistryAdd(&DAT_00B72608, this);
    }
}

// FUNCTION: GAMEMD 0x7638C0
WaypointPathClass::~WaypointPathClass()
{
    AnnounceExpiredPointer(1);
    DAT_00B72608.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x763980  (__thiscall)
// Bounds-checked element accessor: return &Waypoints[idx], or null when idx is
// out of [0, Count). The element address is `Items + idx*0xC`.
WaypointClass* WaypointPathClass::GetWaypoint(int idx) const
{
    if (idx >= 0 && idx < Waypoints.Count)
        return &Waypoints.Items[idx];
    return 0;
}

// FUNCTION: GAMEMD 0x763AF0
// Overwrites the point at an in-range index.
void WaypointPathClass::SetWaypoint(int idx, const WaypointClass* pWaypoint)
{
    if (idx >= 0 && idx < Waypoints.Count) {
        new (&Waypoints.Items[idx]) WaypointClass(*pWaypoint);
    }
}

// FUNCTION: GAMEMD 0x763B30
// Removes the point at an in-range index; the loop point is forgotten when it was that point
// or the last one.
void WaypointPathClass::RemoveWaypoint(int idx)
{
    if (idx >= 0 && idx < Waypoints.Count) {
        if (idx == CurrentWaypointIndex || idx == Waypoints.Count - 1) {
            CurrentWaypointIndex = -1;
        }
        Waypoints.Delete(idx);
    }
}

// FUNCTION: GAMEMD 0x763BA0  (__thiscall)
// Given a node pointer, return the node that follows it in the path. The index
// is recovered via the vector's GetItemIndex virtual (slot 0x14); if the next
// index would run off the end and a CurrentWaypointIndex is set (!= -1), wrap to
// CurrentWaypointIndex. Returns null when the resulting index is out of range.
WaypointClass* WaypointPathClass::GetWaypointAfter(WaypointClass* pWaypoint) const
{
    int index = Waypoints.Slot5(pWaypoint) + 1;
    if (CurrentWaypointIndex != -1 && index == Waypoints.Count)
        index = CurrentWaypointIndex;
    if (index >= 0 && index < Waypoints.Count)
        return &Waypoints.Items[index];
    return 0;
}
// FUNCTION: GAMEMD 0x763BE0
// Empties the point list and forgets the loop point.
void WaypointPathClass::ClearWaypoints()
{
    Waypoints.Clear();
    CurrentWaypointIndex = -1;
}
// FUNCTION: GAMEMD 0x763C70
// Reads the stream, rebuilds the object in place and reads back the waypoint list.
HRESULT __stdcall WaypointPathClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) WaypointPathClass(AbstractNoInit());
    int count;
    hr = pStm->Read(&count, 4, 0);
    if (hr < 0) {
        return hr;
    }
    new (&Waypoints) DynamicVectorClass<WaypointClass>();
    for (int i = 0; i < count; i++) {
        WaypointClass waypoint(0, 0, 0);
        hr = pStm->Read(&waypoint, 12, 0);
        if (hr < 0) {
            return hr;
        }
        WaypointAdd(&Waypoints, waypoint);
    }
    return 0;
}

// SYNTHETIC: GAMEMD 0x763E20
// WaypointPathClass scalar deleting destructor (primary slot 8), the destructor expanded in place.
