// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The voxel section source as its readers see it. FUN_007540f0 (queues one
//   section) calls 0x7564B0 with (section, frame) and reads eight corner
//   vectors at +0x40 of the record it returns. 0x7564B0 itself reads the
//   section table at +0x10 (12-byte rows, first dword = the row's first
//   record) and the record array at +0x14, stride 0xA4
//   (`LEA EDX,[EAX+EAX*4]; LEA EAX,[EAX+EDX*8]; LEA EAX,[ECX+EAX*4]`).
//   Placeholder names: no string or RTTI names these types.
#ifndef GG_MATCH_CORE_VOXEL_SECTION_SOURCE_H
#define GG_MATCH_CORE_VOXEL_SECTION_SOURCE_H

#include "../_layout/voxel_resource_data.h"
// Compatibility spelling for the former partial resource view.
typedef Obj_00755D10 VoxelSectionSource;
#endif
