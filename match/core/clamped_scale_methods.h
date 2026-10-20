// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, the clamp bound and both shifts read numerically off the user's
//   retail gamemd.exe v1.001 via the local Ghidra CLI at 0x4061D0.
//
// Clamp a level to 0..0x4000, scale it by the rate held at +0x24, and hand it
// to one of two setters depending on the mode at +0x1C.
//
// The clamp is written twice in retail, once per branch, and each copy compares
// *unsigned* (`CMP EDX,0x4000; JBE`) before testing the sign. With the value
// unsigned the second test can never fire - anything negative is already above
// the bound - so the `XOR EAX,EAX` arm is dead in both copies. It is reproduced
// as written rather than tidied away.
//
// The scale is `(rate >> 16) * level >> 14`, both shifts unsigned.
#ifndef GG_MATCH_CORE_CLAMPED_SCALE_METHODS_H
#define GG_MATCH_CORE_CLAMPED_SCALE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Sink_004061D0;

// FUNCTION: GAMEMD 0x407150 (decl; reloc) — the mode-not-3 setter. Takes the
// scaled value in EDX (`SHL EDX,0x10; MOV [ECX+8],EDX` at 0x407154), so it is
// a __fastcall free function, not a __thiscall member.
void __fastcall FUN_00407150(Sink_004061D0* sink, int scaled);

// FUNCTION: GAMEMD 0x407170 (decl; reloc) — the mode-3 setter, reached by
// `JMP` at 0x406204.
int __fastcall FUN_00407170(Sink_004061D0* sink, int scaled);

// FUNCTION: GAMEMD 0x4071C0 (decl; reloc) — the post-set notify, reached by
// `MOV ECX,ESI; POP ESI; JMP` at 0x40623B. Only ECX is loaded, so __fastcall
// and __thiscall are both consistent with the bytes; __fastcall is what makes
// VC6 tail-jump it (a __thiscall member here stays a `CALL; POP; RET`).
int __fastcall FUN_004071C0(Sink_004061D0* sink);

struct Sink_004061D0
{
    // The mode-not-3 path: set, then notify. Inlined into 0x4061D0, which is
    // what keeps the `PUSH ESI` inside that branch (0x40621E) instead of the
    // prologue.
    int Set(int scaled)
    {
        FUN_00407150(this, scaled);
        return FUN_004071C0(this);
    }
};

struct Rate_004061D0
{
    char     _pad000[0x1C];
    unsigned Value;   // +0x001C
};
GG_STATIC_ASSERT(offsetof(Rate_004061D0, Value) == 0x1C);

struct Obj_004061D0
{
    char            _pad000[0x1C];
    int             Mode;   // +0x001C
    char            _pad020[0x24 - 0x20];
    Rate_004061D0*  Rate;   // +0x0024
    char            _pad028[0xB8 - 0x28];
    Sink_004061D0   Sink;   // +0x00B8
};
GG_STATIC_ASSERT(offsetof(Obj_004061D0, Mode) == 0x1C);
GG_STATIC_ASSERT(offsetof(Obj_004061D0, Rate) == 0x24);
GG_STATIC_ASSERT(offsetof(Obj_004061D0, Sink) == 0xB8);

// The level arrives in EDX with the object in ECX, so this is a __fastcall free
// function rather than a member - a __thiscall method would take it on the
// stack. Both paths end in a tail-jump to an int-returning setter, and the
// result is passed through.
// FUNCTION: GAMEMD 0x4061D0
int __fastcall FUN_004061D0(Obj_004061D0* self, unsigned level);

#endif  // GG_MATCH_CORE_CLAMPED_SCALE_METHODS_H
