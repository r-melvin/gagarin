// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// GraphicMenuShortcutItem entries (layout and evidence: menus_graphic_menu.h).
// LIBRARY: GAMEMD 0x7C8B3D -- operator delete.

#include "menus_graphic_menu.h"

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

// SYNTHETIC: GAMEMD 0x4F3F60
// GraphicMenuShortcutItem::scalar deleting destructor (compiler-generated ??_G; scored from the harness, see menus.rows.tsv)
