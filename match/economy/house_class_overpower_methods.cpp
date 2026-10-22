// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x4F9AF0 / 0x50C8C0 (Ghidra
//   disasm). Cross-checked vs YRpp CanOverpower / Cheer
//   (each offset, vtable slot and global reconfirmed below).
//
// Translation unit: HouseClass::CanOverpower + HouseClass::Cheer.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4F9AF0   HouseClass::CanOverpower (__thiscall)
//   FUNCTION: GAMEMD 0x50C8C0   HouseClass::Cheer        (__thiscall)
//   GLOBAL:   GAMEMD 0xA8EC78   TechnoClass::Array (DynamicVectorClass<TechnoClass*>)
//   GLOBAL:   GAMEMD 0x8871E0   RulesClass::Instance pointer

#include "house_class_overpower_methods.h"
#include "../audio/voc_class_play_global_methods.h"

// ---------------------------------------------------------------------------
// Offset-pinned model of the global TechnoClass::Array (DynamicVectorClass head
// @0xA8EC78). Confirmed from 0x50C8C0: `MOV EAX,[0xA8EC7C]` == &Array.Items
// (Items @+0x04) and `MOV EDI,[0xA8EC88]` == Array.Count (@+0x10).
// ---------------------------------------------------------------------------
struct DynamicVectorClass_TechnoPtr
{
    void*        vtable;             // +0x00
    TechnoClass** Items;            // +0x04
    int          Capacity;          // +0x08
    int          IsAllocated;       // +0x0C
    int          Count;             // +0x10
    int          CapacityIncrement; // +0x14
};
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(DynamicVectorClass_TechnoPtr, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass_TechnoPtr, Count) == 0x10);
#endif

// GLOBAL: GAMEMD 0xA8EC78 -- the engine's global array of all technos.
extern DynamicVectorClass_TechnoPtr TechnoArray;

// RulesClass singleton (pointer global @0x8871E0). Only field @0x1C8 is touched
// (`MOV EAX,[0x8871E0]; MOV ECX,[EAX+0x1C8]`).
struct RulesClass
{
    char _pad00[0x1C8];   // +0x00
    int  field_1C8;       // +0x1C8
};
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(RulesClass, field_1C8) == 0x1C8);
#endif
extern RulesClass* Rules;  // GLOBAL: GAMEMD 0x8871E0

// FUNCTION: GAMEMD 0x4F9AF0  HouseClass::CanOverpower  (__thiscall)
bool HouseClass::CanOverpower(TechnoClass* pTarget) const
{
    if (pTarget && (pTarget->AbstractFlags & 2)) {
        HouseClass* pHouse = pTarget->GetOwningHouse();
        if (pHouse) {
            if (pHouse == this) return true;
            if (pHouse->ArrayIndex == this->ArrayIndex) return true;
            if (pHouse->ArrayIndex != -1) {
                bool overpower = (this->Allies & (1 << pHouse->ArrayIndex)) != 0;
                return overpower;
            }
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x50C8C0  HouseClass::Cheer  (__thiscall)
//
// Retail loads EDX (the 0x2000 pan) between the controller and volume pushes,
// which is cl's right-to-left order for PlayGlobal(index, volume, pan,
// controller): the pan is declared after the volume.
void HouseClass::Cheer()
{
    int count = TechnoArray.Count;
    for (int i = 0; i < count; ++i) {
        TechnoClass* pTechno = TechnoArray.Items[i];
        if (pTechno && pTechno->Owner == this) {
            pTechno->OnHouseCheer(0);
        }
    }
    VocClass::PlayGlobal(Rules->field_1C8, 1.0f, 0x2000, 0);
}
