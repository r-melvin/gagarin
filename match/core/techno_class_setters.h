// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly). Names cross-checked against
//   YRpp TechnoClass.h / ObjectClass.h (consult-only, no LICENSE; every offset
//   reconfirmed numerically below from the matched bodies).
//
// This TU matches three tiny TechnoClass setters. Only the members the matched
// bodies touch are modelled; the full layout is the committed _layout spine /
// P2. Confirmed offsets:
//   * InOpenToppedTransport +0x82  (ObjectClass byte; ExitedOpenTopped writes
//     `MOV byte ptr [EAX+0x82],0`)  — matches _layout/object_class.h
//   * CurrentGattlingStage  +0x140 (int; SetCurrentWeaponStage writes
//     `MOV [ECX+0x140],EAX`)        — matches _layout/techno_class.h
//   * ArchiveTarget         +0x218 (AbstractClass*; SetArchiveTarget writes
//     `MOV [ECX+0x218],EAX`)        — matches _layout/techno_class.h
#ifndef GG_MATCH_CORE_TECHNO_CLASS_SETTERS_H
#define GG_MATCH_CORE_TECHNO_CLASS_SETTERS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#ifndef NULL
#define NULL 0
#endif

class AbstractClass;

// ---------------------------------------------------------------------------
// TechnoClass — minimal offset-pinned model for the three setters. The pad gaps
// stand in for the full RadioClass/MissionClass/ObjectClass/TechnoClass spine
// (see match/_layout/techno_class.h); only the three touched members are named.
// ---------------------------------------------------------------------------
class TechnoClass
{
public:
    // Declared ascending by retail address (reccmp/isle TU discipline).
    void SetArchiveTarget(AbstractClass* pTarget);    // GAMEMD 0x70C610 __thiscall
    void SetCurrentWeaponStage(int idx);              // GAMEMD 0x70DDD0 __thiscall
    int  SetGattlingValue(int value);                 // GAMEMD 0x70DE00 __thiscall
    void ExitedOpenTopped(TechnoClass* pWho);         // GAMEMD 0x7104A0 __thiscall

    char           _pad_00[0x82];          // +0x000 .. +0x081
    unsigned char  InOpenToppedTransport;  // +0x082  (ObjectClass bool)
    char           _pad_83[0x140 - 0x83];  // +0x083 .. +0x13F
    int            CurrentGattlingStage;   // +0x140
    int            GattlingValue;          // +0x144  (SetGattlingValue writes
                                           //          `MOV [ECX+0x144],EAX`)
    char           _pad_148[0x218 - 0x148];// +0x148 .. +0x217
    AbstractClass* ArchiveTarget;          // +0x218
};

GG_STATIC_ASSERT(offsetof(TechnoClass, InOpenToppedTransport) == 0x82);
GG_STATIC_ASSERT(offsetof(TechnoClass, CurrentGattlingStage)  == 0x140);
GG_STATIC_ASSERT(offsetof(TechnoClass, ArchiveTarget)         == 0x218);

#endif  // GG_MATCH_CORE_TECHNO_CLASS_SETTERS_H
