// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly), cross-checked against YRpp
//   ToolTipManager.h (consult-only, no LICENSE; reconfirmed here from disasm).
//
// ToolTipManager::SetState (0x7241A0).  This TU models only the members the
// activate/deactivate path touches; the full layout (mouse pos, the help-text
// data block tail, the ToolTips vector + index) is P2 work.
//
// Confirmed offsets from the 0x7241A0 disasm:
//   MOV ESI,ECX                       -> this
//   CMP [ESI+0xc],AL / MOV [ESI+0xc]  -> IsActive @0x0c  (bool, 1 byte)
//   MOV EAX,[ESI+0x8]                 -> hWnd     @0x08
//   MOV EAX,[ESI+0x4]                 -> CurrentToolTip @0x04
//   MOV EDX,[ESI] / CALL [EDX+0x8]    -> vtable @0x00, virtual slot #2
//   LEA EAX,[ESI+0x18]                -> CurrentToolTipData @0x18
#ifndef GG_MATCH_UI_TOOLTIP_MANAGER_STATE_METHODS_H
#define GG_MATCH_UI_TOOLTIP_MANAGER_STATE_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

struct ToolTip;  // opaque — only a pointer is touched

// RectangleStruct Dimension (4 ints) + wchar_t HelpText[0x100].
struct ToolTipManagerData
{
    int  X, Y, Width, Height;        // RectangleStruct
    unsigned short HelpText[0x100];  // wchar_t HelpText[256]
};

struct Point2D
{
    int X, Y;
};

// ---------------------------------------------------------------------------
// ToolTipManager (partial).  The COM vptr is modelled as real C++ virtuals so
// SetState's vtable[+0x8] dispatch (MarkToRedraw) is emitted natively.  No ctor
// is defined in this TU, so cl emits no vtable image — only the call site.
// ---------------------------------------------------------------------------
struct ToolTipManager
{
    virtual ~ToolTipManager();                          // vtable[0]
    virtual bool Update(ToolTipManagerData& from);      // vtable[1]
    virtual void MarkToRedraw(ToolTipManagerData& from);// vtable[2] (+0x8)

    ToolTip*           CurrentToolTip;       // +0x04
    void*              hWnd;                 // +0x08
    bool               IsActive;            // +0x0c
    Point2D            CurrentMousePosition; // +0x10
    ToolTipManagerData CurrentToolTipData;   // +0x18

    void SetState(bool bState);  // GAMEMD 0x7241A0 __thiscall
};

GG_STATIC_ASSERT(offsetof(ToolTipManager, CurrentToolTip) == 0x04);
GG_STATIC_ASSERT(offsetof(ToolTipManager, hWnd) == 0x08);
GG_STATIC_ASSERT(offsetof(ToolTipManager, IsActive) == 0x0c);
GG_STATIC_ASSERT(offsetof(ToolTipManager, CurrentToolTipData) == 0x18);

#endif  // GG_MATCH_UI_TOOLTIP_MANAGER_STATE_METHODS_H
