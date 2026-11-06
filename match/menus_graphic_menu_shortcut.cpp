// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// GraphicMenuShortcutItem entries (layout and evidence: menus_graphic_menu.h).
// LIBRARY: GAMEMD 0x7C8B3D -- operator delete.

#include "menus_graphic_menu.h"
#include "string_class.h"
#include "vector_class_operations.h"

// Defined below (GAMEMD 0x4F3D40).
unsigned FUN_004F3D40(Wstring* spec);

// FUNCTION: GAMEMD 0x4F3C40
GraphicMenuShortcutItem::GraphicMenuShortcutItem(int id, Wstring& keys)
    : GraphicMenuItem(id)
{
    Wstring token;
    int cursor = keys.FUN_007B5F10(0, ",", &token);
    unsigned int length = token.Length();
    while (length > 0) {
        unsigned code = FUN_004F3D40(&token);
        if (code != 0)
            Keys.AddItem(code);
        cursor = keys.FUN_007B5F10(cursor, ",;", &token);
        if (cursor == -1)
            token.FUN_007B5340();
        length = token.Length();
    }
}

// GLOBAL: GAMEMD 0x824320 -- names of the keys that are not a single character, with their key codes.
struct MenusKeyName
{
    const char* Name;
    int Code;
};
extern const MenusKeyName DAT_00824320[2] = { { "backspace", 8 }, { "esc", 27 } };

// FUNCTION: GAMEMD 0x4F3D40
// Parse one key spec ("ctrl-alt-shift-x", case-insensitive) into modifier flags plus
// the key code; 0 when the key part is not recognised.
unsigned FUN_004F3D40(Wstring* spec)
{
    unsigned code = 0;
    Wstring text(*spec);
    text.FUN_007B5B30();
    Wstring prefix(text);
    prefix.FUN_007B5D70(5);
    if (prefix.FUN_007B4710("ctrl-")) {
        code = 0x200;
        text.FUN_007B5020(0, 5);
    }
    prefix = text;
    prefix.FUN_007B5D70(4);
    if (prefix.FUN_007B4710("alt-")) {
        code |= 0x400;
        text.FUN_007B5020(0, 4);
    }
    prefix = text;
    prefix.FUN_007B5D70(6);
    if (prefix.FUN_007B4710("shift-")) {
        code |= 0x100;
        text.FUN_007B5020(0, 6);
    }
    unsigned key = 0;
    switch (text.Length()) {
    case 0:
        break;
    case 1:
        key = text.FUN_007B5410(0) - 0x20;
        break;
    default: {
        int i = 1;
        for (; i >= 0; --i) {
            if (!text.FUN_007B47F0(DAT_00824320[i].Name))
                break;
        }
        if (i >= 0)
            key = DAT_00824320[i].Code;
    }
    }
    if (key != 0)
        code |= key;
    else
        code = 0;
    return code;
}

// The search helper takes the iterator by reference, so its calls stay virtual (as in retail).
static inline bool MenusFindKey(MenusKeyIterator& it, unsigned key)
{
    while (it.IsValid() && it.Current() != key)
        it.Next();
    return it.IsValid();
}

// FUNCTION: GAMEMD 0x4F3EE0
// True when the item is visible and the key is in its key list.
bool GraphicMenuShortcutItem::Slot1(unsigned key)
{
    if (!Visible)
        return false;
    MenusKeyIterator it(&Keys);
    return MenusFindKey(it, key);
}

// FUNCTION: GAMEMD 0x4F3E90
// Destroys the key vector, then runs the base destructor. (The scalar deleting destructor 0x4F3F60 is
// the SYNTHETIC row below: cl emits ??_G beside the constructor 0x4F3C40, whose row is above.)
GraphicMenuShortcutItem::~GraphicMenuShortcutItem()
{
}

// SYNTHETIC: GAMEMD 0x4F3F60 -- GraphicMenuShortcutItem::`scalar deleting destructor' (compiler-generated ??_G beside the out-of-line destructor)
