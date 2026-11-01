// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Window handles and online-lobby lists in the 0xB30000 data block.
#ifndef GG_MATCH_PLATFORM_ONLINE_GLOBALS_H
#define GG_MATCH_PLATFORM_ONLINE_GLOBALS_H
#include "wdt_rc_ptr_base.h"

class WDTState;


// GLOBAL: GAMEMD 0xB77F58
extern rc_ptr<WDTState> DAT_00B77F58;

#endif  // GG_MATCH_PLATFORM_ONLINE_GLOBALS_H
