// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every vtable constant, member displacement and relayed address below read
//   numerically off the user's retail gamemd.exe v1.001 with the local Ghidra
//   CLI: the vtables from the `MOV dword ptr [ESI+n],imm32` stores, the
//   subobject displacements from the store offsets (+0x00, +0x04, +0x18), the
//   COM member displacement from `MOV EAX,[ESI+n]`, and the relayed addresses
//   from the CALL displacements. None of these classes is bound by YRpp,
//   so all keep placeholder names built from their own addresses.
//
// Two destructor shapes for classes that carry more than one vtable, both
// relaying to the same base destructor at 0x55A6F0:
//
//   COMREL  45 bytes: seat three vtables (+0x00, +0x04, +0x18), release the
//           COM interface held at one member, then call the base destructor.
//           `MOV ECX,[EAX]; PUSH EAX; CALL [ECX+8]` is an `__stdcall` COM
//           virtual at slot 2 — IUnknown::Release. Four instantiations, varying
//           in their three vtables and in where the interface pointer sits.
//   SDD43   43 bytes: seat two vtables (+0x00, +0x04), call the base
//           destructor, then free the object when the caller's deleting bit is
//           set — the scalar-deleting destructor of the same kind of class.
//           Three instantiations, varying only in their two vtables.
//
// Phrasing notes (two levers, both worth the whole family):
//   * The destructors are declared `throw()`. That was measured under the
//     tree's old /GX default, where COMREL's base-destructor call made cl emit
//     a full EH unwind frame retail does not have (0.0%); the default no
//     longer has /GX.
//   * With the release written directly in the destructor body, cl hoists the
//     interface load above the three vtable stores (66.7%). Retail stores all
//     three vtables first. Moving the interface pointer into a small member
//     object whose own destructor does the release puts the load back where
//     retail has it: the member destructor is expanded after the vptr seats,
//     and cl no longer schedules across them. 66.7% -> 100%. A named local, a
//     `volatile` member and an inline free helper were all measured and none of
//     them moves the load.
#ifndef GG_MATCH_CORE_MULTI_VTABLE_DTOR_FAMILY_METHODS_H
#define GG_MATCH_CORE_MULTI_VTABLE_DTOR_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x7C8B3D (decl; reloc) — CRT free.
extern "C" void __cdecl gg_free(void* block);

// The minimal COM interface this family touches: only slot 2 is called.
struct IUnknownLite
{
    virtual long __stdcall QueryInterface(void* iid, void** out) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
};

// The shared base whose destructor is at 0x55A6F0, and the two other
// vtable-carrying bases. PrimaryBase sits at +0x00, SecondBase at +0x04 (which
// fixes its size at 0x14) and ThirdBase at +0x18.
// FUNCTION: GAMEMD 0x55A6F0 (decl; reloc) — PrimaryBase::~PrimaryBase.
class PrimaryBase
{
public:
    virtual ~PrimaryBase() throw();
    virtual void Slot1();
};

class SecondBase
{
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    int unknown_04;
    int unknown_08;
    int unknown_0C;
    int unknown_10;
};

class ThirdBase
{
public:
    virtual void Slot0();
    virtual void Slot1();
};

GG_STATIC_ASSERT(sizeof(PrimaryBase) == 0x4 && sizeof(SecondBase) == 0x14 &&
                 sizeof(ThirdBase) == 0x4);

// The COM holder. Making the release the holder's own destructor rather than a
// statement in the enclosing destructor is the scheduling lever described above.
struct ComHolder
{
    IUnknownLite* Interface;
    ~ComHolder() throw()
    {
        if (this->Interface != 0) {
            this->Interface->Release();
        }
    }
};

// COMREL. OFF is where the interface pointer sits; the three bases end at
// 0x1C, so the padding in front of it is OFF - 0x1C.
#define GG_COMREL_DECL(TAG, OFF)                                          \
class ComRel_##TAG : public PrimaryBase, public SecondBase, public ThirdBase \
{                                                                         \
public:                                                                   \
    virtual ~ComRel_##TAG() throw();                                      \
    char      _pad1C[(OFF) - 0x1C];                                       \
    ComHolder Holder;             /* +OFF */                              \
}

#define GG_COMREL_BODY(TAG) ComRel_##TAG::~ComRel_##TAG() throw() {}

// SDD43. Only the two seated vtables reach the code, so only they are modelled;
// the base destructor is taken as a __fastcall extern rather than a real base
// so the deleting tail can be written directly.
// FUNCTION: GAMEMD 0x55A6F0 (decl; reloc) — the same base destructor COMREL
// relays to, reached here through a plain declaration.
void PrimaryBaseDtor(void* self);

struct MultiVtableObject
{
    char* Vptr00;                 /* +0x0000 */
    char* Vptr04;                 /* +0x0004 */

    MultiVtableObject* FUN_004D03A0(char flags);
};
GG_STATIC_ASSERT(offsetof(MultiVtableObject, Vptr04) == 0x4);

#define GG_SDD43_BODY(TAG, VT0, VT4)                                      \
MultiVtableObject* MultiVtableObject::FUN_##TAG(char flags)               \
{                                                                         \
    this->Vptr00 = &VT0;                                                  \
    this->Vptr04 = &VT4;                                                  \
    PrimaryBaseDtor(this);                                                \
    if (flags & 1) {                                                      \
        gg_free(this);                                                    \
    }                                                                     \
    return this;                                                          \
}

// VTABLE: GAMEMD 0x007E7F7C
// VTABLE: GAMEMD 0x007E7EB0
// VTABLE: GAMEMD 0x007E7E8C
GG_COMREL_DECL(004AF5E0, 0x68);
// VTABLE: GAMEMD 0x007E8344
// VTABLE: GAMEMD 0x007E8278
// VTABLE: GAMEMD 0x007E8254
GG_COMREL_DECL(004B5B00, 0x2C);
// VTABLE: GAMEMD 0x007F2E58
// VTABLE: GAMEMD 0x007F2D8C
// VTABLE: GAMEMD 0x007F2D68
GG_COMREL_DECL(0069ECF0, 0x68);
// VTABLE: GAMEMD 0x007F6AC4
// VTABLE: GAMEMD 0x007F69F8
// VTABLE: GAMEMD 0x007F69D4
GG_COMREL_DECL(0075AB00, 0x38);

GG_STATIC_ASSERT(offsetof(ComRel_004AF5E0, Holder) == 0x68 &&
                 offsetof(ComRel_004B5B00, Holder) == 0x2C &&
                 offsetof(ComRel_0069ECF0, Holder) == 0x68 &&
                 offsetof(ComRel_0075AB00, Holder) == 0x38);

// VTABLE: GAMEMD 0x007E8AC0
extern char VT_007E8AC0;
// VTABLE: GAMEMD 0x007E89F4
extern char VT_007E89F4;

// Address -> class map for COMREL. A destructor cannot be redeclared at
// namespace scope, so its reccmp `// FUNCTION:` annotations live on the bodies
// in the .cpp; this is the index.
//   0x004AF5E0  ->  ComRel_004AF5E0::~ComRel_004AF5E0
//   0x004B5B00  ->  ComRel_004B5B00::~ComRel_004B5B00
//   0x0069ECF0  ->  ComRel_0069ECF0::~ComRel_0069ECF0
//   0x0075AB00  ->  ComRel_0075AB00::~ComRel_0075AB00

#endif  // GG_MATCH_CORE_MULTI_VTABLE_DTOR_FAMILY_METHODS_H
