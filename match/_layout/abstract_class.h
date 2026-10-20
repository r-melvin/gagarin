// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: ctors FUN_0x00410170 / FUN_0x00410800 (docs/decomp_spec/
//   type_hierarchy_layout.md), cross-checked vs YRpp AbstractClass.h. P2
//   layout-spine root.
//
// AbstractClass — the root of every RA2 game object (instances) and, via
// AbstractTypeClass, every INI "blueprint" type. Begins with FOUR COM vtable
// pointers (multiple inheritance from IPersistStream / IRTTITypeInfo /
// INoticeSink / INoticeSource), then the shared bookkeeping fields.
//
// The four vptrs are modelled as explicit fields here so the 32-bit layout is
// exact and VC6-robust. Functions that *store* these vptrs (an inlined ctor)
// or dispatch through them need the real COM multiple-inheritance base or inline
// _asm; the vptr-group addresses per concrete class come from its ctor (e.g.
// AbstractTypeClass writes 0x7E4A28/0x7E4A0C/0x7E4A04/0x7E49FC).
#ifndef GG_MATCH_LAYOUT_ABSTRACT_CLASS_H
#define GG_MATCH_LAYOUT_ABSTRACT_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// AbstractClass base  (0x00..0x23, sizeof = 0x24)
struct AbstractClass
{
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
