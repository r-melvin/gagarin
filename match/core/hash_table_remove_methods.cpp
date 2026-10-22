// Provenance: own-binary-via-Ghidra
// Hash table Remove(key, value&) instantiations (__thiscall, `ret 8`, bool
// in AL); table layout in hash_table_view.h. Remove takes
// the load ratio (count - 1) / buckets before unlinking, frees the node
// (operator delete 0x7C8B3D) and, when the ratio is at or below the
// threshold, halves the table inline (the shrink body that main matches
// out of line at 0x625780 / 0x6258E0).
// C4661: the members this TU does not define stay declarations on purpose.
#pragma warning(disable : 4661)
#include "hash_table_view.h"

template<class KEY, class VALUE>
bool HashTable_006249A0<KEY, VALUE>::Remove(const KEY& key, VALUE& value)
{
    if (this->Count == 0) return false;

    float load = (float)(this->Count - 1);
    load /= this->BucketCount;
    int hash = this->Hash(&key);
    unsigned idx = ((1 << this->BitWidth) - 1) & hash;
    Node* node = this->Buckets[idx];
    if (node == NULL) return false;

    if (node->Key == key) {
        value = node->Value;
        Node* next = this->Buckets[idx]->Next;
        delete this->Buckets[idx];
        this->Buckets[idx] = next;
        this->Count--;
        if (load <= this->ShrinkRatio) {
            Shrink();
        }
        return true;
    }

    bool found = false;
    for (Node* cur = node->Next; cur != NULL; cur = cur->Next) {
        if (cur->Key == key) {
            value = cur->Value;
            node->Next = cur->Next;
            this->Count--;
            delete cur;
            found = true;
            break;
        }
        node = cur;
    }
    if (load <= this->ShrinkRatio) {
        Shrink();
    }
    return found;
}

// The two-word key of the 0x625090 table; equality tests the second word
// first (retail compares [key+4] before [key+0]).
struct CellKey_00625090
{
    int A;   // +0x00
    int B;   // +0x04

    bool operator==(const CellKey_00625090& other) const { return other.B == B && other.A == A; }
};
GG_STATIC_ASSERT(sizeof(CellKey_00625090) == 8);

// FUNCTION: GAMEMD 0x6249A0
template struct HashTable_006249A0<int, int>;
// FUNCTION: GAMEMD 0x625090
template struct HashTable_006249A0<CellKey_00625090, char>;

typedef HashTable_006249A0<int, int> HashTableRep_006249A0;
GG_STATIC_ASSERT(offsetof(HashTableRep_006249A0, Buckets)     == 0x00);
GG_STATIC_ASSERT(offsetof(HashTableRep_006249A0, Count)       == 0x04);
GG_STATIC_ASSERT(offsetof(HashTableRep_006249A0, BucketCount) == 0x08);
GG_STATIC_ASSERT(offsetof(HashTableRep_006249A0, BitWidth)    == 0x0C);
GG_STATIC_ASSERT(offsetof(HashTableRep_006249A0, IsFixed)     == 0x14);
GG_STATIC_ASSERT(offsetof(HashTableRep_006249A0, Hash)        == 0x18);
GG_STATIC_ASSERT(offsetof(HashTableRep_006249A0, ShrinkRatio) == 0x20);
GG_STATIC_ASSERT(offsetof(HashTableRep_006249A0, MinBuckets)  == 0x30);
