// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x6F1F30 / 0x6F1F70
//   (Ghidra disasm). Structure cross-checked against YRpp
//   (each offset/global/call target
//   reconfirmed against the user's binary).
//
// Translation unit: TeamTypeClass instance-enumeration helpers.
//   FUNCTION: GAMEMD 0x6F1F30   TeamTypeClass::FlashAllInstances  (__thiscall)
//   FUNCTION: GAMEMD 0x6F1F70   TeamTypeClass::FindFirstInstance  (__thiscall)
//   GLOBAL:   GAMEMD 0x8B40E8   TeamClass::Array (DynamicVectorClass)
//   CALLEE:   GAMEMD 0x6EF5F0   TeamClass::Flash(int)

#include "team_type_class_instance_methods.h"

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x6F1F30  TeamTypeClass::FlashAllInstances (__thiscall)
//
// Flash every live TeamClass spawned from this TeamTypeClass.  Walks the global
// TeamClass::Array; each team whose Type == this is flashed for `duration`.
// The Flash call prevents the compiler from hoisting Items/Count, so both are
// re-read from the globals on each iteration.
// ---------------------------------------------------------------------------
void TeamTypeClass::FlashAllInstances(int duration)
{
    for (int i = 0; i < TeamArray.Count; i++) {
        TeamClass* team = ((TeamClass**)TeamArray.Items)[i];
        if (team->Type == this) {
            team->Flash(duration);
        }
    }
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x6F1F70  TeamTypeClass::FindFirstInstance (__thiscall)
//
// Return the first live TeamClass whose Type == this, or null if none.  With no
// call in the loop the compiler hoists Count and strength-reduces the Items walk
// to a moving pointer.
// ---------------------------------------------------------------------------
TeamClass* TeamTypeClass::FindFirstInstance() const
{
    int count = TeamArray.Count;
    for (int i = 0; i < count; i++) {
        TeamClass* team = ((TeamClass**)TeamArray.Items)[i];
        if (team->Type == this) {
            return team;
        }
    }
    return 0;
}
