// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4137A0  AircraftTrackerClass::Get   (__thiscall)
//   FUNCTION: GAMEMD 0x413800  AircraftTrackerClass::Clear (__thiscall)

#include "aircraft_tracker_class.h"

// The tracked object's vtable view; see TechnoView_004134A0.
#define TRACKED(t) ((TechnoView_004134A0*)(t))

// The 20x20 bucket a cell falls into: each axis is divided into twenty bands
// of the map's width / height, negative coordinates clamp to the first band
// and anything past the end to the last. The column clamp is a ternary
// (retail compares against the immediate 19 with the default already in
// ESI); the row clamp is an in-place `if`. Written the other way round each
// axis picks up the other's shape.
static inline int TrackerBucket_004134A0(CellStruct_004134A0 cell)
{
    int x = cell.X < 0 ? 0 : cell.X;
    int y = cell.Y < 0 ? 0 : cell.Y;
    int col = x / (DAT_0087F914 / 20);
    int c = col > 19 ? 19 : col;
    int row = y / (DAT_0087F918 / 20);
    if (row > 19)
        row = 19;
    return c + row * 20;
}

// FUNCTION: GAMEMD 0x4134A0  AircraftTrackerClass::Add (__thiscall)
// File a techno under the bucket of its current cell, remembering that cell
// on the techno so Remove can find the same bucket later.
void AircraftTrackerClass::Add(TechnoClass* techno)
{
    CellStruct_004134A0 buf;
    CellStruct_004134A0 cell = *(TRACKED(techno)->*TRACKED(techno)->Vptr->GetMapCoords)(&buf);
    (TRACKED(techno)->*TRACKED(techno)->Vptr->SetTrackedCoords)(cell);
    int bucket = TrackerBucket_004134A0(cell);
    (&TrackerVectors[0][0])[bucket].AddItem(techno);
}

// FUNCTION: GAMEMD 0x4135D0  AircraftTrackerClass::Remove (__thiscall)
// Take a techno out of the bucket its remembered cell points at, and clear
// that memory to the "no cell" value.
void AircraftTrackerClass::Remove(TechnoClass* techno)
{
    CellStruct_004134A0 buf;
    CellStruct_004134A0 cell = *(TRACKED(techno)->*TRACKED(techno)->Vptr->GetTrackedCoords)(&buf);
    (TRACKED(techno)->*TRACKED(techno)->Vptr->SetTrackedCoords)(DAT_00887850);
    int bucket = TrackerBucket_004134A0(cell);
    (&TrackerVectors[0][0])[bucket].RemoveItem(techno);
}

// FUNCTION: GAMEMD 0x4137A0  (__thiscall)
// Pops the first item out of CurrentVector (removing it in place) and returns
// it; returns null when the scratch vector is empty.
//
// The item is read through the receiver (`this->CurrentVector.Items[0]`, which
// is retail's `MOV EAX,[ECX+0x2584]` issued before `PUSH ESI` ever forms the
// container pointer) and the removal is left to the inline `RemoveItem`
// member. Both halves matter. Binding a `DynVec* cv = &this->CurrentVector`
// first and reading the item off it costs the seven-instruction call setup:
// retail takes the address of the item slot, pushes it, loads the vptr, sets
// ECX and only then stores the item into that slot, and with the container
// pointer formed first cl stores the item before it takes the address (81.1%).
// Spelling the removal out through `this->CurrentVector` instead of through
// `RemoveItem` re-bases every access and collapses to 2.6%; hoisting the item
// array into its own local ahead of the container pointer gives 75.7%. Taking
// the item through the receiver and then forming the container local for the
// removal also reaches 100%, so what is load-bearing is only that the item's
// load is not routed through the container pointer.
TechnoClass* AircraftTrackerClass::Get()
{
    if (this->CurrentVector.Count == 0)
        return 0;

    TechnoClass* pItem = this->CurrentVector.Items[0];
    this->CurrentVector.RemoveItem(pItem);
    return pItem;
}

// FUNCTION: GAMEMD 0x413800  (__thiscall)
// Empties every bucket while preserving each bucket's allocated capacity:
// for all 400 TrackerVectors and the CurrentVector, snapshot Capacity, Clear,
// then re-reserve that capacity.
void AircraftTrackerClass::Clear()
{
    DynVec* v = &this->TrackerVectors[0][0];
    int i = 400;
    do
    {
        int cap = v->Capacity;
        v->Clear();
        v->SetCapacity(cap, 0);
        ++v;
    } while (--i != 0);

    int cap = this->CurrentVector.Capacity;
    this->CurrentVector.Clear();
    this->CurrentVector.SetCapacity(cap, 0);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x887850
CellStruct_004134A0 DAT_00887850;
// END defined globals
