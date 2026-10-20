// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x703590.

#include "techno_class_nearby_location_methods.h"

// FUNCTION: GAMEMD 0x703590
//
// A free cell near an object (or near this techno when none is given) that
// this techno's speed and movement zone can use. Amphibious speed is treated
// as wheeled; the zone type is looked up first, or -1 when the type has no
// zone.
//
// PARTIAL (52.9%, 55/104). The body between the speed test and the zone
// lookup is byte-exact once the cell comes from a by-value inline helper
// (two copies of the divide, each ending in a dword load of the temporary
// in the parameter slot, one shared store to the named cell). The residual
// is retail's constant handling in the final call: it keeps zero in EBP
// from the object null test (`XOR EBP,EBP; CMP ECX,EBP`) and spends it on
// the two trailing bool pushes and the word stores of the close-to cell
// (built late, in the parameter slot, as the thirteenth argument), then
// holds the repeated 1 in ECX/EDX (`MOV ECX,1; MOV EDX,ECX`) and pushes
// the registers; cl 8804 tests the pointer against itself, stores the zero
// words as immediates and pushes every constant as an immediate, which
// also drops the EBP save. The same materialised-constant shape appears at
// every retail NearByLocation call site (0x4FBF60, 0x41A2C0) and is
// recorded as a suspected 8447-vs-8804 difference. Tried: close-to cell
// declared at the top (kept), after the cell, after the zone lookup; as a
// two-argument constructor temporary and as an inline zero helper in the
// argument list; the by-value NearByLocation wrapper (homes the bool
// argument in a byte slot and reloads it as a dword); bool member passed
// with and without `!= 0`.
Cell_00703590 Obj_00703590::NearbyLocation(Obj_00703590* object)
{
    int speed = (this->*Vptr->GetTechnoType)()->SpeedType;
    if (speed == 4) {
        speed = 1;
    }
    Cell_00703590 closeTo;
    closeTo.X = 0;
    closeTo.Y = 0;

    Cell_00703590 cell;
    Coord_00703590 buf;
    if (object != 0) {
        cell = CoordToCell_00703590((object->*object->Vptr->GetCoords)(&buf));
    } else {
        cell = CoordToCell_00703590((this->*Vptr->GetCoords)(&buf));
    }

    int zone = (this->*Vptr->GetTechnoType)()->MovementZone;
    int zoneType;
    if (zone != -1) {
        zoneType = MapInstance_00703590.GetMovementZoneType(cell, zone, OnBridge);
    } else {
        zoneType = -1;
    }

    Cell_00703590 out;
    return *MapInstance_00703590.NearByLocation(&out, cell, speed, zoneType, zone,
                                                OnBridge, 1, 1, false, false,
                                                false, true, closeTo, false, false);
}
