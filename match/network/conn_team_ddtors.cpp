// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The MultiplayerTeam constructor and scalar deleting destructor (no base
// class in RTTI; the class is in multiplayer_team.h), and the scalar deleting
// destructor of NullModemConnClass (RTTI base ConnectionClass, whose
// destructor 0x48BEE0 is called out of line). The NullModemConnClass wrapper
// stores its own vtable, destroys what it owns, frees the object when bit 0
// of the flag is set and returns `this`; its slot 0 is modelled as an
// ordinary virtual holding the deleting wrapper, as FileClass does in
// match/core/ram_file_class.h.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "multiplayer_team.h"

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

// FUNCTION: GAMEMD 0x5D8C50
MultiplayerTeam::MultiplayerTeam(const Obj_007B66D0& name, int unknown)
    : unknown_04(name),
      unknown_08(unknown)
{
}

// SYNTHETIC: GAMEMD 0x5D8D50
// MultiplayerTeam scalar deleting destructor, emitted with the vtable
// 0x7EEEDC by the constructor above. The destructor is `inline` in this unit
// so that the wrapper carries its body as retail's does; the out-of-line
// copy 0x5D8C80, which the leaf destructors jump to, stays a declaration.
inline MultiplayerTeam::~MultiplayerTeam()
{
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
