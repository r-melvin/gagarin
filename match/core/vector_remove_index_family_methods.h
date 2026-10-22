// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x4E0ED0 and its 15 duplicates: remove one element of the
//   counted vector template by index. The count lives at +0x10 and the items
//   pointer at +4; the tail is shifted down one slot with a four-byte
//   element, and the count is written back before the shift begins. All
//   sixteen have identical retail bytes, so the family carries no
//   per-instance constant.
//
//   The method name DynamicVectorClass<T>::RemoveItem(int index) is
//   cross-checked against YRpp; the body is reconfirmed against retail below
//   (the bounds check is the `index < Count` test seen in the disassembly).
//
//   That is a real recovered method name, not a placeholder: this family is
//   converted from the free-`__fastcall`-with-a-receiver shortcut (batch
//   forty-one) to genuine
//   `__thiscall` members of the class the receiver actually belongs to.
//
//   Each of the 16 retail addresses is its own template instantiation of the
//   counted-vector template for a distinct (and, from this evidence alone,
//   unidentified) element type, so each gets its own type below rather than
//   being folded into one shared class: the layout is proven identical across
//   all 16 by the extraction, but the classes are not one class, and giving
//   them a single shared name would fabricate an identity the bytes do not
//   establish.
#ifndef GG_MATCH_CORE_VECTOR_REMOVE_INDEX_FAMILY_METHODS_H
#define GG_MATCH_CORE_VECTOR_REMOVE_INDEX_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// One struct per retail address (see the provenance note above for why), all
// sharing the identical proven layout and body.
#define GG_REMOVE_VECTOR_TYPE(addr)                                           \
    struct RemoveVector_##addr                                               \
    {                                                                        \
        char* Vptr;    /* +0x0000 */                                         \
        int*  Items;   /* +0x0004 */                                         \
        char  _pad008[0x10 - 0x08];                                          \
        int   Count;   /* +0x0010 */                                         \
        bool RemoveItem(int index);                                          \
    };                                                                       \
    GG_STATIC_ASSERT(offsetof(RemoveVector_##addr, Items) == 0x4);           \
    GG_STATIC_ASSERT(offsetof(RemoveVector_##addr, Count) == 0x10)

GG_REMOVE_VECTOR_TYPE(004E0ED0);   // FUNCTION: GAMEMD 0x004E0ED0
GG_REMOVE_VECTOR_TYPE(00510820);   // FUNCTION: GAMEMD 0x00510820
GG_REMOVE_VECTOR_TYPE(0053DDA0);   // FUNCTION: GAMEMD 0x0053DDA0
GG_REMOVE_VECTOR_TYPE(005AD790);   // FUNCTION: GAMEMD 0x005AD790
GG_REMOVE_VECTOR_TYPE(005E23D0);   // FUNCTION: GAMEMD 0x005E23D0
GG_REMOVE_VECTOR_TYPE(0063E590);   // FUNCTION: GAMEMD 0x0063E590
GG_REMOVE_VECTOR_TYPE(0063EF70);   // FUNCTION: GAMEMD 0x0063EF70
GG_REMOVE_VECTOR_TYPE(0063F000);   // FUNCTION: GAMEMD 0x0063F000
GG_REMOVE_VECTOR_TYPE(0063F040);   // FUNCTION: GAMEMD 0x0063F040
GG_REMOVE_VECTOR_TYPE(00652560);   // FUNCTION: GAMEMD 0x00652560
GG_REMOVE_VECTOR_TYPE(00660F10);   // FUNCTION: GAMEMD 0x00660F10
GG_REMOVE_VECTOR_TYPE(0067C360);   // FUNCTION: GAMEMD 0x0067C360
GG_REMOVE_VECTOR_TYPE(0067C3F0);   // FUNCTION: GAMEMD 0x0067C3F0
GG_REMOVE_VECTOR_TYPE(006CE320);   // FUNCTION: GAMEMD 0x006CE320
GG_REMOVE_VECTOR_TYPE(00717DB0);   // FUNCTION: GAMEMD 0x00717DB0
GG_REMOVE_VECTOR_TYPE(0074F6F0);   // FUNCTION: GAMEMD 0x0074F6F0

#endif  // GG_MATCH_CORE_VECTOR_REMOVE_INDEX_FAMILY_METHODS_H
