// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference | YRpp-cross-check |
//             private-ref-cross-check
//   Every body below was written against the retail disassembly of the user's
//   gamemd.exe v1.001 read through the local Ghidra CLI.
//
// IndexClass — the lazily sorted {ID, Data} index. Bodies ascending by address.

#include "index_class.h"

// Grows the table to hold `amount` more entries, copying the live entries over
// node by node and dropping the cached node because the array moved. The new
// table is an array-new of nodes with a no-throw empty constructor, which is
// what leaves retail's dead "count minus one" local in the frame. Retail
// has this expanded into AddIndex, with its own early return for a negative
// amount surviving as the one conditional on the doubling path.
__forceinline bool IndexClass::IncreaseTableSize(int amount)
{
    if (amount < 0) return false;

    int newsize = IndexSize + amount;
    NodeElement* table = new NodeElement[newsize];
    if (table != 0) {

        for (int index = 0; index < IndexCount; index++) {
            table[index] = IndexTable[index];
        }

        FUN_007C8B3D(IndexTable);
        IndexTable = table;
        IndexSize += amount;
        Archive = 0;

        return true;
    }

    return false;
}

// Sorts the table if it has gone stale, then binary-searches it. The loop
// walks a shrinking (base, count) window rather than a pair of indices, which
// is why retail advances a pointer and folds the count adjustment into one
// add.
__forceinline IndexClass::NodeElement* IndexClass::SearchForNode(const int& id) const
{
    if (!IsSorted) {
        FUN_007C8B48(IndexTable, IndexCount, sizeof(NodeElement), &Comparator);
        ((IndexClass*)this)->Archive = 0;
        ((IndexClass*)this)->IsSorted = true;
    }

    int num = IndexCount;
    int key = id;
    NodeElement* base = IndexTable;

    while (num > 0) {
        int half = num / 2;
        NodeElement* mid = &base[half];

        if (mid->ID > key) {
            num = half;
        } else {
            if (mid->ID == key) {
                return mid;
            }
            base = mid + 1;
            num += -1 - half;
        }
    }

    return 0;
}

// The lookup both IsPresent and FetchIndex are built from.
__forceinline bool IndexClass::IsPresentImpl(const int& id) const
{
    if (IndexCount == 0) {
        return false;
    }

    if (Archive != 0 && Archive->ID == id) {
        return true;
    }

    NodeElement* nodeptr = SearchForNode(id);

    if (nodeptr != 0) {
        ((IndexClass*)this)->Archive = nodeptr;
        return true;
    }

    return false;
}

__forceinline IndexClassB::NodeElement* IndexClassB::SearchForNode(const int& id) const
{
    if (!IsSorted) {
        FUN_007C8B48(IndexTable, IndexCount, sizeof(NodeElement), &Comparator);
        ((IndexClassB*)this)->Archive = 0;
        ((IndexClassB*)this)->IsSorted = true;
    }

    int num = IndexCount;
    int key = id;
    NodeElement* base = IndexTable;

    while (num > 0) {
        int half = num / 2;
        NodeElement* mid = &base[half];

        if (mid->ID > key) {
            num = half;
        } else {
            if (mid->ID == key) {
                return mid;
            }
            base = mid + 1;
            num += -1 - half;
        }
    }

    return 0;
}

__forceinline bool IndexClassB::IsPresentImpl(const int& id) const
{
    if (IndexCount == 0) {
        return false;
    }

    if (Archive != 0 && Archive->ID == id) {
        return true;
    }

    NodeElement* nodeptr = SearchForNode(id);

    if (nodeptr != 0) {
        ((IndexClassB*)this)->Archive = nodeptr;
        return true;
    }

    return false;
}

// An empty index owns nothing and is trivially "sorted": every field is zero,
// which retail writes out of one zeroed register.
// FUNCTION: GAMEMD 0x52B080
IndexClass::IndexClass()
{
    IndexTable = 0;
    IndexCount = 0;
    IndexSize = 0;
    IsSorted = false;
    Archive = 0;
}

// Appends an entry, growing the table first when it is full. Growth doubles
// the table, or takes ten entries when there is none yet; the old contents are
// copied node by node, which is what retail's paired dword stores are, and
// the cached node is dropped because the table moved. The append itself leaves
// the index unsorted.
// FUNCTION: GAMEMD 0x52B0A0
bool IndexClass::AddIndex(const int& id, void* const& data)
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

// Is the ID in the index? The cached node answers first; otherwise the table is
// sorted if it is not already and searched. A hit re-arms the cache.
// FUNCTION: GAMEMD 0x52B170
bool IndexClass::IsPresent(const int& id) const
{
    return IsPresentImpl(id);
}

// Returns the value stored against the ID, or the shared default when the ID is
// absent. The lookup is IsPresent expanded, so the cached node it leaves behind
// is what the value is read from.
// FUNCTION: GAMEMD 0x52B210
void* const& IndexClass::FetchIndex(const int& id) const
{
    if (IsPresentImpl(id)) {
        return Archive->Data;
    }
    return reinterpret_cast<void* const&>(DAT_00B78830);
}

// The search key lives in a local node (retail's 8-byte frame is that node: the
// key is its ID, its Data is never written), the shift is a whole-node copy, and
// the freed last slot is cleared by assigning a zeroed node.
//
// Removes an entry. The table is sorted and searched as in IsPresent, then the
// tail is shifted down one slot, the count drops and the freed last slot is
// zeroed. The cached node is dropped because everything past the hole moved.
// FUNCTION: GAMEMD 0x52B2B0
bool IndexClass::RemoveIndex(const int& id)
{
    NodeElement* nodeptr = 0;

    if (IndexCount != 0) {
        if (!IsSorted) {
            FUN_007C8B48(IndexTable, IndexCount, sizeof(NodeElement),
                         &IndexClassB::Comparator);
            Archive = 0;
            IsSorted = true;
        }

        int num = IndexCount;
        NodeElement elem;
        elem.ID = id;
        NodeElement* base = IndexTable;

        while (num > 0) {
            int half = num / 2;
            NodeElement* mid = &base[half];

            if (elem.ID < mid->ID) {
                num = half;
            } else {
                if (mid->ID == elem.ID) {
                    nodeptr = mid;
                    break;
                }
                base = mid + 1;
                num += -1 - half;
            }
        }

        if (nodeptr != 0) {
            int found_index = nodeptr - IndexTable;

            if (found_index != -1) {

                for (int index = found_index + 1; index < IndexCount; index++) {
                    IndexTable[index - 1] = IndexTable[index];
                }

                IndexCount--;
                NodeElement zero;
                zero.ID = 0;
                zero.Data = 0;
                IndexTable[IndexCount] = zero;
                Archive = 0;

                return true;
            }
        }
    }

    return false;
}

// The second instantiation's lookup: the same body, its own comparator.
// FUNCTION: GAMEMD 0x52B390
bool IndexClassB::IsPresent(const int& id) const
{
    return IsPresentImpl(id);
}

// The second instantiation's value fetch.
// FUNCTION: GAMEMD 0x52B430
void* const& IndexClassB::FetchIndex(const int& id) const
{
    if (IsPresentImpl(id)) {
        return Archive->Data;
    }
    return reinterpret_cast<void* const&>(DAT_00B7882C);
}

// The qsort comparator: order by ID. Equal IDs short-circuit to zero, and the
// remaining case is turned into -1 or 1 by a SETGE-and-fold idiom rather than
// by two branches.
// FUNCTION: GAMEMD 0x52B6A0
int __cdecl IndexClass::Comparator(const void* ptr1, const void* ptr2)
{
    if (*(const int*)ptr1 == *(const int*)ptr2) {
        return 0;
    }
    if (*(const int*)ptr1 < *(const int*)ptr2) {
        return -1;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x52B720
int __cdecl IndexClassB::Comparator(const void* ptr1, const void* ptr2)
{
    if (*(const int*)ptr1 == *(const int*)ptr2) {
        return 0;
    }
    if (*(const int*)ptr1 < *(const int*)ptr2) {
        return -1;
    }
    return 1;
}
