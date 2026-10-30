// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// VC6FLAGS: /nologo /c /O2 /Gr /GR /DNDEBUG /Gy /MT
// Placement lead: ??_GSliderClass (0x558180) belongs in the file that constructs
// a SliderClass (not matched yet), where only the destructor declaration is
// visible; until then this file avoids /Ob2, which would expand ~SliderClass
// into it.
// Flag bisection: a paired /GX probe of every entry in this TU produced the same scores as the
// line above. /GX is omitted because controls_static_button.cpp shows retail has no unwind code.
//
// SliderClass entries (layout and evidence: ui_gadget.h).
#include "controls_views.h"


// FUNCTION: GAMEMD 0x558120
int SliderClass::vf_38()
{
    return unknown_4C;
}

// FUNCTION: GAMEMD 0x6B1D00
// Releases the plus and minus buttons the constructor allocated.
SliderClass::~SliderClass()
{
    if (unknown_3C) {
        delete unknown_3C;
        unknown_3C = 0;
    }
    if (unknown_40) {
        delete unknown_40;
        unknown_40 = 0;
    }
}

// FUNCTION: GAMEMD 0x6B1D40
int SliderClass::vf_34(int maximum)
{
    if (GaugeClass::vf_34(maximum)) {
        SyncThumb();
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6B1DC0
void SliderClass::vf_42(int size)
{
    unknown_48 = size < Maximum ? size : Maximum;
    unknown_48 = unknown_48 > 1 ? unknown_48 : 1;
    MarkRedraw();
    SyncThumb();
}

// FUNCTION: GAMEMD 0x6B1E50
int SliderClass::SetValue(int value)
{
    if (value >= Maximum - unknown_48)
        value = Maximum - unknown_48;
    if (GaugeClass::SetValue(value)) {
        SyncThumb();
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6B1F50
// CAPPED at 69.1% (47 of 68 instructions; multiset delta: retail has 1 `pop`). Retail pushes EDI in the
// prologue before the `flags & 1` test and pops it on the plain `GaugeClass::Action` return too; ours
// saves EDI lazily inside the pressed block, so the prologue and the first fifteen instructions shift.
// Variants tried: the nested form (this), an early return for the unpressed case (7.4%), the
// origin-plus-one local (`low`) versus separate X/Y adds.
int SliderClass::Action(unsigned flags, unsigned* key, int modifier)
{
    if (flags & 1) {
        int mouse;
        int low;
        if (unknown_2E) {
            mouse = DAT_00887640->GetX();
            low = X;
        } else {
            mouse = DAT_00887640->GetY();
            low = Y;
        }
        low++;
        if (mouse < unknown_50 + low) {
            Bump(1);
            GaugeClass::Action(0, key, 0);
        } else if (mouse > unknown_4C + unknown_50 + low) {
            Bump(0);
            GaugeClass::Action(0, key, 0);
        } else {
            GaugeClass::Action(flags, key, 0);
        }
        *key = 0;
        return 1;
    }
    return GaugeClass::Action(flags, key, 0);
}

// FUNCTION: GAMEMD 0x6B2000
int SliderClass::Bump(int up)
{
    if (up)
        return SetValue(Value - unknown_48);
    return SetValue(unknown_48 + Value);
}

// FUNCTION: GAMEMD 0x6B2040
int SliderClass::Step(int up)
{
    if (up)
        return SetValue(Value - 1);
    return SetValue(Value + 1);
}

// FUNCTION: GAMEMD 0x6B2070
void SliderClass::vf_39()
{
    if (unknown_2E) {
        Rect area;
        area.X = unknown_50 + X;
        area.Y = Y;
        area.Width = unknown_4C;
        area.Height = Height;
        FUN_004A5A50(&area, 1, 1);
    } else {
        Rect area;
        area.X = X;
        area.Y = unknown_50 + Y;
        area.Width = Width;
        area.Height = unknown_4C;
        FUN_004A5A50(&area, 1, 1);
    }
}

// FUNCTION: GAMEMD 0x6B20F0
int SliderClass::Draw(int forced)
{
    if (unknown_44 && ControlClass::Draw(forced)) {
        Rect area(X, Y, Width, Height);
        FUN_004A5A50(&area, 0, 1);
        vf_39();
        return 1;
    }
    return GaugeClass::Draw(forced);
}

// FUNCTION: GAMEMD 0x6B2160
void SliderClass::PeerToPeer(unsigned flags, unsigned* key, GadgetClass* source)
{
    if (flags & 4) {
        if (source == unknown_3C)
            Step(0);
        if (source == unknown_40)
            Step(1);
    }
}

// SYNTHETIC: GAMEMD 0x558180 -- SliderClass scalar deleting destructor, emitted by the compiler from the virtual destructor
