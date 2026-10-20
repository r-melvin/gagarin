// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and offsets from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (0x6F3280, 0x6F4A70).
//
//   NAMING: both bodies keep their raw `FUN_` placeholder. CLAUDE.md sanctions
//   that as a transitional name, and it is the honest one here — the receiver
//   is TechnoClass (both sit in the 0x6Fxxxx TechnoClass run and both take the
//   receiver in ECX with a TechnoClass member access), but neither behaviour is
//   pinned to a Westwood name by anything better than a private-reference guess
//   ("technoSelectNavalTargeting", "technoClickedMission"), and neither guess
//   is supported by what the bodies actually read.
//
//   Slots reached, from docs/decomp_spec/vtable_map_techno.md and consistent
//   with the bytes:
//     +0x084  GetTechnoType()             -> TechnoTypeClass*
//     +0x184  GetCurrentMission()         -> int   (line 188, HIGH)
//     +0x274  TransmitMessage(int)        -> int   (line 315, RadioClass)
//
//   Member offsets confirmed numerically:
//     TechnoClass  +0x418  IsTether    `MOV AL,[ESI+0x418]` — agrees with the
//                                      committed spine match/_layout/techno_class.h:325
//     TechnoTypeClass +0xC94  a bool the first body gates on. This offset is
//                             NOT in match/_layout/techno_type_class.h, whose
//                             modelled span stops short of it; it is recorded
//                             here as unknown_C94 rather than named.
#ifndef GG_MATCH_CORE_TECHNO_CLASS_MISSION_GATE_METHODS_H
#define GG_MATCH_CORE_TECHNO_CLASS_MISSION_GATE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class TechnoClass;
struct TechnoGateVtbl;

// TechnoTypeClass — only the byte at +0xC94 is read from this TU.
class TechnoTypeClass
{
public:
    char          _pad_000[0xC94];    // +0x000
    unsigned char unknown_C94;        // +0xC94
};
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, unknown_C94) == 0xC94);

class TechnoClass
{
public:
    // Declared ascending by retail address (reccmp/isle TU discipline).
    bool FUN_006F3280();               // GAMEMD 0x6F3280
    bool FUN_006F4A70(int param);      // GAMEMD 0x6F4A70

    // FUNCTION: GAMEMD 0x5F5850 (decl; reloc) — the ObjectClass-level base the
    // second body delegates to first; reached by a direct CALL with the
    // receiver in ECX and one stack argument, so an ordinary __thiscall member.
    bool BaseStep_005F5850(int param);

    TechnoGateVtbl* Vfptr;                     // +0x000
    char            _pad_004[0x418 - 0x004];
    unsigned char   IsTether;                  // +0x418
};
GG_STATIC_ASSERT(offsetof(TechnoClass, Vfptr)    == 0x000);
GG_STATIC_ASSERT(offsetof(TechnoClass, IsTether) == 0x418);

// The classes have to be complete before these typedefs, or VC6 falls back to
// the multiple-inheritance member-pointer form and emits a `this` adjustment.
typedef TechnoTypeClass* (TechnoClass::*GetTechnoTypeFn)();
typedef int              (TechnoClass::*GetCurrentMissionFn)();
typedef int              (TechnoClass::*TransmitMessageFn)(int);

struct TechnoGateVtbl
{
    char                _pad_000[0x084];
    GetTechnoTypeFn     At_84;                     // +0x084
    char                _pad_088[0x184 - 0x088];
    GetCurrentMissionFn At_184;                    // +0x184
    char                _pad_188[0x274 - 0x188];
    TransmitMessageFn   At_274;                    // +0x274
};
GG_STATIC_ASSERT(offsetof(TechnoGateVtbl, At_84)  == 0x084);
GG_STATIC_ASSERT(offsetof(TechnoGateVtbl, At_184) == 0x184);
GG_STATIC_ASSERT(offsetof(TechnoGateVtbl, At_274) == 0x274);

#endif // GG_MATCH_CORE_TECHNO_CLASS_MISSION_GATE_METHODS_H
