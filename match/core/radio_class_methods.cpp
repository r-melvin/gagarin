// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Offsets
//   derived numerically from the disassembly (RadioLinks.Items @ [this+0xE4],
//   RadioLinks.Capacity @ [this+0xE8]); names cross-checked vs YRpp.
//
// reccmp annotations (by retail address):
//   FUNCTION: GAMEMD 0x65AD50  RadioClass::ContainsLink   (__thiscall)
//   FUNCTION: GAMEMD 0x65AD90  RadioClass::FindLinkIndex  (__thiscall)
//   FUNCTION: GAMEMD 0x65ADC0  RadioClass::HasFreeLink    (__thiscall)
//   FUNCTION: GAMEMD 0x65AE30  RadioClass::HasAnyLink     (__thiscall)
//   FUNCTION: GAMEMD 0x65AE60  RadioClass::SetLinkCount   (__thiscall)
//
// NOTE on physical order: FindLinkIndex (0x65AD90) is defined before
// ContainsLink (0x65AD50) so that /O2 /Ob2 auto-inlines its body into
// ContainsLink (which the retail compiler did — ContainsLink contains the
// search loop inline, not a CALL). Both retain a standalone external symbol.

#include "radio_class_methods.h"

// Real-virtual view of RadioLinks (a VectorClass) used only to issue the
// inlined virtual SetCapacity call. VC6 slots virtuals in declaration order:
//   slot 0 = ~VectorClass, slot 1 = operator==, slot 2 = SetCapacity (+0x8).
// This reproduces retail's `MOV EAX,[vptr]; CALL [EAX+8]` at 0x65AE82.
struct VectorClassVT
{
    virtual ~VectorClassVT();
    virtual bool operator==(const VectorClassVT& other) const;
    virtual bool SetCapacity(int capacity, void* pMem);
};

// FUNCTION: GAMEMD 0x65AD90  (__thiscall)
// Index of pLink in RadioLinks, or -1. A null pLink always returns -1.
int RadioClass::FindLinkIndex(const TechnoClass* pLink) const
{
    if (pLink) {
        for (int i = 0; i < this->RadioLinks.Capacity; i++) {
            if (((const TechnoClass**)this->RadioLinks.Items)[i] == pLink)
                return i;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x65AD50  (__thiscall)
// Whether pLink is one of the radio links. Retail inlined FindLinkIndex's
// search loop here (the loop counter is the result), so reproduce it inline.
bool RadioClass::ContainsLink(const TechnoClass* pLink) const
{
    int idx;
    if (pLink) {
        for (idx = 0; idx < this->RadioLinks.Capacity; idx++) {
            if (((const TechnoClass**)this->RadioLinks.Items)[idx] == pLink)
                goto done;
        }
    }
    idx = -1;
done:
    return idx != -1;
}

// FUNCTION: GAMEMD 0x65ADC0  (__thiscall)
// True if any slot is empty (i.e. the vector is not full).
bool RadioClass::HasFreeLink() const
{
    for (int i = 0; i < this->RadioLinks.Capacity; i++) {
        if (((const TechnoClass**)this->RadioLinks.Items)[i] == 0)
            return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x65ADF0  RadioClass::HasFreeLinkFor (__thiscall, ret 0x4)
// The one-argument sibling of HasFreeLink above: a slot counts as available if
// it is empty *or* already points at the object asking, so re-establishing an
// existing link never fails for want of room.
bool RadioClass::HasFreeLinkFor(RadioClass* who) const
{
    for (int i = 0; i < RadioLinks.Capacity; i++) {
        RadioClass* link = ((RadioClass**)RadioLinks.Items)[i];
        if (link == 0 || link == who)
            return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x65AE30  (__thiscall)
// True if at least one slot is occupied.
bool RadioClass::HasAnyLink() const
{
    for (int i = 0; i < this->RadioLinks.Capacity; i++) {
        if (((const TechnoClass**)this->RadioLinks.Items)[i] != 0)
            return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x65AE60  (__thiscall)
// Grow RadioLinks to `count` slots and null the freshly added elements.
void RadioClass::SetLinkCount(int count)
{
    int oldCapacity = this->RadioLinks.Capacity;
    if (count > oldCapacity) {
        ((VectorClassVT*)&this->RadioLinks)->SetCapacity(count, 0);
        for (int i = oldCapacity; i < count; i++)
            ((TechnoClass**)this->RadioLinks.Items)[i] = 0;
    }
}
