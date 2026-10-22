// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Score screen animation and campaign score classes.
//
// Scalar deleting destructors of classes whose destructor is empty. Each one
// stores the vtable of the class that declares the destructor (the derived
// classes add nothing to it), frees the object when bit 0 of the flag is set,
// and returns `this`. Retail's 32-byte shape:
//
//     MOV AL,[ESP+4]; PUSH ESI; MOV ESI,ECX; TEST AL,1; MOV [ESI],<vtable>
//     JZ +9; PUSH ESI; CALL 0x7C8B3D; ADD ESP,4; MOV EAX,ESI; POP ESI; RET 4
//
// Class names and the base relation come from the retail RTTI descriptors;
// the owning class of each body is the class whose vtable slot 0 holds it.
// Slot 0 is modelled as an ordinary virtual holding the deleting wrapper, as
// FileClass does in match/core/ram_file_class.h: these classes are never
// constructed in this translation unit, so cl would not emit their tables or
// a compiler-generated `??_G`. The classes are opaque views; no member is
// touched, so there is no layout to assert.

// VTABLE: GAMEMD 0x7E4AB8
class CampaignEndScoreClass
{
public:
    ~CampaignEndScoreClass() {}
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x7E4AAC
class CampaignScoreClass
{
public:
    ~CampaignScoreClass() {}
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x7F0EDC
class ScoreAnimClass
{
public:
    ~ScoreAnimClass() {}
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007F0EC8
class ScoreTimeClass : public ScoreAnimClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007F0EB4
class ScorePrintClass : public ScoreAnimClass
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};


// FUNCTION: GAMEMD 0x690FE0 -- ScoreAnimClass scalar deleting destructor
void* ScoreAnimClass::DeletingDtor(unsigned int flags)
{
    this->~ScoreAnimClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x691000 -- ScoreTimeClass scalar deleting destructor
void* ScoreTimeClass::DeletingDtor(unsigned int flags)
{
    this->~ScoreTimeClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x691020 -- ScorePrintClass scalar deleting destructor
void* ScorePrintClass::DeletingDtor(unsigned int flags)
{
    this->~ScorePrintClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}
