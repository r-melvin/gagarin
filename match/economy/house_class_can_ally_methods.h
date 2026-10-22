// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x501540: on the house `[EDI+0x30]` / `[ESI+0x30]`
//   (ArrayIndex), `[ESI+0x5788]` (Allies bitfield dword), `[EDI+0x34]`
//   (Type), `[ESI+0x1F5]` (Defeated byte); on the house type `[ECX+0xBC]`
//   (ArrayIndex2) and `[ECX+0x1A6]` (MultiplayPassive byte); the globals
//   0xA8022C / 0xA80238 (HouseClass::Array Items / Count), 0xA8B238
//   (SessionClass GameMode) and 0xA8E7AC (ScenarioInit); the "Civilian"
//   house-type index lookup 0x6A46D0 with the name in ECX. Names cross-checked
//   against YRpp.
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_CAN_ALLY_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_CAN_ALLY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// HouseTypeClass — the type's ArrayIndex2 and the MultiplayPassive flag.
struct HouseType_00501540
{
    char _pad000[0xBC];          // +0x0000
    int  ArrayIndex2;            // +0x00BC
    char _pad0C0[0x1A6 - 0xC0];  // +0x00C0
    char MultiplayPassive;       // +0x01A6
};
GG_STATIC_ASSERT(offsetof(HouseType_00501540, ArrayIndex2)      == 0xBC);
GG_STATIC_ASSERT(offsetof(HouseType_00501540, MultiplayPassive) == 0x1A6);

// The house-type name whose index the civilian test compares against; the
// lookup takes the name in ECX.
struct HouseTypeName_00501540
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x6A46D0 (decl; reloc) — HouseTypeClass::FindIndex.
    int FindIndex();
};
// STRING: GAMEMD 0x818164 — "Civilian".
extern HouseTypeName_00501540 DAT_00818164;

// HouseClass — only the members CanAlly touches.
struct House_00501540
{
    char                 _pad000[0x30];           // +0x0000
    int                  ArrayIndex;              // +0x0030
    HouseType_00501540*  Type;                    // +0x0034
    char                 _pad038[0x1F5 - 0x38];   // +0x0038
    char                 Defeated;                // +0x01F5
    char                 _pad1F6[0x5788 - 0x1F6]; // +0x01F6
    int                  Allies;                  // +0x5788

    // FUNCTION: GAMEMD 0x4F9A50 (inlined here) — HouseClass::IsAlliedWith.
    bool IsAlliedWith(House_00501540 const* pHouse) const
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

    // FUNCTION: GAMEMD 0x501540 — HouseClass::CanAlly.
    bool CanAlly(House_00501540* other);
};
GG_STATIC_ASSERT(offsetof(House_00501540, ArrayIndex) == 0x30);
GG_STATIC_ASSERT(offsetof(House_00501540, Type)       == 0x34);
GG_STATIC_ASSERT(offsetof(House_00501540, Defeated)   == 0x1F5);
GG_STATIC_ASSERT(offsetof(House_00501540, Allies)     == 0x5788);

// GLOBAL: GAMEMD 0xA8022C — HouseClass::Array.Items.
extern House_00501540** DAT_00A8022C;
// GLOBAL: GAMEMD 0xA80238 — HouseClass::Array.Count.
extern int DAT_00A80238;
// GLOBAL: GAMEMD 0xA8B238 — SessionClass::Instance.GameMode (Campaign == 0).
extern int DAT_00A8B238;
// GLOBAL: GAMEMD 0xA8E7AC — Unsorted::ScenarioInit.
extern int DAT_00A8E7AC;

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_CAN_ALLY_METHODS_H
