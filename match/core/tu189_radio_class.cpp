// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// TU189 is a provisional grouping of this RadioClass address run. No original
// filename is attested; the header-initializer bounds do not prove a complete TU.
// RadioLinks' own RTTI at 0x816880 identifies VectorClass<TechnoClass*>.
#include "../_layout/radio_class.h"
#include "../_layout/techno_class.h"

// GLOBAL: GAMEMD 0xA8EC30
// Slot 158 passes this address as the opaque second argument to slot 159.
extern char DAT_00A8EC30[];

// TU-WINDOW: past the proven header-initializer end 0x65A746.
// FUNCTION: GAMEMD 0x65AAA0
int RadioClass::vf_158(int command, RadioClass* peer)
{
    return vf_159(command, DAT_00A8EC30, peer);
}

// TU-WINDOW: past the proven header-initializer end 0x65A746.
// FUNCTION: GAMEMD 0x65AD30
TechnoClass* RadioClass::FUN_0065AD30(int index)
{
    return RadioLinks.Items[index];
}

// TU-WINDOW: past the proven header-initializer end 0x65A746.
// FUNCTION: GAMEMD 0x65AD40
TechnoClass* RadioClass::FUN_0065AD40(int index)
{
    return RadioLinks.Items[index];
}

// TU-WINDOW: past the proven header-initializer end 0x65A746.
// FUNCTION: GAMEMD 0x65AD50  (__thiscall)
// Whether pLink is one of the radio links. Retail inlined FindLinkIndex's
// search loop here (the loop counter is the result), so reproduce it inline.
bool RadioClass::ContainsLink(const TechnoClass* pLink) const
{
    int idx;
    if (pLink) {
        for (idx = 0; idx < this->RadioLinks.Capacity; idx++) {
            if (this->RadioLinks.Items[idx] == pLink)
                goto done;
        }
    }
    idx = -1;
done:
    return idx != -1;
}

// TU-WINDOW: past the proven header-initializer end 0x65A746.
// FUNCTION: GAMEMD 0x65AD90  (__thiscall)
// Index of pLink in RadioLinks, or -1. A null pLink always returns -1.
int RadioClass::FindLinkIndex(const TechnoClass* pLink) const
{
    if (pLink) {
        for (int i = 0; i < this->RadioLinks.Capacity; i++) {
            if (this->RadioLinks.Items[i] == pLink)
                return i;
        }
    }
    return -1;
}

// TU-WINDOW: past the proven header-initializer end 0x65A746.
// FUNCTION: GAMEMD 0x65ADC0  (__thiscall)
// True if any slot is empty (i.e. the vector is not full).
bool RadioClass::HasFreeLink() const
{
    for (int i = 0; i < this->RadioLinks.Capacity; i++) {
        if (this->RadioLinks.Items[i] == 0)
            return true;
    }
    return false;
}

// TU-WINDOW: past the proven header-initializer end 0x65A746.
// FUNCTION: GAMEMD 0x65ADF0  RadioClass::HasFreeLinkFor (__thiscall, ret 0x4)
// The one-argument sibling of HasFreeLink above: a slot counts as available if
// it is empty *or* already points at the object asking, so re-establishing an
// existing link never fails for want of room.
bool RadioClass::HasFreeLinkFor(RadioClass* who) const
{
    for (int i = 0; i < RadioLinks.Capacity; i++) {
        RadioClass* link = RadioLinks.Items[i];
        if (link == 0 || link == who)
            return true;
    }
    return false;
}

// TU-WINDOW: past the proven header-initializer end 0x65A746.
// FUNCTION: GAMEMD 0x65AE30  (__thiscall)
// True if at least one slot is occupied.
bool RadioClass::HasAnyLink() const
{
    for (int i = 0; i < this->RadioLinks.Capacity; i++) {
        if (this->RadioLinks.Items[i] != 0)
            return true;
    }
    return false;
}

// TU-WINDOW: past the proven header-initializer end 0x65A746.
// FUNCTION: GAMEMD 0x65AE60  (__thiscall)
// Grow RadioLinks to `count` slots and null the freshly added elements.
void RadioClass::SetLinkCount(int count)
{
    int oldCapacity = this->RadioLinks.Capacity;
    if (count > oldCapacity) {
        this->RadioLinks.SetCapacity(count, 0);
        for (int i = oldCapacity; i < count; i++)
            this->RadioLinks.Items[i] = 0;
    }
}
