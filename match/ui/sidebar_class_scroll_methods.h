// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x6A6A00: `[ECX+0x539C]` is the active tab, the strip
//   base is `LEA ESI,[ECX+EAX*4+0x1544]` with EAX = tab*997 (stride 0xF94),
//   the strip fields are `[ESI+0x44]`, `[ESI+0x48]`, `[ESI+0x54]`, the
//   scenario flag is `[EDX+0x34B8]` through `[0xA8B230]`, the seven plain
//   globals are read by absolute address (see the GLOBAL lines below) and the
//   redraw hook is `CALL [EAX+0x38]` with one pushed 0. Names cross-checked
//   against YRpp SidebarClass.h / Unsorted.h / HouseClass.h (consult-only).
#ifndef GG_MATCH_UI_SIDEBAR_CLASS_SCROLL_METHODS_H
#define GG_MATCH_UI_SIDEBAR_CLASS_SCROLL_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// ---------------------------------------------------------------------------
// StripClass (sizeof == 0xF94) — one sidebar build column. Only the scroll
// position, its target, and the filled-cameo count are touched.
// ---------------------------------------------------------------------------
struct Strip_006A6A00
{
    char _pad000[0x44];              // +0x0000
    int  TopRowIndex;                // +0x0044
    int  At_48;                      // +0x0048  scroll target row
    char _pad04C[8];                 // +0x004C
    int  CameoCount;                 // +0x0054
    char _pad058[0xF94 - 0x58];      // +0x0058
};
GG_STATIC_ASSERT(offsetof(Strip_006A6A00, TopRowIndex) == 0x44);
GG_STATIC_ASSERT(offsetof(Strip_006A6A00, At_48) == 0x48);
GG_STATIC_ASSERT(offsetof(Strip_006A6A00, CameoCount) == 0x54);
GG_STATIC_ASSERT(sizeof(Strip_006A6A00) == 0xF94);

// Minimal ScenarioClass view: the dword at +0x34B8 selects the sidebar
// bottom margin.
struct Scenario_006A6A00
{
    char _pad000[0x34B8];            // +0x0000
    int  At_34B8;                    // +0x34B8
};
GG_STATIC_ASSERT(offsetof(Scenario_006A6A00, At_34B8) == 0x34B8);

// GLOBAL: GAMEMD 0xA8B230 — ScenarioClass::Instance.
extern Scenario_006A6A00* ScenarioInstance;
// GLOBAL: GAMEMD 0xA8ED8C — WSDialogCount (a modal dialog is up).
extern int WSDialogCount;
// GLOBAL: GAMEMD 0x886F9C — sidebar area height term.
extern int DAT_00886F9C;
// GLOBAL: GAMEMD 0xB0B4F8 — sidebar area top term.
extern int DAT_00B0B4F8;
// GLOBAL: GAMEMD 0x886F94 — sidebar area adjustment term.
extern int DAT_00886F94;
// GLOBAL: GAMEMD 0xA83D4C — HouseClass::CurrentPlayer.
extern void* CurrentPlayer;
// GLOBAL: GAMEMD 0xAC1198 — HouseClass::Observer.
extern void* Observer;
// GLOBAL: GAMEMD 0x884CF8 — observer-mode row limit.
extern int DAT_00884CF8;

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_006A6A00;

struct SidebarClass
{
    Vtbl_006A6A00* Vtbl;             // +0x0000
    char _pad004[0x1544 - 4];        // +0x0004
    Strip_006A6A00 Tabs[4];          // +0x1544
    int  unknown_5394;               // +0x5394
    int  unknown_5398;               // +0x5398
    int  ActiveTabIndex;             // +0x539C

    // FUNCTION: GAMEMD 0x6A6A00
    bool Scroll(bool up, int tab);
};
GG_STATIC_ASSERT(offsetof(SidebarClass, Tabs) == 0x1544);
GG_STATIC_ASSERT(offsetof(SidebarClass, ActiveTabIndex) == 0x539C);

typedef void (SidebarClass::*Fn38_006A6A00)(int mode);

struct Vtbl_006A6A00
{
    char _pad000[0x38];              // +0x0000
    Fn38_006A6A00 At_38;             // +0x0038  redraw hook
};
GG_STATIC_ASSERT(offsetof(Vtbl_006A6A00, At_38) == 0x38);

#endif  // GG_MATCH_UI_SIDEBAR_CLASS_SCROLL_METHODS_H
