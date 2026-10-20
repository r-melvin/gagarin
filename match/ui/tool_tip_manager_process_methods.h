// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x724AD0: `[ESI+0x4]` (CurrentToolTip, tested and
//   cleared), on the tip `[EAX+0x14]` (Text, tested) and `[EAX]` (GadgetID,
//   pushed to slot `[EDX+0x14]`), the string-table call 0x734E60 with
//   ECX = Text, EDX = 0 and "D:\ra2mdpost\ToolTip.cpp" / 0x233 pushed, the
//   CRT calls 0x7CA405 (wcslen, unsigned `JBE` on the result) and 0x7CA422
//   (wcsncpy into `[ESI+0x28]`, 0x100), `[ESI+0x10]` / `[ESI+0x14]`
//   (CurrentMousePosition) copied to `[ESI+0x18]` / `[ESI+0x1C]`, the slot
//   `[EDX+0x4]` (Update) with `ESI+0x18` pushed, and the four dword clears
//   `[ESI+0x18..0x24]`. Names cross-checked against YRpp ToolTipManager.h
//   (consult-only, NO LICENSE); the layout repeats
//   match/ui/tooltip_manager_state_methods.h (CurrentToolTip @0x04,
//   CurrentMousePosition @0x10, CurrentToolTipData @0x18).
#ifndef GG_MATCH_UI_TOOL_TIP_MANAGER_PROCESS_METHODS_H
#define GG_MATCH_UI_TOOL_TIP_MANAGER_PROCESS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// One registered tooltip: the gadget id, its bounds, and an optional string
// table label (null means the id is resolved through the virtual).
struct ToolTip
{
    unsigned int GadgetID;   // +0x00
    int          X;          // +0x04 Bounds
    int          Y;          // +0x08
    int          Width;      // +0x0C
    int          Height;     // +0x10
    const char*  Text;       // +0x14
    bool         field_18;   // +0x18
};
GG_STATIC_ASSERT(offsetof(ToolTip, Text) == 0x14);

struct Point2D
{
    int X;   // +0x00
    int Y;   // +0x04
};

// RectangleStruct Dimension (4 ints) + wchar_t HelpText[0x100].
struct ToolTipManagerData
{
    int     X;                // +0x00
    int     Y;                // +0x04
    int     Width;            // +0x08
    int     Height;           // +0x0C
    wchar_t HelpText[0x100];  // +0x10
};
GG_STATIC_ASSERT(offsetof(ToolTipManagerData, HelpText) == 0x10);

// Zero the dimension of a help block. Written as an inline taking the block
// by reference: retail clears through the block pointer already in EDI on the
// Update-refused path (`MOV [EDI],EBX .. [EDI+0xC]`) and through `this` on the
// empty-text path, which is what the inlined reference parameter reproduces.
inline void ClearDimension(ToolTipManagerData& d)
{
    d.X      = 0;
    d.Y      = 0;
    d.Width  = 0;
    d.Height = 0;
}

// The COM vptr is modelled as real C++ virtuals so the two dispatches
// (`CALL [EDX+0x4]` Update, `CALL [EDX+0x14]` GetToolTipText) are emitted
// natively. No ctor is defined in this TU, so cl emits no vtable image.
struct ToolTipManager
{
    virtual ~ToolTipManager();                              // vtable[0]
    virtual bool Update(ToolTipManagerData& from);          // vtable[1] (+0x04)
    virtual void MarkToRedraw(ToolTipManagerData& from);    // vtable[2] (+0x08)
    virtual void Draw(bool onSidebar);                      // vtable[3] (+0x0C)
    virtual void DrawText(ToolTipManagerData& from);        // vtable[4] (+0x10)
    virtual wchar_t* GetToolTipText(unsigned int id);       // vtable[5] (+0x14)

    ToolTip*           CurrentToolTip;         // +0x04
    void*              hWnd;                   // +0x08
    bool               IsActive;               // +0x0C
    Point2D            CurrentMousePosition;   // +0x10
    ToolTipManagerData CurrentToolTipData;     // +0x18

    // FUNCTION: GAMEMD 0x724AD0
    bool Process();
};
GG_STATIC_ASSERT(offsetof(ToolTipManager, CurrentToolTip)       == 0x04);
GG_STATIC_ASSERT(offsetof(ToolTipManager, CurrentMousePosition) == 0x10);
GG_STATIC_ASSERT(offsetof(ToolTipManager, CurrentToolTipData)   == 0x18);
GG_STATIC_ASSERT(offsetof(ToolTipManager, CurrentToolTipData)
                 + offsetof(ToolTipManagerData, HelpText)       == 0x28);

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) — StringTable::LoadString.
// __fastcall: the label in ECX, an optional out-flag in EDX, then the source
// file and line on the stack (RET 8).
wchar_t* __fastcall StringTable_LoadString(const char* label, int* out,
                                           const char* file, int line);

// FUNCTION: GAMEMD 0x7CA405 (decl; reloc) — CRT wcslen.
extern "C" unsigned int __cdecl wcslen(const wchar_t* s);
// FUNCTION: GAMEMD 0x7CA422 (decl; reloc) — CRT wcsncpy.
extern "C" wchar_t* __cdecl wcsncpy(wchar_t* dst, const wchar_t* src, unsigned int n);

#endif  // GG_MATCH_UI_TOOL_TIP_MANAGER_PROCESS_METHODS_H
