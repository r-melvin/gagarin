// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2
//   Bodies matched against retail gamemd.exe v1.001 at each address below.
//
// Mounted-MIX list lookups: walk the List<MixFileClass*> at 0xABEFD8 and compare
// each entry's base file name with the requested one.
//   0x5B4270  drop a file from the CRC-keyed file cache
//   0x5B3E90  release the cached data of the named mix
//   0x5B4350  find the named mix

#include <stdlib.h>
#include <string.h>
#include "mix_file_class.h"
#include "../core/mix_file_list_00abefd8.h"
#include "../_layout/crc_00476d80.h"
#include "../_layout/sorted_tree_node.h"

extern SortedTreeNode* g_FileCacheRoot; // GLOBAL: GAMEMD 0x00ABF00C

// LIBRARY: GAMEMD 0x7CB673 (decl; reloc) - CRT _splitpath.
// LIBRARY: GAMEMD 0x7C9FF0 (decl; reloc) - CRT _makepath.
// LIBRARY: GAMEMD 0x7C8D20 (decl; reloc) - CRT _stricmp.
// LIBRARY: GAMEMD 0x7C8B3D (decl; reloc) - operator delete.

// The list-walk guard: a real node has both links set (the sentinels do not).
static __forceinline bool IsListNode(const MixFileClass* mix)
{
    return mix != 0 && mix->NextNode != 0 && mix->PrevNode != 0;
}

// FUNCTION: GAMEMD 0x5B4350
// Returns the mounted mix whose file name matches, or 0.
MixFileClass* FUN_005B4350(const char* name)
{
    MixFileClass* mix = (MixFileClass*)MixFileListHolder_00ABEFD8::DAT_00ABEFD8.FirstNode.NextNode;
    for (; IsListNode(mix); mix = mix->NextNode) {
        char fname[256];
        char ext[256];
        char path[260];
        _splitpath(mix->FileName, 0, 0, fname, ext);
        _makepath(path, 0, 0, fname, ext);
        if (_stricmp(path, name) == 0)
            return mix;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x5B3E90
// Frees the cached data of the named mix; false when no such mix is mounted.
bool FUN_005B3E90(const char* name)
{
    MixFileClass* mix = FUN_005B4350(name);
    if (mix != 0) {
        if (mix->CachedData != 0 && mix->IsLoaded)
            delete mix->CachedData;
        mix->CachedData = 0;
        mix->IsLoaded = false;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x5B4270
// Clears the cached value for a file name in the CRC-keyed file cache.
void __fastcall FUN_005B4270(char* name)
{
    char buf[0x101];
    strcpy(buf, name);
    _strupr(buf);

    CRC_00476D80 eng;
    eng.CRC = 0; eng.Staging = 0; eng.Index = 0;
    int crc = eng.FUN_004A1DE0(buf, strlen(buf));

    for (SortedTreeNode* node = g_FileCacheRoot; node; ) {
        if (node->Key == crc && node->Value != 0) {
            node->Value = 0;
            return;
        }
        if (node->Key < crc)
            node = node->High;
        else
            node = node->Low;
    }
}
