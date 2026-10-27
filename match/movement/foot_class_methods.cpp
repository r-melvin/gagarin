// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Bodies and
//   member offsets derived directly from the disassembly; signatures
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x41C090  FootClass::vf_323 (__thiscall)
//   FUNCTION: GAMEMD 0x4DA1C0  FootClass::ClearNavigationList (__thiscall)
//   FUNCTION: GAMEMD 0x4DF0D0  FootClass::AbortMotion         (__thiscall)

#include "foot_class_methods.h"

// FUNCTION: GAMEMD 0x41C090
// Native wrapper forwards sixteen stack dwords to the existing TechnoClass
// helper, preserving the receiver in ECX.
void FootClass::vf_323(SHPStruct* a1, int a2, Point2D* a3,
                       RectangleStruct* a4, int a5, int a6, int a7, int a8,
                       int a9, int a10, int a11, int a12, int a13, int a14,
                       int a15, int a16)
{
    TechnoClass::FUN_00705E00(a1, a2, a3, a4, a5, a6, a7, a8,
                             a9, a10, a11, a12, a13, a14, a15, a16);
}

// FUNCTION: GAMEMD 0x4DA1C0  (__thiscall)
// Empty the pending movement-destination queue: tail-call NavQueue.Clear()
// (virtual slot +0x0C), forwarding `this+0x5AC` as the vector's `this`.
//   MOV EAX,[ECX+0x5AC] ; ADD ECX,0x5AC ; JMP [EAX+0x0C]
void FootClass::ClearNavigationList()
{
    ((NavVector*)&this->NavQueue)->Clear();
}

// FUNCTION: GAMEMD 0x4DF0D0  (__thiscall)
// Abort the current motion: drop the immediate source and destination cells.
//   XOR EAX,EAX ; MOV [ECX+0x5A0],EAX ; MOV [ECX+0x5A4],EAX ; RET
void FootClass::AbortMotion()
{
    this->unknown_5A0 = 0;
    this->Destination = 0;
}
