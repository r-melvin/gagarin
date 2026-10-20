// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x55A7D0.
//   GLOBAL: GAMEMD 0x7E4408  double -pi/4  (the per-facing rotation step)

#include "locomotion_class_shadow_matrix_methods.h"

// FUNCTION: GAMEMD 0x55A7D0  (__stdcall COM virtual; `this` on the stack)
//
// The shadow matrix for a plain locomotor: the voxel ramp matrix for the
// slope of the cell under the linked object, rotated about Z by the object's
// current facing reduced to 32 steps and re-based so that facing 8 is zero.
// When a voxel index key is supplied (and is not the "none" marker) the slope
// index and the 32-step facing are folded into its low eleven bits.
//
// As in Draw_Matrix (0x55A730), the facing-to-angle conversion stays inside
// the RotateZ argument so the hidden-pointer DirStruct temporary gets its own
// frame slot. Two further points are load-bearing: the slope is an `int`
// local (retail zero-extends the byte straight into EDX, `XOR EDX,EDX; MOV
// DL,[EAX+0x11C]`, and passes it there; a `unsigned char` local spills it to
// a byte slot and re-masks), and Matrix3D carries a user-declared constructor
// so the __fastcall ramp lookup receives its hidden pointer in ECX and its
// result is copied once into `m` (a POD pushes the pointer and copies twice;
// 16.3%). The key fold `((*key << 6) + slope) << 5` is one store.
Matrix3D_0055A7D0 __stdcall Loco_0055A7D0::Shadow_Matrix(unsigned int* key)
{
    Coord_0055A7D0 coord = this->LinkedTo->Location;
    int slope = MapInstance.GetCellAt(coord)->SlopeIndex;
    Matrix3D_0055A7D0 m = FUN_007559B0(slope);

    m.RotateZ((float)(((int)((((this->LinkedTo->PrimaryFacing.Current().Raw >> 10) + 1) >> 1) & 0x1F) - 8)
                      * -0.78539816339744830962));

    if (key != 0 && *key != 0xFFFFFFFF) {
        *key = ((*key << 6) + slope) << 5;
        *key |= (((this->LinkedTo->PrimaryFacing.Current().Raw >> 10) + 1) >> 1) & 0x1F;
    }

    return m;
}
