// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets from the user's retail gamemd.exe v1.001 (Ghidra disasm):
//   - MissionControlClass ctor FUN_0x5B3700 init writes:
//       ArrayIndex@0x00=-1, NoThreat@0x04=0, Zombie@0x05=0, Recruitable@0x06=1,
//       Paralyzed@0x07=0, Retaliate@0x08=1, Scatter@0x09=1,
//       Rate@0x10=0.016 (0x3F90624D D2F1A9FC), AARate@0x18=0.016.
//       Last write @0x18(+8) => sizeof == 0x20.
//   - IsRecruitableMission @0x5B36E0: `SHL ECX,5` (mission*0x20) +
//       `MOV AL,[ECX+0xA8E3AE]` => Array base 0xA8E3A8, Recruitable@0x06.
//   Cross-checked vs YRpp `class MissionControlClass`.
//
// MissionControlClass — the per-Mission control record (one per Mission enum
// value). The global Array @0xA8E3A8 holds 0x20-byte records; a parallel
// name-pointer table @0x816CAC holds the mission names.
#ifndef GG_MATCH_CORE_MISSION_CLASS_METHODS_H
#define GG_MATCH_CORE_MISSION_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct MissionControlClass
{
    int    ArrayIndex;    // +0x00
    bool   NoThreat;      // +0x04
    bool   Zombie;        // +0x05
    bool   Recruitable;   // +0x06
    bool   Paralyzed;     // +0x07
    bool   Retaliate;     // +0x08
    bool   Scatter;       // +0x09
    char   pad_0A[6];     // +0x0A  (align Rate to 0x10)
    double Rate;          // +0x10
    double AARate;        // +0x18

    // Constructor at GAMEMD 0x5B3700; implemented in mission_class_methods.cpp.
    MissionControlClass();

    // Declared ascending by retail address (reccmp/isle TU discipline).
    static bool IsRecruitableMission(int mission);  // GAMEMD 0x5B36E0
    const char*            GetName();                          // GAMEMD 0x5B3740
    static int  FindIndex(const char* name);        // GAMEMD 0x5B3910
    static const char* NameOf(int mission);         // GAMEMD 0x5B3950
};

GG_STATIC_ASSERT(offsetof(MissionControlClass, ArrayIndex)  == 0x00);
GG_STATIC_ASSERT(offsetof(MissionControlClass, NoThreat)    == 0x04);
GG_STATIC_ASSERT(offsetof(MissionControlClass, Zombie)      == 0x05);
GG_STATIC_ASSERT(offsetof(MissionControlClass, Paralyzed)   == 0x07);
GG_STATIC_ASSERT(offsetof(MissionControlClass, Retaliate)   == 0x08);
GG_STATIC_ASSERT(offsetof(MissionControlClass, Scatter)     == 0x09);
GG_STATIC_ASSERT(offsetof(MissionControlClass, Recruitable) == 0x06);
GG_STATIC_ASSERT(offsetof(MissionControlClass, Rate)        == 0x10);
GG_STATIC_ASSERT(offsetof(MissionControlClass, AARate)      == 0x18);
GG_STATIC_ASSERT(sizeof(MissionControlClass)                == 0x20);

// GLOBAL: GAMEMD 0x00A8E3A8
// 0x5B36E8/0x5B3A06 scale indices by 0x20; the native global constructor
// 0x4E7CF0 constructs 32 records with the constructor at 0x5B3700.
extern MissionControlClass DAT_00A8E3A8[32];
GG_STATIC_ASSERT(sizeof(DAT_00A8E3A8) == 0x400);

#endif  // GG_MATCH_CORE_MISSION_CLASS_METHODS_H
