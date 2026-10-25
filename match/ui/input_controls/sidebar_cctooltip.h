// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
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

#include "../../renderer/pixel_shift_view.h"
#include "../../renderer/composite_surface.h"
#include "../../_layout/geometry2d.h"
#include "../../_layout/rgb_class.h"
#include "../bit_font_print_methods.h"
#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "../tooltip_manager_shared.h"
#include "mouse_ww_mouse_class.h"

// GLOBAL: GAMEMD 0x886F90 -- sidebar rectangle.
extern RectangleStruct SidebarRect_00886F90;
// GLOBAL: GAMEMD 0x886FA0 -- tactical view rectangle.
extern RectangleStruct TacticalRect_00886FA0;
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

// GLOBAL: GAMEMD 0xB0FA1C -- tooltip component bytes at offsets 0, 1, 2.
extern RGBClass TipColor_00B0FA1C;
// GLOBAL: GAMEMD 0x887300 -- polymorphic sidebar surface; concrete type not inferred.
extern Surface* DAT_00887300;
// GLOBAL: GAMEMD 0x89C4D0 -- the existing BitFont state pointer.
extern BitFont* DAT_0089C4D0;

// RTTI (COL 0x80E560): CCToolTip derives from ToolTipManager at offset 0.
class CCToolTip : public ToolTipManager
{
public:
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
