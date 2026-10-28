// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native entry 0x5F7900 walks HouseClass's building vector and selects an
// eligible matching factory, preferring the primary one. Names of the three
// Boolean policy arguments remain unknown; branch and member evidence is
// native entry-point disassembly through 0x5F7A8B.
#include "../_layout/object_type_class.h"
#include "../_layout/house_class.h"
#include "../_layout/building_class.h"

GG_STATIC_ASSERT(offsetof(HouseClass, Buildings) == 0x68);
GG_STATIC_ASSERT(offsetof(HouseClass, Buildings.Items) == 0x6C);
GG_STATIC_ASSERT(offsetof(HouseClass, Buildings.Count) == 0x78);
GG_STATIC_ASSERT(sizeof(((HouseClass*)0)->Buildings) == 0x18);
GG_STATIC_ASSERT(offsetof(BuildingClass, InLimbo) == 0x81);
GG_STATIC_ASSERT(sizeof(((BuildingClass*)0)->InLimbo) == 1);
GG_STATIC_ASSERT(offsetof(BuildingClass, Type) == 0x520);
GG_STATIC_ASSERT(sizeof(((BuildingClass*)0)->Type) == 4);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, Factory) == 0xEB8);
GG_STATIC_ASSERT(sizeof(((BuildingTypeClass*)0)->Factory) == 4);
GG_STATIC_ASSERT(offsetof(BuildingClass, HasPower) == 0x660);
GG_STATIC_ASSERT(sizeof(((BuildingClass*)0)->HasPower) == 1);
GG_STATIC_ASSERT(offsetof(BuildingClass, QueuedMission) == 0xB4);
GG_STATIC_ASSERT(sizeof(((BuildingClass*)0)->QueuedMission) == 4);
GG_STATIC_ASSERT(offsetof(BuildingClass, Owner) == 0x21C);
GG_STATIC_ASSERT(sizeof(((BuildingClass*)0)->Owner) == 4);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Naval) == 0xCCE);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->Naval) == 1);
GG_STATIC_ASSERT(offsetof(BuildingClass, IsPrimaryFactory) == 0x3D3);
GG_STATIC_ASSERT(sizeof(((BuildingClass*)0)->IsPrimaryFactory) == 1);

// FUNCTION: GAMEMD 0x5F7900
void* ObjectTypeClass::vf_37(bool a1, bool a2, bool a3, void* house)
{
    BuildingClass* result = 0;
    int mask = vf_28();
    HouseClass* owner = static_cast<HouseClass*>(house);
    int count = owner->Buildings.Count;
    for (int i = 0; i < count; ++i)
    {
        BuildingClass* building = owner->Buildings.Items[i];
        if (!building->InLimbo
            && building->Type->Factory == vf_11()
            && (!a2 || building->HasPower)
            && building->vf_97() != 0x13
            && building->QueuedMission != 0x13
            && (!a3 || building->Owner->FUN_004F7870(this, true, true) > 0)
            && (building->Type->vf_28() & mask))
        {
            if (!a1 && building->HasAnyLink() && vf_11() == 3)
            {
                if (vf_11() == 3 && building->HasFreeLink())
                {
                    if (building->IsPrimaryFactory)
                        return building;
                    result = building;
                }
            }
            else
            {
                // Native 0x5F7A10 guards the +0xCCE access by RTTI kind 0x28.
                // Naval occupies that offset in the shared TechnoType prefix.
                if (vf_11() == 0x28 && static_cast<TechnoTypeClass*>(this)->Naval)
                {
                    if (building->Type->Naval)
                    {
                        if (building->IsPrimaryFactory)
                            return building;
                        result = building;
                    }
                }
                else if (!building->Type->Naval)
                {
                    if (building->IsPrimaryFactory)
                        return building;
                    result = building;
                }
            }
        }
    }
    if (result)
        return result;
    return 0;
}
