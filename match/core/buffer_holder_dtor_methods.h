// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The original 53 entry points and their vtable addresses were extracted
//   individually from the user's retail gamemd.exe v1.001 via the local Ghidra
//   CLI, one disassembly each. Every one agreed on the layout: buffer at +0x04,
//   length at +0x08, ownership flag at +0x0D. None is bound by YRpp or the seed
//   map.
//
// The buffer-holder deleting destructor. Same class family as the plain
// buffer-release template in buffer_release_methods.h, but here the release is
// inlined into a scalar deleting destructor: install the vtable, free the
// buffer if owned, reset the holder, then free the object itself only if bit 0
// of the flag argument is set, and return the pointer.
//
// Declared as members rather than free __fastcall functions. Retail reads the
// flag from [ESP+8] and returns with `RET 4`, so it is a stack argument -
// __fastcall would put it in EDX and nothing after the prologue would line up.
//
// The vtables are declared as opaque extern arrays purely so the store emits a
// relocation the diff normalises. Nothing here models their contents.
#ifndef GG_MATCH_CORE_BUFFER_HOLDER_DTOR_METHODS_H
#define GG_MATCH_CORE_BUFFER_HOLDER_DTOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "buffer_release_methods.h"

extern char VTABLE_007E177C[];   // VTABLE: GAMEMD 0x7E177C
extern char VTABLE_007E184C[];   // VTABLE: GAMEMD 0x7E184C
extern char VTABLE_007E18DC[];   // VTABLE: GAMEMD 0x7E18DC
extern char VTABLE_007E192C[];   // VTABLE: GAMEMD 0x7E192C
extern char VTABLE_007E1A64[];   // VTABLE: GAMEMD 0x7E1A64
extern char VTABLE_007E1B44[];   // VTABLE: GAMEMD 0x7E1B44
extern char VTABLE_007E1E4C[];   // VTABLE: GAMEMD 0x7E1E4C
extern char VTABLE_007E1EF4[];   // VTABLE: GAMEMD 0x7E1EF4
extern char VTABLE_007E37EC[];   // VTABLE: GAMEMD 0x7E37EC
extern char VTABLE_007E3824[];   // VTABLE: GAMEMD 0x7E3824
extern char VTABLE_007E38D0[];   // VTABLE: GAMEMD 0x7E38D0
extern char VTABLE_007E38F0[];   // VTABLE: GAMEMD 0x7E38F0
extern char VTABLE_007E3E54[];   // VTABLE: GAMEMD 0x7E3E54
extern char VTABLE_007E43E8[];   // VTABLE: GAMEMD 0x7E43E8
extern char VTABLE_007E4468[];   // VTABLE: GAMEMD 0x7E4468
extern char VTABLE_007E4514[];   // VTABLE: GAMEMD 0x7E4514
extern char VTABLE_007E4638[];   // VTABLE: GAMEMD 0x7E4638
extern char VTABLE_007E4698[];   // VTABLE: GAMEMD 0x7E4698

// The deleting destructors hang off the same layout as BufferHolder.
struct BufferHolderDtor : BufferHolder
{
    void* FUN_0040B300(unsigned int flags);   // FUNCTION: GAMEMD 0x40B300
    void* FUN_0040C110(unsigned int flags);   // FUNCTION: GAMEMD 0x40C110
    void* FUN_0040C160(unsigned int flags);   // FUNCTION: GAMEMD 0x40C160
    void* FUN_0040CAE0(unsigned int flags);   // FUNCTION: GAMEMD 0x40CAE0
    void* FUN_0040CB30(unsigned int flags);   // FUNCTION: GAMEMD 0x40CB30
    void* FUN_0040CC20(unsigned int flags);   // FUNCTION: GAMEMD 0x40CC20
    void* FUN_0040CF30(unsigned int flags);   // FUNCTION: GAMEMD 0x40CF30
    void* FUN_0040D800(unsigned int flags);   // FUNCTION: GAMEMD 0x40D800
    void* FUN_0040D850(unsigned int flags);   // FUNCTION: GAMEMD 0x40D850
    void* FUN_0040EAB0(unsigned int flags);   // FUNCTION: GAMEMD 0x40EAB0
    void* FUN_0040EB00(unsigned int flags);   // FUNCTION: GAMEMD 0x40EB00
    void* FUN_0040F180(unsigned int flags);   // FUNCTION: GAMEMD 0x40F180
    void* FUN_0040F1D0(unsigned int flags);   // FUNCTION: GAMEMD 0x40F1D0
    void* FUN_0040FE70(unsigned int flags);   // FUNCTION: GAMEMD 0x40FE70
    void* FUN_0040FEC0(unsigned int flags);   // FUNCTION: GAMEMD 0x40FEC0
    void* FUN_0042DB10(unsigned int flags);   // FUNCTION: GAMEMD 0x42DB10
    void* FUN_0042DB60(unsigned int flags);   // FUNCTION: GAMEMD 0x42DB60
    void* FUN_0042DBB0(unsigned int flags);   // FUNCTION: GAMEMD 0x42DBB0
    void* FUN_0042DC00(unsigned int flags);   // FUNCTION: GAMEMD 0x42DC00
    void* FUN_0042F970(unsigned int flags);   // FUNCTION: GAMEMD 0x42F970
    void* FUN_0042FB50(unsigned int flags);   // FUNCTION: GAMEMD 0x42FB50
    void* FUN_0042FBA0(unsigned int flags);   // FUNCTION: GAMEMD 0x42FBA0
    void* FUN_0042FBF0(unsigned int flags);   // FUNCTION: GAMEMD 0x42FBF0
    void* FUN_0043ACB0(unsigned int flags);   // FUNCTION: GAMEMD 0x43ACB0
    void* FUN_0045ACE0(unsigned int flags);   // FUNCTION: GAMEMD 0x45ACE0
    void* FUN_0045AD30(unsigned int flags);   // FUNCTION: GAMEMD 0x45AD30
    void* FUN_00466080(unsigned int flags);   // FUNCTION: GAMEMD 0x466080
};

#endif  // GG_MATCH_CORE_BUFFER_HOLDER_DTOR_METHODS_H
