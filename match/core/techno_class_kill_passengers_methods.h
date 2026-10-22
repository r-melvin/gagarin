// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and offsets read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x707CB0. Three callee bindings come from YRpp
//   and are reconfirmed against the disassembly:
//   0x473430 = PassengersClass::RemoveFirstPassenger, 0x6EA870 =
//   TeamClass::LiberateMember, 0x707CB0 = TechnoClass::KillPassengers itself
//   (the recursive call at 0x707CF5 confirms it). 0x473450 is the out-of-line
//   PassengersClass::GetFirstPassenger — YRpp inlines that accessor, but retail
//   has a real function, called here and by MarkPassengersAsExited with the
//   same `ECX = this + 0x114`.
#ifndef GG_MATCH_CORE_TECHNO_CLASS_KILL_PASSENGERS_METHODS_H
#define GG_MATCH_CORE_TECHNO_CLASS_KILL_PASSENGERS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class TechnoClass;
class FootClass;

class TeamClass
{
public:
    void LiberateMember(FootClass* foot, int idx, unsigned char count);  // GAMEMD 0x6EA870
};

// PassengersClass — the cargo list embedded in TechnoClass at +0x114. The
// NumPassengers test at `[EBX+0x118]` puts the count at +0x04 of the record.
struct PassengersClass
{
    FootClass* FirstPassenger;   // +0x00
    int        NumPassengers;    // +0x04

    FootClass* GetFirstPassenger();      // GAMEMD 0x473450 (declared; reloc)
    FootClass* RemoveFirstPassenger();   // GAMEMD 0x473430 (declared; reloc)
};
GG_STATIC_ASSERT(offsetof(PassengersClass, NumPassengers) == 0x04);

// The two passenger virtuals are declared for real rather than reached through
// the tree's usual __fastcall-fn-pointer idiom. That shortcut works for
// zero-argument slots, but +0xE0 takes one: retail *pushes* the killer
// (`PUSH EBP; MOV ECX,ESI; CALL [EAX+0xE0]`), which is __thiscall, whereas an
// __fastcall stand-in would put the second argument in EDX. Declaring the full
// slot run up to +0xF8 is what gets the convention and the index both right.
class FootClass
{
public:
    virtual void v00() = 0;                   // vtable +0x00
    virtual void v04() = 0;                   // vtable +0x04
    virtual void v08() = 0;                   // vtable +0x08
    virtual void v0C() = 0;                   // vtable +0x0C
    virtual void v10() = 0;                   // vtable +0x10
    virtual void v14() = 0;                   // vtable +0x14
    virtual void v18() = 0;                   // vtable +0x18
    virtual void v1C() = 0;                   // vtable +0x1C
    virtual void v20() = 0;                   // vtable +0x20
    virtual void v24() = 0;                   // vtable +0x24
    virtual void v28() = 0;                   // vtable +0x28
    virtual void v2C() = 0;                   // vtable +0x2C
    virtual void v30() = 0;                   // vtable +0x30
    virtual void v34() = 0;                   // vtable +0x34
    virtual void v38() = 0;                   // vtable +0x38
    virtual void v3C() = 0;                   // vtable +0x3C
    virtual void v40() = 0;                   // vtable +0x40
    virtual void v44() = 0;                   // vtable +0x44
    virtual void v48() = 0;                   // vtable +0x48
    virtual void v4C() = 0;                   // vtable +0x4C
    virtual void v50() = 0;                   // vtable +0x50
    virtual void v54() = 0;                   // vtable +0x54
    virtual void v58() = 0;                   // vtable +0x58
    virtual void v5C() = 0;                   // vtable +0x5C
    virtual void v60() = 0;                   // vtable +0x60
    virtual void v64() = 0;                   // vtable +0x64
    virtual void v68() = 0;                   // vtable +0x68
    virtual void v6C() = 0;                   // vtable +0x6C
    virtual void v70() = 0;                   // vtable +0x70
    virtual void v74() = 0;                   // vtable +0x74
    virtual void v78() = 0;                   // vtable +0x78
    virtual void v7C() = 0;                   // vtable +0x7C
    virtual void v80() = 0;                   // vtable +0x80
    virtual void v84() = 0;                   // vtable +0x84
    virtual void v88() = 0;                   // vtable +0x88
    virtual void v8C() = 0;                   // vtable +0x8C
    virtual void v90() = 0;                   // vtable +0x90
    virtual void v94() = 0;                   // vtable +0x94
    virtual void v98() = 0;                   // vtable +0x98
    virtual void v9C() = 0;                   // vtable +0x9C
    virtual void vA0() = 0;                   // vtable +0xA0
    virtual void vA4() = 0;                   // vtable +0xA4
    virtual void vA8() = 0;                   // vtable +0xA8
    virtual void vAC() = 0;                   // vtable +0xAC
    virtual void vB0() = 0;                   // vtable +0xB0
    virtual void vB4() = 0;                   // vtable +0xB4
    virtual void vB8() = 0;                   // vtable +0xB8
    virtual void vBC() = 0;                   // vtable +0xBC
    virtual void vC0() = 0;                   // vtable +0xC0
    virtual void vC4() = 0;                   // vtable +0xC4
    virtual void vC8() = 0;                   // vtable +0xC8
    virtual void vCC() = 0;                   // vtable +0xCC
    virtual void vD0() = 0;                   // vtable +0xD0
    virtual void vD4() = 0;                   // vtable +0xD4
    virtual void vD8() = 0;                   // vtable +0xD8
    virtual void vDC() = 0;                   // vtable +0xDC
    virtual void Slot_E0(TechnoClass* killer);   // vtable +0xE0  <- used
    virtual void vE4() = 0;                   // vtable +0xE4
    virtual void vE8() = 0;                   // vtable +0xE8
    virtual void vEC() = 0;                   // vtable +0xEC
    virtual void vF0() = 0;                   // vtable +0xF0
    virtual void vF4() = 0;                   // vtable +0xF4
    virtual void Slot_F8();                      // vtable +0xF8  <- used

    char       _pad004[0x14 - 4];    // +0x0004  (vptr occupies +0x0000)
    unsigned char unknown_14;        // +0x0014  AbstractClass flag word (low byte)
    char       _pad015[0x30 - 0x15]; // +0x0015
    void*      NextObject;           // +0x0030  ObjectClass
    char       _pad034[0x82 - 0x34]; // +0x0034
    bool       InOpenToppedTransport;// +0x0082  ObjectClass
    char       _pad083[0x5D4 - 0x83];// +0x0083
    TeamClass* Team;                 // +0x05D4
};
GG_STATIC_ASSERT(offsetof(FootClass, unknown_14)            == 0x14);
GG_STATIC_ASSERT(offsetof(FootClass, NextObject)            == 0x30);
GG_STATIC_ASSERT(offsetof(FootClass, InOpenToppedTransport) == 0x82);
GG_STATIC_ASSERT(offsetof(FootClass, Team) == 0x5D4);

// Retail RTTI 0x817B58 establishes the class key; public access preserves this ABI view.
class TechnoClass
{
public:
    char            _pad000[0x114];   // +0x0000
    PassengersClass Passengers;       // +0x0114 (NumPassengers lands at +0x118)

    void KillPassengers(TechnoClass* source);   // GAMEMD 0x707CB0
    void MarkPassengersAsExited();              // GAMEMD 0x7104C0
};
GG_STATIC_ASSERT(offsetof(TechnoClass, Passengers) == 0x114);

#endif  // GG_MATCH_CORE_TECHNO_CLASS_KILL_PASSENGERS_METHODS_H
