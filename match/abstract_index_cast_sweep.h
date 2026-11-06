// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Every offset, global address and RTTI type-descriptor address below was
//   read numerically off the user's own retail gamemd.exe v1.001 with the local
//   Ghidra CLI (disasm at 0x6E6BB0 and its seventeen siblings, memory read at
//   0xB0E840 / 0xB78828 and at each `.?AV...@@` descriptor). No YRpp binding.
//
// The 204-byte "look the abstract object up by ID, then dynamic_cast it" family.
//
// Eighteen sibling accessors share one body. Each checks the owner's one-byte
// abstract tag at +4 against 0x34, looks the owner's ID (+0) up in the single
// global IndexClass at 0xB0E840, and hands the stored pointer to the CRT's
// `__RTDynamicCast`. The only thing that varies across the family is the target
// RTTI type descriptor pushed as the fourth argument, so the eighteen differ in
// exactly three bytes plus two call displacements.
//
// The whole lookup (IndexClass<int, AbstractClass*>::FetchIndex, _layout/index.h) is
// inlined into every member: the empty-table test, the one-entry archive cache,
// the lazy qsort that sorts the table on first use, and the binary search over
// 8-byte nodes. cl threads the "not found" exits of that chain into a single
// error return, which is why retail materialises the miss slot with `MOV
// EAX,imm32` and then shares one `MOV EAX,[EAX]` with the found path.
#ifndef GG_MATCH_CORE_ABSTRACT_INDEX_CAST_SWEEP_H
#define GG_MATCH_CORE_ABSTRACT_INDEX_CAST_SWEEP_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "_layout/index.h"

// MSVC6's RTTI helper, declared by hand rather than reached through a real
// `dynamic_cast` so the five pushed arguments are spelled explicitly and no
// /GR-dependent type descriptor has to be emitted for a reconstructed class.
extern "C" void* __cdecl FUN_007CAAE4(void* object, long vfDelta,
                                      void* srcType, void* dstType,
                                      int isReference);   // GAMEMD 0x7CAAE4

// RTTI type descriptors. Only their addresses matter here; the payload is the
// CRT's own type_info image and is never reconstructed.
// GLOBAL: GAMEMD 0x8177C8   .?AVAbstractClass@@
extern char TypeDesc_AbstractClass[];
// GLOBAL: GAMEMD 0x817808   .?AVAbstractTypeClass@@
extern char TypeDesc_AbstractTypeClass[];
// GLOBAL: GAMEMD 0x817AF8   .?AVObjectClass@@
extern char TypeDesc_ObjectClass[];
// GLOBAL: GAMEMD 0x817B78   .?AVFootClass@@
extern char TypeDesc_FootClass[];
// GLOBAL: GAMEMD 0x817B90   .?AVAircraftClass@@
extern char TypeDesc_AircraftClass[];
// GLOBAL: GAMEMD 0x817F98   .?AVTechnoTypeClass@@
extern char TypeDesc_TechnoTypeClass[];
// GLOBAL: GAMEMD 0x8182C8   .?AVAnimClass@@
extern char TypeDesc_AnimClass[];
// GLOBAL: GAMEMD 0x818D60   .?AVBuildingClass@@
extern char TypeDesc_BuildingClass[];
// GLOBAL: GAMEMD 0x81AF70   .?AVBulletClass@@
extern char TypeDesc_BulletClass[];
// GLOBAL: GAMEMD 0x824500   .?AVHouseClass@@
extern char TypeDesc_HouseClass[];
// GLOBAL: GAMEMD 0x8249E8   .?AVTagClass@@
extern char TypeDesc_TagClass[];
// GLOBAL: GAMEMD 0x825508   .?AVInfantryClass@@
extern char TypeDesc_InfantryClass[];
// GLOBAL: GAMEMD 0x842CB0   .?AVTagTypeClass@@
extern char TypeDesc_TagTypeClass[];
// GLOBAL: GAMEMD 0x842CE8   .?AVTriggerClass@@
extern char TypeDesc_TriggerClass[];
// GLOBAL: GAMEMD 0x842D08   .?AVTriggerTypeClass@@
extern char TypeDesc_TriggerTypeClass[];
// GLOBAL: GAMEMD 0x842D28   .?AVTeamTypeClass@@
extern char TypeDesc_TeamTypeClass[];
// GLOBAL: GAMEMD 0x842D48   .?AVTerrainClass@@
extern char TypeDesc_TerrainClass[];
// GLOBAL: GAMEMD 0x842D68   .?AVTeamClass@@
extern char TypeDesc_TeamClass[];
// GLOBAL: GAMEMD 0x842D80   .?AVUnitClass@@
extern char TypeDesc_UnitClass[];

class AbstractClass;
class CellClass;
struct CellStruct;
struct CoordStruct;

// The owner: an integer ID at +0 and the one-byte abstract tag at +4. Every
// member of the family is a method on this shape. The constructors encode an
// object (tag 0x34, its IRTTITypeInfo id), a cell (tag 0x0B, X + Y * 1000) or
// nothing (tag 0).
struct AbstractIdOwner
{
    int  ID;      // +0x0000
    char Rtti;    // +0x0004

    AbstractIdOwner(AbstractClass* object);        // FUNCTION: GAMEMD 0x6E6AB0
    AbstractIdOwner(const CellStruct& cell);       // FUNCTION: GAMEMD 0x6E6B20
    AbstractIdOwner(const CoordStruct& coord);     // FUNCTION: GAMEMD 0x6E6B70
    AbstractClass* FUN_006E6E20();                  // FUNCTION: GAMEMD 0x6E6E20

    void* AsAbstractTypeClass();         // FUNCTION: GAMEMD 0x6E6BB0
    void* AsTagClass();                  // FUNCTION: GAMEMD 0x6E6C80
    void* AsTagTypeClass();              // FUNCTION: GAMEMD 0x6E6D50
    void* AsObjectClass();               // FUNCTION: GAMEMD 0x6E6FF0
    void* AsFootClass();                 // FUNCTION: GAMEMD 0x6E70C0
    void* AsTriggerClass();              // FUNCTION: GAMEMD 0x6E7190
    void* AsHouseClass();                // FUNCTION: GAMEMD 0x6E7260
    void* AsTechnoTypeClass();           // FUNCTION: GAMEMD 0x6E7330
    void* AsTriggerTypeClass();          // FUNCTION: GAMEMD 0x6E7400
    void* AsTeamTypeClass();             // FUNCTION: GAMEMD 0x6E74D0
    void* AsTerrainClass();              // FUNCTION: GAMEMD 0x6E75A0
    void* AsBulletClass();               // FUNCTION: GAMEMD 0x6E7670
    void* AsAnimClass();                 // FUNCTION: GAMEMD 0x6E7740
    void* AsTeamClass();                 // FUNCTION: GAMEMD 0x6E7810
    void* AsInfantryClass();             // FUNCTION: GAMEMD 0x6E78E0
    void* AsUnitClass();                 // FUNCTION: GAMEMD 0x6E79B0
    void* AsBuildingClass();             // FUNCTION: GAMEMD 0x6E7A80
    void* AsAircraftClass();             // FUNCTION: GAMEMD 0x6E7B50
};
GG_STATIC_ASSERT(offsetof(AbstractIdOwner, ID) == 0x0);
GG_STATIC_ASSERT(offsetof(AbstractIdOwner, Rtti) == 0x4);

// GLOBAL: GAMEMD 0xB0E840 -- defined in abstract_index_cast_sweep.cpp
extern IndexClass<int, AbstractClass*> AbstractIndex;

// One 8-byte index node: the integer key at +0, the stored pointer at +4.
struct IndexNode
{
    int   ID;      // +0x0000
    void* Data;    // +0x0004
};
GG_STATIC_ASSERT(offsetof(IndexNode, ID) == 0x0);
GG_STATIC_ASSERT(offsetof(IndexNode, Data) == 0x4);
GG_STATIC_ASSERT(sizeof(IndexNode) == 0x8);

// The held second spelling of the lookup (0x6E6E20): retail expands the sort there and leaves the binary
// search as a call to 0x523440, where the canonical IndexClass<int, AbstractClass*>::FetchIndex above
// has it expanded. It stays on its former form (a view of the same global) until the compile context
// that makes cl choose is understood.
struct AbstractIndexTable
{
    IndexNode* IndexTable;    // +0x0000   0xB0E840
    int        IndexCount;    // +0x0004   0xB0E844
    int        IndexSize;     // +0x0008   0xB0E848
    bool       IsSorted;      // +0x000C   0xB0E84C
    IndexNode* Archive;       // +0x0010   0xB0E850

    IndexNode* SearchForNode(const int& id);
    bool       IsPresent(const int& id);
    void**     FetchIndex(const int& id);

    // The Load bodies' (terrain 0x71CDA0, building 0x453E20) forms of the same table: the removal shifts the tail
    // down one slot, zeroes the freed slot and drops the cache; the append leaves the growth as a call.
    // FUNCTION: GAMEMD 0x41C500 (decl; reloc) -- grows the table by `amount` entries.
    bool       Grow(int amount);
    // FUNCTION: GAMEMD 0x41C590 (decl; reloc) -- the out-of-line sorted search the building Load calls.
    IndexNode* Find(const int* key);
    void       RemoveIndex(const int& id);
    void       RemoveIndexByFind(const int& id);
    void       AddIndexOutOfLine(const int& id, void* const& data);
};
GG_STATIC_ASSERT(sizeof(AbstractIndexTable) == 0x14);

// GLOBAL: GAMEMD 0xB0E840 -- the same object, declared with the held view (bound by address)
extern AbstractIndexTable AbstractIndexView;
// GLOBAL: GAMEMD 0xB78828   the slot the held fetch yields on a miss
extern void* IndexErrorValue;

// CRT qsort, and the node comparator retail hands it.
extern "C" void __cdecl FUN_007C8B48(void* base, unsigned int count, unsigned int width,
                                     int (__cdecl* compare)(const void*, const void*));
extern "C" int __cdecl FUN_0041C610(const void* a, const void* b);  // GAMEMD 0x41C610

// FUNCTION: GAMEMD 0x523440 (decl; reloc) -- __fastcall sorted search: table in ECX, count in EDX, key by pointer.
IndexNode* FUN_00523440(IndexNode* table, int count, const IndexNode* key);
// The same search with the key passed as a bare integer, as the Load bodies hold it.
IndexNode* FUN_00523440(IndexNode* table, int count, const int* key);

inline IndexNode* AbstractIndexTable::SearchForNode(const int& id)
{
    if (IndexCount == 0) {
        return 0;
    }
    if (!IsSorted) {
        FUN_007C8B48(IndexTable, IndexCount, sizeof(IndexNode), FUN_0041C610);
        Archive = 0;
        IsSorted = true;
    }
    IndexNode key;
    key.ID = id;
    return FUN_00523440(IndexTable, IndexCount, &key);
}

// The sorted-index removal, expanded in the terrain Load (the search is the inline sort and the call to 0x523440).
inline void AbstractIndexTable::RemoveIndex(const int& id)
{
    if (IndexCount) {
        if (!IsSorted) {
            FUN_007C8B48(IndexTable, IndexCount, sizeof(IndexNode), FUN_0041C610);
            Archive = 0;
            IsSorted = true;
        }
        int key = id;
        IndexNode* node = FUN_00523440(IndexTable, IndexCount, &key);
        if (node) {
            int found = node - IndexTable;
            if (found != -1) {
                for (int i = found + 1; i < IndexCount; i++) {
                    IndexTable[i - 1].ID = IndexTable[i].ID;
                    IndexTable[i - 1].Data = IndexTable[i].Data;
                }
                IndexCount--;
                IndexTable[IndexCount].ID = 0;
                IndexTable[IndexCount].Data = 0;
                Archive = 0;
            }
        }
    }
}

// The same removal with the search left as a call to 0x41C590 (the building Load).
inline void AbstractIndexTable::RemoveIndexByFind(const int& id)
{
    IndexNode* node = Find(&id);
    if (node) {
        int found = node - IndexTable;
        if (found != -1) {
            for (int i = found + 1; i < IndexCount; i++) {
                IndexTable[i - 1] = IndexTable[i];
            }
            IndexCount--;
            IndexTable[IndexCount].ID = 0;
            IndexTable[IndexCount].Data = 0;
            Archive = 0;
        }
    }
}

// The append, expanded in the Load bodies with the growth left as a call.
inline void AbstractIndexTable::AddIndexOutOfLine(const int& id, void* const& data)
{
    if (IndexCount + 1 > IndexSize) {
        if (!Grow(IndexSize == 0 ? 10 : IndexSize))
            return;
    }
    IndexTable[IndexCount].ID = id;
    IndexTable[IndexCount].Data = data;
    IndexCount++;
    IsSorted = false;
}

inline bool AbstractIndexTable::IsPresent(const int& id)
{
    if (IndexCount == 0) {
        return false;
    }
    if (Archive != 0 && Archive->ID == id) {
        return true;
    }
    IndexNode* node = SearchForNode(id);
    if (node != 0) {
        Archive = node;
        return true;
    }
    return false;
}

inline void** AbstractIndexTable::FetchIndex(const int& id)
{
    if (IsPresent(id)) {
        return &Archive->Data;
    }
    return &IndexErrorValue;
}


#endif  // GG_MATCH_CORE_ABSTRACT_INDEX_CAST_SWEEP_H
