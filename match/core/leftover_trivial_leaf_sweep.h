// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every shape below read numerically off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at the address in each annotation. None is bound
//   by YRpp, so all keep Ghidra placeholder names.
//
// The trivial leaves left over after the large shape sweeps: one- and
// two-instruction functions that survived the earlier passes because their
// families are small. They do not belong to one class; they are grouped
// because each is a single load, a single constant, or a single store with
// nothing else to model. Ordered ascending by retail address.
//
// Reading the convention off the epilogue, since nothing else pins it:
//   `RET` with no immediate and ECX read -> __fastcall/__thiscall, object in ECX
//   `RET` with no immediate and no ECX use -> no arguments at all
//   `RET 4` -> one stack argument
// A `RET 4` leaf that ignores ECX is indistinguishable from a __thiscall member
// that ignores its `this`; the free __stdcall form is used because it claims
// less.
//
// Reviewed in the batch forty-one pass
// (the free-`__fastcall`-with-a-receiver debt) and deliberately LEFT as free
// functions. Converting would cost nothing in bytes — a member spelled
// `__fastcall` keeps the receiver in ECX and the first explicit argument in
// EDX — but `LeafObj_0x04 / LeafObj_0x10` is not one recovered class: it is ten separate leaves spread across more than 0x1D0000 of the image, grouped only by which offset they touch, modelled against one
// shared layout because the extraction proved the layout identical, not
// because they are one type. Declaring them members of a single struct would
// assert a class identity the evidence does not establish, which batch
// forty-one explicitly rules out. Each receiver's true class is undetermined.
#ifndef GG_MATCH_CORE_LEFTOVER_TRIVIAL_LEAF_SWEEP_H
#define GG_MATCH_CORE_LEFTOVER_TRIVIAL_LEAF_SWEEP_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A container read through its field at +0x10. Five leaves return this member
// raw (`MOV EAX,[ECX+0x10]; RET`); the surrounding address runs are the
// growable-vector clusters, so this is that shape's live-count accessor.
struct LeafObj_0x10
{
    char _pad00[0x10];   // +0x0000
    int  unknown_10;     // +0x0010
};
GG_STATIC_ASSERT(offsetof(LeafObj_0x10, unknown_10) == 0x10);

// A container read through its field at +0x04 (`MOV EAX,[ECX+4]; RET`) — the
// storage pointer of the same shape.
struct LeafObj_0x04
{
    char _pad00[0x4];    // +0x0000
    int  unknown_04;     // +0x0004
};
GG_STATIC_ASSERT(offsetof(LeafObj_0x04, unknown_04) == 0x4);

int FUN_0049FB60(LeafObj_0x10* self);   // FUNCTION: GAMEMD 0x49FB60
bool __cdecl   FUN_004A3BF0();                     // FUNCTION: GAMEMD 0x4A3BF0
void __stdcall FUN_004AAD20(int unused);           // FUNCTION: GAMEMD 0x4AAD20
bool __stdcall FUN_00484F10(int unused);           // FUNCTION: GAMEMD 0x484F10
void __stdcall FUN_004FF540(int unused);           // FUNCTION: GAMEMD 0x4FF540
bool __cdecl   FUN_005B43E0();                     // FUNCTION: GAMEMD 0x5B43E0
bool __stdcall FUN_005B43F0(int unused);           // FUNCTION: GAMEMD 0x5B43F0
bool __stdcall FUN_005D6310(int unused);           // FUNCTION: GAMEMD 0x5D6310
bool __cdecl   FUN_005D6340();                     // FUNCTION: GAMEMD 0x5D6340
bool __cdecl   FUN_005D7570();                     // FUNCTION: GAMEMD 0x5D7570
void __stdcall FUN_006A4FF0(int unused);           // FUNCTION: GAMEMD 0x6A4FF0
int FUN_0067A730(LeafObj_0x10* self);   // FUNCTION: GAMEMD 0x67A730
int FUN_0067A7C0(LeafObj_0x10* self);   // FUNCTION: GAMEMD 0x67A7C0
int FUN_0067A8A0(LeafObj_0x10* self);   // FUNCTION: GAMEMD 0x67A8A0
bool __cdecl   FUN_00711E80();                     // FUNCTION: GAMEMD 0x711E80
int FUN_00717A70(LeafObj_0x04* self);   // FUNCTION: GAMEMD 0x717A70
int FUN_0076F020(LeafObj_0x04* self);   // FUNCTION: GAMEMD 0x76F020
int FUN_0076F070(LeafObj_0x04* self);   // FUNCTION: GAMEMD 0x76F070
int FUN_0076F080(LeafObj_0x04* self);   // FUNCTION: GAMEMD 0x76F080

// Three single-store leaves that publish their ECX argument into a fixed
// global (`MOV [imm32],ECX; RET`). The destinations are read off the stores.
extern int DAT_00828140;   // GLOBAL: GAMEMD 0x828140
extern int DAT_00829FF4;   // GLOBAL: GAMEMD 0x829FF4
extern int DAT_00829FF8;   // GLOBAL: GAMEMD 0x829FF8

void FUN_0053F1F0(int value);   // FUNCTION: GAMEMD 0x53F1F0
void FUN_0055AF40(int value);   // FUNCTION: GAMEMD 0x55AF40
void FUN_0055AF50(int value);   // FUNCTION: GAMEMD 0x55AF50

#endif  // GG_MATCH_CORE_LEFTOVER_TRIVIAL_LEAF_SWEEP_H
