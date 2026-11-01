// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout, bodies and the out-of-line copies were read numerically off the user's retail gamemd.exe
//   v1.001 with the local Ghidra CLI. The out-of-line copies of the members are the strongest evidence of
//   the source form: 0x41C500 (growth), 0x41C590 (sorted node search, one per instantiation), 0x41C610
//   (comparator) and 0x52B0A0 / 0x52B170 / 0x52B210 / 0x52B2B0 (the INI instantiation's AddIndex /
//   IsPresent / FetchIndex / RemoveIndex). Member names follow Westwood's IndexClass<T, U> template (via
//   YRpp), checked against the offsets and behaviour below.
//
// IndexClass<T, U> is the lazily sorted {ID, Data} index with a one-entry cache in front of it (Archive).
// Layout, confirmed numerically on every instantiation:
//   +0x00 IndexTable   the node array, 8-byte stride when T and U are both four bytes wide
//   +0x04 IndexCount   entries in use
//   +0x08 IndexSize    entries allocated
//   +0x0C IsSorted     one byte
//   +0x10 Archive      the node of the last successful lookup
//
// Instantiations in the retail image (the dummy of each FetchIndex is a function-local `static U _dummy`; the
// four adjacent words 0xB78820 / 0xB78828 / 0xB7882C / 0xB78830 are the dummies of four instantiations):
//   IndexClass<int, AbstractClass*>        the global at 0xB0E840; every ObjectClass registers itself in its
//                                          constructor and removes/re-adds itself in Load. Out-of-line copies:
//                                          0x41C500 growth, 0x41C590 SearchForNode, 0x41C610 Comparator,
//                                          0x523440 binary search. Dummy 0xB78828.
//   IndexClass<int, INIClass::INIEntry*>   INIClass entry lookups (0x52B080..0x52B2B0, 0x52B6A0), dummy 0xB78830;
//                                          explicit specialisation in index_class.h (its bodies are phrased as
//                                          retail's copies are, with const members and no empty-table test in
//                                          the search).
//   IndexClass<int, INIClass::INISection*> INIClass section lookups (0x52B390, 0x52B430, 0x52B720), dummy 0xB7882C.
//   IndexClass<int, void*>                 the four ObjectTypeClass voxel caches (Clear at 0x5F9B60); the value
//                                          type is a four-byte placeholder, only the node width reaches the code.
// Other index instantiations still carry per-TU views (IndexClassC in Init.cpp, IndexClassRaw, the ccini
// IndexNode_* views, StaticIndex_008B3CC0, BuildingBIndexView) and are to be folded into this template.
//
// The constructors of the global expand AddIndex with the growth inline (0x413D20, 0x43B740, 0x517A50,
// 0x7353C0, 0x71BB90, 0x71BDF0, 0x74C5B0, 0x74EA70); the Load bodies (0x41B430, 0x453E20, 0x521960, 0x71CDA0,
// 0x744470) call the out-of-line growth at 0x41C500.
#ifndef GG_MATCH_LAYOUT_INDEX_H
#define GG_MATCH_LAYOUT_INDEX_H

#include <stddef.h>
#include <stdlib.h>
#include "../_rt/gg_static_assert.h"

template<class T, class U>
class IndexClass
{
public:
    struct NodeElement
    {
        T ID;     // +0x00
        U Data;   // +0x04

        // The empty constructor is what makes `new NodeElement[n]` compile to the bare allocation with the
        // vector-constructor counter left as a dead decrement, as at 0x41C52C.
        NodeElement() {}
    };

    IndexClass() : IndexTable(0), IndexCount(0), IndexSize(0), IsSorted(false), Archive(0) {}
    ~IndexClass() { Clear(); }

    void Clear();
    bool AddIndex(const T& id, const U& data);
    bool RemoveIndex(const T& id);
    bool IsPresent(const T& id);
    const U& FetchIndex(const T& id);

    bool IncreaseTableSize(int amount);
    NodeElement* SearchForNode(const T& id);

    static int __cdecl Comparator(const void* ptr1, const void* ptr2);

    NodeElement* IndexTable;   // +0x00
    int          IndexCount;   // +0x04
    int          IndexSize;    // +0x08
    bool         IsSorted;     // +0x0C
    NodeElement* Archive;      // +0x10

    // Out-of-line copies retail has at their own addresses (defined where they are matched).
    // FUNCTION: GAMEMD 0x5F9B60 -- Clear for IndexClass<int, void*> (ObjectTypeClass::Load calls it).
    void FUN_005F9B60();
    // FUNCTION: GAMEMD 0x41C500 -- IncreaseTableSize.
    bool FUN_0041C500(int amount);
    // FUNCTION: GAMEMD 0x523440 -- the __fastcall binary search over a sorted node array.
    static NodeElement* FUN_00523440(NodeElement* table, int count, const NodeElement* key);
};

template<class T, class U>
void IndexClass<T, U>::Clear()
{
    delete[] IndexTable;
    IndexTable = 0;
    IndexCount = 0;
    IndexSize = 0;
    IsSorted = false;
    Archive = 0;
}

template<class T, class U>
bool IndexClass<T, U>::IncreaseTableSize(int amount)
{
    if (amount >= 0) {
        NodeElement* table = new NodeElement[IndexSize + amount];
        if (table != 0) {
            for (int index = 0; index < IndexCount; index++) {
                table[index] = IndexTable[index];
            }
            delete[] IndexTable;
            IndexTable = table;
            IndexSize += amount;
            Archive = 0;
            return true;
        }
    }
    return false;
}

template<class T, class U>
bool IndexClass<T, U>::AddIndex(const T& id, const U& data)
{
    if (IndexCount + 1 > IndexSize) {
        if (!IncreaseTableSize(IndexSize == 0 ? 10 : IndexSize)) {
            return false;
        }
    }
    IndexTable[IndexCount].ID = id;
    IndexTable[IndexCount].Data = data;
    IndexCount++;
    IsSorted = false;
    return true;
}

template<class T, class U>
typename IndexClass<T, U>::NodeElement* IndexClass<T, U>::SearchForNode(const T& id)
{
    if (IndexCount == 0) {
        return 0;
    }
    if (!IsSorted) {
        qsort(IndexTable, IndexCount, sizeof(NodeElement), Comparator);
        Archive = 0;
        IsSorted = true;
    }
    NodeElement node;
    node.ID = id;
    NodeElement* base = IndexTable;
    for (int count = IndexCount; count > 0; ) {
        int half = count / 2;
        NodeElement* mid = base + half;
        if (mid->ID > node.ID) {
            count = half;
        } else {
            if (mid->ID == node.ID) {
                return mid;
            }
            base = mid + 1;
            count = count - 1 - half;
        }
    }
    return 0;
}

template<class T, class U>
bool IndexClass<T, U>::RemoveIndex(const T& id)
{
    NodeElement* node = SearchForNode(id);
    if (node != 0) {
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
            return true;
        }
    }
    return false;
}

template<class T, class U>
bool IndexClass<T, U>::IsPresent(const T& id)
{
    if (IndexCount == 0) {
        return false;
    }
    if (Archive != 0 && Archive->ID == id) {
        return true;
    }
    NodeElement* node = SearchForNode(id);
    if (node != 0) {
        Archive = node;
        return true;
    }
    return false;
}

template<class T, class U>
const U& IndexClass<T, U>::FetchIndex(const T& id)
{
    if (IsPresent(id)) {
        return Archive->Data;
    }
    static U _dummy;
    return _dummy;
}

#endif  // GG_MATCH_LAYOUT_INDEX_H
