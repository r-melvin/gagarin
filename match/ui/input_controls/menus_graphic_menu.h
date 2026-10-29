// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Menus cluster views (UI input/controls module): the GraphicMenuItem family. Every fact below is read
//   from the retail gamemd.exe v1.001: RTTI .?AVGraphicMenuItem@@ (vtable 0x7EA690), ...AnimItem@@
//   (0x7EA658), ...ImageItem@@ (0x7EA674), ...ShortcutItem@@ (0x7EA6AC), each deriving GraphicMenuItem at
//   offset 0; the base constructor 0x4F3A50 (the +0x04/+0x08/+0x09/+0x0C stores); the bodies in
//   menus_graphic_menu.cpp (every other offset); allocation sites `PUSH 0x28; CALL 0x7C8E17` at 0x4F2EB4
//   (AnimItem) and 0x4F3C0A (ShortcutItem), `PUSH 0x38; CALL 0x7C8E17` at 0x4F33E1 (ImageItem).
//
//   Address-scoped views: the class names are the true names. The helper types are named for what the
//   bodies do with them, not recovered names. The base GraphicMenuItem has no allocation site in
//   this cluster, so its size is modelled (0x10 up to the first derived member).
#ifndef GG_MATCH_UI_INPUT_CONTROLS_MENUS_GRAPHIC_MENU_H
#define GG_MATCH_UI_INPUT_CONTROLS_MENUS_GRAPHIC_MENU_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "ui_common.h"
#include "../../core/vector_class.h"

// Point2D and Rect (ui_common.h) are the module-wide point and rectangle views.

// An owned helper object. Its destructor is the out-of-line thunk at 0x5D0580 (a jump to the
// pointer-release body at 0x7B46F0) and 0x5D0590 is a no-argument empty method; both are declared only.
struct MenusItemPart
{
    ~MenusItemPart();
    void Func_5D0590();
};

// An embedded text holder; its destructor is the body at 0x7B46F0 (called directly, not through the
// thunk), and it is the argument of the file-name constructor 0x473A30 and the sprite constructor 0x5CCC30.
struct MenusString
{
    ~MenusString();
    void* Block;  // +0x00
};
GG_STATIC_ASSERT(sizeof(MenusString) == 0x04);

// An object with a virtual destructor in slot 0 and a one-flag setter in slot 1 (`CALL [vptr+4]`).
struct MenusFlagSink
{
    virtual ~MenusFlagSink();
    virtual void vf_1(bool on);
};

// The sprite the image item places and redraws: 0x5D26C0 takes the item rectangle, 0x5D1E50 refreshes.
struct MenusSprite
{
    void Func_5D26C0(::Rect* rect);
    void Func_5D1E50();
};

// The 0x30-byte object built by 0x5CCC30 and handed to the host (0x5D1DF0).
struct MenusSurfaceSprite
{
    MenusSurfaceSprite(MenusString* name, void* surface, int* anchor, int flag);
    char _pad000[0x30];
};

// The host the image item registers its sprite with (slot 3 argument).
struct MenusItemHost
{
    char _pad000[0x18];
    int  Anchor;  // +0x18
    void Func_5D1DF0(MenusSurfaceSprite* sprite, int id);
};
GG_STATIC_ASSERT(offsetof(MenusItemHost, Anchor) == 0x18);

// The stack file object of slot 3 (0x6C bytes): constructed from a name by 0x473A30, probed through
// its virtual slot 5 (`CALL [vptr+0x14]`), and torn down by the inline destructor chain
// (vtable 0x7E16B0 at +0, +0x64 reset, 0x43AE50 on the buffer at +0x58, vtable 0x7E1668, 0x431B80).
struct MenusBuffer
{
    void Clear();
    void* Buffer;     // +0x00
    int   Size;       // +0x04
    bool  Allocated;  // +0x08
    char  _pad009[3];
};
GG_STATIC_ASSERT(sizeof(MenusBuffer) == 0x0C);

class MenusBufferIOFile
{
public:
    virtual ~MenusBufferIOFile();  // 0x431B80 (read-only dependency)
    char _pad004[0x58 - 4];
};

class MenusCDFile : public MenusBufferIOFile
{
public:
    virtual ~MenusCDFile() {}
};

class MenusCCFile : public MenusCDFile
{
public:
    MenusCCFile(const MenusString* name);  // 0x473A30
    virtual ~MenusCCFile()
    {
        Position = 0;
        Buffer.Clear();
    }
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual bool Exists(int forced);  // slot 5, +0x14
    MenusBuffer Buffer;  // +0x58
    int Position;        // +0x64
    int Availability;    // +0x68
};
GG_STATIC_ASSERT(sizeof(MenusCCFile) == 0x6C);

// GLOBAL: GAMEMD 0x887310 -- the screen surface.
extern void* MenusScreenSurface;

// VTABLE: GAMEMD 0x7EA690
class GraphicMenuItem
{
public:
    // FUNCTION: GAMEMD 0x4F3A50
    GraphicMenuItem(int id);
    virtual ~GraphicMenuItem();                       // 0x4F3A70 body, 0x4F3B20 scalar deleting
    virtual bool Slot1(unsigned key);                    // 0x4F3B00 (shared by Anim and Image)
    virtual bool Slot2(const Point2D* point);      // 0x4F3AF0 (base and Shortcut)
    virtual void Slot3(MenusItemHost* host);          // 0x4F3B10 (base, Anim, Shortcut)
    virtual void Slot4(bool value);                   // 0x4F3AD0
    virtual void Slot5(bool value);                   // 0x4F3AE0

    int            Id;         // +0x04
    bool           Flag08;     // +0x08
    bool           Visible;    // +0x09
    char           _pad00A[2];
    MenusItemPart* Part;       // +0x0C
};
GG_STATIC_ASSERT(offsetof(GraphicMenuItem, Id) == 0x04);
GG_STATIC_ASSERT(offsetof(GraphicMenuItem, Flag08) == 0x08);
GG_STATIC_ASSERT(offsetof(GraphicMenuItem, Visible) == 0x09);
GG_STATIC_ASSERT(offsetof(GraphicMenuItem, Part) == 0x0C);

// VTABLE: GAMEMD 0x7EA658
class GraphicMenuAnimItem : public GraphicMenuItem
{
public:
    virtual ~GraphicMenuAnimItem();                   // 0x4F3070 body, 0x4F30E0 scalar deleting
    virtual bool Slot2(const Point2D* point);      // 0x4F3090

    ::Rect        Rect;       // +0x10
    int            Unknown20;  // +0x20
    MenusFlagSink* Anim;       // +0x24
};
GG_STATIC_ASSERT(offsetof(GraphicMenuAnimItem, Rect) == 0x10);
GG_STATIC_ASSERT(offsetof(GraphicMenuAnimItem, Anim) == 0x24);
GG_STATIC_ASSERT(sizeof(GraphicMenuAnimItem) == 0x28);

// VTABLE: GAMEMD 0x7EA674
class GraphicMenuImageItem : public GraphicMenuItem
{
public:
    virtual ~GraphicMenuImageItem();                  // 0x4F3600 body, 0x4F3840 scalar deleting
    virtual bool Slot2(const Point2D* point);      // 0x4F3640
    virtual void Slot3(MenusItemHost* host);          // 0x4F37A0
    virtual void Slot4(bool value);                   // 0x4F3690
    virtual void Slot5(bool value);                   // 0x4F3720

    MenusSprite*   Sprite;     // +0x10
    ::Rect        Rect;       // +0x14
    MenusFlagSink* Sink24;     // +0x24
    MenusFlagSink* Sink28;     // +0x28
    MenusFlagSink* Sink2C;     // +0x2C
    MenusItemPart* Part30;     // +0x30
    MenusString    Name;       // +0x34
};
GG_STATIC_ASSERT(offsetof(GraphicMenuImageItem, Sprite) == 0x10);
GG_STATIC_ASSERT(offsetof(GraphicMenuImageItem, Rect) == 0x14);
GG_STATIC_ASSERT(offsetof(GraphicMenuImageItem, Sink24) == 0x24);
GG_STATIC_ASSERT(offsetof(GraphicMenuImageItem, Sink28) == 0x28);
GG_STATIC_ASSERT(offsetof(GraphicMenuImageItem, Sink2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(GraphicMenuImageItem, Part30) == 0x30);
GG_STATIC_ASSERT(offsetof(GraphicMenuImageItem, Name) == 0x34);
GG_STATIC_ASSERT(sizeof(GraphicMenuImageItem) == 0x38);

// The iterator over the shortcut vector (vtable 0x7EA6C8: deleting destructor 0x4F3FD0, then
// IsValid 0x4F3FC0 (index < vector Count), Next 0x4F3FF0, Prev 0x4F4000).
// VTABLE: GAMEMD 0x7EA6C8
class MenusKeyIterator
{
public:
    MenusKeyIterator(DynamicVectorClass<unsigned>* vec) : Vec(vec), Index(0) {}
    virtual ~MenusKeyIterator() {}  // 0x4F3FD0 (scalar deleting destructor)
    virtual bool IsValid();        // 0x4F3FC0
    virtual void Next();           // 0x4F3FF0
    virtual void Prev();           // 0x4F4000
    unsigned Current() { return Vec->Items[Index]; }

    DynamicVectorClass<unsigned>* Vec;  // +0x04
    int Index;                          // +0x08
};

// VTABLE: GAMEMD 0x7EA6AC
class GraphicMenuShortcutItem : public GraphicMenuItem
{
public:
    virtual ~GraphicMenuShortcutItem();               // 0x4F3E90 body, 0x4F3F60 scalar deleting
    virtual bool Slot1(unsigned key);                    // 0x4F3EE0

    DynamicVectorClass<unsigned> Keys;  // +0x10
};
GG_STATIC_ASSERT(offsetof(GraphicMenuShortcutItem, Keys) == 0x10);
GG_STATIC_ASSERT(sizeof(GraphicMenuShortcutItem) == 0x28);

#endif  // GG_MATCH_UI_INPUT_CONTROLS_MENUS_GRAPHIC_MENU_H
