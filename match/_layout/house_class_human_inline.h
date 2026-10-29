// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail inlines HouseClass::IsControlledByHuman (0x50B730) into some callers
//   (AllyAIHouses 0x501640) and calls it out of line from others. The class
//   declares the method out of line; a TU where retail inlined it includes this
//   header so its calls expand in place. Do not include it in a TU where retail
//   calls 0x50B730.
#ifndef GG_MATCH_LAYOUT_HOUSE_CLASS_HUMAN_INLINE_H
#define GG_MATCH_LAYOUT_HOUSE_CLASS_HUMAN_INLINE_H

#include "house_class.h"
#include "session_class.h"

inline bool HouseClass::IsControlledByHuman() const
{
    if (Session_00A8B238.GameMode != 0) {
        return IsHumanPlayer;
    }
    bool result = IsHumanPlayer;
    result = result || IsInPlayerControl;
    return result;
}

#endif  // GG_MATCH_LAYOUT_HOUSE_CLASS_HUMAN_INLINE_H
