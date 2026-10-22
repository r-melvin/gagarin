// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4A3B40.

#include "resource_query_methods.h"

// Win32 imports reached through the IAT.
extern "C" __declspec(dllimport) HRSRC   __stdcall FindResourceA(HINSTANCE hModule, const char* lpName, const char* lpType);
extern "C" __declspec(dllimport) HGLOBAL __stdcall LoadResource(HINSTANCE hModule, HRSRC hResInfo);
extern "C" __declspec(dllimport) void*   __stdcall LockResource(HGLOBAL hResData);

// FUNCTION: GAMEMD 0x4A3B40  Unsorted::GetResource (__fastcall)
// The id is narrowed to a word and passed as a MAKEINTRESOURCE pseudo-pointer.
// Both early exits are bare RETs: EAX already holds the null the caller gets.
void* Unsorted_GetResource(int id, const char* type)
{
    HRSRC found = FindResourceA(GameInstance, (const char*)(id & 0xFFFF), type);
    if (found == 0)
        return 0;

    HGLOBAL loaded = LoadResource(GameInstance, found);
    if (loaded == 0)
        return 0;

    return LockResource(loaded);
}
