// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// Shared prefix of the entries retrieved from the vector at 0xA8B8C8.
// 0x69ACD0 copies 44 UTF-16 units at +0; 0x69AD20 copies 0x104 bytes
// at +0x58; 0x69AD80 copies 0x20 bytes at +0x15C. Each terminates
// the last element. This prefix does not describe the later member lifetimes.
#ifndef GG_MATCH_NETWORK_SESSION_ENTRY_H
#define GG_MATCH_NETWORK_SESSION_ENTRY_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
class Obj_007B4620;
struct Entry_00A8B8C8
{
    wchar_t unknown_000[0x2C];
    char unknown_058[0x104];
    char unknown_15C[0x20];
    bool unknown_17C;
    // Declaration at 0x69ACD0
    void FUN_0069ACD0(const wchar_t* source);
    // Declaration at 0x69AD20
    void FUN_0069AD20(const char* source);
    // Declaration at 0x69AD80
    void FUN_0069AD80(const char* source);
    // Declaration at 0x69ADF0
    bool FUN_0069ADF0();
    // Declaration at 0x69AE10 (declaration)
    bool FUN_0069AE10(Obj_007B4620* mode);
};
GG_STATIC_ASSERT(offsetof(Entry_00A8B8C8, unknown_000) == 0);
GG_STATIC_ASSERT(sizeof(((Entry_00A8B8C8*)0)->unknown_000) == 0x58);
GG_STATIC_ASSERT(offsetof(Entry_00A8B8C8, unknown_058) == 0x58);
GG_STATIC_ASSERT(sizeof(((Entry_00A8B8C8*)0)->unknown_058) == 0x104);
GG_STATIC_ASSERT(offsetof(Entry_00A8B8C8, unknown_15C) == 0x15C);
GG_STATIC_ASSERT(sizeof(((Entry_00A8B8C8*)0)->unknown_15C) == 0x20);
GG_STATIC_ASSERT(offsetof(Entry_00A8B8C8, unknown_17C) == 0x17C);
GG_STATIC_ASSERT(sizeof(((Entry_00A8B8C8*)0)->unknown_17C) == 1);
#endif
