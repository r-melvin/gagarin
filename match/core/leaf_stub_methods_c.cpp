// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Small stand-alone bodies (field readers, zero-initialisers, interface
// forwarders and the like) found at one address each, in ascending retail
// address order. Owners that no other file models are placeholders
// `Obj_<ADDR>` declaring only the members the body touches, with offset
// asserts; interface objects reached through COM slots use the objbase types.

#include <stddef.h>
#include <objbase.h>
#include "../_rt/gg_static_assert.h"

struct Guid_007E36C0 { unsigned int unknown[4]; };
// GLOBAL: GAMEMD 0x7E36C0
extern const Guid_007E36C0 DAT_007E36C0;

// COM error raiser (COMSUPP library, 0x7DC720).
void __stdcall FUN_007DC720(unsigned int hr);

// Slot 0 of the object's own interface table, called on the object with the
// interface id at 0x7E36C0 and the caller's out pointer.
struct Iface_00429400
{
    virtual long __stdcall Slot00(const Guid_007E36C0& iid, void* out);
};

// FUNCTION: GAMEMD 0x00429400
long __stdcall FUN_00429400(Iface_00429400* self, void* out)
{
    return self->Slot00(DAT_007E36C0, out);
}

// FUNCTION: GAMEMD 0x00429480
long __stdcall FUN_00429480(Iface_00429400* self, void* out)
{
    return self->Slot00(DAT_007E36C0, out);
}

// Write one dword through 0x4A1DE0.
struct Obj_004A1D70 {
    void FUN_004A1DE0(const void* data, int length);
    void FUN_004A1D70(int value);
};
// FUNCTION: GAMEMD 0x004A1D70
void Obj_004A1D70::FUN_004A1D70(int value)
{
    int dword = value;
    FUN_004A1DE0(&dword, 4);
}

struct Obj_004A31F0 {
    void* unknown_00;
    bool FUN_004A31F0(void* arg);
};
GG_STATIC_ASSERT(offsetof(Obj_004A31F0, unknown_00) == 0x00);
// FUNCTION: GAMEMD 0x004A31F0
bool Obj_004A31F0::FUN_004A31F0(void* arg)
{
    if (arg != 0) {
        FUN_007DC720(0x80004003);
    }
    return unknown_00 == 0;
}

// A four-integer record built from its four arguments.
struct Quad_0054A120 {
    int unknown_0;
    int unknown_4;
    int unknown_8;
    int unknown_C;
    Quad_0054A120(int a, int b, int c, int d);
};
GG_STATIC_ASSERT(sizeof(Quad_0054A120) == 0x10);
// FUNCTION: GAMEMD 0x0054A120
Quad_0054A120::Quad_0054A120(int a, int b, int c, int d)
{
    unknown_0 = a;
    unknown_4 = b;
    unknown_8 = c;
    unknown_C = d;
}

// The index of an element pointer within a vector of 36-byte records.
struct Obj_00589A30 {
    unsigned char unknown_00[4];
    unsigned char* unknown_04;
    unsigned char unknown_08[4];
    bool unknown_0C;
    unsigned int FUN_00589A30(const void* item) const;
};
GG_STATIC_ASSERT(offsetof(Obj_00589A30, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(Obj_00589A30, unknown_0C) == 0x0C);
// FUNCTION: GAMEMD 0x00589A30
unsigned int Obj_00589A30::FUN_00589A30(const void* item) const
{
    if (!unknown_0C) {
        return 0;
    }
    return ((unsigned int)item - (unsigned int)unknown_04) / 36;
}

// Read one float of an inline array by index.
struct Obj_00645D10 {
    float unknown_00[1];
    float FUN_00645D10(int index) const;
};
// FUNCTION: GAMEMD 0x00645D10
float Obj_00645D10::FUN_00645D10(int index) const
{
    return unknown_00[index];
}

struct Obj_0065AD40 {
    unsigned char unknown_00[0xE4];
    int* unknown_E4;
    int FUN_0065AD40(int index);
};
GG_STATIC_ASSERT(offsetof(Obj_0065AD40, unknown_E4) == 0xE4);
// FUNCTION: GAMEMD 0x0065AD40
int Obj_0065AD40::FUN_0065AD40(int index)
{
    return unknown_E4[index];
}

// Run a handler over every entry of a global table of objects.
struct Obj_0065FE00 {
    // FUNCTION: GAMEMD 0x65FE00 (decl; reloc)
    void FUN_0065FE00();
};
// GLOBAL: GAMEMD 0xB04DAC
extern Obj_0065FE00** DAT_00B04DAC;
// GLOBAL: GAMEMD 0xB04DB8
extern int DAT_00B04DB8;
// FUNCTION: GAMEMD 0x0065FDD0
void FUN_0065FDD0()
{
    for (int i = 0; i < DAT_00B04DB8; i++) {
        DAT_00B04DAC[i]->FUN_0065FE00();
    }
}

// Store the argument in the first dword.
struct Obj_00681080 {
    int unknown_00;
    void FUN_00681080(int value);
};
// FUNCTION: GAMEMD 0x00681080
void Obj_00681080::FUN_00681080(int value)
{
    unknown_00 = value;
}

// The held interface pointer, raising E_POINTER when there is none.
struct Obj_00683030 {
    void* unknown_00;
    void* FUN_00683030();
};
GG_STATIC_ASSERT(offsetof(Obj_00683030, unknown_00) == 0x00);
// FUNCTION: GAMEMD 0x00683030
void* Obj_00683030::FUN_00683030()
{
    if (unknown_00 == 0) {
        FUN_007DC720(0x80004003);
    }
    return unknown_00;
}

struct Map_00578AD0 {
    // FUNCTION: GAMEMD 0x578AD0 (decl; reloc)
    int FUN_00578AD0(int cell, int* arg);
};
// GLOBAL: GAMEMD 0x87F7E8 -- the map instance.
extern Map_00578AD0 DAT_0087F7E8;
struct Obj_006A3E30 {
    unsigned char unknown_00[0xC];
    int unknown_0C;
    int FUN_006A3E30(int arg);
};
GG_STATIC_ASSERT(offsetof(Obj_006A3E30, unknown_0C) == 0x0C);
// FUNCTION: GAMEMD 0x006A3E30
int Obj_006A3E30::FUN_006A3E30(int arg)
{
    return DAT_0087F7E8.FUN_00578AD0(unknown_0C, &arg);
}

// The multimedia timer in sixteenths of a unit.
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
// FUNCTION: GAMEMD 0x006C8C50
unsigned long __cdecl FUN_006C8C50()
{
    return timeGetTime() >> 4;
}

// Clear the two dwords after the header.
struct Obj_006C9D20 {
    int unknown_00;
    int unknown_04;
    int unknown_08;
    void FUN_006C9D20();
};
GG_STATIC_ASSERT(offsetof(Obj_006C9D20, unknown_08) == 0x08);
// FUNCTION: GAMEMD 0x006C9D20
void Obj_006C9D20::FUN_006C9D20()
{
    unknown_04 = 0;
    unknown_08 = 0;
}

// A value inside the half-open range [low, high).
// GLOBAL: GAMEMD 0x7E1748
extern const float DAT_007E1748;
// GLOBAL: GAMEMD 0x7E2AC8
extern const float DAT_007E2AC8;
struct Obj_0074FFC0 {
    float unknown_00;
    bool FUN_0074FFC0() const;
};
// FUNCTION: GAMEMD 0x0074FFC0
bool Obj_0074FFC0::FUN_0074FFC0() const
{
    return unknown_00 >= DAT_007E1748 && unknown_00 < DAT_007E2AC8;
}

// Three-component equality.
struct Obj_00769510 {
    int unknown_00;
    int unknown_04;
    int unknown_08;
    bool FUN_00769510(const Obj_00769510* other) const;
};
GG_STATIC_ASSERT(offsetof(Obj_00769510, unknown_08) == 0x08);
// FUNCTION: GAMEMD 0x00769510
bool Obj_00769510::FUN_00769510(const Obj_00769510* other) const
{
    return unknown_00 == other->unknown_00 && unknown_04 == other->unknown_04 && unknown_08 == other->unknown_08;
}

// The character at an index of a wide string, or zero past its end.
// LIBRARY: GAMEMD 0x7CA405 (decl; reloc) -- wcslen.
unsigned int __cdecl FUN_007CA405(const unsigned short* text);
struct Obj_007B7150 {
    unsigned short* unknown_00;
    unsigned short FUN_007B7150(unsigned int index) const;
};
// FUNCTION: GAMEMD 0x007B7150
unsigned short Obj_007B7150::FUN_007B7150(unsigned int index) const
{
    if (index < FUN_007CA405(unknown_00)) {
        return unknown_00[index];
    }
    return 0;
}

// Forward a by-value rectangle to the held surface's fill slot (slot 5).
struct Rect_007BCF90 {
    int unknown_00;
    int unknown_04;
    int unknown_08;
    int unknown_0C;
};
struct Surface_007BCF90 {
    virtual void vf_00(); virtual void vf_01(); virtual void vf_02(); virtual void vf_03(); virtual void vf_04();
    virtual bool vf_05(Rect_007BCF90* area, int color);
};
struct Obj_007BCF90 {
    unsigned char unknown_00[0x14];
    Surface_007BCF90* unknown_14;
    bool FUN_007BCF90(unsigned short color, Rect_007BCF90 area);
};
GG_STATIC_ASSERT(offsetof(Obj_007BCF90, unknown_14) == 0x14);
// FUNCTION: GAMEMD 0x007BCF90
bool Obj_007BCF90::FUN_007BCF90(unsigned short color, Rect_007BCF90 area)
{
    return unknown_14->vf_05(&area, color);
}
