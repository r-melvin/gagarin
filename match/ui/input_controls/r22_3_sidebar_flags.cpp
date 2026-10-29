// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x6A7D20.
//
// Address index: 0x6A7D20 0x6A67A0

#include "sidebar_class_layout.h"

// FUNCTION: GAMEMD 0x6A7D20
// Ask every strip whether it has changed; when the active strip has, flag it for redraw, mark the
// sidebar dirty and request a redraw.
void SidebarClass::FUN_006A7D20()
{
    bool changed = false;
    for (int i = 0; i < 4; i++) {
        if (Strips[i].FUN_006AA600() && i == unknown_539C) {
            Strips[i].At_3C = 1;
            changed = true;
        }
    }
    if (changed) {
        At_53A6 = true;
        FlagToRedraw(0);
    }
}

// GLOBAL: GAMEMD 0xB0B478 -- sidebar state flag, tested when no strip holds a cameo.
extern int DAT_00B0B478;

// FUNCTION: GAMEMD 0x6A67A0
// Re-enable the given tab button if it was disabled, rebuilding the strip contents when it is the active
// tab. When no strip holds any cameo and the flag is set, reset the sidebar scroll state first.
void SidebarClass::FUN_006A67A0(int tab)
{
    int first = -1;
    for (int i = 0; i < 4; i++) {
        if (Strips[i].CameoCount > 0) {
            first = i;
            break;
        }
    }
    if (first == -1 && DAT_00B0B478) {
        unknown_5398 = 1;
        unknown_5394 = 0;
    }
    if (!TabButtons_00B07C48[tab].IsEnabled()) {
        TabButtons_00B07C48[tab].Enable();
    }
    if (tab == unknown_539C) {
        FUN_006A6610();
    }
}
