// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// One definition for the shared frame-counter storage. Retail .data maps
// 0x812000..0xB79BE4 with only 0x6C000 bytes backed by the file; 0xA8ED84
// is in the loader-zeroed tail. Runtime writes are recovered separately.
#include "frame_counter.h"

// GLOBAL: GAMEMD 0xA8ED84
int CurrentFrame;
