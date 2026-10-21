// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: retail constructor 0x00410170 and the RTTI descriptor below;
//   YRpp AbstractClass.h was consulted for naming hypotheses only.
//   The retail RTTI TypeDescriptor at 0x008177C8 is named ".?AVAbstractClass@@",
//   confirming the class-key; offsets and fields remain grounded in the
//   constructor stores below.
//
// AbstractClass — the root of every RA2 game object (instances) and, via
// AbstractTypeClass, every INI "blueprint" type. Begins with FOUR COM vtable
// pointers (multiple inheritance from IPersistStream / IRTTITypeInfo /
// INoticeSink / INoticeSource), then the shared bookkeeping fields.
//
// The four vptrs are modelled as explicit fields here so the 32-bit layout is
// exact. Constructors store these fields directly; dispatching methods use
// explicit slot-call views until the COM inheritance graph is reconstructed.
// The vptr-group addresses per concrete class come from its ctor (e.g.
// AbstractTypeClass writes 0x7E2000/0x7E1FE4/0x7E1FDC/0x7E1FD4).
#ifndef GG_MATCH_LAYOUT_ABSTRACT_CLASS_H
#define GG_MATCH_LAYOUT_ABSTRACT_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// AbstractClass base  (0x00..0x23, sizeof = 0x24)
class AbstractClass
{
public:
    // FUNCTION: GAMEMD 0x410170 (declaration; native base constructor)
    AbstractClass();
    // FUNCTION: GAMEMD 0x4101F0 (native base destructor)
    ~AbstractClass();
    // FUNCTION: GAMEMD 0x7258D0 (declaration; ECX receiver, DL flag)
    void __fastcall AnnounceExpiredPointer(unsigned char removed);

    void* _vtable_IPersistStream;   // +0x00
    void* _vtable_IRTTITypeInfo;    // +0x04
    void* _vtable_INoticeSink;      // +0x08
    void* _vtable_INoticeSource;    // +0x0C
    int   UniqueID;                 // +0x10
    int   AbstractFlags;            // +0x14
    int   unknown_18;               // +0x18
    long  RefCount;                 // +0x1C
    unsigned char Dirty;            // +0x20  (bool)
    unsigned char _pad_21[3];       // +0x21
};

GG_STATIC_ASSERT(offsetof(AbstractClass, UniqueID)      == 0x10);
GG_STATIC_ASSERT(offsetof(AbstractClass, AbstractFlags) == 0x14);
GG_STATIC_ASSERT(offsetof(AbstractClass, unknown_18)    == 0x18);
GG_STATIC_ASSERT(offsetof(AbstractClass, RefCount)      == 0x1C);
GG_STATIC_ASSERT(offsetof(AbstractClass, Dirty)         == 0x20);
GG_STATIC_ASSERT(sizeof(AbstractClass)                  == 0x24);

#endif  // GG_MATCH_LAYOUT_ABSTRACT_CLASS_H
