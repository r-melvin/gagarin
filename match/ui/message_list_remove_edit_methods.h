// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and offsets read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x5D4390.
//
// Note the IsEditing flag is read again at 0x5D43BC after being cleared at
// 0x5D43A2. That is *not* a dead test: the Unlock call at 0x778170 sits between
// them, so the compiler must assume the flag can change and reloads it. This is
// the case §4.8 explicitly does not cover.
#ifndef GG_MATCH_UI_MESSAGE_LIST_REMOVE_EDIT_METHODS_H
#define GG_MATCH_UI_MESSAGE_LIST_REMOVE_EDIT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A paired call around the edit teardown. Named lock/unlock for readability,
// but the pairing is not an RAII lock: retail's not-editing path skips the
// second call entirely, so whatever they guard is conditional.
void MessageListLock();     // GAMEMD 0x7781A0 (declared; reloc)
void MessageListUnlock();   // GAMEMD 0x778170 (declared; reloc)

#include "message_list_class_methods.h"
#endif
