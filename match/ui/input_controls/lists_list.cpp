// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Flags: /GX is left off. A paired /GX probe changes nothing except the compiler-emitted scalar deleting
//   destructors, which stop inlining their bodies with it (0x4E1A60 100% -> 6.5%, 0x558060 and 0x488F00 -> 0%,
//   0x4B55F0 -> 17.6%); every other function here scores identically with and without it.
//   Lists cluster: ListClass vtable bodies at 0x4886B0 and 0x557570..0x558060 (ordered by address).
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
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

// FUNCTION: GAMEMD 0x00557600
ListClass::~ListClass()
{
    if (IsScrollActive) {
        DisableScrollBar();
    }
}

// FUNCTION: GAMEMD 0x005576A0
int ListClass::AddItem(wchar_t const* text)
{
    if (text != 0) {
        List.AddItem(text);
        MarkRedraw();
        if (List.Count > LineCount) {
            EnableScrollBar();
        }
        if (IsScrollActive) {
            Scroller.vf_34(List.Count);
        }
    }
    return List.Count - 1;
}

// FUNCTION: GAMEMD 0x00557730
void ListClass::RemoveItem(int index)
{
    if ((unsigned)index < (unsigned)List.GetCount()) {
        List.Delete(index);
        if (List.GetCount() <= LineCount) {
            DisableScrollBar();
        }
        if (IsScrollActive) {
            Scroller.vf_34(List.GetCount());
        }
        if (SelectedIndex >= List.GetCount()) {
            SelectedIndex--;
            if (SelectedIndex < 0) {
                SelectedIndex = 0;
            }
        }
        if (CurrentTopIndex >= List.GetCount()) {
            CurrentTopIndex--;
            if (CurrentTopIndex < 0) {
                CurrentTopIndex = 0;
            }
            if (IsScrollActive) {
                Scroller.Step(1);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x00557800
void ListClass::RemoveItem(wchar_t const* text)
{
    if (text != 0) {
        RemoveItem(List.FindItemIndex(text));
    }
}

// FUNCTION: GAMEMD 0x00557830
// PARTIAL 96.8%: retail stores SelectedIndex before loading the final count;
// the compiler schedules that store after the load. Existing body bytes are preserved.
int ListClass::Action(unsigned flags, unsigned* key, int extra)
{
    if (flags & 4) {
        *key = 0;
        ControlClass::Action(flags & ~4, key, 0);
        return 1;
    }
    if (flags & 0x100) {
        if (*key == 0x26) {
            StepSelectedIndex(-1);
            *key = 0;
        } else if (*key == 0x28) {
            StepSelectedIndex(1);
            *key = 0;
        } else {
            flags &= ~0x100;
        }
    } else {
        int mouseY = DAT_00887640->GetY();
        SelectedIndex = (mouseY - Y - 1) / LineHeight + CurrentTopIndex;
        int row = SelectedIndex;
        if (row >= List.Count - 1) {
            row = List.Count - 1;
        }
        SelectedIndex = row;
        if (row == -1) {
            SelectedIndex = 0;
        }
    }
    return ControlClass::Action(flags, key, 0);
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

// FUNCTION: GAMEMD 0x00557A20
void ListClass::Bump(int minus)
{
    if (IsScrollActive) {
        if (Scroller.Step(minus)) {
            CurrentTopIndex = Scroller.GetValue();
            MarkRedraw();
        }
    }
}

// FUNCTION: GAMEMD 0x00557A70
void ListClass::Step(int minus)
{
    if (IsScrollActive) {
        if (Scroller.Step(minus)) {
            CurrentTopIndex = Scroller.GetValue();
            MarkRedraw();
        }
    }
}

// FUNCTION: GAMEMD 0x00557AC0
wchar_t const* ListClass::GetItem(int index)
{
    if (List.Count == 0) {
        return 0;
    }
    int last = List.Count - 1;
    if (index >= last) {
        index = last;
    }
    return List.Items[index];
}

// FUNCTION: GAMEMD 0x00557AE0
wchar_t const* ListClass::GetCurrentItem()
{
    if (List.Count <= SelectedIndex) {
        return 0;
    }
    return List.Items[SelectedIndex];
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

// FUNCTION: GAMEMD 0x00557B70
int ListClass::SetViewIndex(int index)
{
    int span = List.Count - LineCount;
    int clamped = (span < 0) - 1;
    clamped &= span;
    if (index < 0) {
        index = 0;
    } else if (index > clamped) {
        index = clamped;
    }
    if (index != CurrentTopIndex) {
        CurrentTopIndex = index;
        MarkRedraw();
        if (IsScrollActive) {
            Scroller.SetValue(CurrentTopIndex);
        }
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x00557BE0
int ListClass::EnableScrollBar()
{
    if (!IsScrollActive) {
        IsScrollActive = true;
        MarkRedraw();
        Width -= Scroller.Width;
        UpButton.SetPeer(this);
        DownButton.SetPeer(this);
        Scroller.SetPeer(this);
        UpButton.Add(*this);
        DownButton.Add(*this);
        Scroller.Add(*this);
        UpButton.MarkRedraw();
        DownButton.MarkRedraw();
        Scroller.MarkRedraw();
        Scroller.vf_34(List.Count);
        Scroller.vf_42(LineCount);
        Scroller.SetValue(CurrentTopIndex);
        return 1;
    }
    return 0;
}

// SYNTHETIC: GAMEMD 0x00557CB0
// ListClass::DisableScrollBar (ordinary inline definition in ui_gadget.h)

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

// FUNCTION: GAMEMD 0x00557E10
LinkClass* ListClass::Add(LinkClass& object)
{
    if (IsScrollActive) {
        Scroller.Add(object);
        DownButton.Add(object);
        UpButton.Add(object);
    }
    return LinkClass::Add(object);
}

// FUNCTION: GAMEMD 0x00557E60
LinkClass* ListClass::AddHead(LinkClass& object)
{
    if (IsScrollActive) {
        Scroller.AddHead(object);
        DownButton.AddHead(object);
        UpButton.AddHead(object);
    }
    return LinkClass::AddHead(object);
}

// FUNCTION: GAMEMD 0x00557EB0
LinkClass* ListClass::AddTail(LinkClass& object)
{
    LinkClass::AddTail(object);
    if (IsScrollActive) {
        UpButton.AddTail(object);
        DownButton.AddTail(object);
        Scroller.AddTail(object);
    }
    return HeadOfList();
}

// FUNCTION: GAMEMD 0x00557F00
LinkClass* ListClass::Remove()
{
    if (IsScrollActive) {
        Scroller.Remove();
        DownButton.Remove();
        UpButton.Remove();
    }
    return GadgetClass::Remove();
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

// SYNTHETIC: GAMEMD 0x00558060
// ListClass::scalar deleting destructor
