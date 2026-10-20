// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 through
//   the local Ghidra CLI at 0x6B7BB0: the node vector's Items at [ESI+0x3C]
//   and Count at [ESI+0x48], Target at [ESI+0x68], NewTarget at [ESI+0x6C],
//   the status dword at [ESI+0x70]; the node's Unit at [node+0] and Status at
//   [node+4]; the unit's type at [unit+0x6C4] and the type's flag byte at
//   [type+0xD68]. The 12-byte global at 0xABC5F8 (YRpp Kamikaze::Instance) is
//   written as three dwords at 0x6B7BFA..0x6B7C05; 0xA8ED84 is the frame
//   counter (YRpp Unsorted::CurrentFrame). UnlinkPointer (0x6B7C60) adds the
//   owner at [ESI+0x24], the regen rate at [ESI+0x30], the node timer at
//   node+0x08 and the node dword at node+0x14, and on the unit the int at
//   [EDX+0x6C] and the byte at [EDX+0x6CA]. Names cross-checked against YRpp
//   SpawnManagerClass.h / Kamikaze.h (consult-only; NO LICENSE — every offset
//   reconfirmed here).
#ifndef GG_MATCH_COMBAT_SPAWN_MANAGER_CLASS_RESET_METHODS_H
#define GG_MATCH_COMBAT_SPAWN_MANAGER_CLASS_RESET_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct AbstractClass;

// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame.
extern int DAT_00A8ED84;

// A frame-clocked countdown (YRpp CDTimerClass). The clock slot at +0x04 is
// never written by the constructor, which is exactly what retail shows: the
// temporary's middle dword is copied out of an uninitialised stack slot.
struct CDTimer_006B7BB0
{
    int StartTime;    // +0x00
    int unknown_04;   // +0x04
    int TimeLeft;     // +0x08

    explicit CDTimer_006B7BB0(int duration)
    {
        StartTime = DAT_00A8ED84;
        TimeLeft = duration;
    }
};
GG_STATIC_ASSERT(offsetof(CDTimer_006B7BB0, TimeLeft) == 0x08);
GG_STATIC_ASSERT(sizeof(CDTimer_006B7BB0) == 0x0C);

// The spawned unit's type; only the flag byte at +0xD68 is read.
struct SpawnType_006B7BB0
{
    char _pad0000[0xD68];    // +0x0000
    char At_D68;             // +0x0D68
};
GG_STATIC_ASSERT(offsetof(SpawnType_006B7BB0, At_D68) == 0xD68);

// The spawned unit (an AircraftClass): health at +0x6C, the type pointer at
// +0x6C4 and the byte at +0x6CA that Kamikaze::Add raises.
struct SpawnUnit_006B7BB0
{
    char _pad0000[0x6C];         // +0x0000
    int Health;                  // +0x006C
    char _pad0070[0x6C4 - 0x70]; // +0x0070
    SpawnType_006B7BB0* Type;    // +0x06C4
    char _pad06C8[0x02];         // +0x06C8
    char At_6CA;                 // +0x06CA
};
GG_STATIC_ASSERT(offsetof(SpawnUnit_006B7BB0, Health) == 0x6C);
GG_STATIC_ASSERT(offsetof(SpawnUnit_006B7BB0, Type) == 0x6C4);
GG_STATIC_ASSERT(offsetof(SpawnUnit_006B7BB0, At_6CA) == 0x6CA);

// Per-spawn node: Unit at +0, Status at +4 (2 = recallable, 7 = dead), the
// respawn timer at +8 and a dword at +0x14 that UnlinkPointer tests against 1.
struct SpawnControl_006B7BB0
{
    SpawnUnit_006B7BB0* Unit;    // +0x00
    int Status;                  // +0x04
    CDTimer_006B7BB0 Timer;      // +0x08
    int At_14;                   // +0x14
};
GG_STATIC_ASSERT(offsetof(SpawnControl_006B7BB0, Status) == 0x04);
GG_STATIC_ASSERT(offsetof(SpawnControl_006B7BB0, Timer) == 0x08);
GG_STATIC_ASSERT(offsetof(SpawnControl_006B7BB0, At_14) == 0x14);

// Kamikaze::Instance — the suicide-run manager. Its UpdateTimer is the leading
// 12 bytes; the node vector that follows is not touched here.
struct Kamikaze_006B7BB0
{
    CDTimer_006B7BB0 UpdateTimer;    // +0x00

    // FUNCTION: GAMEMD 0x54E3B0 (decl; reloc) — Kamikaze::Add.
    void Add(SpawnUnit_006B7BB0* unit, AbstractClass* target);
};
GG_STATIC_ASSERT(offsetof(Kamikaze_006B7BB0, UpdateTimer) == 0x00);

// GLOBAL: GAMEMD 0xABC5F8 — Kamikaze::Instance.
extern Kamikaze_006B7BB0 DAT_00ABC5F8;

struct SpawnManager_006B7BB0
{
    char _pad0000[0x24];                  // +0x0000  AbstractClass
    AbstractClass* Owner;                 // +0x0024
    char _pad0028[0x08];                  // +0x0028
    int RegenRate;                        // +0x0030
    char _pad0034[0x08];                  // +0x0034  ReloadRate + vector vptr
    SpawnControl_006B7BB0** Items;        // +0x003C  SpawnedNodes.Items
    char _pad0040[0x08];                  // +0x0040
    int Count;                            // +0x0048  SpawnedNodes.Count
    char _pad004C[0x1C];                  // +0x004C
    AbstractClass* Target;                // +0x0068
    AbstractClass* NewTarget;             // +0x006C
    int Status;                           // +0x0070

    // FUNCTION: GAMEMD 0x6B7BB0
    void ResetTarget();

    // FUNCTION: GAMEMD 0x6B7C60 — SpawnManagerClass::UnlinkPointer.
    void UnlinkPointer(AbstractClass* remove);

    // FUNCTION: GAMEMD 0x6B7100 (decl; reloc) — release every node.
    void FUN_006B7100();
};
GG_STATIC_ASSERT(offsetof(SpawnManager_006B7BB0, Owner) == 0x24);
GG_STATIC_ASSERT(offsetof(SpawnManager_006B7BB0, RegenRate) == 0x30);
GG_STATIC_ASSERT(offsetof(SpawnManager_006B7BB0, Items) == 0x3C);
GG_STATIC_ASSERT(offsetof(SpawnManager_006B7BB0, Count) == 0x48);
GG_STATIC_ASSERT(offsetof(SpawnManager_006B7BB0, Target) == 0x68);
GG_STATIC_ASSERT(offsetof(SpawnManager_006B7BB0, NewTarget) == 0x6C);
GG_STATIC_ASSERT(offsetof(SpawnManager_006B7BB0, Status) == 0x70);

#endif  // GG_MATCH_COMBAT_SPAWN_MANAGER_CLASS_RESET_METHODS_H
