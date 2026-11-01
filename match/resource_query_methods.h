// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and IAT slots read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4A3B40. The three indirect calls were resolved from
//   the binary's own import labels, not guessed: 0x007E122C is FindResourceA,
//   0x007E1230 is LoadResource and 0x007E1228 is LockResource. Signature
//   cross-checked against YRpp (`Unsorted::GetResource`).
#ifndef GG_MATCH_PLATFORM_RESOURCE_QUERY_METHODS_H
#define GG_MATCH_PLATFORM_RESOURCE_QUERY_METHODS_H

typedef struct HINSTANCE__* HINSTANCE;
typedef struct HRSRC__*     HRSRC;
typedef void*               HGLOBAL;

// GLOBAL: GAMEMD 0x0089F974 — the game's own module handle, read twice by the
// lookup below (retail reloads it rather than keeping it live across the call).
extern HINSTANCE GameInstance;

// Find, load and lock an embedded resource in one step, returning a pointer to
// its bytes or null at the first failed stage.
void* Unsorted_GetResource(int id, const char* type);   // GAMEMD 0x4A3B40

#endif  // GG_MATCH_PLATFORM_RESOURCE_QUERY_METHODS_H
