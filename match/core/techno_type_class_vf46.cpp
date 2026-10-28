// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Target bytes: user's retail gamemd.exe v1.001 (disasm 0x711F60).
#include "../_layout/techno_type_class.h"
#include "../_layout/house_class.h"
#include "../_layout/rules_class.h"

// FUNCTION: GAMEMD 0x711F60
// Price of the type. With a house: the soylent override, or the slot-43 cost
// scaled by two house factors, and again by a rules double (1.0 when `a2`) if
// the house is human-controlled. Without a house: the cost times that double.
int TechnoTypeClass::vf_46(HouseClass* house, bool a2)
{
    float scale = (float)*(double*)&Rules->unknown_1738;
    if (a2) {
        scale = 1.0f;
    }
    if (house != 0) {
        float first = house->FUN_0050BDF0(this);
        float second = house->FUN_0050BEB0(this);
        if (Soylent != 0) {
            return (int)(Soylent * first);
        }
        int price = (int)(vf_43() * second * first);
        if (house->FUN_0050B730()) {
            price = (int)(price * scale);
        }
        return price;
    }
    return (int)(vf_43() * scale);
}
