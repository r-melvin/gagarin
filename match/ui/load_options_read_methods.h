// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Shape read off the user's retail gamemd.exe v1.001 via the local Ghidra
//   CLI at 0x67FD20: the file name arrives in ECX and the record in EDX
//   (`MOV ESI,EDX`), the storage pointer lives at `[ESP+0x04]` with the
//   64-wchar name buffer above it, the two imports are `CALL [0x7E11C4]`
//   (MultiByteToWideChar) and `CALL [0x7E15E4]` (StgOpenStorage), and the
//   interface is released through slot +0x08 with the receiver pushed
//   (`MOV ECX,[EAX]; PUSH EAX; CALL [ECX+0x8]`). The record's reader at
//   0x681840 is __thiscall with the storage pushed and its result tested as a
//   signed dword (`JGE`). Names from YRpp.
#ifndef GG_MATCH_UI_LOAD_OPTIONS_READ_METHODS_H
#define GG_MATCH_UI_LOAD_OPTIONS_READ_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A COM interface handle. Only Release (slot +0x08, __stdcall, receiver
// pushed) is dispatched here.
struct IStorage_0067FD20;
typedef unsigned long (__stdcall* ReleaseSlot_0067FD20)(IStorage_0067FD20*);
#define COM_RELEASE_0067FD20(p) \
    ((*(ReleaseSlot_0067FD20*)(*(char**)(p) + 0x08))(p))

// KERNEL32 / OLE32 imports, dllimport so the calls go indirect through the
// IAT (0x7E11C4 and 0x7E15E4).
extern "C" __declspec(dllimport) int __stdcall MultiByteToWideChar(
    unsigned int codePage, unsigned long flags, const char* src, int srcLen,
    unsigned short* dst, int dstLen);
extern "C" __declspec(dllimport) long __stdcall StgOpenStorage(
    const unsigned short* name, IStorage_0067FD20* priority, unsigned long mode,
    void* exclude, unsigned long reserved, IStorage_0067FD20** out);

// The save-game information record. No member is touched here.
struct SavegameInfo_0067FD20
{
    // FUNCTION: GAMEMD 0x681840 (decl; reloc) — Read(storage), signed result.
    long Read(IStorage_0067FD20* storage);
};

// FUNCTION: GAMEMD 0x67FD20 — LoadOptionsClass::ReadFromFile (static).
bool LoadOptionsClass_ReadFromFile(const char* fileName,
                                   SavegameInfo_0067FD20* info);

#endif  // GG_MATCH_UI_LOAD_OPTIONS_READ_METHODS_H
