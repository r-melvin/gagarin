// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit Power.CPP. The name is the source-file string at 0x836db8
//   in retail gamemd.exe v1.001, passed by the assert at 0x640473 inside this object's
//   code range (0x63f4c0-0x6404ef). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.
//
// The nine tail-jump thunks, ordered ascending by retail address.

#include "deleting_dtor_sweep.h"
#include "../network/transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

#include "tail_jmp_thunk_sweep.h"

#include "trivial_tu181_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EFF40
extern const double DAT_007EFF40;
// GLOBAL: GAMEMD 0xAC4D18
extern double DAT_00AC4D18;
// GLOBAL: GAMEMD 0xAC4E50
extern double DAT_00AC4E50;
// GLOBAL: GAMEMD 0xAC4E58
extern int DAT_00AC4E58;
// GLOBAL: GAMEMD 0xAC4E5C
extern int DAT_00AC4E5C;
// GLOBAL: GAMEMD 0xAC4E60
extern int DAT_00AC4E60;
// GLOBAL: GAMEMD 0xAC4E68
extern double DAT_00AC4E68;

// FUNCTION: GAMEMD 0x63F4F0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_0063F4F0()
{
    DAT_00AC4E68 = DAT_00AC4D18 / DAT_007EFF40;
}

// FUNCTION: GAMEMD 0x63F510
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_0063F510()
{
    DAT_00AC4E50 = DAT_007E1718 / DAT_00AC4E68;
}

// FUNCTION: GAMEMD 0x63F690
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_0063F690()
{
    DAT_00AC4E60 = 0;
    DAT_00AC4E58 = 0x80;
    DAT_00AC4E5C = 0x80;
}

// FUNCTION: GAMEMD 0x63F7B0
void __fastcall FUN_0063F7B0(void* self)
{
    RadarClass_OneTime(self);
}

// FUNCTION: GAMEMD 0x63F7C0
// Calls other functions. Vtable slot 53 of PowerClass (RTTI).
int FUN_0063F7C0(Obj_0063F7C0* a1, int a2)
{
    FUN_00652E90(a1, a2);
    int c1 = FUN_004A38D0(DAT_00836D9C, DAT_00AC4E78);
    DAT_00AC4E74 = c1;
    return c1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6404B0
void* Obj_6404B0::FUN_6404B0(unsigned int flags)
{
    FUN_00652C00(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}
