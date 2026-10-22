// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every shape below read numerically off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at the address in each annotation. None is bound
//   by YRpp, so all keep Ghidra placeholder names.
//
// Constant-return and identity leaves. These do not belong to one class — they
// are grouped because they share a shape and each is a single instruction pair
// with nothing to model. They are ordered ascending by retail address, as every
// TU here is.
//
// Reading the convention off the epilogue, since nothing else pins it:
//   `RET` with no immediate and no ECX use  -> no arguments at all
//   `RET` with no immediate and ECX read    -> __fastcall, object in ECX
//   `RET 4`                                 -> one stack argument
// A `RET 4` stub that ignores ECX is indistinguishable from a __thiscall member
// that ignores its `this`; the bytes are the same either way, and the free
// __stdcall form is used because it claims less.
#ifndef GG_MATCH_CORE_CONST_RETURN_STUB_METHODS_H
#define GG_MATCH_CORE_CONST_RETURN_STUB_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA8ED84 — the engine frame counter, read by 0x426630.
#include "../core/frame_counter.h"

// A countdown timer: a start frame at +0x00 and a duration at +0x08, with -1
// in the start field meaning "not running". 0x426620 sits on the same object,
// which is why it shares this type rather than getting its own.
struct Obj_00426600
{
    int  unknown_00;   // +0x0000  start frame, or -1
    char _pad04[0x4];
    int  unknown_08;   // +0x0008  duration in frames

    // FUNCTION: GAMEMD 0x426620
    Obj_00426600* FUN_00426620(int unused);
    // FUNCTION: GAMEMD 0x426630
    int FUN_00426630() const;
};

GG_STATIC_ASSERT(offsetof(Obj_00426600, unknown_08) == 0x08);

int   __stdcall FUN_00410300(int unused);   // FUNCTION: GAMEMD 0x410300
int   __stdcall FUN_00410310(int unused);   // FUNCTION: GAMEMD 0x410310
void  __stdcall FUN_00413490(int unused);   // FUNCTION: GAMEMD 0x413490
int   __cdecl   FUN_004125F0();             // FUNCTION: GAMEMD 0x4125F0
int   __cdecl   FUN_00412600();             // FUNCTION: GAMEMD 0x412600
void* FUN_00420120(void* self);  // FUNCTION: GAMEMD 0x420120
bool  __cdecl   FUN_00465D30();             // FUNCTION: GAMEMD 0x465D30

#endif  // GG_MATCH_CORE_CONST_RETURN_STUB_METHODS_H
