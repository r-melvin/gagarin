// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit WDTTerr.cpp. The name is the source-file string at 0x84917c
//   in retail gamemd.exe v1.001, passed by the assert at 0x76fa3a inside this object's
//   code range (0x76f720-0x77007f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Scalar deleting destructors of the World Domination Tour data classes
// (rc_ptr_base's own is in rc_ptr_base.cpp). Each one runs the class's
// destructor inline (the vtable store, then the member destructors in reverse
// declaration order, then the base destructor out of line), frees the object
// when bit 0 of the flag is set, and returns `this`.
//
// Class names are the retail RTTI names. A class that stores its own vtable
// first declares its destructor; a class whose body starts with member
// destructors and stores only its base's vtable has the implicit one (MSVC's
// implicit destructor does not reseat the vptr). Member types are known only
// by their out-of-line destructors, so each is an opaque view named after it.
//
// Slot 0 is modelled as an ordinary virtual holding the deleting wrapper, as
// FileClass does in match/core/ram_file_class.h: nothing here is constructed,
// so cl would not emit the tables or a compiler-generated `??_G`.
// Offsets come from the `LEA ECX,[ESI+n]` member addresses in each body.

#include "../core/trivial_tu280_methods.h"

#include "world_domination_tour.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F7320
extern const double DAT_007F7320;
// GLOBAL: GAMEMD 0xB72B30
extern double DAT_00B72B30;
// GLOBAL: GAMEMD 0xB72B68
extern double DAT_00B72B68;
// GLOBAL: GAMEMD 0xB72B70
extern int DAT_00B72B70;
// GLOBAL: GAMEMD 0xB72B74
extern int DAT_00B72B74;
// GLOBAL: GAMEMD 0xB72B78
extern int DAT_00B72B78;
// GLOBAL: GAMEMD 0xB72B80
extern double DAT_00B72B80;

// FUNCTION: GAMEMD 0x76F750
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_0076F750()
{
    DAT_00B72B80 = DAT_00B72B30 / DAT_007F7320;
}

// FUNCTION: GAMEMD 0x76F770
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_0076F770()
{
    DAT_00B72B68 = DAT_007E1718 / DAT_00B72B80;
}

// FUNCTION: GAMEMD 0x76F8F0
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_0076F8F0()
{
    DAT_00B72B78 = 0;
    DAT_00B72B70 = 0x80;
    DAT_00B72B74 = 0x80;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x76FF20
// Stores its argument in a member; pops its stack arguments.
void Obj_0076FF20::FUN_0076FF20(int a1)
{
    unknown_2C = a1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x76FF30
// Stores its argument in a member.
int Obj_0076FF30::FUN_0076FF30()
{
    int t1 = unknown_2C;
    unknown_2C = 0;
    return t1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x770020
void* WorldDominationTour::Territory::DeletingDtor(unsigned int flags)
{
    this->~Territory();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}
