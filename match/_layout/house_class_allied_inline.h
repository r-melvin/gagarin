// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail inlines the ally test of 0x4F9A50 (HouseClass::IsAlliedWith(HouseClass const*))
//   into some callers (UpdateAngerNodes 0x504790, CanAlly 0x501540) and calls it out of line from
//   others. The class declares the method out of line; a TU where retail inlined it includes this
//   header so its calls expand in place. Do not include it in a TU where retail calls 0x4F9A50.
#ifndef GG_MATCH_LAYOUT_HOUSE_CLASS_ALLIED_INLINE_H
#define GG_MATCH_LAYOUT_HOUSE_CLASS_ALLIED_INLINE_H

#include "house_class.h"

inline bool HouseClass::IsAlliedWith(const HouseClass* pHouse) const
{
    if (pHouse) {
        if (pHouse == this) return true;
        if (pHouse->ArrayIndex == this->ArrayIndex) return true;
        if (pHouse->ArrayIndex != -1) {
            bool allied = (this->Allies & (1 << pHouse->ArrayIndex)) != 0;
            return allied;
        }
    }
    return false;
}

#endif  // GG_MATCH_LAYOUT_HOUSE_CLASS_ALLIED_INLINE_H
