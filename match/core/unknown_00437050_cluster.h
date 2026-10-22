// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail gamemd.exe v1.001 entry bytes, global references and call targets
// were confirmed by entry-bounded Ghidra disassembly and focused REA records.
#ifndef GG_MATCH_CORE_UNKNOWN_00437050_CLUSTER_H
#define GG_MATCH_CORE_UNKNOWN_00437050_CLUSTER_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "techno_class_opentopped_methods.h"

struct UnknownObject_00437050
{
    // FUNCTION: GAMEMD 0x005F4EC0 (decl; reloc)
    bool FUN_005F4EC0(const void* location, int flag);

    // FUNCTION: GAMEMD 0x00437050
    bool FUN_00437050(const void* location, int flag);
};

// GLOBAL: GAMEMD 0x0089C558
extern "C" unsigned int DAT_0089C558;
// GLOBAL: GAMEMD 0x0089C55C
extern "C" unsigned int DAT_0089C55C;
// GLOBAL: GAMEMD 0x0089C560
extern "C" unsigned int DAT_0089C560;
// GLOBAL: GAMEMD 0x0089C564
extern "C" unsigned int DAT_0089C564;

// Entry 0x4371B0 loads the receiver's vtable from offset 0, then calls its
// byte offset 0x70 (slot 28 (0x1C)). The target returns int.
struct UnknownVtable_004371B0
{
    unsigned char unknown_00[0x70];
    int (*slot_1C)(void* receiver);
};

// This view contains only the prefix read by entry 0x4371B0.
struct UnknownObject_004371B0
{
    UnknownVtable_004371B0* vtable;
};

GG_STATIC_ASSERT(offsetof(UnknownVtable_004371B0, slot_1C) == 0x70);
GG_STATIC_ASSERT(sizeof(UnknownVtable_004371B0) == 0x74);
GG_STATIC_ASSERT(offsetof(UnknownObject_004371B0, vtable) == 0);
GG_STATIC_ASSERT(sizeof(UnknownObject_004371B0) == 4);

// FUNCTION: GAMEMD 0x004370B0
extern "C" int __cdecl FUN_004370B0();

// FUNCTION: GAMEMD 0x00437190
extern "C" void __cdecl FUN_00437190();

// FUNCTION: GAMEMD 0x004371B0
extern "C" int FUN_004371B0(
    UnknownObject_004371B0* object, int factor, int count);

#endif  // GG_MATCH_CORE_UNKNOWN_00437050_CLUSTER_H
