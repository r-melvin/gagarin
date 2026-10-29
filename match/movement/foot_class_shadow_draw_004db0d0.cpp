// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Disassembly of 0x4DB0D0 in retail gamemd.exe v1.001 (FootClass, non-virtual, RET 0x2C): the
//   locomotor's ILocomotion slots 8 (+0x20) and 12 (+0x30) and the TechnoClass helper at 0x706BD0.

#include "../_layout/foot_class.h"
#include "../_layout/geometry2d.h"
#include "loco_com.h"

struct TechnoView_004DB0D0 : TechnoClass
{
    // FUNCTION: GAMEMD 0x706BD0 (decl; reloc) -- eleven dwords, the sixth is a Point2D pointer.
    void FUN_00706BD0(int a1, int a2, int a3, int a4, int a5, Point2D* point, int a7, int a8, int a9, int a10, int a11);
};

// FUNCTION: GAMEMD 0x4DB0D0
// When the locomotor casts a shadow, shift the screen point by the locomotor's shadow point and
// pass the shifted point on with the rest of the arguments to the TechnoClass drawing helper.
void FootClass::FUN_004DB0D0(int a1, int a2, int a3, int a4, int a5, Point2D* point, int a7, int a8, int a9, int a10, int a11)
{
    if (Locomotor != 0 && (*(ILocomotionPtr*)&Locomotor)->IsToHaveShadow() == 1) {
        Point2D shifted = *point;
        if (Locomotor != 0) {
            LocoPoint2D offset = (*(ILocomotionPtr*)&Locomotor)->ShadowPoint();
            shifted = Point2D(point->X + offset.X, point->Y + offset.Y);
        }
        ((TechnoView_004DB0D0*)this)->FUN_00706BD0(a1, a2, a3, a4, a5, &shifted, a7, a8, a9, a10, a11);
    }
}
