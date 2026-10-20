// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and global addresses read off the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI at 0x53D310 and 0x5FFFA0. Names cross-checked against
//   YRpp IonBlastClass.h / SpotlightClass.h (consult-only, no LICENSE).
//
// Two per-frame sweeps over global effect arrays. They are byte-for-byte the
// same shape — count into a descending index, then a reload of the Items base
// on every iteration (the element call may reallocate or remove entries, so the
// compiler cannot cache it) — differing only in their array and callee.
//
// NAMING RECONCILED: `SpotlightClass` and its `SpotlightArray` registry are
// now defined once, canonically, in match/renderer/shadow_block_list_methods.h
// (which also matches the 0x5FF250/0x5FF2D0 ctor/dtor and the 0x5FF420
// gradient-cache builder for the same class) rather than re-declared here.
#ifndef GG_MATCH_RENDERER_EFFECT_ARRAY_UPDATE_METHODS_H
#define GG_MATCH_RENDERER_EFFECT_ARRAY_UPDATE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector_class.h"
#include "shadow_block_list_methods.h"

struct IonBlastClass
{
    void Update();                 // GAMEMD 0x53CBE0 __thiscall (declared; reloc)
    static void __fastcall UpdateAll();   // GAMEMD 0x53D310
};

// GLOBAL: GAMEMD 0x00AA0118 — IonBlastClass::Array. The sweep reads Items from
// 0x00AA011C (+0x04) and Count from 0x00AA0128 (+0x10), which pins the base.
extern DynamicVectorClass IonBlastArray;

#endif  // GG_MATCH_RENDERER_EFFECT_ARRAY_UPDATE_METHODS_H
