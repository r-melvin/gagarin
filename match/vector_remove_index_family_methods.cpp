// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001. These 16 functions have
//   byte-identical retail bodies: the element type is four bytes wide and the
//   body names no vtable, so every instantiation compiled to the same 49
//   bytes. The body is written once and repeated verbatim under each address,
//   now as the RemoveItem member of its own addr-scoped type (see the header
//   for why one struct per address, not one shared class).

#include "vector_remove_index_family_methods.h"

// Remove the element at `index` by shifting the tail down one slot. The count
// is decremented first, so the shift runs while the index is still below the
// new count. Recovered as DynamicVectorClass<T>::RemoveItem (name
// cross-checked against YRpp).
#define GG_REMOVE_VECTOR_BODY(addr)                                          \
    bool RemoveVector_##addr::RemoveItem(int index)                         \
    {                                                                       \
        if (index < Count) {                                                \
            Count = Count - 1;                                              \
            for (int i = index; i < Count; i++) {                           \
                Items[i] = Items[i + 1];                                    \
            }                                                               \
            return true;                                                    \
        }                                                                    \
        return false;                                                        \
    }

// FUNCTION: GAMEMD 0x004E0ED0
GG_REMOVE_VECTOR_BODY(004E0ED0)

// FUNCTION: GAMEMD 0x00510820
GG_REMOVE_VECTOR_BODY(00510820)

// FUNCTION: GAMEMD 0x0053DDA0
GG_REMOVE_VECTOR_BODY(0053DDA0)

// FUNCTION: GAMEMD 0x005AD790
GG_REMOVE_VECTOR_BODY(005AD790)

// FUNCTION: GAMEMD 0x005E23D0
GG_REMOVE_VECTOR_BODY(005E23D0)

// FUNCTION: GAMEMD 0x0063E590
GG_REMOVE_VECTOR_BODY(0063E590)

// FUNCTION: GAMEMD 0x0063EF70
GG_REMOVE_VECTOR_BODY(0063EF70)

// FUNCTION: GAMEMD 0x0063F000
GG_REMOVE_VECTOR_BODY(0063F000)

// FUNCTION: GAMEMD 0x0063F040
GG_REMOVE_VECTOR_BODY(0063F040)

// FUNCTION: GAMEMD 0x00652560
GG_REMOVE_VECTOR_BODY(00652560)

// FUNCTION: GAMEMD 0x00660F10
GG_REMOVE_VECTOR_BODY(00660F10)

// FUNCTION: GAMEMD 0x0067C360
GG_REMOVE_VECTOR_BODY(0067C360)

// FUNCTION: GAMEMD 0x0067C3F0
GG_REMOVE_VECTOR_BODY(0067C3F0)

// FUNCTION: GAMEMD 0x006CE320
GG_REMOVE_VECTOR_BODY(006CE320)

// FUNCTION: GAMEMD 0x00717DB0
GG_REMOVE_VECTOR_BODY(00717DB0)

// FUNCTION: GAMEMD 0x0074F6F0
GG_REMOVE_VECTOR_BODY(0074F6F0)

