// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x526CC0: the section index lives at `this+0x28`
//   (`ADD ESI,0x28`), its entry count at `[ESI+0x4]` and its cached node at
//   `[ESI+0x10]` (stored after CALL 0x52B620, the node search); CALL 0x52B600
//   (byte result) and CALL 0x52B430 (returns a pointer to the section
//   pointer) both take the address of the CRC; the CRC engine is three zeroed
//   dwords fed through 0x4A1DE0 after an inlined strlen (`REPNE SCASB`). The
//   found section's key count is `[EAX+0x30]` and its entry list head is
//   `[EAX+0x18]`; an entry is walked through `[EAX+0x4]` (next) with
//   `[EAX+0x8]` (prev) tested non-null and its name read at `[EAX+0xC]`.
//   Same index model as match/platform/ccini_class_key_count_methods.h, but
//   here the archive probe and the fetch are out of line. Method name from
//   YRpp (consult-only; name only).
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_KEY_NAME_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_KEY_NAME_METHODS_H

#include <stddef.h>
#include "../_layout/ini_nodes.h"
#include <string.h>
#include "../_rt/gg_static_assert.h"

// The CRC engine: running CRC, staging word, staging index. Constructed
// inline (three zero stores); the block feed is out of line.
struct CRC_00526CC0
{
    int CRC;       // +0x0000
    int Staging;   // +0x0004
    int Index;     // +0x0008

    CRC_00526CC0()
    {
        this->CRC     = 0;
        this->Staging = 0;
        this->Index   = 0;
    }

    // FUNCTION: GAMEMD 0x4A1DE0 (decl; reloc) -- feed a block, return the CRC.
    int operator()(const void* data, int length);
};
GG_STATIC_ASSERT(offsetof(CRC_00526CC0, Staging) == 0x04);
GG_STATIC_ASSERT(offsetof(CRC_00526CC0, Index) == 0x08);
GG_STATIC_ASSERT(sizeof(CRC_00526CC0) == 0x0C);

// A node of the section index: the CRC of the section name and the section.
struct IndexNode_00526CC0
{
    int                  ID;      // +0x0000
    INIClass::INISection* Data;    // +0x0004
};
GG_STATIC_ASSERT(sizeof(IndexNode_00526CC0) == 0x08);

// Typed call/read view of the CRC-keyed section index.
struct Index_00526CC0
{
    IndexNode_00526CC0* IndexTable;   // +0x0000
    int                 IndexCount;   // +0x0004
    int                 IndexSize;    // +0x0008
    char                IsSorted;     // +0x000C
    char                _pad00D[3];   // +0x000D
    IndexNode_00526CC0* Archive;      // +0x0010

    // FUNCTION: GAMEMD 0x52B600 (decl; reloc) -- is the cached node this id?
    bool IsArchiveSame(const int& id);
    // FUNCTION: GAMEMD 0x52B620 (decl; reloc) -- binary-search the table.
    IndexNode_00526CC0* SearchForNode(const int& id);
    // FUNCTION: GAMEMD 0x52B430 (decl; reloc) -- fetch the section by id.
    INIClass::INISection* const& FetchIndex(const int& id);

    // Both inline wrappers take the id BY VALUE: retail copies the CRC out of
    // its register into the section parameter's home slot before each of the
    // by-reference calls, i.e. each expansion has its own `id` copy.
    int IsPresent(int id)
    {
        if (this->IndexCount == 0)
            return 0;
        if (this->IsArchiveSame(id))
            return 1;
        IndexNode_00526CC0* node = this->SearchForNode(id);
        if (node == 0)
            return 0;
        this->Archive = node;
        return 1;
    }

    INIClass::INISection* const& operator[](int id)
    {
        return this->FetchIndex(id);
    }
};
GG_STATIC_ASSERT(offsetof(Index_00526CC0, IndexCount) == 0x04);
GG_STATIC_ASSERT(offsetof(Index_00526CC0, Archive) == 0x10);
GG_STATIC_ASSERT(sizeof(Index_00526CC0) == 0x14);

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_KEY_NAME_METHODS_H
