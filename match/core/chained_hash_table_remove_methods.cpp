// Provenance: own-binary-via-Ghidra
//   Bytes read off the user's retail gamemd.exe v1.001 via the local Ghidra
//   CLI at 0x7ADCD0: __thiscall, `RET 8` (key reference, value out-pointer).
//   A chained hash table keyed by a 4-byte handle (equality 0x7B4780, release
//   0x7B46F0) holding 0x6C-byte values; nodes are {key, value, next@+0x70}.
//   Removing may halve the bucket array (shift-mask hashing through the hash
//   callback at +0x18) when the load drops to the shrink ratio at +0x20.
#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

// The 4-byte key handle.
struct HashKeyHandle
{
    // FUNCTION: GAMEMD 0x7B4780 (decl; reloc) -- equality.
    bool operator==(const HashKeyHandle& other) const;
    // FUNCTION: GAMEMD 0x7B46F0 (decl; reloc) -- free the text.
    void Release();
    ~HashKeyHandle()
    {
        Release();
    }

    void* unknown_00;   // +0x00
};

struct HashValue6C
{
    int unknown_00[0x1B];
};

template<class Key, class Value>
struct ChainedHashTable
{
    struct Node
    {
        Key   NodeKey;     // +0x00
        Value NodeValue;   // +0x04
        Node* Next;        // +0x04 + sizeof(Value)
    };
    typedef unsigned (__fastcall *HashFunc)(const Key& key);

    Node**   Buckets;        // +0x00
    unsigned Count;          // +0x04
    unsigned BucketCount;    // +0x08
    int      Bits;           // +0x0C
    int      unknown_10;     // +0x10
    bool     FixedSize;      // +0x14
    HashFunc Hash;           // +0x18
    int      unknown_1C;     // +0x1C
    double   ShrinkLoad;     // +0x20
    int      unknown_28[2];  // +0x28
    unsigned MinBuckets;     // +0x30

    void Shrink()
    {
        Node** old = Buckets;
        int oldCount = BucketCount;
        BucketCount = (unsigned)oldCount >> 1;
        Bits--;
        Buckets = (Node**)operator new(BucketCount * sizeof(Node*));
        memset(Buckets, 0, BucketCount * sizeof(Node*));
        Node** slot = old;
        for (int i = oldCount; i > 0; i--) {
            for (Node* node = *slot; node; ) {
                unsigned index = ((1 << Bits) - 1) & Hash(node->NodeKey);
                Node* head = Buckets[index];
                Buckets[index] = node;
                Node* next = node->Next;
                node->Next = head;
                node = next;
            }
            slot++;
        }
        operator delete(old);
    }
    bool Remove(const Key& key, Value* value);
};

template<class Key, class Value>
bool ChainedHashTable<Key, Value>::Remove(const Key& key, Value* value)
{
    if (Count == 0) {
        return false;
    }
    float load = (float)(Count - 1) / BucketCount;
    unsigned index = ((1 << Bits) - 1) & Hash(key);
    Node* prev = Buckets[index];
    if (!prev) {
        return false;
    }

    if (prev->NodeKey == key) {
        *value = prev->NodeValue;
        Node* node = Buckets[index];
        Node* next = node->Next;
        delete node;
        Buckets[index] = next;
        Count--;
        if (load <= ShrinkLoad && BucketCount > MinBuckets && FixedSize != true) {
            Shrink();
        }
        return true;
    }

    bool found = false;
    for (Node* node = prev->Next; node; node = node->Next) {
        if (node->NodeKey == key) {
            *value = node->NodeValue;
            prev->Next = node->Next;
            Count--;
            delete node;
            found = true;
            break;
        }
        prev = node;
    }
    if (load <= ShrinkLoad && BucketCount > MinBuckets && FixedSize != true) {
        Shrink();
    }
    return found;
}

// FUNCTION: GAMEMD 0x7ADCD0
template struct ChainedHashTable<HashKeyHandle, HashValue6C>;
