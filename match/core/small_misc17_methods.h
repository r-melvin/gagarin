// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC17_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC17_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A zero-argument virtual at +0x30 returning a pointer.
struct Provider_004103E0;
typedef char* (* Slot30)(Provider_004103E0*);
#define SLOT_30(p) ((*(Slot30*)(*(char**)(p) + 0x30))(p))

// FUNCTION: GAMEMD 0x4103E0 — publish the provider's buffer, skipping its
// four-byte header, and clear the companion word.
long __stdcall FUN_004103E0(Provider_004103E0* provider, void** out);

#endif  // GG_MATCH_CORE_SMALL_MISC17_METHODS_H
