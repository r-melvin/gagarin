// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly), cross-checked against YRpp
//   ToolTipManager.h (consult-only, no LICENSE; reconfirmed here).
//
// ToolTipManager — the in-game tooltip controller. This TU matches only the
// three trivial timer-delay accessors; the full layout (CurrentToolTip, hWnd,
// CurrentToolTipData, the ToolTips vector + index) is P2 work, so the base is
// padded to the first touched member.
#ifndef GG_MATCH_UI_TOOLTIP_MANAGER_METHODS_H
#define GG_MATCH_UI_TOOLTIP_MANAGER_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// ToolTipManager (partial)
//
// Confirmed offsets from the three target functions:
//   0x724520 SetTimerDelay   : MOV [ECX+0x228], arg        -> ToolTipDelay @0x228
//   0x724530 SaveTimerDelay  : MOV [ECX+0x22c], [ECX+0x228]-> LastToolTipDelay @0x22c
//   0x724540 RestoreTimeDelay: MOV [ECX+0x228], [ECX+0x22c]
//
// YRpp names: ToolTipDelay then LastToolTipDelay (declared in retail order,
// 4 bytes apart). The CurrentToolTipData block precedes them; padded out.
// ---------------------------------------------------------------------------
struct ToolTipManager
{
    void SetTimerDelay(int value);   // GAMEMD 0x724520 __thiscall
    void SaveTimerDelay();           // GAMEMD 0x724530 __thiscall
    void RestoreTimeDelay();         // GAMEMD 0x724540 __thiscall
    bool IsToolTipShowing() const;   // GAMEMD 0x724C00 __thiscall

    char  _pad00[0x4];               // +0x000  COM vptr
    void* CurrentToolTip;            // +0x004  non-null while a tip is on screen
    char _layout_pad_P2[0x228 - 8];  // remainder of the P2 base
    int  ToolTipDelay;               // +0x228
    int  LastToolTipDelay;           // +0x22c
};

GG_STATIC_ASSERT(offsetof(ToolTipManager, CurrentToolTip) == 0x004);
GG_STATIC_ASSERT(offsetof(ToolTipManager, ToolTipDelay) == 0x228);
GG_STATIC_ASSERT(offsetof(ToolTipManager, LastToolTipDelay) == 0x22c);

#endif  // GG_MATCH_UI_TOOLTIP_MANAGER_METHODS_H
