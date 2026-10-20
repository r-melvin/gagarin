// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 through
//   the local Ghidra CLI at 0x5FDD20: the overlay index arrives in ECX and
//   indexes OverlayTypeClass::Array.Items at 0xA83D84; the type's Tiberium
//   byte is [EAX+0x2A9] and its 0x31-byte Name at EAX+0x64 (the `REP MOVSD`
//   of 12 dwords plus `MOVSB` into a 0x34-byte argument block ahead of CALL
//   0x4068E0 with the string 0x833490). TiberiumClass::Array.Items at
//   0xB0F4EC and .Count at 0xB0F4F8; per tiberium Image [EAX+0xE0] whose
//   ArrayIndex is [EDX+0x294], NumImages [EAX+0xE8], NumSlopes [EAX+0xEC]
//   and the returned ArrayIndex [EAX+0x98]. Names cross-checked against YRpp
//   OverlayClass.h / OverlayTypeClass.h / TiberiumClass.h (consult-only; NO
//   LICENSE; every offset reconfirmed above); the two counts are named
//   positionally after YRpp's member run.
#ifndef GG_MATCH_MAP_OVERLAY_CLASS_TIBERIUM_TYPE_METHODS_H
#define GG_MATCH_MAP_OVERLAY_CLASS_TIBERIUM_TYPE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// AbstractTypeClass::Name — a fixed 0x31-byte string that retail hands to
// the logger by value (the copy is the argument block itself).
struct Name_005FDD20
{
    char Text[0x31];
};
GG_STATIC_ASSERT(sizeof(Name_005FDD20) == 0x31);

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) — the logger, __cdecl; here it
// receives the name struct by value.
void __cdecl FUN_004068E0(const char* format, Name_005FDD20 name);

// STRING: GAMEMD 0x833490 "Overlay %s not really tiberium\n"
extern const char STR_00833490[];

// OverlayTypeClass — Name @0x64, ArrayIndex @0x294, Tiberium @0x2A9.
struct OverlayType_005FDD20
{
    char           _pad000[0x64];         // +0x0000
    Name_005FDD20  Name;                  // +0x0064
    char           _pad095[0x294 - 0x95];
    int            ArrayIndex;            // +0x0294
    char           _pad298[0x2A9 - 0x298];
    char           Tiberium;              // +0x02A9
};
GG_STATIC_ASSERT(offsetof(OverlayType_005FDD20, Name) == 0x64);
GG_STATIC_ASSERT(offsetof(OverlayType_005FDD20, ArrayIndex) == 0x294);
GG_STATIC_ASSERT(offsetof(OverlayType_005FDD20, Tiberium) == 0x2A9);

// GLOBAL: GAMEMD 0xA83D84 — OverlayTypeClass::Array.Items.
extern OverlayType_005FDD20** DAT_00A83D84;

// TiberiumClass — ArrayIndex @0x98, Image @0xE0, NumImages @0xE8,
// NumSlopes @0xEC.
struct Tiberium_005FDD20
{
    char                   _pad000[0x98];      // +0x0000
    int                    ArrayIndex;         // +0x0098
    char                   _pad09C[0xE0 - 0x9C];
    OverlayType_005FDD20*  Image;              // +0x00E0
    int                    NumFrames;          // +0x00E4
    int                    NumImages;          // +0x00E8
    int                    NumSlopes;          // +0x00EC
};
GG_STATIC_ASSERT(offsetof(Tiberium_005FDD20, ArrayIndex) == 0x98);
GG_STATIC_ASSERT(offsetof(Tiberium_005FDD20, Image) == 0xE0);
GG_STATIC_ASSERT(offsetof(Tiberium_005FDD20, NumImages) == 0xE8);
GG_STATIC_ASSERT(offsetof(Tiberium_005FDD20, NumSlopes) == 0xEC);

// GLOBAL: GAMEMD 0xB0F4EC — TiberiumClass::Array.Items.
extern Tiberium_005FDD20** DAT_00B0F4EC;
// GLOBAL: GAMEMD 0xB0F4F8 — TiberiumClass::Array.Count.
extern int DAT_00B0F4F8;

struct OverlayClass
{
    // FUNCTION: GAMEMD 0x5FDD20 — the overlay index arrives in ECX.
    static int __fastcall GetTiberiumType(int idxOverlay);
};

#endif  // GG_MATCH_MAP_OVERLAY_CLASS_TIBERIUM_TYPE_METHODS_H
