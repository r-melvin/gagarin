// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference | YRpp-cross-check |
//             private-ref-cross-check
//   Every body below was written against the retail disassembly of the user's
//   gamemd.exe v1.001 read through the local Ghidra CLI.
//
// IndexClass — the lazily sorted {ID, Data} index. Bodies ascending by address.

#include "index_class.h"

// Grows the table to hold `amount` more entries, copying the live entries over
// field by field and dropping the cached node because the array moved. Retail
// has this expanded into AddIndex, with its own early return for a negative
// amount surviving as the one conditional on the doubling path.
__forceinline bool IndexClass::IncreaseTableSize(int amount)
{
    if (amount < 0) return false;

    int newsize = IndexSize + amount;
    NodeElement* table =
        (NodeElement*)FUN_007C8E17(newsize * sizeof(NodeElement));
    if (table != 0) {

        for (int index = 0; index < IndexCount; index++) {
            table[index].ID = IndexTable[index].ID;
            table[index].Data = IndexTable[index].Data;
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

// PARTIAL 3.7% (best of four spellings). The instruction multiset is close and
// the growth arithmetic, the doubling choice and the copy loop all appear, but
// retail reserves one dword of frame (`PUSH ECX` at entry) that our build does
// not, and it keeps the new element count as a live local it decrements and
// stores without ever reading back. Every instruction after that dead store
// lands one slot early, which is what depresses the score. Variants measured:
// the allocation size written inline versus bound to a named `newsize` local
// (3.7% either way at the head, the named form matching retail's paired LEAs);
// the per-entry copy written field by field (3.7%) versus as a whole-struct
// assignment (0.0%, cl then emits its own two-dword copy with the other
// addressing). Next step is the frame-size sweep from the thirteenth batch:
// recover the real local count from the frame-relative addresses before
// touching the body again.
//
// Appends an entry, growing the table first when it is full. Growth doubles
// the table, or takes ten entries when there is none yet; the old contents are
// copied field by field, which is what retail's paired dword stores are, and
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
    return GG_INDEX_DEFAULT_VALUE;
}

// PARTIAL 4.4% (best of three spellings). The multiset is identical at 90
// instructions against 90, so the body is right; the whole stream sits one
// instruction out because retail opens with `SUB ESP,8` for two spilled locals
// and our build spills one. The residual multiset is retail-only SUB/ADD/ADD/
// XOR/INC against our two LEAs, which is the same frame difference seen from
// the other end. Variants measured: the three failure paths merged into one
// shared tail (4.4%) versus each returning where it stands (0.0%); the search
// comparison written key-against-node, which is retail's operand order, versus
// node-against-key (0.0%); the shift loop and the last-slot zeroing written
// field by field (4.4%) versus as struct assignments through a named zero
// temporary (0.0%). The frame-size sweep is the next step here too.
//
// Removes an entry. The table is sorted and searched as in IsPresent, then the
// tail is shifted down one slot, the count drops and the freed last slot is
// zeroed. The cached node is dropped because everything past the hole moved.
// FUNCTION: GAMEMD 0x52B2B0
bool IndexClass::RemoveIndex(const int& id)
{
    NodeElement* nodeptr = 0;

    // Every failure path leaves through one shared tail, which is why the
    // empty-index test jumps forward past the whole body instead of returning
    // where it stands.
    if (IndexCount != 0) {

        // RemoveIndex carries its own copy of the search rather than sharing
        // the one above: retail spells its comparison the other way round,
        // testing the key against the node instead of the node against the
        // key, and that shows up as the whole loop's operand order.
        if (!IsSorted) {
            FUN_007C8B48(IndexTable, IndexCount, sizeof(NodeElement),
                         &IndexClassB::Comparator);
            Archive = 0;
            IsSorted = true;
        }

        int num = IndexCount;
        int key = id;
        NodeElement* base = IndexTable;

        while (num > 0) {
            int half = num / 2;
            NodeElement* mid = &base[half];

            if (key < mid->ID) {
                num = half;
            } else {
                if (mid->ID == key) {
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
                    IndexTable[index - 1].ID = IndexTable[index].ID;
                    IndexTable[index - 1].Data = IndexTable[index].Data;
                }

                IndexCount--;
                IndexTable[IndexCount].ID = 0;
                IndexTable[IndexCount].Data = 0;
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
    return GG_INDEX_DEFAULT_VALUE;
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
