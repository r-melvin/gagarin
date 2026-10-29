// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
// RTTI type names from the pinned image: vtable 0x7ECF44 -> .?AVLCWStraw@@,
// 0x7ED37C -> .?AVLZOPipe@@, 0x7ED394 -> .?AVLZOStraw@@. Slot words read
// from the image are listed beside each VTABLE marker.
// Member offsets come from the constructors recovered here:
//   0x5523E0 (LCWStraw): +0x0C control, +0x10/+0x14/+0x18 zeroed, +0x1C block
//     size, +0x20 margin = size/128 + 1, two operator-new results at +0x14/+0x18.
//   0x55C2B0 (LZOPipe) and 0x55C720 (LZOStraw): the same +0x0C..+0x20 run with
//     the margin equal to the block size, and LZOPipe stores word 0xFFFF at +0x24.
// Allocation sites for complete objects were not traced, so no sizeof is
// asserted.
#ifndef GG_MATCH_PLATFORM_COMPRESSION_STRAWS_H
#define GG_MATCH_PLATFORM_COMPRESSION_STRAWS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

class LCWStraw : public Straw
{
public:
    enum CompControl { COMPRESS = 0, DECOMPRESS = 1 };

    // FUNCTION: GAMEMD 0x5523E0
    LCWStraw(CompControl control, int blocksize);
    virtual ~LCWStraw();                                // slot 0 via 0x5525F0
    virtual int FUN_006C98E0(void* first, int second);    // slot 2 = 0x552490

    int   Control;      // +0x0C
    int   Counter;      // +0x10
    char* Buffer;       // +0x14
    char* Buffer2;      // +0x18
    int   BlockSize;    // +0x1C
    int   SafetyMargin; // +0x20
};
GG_STATIC_ASSERT(offsetof(LCWStraw, Control)      == 0x0C);
GG_STATIC_ASSERT(offsetof(LCWStraw, Counter)      == 0x10);
GG_STATIC_ASSERT(offsetof(LCWStraw, Buffer)       == 0x14);
GG_STATIC_ASSERT(offsetof(LCWStraw, Buffer2)      == 0x18);
GG_STATIC_ASSERT(offsetof(LCWStraw, BlockSize)    == 0x1C);
GG_STATIC_ASSERT(offsetof(LCWStraw, SafetyMargin) == 0x20);
// VTABLE: GAMEMD 0x7ECF44 -- [0x5525F0, 0x6C9890, 0x552490]

class LZOPipe : public Pipe
{
public:
    enum CompControl { COMPRESS = 0, DECOMPRESS = 1 };

    // FUNCTION: GAMEMD 0x55C2B0
    LZOPipe(CompControl control, int blocksize);
    virtual ~LZOPipe();                                 // slot 0 via 0x55C6D0
    virtual int FUN_00631D30();                         // slot 1 = 0x55C5E0
    virtual int FUN_00631D10(int first, int second);    // slot 4 = 0x55C350

    int            Control;      // +0x0C
    int            Counter;      // +0x10
    char*          Buffer;       // +0x14
    char*          Buffer2;      // +0x18
    int            BlockSize;    // +0x1C
    int            SafetyMargin; // +0x20
    unsigned short HeaderWord0;  // +0x24
    unsigned short HeaderWord1;  // +0x26
};
GG_STATIC_ASSERT(offsetof(LZOPipe, Control)      == 0x0C);
GG_STATIC_ASSERT(offsetof(LZOPipe, Counter)      == 0x10);
GG_STATIC_ASSERT(offsetof(LZOPipe, Buffer)       == 0x14);
GG_STATIC_ASSERT(offsetof(LZOPipe, Buffer2)      == 0x18);
GG_STATIC_ASSERT(offsetof(LZOPipe, BlockSize)    == 0x1C);
GG_STATIC_ASSERT(offsetof(LZOPipe, SafetyMargin) == 0x20);
GG_STATIC_ASSERT(offsetof(LZOPipe, HeaderWord0)  == 0x24);
// VTABLE: GAMEMD 0x7ED37C -- [0x55C6D0, 0x55C5E0, 0x477740, 0x631CC0, 0x55C350]

class LZOStraw : public Straw
{
public:
    enum CompControl { COMPRESS = 0, DECOMPRESS = 1 };

    // FUNCTION: GAMEMD 0x55C720
    LZOStraw(CompControl control, int blocksize);
    virtual ~LZOStraw();                                // slot 0 via 0x55C990
    virtual int FUN_006C98E0(void* first, int second);    // slot 2 = 0x55C7C0

    int   Control;      // +0x0C
    int   Counter;      // +0x10
    char* Buffer;       // +0x14
    char* Buffer2;      // +0x18
    int   BlockSize;    // +0x1C
    int   SafetyMargin; // +0x20
};
GG_STATIC_ASSERT(offsetof(LZOStraw, Control)      == 0x0C);
GG_STATIC_ASSERT(offsetof(LZOStraw, Counter)      == 0x10);
GG_STATIC_ASSERT(offsetof(LZOStraw, Buffer)       == 0x14);
GG_STATIC_ASSERT(offsetof(LZOStraw, Buffer2)      == 0x18);
GG_STATIC_ASSERT(offsetof(LZOStraw, BlockSize)    == 0x1C);
GG_STATIC_ASSERT(offsetof(LZOStraw, SafetyMargin) == 0x20);
// VTABLE: GAMEMD 0x7ED394 -- [0x55C990, 0x6C9890, 0x55C7C0]

#endif // GG_MATCH_PLATFORM_COMPRESSION_STRAWS_H
