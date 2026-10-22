// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Flags: /GX is left off. A paired /GX probe changes nothing except the compiler-emitted scalar deleting
//   destructors, which stop inlining their bodies with it (0x558060 and 0x488F00 -> 0%,
//   0x4B55F0 -> 17.6%); every other function here scores identically with and without it.
//   Lists cluster: GadgetClass slots that are shared by every gadget vtable (bodies ordered by address).
#include "lists_views.h"

// FUNCTION: GAMEMD 0x488690
// GadgetClass::MarkListToRedraw slot (+0x38): clears the "last list" global.
void GadgetClass::MarkListToRedraw()
{
    GadgetClass_LastList = 0;
}

// FUNCTION: GAMEMD 0x4886A0
// GadgetClass::IsToRedraw slot (+0x60): returns the repaint byte.
unsigned char GadgetClass::IsToRedraw()
{
    return IsToRepaint;
}

// FUNCTION: GAMEMD 0x4E13F0
// GadgetClass::Clicked slot (+0x80): a press inside the rectangle (or on the sticky/pressed gadget)
// is forwarded to Action with the event bits this gadget listens for.
int GadgetClass::Clicked(unsigned* key, unsigned flags, int x, int y, int modifier)
{
    flags &= Flags;
    if (this != GadgetClass_StuckOn && !(flags & 0x100)) {
        if (!flags || (unsigned)(x - X) >= (unsigned)Width || (unsigned)(y - Y) >= (unsigned)Height) {
            return 0;
        }
    }
    return Action(flags, key, modifier);
}

// FUNCTION: GAMEMD 0x4E1640
// CAPPED at 80.0% after four attempts (natural form; assignment inside the Clicked call with a do-while loop; a
// 16-bit Down() argument; combined forms). Remaining delta: the vtable pointer is loaded into edx where this build
// uses eax at five call sites, the key operand of the second Down() of each modifier pair is loaded after the
// keyboard pointer instead of before it, and the tail of the gadget loop is laid out with an extra jump.
// GadgetClass::Input slot (+0x28): polls the keyboard/mouse once, tracks the hovered gadget, builds the event
// flag word and offers the event to the sticky gadget, the focused gadget, or each gadget of the list in turn.
unsigned GadgetClass::Input()
{
    int newList = 0;
    if (GadgetClass_LastList != this) {
        GadgetClass_LastList = this;
        newList = 1;
        GadgetClass_StuckOn = 0;
        GadgetClass_Focused = 0;
    }

    unsigned key = DAT_0087F770->Check() & 0xFFFF;
    if (key) {
        key = DAT_0087F770->Get() & 0xFFFF;
    }

    int mx;
    int my;
    if ((key & 0xFF) == 1 || (key & 0xFF) == 2) {
        mx = DAT_0087F770->MouseX;
        my = DAT_0087F770->MouseY;
    } else {
        mx = DAT_00887640->GetX();
        my = DAT_00887640->GetY();
    }

    GadgetClass* hit = ExtractGadgetAt(mx, my);
    if (hit != GadgetClass_Hovered) {
        if (GadgetClass_Hovered) {
            GadgetClass_Hovered->OnMouseLeave();
        }
        GadgetClass_Hovered = hit;
        if (hit) {
            hit->OnMouseEnter();
        }
    }

    unsigned flags = 0;
    if (key) {
        if (key == 1) {
            flags = 1;
        } else if (key == 2) {
            flags = 0x10;
        } else if (key == 0x801) {
            flags = 4;
        } else if (key == 0x802) {
            flags = 0x40;
        }
    }

    unsigned modifier = 0;
    if (DAT_0087F770->Down(DAT_00A8EC08) || DAT_0087F770->Down(DAT_00A8EC0C)) {
        modifier = 1;
    }
    if (DAT_0087F770->Down(DAT_00A8EC00) || DAT_0087F770->Down(DAT_00A8EC04)) {
        modifier |= 2;
    }
    if (DAT_0087F770->Down(DAT_00A8EBF8) || DAT_0087F770->Down(DAT_00A8EBFC)) {
        modifier |= 4;
    }

    if (key) {
        if (!flags) {
            flags = 0x100;
        }
    } else {
        if (DAT_0087F770->Down(1)) {
            flags |= 2;
        } else {
            flags |= 8;
        }
        if (DAT_0087F770->Down(2)) {
            flags |= 0x20;
        } else {
            flags |= 0x80;
        }
    }

    GadgetClass* gadget;
    if (GadgetClass_StuckOn) {
        GadgetClass_StuckOn->Draw(0);
        (gadget = GadgetClass_StuckOn)->Clicked(&key, flags, mx, my, 0);
        if (GadgetClass_StuckOn) {
            GadgetClass_StuckOn->Draw(0);
            return key;
        }
    } else if (GadgetClass_Focused && (flags & 0x100)) {
        GadgetClass_Focused->Draw(0);
        GadgetClass_Focused->Clicked(&key, flags, mx, my, 0);
        if (GadgetClass_Focused) {
            GadgetClass_Focused->Draw(0);
        }
        return key;
    } else {
        gadget = this;
        if (!gadget) {
            return key;
        }
        do {
            gadget->Draw(newList);
            if (!gadget->IsDisabled && gadget->Clicked(&key, flags, mx, my, modifier)) {
                break;
            }
            gadget = (GadgetClass*)gadget->GetNext();
        } while (gadget);
        if (!gadget) {
            return key;
        }
    }
    gadget->Draw(0);
    return key;
}

// FUNCTION: GAMEMD 0x4E1920
// GadgetClass::ExtractGadget slot (+0x34): walks the list from this gadget for the one whose ID matches.
GadgetClass* GadgetClass::ExtractGadget(unsigned id)
{
    GadgetClass* gadget = this;
    if (id) {
        while (gadget) {
            if (gadget->GetID() == id) {
                return gadget;
            }
            gadget = (GadgetClass*)gadget->GetNext();
        }
    }
    return 0;
}
