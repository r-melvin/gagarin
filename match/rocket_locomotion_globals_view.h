// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001 entry-origin reads; address-local views only.
#ifndef GG_ROCKET_LOCOMOTION_GLOBALS_VIEW_H
#define GG_ROCKET_LOCOMOTION_GLOBALS_VIEW_H
#include "rocket_locomotion_views.h"
#include "rocket_locomotion_globals.h"
// GLOBAL: GAMEMD 0x008871E0 (pointer storage; target used through RocketRulesView prefix).
struct RocketRulesView;
extern RocketRulesView* DAT_008871E0;
// GLOBAL: GAMEMD 0x008399AC (string-pointer slot).
extern const char* DAT_008399AC;
// GLOBAL: GAMEMD 0x008399B0 (string-pointer slot).
extern const char* DAT_008399B0;
// GLOBAL: GAMEMD 0x008B4150 (array prefix: item pointer at +4).
extern RocketAnimTypeArray DAT_008B4150;
// GLOBAL: GAMEMD 0x00A8ED84 (frame counter read by timer methods).
extern int DAT_00A8ED84;
#endif
