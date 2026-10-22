// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit WDTGameOptions.cpp. The name is the source-file string at 0x8486ac
//   in retail gamemd.exe v1.001, passed by the assert at 0x767371 inside this object's
//   code range (0x767110-0x76790f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The seven vtable-seating base destructors, ordered ascending by address.
//
// World Domination Tour game-option methods (retail 0x767310-0x767820).
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

#include "../core/seat_vtable_tail_dtor_sweep.h"

#include "world_domination_tour.h"

using WorldDominationTour::GameOption;
using WorldDominationTour::FlagGameOption;
using WorldDominationTour::MapSizeGameOption;

// An object with four ascending unsigned thresholds; slot 5 (+0x14) is the
// classifier at 0x767400, which 0x767440 calls virtually. RTTI class unknown.
class Obj_00767400
{
public:
    virtual void vf_00();
    virtual void vf_04();
    virtual void vf_08();
    virtual void vf_0C();
    virtual void vf_10();
    virtual int vf_14(unsigned int value) const;
    int FUN_00767440(unsigned int value) const;
    char unknown_04[0x10];      // +0x04
    unsigned int unknown_14;    // +0x14
    unsigned int unknown_18;    // +0x18
    unsigned int unknown_1C;    // +0x1C
    unsigned int unknown_20;    // +0x20
};
GG_STATIC_ASSERT(offsetof(Obj_00767400, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_00767400, unknown_20) == 0x20);

// A one-argument method returning zero; owner not identified.
class Obj_00767600
{
public:
    int FUN_00767600(int) const;
};

// GLOBAL: GAMEMD 0x848628 -- a 4x4 table indexed by the subject's two bytes.
extern int DAT_00848628[];

#include "world_domination_tour.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F7078
extern const double DAT_007F7078;
// GLOBAL: GAMEMD 0xB727B0
extern double DAT_00B727B0;
// GLOBAL: GAMEMD 0xB727E8
extern double DAT_00B727E8;
// GLOBAL: GAMEMD 0xB727F0
extern int DAT_00B727F0;
// GLOBAL: GAMEMD 0xB727F4
extern int DAT_00B727F4;
// GLOBAL: GAMEMD 0xB727F8
extern int DAT_00B727F8;
// GLOBAL: GAMEMD 0xB72800
extern double DAT_00B72800;

// FUNCTION: GAMEMD 0x767140
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_00767140()
{
    DAT_00B72800 = DAT_00B727B0 / DAT_007F7078;
}

// FUNCTION: GAMEMD 0x767160
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_00767160()
{
    DAT_00B727E8 = DAT_007E1718 / DAT_00B72800;
}

// FUNCTION: GAMEMD 0x7672E0
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_007672E0()
{
    DAT_00B727F8 = 0;
    DAT_00B727F0 = 0x80;
    DAT_00B727F4 = 0x80;
}

// FUNCTION: GAMEMD 0x767300
// VTABLE: GAMEMD 0x7F7060
void __fastcall FUN_00767300(SeatDtorObject* self)
{
    self->Vtbl = VTABLE_007F7060;
    FUN_0065D660(self);
}

// FUNCTION: GAMEMD 0x767310
bool GameOption::FUN_00767310(const rc_ptr<Obj_007674E0>&) const
{
    return false;
}

// FUNCTION: GAMEMD 0x767400
int Obj_00767400::vf_14(unsigned int value) const
{
    if (value <= unknown_14)
        return 0;
    if (value <= unknown_18)
        return 1;
    if (value >= unknown_20)
        return 3;
    return value < unknown_1C ? 4 : 2;
}

// FUNCTION: GAMEMD 0x767440
int Obj_00767400::FUN_00767440(unsigned int value) const
{
    return vf_14(value) == 4 ? 2 : 0;
}

// FUNCTION: GAMEMD 0x7674E0
int FlagGameOption::vf_0C(const rc_ptr<Obj_007674E0>& subject) const
{
    if (unknown_08 & subject.Get()->unknown_38)
        return unknown_10;
    return unknown_0C;
}

// FUNCTION: GAMEMD 0x767600
int Obj_00767600::FUN_00767600(int) const
{
    return 0;
}

// FUNCTION: GAMEMD 0x7676F0
// Wraps a new MapSizeGameOption; the result is the hidden first argument.
rc_ptr<MapSizeGameOption> __fastcall FUN_007676F0(unsigned int value)
{
    return rc_ptr<MapSizeGameOption>(new MapSizeGameOption(value));
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x767800
int MapSizeGameOption::vf_0C(const rc_ptr<Obj_007674E0>& subject) const
{
    Obj_007674E0* s = subject.Get();
    return DAT_00848628[s->unknown_12 * 4 + s->unknown_13];
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x767880
void* WorldDominationTour::FlagGameOption::DeletingDtor(unsigned int flags)
{
    this->~FlagGameOption();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}
