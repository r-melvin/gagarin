// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; retail entries 0x4354D0, 0x435500, 0x435530.
#ifndef GG_BIT_FONT_SINGLETON_METHODS_H
#define GG_BIT_FONT_SINGLETON_METHODS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
// RTTI: vtable 7E3A78, locator 7FBF40, descriptor 818B68 names BitFont.
class BitFontSingletonView {
public:
    virtual ~BitFontSingletonView();
    // FUNCTION: GAMEMD 0x433880
    BitFontSingletonView(const char* name);
    char unknown_04[0x40];
};
GG_STATIC_ASSERT(offsetof(BitFontSingletonView, unknown_04) == 4);
GG_STATIC_ASSERT(sizeof(BitFontSingletonView) == 0x44);
struct BitFontSingletonVtable { void* deletingDestructor; };
GG_STATIC_ASSERT(offsetof(BitFontSingletonVtable, deletingDestructor) == 0);
GG_STATIC_ASSERT(sizeof(BitFontSingletonVtable) == 4);
// VTABLE: GAMEMD 0x7E3A78
// Slot zero: scalar deleting destructor at 0x434A40.
extern BitFontSingletonVtable BitFontSingletonVtableAddress;
// GLOBAL: GAMEMD 0x89C4D0
extern BitFontSingletonView* BitFontSingleton;
// STRING: GAMEMD 0x818B98
extern const char BitFontGameName[];
#endif
