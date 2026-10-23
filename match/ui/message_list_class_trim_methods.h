// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x5D4B20: five stack arguments (`RET 0x14`, no `this`
//   use — YRpp models it as a plain member), CRT wcslen @0x7CA405 on the
//   second, the two scans stepping a word pointer up (`LEA ESI,[EBP+EDI*2-2]`)
//   or down (`LEA EDX,[EBP+ECX*2-2]`) with the `TEST DX,DX` / `CMP DX,0x20;
//   JBE` break, the inlined `REP MOVSD`/`REP MOVSB` copy into the first
//   argument plus the terminating word store, and the out-of-line tail move
//   through 0x7CA090. Method name and argument roles are YRpp's.
#ifndef GG_MATCH_UI_MESSAGE_LIST_CLASS_TRIM_METHODS_H
#define GG_MATCH_UI_MESSAGE_LIST_CLASS_TRIM_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// LIBRARY: GAMEMD 0x7CA405 (decl; reloc) — CRT wcslen.
extern "C" unsigned int __cdecl wcslen(const wchar_t* s);
// CRT memcpy — the /Oi intrinsic here (retail's inlined REP MOVSD/MOVSB).
extern "C" void* __cdecl memcpy(void* destination, const void* source, unsigned int count);
// LIBRARY: GAMEMD 0x7CA090 (decl; reloc) — CRT memmove (the static CRT's
// memcpy/memmove share one body; retail calls it out of line here while the
// fixed-shape copy above it is the /Oi intrinsic).
extern "C" void* __cdecl memmove(void* destination, const void* source, unsigned int count);

// MessageListClass — no member is touched by TrimMessage, so only the method
// is modelled here; the layout lives in match/ui/message_list_class_methods.h.
struct MessageList_005D4B20
{
    // FUNCTION: GAMEMD 0x5D4B20 — MessageListClass::TrimMessage.
    int TrimMessage(wchar_t* dest, wchar_t* src, int minLen, int maxLen, int fromEnd);
};

#endif  // GG_MATCH_UI_MESSAGE_LIST_CLASS_TRIM_METHODS_H
