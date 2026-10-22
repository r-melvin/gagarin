// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
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

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Out-of-line destructor 0x7B46F0 (a four-byte member: a string handle).
class Member_7B46F0
{
public:
    ~Member_7B46F0();
    void* Data;
};

// Out-of-line destructor 0x7B6760 (a four-byte member).
class Member_7B6760
{
public:
    ~Member_7B6760();
    void* Data;
};

// rc_ptr<T> is the canonical one: its inline destructor reseats the table,
// then calls the rc_ptr_base destructor 0x65D460 out of line.
#include "wdt_rc_ptr.h"

class WDTTerritory;
class WDTState;

// ReferenceCounted (RTTI vtable 0x7F0954) as these wrappers see it: the
// destructor out of line at 0x65D660 and slot 0 holding the deleting wrapper.
// A separate view of the class in wdt_rc_ptr.h, whose destructor is virtual.
class ReferenceCounted_0065D660
{
public:
    ~ReferenceCounted_0065D660();
    virtual void* DeletingDtor(unsigned int flags);
    long RefCount;   // +0x04
};

namespace WorldDominationTour {

// VTABLE: GAMEMD 0x7F6FC4
class Conflict : public ReferenceCounted_0065D660
{
public:
    ~Conflict() {}
    virtual void* DeletingDtor(unsigned int flags);
    rc_ptr<WDTTerritory> Territory;   // +0x08
};

// VTABLE: GAMEMD 0x7F70DC
class History : public ReferenceCounted_0065D660
{
public:
    ~History() {}
    virtual void* DeletingDtor(unsigned int flags);
    rc_ptr<WDTState> State;   // +0x08
};

// VTABLE: GAMEMD 0x7F7314
class State : public ReferenceCounted_0065D660
{
public:
    ~State() {}
    virtual void* DeletingDtor(unsigned int flags);
    rc_ptr<WDTState> Next;   // +0x08
};

// VTABLE: GAMEMD 0x7F7334
class Territory : public ReferenceCounted_0065D660
{
public:
    ~Territory() {}
    virtual void* DeletingDtor(unsigned int flags);
    int unknown_08;            // +0x08
    Member_7B6760 Member_0C;   // +0x0C
    char unknown_10[0x10];     // +0x10
    Member_7B46F0 Member_20;   // +0x20
};

// VTABLE: GAMEMD 0x7F7060
class GameOption : public ReferenceCounted_0065D660
{
public:
    ~GameOption() {}
    virtual void* DeletingDtor(unsigned int flags);
    char unknown_08[0x0C];   // +0x08
};

// Implicit destructor: the members, then GameOption's inline one.
class FlagGameOption : public GameOption
{
public:
    virtual void* DeletingDtor(unsigned int flags);
    Member_7B46F0 Member_14;   // +0x14
    Member_7B46F0 Member_18;   // +0x18
};

}  // namespace WorldDominationTour

// VTABLE: GAMEMD 0x7F74F4
class PlayerProfile : public ReferenceCounted_0065D660
{
public:
    ~PlayerProfile() {}
    virtual void* DeletingDtor(unsigned int flags);
    int unknown_08;            // +0x08
    Member_7B46F0 Member_0C;   // +0x0C
    char unknown_10[0x2C];     // +0x10
    Member_7B6760 Member_3C;   // +0x3C
    Member_7B6760 Member_40;   // +0x40
};

GG_STATIC_ASSERT(offsetof(WorldDominationTour::Conflict, Territory) == 0x08);
GG_STATIC_ASSERT(offsetof(WorldDominationTour::Territory, Member_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(WorldDominationTour::Territory, Member_20) == 0x20);
GG_STATIC_ASSERT(offsetof(WorldDominationTour::FlagGameOption, Member_14) == 0x14);
GG_STATIC_ASSERT(offsetof(WorldDominationTour::FlagGameOption, Member_18) == 0x18);
GG_STATIC_ASSERT(offsetof(PlayerProfile, Member_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(PlayerProfile, Member_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(PlayerProfile, Member_40) == 0x40);

// FUNCTION: GAMEMD 0x7667A0
void* WorldDominationTour::Conflict::DeletingDtor(unsigned int flags)
{
    this->~Conflict();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x767880
void* WorldDominationTour::FlagGameOption::DeletingDtor(unsigned int flags)
{
    this->~FlagGameOption();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x767C10
void* WorldDominationTour::History::DeletingDtor(unsigned int flags)
{
    this->~History();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x76F6C0
void* WorldDominationTour::State::DeletingDtor(unsigned int flags)
{
    this->~State();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x770020
void* WorldDominationTour::Territory::DeletingDtor(unsigned int flags)
{
    this->~Territory();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x77B030
void* PlayerProfile::DeletingDtor(unsigned int flags)
{
    this->~PlayerProfile();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}
