// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Flags: /GX is left off. A paired /GX probe changes nothing except the compiler-emitted scalar deleting
//   destructors, which stop inlining their bodies with it (0x558060 and 0x488F00 -> 0%,
//   0x4B55F0 -> 17.6%); every other function here scores identically with and without it.
//   Lists cluster: GadgetClass slots that are shared by every gadget vtable (bodies ordered by address).
#include "lists_views.h"
#include "../gadget_class_color_methods.h"

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

// FUNCTION: GAMEMD 0x4E12D0  GadgetClass::GetColorScheme (__fastcall, static)
// Entry 1 of the colour-scheme collection, dereferenced to its first field.
// A missing entry degrades to 0 rather than faulting.
int GadgetClass::GetColorScheme()
{
    void* scheme = ColorSchemeCollection_GetItem(ColorSchemeCollection, 1);
    if (scheme != 0)
        return *(int*)scheme;

    return 0;
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

// FUNCTION: GAMEMD 0x4E1450  GadgetClass::Enable (__thiscall)
// Clears IsDisabled, flags a redraw, then drops focus through the vtable
// (`jmp [eax+0x54]` — a tail call to slot 21, KillFocus).
void GadgetClass::Enable()
{
    IsDisabled = 0;
    IsToRepaint = 1;
    KillFocus();
}

// FUNCTION: GAMEMD 0x4E1460  GadgetClass::Disable (__thiscall)
// Same shape as Enable but sets IsDisabled; retail shares the constant 1 in AL
// across both byte stores (`mov al,1; mov [ecx+0x1e],al; mov [ecx+0x1c],al`).
void GadgetClass::Disable()
{
    IsDisabled = 1;
    IsToRepaint = 1;
    KillFocus();
}

// FUNCTION: GAMEMD 0x4E1470  GadgetClass::IsEnabled (__thiscall)
// Not a vtable entry — a plain inline-able accessor emitted out of line.
bool GadgetClass::IsEnabled() const
{
    return IsDisabled == 0;
}

// FUNCTION: GAMEMD 0x4E1480  GadgetClass::Remove (__thiscall)
// Drops focus (virtual slot 0x54) then unlinks via the LinkClass base.
LinkClass* GadgetClass::Remove()
{
    KillFocus();
    return LinkClass::Remove();
}

// FUNCTION: GAMEMD 0x4E14A0  GadgetClass::GetNext (__thiscall)
// Covariant forwarder to LinkClass::GetNext — retail is the bare tail `jmp`.
LinkClass* GadgetClass::GetNext()
{
    return LinkClass::GetNext();
}

// FUNCTION: GAMEMD 0x4E14B0  GadgetClass::GetPrev (__thiscall)
LinkClass* GadgetClass::GetPrev()
{
    return LinkClass::GetPrev();
}

// FUNCTION: GAMEMD 0x4E14C0  GadgetClass::DeleteList (__thiscall)
void GadgetClass::DeleteList()
{
    // Walk back to the head of the list.
    GadgetClass* cur  = this;
    GadgetClass* prev = (GadgetClass*)cur->GetPrev();
    while (prev != 0) {
        cur  = (GadgetClass*)cur->GetPrev();
        prev = (GadgetClass*)cur->GetPrev();
    }

    // Then destroy each gadget from head to tail.
    while (cur != 0) {
        cur->KillFocus();
        GadgetClass* temp = cur;
        cur = (GadgetClass*)cur->GetNext();
        delete temp;
    }
}

// FUNCTION: GAMEMD 0x4E1530  GadgetClass::Action (__thiscall, ret 0xC)
// Base action handler: any non-zero flag set means "this gadget was hit" —
// flag a redraw, run the sticky-capture state machine, and report handled.
int GadgetClass::Action(unsigned flags, unsigned* key, int modifier)
{
    if (flags != 0) {
        IsToRepaint = 1;
        StickyProcess(flags);
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4E1550  GadgetClass::Draw (__thiscall, ret 0x4)
// Redraw when forced or when the redraw byte is set, and clear that byte. `forced` is dword-wide here (retail: `mov eax,[esp+4]; test eax,eax`) —
// DrawAll below widens its own bool argument with `and edi,0xff` before pushing.
int GadgetClass::Draw(int forced)
{
    if (forced || IsToRepaint) {
        IsToRepaint = 0;
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4E1570  GadgetClass::DrawAll (__thiscall)
void GadgetClass::DrawAll(bool forced)
{
    GadgetClass* g = this;
    while (g != 0) {
        g->Draw(forced);
        g = (GadgetClass*)g->GetNext();
    }
}

// FUNCTION: GAMEMD 0x4E1640
// PARTIAL 89.2%. The list walk is a for loop whose exhaustion has its own
// `return key` and whose hit jumps to the shared redraw (retail has four return
// blocks; the do-while form with a post-loop test merged two of them, 80.0%).
// Remaining delta: the key operand of the second Down() of each modifier pair
// is loaded into ECX/EDX after the keyboard pointer instead of into EAX before
// it, and the vtable pointer register of five calls (register choice only).
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
        for (gadget = this; gadget; gadget = (GadgetClass*)gadget->GetNext()) {
            gadget->Draw(newList);
            if (!gadget->IsDisabled && gadget->Clicked(&key, flags, mx, my, modifier)) {
                goto redraw;
            }
        }
        return key;
    }
redraw:
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
// FUNCTION: GAMEMD 0x4E1960  GadgetClass::MarkRedraw (__thiscall)
void GadgetClass::MarkRedraw()
{
    IsToRepaint = 1;
}

// FUNCTION: GAMEMD 0x4E1970  GadgetClass::StickyProcess (__thiscall, ret 0x4)
// Mouse-capture state machine. Flag bits confirmed from the retail immediates:
//   0x11 = LEFTPRESS(0x01) | RIGHTPRESS(0x10)
//   0x44 = LEFTRELEASE(0x04) | RIGHTRELEASE(0x40)
// A sticky gadget grabs the capture on either press and releases it on either
// release. Retail's fallthrough (`jmp` past the CMP after the store) confirms
// the compiler knows GadgetClass_StuckOn == this on the taken branch.
void GadgetClass::StickyProcess(unsigned flags)
{
    if (IsSticky && (flags & 0x11) != 0) {
        GadgetClass_StuckOn = this;
    }

    if (GadgetClass_StuckOn == this && (flags & 0x44) != 0) {
        GadgetClass_StuckOn = 0;
    }
}

// FUNCTION: GAMEMD 0x4E19A0  GadgetClass::SetFocus (__thiscall)
void GadgetClass::SetFocus()
{
    if (GadgetClass_Focused != 0) {
        GadgetClass_Focused->MarkRedraw();
        GadgetClass_Focused->KillFocus();
    }
    this->Flags |= 0x100;
    GadgetClass_Focused = this;
}

// FUNCTION: GAMEMD 0x4E19D0  GadgetClass::KillFocus (__thiscall)
// Clears the focus bit only if *this* holds it. Retail clears bit 8 through AH
// (`mov eax,[ecx+0x20]; and ah,0xfe; mov [ecx+0x20],eax`) — the VC6 byte-lane
// idiom for `Flags &= ~0x100`.
void GadgetClass::KillFocus()
{
    if (GadgetClass_Focused == this) {
        Flags &= ~0x100;
        GadgetClass_Focused = 0;
    }
}

// FUNCTION: GAMEMD 0x4E19F0  GadgetClass::IsFocused (__thiscall)
bool GadgetClass::IsFocused()
{
    return this == GadgetClass_Focused;
}

// FUNCTION: GAMEMD 0x4E1A00  GadgetClass::IsListToRedraw (__thiscall)
// Walks the list from `this` forward; true if any gadget is dirty. Retail opens
// with `test ecx,ecx`, so the null check on `this` is in the source.
int GadgetClass::IsListToRedraw()
{
    GadgetClass* g = this;
    while (g != 0) {
        if (g->IsToRepaint) {
            return 1;
        }
        g = (GadgetClass*)g->GetNext();
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4E1A20  GadgetClass::SetPosition (__thiscall, ret 0x8)
void GadgetClass::SetPosition(int x, int y)
{
    X = x;
    Y = y;
}

// FUNCTION: GAMEMD 0x4E1A40  GadgetClass::SetDimension (__thiscall, ret 0x8)
void GadgetClass::SetDimension(int w, int h)
{
    Width = w;
    Height = h;
}
