// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Shared views for the UI input/controls module (the lists and controls clusters): rectangles, points,
//   the surface, the mouse and keyboard singletons, colour schemes, the palette-to-pixel lookup, the font
//   and the shape header, plus the text/box/shape draw helpers they are passed to. Every slot and offset is
//   read off a retail gamemd.exe v1.001 instruction in a function of this module; the class and member names
//   are descriptive unless a comment names their source. Placeholder DAT_/FUN_ names are kept where no real
//   name is confirmed.
//
//   These views replace the duplicate copies that lists_views.h and controls_views.h used to carry
//   (Rect/ControlsRect, Point2D/ControlsPoint, Box/ControlsBox, Surface/ControlsSurfaceView,
//   Mouse/ControlsMouseView, ColorScheme/ControlsColorScheme, PixelFormat/ControlsColorLookup,
//   Font/ControlsFont, ShapeHeader/ControlsShapeHeader). Where the two copies disagreed the choice is noted
//   beside the member.
#ifndef GG_MATCH_UI_INPUT_CONTROLS_UI_COMMON_H
#define GG_MATCH_UI_INPUT_CONTROLS_UI_COMMON_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"

// A screen rectangle: X, Y, Width, Height (four dwords).
struct Rect
{
    int X;       // +0x00
    int Y;       // +0x04
    int Width;   // +0x08
    int Height;  // +0x0C

    Rect() {}
    Rect(int x, int y, int w, int h) : X(x), Y(y), Width(w), Height(h) {}
};
GG_STATIC_ASSERT(sizeof(Rect) == 0x10);

// A point; returned by the print routines through a hidden pointer, so it has a user-declared constructor.
struct Point2D
{
    int X;  // +0x00
    int Y;  // +0x04

    Point2D() {}
    Point2D(int x, int y) : X(x), Y(y) {}
};
GG_STATIC_ASSERT(sizeof(Point2D) == 0x08);

// A rectangle given as left, top, right and bottom edges (the surface outline slot +0x58 takes one).
struct Box
{
    int Left;    // +0x00
    int Top;     // +0x04
    int Right;   // +0x08
    int Bottom;  // +0x0C

    Box() {}
    Box(int l, int t, int r, int b) : Left(l), Top(t), Right(r), Bottom(b) {}
};
GG_STATIC_ASSERT(sizeof(Box) == 0x10);

// The leading words of a loaded shape file: a zero word, then width and height (ShapeButton 0x69DD83 and the
// drop list constructor 0x4B4E10 read +0x02 and +0x04).
struct ShapeHeader
{
    short unknown_00;  // +0x00
    short Width;       // +0x02
    short Height;      // +0x04
};
GG_STATIC_ASSERT(offsetof(ShapeHeader, Width) == 0x02);
GG_STATIC_ASSERT(offsetof(ShapeHeader, Height) == 0x04);

// The surface behind [0x887314] (and [0x887300]). Slots read in this module: +0x14 (rectangle, colour), +0x58
// (box, colour), +0x70 (no arguments), +0x78 (returns a rectangle through the hidden return pointer) and +0x7C
// (no arguments). The lists copy declared +0x14 as returning void; no caller reads the result, the controls
// copy's int is kept.
struct Surface
{
    virtual void vf_00();
    virtual void vf_04();
    virtual void vf_08();
    virtual void HideCursor();             // +0x0C
    virtual void ShowCursor();             // +0x10
    virtual int  FillRect(Rect* area, unsigned colour);    // +0x14
    virtual void vf_18();
    virtual void vf_1C();
    virtual void vf_20();
    virtual void vf_24();
    virtual void vf_28();
    virtual void vf_2C();
    virtual void vf_30();
    virtual void vf_34();
    virtual void vf_38();
    virtual void vf_3C();
    virtual void vf_40();
    virtual void vf_44();
    virtual void vf_48();
    virtual void vf_4C();
    virtual void vf_50();
    virtual void vf_54();
    virtual int  OutlineRect(Box* area, unsigned colour);  // +0x58
    virtual void vf_5C();
    virtual void vf_60();
    virtual void vf_64();
    virtual void vf_68();
    virtual void vf_6C();
    virtual int  GetBytesPerPixel();                      // +0x70
    virtual void vf_74();
    virtual Rect GetRect();                               // +0x78, struct return: hidden out pointer
    virtual int  GetWidth();                              // +0x7C
};
// GLOBAL: GAMEMD 0x887314 -- the surface the gadgets draw on.
extern Surface* DAT_00887314;
// GLOBAL: GAMEMD 0x887300 -- the sidebar surface.
extern Surface* DAT_00887300;

// The window-manager mouse singleton at [0x887640]. Slots read here: +0x0C and +0x10 (hide and show the cursor,
// no arguments; LoadOptions 0x559D60), +0x20 (takes a rectangle by value and pops it itself), +0x24 (no
// arguments), +0x28 (the hide count; LoadOptions), +0x2C and +0x30 (return the pointer X and Y).
struct Mouse
{
    virtual void vf_00();
    virtual void vf_04();
    virtual void vf_08();
    virtual void HideCursor();             // +0x0C
    virtual void ShowCursor();             // +0x10
    virtual void vf_14();
    virtual void vf_18();
    virtual void vf_1C();
    virtual void HideRegion(Rect region);  // +0x20
    virtual void ShowRegion();             // +0x24
    virtual int  GetCursorCount();         // +0x28
    virtual int  GetX();                   // +0x2C
    virtual int  GetY();                   // +0x30
};
// GLOBAL: GAMEMD 0x887640 -- the window-manager mouse singleton.
extern Mouse* DAT_00887640;

// Keyboard singleton (0x87F770): the first two dwords hold the pointer position recorded with the last
// mouse-button key event; 0x54F000 Check, 0x54F050 Get, 0x54F5C0 Down, 0x54F450 ToAscii.
struct Keyboard
{
    int MouseX;  // +0x00
    int MouseY;  // +0x04

    unsigned short Check();
    unsigned short Get();
    bool           Down(int key);
    char           ToAscii(int key);
};
// GLOBAL: GAMEMD 0x87F770 -- the keyboard singleton.
extern Keyboard* DAT_0087F770;

// Palette-to-pixel lookup: [0x87F6C4], every scheme's +0x30C and ShapeButton's draw context (+0x50, stored
// from [0x87F6C4] by 0x69DD64 and passed to the shape blitter). +0x04 is the bytes per pixel (1: byte table,
// else word table) and +0x174 points at the table. (Was PixelFormat in lists, ControlsColorLookup in controls.)
struct ColorConvert
{
    int   unknown_00;
    int   BytesPerPixel;           // +0x04
    char  unknown_08[0x174 - 0x08];
    void* ColorTable;              // +0x174

    // The table is indexed by colour number; the entry is a byte when BytesPerPixel is 1.
    unsigned Lookup(int index) const
    {
        if (BytesPerPixel == 1)
            return ((const unsigned char*)ColorTable)[index];
        return ((const unsigned short*)ColorTable)[index];
    }
};
GG_STATIC_ASSERT(offsetof(ColorConvert, BytesPerPixel) == 0x04);
GG_STATIC_ASSERT(offsetof(ColorConvert, ColorTable) == 0x174);
// GLOBAL: GAMEMD 0x87F6C4 -- the palette lookup used by the gauges, lists and shape buttons.
extern ColorConvert* DAT_0087F6C4;

struct RGBTriple
{
    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;
};
GG_STATIC_ASSERT(sizeof(RGBTriple) == 0x03);

// The colour object embedded at scheme +0x308; 0x517440 adjusts it and hands back an RGB triple.
struct ColorSchemeTint
{
    char unknown_00[4];
    const RGBTriple* Adjust(int* amount);   // 0x517440, RET 4
};

// One colour scheme. Offsets read in this module: +0x308 (TextLabel 0x72A4A0), +0x30C (TextButton 0x720070),
// +0x314 and +0x31C (the list draw slots), +0x330 (Gauge 0x4E2690).
struct ColorScheme
{
    char             unknown_000[0x308];
    ColorSchemeTint  Tint;            // +0x308 (the object ends before +0x30C)
    ColorConvert*    Convert;         // +0x30C
    char             unknown_310[0x314 - 0x310];
    int              BarColorIndex;   // +0x314
    char             unknown_318[0x31C - 0x318];
    int              TextColorIndex;  // +0x31C
    char             unknown_320[0x330 - 0x320];
    int              ThemeColour;     // +0x330
};
GG_STATIC_ASSERT(offsetof(ColorScheme, Tint) == 0x308);
GG_STATIC_ASSERT(offsetof(ColorScheme, Convert) == 0x30C);
GG_STATIC_ASSERT(offsetof(ColorScheme, BarColorIndex) == 0x314);
GG_STATIC_ASSERT(offsetof(ColorScheme, TextColorIndex) == 0x31C);
GG_STATIC_ASSERT(offsetof(ColorScheme, ThemeColour) == 0x330);

// The scheme registry at 0xB054D0: a dynamic vector of scheme pointers (Items at +4, active count at +0x10).
// Retail indexes it through an accessor that returns the element by reference, so every use loads [0xB054D4]
// and then the pointer. (The lists copy bound the Items word 0xB054D4 directly as a ColorScheme**; this one
// object replaces both.)
struct ColorSchemeVector
{
    void*         unknown_00;
    ColorScheme** Items;      // +0x04
    int           Capacity;   // +0x08
    int           unknown_0C;
    int           Count;      // +0x10
    int           Growth;     // +0x14

    ColorScheme*& operator[](int index) { return Items[index]; }
};
GG_STATIC_ASSERT(offsetof(ColorSchemeVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(ColorSchemeVector, Count) == 0x10);
// GLOBAL: GAMEMD 0xB054D0 -- the colour-scheme registry.
extern ColorSchemeVector DAT_00B054D0;

// The font returned by 0x4A60D0. Its height (+0x1C) and the width queries are used here.
struct Font
{
    char unknown_000[0x1C];
    int  Height;                                    // +0x1C

    int TextWidth(const wchar_t* text, int flag);   // 0x433ED0, RET 8
    int CharWidth(unsigned short ch);               // 0x4349B0
};
GG_STATIC_ASSERT(offsetof(Font, Height) == 0x1C);

// 0x4A60D0: the font for a set of print flags (flags in ECX).
Font* __fastcall FUN_004A60D0(int flags);
// 0x4A5A50: bevelled box. Rectangle in ECX, style in EDX, one stack argument (RET 4).
void __fastcall FUN_004A5A50(Rect* area, int style, int arg);
// 0x4A6500: text draw. The hidden return buffer arrives in ECX and the text in EDX, the rest on the stack
// (callee pops 0x20).
Point2D __fastcall FUN_004A6500(const wchar_t* text, Surface* surface, Rect* clip, Point2D* pos,
                                ColorScheme* scheme, int back, unsigned flags, int width, int tabStops);
// 0x4A61C0: prints text on a surface inside a clip rectangle; the returned point comes back through the
// hidden first stack word. Caller-cleaned (cdecl).
Point2D __cdecl FUN_004A61C0(const wchar_t* text, Surface* surface, Rect* clip, Point2D* position,
                             ColorScheme* scheme, int background, int flags);
// 0x4A6010: print variant with one extra trailing argument. The result point is written through the pointer
// in ECX and the text is in EDX; seven words follow on the stack (RET 0x1C).
void __fastcall FUN_004A6010(Point2D* result, const wchar_t* text, Surface* surface, Rect* clip,
                             Point2D* position, ColorScheme* scheme, int background, int flags, int extra);
// 0x4AED70: shape blitter. Surface in ECX, the palette lookup in EDX, fourteen stack words.
void __fastcall FUN_004AED70(Surface* surface, ColorConvert* convert, ShapeHeader* shape, int frame,
                             Point2D* position, Rect* clip, int flags, int a8, int a9, int a10, int a11,
                             int a12, int a13, int a14, int a15, int a16);
// 0x623880: draws a label's text. Surface in ECX, rectangle in EDX, nine stack words (RET 0x24).
void __fastcall FUN_00623880(Surface* surface, Rect* area, const wchar_t* text, int length, Font* font,
                             unsigned colour, int* extra, int focused, int a8, int a9, int shown);

#endif  // GG_MATCH_UI_INPUT_CONTROLS_UI_COMMON_H
