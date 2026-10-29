// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
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
// The deleting destructors (??_G) of the World Domination Tour data classes are
// compiler output: the out-of-line destructors below make cl emit the tables and
// the wrappers, and /Ob2 expands the destructor bodies into them as retail has it.

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

// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_00767140()
{
    DAT_00B72800 = DAT_00B727B0 / DAT_007F7078;
}

// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_00767160()
{
    DAT_00B727E8 = DAT_007E1718 / DAT_00B72800;
}

// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_007672E0()
{
    DAT_00B727F8 = 0;
    DAT_00B727F0 = 0x80;
    DAT_00B727F4 = 0x80;
}


// FUNCTION: GAMEMD 0x767300
// Seats the GameOption table, then the ReferenceCounted destructor.
GameOption::~GameOption()
{
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
rc_ptr<MapSizeGameOption> FUN_007676F0(unsigned int value)
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
// FUNCTION: GAMEMD 0x767820
// A flag option: two labels and the value taken when the subject's bit is
// set or clear.
FlagGameOption::FlagGameOption(unsigned int flags, Member_7B46F0 name18, int when_clear,
                               Member_7B46F0 name14, int when_set)
    : GameOption(flags), unknown_0C(when_clear), unknown_10(when_set), Member_14(name14), Member_18(name18)
{
}

// SYNTHETIC: GAMEMD 0x767880
// FlagGameOption scalar deleting destructor.

// SYNTHETIC: GAMEMD 0x7678C0
// MapSizeGameOption scalar deleting destructor.
