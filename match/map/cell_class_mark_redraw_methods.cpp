// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x486E70.

#include "cell_class_mark_redraw_methods.h"

// RectangleStruct::Union, expanded inline twice by cl at 0x486E70. An
// invalid (zero/negative extent) operand simply yields the other one; the
// general case grows a copy of the first rectangle left/up to cover the
// second and then extends its right/bottom edge, the `+1` being retail's
// inclusive-edge convention.
static __forceinline RectangleStruct Union_00486E70(RectangleStruct const& b,
                                                    RectangleStruct const& a)
{
    if (a.Width <= 0 || a.Height <= 0) {
        return b;
    }
    if (b.Width <= 0 || b.Height <= 0) {
        return a;
    }

    RectangleStruct r = a;
    if (r.X > b.X) {
        r.Width += r.X - b.X;
        r.X = b.X;
    }
    if (r.Y > b.Y) {
        r.Height += r.Y - b.Y;
        r.Y = b.Y;
    }
    if (r.X + r.Width < b.X + b.Width) {
        r.Width = b.X - r.X + b.Width + 1;
    }
    if (r.Y + r.Height < b.Y + b.Height) {
        r.Height = b.Y + b.Height - r.Y + 1;
    }
    return r;
}

// FUNCTION: GAMEMD 0x486E70  CellClass::MarkForRedraw (__thiscall)
//
// Mark everything this cell draws as dirty: the union of the cell's own
// screen rectangle, its overlapper rectangle and its occupier rectangle is
// shifted into client space by the tactical origin and handed to the
// tactical renderer, and the cell's radar pixel is flagged too.
//
// The argument order of the inlined Union matters: cl evaluates the argument
// list right to left even when the callee is expanded inline, so the rect
// that Union tests FIRST has to be written LAST in the call for its getter to
// be the one called first. Writing it the other way round swaps every
// register in both expansions (18.7% vs 96.6%).
//
// PARTIAL (96.6%, 144/149): the residual is the frame size only. Retail gives
// the third getter's hidden-return temporary its own 16-byte slot
// (`SUB ESP,0x40`, `LEA EAX,[ESP+0x40]`), cl 12.00.8804 overlaps it with the
// second getter's dead slot (`SUB ESP,0x30`, `LEA EAX,[ESP+0x30]`); the only
// other delta is EDI vs EBP for the 0x886FA4 load and its SUB, which follows
// from that. Variants tried: all three getter results bound to named locals
// (3.9%), the third one alone bound to a named local (18.9%), the client
// rectangle declared ahead of the unions to claim an early slot (96.6%,
// identical residual). This looks like the recorded 8447-vs-8804
// frame-slot-merging class rather than a phrasing lever.
// FRAME-LAYOUT CENSUS: this is one of the four partials whose entire residual
// is the frame reservation constant. Six further variants were measured against
// a labelled control in one compile and none moves the slot: the second union's
// result in a fresh local rather than back into `area` (the thirty-second
// batch's "a local whose address never escapes costs an extra rectangle"
// lever), the same with the client rectangle declared first, the same with the
// first union's result still read after the second so the two lifetimes overlap
// (46.6%), the third getter's result named before the union (18.9%), and the
// client built by whole-struct copy (52.2%). The three that keep retail's
// instruction stream are byte-identical to the control at 96.6%. No
// expression-level spelling reaches a frame-layout decision.
//
void CellClass::MarkForRedraw()
{
    RectangleStruct area = Union_00486E70(FUN_0047FB90(), FUN_0047FF80());
    area = Union_00486E70(FUN_0047FDE0(), area);

    RectangleStruct client;
    client.X      = area.X - DAT_00886FA0;
    client.Y      = area.Y - DAT_00886FA4;
    client.Width  = area.Width;
    client.Height = area.Height;
    DAT_00887324->FUN_006D2790(client, false);

    DAT_0087F7E8.FUN_006551C0(this->MapCoords);
}
