// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Shared reconstruction storage for the six DWORD cells read by pixel helpers.
// Writer 0x4BA770 stores the complete cells, with position/loss loop bounds
// 16/8. The pinned PE covers all 24 bytes as virtual zero-fill.
// The original declaration form and source filename remain unknown.
#include "pixel_shift_view.h"

extern "C" {
// GLOBAL: GAMEMD 0x8A0DD0
BTranslucentPixelFormat gg_b_translucent_pixel_format;
}
