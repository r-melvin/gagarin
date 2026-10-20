// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   All 53 entry points and their 28 distinct vtable addresses were extracted
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
extern char VTABLE_007E17EC[];   // VTABLE: GAMEMD 0x7E17EC
extern char VTABLE_007E180C[];   // VTABLE: GAMEMD 0x7E180C
extern char VTABLE_007E184C[];   // VTABLE: GAMEMD 0x7E184C
extern char VTABLE_007E188C[];   // VTABLE: GAMEMD 0x7E188C
extern char VTABLE_007E18DC[];   // VTABLE: GAMEMD 0x7E18DC
extern char VTABLE_007E192C[];   // VTABLE: GAMEMD 0x7E192C
extern char VTABLE_007E1A64[];   // VTABLE: GAMEMD 0x7E1A64
extern char VTABLE_007E1B44[];   // VTABLE: GAMEMD 0x7E1B44
extern char VTABLE_007E1E4C[];   // VTABLE: GAMEMD 0x7E1E4C
extern char VTABLE_007E1EA4[];   // VTABLE: GAMEMD 0x7E1EA4
extern char VTABLE_007E1EF4[];   // VTABLE: GAMEMD 0x7E1EF4
extern char VTABLE_007E295C[];   // VTABLE: GAMEMD 0x7E295C
extern char VTABLE_007E2AF0[];   // VTABLE: GAMEMD 0x7E2AF0
extern char VTABLE_007E3258[];   // VTABLE: GAMEMD 0x7E3258
extern char VTABLE_007E37EC[];   // VTABLE: GAMEMD 0x7E37EC
extern char VTABLE_007E3824[];   // VTABLE: GAMEMD 0x7E3824
extern char VTABLE_007E38D0[];   // VTABLE: GAMEMD 0x7E38D0
extern char VTABLE_007E38F0[];   // VTABLE: GAMEMD 0x7E38F0
extern char VTABLE_007E3E54[];   // VTABLE: GAMEMD 0x7E3E54
extern char VTABLE_007E43E8[];   // VTABLE: GAMEMD 0x7E43E8
extern char VTABLE_007E4424[];   // VTABLE: GAMEMD 0x7E4424
extern char VTABLE_007E4468[];   // VTABLE: GAMEMD 0x7E4468
extern char VTABLE_007E4514[];   // VTABLE: GAMEMD 0x7E4514
extern char VTABLE_007E4638[];   // VTABLE: GAMEMD 0x7E4638
extern char VTABLE_007E4698[];   // VTABLE: GAMEMD 0x7E4698
extern char VTABLE_007E4AF4[];   // VTABLE: GAMEMD 0x7E4AF4
extern char VTABLE_007E4BC4[];   // VTABLE: GAMEMD 0x7E4BC4

// The deleting destructors hang off the same layout as BufferHolder.
struct BufferHolderDtor : BufferHolder
{
    void* FUN_0040B300(unsigned int flags);   // FUNCTION: GAMEMD 0x40B300
    void* FUN_0040BBC0(unsigned int flags);   // FUNCTION: GAMEMD 0x40BBC0
    void* FUN_0040BC10(unsigned int flags);   // FUNCTION: GAMEMD 0x40BC10
    void* FUN_0040BC60(unsigned int flags);   // FUNCTION: GAMEMD 0x40BC60
    void* FUN_0040BCB0(unsigned int flags);   // FUNCTION: GAMEMD 0x40BCB0
    void* FUN_0040C110(unsigned int flags);   // FUNCTION: GAMEMD 0x40C110
    void* FUN_0040C160(unsigned int flags);   // FUNCTION: GAMEMD 0x40C160
    void* FUN_0040C4F0(unsigned int flags);   // FUNCTION: GAMEMD 0x40C4F0
    void* FUN_0040C540(unsigned int flags);   // FUNCTION: GAMEMD 0x40C540
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
    void* FUN_0040F8A0(unsigned int flags);   // FUNCTION: GAMEMD 0x40F8A0
    void* FUN_0040F8F0(unsigned int flags);   // FUNCTION: GAMEMD 0x40F8F0
    void* FUN_0040FE70(unsigned int flags);   // FUNCTION: GAMEMD 0x40FE70
    void* FUN_0040FEC0(unsigned int flags);   // FUNCTION: GAMEMD 0x40FEC0
    void* FUN_0041E0A0(unsigned int flags);   // FUNCTION: GAMEMD 0x41E0A0
    void* FUN_0041E0F0(unsigned int flags);   // FUNCTION: GAMEMD 0x41E0F0
    void* FUN_00420630(unsigned int flags);   // FUNCTION: GAMEMD 0x420630
    void* FUN_00420680(unsigned int flags);   // FUNCTION: GAMEMD 0x420680
    void* FUN_00421AC0(unsigned int flags);   // FUNCTION: GAMEMD 0x421AC0
    void* FUN_00421B10(unsigned int flags);   // FUNCTION: GAMEMD 0x421B10
    void* FUN_0042DB10(unsigned int flags);   // FUNCTION: GAMEMD 0x42DB10
    void* FUN_0042DB60(unsigned int flags);   // FUNCTION: GAMEMD 0x42DB60
    void* FUN_0042DBB0(unsigned int flags);   // FUNCTION: GAMEMD 0x42DBB0
    void* FUN_0042DC00(unsigned int flags);   // FUNCTION: GAMEMD 0x42DC00
    void* FUN_0042F970(unsigned int flags);   // FUNCTION: GAMEMD 0x42F970
    void* FUN_0042FB50(unsigned int flags);   // FUNCTION: GAMEMD 0x42FB50
    void* FUN_0042FBA0(unsigned int flags);   // FUNCTION: GAMEMD 0x42FBA0
    void* FUN_0042FBF0(unsigned int flags);   // FUNCTION: GAMEMD 0x42FBF0
    void* FUN_0043ACB0(unsigned int flags);   // FUNCTION: GAMEMD 0x43ACB0
    void* FUN_0045A9C0(unsigned int flags);   // FUNCTION: GAMEMD 0x45A9C0
    void* FUN_0045AA10(unsigned int flags);   // FUNCTION: GAMEMD 0x45AA10
    // 0x45AA60 removed from this family: RTTI-confirmed as
    // VectorClass<InfantryClass*>::`scalar deleting destructor', modelled
    // separately below via the Vector<T> template family (see the
    // out-of-line explicit instantiation in the .cpp) rather than under this
    // shared BufferHolderDtor shape. See docs/naming_proposals.md #3 and the
    // docs/decomp_spec/vtable_map_techno.md provenance-warning correction.
    void* FUN_0045AAB0(unsigned int flags);   // FUNCTION: GAMEMD 0x45AAB0
    void* FUN_0045AB00(unsigned int flags);   // FUNCTION: GAMEMD 0x45AB00
    void* FUN_0045AC90(unsigned int flags);   // FUNCTION: GAMEMD 0x45AC90
    void* FUN_0045ACE0(unsigned int flags);   // FUNCTION: GAMEMD 0x45ACE0
    void* FUN_0045AD30(unsigned int flags);   // FUNCTION: GAMEMD 0x45AD30
    void* FUN_00466080(unsigned int flags);   // FUNCTION: GAMEMD 0x466080
    void* FUN_0046B8C0(unsigned int flags);   // FUNCTION: GAMEMD 0x46B8C0
    void* FUN_0046B910(unsigned int flags);   // FUNCTION: GAMEMD 0x46B910
    void* FUN_00473000(unsigned int flags);   // FUNCTION: GAMEMD 0x473000
    void* FUN_00473050(unsigned int flags);   // FUNCTION: GAMEMD 0x473050
    void* FUN_004730A0(unsigned int flags);   // FUNCTION: GAMEMD 0x4730A0
    void* FUN_004730F0(unsigned int flags);   // FUNCTION: GAMEMD 0x4730F0
};

#endif  // GG_MATCH_CORE_BUFFER_HOLDER_DTOR_METHODS_H
