// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Inline bodies of the no-initialisation constructors VoxelAnimClass::Load (0x74A970) expands in place:
//   ObjectClass starts its no-init chain (call 0x5F3B50), the four vtables are stored, and neither the
//   bounce state nor its two quaternions are touched. Kept out of the class headers: a body there shifts
//   the compiler's internal counters in every includer.
#ifndef GG_MATCH_LAYOUT_VOXEL_ANIM_NOINIT_H
#define GG_MATCH_LAYOUT_VOXEL_ANIM_NOINIT_H

#include "voxel_anim_class.h"
#include "quaternion.h"

inline QuaternionEntry::QuaternionEntry(const AbstractNoInit&) {}
inline BounceClass::BounceClass(const AbstractNoInit& noInit) : CurrentAngle(noInit), unknown_40(noInit) {}
inline VoxelAnimClass::VoxelAnimClass(const AbstractNoInit& noInit) : ObjectClass(noInit), BounceClass(noInit) {}

#endif  // GG_MATCH_LAYOUT_VOXEL_ANIM_NOINIT_H
