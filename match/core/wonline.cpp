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

// The node layout (netshare_slot_nodes.h) names a global LocalHandle (0xA8B380);
// <windows.h> declares a Win32 function of that name, which this unit never
// calls, so it is renamed for the duration of the include (as netshare_win.h does).
#define LocalHandle LocalHandle_Win32
#include <windows.h>
#undef LocalHandle
#include "../economy/netshare_slot_nodes.h"
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
    typedef unsigned (*HashFunc)(const Key& key);

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



// Retail PAUtConnInfoStruct RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "vector_class_operations.h"

struct tConnInfoStruct;

// VTABLE: GAMEMD 0x7F78A4 -- VectorClass<tConnInfoStruct*>.
template class VectorClass<tConnInfoStruct*>;
typedef VectorClass<tConnInfoStruct*> GgtConnInfoStructVectorClass;
GG_STATIC_ASSERT(offsetof(GgtConnInfoStructVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgtConnInfoStructVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgtConnInfoStructVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgtConnInfoStructVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F78C4 -- DynamicVectorClass<tConnInfoStruct*>.
template class DynamicVectorClass<tConnInfoStruct*>;
typedef DynamicVectorClass<tConnInfoStruct*> GgtConnInfoStructDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgtConnInfoStructDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgtConnInfoStructDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgtConnInfoStructDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgtConnInfoStructDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgtConnInfoStructDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgtConnInfoStructDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(tConnInfoStruct*) == 4);

// FUNCTION: GAMEMD 0x7AC970
// DynamicVectorClass<tConnInfoStruct*>::Clear

// FUNCTION: GAMEMD 0x7AC9A0
// DynamicVectorClass<tConnInfoStruct*>::Slot5

// FUNCTION: GAMEMD 0x7AC9C0
// VectorClass<tConnInfoStruct*>::Slot6

// FUNCTION: GAMEMD 0x7AD090
// VectorClass<tConnInfoStruct*>::operator==

// FUNCTION: GAMEMD 0x7AD0D0
// VectorClass<tConnInfoStruct*>::SetCapacity

// FUNCTION: GAMEMD 0x7AD180
// VectorClass<tConnInfoStruct*>::Clear

// FUNCTION: GAMEMD 0x7AD1B0
// VectorClass<tConnInfoStruct*>::FindItemIndex

// FUNCTION: GAMEMD 0x7AD1F0
// VectorClass<tConnInfoStruct*>::Slot5

// FUNCTION: GAMEMD 0x7AD210
// DynamicVectorClass<tConnInfoStruct*>::SetCapacity

// FUNCTION: GAMEMD 0x7AD2C0
// DynamicVectorClass<tConnInfoStruct*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x7AD370
// VectorClass<tConnInfoStruct*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x7AD3C0
// DynamicVectorClass<tConnInfoStruct*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x007B46F0 (decl; reloc) -- string object destructor (this in ECX).
extern void FUN_007B46F0(void* self);

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
    Member_7B46F0();    // FUNCTION: GAMEMD 0x7B4620 (decl; reloc)
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
    DialogControl();    // FUNCTION: GAMEMD 0x624110 (decl; reloc)
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
    WonlineStringDialogControl();
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

#include <new.h>
// ---- declarations used by the bodies below ----
#include "../_layout/elapsed_timer.h"
#include <mbstring.h>
#include "../platform/ccini_class_methods.h"
#include "../platform/ccfile_class.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new (decl; reloc)
extern int DAT_00B77EA8;

// Callbacks and helpers of the dialog runner below.
BOOL CALLBACK FUN_00796B90(HWND window, UINT message, WPARAM wparam, LPARAM lparam);   // FUNCTION: GAMEMD 0x796B90 (decl; reloc)
BOOL CALLBACK FUN_007A29E0(HWND window, UINT message, WPARAM wparam, LPARAM lparam);   // FUNCTION: GAMEMD 0x7A29E0 (decl; reloc)
// FUNCTION: GAMEMD 0x6241F0 (decl; reloc) -- runs the modal dialog `id` with `proc`.
int FUN_006241F0(int id, BOOL (CALLBACK* proc)(HWND, UINT, WPARAM, LPARAM), OwnerDraw::DialogControl* control);
// FUNCTION: GAMEMD 0x779940 (decl; reloc)
bool FUN_00779940();
// FUNCTION: GAMEMD 0x79C520 (decl; reloc)
bool FUN_0079C520(String_007B4620* name);
extern String_007B4620 DAT_00B76AC4;
extern char DAT_00B77DC2;
// FUNCTION: GAMEMD 0x780A90 (decl; reloc)
WideString_007B66C0 FUN_00780A90(const Entry_00B77908* entry);
// FUNCTION: GAMEMD 0x77D4C0 (decl; reloc)
bool FUN_0077D4C0(Entry_00B77908* entry);
// FUNCTION: GAMEMD 0x7B7ED0 (decl; reloc) -- the wide text of a narrow string.
WideString_007B66C0 FUN_007B7ED0(const String_007B4620& text);
extern char DAT_00A8B380[];
extern int DAT_00B779C0;
extern int DAT_00B779DC;
extern int DAT_007EEF34;
// STRING: GAMEMD 0x84B224
static const wchar_t DAT_0084B224[] = L"%hs %s";

// The picture cache at 0xAC4848.
struct PCXCache_00AC4848
{
    // FUNCTION: GAMEMD 0x6BA140 (decl; reloc)
    void* GetSurface(const char* filename, void* palette);
};
extern PCXCache_00AC4848 DAT_00AC4848;

extern int DAT_00A8B238;
extern int DAT_00B76B24;
extern unsigned int DAT_00B76B30;
extern int DAT_00A8B274;
extern char DAT_00A8B31C;
extern char DAT_00A8B262;
extern char DAT_00A8B258;

extern char DAT_00B76B44[];

int FUN_00788180();   // FUNCTION: GAMEMD 0x788180 (decl; reloc)
void FUN_00781480();  // FUNCTION: GAMEMD 0x781480 (decl; reloc)
// FUNCTION: GAMEMD 0x788800 (decl; reloc) -- RET 4: the wide text is a by-value argument.
int FUN_00788800(GrowListRecord10C* record, const String_007B4620& key, WideString_007B66C0 text);
extern int DAT_007EEF38;
// STRING: GAMEMD 0x84AFB0
static const wchar_t DAT_0084AFB0[] = L"[%hs] : %s";
// STRING: GAMEMD 0x84AFC8
static const wchar_t DAT_0084AFC8[] = L"%hs : %s";
extern int DAT_007EEF2C;
extern int DAT_007EEF30;
extern int DAT_007EEF3C;

extern CCINIClass DAT_008870C0;
extern int DAT_00B76234;
extern int DAT_00B779F0;
extern int DAT_00B779BC;
extern int DAT_00B7690C;
extern int DAT_00B77784;
extern bool DAT_00B76AF0;
extern bool DAT_00B73AD0;
void FUN_005EE1B0();   // FUNCTION: GAMEMD 0x5EE1B0 (decl; reloc)
bool FUN_0079BC80();   // FUNCTION: GAMEMD 0x79BC80 (decl; reloc)
// FUNCTION: GAMEMD 0x7B54B0 (decl; reloc) -- the length of a string, unsigned.
unsigned int FUN_007B54B0(const String_007B4620* text);
void FUN_005EE190();   // FUNCTION: GAMEMD 0x5EE190 (decl; reloc)

// Shared pieces of the dialog procedures.
int FUN_00622B50(HWND window, UINT message, WPARAM wparam, LPARAM lparam);   // FUNCTION: GAMEMD 0x622B50 (decl; reloc)
void FUN_006213A0(LPARAM drawItem);   // FUNCTION: GAMEMD 0x6213A0 (decl; reloc)
void FUN_00621E90(HWND window);       // FUNCTION: GAMEMD 0x621E90 (decl; reloc)
void FUN_00607FD0(HWND window);       // FUNCTION: GAMEMD 0x607FD0 (decl; reloc)

struct Obj_00AC1174;
struct Vtbl_00AC1174
{
    char unknown_00[0x10];
    long (__stdcall* At_10)(Obj_00AC1174* self);   // +0x10
};
GG_STATIC_ASSERT(offsetof(Vtbl_00AC1174, At_10) == 0x10);
struct Obj_00AC1174
{
    Vtbl_00AC1174* Vtbl;   // +0x00
};
extern Obj_00AC1174* DAT_00AC1174;
void FUN_00779830(bool value);                   // FUNCTION: GAMEMD 0x779830 (decl; reloc)
void FUN_00779C90(String_007B4620* name);        // FUNCTION: GAMEMD 0x779C90 (decl; reloc)
class DialogOwner_0079AE00
{
public:
    virtual void vf_0();
    virtual void vf_1(HWND window, int code);   // slot 1 (+0x04)
};
void FUN_005E2AC0();   // FUNCTION: GAMEMD 0x5E2AC0 (decl; reloc)
// FUNCTION: GAMEMD 0x7B7F90 (decl; reloc) -- the narrow text of a wide string.
String_007B4620 FUN_007B7F90(const WideString_007B66C0& text);

// Connection-state table: the pair of player slots of each connection, and the state
// each side holds.
struct SlotPair_00A8DC4C
{
    int First;    // +0x00
    int Second;   // +0x04
};
struct StatePair_00A8DE4C
{
    int FirstState;    // +0x00
    int SecondState;   // +0x04
};
extern int DAT_00A8E04C;
extern SlotPair_00A8DC4C DAT_00A8DC4C[];
extern StatePair_00A8DE4C DAT_00A8DE4C[];

// FUNCTION: GAMEMD 0x735060 (decl; reloc) -- converts `text` to wide characters into `out`.
void FUN_00735060(wchar_t* out, const char* text, int length);
extern int DAT_007EEF28;
// STRING: GAMEMD 0x83F328
static const char DAT_0083F328[] = "\n";
// STRING: GAMEMD 0x830174
static const wchar_t DAT_00830174[] = L"\n";
void FUN_00608440(HWND window);          // FUNCTION: GAMEMD 0x608440 (decl; reloc)
void FUN_00773E90(const char* label);    // FUNCTION: GAMEMD 0x773E90 (decl; reloc)
extern UINT DAT_0084A248;
// LIBRARY: GAMEMD 0x007C93E8 -- CRT free (caller cleanup).
extern "C" void __cdecl FUN_007C93E8(void* block);

void FUN_007A16B0(const char* text, bool flag);   // FUNCTION: GAMEMD 0x7A16B0 (decl; reloc)

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

extern CountedStringArray DAT_00B765F8;
// FUNCTION: GAMEMD 0x0077C5A0
void FUN_0077C5A0()
{
    for (int i = 0; i < DAT_00B765F8.count; ++i)
        FUN_007B46F0(DAT_00B765F8.data + i * 4);
    void* block = DAT_00B765F8.data;
    DAT_00B765F8.count = 0;
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

extern CountedStringArray DAT_00B736F8;
// FUNCTION: GAMEMD 0x0077C660
void FUN_0077C660()
{
    for (int i = 0; i < DAT_00B736F8.count; ++i)
        FUN_007B46F0(DAT_00B736F8.data + i * 4);
    void* block = DAT_00B736F8.data;
    DAT_00B736F8.count = 0;
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
CtorSeatObject* FUN_0077D1D0(CtorSeatObject* self)
{
    FUN_00624110(self);
    self->Vtbl = VTABLE_007F7624;

    return self;
}

// FUNCTION: GAMEMD 0x77D1F0
// VTABLE: GAMEMD 0x7F7624
void FUN_0077D1F0(SeatDtorObject* self)
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

// FUNCTION: GAMEMD 0x77DED0
// Loads the online options from the game's INI file.
void FUN_0077DED0()
{
    DAT_00B76234 = DAT_008870C0.FUN_005276D0("WOnline", "AllowPage", 1);
    DAT_00B779F0 = DAT_008870C0.FUN_005276D0("WOnline", "AllowFind", 1);
    DAT_00B779BC = DAT_008870C0.FUN_005276D0("WOnline", "LangFilter", 1);
    DAT_00B7690C = DAT_008870C0.FUN_005276D0("WOnline", "LobMusic", 1);
    DAT_00B77784 = DAT_008870C0.FUN_005276D0("WOnline", "ShowAll", 1);
    DAT_00B779DC = DAT_008870C0.FUN_005276D0("WOnline", "DisplayAsian", 1);
    DAT_00B779C0 = DAT_008870C0.FUN_005276D0("WOnline", "DisplayLatin", 1);
    DAT_00B76AF0 = DAT_008870C0.FUN_005295F0("WOnline", "DisplayBuddies", false);
    DAT_00B73AD0 = DAT_008870C0.FUN_005295F0("WOnline", "DisplayClan", false);
    FUN_005EE190();
}

// FUNCTION: GAMEMD 0x77DFD0
// Saves the online options to the game's INI file.
void FUN_0077DFD0()
{
    RawFileClass file("RA2MD.INI");
    DAT_008870C0.WriteInteger("WOnline", "AllowPage", DAT_00B76234, 0);
    DAT_008870C0.WriteInteger("WOnline", "AllowFind", DAT_00B779F0, 0);
    DAT_008870C0.WriteInteger("WOnline", "LangFilter", DAT_00B779BC, 0);
    DAT_008870C0.WriteInteger("WOnline", "LobMusic", DAT_00B7690C, 0);
    DAT_008870C0.WriteInteger("WOnline", "ShowAll", DAT_00B77784, 0);
    DAT_008870C0.WriteInteger("WOnline", "DisplayAsian", DAT_00B779DC, 0);
    DAT_008870C0.WriteInteger("WOnline", "DisplayLatin", DAT_00B779C0, 0);
    DAT_008870C0.WriteBool("WOnline", "DisplayBuddies", DAT_00B76AF0);
    DAT_008870C0.WriteBool("WOnline", "DisplayClan", DAT_00B73AD0);
    DAT_008870C0.WriteCCFile(&file, false);
    FUN_005EE1B0();
}

// FUNCTION: GAMEMD 0x77E110
void FUN_0077E110()
{
    if (DAT_00AC116C != NULL) {
        DAT_00AC116C->Vtbl->At_7C(DAT_00AC116C, DAT_00B779BC);
        DAT_00AC116C->Vtbl->At_68(DAT_00AC116C, DAT_00B779F0, DAT_00B76234);
    }
    FUN_005EE350(0);
    bool start = DAT_00B7690C != 0;
    ThemeUpdate_0077D7A0(start);
}

// STRING: GAMEMD 0x817F70
static const char DAT_00817F70[] = ",";

// FUNCTION: GAMEMD 0x77E820
// Splits `text` at commas into five numbers and a name.
String_007B4620& FUN_0077E820(char* text, int* a, int* b, int* c, int* d, int* e, String_007B4620* name)
{
    char* token = strtok(text, DAT_00817F70);
    *a = token ? atol(token) : 0;
    token = strtok(NULL, DAT_00817F70);
    *b = token ? atol(token) : 0;
    token = strtok(NULL, DAT_00817F70);
    *c = token ? atol(token) : 0;
    token = strtok(NULL, DAT_00817F70);
    *d = token ? atol(token) : 0;
    token = strtok(NULL, DAT_00817F70);
    *e = token ? atol(token) : 0;
    return *name = strtok(NULL, DAT_00817F70);
}

// A map list entry: the description text, then the map name at +0x58.
struct MapEntry_00A8B8CC
{
    wchar_t Description[0x2C];   // +0x00
    char Name[1];                // +0x58
};
GG_STATIC_ASSERT(offsetof(MapEntry_00A8B8CC, Name) == 0x58);
extern MapEntry_00A8B8CC** DAT_00A8B8CC;
extern int DAT_00A8B8D8;
// STRING: GAMEMD 0x82BC30
static const char DAT_0082BC30[] = "RandMap.Sed";
extern wchar_t DAT_00887734[];

// FUNCTION: GAMEMD 0x780D90
// The description of a map by name.
WideString_007B66C0 FUN_00780D90(String_007B4620* name)
{
    if (_stricmp(name->FUN_007B5440(), DAT_0082BC30) == 0) {
        return WideString_007B66C0(FUN_00734E60("TXT_RANDOM_MAP_DESCRIPTION", NULL, DAT_0084A430, 0xB9A));
    }
    for (int i = 0; i < DAT_00A8B8D8; i++) {
        MapEntry_00A8B8CC* entry = DAT_00A8B8CC[i];
        if (_stricmp(name->FUN_007B5440(), entry->Name) == 0) {
            return WideString_007B66C0(entry->Description);
        }
    }
    return WideString_007B66C0(DAT_00887734);
}

// FUNCTION: GAMEMD 0x781090
// Text for the list entry `index` of the lobby list box; the result is returned through
// the hidden return pointer (ECX under /Gr).
WideString_007B66C0 FUN_00781090(HWND list, int index)
{
    if (index == -1) {
        return WideString_007B66C0(FUN_00734E60("STT:LobbyListUsers", NULL, DAT_0084A430, 0xBEA));
    }
    int record = SendMessageA(list, 0x199, index, 0);
    if (record >= 0 && record < DAT_00B77900.count) {
        Entry_00B77908 entry;
        memset(&entry, 0, sizeof(entry));
        entry = DAT_00B77900.data[record];
        return FUN_00780A90(&entry);
    }
    return WideString_007B66C0(FUN_00734E60("STT:LobbyListUsers", NULL, DAT_0084A430, 0xBEF));
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
void FUN_007813E0(Obj_00781380* pairs, bool descending)
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
void FUN_00783070(void* object)
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

// FUNCTION: GAMEMD 0x7831A0
// Orders by flag (zero sorts last), then by key (larger first), then by the records'
// names, case-insensitively.
int __cdecl FUN_007831A0(const Item_007830C0* a, const Item_007830C0* b)
{
    if (a->Flag != b->Flag) return a->Flag ? -1 : 1;

    if (a->Key > b->Key) return -1;
    if (a->Key < b->Key) return 1;

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

// FUNCTION: GAMEMD 0x783A90
// The digit picture for 0..9.
void* FUN_00783A90(int digit)
{
    switch (digit) {
    case 0: return DAT_00AC4848.GetSurface("number0.pcx", NULL);
    case 1: return DAT_00AC4848.GetSurface("number1.pcx", NULL);
    case 2: return DAT_00AC4848.GetSurface("number2.pcx", NULL);
    case 3: return DAT_00AC4848.GetSurface("number3.pcx", NULL);
    case 4: return DAT_00AC4848.GetSurface("number4.pcx", NULL);
    case 5: return DAT_00AC4848.GetSurface("number5.pcx", NULL);
    case 6: return DAT_00AC4848.GetSurface("number6.pcx", NULL);
    case 7: return DAT_00AC4848.GetSurface("number7.pcx", NULL);
    case 8: return DAT_00AC4848.GetSurface("number8.pcx", NULL);
    case 9: return DAT_00AC4848.GetSurface("number9.pcx", NULL);
    }
    return NULL;
}

// The record whose rank picture is chosen: only the points at +0x0C are read.
struct RankHolder_00783B80
{
    int unknown_00;
    int unknown_04;
    int unknown_08;
    unsigned int Points;   // +0x0C
};
GG_STATIC_ASSERT(offsetof(RankHolder_00783B80, Points) == 0x0C);

// FUNCTION: GAMEMD 0x783B80
// The rank picture for a points total.
void* FUN_00783B80(RankHolder_00783B80* holder)
{
    if (holder == NULL)
        return NULL;
    unsigned int points = holder->Points;
    if (points > 2000)
        return DAT_00AC4848.GetSurface("comchief.pcx", NULL);
    if (points > 1500)
        return DAT_00AC4848.GetSurface("stargen.pcx", NULL);
    if (points > 1000)
        return DAT_00AC4848.GetSurface("general.pcx", NULL);
    if (points > 500)
        return DAT_00AC4848.GetSurface("briggenr.pcx", NULL);
    if (points > 250)
        return DAT_00AC4848.GetSurface("colonel.pcx", NULL);
    if (points > 150)
        return DAT_00AC4848.GetSurface("major.pcx", NULL);
    if (points > 80)
        return DAT_00AC4848.GetSurface("lieutena.pcx", NULL);
    if (points > 60)
        return DAT_00AC4848.GetSurface("sergeant.pcx", NULL);
    if (points > 31)
        return DAT_00AC4848.GetSurface("corporal.pcx", NULL);
    return DAT_00AC4848.GetSurface("private.pcx", NULL);
}

// FUNCTION: GAMEMD 0x785360
// Tail-calls a method on a global object.
void __cdecl FUN_00785360()
{
    FUN_00783C80(0, 0);
}

// GLOBAL: GAMEMD 0xB77E50 -- the SKU read from the registry; also formatted into the support links.
extern int DAT_00B77E50;
// GLOBAL: GAMEMD 0x8313B0 -- the game's registry key path under HKEY_LOCAL_MACHINE.
extern const char DAT_008313B0[];
// GLOBAL: GAMEMD 0xB73B34 -- a host name.
extern char DAT_00B73B34[];
// GLOBAL: GAMEMD 0xB76B0C -- that host's port.
extern int DAT_00B76B0C;

// Reads one DWORD value of a key under HKEY_LOCAL_MACHINE into `value`, which
// is left alone when the key or the value is missing. Expanded inline in
// 0x786270 and 0x786390.
static inline void ReadMachineDword(const char* keyPath, const char* name, DWORD* value)
{
    char path[256];
    HKEY key;
    DWORD type;
    DWORD size;

    if (keyPath != NULL && strlen(keyPath) != 0) {
        strcpy(path, keyPath);
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, path, 0, KEY_READ, &key) == ERROR_SUCCESS) {
            size = sizeof(DWORD);
            RegQueryValueExA(key, name, NULL, &type, (LPBYTE)value, &size);
            RegCloseKey(key);
        }
    }
}

// FUNCTION: GAMEMD 0x786270
// Reads the SKU value of the game's registry key, keeps its low byte and hands
// it to the first COM object, then hands the host and port to the second.
bool FUN_00786270()
{
    DWORD sku = 0;
    ReadMachineDword(DAT_008313B0, "SKU", &sku);

    DAT_00B77E50 = sku & 0xFF;
    if (DAT_00AC116C != NULL) {
        DAT_00AC116C->Vtbl->At_8C(DAT_00AC116C, sku);
    }
    if (DAT_00AC1170 != NULL) {
        FUN_004068E0("Get_WDT_State_Silent: WDTHost is %s, port is %d\n", DAT_00B73B34, DAT_00B76B0C);
        DAT_00AC1170->Vtbl->At_2C(DAT_00AC1170, DAT_00B73B34, DAT_00B76B0C, 3);
        return true;
    }
    return false;
}

// GLOBAL: GAMEMD 0xB77E75 -- set once the session below has been brought up.
extern bool DAT_00B77E75;
// GLOBAL: GAMEMD 0xB77DC0
extern bool DAT_00B77DC0;
// GLOBAL: GAMEMD 0x84A234 -- 0x2900 plus the SKU's low byte.
extern int DAT_0084A234;
// FUNCTION: GAMEMD 0x780110 (decl; reloc)
void FUN_00780110();
// FUNCTION: GAMEMD 0x785370 (decl; reloc) -- given the module handle.
int FUN_00785370(void* instance);

// FUNCTION: GAMEMD 0x786390
// One-time bring-up: builds the lobby slot nodes, resets the lobby, reads the
// SKU from the registry, creates the eighteen events and continues in 0x785370.
int FUN_00786390()
{
    if (DAT_00B77E75) return 1;

    DAT_00B77E75 = true;
    Build_Slot_Nodes();
    Clear_Lobby_Flags();
    Reset_Lobby();

    DWORD sku = 0;
    ReadMachineDword(DAT_008313B0, "SKU", &sku);
    sku &= 0xFF;
    DAT_00B77E50 = sku;
    DAT_0084A234 = sku + 0x2900;
    FUN_00780110();
    DAT_00B77DC0 = true;
    for (int i = 0; i < 18; i++) {
        DAT_00B73684[i] = CreateEventA(NULL, FALSE, FALSE, NULL);
    }
    return FUN_00785370(DAT_00B732F0);
}

// FUNCTION: GAMEMD 0x786D90
bool FUN_00786D90()
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
int FUN_00786E70(String_007B4620* name)
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

// GLOBAL: GAMEMD 0xB77DF8 -- the last error code of the online session.
extern unsigned int DAT_00B77DF8;
// GLOBAL: GAMEMD 0xB77AD0 -- the wide message text shown for that error.
extern wchar_t DAT_00B77AD0[];
// GLOBAL: GAMEMD 0x84B448 -- support-link format for code 0x80040076 (serialdup_%d).
extern const char DAT_0084B448[];
// GLOBAL: GAMEMD 0x84B484 -- support-link format for code 0x80040075 (serialbanned_%d).
extern const char DAT_0084B484[];
// GLOBAL: GAMEMD 0x84B4C4 -- support-link format for code 0x80040074 (disabled_%d).
extern const char DAT_0084B4C4[];
// GLOBAL: GAMEMD 0x84B500 -- support-link format for code 0x80040072 (banned_%d).
extern const char DAT_0084B500[];
// GLOBAL: GAMEMD 0x84B538 -- support-link format for code 0x80040078 (skuserialmismatch_%d).
extern const char DAT_0084B538[];
// GLOBAL: GAMEMD 0x84B57C -- support-link format for code 0x80040077 (serialunknown_%d).
extern const char DAT_0084B57C[];
// FUNCTION: GAMEMD 0x77DC90 (decl; reloc) -- opens a link (network/wonline.cpp).
void FUN_0077DC90(const char* url, int flag);

// FUNCTION: GAMEMD 0x786EF0
// Shows the stored error text. For the six serial/account error codes the box
// offers a support link, opened when the user answers 6 (IDYES).
bool FUN_00786EF0()
{
    char url[0x104];
    bool linked = false;

    if (DAT_00B77DF8 == 0x80040077 || DAT_00B77DF8 == 0x80040078
        || DAT_00B77DF8 == 0x80040072 || DAT_00B77DF8 == 0x80040074
        || DAT_00B77DF8 == 0x80040075 || DAT_00B77DF8 == 0x80040076) {
        linked = true;
        if (FUN_005E2CD0(DAT_00B77AD0, 4, (void*)FUN_0077D710, 0) == 6) {
            int account = DAT_00B77E50;
            switch (DAT_00B77DF8) {
            case 0x80040077:
                sprintf(url, DAT_0084B57C, account);
                break;
            case 0x80040078:
                sprintf(url, DAT_0084B538, account);
                break;
            case 0x80040072:
                sprintf(url, DAT_0084B500, account);
                break;
            case 0x80040074:
                sprintf(url, DAT_0084B4C4, account);
                break;
            case 0x80040075:
                sprintf(url, DAT_0084B484, account);
                break;
            case 0x80040076:
                sprintf(url, DAT_0084B448, account);
                break;
            }
            FUN_0077DC90(url, 1);
        }
    } else {
        FUN_005E2CD0(DAT_00B77AD0, 0, (void*)FUN_0077D710, 0);
    }
    return linked;
}

// FUNCTION: GAMEMD 0x788710
// Leaves the current channel, waits for the leave to finish and refocuses the chat box.
bool FUN_00788710(int mode, int flag)
{
    if (DAT_00B77DD0 != 0) {
        FUN_004068E0("Leave_Channel, channel %s type %d\n", DAT_00B76B44, DAT_00B76B10[0]);
        DAT_00AC116C->Vtbl->At_24(DAT_00AC116C);
        {
            WideString_007B66C0 text(FUN_00734E60("WOL:LeavingChannel", NULL, DAT_0084A430, 0x29D0));
            FUN_00792BE0(mode, &text, flag);
        }
        for (int i = 0; DAT_00B77DD0 != 0 && i < 150; i++) {
            Sleep(100);
            FUN_0077F900();
        }
        HWND dialog = FUN_00775940(0xC4);
        if (dialog != NULL) {
            DAT_00B77DC8 &= ~0x40u;
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
    return DAT_00B77DD0 == 0;
}

// STRING: GAMEMD 0x84B698
static const char DAT_0084B698[] = "zotclot9";

// FUNCTION: GAMEMD 0x788A30
int FUN_00788A30()
{
    int index = FUN_00788180();
    if (index != -1) {
        GrowListRecord10C record;
        if (index >= 0 && index < DAT_00B73E10.count) {
            record = ((GrowListRecord10C*)DAT_00B73E10.data)[index];
        }
        int failed;
        {
            String_007B4620 key(DAT_0084B698);
            failed = FUN_00788800(&record, key, FUN_00734E60("TXT_JOINLOB", NULL, DAT_0084A430, 0x2A01));
        }
        if (failed == 0) {
            HWND dialog = FUN_00775940(0x113);
            if (dialog != NULL) {
                SetFocus(GetDlgItem(dialog, 0x540));
            }
            FUN_00781480();
            return index;
        }
    }
    FUN_00781480();
    return -1;
}

// STRING: GAMEMD 0x8318B8
static const char DAT_008318B8[] = ":";

// FUNCTION: GAMEMD 0x789630
// The text of a record after its first ':' (the whole text when there is none).
String_007B4620 FUN_00789630(const char* record)
{
    String_007B4620 text(record + 0x18);
    String_007B4620 rest;
    int colon = text.FUN_007B5F10(0, DAT_008318B8, &rest);
    if (colon >= 0) {
        text.FUN_007B5020(0, colon + 1);
    }
    return text;
}

// FUNCTION: GAMEMD 0x78ABF0
void FUN_0078ABF0(char flag, const wchar_t* text)
{
    DAT_00B77E40 = flag;
    DAT_00B76230.FUN_007B7600(text);
}

// FUNCTION: GAMEMD 0x78DA30
BOOL CALLBACK FUN_0078DA30(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == 0x110 && lparam != 0) {
        SetWindowLongA(window, 8, ((int*)lparam)[1]);
    }
    int handled = FUN_00622B50(window, message, wparam, lparam);
    if (handled != 0)
        return handled;
    switch (message) {
    case 0x2B:
        FUN_006213A0(lparam);
        return 1;
    case 0xF:
        FUN_00621E90(window);
        FUN_00607FD0(window);
        ValidateRect(window, NULL);
        return 0;
    case 0x5F5:
        FUN_005E2CD0(FUN_00734E60("TXT_DOWNLOAD_FAILED", NULL, DAT_0084A430, 0x3959), 0, (void*)FUN_0077D710, 0);
        DAT_00AC1174->Vtbl->At_10(DAT_00AC1174);
        FUN_007757E0(window, 2);
        return 1;
    case 0x5F4:
        FUN_007757E0(window, 1);
        return 1;
    case 0x111:
        switch (wparam & 0xFFFF) {
        case 2:
            DAT_00AC1174->Vtbl->At_10(DAT_00AC1174);
            FUN_007757E0(window, 2);
            break;
        default:
            return 0;
        }
    case 0x14:
    case 0x110:
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x78F6B0
int FUN_0078F6B0(int id)
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

// FUNCTION: GAMEMD 0x78F720
// Locks the host controls of the lobby dialog.
void FUN_0078F720(HWND dialog)
{
    if (DAT_00A8B238 != 4)
        return;
    bool hostLocked;
    if (DAT_00B76B24 != 0)
        hostLocked = true;
    else
        hostLocked = ((DAT_00B76B30 >> 8) & 1) != 0;
    if (hostLocked) {
        EnableWindow(GetDlgItem(dialog, 0x552), 0);
        EnableWindow(GetDlgItem(dialog, 0x553), 0);
        EnableWindow(GetDlgItem(dialog, 0x597), 0);
        DAT_00A8B274 = 0;
        DAT_00A8B31C = 0;
        HWND check = GetDlgItem(dialog, 0x54E);
        SendMessageA(check, 0xF1, 1, 0);
        EnableWindow(check, 0);
        HWND other = GetDlgItem(dialog, 0x54B);
        SendMessageA(other, 0xF1, 1, 0);
        EnableWindow(other, 0);
        DAT_00A8B262 = 1;
        DAT_00A8B258 = 1;
    }
}

// FUNCTION: GAMEMD 0x791AA0
void FUN_00791AA0(void* window)
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

// FUNCTION: GAMEMD 0x792CF0
BOOL CALLBACK FUN_00792CF0(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    switch (message) {
    case 0x110:
        return 0;
    case 2:
        KillTimer(window, 0x45);
        return 0;
    case 0x2B:
        FUN_006213A0(lparam);
    case 0x14:
        return 1;
    case 0xF:
        FUN_00621E90(window);
        FUN_00607FD0(window);
        ValidateRect(window, NULL);
        return 0;
    case 0x111:
        switch (wparam & 0xFFFF) {
        case 0x58D:
            SetEvent(DAT_00B73684[0]);
            FUN_007757E0(window, 1);
            return 0;
        case 0x58E:
            FUN_00773E90("NetStatus");
            return 0;
        }
        break;
    case 0x113:
        if (wparam == 0x45) {
            ShowWindow(window, 5);
            KillTimer(window, 0x45);
        }
        return 0;
    case 0x497: {
        SendMessageA(window, 0x4A9, 0, 1);
        SetTimer(window, 0x45, DAT_0084A248, NULL);
        FUN_00608440(window);
        HWND item = GetDlgItem(window, 0x7A9);
        PostMessageA(item, 0x4D5, 0, 0);
        PostMessageA(item, 0x4D3, 0, 0);
        return 0;
    }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x792E90
void FUN_00792E90(LPARAM value)
{
    HWND dialog = FUN_00775940(0xC4);
    if (dialog != NULL) {
        SendDlgItemMessageA(dialog, 0x5B2, 0x4B2, 0, value);
    }
}

// FUNCTION: GAMEMD 0x792EC0
void FUN_00792EC0(unsigned int mask)
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
bool FUN_007930A0()
{
    Entry_00B77908* record = FirstFlaggedRecord();
    if (record == NULL) return false;
    return _stricmp(record->unknown_24, DAT_00B73E40.FUN_007B5440()) ? false : true;
}

// FUNCTION: GAMEMD 0x793120
bool FUN_00793120(String_007B4620* name)
{
    Entry_00B77908* record = FirstFlaggedRecord();
    if (record == NULL) return false;
    return _stricmp(record->unknown_24, name->FUN_007B5440()) ? false : true;
}

// FUNCTION: GAMEMD 0x7931A0
Entry_00B77908* FUN_007931A0()
{
    return FirstFlaggedRecord();
}

// FUNCTION: GAMEMD 0x7931F0
void FUN_007931F0(int slot)
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
void FUN_00793250()
{
    HWND window = FUN_00775700(DAT_00B732F0, 0x130, DAT_00B73550, (void*)FUN_00793280, 0);
    if (window != NULL) {
        FUN_00622820(window, 0x130);
    }
}

// FUNCTION: GAMEMD 0x793460
void FUN_00793460(int index, int value)
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
unsigned short FUN_00793710(int base, int offset, int unused, int spread)
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
    if (narrow < 0x400) {
        narrow = 0x400;
    }
    return narrow;
}

// FUNCTION: GAMEMD 0x793930
// Records the connection state between two named players.
void FUN_00793930(const char* from, const char* to, int state)
{
    int fromSlot = -1;
    int toSlot = -1;
    FUN_004068E0("Registering connection state from %s to %s. conn_state = %d\n", from, to, state);
    for (int i = 0; i < 8; i++) {
        if (_stricmp(FUN_007350C0(DAT_00A8DA90[i]), from) == 0) {
            fromSlot = i;
        }
        if (_stricmp(FUN_007350C0(DAT_00A8DA90[i]), to) == 0) {
            toSlot = i;
        }
    }
    for (int j = 0; j < DAT_00A8E04C; j++) {
        if (DAT_00A8DC4C[j].First == fromSlot && DAT_00A8DC4C[j].Second == toSlot) {
            DAT_00A8DE4C[j].FirstState = state;
            return;
        }
        if (DAT_00A8DC4C[j].First == toSlot && DAT_00A8DC4C[j].Second == fromSlot) {
            DAT_00A8DE4C[j].SecondState = state;
            return;
        }
    }
}

// FUNCTION: GAMEMD 0x793A10
void FUN_00793A10(const char* name, int port)
{
    FUN_004068E0("Player %s is telling us we should send to port %d\n", name, port & 0xFFFF);
    for (int i = 0; i < 8; i++) {
        if (_stricmp(FUN_007350C0(DAT_00A8DA90[i]), name) == 0) {
            DAT_00A8E050[i] = (short)port;
            return;
        }
    }
}

// FUNCTION: GAMEMD 0x793A70
// Sends the code string to the user of that name.
void FUN_00793A70(const char* name, unsigned short code)
{
    Entry_00B77908* entry = NULL;
    for (int i = 0; i < DAT_00B77900.count; i++) {
        if (i >= 0 && i < DAT_00B77900.count) {
            entry = &DAT_00B77900.data[i];
        }
        if (_stricmp(name, entry->unknown_24) == 0) {
            char text[0x100];
            text[0] = 'Z';
            text[1] = '4';
            sprintf(&text[2], "%d", code);
            FUN_004068E0("Sending string %s to user %s\n", text, name);
            DAT_00AC116C->Vtbl->At_38(DAT_00AC116C, entry, text);
        }
    }
}

// FUNCTION: GAMEMD 0x793B30
void FUN_00793B30(int digit, const char* text)
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

// One global holding eight receivers, eight timers and the running count (0xA8E1A4
// + 0x20 = 0xA8E1C4, + 0x60 = 0xA8E224). The receiver is filed under the count and a
// timer armed with 0x4B0 ticks is stored beside it.
struct Registry_00A8E1A4
{
    void* Owners[8];                  // +0x00
    ScenarioElapsedTimer Timers[8];   // +0x20
    int Count;                        // +0x80
};
GG_STATIC_ASSERT(offsetof(Registry_00A8E1A4, Timers) == 0x20);
GG_STATIC_ASSERT(offsetof(Registry_00A8E1A4, Count) == 0x80);
extern Registry_00A8E1A4 DAT_00A8E1A4;

struct Obj_00793CD0
{
    void FUN_00793CD0();
};

// FUNCTION: GAMEMD 0x793CD0
void Obj_00793CD0::FUN_00793CD0()
{
    DAT_00A8E1A4.Owners[DAT_00A8E1A4.Count] = this;
    DAT_00A8E1A4.Timers[DAT_00A8E1A4.Count] = ScenarioElapsedTimer(0x4B0);
    DAT_00A8E1A4.Count++;
}

// FUNCTION: GAMEMD 0x796B20
// Empty function.
void __cdecl FUN_00796B20()
{
}

// FUNCTION: GAMEMD 0x796B30
int FUN_00796B30()
{
    SimpleWonlineDialogControl control;
    int result = FUN_006241F0(0xFE, FUN_00796B90, &control);
    if (result < 0)
        return 0;
    return result;
}

#include "vector_class.h"
#include "vector_class_operations.h"

// GLOBAL: GAMEMD 0xA8DA74 -- the lobby's node vector (DynamicVectorClass<NodeNameType*>, vtable 0x7EE370).
extern DynamicVectorClass<NodeNameType*> DAT_00A8DA74;
// GLOBAL: GAMEMD 0xA8B54C
extern int DAT_00A8B54C;
// GLOBAL: GAMEMD 0xB7790C -- an int per node, indexed by 0xA8B54C.
extern int DAT_00B7790C[];
// GLOBAL: GAMEMD 0xA8BB1C -- a copy of the last address (12 bytes).
extern IPXAddressClass DAT_00A8BB1C;

// FUNCTION: GAMEMD 0x796FC0
// Builds a node named "PotatoToo" with the fixed address 0A:02:50:FA:00:00 and
// appends it to the node vector at 0xA8DA74.
void FUN_00796FC0()
{
    NodeNameType* node = new NodeNameType;
    FUN_00735060(node->Name, "PotatoToo", -1);
    node->unknown_7B = -1;
    node->unknown_4B = 1;
    node->unknown_53 = 2;

    NetworkNumberType network;
    NodeAddressType address;
    network.Number = 0;
    address.Node[5] = 0;
    address.Node[4] = 0;
    address.Node[3] = 0xFA;
    address.Node[2] = 0x50;
    address.Node[1] = 2;
    address.Node[0] = 0x0A;
    node->Address.FUN_0053ED20(network, address, 0);

    DAT_00A8DA74.AddItem(node);
    DAT_00B7790C[DAT_00A8B54C++] = 100;
    DAT_00A8BB1C = node->Address;
}

// FUNCTION: GAMEMD 0x7975E0
void FUN_007975E0()
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

// FUNCTION: GAMEMD 0x7982A0
void __stdcall FUN_007982A0(int count, int unused, Member_7B46F0* items)
{
    for (int i = 0; i < count; i++) {
        items[i].~Member_7B46F0();
    }
    gg_free(items);
}

// FUNCTION: GAMEMD 0x7982D0
// Waits up to `seconds` for one of `count` events, pumping in 100 ms slices;
// returns the signalled index (the event is reset) or 0x12 on timeout.
DWORD FUN_007982D0(int seconds, DWORD count)
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
void FUN_00798340()
{
    for (int i = 0; i < 18; i++) {
        ResetEvent(DAT_00B73684[i]);
    }
}

// FUNCTION: GAMEMD 0x799CD0
void FUN_00799CD0()
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
void FUN_00799D10()
{
    void* object;
    for (object = FUN_00775B10(); object != NULL; object = FUN_00775B10()) {
        FUN_007757E0(object, 0);
    }
}

// FUNCTION: GAMEMD 0x79AE00
BOOL CALLBACK FUN_0079AE00(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == 0x110 && lparam != 0) {
        SetWindowLongA(window, 8, ((int*)lparam)[1]);
    }
    int handled = FUN_00622B50(window, message, wparam, lparam);
    if (handled != 0)
        return handled;
    DialogOwner_0079AE00* owner = (DialogOwner_0079AE00*)GetWindowLongA(window, 8);
    switch (message) {
    case 0x14:
        return 1;
    case 0xF:
        FUN_00621E90(window);
        FUN_00607FD0(window);
        ValidateRect(window, NULL);
        return 1;
    case 0x2B:
        FUN_006213A0(lparam);
        return 1;
    case 0x111:
        switch (wparam & 0xFFFF) {
        case 1:
            FUN_00779C90(&DAT_00B73E40);
            owner->vf_1(window, 1);
            return 0;
        case 2:
            bool checked = IsDlgButtonChecked(window, 0x6F9) == 1;
            FUN_00779830(!checked);
            owner->vf_1(window, 2);
            return 0;
        }
        break;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x79BE70
void FUN_0079BE70()
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
bool FUN_0079BED0()
{
    if (DAT_00B76E24.Length() == 0) return false;

    int* value = FindValue_0079BED0(DAT_00B76990, DAT_00B76E24);
    if (value == NULL) return false;
    return *value < 0 || *value > 2;
}

// A 0x10C-byte record whose name sits at +0x34.
struct Record_0079F0A0
{
    int unknown_00[13];       // +0x00
    char Name[0xD8];          // +0x34
};
GG_STATIC_ASSERT(sizeof(Record_0079F0A0) == 0x10C);

struct Vec_0079F0A0
{
    int count;                // +0x00
    int unknown_04;           // +0x04
    Record_0079F0A0* data;    // +0x08
};

// FUNCTION: GAMEMD 0x79F0A0
// Finds the record named like `name`, copying it to `out`; clears `out` when none.
bool FUN_0079F0A0(String_007B4620* name, Vec_0079F0A0* list, Record_0079F0A0* out)
{
    memset(out, 0, sizeof(*out));
    for (int i = 0; i < list->count; i++) {
        if (i >= 0 && i < list->count) {
            *out = list->data[i];
        }
        if (_stricmp(out->Name, name->FUN_007B5440()) == 0) {
            return true;
        }
    }
    memset(out, 0, sizeof(*out));
    return false;
}

// FUNCTION: GAMEMD 0x79FC10
void FUN_0079FC10(int first, int second, int third)
{
    DAT_00B77E14 = third;
    DAT_00B73A20 = first;
    DAT_00B77D70 = second;
    DAT_00B77A88 = (int)time(NULL);
}

// FUNCTION: GAMEMD 0x7A0DD0
void FUN_007A0DD0(Entry_00B77908* entry)
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
void FUN_007A0E50()
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
void FUN_007A0EA0(const char* name, int ping)
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

// GLOBAL: GAMEMD 0xB77E28
extern int DAT_00B77E28;
// FUNCTION: GAMEMD 0x5E3720 (decl; reloc) -- sends a text request (netshare.cpp).
void FUN_005E3720(const char* text);

// FUNCTION: GAMEMD 0x7A0F40
// Builds "P<count>" followed by ",<name>,<ping>" for every record of the table
// at 0xB77908, recording each ping on the way, then sends the list.
void FUN_007A0F40()
{
    int count = DAT_00B77900.count;
    int ping;
    Entry_00B77908 entry;
    char list[256];
    char item[128];

    memset(&entry, 0, sizeof(entry));
    list[0] = 'P';
    list[1] = (char)('0' + count);
    list[2] = '\0';

    if (DAT_00B77E28 != 0) return;

    for (int i = 0; i < count; i++) {
        if (i >= 0 && i < DAT_00B77900.count) {
            entry = DAT_00B77900.data[i];
        }
        DAT_00AC1170->Vtbl->At_20(DAT_00AC1170, entry.unknown_18, &ping);
        sprintf(item, ",%s,%d", entry.unknown_24, ping);
        strcat(list, item);
        FUN_007A0EA0(entry.unknown_24, ping);
    }
    FUN_004068E0("Sending pings for users: %s\n", list);
    FUN_005E3720(list);
}

// FUNCTION: GAMEMD 0x7A2110
BOOL CALLBACK FUN_007A2110(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    switch (message) {
    case 0x14:
        return 1;
    case 0xF:
        FUN_00621E90(window);
        FUN_00607FD0(window);
        ValidateRect(window, NULL);
        return 1;
    case 2:
        KillTimer(window, 0);
        return 0;
    case 0x2B:
        FUN_006213A0(lparam);
        return 1;
    case 0x497:
        SetTimer(window, 0, 2000, NULL);
        return 0;
    case 0x113:
        if (wparam == 0) {
            FUN_005E2AC0();
        }
        return 0;
    case 0x111:
        switch (wparam & 0xFFFF) {
        case 0x709:
            DAT_00AC116C->Vtbl->At_2C(DAT_00AC116C, "start 4439,0,0,10000,10,1,1,1,3,Match,1,0,MP18S3.MAP,Match:xyzkerble,7,4,mshag,4,1,");
            return 0;
        case 0x708:
            DAT_00AC116C->Vtbl->At_2C(DAT_00AC116C, "start 4439,0,0,10000,10,1,1,1,3,Match,1,0,MP18S3.MAP,Match:mshag,4,1,xyzkerble,7,4");
            return 0;
        case 0x5C0:
            if (DAT_00B73A20 == 0xB) {
                FUN_007757E0(window, 0);
            } else {
                SetEvent(DAT_00B73684[0]);
            }
            return 0;
        }
        break;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7A2730
void FUN_007A2730()
{
    if (DAT_00AC116C != NULL) {
        DAT_00AC116C->Vtbl->At_3C(DAT_00AC116C, DAT_0084D690);
    }
}

// FUNCTION: GAMEMD 0x7A2750
void FUN_007A2750()
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

// FUNCTION: GAMEMD 0x7A27D0
void FUN_007A27D0()
{
    HWND parent = (HWND)FUN_00775B10();
    HWND control = GetDlgItem(parent, 0x59F);
    SendMessageA(control, 0x4DC, 0, 0);
}

// FUNCTION: GAMEMD 0x7A2800
void FUN_007A2800(int a, int b, int c)
{
    HWND window = FUN_00775940(0xC2);
    FUN_005EC880(window, a, b, c);
}

// FUNCTION: GAMEMD 0x7A2830
void FUN_007A2830(String_007B4620* name)
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

// FUNCTION: GAMEMD 0x7A2970
void FUN_007A2970()
{
    DAT_00B77DC1 = 0;
    if (!DAT_00B77DC2 && FUN_00779940() && FUN_0079C520(&DAT_00B76AC4)) {
        SimpleWonlineDialogControl control;
        FUN_006241F0(0x122, FUN_007A29E0, &control);
    }
}

// A critical-section holder: count cleared, section initialised, then the
// vtable seated by the derived class. Two such holders differ only in vtable.
struct LockBase_007A2FC0 {
    int unknown_04;
    CRITICAL_SECTION unknown_08;
    LockBase_007A2FC0() : unknown_04(0) { InitializeCriticalSection(&unknown_08); }
};
struct Obj_007A2FC0 : LockBase_007A2FC0 {
    virtual void vf_00();
    Obj_007A2FC0();
};
GG_STATIC_ASSERT(offsetof(Obj_007A2FC0, unknown_08) == 0x08);
// FUNCTION: GAMEMD 0x007A2FC0
Obj_007A2FC0::Obj_007A2FC0() {}

// The same holder in a second class (its own vtable).
struct Obj_007A41A0 : LockBase_007A2FC0 {
    virtual void vf_00();
    Obj_007A41A0();
};
GG_STATIC_ASSERT(offsetof(Obj_007A41A0, unknown_08) == 0x08);
// FUNCTION: GAMEMD 0x007A41A0
Obj_007A41A0::Obj_007A41A0() {}

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

// STRING: GAMEMD 0x8240B4
static const wchar_t DAT_008240B4[] = L"%s";

// FUNCTION: GAMEMD 0x7A5240
int __stdcall FUN_007A5240(void* unused, int a1, int a2)
{
    if (!DAT_00B77DC1) {
        wchar_t text[0x200];
        swprintf(text, DAT_008240B4, FUN_00734E60("TXT_SERVER_ERROR", NULL, DAT_0084A430, 0x1617));
        FUN_005E2700(-1, text);
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7A55F0
// Prints a message line by line.
int __stdcall FUN_007A55F0(void* unused, int slot, const char* message)
{
    if (slot < 0)
        return 0;
    char* copy = (char*)_mbsdup((const unsigned char*)message);
    for (char* line = strtok(copy, DAT_0083F328); line != NULL; line = strtok(NULL, DAT_0083F328)) {
        wchar_t text[0x400];
        FUN_00735060(text, line, -1);
        FUN_005E2700(DAT_007EEF28, text);
    }
    FUN_007C93E8(copy);
    FUN_005E2700(DAT_007EEF28, DAT_00830174);
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

// FUNCTION: GAMEMD 0x7A8DA0
int __stdcall FUN_007A8DA0(void* unused, int slot, int unused2, Entry_00B77908* entry, const char* text)
{
    if (!DAT_00B77DC1 && slot >= 0) {
        if (IsOnlineMode()) {
            if (entry->unknown_00[0] & 1) {
                FUN_007A16B0(text, false);
            }
        } else {
            bool shown;
            {
                String_007B4620 name(text);
                if (entry == NULL) {
                    shown = false;
                } else if (entry->unknown_00[0] & 1) {
                    shown = true;
                } else if (FUN_00775940(0xC2)) {
                    shown = true;
                } else if (FUN_00775940(0xC9)) {
                    shown = true;
                } else {
                    shown = DAT_00B779C0 != 0;
                }
            }
            if (shown && FUN_0077D4C0(entry)) {
                WideString_007B66C0 wide = FUN_007B7ED0(text);
                int channel = DAT_007EEF2C;
                if (entry->unknown_00[0] & 1)
                    channel = DAT_007EEF3C;
                if (_stricmp(DAT_00A8B380, entry->unknown_24) != 0) {
                    FUN_005E2700(channel, DAT_0084AFB0, entry->unknown_24, wide.FUN_007B7100());
                }
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7A8FC0
int __stdcall FUN_007A8FC0(void* unused, int slot, Entry_00B77908* entry, const char* text)
{
    if (!DAT_00B77DC1 && slot >= 0) {
        if (IsOnlineMode()) {
            if (entry->unknown_00[0] & 1) {
                FUN_007A16B0(text, true);
            } else {
                FUN_004068E0("Received message from non-channel owner %s: %s\n", entry->unknown_24, text);
            }
        } else {
            bool shown;
            {
                String_007B4620 name(text);
                if (entry == NULL) {
                    shown = false;
                } else if (entry->unknown_00[0] & 1) {
                    shown = true;
                } else if (FUN_00775940(0xC2)) {
                    shown = true;
                } else if (FUN_00775940(0xC9)) {
                    shown = true;
                } else {
                    shown = DAT_00B779C0 != 0;
                }
            }
            if (shown && FUN_0077D4C0(entry)) {
                WideString_007B66C0 wide = FUN_007B7ED0(text);
                int channel = DAT_007EEF30;
                if (entry->unknown_00[0] & 1)
                    channel = DAT_007EEF3C;
                if (_stricmp(DAT_00A8B380, entry->unknown_24) != 0) {
                    FUN_005E2700(channel, DAT_0084AFC8, entry->unknown_24, wide.FUN_007B7100());
                }
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7AAFB0
int __stdcall FUN_007AAFB0(void* unused, int slot, Entry_00B77908* entry, const char* text)
{
    if (!DAT_00B77DC1 && slot >= 0) {
        bool shown;
        {
            String_007B4620 name(text);
            if (entry == NULL) {
                shown = false;
            } else if (entry->unknown_00[0] & 1) {
                shown = true;
            } else if (FUN_00775940(0xC2)) {
                shown = true;
            } else if (FUN_00775940(0xC9)) {
                shown = true;
            } else {
                shown = DAT_00B779C0 != 0;
            }
        }
        if (shown && FUN_0077D4C0(entry)) {
            WideString_007B66C0 wide = FUN_007B7ED0(text);
            if (_stricmp(DAT_00A8B380, entry->unknown_24) != 0) {
                FUN_005E2700(DAT_007EEF34, DAT_0084B224, entry->unknown_24, wide.FUN_007B7100());
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7AB0A0
int __stdcall FUN_007AB0A0(void* unused, int slot, Entry_00B77908* entry, const wchar_t* text)
{
    if (!DAT_00B77DC1 && slot >= 0) {
        bool shown;
        {
            WideString_007B66C0 name(text);
            if (entry == NULL) {
                shown = false;
            } else if (entry->unknown_00[0] & 1) {
                shown = true;
            } else if (FUN_00775940(0xC2)) {
                shown = true;
            } else if (FUN_00775940(0xC9)) {
                shown = true;
            } else {
                shown = (name.FUN_007B7D90() ? DAT_00B779C0 : DAT_00B779DC) != 0;
            }
        }
        if (shown && FUN_0077D4C0(entry) && _stricmp(DAT_00A8B380, entry->unknown_24) != 0) {
            FUN_005E2700(DAT_007EEF34, DAT_0084B224, entry->unknown_24, text);
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7AB170
int __stdcall FUN_007AB170(void* unused, int slot, int unused2, Entry_00B77908* entry, const char* text)
{
    if (!DAT_00B77DC1 && slot >= 0) {
        bool shown;
        {
            String_007B4620 name(text);
            if (entry == NULL) {
                shown = false;
            } else if (entry->unknown_00[0] & 1) {
                shown = true;
            } else if (FUN_00775940(0xC2)) {
                shown = true;
            } else if (FUN_00775940(0xC9)) {
                shown = true;
            } else {
                shown = DAT_00B779C0 != 0;
            }
        }
        if (shown && FUN_0077D4C0(entry)) {
            WideString_007B66C0 wide = FUN_007B7ED0(text);
            if (_stricmp(DAT_00A8B380, entry->unknown_24) != 0) {
                FUN_005E2700(DAT_007EEF38, DAT_0084B224, entry->unknown_24, wide.FUN_007B7100());
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7AB260
int __stdcall FUN_007AB260(void* unused, int slot, int unused2, Entry_00B77908* entry, const wchar_t* text)
{
    if (!DAT_00B77DC1 && slot >= 0) {
        bool shown;
        {
            WideString_007B66C0 name(text);
            if (entry == NULL) {
                shown = false;
            } else if (entry->unknown_00[0] & 1) {
                shown = true;
            } else if (FUN_00775940(0xC2)) {
                shown = true;
            } else if (FUN_00775940(0xC9)) {
                shown = true;
            } else {
                shown = (name.FUN_007B7D90() ? DAT_00B779C0 : DAT_00B779DC) != 0;
            }
        }
        if (shown && FUN_0077D4C0(entry) && _stricmp(DAT_00A8B380, entry->unknown_24) != 0) {
            FUN_005E2700(DAT_007EEF38, DAT_0084B224, entry->unknown_24, text);
        }
    }
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

// FUNCTION: GAMEMD 0x7AC610
WonlineStringDialogControl::WonlineStringDialogControl()
{
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
void FUN_007ACBD0(ConstStoreObject* self)
{
    self->Head = 0;
}

// Files a copy of the key and value under the key's hash and doubles the table when
// the load passes the grow threshold at +0x28.
template<class KEY, class VALUE>
bool HashTable_006249A0<KEY, VALUE>::Insert(const KEY& key, const VALUE& value)
{
    Node* node = new Node;
    node->Key = key;
    node->Value = value;
    node->Next = NULL;

    int hash = this->Hash(&key);
    unsigned index = ((1 << this->BitWidth) - 1) & hash;
    Node* head = this->Buckets[index];
    this->Buckets[index] = node;
    if (head != NULL) {
        node->Next = head;
    }
    this->Count++;

    if ((float)this->Count / this->BucketCount >= this->unknown_28 && this->IsFixed != 1) {
        Grow();
    }
    return true;
}

// FUNCTION: GAMEMD 0x7ACBE0
template struct HashTable_006249A0<String_007B4620, int>;

// FUNCTION: GAMEMD 0x7ACD30
void Obj_007ACD30::FUN_007ACD30()
{
    for (int i = 0; i < Count; i++) {
        Items[i].~String_007B4620();
    }
    Count = 0;
}

#pragma warning(disable : 4661)
// Frees every node, empties the buckets and shrinks the table to its floor.
template<class KEY, class VALUE>
void HashTable_006249A0<KEY, VALUE>::Clear()
{
    for (unsigned i = 0; i < this->BucketCount; i++) {
        Node* node = this->Buckets[i];
        while (node != NULL) {
            Node* doomed = node;
            node = node->Next;
            delete doomed;
        }
        this->Buckets[i] = NULL;
    }
    this->Count = 0;

    for (;;) {
        unsigned minimum = this->MinBuckets;
        if (this->BucketCount <= minimum || this->IsFixed)
            break;
        Shrink();
    }
}

// FUNCTION: GAMEMD 0x7ACE60
template struct HashTable_006249A0<String_007B4620, int>;

// FUNCTION: GAMEMD 0x7ACF70
template struct HashTable_006249A0<String_007B4620, Value_007AE8E0>;

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

// FUNCTION: GAMEMD 0x7AD480
int __stdcall FUN_007AD480(void* unused, unsigned int done, unsigned int total, int unused2, int seconds)
{
    wchar_t text[200];
    text[0] = 0;
    SendDlgItemMessageA((HWND)FUN_00775B10(), 0x5C6, 0x402, done * 100 / total, 0);
    if (seconds > 0) {
        swprintf(text, FUN_00734E60("TXT_BYTES_W_TIME", NULL, DAT_0084A430, 0x142F), done, total, seconds);
    } else {
        swprintf(text, FUN_00734E60("TXT_BYTES_WO_TIME", NULL, DAT_0084A430, 0x1434), done, total);
    }
    if (time(0) - DAT_00B77EA8 != 0) {
        HWND control = GetDlgItem((HWND)FUN_00775B10(), 0x5C8);
        SendMessageA(control, 0x4B2, 0, (LPARAM)text);
        DAT_00B77EA8 = time(0);
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7AD580
int __stdcall FUN_007AD580(void* unused, int state)
{
    wchar_t text[200];
    text[0] = 0;
    switch (state) {
    case 2:
        swprintf(text, FUN_00734E60("TXT_CONNECTING", NULL, DAT_0084A430, 0x1447));
        break;
    case 4:
        swprintf(text, FUN_00734E60("TXT_FINDING_PATCH", NULL, DAT_0084A430, 0x144B));
        break;
    }
    HWND control = GetDlgItem((HWND)FUN_00775B10(), 0x5C8);
    SendMessageA(control, 0x4B2, 0, (LPARAM)text);
    return 0;
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

// Growth step and shrink step of a record array (count at +0x00, capacity at +0x04,
// heap block at +0x08) whose elements are 0x6C bytes.
struct Obj_007AD9D0 {
    int count;      // +0x00
    int capacity;   // +0x04
    GrowListRecord6C* data;   // +0x08
    bool FUN_007AD9D0();
    bool FUN_007ADA70();
};
GG_STATIC_ASSERT(offsetof(Obj_007AD9D0, data) == 0x08);

// FUNCTION: GAMEMD 0x7AD9D0
bool Obj_007AD9D0::FUN_007AD9D0()
{
    if (count < capacity)
        return false;
    int newCapacity = count * 2;
    if (newCapacity < 10)
        newCapacity = 10;
    GrowListRecord6C* block = new GrowListRecord6C[newCapacity];
    memset(block, 0, newCapacity * sizeof(GrowListRecord6C));
    if (data != 0)
        memcpy(block, data, count * sizeof(GrowListRecord6C));
    gg_free(data);
    capacity = newCapacity;
    data = block;
    return true;
}

// FUNCTION: GAMEMD 0x7ADA70
bool Obj_007AD9D0::FUN_007ADA70()
{
    if (count * 3 > capacity)
        return false;
    int newCapacity = capacity / 2;
    if (newCapacity < 10)
        newCapacity = 10;
    if (newCapacity >= capacity)
        return false;
    GrowListRecord6C* block = new GrowListRecord6C[newCapacity];
    if (data != 0)
        memcpy(block, data, count * sizeof(GrowListRecord6C));
    gg_free(data);
    data = block;
    capacity = newCapacity;
    return true;
}

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

// Unlinks the entry for `key`, copying its value out, and halves the table when the
// load falls to the shrink threshold (same body as the instantiations in
// hash_table_remove_methods.cpp).
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

// FUNCTION: GAMEMD 0x7AE1F0
template struct HashTable_006249A0<String_007B4620, int>;

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

// Shrink step of a plain-old-data array holder (count at +0x00, capacity at
// +0x04, heap block at +0x08): refused while the count exceeds a third of the
// capacity; otherwise the capacity is halved (floor of ten) and the live
// elements are copied into a block of the new size.
struct Obj_007AE730 {
    int count;     // +0x00
    int capacity;  // +0x04
    int* data;     // +0x08
    bool FUN_007AE730();
};
GG_STATIC_ASSERT(offsetof(Obj_007AE730, data) == 0x08);
// FUNCTION: GAMEMD 0x007AE730
bool Obj_007AE730::FUN_007AE730()
{
    if (count * 3 > capacity)
        return false;
    int newCapacity = capacity / 2;
    if (newCapacity < 10)
        newCapacity = 10;
    if (newCapacity >= capacity)
        return false;
    int* block = new int[newCapacity];
    if (data != 0)
        memcpy(block, data, count * sizeof(int));
    gg_free(data);
    data = block;
    capacity = newCapacity;
    return true;
}

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

// FUNCTION: GAMEMD 0x7AE950
template struct HashTable_006249A0<String_007B4620, Value_007AE8E0>;

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
