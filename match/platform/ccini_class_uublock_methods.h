// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x526E80: the buffer straw at `[ESP+0x10]` is built
//   inline (`[+0x04]=0`, `[+0x08]=0`, `[+0x00]=0x7E61F0`, then the 0x43AD00
//   buffer ctor on `[+0x0C]` with (block, length), `[+0x18]=0`,
//   `[+0x00]=0x7E61E0`); the base64 straw at `[ESP+0x2C]` likewise
//   (`[+0x04]`..`[+0x10]` zeroed, `[+0x00]=0x7EB764`) and chained by the
//   slot-1 call `CALL [0x7EB768]` with the buffer straw pushed; 0x42DF90 is
//   its Get(buffer, 0x46) into the 71-byte line at `[ESP+0x48]`; the key is
//   sprintf'd (0x7C8EF4, "%d" at 0x817F6C) into `[ESP+0x90]`; 0x5257C0 is
//   Clear(section, 0) and 0x528660 WriteString(section, key, value).
//   Teardown: 0x6C9850 (straw dtor) on both straws, 0x43AE50 (buffer cleanup)
//   between them. Method name from YRpp (consult-only).
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_UUBLOCK_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_UUBLOCK_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/memory_buffer.h"
#include "../_layout/straw.h"
#include "../_rt/gg_vslot.h"

// CRT sprintf, __cdecl variadic; the caller pops the arguments.
// FUNCTION: GAMEMD 0x7C8EF4 (decl; reloc)
extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);

// STRING: GAMEMD 0x817F6C — "%d".
extern const char STR_00817F6C[];

// VTABLE: GAMEMD 0x7E61F0 — the straw base vtable (installed first).
extern char VT_007E61F0;
// VTABLE: GAMEMD 0x7E61E0 — the buffer straw's vtable.
extern char VT_007E61E0;

// The straw base: vtable plus the two chain links.
struct Straw_00526E80
{
    char* Vtable;            // +0x0000
    int   ChainTo;           // +0x0004
    int   ChainFrom;         // +0x0008

};
GG_STATIC_ASSERT(sizeof(Straw_00526E80) == 0x0C);

// The adopt-or-allocate buffer (ctor 0x43AD00, cleanup 0x43AE50).
struct Buffer_00526E80
{
    const void*   Data;          // +0x0000
    int           Length;        // +0x0004
    unsigned char IsAllocated;   // +0x0008
    unsigned char _pad009[3];    // +0x0009

    // FUNCTION: GAMEMD 0x43AD00 (decl; reloc) — ctor(buffer, size).
    Buffer_00526E80* Construct(const void* buffer, int size);
};
GG_STATIC_ASSERT(offsetof(Buffer_00526E80, IsAllocated) == 0x8);
GG_STATIC_ASSERT(sizeof(Buffer_00526E80) == 0x0C);

// The buffer-backed straw as built on the stack.
struct BufferStraw_00526E80 : Straw_00526E80
{
    Buffer_00526E80 Buffer;      // +0x000C
    int             Index;       // +0x0018
};
GG_STATIC_ASSERT(offsetof(BufferStraw_00526E80, Buffer) == 0x0C);
GG_STATIC_ASSERT(offsetof(BufferStraw_00526E80, Index) == 0x18);
GG_STATIC_ASSERT(sizeof(BufferStraw_00526E80) == 0x1C);

struct Vtbl_007EB764;

// The base64 encoding straw as built on the stack.
struct Base64Straw_00526E80
{
    Vtbl_007EB764* Vtbl;         // +0x0000
    int            ChainTo;      // +0x0004
    int            ChainFrom;    // +0x0008
    int            Control;      // +0x000C  (0 = encode)
    int            Counter;      // +0x0010
    char           CBuffer[4];   // +0x0014
    char           PBuffer[3];   // +0x0018
    char           _pad01B[1];   // +0x001B

    // FUNCTION: GAMEMD 0x42DF90 (decl; reloc) — Get(buffer, length).
    int  Get(void* buffer, int length);
};
GG_STATIC_ASSERT(offsetof(Base64Straw_00526E80, Control) == 0x0C);
GG_STATIC_ASSERT(offsetof(Base64Straw_00526E80, Counter) == 0x10);
GG_STATIC_ASSERT(sizeof(Base64Straw_00526E80) == 0x1C);

typedef void (Base64Straw_00526E80::*Fn004_007EB764)(Straw_00526E80* straw);

// The base64 straw's vtable: slot +0x4 is Get_From(straw).
struct Vtbl_007EB764
{
    char           _pad000[4];   // +0x0000
    Fn004_007EB764 At_004;       // +0x0004
};
GG_STATIC_ASSERT(offsetof(Vtbl_007EB764, At_004) == 0x4);

// VTABLE: GAMEMD 0x7EB764 — the base64 straw's vtable.
extern Vtbl_007EB764 VT_007EB764;

struct CCINI_00526E80
{
    // FUNCTION: GAMEMD 0x5257C0 (decl; reloc) — Clear(section, key).
    bool Clear(const char* section, const char* key);
    // FUNCTION: GAMEMD 0x528660 (decl; reloc) — WriteString(section, key, value).
    bool WriteString(const char* section, const char* key, const char* value);

    // FUNCTION: GAMEMD 0x526E80 — CCINIClass::WriteUUBlock.
    bool WriteUUBlock(const char* section, const void* block, int length);
};

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_UUBLOCK_METHODS_H
