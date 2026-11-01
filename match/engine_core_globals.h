// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Engine-wide singletons and flags in the 0x87E000 data block: audio switch, critical sections, resource registry, logic, surface sizes.
#ifndef GG_MATCH_ENGINE_CORE_GLOBALS_H
#define GG_MATCH_ENGINE_CORE_GLOBALS_H

// GLOBAL: GAMEMD 0x87E2A0
extern void* g_AudioEnabled;
// GLOBAL: GAMEMD 0x87E728
extern void* DAT_0087E728;
// GLOBAL: GAMEMD 0x87F8E0
extern int g_SurfaceHeight;

#endif  // GG_MATCH_ENGINE_CORE_GLOBALS_H
