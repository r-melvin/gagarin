// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
//
// VectorClass / DynamicVectorClass over rc_ptr<WorldDominationTour::Territory>
// (RTTI vtables 0x7F7184 and 0x7F7164) and VectorClass over
// WorldDominationTour::Centroid (0x7F71E0): the members of these
// instantiations not already bound elsewhere, in retail address order. The
// element is rc_ptr<T> (wdt_rc_ptr.h); the Centroid element is twelve bytes
// (slot 6 at 0x769D30 copies three dwords through the hidden result pointer).
// The explicit instantiations also emit the members bound in other units
// (deleting destructors, Clear, Slot5, the Centroid bodies); only the rows
// annotated here are claimed from this unit.
#include "vector_class_operations.h"
#include "../network/wdt_rc_ptr.h"

namespace WorldDominationTour {
class Territory;
struct Centroid
{
    int unknown_00;   // +0x00
    int unknown_04;   // +0x04
    int unknown_08;   // +0x08
    bool operator==(const Centroid& o) const
    {
        return unknown_00 == o.unknown_00 && unknown_04 == o.unknown_04 && unknown_08 == o.unknown_08;
    }
    bool operator!=(const Centroid& o) const { return !(*this == o); }
};
}
GG_STATIC_ASSERT(sizeof(WorldDominationTour::Centroid) == 0x0C);

typedef rc_ptr<WorldDominationTour::Territory> TerritoryPtr;

// FUNCTION: GAMEMD 0x769C80
// DynamicVectorClass<rc_ptr<WorldDominationTour::Territory>>::Slot5

// FUNCTION: GAMEMD 0x769CA0
// VectorClass<rc_ptr<WorldDominationTour::Territory>>::Slot6 (shared by both tables)

// FUNCTION: GAMEMD 0x769D30
// VectorClass<WorldDominationTour::Centroid>::Slot6

// FUNCTION: GAMEMD 0x769DE0
// VectorClass<rc_ptr<WorldDominationTour::Territory>>::operator== (shared by both tables)

// FUNCTION: GAMEMD 0x769E30
// VectorClass<rc_ptr<WorldDominationTour::Territory>>::SetCapacity
// PARTIAL (54.4%). Retail frees the old block with `delete[]` (slot 0 with 3)
// and clamps the copy count as `capacity < Capacity ? capacity : Capacity`
// (reusing the capacity register); vector_class_operations.h uses gg_free and
// the two-step clamp. With both changes in the shared header this body
// measures 100% (held for the lander).

// FUNCTION: GAMEMD 0x769F80
// VectorClass<rc_ptr<WorldDominationTour::Territory>>::FindItemIndex

// FUNCTION: GAMEMD 0x769FC0
// VectorClass<rc_ptr<WorldDominationTour::Territory>>::Slot5

// FUNCTION: GAMEMD 0x769FE0
// DynamicVectorClass<rc_ptr<WorldDominationTour::Territory>>::SetCapacity
// PARTIAL (28.9%). Retail inlines the base SetCapacity but calls the element
// constructor out of line (0x76A7C0) in both array loops; cl inlines it.

// FUNCTION: GAMEMD 0x76A100
// DynamicVectorClass<rc_ptr<WorldDominationTour::Territory>>::FindItemIndex

// FUNCTION: GAMEMD 0x76A610
// rc_ptr<WorldDominationTour::Territory>: the deleting destructor the compiler emits for it.

// FUNCTION: GAMEMD 0x76A7E0
// VectorClass<rc_ptr<WorldDominationTour::Territory>>::VectorClass

// VTABLE: GAMEMD 0x7F7184 -- VectorClass<rc_ptr<WorldDominationTour::Territory>>.
template class VectorClass<TerritoryPtr>;
// VTABLE: GAMEMD 0x7F7164 -- DynamicVectorClass<rc_ptr<WorldDominationTour::Territory>>.
template class DynamicVectorClass<TerritoryPtr>;
// VTABLE: GAMEMD 0x7F71E0 -- VectorClass<WorldDominationTour::Centroid>.
template class VectorClass<WorldDominationTour::Centroid>;

GG_STATIC_ASSERT(offsetof(DynamicVectorClass<TerritoryPtr>, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<TerritoryPtr>, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<TerritoryPtr>, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<TerritoryPtr>, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<TerritoryPtr>, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(TerritoryPtr) == 0x08);
