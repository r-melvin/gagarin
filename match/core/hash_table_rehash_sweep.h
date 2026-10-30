// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Every entry point, offset and chain-link displacement below was read off
//   the user's own retail gamemd.exe v1.001 with the local Ghidra CLI. The
//   table offsets come straight off the member accesses: the bucket array at
//   [EBX], the bucket count at [EBX+8], the bit width at [EBX+0xC], the fixed
//   flag at [EBX+0x14], the hash function at [EBX+0x18] and the floor at
//   [EBX+0x30]. The per-instance chain link is the displacement in
//   `MOV EAX,[ESI+n]` / `MOV [ESI+n],ECX` near the end of each body.
//
// Thirteen hash-table rehash functions: seven that halve the table (0xA8
// bytes) and six that double it (0x9C bytes).
//
// Both directions are the same routine with the new size computed differently.
// Halving refuses to go below the floor at +0x30; doubling has no such test.
// Either way: a table pinned by the flag at +0x14 is left alone, the new size
// and bit width are written back, a fresh bucket array is allocated and zeroed
// with an inline REP STOS, every chain in the old array is walked node by node
// and pushed onto the front of its new bucket, and the old array is freed.
//
// The rehash calls the table's own hash function through the member at +0x18
// with the node in ECX, then masks the result to the current bit width, so a
// node moves without the table knowing its key type.
//
//   THE TEMPLATE. Thirteen bodies, two shapes, and the only thing that varies
//   inside a shape is the displacement of the node's chain link -- exactly a
//   node type the table is parameterised on. So this is one class template,
//   `HashTable<Node>`, with the two directions as two members, emitted once
//   per instantiation as its own COMDAT. That is what the macro expansion this
//   file used to carry was standing in for; the template says the same thing
//   in the language retail's source used.
//
//   WHICH REFERENCE SHAPE APPLIES: NEITHER OF THE VTABLE ONES. Nothing here
//   writes a vptr -- the table has no virtual anything, its first member is
//   the bucket array at +0 -- so batch fifty-four's store-order test does not
//   arise and no traits parameter carrying a vtable is needed.
//
//   THE SPELLING IS A PLAIN `__thiscall` MEMBER. Each rehash takes its table
//   in ECX and no further argument, and returns with a bare `RET`; by batch
//   forty-seven's rule (zero further arguments -> `__thiscall` member, one or
//   more -> `__fastcall` member) the ordinary member spelling is
//   byte-identical to the free `__fastcall` form these used to carry.
//
//   ONE NODE TYPE PER RETAIL ADDRESS, NOT ONE PER DISPLACEMENT. Only four
//   displacements occur (+0x08, +0x0C, +0x48, +0x70) but thirteen addresses
//   exist, and several share a displacement and a direction. A template
//   instantiation emits one COMDAT per member, so thirteen distinct
//   instantiations are needed to reach thirteen retail addresses; each node
//   type is therefore keyed by the address of the rehash it produces, and
//   carries that address's measured link displacement. This also stops the
//   file asserting that two tables with the same link offset are the same
//   class -- they are not, and nothing here claims they are.
//
//   KNOWN LIMITATION -- this file is a staging ground, not a destination. The
//   TU-partition work established that MSVC6 emits each template
//   instantiation as a COMDAT into the translation unit that instantiated it.
//   These instantiations therefore belong to many different original
//   translation units, not to one. Grouping them in a single sweep file is
//   correct for matching bytes now and wrong for reproducing retail's link
//   order eventually; they will have to be redistributed to their owning TUs
//   when the partition is reconstructed.
#ifndef GG_MATCH_CORE_HASH_TABLE_REHASH_SWEEP_H
#define GG_MATCH_CORE_HASH_TABLE_REHASH_SWEEP_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void* __cdecl memset(void* dst, int fill, unsigned int bytes);

// One node type per retail rehash, carrying that rehash's measured chain-link
// displacement. The name is the address of the rehash it produces.
#define GG_REHASH_NODE(ADDR, OFF)                                          \
struct Node_##ADDR                                                         \
{                                                                          \
    char          _pad[0x##OFF];                                           \
    Node_##ADDR*  Next;                                                    \
};                                                                         \
GG_STATIC_ASSERT(offsetof(Node_##ADDR, Next) == 0x##OFF)

// FUNCTION: GAMEMD 0x005EEF60 -- chain link at +0x08.
GG_REHASH_NODE(005EEF60, 08);
// FUNCTION: GAMEMD 0x005EF010 -- chain link at +0x08.
GG_REHASH_NODE(005EF010, 08);
// FUNCTION: GAMEMD 0x00624BE0 -- chain link at +0x08.
GG_REHASH_NODE(00624BE0, 08);
// FUNCTION: GAMEMD 0x006252F0 -- chain link at +0x0C.
GG_REHASH_NODE(006252F0, 0C);
// FUNCTION: GAMEMD 0x00625780 -- chain link at +0x08.
GG_REHASH_NODE(00625780, 08);
// FUNCTION: GAMEMD 0x006258E0 -- chain link at +0x0C.
GG_REHASH_NODE(006258E0, 0C);
// FUNCTION: GAMEMD 0x006BAFA0 -- chain link at +0x308.
GG_REHASH_NODE(006BAFA0, 308);
// FUNCTION: GAMEMD 0x007ADF70 -- chain link at +0x70.
GG_REHASH_NODE(007ADF70, 70);
// FUNCTION: GAMEMD 0x007AE020 -- chain link at +0x70.
GG_REHASH_NODE(007AE020, 70);
// FUNCTION: GAMEMD 0x007AE0E0 -- chain link at +0x48.
GG_REHASH_NODE(007AE0E0, 48);
// FUNCTION: GAMEMD 0x007AE460 -- chain link at +0x08.
GG_REHASH_NODE(007AE460, 08);
// FUNCTION: GAMEMD 0x007AE510 -- chain link at +0x08.
GG_REHASH_NODE(007AE510, 08);
// FUNCTION: GAMEMD 0x007AE830 -- chain link at +0x08.
GG_REHASH_NODE(007AE830, 08);
// FUNCTION: GAMEMD 0x007AEF50 -- chain link at +0x48.
GG_REHASH_NODE(007AEF50, 48);

// The table. The bodies are the two directions; the phrasing levers in them
// are load-bearing and recorded beside the lines they govern.
template<class Node>
struct HashTable
{
    typedef int (* HashOf)(Node* node);

    Node**   Buckets;      // +0x0000
    int      _unknown_04;  // +0x0004
    unsigned BucketCount;  // +0x0008
    int      BitWidth;     // +0x000C
    int      _unknown_10;  // +0x0010
    char     IsFixed;      // +0x0014
    char     _pad015[3];   // +0x0015
    HashOf   Hash;         // +0x0018
    char     _pad01C[0x14];// +0x001C
    unsigned MinBuckets;   // +0x0030

    void Shrink();
    void Grow();
};

// The shared re-chaining tail. Binding the hash result to a named local before
// the mask is the phrasing lever: written inline as
// `((1 << BitWidth) - 1) & Hash(node)` cl builds the mask into the wrong
// register and reverses the three instructions that index the new bucket
// (81.7%); hoisting the mask into its own local instead is worse still (45.8%).
#define GG_REHASH_RECHAIN()                                                \
            Node* node = *p;                                               \
                                                                           \
            while (node != 0) {                                            \
                int hash = this->Hash(node);                               \
                unsigned idx = ((1 << this->BitWidth) - 1) & hash;         \
                Node* head = this->Buckets[idx];                           \
                this->Buckets[idx] = node;                                 \
                Node* next = node->Next;                                   \
                node->Next = head;                                         \
                node = next;                                               \
            }                                                              \
                                                                           \
            p++;                                                           \
            n--;

// Halve the table, unless it is pinned or already at the floor.
template<class Node>
void HashTable<Node>::Shrink()
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
                GG_REHASH_RECHAIN()
            } while (n != 0);
        }

        delete[] old;
    }
}

// Double the table, unless it is pinned.
//
// The doubled count has to be a named local used for both the write-back and
// the allocation. Spelled `count * 2` twice, cl computes the byte size
// independently as `LEA ECX,[ESI*8]` where retail derives it from the stored
// count with `SHL EAX,2` (85.1%).
template<class Node>
void HashTable<Node>::Grow()
{
    if (this->IsFixed == 1) return;

    {
        unsigned count = this->BucketCount;
        Node** old = this->Buckets;
        unsigned grown = count * 2;
        Node** fresh;

        this->BucketCount = grown;
        this->BitWidth = this->BitWidth + 1;
        fresh = new Node*[grown];
        this->Buckets = fresh;
        memset(fresh, 0, this->BucketCount * 4);

        if ((int)count > 0) {
            Node** p = old;
            unsigned n = count;

            do {
                GG_REHASH_RECHAIN()
            } while (n != 0);
        }

        delete[] old;
    }
}

#endif  // GG_MATCH_CORE_HASH_TABLE_REHASH_SWEEP_H
