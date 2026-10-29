#include "../_layout/ini_class.h"
#include <stdio.h>
#include <new.h>
#include <wchar.h>
#include <string.h>
// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | private-ref-cross-check
//   Original translation unit Ini.CPP. The name is the source-file string at 0x825bdc
//   in retail gamemd.exe v1.001, passed by the assert at 0x529316 inside this object's
//   code range (0x523697-0x52b7bf). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.
//
//   Every body below was written against the retail disassembly of the user's
//   gamemd.exe v1.001 read through the local Ghidra CLI.
//
// IndexClass — the lazily sorted {ID, Data} index. Bodies ascending by address.
//
// Six key/value-vector Grow instances, ordered ascending by retail address.
//
// Grow the vector by `extra` slots: allocate, copy the live elements across
// field by field, free the old block, and invalidate the cached lookup slot. A
// negative request and a failed allocation both report false without touching
// anything.
//
// The phrasing is the one already driven to 100% at 0x41C500 and is reproduced
// unchanged. The two details that matter are recorded there and hold here: the
// allocation is `new GrowPair[total]`, whose elided vector-constructor-iterator
// setup is retail's `DEC`/spill pair after the null check, and the copy is a
// whole-struct assignment through an explicit byte offset, which is what moves
// the pair as two dwords sharing one address computation and keeps the index a
// plain register. Count and Items are re-read every iteration rather than
// hoisted.
//
// Retail IPersist::GetClassID (slot 3 of each class's primary vtable) copies a
// 16-byte CLSID global to the caller and returns E_POINTER for a null pointer.
// The owning class of each address is read from the RTTI-named vtable that holds
// it in slot 3. Each class is declared here only as far as this one virtual
// (no layout is claimed); the bodies move into the canonical class once it exists.
//
// The four remaining identity tests, ordered ascending by retail address.
//
// The two conditions have to sit in one `&&` with the `true` inline: split
// into two early-return `if`s the failure block is duplicated and the score
// drops to 18.2%.
//
//   Reconstructed against retail gamemd.exe v1.001 at 0x526810; partial below.
//
//   YRpp.
//
//   YRpp.
//
//   cross-checked against YRpp (each
//   address/convention reconfirmed against the user's binary below).
//
// Translation unit: three CCINIClass/INIClass INI writers/queries, all pure
// __thiscall forwarders that touch NO member offset of `this` (confirmed: every
// referenced register is an incoming stack arg or the preserved `this` in ECX).
//
//   DATA:     GAMEMD 0x825BF8   "yes"   (WriteBool true literal)
//   DATA:     GAMEMD 0x825BF4   "no"    (WriteBool false literal)
//   DATA:     GAMEMD 0x81C000   "%d,%d" (Write2Integers format)
//   LIBRARY:  GAMEMD 0x7C8EF4   sprintf (CRT; cdecl; excluded from match target)
//
//   string is read out of the image at 0x81F0A8.
//
// reccmp annotations:
//   STRING:   GAMEMD 0x00825BAC  "%Xh"
//   STRING:   GAMEMD 0x00825BB0  "$%X"
//   STRING:   GAMEMD 0x00817F6C  "%d"
//
//   No /GX: the by-value TypeList parameter has a destructor, and /GX would
//   wrap the body in an unwind frame retail does not have (bare `SUB ESP`).
//   Read off retail gamemd.exe v1.001 at 0x525430: __fastcall with the hidden
//   result in ECX and the INI object in EDX, three stack arguments (section,
//   key, a 0x1C-byte TypeList<int> by value; `RET 0x24`); a 0x80-byte read
//   buffer filled by 0x528A10; tokens split on "," (0x817F70) by 0x7C9CC2;
//   each token resolved by 0x751520 (name -> record) and 0x7515C0 (record ->
//   index), appended through the inlined TypeList add; returned by the
//   out-of-line copy 0x477B60, or the default copied through 0x478720.
//
//   Read off retail gamemd.exe v1.001 at 0x52A4D0: __thiscall on an INI
//   section (`RET 4`); the twelve-byte hash state zeroed a dword at a time
//   and passed to 0x4A1DE0 with the name and its inlined strlen; the entry
//   index at `[ESI+0x2C]` (table), `[ESI+0x30]` (count), `[ESI+0x38]` (sorted
//   byte) and `[ESI+0x3C]` (cached node); qsort 0x7C8B48 with element width 8
//   and comparator 0x52B6A0; the search at 0x52B6D0 (__fastcall: table in
//   ECX, count in EDX, key pointer pushed); the fallback cell 0xB78830.

#include "../core/deleting_dtor_sweep.h"
#include "../network/transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

#include "../core/index_class.h"

// Grows the table to hold `amount` more entries, copying the live entries over
// node by node and dropping the cached node because the array moved. The new
// table is an array-new of nodes with a no-throw empty constructor, which is
// what leaves retail's dead "count minus one" local in the frame. Retail
// has this expanded into AddIndex, with its own early return for a negative
// amount surviving as the one conditional on the doubling path.
__forceinline bool IndexClass::IncreaseTableSize(int amount)
{
    if (amount < 0) return false;

    int total = IndexSize + amount;
    NodeElement* table = new NodeElement[total];
    if (table != 0) {

        for (int index = 0; index < IndexCount; index++) {
            table[index] = IndexTable[index];
        }

        ::operator delete(IndexTable);
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

#include "../core/pair_vector_grow_sweep.h"

#include <objidl.h>
#include "../_layout/side_class.h"
#include "../_layout/wave_class.h"
#include "../_layout/bullet_class.h"
#include "../_layout/script_class.h"
#include "../_layout/script_type_class.h"
#include "../ai/taction_class_methods.h"
#include "../_layout/tag_type_class.h"
#include "../_layout/task_force_class.h"
#include "../_layout/team_class.h"
#include "../_layout/team_type_class.h"
#include "../ai/tevent_class_methods.h"
#include "../_layout/trigger_class.h"
#include "../_layout/warhead_type_class.h"

// GLOBAL: GAMEMD 0x007E9660 -- CLSID of AircraftClass.
extern const CLSID DAT_007E9660;
// GLOBAL: GAMEMD 0x007E95B0 -- CLSID of AircraftTypeClass.
extern const CLSID DAT_007E95B0;
// GLOBAL: GAMEMD 0x007E98E0 -- CLSID of AirstrikeClass.
extern const CLSID DAT_007E98E0;
// GLOBAL: GAMEMD 0x007E9960 -- CLSID of AITriggerTypeClass.
extern const CLSID DAT_007E9960;
// GLOBAL: GAMEMD 0x007E99A0 -- CLSID of AlphaShapeClass.
extern const CLSID DAT_007E99A0;
// GLOBAL: GAMEMD 0x007E9670 -- CLSID of AnimClass.
extern const CLSID DAT_007E9670;
// GLOBAL: GAMEMD 0x007E9620 -- CLSID of AnimTypeClass.
extern const CLSID DAT_007E9620;
// GLOBAL: GAMEMD 0x007E9980 -- CLSID of NeuronClass.
extern const CLSID DAT_007E9980;
// GLOBAL: GAMEMD 0x007E96E0 -- CLSID of BulletClass.
extern const CLSID DAT_007E96E0;
// GLOBAL: GAMEMD 0x007E95D0 -- CLSID of BulletTypeClass.
extern const CLSID DAT_007E95D0;
// GLOBAL: GAMEMD 0x007E9900 -- CLSID of CampaignClass.
extern const CLSID DAT_007E9900;
// GLOBAL: GAMEMD 0x007E9930 -- CLSID of CellClass.
extern const CLSID DAT_007E9930;
// GLOBAL: GAMEMD 0x007E9890 -- CLSID of DiskLaserClass.
extern const CLSID DAT_007E9890;
// GLOBAL: GAMEMD 0x007E9940 -- CLSID of EMPulseClass.
extern const CLSID DAT_007E9940;
// GLOBAL: GAMEMD 0x007E9820 -- CLSID of FactoryClass.
extern const CLSID DAT_007E9820;
// GLOBAL: GAMEMD 0x007E9990 -- CLSID of FoggedObjectClass.
extern const CLSID DAT_007E9990;
// GLOBAL: GAMEMD 0x007E9680 -- CLSID of InfantryClass.
extern const CLSID DAT_007E9680;
// GLOBAL: GAMEMD 0x007E95A0 -- CLSID of InfantryTypeClass.
extern const CLSID DAT_007E95A0;
// GLOBAL: GAMEMD 0x007E9640 -- CLSID of IsometricTileClass.
extern const CLSID DAT_007E9640;
// GLOBAL: GAMEMD 0x007E95F0 -- CLSID of IsometricTileTypeClass.
extern const CLSID DAT_007E95F0;
// GLOBAL: GAMEMD 0x007E9AC0 -- CLSID of JumpjetLocomotionClass.
extern const CLSID DAT_007E9AC0;
// GLOBAL: GAMEMD 0x007E98F0 -- CLSID of LightSourceClass.
extern const CLSID DAT_007E98F0;
// GLOBAL: GAMEMD 0x007E98A0 -- CLSID of ParasiteClass.
extern const CLSID DAT_007E98A0;
// GLOBAL: GAMEMD 0x007E98C0 -- CLSID of RadSiteClass.
extern const CLSID DAT_007E98C0;
// GLOBAL: GAMEMD 0x007E97A0 -- CLSID of ScriptClass.
extern const CLSID DAT_007E97A0;
// GLOBAL: GAMEMD 0x007E97B0 -- CLSID of ScriptTypeClass.
extern const CLSID DAT_007E97B0;
// GLOBAL: GAMEMD 0x007E9AB0 -- CLSID of ShipLocomotionClass.
extern const CLSID DAT_007E9AB0;
// GLOBAL: GAMEMD 0x007E9910 -- CLSID of SideClass.
extern const CLSID DAT_007E9910;
// GLOBAL: GAMEMD 0x007E9870 -- CLSID of SlaveManagerClass.
extern const CLSID DAT_007E9870;
// GLOBAL: GAMEMD 0x007E9860 -- CLSID of SpawnManagerClass.
extern const CLSID DAT_007E9860;
// GLOBAL: GAMEMD 0x007E9580 -- CLSID of SuperClass.
extern const CLSID DAT_007E9580;
// GLOBAL: GAMEMD 0x007E9570 -- CLSID of SuperWeaponTypeClass.
extern const CLSID DAT_007E9570;
// GLOBAL: GAMEMD 0x007E9950 -- CLSID of Tactical.
extern const CLSID DAT_007E9950;
// GLOBAL: GAMEMD 0x007E9800 -- CLSID of TActionClass.
extern const CLSID DAT_007E9800;
// GLOBAL: GAMEMD 0x007E97C0 -- CLSID of TagClass.
extern const CLSID DAT_007E97C0;
// GLOBAL: GAMEMD 0x007E97D0 -- CLSID of TagTypeClass.
extern const CLSID DAT_007E97D0;
// GLOBAL: GAMEMD 0x007E9770 -- CLSID of TaskForceClass.
extern const CLSID DAT_007E9770;
// GLOBAL: GAMEMD 0x007E9760 -- CLSID of TeamClass.
extern const CLSID DAT_007E9760;
// GLOBAL: GAMEMD 0x007E9780 -- CLSID of TeamTypeClass.
extern const CLSID DAT_007E9780;
// GLOBAL: GAMEMD 0x007E9A90 -- CLSID of TeleportLocomotionClass.
extern const CLSID DAT_007E9A90;
// GLOBAL: GAMEMD 0x007E98D0 -- CLSID of TemporalClass.
extern const CLSID DAT_007E98D0;
// GLOBAL: GAMEMD 0x007E9810 -- CLSID of TEventClass.
extern const CLSID DAT_007E9810;
// GLOBAL: GAMEMD 0x007E9920 -- CLSID of TiberiumClass.
extern const CLSID DAT_007E9920;
// GLOBAL: GAMEMD 0x007E97E0 -- CLSID of TriggerClass.
extern const CLSID DAT_007E97E0;
// GLOBAL: GAMEMD 0x007E97F0 -- CLSID of TriggerTypeClass.
extern const CLSID DAT_007E97F0;
// GLOBAL: GAMEMD 0x007E9750 -- CLSID of TubeClass.
extern const CLSID DAT_007E9750;
// GLOBAL: GAMEMD 0x007E9A50 -- CLSID of TunnelLocomotionClass.
extern const CLSID DAT_007E9A50;
// GLOBAL: GAMEMD 0x007E96F0 -- CLSID of UnitClass.
extern const CLSID DAT_007E96F0;
// GLOBAL: GAMEMD 0x007E9590 -- CLSID of UnitTypeClass.
extern const CLSID DAT_007E9590;
// GLOBAL: GAMEMD 0x007E9650 -- CLSID of VoxelAnimClass.
extern const CLSID DAT_007E9650;
// GLOBAL: GAMEMD 0x007E9790 -- CLSID of VoxelAnimTypeClass.
extern const CLSID DAT_007E9790;
// GLOBAL: GAMEMD 0x007E99B0 -- CLSID of VeinholeMonsterClass.
extern const CLSID DAT_007E99B0;
// GLOBAL: GAMEMD 0x007E9A60 -- CLSID of WalkLocomotionClass.
extern const CLSID DAT_007E9A60;
// GLOBAL: GAMEMD 0x007E9840 -- CLSID of WarheadTypeClass.
extern const CLSID DAT_007E9840;
// GLOBAL: GAMEMD 0x007E9720 -- CLSID of WaveClass.
extern const CLSID DAT_007E9720;
// GLOBAL: GAMEMD 0x007E9850 -- CLSID of WaypointPathClass.
extern const CLSID DAT_007E9850;
// GLOBAL: GAMEMD 0x007E9830 -- CLSID of WeaponTypeClass.
extern const CLSID DAT_007E9830;

// Kept local: the canonical header reaches _layout/components.h, whose IndexClass collides with core/index_class.h in this TU.
// Kept local: the canonical header reaches _layout/components.h, whose IndexClass collides with core/index_class.h in this TU.

#include "../core/same_object_test_sweep.h"

#include "../core/trivial_tu100_methods.h"

#include "ccini_class_get_section_methods.h"

#include "ccini_class_key_count_methods.h"

#include "ccini_class_key_name_methods.h"

#include "ccini_class_methods.h"

// CRT sprintf: cdecl variadic, 4-arg call cleaned by the caller (ADD ESP,0x10).
extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);

#include "ccini_class_time_methods.h"

#include "ccini_class_unicode_methods.h"

#include "ccini_class_uublock_methods.h"

#include "ccini_class_write_integer_methods.h"

#include "ccini_class_type_list_methods.h"

// FUNCTION: GAMEMD 0x751520 (decl; reloc) -- name -> record, or 0.
void* FUN_00751520(const char* name);

// FUNCTION: GAMEMD 0x7515C0 (decl; reloc) -- record -> registry index.
int FUN_007515C0(void* record);

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/ini_nodes.h"
#include "../_layout/ini_index_defaults.h"

// The hash state the entry name is run through.
struct Crc_0052A4D0
{
    int A;   // +0x0000
    int B;   // +0x0004
    int C;   // +0x0008

    // FUNCTION: GAMEMD 0x4A1DE0 (decl; reloc) -- hash a block.
    int Hash(const char* data, int length);
};
GG_STATIC_ASSERT(sizeof(Crc_0052A4D0) == 0xC);

// One {key, entry} node of the section's sorted entry index.
struct EntryNode_0052A4D0
{
    int                 Key;     // +0x0000
    INIClass::INIEntry* Entry;   // +0x0004
};
GG_STATIC_ASSERT(sizeof(EntryNode_0052A4D0) == 8);

// LIBRARY: GAMEMD 0x7C8B48 (decl; reloc) -- CRT qsort.
extern "C" void __cdecl gg_qsort(void* base, unsigned int count, unsigned int size,
                                 int (__cdecl* compare)(const void*, const void*));

// FUNCTION: GAMEMD 0x52B6A0 (decl; reloc) -- key comparison.
int __cdecl FUN_0052B6A0(const void* a, const void* b);

// FUNCTION: GAMEMD 0x52B6D0 (decl; reloc) -- table search.
EntryNode_0052A4D0* FUN_0052B6D0(EntryNode_0052A4D0* items, int count, int* key);

// Read/write view of the observed INISection entry-index offsets; the
// canonical INISection (ini_nodes.h) has no declaration for this method.
struct INISectionEntryView
{
    char                 _pad000[0x2C];   // +0x0000
    EntryNode_0052A4D0*  Items;           // +0x002C
    int                  Count;           // +0x0030
    int                  Size;            // +0x0034
    char                 IsSorted;        // +0x0038
    char                 _pad039[3];      // +0x0039
    EntryNode_0052A4D0*  Cached;          // +0x003C

    // FUNCTION: GAMEMD 0x52A4D0
    INIClass::INIEntry* FindEntry(const char* name);

    __forceinline INIClass::INIEntry* const& Fetch(int key);
};
GG_STATIC_ASSERT(offsetof(INISectionEntryView, Items)    == 0x2C);
GG_STATIC_ASSERT(offsetof(INISectionEntryView, Count)    == 0x30);
GG_STATIC_ASSERT(offsetof(INISectionEntryView, IsSorted) == 0x38);
GG_STATIC_ASSERT(offsetof(INISectionEntryView, Cached)   == 0x3C);
GG_STATIC_ASSERT(offsetof(INIClass::INISection, EntryIndex) == 0x2C);

// The inlined second lookup: cached node, sort on demand, binary search,
// default cell when absent.
INIClass::INIEntry* const& INISectionEntryView::Fetch(int key)
{
    if (Count != 0) {
        if (Cached != 0 && Cached->Key == key) {
            return Cached->Entry;
        }
        if (!IsSorted) {
            gg_qsort(Items, Count, 8, FUN_0052B6A0);
            Cached = 0;
            IsSorted = 1;
        }
        int n = Count;
        EntryNode_0052A4D0* base = Items;
        while (n > 0) {
            int half = n / 2;
            EntryNode_0052A4D0* mid = base + half;
            if (mid->Key > key) {
                n = half;
            } else {
                if (mid->Key == key) {
                    if (mid != 0) {
                        Cached = mid;
                        return Cached->Entry;
                    }
                    break;
                }
                base = mid + 1;
                n = n + (-1 - half);
            }
        }
    }
    return DAT_00B78830;
}

#include "trivial_tu101_methods.h"

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// FUNCTION: GAMEMD 0x523C80
// Empty function.
void __cdecl FUN_00523C80()
{
}

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// FUNCTION: GAMEMD 0x5247A0
// Returns zero. Vtable slot 44 of InfantryTypeClass (RTTI).
int Obj_005247A0::FUN_005247A0() const
{
    return 0;
}

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// FUNCTION: GAMEMD 0x5247B0
// Tail-forwards to another function. Vtable slot 40 of InfantryTypeClass (RTTI).
void Obj_005247B0::FUN_005247B0()
{
    FUN_00711E80();
}

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// FUNCTION: GAMEMD 0x5247C0
// Tail-forwards to another function. Vtable slot 41 of InfantryTypeClass (RTTI).
void Obj_005247C0::FUN_005247C0()
{
    FUN_00711E90();
}

// Clamp of the third component of a three-integer record to a lower bound taken
// from a global object that is queried with the record (global at 0x87F7E8,
// query 0x578080). The record is returned through the hidden pointer (RET 8).
struct Triple_005247D0 {
    int unknown_00;
    int unknown_04;
    int unknown_08;
};
#include "../_layout/map_0087f7e8.h"
struct Obj_005247D0 {
    Triple_005247D0 FUN_005247D0(const Triple_005247D0* value);
};
// FUNCTION: GAMEMD 0x005247D0
Triple_005247D0 Obj_005247D0::FUN_005247D0(const Triple_005247D0* value)
{
    Triple_005247D0 local = *value;
    if (local.unknown_08 < DAT_0087F7E8.FUN_00578080(&local))
        local.unknown_08 = DAT_0087F7E8.FUN_00578080(&local);
    return local;
}

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// FUNCTION: GAMEMD 0x524D40
// Returns a constant. Vtable slot 11 of InfantryTypeClass (RTTI).
int Obj_00524D40::FUN_00524D40() const
{
    return 0x10;
}

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// FUNCTION: GAMEMD 0x524D50
// Returns a constant. Vtable slot 12 of InfantryTypeClass (RTTI).
int Obj_00524D50::FUN_00524D50() const
{
    return 0xED0;
}

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// FUNCTION: GAMEMD 0x524D60
// Member getter (dword). Vtable slot 16 of InfantryTypeClass (RTTI).
int Obj_00524D60::FUN_00524D60() const
{
    return unknown_DF8;
}

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// FUNCTION: GAMEMD 0x524EC0
// Returns its receiver.
Obj_00524EC0* Obj_00524EC0::FUN_00524EC0()
{
    return this;
}

// A growable array of dwords, assigned from another (slot 3 releases the old storage).
struct Vec_00524F20 {
    virtual void vf_00(); virtual void vf_01(); virtual void vf_02();
    virtual void Clear();
    int* unknown_04;
    int unknown_08;
    bool unknown_0C;
    bool unknown_0D;
    int unknown_10;
    int unknown_14;
    Vec_00524F20* FUN_00524F20(const Vec_00524F20& other);
};
// FUNCTION: GAMEMD 0x00524F20
Vec_00524F20* Vec_00524F20::FUN_00524F20(const Vec_00524F20& other)
{
    if (this != &other) {
        Clear();
        unknown_08 = other.unknown_08;
        if (unknown_08 != 0) {
            unknown_04 = new int[unknown_08];
            if (unknown_04 != 0) {
                unknown_0D = true;
                for (int i = 0; i < unknown_08; ++i)
                    unknown_04[i] = other.unknown_04[i];
            }
        } else {
            unknown_04 = 0;
            unknown_0D = false;
        }
    }
    unknown_10 = other.unknown_10;
    unknown_14 = other.unknown_14;
    return this;
}

// TU-WINDOW: before the proven start of this TU; it may belong to the previous object.
// FUNCTION: GAMEMD 0x525430
// Read a comma-separated list of record names as registry indices. Unknown
// names are skipped; a missing key returns the caller's default list.
TypeListInt FUN_00525430(CCINI_00475C70* ini, const char* section,
    const char* key, TypeListInt defaultValue)
{
    char buffer[128];

    if (ini->ReadString(section, key, STR_00889F64, buffer, sizeof(buffer))) {
        TypeListInt list(0, 0);

        for (char* token = FUN_007C9CC2(buffer, STR_00817F70);
             token != 0 && *token != '\0';
             token = FUN_007C9CC2(0, STR_00817F70)) {
            void* record = FUN_00751520(token);
            if (record != 0) {
                list.AddItem(FUN_007515C0(record));
            }
        }

        return TypeListInt(list, 0);
    }

    return defaultValue;
}

// FUNCTION: GAMEMD 0x526810
//
// Find a section by name. The name is hashed, the cached entry answers when
// it still matches, and otherwise the table is sorted on demand and
// searched. The search runs twice because the first pass only decides
// whether the name is there at all; a name that is not gives back the
// shared empty section.
//
// PARTIAL (3.3% by position; 119 instructions against retail's 120, one
// push and one branch polarity apart). The hash with its inlined strlen,
// the sort-on-demand, the search call, the second inlined binary search and
// every exit match in form. Two things were load-bearing: all three zero
// returns and both found returns are routed through one shared label each,
// which is how retail lays them out; and the search key is written into the
// hash state's own first dword and passed from there, which is what keeps
// the frame at twelve bytes. The residual is that retail defers its EBP
// push into the second lookup where cl emits it in the prologue — the
// banked deferred-callee-saved-push class — and everything after the
// prologue is shifted by it.
INIClass::INISection* INIClass::GetSection(const char* name)
{
    INISectionLookupView* view = reinterpret_cast<INISectionLookupView*>(this);
    if (name == 0) {
        goto missing;
    }

    {
        Crc_00526810 crc;
        crc.A = 0;
        crc.B = 0;
        crc.C = 0;
        int key = crc.Hash(name, strlen(name));

        if (view->Count == 0) {
            goto missing;
        }

        if (view->Cached == 0 || view->Cached->Key != key) {
            if (!view->IsSorted) {
                gg_qsort(view->Items, view->Count, 8, FUN_0052B720);
                view->Cached = 0;
                view->IsSorted = 1;
            }
            crc.A = key;
            Entry_00526810* found = FUN_0052B750(view->Items, view->Count, &crc.A);
            if (found == 0) {
                goto missing;
            }
            view->Cached = found;
        }

        if (view->Count != 0) {
            if (view->Cached != 0 && view->Cached->Key == key) {
                goto found;
            }
            if (!view->IsSorted) {
                gg_qsort(view->Items, view->Count, 8, FUN_0052B720);
                view->Cached = 0;
                view->IsSorted = 1;
            }
            int n = view->Count;
            Entry_00526810* base = view->Items;
            while (n > 0) {
                int half = n / 2;
                Entry_00526810* mid = base + half;
                if (mid->Key > key) {
                    n = half;
                } else {
                    if (mid->Key == key) {
                        if (mid != 0) {
                            view->Cached = mid;
                            goto found;
                        }
                        break;
                    }
                    base = mid + 1;
                    n = n + (-1 - half);
                }
            }
        }
        return DAT_00B7882C;

    found:
        return view->Cached->Section;
    }

missing:
    return 0;
}

// FUNCTION: GAMEMD 0x526950
// Member getter (dword).
int Obj_00526950::FUN_00526950() const
{
    return unknown_2C;
}

// FUNCTION: GAMEMD 0x526960
//
// Number of keys in a section. The section name is CRC'd, the section index
// is probed (IsPresent, then operator[] -- both inlined, so the probe runs
// twice), and the found section's key count is returned; a null name, an
// unknown section or an empty slot all answer zero.
int INIClass::GetKeyCount(const char* section)
{
    if (section != 0) {
        CRC_00526960 engine;
        int crc = engine(section, strlen(section));

        Index_00526960* index = reinterpret_cast<Index_00526960*>(&SectionIndex);
        if (index->IsPresent(crc)) {
            INIClass::INISection* sec = (*index)[crc];
            if (sec != 0)
                return sec->EntryIndex.IndexCount;
        }
    }

    return 0;
}

// FUNCTION: GAMEMD 0x526B00  INIClass::Reset (__thiscall)
// Drop the parsed section bookkeeping. Retail zeroes both dwords from a single
// XOR'd register and never touches the vptr.
void INIClass::Reset()
{
    unknown_04 = 0;
    unknown_08 = 0;
}

// FUNCTION: GAMEMD 0x526CC0
//
// Name of the index-th key of a section. The section name is CRC'd, the
// section index probed (IsPresent inlined: count test, archive probe, node
// search) and fetched; when the index is inside the section's key count the
// entry list is walked, counting down, until the wanted entry is reached and
// its name returned. Every miss answers null.
// The walk is written as retail's own shape rather than as a `while` over the
// three clauses. Retail tests the head once (`MOV EAX,[EAX+0x18]; TEST EAX,EAX`
// at 0x526D56), then the loop head is the `Next` load at 0x526D5D, and the back
// edge is an unconditional `JMP 0x526D5D` reached through a second null test
// that follows the advance. So the null test is peeled at entry and repeated at
// the bottom; it is not the leading clause of a three-way conjunction. Writing
// it that way puts the found block ahead of the shared zero tail exactly as
// retail has it, and the whole function falls out byte for byte.
//
// Measured alternatives: the three clauses as one `while` condition 74.0%, the
// same conjunction inside `while (1)` behind a single negation 68.8%, a
// `for (;;)` with explicit breaks in retail's order 70.9%, and a `do`/`while
// (node != 0)` 70.9%. Retail advances before it decrements (`MOV EAX,ECX;
// DEC EDX`); the other order also reaches 100%, so only the loop's shape is
// load-bearing.
const char* INIClass::GetKeyName(const char* section, int index)
{
    if (section != 0) {
        CRC_00526CC0 engine;
        int crc = engine(section, strlen(section));

        Index_00526CC0* indexView = reinterpret_cast<Index_00526CC0*>(&SectionIndex);
        if (indexView->IsPresent(crc)) {
            INIClass::INISection* sec = (*indexView)[crc];
            if (sec != 0 && index < sec->EntryIndex.IndexCount) {
                INIClass::INIEntry* node = sec->FirstEntry();
                if (node != 0) {
                    while (1) {
                        if (!(node->NextNode != 0 && node->PrevNode != 0)) {
                            break;
                        }
                        if (index == 0) {
                            return node->Entry;
                        }
                        node = static_cast<INIClass::INIEntry*>(node->NextNode);
                        index--;
                        if (node == 0) {
                            break;
                        }
                    }
                }
            }
        }
    }

    return 0;
}

// FUNCTION: GAMEMD 0x526E80
//
// Store a binary block under a section as base64 text: the section is
// cleared, a buffer straw over the block feeds a base64 straw, and each
// 70-character line is written under the keys "1", "2", ... until the straw
// runs dry. A null section or block, or a non-positive length, is refused.
// Both straws are stack objects built and torn down explicitly (banked
// stack-object rule); the chaining call goes through the base64 straw's
// vtable slot, which cl folds to the absolute slot address.
bool CCINI_00526E80::WriteUUBlock(const char* section, const void* block, int length)
{
    if (section == 0 || block == 0 || length < 1) {
        return false;
    }

    Clear(section, 0);

    BufferStraw_00526E80 straw;
    straw.ChainTo   = 0;
    straw.ChainFrom = 0;
    straw.Vtable    = &VT_007E61F0;
    straw.Buffer.Construct(block, length);
    straw.Index     = 0;
    straw.Vtable    = &VT_007E61E0;

    Base64Straw_00526E80 b64;
    b64.ChainTo   = 0;
    b64.ChainFrom = 0;
    b64.Control   = 0;
    b64.Counter   = 0;
    b64.Vtbl      = &VT_007EB764;
    (b64.*b64.Vtbl->At_004)(&straw);

    char line[71];
    char key[32];
    int  counter = 1;
    for (;;) {
        int len = b64.Get(line, sizeof(line) - 1);
        line[len] = 0;
        if (len == 0) {
            break;
        }
        sprintf(key, STR_00817F6C, counter);
        WriteString(section, key, line);
        counter++;
    }

    ((Straw*)&b64)->Straw::~Straw();
    reinterpret_cast<MemoryBuffer*>(&straw.Buffer)->Clear();
    ((Straw*)&straw)->Straw::~Straw();
    return true;
}

// FUNCTION: GAMEMD 0x5275C0  INIClass::WriteInteger (__thiscall, ret 0x10)
// Render an integer in one of three radix styles and hand it to WriteString.
// The selector is tested with a chain of `DEC EAX; JZ`, which is what VC6 emits
// for a `switch` over *small consecutive* labels — an if/else chain gives
// `CMP EAX,1` / `CMP EAX,2` instead and scores 76.3%. Note this is the opposite
// pull from SidebarClass::GetObjectTabIdx, where a switch over eleven *sparse*
// labels became a jump table and the if-chain was correct: the deciding factor
// is label density, not the source keyword.
bool INIClass::WriteInteger(const char* pSection, const char* pKey, int value, int format)
{
    char buffer[INI_INTEGER_BUFFER];

    switch (format) {
    case 1:
        sprintf(buffer, "%Xh", value);
        break;
    case 2:
        sprintf(buffer, "$%X", value);
        break;
    default:
        sprintf(buffer, "%d", value);
        break;
    }

    return WriteString(pSection, pKey, buffer);
}

int FUN_007B5440(int);
int FUN_007B7140(int);

struct Obj_005289E0 {
    void FUN_00528660(int, int, int);
    void FUN_005289E0(int a, int b, int c);
};
// FUNCTION: GAMEMD 0x005289E0
void Obj_005289E0::FUN_005289E0(int a, int b, int c)
{
    FUN_00528660(FUN_007B5440(a), FUN_007B5440(b), FUN_007B5440(c));
}

// FUNCTION: GAMEMD 0x528E00
//
// Write a Unicode string as a comma-separated list of hexadecimal code units.
// A scratch buffer of eight bytes per character (up to four hex digits, the
// comma, and slack) plus the terminator is allocated, each code unit is
// rendered with _itoa at the cursor and a "," appended, and the cursor is
// re-derived from the buffer start before the string pointer advances. The
// list then goes through WriteString and the buffer is freed. A null string or a failed allocation writes nothing and reports
// false.
//
// Two spellings are load-bearing. The allocation size is `n + sizeof(char)`
// with `n = wcslen * 8` in its own local: every form that adds a literal 1
// (`* 8 + 1`, `(x << 3) + 1`, `+= 1`, `++n`, `+ 1U`, `+ (string != 0)`) is
// fused by cl into one `LEA EAX,[EAX*8+1]`, where retail has `SHL EAX,3;
// INC EAX`; the sizeof term keeps the two operations apart. The terminator
// store goes through the cursor (`*cursor = '\0'` after `cursor = buffer`)
// so that cl emits the immediate `MOV byte ptr [EBP],0` (C6 45 00 00);
// written as `buffer[0] = 0` it substitutes the zero already held in BL for
// the false result (`MOV [EBP],BL`, 88 5D 00), which is the same bytes
// minus one and shifts every later jump target. The loop is a `while` with
// `string++` as its last statement.
bool INIClass::FUN_00528E00(const char* section, const char* key,
                                        const wchar_t* string)
{
    bool result = false;

    if (string != 0) {
        unsigned n = wcslen(string) * 8;
        char* buffer = (char*)FUN_007C8E17(n + sizeof(char));
        if (buffer != 0) {
            char* cursor = buffer;
            *cursor = '\0';
            while (*string != 0) {
                _itoa(*string, cursor, 16);
                strcat(cursor, STR_00817F70);
                cursor = buffer + strlen(buffer);
                string++;
            }
            result = this->WriteString(section, key, buffer);
            ::operator delete(buffer);
        }
    }

    return result;
}

struct Obj_00528ED0 {
    void FUN_00528E00(int, int, int);
    void FUN_00528ED0(int a, int b, int c);
};
// FUNCTION: GAMEMD 0x00528ED0
void Obj_00528ED0::FUN_00528ED0(int a, int b, int c)
{
    FUN_00528E00(FUN_007B5440(a), FUN_007B5440(b), FUN_007B7140(c));
}

// FUNCTION: GAMEMD 0x528F00
unsigned int INIClass::FUN_00528F00(const char* section, const char* key,
    const wchar_t* fallback, wchar_t* output, int maximum)
{
    char buffer[0x5000];
    if (!FUN_00528A10(section, key, 0, buffer, sizeof(buffer))) {
        wcsncpy(output, fallback, maximum);
        return wcslen(output);
    }

    char* token = strtok(buffer, STR_00817F70);
    wchar_t* cursor = output;
    while (token != 0 && maximum != 0) {
        unsigned int code;
        sscanf(token, "%x", &code); // STRING: GAMEMD 0x825BD4
        // Native stores only DX; sscanf failure is deliberately unchecked.
        *cursor++ = (wchar_t)code;
        token = strtok(0, STR_00817F70);
        --maximum;
    }
    *cursor = 0;
    return wcslen(output);
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x529560
// 0x529560  INIClass::WriteBool
//   Forwards to WriteString(pSection, pKey, bValue ? "yes" : "no"); the
//   incoming `this` stays in ECX (no reload), so cl emits a bare CALL.
// ---------------------------------------------------------------------------
bool INIClass::WriteBool(const char* pSection, const char* pKey, bool bValue)
{
    if (bValue) {
        return WriteString(pSection, pKey, "yes");
    }
    return WriteString(pSection, pKey, "no");
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x5297E0
// 0x5297E0  INIClass::Write2Integers
//   sprintf(buffer, "%d,%d", pValues[0], pValues[1]); then forwards the buffer
//   to WriteString. `this` is spilled to ESI across the cdecl sprintf call.
//   Frame: SUB ESP,0x38 == one 56-byte scratch buffer.
// ---------------------------------------------------------------------------
bool INIClass::Write2Integers(const char* pSection, const char* pKey, int* pValues)
{
    char buffer[56];
    sprintf(buffer, "%d,%d", pValues[0], pValues[1]);
    return WriteString(pSection, pKey, buffer);
}

// FUNCTION: GAMEMD 0x52A4D0
// Find an entry of this section by name: hash the name, answer from the
// cached node when it still matches, otherwise sort on demand and search.
// A name that is absent yields 0; the second (inlined) lookup falls back to
// the shared default entry cell.
INIClass::INIEntry* INISectionEntryView::FindEntry(const char* name)
{
    if (name == 0) {
        goto missing;
    }

    {
        Crc_0052A4D0 crc;
        crc.A = 0;
        crc.B = 0;
        crc.C = 0;
        int key = crc.Hash(name, strlen(name));

        if (Count == 0) {
            goto missing;
        }

        if (Cached == 0 || Cached->Key != key) {
            if (!IsSorted) {
                gg_qsort(Items, Count, 8, FUN_0052B6A0);
                Cached = 0;
                IsSorted = 1;
            }
            crc.A = key;
            EntryNode_0052A4D0* found = FUN_0052B6D0(Items, Count, &crc.A);
            if (found == 0) {
                goto missing;
            }
            Cached = found;
        }

        return Fetch(key);
    }

missing:
    return 0;
}

// FUNCTION: GAMEMD 0x52A940
//
// Write a tick count as an "hh:mm:ss" string. The value is divided by sixty
// three times in a row — ticks to seconds, seconds to minutes, minutes to
// hours — and the two lower fields are reduced modulo sixty. All three
// divisions come out as the same 0x88888889 magic-multiply, and the two
// remainders reuse the quotient already in hand.
//
// The remainders are spelled `q - (q / 60) * 60` rather than `q % 60`: VC6
// does not strength-reduce a signed `%` by a constant into the shared
// quotient, it emits a separate CDQ/IDIV, where retail has the LEA/SHL/SUB
// multiply-back off the quotient it already computed.
bool CCINI_0052A940::WriteTime(const char* section, const char* key, int value)
{
    char buffer[32];

    int seconds = value / 60;
    int minutes = seconds / 60;
    int hours   = minutes / 60;

    // STRING: GAMEMD 0x81F0A8 "%02d:%02d:%02d"
    sprintf(buffer, "%02d:%02d:%02d", hours, minutes - hours * 60, seconds - minutes * 60);

    return WriteString(section, key, buffer);
}

// FUNCTION: GAMEMD 0x52A9E0
// Scans one INI line, tracking the column (tabs advance to the next multiple of eight): the column of
// the first '=' (*eq), of the first visible character after it (*valueStart) and of a ';' comment
// (*comment). Unset columns come back as 0. Returns the text after the ';', or 0 when there is none.
char* __fastcall FUN_0052A9E0(unsigned char* line, int* eq, int* valueStart, int* comment)
{
    *eq = -1;
    char* rest = 0;
    *valueStart = -1;
    *comment = -1;
    unsigned char c = *line;
    int column = 0;
    while (c != 0) {
        if (*eq >= 0 && *valueStart < 0 && c > 0x20)
            *valueStart = column;
        c = *line;
        if (c == ';') {
            *comment = column;
            rest = (char*)(line + 1);
            break;
        }
        if (c != '\t') {
            if (c != '=') {
                column++;
            } else {
                if (*eq < 0)
                    *eq = column;
                column++;
            }
        } else {
            column = (column & ~7) + 8;
        }
        c = line[1];
        line++;
    }
    *eq = *eq < 0 ? 0 : *eq;
    *valueStart = *valueStart < 0 ? 0 : *valueStart;
    *comment = *comment < 0 ? 0 : *comment;
    return rest;
}

// FUNCTION: GAMEMD 0x52AE00
void* Obj_52AE00::FUN_52AE00(unsigned int flags)
{
    FUN_0052AB80(this);

    if (flags & 1) {
        ::operator delete(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x52AEA0
void* Obj_52AEA0::FUN_52AEA0(unsigned int flags)
{
    ((Straw*)this)->Straw::~Straw();

    if (flags & 1) {
        ::operator delete(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x52AEE0
void* Obj_52AEE0::FUN_52AEE0(unsigned int flags)
{
    ((Pipe*)this)->Pipe::~Pipe();

    if (flags & 1) {
        ::operator delete(this);
    }

    return this;
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

// Appends an entry, growing the table first when it is full. Growth doubles
// the table, or takes ten entries when there is none yet; the old contents are
// copied node by node, which is what retail's paired dword stores are, and
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
    return reinterpret_cast<void* const&>(DAT_00B78830);
}

// The search key lives in a local node (retail's 8-byte frame is that node: the
// key is its ID, its Data is never written), the shift is a whole-node copy, and
// the freed last slot is cleared by assigning a zeroed node.
//
// Removes an entry. The table is sorted and searched as in IsPresent, then the
// tail is shifted down one slot, the count drops and the freed last slot is
// zeroed. The cached node is dropped because everything past the hole moved.
// FUNCTION: GAMEMD 0x52B2B0
bool IndexClass::RemoveIndex(const int& id)
{
    NodeElement* nodeptr = 0;

    if (IndexCount != 0) {
        if (!IsSorted) {
            FUN_007C8B48(IndexTable, IndexCount, sizeof(NodeElement),
                         &IndexClassB::Comparator);
            Archive = 0;
            IsSorted = true;
        }

        int num = IndexCount;
        NodeElement elem;
        elem.ID = id;
        NodeElement* base = IndexTable;

        while (num > 0) {
            int half = num / 2;
            NodeElement* mid = &base[half];

            if (elem.ID < mid->ID) {
                num = half;
            } else {
                if (mid->ID == elem.ID) {
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
                    IndexTable[index - 1] = IndexTable[index];
                }

                IndexCount--;
                NodeElement zero;
                zero.ID = 0;
                zero.Data = 0;
                IndexTable[IndexCount] = zero;
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
    return reinterpret_cast<void* const&>(DAT_00B7882C);
}

// FUNCTION: GAMEMD 0x52B4D0
bool HandleHolder::FUN_0052B4D0(void** other)
{
    if (this->Held != 0 && *this->Held == *other) {
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x52B570
bool GrowPairVector::Grow_52B570(int extra)
{
    GrowPair* grown;
    int total;
    int i;

    if (extra < 0) goto fail;

    total = Capacity + extra;
    grown = new GrowPair[total];
    if (grown == 0) goto fail;

    for (i = 0; i < Count; i++) {
        int off = i * 8;
        GrowPair* src = (GrowPair*)((char*)Items + off);
        *(GrowPair*)((char*)grown + off) = *src;
    }

    delete[] Items;

    Items    = grown;
    Capacity = Capacity + extra;
    Cached   = 0;
    return true;

fail:
    return false;
}

// FUNCTION: GAMEMD 0x52B600
bool HandleHolder::FUN_0052B600(void** other)
{
    if (this->Held != 0 && *this->Held == *other) {
        return true;
    }

    return false;
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
