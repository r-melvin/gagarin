// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x5980C0; the object is
//   the one constructed at 0x5980A0 (flag +0x00, spare value +0x08, uniform
//   source function +0x10).

#include <math.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- table square root.
float __cdecl FUN_004CAC40(double value);

// Gaussian generator built on a uniform [0,1) source (view name; the real name is unrecovered).
struct GaussianRandom_005980C0
{
    unsigned char HaveSpare;            // +0x00
    unsigned char unknown_01[7];
    double Spare;                       // +0x08
    double (__cdecl* Uniform)();        // +0x10

    // FUNCTION: GAMEMD 0x5980C0
    double Next();
};
GG_STATIC_ASSERT(offsetof(GaussianRandom_005980C0, Spare) == 0x08);
GG_STATIC_ASSERT(offsetof(GaussianRandom_005980C0, Uniform) == 0x10);

// FUNCTION: GAMEMD 0x5980C0
// Marsaglia polar method: hand back the spare value from the last pair if
// there is one, otherwise draw points in the unit disc until one is usable
// and keep the second deviate for the next call.
double GaussianRandom_005980C0::Next()
{
    if (HaveSpare) {
        HaveSpare = 0;
        return Spare;
    }
    double x;
    double y;
    double s;
    do {
        do {
            x = Uniform() * 2.0 - 1.0;
            y = Uniform() * 2.0 - 1.0;
            s = x * x + y * y;
        } while (s >= 1.0);
    } while (s == 0.0);
    double ln = log(s);
    double factor = FUN_004CAC40((-ln - ln) / s);
    HaveSpare = 1;
    Spare = factor * y;
    return factor * x;
}
