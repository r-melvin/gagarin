// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 through
//   the local Ghidra CLI at 0x6B7100: the owner at [ESI+0x24] with its
//   `[EAX+0x6C]` (tested > 0) and byte `[EAX+0x90]`; the regen rate at
//   [ESI+0x30]; the node vector's Items at [ESI+0x3C] and Count at
//   [ESI+0x48]; Target at [ESI+0x68]; the node's Unit at [node+0], Status at
//   [node+4] (0/6, 1, 7 tested; 7 stored from EBP) and the timer at node+8
//   (frame counter 0xA8ED84 to +0, the uninitialised temporary slot
//   [ESP+0x14] to +4, the duration to +8); the unit's slot `[EAX+0xF8]`
//   (no arguments); the kamikaze manager 0xABC5F8 with 0x54E590 (one pushed
//   unit) and 0x54E3B0 (pushed target, pushed unit). Names cross-checked
//   against YRpp (
//   — every offset reconfirmed here) and the sibling
//   match/combat/spawn_manager_class_reset_methods.h.
#ifndef GG_MATCH_COMBAT_SPAWN_MANAGER_CLASS_KILL_NODES_METHODS_H
#define GG_MATCH_COMBAT_SPAWN_MANAGER_CLASS_KILL_NODES_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct AbstractClass;

// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame.
#include "../core/frame_counter.h"

// A frame-clocked countdown (YRpp CDTimerClass). The clock slot at +0x04 is
// never written by the constructor, which is what retail shows: the
// temporary's middle dword is copied out of an uninitialised stack slot.
struct CDTimer_006B7100
{
    int StartTime;    // +0x00
    int unknown_04;   // +0x04
    int TimeLeft;     // +0x08

    explicit CDTimer_006B7100(int duration)
    {
        StartTime = CurrentFrame;
        TimeLeft = duration;
    }
};
GG_STATIC_ASSERT(offsetof(CDTimer_006B7100, TimeLeft) == 0x08);
GG_STATIC_ASSERT(sizeof(CDTimer_006B7100) == 0x0C);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct UnitVtbl_006B7100;

// The spawned unit (an AircraftClass); only one vtable slot is called.
struct SpawnUnit_006B7100
{
    UnitVtbl_006B7100* Vtbl;    // +0x0000
};

typedef void (SpawnUnit_006B7100::*FnF8_006B7100)();

struct UnitVtbl_006B7100
{
    char _pad000[0xF8];          // +0x0000
    FnF8_006B7100 At_F8;         // +0x00F8 — take the object off the map.
};
GG_STATIC_ASSERT(offsetof(UnitVtbl_006B7100, At_F8) == 0xF8);

// The owner (a TechnoClass): health at +0x6C and the byte at +0x90.
struct Owner_006B7100
{
    char _pad0000[0x6C];         // +0x0000
    int  Health;                 // +0x006C
    char _pad0070[0x90 - 0x70];  // +0x0070
    char At_90;                  // +0x0090
};
GG_STATIC_ASSERT(offsetof(Owner_006B7100, Health) == 0x6C);
GG_STATIC_ASSERT(offsetof(Owner_006B7100, At_90) == 0x90);

// Per-spawn node: Unit at +0, Status at +4 (7 = dead), the respawn timer at
// +8.
struct SpawnControl_006B7100
{
    SpawnUnit_006B7100* Unit;    // +0x00
    int Status;                  // +0x04
    CDTimer_006B7100 Timer;      // +0x08
};
GG_STATIC_ASSERT(offsetof(SpawnControl_006B7100, Status) == 0x04);
GG_STATIC_ASSERT(offsetof(SpawnControl_006B7100, Timer) == 0x08);

// Kamikaze::Instance — the suicide-run manager.
struct Kamikaze_006B7100
{
    char opaque[4];

    // FUNCTION: GAMEMD 0x54E3B0 (decl; reloc) — Kamikaze::Add.
    void Add(SpawnUnit_006B7100* unit, AbstractClass* target);
    // FUNCTION: GAMEMD 0x54E590 (decl; reloc) — Kamikaze::Remove.
    void Remove(SpawnUnit_006B7100* unit);
};

// GLOBAL: GAMEMD 0xABC5F8 — Kamikaze::Instance.
extern Kamikaze_006B7100 DAT_00ABC5F8;

struct SpawnManager_006B7100
{
    char _pad0000[0x24];                  // +0x0000  AbstractClass
    Owner_006B7100* Owner;                // +0x0024
    char _pad0028[0x08];                  // +0x0028
    int RegenRate;                        // +0x0030
    char _pad0034[0x08];                  // +0x0034  ReloadRate + vector vptr
    SpawnControl_006B7100** Items;        // +0x003C  SpawnedNodes.Items
    char _pad0040[0x08];                  // +0x0040
    int Count;                            // +0x0048  SpawnedNodes.Count
    char _pad004C[0x1C];                  // +0x004C
    AbstractClass* Target;                // +0x0068

    // FUNCTION: GAMEMD 0x6B7100 — SpawnManagerClass::KillNodes.
    void KillNodes();
};
GG_STATIC_ASSERT(offsetof(SpawnManager_006B7100, Owner) == 0x24);
GG_STATIC_ASSERT(offsetof(SpawnManager_006B7100, RegenRate) == 0x30);
GG_STATIC_ASSERT(offsetof(SpawnManager_006B7100, Items) == 0x3C);
GG_STATIC_ASSERT(offsetof(SpawnManager_006B7100, Count) == 0x48);
GG_STATIC_ASSERT(offsetof(SpawnManager_006B7100, Target) == 0x68);

#endif  // GG_MATCH_COMBAT_SPAWN_MANAGER_CLASS_KILL_NODES_METHODS_H
