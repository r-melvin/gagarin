// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Scalar deleting destructors of two WOL dialog controls and of MapSelect.
// Each runs the destructor inline (own vtable store where the class declares
// a destructor, member destructors in reverse order, then the base), frees
// the object when bit 0 of the flag is set and returns `this`.
//
// RTTI chains: CreateGameDialogControl -> WonlineStringDialogControl ->
// SimpleWonlineDialogControl -> OwnerDraw::SimpleDialogControl ->
// OwnerDraw::DialogControl, and MapSelect -> MSEngine. The DialogControl
// destructor (0x624130) and the MSEngine destructor (0x5D1B30) are out of
// line here; SimpleDialogControl and CreateGameDialogControl have implicit
// destructors (no vtable store of their own). Slot 0 is modelled as an
// ordinary virtual holding the deleting wrapper, as FileClass does in
// match/core/ram_file_class.h, because nothing is constructed in this file.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Out-of-line destructor 0x7B46F0 (a four-byte member: a string handle).
class Member_7B46F0
{
public:
    ~Member_7B46F0();
    void* Data;
};

// MapStageList::~MapStageList is the out-of-line destructor at 0x5CEE60.
class MapStageList
{
public:
    ~MapStageList();
};

namespace OwnerDraw {

class DialogControl
{
public:
    ~DialogControl();   // 0x624130
    virtual void* DeletingDtor(unsigned int flags);
    int unknown_04;     // +0x04
    int unknown_08;     // +0x08
};

class SimpleDialogControl : public DialogControl
{
};

}  // namespace OwnerDraw

// VTABLE: GAMEMD 0x7F7624
class SimpleWonlineDialogControl : public OwnerDraw::SimpleDialogControl
{
public:
    ~SimpleWonlineDialogControl() {}
};

// VTABLE: GAMEMD 0x7F7874
class WonlineStringDialogControl : public SimpleWonlineDialogControl
{
public:
    ~WonlineStringDialogControl() {}
    virtual void* DeletingDtor(unsigned int flags);
    Member_7B46F0 String;   // +0x0C
};

class CreateGameDialogControl : public WonlineStringDialogControl
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

GG_STATIC_ASSERT(offsetof(WonlineStringDialogControl, String) == 0x0C);

class MSEngine
{
public:
    ~MSEngine();   // 0x5D1B30
    virtual void* DeletingDtor(unsigned int flags);
    char unknown_04[0x4C];   // +0x04
};

// Implicit destructor: the members, then the MSEngine one.
class MapSelect : public MSEngine
{
public:
    virtual void* DeletingDtor(unsigned int flags);
    MapStageList Stages;        // +0x50
    char unknown_51[0x77];      // +0x51
    Member_7B46F0 Member_C8;    // +0xC8
};

GG_STATIC_ASSERT(offsetof(MapSelect, Stages) == 0x50);
GG_STATIC_ASSERT(offsetof(MapSelect, Member_C8) == 0xC8);

// FUNCTION: GAMEMD 0x5AE5A0
void* MapSelect::DeletingDtor(unsigned int flags)
{
    this->~MapSelect();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x7AC5D0
void* WonlineStringDialogControl::DeletingDtor(unsigned int flags)
{
    this->~WonlineStringDialogControl();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x7AC630
void* CreateGameDialogControl::DeletingDtor(unsigned int flags)
{
    this->~CreateGameDialogControl();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}
