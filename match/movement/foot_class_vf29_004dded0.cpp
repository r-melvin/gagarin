// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Disassembly of 0x4DDED0 in retail gamemd.exe v1.001 (FootClass slot 29, vtable 0x7E8C94): the
//   action this object would take on a target, built on 0x6FFEC0, 0x578080, 0x565730 and 0x586360.

#include "../_layout/foot_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/map_0087f7e8.h"
#include "../_layout/session_class.h"

// GLOBAL: GAMEMD 0x8B3DF4
extern int DAT_008B3DF4;

struct TechnoView_004DDED0 : TechnoClass
{
    // FUNCTION: GAMEMD 0x6FFEC0 (decl; reloc) -- the action this object takes on a target.
    int FUN_006FFEC0(AbstractClass* target, int a2);
};

// FUNCTION: GAMEMD 0x4DDED0
// The TechnoClass action for the target (a1). When the target's spot is shrouded, the action is
// nonzero and the game mode is 0, it becomes 1 if the type sets its flag at +0xC8D, else 2.
int FootClass::vf_29(int a1, int a2)
{
    AbstractClass* target = (AbstractClass*)a1;
    int action = ((TechnoView_004DDED0*)this)->FUN_006FFEC0(target, a2);
    CoordStruct coord = target->vf_18();
    coord.Z = DAT_0087F7E8.FUN_00578080(&coord);
    if (DAT_0087F7E8.FUN_00565730(&coord)->Flags & 0x100) {
        coord.Z += DAT_008B3DF4;
    }
    if (DAT_0087F7E8.IsLocationShrouded(coord) && action != 0 && Session_00A8B238.GameMode == 0) {
        return vf_33()->bools_C8C[1] ? 1 : 2;
    }
    return action;
}
