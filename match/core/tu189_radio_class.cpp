// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// TU189 is a provisional grouping of this RadioClass address run. No original
// filename is attested; the header-initializer bounds do not prove a complete TU.
// RadioLinks' own RTTI at 0x816880 identifies VectorClass<TechnoClass*>.
#include "../_layout/radio_class.h"
#include "../_layout/techno_class.h"

TechnoClass* __fastcall FUN_0040DD70(ObjectClass* object); // GAMEMD 0x40DD70; checked type filter

// GLOBAL: GAMEMD 0xA8EC30
// Slot 158 passes this address as the opaque second argument to slot 159.
extern char DAT_00A8EC30[];

// TU-WINDOW: past the proven header-initializer end 0x65A746.
// FUNCTION: GAMEMD 0x0065A970
int RadioClass::vf_159(int command, void* data, RadioClass* peer)
{
    if (!peer) {
        peer = RadioLinks.Items[0];
        if (!peer) {
            return 0;
        }
    }

    if (command == 3) {
        for (int i = 0; i < RadioLinks.Capacity; ++i) {
            if (RadioLinks.Items[i] == peer) {
                RadioLinks.Items[i] = 0;
            }
        }
    }

    if (command == 2) {
        int slot = -1;
        for (int i = 0; i < RadioLinks.Capacity; ++i) {
            if (slot == -1 && RadioLinks.Items[i] == 0) {
                slot = i;
            }
            if (RadioLinks.Items[i] == peer) {
                return 1;
            }
        }

        if (slot == -1) {
            vf_158(3, RadioLinks.Items[0]);
            slot = 0;
        }

        int response = peer->vf_101(
            reinterpret_cast<int>(FUN_0040DD70(this)),
            2,
            reinterpret_cast<int>(data));
        if (response != 1) {
            return 10;
        }

        // Native stores this RadioClass* into VectorClass<TechnoClass*>::Items.
        // The binary's object/RTTI contract places TechnoClass at RadioBase+0,
        // and RadioLinks is proven to contain TechnoClass* elements.
        RadioLinks.Items[slot] = static_cast<TechnoClass*>(peer);
        return 1;
    }

    return peer->vf_101(
        reinterpret_cast<int>(FUN_0040DD70(this)),
        command,
        reinterpret_cast<int>(data));
}


// FUNCTION: GAMEMD 0x65AAA0
int RadioClass::vf_158(int command, RadioClass* peer)
{
    return vf_159(command, DAT_00A8EC30, peer);
}

// TU-WINDOW: past the proven header-initializer end 0x65A746.
// FUNCTION: GAMEMD 0x0065ACB0
int RadioClass::vf_157(int command)
{
    TechnoClass* first = RadioLinks.Items[0];
    if (first) {
        return vf_159(command, DAT_00A8EC30, first);
    }
    return 0;
}

// FUNCTION: GAMEMD 0x0065ACE0
void RadioClass::vf_160(int command)
{
    for (int i = 0; i < RadioLinks.Capacity; ++i) {
        TechnoClass* peer = RadioLinks.Items[i];
        if (peer) {
            vf_159(command, DAT_00A8EC30, peer);
        }
    }
}

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
