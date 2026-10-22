// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check | YRpp-cross-check | behaviour-confirmed-name
//   Trivial 3-20 byte leaf functions from multiple classes. Each is a simple
//   accessor (getter/setter/constructor) matching one of the proven recipes
//   identified from retail bytes. Offsets numerically confirmed against the
//   disassembly via local Ghidra CLI.

#ifndef GG_MATCH_CORE_LEAF_BATCH_METHODS_H
#define GG_MATCH_CORE_LEAF_BATCH_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ============================================================================
// SaveGameInformation - entry at 0x00681090
// ============================================================================
struct SaveGameInformation_00681090
{
    void* Pad0;              // +0x0000
    void* Pad4;              // +0x0004
    void* ScenarioDescPtr;   // +0x0008
    char _pad0c[256];
    char _pad10c[124];       // 256 + 124 = 380, total with Pad0/Pad4/DescPtr = 12+380 = 392
    int Campaign;            // +0x0188
    int ScenarioNumber;      // +0x018C
    char _pad190[256];
    char _pad290[256];
    char _pad390[96];        // 256+256+96 = 608, total = 392+4+4+608 = 1008
    int GameType;            // +0x03F0

    // FUNCTION: GAMEMD 0x00681090
    void* GetPad0() const;
    // FUNCTION: GAMEMD 0x006810C0
    void* GetScenarioDescriptionPtr() const;
    // FUNCTION: GAMEMD 0x00681100
    void* GetPlayerHousePtr() const;
    // FUNCTION: GAMEMD 0x00681120
    int GetCampaign() const;
    // FUNCTION: GAMEMD 0x00681140
    int FUN_00681140() const;
    // FUNCTION: GAMEMD 0x006812D0
    int GetGameType() const;
};

GG_STATIC_ASSERT(offsetof(SaveGameInformation_00681090, Pad0) == 0);
GG_STATIC_ASSERT(offsetof(SaveGameInformation_00681090, ScenarioDescPtr) == 8);
GG_STATIC_ASSERT(offsetof(SaveGameInformation_00681090, Campaign) == 392);
GG_STATIC_ASSERT(offsetof(SaveGameInformation_00681090, ScenarioNumber) == 396);
GG_STATIC_ASSERT(offsetof(SaveGameInformation_00681090, GameType) == 1008);

// ============================================================================
// VQASession - entry at 0x00759E50
// ============================================================================
struct VQASession_00759E50
{
    char _pad0[256];
    char _pad100[256];
    char _pad200[256];
    char _pad300[256];
    char _pad400[256];
    char _pad500[12];
    int ColorMode;           // +0x050C
    char _pad510[8];
    int Width;               // +0x0518
    int Height;              // +0x051C
    char _pad520[48];
    char Flags;              // +0x0550

    // FUNCTION: GAMEMD 0x00759E50
    void Resume();
    // FUNCTION: GAMEMD 0x00759EA0
    int GetColorMode() const;
    // FUNCTION: GAMEMD 0x00759F70
    int GetWidth() const;
    // FUNCTION: GAMEMD 0x00759F80
    int GetHeight() const;
};

GG_STATIC_ASSERT(offsetof(VQASession_00759E50, ColorMode) == 1292);
GG_STATIC_ASSERT(offsetof(VQASession_00759E50, Width) == 1304);
GG_STATIC_ASSERT(offsetof(VQASession_00759E50, Height) == 1308);
GG_STATIC_ASSERT(offsetof(VQASession_00759E50, Flags) == 1360);

// ============================================================================
// TechnoClass subset
// ============================================================================
struct TechnoClass_00707000
{
    char _pad0[256];
    char _pad100[36];        // 256+36 = 292
    int CurrentTurret;       // +0x0124 (292)
    char _pad128[24];        // 296 + 24 = 320
    int CaptureTarget;       // +0x0140 (320)
    int Ammo;                // +0x0144 (324)

    // FUNCTION: GAMEMD 0x0070DCF0
    int GetCurrentTurret() const;
    // FUNCTION: GAMEMD 0x0070DDC0
    int GetCaptureTarget() const;
    // FUNCTION: GAMEMD 0x0070DDF0
    int GetAmmo() const;
};

GG_STATIC_ASSERT(offsetof(TechnoClass_00707000, CurrentTurret) == 292);
GG_STATIC_ASSERT(offsetof(TechnoClass_00707000, CaptureTarget) == 320);
GG_STATIC_ASSERT(offsetof(TechnoClass_00707000, Ammo) == 324);

// ============================================================================
// SelectableClass subset - entry at 0x006DC420
// ============================================================================
struct SelectableClass_006D0000
{
    char _pad0[256];
    char _pad100[256];
    char _pad200[256];
    char _pad300[256];
    char _pad400[256];
    char _pad500[256];
    char _pad600[256];
    char _pad700[256];
    char _pad800[256];
    char _pad900[256];
    char _padA00[256];
    char _padB00[256];
    char _padC00[256];       // 256*13 = 3328
    char _padD00[176];       // 3328+176 = 3504
    int SelectableCount;     // +0x0DB0

    // FUNCTION: GAMEMD 0x006DC420
    int GetSelectableCount() const;
};

GG_STATIC_ASSERT(offsetof(SelectableClass_006D0000, SelectableCount) == 3504);

#endif  // GG_MATCH_CORE_LEAF_BATCH_METHODS_H
