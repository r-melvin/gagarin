// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x74F730: the vtable store `[EAX]`, the dword stores
//   `[EAX+0x4]`, `[EAX+0x3C]`, `[EAX+0x40]`, the word stores `[EAX+0x8]`,
//   `[EAX+0xA]`, the byte stores `[EAX+0xC]`, `[EAX+0x2A]` and the four-bit
//   clear `AND EDX,0xFFFFFFF0` on `[EAX+0x44]`. Field meaning cross-read from
//   Version_Number at 0x74F760 (masks 1/2/4/8 on +0x44; the 16-byte text read
//   into +0x2A terminated at +0x39). Class and method names cross-checked
//   against YRpp only (nothing copied).
//
// VersionClass — the network-protocol version record. The constructor leaves
// every cached value unset and clears all four "computed" bits so the getters
// recompute on first use. The full method set lives in
// match/network/version_class_methods.{h,cpp}; this TU carries the constructor
// and so the layout it initialises.
#ifndef GG_MATCH_CORE_VERSION_CLASS_CTOR_METHODS_H
#define GG_MATCH_CORE_VERSION_CLASS_CTOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class VersionClass
{
public:
    // VTABLE: GAMEMD 0x7EA57C
    virtual ~VersionClass() {}

    unsigned int   Version;              // +0x0004  cached (major<<16)|minor
    unsigned short MajorVersion;         // +0x0008
    unsigned short MinorVersion;         // +0x000A
    char           VersionName[0x1E];    // +0x000C  "#.#" text, trimmed
    char           VersionText[0x12];    // +0x002A  VERSION.TXT contents (16 + NUL, padded)
    unsigned int   MinClipVer;           // +0x003C
    unsigned int   MaxClipVer;           // +0x0040
    unsigned int   VersionInit : 1;      // +0x0044  bit 0
    unsigned int   MajorInit   : 1;      //          bit 1
    unsigned int   MinorInit   : 1;      //          bit 2
    unsigned int   TextInit    : 1;      //          bit 3

    // FUNCTION: GAMEMD 0x74F730
    VersionClass();
    // Declaration: GAMEMD 0x74FAE0 -- returns this+0xC; RET0.
    char* FUN_0074FAE0();
};
GG_STATIC_ASSERT(offsetof(VersionClass, Version)      == 0x04);
GG_STATIC_ASSERT(offsetof(VersionClass, MajorVersion) == 0x08);
GG_STATIC_ASSERT(offsetof(VersionClass, MinorVersion) == 0x0A);
GG_STATIC_ASSERT(offsetof(VersionClass, VersionName)  == 0x0C);
GG_STATIC_ASSERT(offsetof(VersionClass, VersionText)  == 0x2A);
GG_STATIC_ASSERT(offsetof(VersionClass, MinClipVer)   == 0x3C);
GG_STATIC_ASSERT(offsetof(VersionClass, MaxClipVer)   == 0x40);
GG_STATIC_ASSERT(sizeof(VersionClass)                 == 0x48);

#endif  // GG_MATCH_CORE_VERSION_CLASS_CTOR_METHODS_H
