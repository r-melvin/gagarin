// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/convention derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (disasm at 0x6E3EE0 and 0x6E45E0), cross-checked against
//   YRpp TActionClass.h (consult-only; reconfirmed numerically here).
//
// TActionClass — trigger-action logic. The two methods matched here touch NO
// instance members of TActionClass:
//   * GetFlags(actionKind)        — a pure switch over the action id; the single
//     int argument arrives in ECX and the function ends in a plain `ret`, i.e.
//     it is __fastcall (NOT the stack-based __stdcall the YRpp wrapper implies).
//   * FindHouseByIndex(ptr,index) — a free __stdcall(2 args, `ret 8`) helper
//     that dispatches an opaque pointer / house index to four external callees.
// No class layout is required; nothing here dereferences `this`.
#ifndef GG_MATCH_AI_TACTION_CLASS_METHODS_H
#define GG_MATCH_AI_TACTION_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct TActionClass
{
    // GAMEMD 0x6E3EE0 — returns a flag bitfield for a given action id.
    // The retail single-arg form is register-passed (ECX) with a plain ret:
    // model it as __fastcall so cl emits the `add ecx,-0xe` / jump-table form.
    static int __fastcall GetFlags(int actionKind);

    // GAMEMD 0x6E45E0 — resolve a house from (opaque source ptr, house index).
    // Free helper: two stack args, callee-cleaned 8 bytes (__stdcall).
    static int __stdcall FindHouseByIndex(void* pSource, int index);
};

#endif // GG_MATCH_AI_TACTION_CLASS_METHODS_H
