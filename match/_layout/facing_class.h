// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Facing fields: constructor 0x4C91E0 and predicates 0x4C9480..0x4C9529.
// Jumpjet 0x54AD30 copies six DWORDs at 0x54AE08..0x54AE13.
#ifndef GG_MATCH_LAYOUT_FACING_CLASS_H
#define GG_MATCH_LAYOUT_FACING_CLASS_H
#include <stddef.h>
#include <stdlib.h>
#include "../_rt/gg_static_assert.h"
#include "frame_timer.h"

// Retail edits the low word in place (0x4C93D0 subtracts into the word of a
// copied dword) but several readers load the whole dword (0x43EE50, 0x41B760,
// 0x4CF610, 0x4CFB00), so both views are members of one four-byte value.
struct DirStruct
{
    union {
        unsigned int Whole;
        struct {
            unsigned short Raw;
            unsigned short Padding;
        };
    };
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

    // Declaration: GAMEMD 0x4C9220 -- word key argument, RET 4.
    bool SetDesired(const DirStruct& facing);

    // FUNCTION: GAMEMD 0x4C93D0
    // Native 0x4C93D0 copies a four-byte result to the caller-provided slot
    // and returns its address (RET 4). This value-return inline preserves
    // both direction words; SetDesired at 0x4C9220 inlines the same arithmetic.
    DirStruct Current() const
    {
        if ((short)this->ROT.Raw > 0 && this->RotationTimer.GetTimeLeft() != 0) {
            short diff  = (short)(this->DesiredFacing.Raw - this->StartFacing.Raw);
            short steps = (short)(abs(diff) / (short)this->ROT.Raw);
            DirStruct ret = this->DesiredFacing;
            if (steps > 0) {
                ret.Raw = (unsigned short)(ret.Raw - (diff / steps) * this->RotationTimer.GetTimeLeft());
            }
            return ret;
        }
        return this->DesiredFacing;
    }

    bool IsRotating() const;    // 0x4C9480
    bool IsRotatingCW() const;  // 0x4C94B0
    bool IsRotatingCCW() const; // 0x4C94F0
    // Existing external receiver spellings; no body recovered here.
    DirStruct FUN_004C93D0() const;
    DirStruct* FUN_004C93D0(DirStruct* out);
    bool FUN_004C9480() const;
    DirStruct FUN_004C9530() const;
    DirStruct FUN_004C95D0(const DirStruct* other) const;

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
