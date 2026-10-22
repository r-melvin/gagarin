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

// A displayed message. Slot 0 is the scalar-deleting destructor and slot +0x04
// returns the next message, so the walk is a virtual call rather than a field
// dereference.
struct MessageEntry
{
    virtual ~MessageEntry();          // +0x00
    virtual MessageEntry* GetNext();  // +0x04

    char _pad04[0x10 - 4];   // +0x04  (vptr occupies +0x00)
    int  Y;                  // +0x10
};
GG_STATIC_ASSERT(offsetof(MessageEntry, Y) == 0x10);

// The edit line, destroyed through its own virtual destructor.
struct EditLabelClass
{
    virtual ~EditLabelClass();   // +0x00
};

struct MessageListClass
{
    MessageEntry*   FirstMessage;      // +0x00
    char            _pad04[0x08 - 4];  // +0x04
    int             ListOrigin;        // +0x08
    int             RedrawCounter;     // +0x0C
    char            _pad10[0x14 - 0x10];
    int             LineHeight;        // +0x14
    char            _pad18[0x19 - 0x18];
    bool            IsEditing;         // +0x19
    bool            NeedsRedraw;       // +0x1A
    char            _pad1B[0x24 - 0x1B];
    EditLabelClass* EditLabel;         // +0x24

    void RemoveEdit();                 // GAMEMD 0x5D4390
};
GG_STATIC_ASSERT(offsetof(MessageListClass, ListOrigin)    == 0x08);
GG_STATIC_ASSERT(offsetof(MessageListClass, RedrawCounter) == 0x0C);
GG_STATIC_ASSERT(offsetof(MessageListClass, LineHeight)    == 0x14);
GG_STATIC_ASSERT(offsetof(MessageListClass, IsEditing)     == 0x19);
GG_STATIC_ASSERT(offsetof(MessageListClass, NeedsRedraw)   == 0x1A);
GG_STATIC_ASSERT(offsetof(MessageListClass, EditLabel)     == 0x24);

#endif  // GG_MATCH_UI_MESSAGE_LIST_REMOVE_EDIT_METHODS_H
