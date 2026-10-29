// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   WDTTerritory and WDTState, their rc_ptr factories, and the
//   VectorClass<rc_ptr<WDTTerritory>> members emitted beside them. Class names
//   are the retail RTTI names; members are placeholders.
#include "world_domination_tour.h"
#include "../core/vector_class_operations.h"

// FUNCTION: GAMEMD 0x76AAB0
rc_ptr<WDTTerritory> FUN_0076AAB0()
{
    return rc_ptr<WDTTerritory>(new WDTTerritory);
}

// FUNCTION: GAMEMD 0x76AAF0
WDTTerritory::WDTTerritory()
{
    unknown_08 = 0;
    unknown_0E = 10;
    unknown_0F = 10;
    unknown_10 = 10000;
    unknown_0C = 0;
    unknown_12 = 1;
    unknown_13 = 1;
    unknown_14 = 2;
    unknown_1C = 1;
    unknown_1D = 0;
    unknown_1E = 0;
    unknown_1F[0].unknown_00 = 0;
    unknown_1F[0].unknown_01 = 100;
    unknown_1F[0].unknown_02 = 50;
    unknown_1F[1].unknown_00 = 0;
    unknown_1F[1].unknown_01 = 100;
    unknown_1F[1].unknown_02 = 50;
    unknown_1F[2].unknown_00 = 0;
    unknown_1F[2].unknown_01 = 100;
    unknown_1F[2].unknown_02 = 50;
    unknown_1F[3].unknown_00 = 0;
    unknown_1F[3].unknown_01 = 100;
    unknown_1F[3].unknown_02 = 50;
    unknown_1F[4].unknown_00 = 1;
    unknown_1F[4].unknown_01 = 100;
    unknown_1F[4].unknown_02 = 50;
    unknown_1F[5].unknown_00 = 0;
    unknown_1F[5].unknown_01 = 100;
    unknown_1F[5].unknown_02 = 50;
    unknown_1F[6].unknown_00 = 0;
    unknown_1F[6].unknown_01 = 100;
    unknown_1F[6].unknown_02 = 50;
    unknown_1F[7].unknown_00 = 0;
    unknown_1F[7].unknown_01 = 100;
    unknown_1F[7].unknown_02 = 50;
    unknown_38 = -1;
    unknown_3C = -1;
}

// FUNCTION: GAMEMD 0x76AB90
WDTTerritory::~WDTTerritory()
{
}

// FUNCTION: GAMEMD 0x76ABA0
rc_ptr<WDTState> FUN_0076ABA0(void* source)
{
    return rc_ptr<WDTState>(new WDTState(source));
}

// FUNCTION: GAMEMD 0x76B080
bool WDTState::FUN_0076B080() const
{
    if (unknown_44 != 0) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x76B090
unsigned char WDTState::FUN_0076B090() const
{
    return unknown_48;
}

// FUNCTION: GAMEMD 0x76B740
// DynamicVectorClass<rc_ptr<WDTTerritory>>::Slot5

// FUNCTION: GAMEMD 0x76B760
// VectorClass<rc_ptr<WDTTerritory>>::Slot6

// FUNCTION: GAMEMD 0x76B790
// rc_ptr<WDTTerritory>::rc_ptr(WDTTerritory*)
// SYNTHETIC: GAMEMD 0x538A20 -- compiler-generated rc_ptr<WDTTerritory> vector deleting destructor.
// FUNCTION: GAMEMD 0x76BC60
// rc_ptr<WDTTerritory>::rc_ptr()
template class rc_ptr<WDTTerritory>;

// FUNCTION: GAMEMD 0x76B7B0
// VectorClass<rc_ptr<WDTTerritory>>::operator=

// FUNCTION: GAMEMD 0x76B870
// VectorClass<rc_ptr<WDTTerritory>>::operator==

// FUNCTION: GAMEMD 0x76B8C0
// VectorClass<rc_ptr<WDTTerritory>>::SetCapacity. PARTIAL: retail releases
// the old block with the element-destroying delete[] (a call through the
// first element's deleting destructor); the canonical template frees raw.

// FUNCTION: GAMEMD 0x76BA10
// VectorClass<rc_ptr<WDTTerritory>>::FindItemIndex

// FUNCTION: GAMEMD 0x76BA50
// VectorClass<rc_ptr<WDTTerritory>>::Slot5

// FUNCTION: GAMEMD 0x76BA70
// DynamicVectorClass<rc_ptr<WDTTerritory>>::SetCapacity. PARTIAL, as 0x76B8C0.

// FUNCTION: GAMEMD 0x76BB90
// DynamicVectorClass<rc_ptr<WDTTerritory>>::FindItemIndex

// The two vector instantiations above. Only the members annotated here are
// claimed; the canonical template's storage handling does not yet model
// element construction and destruction for a class element type.
template class VectorClass<rc_ptr<WDTTerritory> >;
template class DynamicVectorClass<rc_ptr<WDTTerritory> >;
