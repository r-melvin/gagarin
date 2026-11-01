// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x4DA0E0: the byte `MOV byte ptr [EDI+0x6B1],1/0`, the
//   NavQueue vector `LEA ESI,[EDI+0x5AC]` with its Capacity `[EDI+0x5B4]`,
//   Count `[EDI+0x5BC]`, IsAllocated `MOV AL,[ESI+0xD]`, CapacityIncrement
//   `[ESI+0x14]`, Items `[ESI+0x4]` and Resize `CALL [EDX+0x8]` (the
//   inlined DynamicVectorClass::AddItem), Destination `[EDI+0x5A4]`, the
//   virtuals `CALL [EAX+0x184]` (no args, compared with 5) and
//   `CALL [EDX+0x484]` (pushed 0, 1), the link accessor CALL 0x65AD30 with a
//   pushed 0, the link's `CALL [EDX+0x2C]` (WhatAmI, compared with 6), its
//   type at `[ESI+0x520]` and the type byte `[EAX+0x16BD]`. All FootClass
//   offsets agree with match/_layout/foot_class.h, which is included. Method
//   name from YRpp (name only).
#ifndef GG_MATCH_MOVEMENT_FOOT_CLASS_NAV_LIST_METHODS_H
#define GG_MATCH_MOVEMENT_FOOT_CLASS_NAV_LIST_METHODS_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "_layout/foot_class.h"
#include "_layout/building_class.h"   // the radio link tested as a building   // FootClass: Destination @0x5A4, NavQueue @0x5AC, unknown_bool_6B1

#include "vector_class_operations.h"   // DynamicVectorClass::AddItem / Delete, expanded inline

#endif  // GG_MATCH_MOVEMENT_FOOT_CLASS_NAV_LIST_METHODS_H
