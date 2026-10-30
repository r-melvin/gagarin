// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x6A60A0), cross-checked
//   against YRpp (every offset reconfirmed below
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
#include "input_controls/ui_display_chain.h"

// SidebarClass::Instance — the singleton at 0x87F7E8 (the hard-coded ECX of
// the retail FlagToRedraw call).  Address is the only thing that matters; the
// reloc is normalised by the differ.
extern SidebarClass SidebarClass_Instance;

#endif  // GG_MATCH_UI_SIDEBAR_CLASS_REPAINT_METHODS_H
