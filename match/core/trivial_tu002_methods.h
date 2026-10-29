// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU002_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU002_METHODS_H

#include <stddef.h>
#include "triple_timer_init_methods.h"
#include "../_rt/gg_static_assert.h"
#include "intrusive_list_methods.h"
#include "tail_call_methods.h"
#include "../audio/audio_sample_methods.h"

struct Gbl_0087E8A8;
struct Obj_00407060;
struct Obj_00407090;
struct Obj_00407F80;
struct Obj_004080A0;
struct Obj_00408EB0;
struct Obj_00408EC0;
struct Obj_00408ED0;
struct Obj_004090F0;
struct Obj_00409330;

// GLOBAL: GAMEMD 0x87E728
extern void* DAT_0087E728;
// GLOBAL: GAMEMD 0x87E8A8
extern Gbl_0087E8A8 DAT_0087E8A8;

// FUNCTION: GAMEMD 0x4033C0 (declaration)
void FUN_004033C0(void*, int);
// FUNCTION: GAMEMD 0x407170 (declaration)

#include "gbl_0087e8a8.h"

struct Obj_00407060
{
    unsigned unknown_00;
    // FUNCTION: GAMEMD 0x407160
    void FUN_00407160();
    // FUNCTION: GAMEMD 0x407060
    void FUN_00407060();
};

GG_STATIC_ASSERT(offsetof(Obj_00407060, unknown_00) == 0);
GG_STATIC_ASSERT(sizeof(Obj_00407060) == 4);

struct Obj_00407090
{
    char unknown_00[0x4];
    int unknown_04;   // +0x0004
    int unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x407090
    int FUN_00407090() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00407090, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_00407090, unknown_08) == 0x8);

class FileClass;
struct Peer_00405D40;
struct Obj_00408D00;
struct Cursor_00408930;
struct Obj_00407F80
{
    ListNode Links;
    unsigned unknown_0C;
    void* unknown_10;
    Peer_00405D40* unknown_14;
    unsigned __int64 unknown_18;
    __int64 unknown_20;
    __int64 unknown_28;
    Obj_00408D00* unknown_30;
    Cursor_00408930* unknown_34;
    Cursor_00408930* unknown_38;
    Obj_00408500b unknown_3C;
    int unknown_58;
    AudioSampleData unknown_5C;
    FileClass* unknown_7C;
    int unknown_80;
    int unknown_84;
    int unknown_88;
    int unknown_8C;
    int unknown_90;
    unsigned unknown_94;
    int unknown_98;
    int unknown_9C;
    int unknown_A0;
    char unknown_A4[0x54];
    // FUNCTION: GAMEMD 0x407B60
    int __fastcall FUN_00407B60(const char* name, int mode);
    // FUNCTION: GAMEMD 0x407A90
    void FUN_00407A90();
    // FUNCTION: GAMEMD 0x407F80
    int FUN_00407F80();
    // FUNCTION: GAMEMD 0x407F90
    int FUN_00407F90();
};
GG_STATIC_ASSERT(offsetof(Obj_00407F80, Links) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_00407F80, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(Obj_00407F80, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(Obj_00407F80, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_00407F80, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(Obj_00407F80, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(Obj_00407F80, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(Obj_00407F80, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(Obj_00407F80, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(Obj_00407F80, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(Obj_00407F80, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(Obj_00407F80, unknown_5C) == 0x5C);
GG_STATIC_ASSERT(offsetof(Obj_00407F80, unknown_7C) == 0x7C);
GG_STATIC_ASSERT(offsetof(Obj_00407F80, unknown_80) == 0x80);
GG_STATIC_ASSERT(offsetof(Obj_00407F80, unknown_84) == 0x84);
GG_STATIC_ASSERT(offsetof(Obj_00407F80, unknown_88) == 0x88);
GG_STATIC_ASSERT(offsetof(Obj_00407F80, unknown_8C) == 0x8C);
GG_STATIC_ASSERT(offsetof(Obj_00407F80, unknown_90) == 0x90);
GG_STATIC_ASSERT(offsetof(Obj_00407F80, unknown_94) == 0x94);
GG_STATIC_ASSERT(offsetof(Obj_00407F80, unknown_98) == 0x98);
GG_STATIC_ASSERT(offsetof(Obj_00407F80, unknown_9C) == 0x9C);
GG_STATIC_ASSERT(offsetof(Obj_00407F80, unknown_A0) == 0xA0);
GG_STATIC_ASSERT(offsetof(Obj_00407F80, unknown_A4) == 0xA4);
GG_STATIC_ASSERT(sizeof(Obj_00407F80) == 0xF8);

struct Obj_004080A0
{
    char unknown_00[0xA4];
    int unknown_A4;   // +0x00A4
    // FUNCTION: GAMEMD 0x4080A0
    int* FUN_004080A0();
};
GG_STATIC_ASSERT(offsetof(Obj_004080A0, unknown_A4) == 0xA4);

struct Obj_00408EB0
{
    char unknown_00[0x18];
    int unknown_18;   // +0x0018
};
GG_STATIC_ASSERT(offsetof(Obj_00408EB0, unknown_18) == 0x18);

struct Obj_00408EC0
{
    char unknown_00[0x18];
    int unknown_18;   // +0x0018
    // FUNCTION: GAMEMD 0x408EC0
    int FUN_00408EC0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00408EC0, unknown_18) == 0x18);

struct Obj_00408ED0
{
    char unknown_00[0x14];
    int unknown_14;   // +0x0014
    // FUNCTION: GAMEMD 0x408ED0
    int FUN_00408ED0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00408ED0, unknown_14) == 0x14);

struct Obj_004090F0
{
    char unknown_00[0x24];
    int unknown_24;   // +0x0024
    // FUNCTION: GAMEMD 0x4090F0
    int FUN_004090F0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_004090F0, unknown_24) == 0x24);

struct Obj_00409330
{
    char unknown_00[0x30];
    int unknown_30;   // +0x0030
    // FUNCTION: GAMEMD 0x409330
    int FUN_00409330() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00409330, unknown_30) == 0x30);


// FUNCTION: GAMEMD 0x406E60
void FUN_00406E60(int a1, int a2);
// FUNCTION: GAMEMD 0x408EB0
int FUN_00408EB0(Obj_00408EB0* a1, int a2);

#endif  // GG_MATCH_CORE_TRIVIAL_TU002_METHODS_H
