// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against the user's retail gamemd.exe v1.001 over the
//   0x4CFC40-0x4CFDBF leaf run of FlyLocomotionClass. See the header for how
//   the class name was read out of its own runtime type information and for
//   the numeric offset derivation. Bodies ordered ascending by retail address.
#include "fly_locomotion_com_methods.h"
#include "loco_base.h"
#include "../_layout/foot_class.h"
#include "../_layout/techno_type_class.h"
#include <new.h>
#include "../ui/input_controls/ui_display_chain.h"
#include "../_layout/cell_class.h"
#include "matrix3d_native_helpers.h"
#include "locomotion_rotation_step.h"

GG_STATIC_ASSERT(offsetof(TechnoTypeClass, bools_C8C) + 9 == 0xC95);

// GLOBAL: GAMEMD 0x822410
// Native QueryInterface key; GUID field order reproduces its sixteen bytes.
extern const IID IID_00822410 = {
    0x820F501C, 0x4F39, 0x11D2,
    {0x9B, 0x70, 0x00, 0x10, 0x4B, 0x97, 0x2F, 0xE8}
};


// VTABLE: GAMEMD 0x7E89F4 — the locomotor interface vtable (base offset 4).
// VTABLE: GAMEMD 0x7E8AC0 — the persist vtable (base offset 0).
// GLOBAL: GAMEMD 0x7E9A80 — CLSID_FlyLocomotionClass.
// GLOBAL: GAMEMD 0xA8B230 — the scenario object.

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// ILocomotion slot +0x28 — the shadow matrix for a flyer: the voxel ramp
// matrix for the slope of the cell under the client, flattened to slope zero
// for a type that lies flat on the ground, then rotated about Z by the
// client's secondary facing. The key folds the slope and the facing into its
// low eleven bits.
// FUNCTION: GAMEMD 0x4CFB00
Matrix3D __stdcall FlyLocomotionClass::ShadowMatrix(unsigned int* key)
{
    CoordStruct coord = this->LinkedTo->Location;
    int slope = Map_0087F7E8.FUN_00565730(coord)->SlopeIndex;
    if (this->LinkedTo->vf_33()->bools_C8C[9] != 0) {
        slope = 0;
    }
    Matrix3D m = FUN_007559B0(slope);

    m.RotateZ((float)(((int)((((this->LinkedTo->SecondaryFacing.FUN_004C93D0().Whole >> 10) + 1U) >> 1) & 0x1FU) - 8)
                      * gg_locomotion_facing_step));

    if (key != 0 && *key != 0xFFFFFFFF) {
        *key = ((*key << 6) + slope) << 5;
        *key |= (((this->LinkedTo->SecondaryFacing.FUN_004C93D0().Whole >> 10) + 1U) >> 1) & 0x1FU;
    }

    return m;
}
