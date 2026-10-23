// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Hash table view shared by hash_table_remove_methods.cpp and
// hash_table_clear_methods.cpp. Table layout as in
// core/hash_table_rehash_sweep.h: buckets +0x00, entry count +0x04, bucket
// count +0x08, bit width +0x0C, fixed flag +0x14, __fastcall hash function
// +0x18 (called with the key address in ECX), shrink threshold (double)
// +0x20, bucket floor +0x30. The inline Shrink is the halving body main
// matches out of line (e.g. 0x625780 / 0x6258E0).
#ifndef GG_MATCH_CORE_HASH_TABLE_VIEW_H
#define GG_MATCH_CORE_HASH_TABLE_VIEW_H

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

template<class KEY, class VALUE>
struct HashNode_006249A0
{
    KEY Key;
    VALUE Value;
    HashNode_006249A0* Next;
};

template<class KEY, class VALUE>
struct HashTable_006249A0
{
    typedef HashNode_006249A0<KEY, VALUE> Node;
    typedef int (* HashOf)(const KEY* key);

    Node**   Buckets;        // +0x0000
    unsigned Count;          // +0x0004
    unsigned BucketCount;    // +0x0008
    int      BitWidth;       // +0x000C
    int      unknown_10;     // +0x0010
    char     IsFixed;        // +0x0014
    char     unknown_15[3];  // +0x0015
    HashOf   Hash;           // +0x0018
    int      unknown_1C;     // +0x001C
    double   ShrinkRatio;    // +0x0020
    double   unknown_28;     // +0x0028
    unsigned MinBuckets;     // +0x0030

    inline void Shrink()
    {
        unsigned count = this->BucketCount;

        if (count <= this->MinBuckets) return;
        if (this->IsFixed == 1) return;

        {
            Node** old = this->Buckets;
            Node** fresh;

            this->BucketCount = count >> 1;
            this->BitWidth = this->BitWidth - 1;
            fresh = new Node*[count >> 1];
            this->Buckets = fresh;
            memset(fresh, 0, this->BucketCount * 4);

            if ((int)count > 0) {
                Node** p = old;
                unsigned n = count;

                do {
                    Node* node = *p;

                    while (node != 0) {
                        int hash = this->Hash(&node->Key);
                        unsigned idx = ((1 << this->BitWidth) - 1) & hash;
                        Node* head = this->Buckets[idx];
                        this->Buckets[idx] = node;
                        Node* next = node->Next;
                        node->Next = head;
                        node = next;
                    }

                    p++;
                    n--;
                } while (n != 0);
            }

            delete[] old;
        }
    }

    inline void Grow()
    {
        unsigned count = this->BucketCount;
        Node** old = this->Buckets;
        Node** fresh;

        this->BucketCount = count * 2;
        this->BitWidth = this->BitWidth + 1;
        fresh = new Node*[this->BucketCount];
        this->Buckets = fresh;
        memset(fresh, 0, this->BucketCount * 4);

        if ((int)count > 0) {
            Node** p = old;
            unsigned n = count;

            do {
                Node* node = *p;

                while (node != 0) {
                    int hash = this->Hash(&node->Key);
                    unsigned idx = ((1 << this->BitWidth) - 1) & hash;
                    Node* head = this->Buckets[idx];
                    this->Buckets[idx] = node;
                    Node* next = node->Next;
                    node->Next = head;
                    node = next;
                }

                p++;
                n--;
            } while (n != 0);
        }

        delete[] old;
    }

    // Defined per using TU; an explicit instantiation emits only the members
    // whose definitions it can see.
    HashTable_006249A0();
    bool Find(const KEY& key, VALUE*& pValue);
    bool Remove(const KEY& key, VALUE& value);
    bool PopFirst(KEY& key, VALUE& value);
    void Clear();
    bool Insert(const KEY& key, const VALUE& value);
    ~HashTable_006249A0();
};

#endif // GG_MATCH_CORE_HASH_TABLE_VIEW_H
