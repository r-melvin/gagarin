// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Bytes matched against retail gamemd.exe v1.001 at 0x4F9950 / 0x4F9B50 /
//   0x50B730 / 0x50BD10 / 0x50D9E0 / 0x50D9F0 / 0x50E1B0 via the local Ghidra
//   disassembly. Member offsets confirmed numerically (see the header).
//
// HouseClass accessor leaves. Functions ordered ascending by retail address.

#include "house_class_accessor_methods.h"

// FUNCTION: GAMEMD 0x4F9950  HouseClass::GiveMoney (__thiscall, ret 0x4)
void HouseClass::GiveMoney(int amount)
{
    Balance += amount;
}

// FUNCTION: GAMEMD 0x4F9B50  HouseClass::MakeAlly (__thiscall, ret 0x8)
// The by-index overload: resolve the house through HouseClass::Array and
// forward to the by-pointer overload at 0x4F9B70. Retail reads the Items base
// straight out of 0x00A8022C, which is HouseClass::Array (@0x00A80228) + 4 —
// i.e. Array is a static *object*, not a pointer variable.
void HouseClass::MakeAlly(int houseIndex, bool announce)
{
    MakeAlly(((HouseClass**)HouseClassArray.Items)[houseIndex], announce);
}

// FUNCTION: GAMEMD 0x50B730  HouseClass::IsControlledByHuman (__thiscall)
// Outside a campaign only the explicit human-player flag counts; inside one, a
// house the player has been handed control of counts too.
//
// Phrasing is load-bearing here. The GameMode test has to come first so VC6
// reads the global into EAX and schedules `MOV AL,[ECX+0x1EC]` *between* the
// TEST and the JNZ (retail's exact sequence); leading with the flag instead puts
// the global in EDX. The second half has to stay `result = result || ...` rather
// than `return a || b`, because the assignment form materialises the bool in AL
// (`XOR AL,AL` / `MOV AL,1`) while the return-expression form widens to EAX.
bool HouseClass::IsControlledByHuman() const
{
    if (SessionGameMode != 0) {          // anything but GameMode::Campaign
        return IsHumanPlayer;
    }
    bool result = IsHumanPlayer;
    result = result || IsInPlayerControl;
    return result;
}

// FUNCTION: GAMEMD 0x50BD10  HouseClass::ReshroudMap (__thiscall)
// A spy satellite pins the map revealed, so the reshroud is skipped entirely.
void HouseClass::ReshroudMap()
{
    if (!SpySatActive) {
        MapInstance.Reshroud(this);
    }
}

// FUNCTION: GAMEMD 0x50D9E0  HouseClass::GetInfSelfHealStep (__thiscall)
int HouseClass::GetInfSelfHealStep() const
{
    return RulesGlobalPtr->SelfHealInfantryAmount * InfantrySelfHeal;
}

// FUNCTION: GAMEMD 0x50D9F0  HouseClass::GetUnitSelfHealStep (__thiscall)
int HouseClass::GetUnitSelfHealStep() const
{
    return RulesGlobalPtr->SelfHealUnitAmount * UnitsSelfHeal;
}

// FUNCTION: GAMEMD 0x50E1B0  HouseClass::GainedPoweredCenter (__thiscall, ret 0x4)
// NOTE: the retail body ignores its argument entirely and just reports whether
// the powered-centre count at +0x2D8 is positive (`SETG AL`), so this is a
// bool-returning predicate, not the void mutator YRpp declares
// for this address. The name is kept from YRpp; the signature follows the bytes.
bool HouseClass::GainedPoweredCenter(TechnoTypeClass* type)
{
    return PoweredCenterCount > 0;
}
