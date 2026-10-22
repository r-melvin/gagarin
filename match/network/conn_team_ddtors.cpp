// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Scalar deleting destructors of MultiplayerTeam (no base class in RTTI) and
// NullModemConnClass (RTTI base ConnectionClass, whose destructor 0x48BEE0 is
// called out of line). Each stores its own vtable, destroys what it owns,
// frees the object when bit 0 of the flag is set and returns `this`. Slot 0
// is modelled as an ordinary virtual holding the deleting wrapper, as
// FileClass does in match/core/ram_file_class.h.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Out-of-line destructor 0x7B6760 (a four-byte member).
class Member_7B6760
{
public:
    ~Member_7B6760();
    void* Data;
};

// VTABLE: GAMEMD 0x7EEEDC
class MultiplayerTeam
{
public:
    ~MultiplayerTeam() {}
    virtual void* DeletingDtor(unsigned int flags);
    Member_7B6760 Member_04;   // +0x04
};

GG_STATIC_ASSERT(offsetof(MultiplayerTeam, Member_04) == 0x04);

class ConnectionClass
{
public:
    ~ConnectionClass();   // 0x48BEE0
    virtual void* DeletingDtor(unsigned int flags);
    char unknown_04[0x4C];   // +0x04
};

// VTABLE: GAMEMD 0x7EEF90
class NullModemConnClass : public ConnectionClass
{
public:
    ~NullModemConnClass() { operator delete(Buffer); }
    virtual void* DeletingDtor(unsigned int flags);
    void* Buffer;   // +0x50
};

GG_STATIC_ASSERT(offsetof(NullModemConnClass, Buffer) == 0x50);

// FUNCTION: GAMEMD 0x5D8D50
void* MultiplayerTeam::DeletingDtor(unsigned int flags)
{
    this->~MultiplayerTeam();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x5EF290
void* NullModemConnClass::DeletingDtor(unsigned int flags)
{
    this->~NullModemConnClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}
