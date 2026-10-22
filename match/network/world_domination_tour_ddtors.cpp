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

#include "world_domination_tour.h"

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
