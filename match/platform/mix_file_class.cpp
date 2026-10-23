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

#include "../_layout/sorted_tree_node.h"

extern SortedTreeNode* g_FileCacheRoot; // GLOBAL: GAMEMD 0x00ABF00C

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

    SortedTreeNode* found = 0;
    SortedTreeNode* node  = g_FileCacheRoot;
    while (node)
    {
        if (node->Key == crc && node->Value != 0)
        {
            found = node;
            break;
        }
        if (node->Key < crc) node = node->High;
        else                 node = node->Low;
    }
    if (found)
        return found->Value;

    // ---- cache miss: probe the file on a stack CCFileClass ----
    CCFileClass file(name);
    if (!file.Exists(false))
        return 0;

    SortedTreeNode* fresh = new SortedTreeNode;
    fresh->Key = crc;
    SortedTreeNode* p = g_FileCacheRoot;
    if (p == 0)
    {
        g_FileCacheRoot = fresh;
        fresh->Low = 0;
        fresh->High = 0;
    }
    else
    {
        fresh->SortedTreeInsert(p->Key < crc ? &p->High : &p->Low);
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
