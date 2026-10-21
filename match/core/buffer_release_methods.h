// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every offset below was extracted individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI, one disassembly per entry
//   point in the original 53-entry family: buffer at +0x04, length at +0x08, ownership flag
//   at +0x0D, and on 25 of them an extra word at +0x10 cleared up front. None
//   of these addresses is bound by YRpp or the seed map.
//
// The buffer-release template. Free the buffer only if this object owns it,
// then reset the holder either way — note the flag and length are cleared even
// when the buffer was borrowed or already null, so the clear is unconditional
// and only the free is guarded.
//
// These are 53 separate entry points on what are presumably as many classes;
// they are modelled against one shared layout because the extraction proved the
// layout identical, not because they are assumed to be one type. Each is
// written out as its own function and verified against its own address.
//
// Reviewed against docs/matching_methodology_and_toolchain.md batch
// forty-one (the free-`__fastcall`-with-a-receiver debt) and deliberately
// LEFT as free functions: `obj` has a receiver and no further argument, so
// converting to a `__thiscall` member would be free in bytes, but
// `BufferHolder` is not one recovered class — it is 53 different, presumably
// unrelated, enclosing classes that happen to share this embedded layout
// (Buffer at +0x04 rather than +0x00 means each sits inside a larger class we
// have not identified). Naming a `BufferHolder::Release()` member would
// assert that all 53 retail call sites share one class identity, which the
// evidence does not establish; that would be inventing a class to satisfy the
// rule, which batch forty-one explicitly rules out. The receiver's true
// per-address class remains undetermined.
#ifndef GG_MATCH_CORE_BUFFER_RELEASE_METHODS_H
#define GG_MATCH_CORE_BUFFER_RELEASE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void __cdecl FUN_007C8B3D(void* block);

struct BufferHolder
{
    char          _pad00[0x4];
    void*         Buffer;        // +0x0004
    int           Length;        // +0x0008
    char          _pad0C[0x1];
    unsigned char IsAllocated;   // +0x000D
    char          _pad0E[0x2];
    int           unknown_10;    // +0x0010
};
GG_STATIC_ASSERT(offsetof(BufferHolder, Buffer) == 0x04);
GG_STATIC_ASSERT(offsetof(BufferHolder, Length) == 0x08);
GG_STATIC_ASSERT(offsetof(BufferHolder, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(BufferHolder, unknown_10) == 0x10);

void __fastcall FUN_0040B270(BufferHolder* obj);   // FUNCTION: GAMEMD 0x40B270
void __fastcall FUN_0040B640(BufferHolder* obj);   // FUNCTION: GAMEMD 0x40B640
void __fastcall FUN_0040B7F0(BufferHolder* obj);   // FUNCTION: GAMEMD 0x40B7F0
void __fastcall FUN_0040BE50(BufferHolder* obj);   // FUNCTION: GAMEMD 0x40BE50
void __fastcall FUN_0040BFA0(BufferHolder* obj);   // FUNCTION: GAMEMD 0x40BFA0
void __fastcall FUN_0040C230(BufferHolder* obj);   // FUNCTION: GAMEMD 0x40C230
void __fastcall FUN_0040C380(BufferHolder* obj);   // FUNCTION: GAMEMD 0x40C380
void __fastcall FUN_0040C820(BufferHolder* obj);   // FUNCTION: GAMEMD 0x40C820
void __fastcall FUN_0040C970(BufferHolder* obj);   // FUNCTION: GAMEMD 0x40C970
void __fastcall FUN_0040CC70(BufferHolder* obj);   // FUNCTION: GAMEMD 0x40CC70
void __fastcall FUN_0040CDC0(BufferHolder* obj);   // FUNCTION: GAMEMD 0x40CDC0
void __fastcall FUN_0040D540(BufferHolder* obj);   // FUNCTION: GAMEMD 0x40D540
void __fastcall FUN_0040D690(BufferHolder* obj);   // FUNCTION: GAMEMD 0x40D690
void __fastcall FUN_0040E7F0(BufferHolder* obj);   // FUNCTION: GAMEMD 0x40E7F0
void __fastcall FUN_0040E940(BufferHolder* obj);   // FUNCTION: GAMEMD 0x40E940
void __fastcall FUN_0040EEC0(BufferHolder* obj);   // FUNCTION: GAMEMD 0x40EEC0
void __fastcall FUN_0040F010(BufferHolder* obj);   // FUNCTION: GAMEMD 0x40F010
void __fastcall FUN_0040FBB0(BufferHolder* obj);   // FUNCTION: GAMEMD 0x40FBB0
void __fastcall FUN_0040FD00(BufferHolder* obj);   // FUNCTION: GAMEMD 0x40FD00
void __fastcall FUN_0041DDE0(BufferHolder* obj);   // FUNCTION: GAMEMD 0x41DDE0
void __fastcall FUN_0041DF30(BufferHolder* obj);   // FUNCTION: GAMEMD 0x41DF30
void __fastcall FUN_00420370(BufferHolder* obj);   // FUNCTION: GAMEMD 0x420370
void __fastcall FUN_004204C0(BufferHolder* obj);   // FUNCTION: GAMEMD 0x4204C0
void __fastcall FUN_00421800(BufferHolder* obj);   // FUNCTION: GAMEMD 0x421800
void __fastcall FUN_00421950(BufferHolder* obj);   // FUNCTION: GAMEMD 0x421950
void __fastcall FUN_0042D540(BufferHolder* obj);   // FUNCTION: GAMEMD 0x42D540
void __fastcall FUN_0042D5A0(BufferHolder* obj);   // FUNCTION: GAMEMD 0x42D5A0
void __fastcall FUN_0042D6F0(BufferHolder* obj);   // FUNCTION: GAMEMD 0x42D6F0
void __fastcall FUN_0042D9A0(BufferHolder* obj);   // FUNCTION: GAMEMD 0x42D9A0
void __fastcall FUN_0042F3A0(BufferHolder* obj);   // FUNCTION: GAMEMD 0x42F3A0
void __fastcall FUN_0042F420(BufferHolder* obj);   // FUNCTION: GAMEMD 0x42F420
void __fastcall FUN_0042F7C0(BufferHolder* obj);   // FUNCTION: GAMEMD 0x42F7C0
void __fastcall FUN_0042FAB0(BufferHolder* obj);   // FUNCTION: GAMEMD 0x42FAB0
void __fastcall FUN_0043AC20(BufferHolder* obj);   // FUNCTION: GAMEMD 0x43AC20
void __fastcall FUN_0045A0D0(BufferHolder* obj);   // FUNCTION: GAMEMD 0x45A0D0
void __fastcall FUN_0045A850(BufferHolder* obj);   // FUNCTION: GAMEMD 0x45A850
void __fastcall FUN_00465F50(BufferHolder* obj);   // FUNCTION: GAMEMD 0x465F50
void __fastcall FUN_00472A80(BufferHolder* obj);   // FUNCTION: GAMEMD 0x472A80
void __fastcall FUN_00472AE0(BufferHolder* obj);   // FUNCTION: GAMEMD 0x472AE0
void __fastcall FUN_00472C30(BufferHolder* obj);   // FUNCTION: GAMEMD 0x472C30
void __fastcall FUN_00472E90(BufferHolder* obj);   // FUNCTION: GAMEMD 0x472E90

#endif  // GG_MATCH_CORE_BUFFER_RELEASE_METHODS_H
