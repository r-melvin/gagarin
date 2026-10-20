// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Element stride, the count's placement and the flag bits read numerically
//   off the user's retail gamemd.exe v1.001 via the local Ghidra CLI at
//   0x41C490.
//
// The vector deleting destructor. Bit 1 of the flag says "this is an array":
// the element count sits in the dword *before* the object, the elements are
// 12 bytes each (`LEA ECX,[EAX+EAX*2]` then a `*4` index, and `SUB ESI,0xC` per
// step), they are destroyed back to front, and the block freed is the count
// word rather than the first element. Bit 0 is the usual "the object was heap
// allocated" marker.
//
// Written by hand rather than letting the compiler generate a `??_E`: the
// generated form would not be addressable at a chosen symbol, and the scalar
// path here is a separate branch rather than a separate function.
#ifndef GG_MATCH_CORE_VECTOR_DTOR_METHODS_H
#define GG_MATCH_CORE_VECTOR_DTOR_METHODS_H

extern "C" void __cdecl FUN_007C8B3D(void* block);

// FUNCTION: GAMEMD 0x763720 — the element destructor, __fastcall.
void __fastcall FUN_00763720(void* element);

// `MOV BL,byte ptr [ESP+8]` with the object in ECX makes the flag a *stack*
// argument, so this is __thiscall: a free __fastcall taking two arguments would
// deliver it in DL.
struct Element_0041C490
{
    char Bytes[12];

    // FUNCTION: GAMEMD 0x41C490
    void* FUN_0041C490(char flags);
};

#endif  // GG_MATCH_CORE_VECTOR_DTOR_METHODS_H
