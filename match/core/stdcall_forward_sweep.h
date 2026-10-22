// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every entry point and callee address below was read off the user's own
//   retail gamemd.exe v1.001 with the local Ghidra CLI.
//
// Four thirteen-byte argument forwarders.
//
// `MOV EAX,[ESP+4]; PUSH EAX; CALL <callee>; RET 4`. Each is a virtual slot,
// so the caller passes `this` in ECX; the function takes one stack argument,
// ignores `this` entirely, and hands the argument straight on. The absence of
// any stack cleanup after the CALL pins the callee's convention: it is
// `__stdcall`, not `__cdecl`. Declared
// `__cdecl` instead, cl adds the `POP ECX` and the tail diverges (60%).
//
// 0x6D1800 differs: it is slot 33 of the TabClass (0x7EDFB4),
// ScrollClass (0x7F1094) and MouseClass (0x7E1964) vtables, and its callee
// 0x6AC210 is slot 33 of SidebarClass's (0x7F3058). It leaves `this` in ECX
// for the base-class call.
#ifndef GG_MATCH_CORE_STDCALL_FORWARD_SWEEP_H
#define GG_MATCH_CORE_STDCALL_FORWARD_SWEEP_H

void __stdcall FUN_004AE4F0(void* arg);   // GAMEMD 0x4AE4F0
void __stdcall FUN_006568A0(void* arg);   // GAMEMD 0x6568A0
void __stdcall FUN_00656AC0(void* arg);   // GAMEMD 0x656AC0

// RadarClass (RTTI), only slot 33 (vtable 0x7F0344).
struct Radar_00658770
{
    void FUN_00658770(void* arg);   // FUNCTION: GAMEMD 0x658770
};

// SidebarClass and TabClass (RTTI), only the slots used here. 0x6AC5D0 and
// 0x6AC5E0 are slots 30 and 31 of the SidebarClass, TabClass and ScrollClass
// vtables. Slot 33's name is not attested, so it keeps the vf_<slot>
// placeholder.
struct Sidebar_006D1800
{
    void FUN_006AC5D0(void* arg);   // FUNCTION: GAMEMD 0x6AC5D0
    void FUN_006AC5E0(void* arg);   // FUNCTION: GAMEMD 0x6AC5E0
    void vf_33(void* arg);   // GAMEMD 0x6AC210 (decl; reloc)
};
struct Tab_006D1800 : Sidebar_006D1800
{
    void vf_33(void* arg);   // FUNCTION: GAMEMD 0x6D1800
};

#endif  // GG_MATCH_CORE_STDCALL_FORWARD_SWEEP_H
