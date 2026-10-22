// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Globals and call shapes read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x53E6B0: the guard at 0xAA0448, the
//   critical section pushed as 0xAA0418 to IAT 0x7E11E8 / 0x7E11EC, the four
//   tests at 0xAA0468 / 0xAA045C / 0xAA0444 / 0xAA0464, the ECX-only call to
//   0x409320, the ECX/EDX + two-stack-argument call to 0x409030, and the cdecl
//   call to 0x7CB19C (`ADD ESP,4`). YRpp names 0x53E6B0 (StreamerThreadFlush)
//   and 0x7CB19C (CRT fflush) - name-only cross-check.
#ifndef GG_MATCH_AUDIO_STREAMER_THREAD_FLUSH_METHODS_H
#define GG_MATCH_AUDIO_STREAMER_THREAD_FLUSH_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct CriticalSection_0053E6B0 { char Opaque[0x18]; };
GG_STATIC_ASSERT(sizeof(CriticalSection_0053E6B0) == 0x18);

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(CriticalSection_0053E6B0*);  // IAT 0x7E11E8
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CriticalSection_0053E6B0*);  // IAT 0x7E11EC

// GLOBAL: GAMEMD 0xAA0418 — the streamer's critical section.
extern CriticalSection_0053E6B0 DAT_00AA0418;
// GLOBAL: GAMEMD 0xAA0444 — streamer state; 1 is the flushable state.
extern int   DAT_00AA0444;
// GLOBAL: GAMEMD 0xAA0448 — streamer running.
extern int   DAT_00AA0448;
// GLOBAL: GAMEMD 0xAA045C
extern int   DAT_00AA045C;
// GLOBAL: GAMEMD 0xAA0464 — the ring buffer being drained.
extern void* DAT_00AA0464;
// GLOBAL: GAMEMD 0xAA0468 — the CRT stream it drains into.
extern void* DAT_00AA0468;

// FUNCTION: GAMEMD 0x409320 (decl; reloc) — bytes pending in the ring
// (`[ECX+0x34] - [ECX+0x38]`).
int  FUN_00409320(void* ring);
// FUNCTION: GAMEMD 0x409030 (decl; reloc) — drain `count` bytes of the ring
// into the stream.
int  FUN_00409030(void* ring, void* stream, unsigned count, void* unused);
// LIBRARY: GAMEMD 0x7CB19C (decl; reloc) — CRT fflush.
int  __cdecl   FUN_007CB19C(void* stream);

// FUNCTION: GAMEMD 0x53E6B0 — YRpp: Unsorted::StreamerThreadFlush.
void __cdecl FUN_0053E6B0();

#endif  // GG_MATCH_AUDIO_STREAMER_THREAD_FLUSH_METHODS_H
