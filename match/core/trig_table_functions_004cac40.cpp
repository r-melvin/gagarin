// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Disassembly of each address below in retail gamemd.exe v1.001; table bases,
//   bounds and constants read from the same image.
//
// Table-driven trigonometry and square root. The tables sit at 0x85D0A4
// (4097 floats), 0x8610B4 (4097 floats), 0x84F084 and 0x859094; each body
// scales its argument, converts with _ftol and indexes a table.
//
//   0x4CAC40  square root by exponent halving and a mantissa table
//   0x4CAD80  reversed table read
//   0x4CADB0  reversed table read, subtracted from a constant
//   0x4CADE0  odd arc table, double argument
//   0x4CAE30  two-argument arc (atan2 shape)
//   0x4CB060  square root, float argument
//   0x4CB0E0  fills the 0x84F084 table
//   0x4CB150  8192-entry table lookup, float argument
//   0x4CB1A0  the same lookup offset by 0x800 entries
//   0x4CB200  fills the 0x859094 table
//   0x4CB260  reversed table read, float argument
//   0x4CB290  as 0x4CB260, subtracted from a constant
//   0x4CB2C0  fills the 0x85D0A4 table
//   0x4CB320  circular table read, float argument
//   0x4CB3D0  two-argument arc, float arguments
//   0x4CB480  odd arc table, float argument

extern "C" int __cdecl abs(int);

// GLOBAL: GAMEMD 0x8223B0
extern const float DAT_008223B0;
// GLOBAL: GAMEMD 0x8223B4
extern const float DAT_008223B4;
// GLOBAL: GAMEMD 0x84F084
extern float DAT_0084F084[];
// GLOBAL: GAMEMD 0x859094
extern float DAT_00859094[];
// GLOBAL: GAMEMD 0x85D0A4
extern float DAT_0085D0A4[];
// GLOBAL: GAMEMD 0x8650B8
extern const float DAT_008650B8;
// GLOBAL: GAMEMD 0x8650BC
extern const unsigned int DAT_008650BC[];
// GLOBAL: GAMEMD 0x8610B4
extern const float DAT_008610B4[];

// FUNCTION: GAMEMD 0x4CAC40
// Square root: halve the binary exponent, look the mantissa up in a table.
float __cdecl FUN_004CAC40(double value)
{
    float f = (float)value;
    if (f == 0.0f) {
        return 0.0f;
    }
    if (f <= 0.0f) {
        f *= -1.0;
    }
    float t = f;
    unsigned int bits = *(unsigned int*)&t;
    short exponent = (short)((bits >> 23) - 0x7F);
    unsigned int mantissa = bits & 0x7FFFFF;
    if (exponent & 1) {
        mantissa |= 0x800000;
    }
    exponent >>= 1;
    unsigned int result = DAT_008650BC[mantissa >> 10] + ((exponent + 0x7F) << 23);
    return *(float*)&result;
}

// FUNCTION: GAMEMD 0x4CAD80
// Arc table read backwards from 0x859094.
float __cdecl FUN_004CAD80(double value)
{
    float f = (float)value;
    int index = (int)((f + 1.0f) * -2048.0f);
    return DAT_00859094[-index];
}

// FUNCTION: GAMEMD 0x4CADB0
// The same read, subtracted from a quarter turn.
double __cdecl FUN_004CADB0(double value)
{
    float f = (float)value;
    int index = (int)((f + 1.0f) * -2048.0f);
    return 1.5707963267948966 - DAT_00859094[-index];
}

// FUNCTION: GAMEMD 0x4CADE0
// Odd arc table scaled by 1/0x8650B8, signed by the argument.
float __cdecl FUN_004CADE0(double value)
{
    float f = (float)value;
    int index = (int)(f / DAT_008650B8);
    index = abs(index);
    float result;
    if (index < 0x1001) {
        result = DAT_008610B4[index];
    } else {
        result = 1.5707964f;
    }
    if (f < 0.0f) {
        result = -result;
    }
    return result;
}

// FUNCTION: GAMEMD 0x4CB260
// Backwards arc table read, float argument.
float __stdcall FUN_004CB260(float value)
{
    int index = (int)((value + 1.0f) * -2048.0f);
    return DAT_00859094[-index];
}

// FUNCTION: GAMEMD 0x4CB290
// As 0x4CB260, subtracted from a quarter turn.
double __stdcall FUN_004CB290(float value)
{
    int index = (int)((value + 1.0f) * -2048.0f);
    return 1.5707963267948966 - DAT_00859094[-index];
}

// The 0x4CAD50 lookup, expanded inline in the table builder.
static inline float TableLookup(double angle)
{
    int index = (int)(angle * 651.8986469044033) % 4096;
    if (index < 0) {
        index += 4096;
    }
    return DAT_0085D0A4[index];
}

// FUNCTION: GAMEMD 0x4CB2C0
// Fills the 4097-entry table at 0x85D0A4, one step of 2pi/4096 per entry.
void __cdecl FUN_004CB2C0()
{
    for (int i = 0; i != 4097; i++) {
        double angle = i * 0.0015339807878856412;
        DAT_0085D0A4[i] = TableLookup(angle);
    }
}

// FUNCTION: GAMEMD 0x4CB320
// Circular table read at 0x85D0A4, float argument.
float __stdcall FUN_004CB320(float value)
{
    int index = (int)(value * 651.8986469044033) % 4096;
    if (index < 0) {
        return DAT_0085D0A4[index + 4096];
    }
    return DAT_0085D0A4[index];
}

// FUNCTION: GAMEMD 0x4CB480
// Odd arc table scaled by 1/0x8650B8, float argument.
float __stdcall FUN_004CB480(float value)
{
    int index = (int)(value / DAT_008650B8);
    index = abs(index);
    float result;
    if (index < 0x1001) {
        result = DAT_008610B4[index];
    } else {
        result = 1.5707964f;
    }
    if (value < 0.0f) {
        result = -result;
    }
    return result;
}

// FUNCTION: GAMEMD 0x4CB150
// 8192-entry table lookup, float argument; the low bit selects the next entry.
float __stdcall FUN_004CB150(float value)
{
    int scaled = (int)(DAT_008223B0 * value);
    bool odd = (scaled & 1) != 0;
    int index = (scaled / 2) % 0x2000;
    if (index < 0) {
        index += 0x2000;
    }
    if (odd && index < 0x1FFF) {
        index++;
    }
    return DAT_0084F084[index];
}

// FUNCTION: GAMEMD 0x4CB1A0
// The same lookup, offset by 0x800 entries.
float __stdcall FUN_004CB1A0(float value)
{
    int scaled = (int)(DAT_008223B4 * value);
    bool odd = (scaled & 1) != 0;
    int index = (scaled / 2) % 0x2000;
    if (index < 0) {
        index += 0x2800;
    } else {
        index += 0x800;
    }
    if (odd && index < 0x27FF) {
        index++;
    }
    return DAT_0084F084[index];
}

// FUNCTION: GAMEMD 0x4CAE30
// Two-argument arc: ratio y / x through the odd arc table, quadrant fixed by the signs.
float __cdecl FUN_004CAE30(double a, double b)
{
    float x = (float)b;
    float y = (float)a;
    if (x == 0.0f) {
        if (y == 0.0f) {
            return 0.0f;
        }
        if (y > 0.0f) {
            return 1.5707964f;
        }
        return -1.5707964f;
    }
    int index = (int)(y / x / DAT_008650B8);
    index = abs(index);
    float result;
    if (index < 0x1001) {
        result = DAT_008610B4[index];
    } else {
        result = 1.5707964f;
    }
    if (x < 0.0f) {
        result = 3.141592653589793 - result;
    }
    if (y < 0.0f) {
        result = -result;
    }
    return result;
}

// FUNCTION: GAMEMD 0x4CB060
// Square root, float argument.
float __stdcall FUN_004CB060(float value)
{
    if (value == 0.0f) {
        return 0.0f;
    }
    value = (value <= 0.0f) ? value * -1.0 : value;
    unsigned int bits = *(unsigned int*)&value;
    short exponent = (short)((bits >> 23) - 0x7F);
    unsigned int mantissa = bits & 0x7FFFFF;
    if (exponent & 1) {
        mantissa |= 0x800000;
    }
    exponent >>= 1;
    unsigned int result = DAT_008650BC[mantissa >> 10] + ((exponent + 0x7F) << 23);
    return *(float*)&result;
}

// FUNCTION: GAMEMD 0x4CB3D0
// Two-argument arc, float arguments.
float __stdcall FUN_004CB3D0(float y, float x)
{
    if (x == 0.0f) {
        if (y == 0.0f) {
            return 0.0f;
        }
        if (y > 0.0f) {
            return 1.5707964f;
        }
        return -1.5707964f;
    }
    int index = (int)(y / x / DAT_008650B8);
    index = abs(index);
    float result;
    if (index < 0x1001) {
        result = DAT_008610B4[index];
    } else {
        result = 1.5707964f;
    }
    if (x < 0.0f) {
        result = 3.141592653589793 - result;
    }
    if (y < 0.0f) {
        result = -result;
    }
    return result;
}

// The 0x4CAD80 lookup, expanded inline in the table builder.
static inline float ArcLookup(double value)
{
    float f = (float)value;
    int index = (int)((f + 1.0f) * -2048.0f);
    return DAT_00859094[-index];
}

// FUNCTION: GAMEMD 0x4CB200
// Fills the 4097-entry table at 0x859094, one step of 1/2048 per entry from -1.
void __cdecl FUN_004CB200()
{
    for (int i = 0; i != 4097; i++) {
        double step = i * 0.00048828125 - 1.0;
        DAT_00859094[i] = ArcLookup(step);
    }
}

// The 0x4CACB0 lookup, expanded inline in the table builder.
static inline float Lookup8192(double value)
{
    float f = (float)value;
    int scaled = (int)(f * DAT_008223B0);
    bool odd = (scaled & 1) != 0;
    int index = (scaled / 2) % 0x2000;
    if (index < 0) {
        index += 0x2000;
    }
    if (odd && index < 0x1FFF) {
        index++;
    }
    return DAT_0084F084[index];
}

// FUNCTION: GAMEMD 0x4CB0E0
// Fills the 0x2801-entry table at 0x84F084.
void __cdecl FUN_004CB0E0()
{
    for (int i = 0; i != 0x2801; i++) {
        DAT_0084F084[i] = Lookup8192(i * 0.0007669903939428206);
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x8223B0
extern const float DAT_008223B0 = 2607.594482421875f;
// GLOBAL: GAMEMD 0x8223B4
extern const float DAT_008223B4 = 2607.594482421875f;
// GLOBAL: GAMEMD 0x8650B8
extern const float DAT_008650B8 = 0.024413354694843292f;
// END defined globals
