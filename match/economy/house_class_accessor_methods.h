// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | TSpp-name-cross-check
//   Every offset below was read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI, from the member-access instructions in the
//   seven functions this header serves (addresses in the comments). Member and
//   method *names* are cross-checked against YRpp HouseClass.h / RulesClass.h
//   (consult-only, no LICENSE) and TS++ src/house.h (Vinifera-Developers,
//   GPL-3.0 — `IsHuman`/`IsPlayerControl` there, widened to RA2's
//   `IsHumanPlayer`/`IsInPlayerControl`).
//
// HouseClass accessor leaves — seven independent small methods spanning the
// money, alliance, control, shroud, self-heal, and powered-centre surfaces.
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_ACCESSOR_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_ACCESSOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector_class.h"

struct HouseClass;
struct TechnoTypeClass;

// ---------------------------------------------------------------------------
// RulesClass shim — only the two self-heal step amounts are needed here.
//
// Confirmed from 0x50D9E0 / 0x50D9F0: MOV EAX,[0x008871E0] (the global
// RulesClass pointer) then IMUL against [EAX+0x34] / [EAX+0x3C]. The names come
// from YRpp's RulesClass run SelfHealInfantryFrames / SelfHealInfantryAmount /
// SelfHealUnitFrames / SelfHealUnitAmount, which places the two *Amount* ints
// at exactly +0x34 and +0x3C.
// ---------------------------------------------------------------------------
struct RulesSelfHealShim
{
    char _layout_pad_P2[0x34];       // +0x0000
    int  SelfHealInfantryAmount;     // +0x0034  (IMUL operand @0x50D9E0)
    char _pad38[0x3C - 0x38];        // +0x0038  (SelfHealUnitFrames)
    int  SelfHealUnitAmount;         // +0x003C  (IMUL operand @0x50D9F0)
};
GG_STATIC_ASSERT(offsetof(RulesSelfHealShim, SelfHealInfantryAmount) == 0x34);
GG_STATIC_ASSERT(offsetof(RulesSelfHealShim, SelfHealUnitAmount)     == 0x3C);

// GLOBAL: GAMEMD 0x008871E0 — pointer to the active RulesClass instance.
extern RulesSelfHealShim* RulesGlobalPtr;

// ---------------------------------------------------------------------------
// MapClass shim — ReshroudMap @0x50BD10 loads the instance address as an
// *immediate* (`MOV ECX,0x87F7E8`), so MapClass::Instance is a static object at
// 0x87F7E8, not a pointer variable. Only the one called method matters here.
// ---------------------------------------------------------------------------
struct MapShim
{
    void Reshroud(HouseClass* house);   // GAMEMD 0x577AB0 __thiscall (declared; reloc)
};

// GLOBAL: GAMEMD 0x0087F7E8 — the MapClass instance itself.
extern MapShim MapInstance;

// GLOBAL: GAMEMD 0x00A80228 — HouseClass::Array (the object; Items lands at
// 0x00A8022C, which is the address MakeAlly @0x4F9B50 reads directly).
extern DynamicVectorClassLayout HouseClassArray;

// GLOBAL: GAMEMD 0x00A8B238 — SessionClass::Instance.GameMode. Campaign == 0;
// IsControlledByHuman @0x50B730 branches on it being non-zero.
extern int SessionGameMode;

// ---------------------------------------------------------------------------
// HouseClass — only the members these seven methods touch are modelled; the
// full AbstractClass-derived layout is P2. Offsets confirmed numerically:
//   InfantrySelfHeal    @0x0164  int   (IMUL [ECX+0x164]  @0x50D9E0)
//   UnitsSelfHeal       @0x0168  int   (IMUL [ECX+0x168]  @0x50D9F0)
//   IsHumanPlayer       @0x01EC  bool  (MOV AL,[ECX+0x1EC] @0x50B730)
//   IsInPlayerControl   @0x01ED  bool  (MOV AL,[ECX+0x1ED] @0x50B730)
//   PoweredCenterCount  @0x02D8  int   (TEST/SETG [ECX+0x2D8] @0x50E1B0)
//   Balance             @0x030C  int   (ADD [ECX+0x30C]   @0x4F9950)
//   SpySatActive        @0x577A  bool  (MOV AL,[ECX+0x577A] @0x50BD10)
// ---------------------------------------------------------------------------
struct HouseClass
{
    char _pad0[0x164];                        // +0x0000
    int  InfantrySelfHeal;                    // +0x0164
    int  UnitsSelfHeal;                       // +0x0168
    char _pad1[0x1EC - 0x16C];                // +0x016C
    bool IsHumanPlayer;                       // +0x01EC
    bool IsInPlayerControl;                   // +0x01ED
    char _pad2[0x2D8 - 0x1EE];                // +0x01EE
    int  PoweredCenterCount;                  // +0x02D8
    char _pad3[0x30C - 0x2DC];                // +0x02DC
    int  Balance;                             // +0x030C
    char _pad4[0x577A - 0x310];               // +0x0310
    bool SpySatActive;                        // +0x577A

    // Declared ascending by retail address.
    void GiveMoney(int amount);                            // GAMEMD 0x4F9950
    void MakeAlly(int houseIndex, bool announce);          // GAMEMD 0x4F9B50
    bool IsControlledByHuman() const;                      // GAMEMD 0x50B730
    void ReshroudMap();                                    // GAMEMD 0x50BD10
    int  GetInfSelfHealStep() const;                       // GAMEMD 0x50D9E0
    int  GetUnitSelfHealStep() const;                      // GAMEMD 0x50D9F0
    bool GainedPoweredCenter(TechnoTypeClass* type);       // GAMEMD 0x50E1B0

    // Retail callee we are NOT matching here — declared (no body) so cl emits a
    // reloc-normalised CALL. The HouseClass* overload MakeAlly @0x4F9B70.
    void MakeAlly(HouseClass* who, bool announce);         // GAMEMD 0x4F9B70
};

GG_STATIC_ASSERT(offsetof(HouseClass, InfantrySelfHeal)   == 0x164);
GG_STATIC_ASSERT(offsetof(HouseClass, UnitsSelfHeal)      == 0x168);
GG_STATIC_ASSERT(offsetof(HouseClass, IsHumanPlayer)      == 0x1EC);
GG_STATIC_ASSERT(offsetof(HouseClass, IsInPlayerControl)  == 0x1ED);
GG_STATIC_ASSERT(offsetof(HouseClass, PoweredCenterCount) == 0x2D8);
GG_STATIC_ASSERT(offsetof(HouseClass, Balance)            == 0x30C);
GG_STATIC_ASSERT(offsetof(HouseClass, SpySatActive)       == 0x577A);

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_ACCESSOR_METHODS_H
