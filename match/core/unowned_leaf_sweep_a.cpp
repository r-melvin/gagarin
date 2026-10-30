// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every displacement, constant, table bound and callee below was read off
//   the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. None of the owning classes is bound by RTTI or
//   a binary string here, so all keep placeholder names.
//
// Small leaves (64 bytes or less) between 0x470000 and 0x500000 that other
// translation units already declared as callees but nothing defined.
#include "../_layout/bullet_class.h"
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);
extern "C" size_t __cdecl strlen(const char* s);
#pragma intrinsic(strlen)

// GLOBAL: GAMEMD 0x00A8ED84
extern "C" int DAT_00A8ED84;
// GLOBAL: GAMEMD 0x00AA0738
extern "C" int DAT_00AA0738;
// GLOBAL: GAMEMD 0x007E1B60 (five string pointers)
extern "C" const char* const DAT_007E1B60[5];
// GLOBAL: GAMEMD 0x007E523C (nineteen string pointers)
extern "C" const char* const DAT_007E523C[19];
// GLOBAL: GAMEMD 0x0081DA28 (twelve string pointers)
extern "C" const char* const DAT_0081DA28[12];
// GLOBAL: GAMEMD 0x00817474
extern "C" const char DAT_00817474[];

// 0x4CAC40: x87 helper taking one double and returning one (callee only).
double __cdecl FUN_004CAC40(double value);
// 0x5117D0: name -> index, -1 when absent (callee only).
int FUN_005117D0(const char* name);

// ---------------------------------------------------------------------------

#include "../_layout/obj_00483460.h"


#include "../_layout/obj_00485060.h"


#include "../_layout/obj_004870b0.h"


#include "../_layout/geometry2d.h"

// FUNCTION: GAMEMD 0x00487F20
// Member-wise difference, returned through the hidden buffer.
Point2D Point2D::operator-(const Point2D& other) const
{
    return Point2D(X - other.X, Y - other.Y);
}

// FUNCTION: GAMEMD 0x0048AB90
// Scale an integer by a double and 1.2 (the constant at 0x7E5190), pass it through
// 0x4CAC40 and truncate.
int FUN_0048AB90(int value, double scale)
{
    return (int)FUN_004CAC40(value * scale * 1.2);
}

#include "../_layout/obj_0048ba80.h"

// FUNCTION: GAMEMD 0x0048BA80
int FUN_0048BA80(Obj_0048BA80* self)
{
    return self->unknown_1C;
}


#include "../_layout/obj_004a1d30.h"

// FUNCTION: GAMEMD 0x004A1D30
// Write one word through 0x4A1DE0.
void Obj_004A1D30::FUN_004A1D30(unsigned short value)
{
    unsigned short word = value;
    FUN_004A1DE0(&word, 2);
}

// FUNCTION: GAMEMD 0x004A1D50
// Write one dword through 0x4A1DE0.
void Obj_004A1D30::FUN_004A1D50(int value)
{
    int dword = value;
    FUN_004A1DE0(&dword, 4);
}

// FUNCTION: GAMEMD 0x004A1DB0
// Write a string's characters (no terminator) through 0x4A1DE0.
void Obj_004A1D30::FUN_004A1DB0(const char* text)
{
    if (text != NULL) {
        FUN_004A1DE0(text, strlen(text));
    }
}

#include "../_layout/obj_004a50f0.h"

// FUNCTION: GAMEMD 0x004A50F0
Obj_004A50F0::Obj_004A50F0()
{
    unknown_8 = DAT_00A8ED84;
    unknown_10 = 0;
    unknown_14 = 0;
    unknown_18 = 0;
    unknown_19 = 0;
}

// FUNCTION: GAMEMD 0x004A5130
bool Obj_004A50F0::FUN_004A5130() const
{
    if (unknown_18 && !unknown_19) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x004A51B0
bool Obj_004A50F0::FUN_004A51B0() const
{
    if (!unknown_18 && unknown_19 == 1) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x004A51D0
bool Obj_004A50F0::FUN_004A51D0() const
{
    if (!unknown_18 && !unknown_19) {
        return true;
    }
    return false;
}

#include "../_layout/pair_004c1b50.h"


#include "../_layout/obj_004c91c0.h"

// FUNCTION: GAMEMD 0x004C91C0
Obj_004C91C0::Obj_004C91C0()
{
    unknown_0 = 0;
    unknown_4 = 0;
    unknown_8 = DAT_00A8ED84;
    unknown_10 = 0;
    unknown_14 = 0;
}

// FUNCTION: GAMEMD 0x004C91E0
// As 0x4C91C0, then the high byte of +0x14 takes `value` capped at 0x7F.
Obj_004C91C0::Obj_004C91C0(int value)
{
    unknown_0 = 0;
    unknown_4 = 0;
    unknown_8 = DAT_00A8ED84;
    unknown_10 = 0;
    unknown_14 = 0;
    int level = value;
    if (level >= 0x7F) {
        level = 0x7F;
    }
    unknown_14 = (short)(level << 8);
}

#include "../_layout/obj_004ca160.h"

// FUNCTION: GAMEMD 0x004CA160
int FUN_004CA160(Obj_004CA160* self)
{
    return self->unknown_58;
}

// GLOBAL: GAMEMD 0x0085D0A4 (4096-entry float table)
extern "C" const float DAT_0085D0A4[4096];

// FUNCTION: GAMEMD 0x004CAD50
// Table lookup: scale `value` by 4096 / 2pi, wrap into 0..4095 and read the
// float table at 0x85D0A4.
extern "C" double __cdecl FUN_004CAD50(double value)
{
    int index = (int)(value * 651.8986469044033) % 4096;
    if (index < 0) {
        index += 4096;
    }
    return DAT_0085D0A4[index];
}

// FUNCTION: GAMEMD 0x004E1100
BulletData::BulletData()
    : unknown_18(0), unknown_1C(0), unknown_20(0), unknown_24(0)
{
    // The two timer members initialize to CurrentFrame/zero through their
    // binary-supported inline default construction; the trailing dwords are
    // explicitly zeroed here as observed at +0x18..+0x24.
}

struct Obj_004D2790;

struct Vtbl_004D2790;

#include "../_layout/obj_004d2790.h"


#include "../_layout/vtbl_004d2790.h"

#include "../_layout/record_004d2790.h"

// FUNCTION: GAMEMD 0x004D2790
// For a kind-6 record, slot 0x90 of the object its +0x60 points at, with 0;
// otherwise null.
void* FUN_004D2790(Record_004D2790* self)
{
    if (self->unknown_30 == 6) {
        Obj_004D2790* object = *self->unknown_60;
        return (object->*object->Vtbl->At_90)(0);
    }
    return NULL;
}

// 0x7C5F3D and 0x7C5FFF: runtime-library helpers with no binary name; the
// first returns a byte (callees only).
extern "C" char __cdecl FUN_007C5F3D();
extern "C" void __cdecl FUN_007C5FFF();
extern "C" char* __cdecl strncpy(char* dst, const char* src, size_t count);

// GLOBAL: GAMEMD 0x0084E863
extern "C" signed char DAT_0084E863;
// GLOBAL: GAMEMD 0x0084E865
extern "C" const char DAT_0084E865[];


extern "C" char* __cdecl strcpy(char* dst, const char* src);
#pragma intrinsic(strcpy)
extern "C" char* __cdecl _strupr(char* text);

#include "../_layout/text_004f4cb0.h"

#include "../_layout/obj_004f4c20.h"

// FUNCTION: GAMEMD 0x004F4C20
Obj_004F4C20::Obj_004F4C20()
{
    unknown_0 = 0;
}

// FUNCTION: GAMEMD 0x004F4C30
// Copy `text` into the buffer at `this`, then upper-case it in place
// (the CRT _strupr at 0x7DCFC4).
Text_004F4CB0* Text_004F4CB0::FUN_004F4C30(const char* text)
{
    strcpy(unknown_0, text);
    _strupr(unknown_0);
    return this;
}

// FUNCTION: GAMEMD 0x004F4C70
// Copy `text` into the buffer at `this`; same body as 0x4F4CB0.
Text_004F4CB0* Text_004F4CB0::FUN_004F4C70(const char* text)
{
    strcpy(unknown_0, text);
    return this;
}

// FUNCTION: GAMEMD 0x004F4CA0
// True when the first byte is zero.
bool Obj_004F4C20::FUN_004F4CA0() const
{
    return unknown_0 == 0;
}

// FUNCTION: GAMEMD 0x004F4CB0
// Copy `text` into the buffer at `this`.
Text_004F4CB0* Text_004F4CB0::FUN_004F4CB0(const char* text)
{
    strcpy(unknown_0, text);
    return this;
}
