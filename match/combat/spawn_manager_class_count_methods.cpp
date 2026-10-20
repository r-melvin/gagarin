// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at 0x6B7D80).
//   Names cross-checked against YRpp SpawnManagerClass.h (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x6B7D80  SpawnManagerClass::CountLaunchingSpawns (__thiscall)

#include "spawn_manager_class_count_methods.h"

// FUNCTION: GAMEMD 0x6B7D80  (__thiscall)
// Count spawn nodes that are mid-launch. A node counts when Status == 1
// (TakeOff); it also counts when Status == 2 (CoolDown) and its live Unit is
// not flagged at +0x81 and the unit's type (GetType, vtable +0x84) carries the
// launch flag at type +0xD68. Items / Count are re-read each pass (the virtual
// call may mutate the vector).
//
// MATCH: 38/38 exact (100.0%). Phrasing note: the two Status comparisons must
// read node->Status as independent memory expressions (NOT a single cached
// `int status` local). cl CSEs them back to one load (matching retail's single
// MOV ECX,[EAX+0x4]), but a cached local lets cl prove Status==1 and Status==2
// mutually exclusive and tail-merge both `++count` sites into one shared INC,
// which retail (build 8447) does not do. The two-read form keeps retail's
// fall-through structure (Status==1 INC falls into the CMP ECX,2 re-test).
int SpawnManagerClass::CountLaunchingSpawns() const
{
    int count = 0;
    for (int i = 0; i < SpawnedNodes_Count; ++i) {
        SpawnControl* node = SpawnedNodes_Items[i];
        if (node->Status == 1)
            ++count;
        if (node->Status == 2) {
            SpawnUnit* unit = node->Unit;
            if (unit != NULL && unit->Flag81 == 0) {
                if (unit->GetType()->Flag_d68 != 0)
                    ++count;
            }
        }
    }
    return count;
}
