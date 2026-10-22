// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-xcheck
//   Bytes matched against retail gamemd.exe v1.001. See the header for the
//   shape, the confirmed layout, the YRpp cross-check on the name, and the
//   family's (absent) per-instance variation: all 23 members are
//   byte-identical, so one body macro serves every address and a later fix is
//   a one-place edit. Each address gets its own AddItem member on its own
//   addr-scoped type (see the header); the shared macro is what keeps that
//   from being 23x the source text.

#include "dynamic_vector_ptr_additem_methods.h"

// The one shared body: append `*item` to the vector, growing through the
// vector's own virtual SetCapacity (vtable slot +0x8) when it is full.
// Recovered as DynamicVectorClass<T*>::AddItem (name cross-checked against YRpp).
#define GG_DYNVEC_PTR_ADDITEM_BODY(addr)                                      \
    bool DynVecPtr_##addr::AddItem(void* const* item)                        \
    {                                                                        \
        if (Count >= Capacity) {                                             \
            if ((IsAllocated || Capacity == 0) && CapacityIncrement > 0) {   \
                if (!(this->*Vptr->SetCapacity)(                             \
                        Capacity + CapacityIncrement, 0)) {                  \
                    return false;                                            \
                }                                                            \
            } else {                                                        \
                return false;                                                \
            }                                                                \
        }                                                                    \
        int index = Count++;                                                \
        Items[index] = *item;                                                \
        return true;                                                         \
    }

// FUNCTION: GAMEMD 0x00477EC0
GG_DYNVEC_PTR_ADDITEM_BODY(00477EC0)

// FUNCTION: GAMEMD 0x004A7FE0
GG_DYNVEC_PTR_ADDITEM_BODY(004A7FE0)

// FUNCTION: GAMEMD 0x00512F20
GG_DYNVEC_PTR_ADDITEM_BODY(00512F20)

// FUNCTION: GAMEMD 0x005132F0
GG_DYNVEC_PTR_ADDITEM_BODY(005132F0)

// FUNCTION: GAMEMD 0x005136C0
GG_DYNVEC_PTR_ADDITEM_BODY(005136C0)

// FUNCTION: GAMEMD 0x005253B0
GG_DYNVEC_PTR_ADDITEM_BODY(005253B0)

// FUNCTION: GAMEMD 0x00538780
GG_DYNVEC_PTR_ADDITEM_BODY(00538780)

// FUNCTION: GAMEMD 0x00589C50
GG_DYNVEC_PTR_ADDITEM_BODY(00589C50)

// FUNCTION: GAMEMD 0x005AD7D0
GG_DYNVEC_PTR_ADDITEM_BODY(005AD7D0)

// FUNCTION: GAMEMD 0x005EEE40
GG_DYNVEC_PTR_ADDITEM_BODY(005EEE40)

// FUNCTION: GAMEMD 0x00630250
GG_DYNVEC_PTR_ADDITEM_BODY(00630250)

// FUNCTION: GAMEMD 0x0063E540
GG_DYNVEC_PTR_ADDITEM_BODY(0063E540)

// FUNCTION: GAMEMD 0x0063E880
GG_DYNVEC_PTR_ADDITEM_BODY(0063E880)

// FUNCTION: GAMEMD 0x0063EB80
GG_DYNVEC_PTR_ADDITEM_BODY(0063EB80)

// FUNCTION: GAMEMD 0x0067AD80
GG_DYNVEC_PTR_ADDITEM_BODY(0067AD80)

// FUNCTION: GAMEMD 0x0067B100
GG_DYNVEC_PTR_ADDITEM_BODY(0067B100)

// FUNCTION: GAMEMD 0x0067B480
GG_DYNVEC_PTR_ADDITEM_BODY(0067B480)

// FUNCTION: GAMEMD 0x0068C260
GG_DYNVEC_PTR_ADDITEM_BODY(0068C260)

// FUNCTION: GAMEMD 0x00691160
GG_DYNVEC_PTR_ADDITEM_BODY(00691160)

// FUNCTION: GAMEMD 0x006C6400
GG_DYNVEC_PTR_ADDITEM_BODY(006C6400)

// FUNCTION: GAMEMD 0x00717CD0
GG_DYNVEC_PTR_ADDITEM_BODY(00717CD0)

// FUNCTION: GAMEMD 0x00734390
GG_DYNVEC_PTR_ADDITEM_BODY(00734390)

// FUNCTION: GAMEMD 0x00763330
GG_DYNVEC_PTR_ADDITEM_BODY(00763330)

