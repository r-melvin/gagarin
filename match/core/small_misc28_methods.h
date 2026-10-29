// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. Imports read from the IAT
//   thunks at 0x7E11E8 and 0x7E11EC. Not bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC28_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC28_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// KERNEL32, dllimport so the calls go indirect through the IAT.
struct CRITICAL_SECTION_ { char opaque[24]; };
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(CRITICAL_SECTION_*);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION_*);

// GLOBAL: GAMEMD 0x87E7F8 — the section guarding the worker below.
extern CRITICAL_SECTION_ DAT_0087E7F8;


#include "../_layout/obj_00407f40.h"

#endif  // GG_MATCH_CORE_SMALL_MISC28_METHODS_H
