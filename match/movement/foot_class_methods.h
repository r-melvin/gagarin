// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 via the local Ghidra CLI
//   (member-access + virtual-call disassembly at 0x4DF0D0 / 0x4DA1C0).
//   Signatures cross-checked against YRpp
//   (every offset reconfirmed numerically below).
//
// Two small FootClass movement methods layered on the committed instance-side
// spine (../_layout/foot_class.h). The spine models the COM vptrs as plain data
// fields, so deriving a no-data host struct adds no vtable and keeps `this` and
// every offset identical; the methods just need their own declarations to emit
// the __thiscall symbols the differ slices.
#ifndef GG_MATCH_MOVEMENT_FOOT_CLASS_METHODS_H
#define GG_MATCH_MOVEMENT_FOOT_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/foot_class.h"   // FootClass: unknown_5A0@0x5A0, Destination@0x5A4, NavQueue@0x5AC

// Re-assert the members these methods touch (self-guards this TU to the ABI).
GG_STATIC_ASSERT(offsetof(FootClass, unknown_5A0) == 0x5A0);
GG_STATIC_ASSERT(offsetof(FootClass, Destination) == 0x5A4);
GG_STATIC_ASSERT(offsetof(FootClass, NavQueue)    == 0x5AC);

// NavQueue is a DynamicVectorClass<AbstractClass*>; ClearNavigationList tail-
// calls its virtual Clear() at vtable slot +0x0C (4th virtual, vtable
// 0x7E91EC: slot0 dtor, slot1, slot2, slot3 = Clear @0x4E0190). The spine
// types NavQueue as plain data, so reach the virtual through a host vector with
// four virtuals — only the cast pointer's runtime vptr is used, no vtable is
// emitted for this helper.
struct NavVector
{
    virtual ~NavVector();      // slot 0 (offset 0x00)
    virtual void Unused1();    // slot 1 (offset 0x04)
    virtual void Unused2();    // slot 2 (offset 0x08)
    virtual void Clear();      // slot 3 (offset 0x0C)
};

// No-data host for the two methods; layout identical to FootClass.

#endif  // GG_MATCH_MOVEMENT_FOOT_CLASS_METHODS_H
