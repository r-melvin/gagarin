// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Disassembly of 0x486FF0 in retail gamemd.exe v1.001 (CellClass): the cell test used by
//   TunnelLocomotionClass::CanEnterCell, built on 0x578540 and the cell's object list.

#include "../_layout/cell_class.h"
#include "../_layout/map_0087f7e8.h"
#include "../_layout/object_class.h"

// One iso tile type, as far as this test reads it.
struct IsoTileView_00486FF0
{
    char _pad[0x305];
    bool Flag;   // +0x305
};

// GLOBAL: GAMEMD 0xA8ED2C -- the iso tile type array.
extern IsoTileView_00486FF0** DAT_00A8ED2C;
// GLOBAL: GAMEMD 0xA8ED38 -- the iso tile type count.
extern int DAT_00A8ED38;
// GLOBAL: GAMEMD 0xA8E9A0
extern unsigned char DAT_00A8E9A0;

// FUNCTION: GAMEMD 0x486FF0
// True when the cell is outside the usable area, or when it has no blocking tile flag, slope,
// cell flags, building or object of kind 0x24 on it.
bool CellClass::FUN_00486FF0()
{
    if (!DAT_0087F7E8.FUN_00578540(this, true)) {
        return true;
    }
    int tile = IsoTileTypeIndex;
    if (tile < 0 || tile >= DAT_00A8ED38 || DAT_00A8ED2C[tile]->Flag) {
        if (SlopeIndex == 0 && !(Flags & 0x500)) {
            if (DAT_00A8E9A0) {
                ObjectClass* object = (ObjectClass*)FirstObject;
                while (object && object->vf_11() != 6) {
                    object = (ObjectClass*)object->NextObject;
                }
                if (object) {
                    return false;
                }
            }
            if (DAT_00A8E9A0) {
                ObjectClass* object = (ObjectClass*)FirstObject;
                while (object && object->vf_11() != 0x24) {
                    object = (ObjectClass*)object->NextObject;
                }
                if (object) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA8ED2C
IsoTileView_00486FF0** DAT_00A8ED2C;
// END defined globals
