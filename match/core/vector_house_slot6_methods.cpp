// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail RTTI type descriptors name VectorClass<bool> (vtable 0x7EAA5C) and
//   VectorClass<DiscreteDistributionClass<BuildingTypeClass>::
//   DistributionObject<BuildingTypeClass*>> (vtable 0x7EAAA4). Each address
//   below is slot 6 of that vtable (shared with the DynamicVectorClass
//   vtable).
#include "vector_class_operations.h"

class BuildingTypeClass;

// The distribution element: an 8-byte record copied as two dwords by
// 0x50E7C0. Only the first dword's pointer type is attested (by the RTTI
// template argument); the second is unknown.
template<class T> class DiscreteDistributionClass {
public:
    template<class U> class DistributionObject {
    public:
        U unknown_0;   // +0x00
        int unknown_4; // +0x04

        // A memberwise copy constructor: 0x50E7C0 loads and stores the two
        // dwords one at a time through the element address, the shape a
        // user-declared copy produces (an implicit one copies as a block). The
        // empty default constructor is only what the array allocations need;
        // its retail form is not measured here.
        DistributionObject() {}
        DistributionObject(const DistributionObject& other)
            : unknown_0(other.unknown_0), unknown_4(other.unknown_4) {}

        // Both dwords compared, as FindItemIndex 0x50FDB0 does inline.
        bool operator==(const DistributionObject& other) const
        {
            return unknown_0 == other.unknown_0 && unknown_4 == other.unknown_4;
        }
        bool operator!=(const DistributionObject& other) const { return !(*this == other); }
    };
};
typedef DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*>
    GgBuildingDistributionObject;
GG_STATIC_ASSERT(sizeof(GgBuildingDistributionObject) == 8);
GG_STATIC_ASSERT(offsetof(GgBuildingDistributionObject, unknown_4) == 4);

// TEMPLATE: GAMEMD 0x50E750
// VectorClass<bool>::Slot6 (slot 6)
template class VectorClass<bool>;

// TEMPLATE: GAMEMD 0x50E7C0
// VectorClass<DiscreteDistributionClass<BuildingTypeClass>::DistributionObject<BuildingTypeClass*>>::Slot6 (slot 6)
template class VectorClass<GgBuildingDistributionObject>;
