// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 across 0x4E1450..0x4E1A40
//   via the local Ghidra disassembly. Vtable/member offsets confirmed from the
//   0x7E92BC vtable dump (see gadget_class_methods.h). Method names are
//   YRpp-cross-checked against each body's behaviour; every body is justified
//   by its retail bytes.
//
// GadgetClass — base of the GUI gadget hierarchy: a LinkClass list node plus
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

// FUNCTION: GAMEMD 0x4E15A0  GadgetClass::ExtractGadgetAt (__thiscall)
// Walk the list from this gadget and return the smallest enabled one whose
// rectangle contains the point, starting from a screen-sized best so the first
// hit always qualifies. Ties go to the later gadget (`<=`). The body is a
// rectangle built from the gadget, a point-within test and an area compare,
// as the retail instruction sequence shows.
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
// reversed (flips JG to JL), a Rect temporary with a constructor and a
// point-within helper, a Point2D mouse temporary, and volatile locals (which
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

