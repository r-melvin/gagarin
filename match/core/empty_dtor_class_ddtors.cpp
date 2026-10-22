// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Unrelated single classes with empty destructors.
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

// VTABLE: GAMEMD 0x7E35A8
class Animate
{
public:
    ~Animate() {}
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x7EF720
namespace OwnerDraw {
class DialogControl
{
public:
    ~DialogControl() {}
    virtual void* DeletingDtor(unsigned int flags);
};
}

// VTABLE: GAMEMD 0x7EFDA4
class PixelFXClass
{
public:
    ~PixelFXClass() {}
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x7F0954
class ReferenceCounted
{
public:
    ~ReferenceCounted() {}
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x7EA57C
class VersionClass
{
public:
    ~VersionClass() {}
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EF738
namespace OwnerDraw {
class SimpleDialogControl : public DialogControl
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};
}

// FUNCTION: GAMEMD 0x427270 -- Animate scalar deleting destructor
void* Animate::DeletingDtor(unsigned int flags)
{
    this->~Animate();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x4E8270 -- VersionClass scalar deleting destructor
void* VersionClass::DeletingDtor(unsigned int flags)
{
    this->~VersionClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x6244A0 -- OwnerDraw::DialogControl scalar deleting destructor
void* OwnerDraw::DialogControl::DeletingDtor(unsigned int flags)
{
    this->~DialogControl();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x6244C0 -- OwnerDraw::SimpleDialogControl scalar deleting destructor
void* OwnerDraw::SimpleDialogControl::DeletingDtor(unsigned int flags)
{
    this->~SimpleDialogControl();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x631F40 -- PixelFXClass scalar deleting destructor
void* PixelFXClass::DeletingDtor(unsigned int flags)
{
    this->~PixelFXClass();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x65D6A0 -- ReferenceCounted scalar deleting destructor
void* ReferenceCounted::DeletingDtor(unsigned int flags)
{
    this->~ReferenceCounted();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}
