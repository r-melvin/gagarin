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

#include "../_layout/pairholder_005a9bf0.h"

#include "../_layout/triple_007636f0.h"

#include "../_layout/triple_00769480.h"


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
