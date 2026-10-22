// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x6B7B90 / 0x6B7D30 / 0x6B7D50),
//   cross-checked against YRpp (
//   every offset reconfirmed numerically here).
//
// SpawnManagerClass — manages a carrier's spawned aircraft (e.g. Aircraft
// Carrier Hornets, Boomer missiles). This TU matches three leaf accessors:
//   - SetTarget: stash a pending NewTarget unless it equals the live Target.
//   - CountAliveSpawns: count nodes whose Status != Dead(7).
//   - CountDockedSpawns: count nodes whose Status == Reloading(6) || Idle(0).
#ifndef GG_MATCH_COMBAT_SPAWN_MANAGER_CLASS_METHODS_H
#define GG_MATCH_COMBAT_SPAWN_MANAGER_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class AbstractClass;

// SpawnControl (YRpp "SpawnControl"/spawn node): a per-spawn record. Only the
// Status dword @+0x04 is read by the counters here (the leading Unit pointer
// @+0x00 is the node's AircraftClass*). Full node layout is P2.
struct SpawnControl
{
    void* Unit;     // +0x00  AircraftClass*
    int   Status;   // +0x04  SpawnNodeStatus (Idle=0, Reloading=6, Dead=7)
};

GG_STATIC_ASSERT(offsetof(SpawnControl, Unit)   == 0x00);
GG_STATIC_ASSERT(offsetof(SpawnControl, Status) == 0x04);

// SpawnManagerClass : AbstractClass. The members touched by this TU:
//   SpawnedNodes is a DynamicVectorClass<SpawnControl*> embedded at +0x38; its
//   Items pointer lands at +0x3C (vector vptr @+0x38, Items @+0x3C) and its
//   Count at +0x48 (vector base +0x10). Target @+0x68, NewTarget @+0x6C.
struct SpawnManagerClass
{
    void SetTarget(AbstractClass* pTarget);   // GAMEMD 0x6B7B90 __thiscall
    int  CountAliveSpawns() const;            // GAMEMD 0x6B7D30 __thiscall
    int  CountDockedSpawns() const;           // GAMEMD 0x6B7D50 __thiscall

    char            _base[0x3C];              // +0x00  AbstractClass + leading members + vector head
    SpawnControl**  SpawnedNodes_Items;       // +0x3C  SpawnedNodes.Items
    char            _pad0[0x48 - 0x40];       // +0x40  Capacity / flags
    int             SpawnedNodes_Count;       // +0x48  SpawnedNodes.Count
    char            _pad1[0x68 - 0x4C];       // +0x4C  UpdateTimer / SpawnTimer
    AbstractClass*  Target;                   // +0x68
    AbstractClass*  NewTarget;                // +0x6C
};

GG_STATIC_ASSERT(offsetof(SpawnManagerClass, SpawnedNodes_Items) == 0x3C);
GG_STATIC_ASSERT(offsetof(SpawnManagerClass, SpawnedNodes_Count) == 0x48);
GG_STATIC_ASSERT(offsetof(SpawnManagerClass, Target)             == 0x68);
GG_STATIC_ASSERT(offsetof(SpawnManagerClass, NewTarget)          == 0x6C);

#endif  // GG_MATCH_COMBAT_SPAWN_MANAGER_CLASS_METHODS_H
