// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// World Domination Tour game-option methods (retail 0x767310-0x767820).
#include "world_domination_tour.h"

using WorldDominationTour::GameOption;
using WorldDominationTour::FlagGameOption;
using WorldDominationTour::MapSizeGameOption;

// FUNCTION: GAMEMD 0x767310
bool GameOption::FUN_00767310(const rc_ptr<Obj_007674E0>&) const
{
    return false;
}

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

// FUNCTION: GAMEMD 0x7676F0
// Wraps a new MapSizeGameOption; the result is the hidden first argument.
rc_ptr<MapSizeGameOption> __fastcall FUN_007676F0(unsigned int value)
{
    return rc_ptr<MapSizeGameOption>(new MapSizeGameOption(value));
}

// FUNCTION: GAMEMD 0x7674E0
int FlagGameOption::vf_0C(const rc_ptr<Obj_007674E0>& subject) const
{
    if (unknown_08 & subject.Get()->unknown_38)
        return unknown_10;
    return unknown_0C;
}

// A one-argument method returning zero; owner not identified.
class Obj_00767600
{
public:
    int FUN_00767600(int) const;
};

// FUNCTION: GAMEMD 0x767600
int Obj_00767600::FUN_00767600(int) const
{
    return 0;
}

// GLOBAL: GAMEMD 0x848628 -- a 4x4 table indexed by the subject's two bytes.
extern int DAT_00848628[];

// FUNCTION: GAMEMD 0x767800
int MapSizeGameOption::vf_0C(const rc_ptr<Obj_007674E0>& subject) const
{
    Obj_007674E0* s = subject.Get();
    return DAT_00848628[s->unknown_12 * 4 + s->unknown_13];
}
