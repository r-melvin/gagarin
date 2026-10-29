// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Disassembly of 0x48ABC0 in retail gamemd.exe v1.001; constants read from the same image.

extern float __cdecl FUN_004CAC40(double value);

// FUNCTION: GAMEMD 0x48ABC0
// Tests whether a ballistic arc reaches a target: a is the horizontal reach, b the
// launch speed (0 is replaced by 0.001), c the height difference and g the gravity.
// False when the discriminant is negative, the divisor is zero, or both roots are
// negative.
bool FUN_0048ABC0(int a, int b, int c, double g)
{
    double reach = (double)a;
    double speed = (double)b;
    if (speed == 0.0) {
        speed = 0.001;
    }
    double height = (double)c;
    double reach2 = reach * reach;
    double speed2 = speed * speed;
    double disc = reach2 * reach * reach - (reach2 * height * g + reach2 * height * g) - speed2 * (g * g);
    if (disc < 0.0) {
        return false;
    }
    double div = (height * height / speed2 + 1.0) * 2.0;
    if (div == 0.0) {
        return false;
    }
    double x = reach2 - height * g;
    if ((FUN_004CAC40(disc) + x) / div < 0.0) {
        if ((x - FUN_004CAC40(disc)) / div < 0.0) {
            return false;
        }
    }
    return true;
}
