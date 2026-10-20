// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly), cross-checked against YRpp
//   AbstractClass.h `struct StorageClass` (consult-only; reconfirmed here).
//
// StorageClass — the 16-byte per-object Tiberium store (4 floats, one per
// Tiberium type). Base of every harvester/refinery/silo's stored value.
#ifndef GG_MATCH_ECONOMY_STORAGE_CLASS_H
#define GG_MATCH_ECONOMY_STORAGE_CLASS_H

#include <stddef.h>  // offsetof  (VC6-compatible; <cstddef> is fine too)
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// StorageClass  (sizeof = 0x10)
//
// Confirmed from 0x6C9600 (StorageClass::GetTotalValue): the function walks
// `this` as four contiguous 4-byte floats (ESI advances by 4, EBX counts 4),
// FLD float[ESI] / FCOMP float[0x7E1748(=0.0)] per element. YRpp names them
// Tiberium1..4; declared in exact retail order.
// ---------------------------------------------------------------------------
struct StorageClass
{
    // Declared ascending by retail address (reccmp/isle TU discipline).
    int   GetTotalValue() const;                     // GAMEMD 0x6C9600 __thiscall
    float GetTotalAmount() const;                    // GAMEMD 0x6C9650 __thiscall
    float GetAmount(int index) const;                // GAMEMD 0x6C9680 __thiscall
    float AddAmount(float amount, int index);        // GAMEMD 0x6C9690 __thiscall
    float RemoveAmount(float amount, int index);     // GAMEMD 0x6C96B0 __thiscall

    float Tiberium1;  // +0x00
    float Tiberium2;  // +0x04
    float Tiberium3;  // +0x08
    float Tiberium4;  // +0x0C
};

GG_STATIC_ASSERT(offsetof(StorageClass, Tiberium1) == 0x00);
GG_STATIC_ASSERT(offsetof(StorageClass, Tiberium2) == 0x04);
GG_STATIC_ASSERT(offsetof(StorageClass, Tiberium3) == 0x08);
GG_STATIC_ASSERT(offsetof(StorageClass, Tiberium4) == 0x0C);
GG_STATIC_ASSERT(sizeof(StorageClass) == 0x10);

#endif  // GG_MATCH_ECONOMY_STORAGE_CLASS_H
