// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference
//   Bodies ascending by retail address; bytes diffed against the user's
//   retail gamemd.exe v1.001.
#include "color_list_class_methods.h"

// FUNCTION: GAMEMD 0x4887F0
// ColorListClass::~ColorListClass. Empties the colour vector through its own
// virtual Clear, drops the selection colour, then lets the member vector's
// destructor release the block and the base list destructor run.
void ColorListClass::Dtor()
{
    this->Vfptr = (void*)VT_007E5054;
    this->Colors.Clear();
    this->SelectColor = 0;
    this->Colors.ColorVector::~ColorVector();
    this->ListClass_Dtor();
}

// FUNCTION: GAMEMD 0x488850
// ColorListClass::Add_Item. Appends the entry's colour to the parallel colour
// vector (growing it by GrowthStep when it is full and owns its block) and
// then hands the text to the base list.
void ColorListClass::AddItem(wchar_t const* text, int color)
{
    this->Colors.Add(color);
    this->ListClass_AddItem(text);
}

// FUNCTION: GAMEMD 0x4888B0
// ColorListClass::Remove_Item(text). Looks the text up in the base list's own
// entry vector, drops the matching colour, then removes the entry itself.
void ColorListClass::RemoveItem(wchar_t const* text)
{
    int index = this->List.FindItemIndex(text);

    if (index != -1) {
        this->Colors.Delete(index);
        this->ListClass_RemoveItem(text);
    }
}

// FUNCTION: GAMEMD 0x488910
// ColorListClass::Remove_Item(index). Same pairing by index rather than text.
void ColorListClass::RemoveItem(int index)
{
    if (index != -1) {
        this->Colors.Delete(index);
        this->ListClass_RemoveItem(index);
    }
}
