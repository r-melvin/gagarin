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
int House_0065EAB0::SendSpyPlanes(int typeIndex, int count, int a2,
                                  int a3, void* a4)
{
    AircraftType_0065EAB0* type = DAT_00A8B21C[typeIndex];
    // The edge search's out cell is declared outside the loop: inside it, cl
    // merges its frame slot with the coordinate temporary and the whole tail
    // shifts by a slot.
    Cell_0065EAB0 tmp;
    int made;

    // A `for` loop, not a counted `do`/`while`: retail guards the loop with
    // one `JLE` and then jumps straight into the body, while the do/while
    // form makes cl peel the creating call and duplicate it at the back edge.
    for (made = 0; made < count; made++) {
        DAT_00A8E7AC++;
        Techno_0065EAB0* plane = (type->*type->Vtbl->CreateObject)(this);
        DAT_00A8E7AC--;
        if (plane == 0) {
            break;
        }

        plane->At_3D4 = 1;

        int side = this->At_1E0;
        if (side < 0 || side > 3) {
            side = FUN_0050DA80(this);
        }

        Cell_0065EAB0 cell = *MapInstance_0065EAB0.FUN_004AA440(
            &tmp, side, &DAT_00B04C38, &DAT_00B04C38, 4, 1, 0);

        (plane->*plane->Vtbl->At_1E8)(a2, 0);

        if (a4 != 0) {
            (plane->*plane->Vtbl->At_480)(a4, 1);
        }
        if (a3 != 0) {
            (plane->*plane->Vtbl->At_3C8)(a3);
        }

        DAT_00A8E7AC++;
        // The coordinate is a constructed temporary in the argument list, not
        // a named local filled field by field: that is what puts retail's
        // `PUSH 0` for the second argument ahead of the scaling arithmetic and
        // leaves the Z store after the address push.
        int ok = (plane->*plane->Vtbl->Unlimbo)(
            Coord_0065EAB0(cell.X * 256 + 128, cell.Y * 256 + 128, 0), 0);
        DAT_00A8E7AC--;
        if (!ok) {
            if (plane != 0) {
                (plane->*plane->Vtbl->ScalarDeletingDtor)(1);
            }
            return made - 1;
        }

        (plane->*plane->Vtbl->At_1EC)();
    }

    return made;
}
