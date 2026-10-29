// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, vtable slots and callees read off the user's retail gamemd.exe
//   v1.001 (Ghidra disasm) at the address annotated below. Methods live on
//   the canonical UnitClass (match/_layout/unit_class.h).
//
// Address index:
//   0x736C10  UnitClass::FUN_00736C10

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/unit_class.h"
#include "../_layout/team_class.h"

// The map singleton (GLOBAL 0x87F7E8), as far as the on-map test.
struct MapView_00736C10
{
    // FUNCTION: GAMEMD 0x568350 (decl; reloc) -- is the coordinate inside the map.
    bool FUN_00568350(const CoordStruct* where);
};
// GLOBAL: GAMEMD 0x87F7E8 -- the map.
extern MapView_00736C10 MapInstance_00736C10;

// FUNCTION: GAMEMD 0x736C10
//
// A unit in the mode answered by slot 97 as 5 that has left the map while
// placed in the playfield: flag its team, run slots 232 and 62, and report
// that it was handled.
bool UnitClass::FUN_00736C10()
{
    if (vf_97() == 5) {
        CoordStruct where = this->Location;
        if (!MapInstance_00736C10.FUN_00568350(&where)) {
            if (this->IsInPlayfield) {
                if (this->Team) {
                    this->Team->Flag82 = true;
                }
                vf_232();
                vf_62();
                return true;
            }
        }
    }
    return false;
}
