// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x477EC0 and its 22 siblings.
//
//   The shape is `DynamicVectorClass<T*>::AddItem(T item)`: append one element
//   to a growable vector, growing it through the vector's own virtual
//   `SetCapacity` slot when it is full. The method name is cross-checked
//   against YRpp and the body below is reconfirmed against retail.
//
//   That is a real recovered method name, not a placeholder: this family is
//   converted from the free-`__fastcall`-with-a-receiver shortcut (batch
//   forty-one) to genuine
//   `__thiscall` members of the class the receiver actually belongs to.
//
//   All 23 members are byte-identical to one another over the whole 0x50
//   bytes: the growth call goes through vtable slot +0x8 on `this`, so there
//   is no absolute constant and no call displacement anywhere in the body.
//   Only the retail address varies, so one body macro is instantiated 23
//   times.
//
//   Each of the 23 retail addresses is its own template instantiation of
//   `DynamicVectorClass<T*>` for a distinct (and, from this evidence alone,
//   unidentified) pointee type `T`, so each gets its own type below rather
//   than being folded into one shared class: the layout is proven identical
//   across all 23 by the extraction, but the classes are not one class, and
//   giving them a single shared name would fabricate an identity the bytes do
//   not establish. Vptr, layout offsets and the growth mechanics are the part
//   proven identical; the surrounding class remains addr-scoped.
//
//   Layout confirmed numerically from the member accesses in the
//   disassembly: [ESI]=+0x00 vptr, [ESI+0x04] Items, [ESI+0x08] Capacity,
//   [ESI+0x0D] IsAllocated (byte), [ESI+0x10] Count, [ESI+0x14]
//   CapacityIncrement.
#ifndef GG_MATCH_CORE_DYNAMIC_VECTOR_PTR_ADDITEM_METHODS_H
#define GG_MATCH_CORE_DYNAMIC_VECTOR_PTR_ADDITEM_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// Declaration order per match/_rt/gg_vslot.h: forward-declare the vtable,
// complete the object (now carrying its own AddItem), then type the growth
// slot as a pointer-to-member, then complete the vtable.
//
// One struct per retail address (see the provenance note above for why), all
// sharing the identical proven layout and body.
#define GG_DYNVEC_PTR_ADDITEM_TYPE(addr)                                      \
    struct DynVecPtrVtbl_##addr;                                             \
    struct DynVecPtr_##addr                                                  \
    {                                                                        \
        DynVecPtrVtbl_##addr* Vptr;   /* +0x0000 */                          \
        void** Items;                 /* +0x0004 */                          \
        int Capacity;                 /* +0x0008 */                          \
        char IsInitialized;           /* +0x000C */                          \
        char IsAllocated;              /* +0x000D */                        \
        char unknown_0E[2];            /* +0x000E */                        \
        int Count;                     /* +0x0010 */                        \
        int CapacityIncrement;         /* +0x0014 */                        \
        bool AddItem(void* const* item);                                     \
    };                                                                       \
    GG_STATIC_ASSERT(offsetof(DynVecPtr_##addr, Items) == 0x04);             \
    GG_STATIC_ASSERT(offsetof(DynVecPtr_##addr, Capacity) == 0x08);          \
    GG_STATIC_ASSERT(offsetof(DynVecPtr_##addr, IsInitialized) == 0x0C);     \
    GG_STATIC_ASSERT(offsetof(DynVecPtr_##addr, IsAllocated) == 0x0D);       \
    GG_STATIC_ASSERT(offsetof(DynVecPtr_##addr, Count) == 0x10);             \
    GG_STATIC_ASSERT(offsetof(DynVecPtr_##addr, CapacityIncrement) == 0x14); \
    GG_STATIC_ASSERT(sizeof(DynVecPtr_##addr) == 0x18);                      \
    /* Virtual slot +0x08: SetCapacity(int capacity, T** preallocated). */   \
    typedef bool (DynVecPtr_##addr::*FnSetCapacity_##addr)(int capacity,     \
                                                           void** prealloc); \
    struct DynVecPtrVtbl_##addr                                              \
    {                                                                        \
        char unknown_00[0x08];                                               \
        FnSetCapacity_##addr SetCapacity;   /* +0x0008 */                    \
    };                                                                       \
    GG_STATIC_ASSERT(offsetof(DynVecPtrVtbl_##addr, SetCapacity) == 0x08)

GG_DYNVEC_PTR_ADDITEM_TYPE(00477EC0);   // FUNCTION: GAMEMD 0x00477EC0
GG_DYNVEC_PTR_ADDITEM_TYPE(004A7FE0);   // FUNCTION: GAMEMD 0x004A7FE0
GG_DYNVEC_PTR_ADDITEM_TYPE(00512F20);   // FUNCTION: GAMEMD 0x00512F20
GG_DYNVEC_PTR_ADDITEM_TYPE(005132F0);   // FUNCTION: GAMEMD 0x005132F0
GG_DYNVEC_PTR_ADDITEM_TYPE(005136C0);   // FUNCTION: GAMEMD 0x005136C0
GG_DYNVEC_PTR_ADDITEM_TYPE(005253B0);   // FUNCTION: GAMEMD 0x005253B0
GG_DYNVEC_PTR_ADDITEM_TYPE(00538780);   // FUNCTION: GAMEMD 0x00538780
GG_DYNVEC_PTR_ADDITEM_TYPE(00589C50);   // FUNCTION: GAMEMD 0x00589C50
GG_DYNVEC_PTR_ADDITEM_TYPE(005AD7D0);   // FUNCTION: GAMEMD 0x005AD7D0
GG_DYNVEC_PTR_ADDITEM_TYPE(005EEE40);   // FUNCTION: GAMEMD 0x005EEE40
GG_DYNVEC_PTR_ADDITEM_TYPE(00630250);   // FUNCTION: GAMEMD 0x00630250
GG_DYNVEC_PTR_ADDITEM_TYPE(0063E540);   // FUNCTION: GAMEMD 0x0063E540
GG_DYNVEC_PTR_ADDITEM_TYPE(0063E880);   // FUNCTION: GAMEMD 0x0063E880
GG_DYNVEC_PTR_ADDITEM_TYPE(0063EB80);   // FUNCTION: GAMEMD 0x0063EB80
GG_DYNVEC_PTR_ADDITEM_TYPE(0067AD80);   // FUNCTION: GAMEMD 0x0067AD80
GG_DYNVEC_PTR_ADDITEM_TYPE(0067B100);   // FUNCTION: GAMEMD 0x0067B100
GG_DYNVEC_PTR_ADDITEM_TYPE(0067B480);   // FUNCTION: GAMEMD 0x0067B480
GG_DYNVEC_PTR_ADDITEM_TYPE(0068C260);   // FUNCTION: GAMEMD 0x0068C260
GG_DYNVEC_PTR_ADDITEM_TYPE(00691160);   // FUNCTION: GAMEMD 0x00691160
GG_DYNVEC_PTR_ADDITEM_TYPE(006C6400);   // FUNCTION: GAMEMD 0x006C6400
GG_DYNVEC_PTR_ADDITEM_TYPE(00717CD0);   // FUNCTION: GAMEMD 0x00717CD0
GG_DYNVEC_PTR_ADDITEM_TYPE(00734390);   // FUNCTION: GAMEMD 0x00734390
GG_DYNVEC_PTR_ADDITEM_TYPE(00763330);   // FUNCTION: GAMEMD 0x00763330

#endif  // GG_MATCH_CORE_DYNAMIC_VECTOR_PTR_ADDITEM_METHODS_H
