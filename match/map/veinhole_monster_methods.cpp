// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x74CDF0, 0x74EA30,
//   0x74EEE0 and 0x74EF00. YRpp consulted for method names only.

#include "veinhole_monster_methods.h"

// FUNCTION: GAMEMD 0x74CDF0
//
// The per-frame driver. Every registered monster is updated (top-down, the
// Items pointer re-read each pass because Update may reallocate the registry),
// then the dead-and-drained ones are deleted. The second loop is the body of
// DestroyAll below, written out again: retail carries two copies of the sweep,
// so the source did too. See DestroyAll for why the sweep is phrased the way it
// is.
void VeinholeMonsterClass::UpdateAllVeinholes()
{
    int i;

    for (i = VeinholeArray.Count - 1; i >= 0; --i) {
        VeinholeArray.Items[i]->Update();
    }

    i = VeinholeArray.Count - 1;
    if (i >= 0) {
        VeinholeMonsterClass** items = VeinholeArray.Items;
        do {
            VeinholeMonsterClass* monster = items[i];
            if (monster->IsDead && monster->unknown_B0->Count == 0) {
                if (monster) {
                    delete monster;
                    items = VeinholeArray.Items;
                }
            }
            --i;
        } while (i >= 0);
    }
}

// FUNCTION: GAMEMD 0x74EA30
//
// Delete every monster that is dead and has no growth nodes still queued.
//
// Phrasing is load-bearing. Retail keeps the registry's Items pointer in EAX
// across the loop and reloads it only after the destructor call (the destructor
// unlinks the monster, so the block may move). A plain `VeinholeArray.Items[i]`
// in the loop makes our cl reload it every iteration and costs the byte load
// its register (43.5%). Caching the pointer in a local and reloading it after
// the delete restores the shape, but the reload has to sit inside an explicit
// `if (monster)`: `delete` carries its own null test, and with the reload
// outside that test the null path jumps to the reload instead of past it
// (95.7%). VC6 folds the explicit test into delete's implicit one, so the
// guard costs no instruction.
void VeinholeMonsterClass::DestroyAll()
{
    int i = VeinholeArray.Count - 1;
    if (i >= 0) {
        VeinholeMonsterClass** items = VeinholeArray.Items;
        do {
            VeinholeMonsterClass* monster = items[i];
            if (monster->IsDead && monster->unknown_B0->Count == 0) {
                if (monster) {
                    delete monster;
                    items = VeinholeArray.Items;
                }
            }
            --i;
        } while (i >= 0);
    }
}

// FUNCTION: GAMEMD 0x74EEE0
//
// IPersistStream::Save — forwards the receiver and both stream arguments to the
// shared object saver.
long __stdcall VeinholeMonsterClass::Save(void* pStm, int fClearDirty)
{
    return FUN_00410320(this, pStm, fClearDirty);
}

// FUNCTION: GAMEMD 0x74EF00
//
// The terrain type a veinhole is drawn as, taken from the rules.
void* VeinholeMonsterClass::GetTerrainType()
{
    return RulesInstance->VeinholeTerrainType;
}
