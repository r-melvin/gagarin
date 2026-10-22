// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The two ILocomotion matrix slots of FlyLocomotionClass. Bytes diffed
//   against the user's retail gamemd.exe v1.001; bodies ordered ascending by
//   retail address.
#include "fly_locomotion_matrix_methods.h"
#include "locomotion_rotation_step.h"

// VTABLE: GAMEMD 0x7E89F4 — the locomotor interface vtable (base offset 4).
// GLOBAL: GAMEMD 0x87F7E8 — the map.
// Reads global 0x7E4408: double -pi/16, the per-facing rotation step.
// GLOBAL: GAMEMD 0x7E2800 — double 0.0, the two rate comparisons.

// ILocomotion slot +0x24 — the draw matrix for a flyer: identity rotated
// about Z by the client's secondary facing reduced to 32 steps and re-based
// so that facing 8 is zero, then, while the client still has travel left,
// pitched and rolled by its type's own angles. The voxel index key collects
// the facing and, on each tilt arm, the bit that names it.
// FUNCTION: GAMEMD 0x4CF610
Matrix3D_004CF610 __stdcall FlyLocoMatrix::Draw_Matrix(int* key)
{
    Matrix3D_004CF610 m;
    m.MakeIdentity();

    if (key != 0) {
        *key |= (int)(((((this->LinkedTo->SecondaryFacing.Current().Raw >> 10) + 1) >> 1) & 0x1F) << 3);
    }

    m.RotateZ((float)(((int)((((this->LinkedTo->SecondaryFacing.Current().Raw >> 10) + 1) >> 1) & 0x1F) - 8)
                      * gg_locomotion_facing_step));

    if ((this->LinkedTo->*this->LinkedTo->Vtbl->At_1C8)() > 0) {
        if (this->LinkedTo->IsTilting != 0) {
            m.RotateX(this->LinkedTo->unknown_328);
            if (this->Height > (this->LinkedTo->*this->LinkedTo->Vtbl->At_84)()->PitchHeight) {
                m.RotateY((float)(this->LinkedTo->unknown_32C +
                                  (this->LinkedTo->*this->LinkedTo->Vtbl->At_84)()->PitchAngle));
            } else {
                m.RotateY(this->LinkedTo->unknown_32C);
            }
            if (key != 0) {
                *key = -1;
            }
        } else if (this->Height > (this->LinkedTo->*this->LinkedTo->Vtbl->At_84)()->PitchHeight) {
            if ((this->LinkedTo->*this->LinkedTo->Vtbl->At_84)()->PitchAngle != 0.0) {
                if (key != 0) {
                    *key |= 4;
                }
                m.RotateY((float)(this->LinkedTo->*this->LinkedTo->Vtbl->At_84)()->PitchAngle);
            }
            if ((this->LinkedTo->*this->LinkedTo->Vtbl->At_84)()->RollAngle != 0.0) {
                double roll;
                if (this->LinkedTo->SecondaryFacing.IsTurningA()) {
                    if (key != 0) {
                        *key |= 1;
                    }
                    roll = (this->LinkedTo->*this->LinkedTo->Vtbl->At_84)()->RollAngle;
                } else {
                    if (!this->LinkedTo->SecondaryFacing.IsTurningB()) {
                        goto done;
                    }
                    if (key != 0) {
                        *key |= 2;
                    }
                    roll = -(this->LinkedTo->*this->LinkedTo->Vtbl->At_84)()->RollAngle;
                }
                m.RotateX((float)roll);
            }
        }
    }

done:
    return m;
}

// ILocomotion slot +0x28 — the shadow matrix for a flyer: the voxel ramp
// matrix for the slope of the cell under the client, flattened to slope zero
// for a type that lies flat on the ground, then rotated about Z by the
// client's secondary facing. The key folds the slope and the facing into its
// low eleven bits.
// FUNCTION: GAMEMD 0x4CFB00
Matrix3D_004CF610 __stdcall FlyLocoMatrix::Shadow_Matrix(unsigned int* key)
{
    Coord_004CF610 coord = this->LinkedTo->Location;
    int slope = MapInstance_004CF610.GetCellAt(coord)->SlopeIndex;
    if ((this->LinkedTo->*this->LinkedTo->Vtbl->At_84)()->IsFlatOnGround != 0) {
        slope = 0;
    }
    Matrix3D_004CF610 m = FUN_007559B0_M(slope);

    m.RotateZ((float)(((int)((((this->LinkedTo->SecondaryFacing.Current().Raw >> 10) + 1) >> 1) & 0x1F) - 8)
                      * gg_locomotion_facing_step));

    if (key != 0 && *key != 0xFFFFFFFF) {
        *key = ((*key << 6) + slope) << 5;
        *key |= (((this->LinkedTo->SecondaryFacing.Current().Raw >> 10) + 1) >> 1) & 0x1F;
    }

    return m;
}
