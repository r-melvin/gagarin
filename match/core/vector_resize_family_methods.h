// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x477E10 and its 31 siblings; 0x477E10 now lives on
//   native DynamicVectorClass<int> in vector_int_methods.cpp. Shape found by clustering
//   the unmatched pool on size (176 bytes) and on the first/last eight bytes;
//   every member's 176 retail bytes are identical apart from the two relative
//   call displacements (operator new at 0x7C8E17, free at 0x7C8B3D), so there
//   is no per-instance parameter to model. Offsets re-derived here from the
//   member accesses: Vector `[ESI+4]`, Length `[ESI+8]`, the re-entrancy flag
//   `[ESI+0xC]` (cleared around the allocation, set again after it), the
//   ownership flag `[ESI+0xD]` (`MOV AL,byte ptr [ESI+0xD]` before the free,
//   then written from `SETZ AL`), and ActiveCount `[ESI+0x10]` (clamped at
//   the tail). The element size is four: `LEA EAX,[EBP*0x4]` feeds operator
//   new and `MOV [EDI+EAX*0x4-4]` is the copy store.
//
//   These 32 are the same VectorClass::Resize shape already carried by
//   match/core/vector_resize_methods.{h,cpp}, so that header's VectorBase
//   layout and its clear-virtual macro are reused verbatim rather than
//   redeclared, which keeps the two TUs from disagreeing about the layout.
//   None of the 32 is bound by YRpp or the seed map; the placeholders stand.
#ifndef GG_MATCH_CORE_VECTOR_RESIZE_FAMILY_METHODS_H
#define GG_MATCH_CORE_VECTOR_RESIZE_FAMILY_METHODS_H

#include "vector_resize_methods.h"

GG_STATIC_ASSERT(offsetof(VectorBase, Vector)      == 0x04);
GG_STATIC_ASSERT(offsetof(VectorBase, Length)      == 0x08);
GG_STATIC_ASSERT(offsetof(VectorBase, IsValid)     == 0x0C);
GG_STATIC_ASSERT(offsetof(VectorBase, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(VectorBase, ActiveCount) == 0x10);
GG_STATIC_ASSERT(sizeof(VectorBase) == 0x14);

struct VectorResizeFamily : VectorBase
{
    // FUNCTION: GAMEMD 0x478140
    bool FUN_478140(int newsize, void** array);
    // FUNCTION: GAMEMD 0x49EA70
    bool FUN_49EA70(int newsize, void** array);
    // FUNCTION: GAMEMD 0x49ED30
    bool FUN_49ED30(int newsize, void** array);
    // FUNCTION: GAMEMD 0x4A13C0
    bool FUN_4A13C0(int newsize, void** array);
    // FUNCTION: GAMEMD 0x4CAA70
    bool FUN_4CAA70(int newsize, void** array);
    // FUNCTION: GAMEMD 0x4E04A0
    bool FUN_4E04A0(int newsize, void** array);
    // FUNCTION: GAMEMD 0x4E95E0
    bool FUN_4E95E0(int newsize, void** array);
    // FUNCTION: GAMEMD 0x4E9840
    bool FUN_4E9840(int newsize, void** array);
    // FUNCTION: GAMEMD 0x4EA1C0
    bool FUN_4EA1C0(int newsize, void** array);
    // FUNCTION: GAMEMD 0x4EBD60
    bool FUN_4EBD60(int newsize, void** array);
    // FUNCTION: GAMEMD 0x4EDEA0
    bool FUN_4EDEA0(int newsize, void** array);
    // FUNCTION: GAMEMD 0x4EE360
    bool FUN_4EE360(int newsize, void** array);
    // FUNCTION: GAMEMD 0x4F2A60
    bool FUN_4F2A60(int newsize, void** array);
    // FUNCTION: GAMEMD 0x50EA90
    bool FUN_50EA90(int newsize, void** array);
    // FUNCTION: GAMEMD 0x512E70
    bool FUN_512E70(int newsize, void** array);
    // FUNCTION: GAMEMD 0x513240
    bool FUN_513240(int newsize, void** array);
    // FUNCTION: GAMEMD 0x513610
    bool FUN_513610(int newsize, void** array);
    // FUNCTION: GAMEMD 0x5AC820
    bool FUN_5AC820(int newsize, void** array);
    // FUNCTION: GAMEMD 0x5AD010
    bool FUN_5AD010(int newsize, void** array);
    // FUNCTION: GAMEMD 0x5C0C50
    bool FUN_5C0C50(int newsize, void** array);
    // FUNCTION: GAMEMD 0x5C5510
    bool FUN_5C5510(int newsize, void** array);
    // FUNCTION: GAMEMD 0x5D0C60
    bool FUN_5D0C60(int newsize, void** array);
    // FUNCTION: GAMEMD 0x5D0EC0
    bool FUN_5D0EC0(int newsize, void** array);
    // FUNCTION: GAMEMD 0x5D8730
    bool FUN_5D8730(int newsize, void** array);
    // FUNCTION: GAMEMD 0x627F90
    bool FUN_627F90(int newsize, void** array);
    // FUNCTION: GAMEMD 0x67ACD0
    bool FUN_67ACD0(int newsize, void** array);
    // FUNCTION: GAMEMD 0x67B050
    bool FUN_67B050(int newsize, void** array);
    // FUNCTION: GAMEMD 0x67B3D0
    bool FUN_67B3D0(int newsize, void** array);
    // FUNCTION: GAMEMD 0x69C890
    bool FUN_69C890(int newsize, void** array);
    // FUNCTION: GAMEMD 0x6B15F0
    bool FUN_6B15F0(int newsize, void** array);
    // FUNCTION: GAMEMD 0x6B8400
    bool FUN_6B8400(int newsize, void** array);
};

#endif  // GG_MATCH_CORE_VECTOR_RESIZE_FAMILY_METHODS_H
