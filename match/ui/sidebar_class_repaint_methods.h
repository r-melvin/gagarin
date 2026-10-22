// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x6A60A0), cross-checked
//   against YRpp (consult-only; every offset reconfirmed below
//   from the disassembly operands).
//
// SidebarClass::RepaintSidebar(int tab) — flags a sidebar build-tab dirty and
// kicks a full sidebar redraw, but only when `tab` is the currently-active
// tab.  Disasm reads `this->ActiveTabIndex` @0x539C, sets the byte
// `this->SidebarNeedsRedraw` @0x53A6, sets `this->Tabs[tab].NeedsRedraw`
// (Tabs @0x1544, sizeof(StripClass)==0xF94, NeedsRedraw @0x3C  =>
//  0x1544 + tab*0xF94 + 0x3C == tab*0xF94 + 0x1580, exactly the retail
//  [ECX + tab*997*4 + 0x1580] address term), then calls
//  SidebarClass::Instance->FlagToRedraw(0)  (Instance @0x87F7E8, the literal
//  ECX target of the CALL 0x4F42F0).
#ifndef GG_MATCH_UI_SIDEBAR_CLASS_REPAINT_METHODS_H
#define GG_MATCH_UI_SIDEBAR_CLASS_REPAINT_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// StripClass  (sizeof == 0xF94)  — one sidebar build column/tab.
// Only NeedsRedraw @0x3C is touched by RepaintSidebar; the rest is opaque
// padding so the element stride (0xF94) matches the retail array arithmetic.
// ---------------------------------------------------------------------------
struct StripClass
{
    char          _pad0[0x3C];   // 0x00 .. 0x3B  (Progress/Location/Bounds/Index/...)
    unsigned char NeedsRedraw;   // 0x3C
    char          _pad1[0xF94 - 0x3D];
};

GG_STATIC_ASSERT(offsetof(StripClass, NeedsRedraw) == 0x3C);
GG_STATIC_ASSERT(sizeof(StripClass) == 0xF94);

// ---------------------------------------------------------------------------
// SidebarClass  (only the base padding + the members RepaintSidebar touches).
// The 0x1544 base prefix (PowerClass and earlier StripClass members) is opaque.
// ---------------------------------------------------------------------------
struct SidebarClass
{
    char          _base[0x1544];           // 0x0000 .. 0x1543  (PowerClass base)
    StripClass    Tabs[4];                 // 0x1544 .. 0x5393  (4 * 0xF94)
    int           unknown_5394;            // 0x5394
    int           unknown_5398;            // 0x5398
    int           ActiveTabIndex;          // 0x539C
    int           unknown_53A0;            // 0x53A0
    unsigned char HideObjectNameInTooltip; // 0x53A4
    unsigned char IsSidebarActive;         // 0x53A5
    unsigned char SidebarNeedsRedraw;      // 0x53A6

    // GAMEMD 0x6A60A0  SidebarClass::RepaintSidebar (__thiscall)
    void RepaintSidebar(int tab);

    // GAMEMD 0x4F42F0  GScreenClass::FlagToRedraw (__thiscall, vtable slot 14)
    // — callee, not matched here; declared body-less so cl emits the CALL
    // (reloc-normalised).
    void FlagToRedraw(int mode);
};

GG_STATIC_ASSERT(offsetof(SidebarClass, Tabs) == 0x1544);
GG_STATIC_ASSERT(offsetof(SidebarClass, ActiveTabIndex) == 0x539C);
GG_STATIC_ASSERT(offsetof(SidebarClass, SidebarNeedsRedraw) == 0x53A6);

// SidebarClass::Instance — the singleton at 0x87F7E8 (the hard-coded ECX of
// the retail FlagToRedraw call).  Address is the only thing that matters; the
// reloc is normalised by the differ.
extern SidebarClass SidebarClass_Instance;

#endif  // GG_MATCH_UI_SIDEBAR_CLASS_REPAINT_METHODS_H
