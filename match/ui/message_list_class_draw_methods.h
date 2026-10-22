// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x5D49A0: on the list `byte [ESI+0x19]` (IsEdit),
//   `[ESI+0x10]` (MaxCharacters), `[ESI+0x24]` (the edit label),
//   `[ESI+0x2B0]`/`[ESI+0x2B4]` (current/initial edit position, signed
//   compare) and `word [ESI+0x2B8]` (the cursor character); on the label
//   `[EAX+0x0C]`/`[EAX+0x10]` (X/Y), `[EAX+0x2C]` (print flags, also the ECX
//   argument of the font getter 0x4A60D0), `[EAX+0x30]` (text) and
//   `[EAX+0x34]` (colour-scheme index into `[0xB054D4]`); label vtable slots
//   +0x2C (`PUSH 1`), +0x58 (bool, no args) and +0x6C (`PUSH 1`); mouse
//   singleton `[0x887640]` slots +0x0C/+0x10; surface `[0x887314]` slot
//   +0x78 (rect out-pointer, returned in EAX); the text print at 0x4A61C0 is
//   __cdecl with eight stack words (hidden Point2D return first). Names are
//   YRpp's.
#ifndef GG_MATCH_UI_MESSAGE_LIST_CLASS_DRAW_METHODS_H
#define GG_MATCH_UI_MESSAGE_LIST_CLASS_DRAW_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// 8-byte point returned through a hidden pointer (needs the user-declared
// constructor — see the "Struct returns" rule). The (x, y) constructor is what
// makes the cursor position load X and Y before storing either (Y first).
struct Point2D_005D49A0
{
    int X;                    // +0x0000
    int Y;                    // +0x0004
    Point2D_005D49A0() {}
    Point2D_005D49A0(int x, int y) : X(x), Y(y) {}
};
GG_STATIC_ASSERT(sizeof(Point2D_005D49A0) == 0x8);

struct Rect_005D49A0
{
    int X;                    // +0x0000
    int Y;                    // +0x0004
    int Width;                // +0x0008
    int Height;               // +0x000C
};
GG_STATIC_ASSERT(sizeof(Rect_005D49A0) == 0x10);

// Colour-scheme registry Items pointer.
struct ColorScheme_005D49A0;
// GLOBAL: GAMEMD 0xB054D4 — ColorScheme::Array.Items.
extern ColorScheme_005D49A0** DAT_00B054D4;

// The active font: only its pixel-width query is used.
struct Font_005D49A0
{
    // FUNCTION: GAMEMD 0x433ED0 (decl; reloc) — pixel width of the text
    // (`this` unused by the callee, but the caller loads the font into ECX).
    int TextWidth(const wchar_t* text, int flag);
};
// FUNCTION: GAMEMD 0x4A60D0 (decl; reloc) — the font for a set of print
// flags (flags in ECX).
Font_005D49A0* FUN_004A60D0(int flags);

// Surface: only the rect query slot.
struct SurfaceVtbl_005D49A0;
struct Surface_005D49A0
{
    SurfaceVtbl_005D49A0* Vtbl;   // +0x0000
};
typedef Rect_005D49A0* (Surface_005D49A0::*Fn78_005D49A0)(Rect_005D49A0* out);
struct SurfaceVtbl_005D49A0
{
    char _pad000[0x78];           // +0x0000
    Fn78_005D49A0 GetRect;        // +0x0078
};
GG_STATIC_ASSERT(offsetof(SurfaceVtbl_005D49A0, GetRect) == 0x78);
// GLOBAL: GAMEMD 0x887314 — DSurface::Temp.
extern Surface_005D49A0* DAT_00887314;

// WWMouseClass: hide (+0x0C) and show (+0x10).
struct MouseVtbl_005D49A0;
struct Mouse_005D49A0
{
    MouseVtbl_005D49A0* Vtbl;     // +0x0000
};
typedef void (Mouse_005D49A0::*FnMouse_005D49A0)();
struct MouseVtbl_005D49A0
{
    char _pad000[0xC];            // +0x0000
    FnMouse_005D49A0 At_0C;       // +0x000C
    FnMouse_005D49A0 At_10;       // +0x0010
};
GG_STATIC_ASSERT(offsetof(MouseVtbl_005D49A0, At_0C) == 0xC);
GG_STATIC_ASSERT(offsetof(MouseVtbl_005D49A0, At_10) == 0x10);
// GLOBAL: GAMEMD 0x887640 — WWMouseClass::Instance.
extern Mouse_005D49A0* DAT_00887640;

// FUNCTION: GAMEMD 0x4A61C0 (decl; reloc) — print `text` on the surface
// inside `clip` at `pos` in `scheme`; the returned point comes back through
// the hidden first stack word.
Point2D_005D49A0 __cdecl FUN_004A61C0(const wchar_t* text, Surface_005D49A0* surface,
                                      Rect_005D49A0* clip, Point2D_005D49A0* pos,
                                      ColorScheme_005D49A0* scheme, int back, int flags);

// TextLabelClass gadget as seen from Draw: X/Y, the print flags, the text and
// the colour-scheme index, plus three vtable slots.
struct LabelVtbl_005D49A0;
struct Label_005D49A0
{
    LabelVtbl_005D49A0* Vtbl;     // +0x0000
    char _pad004[0x0C - 0x04];    // +0x0004
    int  X;                       // +0x000C
    int  Y;                       // +0x0010
    char _pad014[0x2C - 0x14];    // +0x0014
    int  Flags;                   // +0x002C  TextPrintType
    const wchar_t* Text;          // +0x0030
    int  SchemeIndex;             // +0x0034
};
GG_STATIC_ASSERT(offsetof(Label_005D49A0, X) == 0x0C);
GG_STATIC_ASSERT(offsetof(Label_005D49A0, Y) == 0x10);
GG_STATIC_ASSERT(offsetof(Label_005D49A0, Flags) == 0x2C);
GG_STATIC_ASSERT(offsetof(Label_005D49A0, Text) == 0x30);
GG_STATIC_ASSERT(offsetof(Label_005D49A0, SchemeIndex) == 0x34);

typedef void (Label_005D49A0::*Fn2C_005D49A0)(int flag);
typedef bool (Label_005D49A0::*Fn58_005D49A0)();
typedef void (Label_005D49A0::*Fn6C_005D49A0)(int flag);
struct LabelVtbl_005D49A0
{
    char _pad000[0x2C];           // +0x0000
    Fn2C_005D49A0 At_2C;          // +0x002C
    char _pad030[0x58 - 0x30];    // +0x0030
    Fn58_005D49A0 At_58;          // +0x0058
    char _pad05C[0x6C - 0x5C];    // +0x005C
    Fn6C_005D49A0 At_6C;          // +0x006C
};
GG_STATIC_ASSERT(offsetof(LabelVtbl_005D49A0, At_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(LabelVtbl_005D49A0, At_58) == 0x58);
GG_STATIC_ASSERT(offsetof(LabelVtbl_005D49A0, At_6C) == 0x6C);

struct MessageList_005D49A0
{
    Label_005D49A0* MessageList;  // +0x0000  list head
    char _pad004[0x10 - 0x04];    // +0x0004
    int  MaxCharacters;           // +0x0010
    char _pad014[0x19 - 0x14];    // +0x0014
    unsigned char IsEdit;         // +0x0019
    char _pad01A[0x24 - 0x1A];    // +0x001A
    Label_005D49A0* EditLabel;    // +0x0024
    char _pad028[0x2B0 - 0x28];   // +0x0028
    int  EditCurrentPos;          // +0x02B0
    int  EditInitialPos;          // +0x02B4
    wchar_t EditCursor;           // +0x02B8

    // FUNCTION: GAMEMD 0x5D49A0 — MessageListClass::Draw.
    void Draw();
};
GG_STATIC_ASSERT(offsetof(MessageList_005D49A0, MaxCharacters) == 0x10);
GG_STATIC_ASSERT(offsetof(MessageList_005D49A0, IsEdit) == 0x19);
GG_STATIC_ASSERT(offsetof(MessageList_005D49A0, EditLabel) == 0x24);
GG_STATIC_ASSERT(offsetof(MessageList_005D49A0, EditCurrentPos) == 0x2B0);
GG_STATIC_ASSERT(offsetof(MessageList_005D49A0, EditInitialPos) == 0x2B4);
GG_STATIC_ASSERT(offsetof(MessageList_005D49A0, EditCursor) == 0x2B8);

#endif  // GG_MATCH_UI_MESSAGE_LIST_CLASS_DRAW_METHODS_H
