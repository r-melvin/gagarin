// Provenance: own-binary-via-Ghidra
// Destructor of a hash table instantiation (layout in hash_table_view.h)
// whose 0x30C-byte node holds a one-word key object (+0x000; constructor
// 0x7B4620, destructor 0x7B46F0, assignment 0x7B4940), a 0x304-byte value
// whose first word owns a polymorphic object (+0x004; released through vtable
// slot 0 with argument 1) and the chain link (+0x308). The body drains the
// table entry by entry through an inline PopFirst (which halves the
// table inline), then frees what is left, shrinks to the floor through the
// out-of-line Shrink (0x6BAEF0) and frees the bucket array. 0x600550 reaches
// it with a tail jump. No EH frame in retail although the key local has a
// destructor.
// C4661: the members this TU does not define stay declarations on purpose.
#pragma warning(disable : 4661)
#include "hash_table_view.h"

class Key_006B9530
{
public:
    void* Data;   // +0x00

    // FUNCTION: GAMEMD 0x7B4620 (decl; reloc)
    Key_006B9530();
    // FUNCTION: GAMEMD 0x7B46F0 (decl; reloc)
    ~Key_006B9530();
    // FUNCTION: GAMEMD 0x7B4940 (decl; reloc)
    Key_006B9530& operator=(const Key_006B9530& other);
};
GG_STATIC_ASSERT(sizeof(Key_006B9530) == 4);

class OwnedObject_006B9530
{
public:
    virtual ~OwnedObject_006B9530();
};

struct Value_006B9530
{
    OwnedObject_006B9530* Object;   // +0x000
    char unknown_004[0x300];        // +0x004
};
GG_STATIC_ASSERT(sizeof(Value_006B9530) == 0x304);

template<class KEY, class VALUE>
inline bool HashTable_006249A0<KEY, VALUE>::PopFirst(KEY& key, VALUE& value)
{
    if (this->Count == 0) return false;

    float load = (float)(this->Count - 1) / this->BucketCount;
    int index = -1;
    for (int i = 0; i < (int)this->BucketCount; i++) {
        if (this->Buckets[i] != NULL) {
            index = i;
            break;
        }
    }
    if (index == -1) return false;

    key = this->Buckets[index]->Key;
    value = this->Buckets[index]->Value;
    Node* next = this->Buckets[index]->Next;
    delete this->Buckets[index];
    this->Buckets[index] = next;
    this->Count--;
    if (load <= this->ShrinkRatio) {
        Shrink();
    }
    return true;
}

template<class KEY, class VALUE>
HashTable_006249A0<KEY, VALUE>::~HashTable_006249A0()
{
    {
        KEY key;
        VALUE value;
        while (PopFirst(key, value)) {
            delete value.Object;
        }
    }

    for (unsigned i = 0; i < this->BucketCount; i++) {
        Node* node = this->Buckets[i];
        while (node != NULL) {
            Node* next = node->Next;
            delete node;
            node = next;
        }
        this->Buckets[i] = NULL;
    }
    this->Count = 0;

    while (this->BucketCount > this->MinBuckets && !this->IsFixed) {
        Shrink();
    }
    delete[] this->Buckets;
}

// The instantiation serves the static table at 0xAC4848, whose
// compiler-generated teardown thunk 0x600550 is `MOV ECX,0xAC4848; JMP
// 0x6B9530`. Defining that global here instead (so the thunks are generated)
// inlines this destructor into the thunk, unlike retail.
// FUNCTION: GAMEMD 0x6B9530 (destructor)
// FUNCTION: GAMEMD 0x6BAEF0 (Shrink, emitted by the same instantiation)
template struct HashTable_006249A0<Key_006B9530, Value_006B9530>;
