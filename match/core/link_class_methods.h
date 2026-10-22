// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + vtable-slot order derived from the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI (member-access disassembly at the LinkClass
//   method addresses), cross-checked against YRpp (consult-only;
//   reconfirmed here).
//
// LinkClass — intrusive doubly-linked-list node base. A single vptr
// at +0x00, then two self-pointers: Next (+0x04) and Previous (+0x08).
//
// Offsets confirmed numerically:
//   * 0x5565F0 Zap        zeroes [ECX+0x4] (Next) and [ECX+0x8] (Previous).
//   * 0x556640 HeadOfList walks the Previous (+0x8) chain.
//   * 0x556670 TailOfList walks the Next (+0x4) chain.
//   * 0x5566A0 Add        loads/stores [..+0x4]=Next, [..+0x8]=Previous; calls
//                         vtable slot +0x24 (Remove) then +0x18 (HeadOfList).
//
// Vtable slot order (declaration order below) is fixed so that the indirect
// calls in Add land on the right slots: Remove == +0x24 (slot 9),
// HeadOfList == +0x18 (slot 6).
#ifndef GG_MATCH_CORE_LINK_CLASS_METHODS_H
#define GG_MATCH_CORE_LINK_CLASS_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

struct LinkClass
{
    // Inline: a derived constructor (GadgetClass, 0x4E12F0) stores both
    // pointers as zero before its own members.
    LinkClass() : Next(0), Previous(0) {}

    // vtable in retail slot order (vptr @ +0x00).
    virtual ~LinkClass();                            // slot 0
    virtual LinkClass* GetNext();                    // slot 1  GAMEMD 0x556620
    virtual LinkClass* GetPrev();                    // slot 2  GAMEMD 0x556630
    virtual LinkClass* Add(LinkClass& object);       // slot 3  GAMEMD 0x5566A0
    virtual LinkClass* AddTail(LinkClass& object);   // slot 4  GAMEMD 0x556700
    virtual LinkClass* AddHead(LinkClass& object);   // slot 5  GAMEMD 0x5566D0
    virtual LinkClass* HeadOfList();                 // slot 6  GAMEMD 0x556640
    virtual LinkClass* TailOfList();                 // slot 7  GAMEMD 0x556670
    virtual void       Zap();                        // slot 8  GAMEMD 0x5565F0
    virtual LinkClass* Remove();                     // slot 9  GAMEMD 0x556730

    LinkClass* Next;      // +0x04
    LinkClass* Previous;  // +0x08
};

GG_STATIC_ASSERT(offsetof(LinkClass, Next) == 0x04);
GG_STATIC_ASSERT(offsetof(LinkClass, Previous) == 0x08);
GG_STATIC_ASSERT(sizeof(LinkClass) == 0x0C);

#endif  // GG_MATCH_CORE_LINK_CLASS_METHODS_H
