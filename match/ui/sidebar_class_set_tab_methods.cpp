// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6A7590.

#include "sidebar_class_set_tab_methods.h"

// FUNCTION: GAMEMD 0x6A7590
//
// PARTIAL (94.9%, 93/98; instruction multiset identical). The only residual
// delta is the sidebar margin constant, and it is the failure class already
// banked for the same formula in match/ui/sidebar_class_scroll_methods.cpp
// (0x6A6A00): retail loads the scenario flag into EAX, tests it, and then
// materialises MOV EAX,0x1A between the TEST and the JZ, while cl 12.00.8804
// hoists the constant above the flag load and tests the flag in EDX. That TU
// already records the exhausted variant list (if/else either way, ternary,
// `-= 8`, `0x1A - (flag ? 8 : 0)`, a flag/bool local read first, the flag
// reused as the margin variable, and an inlined helper — the ternary/helper
// and subtraction forms all go branchless NEG/SBB/AND), so it was not re-run
// here; two further spellings were re-run on this TU anyway — the flag itself
// bound as the margin variable and then overwritten per arm, in both arm
// orders (`if (margin != 0) margin = 0x12; else margin = 0x1A;` and the
// equal-case-first mirror) — and both go branchless (NEG/SBB/AND/ADD, 69.4%),
// which is worse than the hoisted constant. Every other instruction in this
// function is exact.
//
// SidebarClass::SetTab — switch the sidebar to another build tab. Selecting the
// tab that is already active does nothing. Otherwise the old tab record is
// unselected, its strip is cleared and all sixty of its cameo buttons are taken
// off the map's button list; the new tab becomes active and is marked selected;
// and as many of the new strip's buttons as fit in the sidebar (the same
// 50-pixel row arithmetic as SidebarClass::Scroll, two cameos per row) are
// refreshed and put back on the list. The sidebar is then flagged for a full
// redraw and rebuilt.
void Sidebar_006A7590::SetTab(int tab)
{
    if (tab == this->ActiveTabIndex) {
        return;
    }

    DAT_00B07C48[this->ActiveTabIndex].FUN_00723EB0();

    Strip_006A7590* strip = &this->Tabs[this->ActiveTabIndex];
    strip->IsSelected = 0;
    for (int i = 0; i < 60; i++) {
        MapInstance_006A7590.FUN_004F4450(&DAT_00B07E80[strip->RowBlock * 60 + i]);
    }

    this->ActiveTabIndex = tab;
    DAT_00B07C48[tab].FUN_00723EA0();

    strip = &this->Tabs[this->ActiveTabIndex];
    strip->IsSelected = 1;

    int margin = 0x1A;
    if (ScenarioInstance_006A7590->At_34B8) {
        margin = 0x12;
    }
    int count = ((DAT_00886F9C - DAT_00B0B4F8 - margin - 7 + DAT_00886F94) / 50) * 2;

    for (int j = 0; j < count; j++) {
        DAT_00B07E80[strip->RowBlock * 60 + j].FUN_005565F0();
        MapInstance_006A7590.FUN_004F4410(&DAT_00B07E80[strip->RowBlock * 60 + j]);
    }

    DAT_00884B8F = 1;
    this->FUN_006A6610();
    this->At_53A7 = 1;
}
