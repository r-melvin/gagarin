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
// The whole lookup is inlined into every member: the empty-table test, the
// one-entry archive cache, the lazy qsort that sorts the table on first use,
// and a hand-rolled binary search over 8-byte nodes. cl threads the four
// "not found" exits of that chain into a single error return, which is why
// retail materialises `&IndexErrorValue` with `MOV EAX,imm32` and then shares
// one `MOV EAX,[EAX]` with the found path: the inlined fetch yields an address
// in both arms, so only one load is needed.
#ifndef GG_MATCH_CORE_ABSTRACT_INDEX_CAST_SWEEP_H
#define GG_MATCH_CORE_ABSTRACT_INDEX_CAST_SWEEP_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// MSVC6's RTTI helper, declared by hand rather than reached through a real
// `dynamic_cast` so the five pushed arguments are spelled explicitly and no
// /GR-dependent type descriptor has to be emitted for a reconstructed class.
extern "C" void* __cdecl FUN_007CAAE4(void* object, long vfDelta,
                                      void* srcType, void* dstType,
                                      int isReference);   // GAMEMD 0x7CAAE4

// CRT qsort, and the node comparator retail hands it.
extern "C" void __cdecl FUN_007C8B48(void* base, unsigned int count,
                                     unsigned int width,
                                     int (__cdecl* compare)(const void*,
                                                            const void*));
extern "C" int __cdecl FUN_0041C610(const void* a, const void* b);  // GAMEMD 0x41C610

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

// One 8-byte index node: the integer key at +0, the stored pointer at +4.
struct IndexNode
{
    int   ID;      // +0x0000
    void* Data;    // +0x0004
};
GG_STATIC_ASSERT(offsetof(IndexNode, ID) == 0x0);
GG_STATIC_ASSERT(offsetof(IndexNode, Data) == 0x4);
GG_STATIC_ASSERT(sizeof(IndexNode) == 0x8);

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

// The index itself. Four of the five members are pinned by the four absolute
// displacements the family touches - 0xB0E840, 0xB0E844, 0xB0E84C and 0xB0E850
// - which places the never-read size field at 0xB0E848.
struct AbstractIndexTable
{
    IndexNode* IndexTable;    // +0x0000   0xB0E840
    int        IndexCount;    // +0x0004   0xB0E844
    int        IndexSize;     // +0x0008   0xB0E848  (never read by this family)
    bool       IsSorted;      // +0x000C   0xB0E84C
    IndexNode* Archive;       // +0x0010   0xB0E850

    // The file-scope object's constructor zeroes the five fields; its
    // destructor frees the table and zeroes them again.
    AbstractIndexTable() : IndexTable(0), IndexCount(0), IndexSize(0), IsSorted(false), Archive(0) {}
    ~AbstractIndexTable()
    {
        delete IndexTable;
        IndexTable = 0;
        IndexCount = 0;
        IndexSize = 0;
        IsSorted = false;
        Archive = 0;
    }

    IndexNode* SearchSorted(const int* key);
    void**     Fetch(const int& id);
    // The second spelling of the lookup (0x6E6E20): presence test first, the
    // binary search out of line in 0x523440.
    IndexNode* SearchForNode(const int& id);
    bool       IsPresent(const int& id);
    void**     FetchIndex(const int& id);
};
GG_STATIC_ASSERT(offsetof(AbstractIndexTable, IndexTable) == 0x0);
GG_STATIC_ASSERT(offsetof(AbstractIndexTable, IndexCount) == 0x4);
GG_STATIC_ASSERT(offsetof(AbstractIndexTable, IndexSize) == 0x8);
GG_STATIC_ASSERT(offsetof(AbstractIndexTable, IsSorted) == 0xC);
GG_STATIC_ASSERT(offsetof(AbstractIndexTable, Archive) == 0x10);
GG_STATIC_ASSERT(sizeof(AbstractIndexTable) == 0x14);

// GLOBAL: GAMEMD 0xB0E840 -- defined in abstract_index_cast_sweep.cpp
extern AbstractIndexTable AbstractIndex;
// GLOBAL: GAMEMD 0xB78828   the slot the fetch yields on a miss
extern void* IndexErrorValue;

// The lookup. Three separate things have to be true for this to reproduce
// retail's 71 instructions, and each was worth tens of points on its own:
//
//  1. The search loop lives in its own inline function with its own miss
//     `return 0`. Written as one flat body, cl tail-merges the empty-table exit
//     with the loop's miss exit, and because the merged block pops all three
//     callee-saved registers, all three pushes move up into the prologue and
//     the whole register colouring shifts (34.7%).
//  2. The key is read before the table pointer. Retail's `MOV EBX,[ESI]` comes
//     ahead of `MOV EDI,[IndexTable]`; declaring `base` first swaps them (97.2%).
//  3. The labels run error, store, found in that order, so the loop's failure
//     exit falls into the error block and the archive store sits in the cold
//     tail past the return. Spelled `if (node == 0) goto error; ... goto found;`
//     with `found` last, cl lays the store inline and the tail diverges (63.0%).
inline IndexNode* AbstractIndexTable::SearchSorted(const int* key)
{
    int k = *key;
    IndexNode* base = IndexTable;
    int count;

    for (count = IndexCount; count > 0; ) {
        int half = count / 2;
        IndexNode* mid = base + half;

        if (mid->ID > k) {
            count = half;
        } else {
            if (mid->ID == k) {
                return mid;
            }

            base = mid + 1;
            count = count - 1 - half;
        }
    }

    return 0;
}

inline void** AbstractIndexTable::Fetch(const int& id)
{
    IndexNode* node;

    if (IndexCount == 0) {
        goto error;
    }

    node = Archive;

    if (node != 0 && node->ID == id) {
        goto found;
    }

    if (!IsSorted) {
        FUN_007C8B48(IndexTable, IndexCount, sizeof(IndexNode), FUN_0041C610);
        Archive = 0;
        IsSorted = true;
    }

    node = SearchSorted(&id);

    if (node != 0) {
        goto store;
    }

error:
    return &IndexErrorValue;

store:
    Archive = node;

found:
    return &node->Data;
}

// FUNCTION: GAMEMD 0x523440 (decl; reloc) -- __fastcall sorted search: table in ECX, count in EDX, key by pointer.
IndexNode* FUN_00523440(IndexNode* table, int count, const IndexNode* key);

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
