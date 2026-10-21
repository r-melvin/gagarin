// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at each address below. Shape identified by clustering the
//   111-300 byte unmatched pool; two remaining outer views, byte-identical apart from the
//   entry point. None is bound by YRpp or the seed map.
//
// VectorClass::Resize. Take a new size and an optional caller-supplied buffer;
// allocate when none is given, copy across the smaller of the old and new
// lengths, release the old buffer only if this vector owned it, and adopt the
// new one. A size of zero routes to the clear virtual at slot +0x0C instead.
//
// Two details that are easy to get wrong and are visible in the bytes: the
// element size is four (`LEA EAX,[EBP*4]` feeding operator new), and the copy
// loop re-reads the source pointer from the object on *every* iteration
// (`MOV EDX,[ESI+4]` sits inside the loop), so the source indexes through the
// member rather than through a hoisted local.
#ifndef GG_MATCH_CORE_VECTOR_RESIZE_METHODS_H
#define GG_MATCH_CORE_VECTOR_RESIZE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void* __cdecl FUN_007C8E17(unsigned int size);   // operator new
extern "C" void  __cdecl FUN_007C8B3D(void* block);         // free

struct VectorBase;
typedef void (__fastcall* ClearFunc)(VectorBase*);
#define VECTOR_CLEAR(v) ((*(ClearFunc*)(*(char**)(v) + 0xc))(v))

struct VectorBase
{
    void*         _vtable;       // +0x0000
    void**        Vector;        // +0x0004
    int           Length;        // +0x0008
    unsigned char IsValid;       // +0x000C
    unsigned char IsAllocated;   // +0x000D
    char          _pad0E[0x2];
    int           ActiveCount;   // +0x0010

    // VectorClass::Resize, the inlined inner half of the retail function.
    // Kept inline in the header so the remaining address-scoped views share one body: the
    // 176 retail bytes are identical apart from the two call displacements.
    bool ResizeBase(int newsize, void** array);
};
GG_STATIC_ASSERT(offsetof(VectorBase, Vector) == 0x04);
GG_STATIC_ASSERT(offsetof(VectorBase, Length) == 0x08);
GG_STATIC_ASSERT(offsetof(VectorBase, IsValid) == 0x0C);
GG_STATIC_ASSERT(offsetof(VectorBase, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(VectorBase, ActiveCount) == 0x10);

// The retail body is DynamicVectorClass::Resize with VectorClass::Resize
// inlined into it. Writing it as the two nested functions - the inner one
// returning bool, the outer one `if (inner()) { clamp; return true; } return
// false;` - is what places the `return false` epilogue LAST, where retail has
// it; written as one flat function cl 8804 tail-duplicates that block inline
// at its branch and places it second. See the note in
// vector_resize_family_methods.cpp.
inline bool VectorBase::ResizeBase(int newsize, void** array)
{
    if (newsize != 0) {
        void** newptr;

        IsValid = 0;

        if (array == 0) {
            newptr = (void**)FUN_007C8E17(newsize * 4);
        } else {
            newptr = array;
        }

        IsValid = 1;

        if (newptr == 0) {
            return false;
        }

        if (Vector != 0) {
            int count = Length;

            if (newsize < count) {
                count = newsize;
            }

            for (int i = 0; i < count; i++) {
                newptr[i] = Vector[i];
            }

            if (IsAllocated) {
                FUN_007C8B3D(Vector);
                Vector = 0;
            }
        }

        Vector = newptr;
        Length = newsize;
        IsAllocated = (Vector != 0 && array == 0);
    } else {
        VECTOR_CLEAR(this);
    }

    return true;
}

struct VectorResize : VectorBase
{
    // FUNCTION: GAMEMD 0x40CE50
    bool FUN_0040CE50(int newsize, void** array);
    // FUNCTION: GAMEMD 0x42D780
    bool FUN_0042D780(int newsize, void** array);
};

#endif  // GG_MATCH_CORE_VECTOR_RESIZE_METHODS_H
