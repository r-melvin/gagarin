// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; retail gamemd.exe v1.001 0x588DE0..0x589054.
#ifndef GG_BUFFER_ACCESSORS_00588DE0_H
#define GG_BUFFER_ACCESSORS_00588DE0_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
struct BufferPair_00588FB0 {
    int unknown_00;
    int unknown_04;
    BufferPair_00588FB0(const BufferPair_00588FB0& other)
        : unknown_00(other.unknown_00), unknown_04(other.unknown_04) {}
};
GG_STATIC_ASSERT(offsetof(BufferPair_00588FB0, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(BufferPair_00588FB0, unknown_04) == 4);
GG_STATIC_ASSERT(sizeof(BufferPair_00588FB0) == 8);
struct BufferTriple_00589030 {
    int unknown_00;
    int unknown_04;
    unsigned char unknown_08;
    char unknown_09[3];
    BufferTriple_00589030(const BufferTriple_00589030& other)
        : unknown_00(other.unknown_00), unknown_04(other.unknown_04),
          unknown_08(other.unknown_08) {}
};
GG_STATIC_ASSERT(offsetof(BufferTriple_00589030, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(BufferTriple_00589030, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(BufferTriple_00589030, unknown_08) == 8);
GG_STATIC_ASSERT(sizeof(BufferTriple_00589030) == 12);
// Shared prefix view of several buffer instantiations, not their full layout.
struct BufferAccessors_00588DE0 {
    char unknown_00[4];
    unsigned int* Data;
    char unknown_08[4];
    unsigned char Valid;
    char unknown_0D[3];
    unsigned int Index36(const void* item) const;
    unsigned int FUN_00588EF0(int index) const;
    unsigned int Index4(const void* item) const;
    unsigned int FUN_00588F50(int index) const;
    unsigned int Index8(const void* item) const;
    BufferPair_00588FB0 GetPair(int index) const;
    unsigned int Index12(const void* item) const;
    BufferTriple_00589030 GetTriple(int index) const;
};
GG_STATIC_ASSERT(offsetof(BufferAccessors_00588DE0, Data) == 4);
GG_STATIC_ASSERT(offsetof(BufferAccessors_00588DE0, Valid) == 12);
GG_STATIC_ASSERT(sizeof(BufferAccessors_00588DE0) == 16);
#endif
