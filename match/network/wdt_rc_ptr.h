// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   rc_ptr_base (RTTI ".?AVrc_ptr_base@@", vtable 0x7F094C) and its derived
//   rc_ptr<T> instantiations (RTTI ".?AV?$rc_ptr@...", one vtable each), read
//   off the retail gamemd.exe v1.001:
//     * 0x65D430 is the out-of-line base constructor: clear +0x04, seat
//       0x7F094C, return this;
//     * 0x65D460 is the out-of-line base destructor: reseat 0x7F094C, and if
//       +0x04 is set, clear it and release the pointee through its slot 2;
//     * 0x65D480 is the out-of-line assignment from a raw pointer (RET 4):
//       when it differs from +0x04, bump the new pointee's count at +0x04,
//       release the old one through slot 2, then store it.
//   Every derived constructor seen (0x767B00, 0x767FB0, 0x769CA0, the array
//   loops at 0x769E30 / 0x76A7E0) calls 0x65D430, seats its own vtable and,
//   when it has a source, calls 0x65D480 with it; the copy reads the source's
//   +0x04. The derived destructor reseats its own vtable and calls 0x65D460
//   (0x76A610). The derived vtable has one slot, the deleting destructor
//   (0x7F71C4 -> 0x76A610), so the destructor is virtual.
//   Equality compares the +0x04 pointers (0x769DE0, 0x769F80, 0x76A100).
//   ReferenceCounted (RTTI ".?AVReferenceCounted@@", vtable 0x7F0954) is the
//   pointee root: its inline constructor clears the count at +0x04 and seats
//   the table (0x767B70, 0x768000).
#ifndef GG_MATCH_NETWORK_WDT_RC_PTR_H
#define GG_MATCH_NETWORK_WDT_RC_PTR_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "wdt_rc_ptr_base.h"

// VTABLE: GAMEMD 0x7F0954
// Three slots: the deleting destructor (0x65D6A0), 0x65D690 and 0x65D670
// (rc_ptr_base releases through slot 2). The constructor is inline: the
// count at +0x04 is cleared, then the table is seated.
class ReferenceCounted
{
public:
    ReferenceCounted() : RefCount(0) {}
    // FUNCTION: GAMEMD 0x65D660 (decl; reloc)
    virtual ~ReferenceCounted();
    virtual void vf_1();
    virtual void vf_2();

    long RefCount;   // +0x04
};
GG_STATIC_ASSERT(offsetof(ReferenceCounted, RefCount) == 0x04);

#endif  // GG_MATCH_NETWORK_WDT_RC_PTR_H
