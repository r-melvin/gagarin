// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, slots and conventions read numerically off the user's retail gamemd.exe v1.001 via the local Ghidra
//   CLI and REA (entry disassembly at 0x4A8850, 0x4A88C0, 0x4A8930, 0x4A8960, 0x4A9700, 0x4A9840, 0x4AC310,
//   0x4AC380, 0x4AE6B0, 0x4AE6F0, 0x4AE720, 0x4AEAD0) and the RTTI vtable .?AVDisplayClass@@ at 0x7E6114 (50 slots,
//   vtable_slots.json census). Names describe observed behaviour only.
//
// The class hierarchy and the members (+0x1174 .. +0x11E0) are in ui_display_chain.h; this header keeps the foreign
// objects the DisplayClass entries reach.
#ifndef GG_MATCH_UI_INPUT_CONTROLS_DISPLAY_CLASS_H
#define GG_MATCH_UI_INPUT_CONTROLS_DISPLAY_CLASS_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "display_gscreen.h"
#include "../tooltip_manager_shared.h"

// ---- foreign objects the entries reach ----------------------------------------------------------------------

// The tactical view rectangle as the globals below hold it (x, y, width, height); vf_47 copies the origin as one
// point, so the first two fields are kept as a Point2D.
struct DisplayRect
{
    Point2D Origin;   // +0x00
    int Width;        // +0x08
    int Height;       // +0x0C
};
GG_STATIC_ASSERT(sizeof(DisplayRect) == 0x10);

// TacticalClass (0x887324). Only the entries below are reached.
struct DisplayTactical
{
    char  unknown_000[0xD8];   // +0x000
    float unknown_0D8;         // +0x0D8  compared with 0.0f by ScrollClass at 0x693060
    char  unknown_0DC[0xD7D - 0xDC];   // +0x0DC
    bool  unknown_D7D;         // +0xD7D  set by vf_47

    // FUNCTION: GAMEMD 0x6D5F60 (decl; reloc)
    void FUN_006D5F60(const DisplayRect* rect);
    // FUNCTION: GAMEMD 0x6D8530 (decl; reloc)
    void FUN_006D8530(int a, int b);
    // FUNCTION: GAMEMD 0x6D9F80 (decl; reloc)
    void FUN_006D9F80(const Point2D* where);
    // FUNCTION: GAMEMD 0x6D9FC0 (decl; reloc)
    void FUN_006D9FC0(const Point2D* where);
    // FUNCTION: GAMEMD 0x6DA160 (decl; reloc)
    void FUN_006DA160();
    // FUNCTION: GAMEMD 0x6DA230 (decl; reloc)
    int FUN_006DA230(int a);
};
GG_STATIC_ASSERT(offsetof(DisplayTactical, unknown_0D8) == 0xD8);
GG_STATIC_ASSERT(offsetof(DisplayTactical, unknown_D7D) == 0xD7D);
// GLOBAL: GAMEMD 0x887324 -- TacticalClass::Instance.
extern DisplayTactical* DisplayTactical_00887324;

// A draw layer: a vector object (vptr at +0) laid out in 0x18-byte elements from 0x8A0360; vf_03 is dispatched
// through slot 3, Load / Save are direct calls.
class DisplayLayerVec
{
public:
    virtual void vf_00();   // 0x00
    virtual void vf_01();   // 0x04
    virtual void vf_02();   // 0x08
    virtual void vf_03();   // 0x0C
    char unknown_04[0x14];  // +0x04

    // FUNCTION: GAMEMD 0x551B90 (decl; reloc) -- read the layer from a stream (existing matched row).
    long Load(IStream* stream);
    // FUNCTION: GAMEMD 0x551B20 (decl; reloc) -- write the layer to a stream (existing matched row).
    long Save(IStream* stream);
};
GG_STATIC_ASSERT(sizeof(DisplayLayerVec) == 0x18);
// GLOBAL: GAMEMD 0x8A0360 -- the draw-layer array (five layers, ends at 0x8A03D8).
extern DisplayLayerVec DisplayLayers_008A0360[5];

// A control the screen adds to its button list (0x8A06F8): a gadget with a refresh call.
class DisplayTacticalButton : public DisplayGadget
{
public:
    char unknown_04[0x38 - 4];
    // FUNCTION: GAMEMD 0x5565F0 (decl; reloc) -- LinkClass::Zap.
    void FUN_005565F0();
};
// GLOBAL: GAMEMD 0x8A06F8
extern DisplayTacticalButton DisplayButton_008A06F8;

// GLOBAL: GAMEMD 0xA8ED6B -- Unsorted::ArmageddonMode (byte).
extern bool DisplayFlag_00A8ED6B;
// GLOBAL: GAMEMD 0xA8ED9D (byte, set by vf_35)
extern bool DisplayFlag_00A8ED9D;

// GLOBAL: GAMEMD 0x8A03FC -- the PLACE.SHP shape.
extern void* DisplayPlaceShape_008A03FC;
// GLOBAL: GAMEMD 0x8A072C -- the SHADOW.SHP shape.
extern void* DisplayShadowShape_008A072C;

// FUNCTION: GAMEMD 0x5B40B0 (decl; reloc) -- MixFileClass::Retrieve: name in ECX, flag in DL, shape pointer in EAX.
void* __fastcall FUN_005B40B0(const char* name, bool flag);
// FUNCTION: GAMEMD 0x72AD20 (decl; reloc) -- fills the 16-byte rectangle passed in ECX and returns it.
RectangleStruct* __fastcall FUN_0072AD20(RectangleStruct* out);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- square root of a double (cdecl, result in ST0).
double __cdecl FUN_004CAC40(double value);

// GLOBAL: GAMEMD 0xB73554 -- a window handle, cleared by vf_34.
extern void* DisplayWindow_00B73554;
extern "C" __declspec(dllimport) int __stdcall CloseWindow(void* hwnd);

// ---- objects of the view-dimension entry (0x4A8960) ---------------------------------------------------------

// GLOBAL: GAMEMD 0x886FA0 -- the tactical view rectangle (x, y, width, height).
extern DisplayRect DisplayViewRect_00886FA0;
// GLOBAL: GAMEMD 0x8A0704 -- a second copy of the view rectangle.
extern DisplayRect DisplayViewRectCopy_008A0704;

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- printf-style log, caller cleans the stack.
void __cdecl FUN_004068E0(const char* format, ...);

// The 0x30-byte depth buffer (0x887644) and alpha buffer (0x87E8A4) allocated for the view; both are built from
// the 16-byte rectangle passed by value and torn down with ReleaseSurface.
class DisplayZBuffer
{
public:
    char unknown_00[0x24];   // +0x00
    int  unknown_24;         // +0x24  set to 0x8000 after construction
    char unknown_28[0x30 - 0x28];   // +0x28
    // FUNCTION: GAMEMD 0x7BC970 (decl; reloc)
    DisplayZBuffer(DisplayRect rect);
    // FUNCTION: GAMEMD 0x7BCAE0 (decl; reloc)
    void ReleaseSurface();
};
GG_STATIC_ASSERT(sizeof(DisplayZBuffer) == 0x30);
GG_STATIC_ASSERT(offsetof(DisplayZBuffer, unknown_24) == 0x24);
// GLOBAL: GAMEMD 0x887644
extern DisplayZBuffer* DisplayZBuffer_00887644;

class DisplayABuffer
{
public:
    char unknown_00[0x30];   // +0x00
    // FUNCTION: GAMEMD 0x410CE0 (decl; reloc)
    DisplayABuffer(DisplayRect rect);
    // FUNCTION: GAMEMD 0x410E50 (decl; reloc)
    void ReleaseSurface();
};
GG_STATIC_ASSERT(sizeof(DisplayABuffer) == 0x30);
// GLOBAL: GAMEMD 0x87E8A4
extern DisplayABuffer* DisplayABuffer_0087E8A4;

// FUNCTION: GAMEMD 0x7C8B3D / 0x7C8E17 are the CRT operator delete / new, reached through new and delete.

// The map object at 0x87F7E8 is Map_0087F7E8 (ui_display_chain.h).

// GLOBAL: GAMEMD 0x887368 -- CCToolTip::Instance (a ToolTipManager, match/ui/tooltip_manager_shared.h); the view
// change re-registers the tactical tooltip (id 500) through Remove / Add.
extern ToolTipManager* ToolTipManager_Instance;

// The on-screen message list at 0xA8BC60 (the instance itself is the receiver).
struct DisplayMessageList
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x5D3A60 (decl; reloc)
    void FUN_005D3A60(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);
    // FUNCTION: GAMEMD 0x5D4AD0 (decl; reloc)
    void FUN_005D4AD0(int width);
};
// GLOBAL: GAMEMD 0xA8BC60 -- MessageListClass::Instance.
extern DisplayMessageList DisplayMessageList_00A8BC60;

// MapClass and DisplayClass themselves are declared in ui_display_chain.h.

#endif  // GG_MATCH_UI_INPUT_CONTROLS_DISPLAY_CLASS_H
