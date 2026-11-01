// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Statically linked CRT allocator entry points called by game code, declared under their address placeholders so cl cannot substitute its own handling: operator delete (0x7C8B3D), operator new (0x7C8E17) and free (0x7C93E8).
#ifndef GG_MATCH__RT_CRT_ALLOCATOR_H
#define GG_MATCH__RT_CRT_ALLOCATOR_H

extern "C" void __cdecl FUN_007C8B3D(void* block); // LIBRARY: GAMEMD 0x7C8B3D
extern "C" void* __cdecl FUN_007C8E17(unsigned int size); // LIBRARY: GAMEMD 0x7C8E17
// LIBRARY: GAMEMD 0x7C93E8 — CRT free.
// LIBRARY: GAMEMD 0x7C8B3D — operator delete used by the destructor.
extern "C" void __cdecl FUN_007C93E8(void* block);

#endif  // GG_MATCH__RT_CRT_ALLOCATOR_H
