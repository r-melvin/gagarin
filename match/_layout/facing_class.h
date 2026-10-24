// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Facing fields: constructor 0x4C91E0 and predicates 0x4C9480..0x4C9529.
// Jumpjet 0x54AD30 copies six DWORDs at 0x54AE08..0x54AE13.
#ifndef GG_MATCH_LAYOUT_FACING_CLASS_H
#define GG_MATCH_LAYOUT_FACING_CLASS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "frame_timer.h"

struct DirStruct
{
    unsigned short Raw;
    unsigned short Padding;
};
GG_STATIC_ASSERT(offsetof(DirStruct, Raw) == 0);
GG_STATIC_ASSERT(offsetof(DirStruct, Padding) == 2);
GG_STATIC_ASSERT(sizeof(DirStruct) == 4);

struct FacingClass
{
    DirStruct DesiredFacing;
    DirStruct StartFacing;
    CDTimerClass RotationTimer;
    DirStruct ROT;

    bool IsRotating() const;    // 0x4C9480
    bool IsRotatingCW() const;  // 0x4C94B0
    bool IsRotatingCCW() const; // 0x4C94F0
    // Existing external receiver spellings; no body recovered here.
    DirStruct FUN_004C93D0() const;
    DirStruct* FUN_004C93D0(DirStruct* out);
    bool FUN_004C9480() const;

    short Difference() const
    {
        return (short)DesiredFacing.Raw - (short)StartFacing.Raw;
    }
};
GG_STATIC_ASSERT(offsetof(FacingClass, DesiredFacing) == 0);
GG_STATIC_ASSERT(offsetof(FacingClass, StartFacing) == 4);
GG_STATIC_ASSERT(offsetof(FacingClass, RotationTimer) == 8);
GG_STATIC_ASSERT(offsetof(FacingClass, ROT) == 0x14);
GG_STATIC_ASSERT(sizeof(FacingClass) == 0x18);
#endif
