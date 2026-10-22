// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Retail vtable 0x7E528C, constructor 0x48E520 and accesses at
// 0x48E600..0x48E640 establish the GadgetClass base and appended members.
#ifndef GG_MATCH_UI_CONTROL_CLASS_H
#define GG_MATCH_UI_CONTROL_CLASS_H
#include "gadget_class_methods.h"
#include "control_class_vtable_layout.h"

// VTABLE: GAMEMD 0x7E528C
class ControlClass : public GadgetClass
{
public:
    // The inherited virtual destructor is implicit; retail calls Gadget destruction.
    virtual unsigned int GetID();                         // slot 17, 0x48E610
    virtual int Draw(int forced);                         // slot 27, 0x48E620
    virtual int Action(unsigned flags, unsigned* key, int modifier); // slot 31, 0x48E5A0
    virtual void SetPeer(GadgetClass* peer);              // slot 33, 0x48E600 (stores +0x28)

    // FUNCTION: GAMEMD 0x48E520 (decl)
    ControlClass(int id, int x, int y, int width, int height,
                 unsigned int flags, char sticky);

    unsigned int ID;              // +0x24, GetID
    GadgetClass* Peer;             // +0x28, stored by 0x48E600; Draw calls slot +0x6C, Action slot +0x4C
};
GG_STATIC_ASSERT(offsetof(ControlClass, ID) == 0x24);
GG_STATIC_ASSERT(offsetof(ControlClass, Peer) == 0x28);
GG_STATIC_ASSERT(sizeof(ControlClass) == 0x2C);
#endif
