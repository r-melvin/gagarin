// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Flags: /GX is left off. A paired /GX probe changes nothing except the compiler-emitted scalar deleting
//   destructors, which stop inlining their bodies with it (0x4E1A60 100% -> 6.5%, 0x558060 and 0x488F00 -> 0%,
//   0x4B55F0 -> 17.6%); every other function here scores identically with and without it.
//   Lists cluster: DropListClass vtable bodies at 0x4B4EE0, 0x4B5530, 0x4B55F0.
//   A DropListClass is an EditClass with a drop button (+0x50) and an embedded ListClass (+0xB0).
#include "lists_views.h"

// LIBRARY: GAMEMD 0x7DD0F8 _wcsicmp
extern "C" int __cdecl _wcsicmp(const wchar_t* a, const wchar_t* b);

// FUNCTION: GAMEMD 0x4B4E10
// Expansion row (outside the 37-address partition): defined because the compiler needs the constructor to emit the
// vtable and the deleting destructor.
DropListClass::DropListClass(int id, wchar_t* text, int size, unsigned textFlags, int x, int y, int w,
                             int listHeight, void const* upShape, ShapeHeader const* dropShape)
    : EditClass(id, text, size, textFlags, x, y, w, 0x12, 7),
      unknown_48(false),
      unknown_4C(listHeight),
      unknown_50(0, dropShape, x + w, y, 0, 0, 0),
      unknown_B0(0, x, y + dropShape->Height, w + dropShape->Width, listHeight, textFlags, upShape, dropShape)
{
    Height = FUN_004A60D0(textFlags)->Height + 1;
    unknown_B0.SetPeer(this);
    unknown_50.SetPeer(this);
}

// SYNTHETIC: GAMEMD 0x4B55F0
// DropListClass scalar deleting destructor, emitted from the inline destructor in ui_gadget.h.

// FUNCTION: GAMEMD 0x4B4EE0
// DropListClass::Zap slot (+0x20): closes the dropped list, zaps the list and the button, then unlinks itself.
void DropListClass::Zap()
{
    if (unknown_48) {
        unknown_B0.Remove();
        unknown_48 = false;
    }
    unknown_B0.Zap();
    unknown_50.Zap();
    LinkClass::Zap();
}

// FUNCTION: GAMEMD 0x4B5530
// DropListClass::SelectItem slot (+0xA8): selects the entry whose text equals `text` (case-insensitive).
void DropListClass::SelectItem(wchar_t const* text)
{
    if (text) {
        for (int i = 0; i < GetCount(); i++) {
            if (!_wcsicmp(text, unknown_B0.GetItem(i))) {
                vf_43(i);
                return;
            }
        }
    }
}
