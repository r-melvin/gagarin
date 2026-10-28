// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Layout, vtable slots and globals read from the user's retail gamemd.exe v1.001: RTTI
//   .?AVWWMouseClass@@ (type descriptor 0x84E638, vtable 0x7F7B2C, COL 0x80EC60, bases WWMouseClass ->
//   Mouse), .?AVMouse@@ (vtable 0x7F7B78, one slot), the constructor 0x7B8730 (every member store below;
//   it is read-only evidence here, not a scored entry), and the allocation site 0x560D41
//   (`PUSH 0x98; CALL 0x7C8E17`, also 0x6BDEFE's equivalent).
//
// View: mouse-prefixed, address-scoped. WWMouseClass (RTTI) is the software-cursor controller, and this is the one
// view of it for the module (the display, sidebar and tooltip units call it through WWMouseClassInstance). Every
// method below that takes the cursor lock does so through LockMouse() (mouse_ww_mouse_lock.h), the out-of-line
// instance of which sits at 0x7BA2C0 (a `WaitForSingleObject(MouseMutex, 10000)` followed by the "Probable deadlock"
// message at line 0x4FD of wwmous.cpp); the release is `ReleaseMutex(MouseMutex)`.
//
//   +0x00  vptr (Mouse 0x7F7B78, then WWMouseClass 0x7F7B2C)
//   +0x04  unknown_4   (shape-file pointer, ctor 0)       +0x08  CursorFrame
//   +0x0C  unknown_C     (ctor -1; Hide decrements, Show increments)
//   +0x10  Captured      (byte)
//   +0x14  Position (X,Y) +0x1C  ReportedPosition (X,Y)
//   +0x24  Screen (surface the cursor is drawn on)           +0x28  Window (ctor argument)
//   +0x2C  Bounds        (X,Y offset added to draws; Width,Height clamp of ConvertCoords)
//   +0x3C  unknown_3C (X,Y) +0x44  Under   (saved-background surface)
//   +0x48  UnderRect     +0x58  Cache1 +0x5C Cache1Rect +0x6C Cache2 +0x70 Cache2Rect
//   +0x80  (rect)        +0x90 / +0x94 ints; sizeof 0x98
#ifndef GG_MATCH_UI_INPUT_CONTROLS_MOUSE_WW_MOUSE_CLASS_H
#define GG_MATCH_UI_INPUT_CONTROLS_MOUSE_WW_MOUSE_CLASS_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "../../_layout/geometry2d.h"
#include "../../_layout/obj_0069e430.h"

// Surface vtable as the mouse code uses it: slot 0 = deleting destructor (`PUSH 1; CALL [EAX]`),
// slot 2 (+0x08) = the five-argument blit, slot 31 (+0x7C) / 32 (+0x80) = width / height. The match/renderer
// Surface header names slots 0x7C and 0x80 GetWidth / GetHeight; slot 2 is declared there without
// arguments, so this view carries the arguments the mouse code pushes.
class MouseSurfaceView
{
public:
    virtual ~MouseSurfaceView() {}
    virtual void vf_01() = 0;
    virtual bool Blt(const RectangleStruct& dest, MouseSurfaceView* src, const RectangleStruct& srcRect,
                     int arg4, int arg5) = 0;
    virtual void vf_03() = 0;
    virtual void vf_04() = 0;
    virtual void vf_05() = 0;
    virtual bool vf_06(unsigned int color) = 0; // +18 Fill, native0x683E10; renderer7BBAB0
    virtual void vf_07() = 0;
    virtual void vf_08() = 0;
    virtual void vf_09() = 0;
    virtual void vf_10() = 0;
    virtual void vf_11() = 0;
    virtual void vf_12() = 0;
    virtual void vf_13() = 0;
    virtual void vf_14() = 0;
    virtual void vf_15() = 0;
    virtual void vf_16() = 0;
    virtual void vf_17() = 0;
    virtual void vf_18() = 0;
    virtual void vf_19() = 0;
    virtual void vf_20() = 0;
    virtual void vf_21() = 0;
    virtual void vf_22() = 0;
    virtual void vf_23() = 0;
    virtual void vf_24() = 0;
    virtual void vf_25() = 0;
    virtual void vf_26() = 0;
    virtual void vf_27() = 0;
    virtual void vf_28() = 0;
    virtual void vf_29() = 0;
    virtual void vf_30() = 0;
    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;
};

// The cursor code's rectangle: RectangleStruct plus the inline "positive width and height" predicate it applies to its
// saved rectangles and the four-argument constructor at 0x42E410 (__thiscall, RET 0x10, returns `this`). The
// vf_4 / CaptureMouse locals are built by calls to that constructor; the other entries fill their
// RectangleStruct locals field by field.
struct CursorRect : public RectangleStruct
{
    CursorRect() {}
    // FUNCTION: GAMEMD 0x42E410 (decl; reloc)
    CursorRect(int x, int y, int width, int height);
    bool IsPositive() const { return Width > 0 && Height > 0; }
};

// VTABLE: GAMEMD 0x7F7B78 (one slot: the scalar deleting destructor 0x7BA300)
class Mouse
{
public:
    virtual ~Mouse() {}
};

// GLOBAL: GAMEMD 0x00B78160 - a flag read by ConvertCoords (0x7B9D90).
extern bool MouseConvertFlag;
// GLOBAL: GAMEMD 0x00A8EB7C - a flag read by the draw path (0x7B90C0).
extern bool MouseDrawFlag;
// GLOBAL: GAMEMD 0x00886FA8 / 0x00886FB8 - view bound width and an offset used by 0x7B90C0.
extern int MouseViewBoundWidth;
extern int MouseViewOffset;
// GLOBAL: GAMEMD 0x00887300 - the sidebar surface.
extern MouseSurfaceView* MouseSidebarSurface;

// VTABLE: GAMEMD 0x7F7B2C
class WWMouseClass : public Mouse
{
public:
    // ---- virtual slots (complete-object order) ----------------------------------------------
    virtual ~WWMouseClass(); // slot0: body0x7B88D0, deleting wrapper0x7BA3A0
    virtual void SetCursor(const Point2D* hotspot, Obj_0069E430* shape, int frame);      // 1  0x7B8A00
    virtual bool IsMouseHidden();                                                // 2  0x7BA320
    virtual void vf_3();                                                    // 3  0x7B9930
    virtual void vf_4();                                                    // 4  0x7B9750
    virtual void vf_5();                                                 // 5  0x7B9C30
    virtual void CaptureMouse();                                                 // 6  0x7B9A60
    virtual bool IsCaptured();                                                   // 7  0x7BA330
    virtual void vf_8(int a, int b, int c, int d);               // 8  0x7B9D70
    virtual void vf_9();                                         // 9  0x7B9D80
    virtual int GetHideCount();                                                  // 10 0x7B89F0
    virtual int vf_11();                                                     // 11 0x7BA340
    virtual int vf_12();                                                     // 12 0x7BA350
    virtual Point2D* vf_13(Point2D* out);                                  // 13 0x7BA360 (returns `out`)
    virtual void vf_14(int x, int y);                                      // 14 0x7BA380
    virtual void DrawMouseOnto(MouseSurfaceView* surface, bool useCache2);       // 15 0x7B90C0
    virtual void DrawCachedOnto(MouseSurfaceView* surface, bool useCache2);      // 16 0x7B92D0
    virtual void ConvertCoords(int* x, int* y);                                  // 17 0x7B9D90

    // ---- non-virtual neighbours called from the scored entries (declared; reloc) ------------
    bool Method_7B8C60();                                    // 0x7B8C60 __thiscall, no args, bool
    CursorRect Method_7B8E80();                               // 0x7B8E80 __thiscall, hidden result pointer, RET 4
    void Method_7B93F0(MouseSurfaceView* surface, int a, int b);  // 0x7B93F0 __thiscall, RET 0xC

    // ---- inline helpers shared by the scored entries ----------------------------------------
    void RestoreUnder();
    void DrawCursorBlock();

    // ---- members ---------------------------------------------------------------------------
    Obj_0069E430*    unknown_4;       // +0x04
    int                CursorFrame;       // +0x08
    int                unknown_C;         // +0x0C
    bool               Captured;          // +0x10
    Point2D            Position;          // +0x14
    Point2D            ReportedPosition;  // +0x1C
    MouseSurfaceView*  Screen;            // +0x24
    void*              Window;            // +0x28
    RectangleStruct    Bounds;            // +0x2C
    Point2D            unknown_3C;           // +0x3C
    MouseSurfaceView*  Under;             // +0x44
    CursorRect          UnderRect;         // +0x48
    MouseSurfaceView*  Cache1;            // +0x58
    CursorRect          Cache1Rect;        // +0x5C
    MouseSurfaceView*  Cache2;            // +0x6C
    CursorRect          Cache2Rect;        // +0x70
    RectangleStruct    unknown_80;        // +0x80
    int                unknown_90;        // +0x90
    int                unknown_94;        // +0x94
};

GG_STATIC_ASSERT(offsetof(WWMouseClass, unknown_4) == 0x04);
GG_STATIC_ASSERT(offsetof(WWMouseClass, CursorFrame) == 0x08);
GG_STATIC_ASSERT(offsetof(WWMouseClass, unknown_C) == 0x0C);
GG_STATIC_ASSERT(offsetof(WWMouseClass, Captured) == 0x10);
GG_STATIC_ASSERT(offsetof(WWMouseClass, Position) == 0x14);
GG_STATIC_ASSERT(offsetof(WWMouseClass, ReportedPosition) == 0x1C);
GG_STATIC_ASSERT(offsetof(WWMouseClass, Screen) == 0x24);
GG_STATIC_ASSERT(offsetof(WWMouseClass, Window) == 0x28);
GG_STATIC_ASSERT(offsetof(WWMouseClass, Bounds) == 0x2C);
GG_STATIC_ASSERT(offsetof(WWMouseClass, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(WWMouseClass, Under) == 0x44);
GG_STATIC_ASSERT(offsetof(WWMouseClass, UnderRect) == 0x48);
GG_STATIC_ASSERT(offsetof(WWMouseClass, Cache1) == 0x58);
GG_STATIC_ASSERT(offsetof(WWMouseClass, Cache1Rect) == 0x5C);
GG_STATIC_ASSERT(offsetof(WWMouseClass, Cache2) == 0x6C);
GG_STATIC_ASSERT(offsetof(WWMouseClass, Cache2Rect) == 0x70);
GG_STATIC_ASSERT(offsetof(WWMouseClass, unknown_80) == 0x80);
GG_STATIC_ASSERT(offsetof(WWMouseClass, unknown_94) == 0x94);
GG_STATIC_ASSERT(sizeof(((WWMouseClass*)0)->Under) == 4);
GG_STATIC_ASSERT(sizeof(((WWMouseClass*)0)->Cache1) == 4);
GG_STATIC_ASSERT(sizeof(((WWMouseClass*)0)->Cache2) == 4);
// sizeof from the allocation: `PUSH 0x98; CALL 0x7C8E17` at 0x560D41.
GG_STATIC_ASSERT(sizeof(WWMouseClass) == 0x98);

// GLOBAL: GAMEMD 0x00887640 - WWMouseClass::Instance.
extern WWMouseClass* WWMouseClassInstance;

// The cursor lock helpers need <windows.h>; they are in mouse_ww_mouse_lock.h so that this class header can be
// included by the display and sidebar units, which declare their own WinAPI entries.

#endif  // GG_MATCH_UI_INPUT_CONTROLS_MOUSE_WW_MOUSE_CLASS_H
