// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and global addresses read off the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI at 0x53D310 and 0x5FFFA0. Names cross-checked against
//   IonBlast naming was cross-checked with YRpp.
//   SpotLight spelling follows the retail registry RTTI and direct uses
//   documented in shadow_block_list_methods.h.
//
// Two per-frame sweeps over global effect arrays. They are byte-for-byte the
// same shape — count into a descending index, then a reload of the Items base
// on every iteration (the element call may reallocate or remove entries, so the
// compiler cannot cache it) — differing only in their array and callee.
//
// NAMING RECONCILED: `SpotLightClass` and its `SpotlightArray` registry are
// now defined once, canonically, in match/renderer/shadow_block_list_methods.h
// (which also matches the 0x5FF250/0x5FF2D0 ctor/dtor). The partial
// 0x5FF420 gradient-cache builder remains a free routine, not a class method.
#ifndef GG_MATCH_RENDERER_EFFECT_ARRAY_UPDATE_METHODS_H
#define GG_MATCH_RENDERER_EFFECT_ARRAY_UPDATE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/ion_blast_class.h"
#include "shadow_block_list_methods.h"

#endif  // GG_MATCH_RENDERER_EFFECT_ARRAY_UPDATE_METHODS_H
