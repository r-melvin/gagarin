// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Flags: /GX is left off. A paired /GX probe changes nothing except the compiler-emitted scalar deleting
//   destructors, which stop inlining their bodies with it (0x4E1A60 100% -> 6.5%, 0x558060 and 0x488F00 -> 0%,
//   0x4B55F0 -> 17.6%); every other function here scores identically with and without it.
//   Lists cluster: CheckListClass vtable bodies at 0x488350, 0x488360, 0x488520, 0x4886C0, 0x4886D0.
//   The entries of a CheckListClass are CheckItemClass records stored through the base text vector.
#include "lists_views.h"

// FUNCTION: GAMEMD 0x488350
// CheckListClass::GetCurrentItem slot (+0x9C): the text of the selected entry, or null.
wchar_t const* CheckListClass::GetCurrentItem()
{
    CheckItemClass* item = (CheckItemClass*)ListClass::GetCurrentItem();
    if (item) {
        return item->Text;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x488360
// CheckListClass::GetItem slot (+0xA0): the text of entry `index`, or null.
wchar_t const* CheckListClass::GetItem(int index)
{
    CheckItemClass* item = (CheckItemClass*)ListClass::GetItem(index);
    if (item) {
        return item->Text;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x488520
// CheckListClass::DrawItem slot (+0xC8): draws entry `index` prefixed by its check glyph.
void CheckListClass::DrawItem(int index, int x, int y, int width, int selected)
{
    if (index < GetCount()) {
        CheckItemClass* item = (CheckItemClass*)ListClass::GetItem(index);
        if (item) {
            wchar_t line[100] = {0};
            line[0] = item->IsChecked ? 3 : 0x20;
            line[1] = 0x20;
            _swprintf(line + 2, item->Text);
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
            FUN_004A6500(line, DAT_00887314, &DAT_00887314->GetRect(), &Point2D(x, y),
                         DAT_00B054D0[scheme], 0, flags, width, Tabs);
        }
    }
}

// FUNCTION: GAMEMD 0x4886C0
// CheckListClass::RemoveItem(index) slot (+0xA8): forwards to the base list.
void CheckListClass::RemoveItem(int index)
{
    ListClass::RemoveItem(index);
}

// FUNCTION: GAMEMD 0x4886D0
// CheckListClass::vf_46 slot (+0xB8): forwards to the base list.
void CheckListClass::vf_46(int index)
{
    ListClass::vf_46(index);
}
