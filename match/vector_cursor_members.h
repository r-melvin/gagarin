// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Slot bodies of VectorCursor (vector_cursor.h): 0x4F3FC0 / 0x4F3FF0 / 0x4F4000 and their siblings in the
//   other instantiations. Only the unit with the explicit instantiations includes it; the code that drives
//   a cursor (e.g. 0x76DED0) sees the declarations and calls the slots through the vtable.
#ifndef GG_MATCH_CORE_VECTOR_CURSOR_MEMBERS_H
#define GG_MATCH_CORE_VECTOR_CURSOR_MEMBERS_H

#include "vector_cursor.h"

template <class T, class Container>
bool VectorCursor<T, Container>::vf_01()
{
    return unknown_08 < CursorLimit(unknown_04);
}

template <class T, class Container>
VectorCursor<T, Container>* VectorCursor<T, Container>::vf_02()
{
    unknown_08++;
    return this;
}

template <class T, class Container>
VectorCursor<T, Container>* VectorCursor<T, Container>::vf_03()
{
    unknown_08--;
    return this;
}

#endif  // GG_MATCH_CORE_VECTOR_CURSOR_MEMBERS_H
