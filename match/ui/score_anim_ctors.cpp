// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x690BB0 and 0x690F30; RTTI .?AVScoreTimeClass@@ (vtable 0x7F0EC8, base
//   ScoreAnimClass) and .?AVScoreAnimClass@@ (vtable 0x7F0EDC). The timer at +0x0C is the 3-dword
//   clock stamp of match/_layout/ms_anim.h; the base constructor is expanded inline in the derived one.
//   Address index: 0x690BB0, 0x690F30.
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/ms_anim.h"

// VTABLE: GAMEMD 0x7F0EDC
class ScoreAnimClass
{
public:
    ScoreAnimClass(int x, int y, int param);
    virtual ~ScoreAnimClass();

    int     X;       // +0x04
    int     Y;       // +0x08
    MSTimer Timer;   // +0x0C
    int     Param;   // +0x18
};
GG_STATIC_ASSERT(offsetof(ScoreAnimClass, X) == 0x4);
GG_STATIC_ASSERT(offsetof(ScoreAnimClass, Y) == 0x8);
GG_STATIC_ASSERT(offsetof(ScoreAnimClass, Timer) == 0xC);
GG_STATIC_ASSERT(offsetof(ScoreAnimClass, Param) == 0x18);
GG_STATIC_ASSERT(sizeof(ScoreAnimClass) == 0x1C);

// VTABLE: GAMEMD 0x7F0EC8
class ScoreTimeClass : public ScoreAnimClass
{
public:
    ScoreTimeClass(int x, int y, int param, int a, int b, int c);
    virtual ~ScoreTimeClass();

    int Field1C;   // +0x1C
    int Field20;   // +0x20
    int Field24;   // +0x24
    int Field28;   // +0x28
};
GG_STATIC_ASSERT(offsetof(ScoreTimeClass, Field1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(ScoreTimeClass, Field28) == 0x28);
GG_STATIC_ASSERT(sizeof(ScoreTimeClass) == 0x2C);

// FUNCTION: GAMEMD 0x690BB0
// Builds the timed score animation: the base fields, then the three extra words.
ScoreTimeClass::ScoreTimeClass(int x, int y, int param, int a, int b, int c)
    : ScoreAnimClass(x, y, param), Field1C(0), Field20(a), Field24(b), Field28(c)
{
}

// FUNCTION: GAMEMD 0x690F30
// Stamps the clock and stores the position and parameter.
ScoreAnimClass::ScoreAnimClass(int x, int y, int param) : X(x), Y(y), Param(param)
{
}
