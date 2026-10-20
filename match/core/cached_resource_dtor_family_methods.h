// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, vtable addresses and the global registry address were read
//   numerically off the user's retail gamemd.exe v1.001 with the local Ghidra
//   CLI at 0x49A200 and its 36 neighbours. No YRpp or EA-GPL reference was
//   consulted; the bodies carry no name in the binary, so they keep their
//   FUN_ placeholder names.
//
//   The family: 37 scalar-deleting destructors of 59 bytes each, laid out in
//   two runs (0x49A200..0x49A720 and 0x49AA00..0x49AE40). Masking every 4-byte
//   absolute constant and call displacement makes all 37 byte-identical, so
//   the only per-instance variation is
//     * the derived vtable reseated on entry (37 distinct addresses),
//     * the base vtable the inlined empty base destructor reseats
//       (0x007E5B88 for the first run, 0x007E5BA0 for the second), and
//     * the offset of the owned registry handle (+8, or +0xC for six of them).
//   The registry object (0x0087E8A8), the release entry point (0x00420270)
//   and the CRT free (0x007C8B3D) are the same in all 37.
#ifndef GG_MATCH_CORE_CACHED_RESOURCE_DTOR_FAMILY_METHODS_H
#define GG_MATCH_CORE_CACHED_RESOURCE_DTOR_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x007C8B3D (decl; reloc) — CRT free.
extern "C" void __cdecl gg_free(void* block);

// The refcounted resource registry. Release() drops one reference on the
// handle it is given and, when the last reference goes, unlinks the handle
// from the registry's table and frees it (retail 0x00420270). The retail
// callee ignores its `this`, but the call site is an ordinary member call on
// the global instance, so ECX is loaded with the object's address before the
// handle is pushed.
class ResourceRegistry
{
public:
    void Release(void* handle);
};

// GLOBAL: GAMEMD 0x0087E8A8
extern ResourceRegistry TheResourceRegistry;

// VTABLE: GAMEMD 0x007E5360
extern char VT_007E5360;
// VTABLE: GAMEMD 0x007E5370
extern char VT_007E5370;
// VTABLE: GAMEMD 0x007E5380
extern char VT_007E5380;
// VTABLE: GAMEMD 0x007E5390
extern char VT_007E5390;
// VTABLE: GAMEMD 0x007E53A0
extern char VT_007E53A0;
// VTABLE: GAMEMD 0x007E53B0
extern char VT_007E53B0;
// VTABLE: GAMEMD 0x007E53C0
extern char VT_007E53C0;
// VTABLE: GAMEMD 0x007E53D0
extern char VT_007E53D0;
// VTABLE: GAMEMD 0x007E53E0
extern char VT_007E53E0;
// VTABLE: GAMEMD 0x007E53F0
extern char VT_007E53F0;
// VTABLE: GAMEMD 0x007E5400
extern char VT_007E5400;
// VTABLE: GAMEMD 0x007E5410
extern char VT_007E5410;
// VTABLE: GAMEMD 0x007E5420
extern char VT_007E5420;
// VTABLE: GAMEMD 0x007E5430
extern char VT_007E5430;
// VTABLE: GAMEMD 0x007E5440
extern char VT_007E5440;
// VTABLE: GAMEMD 0x007E5450
extern char VT_007E5450;
// VTABLE: GAMEMD 0x007E5460
extern char VT_007E5460;
// VTABLE: GAMEMD 0x007E5470
extern char VT_007E5470;
// VTABLE: GAMEMD 0x007E55D0
extern char VT_007E55D0;
// VTABLE: GAMEMD 0x007E55E8
extern char VT_007E55E8;
// VTABLE: GAMEMD 0x007E5600
extern char VT_007E5600;
// VTABLE: GAMEMD 0x007E5618
extern char VT_007E5618;
// VTABLE: GAMEMD 0x007E5630
extern char VT_007E5630;
// VTABLE: GAMEMD 0x007E5648
extern char VT_007E5648;
// VTABLE: GAMEMD 0x007E5660
extern char VT_007E5660;
// VTABLE: GAMEMD 0x007E5678
extern char VT_007E5678;
// VTABLE: GAMEMD 0x007E5690
extern char VT_007E5690;
// VTABLE: GAMEMD 0x007E56A8
extern char VT_007E56A8;
// VTABLE: GAMEMD 0x007E56C0
extern char VT_007E56C0;
// VTABLE: GAMEMD 0x007E56D8
extern char VT_007E56D8;
// VTABLE: GAMEMD 0x007E56F0
extern char VT_007E56F0;
// VTABLE: GAMEMD 0x007E5780
extern char VT_007E5780;
// VTABLE: GAMEMD 0x007E5798
extern char VT_007E5798;
// VTABLE: GAMEMD 0x007E57B0
extern char VT_007E57B0;
// VTABLE: GAMEMD 0x007E57C8
extern char VT_007E57C8;
// VTABLE: GAMEMD 0x007E57E0
extern char VT_007E57E0;
// VTABLE: GAMEMD 0x007E57F8
extern char VT_007E57F8;
// VTABLE: GAMEMD 0x007E5B88
extern char VT_007E5B88;
// VTABLE: GAMEMD 0x007E5BA0
extern char VT_007E5BA0;

// A small polymorphic object that owns one registry handle at +8. Its
// scalar-deleting destructor is the whole of its recovered API here.
struct CachedResourceOwner8
{
    void* Vptr;        // +0x00  reseated twice: derived, then base
    void* unknown_04;  // +0x04  untouched by this destructor
    void* Resource;    // +0x08  the owned registry handle

    void* FUN_0049A200(char flags);
    void* FUN_0049A240(char flags);
    void* FUN_0049A2C0(char flags);
    void* FUN_0049A300(char flags);
    void* FUN_0049A340(char flags);
    void* FUN_0049A420(char flags);
    void* FUN_0049A4A0(char flags);
    void* FUN_0049A4E0(char flags);
    void* FUN_0049A520(char flags);
    void* FUN_0049A560(char flags);
    void* FUN_0049A5A0(char flags);
    void* FUN_0049A5E0(char flags);
    void* FUN_0049A620(char flags);
    void* FUN_0049A6A0(char flags);
    void* FUN_0049A6E0(char flags);
    void* FUN_0049A720(char flags);
    void* FUN_0049AA00(char flags);
    void* FUN_0049AA80(char flags);
    void* FUN_0049AAC0(char flags);
    void* FUN_0049AB00(char flags);
    void* FUN_0049AB40(char flags);
    void* FUN_0049ABC0(char flags);
    void* FUN_0049AC00(char flags);
    void* FUN_0049AC40(char flags);
    void* FUN_0049AC80(char flags);
    void* FUN_0049ACC0(char flags);
    void* FUN_0049AD00(char flags);
    void* FUN_0049AD40(char flags);
    void* FUN_0049ADC0(char flags);
    void* FUN_0049AE00(char flags);
    void* FUN_0049AE40(char flags);
};

// The same object with one more 4-byte member ahead of the handle, which
// therefore sits at +0xC.
struct CachedResourceOwnerC
{
    void* Vptr;        // +0x00
    void* unknown_04;  // +0x04
    void* unknown_08;  // +0x08
    void* Resource;    // +0x0C  the owned registry handle

    void* FUN_0049A280(char flags);
    void* FUN_0049A460(char flags);
    void* FUN_0049A660(char flags);
    void* FUN_0049AA40(char flags);
    void* FUN_0049AB80(char flags);
    void* FUN_0049AD80(char flags);
};

GG_STATIC_ASSERT(offsetof(CachedResourceOwner8, Vptr) == 0x00);
GG_STATIC_ASSERT(offsetof(CachedResourceOwner8, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(CachedResourceOwner8, Resource) == 0x08);
GG_STATIC_ASSERT(sizeof(CachedResourceOwner8) == 0x0C);
GG_STATIC_ASSERT(offsetof(CachedResourceOwnerC, Vptr) == 0x00);
GG_STATIC_ASSERT(offsetof(CachedResourceOwnerC, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(CachedResourceOwnerC, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(CachedResourceOwnerC, Resource) == 0x0C);
GG_STATIC_ASSERT(sizeof(CachedResourceOwnerC) == 0x10);

#endif
