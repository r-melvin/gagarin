// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Engine-wide singletons and flags in the 0x87E000 data block: audio switch, critical sections, resource registry, logic, surface sizes.
#ifndef GG_MATCH_ENGINE_CORE_GLOBALS_H
#define GG_MATCH_ENGINE_CORE_GLOBALS_H

struct Obj_00407520;


// GLOBAL: GAMEMD 0x87E2A0
extern void* g_AudioEnabled;
// GLOBAL: GAMEMD 0x87E728
extern void* DAT_0087E728;
// GLOBAL: GAMEMD 0x87F8E0
extern int g_SurfaceHeight;
// GLOBAL: GAMEMD 0x87E2A8 -- free pool of event blocks.
extern Obj_00407520* DAT_0087E2A8;
// GLOBAL: GAMEMD 0x87F6C0
extern void* ParticleDrawContext;
// GLOBAL: GAMEMD 0x880994
extern int OverlayParkedValue;
// GLOBAL: GAMEMD 0x88099A
extern bool DAT_0088099A;
// GLOBAL: GAMEMD 0x88099B
extern bool DAT_0088099B;
// GLOBAL: GAMEMD 0x88099C
extern bool DAT_0088099C;

#endif  // GG_MATCH_ENGINE_CORE_GLOBALS_H
