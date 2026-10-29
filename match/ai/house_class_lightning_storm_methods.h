// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x509E00: CALL 0x53A100 (a byte global read, no receiver),
//   `[ESI+0x5600]` compared with -1, the CellStruct at `[ESI+0x54F0]` compared
//   word-wise with the sentinel at 0xA8EF98/0xA8EF9A, `[ESI+0x54EC]` compared
//   with 1 and otherwise passed to 0x50D170 (PickTargetByType) where 0x50CBF0
//   (PickIonCannonTarget) takes only the out buffer, the super-weapon vector
//   at `[ESI+0x254]` whose slot `[EAX+0x10]` (FindItemIndex) receives the
//   *address* of the parameter slot (`LEA EDX,[ESP+0x14]`), and CALL 0x4FAE50
//   (Fire_SW) taking the index and the cell by pointer. Names are YRpp's
//   HouseClass::Fire_LightningStorm / PickIonCannonTarget / PickTargetByType /
//   Fire_SW (names only).
#ifndef GG_MATCH_AI_HOUSE_CLASS_LIGHTNING_STORM_METHODS_H
#define GG_MATCH_AI_HOUSE_CLASS_LIGHTNING_STORM_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/house_class.h"

// FUNCTION: GAMEMD 0x53A100 (decl; reloc) — a global byte flag, read without a
// receiver (`MOV AL,[0xA9FAB4]; RET`).
bool __cdecl FUN_0053A100();

#endif  // GG_MATCH_AI_HOUSE_CLASS_LIGHTNING_STORM_METHODS_H
