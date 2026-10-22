// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit wonline.cpp. The name is the source-file string at 0x84a430
//   in retail gamemd.exe v1.001, passed by the assert at 0x77d360 inside this object's
//   code range (0x77b690-0x7af0af). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The five derived constructors, ordered ascending by retail address.
//
//   Bytes read off the user's retail gamemd.exe v1.001 via the local Ghidra
//   CLI at 0x7ADCD0: __thiscall, `RET 8` (key reference, value out-pointer).
//   A chained hash table keyed by a 4-byte handle (equality 0x7B4780, release
//   0x7B46F0) holding 0x6C-byte values; nodes are {key, value, next@+0x70}.
//   Removing may halve the bucket array (shift-mask hashing through the hash
//   callback at +0x18) when the load drops to the shrink ratio at +0x20.
//
// The four seven-byte constant stores, ordered ascending by retail address.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.
//
// Small leaf bodies that repeat byte for byte at many addresses, each bound to
// its own global: release of a counted heap block, release of a counted array
// of string objects, and address-of-global accessors. Globals are named by
// retail address and typed only as far as the instructions show (a count at
// +0x00, a heap pointer at +0x08 for the two release shapes). The same shape
// at other addresses belongs to other statics; each address here is verified
// separately against retail.
//
// LIBRARY: GAMEMD 0x7C8B3D -- CRT free.
//
//   Bytes read off the user's retail gamemd.exe v1.001 via the local Ghidra
//   CLI at 0x7ACA00, 0x7AD790, 0x7ADB00 and 0x7AE5D0: four out-of-line copies
//   of one growable-array Insert (__thiscall, `RET 8`: item reference, index)
//   for element sizes 0x6C, 0x10C, 4 and a 4-byte class whose copy
//   constructor is 0x7B4690. The same grow-by-doubling (minimum 10) body is
//   inlined into 0x775DB0.
//
// This is not the VectorClass/DynamicVectorClass family: no vtable, the
// layout is {count, capacity, data}.
// No /GX: with it VC6 wraps the placement copy-construction of the handle
// instance (0x7AE5D0) in an unwind frame retail does not have.
//
// The six hash-bucket index functions, ordered ascending by retail address.
//
// Binding the hash result to a named local before the mask expression is the
// whole phrasing lever here. Retail computes the call first and builds the mask
// afterwards in EAX, ANDing the saved hash in EDX into it. Written inline --
// in either operand order, `mask & Hash(key)` or `Hash(key) & mask`
// -- cl builds the mask in EDX and ANDs into EAX, which reverses every register
// in the tail and scores 50%. The named local fixes the evaluation order and
// takes it to 100%.
//
// Growth step of a plain-old-data array holder (count at +0x00, capacity at
// +0x04, heap block at +0x08) that repeats at four addresses in different
// owners. Each address is a member of a placeholder owner `Obj_<ADDR>` that
// declares only those three fields. The new block is zero-filled, the live
// elements are copied across and the old block is freed.
//
// The seven vtable-seating base destructors, ordered ascending by address.
//
// Scalar deleting destructors of two WOL dialog controls and of MapSelect.
// Each runs the destructor inline (own vtable store where the class declares
// a destructor, member destructors in reverse order, then the base), frees
// the object when bit 0 of the flag is set and returns `this`.
//
// RTTI chains: CreateGameDialogControl -> WonlineStringDialogControl ->
// SimpleWonlineDialogControl -> OwnerDraw::SimpleDialogControl ->
// OwnerDraw::DialogControl, and MapSelect -> MSEngine. The DialogControl
// destructor (0x624130) and the MSEngine destructor (0x5D1B30) are out of
// line here; SimpleDialogControl and CreateGameDialogControl have implicit
// destructors (no vtable store of their own). Slot 0 is modelled as an
// ordinary virtual holding the deleting wrapper, as FileClass does in
// match/core/ram_file_class.h, because nothing is constructed in this file.

#include "base_ctor_vtable_seat_sweep.h"

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
        Key   unknown_00;     // +0x00
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
                unsigned index = ((1 << Bits) - 1) & Hash(node->unknown_00);
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

    if (prev->unknown_00 == key) {
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
        if (node->unknown_00 == key) {
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

#include "const_store_leaf_sweep.h"

#include "deleting_dtor_sweep.h"
#include "../network/transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

extern "C" void __cdecl gg_free(void*);


// FUNCTION: GAMEMD 0x007B46F0 (decl; reloc) -- string object destructor (this in ECX).
extern void __fastcall FUN_007B46F0(void* self);

struct CountedBlock {
    int count;          // +0x00
    int unknown_04;
    void* data;         // +0x08
};
struct CountedStringArray {
    int count;          // +0x00
    int unknown_04;
    unsigned char* data; // +0x08, elements of 4 bytes
};

#include "../network/wonline_leaf_methods.h"

extern CountedBlock DAT_00AC1DE0;
extern CountedBlock DAT_00B0BD50;
extern char DAT_00B2FF78;
extern CountedBlock DAT_00B72F38;
extern CountedBlock DAT_00B73E10;
extern CountedBlock DAT_00B76520;
extern CountedStringArray DAT_00B777A0;
extern CountedStringArray DAT_00B73BD8;
extern CountedStringArray DAT_00B76510;
extern CountedStringArray DAT_00B73AE8;
extern CountedStringArray DAT_00B77820;
extern CountedStringArray DAT_00B73708;
extern CountedStringArray DAT_00B76188;
extern CountedStringArray DAT_00B73AA8;
extern CountedStringArray DAT_00B76980;
extern CountedStringArray DAT_00B779B0;
extern CountedStringArray DAT_00B76AD0;
extern CountedStringArray DAT_00B76970;
extern char DAT_00B77F70;
extern char DAT_00B77F78;
extern char DAT_0084E7C0;
extern char DAT_0084E7C4;

#include "grow_list.h"
#include "../_rt/gg_static_assert.h"

// The two plain record element types (copied with REP MOVSD).
struct GrowListRecord6C
{
    int unknown_00[0x1B];
};
struct GrowListRecord10C
{
    int unknown_00[0x43];
};

#include "hash_bucket_mask_sweep.h"

#include <stddef.h>
#include <string.h>
#include <new.h>
#include "../_rt/gg_static_assert.h"

// LIBRARY: GAMEMD 0x7C8B3D -- CRT free.
extern "C" void __cdecl gg_free(void*);

struct Obj_006253B0 {
    int count;     // +0x00
    int capacity;  // +0x04
    int* data;     // +0x08
    bool FUN_006253B0();
};
GG_STATIC_ASSERT(offsetof(Obj_006253B0, data) == 0x08);


struct Obj_00625990 {
    int count;     // +0x00
    int capacity;  // +0x04
    int* data;     // +0x08
    bool FUN_00625990();
};
GG_STATIC_ASSERT(offsetof(Obj_00625990, data) == 0x08);


struct Obj_007AEEC0 {
    int count;     // +0x00
    int capacity;  // +0x04
    int* data;     // +0x08
    bool FUN_007AEEC0();
};
GG_STATIC_ASSERT(offsetof(Obj_007AEEC0, data) == 0x08);

struct Obj_007AF000 {
    int count;     // +0x00
    int capacity;  // +0x04
    int* data;     // +0x08
    bool FUN_007AF000();
};
GG_STATIC_ASSERT(offsetof(Obj_007AF000, data) == 0x08);

#include "seat_vtable_tail_dtor_sweep.h"

#include "trivial_tu288_methods.h"

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Out-of-line destructor 0x7B46F0 (a four-byte member: a string handle).
class Member_7B46F0
{
public:
    ~Member_7B46F0();
    void* Data;
};

// MapStageList::~MapStageList is the out-of-line destructor at 0x5CEE60.
class MapStageList
{
public:
    ~MapStageList();
};

namespace OwnerDraw {

class DialogControl
{
public:
    ~DialogControl();   // 0x624130
    virtual void* DeletingDtor(unsigned int flags);
    int unknown_04;     // +0x04
    int unknown_08;     // +0x08
};

class SimpleDialogControl : public DialogControl
{
};

}  // namespace OwnerDraw

// VTABLE: GAMEMD 0x7F7624
class SimpleWonlineDialogControl : public OwnerDraw::SimpleDialogControl
{
public:
    ~SimpleWonlineDialogControl() {}
};

// VTABLE: GAMEMD 0x7F7874
class WonlineStringDialogControl : public SimpleWonlineDialogControl
{
public:
    ~WonlineStringDialogControl() {}
    virtual void* DeletingDtor(unsigned int flags);
    Member_7B46F0 String;   // +0x0C
};

class CreateGameDialogControl : public WonlineStringDialogControl
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

GG_STATIC_ASSERT(offsetof(WonlineStringDialogControl, String) == 0x0C);

class MSEngine
{
public:
    ~MSEngine();   // 0x5D1B30
    virtual void* DeletingDtor(unsigned int flags);
    char unknown_04[0x4C];   // +0x04
};

// Implicit destructor: the members, then the MSEngine one.
class MapSelect : public MSEngine
{
public:
    virtual void* DeletingDtor(unsigned int flags);
    MapStageList Stages;        // +0x50
    char unknown_51[0x77];      // +0x51
    Member_7B46F0 Member_C8;    // +0xC8
};

GG_STATIC_ASSERT(offsetof(MapSelect, Stages) == 0x50);
GG_STATIC_ASSERT(offsetof(MapSelect, Member_C8) == 0xC8);

// ---- from the former wonline_leaf_methods.cpp ----
// Small leaf functions of the online-services translation unit (retail text
// 0x77B690..0x7AF0AF; its assertion path string 0x84A430 is
// "D:\ra2mdpost\wonline.cpp"). Retail address order. All names are
// placeholders unless a string in the binary attests them.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// First record of the table whose flag bit 0 is set (copied to 0xB777B0), or NULL.
static inline Entry_00B77908* FirstFlaggedRecord()
{
    for (int i = 0; i < DAT_00B77900.count; i++) {
        if (i >= 0 && i < DAT_00B77900.count) {
            DAT_00B777B0 = DAT_00B77900.data[i];
        }
        if (DAT_00B777B0.unknown_00[0] & 1) {
            return &DAT_00B777B0;
        }
    }
    return NULL;
}

// Chain lookup of a string key in a table whose nodes hold a value of the
// given type: the address of the value is stored through `out`. Layout of the
// table as in core/hash_table_view.h. Each table type has its own copy.
template<class VALUE>
inline bool FindNode_007AE180(HashTable_006249A0<String_007B4620, VALUE>* table,
                              const String_007B4620& key, VALUE** out)
{
    if (table->Count == 0) return false;

    int hash = table->Hash(&key);
    HashNode_006249A0<String_007B4620, VALUE>* node =
        table->Buckets[((1 << table->BitWidth) - 1) & hash];
    if (node == NULL) return false;

    while (node != NULL) {
        if (node->Key == key) break;
        node = node->Next;
    }
    if (node == NULL) return false;
    *out = &node->Value;
    return true;
}

// STRING: GAMEMD 0x84A430
static const char DAT_0084A430[] = "D:\\ra2mdpost\\wonline.cpp";

// Value of the node filed under `key`, or null (inlined at every use).
template<class VALUE>
inline VALUE* FindValue_0079BED0(HashTable_006249A0<String_007B4620, VALUE>& table, const String_007B4620& key)
{
    if (table.Count == 0) return 0;

    int hash = table.Hash(&key);
    HashNode_006249A0<String_007B4620, VALUE>* node = table.Buckets[((1 << table.BitWidth) - 1) & hash];

    while (node != 0) {
        if (node->Key == key) break;
        node = node->Next;
    }
    return node != 0 ? &node->Value : 0;
}

// The test of 0x77CF40, inlined here.
static inline int IsOnlineMode()
{
    return DAT_00A8B244 == 3 || DAT_00A8B244 == 1 || DAT_00A8B244 == 2;
}

// STRING: GAMEMD 0x8263A8
static const char DAT_008263A8[] = "INTRO";

// The body of 0x77D7A0, inlined into the caller below.
static inline void ThemeUpdate_0077D7A0(bool start)
{
    if (start) {
        if (!DAT_00A83D10.FUN_00720FD0()) {
            DAT_00A83D10.Stop(false);
            DAT_00A83D10.QueueSong(-2);
        } else {
            int theme = DAT_00A83D10.LastTheme;
            if (theme == -1) theme = DAT_00A83D10.QueuedTheme;
            if (theme == DAT_00A83D10.FindIndex(DAT_008263A8)) {
                DAT_00A83D10.Stop(false);
                DAT_00A83D10.QueueSong(-2);
            }
        }
    } else {
        DAT_00A83D10.QueueSong(-3);
    }
}

// ---- from the former wonline_hash_shrink.cpp ----
// Hash table halving of the online-services translation unit (retail text
// 0x77B690..0x7AF0AF; its assertion path string 0x84A430 is
// "D:\ra2mdpost\wonline.cpp"). The body is the shared template of
// core/hash_table_rehash_sweep.h; only the chain-link displacement differs.

#include "hash_table_rehash_sweep.h"

// Chain link at +0x110 (a 0x10C-byte value after the key word).
GG_REHASH_NODE(007AEC00, 110);

// FUNCTION: GAMEMD 0x0077B920
void FUN_0077B920()
{
    void* block = DAT_00B778D8.data;
    DAT_00B778D8.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077B960
void FUN_0077B960()
{
    void* block = DAT_00B73E10.data;
    DAT_00B73E10.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077B9A0
void FUN_0077B9A0()
{
    void* block = DAT_00B76AE0.data;
    DAT_00B76AE0.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077B9E0
void FUN_0077B9E0()
{
    void* block = DAT_00B77900.data;
    DAT_00B77900.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077BA20
void FUN_0077BA20()
{
    void* block = DAT_00B76520.data;
    DAT_00B76520.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077C370
void FUN_0077C370()
{
    for (int i = 0; i < DAT_00B777A0.count; ++i)
        FUN_007B46F0(DAT_00B777A0.data + i * 4);
    void* block = DAT_00B777A0.data;
    DAT_00B777A0.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077C600
void FUN_0077C600()
{
    for (int i = 0; i < DAT_00B73BD8.count; ++i)
        FUN_007B46F0(DAT_00B73BD8.data + i * 4);
    void* block = DAT_00B73BD8.data;
    DAT_00B73BD8.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077C720
void FUN_0077C720()
{
    for (int i = 0; i < DAT_00B76510.count; ++i)
        FUN_007B46F0(DAT_00B76510.data + i * 4);
    void* block = DAT_00B76510.data;
    DAT_00B76510.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077C780
void FUN_0077C780()
{
    for (int i = 0; i < DAT_00B73AE8.count; ++i)
        FUN_007B46F0(DAT_00B73AE8.data + i * 4);
    void* block = DAT_00B73AE8.data;
    DAT_00B73AE8.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077C7E0
void FUN_0077C7E0()
{
    for (int i = 0; i < DAT_00B77820.count; ++i)
        FUN_007B46F0(DAT_00B77820.data + i * 4);
    void* block = DAT_00B77820.data;
    DAT_00B77820.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077C840
void FUN_0077C840()
{
    for (int i = 0; i < DAT_00B73708.count; ++i)
        FUN_007B46F0(DAT_00B73708.data + i * 4);
    void* block = DAT_00B73708.data;
    DAT_00B73708.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077C8A0
void FUN_0077C8A0()
{
    for (int i = 0; i < DAT_00B76188.count; ++i)
        FUN_007B46F0(DAT_00B76188.data + i * 4);
    void* block = DAT_00B76188.data;
    DAT_00B76188.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077C900
void FUN_0077C900()
{
    for (int i = 0; i < DAT_00B73AA8.count; ++i)
        FUN_007B46F0(DAT_00B73AA8.data + i * 4);
    void* block = DAT_00B73AA8.data;
    DAT_00B73AA8.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077C960
void FUN_0077C960()
{
    for (int i = 0; i < DAT_00B76980.count; ++i)
        FUN_007B46F0(DAT_00B76980.data + i * 4);
    void* block = DAT_00B76980.data;
    DAT_00B76980.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077C9C0
void FUN_0077C9C0()
{
    for (int i = 0; i < DAT_00B779B0.count; ++i)
        FUN_007B46F0(DAT_00B779B0.data + i * 4);
    void* block = DAT_00B779B0.data;
    DAT_00B779B0.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077CE70
void FUN_0077CE70()
{
    for (int i = 0; i < DAT_00B76AD0.count; ++i)
        FUN_007B46F0(DAT_00B76AD0.data + i * 4);
    void* block = DAT_00B76AD0.data;
    DAT_00B76AD0.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x0077CED0
void FUN_0077CED0()
{
    for (int i = 0; i < DAT_00B76970.count; ++i)
        FUN_007B46F0(DAT_00B76970.data + i * 4);
    void* block = DAT_00B76970.data;
    DAT_00B76970.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x77D1D0
// VTABLE: GAMEMD 0x7F7624
CtorSeatObject* __fastcall FUN_0077D1D0(CtorSeatObject* self)
{
    FUN_00624110(self);
    self->Vtbl = VTABLE_007F7624;

    return self;
}

// FUNCTION: GAMEMD 0x77D1F0
// VTABLE: GAMEMD 0x7F7624
void __fastcall FUN_0077D1F0(SeatDtorObject* self)
{
    self->Vtbl = VTABLE_007F7624;
    FUN_00624130(self);
}

// FUNCTION: GAMEMD 0x77D200
// Tail-forwards to another function. Vtable slot 4 of SimpleWonlineDialogControl (RTTI) and 2 derived vtable(s).
void FUN_0077D200(Obj_0077D200* a1, int a2)
{
    FUN_0077F900(a1, a2);
}

// FUNCTION: GAMEMD 0x77E110
void __fastcall FUN_0077E110()
{
    if (DAT_00AC116C != NULL) {
        DAT_00AC116C->Vtbl->At_7C(DAT_00AC116C, DAT_00B779BC);
        DAT_00AC116C->Vtbl->At_68(DAT_00AC116C, DAT_00B779F0, DAT_00B76234);
    }
    FUN_005EE350(0);
    bool start = DAT_00B7690C != 0;
    ThemeUpdate_0077D7A0(start);
}

// FUNCTION: GAMEMD 0x781380
// Orders by Value; the value -1 sorts last.
int __cdecl FUN_00781380(const void* left, const void* right)
{
    int x = ((const Obj_00781380*)left)->Value;
    int y = ((const Obj_00781380*)right)->Value;
    if (x < y) return x == -1 ? 1 : -1;
    if (x > y) return y == -1 ? -1 : 1;
    return 0;
}

// FUNCTION: GAMEMD 0x7813B0
// Orders by Value, descending.
int __cdecl FUN_007813B0(const void* left, const void* right)
{
    int x = ((const Obj_00781380*)left)->Value;
    int y = ((const Obj_00781380*)right)->Value;
    if (x < y) return 1;
    return x > y ? -1 : 0;
}

// FUNCTION: GAMEMD 0x7813E0
// Builds {index, key} pairs for every record and sorts them by key.
void __fastcall FUN_007813E0(Obj_00781380* pairs, bool descending)
{
    Record_00B76AE8 record;
    memset(&record, 0, sizeof(record));

    for (int i = 0; i < DAT_00B76AE0.count; i++) {
        if (i >= 0 && i < DAT_00B76AE0.count) {
            record = DAT_00B76AE0.data[i];
        }
        pairs[i].unknown_00 = i;
        pairs[i].Value = record.Key;
    }
    if (descending) {
        qsort(pairs, DAT_00B76AE0.count, sizeof(Obj_00781380), FUN_00781380);
    } else {
        qsort(pairs, DAT_00B76AE0.count, sizeof(Obj_00781380), FUN_007813B0);
    }
}

// FUNCTION: GAMEMD 0x781CC0
// Orders by flag (zero sorts last), then by name, case-insensitively.
int __cdecl FUN_00781CC0(const Obj_00781CC0* a, const Obj_00781CC0* b)
{
    if (a->Flag != b->Flag) return a->Flag ? -1 : 1;
    return _stricmp(a->Name, b->Name);
}

// FUNCTION: GAMEMD 0x781CF0
// As 0x781CC0 with the names reversed.
int __cdecl FUN_00781CF0(const Obj_00781CC0* a, const Obj_00781CC0* b)
{
    if (a->Flag != b->Flag) return a->Flag ? -1 : 1;
    return _stricmp(b->Name, a->Name);
}

// FUNCTION: GAMEMD 0x783070
void __fastcall FUN_00783070(void* object)
{
    int mode = DAT_00B77E48;
    if (mode == 1) {
        FUN_00781FB0(object, false);
    } else if (mode == 2) {
        FUN_00782320(object, true);
    } else if (mode == 3) {
        FUN_00782320(object, false);
    } else if (mode == 4) {
        FUN_00782BB0(object, true);
    } else if (mode == 5) {
        FUN_00782BB0(object, false);
    } else {
        FUN_00781FB0(object, true);
    }
}

// FUNCTION: GAMEMD 0x7830C0
// Orders by flag (zero sorts last), then by key (-1 sorts last), then by the
// records' names, case-insensitively.
int __cdecl FUN_007830C0(const Item_007830C0* a, const Item_007830C0* b)
{
    if (a->Flag != b->Flag) return a->Flag ? -1 : 1;

    int x = a->Key;
    int y = b->Key;
    if (x < y) return x == -1 ? 1 : -1;
    if (x > y) return y == -1 ? -1 : 1;

    Entry_00B77908 first;
    Entry_00B77908 second;
    memset(&first, 0, sizeof(first));
    memset(&second, 0, sizeof(second));
    if (a->Index >= 0 && a->Index < DAT_00B77900.count) first = DAT_00B77900.data[a->Index];
    if (b->Index >= 0 && b->Index < DAT_00B77900.count) second = DAT_00B77900.data[b->Index];
    return _stricmp(first.unknown_24, second.unknown_24);
}

// FUNCTION: GAMEMD 0x783520
// Case-insensitive name order; an empty name sorts last.
int __cdecl FUN_00783520(const char* a, const char* b)
{
    int lengthA = (int)strlen(a);
    int lengthB = (int)strlen(b);
    if (lengthA != 0) {
        if (lengthB != 0) return _stricmp(a, b);
        if (lengthA > 0) return -1;
    }
    return lengthB > 0;
}

// FUNCTION: GAMEMD 0x783570
// As 0x783520 with the operands of the comparison swapped.
int __cdecl FUN_00783570(const char* a, const char* b)
{
    int lengthA = (int)strlen(a);
    int lengthB = (int)strlen(b);
    if (lengthA != 0) {
        if (lengthB != 0) return _stricmp(b, a);
        if (lengthA > 0) return -1;
    }
    return lengthB > 0;
}

// FUNCTION: GAMEMD 0x7835C0
// Orders by flag (zero sorts last), then by name (an empty name sorts last)
// ascending, then by the records' names, case-insensitively.
int __cdecl FUN_007835C0(const Item_007835C0* a, const Item_007835C0* b)
{
    if (a->Flag != b->Flag) return a->Flag ? -1 : 1;

    int lengthA = (int)strlen(a->Name);
    int lengthB = (int)strlen(b->Name);
    if (lengthA != 0) {
        if (lengthB != 0) {
            int result = _stricmp(a->Name, b->Name);
            if (result != 0) return result;
        } else if (lengthA > 0) {
            return -1;
        }
    } else if (lengthB > 0) {
        return 1;
    }

    Entry_00B77908 first;
    Entry_00B77908 second;
    memset(&first, 0, sizeof(first));
    memset(&second, 0, sizeof(second));
    if (a->Index >= 0 && a->Index < DAT_00B77900.count) first = DAT_00B77900.data[a->Index];
    if (b->Index >= 0 && b->Index < DAT_00B77900.count) second = DAT_00B77900.data[b->Index];
    return _stricmp(first.unknown_24, second.unknown_24);
}

// FUNCTION: GAMEMD 0x7836E0
// Orders by flag (zero sorts last), then by name (an empty name sorts last)
// descending, then by the records' names, case-insensitively.
int __cdecl FUN_007836E0(const Item_007835C0* a, const Item_007835C0* b)
{
    if (a->Flag != b->Flag) return a->Flag ? -1 : 1;

    int lengthA = (int)strlen(a->Name);
    int lengthB = (int)strlen(b->Name);
    if (lengthA != 0) {
        if (lengthB != 0) {
            int result = _stricmp(b->Name, a->Name);
            if (result != 0) return result;
        } else if (lengthA > 0) {
            return -1;
        }
    } else if (lengthB > 0) {
        return 1;
    }

    Entry_00B77908 first;
    Entry_00B77908 second;
    memset(&first, 0, sizeof(first));
    memset(&second, 0, sizeof(second));
    if (a->Index >= 0 && a->Index < DAT_00B77900.count) first = DAT_00B77900.data[a->Index];
    if (b->Index >= 0 && b->Index < DAT_00B77900.count) second = DAT_00B77900.data[b->Index];
    return _stricmp(first.unknown_24, second.unknown_24);
}

// FUNCTION: GAMEMD 0x785360
// Tail-calls a method on a global object.
void __cdecl FUN_00785360()
{
    FUN_00783C80(0, 0);
}

// FUNCTION: GAMEMD 0x786D90
bool __fastcall FUN_00786D90()
{
    int index = DAT_00B76468;
    if (index >= 1 && index < DAT_00B778D8.count) {
        Record_00B778E0* record = NULL;
        if (index >= 0) record = &DAT_00B778D8.data[index];
        return FUN_007864C0(record);
    }
    return false;
}

// FUNCTION: GAMEMD 0x786E70
// Index of the record whose text after the ':' at +0x18 equals the name, or -1.
int __fastcall FUN_00786E70(String_007B4620* name)
{
    if (name->Length() != 0) {
        for (int i = 1; i < DAT_00B778D8.count; i++) {
            const char* text = NULL;
            if (i >= 0 && i < DAT_00B778D8.count) {
                text = (const char*)&DAT_00B778D8.data[i];
            }
            const char* colon = strchr(text + 0x18, ':');
            if (colon != NULL && *colon != 0) {
                if (name->FUN_007B4710(colon + 1)) return i;
            }
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x78ABF0
void __fastcall FUN_0078ABF0(char flag, const wchar_t* text)
{
    DAT_00B77E40 = flag;
    DAT_00B76230.FUN_007B7600(text);
}

// FUNCTION: GAMEMD 0x78F6B0
int __fastcall FUN_0078F6B0(int id)
{
    if (id == 0x754) return 0;
    if (id == 0x755) return 1;
    if (id == 0x756) return 2;
    if (id == 0x757) return 3;
    if (id == 0x758) return 4;
    if (id == 0x759) return 5;
    if (id == 0x75A) return 6;
    return id == 0x75B ? 7 : -1;
}

// FUNCTION: GAMEMD 0x791AA0
void __fastcall FUN_00791AA0(void* window)
{
    if (window != NULL) {
        FUN_005E2CD0(DAT_00AC10C8 == 0
                         ? FUN_00734E60("TXT_CHANNEL_FULL", NULL, DAT_0084A430, 0x4351)
                         : FUN_00734E60("TXT_OBSERVER_FULL", NULL, DAT_0084A430, 0x4353),
                     0, (void*)FUN_0077D710, 0);
        if (DAT_00AC116C->Vtbl->At_24(DAT_00AC116C) < 0) {
            FUN_007757E0(window, 2);
        }
    }
}

// FUNCTION: GAMEMD 0x792E90
void __fastcall FUN_00792E90(LPARAM value)
{
    HWND dialog = FUN_00775940(0xC4);
    if (dialog != NULL) {
        SendDlgItemMessageA(dialog, 0x5B2, 0x4B2, 0, value);
    }
}

// FUNCTION: GAMEMD 0x792EC0
void __fastcall FUN_00792EC0(unsigned int mask)
{
    HWND dialog = FUN_00775940(0xC4);
    if (dialog != NULL) {
        DAT_00B77DC8 &= ~mask;
        if (DAT_00B77DC8 == 0) {
            FUN_007757E0(dialog, 0);
        }
    }
    HWND parent = (HWND)FUN_00775B10();
    HWND control = GetDlgItem(parent, 0x540);
    if (control != NULL) {
        SetFocus(control);
    }
}

// FUNCTION: GAMEMD 0x7930A0
bool __fastcall FUN_007930A0()
{
    Entry_00B77908* record = FirstFlaggedRecord();
    if (record == NULL) return false;
    return _stricmp(record->unknown_24, DAT_00B73E40.FUN_007B5440()) ? false : true;
}

// FUNCTION: GAMEMD 0x793120
bool __fastcall FUN_00793120(String_007B4620* name)
{
    Entry_00B77908* record = FirstFlaggedRecord();
    if (record == NULL) return false;
    return _stricmp(record->unknown_24, name->FUN_007B5440()) ? false : true;
}

// FUNCTION: GAMEMD 0x7931A0
Entry_00B77908* __fastcall FUN_007931A0()
{
    return FirstFlaggedRecord();
}

// FUNCTION: GAMEMD 0x7931F0
void __fastcall FUN_007931F0(int slot)
{
    if (slot >= 0 && slot < DAT_00A8DA84) {
        HWND dialog = FUN_00775940(0x130);
        if (dialog != NULL) {
            HWND control = GetDlgItem(dialog, DAT_0084A1F0[slot]);
            DAT_00B75F54[slot] = 1;
            SendMessageA(control, 0xF1, 1, 0);
            PostMessageA(dialog, 0xF, 0, 0);
        }
    }
}

// FUNCTION: GAMEMD 0x793250
void __fastcall FUN_00793250()
{
    HWND window = FUN_00775700(DAT_00B732F0, 0x130, DAT_00B73550, (void*)FUN_00793280, 0);
    if (window != NULL) {
        FUN_00622820(window, 0x130);
    }
}

// FUNCTION: GAMEMD 0x793460
void __fastcall FUN_00793460(int index, int value)
{
    if (index < DAT_00A8DA84) {
        if (DAT_00B73BB4[index] < DAT_0084A1E0[index]) {
            DAT_00B73BB4[index] = value;
        }
    }
}

// FUNCTION: GAMEMD 0x793710
// Derives a port number from a base, an offset and a spread; the result is
// never below 0x400.
unsigned short __fastcall FUN_00793710(int base, int offset, int unused, int spread)
{
    int port = base + offset;

    if (spread != 1) {
        if (spread == 2) {
            port = offset + base * 2;
        } else if (spread > 1) {
            port = base % 2 + offset + (base / 2) * spread;
        } else if (spread < 0) {
            if (spread == -100) {
                port = offset + base * 100;
            } else {
                port = base % 2 - (base / 2) * spread + offset;
            }
        }
    }
    FUN_004068E0("Get_Port_Blitz_Port_Number - send port = %d, mangled_port = %d, port_spread = %d, port = %d\n",
                 base, offset, spread, port);
    unsigned short narrow = (unsigned short)port;
    if (narrow < 0x400) return 0x400;
    return narrow;
}

// FUNCTION: GAMEMD 0x793A10
void __fastcall FUN_00793A10(const char* name, int port)
{
    FUN_004068E0("Player %s is telling us we should send to port %d\n", name, port & 0xFFFF);
    for (int i = 0; i < 8; i++) {
        if (_stricmp(FUN_007350C0(DAT_00A8DA90[i]), name) == 0) {
            DAT_00A8E050[i] = (short)port;
            return;
        }
    }
}

// FUNCTION: GAMEMD 0x793B30
void __fastcall FUN_00793B30(int digit, const char* text)
{
    char buffer[0x100];

    buffer[0] = 'Z';
    buffer[1] = '1';
    buffer[2] = (char)(digit + '0');
    if (text != NULL) {
        strcpy(&buffer[3], text);
    } else {
        buffer[3] = 0;
    }
    FUN_004068E0("Sending public options string %s\n", buffer);
    DAT_00AC116C->Vtbl->At_3C(DAT_00AC116C, buffer);
}

// FUNCTION: GAMEMD 0x796B20
// Empty function.
void __cdecl FUN_00796B20()
{
}

// FUNCTION: GAMEMD 0x7975E0
void __fastcall FUN_007975E0()
{
    const wchar_t* label = FUN_00734E60("TXT_FETCHING_SERVLIST", NULL, DAT_0084A430, 0x5EEC);
    {
        WideString_007B66C0 text(label);
        FUN_00792BE0(0x10, &text, 0);
    }
    int mode = 0x2300;
    if (DAT_00A8B244 != 3) mode = 0x2900;
    FUN_00797640(mode);
}

// FUNCTION: GAMEMD 0x7982D0
// Waits up to `seconds` for one of `count` events, pumping in 100 ms slices;
// returns the signalled index (the event is reset) or 0x12 on timeout.
DWORD __fastcall FUN_007982D0(int seconds, DWORD count)
{
    int remaining = seconds * 1000;
    DWORD result = WaitForMultipleObjects(count, DAT_00B73684, FALSE, 100);
    while (result == WAIT_TIMEOUT) {
        remaining -= 100;
        if (remaining <= 0) return 0x12;
        FUN_0077F900();
        result = WaitForMultipleObjects(count, DAT_00B73684, FALSE, 100);
    }
    ResetEvent(DAT_00B73684[result]);
    return result;
}

// FUNCTION: GAMEMD 0x798340
void __fastcall FUN_00798340()
{
    for (int i = 0; i < 18; i++) {
        ResetEvent(DAT_00B73684[i]);
    }
}

// FUNCTION: GAMEMD 0x799CD0
void __fastcall FUN_00799CD0()
{
    memset(DAT_00B76B10, 0, sizeof(DAT_00B76B10));
    memset(DAT_00B73BE8, 0, sizeof(DAT_00B73BE8));
    DAT_0084A210 = 1;
    DAT_00B73E10.count = 0;
    DAT_00B76AE0.count = 0;
    DAT_00B77900.count = 0;
    DAT_00B77DD0 = 0;
}

// FUNCTION: GAMEMD 0x799D10
// Releases every object the list head yields.
void __fastcall FUN_00799D10()
{
    void* object;
    for (object = FUN_00775B10(); object != NULL; object = FUN_00775B10()) {
        FUN_007757E0(object, 0);
    }
}

// FUNCTION: GAMEMD 0x79BE70
void __fastcall FUN_0079BE70()
{
    HWND window = FUN_00775700(DAT_00B732F0, 0x11E, DAT_00B73550, (void*)FUN_0079DB50, 0);
    FUN_00622820(window, 0x11E);
    SendMessageA(window, 0x4A9, 0, 1);
    ShowWindow(window, 1);
    FUN_007759E0(window, (void*)static_cast<void (__cdecl*)()>(FUN_0077F900), 0, 1, 1);
}

// FUNCTION: GAMEMD 0x79BED0
//   Not exact (72.9% positional, 83% aligned): retail keeps one false exit
//   per path (the loop exit returns with the comparison result still in AL);
//   this build merges them into one.
bool __fastcall FUN_0079BED0()
{
    if (DAT_00B76E24.Length() == 0) return false;

    int* value = FindValue_0079BED0(DAT_00B76990, DAT_00B76E24);
    if (value == NULL) return false;
    return *value < 0 || *value > 2;
}

// FUNCTION: GAMEMD 0x79FC10
void __fastcall FUN_0079FC10(int first, int second, int third)
{
    DAT_00B77E14 = third;
    DAT_00B73A20 = first;
    DAT_00B77D70 = second;
    DAT_00B77A88 = (int)time(NULL);
}

// FUNCTION: GAMEMD 0x7A0DD0
void __fastcall FUN_007A0DD0(Entry_00B77908* entry)
{
    if (entry == NULL) return;

    for (int i = 0; i < 8; i++) {
        if (DAT_00A8DA90[i] != NULL) {
            if (strcmp(FUN_007350C0(DAT_00A8DA90[i]), entry->unknown_24) == 0) {
                void* object = FUN_005E26C0();
                if (object != NULL) {
                    FUN_004E34A0(object, i, -1);
                }
                return;
            }
        }
    }
}

// FUNCTION: GAMEMD 0x7A0E50
void __fastcall FUN_007A0E50()
{
    for (int i = 0; i < 8; i++) {
        if (DAT_00A8DA90[i] == NULL || !FUN_005E93F0(DAT_00A8DA90[i])) {
            DAT_00B76440[i] = -1;
        }
        const char* name = FUN_007350C0(DAT_00A8DA90[i]);
        FUN_007A0EA0(name, DAT_00B76440[i]);
    }
}

// FUNCTION: GAMEMD 0x7A0EA0
// Records the ping of the player whose name matches and files its quality
// bucket with the object at 0x5E26C0.
void __fastcall FUN_007A0EA0(const char* name, int ping)
{
    FUN_004068E0("Got ping from gameoptions.  name = %s, ping = %d\n", name, ping);
    for (int i = 0; i < 8; i++) {
        if (DAT_00A8DA90[i] != NULL) {
            if (strcmp(FUN_007350C0(DAT_00A8DA90[i]), name) == 0) {
                DAT_00B76440[i] = ping;
                void* object = FUN_005E26C0();
                if (object != NULL) {
                    if (ping < 0) FUN_004E34A0(object, i, -1);
                    else if (ping < 300) FUN_004E34A0(object, i, 0);
                    else if (ping < 500) FUN_004E34A0(object, i, 1);
                    else FUN_004E34A0(object, i, 2);
                }
            }
        }
    }
}

// FUNCTION: GAMEMD 0x7A2730
void __fastcall FUN_007A2730()
{
    if (DAT_00AC116C != NULL) {
        DAT_00AC116C->Vtbl->At_3C(DAT_00AC116C, DAT_0084D690);
    }
}

// FUNCTION: GAMEMD 0x7A2750
void __fastcall FUN_007A2750()
{
    HWND dialog = (HWND)FUN_00775B10();
    HWND control = GetDlgItem(dialog, 0x59F);
    bool notOne;
    {
        String_007B4620 name((const char*)NULL);
        notOne = FUN_0077EBA0(&name) != 1;
    }
    if (notOne) {
        SendMessageA(control, 0x4DC, 0, 1);
        FUN_005E2700(-1, FUN_00734E60("GUI:HostGameStartJoiner", NULL, DAT_0084A430, 0x7212));
    }
}

// FUNCTION: GAMEMD 0x7A2800
void __fastcall FUN_007A2800(int a, int b, int c)
{
    HWND window = FUN_00775940(0xC2);
    FUN_005EC880(window, a, b, c);
}

// FUNCTION: GAMEMD 0x7A2830
void __fastcall FUN_007A2830(String_007B4620* name)
{
    Entry_00B77908 record;

    for (int i = 0; i < DAT_00B77900.count; i++) {
        if (i >= 0 && i < DAT_00B77900.count) {
            record = DAT_00B77900.data[i];
        }
        if (_stricmp(name->FUN_007B5440(), record.unknown_24) == 0) {
            DAT_00AC116C->Vtbl->At_54(DAT_00AC116C, &record);
            return;
        }
    }
}

// FUNCTION: GAMEMD 0x7A30D0
// Slot 5 of CNetUtilEventSink (RTTI); string 0x84A9E0 attests the callback name.
long __stdcall FUN_007A30D0(void* self, int result)
{
    FUN_004068E0("OnGameresSent  %d\n", result);
    if (result == 0) {
        FUN_006C6D00();
    }
    FUN_006C6DE0();
    return 0;
}

// FUNCTION: GAMEMD 0x7A4070
// Slot 7 of CNetUtilEventSink (RTTI); string 0x84AACC attests the callback name.
long __stdcall FUN_007A4070(void* self, int a, int b, int c)
{
    FUN_004068E0("OnAgeCheck\n");
    DAT_00B77DF4 = a;
    if (a == 0) {
        DAT_00B77E60 = b;
        DAT_00B77E64 = c;
    }
    HWND dialog = FUN_00775940(0xC4);
    if (dialog != NULL) {
        DAT_00B77DC8 &= ~0x100u;
        if (DAT_00B77DC8 == 0) {
            FUN_007757E0(dialog, 0);
        }
    }
    HWND parent = (HWND)FUN_00775B10();
    HWND control = GetDlgItem(parent, 0x540);
    if (control != NULL) {
        SetFocus(control);
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7A40F0
// Slot 3 of CNetUtilEventSink (RTTI); string 0x84AAD8 attests the callback name.
long __stdcall FUN_007A40F0(void* self, int a, int b, int c, int d)
{
    if (DAT_00B77DC1 && DAT_00B77780) {
        if (a == 0 && b >= 0 && b < 1000) {
            DAT_00B77CE0++;
        }
        return 0;
    }
    if (IsOnlineMode()) {
        FUN_004068E0("Received Ping\n");
        DAT_00B736F4++;
        if (DAT_00B736F4 >= DAT_00B76970.count) {
            if (DAT_00B73A20 == 4 || DAT_00B73A20 == 5) {
                FUN_007A1330();
            }
            FUN_007A1060();
        }
    } else if (DAT_00B76B10[0] != 0) {
        FUN_00783C80(0, 0);
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7A70E0
// Slot 11 of CChatEventSink (RTTI); string 0x84AD84 attests the callback name.
long __stdcall FUN_007A70E0(void* self, long result, int unused, int value)
{
    if (result < 0) {
        FUN_004068E0("OnChannelLeave with error!\n");
        return 0;
    }
    FUN_00785740(value);
    return 0;
}

// FUNCTION: GAMEMD 0x7AB330
// Returns zero; pops its stack arguments. Vtable slot 12 of CChatEventSink (RTTI) and 1 derived vtable(s).
int Obj_007AB330::FUN_007AB330(int a1, int a2, int a3, int a4) const
{
    return 0;
}

// FUNCTION: GAMEMD 0x7AB340
// Returns zero; pops its stack arguments. Vtable slot 25 of CChatEventSink (RTTI) and 1 derived vtable(s).
int Obj_007AB340::FUN_007AB340(int a1, int a2, int a3) const
{
    return 0;
}

// FUNCTION: GAMEMD 0x7AB350
// Slot 29 of CChatEventSink (RTTI).
long __stdcall FUN_007AB350(void* self, int a, long until)
{
    wchar_t text[200];

    if (!DAT_00B77DC1 && a == 0) {
        swprintf(text, FUN_00734E60("TXT_BANNEDTILL", NULL, DAT_0084A430, 0x2269), ctime(&until));
        FUN_005E2CD0(text, 0, (void*)FUN_0077D710, 0);
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7AB3C0
// Slot 31 of CChatEventSink (RTTI).
long __stdcall FUN_007AB3C0(void* self, int a, const char* name, int banned)
{
    if (!DAT_00B77DC1) {
        if (banned != 0) {
            FUN_005E2700(DAT_007EEF28, FUN_00734E60("TXT_CHAN_BAN", NULL, DAT_0084A430, 0x2276), FUN_00735120(name));
            return 0;
        }
        FUN_005E2700(DAT_007EEF28, FUN_00734E60("TXT_CHAN_UNBAN", NULL, DAT_0084A430, 0x2279), FUN_00735120(name));
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7AC4A0
// Returns zero; pops its stack arguments. Vtable slot 38 of CChatEventSink (RTTI) and 1 derived vtable(s).
int Obj_007AC4A0::FUN_007AC4A0(int a1, int a2, int a3) const
{
    return 0;
}

// FUNCTION: GAMEMD 0x7AC4B0
// Returns zero; pops its stack arguments. Vtable slot 39 of CChatEventSink (RTTI) and 1 derived vtable(s).
int Obj_007AC4B0::FUN_007AC4B0(int a1, int a2, int a3) const
{
    return 0;
}

// FUNCTION: GAMEMD 0x7AC4C0
// Returns zero; pops its stack arguments. Vtable slot 45 of CChatEventSink (RTTI) and 1 derived vtable(s).
int Obj_007AC4C0::FUN_007AC4C0(int a1, int a2, int a3) const
{
    return 0;
}

// FUNCTION: GAMEMD 0x7AC4D0
// Returns zero; pops its stack arguments. Vtable slot 46 of CChatEventSink (RTTI) and 1 derived vtable(s).
int Obj_007AC4D0::FUN_007AC4D0(int a1, int a2, int a3) const
{
    return 0;
}

// FUNCTION: GAMEMD 0x7AC4E0
// Returns zero; pops its stack arguments. Vtable slot 47 of CChatEventSink (RTTI) and 1 derived vtable(s).
int Obj_007AC4E0::FUN_007AC4E0(int a1, int a2, int a3) const
{
    return 0;
}

// FUNCTION: GAMEMD 0x7AC4F0
// Empty function.
void __cdecl FUN_007AC4F0()
{
}

// FUNCTION: GAMEMD 0x7AC5D0
void* WonlineStringDialogControl::DeletingDtor(unsigned int flags)
{
    this->~WonlineStringDialogControl();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x7AC630
void* CreateGameDialogControl::DeletingDtor(unsigned int flags)
{
    this->~CreateGameDialogControl();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x7AC9D0
bool Obj_007AC9D0::FUN_007AC9D0(Record_00B778E0** out, int index)
{
    if (index >= 0 && index < Count) {
        *out = &Items[index];
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x7ACA00
template struct GrowList<GrowListRecord6C>;

// FUNCTION: GAMEMD 0x7ACBD0
void __fastcall FUN_007ACBD0(ConstStoreObject* self)
{
    self->Head = 0;
}

// FUNCTION: GAMEMD 0x7ACD30
void Obj_007ACD30::FUN_007ACD30()
{
    for (int i = 0; i < Count; i++) {
        Items[i].~String_007B4620();
    }
    Count = 0;
}

// FUNCTION: GAMEMD 0x7AD2F0
void* Obj_7AD2F0::FUN_7AD2F0(unsigned int flags)
{
    FUN_007B46F0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x7AD310
void* Obj_7AD310::FUN_7AD310(unsigned int flags)
{
    FUN_007B46F0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x7AD330
void* Obj_7AD330::FUN_7AD330(unsigned int flags)
{
    FUN_007B46F0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x7AD350
void* Obj_7AD350::FUN_7AD350(unsigned int flags)
{
    FUN_007B46F0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7AD610
// Returns zero; pops its stack arguments. Vtable slot 6 of ATL::CComObject<CDownloadEventSink> (RTTI).
int Obj_007AD610::FUN_007AD610(int a1) const
{
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7AD790
template struct GrowList<GrowListRecord10C>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7ADB00
template struct GrowList<int>;

// FUNCTION: GAMEMD 0x7ADC60
bool Table_007ADC60::FUN_007ADC60(const String_007B4620& key, Entry_00B77908** out)
{
    return FindNode_007AE180(this, key, out);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7ADCD0
template struct ChainedHashTable<HashKeyHandle, HashValue6C>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7AE0C0
int HashTableIndex::FUN_007AE0C0(const void* key)
{
    int hash = this->Hash(key);

    return ((1 << this->BitWidth) - 1) & hash;
}

// FUNCTION: GAMEMD 0x7AE180
bool Table_007AE180::FUN_007AE180(const String_007B4620& key, Value_007AE180** out)
{
    return FindNode_007AE180(this, key, out);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7AE5B0
int HashTableIndex::FUN_007AE5B0(const void* key)
{
    int hash = this->Hash(key);

    return ((1 << this->BitWidth) - 1) & hash;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7AE5D0
template struct GrowList<GrowListHandle>;

// FUNCTION: GAMEMD 0x7AE7C0
bool Table_007AE180::FUN_007AE7C0(const String_007B4620& key, Value_007AE180** out)
{
    return FindNode_007AE180(this, key, out);
}

// FUNCTION: GAMEMD 0x7AE8E0
bool Table_007AE8E0::FUN_007AE8E0(const String_007B4620& key, Value_007AE8E0** out)
{
    return FindNode_007AE180(this, key, out);
}

// FUNCTION: GAMEMD 0x007AEC00
// Halves the table, chain link at +0x110.
template struct HashTable<Node_007AEC00>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7AECB0
int HashTableIndex::FUN_007AECB0(const void* key)
{
    int hash = this->Hash(key);

    return ((1 << this->BitWidth) - 1) & hash;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7AED20
void* Obj_7AED20::FUN_7AED20(unsigned int flags)
{
    FUN_007B46F0(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x007AEEC0
bool Obj_007AEEC0::FUN_007AEEC0()
{
    if (count < capacity)
        return false;
    int newCapacity = count * 2;
    if (newCapacity < 10)
        newCapacity = 10;
    int* block = new int[newCapacity];
    memset(block, 0, newCapacity * sizeof(int));
    if (data != 0)
        memcpy(block, data, count * sizeof(int));
    gg_free(data);
    capacity = newCapacity;
    data = block;
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x007AF000
bool Obj_007AF000::FUN_007AF000()
{
    if (count < capacity)
        return false;
    int newCapacity = count * 2;
    if (newCapacity < 10)
        newCapacity = 10;
    int* block = new int[newCapacity];
    memset(block, 0, newCapacity * sizeof(int));
    if (data != 0)
        memcpy(block, data, count * sizeof(int));
    gg_free(data);
    capacity = newCapacity;
    data = block;
    return true;
}
