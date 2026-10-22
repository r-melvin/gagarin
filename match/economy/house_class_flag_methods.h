// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x4FC060), cross-checked against
//   YRpp (every offset reconfirmed
//   numerically from the disassembly below).
//
// HouseClass-flag — the flag-capture handler:
//   PickedUpFlag   a unit picks up this house's flag (CTF logic)
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_FLAG_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_FLAG_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

typedef unsigned long DWORD;

// ---------------------------------------------------------------------------
// HouseTypeClass shim — only the index @0xB8 is touched.
//
// Confirmed from 0x4FC060: MOV EDX,[ESI+0x34] (HouseClass::Type), then
// MOV EAX,[EDX+0xB8] — the value handed to the carrier as its owner/colour
// index. Full AbstractTypeClass-derived layout is P2.
// ---------------------------------------------------------------------------
class HouseTypeClass
{
public:
    char _layout_pad_P2[0xB8];   // +0x0000
    int  ColorSchemeIndex_B8;    // +0x00B8  (MOV EAX,[EDX+0xB8])
};
GG_STATIC_ASSERT(offsetof(HouseTypeClass, ColorSchemeIndex_B8) == 0xB8);

// ---------------------------------------------------------------------------
// UnitClass shim — the flag carrier. Only InLimbo @0x81 (the not-on-map guard)
// and the owner-index setter @0x740DF0 are touched here.
//
// Confirmed from 0x4FC060: MOV AL,[EDI+0x81]; TEST AL,AL (limbo guard), and
// MOV ECX,EDI / CALL 0x740DF0 with one pushed int argument.
// ---------------------------------------------------------------------------
class UnitClass
{
public:
    char          _layout_pad_P2[0x81];   // +0x0000
    unsigned char InLimbo;                // +0x0081  (bool; ObjectClass::InLimbo)

    // Retail callee we are NOT matching — declared (no body) so cl emits a
    // __thiscall + a normalised reloc. Sets the carrier's owner/colour index.
    void SetOwnerIndex_740DF0(int index);  // GAMEMD 0x740DF0 __thiscall (reloc)
};
GG_STATIC_ASSERT(offsetof(UnitClass, InLimbo) == 0x81);

// ---------------------------------------------------------------------------
// HouseClass — only the members PickedUpFlag touches are modelled; the full
// AbstractClass-derived layout is P2. Each offset is asserted and confirmed
// numerically from the disassembly.
//   Type        @0x34    HouseTypeClass*  (MOV EDX,[ESI+0x34])
//   FlagHolder  @0x53DC  UnitClass*       (MOV/[ESI+0x53DC] read & write)
// ---------------------------------------------------------------------------
class HouseClass
{
public:
    char            _pad0[0x34];                  // +0x0000
    HouseTypeClass* Type;                         // +0x0034
    char            _pad1[0x53DC - (0x34 + 4)];   // +0x0038
    UnitClass*      FlagHolder;                   // +0x53DC

    // PickedUpFlag — declared method we are matching.
    char PickedUpFlag(UnitClass* Who, DWORD dwUnk);  // GAMEMD 0x4FC060 __thiscall

    // Retail callee we are NOT matching — declared (no body) so cl emits a
    // __thiscall + a normalised reloc. Updates the dropped-flag bookkeeping.
    void UpdateFlagCoords(UnitClass* NewCarrier, DWORD dwUnk);  // GAMEMD 0x4FBE40 (reloc)
};
GG_STATIC_ASSERT(offsetof(HouseClass, Type)       == 0x34);
GG_STATIC_ASSERT(offsetof(HouseClass, FlagHolder) == 0x53DC);

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_FLAG_METHODS_H
