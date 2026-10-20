// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Every offset below is read from the user's retail gamemd.exe v1.001 with
//   the local Ghidra CLI. The three bodies in this TU are the base
//   implementations of three adjacent TechnoClass voice-response virtuals, and
//   their slot numbers were confirmed by reading the AircraftClass vtable out
//   of the binary rather than from any document:
//
//     ghidra memory read 0x7E22A0 4      -> complete object locator 0x007FB4C0
//     ghidra memory read 0x007FB4C0 16   -> +0xC type descriptor 0x00817B90
//     ghidra memory read 0x00817B90 40   -> ".?AVAircraftClass@@"   (RTTI proof)
//     vtable 0x7E22A4  +0x354 = 0x00708D90   QueueVoice(int)
//                      +0x358 = 0x00709020   VoiceEnter      (this TU)
//                      +0x35C = 0x00709060   VoiceHarvest    (this TU)
//                      +0x364 = 0x00708DC0   VoiceCapture    (this TU)
//                      +0x368 = 0x00708FC0   VoiceMove
//                      +0x084 = 0x006F3270   GetTechnoType()
//
//   The *names* come from the TechnoTypeClass member each body tests, which is
//   the only evidence that separates them:
//     0x00708DC0 tests type+0x55C  VoiceCapture
//     0x00709020 tests type+0x558  VoiceEnter
//     0x00709060 tests type+0x57C  VoiceHarvest
//   and those three offsets agree with the committed spine
//   match/_layout/techno_type_class.h lines 166-175.
//
//   NOTE, recorded because the seed disagrees: the private worklist seed
//   names these three technoSetMissionRecharge / technoSetMissionDeath /
//   technoSetMissionAltDeath. That is wrong — no body here writes a mission
//   field; each reads a voice index out of the type and hands it to the
//   QueueVoice slot. docs/decomp_spec/vtable_map_techno.md lines 118-121 have
//   it right.
#ifndef GG_MATCH_CORE_TECHNO_CLASS_VOICE_METHODS_H
#define GG_MATCH_CORE_TECHNO_CLASS_VOICE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class TechnoClass;
struct TechnoVoiceVtbl;

// TechnoTypeClass, as far as this TU reads it: three `int` voice indices, each
// a VocClass list index or -1 for "this type has no such voice".
class TechnoTypeClass
{
public:
    char _pad_000[0x558];    // +0x000 .. +0x557
    int  VoiceEnter;         // +0x558
    int  VoiceCapture;       // +0x55C
    char _pad_560[0x57C - 0x560];
    int  VoiceHarvest;       // +0x57C
};
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, VoiceEnter)   == 0x558);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, VoiceCapture) == 0x55C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, VoiceHarvest) == 0x57C);

// TechnoClass, as far as this TU reads it: the primary vptr alone. Every other
// access in the three bodies is a vtable dispatch.
class TechnoClass
{
public:
    // Declared ascending by retail address (reccmp/isle TU discipline).
    void VoiceCapture();    // GAMEMD 0x708DC0  slot +0x364
    void VoiceEnter();      // GAMEMD 0x709020  slot +0x358
    void VoiceHarvest();    // GAMEMD 0x709060  slot +0x35C

    TechnoVoiceVtbl* Vfptr;    // +0x000
};
GG_STATIC_ASSERT(offsetof(TechnoClass, Vfptr) == 0x000);

// The class has to be complete before these typedefs, or VC6 falls back to the
// multiple-inheritance member-pointer form and emits a `this` adjustment.
typedef TechnoTypeClass* (TechnoClass::*GetTechnoTypeFn)();
typedef void             (TechnoClass::*QueueVoiceFn)(int);
typedef void             (TechnoClass::*VoiceFn)();

struct TechnoVoiceVtbl
{
    char            _pad_000[0x084];
    GetTechnoTypeFn At_84;                       // +0x084 GetTechnoType()
    char            _pad_088[0x354 - 0x088];
    QueueVoiceFn    At_354;                      // +0x354 QueueVoice(int)
    VoiceFn         At_358;                      // +0x358 VoiceEnter()
    char            _pad_35C[0x368 - 0x35C];
    VoiceFn         At_368;                      // +0x368 VoiceMove()
};
GG_STATIC_ASSERT(offsetof(TechnoVoiceVtbl, At_84)  == 0x084);
GG_STATIC_ASSERT(offsetof(TechnoVoiceVtbl, At_354) == 0x354);
GG_STATIC_ASSERT(offsetof(TechnoVoiceVtbl, At_358) == 0x358);
GG_STATIC_ASSERT(offsetof(TechnoVoiceVtbl, At_368) == 0x368);

#endif // GG_MATCH_CORE_TECHNO_CLASS_VOICE_METHODS_H
