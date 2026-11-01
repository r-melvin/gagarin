// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Argument slots, the copy shape and the return value read numerically off
//   the user's retail gamemd.exe v1.001 via the local Ghidra CLI at 0x409D90.
//
// Copy no more than both sides will allow, then report back how much moved by
// overwriting *both* length cells.
//
// The convention is __fastcall with two register arguments and three stack ones
// (`RET 0xC`). The first register argument is never read - ECX is overwritten by
// `MOV ECX,[EBP]` before any use - while EDX is the destination the `REP MOVSD`
// writes through. It is kept in the signature because dropping it would move
// the destination into ECX and change every call site's setup.
//
// The copy itself is VC6's inline `memcpy` expansion (`SHR ECX,2; REP MOVSD;
// AND ECX,3; REP MOVSB`), so `memcpy` is declared here and called directly
// rather than hand-written.
#ifndef GG_MATCH_CORE_BOUNDED_COPY_METHODS_H
#define GG_MATCH_CORE_BOUNDED_COPY_METHODS_H

extern "C" void* __cdecl memcpy(void* destination, const void* source, unsigned int count);

// FUNCTION: GAMEMD 0x409D90
int FUN_00409D90(void* unused, void* destination,
                 int* destinationLength,
                 const void* source, int* sourceLength);

#endif  // GG_MATCH_CORE_BOUNDED_COPY_METHODS_H
