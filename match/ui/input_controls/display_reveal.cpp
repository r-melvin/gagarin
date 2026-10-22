// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// DisplayClass cell reveal family, vtable slots 36..39 (layout and evidence: display_reveal.h).

#include "display_reveal.h"

// FUNCTION: GAMEMD 0x4A9890
bool DisplayClass::vf_36(CellStruct* cell, DisplayHouse* house)
{
    DisplayCell* c = GetCellAt_005657A0(*cell);
    bool wasClear = !(c->Flags140 & 2);
    bool changed = !((c->Flags140 & 2) && (c->Flags12C & 8));
    bool first = changed;
    c->Flags140 = (c->Flags140 & ~0x40) | 2;
    c->Flags12C |= 8;

    signed char v = DisplayProjector_00887324->FUN_006D8700(cell, 0);
    if (v != c->Layer0Value)
    {
        changed = true;
        c->Layer0Value = v;
    }
    if (c->Layer0Value == -1)
        c->Flags12C |= 0x10;

    v = DisplayProjector_00887324->FUN_006D8700(cell, 1);
    if (v != c->Layer1Value)
    {
        changed = true;
        c->Layer1Value = v;
    }
    if (c->Layer1Value == -1)
        c->Flags140 |= 1;

    if (changed)
        DisplayProjector_00887324->FUN_006DA7D0(c);

    for (int i = 0; i < 8; i++)
    {
        CellStruct n = DisplayStep_0089F688[i & 7] + *cell;
        DisplayCell* nc = GetCellAt_005657A0(n);
        if ((n.X != cell->X || n.Y != cell->Y) && !(nc->Flags12C & 0x10))
        {
            int r = DisplayProjector_00887324->FUN_006D8700(&n, 0);
            if (r == -1)
            {
                if (!(nc->Flags12C & 8))
                    vf_36(&n, house);
                else
                {
                    nc->Flags12C |= 0x10;
                    DisplayProjector_00887324->FUN_006DA7D0(nc);
                    for (int j = 0; j < 8; j++)
                    {
                        CellStruct m = DisplayStep_0089F688[j & 7] + n;
                        DisplayCell* mc = GetCellAt_005657A0(m);
                        signed char b = DisplayProjector_00887324->FUN_006D8700(&m, 0);
                        if (b != mc->Layer0Value)
                        {
                            mc->Layer0Value = b;
                            DisplayProjector_00887324->FUN_006DA7D0(mc);
                        }
                    }
                }
            }
            else if (r != -2 && !(nc->Flags12C & 8))
                vf_36(&n, house);
            else if (r >= 0 && r != nc->Layer0Value)
            {
                nc->Layer0Value = r;
                DisplayProjector_00887324->FUN_006DA7D0(nc);
            }
        }

        if ((n.X != cell->X || n.Y != cell->Y) && !(nc->Flags140 & 1))
        {
            int r = DisplayProjector_00887324->FUN_006D8700(&n, 1);
            if (r == -1)
            {
                if (!(nc->Flags140 & 2))
                    vf_36(&n, house);
                else
                {
                    nc->Flags140 |= 1;
                    DisplayProjector_00887324->FUN_006DA7D0(nc);
                    for (int j = 0; j < 8; j++)
                    {
                        CellStruct m = DisplayStep_0089F688[j & 7] + n;
                        DisplayCell* mc = GetCellAt_005657A0(m);
                        signed char b = DisplayProjector_00887324->FUN_006D8700(&m, 1);
                        if (b != mc->Layer1Value)
                        {
                            mc->Layer1Value = b;
                            DisplayProjector_00887324->FUN_006DA7D0(mc);
                        }
                    }
                }
            }
            else if (r != -2 && !(nc->Flags140 & 2))
                vf_36(&n, house);
            else if (r >= 0 && r != nc->Layer1Value)
            {
                nc->Layer1Value = r;
                DisplayProjector_00887324->FUN_006DA7D0(nc);
            }
        }
    }

    if (changed)
        DisplayMap_0087F7E8.RevealCheck_005865F0(c, house, first);
    if ((c->Flags140 & 2) && wasClear && (DisplayScenario_00A8B230->Flags & 0x1000))
        c->CleanFog_00486BF0();
    return changed;
}

// FUNCTION: GAMEMD 0x4A9CA0
bool DisplayClass::vf_37(CellStruct* cell, DisplayHouse* house, bool increase)
{
    DisplayCell* c = GetCellAt_005657A0(*cell);
    bool wasClear = !(c->Flags140 & 2);
    bool changed = !((c->Flags140 & 2) && (c->Flags12C & 8));
    bool first = changed;
    c->Flags140 = (c->Flags140 & ~0x40) | 2;
    if (increase)
        c->IncreaseShroudCounter_00487690();
    else
        c->ReduceShroudCounter_00487630();

    signed char v = DisplayProjector_00887324->FUN_006D8700(cell, 0);
    if (v != c->Layer0Value)
    {
        changed = true;
        c->Layer0Value = v;
    }
    if (c->Layer0Value == -1)
        c->Flags12C |= 0x10;

    v = DisplayProjector_00887324->FUN_006D8700(cell, 1);
    if (v != c->Layer1Value)
    {
        changed = true;
        c->Layer1Value = v;
    }
    if (c->Layer1Value == -1)
        c->Flags140 |= 1;

    if (changed)
    {
        DisplayProjector_00887324->FUN_006DA7D0(c);
        DisplayMap_0087F7E8.RevealCheck_005865F0(c, house, first);
    }
    if ((c->Flags140 & 2) && wasClear && (DisplayScenario_00A8B230->Flags & 0x1000))
        c->CleanFog_00486BF0();
    return changed;
}

// FUNCTION: GAMEMD 0x4A9DD0
// CAPPED at 44.6% (176 vs 177 instructions; multiset delta: retail has 1 `mov` where cl has `xor`+`jmp`).
// Retail keeps the cell pointer in EBX and the outer loop counter in memory ([esp+0x18]), with the first flag
// copy stored three times as bytes (one of them in the dead stack slot of the first argument); cl keeps the
// counter in EBX and the cell pointer in EDI, so every register after the prologue is named differently.
// Variants tried: single flag variable; three separately computed flags; chained three-way assignment in each
// declaration order (the one kept: three byte stores, no register copy); counter declared at function scope;
// extra uses of the cell pointer; flag loaded into a local first.
bool DisplayClass::vf_38(CellStruct* cell, DisplayHouse* house)
{
    DisplayCell* c = GetCellAt_005657A0(*cell);
    bool ret, fog, changed;
    ret = fog = changed = !(c->Flags140 & 2);
    c->Flags140 = (c->Flags140 & ~0x40) | 2;

    signed char v = DisplayProjector_00887324->FUN_006D8700(cell, 1);
    if (v != c->Layer1Value)
    {
        changed = true;
        c->Layer1Value = v;
    }
    if (c->Layer1Value == -1)
        c->Flags140 |= 1;
    if (changed)
        DisplayProjector_00887324->FUN_006DA7D0(c);

    for (int i = 0; i < 8; i++)
    {
        CellStruct n = DisplayStep_0089F688[i & 7] + *cell;
        DisplayCell* nc = GetCellAt_005657A0(n);
        if ((n.X != cell->X || n.Y != cell->Y) && !(nc->Flags140 & 1))
        {
            int r = DisplayProjector_00887324->FUN_006D8700(&n, 1);
            if (r == -1)
            {
                if (!(nc->Flags140 & 2))
                    vf_38(&n, house);
                else
                {
                    nc->Flags140 |= 1;
                    DisplayProjector_00887324->FUN_006DA7D0(nc);
                    for (int j = 0; j < 8; j++)
                    {
                        CellStruct m = n + DisplayStep_0089F688[j & 7];
                        DisplayCell* mc = GetCellAt_005657A0(m);
                        signed char b = DisplayProjector_00887324->FUN_006D8700(&m, 1);
                        if (b != mc->Layer1Value)
                        {
                            mc->Layer1Value = b;
                            DisplayProjector_00887324->FUN_006DA7D0(mc);
                        }
                    }
                }
            }
            else if (r != -2 && !(nc->Flags140 & 2))
                vf_38(&n, house);
            else if (r >= 0 && r != nc->Layer1Value)
            {
                nc->Layer1Value = r;
                DisplayProjector_00887324->FUN_006DA7D0(nc);
            }
        }
    }

    if (ret)
        DisplayMap_0087F7E8.RevealCheck_005865F0(c, house, changed);
    if ((c->Flags140 & 2) && fog && (DisplayScenario_00A8B230->Flags & 0x1000))
        c->CleanFog_00486BF0();
    return ret;
}

// FUNCTION: GAMEMD 0x4AA050
bool DisplayClass::vf_39(CellStruct* cell, DisplayHouse* house)
{
    DisplayCell* c = GetCellAt_005657A0(*cell);
    bool changed = !(c->Flags12C & 8);
    bool first = changed;
    c->Flags12C |= 8;

    signed char v = DisplayProjector_00887324->FUN_006D8700(cell, 0);
    if (v != c->Layer0Value)
    {
        changed = true;
        c->Layer0Value = v;
    }
    if (c->Layer0Value == -1)
        c->Flags12C |= 0x10;
    if (changed)
        DisplayProjector_00887324->FUN_006DA7D0(c);

    for (int i = 0; i < 8; i++)
    {
        CellStruct n = DisplayStep_0089F688[i & 7] + *cell;
        DisplayCell* nc = GetCellAt_005657A0(n);
        if ((n.X != cell->X || n.Y != cell->Y) && !(nc->Flags12C & 0x10))
        {
            int r = DisplayProjector_00887324->FUN_006D8700(&n, 0);
            if (r == -1)
            {
                if (!(nc->Flags12C & 8))
                    vf_39(&n, house);
                else
                {
                    nc->Flags12C |= 0x10;
                    DisplayProjector_00887324->FUN_006DA7D0(nc);
                    for (int j = 0; j < 8; j++)
                    {
                        CellStruct m = DisplayStep_0089F688[j & 7] + n;
                        DisplayCell* mc = GetCellAt_005657A0(m);
                        signed char b = DisplayProjector_00887324->FUN_006D8700(&m, 0);
                        if (b != mc->Layer0Value)
                        {
                            mc->Layer0Value = b;
                            DisplayProjector_00887324->FUN_006DA7D0(mc);
                        }
                    }
                }
            }
            else if (r != -2 && !(nc->Flags12C & 8))
                vf_39(&n, house);
            else if (r >= 0 && r != nc->Layer0Value)
            {
                nc->Layer0Value = r;
                DisplayProjector_00887324->FUN_006DA7D0(nc);
            }
        }
    }

    if (changed)
        DisplayMap_0087F7E8.RevealCheck_005865F0(c, house, first);
    return changed;
}
