// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | EA-GPL-RA1-reference
//   Bytes matched against retail gamemd.exe v1.001 across 0x4E1450..0x4E1A40
//   via the local Ghidra disassembly. Vtable/member offsets confirmed from the
//   0x7E92BC vtable dump (see gadget_class_methods.h). Method *names* and the
//   algorithm shape cross-checked against YRpp GadgetClass.h (consult-only) and
//   the EA RA1 GadgetClass (Enable/Disable/Remove/Draw_Me/Sticky_Process/
//   Action shapes survive verbatim; reference only, no transcription).
//
// GadgetClass — base of the WW GUI gadget hierarchy: a LinkClass list node plus
// a screen rectangle, redraw/sticky/disabled flags, and the focus bit (0x100).
// Functions below are ordered ascending by retail address.

#include "gadget_class_methods.h"

// The "currently focused gadget" global at 0x008B3E90. Read+written by SetFocus
// (and KillFocus); referenced here as an external so the compiler emits the
// absolute [0x8B3E90] memory accesses (relocation-normalised by the differ).
extern GadgetClass* GadgetClass_Focused;   // 0x008B3E90

// The "currently sticky gadget" global at 0x008B3E88 — the gadget that captured
// the mouse between a press and its matching release (StickyProcess).
extern GadgetClass* GadgetClass_StuckOn;    // 0x008B3E88

// GadgetClass::GetNext/GetPrev/Remove below forward to the LinkClass base with
// explicitly-qualified (non-virtual) calls — LinkClass::GetNext @0x556620,
// LinkClass::GetPrev @0x556630, LinkClass::Remove @0x556730 — matching retail's
// direct `jmp`/`call` to those addresses. See match/core/link_class_methods.h.

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
// The RA1 `Draw_Me` shape: redraw when forced or dirty, and consume the dirty
// bit. `forced` is dword-wide here (retail: `mov eax,[esp+4]; test eax,eax`) —
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

// FUNCTION: GAMEMD 0x4E15A0  GadgetClass::ExtractGadgetAt (__thiscall)
// Walk the list from this gadget and return the smallest enabled one whose
// rectangle contains the point, starting from a screen-sized best so the first
// hit always qualifies. Ties go to the later gadget (`<=`). The shape follows
// TS++'s Extract_Gadget_At_Mouse (Vinifera-Developers, consult-only): a
// rectangle built from the gadget, a point-within test, an area compare.
//
// The body lives in a static inline helper whose cursor parameter starts as
// `this`: after inlining VC6 coalesces the two and keeps the cursor in ECX
// (retail's `MOV AL,[ECX+0x1E]`, `MOV ECX,EAX` after GetNext). A plain
// `GadgetClass* g = this;` local in the member copies `this` to EAX instead
// (6.6%). The best-so-far pointer is declared after the rectangle so its zero
// is scheduled after the two screen-size stores, and the gadget's four values
// are read into a local rectangle so the hit path stores them from the compare
// registers rather than re-reading the gadget.
//
// PARTIAL (89.1%, 49/55; mnemonic multiset identical). Two tie-breaks remain
// that no phrasing moves: retail's `LEA EBP,[EDI+ESI]` for Y + Height has the
// operands the other way round from its X + Width `LEA EBP,[EDX+EAX]`, and
// the two area products take EBX/EBP the other way round (retail loads the
// best area into EBX first). Operand order in either sum, all 24 orders of
// the four field reads, an inline Right()/Bottom()/Area()/Contains() helper
// set, a named best-area local before or inside the test, the area compare
// reversed (flips JG to JL), a TS++-literal Rect temporary with constructor
// and Is_Point_Within, a Point2D mouse temporary, and volatile locals (which
// change the mechanism, not the tie-break) were all tried.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply here.
// Retail's callee-saved pushes sit exactly where ours do (no prologue pushes
// on either side; all four sunk identically), the
// number of epilogues agrees, and the compiled block order already matches,
// so there are no merged return blocks to split. The residual is register
// naming downstream of that, not a prologue hoist.
static inline GadgetClass* ExtractGadgetAt_Walk(GadgetClass* g, int x, int y)
{
    GadgetRect rect;
    rect.Width = DAT_007F5BE8;
    rect.Height = DAT_007F5BF4;
    GadgetClass* best = 0;

    while (g != 0) {
        if (g->IsDisabled == 0) {
            GadgetRect r;
            r.X = g->X;
            r.Y = g->Y;
            r.Width = g->Width;
            r.Height = g->Height;
            if (x >= r.X && x < r.X + r.Width && y >= r.Y && y < r.Y + r.Height
                && r.Height * r.Width <= rect.Height * rect.Width) {
                rect = r;
                best = g;
            }
        }
        g = (GadgetClass*)g->GetNext();
    }
    return best;
}

GadgetClass* GadgetClass::ExtractGadgetAt(int x, int y)
{
    return ExtractGadgetAt_Walk(this, x, y);
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
