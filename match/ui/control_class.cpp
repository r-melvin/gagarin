// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
#include "control_class.h"

// FUNCTION: GAMEMD 0x48E520
ControlClass::ControlClass(int id, int x, int y, int width, int height,
                           unsigned int flags, char sticky)
    : GadgetClass(x, y, width, height, flags, sticky), ID(id), unknown_28(0)
{
}

// FUNCTION: GAMEMD 0x48E5A0
int ControlClass::Action(unsigned flags, unsigned* key, int modifier)
{
    if (flags != 0) {
        unsigned int id = ID;
        if (id != 0) {
            id |= 0x8000;
            *key = id;
            if ((flags & 0x40) != 0 && (Flags & 0x10) != 0) {
                id |= 0x4000;
                *key = id;
            }
        } else {
            *key = 0;
        }
    }

    if (unknown_28 != 0) {
        unknown_28->PeerToPeer(flags, key, this);
    }

    return GadgetClass::Action(flags, key, 0);
}

// FUNCTION: GAMEMD 0x48E600
void ControlClass::FUN_0048E600(GadgetClass* gadget)
{
    unknown_28 = gadget;
}

// FUNCTION: GAMEMD 0x48E610
unsigned int ControlClass::GetID()
{
    return ID;
}

// FUNCTION: GAMEMD 0x48E620
int ControlClass::Draw(int forced)
{
    if (unknown_28) {
        unknown_28->Draw(0);
    }
    return GadgetClass::Draw(forced);
}
