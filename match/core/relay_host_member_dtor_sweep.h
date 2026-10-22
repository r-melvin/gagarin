// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Both vtable constants and both relayed destructor addresses in each member
//   read numerically off the user's retail gamemd.exe v1.001 with the local
//   Ghidra CLI: the vtables from the two `MOV dword ptr [reg],imm32` stores, the
//   subobject displacement from `LEA ECX,[ESI+8]`, and the two destructor
//   addresses from the CALL displacements. Neither class is bound by YRpp,
//   so both keep placeholder names built from their own vtable.
//
// Shape (32 bytes):
//   `PUSH ESI; MOV ESI,ECX; LEA ECX,[ESI+8]; MOV [ESI],host-vtbl;
//    MOV [ECX],member-vtbl; CALL 0x65D460; MOV ECX,ESI; CALL 0x65D660;
//    POP ESI; RET`
//
// The destructor of a class with a base at +0x00 and a polymorphic member
// object at +0x08 whose own destructor — the "seat my vtable and tail-jump to
// my base destructor" shape — is expanded inline here. That inlining is why
// both vtables are seated in this one function and why two different base
// destructors are called, the member's with ECX pointing at +0x08.
//
// Phrasing notes (two levers, both needed):
//   * Under /GX (the tree's flag set when this was measured), a destructor
//     that destroys a subobject emits a full
//     EH unwind frame (`PUSH -1; PUSH 0; MOV EAX,FS:[0]; ...`) that retail does
//     not have — 0.0% against a body that is otherwise correct. Declaring every
//     destructor in the chain `throw()` removes the frame and the function
//     matches exactly.
//   * The +0x08 subobject is a MEMBER, not a second base class. Modelled as a
//     base, cl emits its null-guarded base cast (`NEG ECX; SBB ECX,ECX;
//     AND ECX,EAX`, 15.4%) where retail has a plain `LEA ECX,[ESI+8]`.
#ifndef GG_MATCH_CORE_RELAY_HOST_MEMBER_DTOR_SWEEP_H
#define GG_MATCH_CORE_RELAY_HOST_MEMBER_DTOR_SWEEP_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The two relayed-to base classes, named for the addresses this sweep proves
// they own. Only what reaches the code is modelled.
//   MemberBase: destructor 0x65D460, called with ECX at the member
//   HostBase:   destructor 0x65D660, and one dword at +0x04 (the member object
//               sits at +0x08, which fixes HostBase's size at 8)
class MemberBase { public: virtual ~MemberBase() throw(); virtual void Slot1(); };
class HostBase   { public: virtual ~HostBase() throw(); virtual void Slot1(); int unknown_04; };

GG_STATIC_ASSERT(sizeof(MemberBase) == 0x4 &&
                 offsetof(HostBase, unknown_04) == 0x4 && sizeof(HostBase) == 0x8);

// The embedded member type: adds nothing but its own vtable, and its destructor
// is defined inline so it expands into the host destructor.
#define GG_RELAY_MEMBER_DECL(TAG)                                         \
class RelayMember_##TAG : public MemberBase                               \
{                                                                         \
public:                                                                   \
    virtual ~RelayMember_##TAG() throw() {}                               \
    virtual void Slot1();                                                 \
}

// The enclosing class: a HostBase at +0x00 and the member at +0x08.
#define GG_RELAY_HOST_DECL(TAG, MEMBERTAG)                                \
class RelayHost_##TAG : public HostBase                                   \
{                                                                         \
public:                                                                   \
    virtual ~RelayHost_##TAG() throw();                                   \
    virtual void Slot1();                                                 \
    RelayMember_##MEMBERTAG member_08;                                    \
}

#define GG_RELAY_HOST_DTOR_BODY(TAG) \
    RelayHost_##TAG::~RelayHost_##TAG() throw() {}

// VTABLE: GAMEMD 0x007EBFA4
GG_RELAY_MEMBER_DECL(007EBFA4);
// VTABLE: GAMEMD 0x007F70EC
GG_RELAY_MEMBER_DECL(007F70EC);

// VTABLE: GAMEMD 0x007F6FC4
GG_RELAY_HOST_DECL(007F6FC4, 007EBFA4);
GG_STATIC_ASSERT(offsetof(RelayHost_007F6FC4, member_08) == 0x8 &&
                 sizeof(RelayHost_007F6FC4) == 0xC);

// VTABLE: GAMEMD 0x007F70DC
GG_RELAY_HOST_DECL(007F70DC, 007F70EC);
GG_STATIC_ASSERT(offsetof(RelayHost_007F70DC, member_08) == 0x8 &&
                 sizeof(RelayHost_007F70DC) == 0xC);

// VTABLE: GAMEMD 0x007F7314
GG_RELAY_HOST_DECL(007F7314, 007F70EC);
GG_STATIC_ASSERT(offsetof(RelayHost_007F7314, member_08) == 0x8 &&
                 sizeof(RelayHost_007F7314) == 0xC);

// Address -> class map. A destructor cannot be redeclared at namespace scope,
// so the reccmp `// FUNCTION:` annotations live on the bodies in the .cpp; this
// is the index.
//   0x00766030  ->  RelayHost_007F6FC4::~RelayHost_007F6FC4
//   0x00767BF0  ->  RelayHost_007F70DC::~RelayHost_007F70DC
//   0x0076F650  ->  RelayHost_007F7314::~RelayHost_007F7314

#endif  // GG_MATCH_CORE_RELAY_HOST_MEMBER_DTOR_SWEEP_H
