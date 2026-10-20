// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x44ABD0.

#include "building_class_fire_laser_methods.h"

// FUNCTION: GAMEMD 0x44ABD0  BuildingClass::FireLaser (__thiscall, ret 0xC)
//
// Draw the prism support beam from this building's firing point to `target`:
// a new LaserDrawClass in the type's laser colour (no outer colours), lasting
// the rules-supplied duration, thickened to 3 and drawn in house colour; then
// restart the support timer with the rules-supplied delay and clear +0x664.
//
// Phrasing notes (each was load-bearing): the allocation is `operator new`
// plus an explicit Construct on the block (a `new T(...)` gives an EH frame
// or an internal compiler error, see the header); the zero base coordinate
// is a three-argument ctor temporary (three separate zero registers); the
// firing point goes through a named `flh` local so its temporary stays in
// the frame; and the timer is assigned before the +0x664 clear so the clear
// lands between the LEA and the timer stores.
void Building_0044ABD0::FireLaser(Coord_0044ABD0 target)
{
    Color_0044ABD0 black;
    black.R = 0;
    black.G = 0;
    black.B = 0;

    Coord_0044ABD0 flh;
    LaserDraw_0044ABD0* laser = (LaserDraw_0044ABD0*)operator new(sizeof(LaserDraw_0044ABD0));
    if (laser) {
        laser = laser->Construct(
            *(this->*this->Vtbl->GetFLH)(&flh, 0, Coord_0044ABD0(0, 0, 0)), target, 0, 1,
            this->Type->At_56FC, black, black,
            DAT_008871E0->At_4A8, false, true, 1.0f, 0.0f);
        if (laser) {
            laser->IsHouseColor = true;
            laser->Thickness = 3;
        }
    }

    this->At_2EC = CDTimer_0044ABD0(DAT_008871E0->At_4A4);
    this->At_664 = 0;
}
