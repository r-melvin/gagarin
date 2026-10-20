// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp or the
//   seed map.
#ifndef GG_MATCH_CORE_SMALL_MISC4_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC4_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// memset as a declared function rather than the intrinsic: with a
// compile-time-constant size cl expands <string.h>'s memset inline to
// `REP STOSD`, where retail issues a real call.
extern "C" void* __cdecl FUN_007C91D0(void* dst, int fill, unsigned int n);

// GLOBAL: GAMEMD 0x87E730 — the acquire count 0x407020 raises.
extern int DAT_0087E730;
void __cdecl FUN_0040A950();   // GAMEMD 0x40A950 — teardown on the last release

// FUNCTION: GAMEMD 0x407040 — release; tear down on the transition to zero.
void __cdecl FUN_00407040();

// Four vtable pointers written back to back: a multiple-inheritance object
// reinstalling every sub-object's vptr.
extern char VT_007E1F50[];   // VTABLE: GAMEMD 0x7E1F50
extern char VT_007E1F34[];   // VTABLE: GAMEMD 0x7E1F34
extern char VT_007E1F2C[];   // VTABLE: GAMEMD 0x7E1F2C
extern char VT_007E1F24[];   // VTABLE: GAMEMD 0x7E1F24

struct Obj_004101F0
{
    char* vt0;   // +0x0000
    char* vt1;   // +0x0004
    char* vt2;   // +0x0008
    char* vt3;   // +0x000C

    // FUNCTION: GAMEMD 0x4101F0
    void FUN_004101F0();
};

struct Inner_00408000 { char _pad[0x14]; int at14; int at18; };
struct Obj_00408000c
{
    char             _pad00[0xC];
    int              Flags;        // +0x000C
    char             _pad10[0x4];
    Inner_00408000*  unknown_14;   // +0x0014

    // FUNCTION: GAMEMD 0x4080D0
    int FUN_004080D0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00408000c, unknown_14) == 0x14);

// The 0x50-byte fill at +0xA4 spans 0xA4..0xF3, so the byte cleared afterwards
// at +0xF3 is the *last* byte of that same buffer, not a separate field. This
// is a fill-then-terminate, which is why the store comes after the memset.
struct Obj_00408080
{
    char _pad000[0xA4];
    char Buffer[0x50];   // +0x00A4 .. +0x00F3

    // FUNCTION: GAMEMD 0x408080
    void __fastcall FUN_00408080(int fill);
};
GG_STATIC_ASSERT(offsetof(Obj_00408080, Buffer) == 0xA4);
GG_STATIC_ASSERT(sizeof(Obj_00408080) == 0xF4);

void __fastcall FUN_004072D0b(void* self);   // GAMEMD 0x4072D0

struct Obj_004085E0
{
    char _pad00[0xC];
    int  unknown_0C;   // +0x000C
    int  unknown_10;   // +0x0010
    int  unknown_14;   // +0x0014

    // FUNCTION: GAMEMD 0x4085E0
    void __fastcall FUN_004085E0(int a, int b);
};
GG_STATIC_ASSERT(offsetof(Obj_004085E0, unknown_14) == 0x14);

// Zero-argument virtual at +0x400 returning bool.
// CLASS IDENTITY (whole-image RTTI sweep, docs/rtti_sweep.md; renamed from
// the raw `Obj_` placeholder). BuildingClass's own vtable is 0x7E3EBC.
//   0x458DB0 -> BuildingClass slot 171 (byte-off 0x2AC).
// No other table in the image holds it, so the slot is declared on
// BuildingClass rather than inherited. The METHOD name is still unknown; only the
// class is proven, so the `FUN_<addr>` member name stays a placeholder.
struct BuildingClass_00458DB0;
typedef bool (__fastcall* Slot400)(BuildingClass_00458DB0*);
#define SLOT_400(o) ((*(Slot400*)(*(char**)(o) + 0x400))(o))
bool __fastcall FUN_00701120(BuildingClass_00458DB0* self);   // GAMEMD 0x701120

// CLASS IDENTITY (whole-image RTTI sweep, docs/rtti_sweep.md; renamed from
// the raw `Obj_`/`Sub_`/`Subject_` placeholder). BuildingClass's own vtable is 0x7E3EBC.
//   0x458DB0 -> BuildingClass slot 171 (byte-off 0x2AC).
// That table is the only table in the image that holds it, so the slot is
// declared on BuildingClass and not inherited from TechnoClass/ObjectClass above it.
// The METHOD name is still unknown; only the class is proven, so the
// `FUN_<addr>` member name stays as the transitional placeholder.
struct BuildingClass_00458DB0
{
    // FUNCTION: GAMEMD 0x458DB0
    bool FUN_00458DB0();
};

// CLASS IDENTITY (whole-image RTTI sweep, docs/rtti_sweep.md; renamed from
// the raw `Obj_` placeholder). BuildingClass's own vtable is 0x7E3EBC.
//   0x459C00 -> BuildingClass slot 79 (byte-off 0x13C).
// No other table in the image holds it, so the slot is declared on
// BuildingClass rather than inherited. The METHOD name is still unknown; only the
// class is proven, so the `FUN_<addr>` member name stays a placeholder.
struct BuildingClass_00459C00;
bool __fastcall FUN_00465D40(void* self);            // GAMEMD 0x465D40
void __fastcall FUN_006FC030(BuildingClass_00459C00* self);    // GAMEMD 0x6FC030

struct BuildingClass_00459C00
{
    char  _pad000[0x520];
    void* unknown_520;   // +0x0520

    // FUNCTION: GAMEMD 0x459C00
    void FUN_00459C00();
};
GG_STATIC_ASSERT(offsetof(BuildingClass_00459C00, unknown_520) == 0x520);

#endif  // GG_MATCH_CORE_SMALL_MISC4_METHODS_H
