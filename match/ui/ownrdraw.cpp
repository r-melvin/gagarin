// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | private-ref-cross-check
//   Original translation unit ownrdraw.cpp. The name is the source-file string at 0x833730
//   in retail gamemd.exe v1.001, passed by the assert at 0x604079 inside this object's
//   code range (0x600340-0x628a6f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The four seven-byte constant stores, ordered ascending by retail address.
//
// Unrelated single classes with empty destructors.
//
// Scalar deleting destructors of classes whose destructor is empty. Each one
// stores the vtable of the class that declares the destructor (the derived
// classes add nothing to it), frees the object when bit 0 of the flag is set,
// and returns `this`. Retail's 32-byte shape:
//
//     MOV AL,[ESP+4]; PUSH ESI; MOV ESI,ECX; TEST AL,1; MOV [ESI],<vtable>
//     JZ +9; PUSH ESI; CALL 0x7C8B3D; ADD ESP,4; MOV EAX,ESI; POP ESI; RET 4
//
// Class names and the base relation come from the retail RTTI descriptors;
// the owning class of each body is the class whose vtable slot 0 holds it.
// Slot 0 is modelled as an ordinary virtual holding the deleting wrapper, as
// FileClass does in match/core/ram_file_class.h: these classes are never
// constructed in this translation unit, so cl would not emit their tables or
// a compiler-generated `??_G`. The classes are opaque views; no member is
// touched, so there is no layout to assert.
//
// Copy constructor (__thiscall, `ret 4`, returns this) of a record of two
// words (+0x00, +0x04) and a growable list of 0x18-byte entries at +0x08
// (count +0x08, capacity +0x0C, data +0x10: the list shape of
// window_list_collect_methods.cpp). Each entry holds an id (+0x00), two wide
// strings (+0x04, +0x08; default constructor 0x7B66C0, destructor 0x7B6760,
// assignment 0x7B68E0 -- the Obj_007B66D0 of
// core/wide_string_class.h, which does not declare the first two) and
// three words (+0x0C = -1, +0x10 = 0, +0x14 = -1 when default-built). The
// list's grow step (0x624810) and the entry copy constructor (0x6247D0) are
// called out of line here. No EH frame in retail although the staging entry
// has destructors, hence no /GX.
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
// The trivial leaves the big shape sweeps left behind: four loads of a
// container's +0x10 field, five loads of its +0x04 storage pointer, five
// constant-true returns with no arguments, three with one argument, three
// one-argument no-ops, and three stores of the ECX argument into a fixed
// global. Ordered ascending by retail address.
//
// 256-entry three-byte color table and its color element. Layout read off the
// bodies at 0x626070 (0x100 three-byte zeroing loop, then a 0xC0-dword copy)
// and 0x661350 (byte reads at +0/+1/+2). Names are descriptive placeholders.
//
// Draws a strip of randomly chosen 10x12 frames along the top (row y + 1)
// and bottom (row y + height - 16) edges of a rectangle, from two PCX
// images ("bits_i.pcx" with its palette, "bits_a.pcx" without) held by the
// PCX cache at 0xAC4848 (renderer/pcx_get_surface_methods.h names it
// PCX; GetSurface is 0x6BA140, the draw 0x6BA690 is __thiscall `ret 0x20`).
// Every sixth frame leaves a 10-pixel gap. __fastcall free function:
// rectangle in ECX, destination surface in EDX, plain `ret`.
//
// Growth step of a plain-old-data array holder (count at +0x00, capacity at
// +0x04, heap block at +0x08) that repeats at four addresses in different
// owners. Each address is a member of a placeholder owner `Obj_<ADDR>` that
// declares only those three fields. The new block is zero-filled, the live
// elements are copied across and the old block is freed.
//
// Retail RTTI names VectorClass over RGBClass and HSVClass (3-byte elements). HSVClass compares through
// two out-of-line bodies: operator!= at 0x517590 (thiscall) and operator== at 0x5175D0 (fastcall).
//
//   LIBRARY: GAMEMD 0x7C8E17  operator new  (CRT; reloc)
//
//   Bytes matched against the user's retail gamemd.exe v1.001 at 0x600CA0,
//   0x6015E0, 0x601D20 and 0x602490. Every constant below was extracted from
//   the disassembly in comparison order; none of it is guessed.
//
//   GLOBAL:   GAMEMD 0xAC1B00  the dialog-type hash table
//   GLOBAL:   GAMEMD 0xA8B238  the session object the last guard reads
//   GLOBAL:   GAMEMD 0x7E13B4  __imp__GetDlgCtrlID
//
//   GLOBAL:   GAMEMD 0x7E14EC  __imp__GetParent
//   GLOBAL:   GAMEMD 0x7E14F0  __imp__GetNextDlgTabItem
//   GLOBAL:   GAMEMD 0x7E13CC  __imp__SetFocus
//
//   Every global address and branch reconfirmed below from the disassembly;
//   names cross-checked against YRpp.
//
// reccmp annotation:
//   GLOBAL:   GAMEMD 0xA8B238   SessionGameMode  (int; ==0 or ==5 -> gate out)
//   GLOBAL:   GAMEMD 0xA8D60E   InhibitFlag      (byte; nonzero -> gate out)
//   GLOBAL:   GAMEMD 0xA8DAB4   InhibitWord      (int;  nonzero -> gate out)
//
// Disassembly of 0x623120 (len 0x42, ends at the RET @0x623161):
//   CALL 0x5D4D50               ; result ignored
//   MOV  EAX,[0xA8B238]         ; SessionGameMode
//   TEST EAX,EAX / JZ  gateout  ; == 0
//   CMP  EAX,5    / JZ  gateout  ; == 5
//   MOV  AL,[0xA8D60E] / JNZ gateout ; byte != 0
//   MOV  EAX,[0xA8DAB4]/ JNZ gateout ; int  != 0
//   CALL 0x55CBF0 / JNZ false   ; if predicate A -> return false
//   CALL 0x55D360 / JZ  false   ; if !predicate B -> return false
//   MOV  AL,1 / RET             ; return true
// gateout: CALL 0x48D080 (CallBack), fall through to
// false:   XOR AL,AL / RET      ; return false

#include "../core/const_store_leaf_sweep.h"

// VTABLE: GAMEMD 0x7E35A8
class Animate
{
public:
    ~Animate() {}
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x7EF720
namespace OwnerDraw {
class DialogControl
{
public:
    ~DialogControl() {}
    virtual void* DeletingDtor(unsigned int flags);
};
}


// VTABLE: GAMEMD 0x7F0954
class ReferenceCounted
{
public:
    ~ReferenceCounted() {}
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x7EA57C
class VersionClass
{
public:
    ~VersionClass() {}
    virtual void* DeletingDtor(unsigned int flags);
};

// VTABLE: GAMEMD 0x007EF738
namespace OwnerDraw {
class SimpleDialogControl : public DialogControl
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};
}

#include "../core/empty_function_family_methods.h"

#include <new.h>
#include <string.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class WideString_006255F0
{
public:
    unsigned short* Buffer;   // +0x00

    // FUNCTION: GAMEMD 0x7B66C0 (decl; reloc)
    WideString_006255F0();
    // FUNCTION: GAMEMD 0x7B6760 (decl; reloc)
    ~WideString_006255F0();
    // FUNCTION: GAMEMD 0x7B68E0 (decl; reloc)
    WideString_006255F0& operator=(const WideString_006255F0& other);
};
GG_STATIC_ASSERT(sizeof(WideString_006255F0) == 4);

struct ListEntry_006255F0
{
    int Id;                       // +0x00
    WideString_006255F0 Name;     // +0x04
    WideString_006255F0 Text;     // +0x08
    int unknown_0C;               // +0x0C
    int unknown_10;               // +0x10
    int unknown_14;               // +0x14

    ListEntry_006255F0() { Id = 0; unknown_0C = -1; unknown_10 = 0; unknown_14 = -1; }
    // FUNCTION: GAMEMD 0x6247D0 (decl; reloc)
    ListEntry_006255F0(const ListEntry_006255F0& other);
};
GG_STATIC_ASSERT(offsetof(ListEntry_006255F0, Name) == 0x04);
GG_STATIC_ASSERT(offsetof(ListEntry_006255F0, Text) == 0x08);
GG_STATIC_ASSERT(offsetof(ListEntry_006255F0, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(ListEntry_006255F0, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(ListEntry_006255F0, unknown_14) == 0x14);
GG_STATIC_ASSERT(sizeof(ListEntry_006255F0) == 0x18);

class EntryList_006255F0
{
public:
    int Count;                   // +0x00
    int Capacity;                // +0x04
    ListEntry_006255F0* Data;    // +0x08

    EntryList_006255F0() : Count(0), Capacity(0), Data(NULL) {}

    // FUNCTION: GAMEMD 0x624810 (decl; reloc)
    void Grow();

    void Clear()
    {
        for (int index = 0; index < Count; index++) {
            Data[index].~ListEntry_006255F0();
        }
        Count = 0;
    }

    void Get(int index, ListEntry_006255F0& entry) const
    {
        if (index >= 0 && index < Count) {
            entry = Data[index];
        }
    }

    void Insert(int index, const ListEntry_006255F0& entry)
    {
        if (Count >= Capacity) Grow();
        if (index < Count) {
            memmove(&Data[index + 1], &Data[index], (Count - index) * sizeof(ListEntry_006255F0));
        }
        new (&Data[index]) ListEntry_006255F0(entry);
        Count++;
    }

    void Add(const ListEntry_006255F0& entry)
    {
        int index = Count;
        if (Count >= Capacity) Grow();
        Insert(index, entry);
    }
};

class EntryRecord_006255F0
{
public:
    int unknown_00;              // +0x00
    int unknown_04;              // +0x04
    EntryList_006255F0 List;     // +0x08

    EntryRecord_006255F0(const EntryRecord_006255F0& other);
};
GG_STATIC_ASSERT(offsetof(EntryRecord_006255F0, List) == 0x08);

extern "C" void __cdecl gg_free(void*);



// Retail PAVColorScheme RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "../core/vector_class_operations.h"

class ColorScheme;

// VTABLE: GAMEMD 0x7EF7B0 -- VectorClass<ColorScheme*>.
template class VectorClass<ColorScheme*>;
typedef VectorClass<ColorScheme*> GgColorSchemeVectorClass;
GG_STATIC_ASSERT(offsetof(GgColorSchemeVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgColorSchemeVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgColorSchemeVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgColorSchemeVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EF790 -- DynamicVectorClass<ColorScheme*>.
template class DynamicVectorClass<ColorScheme*>;
typedef DynamicVectorClass<ColorScheme*> GgColorSchemeDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgColorSchemeDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgColorSchemeDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgColorSchemeDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgColorSchemeDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgColorSchemeDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgColorSchemeDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(ColorScheme*) == 4);

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x627D20
// DynamicVectorClass<ColorScheme*>::Clear

// FUNCTION: GAMEMD 0x627D50
// DynamicVectorClass<ColorScheme*>::Slot5

// FUNCTION: GAMEMD 0x627D70
// VectorClass<ColorScheme*>::Slot6

// FUNCTION: GAMEMD 0x627E10
// VectorClass<ColorScheme*>::operator==

// FUNCTION: GAMEMD 0x627E50
// VectorClass<ColorScheme*>::SetCapacity

// FUNCTION: GAMEMD 0x627F00
// VectorClass<ColorScheme*>::Clear

// FUNCTION: GAMEMD 0x627F30
// VectorClass<ColorScheme*>::FindItemIndex

// FUNCTION: GAMEMD 0x627F70
// VectorClass<ColorScheme*>::Slot5

// FUNCTION: GAMEMD 0x627F90
// DynamicVectorClass<ColorScheme*>::SetCapacity

// FUNCTION: GAMEMD 0x628040
// DynamicVectorClass<ColorScheme*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x6285F0
// VectorClass<ColorScheme*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x628640
// DynamicVectorClass<ColorScheme*>::scalar deleting destructor

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

#include "../core/hash_bucket_mask_sweep.h"

#include "../core/leftover_trivial_leaf_sweep.h"

#include "../_rt/gg_static_assert.h"
#include <stddef.h>

struct ColorRGB_00661350
{
    unsigned char unknown_00;   // +0x00
    unsigned char unknown_01;   // +0x01
    unsigned char unknown_02;   // +0x02

    ColorRGB_00661350() : unknown_00(0), unknown_01(0), unknown_02(0) {}

    // retail thiscall helper, matched elsewhere in main as a separate view.
    void Blend(int ratio, const ColorRGB_00661350& target);
    int Difference(const ColorRGB_00661350& other) const;
};

GG_STATIC_ASSERT(offsetof(ColorRGB_00661350, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(ColorRGB_00661350, unknown_01) == 0x01);
GG_STATIC_ASSERT(offsetof(ColorRGB_00661350, unknown_02) == 0x02);
// 0x626070 steps the element loop by 3.
GG_STATIC_ASSERT(sizeof(ColorRGB_00661350) == 0x03);

// GLOBAL: GAMEMD 0x00A83CD9 -- fixed target color pushed by 0x626170.
extern ColorRGB_00661350 DAT_00A83CD9;

struct ColorTable_00626070
{
    ColorRGB_00661350 Colors[256];   // +0x000

    ColorTable_00626070(const ColorTable_00626070& other);

    const ColorRGB_00661350& operator[](int index) const { return Colors[index % 256]; }

    void FUN_00626120(int ratio, const ColorTable_00626070& target);
    void FUN_00626170(int ratio, const char* marks);
    void FUN_006261B0(int ratio, const ColorTable_00626070& target, const char* marks);
    int Nearest(const ColorRGB_00661350& color) const;
};

GG_STATIC_ASSERT(offsetof(ColorTable_00626070, Colors) == 0x000);

#include <stdlib.h>
#include "../_rt/gg_static_assert.h"

struct Rect_00621D30
{
    int X;        // +0x00
    int Y;        // +0x04
    int Width;    // +0x08
    int Height;   // +0x0C
};
GG_STATIC_ASSERT(sizeof(Rect_00621D30) == 0x10);

struct Palette_00621D30
{
    unsigned char Bytes[0x300];   // +0x000

    // FUNCTION: GAMEMD 0x6B93E0 (decl; reloc)
    void FUN_006B93E0();
};
GG_STATIC_ASSERT(sizeof(Palette_00621D30) == 0x300);

class PCXCache_00621D30
{
public:
    // FUNCTION: GAMEMD 0x6BA140 (decl; reloc)
    void* GetSurface(const char* filename, Palette_00621D30* palette);
    // FUNCTION: GAMEMD 0x6BA690 (decl; reloc)
    int Draw(Rect_00621D30* area, void* dest, void* surface, void* alpha,
             Palette_00621D30* palette, int arg5, int frame, int arg7);
};

// GLOBAL: GAMEMD 0xAC4848
extern PCXCache_00621D30 DAT_00ac4848;

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

#include "../core/trivial_tu171_methods.h"

#include "../core/vector_class_operations.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

struct RGBClass { unsigned char R; unsigned char G; unsigned char B; RGBClass() : R(0), G(0), B(0) {} bool operator==(const RGBClass& o) const { return R==o.R && G==o.G && B==o.B; } bool operator!=(const RGBClass& o) const { return !(*this==o); } };

template class DynamicVectorClass<RGBClass>;

struct HSVClass { unsigned char unknown_00; unsigned char unknown_01; unsigned char unknown_02; HSVClass() : unknown_00(0), unknown_01(0), unknown_02(0) {} bool __fastcall operator==(const HSVClass& o) const; bool operator!=(const HSVClass& o) const; };

template class DynamicVectorClass<HSVClass>;

#include "../renderer/cache_key_extent_methods.h"

#include "../renderer/color_scheme_count_methods.h"

// The hash table's constructor: hash routine, bucket count, growth step 10,
// then the bucket array (vector-new with the count cookie in front and the
// strided constructor iterator, spelt out because cl 8804 expands the loop
// inline instead) and each bucket's growth step.
inline Table_00626C60::Table_00626C60(HashFn_00626C60 hash, int numBuckets) throw()
    : Hash(hash), NumBuckets(numBuckets), At_0C(10)
{
    int* raw = (int*)FUN_007C8E17(4 + 31 * sizeof(Bucket_00626C60));
    Bucket_00626C60* buckets;
    if (raw != 0) {
        buckets = (Bucket_00626C60*)(raw + 1);
        raw[0] = 31;
        FUN_004068F0((char*)buckets, sizeof(Bucket_00626C60), 31, FUN_00628740);
    } else {
        buckets = 0;
    }
    this->Buckets = buckets;

    for (int i = 0; i < this->NumBuckets; i++) {
        this->Buckets[i].CapacityIncrement = 10;
    }
}

inline Owner_00626C60::Owner_00626C60() throw()
    : At_00(-1),
      VecA(new VecA_00626C60()),
      VecB(new VecB_00626C60()),
      Table(new Table_00626C60(FUN_00626660, 31))
{
}

#include "control_id_predicate_methods.h"

#include "dialog_control_group_lookup.h"

// The hash-table probe all four bodies open with, expanded inline at each
// entry. It is the helper proven at 0x602B90/0x603240: it must be forced
// inline and it must keep the inner `n ? &n->Value : 0` guard, because that
// guard is the first of retail's two null tests on the hit path and the
// caller's own `p ? p->Field6C : 0` is the second. Dropping either one loses
// the `ADD EAX,4` block.
__forceinline static MapValue_00602B90* Inline_00600CA0(int nKey)
{
    if (DAT_00AC1B00.Count != 0)
    {
        unsigned hash = DAT_00AC1B00.Hash(&nKey);
        MapNode_00602B90* node =
            DAT_00AC1B00.Buckets[hash & ((1u << DAT_00AC1B00.Shift) - 1u)];

        while (node != 0)
        {
            if (node->Key == nKey)
                return node ? &node->Value : 0;

            node = node->Next;
        }
    }

    return 0;
}

#include "dialog_tab_focus_methods.h"

#include "ui_focus_methods.h"

// Win32 imports reached through the IAT (`CALL dword ptr [0x007E1498]` and
// `CALL dword ptr [0x007E14D0]`).
extern "C" __declspec(dllimport) int __stdcall ShowWindow(HWND hWnd, int nCmdShow);
extern "C" __declspec(dllimport) int __stdcall SetForegroundWindow(HWND hWnd);

#include "ui_updated_methods.h"
#include "../platform/input_manager_class_methods.h"

// Engine globals read by Updated (absolute dword/byte loads in the disasm).
extern int           SessionGameMode; // GAMEMD 0xA8B238 (first field of the session)
extern unsigned char InhibitFlag;     // GAMEMD 0xA8D60E
extern int           InhibitWord;     // GAMEMD 0xA8DAB4

// Helper functions called by Updated (direct CALLs; result is bool in AL where used).
bool PredicateA();  // GAMEMD 0x55CBF0  (byte load -> bool)
bool PredicateB();  // GAMEMD 0x55D360  (byte load -> bool)
void CallBack();    // GAMEMD 0x48D080  (void)

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EF700
extern const double DAT_007EF700;
// GLOBAL: GAMEMD 0xAC1B40
extern double DAT_00AC1B40;
// GLOBAL: GAMEMD 0xAC4838
extern double DAT_00AC4838;
// GLOBAL: GAMEMD 0xAC4888
extern int DAT_00AC4888;
// GLOBAL: GAMEMD 0xAC488C
extern int DAT_00AC488C;
// GLOBAL: GAMEMD 0xAC4890
extern int DAT_00AC4890;
// GLOBAL: GAMEMD 0xAC48A0
extern double DAT_00AC48A0;

// ---- from the former ownrdraw.cpp ----
//   assert string "D:\ra2mdpost\ownrdraw.cpp" at 0x833730.
//
//   GLOBAL:   GAMEMD 0xAC1B00  the dialog-type hash table
//   GLOBAL:   GAMEMD 0x7E149C  __imp__InvalidateRect
//   GLOBAL:   GAMEMD 0x7E14A4  __imp__SendMessageA
//   GLOBAL:   GAMEMD 0x7E1398  __imp__MoveWindow
//   GLOBAL:   GAMEMD 0x7E13BC  __imp__GetWindowRect
//   GLOBAL:   GAMEMD 0x7E14E0  __imp__IsWindowVisible
//   GLOBAL:   GAMEMD 0xAC1CAC  counter bumped by 0x60A180
//   GLOBAL:   GAMEMD 0x7E1474  __imp__GetWindowLongA
//   GLOBAL:   GAMEMD 0x7E14A8  __imp__GetDlgItem
//   GLOBAL:   GAMEMD 0x7E146C  __imp__UpdateWindow
//   GLOBAL:   GAMEMD 0x7E14EC  __imp__GetParent
//   GLOBAL:   GAMEMD 0x7E14E4  __imp__EnumChildWindows

// C4661: the members this TU does not define stay declarations on purpose.
#pragma warning(disable : 4661)
#include "ownrdraw.h"
#include "../network/packet_class.h"
#include "../ui/bit_font_print_methods.h"
#include "../_layout/rules_class.h"
#include "../core/hash_table_rehash_sweep.h"
#include "../core/global_getter_family_methods.h"
#include "../core/trivial_tu181_methods.h"
#pragma intrinsic(strcmp)
#include "../audio/voc_class_play_global_methods.h"

// The probe every function here opens with, expanded inline. Same shape as
// the one proven at 0x602B90: the inner `n ? &n->Value : 0` guard is the first
// of retail's two null tests on the hit path, the caller's own check the second.
__forceinline static MapValue_00602B90* Inline_Probe(int nKey)
{
    if (DAT_00AC1B00.Count != 0)
    {
        unsigned hash = DAT_00AC1B00.Hash(&nKey);
        MapNode_00602B90* node =
            DAT_00AC1B00.Buckets[hash & ((1u << DAT_00AC1B00.Shift) - 1u)];

        while (node != 0)
        {
            if (node->Key == nKey)
                return node ? &node->Value : 0;

            node = node->Next;
        }
    }

    return 0;
}

// GLOBAL: GAMEMD 0xAC4894 -- counter the enumeration callback at 0x60A250 bumps.
extern int DAT_00AC4894;
// GLOBAL: GAMEMD 0xAC48B4 -- count of live Hook_006223C0 objects.
extern int DAT_00AC48B4;

template struct HashTable_006249A0<int, MapValue_00602B90>;
template struct HashTable_006249A0<int, int>;

__forceinline void Obj_00626250::Inline_Release()
{
    if (unknown_100 != 0)
    {
        int nCount = unknown_100->Count;

        for (int i = 0; i < nCount; i++)
        {
            Obj_0068C8D0* pItem = unknown_100->Items[i];

            if (pItem != 0)
                delete pItem;
        }

        if (unknown_100 != 0)
            delete unknown_100;

        unknown_100 = 0;
    }
}

// FUNCTION: GAMEMD 0x600370
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_00600370()
{
    DAT_00AC48A0 = DAT_00AC1B40 / DAT_007EF700;
}

// FUNCTION: GAMEMD 0x600390
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_00600390()
{
    DAT_00AC4838 = DAT_007E1718 / DAT_00AC48A0;
}

// FUNCTION: GAMEMD 0x600510
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_00600510()
{
    DAT_00AC4890 = 0;
    DAT_00AC4888 = 0x80;
    DAT_00AC488C = 0x80;
}

// FUNCTION: GAMEMD 0x600550
// Tail-calls a method on a global object.
void FUN_00600550(int a1, int a2)
{
    FUN_006B9530(DAT_00AC4848, a2);
}

// GLOBAL: GAMEMD 0xAC1DF0, 0xAC4604, 0xAC4624, 0xAC1890, 0xAC18A4, 0xAC1CB0,
//   0xAC4618, 0xAC184C, 0xAC4628, 0xAC4880, 0xAC1DD8, 0xAC1B98, 0xAC1B94,
//   0xAC1CB4, 0xAC1AF8, 0xAC1CA8, 0xAC4620, 0xAC4898, 0xAC4608, 0xAC48B0,
//   0xAC1B90 -- the dialog colour and metric words stored by 0x600560.
extern int DAT_00AC1DF0;
extern int DAT_00AC4604;
extern int DAT_00AC4624;
extern int DAT_00AC1890;
extern int DAT_00AC18A4;
extern int DAT_00AC1CB0;
extern int DAT_00AC4618;
extern int DAT_00AC184C;
extern int DAT_00AC4628;
extern int DAT_00AC4880;
extern int DAT_00AC1DD8;
extern int DAT_00AC1B98;
extern int DAT_00AC1B94;
extern int DAT_00AC1CB4;
extern int DAT_00AC1AF8;
extern int DAT_00AC1CA8;
extern int DAT_00AC4620;
extern int DAT_00AC4898;
extern int DAT_00AC4608;
extern int DAT_00AC48B0;
extern int DAT_00AC1B90;

// FUNCTION: GAMEMD 0x600560
// Static-initialiser shape: stores constants to a run of globals.
void FUN_00600560()
{
    DAT_00AC1DF0 = 1;
    DAT_00AC4604 = 0xFF;
    DAT_00AC4624 = 0xFF;
    DAT_00AC1890 = 0x7F;
    DAT_00AC18A4 = 0xFFFF;
    DAT_00AC1CB0 = 0xEEEEEE;
    DAT_00AC4618 = 0x9F9F;
    DAT_00AC184C = 0xFFFFFF;
    DAT_00AC4628 = 0x808080;
    DAT_00AC4880 = 0x626262;
    DAT_00AC1DD8 = 0x929292;
    DAT_00AC1B98 = 0xC5BEA7;
    DAT_00AC1B94 = 0x807A68;
    DAT_00AC1CB4 = 0x9F;
    DAT_00AC1AF8 = 0x8F8F8F;
    DAT_00AC1CA8 = 0x9F;
    DAT_00AC4620 = 0x646464;
    DAT_00AC4898 = 0x60;
    DAT_00AC4608 = 0xAAAA;
    DAT_00AC48B0 = 0x221B0B;
    DAT_00AC1B90 = 0x443716;
}

// FUNCTION: GAMEMD 0x600660
// Member getter (dword).
int Obj_00600660::FUN_00600660() const
{
    return unknown_00;
}

// FUNCTION: GAMEMD 0x600670  CacheKey_00600670::Extent (__thiscall)
// Total cell count spanned by the key — the product of its two extents. Retail
// loads the +4 field into EAX and multiplies by the +0 field in memory, which
// both operand orders reproduce exactly.
int CacheKey_00600670::Extent()
{
    return Height * Width;
}

// FUNCTION: GAMEMD 0x600680  CacheKey_00600670::operator== (__thiscall)
// Key equality, used to confirm a hash-bucket hit before the entry is reused.
//
// The result must reach the return through an explicit `if`, not as a bare
// comparison chain: written as `return other.Height == Height && ...` cl
// materialises the answer in the full EAX (`MOV EAX,1` / `XOR EAX,EAX`) where
// retail uses the byte form (`MOV AL,1` / `XOR AL,AL`), and the body is
// otherwise instruction-for-instruction identical at 73.3%.
bool CacheKey_00600670::operator==(const CacheKey_00600670& other) const
{
    if (other.Height == Height && other.Width == Width)
        return true;

    return false;
}

// FUNCTION: GAMEMD 0x600C70  FUN_00600C70 (__fastcall)
// Move the dialog keyboard focus one tab stop away from `hCtl`, forwards or
// (with `bPrevious`) backwards, and report whether the focus actually moved.
// When the control is the only tab stop in its parent, GetNextDlgTabItem hands
// back the same window and the focus is left alone.
bool FUN_00600C70(GG_HWND hCtl, unsigned char bPrevious)
{
    // GetParent must be its own statement: nested inside the argument list it
    // costs the whole register assignment (4.8%), because cl then widens the
    // flag before the call instead of holding it raw in ESI across it.
    GG_HWND hParent = GetParent(hCtl);
    GG_HWND hNext = GetNextDlgTabItem(hParent, hCtl, bPrevious);

    if (hNext != hCtl)
    {
        SetFocus(hNext);
        return true;
    }

    return false;
}

// PARTIAL (34.8% by the instruction differ, 671/1718 bytes identical).
// The instruction stream is retail's except for the placement of the return
// blocks: retail carries five of them, one laid out inline at the fallthrough
// of each clause that produces it, and cl 8804 sinks them to the end of the
// function and folds the four `return 0x1E` copies into one. The full-stream
// multiset differs by exactly {jne,pop,pop,pop,mov,ret} retail-only against
// {je,je,je} ours — one whole return block and three branch polarities, which
// is the signature of that sink-and-fold and nothing else. Variants tried:
// the clause written flat with `&&` (this form) and nested as `if (cat) { if
// (id) ... }` (byte-identical output); `else if` chains; an explicit
// `if (!(chain)) goto next; return X;` spelling of retail's own block order;
// each of the fourteen terms of a chain as its own `if` (worse, 951/1730 on
// the sibling); the tail guard written as a bare call statement (worse, 233
// bytes); /Ox, /O1, /Ob2, /Gf, and /O2 decomposed with and without /Og (only
// /Og removes the fold, and without it the whole function regresses to 221
// bytes). Recorded as the 8447-vs-8804 identical-tail cross-jump difference
// already banked for 0x459C00 and 0x41EAF0.
//
// FUNCTION: GAMEMD 0x600CA0  FUN_00600CA0 (__fastcall)
// The first of four sibling group-size lookups. The keyed object supplies a
// category through the hash table, the control supplies its dialog ID, and
// the pair selects one of three group sizes. The clause order, the term
// order inside each clause and the constants themselves are retail's own:
// cl lays a disjunction of equality tests out verbatim, so the chains are
// transcribed in comparison order rather than sorted or switched.
//
// The trailing probe is a call whose result retail discards, because both
// arms of the guard it belongs to answer the same constant (0xF) and cl
// folded the test away; the call itself survives because FUN_00601360 is
// out of line and its side effects are not visible here.
int FUN_00600CA0(int nKey, GG_HWND hCtl)
{
    MapValue_00602B90* value = Inline_00600CA0(nKey);
    int category = value ? value->Field6C : 0;
    int nCtlID = GetDlgCtrlID(hCtl);

    if ((category == 0x10C || category == 0x94 || category == 0xA3 ||
         category == 0x73 || category == 0xD8 || category == 0xBBB ||
         category == 0xF5 || category == 0x105 || category == 0xE2 ||
         category == 0xD5 || category == 0x2B5 || category == 0xB7 ||
         category == 0x2B4 || category == 0xBC7 || category == 0x101 ||
         category == 0x129 || category == 0xBC6 || category == 0xD7 ||
         category == 0x108 || category == 0xBC || category == 0xBD ||
         category == 0xBB || category == 0xB5 || category == 0xBBA ||
         category == 0xFF || category == 0x6B || category == 0x100 ||
         category == 0x102 || category == 0xB8 || category == 0xD6 ||
         category == 0x103 || category == 0x125 || category == 0xE7 ||
         category == 0x116 || category == 0xC2 || category == 0xC9 ||
         category == 0x11D || category == 0x11C || category == 0x114 ||
         category == 0x2BC || category == 0x113 || category == 0x109 ||
         category == 0x10F || category == 0x117 || category == 0xE6 ||
         category == 0xF3 || category == 0xF4 || category == 0x10E ||
         category == 0x112)
        && nCtlID == 0x694)
    {
        return 0x1E;
    }

    if ((category == 0xBC || category == 0xBD || category == 0x102 ||
         category == 0xC2 || category == 0xC9 || category == 0xBC6)
        && (nCtlID == 0x6EC || nCtlID == 0x5A8))
    {
        return 0x1E;
    }

    if (category == 0x103 || category == 0xBC7)
    {
        if (nCtlID == 0x6F4)
            return 0xF;

        if (nCtlID == 0x6F3 || nCtlID == 0x69F || nCtlID == 0x6F6 ||
            nCtlID == 0x6EF || nCtlID == 0x6F1 || nCtlID == 0x6F0 ||
            nCtlID == 0x6F2 || nCtlID == 0x73C || nCtlID == 0x73D ||
            nCtlID == 0x73E || nCtlID == 0x73F || nCtlID == 0x740 ||
            nCtlID == 0x735 || nCtlID == 0x732 || nCtlID == 0x3EA ||
            nCtlID == 0x733)
        {
            return 0x1E;
        }

        if (nCtlID == 0x411 || nCtlID == 0x412 || nCtlID == 0x419 ||
            nCtlID == 0x41A || nCtlID == 0x6A3 || nCtlID == 0x6A4 ||
            nCtlID == 0x6A5 || nCtlID == 0x6A7 || nCtlID == 0x6A6 ||
            nCtlID == 0x6A8 || nCtlID == 0x73A || nCtlID == 0x739 ||
            nCtlID == 0x73B || nCtlID == 0x738)
        {
            return 0x3C;
        }
    }

    if (category == 0x108 || category == 0xBC6)
    {
        if (nCtlID == 0x6D2 || nCtlID == 0x3EA || nCtlID == 0x733 ||
            nCtlID == 0x71B || nCtlID == 0x732 || nCtlID == 0x69D ||
            nCtlID == 0x69F || nCtlID == 0x69E || nCtlID == 0x6A0 ||
            nCtlID == 0x78B || nCtlID == 0x5C8 || nCtlID == 0x411 ||
            nCtlID == 0x412 || nCtlID == 0x413 || nCtlID == 0x414 ||
            nCtlID == 0x415 || nCtlID == 0x416 || nCtlID == 0x417 ||
            nCtlID == 0x418)
        {
            return 0x1E;
        }

        if (nCtlID == 0x419 || nCtlID == 0x41A || nCtlID == 0x41B ||
            nCtlID == 0x41C || nCtlID == 0x41D || nCtlID == 0x41E ||
            nCtlID == 0x41F || nCtlID == 0x420 || nCtlID == 0x6A3 ||
            nCtlID == 0x6A4 || nCtlID == 0x6A9 || nCtlID == 0x6AC ||
            nCtlID == 0x6AF || nCtlID == 0x6B2 || nCtlID == 0x6B5 ||
            nCtlID == 0x6B8 || nCtlID == 0x6A5 || nCtlID == 0x6A7 ||
            nCtlID == 0x6AA || nCtlID == 0x6AD || nCtlID == 0x6B0 ||
            nCtlID == 0x6B3 || nCtlID == 0x6B6 || nCtlID == 0x6B9 ||
            nCtlID == 0x6A6 || nCtlID == 0x6A8 || nCtlID == 0x6AB ||
            nCtlID == 0x6AE || nCtlID == 0x6B1 || nCtlID == 0x6B4 ||
            nCtlID == 0x6B7 || nCtlID == 0x6BA || nCtlID == 0x70A ||
            nCtlID == 0x70B || nCtlID == 0x70C || nCtlID == 0x70D ||
            nCtlID == 0x70E || nCtlID == 0x70F || nCtlID == 0x710 ||
            nCtlID == 0x711)
        {
            return 0x3C;
        }
    }

    if (FUN_00601360(category) && nCtlID == 0x695)
        return 0xF;

    return 0xF;
}

// FUNCTION: GAMEMD 0x601360  FUN_00601360 (__fastcall)
// The wider membership test of the same family: 58 identifiers, again written
// in retail's comparison order because that order is the source order. This one
// answers a one-byte bool (`MOV AL,1` / `XOR AL,AL`) where its 0x602AE0 sibling
// answers a full dword, and its accepted set is a strict superset of that one's
// except for 0x109 and 0x113, which only this test accepts.
bool FUN_00601360(int nID)
{
    if (
        nID == 0x10C || nID == 0x94 || nID == 0xB6 || nID == 0xA3 ||
        nID == 0x73 || nID == 0xD8 || nID == 0xBBB || nID == 0xF5 ||
        nID == 0x105 || nID == 0xE2 || nID == 0xD5 || nID == 0x2B5 ||
        nID == 0xB7 || nID == 0x2B4 || nID == 0x101 || nID == 0x129 ||
        nID == 0xBC7 || nID == 0xBC6 || nID == 0xD7 || nID == 0x108 ||
        nID == 0xBC || nID == 0xBD || nID == 0xBB || nID == 0xB5 ||
        nID == 0xBBA || nID == 0xFF || nID == 0xEA || nID == 0x6B ||
        nID == 0x100 || nID == 0x102 || nID == 0xB8 || nID == 0xD6 ||
        nID == 0x103 || nID == 0x11F || nID == 0x125 || nID == 0x115 ||
        nID == 0x122 || nID == 0x112 || nID == 0xE7 || nID == 0x116 ||
        nID == 0xC2 || nID == 0xC9 || nID == 0x11D || nID == 0x11C ||
        nID == 0x113 || nID == 0xFE || nID == 0x109 || nID == 0x10F ||
        nID == 0x117 || nID == 0x114 || nID == 0xC3 || nID == 0x124 ||
        nID == 0xE6 || nID == 0xF3 || nID == 0xF4 || nID == 0x2BC ||
        nID == 0x11B || nID == 0x10E)
    {
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x6015E0  FUN_006015E0 (__fastcall)
// The same lookup answering a different quantity: 1 for every ordinary
// group and 3 for the two special controls. Here the trailing probe's
// result is live, because its arm answers 3 while the fallthrough answers
// 1, which is what keeps the TEST AL,AL and the 0x695 compare in the body.
int FUN_006015E0(int nKey, GG_HWND hCtl)
{
    MapValue_00602B90* value = Inline_00600CA0(nKey);
    int category = value ? value->Field6C : 0;
    int nCtlID = GetDlgCtrlID(hCtl);

    if ((category == 0x10C || category == 0x94 || category == 0xA3 ||
         category == 0x73 || category == 0xD8 || category == 0xBBB ||
         category == 0xF5 || category == 0x105 || category == 0xE2 ||
         category == 0xD5 || category == 0x2B5 || category == 0xB7 ||
         category == 0x2B4 || category == 0xBC7 || category == 0x101 ||
         category == 0x129 || category == 0xBC6 || category == 0xD7 ||
         category == 0x108 || category == 0xBC || category == 0xBD ||
         category == 0xBB || category == 0xB5 || category == 0xBBA ||
         category == 0xFF || category == 0x6B || category == 0x100 ||
         category == 0x102 || category == 0xB8 || category == 0xD6 ||
         category == 0x103 || category == 0x125 || category == 0xE7 ||
         category == 0x116 || category == 0xC2 || category == 0xC9 ||
         category == 0x11D || category == 0x11C || category == 0x114 ||
         category == 0x2BC || category == 0x113 || category == 0x109 ||
         category == 0x10F || category == 0x117 || category == 0xE6 ||
         category == 0xF3 || category == 0xF4 || category == 0x10E ||
         category == 0x112)
        && nCtlID == 0x694)
    {
        return 1;
    }

    if ((category == 0xBC || category == 0xBD || category == 0x102 ||
         category == 0xC2 || category == 0xC9 || category == 0xBC6)
        && (nCtlID == 0x6EC || nCtlID == 0x5A8))
    {
        return 1;
    }

    if (category == 0x103 || category == 0xBC7)
    {
        if (nCtlID == 0x6F4)
            return 3;

        if (nCtlID == 0x6F3 || nCtlID == 0x69F || nCtlID == 0x6F6 ||
            nCtlID == 0x6EF || nCtlID == 0x6F1 || nCtlID == 0x6F0 ||
            nCtlID == 0x6F2 || nCtlID == 0x733 || nCtlID == 0x735 ||
            nCtlID == 0x732 || nCtlID == 0x3EA || nCtlID == 0x73C ||
            nCtlID == 0x73D || nCtlID == 0x73E || nCtlID == 0x73F ||
            nCtlID == 0x740 || nCtlID == 0x736 || nCtlID == 0x737 ||
            nCtlID == 0x411 || nCtlID == 0x412 || nCtlID == 0x419 ||
            nCtlID == 0x41A || nCtlID == 0x6A3 || nCtlID == 0x6A4 ||
            nCtlID == 0x6A5 || nCtlID == 0x6A7 || nCtlID == 0x6A6 ||
            nCtlID == 0x6A8 || nCtlID == 0x73A || nCtlID == 0x739 ||
            nCtlID == 0x73B || nCtlID == 0x738)
        {
            return 1;
        }
    }

    if ((category == 0x108 || category == 0xBC6)
        && (nCtlID == 0x6D2 || nCtlID == 0x3EA || nCtlID == 0x733 ||
            nCtlID == 0x71B || nCtlID == 0x732 || nCtlID == 0x69D ||
            nCtlID == 0x69F || nCtlID == 0x69E || nCtlID == 0x6A0 ||
            nCtlID == 0x78B || nCtlID == 0x5C8 || nCtlID == 0x411 ||
            nCtlID == 0x412 || nCtlID == 0x413 || nCtlID == 0x414 ||
            nCtlID == 0x415 || nCtlID == 0x416 || nCtlID == 0x417 ||
            nCtlID == 0x418 || nCtlID == 0x419 || nCtlID == 0x41A ||
            nCtlID == 0x41B || nCtlID == 0x41C || nCtlID == 0x41D ||
            nCtlID == 0x41E || nCtlID == 0x41F || nCtlID == 0x420 ||
            nCtlID == 0x6A3 || nCtlID == 0x6A4 || nCtlID == 0x6A9 ||
            nCtlID == 0x6AC || nCtlID == 0x6AF || nCtlID == 0x6B2 ||
            nCtlID == 0x6B5 || nCtlID == 0x6B8 || nCtlID == 0x6A5 ||
            nCtlID == 0x6A7 || nCtlID == 0x6AA || nCtlID == 0x6AD ||
            nCtlID == 0x6B0 || nCtlID == 0x6B3 || nCtlID == 0x6B6 ||
            nCtlID == 0x6B9 || nCtlID == 0x6A6 || nCtlID == 0x6A8 ||
            nCtlID == 0x6AB || nCtlID == 0x6AE || nCtlID == 0x6B1 ||
            nCtlID == 0x6B4 || nCtlID == 0x6B7 || nCtlID == 0x6BA ||
            nCtlID == 0x70A || nCtlID == 0x70B || nCtlID == 0x70C ||
            nCtlID == 0x70D || nCtlID == 0x70E || nCtlID == 0x70F ||
            nCtlID == 0x710 || nCtlID == 0x711))
    {
        return 1;
    }

    if (FUN_00601360(category) && nCtlID == 0x695)
        return 3;

    return 1;
}

// PARTIAL (50.9% by the instruction differ, 1031/1730 bytes identical).
// The closest of the three: the full-stream instruction multiset differs from
// retail by exactly two `je` against two `jne` and nothing else, so this body
// has retail's five return blocks and retail's every compare — only two of
// the blocks sit at the end of the function instead of inline at the
// fallthrough of the last `if` in each nest. Same lever and same variant list
// as 0x600CA0 above.
//
// FUNCTION: GAMEMD 0x601D20  FUN_00601D20 (__fastcall)
// The widest of the four: four distinct answers (8, 0x10, 0x20, 0x40) and
// the only one whose third clause splits its control IDs three ways. The
// shared return blocks retail cross-jumps to are the compiler's own doing,
// not a source-level goto.
int FUN_00601D20(int nKey, GG_HWND hCtl)
{
    MapValue_00602B90* value = Inline_00600CA0(nKey);
    int category = value ? value->Field6C : 0;
    int nCtlID = GetDlgCtrlID(hCtl);

    if ((category == 0x10C || category == 0x94 || category == 0xA3 ||
         category == 0x73 || category == 0xD8 || category == 0xBBB ||
         category == 0xF5 || category == 0x105 || category == 0xE2 ||
         category == 0xD5 || category == 0x2B5 || category == 0xB7 ||
         category == 0x2B4 || category == 0xBC7 || category == 0x101 ||
         category == 0x129 || category == 0xBC6 || category == 0xD7 ||
         category == 0x108 || category == 0xBC || category == 0xBD ||
         category == 0xBB || category == 0xB5 || category == 0xBBA ||
         category == 0xFF || category == 0x6B || category == 0x100 ||
         category == 0x102 || category == 0xB8 || category == 0xD6 ||
         category == 0x103 || category == 0x125 || category == 0xE7 ||
         category == 0x116 || category == 0xC2 || category == 0xC9 ||
         category == 0x11D || category == 0x11C || category == 0x114 ||
         category == 0x2BC || category == 0x113 || category == 0x109 ||
         category == 0x10F || category == 0x117 || category == 0xE6 ||
         category == 0xF3 || category == 0xF4 || category == 0x10E ||
         category == 0x112)
        && nCtlID == 0x694)
    {
        return 8;
    }

    if ((category == 0xBC || category == 0xBD || category == 0x102 ||
         category == 0xC2 || category == 0xC9 || category == 0xBC6)
        && (nCtlID == 0x6EC || nCtlID == 0x5A8))
    {
        return 8;
    }

    if (category == 0x103 || category == 0xBC7)
    {
        if (nCtlID == 0x6F4)
            return 0x10;

        if (nCtlID == 0x6F3 || nCtlID == 0x69F || nCtlID == 0x6F6 ||
            nCtlID == 0x6EF || nCtlID == 0x6F1 || nCtlID == 0x6F0 ||
            nCtlID == 0x6F2 || nCtlID == 0x733 || nCtlID == 0x735 ||
            nCtlID == 0x732 || nCtlID == 0x3EA)
        {
            return 8;
        }

        if (nCtlID == 0x73C || nCtlID == 0x73D || nCtlID == 0x73E ||
            nCtlID == 0x73F || nCtlID == 0x740)
        {
            return 0x10;
        }

        if (nCtlID == 0x411 || nCtlID == 0x412 || nCtlID == 0x419 ||
            nCtlID == 0x41A || nCtlID == 0x6A3 || nCtlID == 0x6A4 ||
            nCtlID == 0x6A5 || nCtlID == 0x6A7 || nCtlID == 0x6A6 ||
            nCtlID == 0x6A8 || nCtlID == 0x73A || nCtlID == 0x739 ||
            nCtlID == 0x73B || nCtlID == 0x738)
        {
            return 0x20;
        }
    }

    if (category == 0x108 || category == 0xBC6)
    {
        if (nCtlID == 0x6D2 || nCtlID == 0x3EA || nCtlID == 0x733 ||
            nCtlID == 0x71B || nCtlID == 0x732 || nCtlID == 0x69D ||
            nCtlID == 0x69F || nCtlID == 0x69E || nCtlID == 0x6A0 ||
            nCtlID == 0x78B || nCtlID == 0x5C8 || nCtlID == 0x411 ||
            nCtlID == 0x412 || nCtlID == 0x413 || nCtlID == 0x414 ||
            nCtlID == 0x415 || nCtlID == 0x416 || nCtlID == 0x417 ||
            nCtlID == 0x418)
        {
            return 0x20;
        }

        if (nCtlID == 0x419 || nCtlID == 0x41A || nCtlID == 0x41B ||
            nCtlID == 0x41C || nCtlID == 0x41D || nCtlID == 0x41E ||
            nCtlID == 0x41F || nCtlID == 0x420 || nCtlID == 0x6A3 ||
            nCtlID == 0x6A4 || nCtlID == 0x6A9 || nCtlID == 0x6AC ||
            nCtlID == 0x6AF || nCtlID == 0x6B2 || nCtlID == 0x6B5 ||
            nCtlID == 0x6B8 || nCtlID == 0x6A5 || nCtlID == 0x6A7 ||
            nCtlID == 0x6AA || nCtlID == 0x6AD || nCtlID == 0x6B0 ||
            nCtlID == 0x6B3 || nCtlID == 0x6B6 || nCtlID == 0x6B9 ||
            nCtlID == 0x6A6 || nCtlID == 0x6A8 || nCtlID == 0x6AB ||
            nCtlID == 0x6AE || nCtlID == 0x6B1 || nCtlID == 0x6B4 ||
            nCtlID == 0x6B7 || nCtlID == 0x6BA || nCtlID == 0x70A ||
            nCtlID == 0x70B || nCtlID == 0x70C || nCtlID == 0x70D ||
            nCtlID == 0x70E || nCtlID == 0x70F || nCtlID == 0x710 ||
            nCtlID == 0x711)
        {
            return 0x40;
        }
    }

    if (FUN_00601360(category) && nCtlID == 0x695)
        return 0x10;

    return 8;
}

// PARTIAL (28.1% by the instruction differ, 521/1602 bytes identical).
// Retail keeps five separate `POP EDI; MOV AL,1; POP ESI; POP ECX; RET`
// blocks, one per clause; cl 8804 folds all five into one. The multiset
// residual is exactly four of those blocks plus five branch polarities. The
// `(char)` cast on FUN_00602AE0's result is load-bearing and stays: retail
// tests that call with `TEST AL,AL` while the callee's own exit at 0x602AE0
// is `MOV EAX,1`, so the value is narrowed at the call site, not at the
// definition. Same variant list as 0x600CA0 above.
//
// FUNCTION: GAMEMD 0x6023F0  FUN_006023F0 (__fastcall)
int FUN_006023F0(int nKey, GG_HWND hCtl)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    int category = value ? value->Field6C : 0;
    int nCtlID = GetDlgCtrlID(hCtl);

    if ((category == 0x103 || category == 0xBC7) && nCtlID == 0x6F4)
        return Rules->unknown_6C4;

    return -1;
}

// FUNCTION: GAMEMD 0x602490  FUN_00602490 (__fastcall)
// The predicate of the family, and the one that answers a byte: its exits
// are MOV AL,1 / XOR AL,AL, where the three siblings above load EAX. Its
// first clause widens the category set with the out-of-line membership test
// at 0x602AE0, and its tail adds one more guard, a flag read off the
// session object at 0xA8B238 + 0x30D8 through the accessor at 0x69BBE0.
bool FUN_00602490(int nKey, GG_HWND hCtl)
{
    MapValue_00602B90* value = Inline_00600CA0(nKey);
    int category = value ? value->Field6C : 0;
    int nCtlID = GetDlgCtrlID(hCtl);

    if ((category == 0x10C || category == 0x94 || category == 0xA3 ||
         category == 0x73 || category == 0xD8 || category == 0xBBB ||
         category == 0xF5 || category == 0x105 || category == 0xE2 ||
         category == 0xD5 || category == 0x2B5 || category == 0xB7 ||
         category == 0x2B4 || category == 0xBC7 || category == 0x101 ||
         category == 0x129 || category == 0xBC6 || category == 0xD7 ||
         category == 0x108 || category == 0xBC || category == 0xBD ||
         category == 0xBB || category == 0xB5 || category == 0xBBA ||
         category == 0xFF || category == 0x6B || category == 0x100 ||
         category == 0x102 || category == 0xB8 || category == 0xD6 ||
         category == 0x103
         || (char)FUN_00602AE0(category))
        && nCtlID == 0x694)
    {
        return true;
    }

    if ((category == 0xBC || category == 0xBD || category == 0x102 ||
         category == 0xC2 || category == 0xC9 || category == 0xBC6)
        && (nCtlID == 0x6EC || nCtlID == 0x5A8))
    {
        return true;
    }

    if ((category == 0x103 || category == 0xBC7)
        && (nCtlID == 0x6F3 || nCtlID == 0x6F4 || nCtlID == 0x69F ||
            nCtlID == 0x6F6 || nCtlID == 0x6EF || nCtlID == 0x6F1 ||
            nCtlID == 0x6F0 || nCtlID == 0x6F2 || nCtlID == 0x733 ||
            nCtlID == 0x735 || nCtlID == 0x732 || nCtlID == 0x3EA ||
            nCtlID == 0x736 || nCtlID == 0x737 || nCtlID == 0x73C ||
            nCtlID == 0x73D || nCtlID == 0x73E || nCtlID == 0x73F ||
            nCtlID == 0x740 || nCtlID == 0x411 || nCtlID == 0x412 ||
            nCtlID == 0x419 || nCtlID == 0x41A || nCtlID == 0x6A3 ||
            nCtlID == 0x6A4 || nCtlID == 0x6A5 || nCtlID == 0x6A7 ||
            nCtlID == 0x6A6 || nCtlID == 0x6A8 || nCtlID == 0x73A ||
            nCtlID == 0x739 || nCtlID == 0x73B || nCtlID == 0x738))
    {
        return true;
    }

    if ((category == 0x108 || category == 0xBC6)
        && (nCtlID == 0x6D2 || nCtlID == 0x3EA || nCtlID == 0x69D ||
            nCtlID == 0x69F || nCtlID == 0x69E || nCtlID == 0x6A0 ||
            nCtlID == 0x78B || nCtlID == 0x5C8 || nCtlID == 0x411 ||
            nCtlID == 0x412 || nCtlID == 0x413 || nCtlID == 0x414 ||
            nCtlID == 0x415 || nCtlID == 0x416 || nCtlID == 0x417 ||
            nCtlID == 0x418 || nCtlID == 0x419 || nCtlID == 0x41A ||
            nCtlID == 0x41B || nCtlID == 0x41C || nCtlID == 0x41D ||
            nCtlID == 0x41E || nCtlID == 0x41F || nCtlID == 0x420 ||
            nCtlID == 0x6A3 || nCtlID == 0x6A4 || nCtlID == 0x6A9 ||
            nCtlID == 0x6AC || nCtlID == 0x6AF || nCtlID == 0x6B2 ||
            nCtlID == 0x6B5 || nCtlID == 0x6B8 || nCtlID == 0x6A5 ||
            nCtlID == 0x6A7 || nCtlID == 0x6AA || nCtlID == 0x6AD ||
            nCtlID == 0x6B0 || nCtlID == 0x6B3 || nCtlID == 0x6B6 ||
            nCtlID == 0x6B9 || nCtlID == 0x6A6 || nCtlID == 0x6A8 ||
            nCtlID == 0x6AB || nCtlID == 0x6AE || nCtlID == 0x6B1 ||
            nCtlID == 0x6B4 || nCtlID == 0x6B7 || nCtlID == 0x6BA ||
            nCtlID == 0x70A || nCtlID == 0x70B || nCtlID == 0x70C ||
            nCtlID == 0x70D || nCtlID == 0x70E || nCtlID == 0x70F ||
            nCtlID == 0x710 || nCtlID == 0x711 || nCtlID == 0x733 ||
            nCtlID == 0x732 || nCtlID == 0x71B || nCtlID == 0x735))
    {
        return true;
    }

    if (FUN_00601360(category) && nCtlID == 0x695
        && !DAT_00A8B238_Session.FUN_0069BBE0())
    {
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x602AE0  FUN_00602AE0 (__fastcall)
// Membership test over a fixed set of eighteen identifiers. The terms are
// written in retail's own comparison order because that order is the source
// order: cl lays a disjunction of equality tests out verbatim, so any
// re-sorting (or a switch, which would bring a jump table) loses the match.
int FUN_00602AE0(int nID)
{
    if (nID == 0x125 || nID == 0xE7 || nID == 0x116 || nID == 0xC2 ||
        nID == 0xC9 || nID == 0x11D || nID == 0x11C || nID == 0x114 ||
        nID == 0x2BC || nID == 0x113 || nID == 0x109 || nID == 0x10F ||
        nID == 0x117 || nID == 0xE6 || nID == 0xF3 || nID == 0xF4 ||
        nID == 0x10E || nID == 0x112)
    {
        return 1;
    }

    return 0;
}

// FUNCTION: GAMEMD 0x602D70  FUN_00602D70
bool FUN_00602D70(int nKey, GG_HWND hCtl)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    int category = value ? value->Field6C : 0;
    int nCtlID = GetDlgCtrlID(hCtl);

    return false;
}

// FUNCTION: GAMEMD 0x602DD0  FUN_00602DD0
bool FUN_00602DD0(int nKey, GG_HWND hCtl)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    int category = value ? value->Field6C : 0;
    int nCtlID = GetDlgCtrlID(hCtl);

    if ((category == 0x94 || category == 0xD8 || category == 0xF5 ||
          category == 0xE2 || category == 0xD5 || category == 0x101 ||
          category == 0x129 || category == 0xD7 || category == 0xBB ||
          category == 0x100 || category == 0xD6 || category == 0x125 ||
          category == 0x122 || category == 0x112 || category == 0xE7 ||
          category == 0x116 || category == 0x11D || category == 0x11C ||
          category == 0xFE || category == 0x10F || category == 0x117 ||
          category == 0x114 || category == 0xE6 || category == 0xF3 ||
          category == 0xF4 || category == 0x2BC || category == 0x10E ||
          category == 0x108 || category == 0xBC6 || category == 0xBC7)
        && nCtlID == 0x71C)
    {
        return true;
    }

    if (category == 0x94 && (nCtlID == 0x6EA || nCtlID == 0x6EC || nCtlID == 0x6EB))
        return true;

    if (category == 0x103 && nCtlID == 0x72B)
        return true;

    if (category == 0xBC7 && nCtlID == 0x72B)
        return true;

    if (category == 0xC4 && nCtlID == 0x7A9)
        return true;

    return false;
}

// FUNCTION: GAMEMD 0x602FE0  FUN_00602FE0
int FUN_00602FE0(int nKey, GG_HWND hCtl)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    int category = value ? value->Field6C : 0;
    int nCtlID = GetDlgCtrlID(hCtl);

    return 0xC;
}

// FUNCTION: GAMEMD 0x603040  FUN_00603040
int FUN_00603040(int nKey, GG_HWND hCtl)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    int category = value ? value->Field6C : 0;
    int nCtlID = GetDlgCtrlID(hCtl);

    if ((category == 0x94 || category == 0xD8 || category == 0xF5 ||
          category == 0xE2 || category == 0xD5 || category == 0x101 ||
          category == 0x129 || category == 0xD7 || category == 0xBB ||
          category == 0x100 || category == 0xD6 || category == 0x125 ||
          category == 0x122 || category == 0x112 || category == 0xE7 ||
          category == 0x116 || category == 0x11D || category == 0x11C ||
          category == 0xFE || category == 0x10F || category == 0x117 ||
          category == 0x114 || category == 0xE6 || category == 0xF3 ||
          category == 0xF4 || category == 0x2BC || category == 0x10E ||
          category == 0x108 || category == 0xBC6 || category == 0xBC7)
        && nCtlID == 0x71C)
    {
        return 0x25;
    }

    if ((category == 0xBC || category == 0xBD || category == 0xC2 ||
         category == 0xC9 || category == 0x102 || category == 0xBC6)
        && (nCtlID == 0x6EC || nCtlID == 0x5A8))
    {
        return 0xE;
    }

    return 0;
}

// FUNCTION: GAMEMD 0x6033F0  FUN_006033F0
int FUN_006033F0(int nKey, GG_HWND hCtl)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    int category = value ? value->Field6C : 0;
    int nCtlID = GetDlgCtrlID(hCtl);

    if (((category == 0x94 || category == 0xD8 || category == 0xF5 ||
          category == 0xE2 || category == 0xD5 || category == 0x101 ||
          category == 0x129 || category == 0xD7 || category == 0xBB ||
          category == 0x100 || category == 0xD6 || category == 0x125 ||
          category == 0x122 || category == 0x112 || category == 0xE7 ||
          category == 0x116 || category == 0x11D || category == 0x11C ||
          category == 0xFE || category == 0x10F || category == 0x117 ||
          category == 0x114 || category == 0xE6 || category == 0xF3 ||
          category == 0xF4 || category == 0x2BC || category == 0x10E ||
          category == 0x108 || category == 0xBC6 || category == 0xBC7)
         && nCtlID == 0x71C))
    {
        return 0x64;
    }

    if (category == 0x94 && (nCtlID == 0x6EA || nCtlID == 0x6EC || nCtlID == 0x6EB))
        return 0x64;

    if (category == 0x103 && nCtlID == 0x72B)
        return 0x64;

    if (category == 0xBC7 && nCtlID == 0x72B)
        return 0x64;

    if (category == 0xC4 && nCtlID == 0x7A9)
        return 0x32;

    return 0;
}

// FUNCTION: GAMEMD 0x6035F0  FUN_006035F0
int FUN_006035F0(int nKey, GG_HWND hCtl)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    int category = value ? value->Field6C : 0;
    int nCtlID = GetDlgCtrlID(hCtl);
    int result = FUN_0072E280();

    if ((category == 0x94 || category == 0xD8 || category == 0xF5 ||
         category == 0xE2 || category == 0xD5 || category == 0x101 ||
         category == 0x129 || category == 0xD7 || category == 0xBB ||
         category == 0x100 || category == 0xD6 || category == 0x125 ||
         category == 0x122 || category == 0x112 || category == 0xE7 ||
         category == 0x116 || category == 0x11D || category == 0x11C ||
         category == 0xFE || category == 0x10F || category == 0x117 ||
         category == 0x114 || category == 0xE6 || category == 0xF3 ||
         category == 0xF4 || category == 0x2BC || category == 0x10E ||
         category == 0x108 || category == 0xBC6 || category == 0xBC7)
        && nCtlID == 0x71C)
    {
        result = FUN_0072E2A0();
    }

    if (category == 0x94)
    {
        if (nCtlID == 0x6EA)
            return FUN_0072DAC0();

        if (nCtlID == 0x6EC)
            return FUN_0072DAD0();

        return result;
    }

    if (category == 0x103)
    {
        if (nCtlID == 0x72B)
            return FUN_0072D450();

        return result;
    }

    if (category == 0xBC7)
    {
        if (nCtlID == 0x72B)
            return FUN_0072D450();

        return result;
    }

    if (category == 0xC4 && nCtlID == 0x7A9)
        return FUN_0072CC80();

    return result;
}

// FUNCTION: GAMEMD 0x603810  FUN_00603810
int FUN_00603810(int nKey, GG_HWND hCtl)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    int category = value ? value->Field6C : 0;
    int nCtlID = GetDlgCtrlID(hCtl);

    return 0;
}

// GLOBAL: GAMEMD 0x833674
extern void* DAT_00833674;
// GLOBAL: GAMEMD 0xB0FB48, 0xB0FB10, 0xB0FB30, 0xB0FAD0
extern int DAT_00B0FB48;
extern int DAT_00B0FB10;
extern int DAT_00B0FB30;
extern int DAT_00B0FAD0;

// FUNCTION: GAMEMD 0x603870  FUN_00603870
int FUN_00603870(int nKey, GG_HWND hCtl, void* pArg)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    int category = value ? value->Field6C : 0;
    int nCtlID = GetDlgCtrlID(hCtl);

    if ((category == 0x94 || category == 0xD8 || category == 0xF5 ||
         category == 0xE2 || category == 0xD5 || category == 0x101 ||
         category == 0x129 || category == 0xD7 || category == 0xBB ||
         category == 0x100 || category == 0xD6 || category == 0x125 ||
         category == 0x122 || category == 0x112 || category == 0xE7 ||
         category == 0x116 || category == 0x11D || category == 0x11C ||
         category == 0xFE || category == 0x10F || category == 0x117 ||
         category == 0x114 || category == 0xE6 || category == 0xF3 ||
         category == 0xF4 || category == 0x2BC || category == 0x10E ||
         category == 0x108 || category == 0xBC6 || category == 0xBC7)
        && nCtlID == 0x71C)
    {
        return FUN_004A38D0(DAT_00833674, pArg);
    }

    if (category == 0x94)
    {
        if (nCtlID == 0x6EA)
            return DAT_00B0FB48;

        if (nCtlID == 0x6EC)
            return DAT_00B0FB10;
    }
    else if (category == 0x103)
    {
        if (nCtlID == 0x72B)
            return DAT_00B0FB30;
    }
    else if (category == 0xBC7)
    {
        if (nCtlID == 0x72B)
            return DAT_00B0FB30;
    }
    else if (category == 0xC4 && nCtlID == 0x7A9)
    {
        return DAT_00B0FAD0;
    }

    return 0;
}

// FUNCTION: GAMEMD 0x603D30  FUN_00603D30 (__fastcall)
void FUN_00603D30(int nKey, int nValue)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    if (value)
    {
        value->Field70 = 2;
        value->Field14 = nValue;
        InvalidateRect((GG_HWND)nKey, 0, 1);
    }
}

// FUNCTION: GAMEMD 0x603DB0
// Calls other functions.
void FUN_00603DB0(GG_HWND hWnd, int a2)
{
    SendMessageA(hWnd, 0x4E5, 0, a2 & 0xFF);
}

// FUNCTION: GAMEMD 0x603DD0  FUN_00603DD0
int FUN_00603DD0(GG_HWND hWnd, unsigned char nValue)
{
    return SendMessageA(hWnd, 0x4E6, 0, nValue);
}

// FUNCTION: GAMEMD 0x603E10  FUN_00603E10
int FUN_00603E10(GG_HWND hWnd, unsigned short nLow, unsigned short nHigh)
{
    return SendMessageA(hWnd, 0x4E8, 0, ((unsigned long)nHigh << 16) | nLow);
}

// FUNCTION: GAMEMD 0x603E40  FUN_00603E40 (__fastcall)
void FUN_00603E40(int nKey, int nValue)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    if (value)
        value->FieldC0 = nValue;
}

// The three-word record the 0x4E9 control message fills in: two input words,
// then the wide string it answers with.
struct Query_00603F00
{
    int           unknown_00;   // +0x00
    int           unknown_04;   // +0x04
    Obj_007B66D0  unknown_08;   // +0x08
};
GG_STATIC_ASSERT(offsetof(Query_00603F00, unknown_08) == 0x08);
GG_STATIC_ASSERT(sizeof(Query_00603F00) == 0x0C);

// FUNCTION: GAMEMD 0x603F00
// Asks the control for a wide string with message 0x4E9; the answer comes back
// by value through the hidden result pointer (ECX).
Obj_007B66D0 FUN_00603F00(GG_HWND hWnd, int a1, int a2)
{
    Query_00603F00 query;
    query.unknown_00 = a1;
    query.unknown_04 = a2;
    SendMessageA(hWnd, 0x4E9, 0, (long)&query);
    return query.unknown_08;
}

// FUNCTION: GAMEMD 0x603F60
// The same query with the second word fixed at -1.
Obj_007B66D0 FUN_00603F60(GG_HWND hWnd, int a1)
{
    Query_00603F00 query;
    query.unknown_00 = a1;
    query.unknown_04 = -1;
    SendMessageA(hWnd, 0x4E9, 0, (long)&query);
    return query.unknown_08;
}

// FUNCTION: GAMEMD 0x606740  FUN_00606740 (__fastcall)
void FUN_00606740(int nKey, bool bValue)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    if (value)
        value->FieldBC = bValue;
}

// FUNCTION: GAMEMD 0x6067A0  FUN_006067A0 (__fastcall)
bool FUN_006067A0(int nKey)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    return value ? value->FieldBC : false;
}

// FUNCTION: GAMEMD 0x6071D0
// Calls other functions.
void FUN_006071D0(GG_HWND hWnd)
{
    EnumChildWindows(hWnd, FUN_00606800, 0);
}

// FUNCTION: GAMEMD 0x607FD0  FUN_00607FD0 (__fastcall)
void FUN_00607FD0(GG_HWND hWnd)
{
    MapValue_00602B90* value = Inline_Probe((int)hWnd);

    if (value && value->FieldBE)
    {
        GG_HWND hItem = GetDlgItem(hWnd, 0x71A);

        if (hItem)
            SendMessageA(hItem, 0x4E2, 0, 0);

        FUN_006071E0(hWnd, false);
        value->FieldBE = false;
    }
}

// FUNCTION: GAMEMD 0x608260  FUN_00608260 (__fastcall)
bool FUN_00608260(GG_HWND hWnd)
{
    if (DAT_00A8B238_Session.FUN_0069BBE0())
        return false;

    MapValue_00602B90* value = Inline_Probe((int)hWnd);

    if (!value)
        return false;

    bool bArmed = value->FieldBD && value->FieldB0 == 1;
    bool bVisible = IsWindowVisible(hWnd) != 0;

    if (!bArmed || !bVisible)
        return false;

    VocClass::PlayGlobal(Rules->unknown_1A0, 1.0f, 0x2000, 0);

    bool bEnabled = IsWindowEnabled(hWnd) != 0;

    EnableWindow(hWnd, 0);
    EnumChildWindows(hWnd, FUN_00606800, 1);
    FUN_006071E0(hWnd, true);
    EnumChildWindows(hWnd, FUN_00606800, 0);
    EnableWindow(hWnd, bEnabled);
    InvalidateRect(hWnd, 0, 0);
    return true;
}

// FUNCTION: GAMEMD 0x608380  FUN_00608380 (__fastcall)
void FUN_00608380(int nKey)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    if (value)
        value->FieldBD = true;
}

// FUNCTION: GAMEMD 0x6083E0  FUN_006083E0 (__fastcall)
void FUN_006083E0(int nKey)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    if (value)
        value->FieldBD = false;
}

// FUNCTION: GAMEMD 0x608440  FUN_00608440 (__fastcall)
void FUN_00608440(int nKey)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    if (value)
        value->FieldD4 = true;
}

// FUNCTION: GAMEMD 0x6084A0  FUN_006084A0 (__fastcall)
void FUN_006084A0(int nKey)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    if (value)
        value->FieldD4 = false;
}

// FUNCTION: GAMEMD 0x6096A0  FUN_006096A0
bool FUN_006096A0(GG_HWND hParent, GG_HWND hWnd)
{
    if ((GetWindowLongA(hWnd, -16) & 0xB) == 0xB)
    {
        MapValue_00602B90* value = Inline_Probe((int)hWnd);

        if (value && value->Field68 == 0)
            return FUN_00608CD0(hParent, hWnd);
    }

    return false;
}

// FUNCTION: GAMEMD 0x609AA0  FUN_00609AA0
bool FUN_00609AA0(GG_HWND hParent, GG_HWND hWnd)
{
    if ((GetWindowLongA(hWnd, -16) & 0xB) == 0xB)
    {
        MapValue_00602B90* value = Inline_Probe((int)hWnd);

        if (value && value->Field68 == 0)
            return FUN_00609730(hParent, hWnd);
    }

    return false;
}

// FUNCTION: GAMEMD 0x609B30  FUN_00609B30
bool FUN_00609B30(int nKey, GG_HWND hCtl)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    int category = value ? value->Field6C : 0;
    int nCtlID = GetDlgCtrlID(hCtl);

    if (FUN_00601360(category) && nCtlID == 0x695)
        return true;

    return false;
}

// FUNCTION: GAMEMD 0x609BC0  FUN_00609BC0
bool FUN_00609BC0(GG_HWND hParent, GG_HWND hWnd)
{
    if (DAT_00A8B238_Session.FUN_0069BBE0())
        return false;

    if ((GetWindowLongA(hWnd, -16) & 0xB) == 0xB)
    {
        MapValue_00602B90* value = Inline_Probe((int)hWnd);

        if (value && value->Field68 == 0 && FUN_00608CD0(hParent, hWnd))
            return true;
    }

    if ((GetWindowLongA(hWnd, -16) & 0xB) == 0xB)
    {
        MapValue_00602B90* value = Inline_Probe((int)hWnd);

        if (value && value->Field68 == 0 && FUN_00609730(hParent, hWnd))
            return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x609CF0  FUN_00609CF0
bool FUN_00609CF0(GG_HWND hParent, GG_HWND hWnd)
{
    if (!DAT_00A8B238_Session.FUN_0069BBE0())
        return false;

    if ((GetWindowLongA(hWnd, -16) & 0xB) == 0xB)
    {
        MapValue_00602B90* value = Inline_Probe((int)hWnd);

        if (value && value->Field68 == 0 && FUN_00608CD0(hParent, hWnd))
            return true;
    }

    if ((GetWindowLongA(hWnd, -16) & 0xB) == 0xB)
    {
        MapValue_00602B90* value = Inline_Probe((int)hWnd);

        if (value && value->Field68 == 0 && FUN_00609730(hParent, hWnd))
            return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x60A100  FUN_0060A100
bool FUN_0060A100(int nKey, GG_HWND hCtl)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    int category = value ? value->Field6C : 0;
    int nCtlID = GetDlgCtrlID(hCtl);

    if (category == 0xE2)
        return nCtlID == 0x71D;

    return false;
}

// FUNCTION: GAMEMD 0x60A180  FUN_0060A180
int __stdcall FUN_0060A180(GG_HWND hWnd, int unused)
{
    GG_HWND hParent = GetParent(hWnd);

    if ((GetWindowLongA(hWnd, -16) & 0xB) == 0xB)
    {
        MapValue_00602B90* value = Inline_Probe((int)hWnd);

        if (value && value->Field68 == 0)
        {
            if (FUN_00608CD0(hParent, hWnd))
            {
                if (IsWindowVisible(hWnd))
                    DAT_00AC1CAC++;
            }
        }
    }

    return 1;
}

// FUNCTION: GAMEMD 0x60A250  FUN_0060A250
int __stdcall FUN_0060A250(GG_HWND hWnd, int unused)
{
    GG_HWND hParent = GetParent(hWnd);

    if ((GetWindowLongA(hWnd, -16) & 0xB) == 0xB)
    {
        MapValue_00602B90* value = Inline_Probe((int)hWnd);

        if (value && value->Field68 == 0)
        {
            if (FUN_00609730(hParent, hWnd))
            {
                if (IsWindowVisible(hWnd))
                    DAT_00AC4894++;
            }
        }
    }

    return 1;
}

// FUNCTION: GAMEMD 0x60A300  FUN_0060A300 (__fastcall)
bool FUN_0060A300(GG_HWND hWnd)
{
    DAT_00AC4894 = 0;
    EnumChildWindows(hWnd, FUN_0060A250, 0);
    return DAT_00AC4894 >= 1;
}

// FUNCTION: GAMEMD 0x60AA60  FUN_0060AA60
int __stdcall FUN_0060AA60(GG_HWND hWnd, int unused)
{
    GG_HWND hParent = GetParent(hWnd);
    if (FUN_00602490((int)hParent, hWnd))
        SendMessageA(hWnd, 0x4EE, 0, 0);

    return 1;
}

// GLOBAL: GAMEMD 0x7F5BE4 / 0x7F5BF0 -- the 800 x 600 layout the dialogs are
// designed for (entries of the width and height tables at 0x7F5BE0/0x7F5BEC).
extern int DAT_007F5BE4;
extern int DAT_007F5BF0;

// The margin that centres an 800 x 600 layout in a larger parent, or zero when
// the session flag says the layout fills the parent.
__forceinline static int Inline_CentreMargin(bool bFills, int nExtent, int nDesign)
{
    return bFills ? 0 : ((nExtent - nDesign) / 2 < 0 ? 0 : (nExtent - nDesign) / 2);
}

// FUNCTION: GAMEMD 0x60AF50  FUN_0060AF50 (__fastcall)
// Moves a control to its design rectangle, shifted by the centring margins
// of its parent, and repaints it.
void FUN_0060AF50(GG_HWND hWnd, RectangleStruct* pRect)
{
    GG_HWND hParent = GetParent(hWnd);
    bool bFills = DAT_00A8B238_Session.FUN_0069BBE0();
    GG_RECT rcParent;
    GetWindowRect(hParent, &rcParent);

    int nMarginX = Inline_CentreMargin(bFills, rcParent.right - rcParent.left, DAT_007F5BE4);
    int nMarginY = Inline_CentreMargin(bFills, rcParent.bottom - rcParent.top, DAT_007F5BF0);

    MoveWindow(hWnd, pRect->X + nMarginX, pRect->Y + nMarginY, pRect->Width, pRect->Height, 0);
    InvalidateRect(hWnd, 0, 0);
}

// FUNCTION: GAMEMD 0x60B740  FUN_0060B740
void FUN_0060B740(GG_HWND hWnd)
{
    GG_RECT rcSelf;
    GG_RECT rcParent;

    GG_HWND hParent = GetParent(hWnd);

    GetWindowRect(hParent, &rcParent);
    GetWindowRect(hWnd, &rcSelf);
    MoveWindow(hWnd, rcSelf.left - rcParent.left, rcSelf.top - rcParent.top,
               rcSelf.right - rcSelf.left, rcSelf.bottom - rcSelf.top, 0);
}

// FUNCTION: GAMEMD 0x60B880  FUN_0060B880
bool FUN_0060B880(int nKey, GG_HWND hCtl)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    int category = value ? value->Field6C : 0;
    int nCtlID = GetDlgCtrlID(hCtl);

    if (category == 0xB7 || category == 0x2B4 || category == 0xBBB ||
        category == 0xF5 || category == 0x2B5 || category == 0xB8 ||
        category == 0xA3 || category == 0xB6 || category == 0x10C ||
        category == 0x73 || category == 0xFF || category == 0xEA)
    {
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x60C4A0  FUN_0060C4A0
void FUN_0060C4A0(GG_HWND hWnd, long lParam)
{
    MoveWindow(hWnd, 0, 0, DAT_008A00A4, DAT_008A00A8, 0);
    DAT_00AC48A8 = hWnd;
    EnumChildWindows(hWnd, FUN_0060C0C0, lParam);
}

// FUNCTION: GAMEMD 0x60C4E0  FUN_0060C4E0 (__fastcall)
int FUN_0060C4E0(int nKey)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    return value ? value->Field74 : 0;
}

// FUNCTION: GAMEMD 0x60C7D0  FUN_0060C7D0 (__fastcall)
bool FUN_0060C7D0(int nKey)
{
    MapValue_00602B90* value = Inline_Probe(nKey);

    if (!value)
        return false;

    int category = value->Field6C;

    if (category == 0x10D || category == 0xD9 || category == 0xF0 ||
        category == 0xCE || category == 0x120 || category == 0x121 ||
        category == 0x115 || category == 0xD3 || category == 0xCF ||
        category == 0x11F || category == 0xC3 || category == 0x11B ||
        category == 0xE1 || category == 0x11E || category == 0xC4 ||
        category == 0x130 || category == 0xD0 || category == 0xFC ||
        category == 0x126)
    {
        value->FieldB0 = 2;
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x60C8D0  FUN_0060C8D0 (__fastcall)
bool FUN_0060C8D0(int nKey)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    return value ? value->FieldD6 : false;
}

// FUNCTION: GAMEMD 0x60C930  FUN_0060C930 (__fastcall)
bool FUN_0060C930(int nKey)
{
    MapValue_00602B90* value = Inline_Probe(nKey);

    if (!value)
        return false;

    int category = value->Field6C;

    if (category == 0xBC || category == 0xBD || category == 0x102 ||
        category == 0xC2 || category == 0xC9 || category == 0xBC6)
    {
        return value->FieldD6 = true;
    }

    return value->FieldD6 = false;
}

// FUNCTION: GAMEMD 0x60C9D0  FUN_0060C9D0 (__fastcall)
void FUN_0060C9D0(int nKey)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    if (value)
        value->FieldD6 = true;
}

// FUNCTION: GAMEMD 0x60CA30  FUN_0060CA30 (__fastcall)
void FUN_0060CA30(int nKey)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    if (value)
        value->FieldD6 = false;
}

// FUNCTION: GAMEMD 0x60CA90  FUN_0060CA90 (__fastcall)
bool FUN_0060CA90(int nKey)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    return value ? value->FieldD5 : false;
}

// FUNCTION: GAMEMD 0x60CAF0  FUN_0060CAF0 (__fastcall)
bool FUN_0060CAF0(int nKey)
{
    MapValue_00602B90* value = Inline_Probe(nKey);

    if (!value)
        return false;

    int category = value->Field6C;

    if (category == 0xBC || category == 0xBD || category == 0x102 ||
        category == 0xC2 || category == 0xC9 || category == 0xBC6 ||
        category == 0x105 || category == 0x6B || category == 0x113)
    {
        return value->FieldD5 = true;
    }

    return value->FieldD5 = false;
}

// FUNCTION: GAMEMD 0x60CBA0  FUN_0060CBA0 (__fastcall)
void FUN_0060CBA0(int nKey)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    if (value)
        value->FieldD5 = true;
}

// FUNCTION: GAMEMD 0x60CC00  FUN_0060CC00 (__fastcall)
void FUN_0060CC00(int nKey)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    if (value)
        value->FieldD5 = false;
}

// FUNCTION: GAMEMD 0x60CC60  FUN_0060CC60 (__fastcall)
bool FUN_0060CC60(int nKey)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    return value ? value->FieldD7 : false;
}

// FUNCTION: GAMEMD 0x60CCC0  FUN_0060CCC0 (__fastcall)
bool FUN_0060CCC0(int nKey)
{
    MapValue_00602B90* value = Inline_Probe(nKey);

    if (!value)
        return false;

    int category = value->Field6C;

    if (category == 0x103 || category == 0xBC7)
        return value->FieldD7 = true;

    return value->FieldD7 = false;
}

// FUNCTION: GAMEMD 0x60CD50  FUN_0060CD50 (__fastcall)
bool FUN_0060CD50(int nKey)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    return value ? value->FieldD8 : false;
}

// FUNCTION: GAMEMD 0x60CDB0  FUN_0060CDB0 (__fastcall)
bool FUN_0060CDB0(int nKey)
{
    MapValue_00602B90* value = Inline_Probe(nKey);

    if (!value)
        return false;

    int category = value->Field6C;

    if (category == 0x108 || category == 0xBC6)
    {
        return value->FieldD8 = true;
    }

    return value->FieldD8 = false;
}

// FUNCTION: GAMEMD 0x60CE40  FUN_0060CE40 (__fastcall)
int FUN_0060CE40(int nKey)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    return value ? value->FieldE0 : 0;
}

// FUNCTION: GAMEMD 0x60CEA0  FUN_0060CEA0 (__fastcall)
int FUN_0060CEA0(int nKey)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    return value ? value->FieldE4 : 0;
}

// FUNCTION: GAMEMD 0x60D2C0  FUN_0060D2C0 (__fastcall)
void FUN_0060D2C0(int nKey, int nValue)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    if (value)
        value->Field6C = nValue;
}

// FUNCTION: GAMEMD 0x60D320  FUN_0060D320 (__fastcall)
int FUN_0060D320(int nKey)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    return value ? value->Field6C : 0;
}

// FUNCTION: GAMEMD 0x0060D430
void FUN_0060D430()
{
}

// FUNCTION: GAMEMD 0x0060D440
void FUN_0060D440()
{
}

struct HWND__;
extern "C" __declspec(dllimport) long __stdcall DefWindowProcA(HWND__* hwnd, unsigned int msg, unsigned int wparam, long lparam);
// FUNCTION: GAMEMD 0x0060D520
long __stdcall FUN_0060D520(HWND__* hwnd, unsigned int msg, unsigned int wparam, long lparam)
{
    return DefWindowProcA(hwnd, msg, wparam, lparam);
}

// The tooltip globals 0xAC1CB8..0xAC1DD4 are declared in ownrdraw.h.

// FUNCTION: GAMEMD 0x6107A0  FUN_006107A0
// Static-initialiser shape: clears a run of globals.
void FUN_006107A0()
{
    DAT_00AC1CB8.X = 0;
    DAT_00AC1CB8.Y = 0;
    DAT_00AC1CB8.Width = 0;
    DAT_00AC1CB8.Height = 0;
    DAT_00AC1CC8 = 0;
    DAT_00AC1CCC[0] = 0;
    DAT_00AC1DCC = 0;
    DAT_00AC1DD0 = 0;
    DAT_00AC1DD4 = 0;
}

// FUNCTION: GAMEMD 0x6107E0  Obj_006107E0::Obj_006107E0 (__thiscall)
Obj_006107E0::Obj_006107E0()
{
    unknown_00 = 0;
    unknown_04 = 0;
    unknown_08 = 0;
    unknown_0C = 0;
    unknown_10 = 0;
    unknown_14[0] = 0;
    unknown_114 = 0;
    unknown_118 = 0;
    unknown_11C = 0;
}

// FUNCTION: GAMEMD 0x610810  FUN_00610810 (__fastcall)
// Raises a tooltip: takes down the one already up (putting its background
// back once), then records the rectangle, the text (the "GUI:ToolTip" string
// unless the caller gives one) and the time, and draws it through 0x610950.
void FUN_00610810(RectangleStruct* pRect, const wchar_t* pText, int nValue)
{
    if (DAT_00AC1DCC != 0)
    {
        if (DAT_00AC1DD0 != 1 && DAT_00AC1CC8 != 0)
        {
            RectangleStruct rcScreen = DAT_00AC1CB8;
            RectangleStruct rcSaved;
            rcSaved.X = 0;
            rcSaved.Y = 0;
            rcSaved.Width = DAT_00AC1CB8.Width;
            rcSaved.Height = DAT_00AC1CB8.Height;
            DAT_00887308->CopyFromPart(&rcScreen, DAT_00AC1CC8, &rcSaved, false, true);
            DAT_00AC1DD0 = 1;
        }

        if (DAT_00AC1CC8 != 0)
            delete DAT_00AC1CC8;

        DAT_00AC1CC8 = 0;
        DAT_00AC1DCC = 0;
        DAT_00AC1DD0 = 0;
    }

    DAT_00AC48D8 = time(0);
    swprintf(DAT_00AC1CCC, FUN_00734E60(
        // STRING: GAMEMD 0x00835868
        "GUI:ToolTip", 0,
        // STRING: GAMEMD 0x00833730
        "D:\\ra2mdpost\\ownrdraw.cpp", 0x1D21));

    if (pText != 0)
        wcscpy(DAT_00AC1CCC, pText);

    DAT_00AC1CB8 = *pRect;
    DAT_00AC1DCC = 1;
    DAT_00AC1DD4 = nValue;
    FUN_00610950(true);
}

// FUNCTION: GAMEMD 0x00612910
void FUN_00612910()
{
    void* block = DAT_00AC1DE0.data;
    DAT_00AC1DE0.count = 0;
    gg_free(block);
}

// FUNCTION: GAMEMD 0x621040  FUN_00621040 (__fastcall)
// Prints text into a rectangle with the given font. The colour arrives as
// a Win32 COLORREF (0x00BBGGRR) and is packed to the display's pixel format with the shift
// globals at 0x8A0DD0..0x8A0DE4. Flag 4 centres the text vertically.
int FUN_00621040(Surface* pSurface, const unsigned short* pText, BitFontBounds* pBounds,
                 BitFont* pFont, unsigned long nColor, int nFlags, int nUnused1,
                 int nUnused2, int nFadeStart, int nFadeLength)
{
    unsigned char red = (unsigned char)nColor;
    unsigned char green = (unsigned char)((unsigned short)nColor >> 8);
    unsigned char blue = (unsigned char)(nColor >> 16);
    unsigned nPixel = ((green >> DAT_008A0DE4) << DAT_008A0DE0)
                    | ((blue >> DAT_008A0DDC) << DAT_008A0DD8)
                    | ((red >> DAT_008A0DD4) << DAT_008A0DD0);

    int x = pBounds->Left;
    int y = pBounds->Top;
    int nWidth = pBounds->Right - x;
    int nHeight = pBounds->Bottom - y;

    if (nFlags & 4)
    {
        int nTextWidth;
        int nTextHeight;
        pFont->FUN_00433CF0(pText, &nTextWidth, &nTextHeight, nWidth);
        y += (nHeight - nTextHeight) / 2;
    }

    pFont->FUN_00433C90(1);
    pFont->FUN_00433CA0(pBounds);
    pFont->FUN_00433C70((short)nPixel);
    DAT_0089C4B8->FUN_00434CD0(pFont, pSurface, pText, x, y, nWidth, nHeight, nFlags,
                               nFadeStart, nFadeLength);
    return 0;
}

// FUNCTION: GAMEMD 0x6213A0  FUN_006213A0 (__fastcall)
// Owner-draw notice for a button (type 4): records the item state in the
// control's entry (+0xE8) and repaints the item rectangle.
void FUN_006213A0(DrawItem_006213A0* pItem)
{
    if (DAT_00887308 != 0 && DAT_00887310 != 0)
    {
        GG_RECT rcWindow;
        FUN_00775690(pItem->hwndItem, &rcWindow);
        GG_RECT rcClient;
        GetClientRect(pItem->hwndItem, &rcClient);

        if (GetWindowLongA(pItem->hwndItem, -16) & 0x800000)
        {
            int nBorderX = GetSystemMetrics(5);
            int nBorderY = GetSystemMetrics(6);
            rcWindow.left += nBorderX;
            rcWindow.right -= nBorderX;
            rcWindow.top += nBorderY;
            rcWindow.bottom -= nBorderY;
        }

        if (pItem->CtlType == 4)
        {
            GG_HWND hWnd = pItem->hwndItem;
            MapValue_00602B90* pValue = Inline_Probe((int)hWnd);

            if (pValue != 0)
            {
                pValue->FieldE8 = pItem->itemState;
                InvalidateRect(hWnd, &pItem->rcItem, 0);
                UpdateWindow(hWnd);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x621D30
void FUN_00621d30(Rect_00621D30* rect, void* dest)
{
    Palette_00621D30 palette;
    void* image = DAT_00ac4848.GetSurface("bits_i.pcx", &palette);
    void* alpha = DAT_00ac4848.GetSurface("bits_a.pcx", NULL);
    int count = 0;
    palette.FUN_006B93E0();

    Rect_00621D30 area = *rect;
    for (int offset = 0; offset < rect->Width; offset += 10) {
        int frame = rand() % 8;
        area.X = rect->X + offset;
        area.Y = rect->Y + 1;
        area.Width = 10;
        area.Height = 12;
        DAT_00ac4848.Draw(&area, dest, image, alpha, &palette, 0, frame * 10, 0);

        frame = rand() % 8;
        area.X = rect->X + offset;
        area.Width = 10;
        area.Height = 12;
        area.Y = rect->Y + rect->Height - 16;
        DAT_00ac4848.Draw(&area, dest, image, alpha, &palette, 0, frame * 10, 0);

        count++;
        if (count % 6 == 0) {
            offset += 10;
        }
    }
}

// The object a dialog entry owns at +0x10; only its virtual deleting
// destructor is used here.
struct Hook_006223C0
{
    virtual ~Hook_006223C0();
};

// FUNCTION: GAMEMD 0x6223C0  FUN_006223C0 (__fastcall)
void FUN_006223C0(int nKey)
{
    MapValue_00602B90* value = Inline_Probe(nKey);

    if (value && value->Field10)
    {
        delete value->Field10;
        value->Field10 = 0;
        DAT_00AC48B4--;
    }
}

// FUNCTION: GAMEMD 0x622800  UI::FocusOnWindow (__fastcall)
void UI_FocusOnWindow(HWND hWnd)
{
    ShowWindow(hWnd, 1);            // SW_SHOWNORMAL
    SetForegroundWindow(hWnd);
    DAT_0087F770->DoSomething();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x623120  (static, __cdecl)
// ---------------------------------------------------------------------------
bool UI::Updated()
{
    FUN_005D4D50();

    if (SessionGameMode == 0 || SessionGameMode == 5 ||
        InhibitFlag != 0 || InhibitWord != 0)
    {
        CallBack();
        return false;
    }

    if (!PredicateA() && PredicateB())
        return true;

    return false;
}

// FUNCTION: GAMEMD 0x623310  FUN_00623310
void FUN_00623310(GG_HWND hDlg, long lParam)
{
    GG_HWND hItem = GetDlgItem(hDlg, 0x5B0);
    SendMessageA(hItem, 0x4B2, 0, lParam);
    UpdateWindow(hDlg);
}


// The list unlink that 0x623460 performs, expanded inline.
inline void Obj_00623420::Inline_Unlink(TextNode_00623420* pNode)
{
    TextNode_00623420* prev = 0;
    TextNode_00623420* cur = TextList;

    for (; cur != 0; cur = cur->Next)
    {
        if (pNode == cur)
            break;

        prev = cur;
    }

    if (cur != 0)
    {
        if (prev != 0)
        {
            prev->Next = cur->Next;
            delete cur;
        }
        else
        {
            TextList = cur->Next;
            delete cur;
        }
    }
}

// The text replacement that 0x623560 performs, expanded inline.
inline void Obj_00623420::Inline_SetText(const wchar_t* pszText)
{
    if (Text != 0)
    {
        delete Text;
        Text = 0;
    }

    if (pszText != 0 && *pszText != 0)
    {
        Text = new wchar_t[wcslen(pszText) + 1];
        wcscpy(Text, pszText);
    }
}

// Prepend a copy of one source node to the list: the allocation of 0x623420,
// then the two words and the text copied across.
inline void Obj_00623420::Inline_AddCopy(const TextNode_00623420* pSource)
{
    TextNode_00623420* node =
        (TextNode_00623420*)operator new(wcslen(pSource->Text) * 2 + 0x12);

    if (node)
    {
        node->Text = node->Buffer;
        node->Next = TextList;
        node->unknown_04 = 0;
        TextList = node;
    }

    node->unknown_0C = pSource->unknown_0C;
    node->unknown_04 = pSource->unknown_04;
    wcscpy(node->Text, pSource->Text);
}

// FUNCTION: GAMEMD 0x623340  Obj_00623420::Obj_00623420 (__thiscall)
Obj_00623420::Obj_00623420()
{
    memset(this, 0, sizeof(Obj_00623420));
    unknown_68 = 0xB;
    unknown_64 = DAT_0089C4D0;
    unknown_3C = new Obj_007B66D0();
    unknown_40 = 0;
    unknown_5C = 0;
    unknown_90 = -1;
}

// FUNCTION: GAMEMD 0x6233A0  Obj_00623420::~Obj_00623420 (__thiscall)
Obj_00623420::~Obj_00623420()
{
    if (Text != 0)
    {
        delete Text;
        Text = 0;
    }

    while (TextList != 0)
        Inline_Unlink(TextList);

    delete unknown_3C;
}

// FUNCTION: GAMEMD 0x623420  Obj_00623420::FUN_00623420 (__thiscall)
void Obj_00623420::FUN_00623420(int nChars)
{
    TextNode_00623420* node = (TextNode_00623420*)operator new(nChars * 2 + 0x12);

    if (node)
    {
        node->Text = node->Buffer;
        node->Next = TextList;
        node->unknown_04 = 0;
        TextList = node;
    }
}

// FUNCTION: GAMEMD 0x623460  Obj_00623420::FUN_00623460 (__thiscall)
void Obj_00623420::FUN_00623460(TextNode_00623420* pNode)
{
    TextNode_00623420* prev = 0;
    TextNode_00623420* cur = TextList;

    for (; cur != 0; cur = cur->Next)
    {
        if (pNode == cur)
            break;

        prev = cur;
    }

    if (cur != 0)
    {
        if (prev != 0)
        {
            prev->Next = cur->Next;
            delete cur;
        }
        else
        {
            TextList = cur->Next;
            delete cur;
        }
    }
}

// FUNCTION: GAMEMD 0x6234B0  Obj_00623420::FUN_006234B0 (__thiscall)
void Obj_00623420::FUN_006234B0(const TextNode_00623420* pSource)
{
    while (TextList != 0)
        Inline_Unlink(TextList);

    for (; pSource != 0; pSource = pSource->Next)
        Inline_AddCopy(pSource);
}

// FUNCTION: GAMEMD 0x623560  Obj_00623420::FUN_00623560 (__thiscall)
void Obj_00623420::FUN_00623560(const wchar_t* pszText)
{
    if (Text != 0)
    {
        delete Text;
        Text = 0;
    }

    if (pszText != 0 && *pszText != 0)
    {
        Text = new wchar_t[wcslen(pszText) + 1];
        wcscpy(Text, pszText);
    }
}

// FUNCTION: GAMEMD 0x6235B0  Obj_00623420::FUN_006235B0 (__thiscall)
// STRING: GAMEMD 0x835874  L"%hs"
void Obj_00623420::FUN_006235B0(const char* pszText)
{
    if (Text != 0)
    {
        delete Text;
        Text = 0;
    }

    if (pszText != 0 && *pszText != 0)
    {
        Text = new wchar_t[strlen(pszText) + 1];
        swprintf(Text, L"%hs", pszText);
    }
}

// FUNCTION: GAMEMD 0x623610  Obj_00623420::FUN_00623610 (__thiscall)
Obj_00623420* Obj_00623420::FUN_00623610(const Obj_00623420& other)
{
    TextNode_00623420* pList = TextList;
    wchar_t* pText = Text;
    Obj_007B66D0* pHeld = unknown_3C;

    if (this == &other)
        return this;

    memcpy(this, &other, sizeof(Obj_00623420));
    Text = pText;
    unknown_3C = pHeld;
    TextList = pList;

    const wchar_t* pszSource = other.Text;
    Inline_SetText(pszSource);

    const TextNode_00623420* pSource = other.TextList;

    while (TextList != 0)
        Inline_Unlink(TextList);

    for (; pSource != 0; pSource = pSource->Next)
        Inline_AddCopy(pSource);

    return this;
}

// FUNCTION: GAMEMD 0x623730  Obj_00623420::FUN_00623730 (__thiscall)
Obj_00623420* Obj_00623420::FUN_00623730(const Obj_00623420& other)
{
    TextNode_00623420* pList = TextList;
    wchar_t* pText = Text;
    Obj_007B66D0* pHeld = unknown_3C;

    memcpy(this, &other, sizeof(Obj_00623420));
    unknown_3C = pHeld;
    Text = pText;
    TextList = pList;

    const wchar_t* pszSource = other.Text;
    Inline_SetText(pszSource);

    const TextNode_00623420* pSource = other.TextList;

    while (TextList != 0)
        Inline_Unlink(TextList);

    for (; pSource != 0; pSource = pSource->Next)
        Inline_AddCopy(pSource);

    return this;
}

// FUNCTION: GAMEMD 0x622B50 (decl; reloc) -- the shared dialog message handler.
int FUN_00622B50(GG_HWND hWnd, unsigned int uMsg, unsigned int wParam, long lParam);

// FUNCTION: GAMEMD 0x623DA0  FUN_00623DA0
// Dialog procedure: after the shared handler declines the message, a click on
// control 0x5C0 or 0x5C1 stores that id in the result slot kept in the
// window's user data.
int __stdcall FUN_00623DA0(GG_HWND hWnd, unsigned int uMsg, unsigned int wParam, long lParam)
{
    int nHandled = FUN_00622B50(hWnd, uMsg, wParam, lParam);

    if (nHandled != 0)
        return nHandled;

    int* pResult = (int*)GetWindowLongA(hWnd, 8);

    if (uMsg == 0x111)
    {
        int nId = wParam & 0xFFFF;

        if (nId >= 0x5C0 && nId <= 0x5C1)
            *pResult = nId;
    }

    return 0;
}

// FUNCTION: GAMEMD 0x623E00  FUN_00623E00
int FUN_00623E00(GG_HWND hList)
{
    int n = SendMessageA(hList, 0x18B, 0, 0);

    while (n-- != 0)
        SendMessageA(hList, 0x182, n, 0);

    return 0;
}

// FUNCTION: GAMEMD 0x623E40  FUN_00623E40
int FUN_00623E40(GG_HWND hWnd, Obj_007B4620* pOut)
{
    int nLength = SendMessageA(hWnd, 0xE, 0, 0);

    if (nLength <= 0)
    {
        pOut->Reset();
        return 0;
    }

    char* pszBuffer = new char[nLength + 2];
    int nCopied = SendMessageA(hWnd, 0x4B5, nLength + 1, (long)pszBuffer);

    pOut->FUN_007B48D0(pszBuffer);
    delete pszBuffer;
    return nCopied;
}

// FUNCTION: GAMEMD 0x623EA0  FUN_00623EA0
int FUN_00623EA0(GG_HWND hWnd, Obj_007B66D0* pOut)
{
    int nLength = SendMessageA(hWnd, 0xE, 0, 0);

    if (nLength <= 0)
    {
        pOut->FUN_007B7040();
        return 0;
    }

    wchar_t* pszBuffer = new wchar_t[nLength + 2];
    int nCopied = SendMessageA(hWnd, 0x4B3, nLength + 1, (long)pszBuffer);

    *pOut = pszBuffer;
    delete pszBuffer;
    return nCopied;
}

// FUNCTION: GAMEMD 0x623F00  FUN_00623F00
int FUN_00623F00(GG_HWND hWnd, int nIndex, Obj_007B4620* pOut)
{
    int nLength = SendMessageA(hWnd, 0x18A, nIndex, 0);

    if (nLength <= 0)
        pOut->Reset();

    char* pszBuffer = new char[nLength + 2];
    int nCopied = SendMessageA(hWnd, 0x4B7, nIndex, (long)pszBuffer);

    pOut->FUN_007B48D0(pszBuffer);
    delete pszBuffer;
    return nCopied;
}

// FUNCTION: GAMEMD 0x623F60  FUN_00623F60
int FUN_00623F60(GG_HWND hWnd, int nIndex, Obj_007B66D0* pOut)
{
    int nLength = SendMessageA(hWnd, 0x18A, nIndex, 0);

    if (nLength <= 0)
        pOut->FUN_007B7040();

    wchar_t* pszBuffer = new wchar_t[nLength + 2];
    int nCopied = SendMessageA(hWnd, 0x4B6, nIndex, (long)pszBuffer);

    *pOut = pszBuffer;
    delete pszBuffer;
    return nCopied;
}

// FUNCTION: GAMEMD 0x623FC0  FUN_00623FC0
int FUN_00623FC0(GG_HWND hWnd, int nIndex, Obj_007B4620* pOut)
{
    int nLength = SendMessageA(hWnd, 0x149, nIndex, 0);

    if (nLength <= 0)
        pOut->Reset();

    char* pszBuffer = new char[nLength + 2];
    int nCopied = SendMessageA(hWnd, 0x4BD, nIndex, (long)pszBuffer);

    pOut->FUN_007B48D0(pszBuffer);
    delete pszBuffer;
    return nCopied;
}

// FUNCTION: GAMEMD 0x624020  FUN_00624020
int FUN_00624020(GG_HWND hWnd, int nIndex, Obj_007B66D0* pOut)
{
    int nLength = SendMessageA(hWnd, 0x149, nIndex, 0);

    if (nLength <= 0)
        pOut->FUN_007B7040();

    wchar_t* pszBuffer = new wchar_t[nLength + 2];
    int nCopied = SendMessageA(hWnd, 0x4C3, nIndex, (long)pszBuffer);

    *pOut = pszBuffer;
    delete pszBuffer;
    return nCopied;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x624080
// Stores its argument in a member.
Obj_00624080* Obj_00624080::FUN_00624080()
{
    unknown_00 = 0x7EF720;
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x624090
// Stores its argument in a member.
void Obj_00624090::FUN_00624090()
{
    unknown_00 = 0x7EF720;
}

// FUNCTION: GAMEMD 0x6240A0  FUN_006240A0
void __stdcall FUN_006240A0(int nKey, int unused)
{
    MapValue_00602B90* value = Inline_Probe(nKey);
    if (value)
        value->FieldD4 = true;
}

// A dialog-control object (+0x04 word, +0x08 byte). Placeholder view of the record.
struct Obj_00624110
{
    void*         unknown_00;   // +0x00 vtable pointer
    int           unknown_04;   // +0x04
    unsigned char unknown_08;   // +0x08

    // FUNCTION: GAMEMD 0x624140 (__thiscall)
    void FUN_00624140(int nKey, int nValue);
};
GG_STATIC_ASSERT(offsetof(Obj_00624110, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(Obj_00624110, unknown_08) == 0x08);

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x624130
// VTABLE: GAMEMD 0x7EF720
void FUN_00624130(ConstStoreObject* self)
{
    self->Head = VTABLE_007EF720;
}

// FUNCTION: GAMEMD 0x624140  Obj_00624110::FUN_00624140 (__thiscall)
void Obj_00624110::FUN_00624140(int nKey, int nValue)
{
    unknown_04 = nValue;

    MapValue_00602B90* value = Inline_Probe(nKey);

    if (value)
        value->FieldD4 = true;

    unknown_08 = true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6241C0
// Member getter (byte). Vtable slot 2 of OwnerDraw::SimpleDialogControl (RTTI) and 4 derived vtable(s).
unsigned char Obj_006241C0::FUN_006241C0() const
{
    return unknown_08;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6241D0
int FUN_006241D0(LeafObj_0x04* self)
{
    return self->unknown_04;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6241E0
// Returns a constant boolean. Vtable slot 4 of OwnerDraw::SimpleDialogControl (RTTI) and 1 derived vtable(s).
bool Obj_006241E0::FUN_006241E0() const
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6244A0 -- OwnerDraw::DialogControl scalar deleting destructor
void* OwnerDraw::DialogControl::DeletingDtor(unsigned int flags)
{
    this->~DialogControl();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6244C0 -- OwnerDraw::SimpleDialogControl scalar deleting destructor
void* OwnerDraw::SimpleDialogControl::DeletingDtor(unsigned int flags)
{
    this->~SimpleDialogControl();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x6244E0  Obj_006244E0::FUN_006244E0 (__thiscall)
void Obj_006244E0::FUN_006244E0()
{
    for (int i = 0; i < Count; i++)
    {
        Entry_006244E0* pEntry = &Entries[i];

        pEntry->unknown_08.~Obj_007B66D0();
        pEntry->unknown_04.~Obj_007B66D0();
    }

    Count = 0;
}

// FUNCTION: GAMEMD 0x624760  HashTable_006249A0<int, MapValue_00602B90>::Find
// FUNCTION: GAMEMD 0x624930  HashTable_006249A0<int, int>::Find
template<class KEY, class VALUE>
bool HashTable_006249A0<KEY, VALUE>::Find(const KEY& key, VALUE*& pValue)
{
    if (this->Count == 0)
        return false;

    int hash = this->Hash(&key);
    unsigned idx = ((1 << this->BitWidth) - 1) & hash;
    Node* node = this->Buckets[idx];

    if (node == 0)
        return false;

    while (node != 0)
    {
        if (node->Key == key)
            break;

        node = node->Next;
    }

    if (node == 0)
        return false;

    pValue = &node->Value;
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x624C80
int HashTableIndex::FUN_00624C80(const void* key)
{
    int hash = this->Hash(key);

    return ((1 << this->BitWidth) - 1) & hash;
}

// The dialog hash table's node: the chain link sits at +0x204 (the end of the
// 0x200-byte MapValue behind the key).
GG_REHASH_NODE(00624FC0, 204);

// FUNCTION: GAMEMD 0x624FC0
// Doubles the dialog hash table, chain link at +0x204. The halving member the
// instantiation also emits is the table's other direction, matched at 0x625830.
template struct HashTable<Node_00624FC0>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x625070
int HashTableIndex::FUN_00625070(const void* key)
{
    int hash = this->Hash(key);

    return ((1 << this->BitWidth) - 1) & hash;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x625390
int HashTableIndex::FUN_00625390(const void* key)
{
    int hash = this->Hash(key);

    return ((1 << this->BitWidth) - 1) & hash;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x006253B0
bool Obj_006253B0::FUN_006253B0()
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

// Shrink step of a plain-old-data array holder (count at +0x00, capacity at
// +0x04, heap block at +0x08): refused while the count exceeds a third of the
// capacity; otherwise the capacity is halved (floor of ten) and the live
// elements are copied into a block of the new size.
struct Obj_00625440 {
    int count;     // +0x00
    int capacity;  // +0x04
    int* data;     // +0x08
    bool FUN_00625440();
};
GG_STATIC_ASSERT(offsetof(Obj_00625440, data) == 0x08);
// FUNCTION: GAMEMD 0x00625440
bool Obj_00625440::FUN_00625440()
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

// Growable array of 0x14-byte elements: count, capacity, storage.
struct Vector20_006254D0
{
    int   Count;       // +0x00
    int   Capacity;    // +0x04
    char* Items;       // +0x08

    // FUNCTION: GAMEMD 0x6254D0 (__thiscall)
    bool FUN_006254D0();
    // FUNCTION: GAMEMD 0x625A20 (__thiscall)
    bool FUN_00625A20();
};
GG_STATIC_ASSERT(offsetof(Vector20_006254D0, Capacity) == 0x04);
GG_STATIC_ASSERT(offsetof(Vector20_006254D0, Items) == 0x08);
GG_STATIC_ASSERT(sizeof(Vector20_006254D0) == 0x0C);

// FUNCTION: GAMEMD 0x6254D0  Vector20_006254D0::FUN_006254D0 (__thiscall)
// Halves the storage (never below ten elements) when the count has fallen
// to a third of the capacity.
bool Vector20_006254D0::FUN_006254D0()
{
    if (Count * 3 > Capacity)
        return false;

    int nNew = Capacity / 2;

    if (nNew < 10)
        nNew = 10;

    if (nNew >= Capacity)
        return false;

    char* pNew = new char[nNew * 20];

    if (Items)
        memcpy(pNew, Items, Count * 20);

    delete Items;
    Items = pNew;
    Capacity = nNew;
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6255F0
EntryRecord_006255F0::EntryRecord_006255F0(const EntryRecord_006255F0& other) :
    unknown_00(other.unknown_00),
    unknown_04(other.unknown_04)
{
    ListEntry_006255F0 entry;
    List.Clear();
    for (int index = 0; index < other.List.Count; index++) {
        other.List.Get(index, entry);
        List.Add(entry);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00625990
bool Obj_00625990::FUN_00625990()
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

GG_REHASH_NODE(00625830, 204);

// FUNCTION: GAMEMD 0x625830
// Halves the dialog hash table, chain link at +0x204.
template struct HashTable<Node_00625830>;

// FUNCTION: GAMEMD 0x625A20  Vector20_006254D0::FUN_00625A20 (__thiscall)
// Doubles the storage (at least ten elements) once the count reaches the
// capacity; the new storage is zeroed before the old contents are copied in.
bool Vector20_006254D0::FUN_00625A20()
{
    if (Count < Capacity)
        return false;

    int nNew = Count * 2;

    if (nNew < 10)
        nNew = 10;

    char* pNew = new char[nNew * 20];
    memset(pNew, 0, nNew * 20);

    if (Items)
        memcpy(pNew, Items, Count * 20);

    delete Items;
    Capacity = nNew;
    Items = pNew;
    return true;
}

struct Node_00625D60 {
    char unknown_00[4];
    int unknown_04;
    unsigned char* unknown_08;
    Node_00625D60* unknown_0C;
};
GG_STATIC_ASSERT(offsetof(Node_00625D60, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(Node_00625D60, unknown_0C) == 0x0C);
struct Obj_00625D60 {
    int unknown_00;
    Node_00625D60* unknown_04;
    Node_00625D60* Find(const char* key)
    {
        for (Node_00625D60* node = unknown_04; node != 0; node = node->unknown_0C) {
            if (strncmp(key, node->unknown_00, 4) == 0)
                return node;
        }
        return 0;
    }
    bool FUN_00625D60(const char* key, unsigned char* out);
    bool FUN_00625DB0(const char* key, unsigned char* out);
};
GG_STATIC_ASSERT(offsetof(Obj_00625D60, unknown_04) == 0x04);
// FUNCTION: GAMEMD 0x00625D60
bool Obj_00625D60::FUN_00625D60(const char* key, unsigned char* out)
{
    Node_00625D60* node = Find(key);
    if (node != 0)
        *out = *node->unknown_08;
    return node ? true : false;
}

// FUNCTION: GAMEMD 0x00625DB0
bool Obj_00625D60::FUN_00625DB0(const char* key, unsigned char* out)
{
    Node_00625D60* node = Find(key);
    if (node != 0)
        *out = *node->unknown_08;
    return node ? true : false;
}

struct Node_00625E00 {
    char unknown_00[4];
    int unknown_04;
    unsigned short* unknown_08;
    Node_00625E00* unknown_0C;
};
GG_STATIC_ASSERT(offsetof(Node_00625E00, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(Node_00625E00, unknown_0C) == 0x0C);
struct Obj_00625E00 {
    int unknown_00;
    Node_00625E00* unknown_04;
    Node_00625E00* Find(const char* key)
    {
        for (Node_00625E00* node = unknown_04; node != 0; node = node->unknown_0C) {
            if (strncmp(key, node->unknown_00, 4) == 0)
                return node;
        }
        return 0;
    }
    bool FUN_00625E00(const char* key, unsigned short* out);
    bool FUN_00625E50(const char* key, unsigned short* out);
};
GG_STATIC_ASSERT(offsetof(Obj_00625E00, unknown_04) == 0x04);
// FUNCTION: GAMEMD 0x00625E00
bool Obj_00625E00::FUN_00625E00(const char* key, unsigned short* out)
{
    Node_00625E00* node = Find(key);
    if (node != 0)
        *out = *node->unknown_08;
    return node ? true : false;
}

// FUNCTION: GAMEMD 0x00625E50
bool Obj_00625E00::FUN_00625E50(const char* key, unsigned short* out)
{
    Node_00625E00* node = Find(key);
    if (node != 0)
        *out = *node->unknown_08;
    return node ? true : false;
}

struct Node_00625EA0 {
    char unknown_00[4];
    int unknown_04;
    unsigned int* unknown_08;
    Node_00625EA0* unknown_0C;
};
GG_STATIC_ASSERT(offsetof(Node_00625EA0, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(Node_00625EA0, unknown_0C) == 0x0C);
struct Obj_00625EA0 {
    int unknown_00;
    Node_00625EA0* unknown_04;
    Node_00625EA0* Find(const char* key)
    {
        for (Node_00625EA0* node = unknown_04; node != 0; node = node->unknown_0C) {
            if (strncmp(key, node->unknown_00, 4) == 0)
                return node;
        }
        return 0;
    }
    bool FUN_00625EA0(const char* key, unsigned int* out);
    bool FUN_00625F60(const char* key, unsigned int* out);
};
GG_STATIC_ASSERT(offsetof(Obj_00625EA0, unknown_04) == 0x04);
// FUNCTION: GAMEMD 0x00625EA0
bool Obj_00625EA0::FUN_00625EA0(const char* key, unsigned int* out)
{
    Node_00625EA0* node = Find(key);
    if (node != 0)
        *out = *node->unknown_08;
    return node ? true : false;
}

// FUNCTION: GAMEMD 0x00625F60
bool Obj_00625EA0::FUN_00625F60(const char* key, unsigned int* out)
{
    Node_00625EA0* node = Find(key);
    if (node != 0)
        *out = *node->unknown_08;
    return node ? true : false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x625AF0  PacketClass::PacketClass (__thiscall)
// Parses a received packet: the size and ID words, then each field's 8-byte
// header and payload, payloads padded to a 4-byte boundary. Fields are pushed
// on the front of the list and converted to host order as they are read.
PacketClass::PacketClass(char* pBuffer)
{
    Size = *(unsigned short*)pBuffer;
    pBuffer += 2;
    Size = ntohs(Size);
    ID = *(unsigned short*)pBuffer;
    pBuffer += 2;
    ID = ntohs(ID);
    Head = 0;

    int nRemaining = Size - 4;

    while (nRemaining > 0)
    {
        FieldClass* pField = new FieldClass;
        memcpy(pField, pBuffer, 8);
        pBuffer += 8;

        int nDataSize = ntohs(pField->Size);
        pField->Data = new char[nDataSize];
        memcpy(pField->Data, pBuffer, nDataSize);

        int nPad = -(ntohs(pField->Size) & 3) & 3;
        pBuffer += nDataSize + nPad;
        nRemaining -= 8 + nPad + nDataSize;

        pField->NetToHost();
        pField->Next = Head;
        Head = pField;
    }
}

// FUNCTION: GAMEMD 0x626070
ColorTable_00626070::ColorTable_00626070(const ColorTable_00626070& other)
{
    *this = other;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x626120
void ColorTable_00626070::FUN_00626120(int ratio, const ColorTable_00626070& target)
{
    for (int i = 0; i < 256; i++) {
        Colors[i].Blend(ratio, target[i]);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x626170
void ColorTable_00626070::FUN_00626170(int ratio, const char* marks)
{
    for (int i = 0; i < 256; i++) {
        if (marks[i]) {
            Colors[i].Blend(ratio, DAT_00A83CD9);
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6261B0
void ColorTable_00626070::FUN_006261B0(int ratio, const ColorTable_00626070& target, const char* marks)
{
    for (int i = 0; i < 256; i++) {
        if (marks[i]) {
            Colors[i].Blend(ratio, target[i]);
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x626200
int ColorTable_00626070::Nearest(const ColorRGB_00661350& color) const
{
    int best = 0;
    int bestDiff = -1;
    const ColorRGB_00661350* entry = Colors;
    for (int i = 0; i < 256; i++) {
        int diff = color.Difference(*entry++);
        if (bestDiff == -1 || diff < bestDiff) {
            bestDiff = diff;
            best = i;
        }
    }
    return best;
}

// FUNCTION: GAMEMD 0x626250  Obj_00626250::Obj_00626250 (__thiscall)
Obj_00626250::Obj_00626250(const char* pszName, DynamicVectorClass<Obj_0068C8D0*>* pUnknown)
{
    strcpy(Name, pszName);
    unknown_100 = pUnknown;
}

// FUNCTION: GAMEMD 0x626290  Obj_00626250::FUN_00626290 (__thiscall)
void Obj_00626250::FUN_00626290()
{
    Inline_Release();
}

// FUNCTION: GAMEMD 0x6262F0  Obj_00626250::FUN_006262F0 (__thiscall)
void Obj_00626250::FUN_006262F0(DynamicVectorClass<Obj_0068C8D0*>* pUnknown)
{
    Inline_Release();
    unknown_100 = pUnknown;
}

// FUNCTION: GAMEMD 0x626370  Obj_00626250::FUN_00626370 (__thiscall)
void Obj_00626250::FUN_00626370()
{
    Inline_Release();
}

// FUNCTION: GAMEMD 0x626660  FUN_00626660
int FUN_00626660(const char* pszName)
{
    int hash = 0;

    while (*pszName != 0)
    {
        hash = (hash * 26 + *pszName) % 31;
        pszName++;
    }

    return hash;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x626C60
//
// Number of colour schemes: lazily builds the palette-table owner on first
// use and answers the count of its first scheme vector.
int ColorScheme_00626C60::GetNumberOfSchemes()
{
    if (DAT_00AC48F0 == 0) {
        DAT_00AC48F0 = new Owner_00626C60();
    }
    return DAT_00AC48F0->VecA->Count;
}

// FUNCTION: GAMEMD 0x626FF0  FUN_00626FF0
void FUN_00626FF0()
{
    if (DAT_00AC48F0 != 0)
    {
        delete DAT_00AC48F0;
        DAT_00AC48F0 = 0;
    }
}

// FUNCTION: GAMEMD 0x627A10  Owner_00626C60::FUN_00627A10 (__thiscall)
// Rebuilds the scheme list of the named palette: frees the old list and its
// entries and installs the one 0x627590 builds.
void Owner_00626C60::FUN_00627A10(const char* pszName)
{
    PaletteKey_00626C60 key;
    key.FUN_004F4C30(pszName);
    Obj_00626250* pPalette = *Table->Find(key);
    DynamicVectorClass<Obj_0068C8D0*>* pSchemes = FUN_00627590(pszName);
    pPalette->Inline_Release();
    pPalette->unknown_100 = pSchemes;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x006281F0
// VectorClass<HSVClass>::operator==
// FUNCTION: GAMEMD 0x00628240
// DynamicVectorClass<HSVClass>::DynamicVectorClass
// FUNCTION: GAMEMD 0x006282E0
// VectorClass<HSVClass>::SetCapacity
// FUNCTION: GAMEMD 0x00628410
// VectorClass<HSVClass>::FindItemIndex
// FUNCTION: GAMEMD 0x00628470
// VectorClass<HSVClass>::Slot5
// FUNCTION: GAMEMD 0x00627DE0
// VectorClass<HSVClass>::Slot6
// FUNCTION: GAMEMD 0x006284A0
// DynamicVectorClass<HSVClass>::SetCapacity
// FUNCTION: GAMEMD 0x00627DB0
// DynamicVectorClass<HSVClass>::Slot5
// VTABLE: GAMEMD 0x007EF7F0 -- VectorClass<HSVClass>.
// VTABLE: GAMEMD 0x007EF750 -- DynamicVectorClass<HSVClass>.
template class VectorClass<HSVClass>;
