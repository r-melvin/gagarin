// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. The same four-character
//   tagged chunk list as 0x625EA0 / 0x625F60 in ownrdraw.cpp: these two copy a chunk's string or
//   bytes out instead of one word.
//
// Address index: 0x625EF0 0x625FB0

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

struct ChunkNode_00625EF0
{
    char               Tag[4];       // +0x00
    unsigned short     unknown_04;
    unsigned short     Size;         // +0x06
    const char*        Data;         // +0x08
    ChunkNode_00625EF0* Next;        // +0x0C
};
GG_STATIC_ASSERT(offsetof(ChunkNode_00625EF0, Size) == 0x06);
GG_STATIC_ASSERT(offsetof(ChunkNode_00625EF0, Next) == 0x0C);

struct ChunkList_00625EF0
{
    int                 unknown_00;
    ChunkNode_00625EF0* First;       // +0x04

    ChunkNode_00625EF0* Find(const char* tag)
    {
        for (ChunkNode_00625EF0* node = First; node != 0; node = node->Next) {
            if (strncmp(tag, node->Tag, 4) == 0) {
                return node;
            }
        }
        return 0;
    }
    bool CopyString(const char* tag, char* out);
    bool CopyBytes(const char* tag, void* out, unsigned int* size);
};
GG_STATIC_ASSERT(offsetof(ChunkList_00625EF0, First) == 0x04);

// FUNCTION: GAMEMD 0x625EF0
// Copy the string held by the chunk with the given tag; false when there is none.
bool ChunkList_00625EF0::CopyString(const char* tag, char* out)
{
    ChunkNode_00625EF0* node = Find(tag);
    if (node != 0) {
        strcpy(out, node->Data);
    }
    return node ? true : false;
}

// FUNCTION: GAMEMD 0x625FB0
// Copy up to *size bytes of the chunk with the given tag and report its full size.
bool ChunkList_00625EF0::CopyBytes(const char* tag, void* out, unsigned int* size)
{
    ChunkNode_00625EF0* node = Find(tag);
    if (node != 0) {
        int count = *size;
        if (node->Size < count) {
            count = node->Size;
        }
        memcpy(out, node->Data, count);
        *size = node->Size;
    }
    return node ? true : false;
}
