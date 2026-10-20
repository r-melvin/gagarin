// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4138C0.

#include "aircraft_tracker_update_methods.h"

// The 20x20 bucket a cell falls into — the same expansion already confirmed
// at 0x4134A0/0x4135D0; the two expansions here share one pair of divisors
// because both spell the global division identically.
static inline int TrackerBucket_004138C0(CellStruct_004138C0 cell)
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

// FUNCTION: GAMEMD 0x4138C0  AircraftTrackerClass::Update (__thiscall, ret 0xC)
//
// An aerial unit has moved from oldCell to newCell. The new cell is recorded
// on the techno unconditionally; the grid is only touched when the move
// crossed a bucket boundary, in which case the techno is taken out of the old
// bucket's vector (with the tail slid down in place) and appended to the new
// one, growing that vector by its increment if it is full.
void AircraftTracker_004138C0::Update(Techno_004138C0* techno,
                                      CellStruct_004138C0 oldCell,
                                      CellStruct_004138C0 newCell)
{
    (techno->*techno->Vptr->SetTrackedCoords)(newCell);

    int oldBucket = TrackerBucket_004138C0(oldCell);
    int newBucket = TrackerBucket_004138C0(newCell);
    if (oldBucket != newBucket) {
        (&TrackerVectors[0][0] + oldBucket)->RemoveItem(techno);
        (&TrackerVectors[0][0] + newBucket)->AddItem(techno);
    }
}
