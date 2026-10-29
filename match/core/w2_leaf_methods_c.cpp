// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Small leaf routines read from retail gamemd.exe v1.001; each owner is a placeholder
// `Obj_<ADDR>` pinned by offsetof asserts. Each address is verified separately.

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x005C69A0
// Count of leading non-zero bytes in a word array of `words` 32-bit words.
int __fastcall FUN_005C69A0(const unsigned char* bytes, unsigned int words)
{
    int count = 0;
    unsigned int i = 0;
    unsigned int size = words << 2;
    while (i < size && bytes[i] != 0) {
        count++;
        i++;
    }
    return count;
}

struct Obj_00550260 {
    // FUNCTION: GAMEMD 0x550260 (decl; reloc)
    void FUN_00550260();
};

// Global vector of Obj_00550260 pointers (items at +4, count at +0x10).
struct Vec_00ABC878 {
    int unknown_00;                 // +0x00
    Obj_00550260** Items;           // +0x04
    int Capacity;                   // +0x08
    int unknown_0C;                 // +0x0C
    int Count;                      // +0x10
};
GG_STATIC_ASSERT(offsetof(Vec_00ABC878, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(Vec_00ABC878, Count) == 0x10);
// GLOBAL: GAMEMD 0xABC878
extern Vec_00ABC878 DAT_00ABC878;

// FUNCTION: GAMEMD 0x00550240
// Run FUN_00550260 over every entry, last to first.
void FUN_00550240()
{
    for (int i = DAT_00ABC878.Count - 1; i >= 0; i--) {
        DAT_00ABC878.Items[i]->FUN_00550260();
    }
}

#include "../_layout/quaternion.h"

// GLOBAL: GAMEMD 0x7E1748 - the float zero the normaliser compares against.
extern const float DAT_007E1748;

struct Quat_00645C70 {
    float X;   // +0x00
    float Y;   // +0x04
    float Z;   // +0x08
    float W;   // +0x0C
    void FUN_00645C70();
};
GG_STATIC_ASSERT(offsetof(Quat_00645C70, W) == 0x0C);

// FUNCTION: GAMEMD 0x00645C70
// Divide every component by the sum of squares unless it is zero.
void Quat_00645C70::FUN_00645C70()
{
    float norm = X * X + Y * Y + Z * Z + W * W;
    if (DAT_007E1748 != norm) {
        X /= norm;
        Y /= norm;
        Z /= norm;
        W /= norm;
    }
}

// GLOBAL: GAMEMD 0x7E2800 - the double zero the running sum starts from.
extern const double DAT_007E2800;

// A run of up to eight double samples (count byte at +0x61) with a divisor at +0x48.
struct Obj_006433D0 {
    unsigned char unknown_00[0x08];
    double Samples[8];              // +0x08
    double Divisor;                 // +0x48
    unsigned char unknown_50[0x11];
    signed char Count;              // +0x61
    double FUN_006433D0();
    double FUN_00643E90(int index);
};
GG_STATIC_ASSERT(offsetof(Obj_006433D0, Samples) == 0x08);
GG_STATIC_ASSERT(offsetof(Obj_006433D0, Divisor) == 0x48);
GG_STATIC_ASSERT(offsetof(Obj_006433D0, Count) == 0x61);

// FUNCTION: GAMEMD 0x006433D0
// Mean of the samples, over the divisor.
double Obj_006433D0::FUN_006433D0()
{
    int n = Count;
    double sum = DAT_007E2800;
    for (int i = 0; i < n; i++) {
        sum += Samples[i];
    }
    return sum / n / Divisor;
}

// FUNCTION: GAMEMD 0x00643E90
// One sample over the divisor; the divisor itself when the index is past the count.
double Obj_006433D0::FUN_00643E90(int index)
{
    if (index >= Count) {
        return Divisor;
    }
    return Samples[index] / Divisor;
}

// FUNCTION: GAMEMD 0x005BD360
// Map a code-page box-drawing character to a plain ASCII stand-in (newline to space,
// verticals to '|', horizontals to '-' and '=', every junction and corner to '+').
unsigned char __stdcall FUN_005BD360(unsigned char ch)
{
    if (ch == 0x0A) {
        return ' ';
    }
    if (ch == 0xB3) {
        return '|';
    }
    if (ch == 0xC4) {
        return '-';
    }
    if (ch == 0xCD) {
        return '=';
    }
    if (ch == 0xDA || ch == 0xC2 || ch == 0xBF || ch == 0xC6 || ch == 0xC3 || ch == 0xD1 || ch == 0xC5
        || ch == 0xD8 || ch == 0xB5 || ch == 0xC0 || ch == 0xC1 || ch == 0xD9 || ch == 0xD5 || ch == 0xB4) {
        return '+';
    }
    return ch;
}
