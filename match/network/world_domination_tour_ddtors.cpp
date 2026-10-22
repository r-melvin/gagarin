// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Scalar deleting destructors of the World Domination Tour data classes and
// of rc_ptr_base, their shared smart-pointer root. Each one runs the class's
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

// The pointee interface: rc_ptr_base releases through slot 2.
class RcTarget
{
public:
    virtual long QueryInterface(const void* iid, void** out) = 0;
    virtual unsigned long AddRef() = 0;
    virtual unsigned long Release() = 0;
};

// VTABLE: GAMEMD 0x7F094C
class rc_ptr_base
{
public:
    ~rc_ptr_base()
    {
        if (Pointer != 0) {
            RcTarget* old = Pointer;
            Pointer = 0;
            old->Release();
        }
    }
    virtual void* DeletingDtor(unsigned int flags);

    RcTarget* Pointer;   // +0x04
};

GG_STATIC_ASSERT(offsetof(rc_ptr_base, Pointer) == 0x04);

// The out-of-line rc_ptr_base destructor body at 0x65D460, as reached from a
// derived rc_ptr<T>: a separate view, since the destructor above is the
// inline one the deleting wrapper expands.
class rc_ptr_base_ool
{
public:
    ~rc_ptr_base_ool();
    virtual void* DeletingDtor(unsigned int flags);
    RcTarget* Pointer;
};

// rc_ptr<T>: an empty derived destructor reseating its own table, then the
// base destructor out of line.
template <class T>
class rc_ptr : public rc_ptr_base_ool
{
public:
    ~rc_ptr() {}
};

class WDTTerritory;
class WDTState;

// ReferenceCounted (RTTI vtable 0x7F0954): destructor out of line at 0x65D660.
class ReferenceCounted
{
public:
    ~ReferenceCounted();
    virtual void* DeletingDtor(unsigned int flags);
    long RefCount;   // +0x04
};

namespace WorldDominationTour {

// VTABLE: GAMEMD 0x7F6FC4
class Conflict : public ReferenceCounted
{
public:
    ~Conflict() {}
    virtual void* DeletingDtor(unsigned int flags);
    rc_ptr<WDTTerritory> Territory;   // +0x08
};

// VTABLE: GAMEMD 0x7F70DC
class History : public ReferenceCounted
{
public:
    ~History() {}
    virtual void* DeletingDtor(unsigned int flags);
    rc_ptr<WDTState> State;   // +0x08
};

// VTABLE: GAMEMD 0x7F7314
class State : public ReferenceCounted
{
public:
    ~State() {}
    virtual void* DeletingDtor(unsigned int flags);
    rc_ptr<WDTState> Next;   // +0x08
};

// VTABLE: GAMEMD 0x7F7334
class Territory : public ReferenceCounted
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
class GameOption : public ReferenceCounted
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
class PlayerProfile : public ReferenceCounted
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

// FUNCTION: GAMEMD 0x65D4D0
void* rc_ptr_base::DeletingDtor(unsigned int flags)
{
    this->~rc_ptr_base();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

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
