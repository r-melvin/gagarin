// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Entry points, vtable slot and both dispatch tables read numerically off the
//   user's retail gamemd.exe v1.001 via the local Ghidra CLI. Neither address is
//   bound by YRpp, so the placeholder names are kept.
//
// A pair of type-filter helpers at 0x40DD20 and 0x40DD70. Both are
// byte-identical apart from their table addresses: null-check the pointer, ask
// it WhatAmI() through vtable slot +0x2C, and hand it back unchanged if the
// answer is one of four accepted AbstractTypes (1, 2, 6, or 15), otherwise return null.
//
// The dispatch is a dense two-level jump table, which is what pins the source
// shape. `ghidra memory read 0x40dd4c 24` gives
//     41dd4000 45dd4000 | 00 00 01 01 01 00 01 01 01 01 01 01 01 01 00
// - a two-entry jump table (0x40DD41 = return self, 0x40DD45 = return null)
// selected by a fifteen-byte index table covering WhatAmI() values 1..15. Index
// 0 is chosen for values 1, 2, 6, and 15; the other eleven values pick index 1.
// VC6 emits a dense table for the fifteen explicit cases; the byte table above
// is its de-duplication of the repeated return targets.
//
// The table at 0x40DD9C is byte-for-byte the same, so the two functions accept
// the same four types; what distinguishes them at their call sites is not
// visible here and neither is given a semantic name.
#ifndef GG_MATCH_CORE_WHATAMI_DISPATCH_METHODS_H
#define GG_MATCH_CORE_WHATAMI_DISPATCH_METHODS_H

// Slot-shaped view: only +0x2C is reached, and it takes no arguments.
struct WhatAmIHolder
{
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual void vt_00C();
    virtual void vt_010();
    virtual void vt_014();
    virtual void vt_018();
    virtual void vt_01C();
    virtual void vt_020();
    virtual void vt_024();
    virtual void vt_028();
    virtual int  WhatAmI();   // +0x002C
};

class AbstractClass;
class TechnoClass;

// Both are reached as `MOV ECX,<ptr>; CALL <addr>` and return with a bare RET,
// so one register argument and nothing on the stack. The argument is explicitly
// null-tested before it is dereferenced, which is why these are written as
// __fastcall free functions rather than members - a null `this` is a documented
// input here, not an accident.

// FUNCTION: GAMEMD 0x40DD20
WhatAmIHolder* FUN_0040DD20(WhatAmIHolder* self);

// FUNCTION: GAMEMD 0x40DD70
TechnoClass* FUN_0040DD70(AbstractClass* object);

#endif  // GG_MATCH_CORE_WHATAMI_DISPATCH_METHODS_H
