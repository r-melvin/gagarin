// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x55A730.
//   Reads global 0x7E4408: double -pi/16 (the per-facing rotation step).

#include "locomotion_class_draw_matrix_methods.h"
#include "locomotion_rotation_step.h"

// FUNCTION: GAMEMD 0x55A730  (__stdcall COM virtual; `this` on the stack)
//
// The draw matrix for a plain locomotor: identity rotated about Z by the
// linked object's current facing, reduced to 32 steps and re-based so that
// facing 8 is zero. When a voxel index key is supplied (and is not the "none"
// marker) the 32-step facing is folded into its low five bits.
//
// The facing-to-angle conversion has to stay inside the RotateZ argument: the
// hidden-pointer DirStruct temporary then outlives the int spill VC6 makes for
// FILD, so it gets its own frame slot (frame 0x34) while the int and the second
// Current() temporary share the dead `this` home slot. Split into a named int
// the temporary dies early, both land in the `this` slot and the frame shrinks
// to 0x30 (77.8%); a named DirStruct local reorders the whole tail (42.6%).
Matrix3D_0055A730 __stdcall Loco_0055A730::Draw_Matrix(unsigned int* key)
{
    Matrix3D_0055A730 m;
    m.MakeIdentity();

    m.RotateZ((float)(((int)((((this->LinkedTo->PrimaryFacing.Current().Raw >> 10) + 1) >> 1) & 0x1F) - 8)
                      * gg_locomotion_facing_step));

    if (key != 0 && *key != 0xFFFFFFFF) {
        *key <<= 5;
        *key |= (((this->LinkedTo->PrimaryFacing.Current().Raw >> 10) + 1) >> 1) & 0x1F;
    }

    return m;
}
