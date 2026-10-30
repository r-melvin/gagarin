// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, offsets and the layer-array base read off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x4A9720. ObjectClass's
//   LastLayer @0x94 comes from the committed P2 spine and is reconfirmed here
//   (`CMP dword ptr [ESI+0x94],-1`). The layer array's 24-byte stride is what
//   `LEA EDX,[EDI+EDI*2]` + `LEA ECX,[EDX*8+0x8A0360]` encodes — 3*8 — which is
//   exactly sizeof(DynamicVectorClass).
#ifndef GG_MATCH_UI_DISPLAY_CLASS_SUBMIT_METHODS_H
#define GG_MATCH_UI_DISPLAY_CLASS_SUBMIT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/object_class.h"

#include "../_layout/layer_class.h"
#include "input_controls/ui_display_chain.h"

#endif  // GG_MATCH_UI_DISPLAY_CLASS_SUBMIT_METHODS_H
