// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes read off the user's retail gamemd.exe v1.001 via the local Ghidra
//   CLI at 0x6E3B60: a __fastcall static taking the action kind in ECX,
//   lowered to one byte-indexed jump table over kinds 1..0x90 with 34 result
//   blocks and a zero default. YRpp names
//   TActionClass::GetMode.
#ifndef GG_MATCH_AI_TACTION_CLASS_MODE_METHODS_H
#define GG_MATCH_AI_TACTION_CLASS_MODE_METHODS_H

// The owning class. Nothing at this address touches a TActionClass instance,
// so no layout is recovered here; the struct exists so the routine is spelled
// as the static member it is rather than as a free function, and so the next
// TAction address to be matched has a class to attach to.
struct TActionClass_006E3B60
{
    // FUNCTION: GAMEMD 0x6E3B60 — TActionClass::GetMode (static __fastcall:
    // the action kind arrives in ECX).
    static int __fastcall GetMode(int kind);
};

#endif  // GG_MATCH_AI_TACTION_CLASS_MODE_METHODS_H
