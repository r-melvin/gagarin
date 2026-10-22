// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Layout, vtable slots and ABI read numerically off the user's retail gamemd.exe v1.001 via the local Ghidra
//   CLI and REA (entry disassembly at 0x40D230, 0x40D240, 0x4F4240, 0x4F42B0, 0x4F4320, 0x4F43F0, 0x4F4410, 0x4F4450,
//   0x4F45B0, 0x4F4BB0, 0x4F4C00) and the RTTI vtable .?AVGScreenClass@@ at 0x7EA6FC (22 slots; locator 0x008027F0).
//   Names are descriptive of the observed behaviour (button list, key / mouse input); no source is transcribed.
//
// GScreenClass: the base screen object (COM-shaped primary vtable, 22 slots, vptr at +0), declared in
// ui_display_chain.h with the rest of the display chain; this header keeps the foreign objects its entries reach.
//
//   +0x00 vptr
//   +0x04 unknown_04  int   (decayed by vf_10, 0x4F4BB0)
//   +0x08 unknown_08  int   (decayed by vf_10, 0x4F4BB0)
//   +0x0C RedrawFlag  int   (see match/ui/gscreen_class_render_methods.h; not touched here)
#ifndef GG_MATCH_UI_INPUT_CONTROLS_DISPLAY_GSCREEN_H
#define GG_MATCH_UI_INPUT_CONTROLS_DISPLAY_GSCREEN_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "ui_display_chain.h"
#include "mouse_ww_mouse_class.h"

// GLOBAL: GAMEMD 0x7F7C90 -- IID_IUnknown.
extern const DisplayGuid IID_IUnknown_007F7C90;
// GLOBAL: GAMEMD 0x7EA6E8 -- the interface id GScreenClass answers to (immediately precedes its vtable at 0x7EA6FC).
extern const DisplayGuid IID_GScreen_007EA6E8;

// GLOBAL: GAMEMD 0xA8EF54 -- the head of the screen's button (gadget) list.
extern DisplayGadget* DisplayButtonList_00A8EF54;

// WWMouseClass::Instance (GLOBAL 0x887640) is WWMouseClassInstance, mouse_ww_mouse_class.h.

// The object at 0x87F770 and the two entry points the keyboard fallback in Input reads through.
struct DisplayKeyboard
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x54F000 (decl; reloc)
    int FUN_0054F000();
    // FUNCTION: GAMEMD 0x54F050 (decl; reloc)
    int FUN_0054F050();
};
// GLOBAL: GAMEMD 0x87F770
extern DisplayKeyboard* DisplayKeyboard_0087F770;

// A drawing surface: only the pointers matter here, plus the dword at +0x1C that 0x4F45B0 hands to the batch.
struct DisplaySurface
{
    char unknown_00[0x1C];   // +0x00
    int  unknown_1C;         // +0x1C
};
GG_STATIC_ASSERT(offsetof(DisplaySurface, unknown_1C) == 0x1C);
// GLOBAL: GAMEMD 0x88730C
extern DisplaySurface* DisplaySurface_0088730C;
// GLOBAL: GAMEMD 0x887314
extern DisplaySurface* DisplaySurface_00887314;
// GLOBAL: GAMEMD 0x88731C -- DSurface::Composite.
extern DisplaySurface* DisplaySurface_0088731C;

// The Direct3D-style device the overlay pass brackets with two stdcall slots (0x28 and 0x2C, `this` pushed).
class DisplayDevice
{
public:
    virtual long __stdcall vf_00();   // 0x00
    virtual long __stdcall vf_01();   // 0x04
    virtual long __stdcall vf_02();   // 0x08
    virtual long __stdcall vf_03();   // 0x0C
    virtual long __stdcall vf_04();   // 0x10
    virtual long __stdcall vf_05();   // 0x14
    virtual long __stdcall vf_06();   // 0x18
    virtual long __stdcall vf_07();   // 0x1C
    virtual long __stdcall vf_08();   // 0x20
    virtual long __stdcall vf_09();   // 0x24
    virtual long __stdcall BeginScene();   // 0x28
    virtual long __stdcall EndScene();     // 0x2C
};
// GLOBAL: GAMEMD 0x8A0DF8
extern DisplayDevice* DisplayDevice_008A0DF8;

// One 0x60-byte batch of three vertices. The constructor takes three bytes of colour (0x80 each) and SetVertex takes
// the vertex index followed by five floats.
struct DisplayTriangle
{
    char data[0x60];
    // FUNCTION: GAMEMD 0x4A35A0 (decl; reloc)
    DisplayTriangle(int a, int b, int c);
    // FUNCTION: GAMEMD 0x4A35F0 (decl; reloc)
    void SetVertex(int index, float x, float y, float z, float u, float v);
};
GG_STATIC_ASSERT(sizeof(DisplayTriangle) == 0x60);

// The three objects of the overlay pass (0x8A0E08, 0x8A0E0C, 0x8A0E10). Their methods are contiguous
// (0x4A33A0, 0x4A3660, 0x4A3840), so one class is assumed; the binary does not state it.
struct DisplayLayer
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x4A33A0 (decl; reloc)
    int FUN_004A33A0(int arg);
    // FUNCTION: GAMEMD 0x4A3660 (decl; reloc)
    void FUN_004A3660(int arg);
    // FUNCTION: GAMEMD 0x4A3840 (decl; reloc)
    void FUN_004A3840(DisplayTriangle* batch);
};
// GLOBAL: GAMEMD 0x8A0E08
extern DisplayLayer* DisplayLayer_008A0E08;
// GLOBAL: GAMEMD 0x8A0E0C
extern DisplayLayer* DisplayLayer_008A0E0C;
// GLOBAL: GAMEMD 0x8A0E10
extern DisplayLayer* DisplayLayer_008A0E10;
// GLOBAL: GAMEMD 0x8A0DF0 -- the overlay pass is enabled.
extern bool DisplayFlag_008A0DF0;
// GLOBAL: GAMEMD 0xA9FA94
extern bool DisplayFlag_00A9FA94;
// GLOBAL: GAMEMD 0xA8ED84 -- Unsorted::CurrentFrame.
extern int DisplayCurrentFrame_00A8ED84;

// FUNCTION: GAMEMD 0x4F4780 (decl; reloc) -- __fastcall: bool in CL, surface in EDX, one stacked int.
void __fastcall FUN_004F4780(bool flag, DisplaySurface* surface, int arg);

// GScreenClass itself is declared in ui_display_chain.h.

#endif  // GG_MATCH_UI_INPUT_CONTROLS_DISPLAY_GSCREEN_H
