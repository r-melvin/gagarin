// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 with the
//   local Ghidra CLI inside 0x6A7590:
//     SidebarClass: the active tab index at [EBP+0x539C] (0x6A7598), the strip
//       array base at [EBP+EAX*4+0x1544] with EAX = tab*997, i.e. stride 0xF94
//       (0x6A75CE) — the same spine as the already-matched
//       match/ui/sidebar_class_scroll_methods.h (read, not edited) — and the
//       byte set on the way out at [EBP+0x53A7] (0x6A76D9).
//     StripClass: the byte at [EDI+0x1C] (0x6A75D5 / 0x6A7633) and the int at
//       [EDI+0x38] (0x6A75D9).
//     The 0x60-byte tab records at 0xB07C48 (LEA/SHL 5 at 0x6A75A6) and the
//       0x38-byte cameo buttons at 0xB07E80 (the *7*8 LEA pair at 0x6A75E1).
//     MapClass::Instance as the immediate 0x87F7E8 (0x6A75F1, 0x6A76BA).
//     ScenarioClass* at 0xA8B230, the int at +0x34B8 (0x6A763D), and the three
//       layout globals 0x886F9C / 0xB0B4F8 / 0x886F94 (0x6A7651..0x6A7663) —
//       the same 50-pixel row formula as 0x6A6A00.
//     The byte flag at 0x884B8F (0x6A76CC).
//   Names cross-checked against YRpp SidebarClass.h (consult-only, NO LICENSE).
#ifndef GG_MATCH_UI_SIDEBAR_CLASS_SET_TAB_METHODS_H
#define GG_MATCH_UI_SIDEBAR_CLASS_SET_TAB_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// One 0x38-byte cameo button.
struct Button_006A7590
{
    char _pad000[0x38];   // +0x0000

    // FUNCTION: GAMEMD 0x5565F0 (decl; reloc) -- refresh the button.
    void FUN_005565F0();
};
GG_STATIC_ASSERT(sizeof(Button_006A7590) == 0x38);
// GLOBAL: GAMEMD 0xB07E80 -- the cameo button pool, 60 per strip row block.
extern Button_006A7590 DAT_00B07E80[];

// One 0x60-byte tab record.
struct TabRec_006A7590
{
    char _pad000[0x60];   // +0x0000

    // FUNCTION: GAMEMD 0x723EA0 (decl; reloc) -- mark the tab selected.
    void FUN_00723EA0();
    // FUNCTION: GAMEMD 0x723EB0 (decl; reloc) -- mark the tab unselected.
    void FUN_00723EB0();
};
GG_STATIC_ASSERT(sizeof(TabRec_006A7590) == 0x60);
// GLOBAL: GAMEMD 0xB07C48 -- the tab records.
extern TabRec_006A7590 DAT_00B07C48[];

// MapClass -- the two button-list calls.
struct Map_006A7590
{
    char _opaque[4];
    // FUNCTION: GAMEMD 0x4F4410 (decl; reloc) -- add the button to the list.
    void FUN_004F4410(Button_006A7590* button);
    // FUNCTION: GAMEMD 0x4F4450 (decl; reloc) -- take the button off the list.
    void FUN_004F4450(Button_006A7590* button);
};
// GLOBAL: GAMEMD 0x87F7E8 -- the MapClass instance itself (an immediate).
extern Map_006A7590 MapInstance_006A7590;

struct Scenario_006A7590
{
    char _pad000[0x34B8];   // +0x0000
    int  At_34B8;           // +0x34B8
};
GG_STATIC_ASSERT(offsetof(Scenario_006A7590, At_34B8) == 0x34B8);

// GLOBAL: GAMEMD 0xA8B230 -- ScenarioClass::Instance.
extern Scenario_006A7590* ScenarioInstance_006A7590;
// GLOBAL: GAMEMD 0x886F9C -- sidebar area height term.
extern int DAT_00886F9C;
// GLOBAL: GAMEMD 0xB0B4F8 -- sidebar area top term.
extern int DAT_00B0B4F8;
// GLOBAL: GAMEMD 0x886F94 -- sidebar area adjustment term.
extern int DAT_00886F94;
// GLOBAL: GAMEMD 0x884B8F -- "sidebar needs a full redraw" byte.
extern char DAT_00884B8F;

// StripClass (sizeof == 0xF94) -- one sidebar build column.
struct Strip_006A7590
{
    char _pad000[0x1C];             // +0x0000
    char IsSelected;                // +0x001C
    char _pad01D[0x38 - 0x1D];      // +0x001D
    int  RowBlock;                  // +0x0038
    char _pad03C[0xF94 - 0x3C];     // +0x003C
};
GG_STATIC_ASSERT(offsetof(Strip_006A7590, IsSelected) == 0x1C);
GG_STATIC_ASSERT(offsetof(Strip_006A7590, RowBlock) == 0x38);
GG_STATIC_ASSERT(sizeof(Strip_006A7590) == 0xF94);

struct Sidebar_006A7590
{
    char           _pad0000[0x1544];   // +0x0000
    Strip_006A7590 Tabs[4];            // +0x1544
    int            unknown_5394;       // +0x5394
    int            unknown_5398;       // +0x5398
    int            ActiveTabIndex;     // +0x539C
    char           _pad53A0[0x53A7 - 0x53A0]; // +0x53A0
    char           At_53A7;            // +0x53A7

    // FUNCTION: GAMEMD 0x6A6610 (decl; reloc) -- rebuild the strip contents.
    void FUN_006A6610();

    // FUNCTION: GAMEMD 0x6A7590
    void SetTab(int tab);
};
GG_STATIC_ASSERT(offsetof(Sidebar_006A7590, Tabs)           == 0x1544);
GG_STATIC_ASSERT(offsetof(Sidebar_006A7590, ActiveTabIndex) == 0x539C);
GG_STATIC_ASSERT(offsetof(Sidebar_006A7590, At_53A7)        == 0x53A7);

#endif  // GG_MATCH_UI_SIDEBAR_CLASS_SET_TAB_METHODS_H
