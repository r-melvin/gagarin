// Provenance: own-binary-via-Ghidra
//
// Locates a file first as given and then under each entry of the search-path
// list at 0x89E410. On success the found name is copied back over the
// caller's buffer and the find handle is kept open in 0x81C8EC (the previous
// one is closed first).
//
// LIBRARY: IAT 0x7E1208 KERNEL32!FindFirstFileA, 0x7E1300 KERNEL32!FindClose.

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/cd_search_path.h"

typedef void* HANDLE;

struct FindData
{
    unsigned long Attributes;      // +0x000
    char          unknown_004[0x28];
    char          FileName[260];   // +0x02C
    char          AltName[14];     // +0x130
    char          unknown_13E[2];
};
GG_STATIC_ASSERT(offsetof(FindData, FileName) == 0x2C);
GG_STATIC_ASSERT(sizeof(FindData) == 0x140);   // frame 0x244 = 0x104 path + 0x140

extern "C" __declspec(dllimport) HANDLE __stdcall FindFirstFileA(char const* name, FindData* data);
extern "C" __declspec(dllimport) int __stdcall FindClose(HANDLE handle);

// GLOBAL: GAMEMD 0x81C8EC -- open find handle, -1 when none.
extern HANDLE DAT_0081C8EC;

// FUNCTION: GAMEMD 0x47AF70
bool __fastcall FUN_0047af70(char* name)
{
    if (name == 0)
    {
        return false;
    }
    if (DAT_0081C8EC != (HANDLE)-1)
    {
        FindClose(DAT_0081C8EC);
        DAT_0081C8EC = (HANDLE)-1;
    }
    char path[0x104];
    FindData data;
    strcpy(path, name);
    HANDLE handle = FindFirstFileA(path, &data);
    if (handle != (HANDLE)-1 && !(data.Attributes & 0x116))
    {
        strcpy(name, data.FileName);
        DAT_0081C8EC = handle;
        return true;
    }
    for (SearchPath_0047AE10* entry = DAT_0089E410; entry != 0; entry = entry->Next)
    {
        strcpy(path, entry->Path);
        strcat(path, name);
        handle = FindFirstFileA(path, &data);
        if (handle != (HANDLE)-1 && !(data.Attributes & 0x116))
        {
            strcpy(name, data.FileName);
            DAT_0081C8EC = handle;
            return true;
        }
    }
    return false;
}
