// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail entry disassembly, RTTI and current canonical class/provider headers
//   establish the member ABI, registry item type, field offsets and virtual
//   slots used below. The original source-file identity is unknown; this is the
//   project home for these VeinholeMonsterClass methods.

#include <stdlib.h>
#include "veinhole_monster_eligible_methods.h"
#include "../_layout/staticvectorholder_00b1d290.h"

// FUNCTION: GAMEMD 0x74CDF0
// Drive every registered monster, then retire dead monsters with no queued
// growth nodes. Re-read Items after deletion because destruction may mutate the
// registry storage.
void VeinholeMonsterClass::UpdateAllVeinholes()
{
    int i;

    for (i = StaticVectorHolder_00B1D290::DAT_00B1D290.Count - 1; i >= 0; --i) {
        StaticVectorHolder_00B1D290::DAT_00B1D290.Items[i]->vf_23();
    }

    i = StaticVectorHolder_00B1D290::DAT_00B1D290.Count - 1;
    if (i >= 0) {
        VeinholeMonsterClass** items = StaticVectorHolder_00B1D290::DAT_00B1D290.Items;
        do {
            VeinholeMonsterClass* monster = items[i];
            if (monster->IsDead && monster->GrowthLogic.unknown_04->Count == 0) {
                if (monster) {
                    delete monster;
                    items = StaticVectorHolder_00B1D290::DAT_00B1D290.Items;
                }
            }
            --i;
        } while (i >= 0);
    }
}

// FUNCTION: GAMEMD 0x74D670
// Reject a candidate that is too close to an existing monster or whose 3x3
// cell neighborhood is not flat, above ground and of land type zero.
bool VeinholeMonsterClass::IsCellEligibleForVeinHole(const Cell_0074D670* cell)
{
    if (DAT_00A8E7AC > 0)
        return true;

    for (int i = StaticVectorHolder_00B1D290::DAT_00B1D290.Count - 1; i >= 0; --i) {
        VeinholeMonsterClass* monster = StaticVectorHolder_00B1D290::DAT_00B1D290.Items[i];
        if (abs(cell->X - monster->Position.X) < 3
            && abs(cell->Y - monster->Position.Y) < 3)
            return false;
    }

    int level = MapInstance_0074D670.GetCellAt(cell)->Level;
    if (level < 1)
        return false;

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            Cell_0074D670 spot;
            spot.X = cell->X + dx;
            spot.Y = cell->Y + dy;
            CellClass_0074D670* c = MapInstance_0074D670.Cell(spot);
            if (c->SlopeIndex != 0 || c->LandType != 0 || c->Level != level)
                return false;
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x74EA30
// Delete every dead monster whose growth-node queue is empty.
void VeinholeMonsterClass::DestroyAll()
{
    int i = StaticVectorHolder_00B1D290::DAT_00B1D290.Count - 1;
    if (i >= 0) {
        VeinholeMonsterClass** items = StaticVectorHolder_00B1D290::DAT_00B1D290.Items;
        do {
            VeinholeMonsterClass* monster = items[i];
            if (monster->IsDead && monster->GrowthLogic.unknown_04->Count == 0) {
                if (monster) {
                    delete monster;
                    items = StaticVectorHolder_00B1D290::DAT_00B1D290.Items;
                }
            }
            --i;
        } while (i >= 0);
    }
}

// FUNCTION: GAMEMD 0x74EEE0
// The inherited COM Save contract is __stdcall with IStream* and BOOL. Its
// base implementation is the partial shared helper at 0x410320.
HRESULT __stdcall VeinholeMonsterClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return AbstractClass::Save(pStm, fClearDirty);
}

// FUNCTION: GAMEMD 0x74F330
// Veinhole monsters sit in no layer.
int VeinholeMonsterClass::vf_30()
{
    return -1;
}
