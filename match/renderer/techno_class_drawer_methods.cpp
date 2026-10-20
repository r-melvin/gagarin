// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x705D70.

#include "techno_class_drawer_methods.h"

// GLOBAL: GAMEMD 0xA83D4C
House_00705D70* DAT_00A83D4C;
// GLOBAL: GAMEMD 0xB054D0
ColorSchemeVec_00705D70 DAT_00B054D0;

// FUNCTION: GAMEMD 0x705D70
//
// Which house-colour remap table draws this object. A type with its own
// Palette= list supplies one ColorScheme per house, indexed by the owner's
// colour-scheme index. Otherwise the global ColorScheme array is used — for the
// owner, unless the local player cannot see through a disguise and the object
// is disguised as some house, in which case that house's colours are drawn.
// The disguise house is fetched twice rather than cached, as retail does.
LightConvertClass* Techno_00705D70::GetDrawer()
{
    TechnoType_00705D70* type = (this->*(*(Vtbl_00705D70**)this)->At_084)();
    int index = ((House_00705D70*)this->Owner)->ColorSchemeIndex;

    if (type->Palette != 0) {
        return (*type->Palette)[index]->LightConvert;
    }

    if (!(this->*(*(Vtbl_00705D70**)this)->At_440)(DAT_00A83D4C)) {
        if ((this->*(*(Vtbl_00705D70**)this)->At_0D0)(1) != 0) {
            return DAT_00B054D0[(this->*(*(Vtbl_00705D70**)this)->At_0D0)(1)->ColorSchemeIndex]->LightConvert;
        }
    }

    return DAT_00B054D0[index]->LightConvert;
}
