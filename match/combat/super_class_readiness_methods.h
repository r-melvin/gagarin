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
#include "../_layout/super_class.h"

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

#endif  // GG_MATCH_COMBAT_SUPER_CLASS_READINESS_METHODS_H
