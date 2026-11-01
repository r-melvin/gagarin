// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU181_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU181_METHODS_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"

struct Obj_0063F7C0;

// GLOBAL: GAMEMD 0x836D9C
extern char DAT_00836D9C[];
// GLOBAL: GAMEMD 0xAC4E74
// Pointer to the buffer FUN_004A38D0 returns: written from EAX at 0x63F7D4 and pushed to
// operator delete at 0x63F7EE/0x63F7F3 (dword accesses; the other readers use it as a base).
extern void* DAT_00AC4E74;
// GLOBAL: GAMEMD 0xAC4E78
// Byte flag: tested at 0x63F7E5 (mov al), cleared at 0x63F7FC (mov byte ptr, 0) and its address is
// the out-parameter (EDX) of FUN_004A38D0 at 0x63F7C5.
extern bool DAT_00AC4E78;

// FUNCTION: GAMEMD 0x4A38D0 (declaration)
int FUN_004A38D0(void*, void*);
// FUNCTION: GAMEMD 0x652E90 (declaration)
void FUN_00652E90(Obj_0063F7C0*, int);

struct Obj_0063F7C0
{
};


// FUNCTION: GAMEMD 0x63F7C0
int FUN_0063F7C0(Obj_0063F7C0* a1, int a2);

#endif  // GG_MATCH_CORE_TRIVIAL_TU181_METHODS_H
