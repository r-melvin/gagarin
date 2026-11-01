// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Flag bisection: a paired /GX probe of every entry in this TU produced the same scores as the
// line above. /GX is omitted because controls_static_button.cpp shows retail has no unwind code.
//
// GaugeClass / TriColorGaugeClass entries (layout and evidence: ui_gadget.h).
#include "controls_views.h"


// FUNCTION: GAMEMD 0x4E2580
int GaugeClass::vf_34(int maximum)
{
    if (maximum != Maximum) {
        Maximum = maximum;
        MarkRedraw();
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4E25A0
int GaugeClass::SetValue(int value)
{
    int maximum = Maximum;
    if (value < 0)
        value = 0;
    else if (value > maximum)
        value = maximum;
    if (value != Value) {
        Value = value;
        MarkRedraw();
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4E30A0
int GaugeClass::GetValue()
{
    return Value;
}

// FUNCTION: GAMEMD 0x4E30B0
void GaugeClass::vf_37(int use)
{
    unknown_2D = use != 0;
}

// FUNCTION: GAMEMD 0x4E30C0
int GaugeClass::vf_38()
{
    return 4;
}

// FUNCTION: GAMEMD 0x4E2AF0
int TriColorGaugeClass::vf_42(int limit)
{
    if (limit >= 0 && limit < Maximum) {
        unknown_3C = limit;
        MarkRedraw();
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4E2B20
int TriColorGaugeClass::vf_43(int limit)
{
    if (limit >= 0 && limit < Maximum) {
        unknown_40 = limit;
        MarkRedraw();
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4E25D0
int GaugeClass::vf_40(int pixel)
{
    int length;
    if (unknown_2E) {
        pixel += -1 - X;
        length = Width;
    } else {
        pixel += -1 - Y;
        length = Height;
    }
    length -= 2;
    if (pixel < 0)
        pixel = 0;
    else if (pixel > length)
        pixel = length;
    return (int)((double)pixel / length * Maximum);
}

// FUNCTION: GAMEMD 0x4E2650
int GaugeClass::vf_41(int value)
{
    int length;
    int origin;
    if (unknown_2E) {
        length = Width;
        origin = X;
    } else {
        length = Height;
        origin = Y;
    }
    return (int)((double)value / Maximum * (length - 2) + origin);
}

// FUNCTION: GAMEMD 0x4E29A0
void GaugeClass::vf_39()
{
    int pos = vf_41(Value);
    if (pos + 4 > vf_41(Maximum))
        pos = vf_41(Maximum) - 2;
    if (pos < X)
        pos = X;
    if (unknown_2E) {
        Rect area;
        area.Y = Y;
        area.Height = Height;
        area.X = pos;
        area.Width = 4;
        FUN_004A5A50(&area, 1, 1);
    } else {
        Rect area;
        area.X = X;
        area.Y = pos;
        area.Width = Width;
        area.Height = 4;
        FUN_004A5A50(&area, 1, 1);
    }
}

// FUNCTION: GAMEMD 0x4E2690
// CAPPED at 38.8% (54 of 139 instructions; multiset delta: retail has 3 `mov`, 1 `push`, 1 `xor`, 1 `lea`
// and 1 `jmp` more). Retail keeps the constant 1 in EBX only through the three colour-table compares and
// then reuses EBX as the zero-extend scratch (`xor ebx,ebx` / `mov bl,[...]`) and re-materialises the
// final `mov eax,1`; cl keeps 1 in EBX to the return, so every register after the rectangle build is
// named differently. Retail also shares only the closing `push eax / call [edx+0x14]` between the
// horizontal and vertical fills, where cl shares the whole surface load as well. Variants tried: two
// named rectangles (stack 0x20 instead of 0x10), one rectangle with the `X + 1` / `Y + 1` common
// subexpressions kept or hoisted into locals, the colour index in a local before the axis test.
int GaugeClass::Draw(int forced)
{
    if (ControlClass::Draw(forced)) {
        DAT_00887640->HideRegion(Rect(X, Y, Width, Height));
        Rect area(X, Y, Width, Height);
        FUN_004A5A50(&area, 0, 1);

        if (unknown_2C) {
            int pixel = vf_41(Value);
            int colour = DAT_00B054D0[GetColorScheme()]->ThemeColour;
            if (unknown_2E) {
                if (pixel >= X + 1) {
                    area.X = X + 1;
                    area.Y = Y + 1;
                    area.Width = pixel - X - 1;
                    area.Height = Height - 2;
                    DAT_00887314->FillRect(&area, DAT_0087F6C4->Lookup(colour));
                }
            } else {
                if (pixel >= Y + 1) {
                    area.X = X + 1;
                    area.Y = Y + 1;
                    area.Width = Width - 2;
                    area.Height = pixel - Y - 1;
                    DAT_00887314->FillRect(&area, DAT_0087F6C4->Lookup(colour));
                }
            }
        }
        if (unknown_2D)
            vf_39();
        DAT_00887640->ShowRegion();
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4E2830
// CAPPED at 45.7% (64 of 140 instructions; multiset delta: retail has 1 `jl`; ours has 1 `mov`, 1 `test`,
// 1 `jge`, 1 `jg` more). The control flow and the lazily saved EBP match. The loop temporaries
// `unknown_38` (read before each `vf_40` call) use ECX/EDX in retail, but ours uses the EBP that is
// still allocated to `thumbStart`, and the `mov`/`test` count differs by one pair. Variants tried: goto-based flow, a `pressed` local, an inline `MouseAlongAxis()`
// helper, and the else-branch form that now builds the shared forward tail.
int GaugeClass::Action(unsigned flags, unsigned* key, int modifier)
{
    if (!unknown_2D)
        return 0;

    StickyProcess(flags);
    if ((flags & 1) || ((flags & 2) && GadgetClass_StuckOn == this)) {
        if (flags & 1) {
            int thumbStart = vf_41(Value);
            int mouse = MouseAlongAxis();
            if (mouse > thumbStart && mouse - thumbStart < vf_38())
                unknown_38 = mouse - thumbStart;
            else
                unknown_38 = 0;

            if (vf_40(MouseAlongAxis() - unknown_38) < Value) {
                while (unknown_38 > 0) {
                    unknown_38--;
                    if (vf_40(MouseAlongAxis() - unknown_38) >= Value)
                        break;
                }
            }
        }
        if (!SetValue(vf_40(MouseAlongAxis() - unknown_38))) {
            ControlClass::Action(0, key, 0);
            *key = 0;
            return 1;
        }
    } else {
        flags &= ~2;
    }
    return ControlClass::Action(flags, key, 0);
}

// FUNCTION: GAMEMD 0x4E2B50
// CAPPED at 3.8% (17 of 445 instructions; multiset delta: retail has 11 `mov`, 9 `push`, 4 `call`, 6 `xor`,
// 5 `lea`, 3 `jmp`, 2 `cmp`, 1 `je`, 1 `jne` more, ours has none that retail lacks). Retail repeats the
// colour-table lookup and the `call [edx+0x14]` in each of the twelve horizontal/vertical fills and
// merges only the closing `push / call` pairs; cl merges whole fill sequences across the two axis
// branches, so the lookups, rectangle stores and calls drift apart. The rectangle fields written in
// the middle band (e.g. X = redPixel - X + 1) are exactly as retail stores them. Variants tried: lookup
// inside the call, lookup in a local ahead of the rectangle stores, whole-rectangle constructor
// assignment instead of field stores.
int TriColorGaugeClass::Draw(int forced)
{
    if (!GaugeClass::Draw(forced))
        return 0;

    DAT_00887640->HideRegion(Rect(X, Y, Width, Height));
    Rect area(X, Y, Width, Height);
    FUN_004A5A50(&area, IsDisabled != 0, 1);

    int redPixel = vf_41(unknown_3C);
    int yellowPixel = vf_41(unknown_40);
    int valuePixel = vf_41(Value);

    if (Value <= unknown_3C) {
        if (unknown_2E) {
            area.X = X + 1;
            area.Y = Y + 1;
            area.Width = valuePixel - X + 1;
            area.Height = Height - 2;
        } else {
            area.X = X + 1;
            area.Y = Y + 1;
            area.Width = Width - 2;
            area.Height = valuePixel - Y + 1;
        }
        DAT_00887314->FillRect(&area, DAT_0087F6C4->Lookup(6));
    } else if (Value <= unknown_40) {
        if (unknown_2E) {
            area.X = X + 1;
            area.Y = Y + 1;
            area.Width = redPixel - X + 1;
            area.Height = Height - 2;
            DAT_00887314->FillRect(&area, DAT_0087F6C4->Lookup(6));
            area.X = redPixel - X + 1;
            area.Y = Y + 1;
            area.Width = valuePixel - X - 1;
            area.Height = Height - 2;
            DAT_00887314->FillRect(&area, DAT_0087F6C4->Lookup(5));
        } else {
            area.X = X + 1;
            area.Y = Y + 1;
            area.Width = Width - 2;
            area.Height = redPixel - Y + 1;
            DAT_00887314->FillRect(&area, DAT_0087F6C4->Lookup(6));
            area.X = X + 1;
            area.Y = redPixel - Y + 1;
            area.Width = X + Width - 2;
            area.Height = valuePixel - Y + 1;
            DAT_00887314->FillRect(&area, DAT_0087F6C4->Lookup(5));
        }
    } else if (Value <= Maximum) {
        if (unknown_2E) {
            area.X = X + 1;
            area.Y = Y + 1;
            area.Width = redPixel - X + 1;
            area.Height = Height - 2;
            DAT_00887314->FillRect(&area, DAT_0087F6C4->Lookup(6));
            area.X = redPixel;
            area.Y = Y + 1;
            area.Width = yellowPixel - X + 1;
            area.Height = Height - 2;
            DAT_00887314->FillRect(&area, DAT_0087F6C4->Lookup(5));
            area.X = yellowPixel;
            area.Y = Y + 1;
            area.Width = valuePixel - X + 1;
            area.Height = Height - 2;
            DAT_00887314->FillRect(&area, DAT_0087F6C4->Lookup(3));
        } else {
            area.X = X + 1;
            area.Y = Y + 1;
            area.Width = Width - 2;
            area.Height = redPixel - Y + 1;
            DAT_00887314->FillRect(&area, DAT_0087F6C4->Lookup(6));
            area.X = X + 1;
            area.Y = redPixel;
            area.Width = Width - 2;
            area.Height = yellowPixel - Y + 1;
            DAT_00887314->FillRect(&area, DAT_0087F6C4->Lookup(5));
            area.X = X + 1;
            area.Y = yellowPixel;
            area.Width = Width - 2;
            area.Height = valuePixel - Y + 1;
            DAT_00887314->FillRect(&area, DAT_0087F6C4->Lookup(3));
        }
    }
    if (unknown_2D)
        vf_39();
    DAT_00887640->ShowRegion();
    return 1;
}
