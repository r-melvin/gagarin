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

// Retail helper @0x750920, called __fastcall(int, uint, undefined4, int*).
// Declared (no body) so cl emits a normalised-reloc call.
int* __fastcall Func_750920(int param1, unsigned int param2,
                            float param3, int* param4);

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
// BUILD-SCHEDULING DELTA (status bool-delta): everything matches 100% except the
// __fastcall argument set-up for the final Func_750920 call -- retail (cl build
// 8447) schedules `mov edx,0x2000` BETWEEN the two stack pushes, whereas our cl
// our compiler emits both pushes first, then the edx/ecx loads. Identical
// instructions, identical total length, same root cause as the documented
// unexplained-codegen setcc-tail scheduling delta. Confirmed phrasing-invariant: three
// independent phrasings (int/float param3, temp-hoisted ecx arg) all produce the
// our compiler ordering, so there is no source form that reproduces the 8447 schedule.
// Eight further spellings were measured this pass against a labelled control,
// as members of a cloned class (never as free functions, per the nineteenth
// batch), and seven are BYTE-IDENTICAL to it at 93.3%: the kind argument named
// ahead of the call, both register arguments named in retail's load order, the
// float argument named, the trailing null named, the call routed through a
// forced-inline forwarder, and the kind written as `1u << 13` so it is not a
// foldable literal. Only a `volatile` kind moves it, to 3.0%. Same residual and
// same verdict as 0x452D40, 0x458200, 0x683EB0, 0x41C2E0 and 0x40A850: the
// register-argument load is scheduled against the stack pushes by the backend,
// not by the source.
//
void HouseClass::Cheer()
{
    int count = TechnoArray.Count;
    for (int i = 0; i < count; ++i) {
        TechnoClass* pTechno = TechnoArray.Items[i];
        if (pTechno && pTechno->Owner == this) {
            pTechno->OnHouseCheer(0);
        }
    }
    Func_750920(Rules->field_1C8, 0x2000, 1.0f, 0);
}
