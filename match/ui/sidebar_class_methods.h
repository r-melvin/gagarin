// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Logic + calling convention derived from the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI (disasm at 0x6ABCD0), cross-checked
//   against YRpp `GetObjectTabIdx` (reconfirmed).
//
// SidebarClass::GetObjectTabIdx — a static __fastcall classifier mapping an
// AbstractType id (+ build category) to a build-tab index. It touches no
// instance members (the args arrive in ECX/EDX + one stack slot), so no
// SidebarClass layout is modelled here.
#ifndef GG_MATCH_UI_SIDEBAR_CLASS_METHODS_H
#define GG_MATCH_UI_SIDEBAR_CLASS_METHODS_H

#include "input_controls/ui_display_chain.h"

#endif  // GG_MATCH_UI_SIDEBAR_CLASS_METHODS_H
