// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, globals and string addresses read numerically off the user's
//   retail gamemd.exe v1.001 via the local Ghidra CLI at 0x422B20 and
//   0x428DE0. The two string literals are read out of the image: 0x817474 is
//   "<none>" and 0x818688 is "Freeing loaded image for".
#ifndef GG_MATCH_CORE_SMALL_MISC49_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC49_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" int  __cdecl FUN_007C8D20(const char* a, const char* b);
extern "C" void __cdecl FUN_007C8B3D(void* block);

// ---------------------------------------------------------------------------
// 0x422B20 — index of the entry whose id matches, or -1.
//
// A null name and the reserved id "<none>" both answer -1 before the scan
// starts, and so does running off the end. The id lives at +0x24 of each entry.
// The count is re-read on every pass, so it is the loop condition rather than a
// value captured up front.
// ---------------------------------------------------------------------------
// STRING: GAMEMD 0x817474 "<none>"
extern const char STR_00817474[];

// GLOBAL: GAMEMD 0x8B4154 — the entry array; 0x8B4160 is its count.
extern char** DAT_008B4154;
extern int    DAT_008B4160;

// FUNCTION: GAMEMD 0x422B20
int FUN_00422B20(const char* name);

// ---------------------------------------------------------------------------
// 0x428DE0 — release the loaded image, once all three preconditions hold.
//
// The two calls share one `ADD ESP,0xC`: VC6 folds the cleanup for the logger's
// two arguments and the free's one into a single adjustment because the calls
// are adjacent.
// ---------------------------------------------------------------------------
// STRING: GAMEMD 0x818688 "Freeing loaded image for"
extern const char STR_00818688[];

// FUNCTION: GAMEMD 0x4068E0 — the logger, __cdecl and variadic in effect.
void __cdecl FUN_004068E0(const char* message, const char* subject);

struct Obj_00428DE0
{
    char  _pad000[0x64];
    char  Name[0xA4 - 0x64];   // +0x0064
    void* Image;               // +0x00A4
    char  ImageValid;          // +0x00A8
    char  _pad0A9[0x35E - 0xA9];
    char  Enabled;             // +0x035E
    char  Loaded;              // +0x035F
};
GG_STATIC_ASSERT(offsetof(Obj_00428DE0, Image) == 0xA4);
GG_STATIC_ASSERT(offsetof(Obj_00428DE0, ImageValid) == 0xA8);
GG_STATIC_ASSERT(offsetof(Obj_00428DE0, Enabled) == 0x35E);
GG_STATIC_ASSERT(offsetof(Obj_00428DE0, Loaded) == 0x35F);

// FUNCTION: GAMEMD 0x428DE0
void FUN_00428DE0(Obj_00428DE0* self);

// ---------------------------------------------------------------------------
#endif  // GG_MATCH_CORE_SMALL_MISC49_METHODS_H
