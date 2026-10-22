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

extern CountedBlock DAT_00AC1DE0;
extern CountedBlock DAT_00B0BD50;
extern char DAT_00B2FF78;
extern CountedBlock DAT_00B72F38;
extern CountedBlock DAT_00B778D8;
extern CountedBlock DAT_00B73E10;
extern CountedBlock DAT_00B76AE0;
extern CountedBlock DAT_00B77900;
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

// FUNCTION: GAMEMD 0x785360
// Tail-calls a method on a global object.
void __cdecl FUN_00785360()
{
    FUN_00783C80(0, 0);
}

// FUNCTION: GAMEMD 0x796B20
// Empty function.
void __cdecl FUN_00796B20()
{
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

// FUNCTION: GAMEMD 0x7ACA00
template struct GrowList<GrowListRecord6C>;

// FUNCTION: GAMEMD 0x7ACBD0
void __fastcall FUN_007ACBD0(ConstStoreObject* self)
{
    self->Head = 0;
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
