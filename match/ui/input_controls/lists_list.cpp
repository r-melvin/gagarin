// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Flags: /GX is left off. A paired /GX probe changes nothing except the compiler-emitted scalar deleting
//   destructors, which stop inlining their bodies with it (0x4E1A60 100% -> 6.5%, 0x558060 and 0x488F00 -> 0%,
//   0x4B55F0 -> 17.6%); every other function here scores identically with and without it.
//   Lists cluster: ListClass vtable bodies at 0x4886B0 and 0x557570..0x558060 (ordered by address).
#include "lists_views.h"

// LIBRARY: GAMEMD 0x7DD0F8 _wcsicmp
extern "C" int __cdecl _wcsicmp(const wchar_t* a, const wchar_t* b);

// FUNCTION: GAMEMD 0x4886B0
// ListClass::GetCount slot (+0x94): the number of strings.
int ListClass::GetCount()
{
    return List.Count;
}

// FUNCTION: GAMEMD 0x557230
// Expansion row (outside the 37-address partition): defined because the compiler needs the constructor to emit the
// vtable and the deleting destructor.
ListClass::ListClass(int id, int x, int y, int w, int h, unsigned textFlags, void const* upShape,
                     void const* downShape)
    : ControlClass(id, x, y, w, h, 0x105, 0),
      UpButton(0, upShape, x + w, y, 0, 0, 0),
      DownButton(0, downShape, x + w, y + h, 0, 0, 0),
      Scroller(0, x + w, y, 0, h, 1)
{
    UpButton.X -= UpButton.Width;
    DownButton.X -= DownButton.Width;
    DownButton.Y -= DownButton.Height;
    Scroller.X -= UpButton.Width > DownButton.Width ? UpButton.Width : DownButton.Width;
    Scroller.Y = Y + UpButton.Height;
    Scroller.Height -= UpButton.Height + DownButton.Height;
    Scroller.Width = UpButton.Width > DownButton.Width ? UpButton.Width : DownButton.Width;
    TextFlags = textFlags;
    IsScrollActive = false;
    Tabs = 0;
    SelectedIndex = 0;
    CurrentTopIndex = 0;
    LineHeight = FUN_004A60D0(textFlags)->Height - 1;
    LineCount = (h - 1) / LineHeight;
}

// FUNCTION: GAMEMD 0x557570
// ListClass::SetPosition slot (+0x64): lays the up button, the down button and the slider out along the
// right edge of the list rectangle.
void ListClass::SetPosition(int x, int y)
{
    UpButton.X = x + Width - UpButton.Width;
    UpButton.Y = y;
    DownButton.X = x + Width - DownButton.Width;
    DownButton.Y = y + Height - DownButton.Height;
    Scroller.X = x + Width - (UpButton.Width > DownButton.Width ? UpButton.Width : DownButton.Width);
    Scroller.Y = y + UpButton.Height;
    Scroller.Height = Height - DownButton.Height - UpButton.Height;
    Scroller.Width = UpButton.Width > DownButton.Width ? UpButton.Width : DownButton.Width;
}

// FUNCTION: GAMEMD 0x557920
// ListClass::Draw slot (+0x6C): when the gadget needs drawing, hides the mouse over the list, paints the frame,
// draws each visible line and shows the mouse again.
int ListClass::Draw(int forced)
{
    if (GadgetClass::Draw(forced)) {
        DAT_00887640->HideRegion(Rect(X, Y, Width, Height));
        FUN_004A5A50(&Rect(X, Y, Width, Height), 4, 1);
        if (List.Count) {
            for (int line = 0; line < LineCount; line++) {
                int index = CurrentTopIndex + line;
                if (List.Count > index) {
                    DrawItem(index, X + 1, LineHeight * line + Y + 1, Width - 2, index == SelectedIndex);
                }
            }
        }
        DAT_00887640->ShowRegion();
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x557B00
// ListClass::GetSelectedIndex slot (+0x98).
int ListClass::GetSelectedIndex()
{
    return SelectedIndex;
}

// FUNCTION: GAMEMD 0x557B10
// ListClass::PeerToPeer slot (+0x4C): a release on the up/down buttons steps the view, a change on the slider
// jumps it.
void ListClass::PeerToPeer(unsigned flags, unsigned* key, GadgetClass* source)
{
    if (flags & 4) {
        if (source == &UpButton) {
            Step(1);
        }
        if (source == &DownButton) {
            Step(0);
        }
    }
    if (source == &Scroller) {
        SetViewIndex(Scroller.GetValue());
    }
}

// FUNCTION: GAMEMD 0x557D10
// ListClass::vf_47 slot (+0xBC).
void ListClass::vf_47(int tabStops)
{
    Tabs = tabStops;
}

// FUNCTION: GAMEMD 0x557D20
// ListClass::DrawItem slot (+0xC8): draws string `index` at (x, y) in a column `width` wide, on a filled bar
// when selected.
void ListClass::DrawItem(int index, int x, int y, int width, int selected)
{
    unsigned flags = TextFlags;
    int scheme = GetColorScheme();
    if (selected) {
        flags |= 0x2000;
        int colorIndex = DAT_00B054D0[scheme]->TextColorIndex;
        unsigned color;
        if (DAT_0087F6C4->BytesPerPixel == 1) {
            color = ((unsigned char*)DAT_0087F6C4->ColorTable)[colorIndex];
        } else {
            color = ((unsigned short*)DAT_0087F6C4->ColorTable)[colorIndex];
        }
        Rect bar(x, y, width, LineHeight);
        DAT_00887314->FillRect(&bar, color);
    } else if (!(flags & 0x4000)) {
        flags |= 0x1000;
    }
    FUN_004A6500(List[index], DAT_00887314, &DAT_00887314->GetRect(), &Point2D(x, y),
                 DAT_00B054D0[scheme], 0, flags, width, Tabs);
}

// FUNCTION: GAMEMD 0x557F40
// ListClass::vf_46 slot (+0xB8): selects `index` and scrolls it into view; out of range resets to 0.
void ListClass::vf_46(int index)
{
    if ((unsigned)index < (unsigned)List.Count) {
        SelectedIndex = index;
        MarkRedraw();
        if (SelectedIndex < CurrentTopIndex) {
            SetViewIndex(SelectedIndex);
        }
        if (SelectedIndex >= CurrentTopIndex + LineCount) {
            SetViewIndex(SelectedIndex - LineCount + 1);
        }
    } else {
        SelectedIndex = 0;
    }
}

// FUNCTION: GAMEMD 0x557FB0
// ListClass::StepSelectedIndex slot (+0xA4): moves the selection by `delta`, returning the old index.
int ListClass::StepSelectedIndex(int delta)
{
    int old = SelectedIndex;
    vf_46(old + delta);
    return old;
}

// FUNCTION: GAMEMD 0x557FD0
// ListClass::MarkRedraw slot (+0x48): also flags the scroll widgets while the scroll bar is active.
void ListClass::MarkRedraw()
{
    if (IsScrollActive) {
        UpButton.MarkRedraw();
        DownButton.MarkRedraw();
        Scroller.MarkRedraw();
    }
    GadgetClass::MarkRedraw();
}

// FUNCTION: GAMEMD 0x558010
// ListClass::SetSelectedText slot (+0xB4): selects the first string equal to `text` (case-insensitive).
void ListClass::SetSelectedText(wchar_t const* text)
{
    if (text && List.Count > 0) {
        for (int i = 0; i < List.Count; i++) {
            if (!_wcsicmp(List.Items[i], text)) {
                vf_46(i);
                return;
            }
        }
    }
}

// FUNCTION: GAMEMD 0x558060
// ListClass scalar deleting destructor (slot 0): switches the scroll bar off if it is on, destroys the slider, the two
// buttons and the text vector, and runs the GadgetClass destructor. Compiler-emitted from the inline destructor below.
inline ListClass::~ListClass()
{
    if (IsScrollActive) {
        DisableScrollBar();
    }
}
