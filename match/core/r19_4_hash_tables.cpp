// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 initialisers 0x6006B0 and 0x600880 and their exit-time
//   stubs 0x600750 and 0x600920. Each global is one chained hash table whose constructor
//   (128 buckets, load limits 0.2 / 0.8, hash function 0x600660) and destructor (free every
//   chain, shrink back to the initial size, free the bucket array) are expanded inline.
//
#include <string.h>

// Address index: 0x6006B0 0x600880 0x600A50 (exit stubs 0x600750 0x600920 0x600AF0 are not matched)

// LIBRARY: GAMEMD 0x600660 (decl; reloc) -- hash function: the key is the node's first dword.
extern "C" unsigned __fastcall HashKey_00600660(const int* key);

template <class T>
class ChainedHashTable
{
public:
    T**      Buckets;       // +0x00
    unsigned Count;         // +0x04
    unsigned Size;          // +0x08
    int      Shift;         // +0x0C
    unsigned unknown_10;    // +0x10
    bool     Fixed;         // +0x14
    unsigned (__fastcall *Hash)(const int*);   // +0x18
    unsigned unknown_1C;    // +0x1C
    double   LowLoad;       // +0x20
    double   HighLoad;      // +0x28
    unsigned InitialSize;   // +0x30

    static T** NewTable(unsigned count)
    {
        T** table = new T*[count];
        for (unsigned i = 0; i < count; i++) {
            table[i] = 0;
        }
        return table;
    }

    ChainedHashTable()
    {
        LowLoad = 0.2;
        HighLoad = 0.8;
        unknown_10 = InitialSize = 128;
        int bits = 0;
        do {
            bits++;
            unknown_10 >>= 1;
        } while (unknown_10 != 0);
        bits--;
        Shift = bits;
        Count = 0;
        Fixed = false;
        Size = 1 << bits;
        Buckets = new T*[Size];
        memset(Buckets, 0, Size * sizeof(T*));
        Hash = HashKey_00600660;
    }

    ~ChainedHashTable()
    {
        Clear();
        delete Buckets;
    }

    void Clear()
    {
        for (unsigned i = 0; i < Size; ) {
            T* node = Buckets[i];
            while (node != 0) {
                T* cur = node;
                node = node->Next;
                delete cur;
            }
            Buckets[i++] = 0;
        }
        Count = 0;
        while (Size > InitialSize && !Fixed) {
            Resize(Size >> 1);
        }
    }

    void Resize(unsigned newSize)
    {
        T** old = Buckets;
        int oldSize = Size;
        Size = newSize;
        Shift--;
        Buckets = NewTable(Size);
        for (int j = 0; j < oldSize; j++) {
            T* node = old[j];
            while (node != 0) {
                unsigned slot = Hash(&node->Key) & ((1 << Shift) - 1);
                T* next = node->Next;
                node->Next = Buckets[slot];
                Buckets[slot] = node;
                node = next;
            }
        }
        delete old;
    }
};

struct HashNode_006006B0
{
    int Key;
    int unknown_04;
    HashNode_006006B0* Next;
};

// GLOBAL: GAMEMD 0xAC1B48
// SYNTHETIC: GAMEMD 0x006006B0 -- initialiser of DAT_00AC1B48
// (exit-time destructor stub at 0x00600750 is emitted here but not yet byte-matched: ~30%)
ChainedHashTable<HashNode_006006B0> DAT_00AC1B48;

struct HashNode_00600880
{
    int Key;
    int unknown_04;
    HashNode_00600880* Next;
};

// GLOBAL: GAMEMD 0xAC18C0
// SYNTHETIC: GAMEMD 0x00600880 -- initialiser of DAT_00AC18C0
// (exit-time destructor stub at 0x00600920 is emitted here but not yet byte-matched: ~30%)
ChainedHashTable<HashNode_00600880> DAT_00AC18C0;

// Node of the dialog-type table: key, a 0x200-byte value, then the chain pointer.
struct HashNode_00600A50
{
    int Key;
    char unknown_04[0x200];
    HashNode_00600A50* Next;
};

// GLOBAL: GAMEMD 0xAC1B00
// SYNTHETIC: GAMEMD 0x00600A50 -- initialiser of DAT_00AC1B00
// (exit-time destructor stub at 0x00600AF0 is emitted here but not yet byte-matched: ~30%)
ChainedHashTable<HashNode_00600A50> DAT_00AC1B00;
