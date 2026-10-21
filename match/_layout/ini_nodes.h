// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// TypeDescriptors 0x825AF0/0x825B40 name .?AUINIEntry@INIClass@@ and
// .?AUINISection@INIClass@@. The retail constructor 0x52AF00 and teardown
// bodies 0x52AAF0/0x52AB80 pin the accessed members and their widths below.
// Unknown complete virtual declarations and original source-file grouping
// remain separate recovery work; explicit inherited vptr views are retained.
#ifndef GG_MATCH_LAYOUT_INI_NODES_H
#define GG_MATCH_LAYOUT_INI_NODES_H
#include "ini_class.h"
struct INIComment
{
    char*       Comment;   // +0x00
    INIComment* Next;      // +0x04
};

GG_STATIC_ASSERT(offsetof(INIComment, Next) == 0x04 && sizeof(INIComment) == 0x08);

// ---------------------------------------------------------------------------
// INIClass::INIEntry - one `key=value` line. The seven-dword tail is pinned by
// the constructor at 0x52AF00, which takes seven arguments (`RET 0x1C`) and
// lands them at +0x0C, +0x10, +0x14, +0x18, +0x1C, +0x20 and +0x24; the fifth
// argument going to +0x24 while the sixth and seventh go to +0x1C and +0x20 is
// what proves the cursor members are declared in the order below and
// initialised out of order by the member-initialiser list.
// ---------------------------------------------------------------------------
struct INIClass::INIEntry : public Node<INIClass::INIEntry*>
{
    char*       Entry;              // +0x0C
    char*       Value;              // +0x10
    INIComment* Comments;           // +0x14
    char*       CommentString;      // +0x18
    int         PreIndentCursor;    // +0x1C
    int         PostIndentCursor;   // +0x20
    int         CommentCursor;      // +0x24

    // FUNCTION: GAMEMD 0x52AF00
    INIEntry(char* entry, char* value, INIComment* comments, char* commentstring,
             int commentcursor, int preindentcursor, int postindentcursor);

    // FUNCTION: GAMEMD 0x52AAF0
    void DestroyEntry();
    // FUNCTION: GAMEMD 0x52AD50  vtable 0x7EB734 slot 0
    void* DeletingDestructor(unsigned int flags);
};

GG_STATIC_ASSERT(offsetof(INIClass::INIEntry, Entry)            == 0x0C &&
                 offsetof(INIClass::INIEntry, Value)            == 0x10 &&
                 offsetof(INIClass::INIEntry, Comments)         == 0x14 &&
                 offsetof(INIClass::INIEntry, CommentString)    == 0x18 &&
                 offsetof(INIClass::INIEntry, PreIndentCursor)  == 0x1C &&
                 offsetof(INIClass::INIEntry, PostIndentCursor) == 0x20 &&
                 offsetof(INIClass::INIEntry, CommentCursor)    == 0x24 &&
                 sizeof(INIClass::INIEntry) == 0x28);

// ---------------------------------------------------------------------------
// INIClass::INISection - one bracketed section. The destructor at 0x52AB80
// pins every offset: the name freed from +0x0C, the entry list worked at
// +0x10 (its head sentinel's forward link at +0x18), the entry index freed and
// zeroed across +0x2C..+0x3C, and the comment chain drained from +0x40.
// ---------------------------------------------------------------------------
struct INIClass::INISection : public Node<INIClass::INISection*>
{
    char*         Section;      // +0x0C
    // RTTI table 0x7EB744; explicit inherited vptr view is retained.
    List<INIEntry*> EntryList;    // +0x10
    IndexClassRaw EntryIndex;   // +0x2C
    INIComment*   Comments;     // +0x40

    INIEntry* FirstEntry() const { return (INIEntry*)EntryList.First(); }

    // FUNCTION: GAMEMD 0x52AB80
    void DestroySection();
};

GG_STATIC_ASSERT(offsetof(INIClass::INISection, Section)    == 0x0C &&
                 offsetof(INIClass::INISection, EntryList)  == 0x10 &&
                 offsetof(INIClass::INISection, EntryIndex) == 0x2C &&
                 offsetof(INIClass::INISection, Comments)   == 0x40 &&
                 sizeof(INIClass::INISection) == 0x44);

GG_STATIC_ASSERT(sizeof(List<INIClass::INIEntry*>) == 0x1C);

#endif
