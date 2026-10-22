// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm).
//   Names cross-checked against YRpp
//   (each offset/address reconfirmed
//   against the user's binary below).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x502D30   HouseClass::FindByCountryIndex          (static __fastcall)
//   FUNCTION: GAMEMD 0x50B6F0   HouseClass::IsControlledByCurrentPlayer (__thiscall)
//   GLOBAL:   GAMEMD 0xA80228   HouseClass::Array  (DynamicVectorClass<HouseClass*>)
//   GLOBAL:   GAMEMD 0xA83D4C   HouseClass::CurrentPlayer  (HouseClass*)
//   GLOBAL:   GAMEMD 0xA8B238   SessionClass::Instance.GameMode  (int; Campaign==0)

#include "house_class_lookup_methods.h"

// ---------------------------------------------------------------------------
// Offset-pinned model of the global HouseClass::Array (DynamicVectorClass head).
// Confirmed from 0x502D30: `MOV ESI,[0xA8022C]` == &Array.Items (Array @0xA80228,
// Items @+0x04) and `MOV EDI,[0xA80238]` == Array.Count (@+0x10). YRpp.
// ---------------------------------------------------------------------------
struct DynamicVectorClass_HousePtr
{
    void*        vtable;             // +0x00
    HouseClass** Items;             // +0x04
    int          Capacity;          // +0x08
    int          IsAllocated;       // +0x0C
    int          Count;             // +0x10
    int          CapacityIncrement; // +0x14
};
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(DynamicVectorClass_HousePtr, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass_HousePtr, Count) == 0x10);
#endif

// GLOBAL: GAMEMD 0xA80228 — the engine's global array of all houses.
extern DynamicVectorClass_HousePtr HouseArray;
// GLOBAL: GAMEMD 0xA83D4C — the house of the player at this computer.
extern HouseClass* CurrentPlayer;
// GLOBAL: GAMEMD 0xA8B238 — SessionClass::Instance.GameMode (GameMode::Campaign==0).
extern int SessionGameMode;

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x502D30  (static __fastcall)
//
// Return the first house in the global Array whose country type-index
// (Type->ArrayIndex2) equals `houseType`, or NULL if none.
// ---------------------------------------------------------------------------
HouseClass* HouseClass::FindByCountryIndex(int houseType)
{
    for (int i = 0; i < HouseArray.Count; ++i) {
        HouseClass* pHouse = HouseArray.Items[i];
        if (pHouse->Type->ArrayIndex2 == houseType) {
            return pHouse;
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x50B6F0  (__thiscall)
//
// Outside campaign play the only controllable house is the current player;
// in campaign, any human-flagged or player-controlled house qualifies.
// ---------------------------------------------------------------------------
bool HouseClass::IsControlledByCurrentPlayer() const
{
    if (SessionGameMode == 0) {
        return this->IsHumanPlayer || this->IsInPlayerControl;
    }
    return this == CurrentPlayer;
}
