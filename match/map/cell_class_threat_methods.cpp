// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at 0x481870).
//   Names cross-checked against YRpp
//   (every offset/address reconfirmed against the binary).
//
// reccmp annotation:
//   FUNCTION: GAMEMD 0x481870   CellClass::UpdateThreat              (__thiscall)
//   GLOBAL:   GAMEMD 0xA80228   HouseClass::Array (DynamicVectorClass<HouseClass*>)
//   GLOBAL:   GAMEMD 0x87F7E8   the cell -> threat-region lookup object

#include "cell_class_threat_methods.h"

// ---------------------------------------------------------------------------
// Offset-pinned model of the global HouseClass::Array (DynamicVectorClass head).
// Confirmed from 0x481870: `MOV EDX,[0xA8022C]` == &Array.Items (Array @0xA80228,
// Items @+0x04) and `MOV EAX,[0xA80238]` == Array.Count (@+0x10).
// ---------------------------------------------------------------------------
struct DynamicVectorClass_HousePtr
{
    void*        vtable;             // +0x00
    HouseClass** Items;             // +0x04
    int          Capacity;          // +0x08
    int          IsAllocated;       // +0x0C
    int          Count;             // +0x10
    int          CapacityIncrement; // +0x14
};
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(DynamicVectorClass_HousePtr, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass_HousePtr, Count) == 0x10);
#endif

// GLOBAL: GAMEMD 0xA80228 — the engine's global array of all houses.
extern DynamicVectorClass_HousePtr HouseArray;
// GLOBAL: GAMEMD 0x87F7E8 — cell-coordinate -> threat-region lookup.
extern RegionLookupClass RegionLookup;

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x481870  (__thiscall)
//
// Called whenever anything moves: once to remove this cell's threat from the
// mover's old position, once to add it at the new one. For every foreign house
// not allied with `SourceHouse`, fold this cell's region into that house's
// per-region threat table.
// ---------------------------------------------------------------------------
void CellClass::UpdateThreat(unsigned int SourceHouse, int ThreatLevel)
{
    CellStruct coords = this->MapCoords;
    int region = RegionLookup.CoordsToRegion(&coords);

    for (int i = 0; i < HouseArray.Count; ++i) {
        HouseClass* pHouse = HouseArray.Items[i];
        if (pHouse
            && (unsigned int)pHouse->ArrayIndex != SourceHouse
            && !pHouse->IsAlliedWith((int)SourceHouse)) {
            pHouse->FUN_004FA2E0(region, ThreatLevel);
        }
    }
}
