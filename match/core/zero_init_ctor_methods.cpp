// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Three constructors that only zero their leading dwords and return `this`:
//   0x5A9BF0 stores 0 at +0x00/+0x04 as immediates (`MOV [EAX],0`);
//   0x7636F0 and 0x769480 store a zeroed ECX at +0x00/+0x04/+0x08.
// 0x769480 is pushed as a constructor callback at 0x769696 and 0x769782.
// The classes are not identified; names are placeholders and no size is
// asserted.
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class PairHolder_005A9BF0
{
public:
    // FUNCTION: GAMEMD 0x5A9BF0
    PairHolder_005A9BF0();

    void* unknown_00;   // +0x00
    void* unknown_04;   // +0x04
};
GG_STATIC_ASSERT(offsetof(PairHolder_005A9BF0, unknown_04) == 0x04);

class Triple_007636F0
{
public:
    // FUNCTION: GAMEMD 0x7636F0
    Triple_007636F0();

    int unknown_00;   // +0x00
    int unknown_04;   // +0x04
    int unknown_08;   // +0x08
};
GG_STATIC_ASSERT(offsetof(Triple_007636F0, unknown_08) == 0x08);

class Triple_00769480
{
public:
    // FUNCTION: GAMEMD 0x769480
    Triple_00769480();

    int unknown_00;   // +0x00
    int unknown_04;   // +0x04
    int unknown_08;   // +0x08
};
GG_STATIC_ASSERT(offsetof(Triple_00769480, unknown_08) == 0x08);


// FUNCTION: GAMEMD 0x7636F0
Triple_007636F0::Triple_007636F0() :
    unknown_00(0),
    unknown_04(0),
    unknown_08(0)
{
}

// FUNCTION: GAMEMD 0x769480
Triple_00769480::Triple_00769480() :
    unknown_00(0),
    unknown_04(0),
    unknown_08(0)
{
}
