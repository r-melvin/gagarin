// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x70E000: the two gattling sound controllers at
//   +0x4A4 / +0x4C0 (0x406060 EndLooping and 0x405D40 on each) with their
//   playing flags `[ESI+0x4B8]` / `[ESI+0x4D4]`, `[ESI+0x140]`
//   (CurrentGattlingStage) and `[ESI+0x144]` (GattlingValue), the veterancy
//   gauge at +0x150 handed to 0x750010 in ECX, the GetTechnoType slot
//   `[EAX+0x84]` and GetWeapon slot `[EDX+0x3F8]` (stage * 2), and the type's
//   `[EAX+0xD10]` (RateDown) and the stage tables reached as
//   `[EAX+EDI*4+0xCD8]` / `[EAX+EDI*4+0xCF0]` (WeaponStage / EliteStage at
//   0xCDC / 0xCF4, indexed one below the stage). Names cross-checked against
//   YRpp.
#ifndef GG_MATCH_COMBAT_TECHNO_CLASS_GATTLING_RATE_METHODS_H
#define GG_MATCH_COMBAT_TECHNO_CLASS_GATTLING_RATE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// The "mofo" audio-event controller (0x14 bytes) and its two helpers.
struct AudioController_0070E000
{
    char opaque[0x14];
    // FUNCTION: GAMEMD 0x406060 (decl; reloc) — Audio::EndLooping.
    void EndLooping();
    // FUNCTION: GAMEMD 0x405D40 (decl; reloc) — stop the controller's voice.
    void FUN_00405D40();
};
GG_STATIC_ASSERT(sizeof(AudioController_0070E000) == 0x14);

struct Veterancy_0070E000
{
    char opaque[4];
};
// FUNCTION: GAMEMD 0x750010 (decl; reloc) — gauge is in the elite band.
bool FUN_00750010(Veterancy_0070E000* vet);

// TechnoTypeClass — WeaponStages, the two stage tables, RateDown.
struct TechnoType_0070E000
{
    char _pad000[0xCD8];   // +0x0000
    int  WeaponStages;     // +0x0CD8
    int  WeaponStage[6];   // +0x0CDC
    int  EliteStage[6];    // +0x0CF4
    int  RateUp;           // +0x0D0C
    int  RateDown;         // +0x0D10
};
GG_STATIC_ASSERT(offsetof(TechnoType_0070E000, WeaponStages) == 0xCD8);
GG_STATIC_ASSERT(offsetof(TechnoType_0070E000, WeaponStage)  == 0xCDC);
GG_STATIC_ASSERT(offsetof(TechnoType_0070E000, EliteStage)   == 0xCF4);
GG_STATIC_ASSERT(offsetof(TechnoType_0070E000, RateDown)     == 0xD10);

struct Vtbl_0070E000;

// TechnoClass — the gattling members only.
struct Techno_0070E000
{
    Vtbl_0070E000*            Vptr;                          // +0x0000
    char                      _pad004[0x13C];                // +0x0004
    int                       CurrentGattlingStage;          // +0x0140
    int                       GattlingValue;                 // +0x0144
    char                      _pad148[8];                    // +0x0148
    Veterancy_0070E000        Veterancy;                     // +0x0150
    char                      _pad154[0x4A4 - 0x154];        // +0x0154
    AudioController_0070E000  GattlingSoundController;       // +0x04A4
    unsigned char             IsGattlingSoundPlaying;        // +0x04B8
    char                      _pad4B9[7];                    // +0x04B9
    AudioController_0070E000  UnusedGattlingSoundController; // +0x04C0
    unsigned char             IsUnusedGattlingSoundPlaying;  // +0x04D4

    // FUNCTION: GAMEMD 0x70E000 — TechnoClass::GattlingRateDown.
    void GattlingRateDown(int rate);
};
GG_STATIC_ASSERT(offsetof(Techno_0070E000, CurrentGattlingStage)          == 0x140);
GG_STATIC_ASSERT(offsetof(Techno_0070E000, GattlingValue)                 == 0x144);
GG_STATIC_ASSERT(offsetof(Techno_0070E000, Veterancy)                     == 0x150);
GG_STATIC_ASSERT(offsetof(Techno_0070E000, GattlingSoundController)       == 0x4A4);
GG_STATIC_ASSERT(offsetof(Techno_0070E000, IsGattlingSoundPlaying)        == 0x4B8);
GG_STATIC_ASSERT(offsetof(Techno_0070E000, UnusedGattlingSoundController) == 0x4C0);
GG_STATIC_ASSERT(offsetof(Techno_0070E000, IsUnusedGattlingSoundPlaying)  == 0x4D4);

typedef TechnoType_0070E000* (Techno_0070E000::*Fn84_0070E000)();
typedef void* (Techno_0070E000::*Fn3F8_0070E000)(int index);

struct Vtbl_0070E000
{
    char            _pad000[0x84];           // +0x0000
    Fn84_0070E000   GetTechnoType;           // +0x0084
    char            _pad088[0x3F8 - 0x88];   // +0x0088
    Fn3F8_0070E000  GetWeapon;               // +0x03F8
};
GG_STATIC_ASSERT(offsetof(Vtbl_0070E000, GetTechnoType) == 0x84);
GG_STATIC_ASSERT(offsetof(Vtbl_0070E000, GetWeapon)     == 0x3F8);

#endif  // GG_MATCH_COMBAT_TECHNO_CLASS_GATTLING_RATE_METHODS_H
