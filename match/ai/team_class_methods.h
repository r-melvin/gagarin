// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/convention derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x6EC3A0), cross-checked
//   against YRpp (every
//   offset/slot reconfirmed below from the disassembly).
//
// TeamClass — an AI strike team (canonical definition: _layout/team_class.h).
#ifndef GG_MATCH_AI_TEAM_CLASS_METHODS_H
#define GG_MATCH_AI_TEAM_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/foot_class.h"   // NextTeamMember @0x5D8, IsScanLimited @0x688, slot 242


// TeamClass itself lives in the canonical _layout/team_class.h.
#include "../_layout/team_class.h"

#endif // GG_MATCH_AI_TEAM_CLASS_METHODS_H
