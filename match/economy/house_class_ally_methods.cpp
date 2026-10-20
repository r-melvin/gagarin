// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x4F9A10 / 0x4F9A50 /
//   0x4F9A90 (Ghidra disasm). Cross-checked vs YRpp HouseClass.h IsAlliedWith
//   (consult-only; each offset/branch reconfirmed against the disassembly).
//
// Translation unit: HouseClass::IsAlliedWith(int / HouseClass* / ObjectClass*).
// Each tests this->Allies (bitfield dword @0x5788) against (1 << otherIndex),
// with short-circuit self/identity/-1 guards. The ObjectClass* overload inlines
// the same house logic after a virtual GetOwningHouse() call (vtable +0x3C).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4F9A10   HouseClass::IsAlliedWith(int)              (__thiscall)
//   FUNCTION: GAMEMD 0x4F9A50   HouseClass::IsAlliedWith(HouseClass const*)(__thiscall)
//   FUNCTION: GAMEMD 0x4F9A90   HouseClass::IsAlliedWith(ObjectClass const*)(__thiscall)

#include "house_class_ally_methods.h"

// Primary slot +0x3C is read by the object overload at 0x4F9A90.
// The shared ObjectClass is an explicit-vptr layout, not a full virtual model.
// The member-pointer owner models the call ABI; original virtual declaration
// ownership and complete dynamic tables remain unproven here.
typedef HouseClass* (ObjectClass::*HouseGetOwningHouse)() const;
struct HouseObjectVtablePrefix
{
    char unknown_00[0x3C];
    HouseGetOwningHouse GetOwningHouse;
};
GG_STATIC_ASSERT(offsetof(ObjectClass, _vtable_IPersistStream) == 0);
GG_STATIC_ASSERT(offsetof(HouseObjectVtablePrefix, GetOwningHouse) == 0x3C);
GG_STATIC_ASSERT(sizeof(HouseGetOwningHouse) == 4);

// FUNCTION: GAMEMD 0x4F9A10  HouseClass::IsAlliedWith(int)  (__thiscall)
bool HouseClass::IsAlliedWith(int idxHouse) const
{
    if (idxHouse == this->ArrayIndex) return true;
    if (idxHouse != -1)
        return (this->Allies & (1 << idxHouse)) != 0;
    return false;
}

// FUNCTION: GAMEMD 0x4F9A50  HouseClass::IsAlliedWith(HouseClass const*)  (__thiscall)
bool HouseClass::IsAlliedWith(HouseClass const* pHouse) const
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

// FUNCTION: GAMEMD 0x4F9A90  HouseClass::IsAlliedWith(ObjectClass const*)  (__thiscall)
bool HouseClass::IsAlliedWith(ObjectClass const* pObject) const
{
    if (pObject) {
        const HouseObjectVtablePrefix* vtable =
            static_cast<const HouseObjectVtablePrefix*>(pObject->_vtable_IPersistStream);
        HouseClass* pHouse = (pObject->*vtable->GetOwningHouse)();
        if (pHouse) {
            if (pHouse == this) return true;
            if (pHouse->ArrayIndex == this->ArrayIndex) return true;
            if (pHouse->ArrayIndex != -1) {
                bool allied = (this->Allies & (1 << pHouse->ArrayIndex)) != 0;
                return allied;
            }
        }
    }
    return false;
}
