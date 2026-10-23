// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Negation of the first three components of a four-float record into a
// destination record (destination in ECX, source in EDX, returns the
// destination; the fourth component is copied). Two copies at different
// addresses; each is verified separately.

struct FloatQuad_006460C0 {
    float unknown_00;
    float unknown_04;
    float unknown_08;
    float unknown_0C;
    FloatQuad_006460C0(float a, float b, float c, float d)
    {
        unknown_00 = a;
        unknown_04 = b;
        unknown_08 = c;
        unknown_0C = d;
    }
};

// FUNCTION: GAMEMD 0x006460C0
FloatQuad_006460C0* FUN_006460C0(FloatQuad_006460C0* dest, const FloatQuad_006460C0* src)
{
    *dest = FloatQuad_006460C0(-src->unknown_00, -src->unknown_04, -src->unknown_08, src->unknown_0C);
    return dest;
}

// FUNCTION: GAMEMD 0x00646110
FloatQuad_006460C0* FUN_00646110(FloatQuad_006460C0* dest, const FloatQuad_006460C0* src)
{
    *dest = FloatQuad_006460C0(-src->unknown_00, -src->unknown_04, -src->unknown_08, src->unknown_0C);
    return dest;
}
