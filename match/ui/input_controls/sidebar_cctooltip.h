// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Entry, span, ABI and field facts read from the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI (disasm from each entry) at 0x478BA0,
//   0x478DB0, 0x478E10, 0x478E30 and 0x479050. RTTI at 0x849EE0 names CCToolTip
//   (base ToolTipManager); its COL is 0x80E560 and its vtable address point is
//   0x7F74C4. Slots 1..5 hold exactly the five entries below; slot 0 is not an
//   entry of this module.
//
// CCToolTip is ToolTipManager (match/ui/tooltip_manager_shared.h, used
// UNCHANGED) plus one byte at +0x260 that selects whether the tooltip may be
// drawn across the sidebar boundary (CMP BYTE PTR [ECX+0x260],1 at 0x478E69).
//
// The views below are address-scoped to this module and carry no claim beyond
// the instructions that touch them.
#ifndef GG_MATCH_UI_INPUT_CONTROLS_SIDEBAR_CCTOOLTIP_H
#define GG_MATCH_UI_INPUT_CONTROLS_SIDEBAR_CCTOOLTIP_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "../tooltip_manager_shared.h"
#include "mouse_ww_mouse_class.h"

// Rectangle stored as {X, Y, Width, Height}: the sidebar rectangle at 0x886F90
// and the tactical view rectangle at 0x886FA0 (reads of +0, +4, +8, +C).
struct TipRect_00478BA0
{
    int X;
    int Y;
    int Width;
    int Height;
};

// GLOBAL: GAMEMD 0x886F90 -- sidebar rectangle.
extern TipRect_00478BA0 SidebarRect_00886F90;
// GLOBAL: GAMEMD 0x886FA0 -- tactical view rectangle.
extern TipRect_00478BA0 TacticalRect_00886FA0;
// GLOBAL: GAMEMD 0xA8EB7C -- compared against 1; picks which side the sidebar is on.
extern unsigned char SidebarSideFlag_00A8EB7C;
// GLOBAL: GAMEMD 0x884B8E -- set when a tooltip touches the sidebar (byte store).
extern unsigned char TipTouchedSidebar_00884B8E;
// GLOBAL: GAMEMD 0x884B8F -- "sidebar needs a full redraw" (byte store).
extern unsigned char SidebarNeedsRedraw_00884B8F;
// GLOBAL: GAMEMD 0xB0B518 -- byte set when the tooltip is drawn on the sidebar surface.
extern unsigned char SidebarSurfaceUsed_00B0B518;

// WWMouseClass::Instance (GLOBAL 0x887640; slot 10 GetHideCount) is WWMouseClassInstance, mouse_ww_mouse_class.h.

// The map singleton is a static object at 0x87F7E8 (MOV ECX,0x87F7E8).
struct TipMap_00478DB0
{
    char _opaque[4];
    // FUNCTION: GAMEMD 0x4F42F0 (decl; reloc) -- GScreenClass::FlagToRedraw.
    void FlagToRedraw(int mode);
    // FUNCTION: GAMEMD 0x6D1800 (decl; reloc) -- stdcall forwarder onto 0x6AC210.
    wchar_t* FUN_006D1800(unsigned int id);
};
// GLOBAL: GAMEMD 0x87F7E8 -- MapClass::Instance.
extern TipMap_00478DB0 MapInstance_0087F7E8;

// The 16-bit pixel packer (inlined at 0x478F65): three bytes at 0xB0FA1C are
// shifted by the six pixel-format globals at 0x8A0DD0..0x8A0DE4.
struct TipRGB_00478E30
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
};
// GLOBAL: GAMEMD 0xB0FA1C -- current tooltip colour (R, G, B bytes).
extern TipRGB_00478E30 TipColor_00B0FA1C;
// GLOBAL: GAMEMD 0x8A0DD0/0x8A0DD4 -- red left/right shift.
extern int RedLeft_008A0DD0;
extern unsigned char RedRight_008A0DD4;
// GLOBAL: GAMEMD 0x8A0DD8/0x8A0DDC -- blue left/right shift.
extern int BlueLeft_008A0DD8;
extern unsigned char BlueRight_008A0DDC;
// GLOBAL: GAMEMD 0x8A0DE0/0x8A0DE4 -- green left/right shift.
extern int GreenLeft_008A0DE0;
extern unsigned char GreenRight_008A0DE4;

// Surface reached through DSurface::Composite (0x88731C) / DSurface::Sidebar
// (0x887300). Slots used: +0x14 (rect, 0), +0x58 (rect, colour), +0x7C ().
struct TipRectLTRB_00478E30
{
    int Left;
    int Top;
    int Right;
    int Bottom;
};
struct TipSurface_00478E30;
struct TipSurfaceVtbl_00478E30;
struct TipSurface_00478E30
{
    TipSurfaceVtbl_00478E30* Vtbl;
};
typedef int (TipSurface_00478E30::*TipSurfaceFn14_00478E30)(TipRect_00478BA0* rect, int arg);
typedef int (TipSurface_00478E30::*TipSurfaceFn58_00478E30)(TipRect_00478BA0* rect, int color);
typedef int (TipSurface_00478E30::*TipSurfaceFn7C_00478E30)();
struct TipSurfaceVtbl_00478E30
{
    char _pad000[0x14];
    TipSurfaceFn14_00478E30 At_14;
    char _pad018[0x58 - 0x18];
    TipSurfaceFn58_00478E30 At_58;
    char _pad05C[0x7C - 0x5C];
    TipSurfaceFn7C_00478E30 At_7C;
};
GG_STATIC_ASSERT(offsetof(TipSurfaceVtbl_00478E30, At_14) == 0x14);
GG_STATIC_ASSERT(offsetof(TipSurfaceVtbl_00478E30, At_58) == 0x58);
GG_STATIC_ASSERT(offsetof(TipSurfaceVtbl_00478E30, At_7C) == 0x7C);
// GLOBAL: GAMEMD 0x88731C -- DSurface::Composite.
extern TipSurface_00478E30* CompositeSurface_0088731C;
// GLOBAL: GAMEMD 0x887300 -- DSurface::Sidebar.
extern TipSurface_00478E30* SidebarSurface_00887300;

// The object at 0x89C4D0 (text/font state). __thiscall members read off the
// callers at 0x478BA0 and 0x478E30.
struct TipFont_00478BA0
{
    // FUNCTION: GAMEMD 0x433C70 (decl; reloc) -- stores a word at +0x24.
    void FUN_00433C70(unsigned short value);
    // FUNCTION: GAMEMD 0x433C90 (decl; reloc) -- stores a byte at +0x41.
    void FUN_00433C90(unsigned char value);
    // FUNCTION: GAMEMD 0x433CA0 (decl; reloc) -- takes a rectangle pointer.
    void FUN_00433CA0(TipRectLTRB_00478E30* rect);
    // FUNCTION: GAMEMD 0x433CF0 (decl; reloc) -- measure text: (text, out width,
    // out height, maximum width), __thiscall, RET 0x10.
    void FUN_00433CF0(const wchar_t* text, int* width, int* height, int maxWidth);
};
// GLOBAL: GAMEMD 0x89C4D0
extern TipFont_00478BA0* FontInstance_0089C4D0;

// The object at 0x89C4B8 whose 0x434CD0 prints text (ten stack arguments,
// RET 0x28). Declared here only as a call target.
struct TipPrinter_00478E30
{
    // FUNCTION: GAMEMD 0x434CD0 (decl; reloc) -- text print.
    int FUN_00434CD0(TipFont_00478BA0* font, TipSurface_00478E30* surface,
                     const wchar_t* text, int x, int y, int width, int height,
                     int a8, int a9, int a10);
};
// GLOBAL: GAMEMD 0x89C4B8
extern TipPrinter_00478E30* PrinterInstance_0089C4B8;

// RTTI (COL 0x80E560): CCToolTip derives from ToolTipManager at offset 0.
struct CCToolTip : public ToolTipManager
{
    // VTABLE: GAMEMD 0x7F74C4
    unsigned char OnSidebar;     // +0x260
    // (+0x261..0x267: not touched by this module)

    // Slots 1..5; slot 0 (deleting destructor) is outside this module.
    // FUNCTION: GAMEMD 0x478BA0 -- slot 1
    virtual bool Update(ToolTipManagerData& from);
    // FUNCTION: GAMEMD 0x478DB0 -- slot 2
    virtual void MarkToRedraw(ToolTipManagerData& from);
    // FUNCTION: GAMEMD 0x478E10 -- slot 3
    virtual void Draw(bool onSidebar);
    // FUNCTION: GAMEMD 0x478E30 -- slot 4
    virtual void DrawText(ToolTipManagerData& from);
    // FUNCTION: GAMEMD 0x479050 -- slot 5
    virtual wchar_t* GetToolTipText(unsigned int id);
};
GG_STATIC_ASSERT(offsetof(CCToolTip, OnSidebar) == 0x260);

#endif  // GG_MATCH_UI_INPUT_CONTROLS_SIDEBAR_CCTOOLTIP_H
