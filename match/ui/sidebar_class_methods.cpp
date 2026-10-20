// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// SidebarClass::GetObjectTabIdx @ 0x6ABCD0 (static __fastcall, RET 0x4).
//
// Retail body (Ghidra disasm, 0x6ABCD0..0x6ABD05, len 0x35):
//   cmp ecx,0x10 ; jnz +.. ; mov eax,2 ; ret 4          -> abs==0x10 -> 2
//   cmp ecx,0x28 ; jz  L3                                \  abs==0x28 ||
//   cmp ecx,3    ; jz  L3                                /  abs==3    -> 3
//   cmp ecx,7    ; jnz Lneg                              -> else abs!=7 -> -1
//   xor eax,eax ; cmp edx,5 ; setz al ; ret 4            -> abs==7 -> buildCat==5
//   Lneg:  or eax,-1 ; ret 4                             -> -1
//   L3:    mov eax,3 ; ret 4                             -> 3
//
// The abs==7 tail clears EAX then SETZ from a CMP whose value lives in EDX
// (not EAX), so it is the clean `xor eax,eax; setz al` form (no register-
// pressure setcc delta).
#include "sidebar_class_methods.h"

// FUNCTION: GAMEMD 0x6ABCD0  SidebarClass::GetObjectTabIdx (static __fastcall)
int __fastcall SidebarClass::GetObjectTabIdx(int abs, int buildCat, int isNaval)
{
    if (abs == 0x10)
        return 2;
    if (abs == 0x28 || abs == 3)
        return 3;
    if (abs == 7)
        return buildCat == 5;
    return -1;
}
