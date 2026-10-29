// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4FAE50:
//     HouseClass::Supers.Items            [EBX+0x258]  (MOV EAX,[EBX+0x258])
//     SuperClass::Type                    [EDI+0x28]   (MOV ECX,[EDI+0x28])
//     SuperClass::ChronoMapCoords         [EDI+0x62]   (MOV [EDI+0x62],EAX, dword copy)
//     SuperWeaponTypeClass::PostClick     [ECX+0xEE]   (MOV DL,[ECX+0xEE])
//     SuperWeaponTypeClass +0xF0 (int)    [ECX+0xF0]   (MOV EDX,[ECX+0xF0], indexes Supers)
//   Globals: HouseClass::CurrentPlayer 0xA83D4C (CMP EBX,[0xA83D4C]),
//   HouseClass::Array.Items 0xA8022C and .Count 0xA80238 (the trailing loop).
//   Callees: SuperClass::ClickFire 0x6CB920 (__thiscall bool, CellStruct&),
//   SuperClass::SetReadiness 0x6CB820, SuperClass::StopPreclickAnim 0x6CB830
//   and the per-house notification 0x4FAF00 (__thiscall SuperClass*,
//   CellStruct&). `RET 0x8` fixes two stack arguments.  Names cross-checked
//   against YRpp
//   (every offset reconfirmed above).
#ifndef GG_MATCH_AI_HOUSE_CLASS_FIRE_SW_METHODS_H
#define GG_MATCH_AI_HOUSE_CLASS_FIRE_SW_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/cell.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);
#include "../_layout/super_class.h"


class HouseClass
{
public:
    char         _pad000[0x258];   // +0x0000
    SuperClass** SupersItems;      // +0x0258

    // FUNCTION: GAMEMD 0x4FAE50
    bool Fire_SW(int index, const CellStruct& cell);

    // FUNCTION: GAMEMD 0x4FAF00 (decl; reloc) — per-house reaction to a
    // superweapon launch.
    void FUN_004FAF00(SuperClass* sw, const CellStruct& cell);
};
GG_STATIC_ASSERT(offsetof(HouseClass, SupersItems) == 0x258);

// GLOBAL: GAMEMD 0xA83D4C — HouseClass::CurrentPlayer.
extern HouseClass* CurrentPlayer;
// GLOBAL: GAMEMD 0xA8022C — HouseClass::Array.Items.
extern HouseClass** HouseArrayItems;
// GLOBAL: GAMEMD 0xA80238 — HouseClass::Array.Count.
extern int HouseArrayCount;

#endif  // GG_MATCH_AI_HOUSE_CLASS_FIRE_SW_METHODS_H
