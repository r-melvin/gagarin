// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | behaviour-confirmed-name
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
// Measured /Ob2 retains the ordinary destructor and expands its deleting entry.
//   Original translation unit TU052 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Candidate window 0x4886e1-0x488f8f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//
//   Flags: /GX is left off. A paired /GX probe changes nothing except the compiler-emitted scalar deleting
//   destructors, which stop inlining their bodies with it (0x4E1A60 100% -> 6.5%, 0x558060 and 0x488F00 -> 0%,
//   0x4B55F0 -> 17.6%); every other function here scores identically with and without it.
//   Lists cluster: ColorListClass vtable bodies at 0x488960, 0x488980, 0x488EE0, 0x488F00.
//   Every entry carries its own colour-scheme index in the Colors vector (parallel to the text vector).

#include "input_controls/lists_views.h"

// The 8/16-bit palette-to-pixel lookup used for every highlight colour below.
static inline unsigned PixelOf(int colorIndex)
{
    if (DAT_0087F6C4->BytesPerPixel == 1) {
        return ((unsigned char*)DAT_0087F6C4->ColorTable)[colorIndex];
    }
    return ((unsigned short*)DAT_0087F6C4->ColorTable)[colorIndex];
}

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// FUNCTION: GAMEMD 0x488760
// Expansion row (outside the 37-address partition): defined because the compiler needs the constructor to emit the
// vtable and the deleting destructor.
ColorListClass::ColorListClass(int id, int x, int y, int w, int h, unsigned textFlags, void const* upShape,
                               void const* downShape)
    : ListClass(id, x, y, w, h, textFlags, upShape, downShape), Style(1), SelectColor(0)
{
}

// FUNCTION: GAMEMD 0x4887F0
ColorListClass::~ColorListClass()
{
    Colors.Clear();
    SelectColor = 0;
}

// FUNCTION: GAMEMD 0x488850
int ColorListClass::AddItem(const wchar_t* text, int color)
{
    Colors.Add(color);
    return ListClass::AddItem(text);
}

// FUNCTION: GAMEMD 0x4888B0
void ColorListClass::RemoveItem(const wchar_t* text)
{
    int index = List.FindItemIndex(text);
    if (index != -1) {
        Colors.Delete(index);
        ListClass::RemoveItem(text);
    }
}

// FUNCTION: GAMEMD 0x488910
void ColorListClass::RemoveItem(int index)
{
    if (index != -1) {
        Colors.Delete(index);
        ListClass::RemoveItem(index);
    }
}

// FUNCTION: GAMEMD 0x488960
// ColorListClass::SetStyle slot (+0xD0): how the selected entry is highlighted, and the colour scheme used.
void ColorListClass::SetStyle(int style, int selectColor)
{
    Style = style;
    SelectColor = selectColor;
}

// FUNCTION: GAMEMD 0x488980
// ColorListClass::DrawItem slot (+0xC8): an unselected entry is drawn in its own colour; a selected one is
// drawn according to Style (0 plain, 1 recoloured, 2 outlined, 3 filled box, 4 bar only).
void ColorListClass::DrawItem(int index, int x, int y, int width, int selected)
{
    if (!selected) {
        FUN_004A6500(List[index], DAT_00887314, &DAT_00887314->GetRect(), &Point2D(x, y),
                     DAT_00B054D0[Colors[index]], 0, TextFlags, width, Tabs);
        return;
    }
    int scheme = SelectColor;
    if (!scheme) {
        scheme = index;
    }
    switch (Style) {
    case 0:
        FUN_004A6500(List[index], DAT_00887314, &DAT_00887314->GetRect(), &Point2D(x, y),
                     DAT_00B054D0[Colors[index]], 0, TextFlags, width, Tabs);
        return;
    case 1:
        if (TextFlags & 6) {
            FUN_004A6500(List[index], DAT_00887314, &DAT_00887314->GetRect(), &Point2D(x, y),
                         DAT_00B054D0[scheme], 0, TextFlags | 0x2000, width, Tabs);
            return;
        }
        FUN_004A6500(List[index], DAT_00887314, &DAT_00887314->GetRect(), &Point2D(x, y),
                     DAT_00B054D0[scheme], 0, TextFlags, width, Tabs);
        return;
    case 2:
        DAT_00887314->OutlineRect(&Box(x, y, x + width - 2, y + LineHeight - 2),
                                                    PixelOf(DAT_00B054D0[scheme]->BarColorIndex));
        FUN_004A6500(List[index], DAT_00887314, &DAT_00887314->GetRect(), &Point2D(x, y),
                     DAT_00B054D0[Colors[index]], 0, TextFlags, width, Tabs);
        return;
    case 3:
        if (TextFlags & 6) {
            DAT_00887314->FillRect(&Rect(x, y, width, LineHeight),
                                                         PixelOf(DAT_00B054D0[scheme]->BarColorIndex));
            FUN_004A6500(List[index], DAT_00887314, &DAT_00887314->GetRect(),
                         &Point2D(x, y), DAT_00B054D0[Colors[index]], 0, TextFlags | 0x2000, width, Tabs);
            return;
        }
        DAT_00887314->FillRect(&Rect(x, y, width - 1, LineHeight - 1),
                                                     PixelOf(DAT_00B054D0[scheme]->BarColorIndex));
        FUN_004A6500(List[index], DAT_00887314, &DAT_00887314->GetRect(), &Point2D(x, y),
                     DAT_00B054D0[Colors[index]], 0, TextFlags, width, Tabs);
        return;
    case 4:
        DAT_00887314->FillRect(&Rect(x, y, width, LineHeight),
                                                     PixelOf(DAT_00B054D0[Colors[index]]->BarColorIndex));
        return;
    }
}

// FUNCTION: GAMEMD 0x488EE0
// ColorListClass::AddItem(text) slot (+0x88): adds the entry in colour scheme 0.
int ColorListClass::AddItem(wchar_t const* text)
{
    return AddItem(text, 0);
}

// SYNTHETIC: GAMEMD 0x488F00
// Scalar deleting destructor: compiler expansion of the ordinary destructor under measured /Ob2.
