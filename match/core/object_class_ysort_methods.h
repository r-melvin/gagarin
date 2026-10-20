// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 via the local Ghidra CLI
//   (virtual-dispatch disassembly at 0x5F6BD0). Signature cross-checked against
//   YRpp ObjectClass.h (consult-only, no LICENSE; every offset reconfirmed
//   numerically from the disasm below).
//
// ObjectClass::GetYSort layered on the committed instance-side spine
// (../_layout/object_class.h). The single method dispatches twice through the
// PRIMARY (offset-0) vtable slot at byte offset 0xAC:
//     MOV EAX,[ESI]; ... CALL [EAX+0xAC]     @0x5F6BE0 / 0x5F6BF1
// That slot is the const, single-CoordStruct*-arg, CoordStruct*-returning
// coordinate accessor (YRpp ObjectClass GetTargetCoords). It returns the filled
// buffer pointer; GetYSort sums the first call's Y (+0x4) and the second call's
// X (+0x0). The spine models the four COM vptrs as plain data, so a natural C++
// virtual call cannot reach slot 0xAC; instead we dispatch through a minimal
// abstract interface (ObjCoordVCall) whose vtable places the accessor at index
// 43 (43*4 == 0xAC), reinterpret-casting `this`. This emits the exact
// `MOV reg,[this]; CALL [reg+0xAC]` __thiscall (this in ECX, buffer pushed) that
// VC6 cannot express via __thiscall (keyword reserved) or __fastcall (would
// force the buffer into EDX, not the stack).
#ifndef GG_MATCH_CORE_OBJECT_CLASS_YSORT_METHODS_H
#define GG_MATCH_CORE_OBJECT_CLASS_YSORT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/object_class.h"   // ObjectClass + CoordStruct (X@0x0, Y@0x4)

// Re-assert the CoordStruct fields the dispatch consumes (self-guards the TU).
GG_STATIC_ASSERT(offsetof(CoordStruct, X) == 0x00);
GG_STATIC_ASSERT(offsetof(CoordStruct, Y) == 0x04);

// Minimal abstract interface used solely to materialise the primary-vtable call
// at byte offset 0xAC. Indices 0..42 are dummy placeholders; the coordinate
// accessor lands at index 43 (43 * 4 == 0xAC). Never instantiated: only `this`
// reinterpret-cast through it to issue the indirect call.
struct ObjCoordVCall
{
#define GG_OBJYSORT_VF(n) virtual void _vf##n();
    GG_OBJYSORT_VF(00) GG_OBJYSORT_VF(01) GG_OBJYSORT_VF(02) GG_OBJYSORT_VF(03)
    GG_OBJYSORT_VF(04) GG_OBJYSORT_VF(05) GG_OBJYSORT_VF(06) GG_OBJYSORT_VF(07)
    GG_OBJYSORT_VF(08) GG_OBJYSORT_VF(09) GG_OBJYSORT_VF(10) GG_OBJYSORT_VF(11)
    GG_OBJYSORT_VF(12) GG_OBJYSORT_VF(13) GG_OBJYSORT_VF(14) GG_OBJYSORT_VF(15)
    GG_OBJYSORT_VF(16) GG_OBJYSORT_VF(17) GG_OBJYSORT_VF(18) GG_OBJYSORT_VF(19)
    GG_OBJYSORT_VF(20) GG_OBJYSORT_VF(21) GG_OBJYSORT_VF(22) GG_OBJYSORT_VF(23)
    GG_OBJYSORT_VF(24) GG_OBJYSORT_VF(25) GG_OBJYSORT_VF(26) GG_OBJYSORT_VF(27)
    GG_OBJYSORT_VF(28) GG_OBJYSORT_VF(29) GG_OBJYSORT_VF(30) GG_OBJYSORT_VF(31)
    GG_OBJYSORT_VF(32) GG_OBJYSORT_VF(33) GG_OBJYSORT_VF(34) GG_OBJYSORT_VF(35)
    GG_OBJYSORT_VF(36) GG_OBJYSORT_VF(37) GG_OBJYSORT_VF(38) GG_OBJYSORT_VF(39)
    GG_OBJYSORT_VF(40) GG_OBJYSORT_VF(41) GG_OBJYSORT_VF(42)
#undef GG_OBJYSORT_VF
    // index 43 -> byte offset 0xAC
    virtual CoordStruct* GetTargetCoords(CoordStruct* pCrd) const;
};

// No-data host for the method; layout identical to ObjectClass.
struct ObjectYSort : ObjectClass
{
    // FUNCTION: GAMEMD 0x5F6BD0  ObjectClass::GetYSort (__thiscall)
    int GetYSort() const;
};

#endif  // GG_MATCH_CORE_OBJECT_CLASS_YSORT_METHODS_H
