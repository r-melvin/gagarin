// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x65EAB0.

#include "house_class_spy_planes_methods.h"

// FUNCTION: GAMEMD 0x65EAB0  HouseClass::SendSpyPlanes (__fastcall, ret 0x10)
//
// Fly a flight of aircraft of one type in from the house's own map edge.
// Each plane is created by its type, marked as arriving from off-map, given a
// mission and an optional target and destination, then placed at the cell the
// edge search picked, converted to leptons at the cell's centre. Scenario
// setup is held open around the creating calls. Returns how many planes made
// it in; a plane that cannot be placed is deleted and the count comes back
// one short.
int __fastcall HouseClass::SendSpyPlanes(int typeIndex, int count, int a2,
                                         AbstractClass* a3, AbstractClass* a4)
{
    AircraftTypeClass* type = DAT_00A8B21C[typeIndex];
    // The edge search's out cell is declared outside the loop: inside it, cl
    // merges its frame slot with the coordinate temporary and the whole tail
    // shifts by a slot.
    CellStruct tmp;
    int made;

    // A `for` loop, not a counted `do`/`while`: retail guards the loop with
    // one `JLE` and then jumps straight into the body, while the do/while
    // form makes cl peel the creating call and duplicate it at the back edge.
    for (made = 0; made < count; made++) {
        DAT_00A8E7AC++;
        AircraftClass* plane = static_cast<AircraftClass*>(type->vf_35(this));
        DAT_00A8E7AC--;
        if (plane == 0) {
            break;
        }

        plane->Spawned = 1;

        int side = this->StartingEdge;
        if (side < 0 || side > 3) {
            side = this->FUN_0050DA80();
        }

        CellStruct cell = *MapInstance_0065EAB0.FUN_004AA440(
            &tmp, side, &DAT_00B04C38, &DAT_00B04C38, 4, 1, 0);

        plane->vf_122(a2, 0);

        if (a4 != 0) {
            plane->SetDestination(a4, 1);
        }
        if (a3 != 0) {
            plane->vf_242(a3);
        }

        DAT_00A8E7AC++;
        // The coordinate is a constructed temporary in the argument list, not
        // a named local filled field by field: that is what puts retail's
        // `PUSH 0` for the second argument ahead of the scaling arithmetic and
        // leaves the Z store after the address push.
        int ok = plane->vf_54(
            Coord_0065EAB0(cell.X * 256 + 128, cell.Y * 256 + 128, 0), 0);
        DAT_00A8E7AC--;
        if (!ok) {
            delete plane;
            return made - 1;
        }

        plane->vf_123();
    }

    return made;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA8B21C
AircraftTypeClass** DAT_00A8B21C;
// GLOBAL: GAMEMD 0xB04C38
CellStruct DAT_00B04C38;
// GLOBAL: GAMEMD 0x87F7E8
MapClass_0065EAB0 MapInstance_0065EAB0;
// END defined globals
