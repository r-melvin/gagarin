// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// A static data member of IndexClass type, as laid out at 0x8B3CC0. Its
// initialiser at 0x4D07F0 zeroes the five prefix fields and registers the
// exit-time destructor stub at 0x4D0820, which tests bit 0 of the guard byte
// 0x8B3CD4, frees the table and zeroes the fields again. The owning class is
// not recoverable, so the member gets a placeholder holder as in
// static_vector_member_dtor_stubs_a.cpp.
#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "_rt/crt_allocator.h"
#include "_layout/index.h"


GG_STATIC_ASSERT(sizeof(IndexClass<int, void*>) == 0x14);

struct StaticIndexHolder_008B3CC0 {
    // GLOBAL: GAMEMD 0x008B3CC0
    static IndexClass<int, void*> DAT_008B3CC0;
};
// SYNTHETIC: GAMEMD 0x004D0820 -- exit-time destructor stub of DAT_008B3CC0, guard byte 0x008B3CD4 bit 0
// SYNTHETIC: GAMEMD 0x004D07F0 -- initialiser of DAT_008B3CC0
IndexClass<int, void*> StaticIndexHolder_008B3CC0::DAT_008B3CC0;
