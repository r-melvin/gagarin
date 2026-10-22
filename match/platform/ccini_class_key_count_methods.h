// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x526960: the section index lives at `this+0x28`
//   (`ADD ESI,0x28`), its entry count at `[ESI+0x4]` and its cached node at
//   `[ESI+0x10]`; a node is `{ID, Data}` (`CMP [EAX],EDI` / `ADD ESI,4`);
//   the miss path reads the static default at 0xB7882C; the found section's
//   key count is `[ESI+0x30]`. The CRC engine is three zeroed dwords on the
//   stack fed through 0x4A1DE0 (same shape as ccini_class_crc_methods.h),
//   and the node search is 0x52B620 taking a pointer to the key. Method name
//   from YRpp (name only, no text copied).
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_KEY_COUNT_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_KEY_COUNT_METHODS_H

#include <stddef.h>
#include "../_layout/ini_nodes.h"
#include "../_layout/ini_index_defaults.h"
#include <string.h>
#include "../_rt/gg_static_assert.h"

// The CRC engine: running CRC, staging word, staging index. Constructed
// inline (three zero stores); the block feed is out of line.
struct CRC_00526960
{
    int CRC;       // +0x0000
    int Staging;   // +0x0004
    int Index;     // +0x0008

    CRC_00526960()
    {
        this->CRC     = 0;
        this->Staging = 0;
        this->Index   = 0;
    }

    // FUNCTION: GAMEMD 0x4A1DE0 (decl; reloc) -- feed a block, return the CRC.
    int operator()(const void* data, int length);
};
GG_STATIC_ASSERT(offsetof(CRC_00526960, Staging) == 0x04);
GG_STATIC_ASSERT(offsetof(CRC_00526960, Index) == 0x08);
GG_STATIC_ASSERT(sizeof(CRC_00526960) == 0x0C);

// A node of the section index: the CRC of the section name and the section.
struct IndexNode_00526960
{
    int                  ID;      // +0x0000
    INIClass::INISection* Data;    // +0x0004
};
GG_STATIC_ASSERT(offsetof(IndexNode_00526960, Data) == 0x04);
GG_STATIC_ASSERT(sizeof(IndexNode_00526960) == 0x08);

// GLOBAL: GAMEMD 0xB7882C -- the index's static "nothing" value, handed back
// by reference when the key is absent.

// Typed call/read view of the CRC-keyed section index. IsPresent and
// operator[] are the inline bodies retail expands twice in GetKeyCount.
struct Index_00526960
{
    IndexNode_00526960* IndexTable;   // +0x0000
    int                 IndexCount;   // +0x0004
    int                 IndexSize;    // +0x0008
    char                IsSorted;     // +0x000C
    char                _pad00D[3];   // +0x000D
    IndexNode_00526960* Archive;      // +0x0010

    // FUNCTION: GAMEMD 0x52B620 (decl; reloc) -- binary-search the table.
    IndexNode_00526960* SearchForNode(const int& id);

    int IsPresent(int id)
    {
        if (this->IndexCount == 0)
            return 0;
        if (this->Archive != 0 && this->Archive->ID == id)
            return 1;
        IndexNode_00526960* node = this->SearchForNode(id);
        if (node == 0)
            return 0;
        this->Archive = node;
        return 1;
    }

    INIClass::INISection* const& operator[](int id)
    {
        if (this->IsPresent(id))
            return this->Archive->Data;
        return DAT_00B7882C;
    }
};
GG_STATIC_ASSERT(offsetof(Index_00526960, IndexCount) == 0x04);
GG_STATIC_ASSERT(offsetof(Index_00526960, Archive) == 0x10);
GG_STATIC_ASSERT(sizeof(Index_00526960) == 0x14);

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_KEY_COUNT_METHODS_H
