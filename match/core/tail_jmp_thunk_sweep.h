// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every entry point and every jump target below was read off the user's own
//   retail gamemd.exe v1.001 with the local Ghidra CLI. No YRpp binding.
//
// Nine one-instruction tail-jump thunks.
//
// Each is a bare `JMP rel32` and nothing else: the linker-visible entry point
// for a function whose body lives elsewhere, so the call arrives, the jump
// happens, and the target returns straight to the original caller. Two of them
// (0x5BBED0, 0x6370A0) jump only eleven bytes forward, over the alignment
// padding to the very next function.
//
// Written as a plain call in a `void __fastcall` wrapper with the identical
// signature: cl turns that into the tail jump on its own under /O2, so no
// inline asm is needed. Nothing is dereferenced, so there is no layout to
// reconstruct and nothing to assert an offsetof against.
#ifndef GG_MATCH_CORE_TAIL_JMP_THUNK_SWEEP_H
#define GG_MATCH_CORE_TAIL_JMP_THUNK_SWEEP_H

void __fastcall FUN_005B2EF0(void* self);   // GAMEMD 0x5B2EF0
void __fastcall FUN_005BBEE0(void* self);   // GAMEMD 0x5BBEE0
void __fastcall FUN_005F6B90(void* self);   // GAMEMD 0x5F6B90
void __fastcall FUN_006370B0(void* self);   // GAMEMD 0x6370B0
void __fastcall FUN_006385C0(void* self);   // GAMEMD 0x6385C0
void __fastcall FUN_00652CF0(void* self);   // GAMEMD 0x652CF0
void __fastcall FUN_006A5000(void* self);   // GAMEMD 0x6A5000
void __fastcall FUN_007529E0(void* self);   // GAMEMD 0x7529E0
void __fastcall FUN_007B46F0(void* self);   // GAMEMD 0x7B46F0

// PLACEHOLDER DELIBERATELY KEPT (whole-image RTTI sweep, docs/rtti_sweep.md).
// 0x4DA2B0 is slot 143 (byte-off 0x23C) of FootClass's own vtable 0x7E8C94 --
// but it is a tail jump to 0x5B2EF0, and 0x5B2EF0 occupies slot 143 of
// MissionClass (0x7EDCC0), RadioClass (0x7F0508) and TechnoClass (0x7F4960)
// as well. MissionClass is the highest of those in the chain that has the slot
// (ObjectClass's table is only 122 slots long), so the VIRTUAL is declared on
// MissionClass and FootClass merely re-enters it through this thunk. Naming
// this thunk `FootClass::...` would put a MissionClass method on FootClass, so
// it keeps the raw name; the body is `void __fastcall(void*)` with no class.
void __fastcall FUN_004DA2B0(void* self);   // FUNCTION: GAMEMD 0x4DA2B0
void __fastcall FUN_004DE620(void* self);   // FUNCTION: GAMEMD 0x4DE620
void __fastcall FUN_005BBED0(void* self);   // FUNCTION: GAMEMD 0x5BBED0
void __fastcall FUN_005D0580(void* self);   // FUNCTION: GAMEMD 0x5D0580
void __fastcall FUN_006370A0(void* self);   // FUNCTION: GAMEMD 0x6370A0
void __fastcall FUN_0063F7B0(void* self);   // FUNCTION: GAMEMD 0x63F7B0
void __fastcall FUN_006D0260(void* self);   // FUNCTION: GAMEMD 0x6D0260
void __fastcall FUN_00705D60(void* self);   // FUNCTION: GAMEMD 0x705D60
void __fastcall FUN_007717F0(void* self);   // FUNCTION: GAMEMD 0x7717F0

#endif  // GG_MATCH_CORE_TAIL_JMP_THUNK_SWEEP_H
