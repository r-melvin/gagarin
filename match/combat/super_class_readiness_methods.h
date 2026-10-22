// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x6CC2B0: `MOV AL,[ECX+0x70]` (IsSuspended),
//   `MOV EAX,[ECX+0x28]` (Type) with `MOV DL,[EAX+0xE5]` (UseChargeDrain),
//   `MOV ECX,[ECX+0x7C]` (ChargeDrainState, the switch value) and
//   `MOV AL,[ECX+0x6F]` (IsReady). The four label strings and the source
//   file name are pushed as immediates (0x83FB2C "TXT_HOLD", 0x8424EC
//   "TXT_CHARGING", 0x81B454 "TXT_READY", 0x8424FC "TXT_FIRESTORM_ON",
//   0x842510 "D:\ra2mdpost\Super.CPP", all reconfirmed by `ghidra memory
//   read`) into the __fastcall lookup at 0x734E60. The member run agrees with
//   match/combat/super_class_methods.h (not edited; re-derived here so the TU
//   stands alone). YRpp names only: SuperClass::NameReadiness,
//   SuperWeaponTypeClass::UseChargeDrain.
#ifndef GG_MATCH_COMBAT_SUPER_CLASS_READINESS_METHODS_H
#define GG_MATCH_COMBAT_SUPER_CLASS_READINESS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// VC6 has no built-in wchar_t; it is a typedef for unsigned short.
typedef unsigned short gg_wchar;

// STRING: GAMEMD 0x842510 — the source file the lookup is told to blame.
extern const char DAT_00842510[];
// STRING: GAMEMD 0x83FB2C — "TXT_HOLD".
extern const char DAT_0083FB2C[];
// STRING: GAMEMD 0x8424EC — "TXT_CHARGING".
extern const char DAT_008424EC[];
// STRING: GAMEMD 0x81B454 — "TXT_READY".
extern const char DAT_0081B454[];
// STRING: GAMEMD 0x8424FC — "TXT_FIRESTORM_ON".
extern const char DAT_008424FC[];

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) — resolve a label to its localised
// text. __fastcall with two further arguments on the stack.
gg_wchar* FUN_00734E60(const char* label, int flags,
                                 const char* file, int line);

// SuperWeaponTypeClass — only UseChargeDrain @0xE5 is read here.
class SuperWeaponTypeClass
{
public:
    char _pad000[0xE5];       // +0x0000
    bool UseChargeDrain;      // +0x00E5
};
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, UseChargeDrain) == 0xE5);

// SuperClass : AbstractClass — a per-house superweapon instance.
class SuperClass
{
public:
    char                  _base[0x28];         // +0x0000  AbstractClass + CustomChargeTime
    SuperWeaponTypeClass* Type;                // +0x0028
    char                  _pad2C[0x6F - 0x2C]; // +0x002C
    bool                  IsReady;             // +0x006F
    bool                  IsSuspended;         // +0x0070
    char                  _pad71[0x7C - 0x71]; // +0x0071
    int                   ChargeDrainState;    // +0x007C

    // FUNCTION: GAMEMD 0x6CC2B0
    gg_wchar* NameReadiness() const;
};
GG_STATIC_ASSERT(offsetof(SuperClass, Type)             == 0x28);
GG_STATIC_ASSERT(offsetof(SuperClass, IsReady)          == 0x6F);
GG_STATIC_ASSERT(offsetof(SuperClass, IsSuspended)      == 0x70);
GG_STATIC_ASSERT(offsetof(SuperClass, ChargeDrainState) == 0x7C);

#endif  // GG_MATCH_COMBAT_SUPER_CLASS_READINESS_METHODS_H
