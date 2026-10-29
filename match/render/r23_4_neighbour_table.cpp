// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Body disassembled from retail gamemd.exe v1.001 at the address below. The receiver has no
//   recovered class yet, so it is an address-named view.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../renderer/surface_class.h"

// The surface whose pitch (slot 29, +0x74) is the grid width used below.
// GLOBAL: GAMEMD 0x887314
extern Surface* DAT_00887314;

// Receiver of 0x75F140: a table of the eight neighbour steps of a grid whose row length is the
// surface pitch halved, an index choosing the current step, and the multiples of that step.
struct Obj_0075F140
{
    char unknown_00[0x1AC];
    int  Steps[8];            // +0x1AC
    int  Direction;           // +0x1CC
    char unknown_1D0[0x208 - 0x1D0];
    int  unknown_208;         // +0x208
    int  unknown_20C;         // +0x20C
    int  unknown_210;         // +0x210
    int  unknown_214;         // +0x214
    int  unknown_218;         // +0x218
    int  unknown_21C;         // +0x21C
    int  unknown_220;         // +0x220
    int  unknown_224;         // +0x224
    int  unknown_228;         // +0x228
    int  unknown_22C;         // +0x22C
    int  unknown_230;         // +0x230
    int  unknown_234;         // +0x234
    int  unknown_238;         // +0x238
    void FUN_0075F140();
};
GG_STATIC_ASSERT(offsetof(Obj_0075F140, Steps) == 0x1AC);
GG_STATIC_ASSERT(offsetof(Obj_0075F140, Direction) == 0x1CC);
GG_STATIC_ASSERT(offsetof(Obj_0075F140, unknown_208) == 0x208);
GG_STATIC_ASSERT(offsetof(Obj_0075F140, unknown_238) == 0x238);

// FUNCTION: GAMEMD 0x75F140
// Fills the eight neighbour steps from half the surface pitch, then the current step and its
// multiples.
void Obj_0075F140::FUN_0075F140()
{
    int half = (int)DAT_00887314->GetPitch() >> 1;
    Steps[0] = -half;
    Steps[1] = 1 - half;
    Steps[3] = half + 1;
    Steps[4] = half;
    Steps[5] = half - 1;
    int last = -1 - half;
    Steps[2] = 1;
    Steps[6] = -1;
    Steps[7] = last;
    unknown_208 = 0;
    unknown_20C = 0;
    int step = Steps[Direction];
    unknown_210 = step;
    unknown_214 = Steps[Direction];
    unknown_218 = Steps[Direction];
    unknown_21C = Steps[Direction];
    unknown_220 = Steps[Direction];
    unknown_224 = Steps[Direction] << 1;
    unknown_228 = Steps[Direction] << 1;
    unknown_22C = Steps[Direction] << 1;
    unknown_230 = Steps[Direction] * 3;
    unknown_234 = Steps[Direction] * 3;
    unknown_238 = Steps[Direction] * 3;
}
