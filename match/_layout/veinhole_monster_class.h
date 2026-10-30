// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: VeinholeMonsterClass ctor FUN_0x0074C5B0 (chains ObjectClass ctor
//   FUN_0x005F3900 at offset 0; sizeof(ObjectClass) == 0xAC). The ctor writes
//   every member in the 0xAC..0x107 span.
//   sizeof: `PUSH 0x108` (264) before the ctor call at its allocation site,
//   which is also the value YRpp static_asserts.
//   RTTI: 0x007F66A8 / 0x007F668C / 0x007F6684 / 0x007F667C all resolve to
//   ".?AVVeinholeMonsterClass@@" (stored @0x0074C669..0x0074C67C).
//   Cross-read against YRpp: 14 named members claimed,
//   14 confirmed. No disagreement found.
//
// VeinholeMonsterClass — a vein hole and its spreading veins. Derives
// ObjectClass at offset 0.
#ifndef GG_MATCH_LAYOUT_VEINHOLE_MONSTER_CLASS_H
#define GG_MATCH_LAYOUT_VEINHOLE_MONSTER_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "object_class.h"
#include "mission_class.h"   // CDTimerClass
#include "foot_class.h"      // CellStruct

// VeinholeLogic — the growth-logic block embedded at VeinholeMonsterClass+0xAC.
// Size 0x1C, proven by closure: the ctor writes 0xAC/0xB0/0xB4 (zeroes), a
// CDTimerClass-shaped pair at 0xB8 (StartTime = [0x00A8ED84], @0x0074C5E7) and
// 0xC0 (@0x0074C5ED), and 0xC4 (@0x0074C5F3); the next confirmed member,
// CurrentState, is at 0xC8 == 0xAC + 0x1C. Field names are NOT established.
#ifndef GG_MATCH_LAYOUT_VEINHOLELOGIC_DEFINED
#define GG_MATCH_LAYOUT_VEINHOLELOGIC_DEFINED
// The veinhole stack begins at GrowthLogic+4 (object+0xB0). The initializer
// allocates 0x14 bytes and stores its fields at +0/+4/+8/+0xC/+0x10; the two
// sweep bodies read Count at +0. This prefix type names only the field used by
// the sweeps; it does not claim a complete stack API.
struct VeinholeGrowthStackPrefix
{
    int Count;  // +0x00, compared as a DWORD by 0x74CDF0 and 0x74EA30
};
GG_STATIC_ASSERT(sizeof(int) == 4);
GG_STATIC_ASSERT(sizeof(VeinholeGrowthStackPrefix*) == 4);
GG_STATIC_ASSERT(offsetof(VeinholeGrowthStackPrefix, Count) == 0x00);
GG_STATIC_ASSERT(sizeof(VeinholeGrowthStackPrefix) == 4);

struct VeinholeLogic
{
    unsigned long unknown_00;                // +0x00
    VeinholeGrowthStackPrefix* unknown_04;   // +0x04 (object+0xB0)
    unsigned char unknown_08[0x10];          // +0x08..+0x17
    char* SpreadData;                        // +0x18 (object+0xC4)
};
GG_STATIC_ASSERT(offsetof(VeinholeLogic, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(VeinholeLogic, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(VeinholeLogic, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(VeinholeLogic, SpreadData) == 0x18);
GG_STATIC_ASSERT(sizeof(char*) == 4);
GG_STATIC_ASSERT(sizeof(unsigned long) == 4);
GG_STATIC_ASSERT(sizeof(VeinholeLogic) == 0x1C);
#endif

class VeinholeMonsterClass : public ObjectClass
{
public:
    virtual int vf_30();                       // 30  0x74F330
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);  // 3   0x74F2D0
    // Statics and methods recovered in the combat/ and map/ TUs.
    static VeinholeMonsterClass* GetVeinholeMonsterFrom(CellStruct* pCell);  // 0x74CD60, lookup by position
    static VeinholeMonsterClass* GetVeinholeMonsterAt(CellStruct* pCell);    // 0x74CDB0, lookup by spread data
    static void LoadVeinholeArt(int idxTheatre);  // 0x74D450
    static void DeleteAll();                   // 0x74D760
    static void DeleteVeinholeGrowthData();    // 0x74E880
    static bool IsCellEligibleForVeinHole(const struct Cell_0074D670* cell);  // 0x74D670
    static void UpdateAllVeinholes();           // 0x74CDF0
    static void DestroyAll();                   // 0x74EA30
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty); // 6, 0x74EEE0
    void RecalculateSpread();                  // 0x74E6B0
    void Recalculate();                        // 0x74E930
    VeinholeLogic GrowthLogic;                 // +0xAC (0x1C) see note
    int           CurrentState;                // +0xC8 ctor @0x0074C5F9
    int           NextState;                   // +0xCC ctor @0x0074C5FF
    int           MonsterFrameIdx;             // +0xD0 ctor @0x0074C605
    signed char   IsAnimationUpToDate;         // +0xD4 ctor @0x0074C60B
    unsigned char align_D5[3];                 // +0xD5
    CDTimerClass  UpdateAnimationFrameTimer;   // +0xD8 ctor StartTime @0x0074C61D, TimeLeft @0x0074C617
    int           AnimationUpdatePeriod;       // +0xE4 ctor @0x0074C623
    int           MonsterFrameIdxChange;       // +0xE8 ctor MOV [ESI+0xE8],1 @0x0074C629
    CDTimerClass  UpdateStateTimer;            // +0xEC ctor StartTime @0x0074C638, TimeLeft @0x0074C63E
    CellStruct    Position;                    // +0xF8 ctor MOV [ESI+0xF8],ECX(= *pWhere) @0x0074C64B
    int           MonsterFrameToDraw;          // +0xFC ctor @0x0074C651
    signed char   IsDead;                      // +0x100 ctor @0x0074C657
    signed char   DontPuffGas;                 // +0x101 ctor @0x0074C65D
    unsigned char align_102[2];                // +0x102
    int           VeinCount;                   // +0x104 ctor @0x0074C663; closes the object at 0x108
};

GG_STATIC_ASSERT(offsetof(VeinholeMonsterClass, GrowthLogic)               == 0xAC);
GG_STATIC_ASSERT(offsetof(VeinholeMonsterClass, GrowthLogic) + offsetof(VeinholeLogic, unknown_04) == 0xB0);
GG_STATIC_ASSERT(offsetof(VeinholeMonsterClass, CurrentState)              == 0xC8);
GG_STATIC_ASSERT(offsetof(VeinholeMonsterClass, NextState)                 == 0xCC);
GG_STATIC_ASSERT(offsetof(VeinholeMonsterClass, MonsterFrameIdx)           == 0xD0);
GG_STATIC_ASSERT(offsetof(VeinholeMonsterClass, IsAnimationUpToDate)       == 0xD4);
GG_STATIC_ASSERT(offsetof(VeinholeMonsterClass, UpdateAnimationFrameTimer) == 0xD8);
GG_STATIC_ASSERT(offsetof(VeinholeMonsterClass, AnimationUpdatePeriod)     == 0xE4);
GG_STATIC_ASSERT(offsetof(VeinholeMonsterClass, MonsterFrameIdxChange)     == 0xE8);
GG_STATIC_ASSERT(offsetof(VeinholeMonsterClass, UpdateStateTimer)          == 0xEC);
GG_STATIC_ASSERT(offsetof(VeinholeMonsterClass, Position)                  == 0xF8);
GG_STATIC_ASSERT(offsetof(VeinholeMonsterClass, MonsterFrameToDraw)        == 0xFC);
GG_STATIC_ASSERT(offsetof(VeinholeMonsterClass, IsDead)                    == 0x100);
GG_STATIC_ASSERT(offsetof(VeinholeMonsterClass, DontPuffGas)               == 0x101);
GG_STATIC_ASSERT(offsetof(VeinholeMonsterClass, VeinCount)                 == 0x104);
GG_STATIC_ASSERT(sizeof(VeinholeMonsterClass)                              == 0x108);

// VTABLE: GAMEMD 0x007F66A8  VeinholeMonsterClass
// VTABLE: GAMEMD 0x007F668C  VeinholeMonsterClass::(+0x04)
// VTABLE: GAMEMD 0x007F6684  VeinholeMonsterClass::(+0x08)
// VTABLE: GAMEMD 0x007F667C  VeinholeMonsterClass::(+0x0C)

#endif  // GG_MATCH_LAYOUT_VEINHOLE_MONSTER_CLASS_H
