// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, vtable slots and globals read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at the addresses below.
//   None is bound by YRpp, so placeholder names are kept.
//
// A small __thiscall method with its own vtable-shaped class: the dummy `vt_XXX` slots exist to place the one
// or two slots actually called at the right displacement, and carry no claim
// about what those slots are.
#ifndef GG_MATCH_CORE_SMALL_MISC36_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC36_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// 0x4587D0 - a two-hop predicate.
//
// Asks the argument object, through its slot +0x8C, for something derived from
// this object's field at +0x21C, then feeds that answer plus a global back into
// this object's own slot +0x100 and reports whether the result was non-zero.
// The `TEST EAX,EAX; SETNZ AL` tail is a bool return, not the raw value.
// ---------------------------------------------------------------------------
struct Arg_004587D0
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
    virtual void vt_02C();
    virtual void vt_030();
    virtual void vt_034();
    virtual void vt_038();
    virtual void vt_03C();
    virtual void vt_040();
    virtual void vt_044();
    virtual void vt_048();
    virtual void vt_04C();
    virtual void vt_050();
    virtual void vt_054();
    virtual void vt_058();
    virtual void vt_05C();
    virtual void vt_060();
    virtual void vt_064();
    virtual void vt_068();
    virtual void vt_06C();
    virtual void vt_070();
    virtual void vt_074();
    virtual void vt_078();
    virtual void vt_07C();
    virtual void vt_080();
    virtual void vt_084();
    virtual void vt_088();
    virtual int vt_08C(void* owner);   // +0x008C
};

// Shared storage view; the dword load alone does not establish a pointer.
#include "../_layout/global_0089c818.h"

struct Obj_004587D0
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
    virtual void vt_02C();
    virtual void vt_030();
    virtual void vt_034();
    virtual void vt_038();
    virtual void vt_03C();
    virtual void vt_040();
    virtual void vt_044();
    virtual void vt_048();
    virtual void vt_04C();
    virtual void vt_050();
    virtual void vt_054();
    virtual void vt_058();
    virtual void vt_05C();
    virtual void vt_060();
    virtual void vt_064();
    virtual void vt_068();
    virtual void vt_06C();
    virtual void vt_070();
    virtual void vt_074();
    virtual void vt_078();
    virtual void vt_07C();
    virtual void vt_080();
    virtual void vt_084();
    virtual void vt_088();
    virtual void vt_08C();
    virtual void vt_090();
    virtual void vt_094();
    virtual void vt_098();
    virtual void vt_09C();
    virtual void vt_0A0();
    virtual void vt_0A4();
    virtual void vt_0A8();
    virtual void vt_0AC();
    virtual void vt_0B0();
    virtual void vt_0B4();
    virtual void vt_0B8();
    virtual void vt_0BC();
    virtual void vt_0C0();
    virtual void vt_0C4();
    virtual void vt_0C8();
    virtual void vt_0CC();
    virtual void vt_0D0();
    virtual void vt_0D4();
    virtual void vt_0D8();
    virtual void vt_0DC();
    virtual void vt_0E0();
    virtual void vt_0E4();
    virtual void vt_0E8();
    virtual void vt_0EC();
    virtual void vt_0F0();
    virtual void vt_0F4();
    virtual void vt_0F8();
    virtual void vt_0FC();
    virtual int vt_100(int derived, void* context);   // +0x0100

    char  _pad04[0x21C - 0x04];
    void* Owner;       // +0x021C

    // FUNCTION: GAMEMD 0x4587D0
    bool FUN_004587D0(Arg_004587D0* other);
};
GG_STATIC_ASSERT(offsetof(Obj_004587D0, Owner) == 0x21C);

#endif  // GG_MATCH_CORE_SMALL_MISC36_METHODS_H
