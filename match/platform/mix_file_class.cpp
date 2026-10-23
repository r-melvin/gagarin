// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at the
//   addresses below). Names cross-checked against YRpp
//   (every offset/slot reconfirmed here).
//
#include "mix_file_class.h"
#include "../_layout/memory_buffer.h"
#include <stdio.h>   // sprintf
#include <string.h>  // strcpy, _strupr, strstr

#include "../_layout/crc_00476d80.h"
#include "../_layout/obj_0069e430.h"

// Cached-file index node (operator new(0x10)): left/right/key(crc)/value.
// Key @+0x8, Value @+0xC confirmed from the walk: `node[2]==crc && node[3]!=0`
// (CMP [EAX+0x8] / [EDX+... ]) and key<crc => node[1] (right @+0x4) else *node
// (left @+0x0).
struct IdxNode { IdxNode* Left; IdxNode* Right; int Key; void* Value; };
GG_STATIC_ASSERT(offsetof(IdxNode, Left) == 0);
GG_STATIC_ASSERT(offsetof(IdxNode, Right) == 4);
GG_STATIC_ASSERT(offsetof(IdxNode, Key)   == 0x08);
GG_STATIC_ASSERT(offsetof(IdxNode, Value) == 0x0C);
GG_STATIC_ASSERT(sizeof(IdxNode) == 0x10);   // operator new(0x10)
extern IdxNode* g_FileCacheRoot;             // GLOBAL: GAMEMD 0x00ABF00C
void IdxInsert(IdxNode* node, IdxNode** parentSlot);  // FUN_005B3FF0

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x5B40B0   MixFileClass::Retrieve  (__fastcall static)
//
// Look a file up by upper-cased name in the CRC-keyed file cache. On a hit,
// return the cached pointer. On a miss, probe the file; if present, insert a
// cache node and build the appropriate file object; otherwise return 0.
//
// Native cache-miss file lifetime is represented by an automatic CCFileClass.
// Child-slot addresses use ordinary typed pointers; no cursor steering casts.
// This remains a partial: register allocation and one MOV differ from retail.
void* MixFileClass_Retrieve(char* name, bool force)
{
    char buf[0x101];                 // uppercase name scratch
    strcpy(buf, name);               // intrinsic: repne scasb + rep movs
    _strupr(buf);

    CRC_00476D80 eng;
    eng.CRC = 0; eng.Staging = 0; eng.Index = 0;
    int crc = eng.FUN_004A1DE0(buf, strlen(buf));

    IdxNode* found = 0;
    IdxNode* node  = g_FileCacheRoot;
    while (node)
    {
        if (node->Key == crc && node->Value != 0)
        {
            found = node;
            break;
        }
        if (node->Key < crc) node = node->Right;
        else                 node = node->Left;
    }
    if (found)
        return found->Value;

    // ---- cache miss: probe the file on a stack CCFileClass ----
    CCFileClass file(name);
    if (!file.Exists(false))
        return 0;

    IdxNode* fresh = new IdxNode;
    fresh->Key = crc;
    IdxNode* p = g_FileCacheRoot;
    if (p == 0)
    {
        g_FileCacheRoot = fresh;
        fresh->Left = 0;
        fresh->Right = 0;
    }
    else
    {
        IdxInsert(fresh, p->Key < crc ? &p->Right : &p->Left);
    }

    void* value;
    if (!force && strstr(buf,
        // STRING: GAMEMD 0x81834C
        ".SHP") == 0)
        value = file.ReadWholeFile();
    else
    {
        value = new Obj_0069E430(name);
    }
    fresh->Value = value;

    return value;
}
