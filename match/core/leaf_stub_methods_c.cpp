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
#include "../_layout/map_0087f7e8.h"

#include "../_layout/guid_007e36c0.h"
// GLOBAL: GAMEMD 0x7E36C0
extern const Guid_007E36C0 DAT_007E36C0;

// COM error raiser (COMSUPP library, 0x7DC720).
void __stdcall FUN_007DC720(unsigned int hr);

// Slot 0 of the object's own interface table, called on the object with the
// interface id at 0x7E36C0 and the caller's out pointer.
#include "../_layout/iface_00429400.h"

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
#include "../_layout/obj_004a1d70.h"
// FUNCTION: GAMEMD 0x004A1D70
void Obj_004A1D70::FUN_004A1D70(int value)
{
    int dword = value;
    FUN_004A1DE0(&dword, 4);
}

#include "../_layout/obj_004a31f0.h"
// FUNCTION: GAMEMD 0x004A31F0
bool Obj_004A31F0::FUN_004A31F0(void* arg)
{
    if (arg != 0) {
        FUN_007DC720(0x80004003);
    }
    return unknown_00 == 0;
}

// A four-integer record built from its four arguments.
#include "../_layout/quad_0054a120.h"

// The index of an element pointer within a vector of 36-byte records.
#include "../_layout/obj_00589a30.h"
// FUNCTION: GAMEMD 0x00589A30
unsigned int Obj_00589A30::FUN_00589A30(const void* item) const
{
    if (!unknown_0C) {
        return 0;
    }
    return ((unsigned int)item - (unsigned int)unknown_04) / 36;
}

// Read one float of an inline array by index.
#include "../_layout/obj_00645d10.h"

// Run a handler over every entry of a global table of objects.
#include "../_layout/obj_0065fe00.h"
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
#include "../_layout/obj_00681080.h"
// FUNCTION: GAMEMD 0x00681080
void Obj_00681080::FUN_00681080(int value)
{
    unknown_00 = value;
}

// The held interface pointer, raising E_POINTER when there is none.
#include "../_layout/obj_00683030.h"
// FUNCTION: GAMEMD 0x00683030
void* Obj_00683030::FUN_00683030()
{
    if (unknown_00 == 0) {
        FUN_007DC720(0x80004003);
    }
    return unknown_00;
}

#include "../_layout/obj_006a3e30.h"
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
#include "../_layout/obj_006c9d20.h"
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
#include "../_layout/obj_0074ffc0.h"
// FUNCTION: GAMEMD 0x0074FFC0
bool Obj_0074FFC0::FUN_0074FFC0() const
{
    return unknown_00 >= DAT_007E1748 && unknown_00 < DAT_007E2AC8;
}

// Three-component equality.
#include "../_layout/obj_00769510.h"
// FUNCTION: GAMEMD 0x00769510
bool Obj_00769510::FUN_00769510(const Obj_00769510* other) const
{
    return unknown_00 == other->unknown_00 && unknown_04 == other->unknown_04 && unknown_08 == other->unknown_08;
}

// The character at an index of a wide string, or zero past its end.
// LIBRARY: GAMEMD 0x7CA405 (decl; reloc) -- wcslen.
unsigned int __cdecl FUN_007CA405(const unsigned short* text);
#include "../_layout/obj_007b7150.h"
// FUNCTION: GAMEMD 0x007B7150
unsigned short Obj_007B7150::FUN_007B7150(unsigned int index) const
{
    if (index < FUN_007CA405(unknown_00)) {
        return unknown_00[index];
    }
    return 0;
}

// Forward a by-value rectangle to the held surface's fill slot (slot 5).
#include "../_layout/rect_007bcf90.h"
#include "../_layout/surface_007bcf90.h"
#include "../_layout/obj_007bcf90.h"
// FUNCTION: GAMEMD 0x007BCF90
bool Obj_007BCF90::FUN_007BCF90(unsigned short color, Rect_007BCF90 area)
{
    return unknown_14->vf_05(&area, color);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB04DAC
Obj_0065FE00** DAT_00B04DAC;
// GLOBAL: GAMEMD 0xB04DB8
int DAT_00B04DB8;
// GLOBAL: GAMEMD 0x7E1748
extern const float DAT_007E1748 = 0.0f;
// END defined globals
