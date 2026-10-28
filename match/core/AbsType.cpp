// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   Original translation unit AbsType.cpp. The name is the source-file string at 0x817830
//   in retail gamemd.exe v1.001, passed by the assert at 0x410994 inside this object's
//   code range (0x410610-0x410e4f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// AbstractTypeClass body for slot 13 of its primary table 0x7E2000
// (abstract_type_class.h); the name is a placeholder.

#include "../_layout/abstract_type_class.h"
#include "../_layout/obj_004a1d30.h"

#include "free_and_compare_methods.h"
#include <string.h>



// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7E1FC0
extern const double DAT_007E1FC0;
// GLOBAL: GAMEMD 0x8876D8
extern double DAT_008876D8;
// GLOBAL: GAMEMD 0x887710
extern double DAT_00887710;
// GLOBAL: GAMEMD 0x887718
extern int DAT_00887718;
// GLOBAL: GAMEMD 0x88771C
extern int DAT_0088771C;
// GLOBAL: GAMEMD 0x887720
extern int DAT_00887720;
// GLOBAL: GAMEMD 0x887728
extern double DAT_00887728;

// SYNTHETIC: GAMEMD 0x00410640
// dynamic initializer for DAT_00887728

// GLOBAL: GAMEMD 0x00887728
double DAT_00887728 = DAT_008876D8 / DAT_007E1FC0;

// SYNTHETIC: GAMEMD 0x00410660
// dynamic initializer for DAT_00887710

// GLOBAL: GAMEMD 0x00887710
double DAT_00887710 = DAT_007E1718 / DAT_00887728;

// FUNCTION: GAMEMD 0x4107E0
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_004107E0()
{
    DAT_00887720 = 0;
    DAT_00887718 = 0x80;
    DAT_0088771C = 0x80;
}

// FUNCTION: GAMEMD 0x410A40
// `NEG EAX; SBB EAX,EAX; INC EAX` after the call is the bool form of `== 0`,
// so the comparison is an equality test rather than an ordering one. Argument
// order is (other, ID) — the pushes put the caller's string first.
bool AbstractTypeClass::FUN_00410A40(const char* other) const
{
    return FUN_007C8D20(other, ID) == 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x410BE0
// The base fields through AbstractClass's slot 13 (a direct call), then the
// ID, Name and the +0x3D text field into the checksum sink.
void AbstractTypeClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
    crc->FUN_004A1DB0(ID);
    crc->FUN_004A1DB0(Name);
    crc->FUN_004A1DB0(UINameLabel);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x410C20
// Empty function that pops its stack arguments. Vtable slot 24 of AbstractTypeClass (RTTI) and 27 derived vtable(s).
void AbstractTypeClass::vf_24(int value)
{
}
