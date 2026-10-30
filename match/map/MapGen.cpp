// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit MapGen.cpp. The name is the source-file string at 0x82ba48
//   in retail gamemd.exe v1.001, passed by the assert at 0x5956ec inside this object's
//   code range (0x58b530-0x5adb1f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.
//
// Leaf bodies that repeat at several addresses: the integer sort comparator
// (the same shape as IndexClass::Comparator, bound to other tables), release
// and replace of one global heap block, a 64 KiB global buffer clear, and
// three constant or global tests. Each address was verified separately.
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
// Retail RTTI names VectorClass/DynamicVectorClass over Cell, BaseNodeClass, TPoint3D<int>, Point2D,
// TRect<int> and DirtyAreaStruct. Element layouts and compare shapes are read from the FindItemIndex,
// Slot5, Slot6 and SetCapacity bodies; field names are placeholders.
//
// Retail RTTI type descriptors name VectorClass<double> and
// DynamicVectorClass<double>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
//
// 10 remaining four-byte-element resize bodies retain address-scoped
// views until their actual template classes are integrated. Recovered entries
// are bound in their native specialization implementations.
// Entry-origin spans are 0xB0 bytes. Instructions confirm Items+4, Capacity+8,
// initialization flag+C, ownership flag+D, live count+10 and Clear slot+C.
// Original source ownership and TU grouping are not established by this sweep.
//
// The source keeps the base resize as an inline call and clamps the count only
// on success. The capacity-zero branch dispatches Clear; allocation failure
// returns false. The ownership expression retains the verified short-circuit
// term so VC6 schedules SETZ and the pointer/capacity stores as retail does.
// These views remain verified under /O2 /DNDEBUG /Gy /GX.
//
// Retail RTTI names VectorClass/DynamicVectorClass over unsigned short, bool, double and unsigned char.
// Scalar elements need no element type; the canonical templates are instantiated as-is.
//
// Three constructors that only zero their leading dwords and return `this`:
//   0x5A9BF0 stores 0 at +0x00/+0x04 as immediates (`MOV [EAX],0`);
//   0x7636F0 and 0x769480 store a zeroed ECX at +0x00/+0x04/+0x08.
// 0x769480 is pushed as a constructor callback at 0x769696 and 0x769782.
// The classes are not identified; names are placeholders and no size is
// asserted.
//
//   Read off retail gamemd.exe v1.001 at 0x5A7250: __fastcall with a
//   rectangle pointer in ECX ({X, Y, Width, Height} dwords at +0/+4/+8/+0xC),
//   a bool in DL and a second bool on the stack (`RET 4`). The four corners
//   are cut to 16-bit cell coordinates (MOVSX) and tested against the dwords
//   at 0xABED04 and 0xABED08; each cell comes from the map object 0x87F7E8
//   through 0x5657A0 and is classified by the cell predicates 0x4866D0,
//   0x4866F0, 0x486380, 0x486650 and 0x486670.
//
//   Bytes matched against the user's retail gamemd.exe v1.001 over the
//   0x5A9920-0x5A9C18 run. See the header for the numeric offset derivation.
//
// The theater tile-link table's element, step and slot constructors. Bodies are

#include "../core/vector_ctor_pod_family_methods.h"
#include "../core/deleting_dtor_sweep.h"
#include "../network/transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

#include "../core/global_getter_family_methods.h"

#include <string.h>


// Retail PAVMapRegionClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// Retail PAU_WIN32_FIND_DATAA RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "../core/vector_class_operations.h"

// The int vector's capacity constructor is out of line at 0x477BE0 (defined in another translation unit).
extern template class VectorClass<int>;

class MapRegionClass;

// VTABLE: GAMEMD 0x7ED878 -- VectorClass<MapRegionClass*>.
template class VectorClass<MapRegionClass*>;
typedef VectorClass<MapRegionClass*> GgMapregionclassVectorClass;
GG_STATIC_ASSERT(offsetof(GgMapregionclassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMapregionclassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMapregionclassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMapregionclassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7ED858 -- DynamicVectorClass<MapRegionClass*>.
template class DynamicVectorClass<MapRegionClass*>;
typedef DynamicVectorClass<MapRegionClass*> GgMapregionclassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgMapregionclassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMapregionclassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMapregionclassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMapregionclassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMapregionclassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMapregionclassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(MapRegionClass*) == 4);

#include "../core/vector_class_operations.h"

#include "../core/vector_find_data.h"

// VTABLE: GAMEMD 0x7ED92C -- VectorClass<_WIN32_FIND_DATAA*>.
template class VectorClass<_WIN32_FIND_DATAA*>;
typedef VectorClass<_WIN32_FIND_DATAA*> GgWin32FindDataaVectorClass;
GG_STATIC_ASSERT(offsetof(GgWin32FindDataaVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgWin32FindDataaVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgWin32FindDataaVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgWin32FindDataaVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7ED94C -- DynamicVectorClass<_WIN32_FIND_DATAA*>.
template class DynamicVectorClass<_WIN32_FIND_DATAA*>;
typedef DynamicVectorClass<_WIN32_FIND_DATAA*> GgWin32FindDataaDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgWin32FindDataaDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgWin32FindDataaDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgWin32FindDataaDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgWin32FindDataaDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgWin32FindDataaDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgWin32FindDataaDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(_WIN32_FIND_DATAA*) == 4);

// SYNTHETIC: GAMEMD 0x5AC270 -- MapSeedClass scalar deleting destructor, emitted by the compiler from the
// virtual destructor where this TU seats the vtable.

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5AC3A0
// DynamicVectorClass<MapRegionClass*>::Clear

// FUNCTION: GAMEMD 0x5AC3D0
// DynamicVectorClass<MapRegionClass*>::Slot5

// FUNCTION: GAMEMD 0x5AC3F0
// VectorClass<MapRegionClass*>::Slot6

// FUNCTION: GAMEMD 0x5AC6A0
// VectorClass<MapRegionClass*>::operator==

// FUNCTION: GAMEMD 0x5AC6E0
// VectorClass<MapRegionClass*>::SetCapacity

// FUNCTION: GAMEMD 0x5AC790
// VectorClass<MapRegionClass*>::Clear

// FUNCTION: GAMEMD 0x5AC7C0
// VectorClass<MapRegionClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x5AC800
// VectorClass<MapRegionClass*>::Slot5

// FUNCTION: GAMEMD 0x5AC820
// DynamicVectorClass<MapRegionClass*>::SetCapacity

// FUNCTION: GAMEMD 0x5AC8D0
// DynamicVectorClass<MapRegionClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x5AD390
// VectorClass<MapRegionClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x5AD3E0
// DynamicVectorClass<MapRegionClass*>::scalar deleting destructor

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5AC4C0
// DynamicVectorClass<_WIN32_FIND_DATAA*>::Clear

// FUNCTION: GAMEMD 0x5AC4F0
// DynamicVectorClass<_WIN32_FIND_DATAA*>::Slot5

// FUNCTION: GAMEMD 0x5AC510
// VectorClass<_WIN32_FIND_DATAA*>::Slot6

// FUNCTION: GAMEMD 0x5ACA60
// VectorClass<_WIN32_FIND_DATAA*>::operator==

// FUNCTION: GAMEMD 0x5ACAA0
// VectorClass<_WIN32_FIND_DATAA*>::SetCapacity

// FUNCTION: GAMEMD 0x5ACB50
// VectorClass<_WIN32_FIND_DATAA*>::Clear

// FUNCTION: GAMEMD 0x5ACB80
// VectorClass<_WIN32_FIND_DATAA*>::FindItemIndex

// FUNCTION: GAMEMD 0x5ACBC0
// VectorClass<_WIN32_FIND_DATAA*>::Slot5

// FUNCTION: GAMEMD 0x5ACBE0
// DynamicVectorClass<_WIN32_FIND_DATAA*>::SetCapacity

// FUNCTION: GAMEMD 0x5ACC90
// DynamicVectorClass<_WIN32_FIND_DATAA*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x5AD430
// VectorClass<_WIN32_FIND_DATAA*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x5AD480
// DynamicVectorClass<_WIN32_FIND_DATAA*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x005AD9F0
template<> VectorClass<WIN32_FIND_DATAA*>::VectorClass(int capacity,
    WIN32_FIND_DATAA** pMem)
    : Items(0), Capacity(capacity), IsInitialized(true), IsAllocated(false)
{
    if (capacity != 0) {
        if (pMem != 0)
            Items = new((void*)pMem) WIN32_FIND_DATAA*[capacity];
        else {
            Items = new WIN32_FIND_DATAA*[capacity];
            IsAllocated = true;
        }
    }
}

// LIBRARY: GAMEMD 0x7C8B3D -- CRT free.
extern "C" void __cdecl gg_free(void*);

extern int DAT_00A9FABC;
extern void* DAT_00ABF3F4;
extern int DAT_00B2FF78[0x4000];
extern int DAT_00B1D5E0[0x4000];
extern void* DAT_00B77F54;
extern void* DAT_00B77F60;

#include "../core/pair_vector_grow_sweep.h"

#include "../core/trivial_tu130_methods.h"

#include "../core/vector_class_operations.h"
#include "MapGen.h"
#include <windows.h>
#include "../core/trivial_tu055_methods.h"
#include "../ui/ui_focus_methods.h"
#include "../ui/ui_updated_methods.h"
#include "../platform/ccfile_class.h"
#include "../core/vtable_seating_ctor_family_methods.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.


template class DynamicVectorClass<Cell>;

#include "../_layout/base_node_class.h"

template class DynamicVectorClass<BaseNodeClass>;

template<class T> class TPoint3D { public: T X; T Y; T Z; TPoint3D() {} bool operator==(const TPoint3D<T>& o) const { return X==o.X && Y==o.Y && Z==o.Z; } bool operator!=(const TPoint3D<T>& o) const { return !(*this==o); } };

#include "../_layout/geometry2d.h"
#include "../_layout/building_class.h"
#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"
#include "../_layout/cell_class.h"

template class DynamicVectorClass<Point2D>;


template class DynamicVectorClass<TRect<int> >;


#include "../_layout/dirty_area.h"
template class DynamicVectorClass<DirtyAreaStruct>;

#include "../core/vector_class_operations.h"

template class DynamicVectorClass<double>;

GG_STATIC_ASSERT(sizeof(double) == 8);
GG_STATIC_ASSERT(sizeof(VectorClass<double >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<double >) == 0x18);

#include "../core/vector_resize_family_methods.h"

#include "../core/vector_class_operations.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

template class DynamicVectorClass<unsigned short>;


template class DynamicVectorClass<bool>;

template class DynamicVectorClass<double>;

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/pairholder_005a9bf0.h"

#include "../_layout/triple_007636f0.h"

#include "../_layout/triple_00769480.h"

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Rect_005A7250
{
    int X;        // +0x00
    int Y;        // +0x04
    int Width;    // +0x08
    int Height;   // +0x0C
};
GG_STATIC_ASSERT(offsetof(Rect_005A7250, Height) == 0x0C);

struct CellStruct_005A7250
{
    short X;   // +0x00
    short Y;   // +0x02
};

struct Cell_005A7250
{
    // FUNCTION: GAMEMD 0x4866D0 (decl; reloc)
    bool FUN_004866D0();
    // FUNCTION: GAMEMD 0x4866F0 (decl; reloc)
    bool FUN_004866F0();
    // FUNCTION: GAMEMD 0x486380 (decl; reloc)
    bool FUN_00486380();
    // FUNCTION: GAMEMD 0x486650 (decl; reloc)
    bool FUN_00486650();
    // FUNCTION: GAMEMD 0x486670 (decl; reloc)
    bool FUN_00486670();
};

// GLOBAL: GAMEMD 0xABED04
extern int DAT_00ABED04;
// GLOBAL: GAMEMD 0xABED08
extern int DAT_00ABED08;

// The diamond test the four corners go through.
static inline bool CellInsideMap(const CellStruct_005A7250& cell)
{
    int x = cell.X;
    int y = cell.Y;
    if (x + y <= DAT_00ABED04 || x - y >= DAT_00ABED04 || y - x >= DAT_00ABED04 ||
        x + y > DAT_00ABED08) {
        return false;
    }
    return true;
}

static inline CellStruct_005A7250 InlineCell_005A7250(int x, int y)
{
    CellStruct_005A7250 cell;
    cell.X = (short)x;
    cell.Y = (short)y;
    return cell;
}

#include "tile_link_table_methods.h"

// GLOBAL: GAMEMD 0xABE370 — the 101-slot tile-link table (0xC per slot).
// GLOBAL: GAMEMD 0xABE834 — the 8-slot continuation of the same table.

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7ED620
extern const double DAT_007ED620;
// GLOBAL: GAMEMD 0xABE368
extern double DAT_00ABE368;
// GLOBAL: GAMEMD 0xABECE8
extern int DAT_00ABECE8;
// GLOBAL: GAMEMD 0xABECEC
extern int DAT_00ABECEC;
// GLOBAL: GAMEMD 0xABECF0
extern int DAT_00ABECF0;


// ---- from the former MapGen.cpp ----
//   File name attested by the assert string "D:\ra2mdpost\MapGen.cpp" at
//   0x0082BA48 in retail gamemd.exe v1.001 (the localised-string lookups at
//   0x595710 and 0x597380 pass it with line 0xF5E). Bytes matched against
//   retail at each address below. Ordered ascending by retail address.
//
//   MapRegionClass is attested by RTTI .?AV?$VectorClass@PAVMapRegionClass@@@@
//   and .?AV?$DynamicVectorClass@PAVMapRegionClass@@@@ (type descriptors
//   0x0082B9A0 and 0x0082B9D0); its member layout, the CellClass view and the
//   other record types here are read from the bodies, with placeholder names.
//
//   /Ob2: retail expands the MapRegionClass destructor (out-of-line copy at
//   0x58C070) inline in the delete loops at 0x58C100 and 0x58CE90, which the
//   default /Ob1 does not do for an out-of-class destructor.

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*), ??3@YAXPAX@Z.
// LIBRARY: GAMEMD 0x7C5F00 -- __ftol (the double to integer conversion).

// dynamic initializer for DAT_00ABECF8
// GLOBAL: GAMEMD 0x00ABECF8
extern double DAT_00ABECF8;

// dynamic initializer for DAT_00ABECE0
// GLOBAL: GAMEMD 0x00ABECE0
extern double DAT_00ABECE0;

GG_STATIC_ASSERT(sizeof(DAT_00ABECF8) == 8);
GG_STATIC_ASSERT(sizeof(DAT_00ABECE0) == 8);

// SYNTHETIC: GAMEMD 0x58B740 -- constructor call + atexit registration
// SYNTHETIC: GAMEMD 0x58B760 -- exit-time stub: tail-jumps to the destructor
// GLOBAL: GAMEMD 0xABDFD8
// The random-map generator object.
Gbl_00ABDFD8 DAT_00ABDFD8;

// SYNTHETIC: GAMEMD 0x58B770 -- initialiser: constructs the generator's Randomizer with seed 0 (0x65C6D0).
// GLOBAL: GAMEMD 0xABE890
Gbl_00ABE890 DAT_00ABE890(0);

// FUNCTION: GAMEMD 0x58B7B0
// Empty function.
void __cdecl FUN_0058B7B0()
{
}

// FUNCTION: GAMEMD 0x58B7C0
// Empty function.
void __cdecl FUN_0058B7C0()
{
}

// FUNCTION: GAMEMD 0x0058B7D0
int FUN_0058B7D0()
{
    return DAT_00ABED0C;
}

// FUNCTION: GAMEMD 0x58B7E0
// Returns a global (dword).
int __cdecl FUN_0058B7E0()
{
    return DAT_00ABDFD4;
}

// FUNCTION: GAMEMD 0x58B7F0
// Returns a global (dword).
int __cdecl FUN_0058B7F0()
{
    return DAT_00ABDFD0;
}

// FUNCTION: GAMEMD 0x58B800
// Returns a global (dword).
int __cdecl FUN_0058B800()
{
    return DAT_00ABEC90;
}

// FUNCTION: GAMEMD 0x58B810
// Returns a global (dword).
int __cdecl FUN_0058B810()
{
    return DAT_00ABECD0;
}

// FUNCTION: GAMEMD 0x58BB00
Pair_8* FUN_0058BB00(Pair_8* a1, int a2)
{
    if (a2 >= 0 && a2 < DAT_00ABED0C) {
        *a1 = DAT_00ABE328[a2];
    } else {
        Pair_8 z = { 0, 0 };
        *a1 = z;
    }
    return a1;
}

// FUNCTION: GAMEMD 0x58BB30
void FUN_0058BB30()
{
    if (DAT_00A8B230) {
        DAT_00A8B230->unknown_113C = DAT_00ABED0C;
        for (int i = 0; i < DAT_00A8B230->unknown_113C; i++) {
            Pair_8 p;
            FUN_0058BB00(&p, i);
            DAT_00A8B230->unknown_1140[i] = p;
            DAT_00A8B230->unknown_11C0[i] = DAT_00ABE304[i];
        }
        DAT_00A8B230->unknown_112C = DAT_00ABDFD4;
        DAT_00A8B230->unknown_1130 = DAT_00ABDFD0;
        DAT_00A8B230->unknown_1134 = DAT_00ABEC90;
        DAT_00A8B230->unknown_1138 = DAT_00ABECD0;
    }
}

// FUNCTION: GAMEMD 0x58BCD0
// Branching.
int FUN_0058BCD0(int a1)
{
    return a1 == 1 || a1 == 3 || a1 == 4;
}

// FUNCTION: GAMEMD 0x58BCF0
bool FUN_0058BCF0(int a1)
{
    return !Inline_0058BCF0(a1);
}

// FUNCTION: GAMEMD 0x58BD20
// Branching.
int FUN_0058BD20(int a1)
{
    return a1 == 3 || a1 == 4;
}

// FUNCTION: GAMEMD 0x58BD40
// Branching.
int FUN_0058BD40(int a1)
{
    return a1 == 4 || a1 == 3;
}

// FUNCTION: GAMEMD 0x58BD60
// Branching.
int FUN_0058BD60(int a1)
{
    return a1 == 3 || a1 == 4;
}

// FUNCTION: GAMEMD 0x58BD80
bool FUN_0058BD80(int a1, int a2)
{
    switch (a1) {
    case 0:
        return a2 == 3;
    case 1:
    case 3:
    case 4:
        return a2 != 3;
    case 2:
        return true;
    default:
        return false;
    }
}

// FUNCTION: GAMEMD 0x58BF70
MapRegionClass::MapRegionClass(CellStruct a1)
    : unknown_00(0), unknown_04(0), unknown_08(DAT_00ABED14), unknown_0C(0),
      unknown_10(DAT_0087F7E8.FUN_005657A0(&a1)->Level),
      unknown_14(DAT_0087F7E8.FUN_005657A0(&a1)->FUN_004865D0()),
      unknown_16(a1), unknown_1A(0), unknown_1B(1), unknown_1C(0), unknown_20(0), unknown_24(0),
      unknown_28(0, 0), unknown_40(0), unknown_44(0), unknown_48(0), unknown_4C(0)
{
    unknown_28.CapacityIncrement = 100000;
    DAT_00ABED14++;
    DAT_00ABDF90.AddItem(this);
}

// FUNCTION: GAMEMD 0x58C070
MapRegionClass::~MapRegionClass()
{
    if (unknown_00) {
        delete unknown_00;
        unknown_00 = 0;
    }
    DAT_00ABDF90.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x58C100
void FUN_0058C100()
{
    DAT_00ABED14 = 0;
    for (int i = DAT_00ABDF90.Count - 1; i >= 0; i--) {
        MapRegionClass* p = DAT_00ABDF90.Items[i];
        if (p)
            delete p;
    }
}

// FUNCTION: GAMEMD 0x58C2D0
void MapRegionClass::FUN_0058C2D0()
{
    unknown_0C = 0;
    int n = DAT_0089C2DC * DAT_0089C2DC;
    for (int i = 0; i < n; i++) {
        Rec_50* c = &DAT_00ABED10[i];
        if (c->unknown_38 == unknown_08 && (c->unknown_00.X || c->unknown_00.Y))
            unknown_0C++;
    }
}

// FUNCTION: GAMEMD 0x58C320
void MapRegionClass::FUN_0058C320(CellStruct* a1)
{
    unsigned int n = DAT_0089C2DC * DAT_0089C2DC;
    unsigned int idx;
    do {
        idx = Inline_0058C320(n - 1);
    } while (DAT_00ABED10[idx].unknown_38 != unknown_08 ||
             (DAT_00ABED10[idx].unknown_00.X == 0 && DAT_00ABED10[idx].unknown_00.Y == 0));
    *a1 = DAT_00ABED10[idx].unknown_00;
}

// FUNCTION: GAMEMD 0x58C3B0
void MapRegionClass::FUN_0058C3B0(CellStruct* a1)
{
    int tries = 0;
    for (;;) {
        unsigned int n = DAT_0089C2DC * DAT_0089C2DC;
        unsigned int idx;
        do {
            idx = Inline_0058C320(n - 1);
        } while (DAT_00ABED10[idx].unknown_38 != unknown_08 ||
                 (DAT_00ABED10[idx].unknown_00.X == 0 && DAT_00ABED10[idx].unknown_00.Y == 0));
        CellStruct c = DAT_00ABED10[idx].unknown_00;
        tries++;
        if (tries > 200)
            break;
        if (DAT_0087F7E8.FUN_005657A0(&c)->FUN_00486380()) {
            *a1 = c;
            return;
        }
    }
    CellStruct z;
    z.X = 0;
    z.Y = 0;
    *a1 = z;
}

// Unclaimed (below partial bar), GAMEMD 0x58C4A0
void MapRegionClass::FUN_0058C4A0(CellStruct* a1)
{
    int tries = 0;
    Rec_50* r = DAT_00ABED10;
    unsigned int n = DAT_0089C2DC * DAT_0089C2DC;
    for (;;) {
        unsigned int idx = Inline_0058C320(n - 1);
        *r = DAT_00ABED10[idx];
        tries++;
        if (tries >= 100)
            break;
        if (r->unknown_38 == unknown_08 && (r->unknown_00.X != 0 || r->unknown_00.Y != 0) && r->unknown_44) {
            if (DAT_0087F7E8.FUN_005657A0(&r->unknown_00)->FUN_00486380()) {
                *a1 = r->unknown_00;
                return;
            }
        }
    }
    CellStruct z;
    z.X = 0;
    z.Y = 0;
    *a1 = z;
}

// FUNCTION: GAMEMD 0x58C5A0
// Draw random records of the 0xABED10 table into its first slot until one
// names a non-origin cell in `zone` that passes 0x486380 and, unless `kind`
// is -1, carries that kind at +0x38. Gives up with the origin after 100 draws.
Cell FUN_0058C5A0(int zone, int kind)
{
    Rec_50* rec = DAT_00ABED10;
    int count = DAT_0089C2DC * DAT_0089C2DC;
    int tries = 0;
    for (;;) {
        *rec = DAT_00ABED10[Inline_0058C320(count - 1)];
        tries++;
        if (tries >= 100) {
            return Cell(0, 0);
        }
        CellClass* cell = DAT_0087F7E8.FUN_005657A0(&rec->unknown_00);
        if (rec->unknown_00.X == 0 && rec->unknown_00.Y == 0) {
            continue;
        }
        if (DAT_0087F7E8.FUN_0056D230(cell->MapCoords, 0, false) != zone) {
            continue;
        }
        if (!cell->FUN_00486380()) {
            continue;
        }
        if (kind == -1 || rec->unknown_38 == kind) {
            return rec->unknown_00;
        }
    }
}

// FUNCTION: GAMEMD 0x58CE90
void FUN_0058CE90()
{
    if (DAT_00ABED10 != 0) {
        int n = DAT_0089C2DC * DAT_0089C2DC;
        for (int i = 0; i < n; i++) {
            DAT_00ABED10[i].unknown_38 = -1;
            DAT_00ABED10[i].unknown_3C = -1;
        }
    }
    for (int j = DAT_00ABDF90.Count - 1; j >= 0; j--) {
        MapRegionClass* p = DAT_00ABDF90.Items[j];
        if (p)
            delete p;
    }
    DAT_00ABED14 = 0;
}

// FUNCTION: GAMEMD 0x58D010
void FUN_0058D010(char a1)
{
    int n = DAT_0089C2DC * DAT_0089C2DC;
    for (int i = 0; i < n; i++) {
        Rec_50* c = &DAT_00ABED10[i];
        if (c->unknown_38 == -1 && (c->unknown_00.X || c->unknown_00.Y)) {
            Rec_0058C800Ret* r = DAT_0087F7E8.FUN_005657A0(&c->unknown_00)->FUN_0058C800();
            if (r)
                r->unknown_1A = a1;
        }
    }
}

// FUNCTION: GAMEMD 0x58D410
// Collect this region's border cells: every cell of the region with a neighbour inside the diamond
// that belongs to another region is appended once to a new list.
DynamicVectorClass<Cell>* MapRegionClass::FUN_0058D410()
{
    DynamicVectorClass<Cell>* list = new DynamicVectorClass<Cell>;
    DAT_0087F7E8.FUN_00578350();
    CellClass* it;
    while ((it = DAT_0087F7E8.FUN_00578290()) != 0) {
        CellStruct own = it->MapCoords;
        if (Inline_CellOwner(own) == unknown_08) {
            bool border = false;
            for (int f = 0; f < 8; f++) {
                CellClass* adj = it->FUN_00481810(f);
                CellStruct n = adj->MapCoords;
                int x = n.X;
                int y = n.Y;
                if (y + x > DAT_00ABED04 && x - y < DAT_00ABED04 && y - x < DAT_00ABED04 && y + x <= DAT_00ABED08) {
                    if (Inline_CellOwner(n) != unknown_08)
                        border = true;
                }
            }
            if (border)
                list->AddItem(it->MapCoords);
        }
    }
    return list;
}

// FUNCTION: GAMEMD 0x58D5A0
void MapRegionClass::FUN_0058D5A0(char a1)
{
    DAT_0087F7E8.FUN_00578350();
    CellClass* it;
    while ((it = DAT_0087F7E8.FUN_00578290()) != 0) {
        CellStruct c = it->MapCoords;
        int id;
        if (DAT_00ABED10 == 0)
            id = -1;
        else
            id = DAT_00ABED10[c.Y * DAT_0089C2DC + c.X].unknown_38;
        if (id == unknown_08)
            it->Level += a1;
    }
}

// FUNCTION: GAMEMD 0x58E5D0
// Collect this region's border cells: walking the cell list from the back,
// every cell with an in-diamond neighbour owned by another region (or by
// none) is appended once to a new list that grows by half the +0x0C count.
DynamicVectorClass<Cell>* MapRegionClass::FUN_0058E5D0()
{
    DynamicVectorClass<Cell>* list = new DynamicVectorClass<Cell>;
    int step = unknown_0C / 2;
    if (step < 10)
        step = 10;
    list->CapacityIncrement = step;
    for (int i = unknown_28.Count - 1; i >= 0; i--) {
        Cell cell = unknown_28.Items[i];
        for (int f = 0; f < 8; f++) {
            CellStruct adj;
            adj.X = (short)(DAT_0089F688[f & 7].X + cell.X);
            adj.Y = (short)(DAT_0089F688[f & 7].Y + cell.Y);
            int x = adj.X;
            int y = adj.Y;
            if (x + y > DAT_00ABED04 && x - y < DAT_00ABED04 && y - x < DAT_00ABED04 && x + y <= DAT_00ABED08) {
                int owner;
                if (DAT_00ABED10 == 0)
                    owner = -1;
                else
                    owner = DAT_00ABED10[y * DAT_0089C2DC + x].unknown_38;
                if (owner != unknown_08) {
                    list->AddItem(cell);
                    break;
                }
            }
        }
    }
    return list;
}

// FUNCTION: GAMEMD 0x58E9B0
// Flood this region outward from its border cells: every free in-diamond neighbour that is
// allowed (flag at +0x4B) takes this region's id and is queued in turn.
bool MapRegionClass::FUN_0058E9B0()
{
    DynamicVectorClass<Cell>* border = FUN_0058D410();
    DynamicVectorClass<Cell> queue;
    queue.CapacityIncrement = 50000;
    for (int i = 0; i < border->Count; i++)
        queue.AddItem(border->Items[i]);
    delete border;
    while (queue.GetCount() > 0) {
        int last = queue.GetCount() - 1;
        Cell c = queue.Items[last];
        queue.Delete(last);
        for (int f = 0; f < 8; f++) {
            CellStruct adj = Inline_005A33F0(c, DAT_0089F688[f & 7]);
            if (Inline_005942F0(adj)) {
                Rec_50* rec = &DAT_00ABED10[adj.Y * DAT_0089C2DC + adj.X];
                if (rec->unknown_38 == -1 && rec->unknown_4B) {
                    rec->unknown_38 = unknown_08;
                    queue.AddItem(adj);
                }
            }
        }
    }
    return true;
}

// Unclaimed (below partial bar), GAMEMD 0x58EEA0
void MapRegionClass::FUN_0058EEA0()
{
    int n = DAT_0089C2DC * DAT_0089C2DC;
    for (int i = 0; i < n; i++) {
        DAT_00ABED10[i].unknown_44 = 0;
    }
    FUN_0058D1C0(8, -2);
    for (int j = 0; j < n; j++) {
        if (DAT_00ABED10[j].unknown_38 == unknown_08) {
            DAT_00ABED10[j].unknown_44 = 1;
        } else if (DAT_00ABED10[j].unknown_38 == -2) {
            DAT_00ABED10[j].unknown_38 = unknown_08;
        }
    }
}

// FUNCTION: GAMEMD 0x58F0C0
// Build this region's neighbour list: every other region touched by a border cell's eight
// neighbours is listed once, then the cell count is recomputed.
void MapRegionClass::FUN_0058F0C0()
{
    unknown_04 = new DynamicVectorClass<int>;
    bool* touched = new bool[DAT_00ABED14];
    for (int i = 0; i < DAT_00ABED14; i++)
        touched[i] = false;
    DynamicVectorClass<Cell>* border = FUN_0058D410();
    for (int j = 0; j < border->Count; j++) {
        Cell cell = border->Items[j];
        for (int f = 0; f < 8; f++) {
            CellStruct adj = Inline_005A33F0(cell, DAT_0089F688[f & 7]);
            if (Inline_005942F0(adj) && DAT_00ABED10 != 0) {
                int owner = DAT_00ABED10[adj.Y * DAT_0089C2DC + adj.X].unknown_38;
                if (owner >= 0)
                    touched[owner] = true;
            }
        }
    }
    for (int k = 0; k < DAT_00ABED14; k++) {
        if (touched[k] && k != unknown_08)
            unknown_04->AddItem(k);
    }
    unknown_0C = 0;
    int n = DAT_0089C2DC * DAT_0089C2DC;
    for (int m = 0; m < n; m++) {
        Rec_50* c = &DAT_00ABED10[m];
        if (c->unknown_38 == unknown_08 && (c->unknown_00.X || c->unknown_00.Y))
            unknown_0C++;
    }
    delete border;
    delete[] touched;
}

// FUNCTION: GAMEMD 0x5904B0
// Find the first cell of `area` (inclusive bounds) with no overlay, passing
// 0x486380 and holding no object, and unlimbo a neutral "CABHUT" building at
// its centre. True when one was placed.
bool __stdcall FUN_005904B0(Rect_4i* area)
{
    for (int y = area->unknown_04; y < area->unknown_04 + area->unknown_0C + 1; y++) {
        for (int x = area->unknown_00; x < area->unknown_00 + area->unknown_08 + 1; x++) {
            CellStruct c;
            c.X = x;
            c.Y = y;
            CellClass* cell = DAT_0087F7E8.FUN_005657A0(&c);
            if (cell->OverlayTypeIndex == -1 && cell->FUN_00486380() && cell->FirstObject == 0) {
                HouseClass* owner = HouseClass::FindByCountryIndex(HouseTypeClass::FindIndexOfName("Neutral"));
                int type = FUN_0045E7B0("CABHUT");
                BuildingClass* hut = new BuildingClass(DAT_00A83C6C[type], owner);
                CoordStruct coord;
                coord.X = cell->MapCoords.X * 256 + 128;
                coord.Y = cell->MapCoords.Y * 256 + 128;
                coord.Z = 0;
                hut->vf_54(coord, 0);
                return true;
            }
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x590FD0
// Test the 5x5 block centred on `cell` with 0x5A1E50 at a threshold scaled
// from `a4`; on failure clear `*ok` and return 0. Otherwise test each of the
// eight surrounding 5x5 blocks and return the 0x82AF18 bits of those that pass.
int Obj_00590970::FUN_00590FD0(CellStruct* cell, bool* ok, int a3, float a4)
{
    int threshold = (int)((1.0f - a4) * (DAT_007ED6E0 - DAT_007ED6D8) + DAT_007ED6D8);
    CellStruct corner;
    corner.X = cell->X - 2;
    corner.Y = cell->Y - 2;
    int x = corner.X;
    int y = corner.Y;
    Rect_4i area;
    area.unknown_00 = x;
    area.unknown_04 = y;
    area.unknown_08 = 5;
    area.unknown_0C = 5;
    if (!FUN_005A1E50(&area, unknown_08, a3, threshold)) {
        *ok = false;
        return 0;
    }
    int mask = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 1 && j == 1) {
                continue;
            }
            area.unknown_00 = x + (j - 1) * 5;
            area.unknown_04 = y + (i - 1) * 5;
            area.unknown_08 = 5;
            area.unknown_0C = 5;
            if (FUN_005A1E50(&area, unknown_08, a3, threshold)) {
                mask |= DAT_0082AF18[i * 3 + j];
            }
        }
    }
    return mask;
}

// FUNCTION: GAMEMD 0x594010
bool MapRegionClass::FUN_00594010(Rect_4i* a1, int a2)
{
    CellStruct c;
    c.X = a1->unknown_00;
    c.Y = a1->unknown_04;
    if (DAT_0087F7E8.FUN_00578460(&c, 1)) {
        c.X = a1->unknown_08 + a1->unknown_00 - 1;
        c.Y = a1->unknown_04;
        if (DAT_0087F7E8.FUN_00578460(&c, 1)) {
            c.X = a1->unknown_00;
            c.Y = a1->unknown_04 + a1->unknown_0C - 1;
            if (DAT_0087F7E8.FUN_00578460(&c, 1)) {
                c.X = a1->unknown_08 + a1->unknown_00 - 1;
                c.Y = a1->unknown_04 + a1->unknown_0C - 1;
                if (DAT_0087F7E8.FUN_00578460(&c, 1)) {
                    for (int y = a1->unknown_04; y < a1->unknown_04 + a1->unknown_0C; y++) {
                        for (int x = a1->unknown_00; x < a1->unknown_08 + a1->unknown_00; x++) {
                            c.X = (short)x;
                            c.Y = (short)y;
                            int owner;
                            if (DAT_00ABED10 == 0)
                                owner = -1;
                            else
                                owner = DAT_00ABED10[c.Y * DAT_0089C2DC + c.X].unknown_38;
                            if (owner != unknown_08 && owner != a2)
                                return false;
                            if (!DAT_0087F7E8.FUN_005657A0(&c)->FUN_00486380())
                                return false;
                        }
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x594190
// Give every in-diamond cell of `area` to region `id`: record the owner in the
// 0x50-byte cell records and copy the region's +0x10 byte into the cell.
void __stdcall FUN_00594190(Rect_4i* area, int id)
{
    for (int y = area->unknown_04; y < area->unknown_0C + area->unknown_04; y++) {
        for (int x = area->unknown_00; x < area->unknown_08 + area->unknown_00; x++) {
            CellStruct c;
            c.X = (short)x;
            c.Y = (short)y;
            if (Inline_005942F0(c)) {
                if (DAT_00ABED10 != 0)
                    DAT_00ABED10[c.Y * DAT_0089C2DC + c.X].unknown_38 = id;
                CellClass* cell = DAT_0087F7E8.FUN_005657A0(&c);
                MapRegionClass* region = Inline_005943E0(id);
                cell->Level = (char)region->unknown_10;
            }
        }
    }
}

// FUNCTION: GAMEMD 0x5942F0
void MapRegionClass::FUN_005942F0(Rect_4i* a1)
{
    for (int y = a1->unknown_04; y < a1->unknown_0C + a1->unknown_04; y++) {
        for (int x = a1->unknown_00; x < a1->unknown_08 + a1->unknown_00; x++) {
            CellStruct c;
            c.X = (short)x;
            c.Y = (short)y;
            if (Inline_005942F0(c)) {
                if (DAT_00ABED10 != 0)
                    DAT_00ABED10[c.Y * DAT_0089C2DC + c.X].unknown_38 = unknown_08;
                DAT_0087F7E8.FUN_005657A0(&c)->Level = (char)unknown_10;
            }
        }
    }
}

// FUNCTION: GAMEMD 0x5943E0
MapRegionClass* FUN_005943E0(int a1)
{
    return Inline_005943E0(a1);
}

// FUNCTION: GAMEMD 0x594700
// Rebuild the regions: clear both owner words of every cell record, delete
// every region, then grow a new region from each free in-diamond cell whose
// +0x4C word is clear and whose zone for movement zone `a1` is `a2`.
void FUN_00594700(int a1, int a2)
{
    if (DAT_00ABED10 != 0) {
        int n = DAT_0089C2DC * DAT_0089C2DC;
        for (int i = 0; i < n; i++) {
            DAT_00ABED10[i].unknown_38 = -1;
            DAT_00ABED10[i].unknown_3C = -1;
        }
    }
    for (int i = DAT_00ABDF90.Count - 1; i >= 0; i--) {
        MapRegionClass* p = DAT_00ABDF90.Items[i];
        if (p)
            delete p;
    }
    DAT_00ABED14 = 0;
    DAT_0087F7E8.FUN_00578350();
    CellClass* it;
    while ((it = DAT_0087F7E8.FUN_00578290()) != 0) {
        if (Inline_005942F0(it->MapCoords) &&
            DAT_00ABED10[it->MapCoords.Y * DAT_0089C2DC + it->MapCoords.X].unknown_38 == -1 &&
            it->Passability == 0 && DAT_0087F7E8.FUN_0056D230(it->MapCoords, a1, false) == a2)
            FUN_00594420(it, a1, a2);
    }
}

// STRING: GAMEMD 0x82BA60 -- "SED"
// FUNCTION: GAMEMD 0x595680
// Set up the random-map save/load driver: default flags, the "SED" file extension and an empty
// description buffer, filled from the localised text when one is loaded.
MapSeedClass::MapSeedClass()
    : unknown_38(0), unknown_3C(1), unknown_40(1), unknown_44(0), unknown_48(1), unknown_4C(0),
      unknown_50(2), unknown_54(0), unknown_58(0), unknown_5C(0), unknown_60(0), unknown_64(0),
      unknown_68(0), unknown_6C(0), unknown_70(0), unknown_74(-1)
{
    Extension = "SED";
    unknown_78 = 0;
    Description = (const wchar_t*)&unknown_78;
    if (FUN_00734FD0())
        FUN_007CA489(&unknown_78, FUN_00734E60(DAT_0082BA2C, 0, DAT_0082BA48, 0xF5E));
}

// FUNCTION: GAMEMD 0x595710
void MapSeedClass::FUN_00595710()
{
    FUN_007CA489(&unknown_78, FUN_00734E60(DAT_0082BA2C, 0, DAT_0082BA48, 0xF5E));
}

// FUNCTION: GAMEMD 0x595BC0
// Run the random-map progress dialog (resource 0x105) until its procedure
// stores a result or the UI loop reports an update, calling `callback` each
// pass. The callback is published at 0x82AF14 and 0xABDFEC for the duration.
// Afterwards the preview at 0xABE154 is written to "RandMap.img" (when it
// holds a surface) and released, and the object at 0xABE150 is deleted.
int FUN_00595BC0(Callback_00595BC0 callback)
{
    int result = 0;
    DAT_00ABDFD8.FUN_005981F0();
    HWND window = (HWND)UI_BeginDialog(0x105, FUN_00596300, 0);
    if (window != 0) {
        DAT_0082AF14 = callback;
        DAT_00ABDFEC = callback;
        SetWindowLongA(window, DWL_USER, (LONG)&result);
        SendMessageA(window, 0x4A9, 0, 1);
        UI_FocusOnWindow(window);
        while (result == 0 && UI::Updated() != true) {
            if (callback != 0) {
                callback();
            }
            FUN_00532100(false);
        }
        UI_EndDialog(window);
    }
    DAT_0082AF14 = (Callback_00595BC0)FUN_0048D1D0;
    DAT_00ABDFEC = 0;
    if (DAT_00ABE154 != 0) {
        if (DAT_00ABE154->unknown_00 != 0) {
            RawFileClass file("RandMap.img");
            FUN_007B05C0(&file, (void*)DAT_00ABE154->unknown_00, DAT_00885780);
        }
        delete DAT_00ABE154;
        DAT_00ABE154 = 0;
    }
    if (DAT_00ABE150 != 0) {
        delete DAT_00ABE150;
        DAT_00ABE150 = 0;
    }
    return result;
}

// FUNCTION: GAMEMD 0x596C70
void MapSeedClass::FUN_00596C70(HWND__* window)
{
    {
        int old = unknown_3C;
        HWND item = GetDlgItem(window, 0x405);
        int now = SendMessageA(item, 0x150, SendMessageA(item, 0x147, 0, 0), 0);
        unknown_3C = now;
        if (old != now)
            DAT_00ABE2D8 = 1;
    }
    {
        int old = unknown_38;
        HWND item = GetDlgItem(window, 0x407);
        int now = SendMessageA(item, 0x150, SendMessageA(item, 0x147, 0, 0), 0);
        unknown_38 = now;
        if (old != now)
            DAT_00ABE2D8 = 1;
    }
    {
        int old = unknown_40;
        HWND item = GetDlgItem(window, 0x408);
        int now = SendMessageA(item, 0x150, SendMessageA(item, 0x147, 0, 0), 0);
        unknown_40 = now;
        if (old != now)
            DAT_00ABE2D8 = 1;
    }
    {
        int old = unknown_48;
        HWND item = GetDlgItem(window, 0x3EA);
        int now = SendMessageA(item, 0x150, SendMessageA(item, 0x147, 0, 0), 0);
        unknown_48 = now;
        if (old != now)
            DAT_00ABE2D8 = 1;
    }
    {
        int old = unknown_64;
        HWND item = GetDlgItem(window, 0x406);
        int now = SendMessageA(item, 0x150, SendMessageA(item, 0x147, 0, 0), 0);
        unknown_64 = now;
        unknown_68 = now;
        if (old != now)
            DAT_00ABE2D8 = 1;
    }
    {
        int old = unknown_50;
        HWND item = GetDlgItem(window, 0x3EB);
        int now = SendMessageA(item, 0x400, 0, 0);
        unknown_50 = now;
        if (old != now)
            DAT_00ABE2D8 = 1;
    }
    if (DAT_00ABE2D8) {
        FUN_00597260(unknown_3C);
        delete DAT_00ABE154;
        DAT_00ABE154 = 0;
        DAT_00ABE2D8 = 0;
    }
    FUN_005975E0();
}

// FUNCTION: GAMEMD 0x597260
void MapSeedClass::FUN_00597260(int a1)
{
    unknown_4C = DAT_00886B88.FUN_0065C7E0(DAT_0082B0A8[a1], DAT_0082B0BC[a1]);
    unknown_44 = DAT_00886B88.FUN_0065C7E0(DAT_0082B10C[a1], DAT_0082B120[a1]);
    unknown_60 = DAT_00886B88.FUN_0065C7E0(DAT_00ABED40[a1], DAT_0082B0F8[a1]);
    unknown_6C = DAT_00886B88.FUN_0065C7E0(DAT_00ABED18[a1], DAT_0082B0D0[a1]);
    unknown_70 = DAT_00886B88.FUN_0065C7E0(DAT_0082B080[a1], DAT_0082B094[a1]);
    unknown_54 = unknown_40 * 0x14;
    unknown_58 = DAT_00886B88.FUN_0065C7E0(0, 100);
    int lo = DAT_00ABE260[a1];
    int hi = DAT_00ABE27C[a1];
    if (lo < 0)
        lo = 0;
    else if (lo > 100)
        lo = 100;
    if (hi < 0)
        hi = 0;
    else if (hi > 100)
        hi = 100;
    if (lo > hi)
        lo = hi;
    unknown_5C = DAT_00886B88.FUN_0065C7E0(lo, hi);
    unknown_74 = DAT_00886B88.FUN_0065C7E0(0, 0xFFFF);
}

// FUNCTION: GAMEMD 0x597380
void MapSeedClass::FUN_00597380()
{
    unknown_38 = DAT_00886B88.FUN_0065C7E0(0, 100) >= 0x32;
    unknown_3C = DAT_00886B88.FUN_0065C7E0(1, 4);
    unknown_48 = DAT_00886B88.FUN_0065C7E0(0, 3);
    unknown_40 = DAT_00886B88.FUN_0065C7E0(0, 3);
    unknown_64 = DAT_00886B88.FUN_0065C7E0(0, 3);
    unknown_68 = unknown_64;
    FUN_00597260(unknown_3C);
    FUN_007CA489(&unknown_78, FUN_00734E60(DAT_0082BA2C, 0, DAT_0082BA48, 0xF5E));
    unknown_74 = DAT_00886B88.FUN_0065C7E0(0, 0xFFFF);
    FUN_005975E0();
}

// FUNCTION: GAMEMD 0x597730
bool MapSeedClass::FUN_00597730(const char* a1)
{
    if (a1)
        return Slot2(a1, &unknown_78);
    return FUN_00558810((const wchar_t*)&unknown_78) ? true : false;
}

// FUNCTION: GAMEMD 0x597D40
// Tail-forwards to another function.
void Obj_00597D40::FUN_00597D40()
{
    FUN_00558840();
}

// FUNCTION: GAMEMD 0x597D50
bool MapSeedClass::DeleteMission(char const* filename)
{
    return LoadOptionsClass::DeleteMission(filename);
}

// FUNCTION: GAMEMD 0x597F80
// Calls other functions. Vtable slot 5 of MapSeedClass (RTTI).
void Obj_00597F80::FUN_00597F80()
{
    FUN_00734E60(DAT_0082BC3C, 0, DAT_0082BA48, 0x15C4);
}

// FUNCTION: GAMEMD 0x597FA0
// Calls other functions. Vtable slot 6 of MapSeedClass (RTTI).
void Obj_00597FA0::FUN_00597FA0()
{
    FUN_00734E60(DAT_0082BC4C, 0, DAT_0082BA48, 0x15CA);
}

// FUNCTION: GAMEMD 0x597FC0
// Calls other functions. Vtable slot 7 of MapSeedClass (RTTI).
void Obj_00597FC0::FUN_00597FC0()
{
    FUN_00734E60(DAT_0082BC5C, 0, DAT_0082BA48, 0x15D0);
}

// FUNCTION: GAMEMD 0x597FE0
// Calls other functions. Vtable slot 8 of MapSeedClass (RTTI).
void Obj_00597FE0::FUN_00597FE0()
{
    FUN_00734E60(DAT_0082BC70, 0, DAT_0082BA48, 0x15D6);
}

// FUNCTION: GAMEMD 0x598160
// One draw from the map generator's random source, scaled by the spread and offset by the base.
double __stdcall FUN_00598160(double base, double spread)
{
    return DAT_00ABDFB8.FUN_005980C0() * spread + base;
}

// FUNCTION: GAMEMD 0x598180
double __stdcall FUN_00598180(double a1, double a2, double a3, double a4)
{
    double v;
    if (a1 - a2 > a4 || a1 + a2 < a3) {
        a2 = (a4 - a3) * 0.5;
        a1 = a2 + a3;
    }
    do {
        v = DAT_00ABDFB8.FUN_005980C0() * a2 + a1;
    } while (v < a3 || v > a4);
    return v;
}

// FUNCTION: GAMEMD 0x599530
void FUN_00599530(Obj_0059C580* a1)
{
    a1->unknown_304 = 0;
    a1->unknown_308 = 0;
    if (DAT_00ABED10 != 0) {
        delete[] DAT_00ABED10;
        DAT_00ABED10 = 0;
    }
    for (int i = DAT_00ABDF90.Count - 1; i >= 0; i--) {
        MapRegionClass* p = DAT_00ABDF90.Items[i];
        if (p)
            delete p;
    }
    DAT_00ABED14 = 0;
    DAT_0087F7E8.FUN_00568BB0(1);
    // STRING: GAMEMD 0x82BDE4 "RMG: Compute Radar Image\n"
    FUN_004068E0("RMG: Compute Radar Image\n");
    DAT_0087F7E8.FUN_00654490(&DAT_0087F8E4);
    DAT_0087F7E8.FUN_00654650();
}

// FUNCTION: GAMEMD 0x59A670
void __stdcall FUN_0059A670(int a1)
{
    if (DAT_00A8B230->unknown_3598)
        Session_00A8B238.FUN_0069AE90(a1 + 0x63);
    else
        DAT_00AC4F58.FUN_00643C50(0, (double)a1, 0xFFFFFFFF, 0xFFFFFFFF);
}

// FUNCTION: GAMEMD 0x59B6D0
void FUN_0059B6D0()
{
    DAT_0087F7E8.FUN_00578350();
    CellClass* it;
    while ((it = DAT_0087F7E8.FUN_00578290()) != 0) {
        if (it->FUN_004865B0()) {
            for (int i = 0; i < 8; i += 2) {
                CellClass* n = it->FUN_00481810(i);
                if (n->FUN_00486380())
                    n->IsoTileTypeIndex = DAT_00AA0E18;
            }
        }
    }
}

// FUNCTION: GAMEMD 0x59B940
// When `area` is the whole map rectangle (0xABE2F0) this is the plain
// distance from a1 to a2. Otherwise a2 and a4 are compared along the two
// diagonals (half sums and half differences): the result weighs those
// components by a5 and a6 over their length and scales by the larger axis
// distance between a1 and a2 (0 when a2 and a4 share both diagonals).
float __stdcall FUN_0059B940(CellStruct* a1, CellStruct* a2, Rect_4i* area, CellStruct* a4, float a5, float a6)
{
    if (*area != DAT_00ABE2F0) {
        int across = abs(((a2->X - a2->Y) >> 1) - ((a4->X - a4->Y) >> 1));
        int along = abs(((a2->X + a2->Y) >> 1) - ((a4->X + a4->Y) >> 1));
        if (across == 0 && along == 0) {
            return 0.0f;
        }
        double length = FUN_004CAC40(along * along + across * across);
        double share = across / length;
        int dx = abs(a1->X - a2->X);
        int dy = abs(a1->Y - a2->Y);
        int steps = dx > dy ? dx : dy;
        return (a5 * share + a6 * (along / length)) * steps;
    }
    int dy = a1->Y - a2->Y;
    int dx = a1->X - a2->X;
    return FUN_004CAC40(dy * dy + dx * dx);
}

// FUNCTION: GAMEMD 0x59BAB0
// True when `a1` lies in `a2`: inside the ellipse inscribed in the rectangle
// (axis weights `a4`/`a5`) when `a3` is set, else inside the rectangle itself.
// The rectangle at 0xABE2F0 always passes.
bool __stdcall FUN_0059BAB0(CellStruct* a1, Rect_4i* a2, char a3, double a4, double a5)
{
    if (*a2 == DAT_00ABE2F0)
        return true;
    if (a3) {
        double dx = (double)(a1->X - a2->unknown_00 * 2 - a1->Y - 1 + DAT_0087F8DC) * 0.5 -
                    (double)a2->unknown_08 * 0.5;
        double dy = (double)(a1->X - a2->unknown_04 * 2 - DAT_0087F8DC - 1 + a1->Y) * 0.5 -
                    (double)a2->unknown_0C * 0.5;
        if (dx * dx * a4 + dy * dy * a5 < 1.0)
            return true;
    } else {
        int x = a1->X;
        int y = a1->Y;
        if (x >= a2->unknown_00 && x < a2->unknown_08 + a2->unknown_00 && y >= a2->unknown_04 &&
            y < a2->unknown_0C + a2->unknown_04)
            return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x59C530
void FUN_0059C530()
{
    DAT_0087F7E8.FUN_00578350();
    CellClass* it;
    while ((it = DAT_0087F7E8.FUN_00578290()) != 0) {
        if (it->IsoTileTypeIndex >= DAT_00ABAD28 && it->IsoTileTypeIndex < DAT_00ABAD28 + 0x2A) {
            it->IsoTileTypeIndex = 0;
            it->Height = 0;
        }
    }
}

// FUNCTION: GAMEMD 0x59C630
void FUN_0059C630()
{
    DAT_0087F7E8.FUN_00578350();
    CellClass* it;
    while ((it = DAT_0087F7E8.FUN_00578290()) != 0) {
        if (it->IsoTileTypeIndex == DAT_00AA0738 && it->Height == 0) {
            CellClass* n2 = it->GetNeighbourCell(2);
            CellClass* n4 = it->GetNeighbourCell(4);
            CellClass* n3 = it->GetNeighbourCell(3);
            if (n2->IsoTileTypeIndex == DAT_00AA0738 && n2->Height == 0 && n4->IsoTileTypeIndex == DAT_00AA0738 &&
                n4->Height == 0 && n3->IsoTileTypeIndex == DAT_00AA0738 && n3->Height == 0 && Inline_0059C630(1, 10) != 1) {
                int r = Inline_0058C320(241);
                int step;
                if (r >= 240)
                    step = 247 - r;
                else
                    step = r / 40;
                FUN_005A6C10(DAT_00AA0738 + step, &it->MapCoords, Inline_CellOwner(it->MapCoords), -1);
            } else {
                it->IsoTileTypeIndex = DAT_00AA0738 + 8 + Inline_0058C320(200) / 40;
            }
        }
    }
}

// FUNCTION: GAMEMD 0x59C800
bool __stdcall FUN_0059C800(int a1)
{
    DAT_0087F7E8.FUN_00578350();
    CellClass* it;
    while ((it = DAT_0087F7E8.FUN_00578290()) != 0) {
        int id;
        if (DAT_00ABED10 == 0)
            id = -1;
        else
            id = DAT_00ABED10[it->MapCoords.Y * DAT_0089C2DC + it->MapCoords.X].unknown_38;
        if (id == a1 && (it->IsoTileTypeIndex == 0 || it->IsoTileTypeIndex == 0xFFFF))
            it->IsoTileTypeIndex = DAT_00AA0E18;
    }
    return true;
}

// FUNCTION: GAMEMD 0x59C880
void Obj_0059C580::FUN_0059C880(int a1, int a2, int a3, int a4)
{
    DAT_0087F7E8.FUN_00578350();
    CellClass* it;
    while ((it = DAT_0087F7E8.FUN_00578290()) != 0) {
        CellStruct c = it->MapCoords;
        Rec_50* r = &DAT_00ABED10[c.Y * DAT_0089C2DC + c.X];
        if (r->unknown_38 == a1) {
            r->unknown_38 = a2;
            r->unknown_4B = 0;
            it->IsoTileTypeIndex = a4;
            it->Height = 0;
            it->Level = (a3 == -1) ? unknown_30C : a3;
        }
    }
}

// FUNCTION: GAMEMD 0x59D440
int Obj_0059C580::FUN_0059D440()
{
    int n = unknown_4C;
    if (n == 0)
        return 0;
    return (int)((double)unknown_184 * unknown_180 * n * 0.008 + 100.0);
}

// FUNCTION: GAMEMD 0x59E640
void __stdcall FUN_0059E640(int a1, char a2)
{
    DAT_0087F7E8.FUN_00578350();
    CellClass* it;
    while ((it = DAT_0087F7E8.FUN_00578290()) != 0) {
        CellStruct c = it->MapCoords;
        int id;
        if (DAT_00ABED10 == 0)
            id = -1;
        else
            id = DAT_00ABED10[c.Y * DAT_0089C2DC + c.X].unknown_38;
        if (id == a1)
            it->Level = a2;
    }
}

// FUNCTION: GAMEMD 0x59E6C0
void __stdcall FUN_0059E6C0(int a1, char a2)
{
    DAT_0087F7E8.FUN_00578350();
    CellClass* it;
    while ((it = DAT_0087F7E8.FUN_00578290()) != 0) {
        CellStruct c = it->MapCoords;
        int id;
        if (DAT_00ABED10 == 0)
            id = -1;
        else
            id = DAT_00ABED10[c.Y * DAT_0089C2DC + c.X].unknown_38;
        if (id == a1)
            it->Level += a2;
    }
}

// FUNCTION: GAMEMD 0x5A1270
void FUN_005A1270()
{
    DAT_0087F7E8.FUN_00578350();
    CellClass* it;
    while ((it = DAT_0087F7E8.FUN_00578290()) != 0) {
        CellStruct c = it->MapCoords;
        DAT_00ABED10[c.Y * DAT_0089C2DC + c.X].unknown_3C = 0;
    }
}

// FUNCTION: GAMEMD 0x5A12D0
void __stdcall FUN_005A12D0(char a1, int a2)
{
    DAT_0087F7E8.FUN_00578350();
    CellClass* it;
    while ((it = DAT_0087F7E8.FUN_00578290()) != 0) {
        CellStruct c = it->MapCoords;
        int id;
        if (DAT_00ABED10 == 0)
            id = -1;
        else
            id = DAT_00ABED10[c.Y * DAT_0089C2DC + c.X].unknown_38;
        if (id != a2)
            it->Level += a1;
    }
}

// FUNCTION: GAMEMD 0x5A19E0
void Obj_0059C580::FUN_005A19E0()
{
    DAT_0087F7E8.FUN_00578350();
    CellClass* it;
    while ((it = DAT_0087F7E8.FUN_00578290()) != 0) {
        CellClass* c5 = it->GetNeighbourCell(5);
        CellClass* c1 = it->GetNeighbourCell(1);
        CellClass* c3 = it->GetNeighbourCell(3);
        CellClass* c2 = it->GetNeighbourCell(2);
        CellClass* c6 = it->GetNeighbourCell(6);
        unsigned int v = DAT_0087F7E8.FUN_00579B70(it);
        if (v == 0x83) {
            if (DAT_0087F7E8.FUN_00579B70(c3) == 0x83 && c2->FUN_00486380()) {
                if (Inline_0058C320(1) == 0) {
                    c2->Level -= 4;
                    Inline_SetCellOwner(c2->MapCoords, Inline_CellOwner(it->MapCoords));
                }
            }
        } else if (v == 0x38) {
            if (DAT_0087F7E8.FUN_00579B70(c3) == 0x38 && c6->FUN_00486380()) {
                if (Inline_0058C320(1) == 0) {
                    c6->Level -= 4;
                    Inline_SetCellOwner(c6->MapCoords, Inline_CellOwner(it->MapCoords));
                }
            }
        } else if (v == 0xE0) {
            if (DAT_0087F7E8.FUN_00579B70(c5) == 0xE0 && DAT_0087F7E8.FUN_00579B70(c1) == 0xE0 && it->FUN_00486380()) {
                it->Level += 4;
                Inline_SetCellOwner(it->MapCoords, Inline_CellOwner(c6->MapCoords));
            }
        }
    }
}

// FUNCTION: GAMEMD 0x5A1E10
void Obj_0059C580::FUN_005A1E10()
{
    if (unknown_3C == 4 || unknown_3C == 3) {
        FUN_0058EBC0();
        FUN_0058EF10();
        FUN_005A19E0();
        DAT_0087F7E8.FUN_00578E60(0, -1);
        FUN_005A17F0();
    }
}

// 0x4CAC40: x87 helper taking one double and returning one (callee only).
double __cdecl FUN_004CAC40(double value);
extern const double DAT_007ED7C0;
// FUNCTION: GAMEMD 0x5A2ED0
double __stdcall FUN_005A2ED0(const CellStruct* a1, const CellStruct* a2)
{
    int dx = a1->X - a2->X;
    int dy = a1->Y - a2->Y;
    double distance = FUN_004CAC40((double)(dx * dx + dy * dy));
    return (double)(unsigned int)DAT_00ABE890.FUN_0065C780() * DAT_007ED7C0 * 2.3283064370807974e-10 + distance;
}

// FUNCTION: GAMEMD 0x5A33F0
void FUN_005A33F0()
{
    DAT_0087F7E8.FUN_00578350();
    CellClass* it;
    while ((it = DAT_0087F7E8.FUN_00578290()) != 0) {
        if (it->FUN_004865B0()) {
            for (int f = 0; f < 8; f++) {
                CellStruct adj = it->MapCoords;
                adj = Inline_005A33F0(adj, DAT_0089F688[f & 7]);
                int x = adj.X;
                int y = adj.Y;
                if (y + x > DAT_00ABED04 && x - y < DAT_00ABED04 && y - x < DAT_00ABED04 && y + x <= DAT_00ABED08) {
                    if (DAT_0087F7E8.FUN_005657A0(&adj)->FUN_00486380()) {
                        DAT_00ABED10[adj.Y * DAT_0089C2DC + adj.X].unknown_08 = 0.5;
                        DAT_00ABED10[adj.Y * DAT_0089C2DC + adj.X].unknown_45 = 1;
                        break;
                    }
                }
            }
        } else if (it->FUN_004863D0()) {
            for (int g = 0; g < 8; g++) {
                CellStruct adj = it->MapCoords;
                adj = Inline_005A33F0(adj, DAT_0089F688[g & 7]);
                int x = adj.X;
                int y = adj.Y;
                if (y + x > DAT_00ABED04 && x - y < DAT_00ABED04 && y - x < DAT_00ABED04 && y + x <= DAT_00ABED08) {
                    if (DAT_0087F7E8.FUN_005657A0(&adj)->FUN_00486380()) {
                        DAT_00ABED10[adj.Y * DAT_0089C2DC + adj.X].unknown_45 = 1;
                        break;
                    }
                }
            }
        }
    }
}

// FUNCTION: GAMEMD 0x5A3A60
void FUN_005A3A60()
{
    DAT_0087F7E8.FUN_00578350();
    CellClass* it;
    while ((it = DAT_0087F7E8.FUN_00578290()) != 0) {
        CellStruct c = it->MapCoords;
        Rec_50* r = &DAT_00ABED10[c.Y * DAT_0089C2DC + c.X];
        r->unknown_28 = DAT_007ED7F0;
        r->unknown_20 = DAT_007ED7F8;
    }
}

extern const double DAT_007ED800;
// FUNCTION: GAMEMD 0x5A4AE0
double __stdcall FUN_005A4AE0(const CellStruct* a1, const CellStruct* a2)
{
    int dx = a1->X - a2->X;
    int dy = a1->Y - a2->Y;
    double distance = FUN_004CAC40((double)(dx * dx + dy * dy));
    return (double)(unsigned int)DAT_00ABE890.FUN_0065C780() * DAT_007ED800 * 2.3283064370807974e-10 + distance;
}

extern const double DAT_007ED808;
// FUNCTION: GAMEMD 0x5A4FA0
double __stdcall FUN_005A4FA0(const CellStruct* a1, const CellStruct* a2)
{
    int dx = a1->X - a2->X;
    int dy = a1->Y - a2->Y;
    double distance = FUN_004CAC40((double)(dx * dx + dy * dy));
    return (double)(unsigned int)DAT_00ABE890.FUN_0065C780() * DAT_007ED808 * 2.3283064370807974e-10 + distance;
}

// FUNCTION: GAMEMD 0x5A6BA0
bool FUN_005A6BA0(CellStruct* a1)
{
    int y = a1->Y;
    int x = a1->X;
    int sy = y - 7;
    int ex = x + 7;
    int sx = x - 7;
    int ey = y + 7;
    for (; sx < ex; sx++) {
        for (int i = sy; i < ey; i++) {
            CellStruct c;
            c.X = (short)sx;
            c.Y = (short)i;
            if (DAT_0087F7E8.FUN_005657A0(&c)->FUN_004863D0())
                return false;
        }
    }
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5A6C10
// Stamp tile `a1` at `a2`: every on-map sub-tile cell with image data takes the
// tile index, its sub-tile number as height, the sub-tile slope and (unless
// `a4` is -1) a level of `a4` plus the sub-tile's own less four; the cell
// record then belongs to region `a3`.
void FUN_005A6C10(int a1, CellStruct* a2, int a3, int a4)
{
    IsometricTileTypeClass* t = DAT_00A8ED2C[a1];
    TileImageHeader* d = (t->*t->Vfptr->At_9C)();
    if (d != 0) {
        for (int y = 0; y < t->unknown_2E8; y++) {
            for (int x = 0; x < t->unknown_2E4; x++) {
                CellStruct c = Cell(a2->X + x, a2->Y + y);
                if (Inline_005942F0(c)) {
                    CellClass* cell = DAT_0087F7E8.FUN_005657A0(&c);
                    int index = t->unknown_2E4 * y + x;
                    SubTileImage* sub = d->SubTiles[index];
                    if (sub != 0) {
                        cell->IsoTileTypeIndex = t->unknown_294;
                        cell->Height = (char)index;
                        if (a4 != -1)
                            cell->Level = sub->unknown_28 + a4 - 4;
                        cell->SlopeIndex = sub->MorphType;
                        if (DAT_00ABED10 != 0)
                            DAT_00ABED10[c.Y * DAT_0089C2DC + c.X].unknown_38 = a3;
                    }
                }
            }
        }
    }
}

// FUNCTION: GAMEMD 0x5A7250
// True when all four corners lie on the map and every cell of the rectangle
// passes: cells of the first kind need `allow_first`, of the second kind
// `allow_second`, anything else one of the three remaining predicates.
bool FUN_005A7250(const Rect_005A7250* rect, bool allow_first, bool allow_second)
{
    int left = rect->X;
    int top = rect->Y;
    if (!CellInsideMap(InlineCell_005A7250(left, top)) ||
        !CellInsideMap(InlineCell_005A7250(left + rect->Width - 1, top)) ||
        !CellInsideMap(InlineCell_005A7250(left, top + rect->Height - 1)) ||
        !CellInsideMap(InlineCell_005A7250(left + rect->Width - 1, top + rect->Height - 1))) {
        return false;
    }

    for (int y = top; y < rect->Y + rect->Height; y++) {
        for (int x = left; x < rect->X + rect->Width; x++) {
            Cell_005A7250* cell = DAT_0087F7E8.GetCell(InlineCell_005A7250(x, y));
            if (cell->FUN_004866D0()) {
                if (!allow_first) {
                    return false;
                }
            } else if (cell->FUN_004866F0()) {
                if (!allow_second) {
                    return false;
                }
            } else if (!cell->FUN_00486380() && !cell->FUN_00486650() && !cell->FUN_00486670()) {
                return false;
            }
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x5A7640
// Bounding box of every cell in `list`, as origin and inclusive extent, starting from (999, 999)
// and (0, 0).
Rect_4i* __fastcall FUN_005A7640(Rect_4i* out, DynamicVectorClass<Cell>* list)
{
    CellStruct hi;
    CellStruct lo;
    hi.X = 0;
    lo.X = 999;
    hi.Y = 0;
    lo.Y = 999;
    for (int i = list->Count - 1; i >= 0; i--) {
        Cell c = list->Items[i];
        if (c.X < lo.X)
            lo.X = c.X;
        if (c.Y < lo.Y)
            lo.Y = c.Y;
        if (c.X > hi.X)
            hi.X = c.X;
        if (c.Y > hi.Y)
            hi.Y = c.Y;
    }
    Rect_4i r;
    r.unknown_00 = lo.X;
    r.unknown_04 = lo.Y;
    r.unknown_08 = hi.X - lo.X + 1;
    r.unknown_0C = hi.Y - lo.Y + 1;
    *out = r;
    return out;
}

// FUNCTION: GAMEMD 0x5A7E90
// For each sub-tile cell of tile `a1` placed at `a2` that lies on the map,
// fetch the cell; where the tile has image data, reset its +0x38 word to
// 0xFFFF and clear the +0x11A byte.
void FUN_005A7E90(int a1, CellStruct* a2)
{
    IsometricTileTypeClass* t = DAT_00A8ED2C[a1];
    TileImageHeader* d = (t->*t->Vfptr->At_9C)();
    if (d != 0) {
        for (int y = 0; y < t->unknown_2E8; y++) {
            for (int x = 0; x < t->unknown_2E4; x++) {
                CellStruct c = Cell(a2->X + x, a2->Y + y);
                if (Inline_005942F0(c)) {
                    CellClass* cell = DAT_0087F7E8.FUN_005657A0(&c);
                    if (d->SubTiles[t->unknown_2E4 * y + x] != 0) {
                        cell->IsoTileTypeIndex = 0xFFFF;
                        cell->Height = 0;
                    }
                }
            }
        }
    }
}

// FUNCTION: GAMEMD 0x5A7FA0
void FUN_005A7FA0(int a1, CellStruct* a2, char a3)
{
    IsometricTileTypeClass* t = DAT_00A8ED2C[a1];
    TileImageHeader* d = (t->*t->Vfptr->At_9C)();
    if (d != 0) {
        for (int y = 0; y < t->unknown_2E8; y++) {
            for (int x = 0; x < t->unknown_2E4; x++) {
                CellStruct c;
                c.X = a2->X + x;
                c.Y = a2->Y + y;
                if (Inline_005942F0(c) && d->SubTiles[t->unknown_2E4 * y + x] != 0)
                    DAT_00ABED10[c.Y * DAT_0089C2DC + c.X].unknown_46 = a3;
            }
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Build a link from a cell offset and a facing.
// FUNCTION: GAMEMD 0x5A9920
TileLink::TileLink(const CellOffset& cell, int facing) throw()
    : Cell(cell), Facing(facing)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Default link: the cell offset zeroed by CellOffset's own constructor and no
// facing yet. This is the body the array-new loops of every list constructor
// below inline.
// FUNCTION: GAMEMD 0x5A9940
TileLinkStandin::TileLinkStandin() throw()
{
    Facing = -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Copy one link.
// FUNCTION: GAMEMD 0x5A9960
TileLink::TileLink(const TileLink& other) throw()
    : Cell(other.Cell), Facing(other.Facing)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Build one queued walk step from its two (tile, cell) endpoints and the link
// index that produced it.
// FUNCTION: GAMEMD 0x5A9980
TileLinkStep::TileLinkStep(int fromTile, const CellOffset& fromCell, int toTile,
                           const CellOffset& toCell, int index) throw()
    : FromTile(fromTile), FromCell(fromCell), ToTile(toTile),
      ToCell(toCell), Index(index)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Empty walk step: both endpoints are the "no tile" sentinel over a zeroed
// cell, and no link index. The two cells are assigned from temporaries rather
// than constructed in place, which is what puts the pair of stack-slot builds
// at the top of retail's body.
// FUNCTION: GAMEMD 0x5A99B0
TileLinkStep::TileLinkStep() throw()
    : FromTile(0xFFFF), FromCell(CellOffset()), ToTile(0xFFFF),
      ToCell(CellOffset()), Index(-1)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// A one-link slot.
// FUNCTION: GAMEMD 0x5A9A20
TileLinkList::TileLinkList(const TileLink& a) throw()
{
    TileIndex = 0;
    Count = 1;
    Links = new TileLink[1];
    Links[0] = a;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// A two-link slot.
// FUNCTION: GAMEMD 0x5A9A70
TileLinkList::TileLinkList(const TileLink& a, const TileLink& b) throw()
{
    TileIndex = 0;
    Count = 2;
    Links = new TileLink[2];
    Links[0] = a;
    Links[1] = b;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// A three-link slot.
// FUNCTION: GAMEMD 0x5A9AE0
TileLinkList::TileLinkList(const TileLink& a, const TileLink& b,
                           const TileLink& c) throw()
{
    TileIndex = 0;
    Count = 3;
    Links = new TileLink[3];
    Links[0] = a;
    Links[1] = b;
    Links[2] = c;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// A four-link slot.
// FUNCTION: GAMEMD 0x5A9B60
TileLinkList::TileLinkList(const TileLink& a, const TileLink& b,
                           const TileLink& c, const TileLink& d) throw()
{
    TileIndex = 0;
    Count = 4;
    Links = new TileLink[4];
    Links[0] = a;
    Links[1] = b;
    Links[2] = c;
    Links[3] = d;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5A9BF0
PairHolder_005A9BF0::PairHolder_005A9BF0() :
    unknown_00(0),
    unknown_04(0)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Release a slot's link array and forget it.
// FUNCTION: GAMEMD 0x5A9C00
TileLinkList::~TileLinkList() throw()
{
    delete[] Links;
    Links = 0;
}

// SYNTHETIC: GAMEMD 0x5A9C20 -- initialiser entry: runs the table build, registers 0x5AC190
// SYNTHETIC: GAMEMD 0x5A9C40 -- table build: constructs the 109 slots in place
// SYNTHETIC: GAMEMD 0x5AC190 -- exit-time stub: destroys the 109 slots backwards
// GLOBAL: GAMEMD 0xABE370
// The theater tile-link table: 109 fixed slots of one to four links (see
// tile_link_table_methods.h). The four empty slots take the default constructor.
TileLinkList DAT_00ABE370[109] = {
    TileLinkList(TileLink(CellOffset(0, 0), 0), TileLink(CellOffset(2, 0), 1)),
    TileLinkList(TileLink(CellOffset(0, 0), 0), TileLink(CellOffset(1, 0), 2)),
    TileLinkList(TileLink(CellOffset(0, 0), 0), TileLink(CellOffset(1, 1), 3)),
    TileLinkList(TileLink(CellOffset(0, 0), 0), TileLink(CellOffset(1, 0), 5)),
    TileLinkList(TileLink(CellOffset(0, 0), 0), TileLink(CellOffset(0, 0), 6)),
    TileLinkList(TileLink(CellOffset(1, 0), 0), TileLink(CellOffset(1, 1), 7)),
    TileLinkList(TileLink(CellOffset(1, 0), 1), TileLink(CellOffset(1, 1), 2)),
    TileLinkList(TileLink(CellOffset(1, 0), 1), TileLink(CellOffset(1, 1), 3)),
    TileLinkList(TileLink(CellOffset(1, 0), 1), TileLink(CellOffset(0, 1), 4)),
    TileLinkList(TileLink(CellOffset(1, 0), 1), TileLink(CellOffset(0, 0), 6)),
    TileLinkList(TileLink(CellOffset(2, 0), 1), TileLink(CellOffset(1, 1), 7)),
    TileLinkList(TileLink(CellOffset(2, 0), 1), TileLink(CellOffset(0, 0), 0)),
    TileLinkList(TileLink(CellOffset(1, 0), 2), TileLink(CellOffset(1, 2), 3)),
    TileLinkList(TileLink(CellOffset(1, 0), 2), TileLink(CellOffset(0, 1), 4)),
    TileLinkList(TileLink(CellOffset(1, 0), 2), TileLink(CellOffset(1, 0), 5)),
    TileLinkList(TileLink(CellOffset(1, 0), 2), TileLink(CellOffset(1, 1), 7)),
    TileLinkList(TileLink(CellOffset(2, 1), 3), TileLink(CellOffset(0, 1), 4)),
    TileLinkList(TileLink(CellOffset(1, 1), 3), TileLink(CellOffset(1, 0), 5)),
    TileLinkList(TileLink(CellOffset(1, 1), 3), TileLink(CellOffset(0, 0), 6)),
    TileLinkList(TileLink(CellOffset(1, 1), 4), TileLink(CellOffset(1, 0), 5)),
    TileLinkList(TileLink(CellOffset(0, 1), 4), TileLink(CellOffset(0, 0), 6)),
    TileLinkList(TileLink(CellOffset(0, 1), 4), TileLink(CellOffset(1, 1), 7)),
    TileLinkList(TileLink(CellOffset(1, 1), 5), TileLink(CellOffset(1, 1), 7)),
    TileLinkList(TileLink(CellOffset(0, 1), 6), TileLink(CellOffset(1, 1), 7)),
    TileLinkList(TileLink(CellOffset(0, 0), 0), TileLink(CellOffset(1, 0), 2), TileLink(CellOffset(0, 1), 4)),
    TileLinkList(TileLink(CellOffset(1, 0), 2), TileLink(CellOffset(0, 1), 4), TileLink(CellOffset(0, 0), 6)),
    TileLinkList(TileLink(CellOffset(0, 0), 0), TileLink(CellOffset(0, 1), 4), TileLink(CellOffset(0, 0), 6)),
    TileLinkList(TileLink(CellOffset(0, 0), 0), TileLink(CellOffset(1, 0), 2), TileLink(CellOffset(0, 0), 6)),
    TileLinkList(TileLink(CellOffset(0, 0), 0), TileLink(CellOffset(1, 0), 2), TileLink(CellOffset(0, 1), 4), TileLink(CellOffset(0, 0), 6)),
    TileLinkList(TileLink(CellOffset(2, 0), 1), TileLink(CellOffset(2, 2), 3), TileLink(CellOffset(1, 1), 5)),
    TileLinkList(TileLink(CellOffset(1, 1), 7), TileLink(CellOffset(1, 1), 5), TileLink(CellOffset(2, 2), 3)),
    TileLinkList(TileLink(CellOffset(2, 0), 1), TileLink(CellOffset(1, 1), 7), TileLink(CellOffset(1, 1), 5)),
    TileLinkList(TileLink(CellOffset(1, 1), 7), TileLink(CellOffset(2, 0), 1), TileLink(CellOffset(2, 2), 3)),
    TileLinkList(TileLink(CellOffset(1, 1), 7), TileLink(CellOffset(1, 1), 5), TileLink(CellOffset(2, 0), 1), TileLink(CellOffset(2, 2), 3)),
    TileLinkList(TileLink(CellOffset(3, 0), 1), TileLink(CellOffset(3, 2), 2), TileLink(CellOffset(0, 2), 6)),
    TileLinkList(TileLink(CellOffset(3, 0), 1), TileLink(CellOffset(1, 2), 5)),
    TileLinkList(TileLink(CellOffset(3, 0), 1), TileLink(CellOffset(1, 2), 5)),
    TileLinkList(TileLink(CellOffset(3, 0), 1), TileLink(CellOffset(1, 2), 5)),
    TileLinkList(TileLink(CellOffset(3, 0), 1), TileLink(CellOffset(1, 2), 5)),
    TileLinkList(TileLink(CellOffset(2, 0), 1), TileLink(CellOffset(1, 1), 5)),
    TileLinkList(TileLink(CellOffset(1, 0), 1), TileLink(CellOffset(1, 0), 5)),
    TileLinkList(TileLink(CellOffset(1, 0), 1), TileLink(CellOffset(1, 0), 5)),
    TileLinkList(TileLink(CellOffset(1, 2), 5)),
    TileLinkList(TileLink(CellOffset(1, 1), 5)),
    TileLinkList(TileLink(CellOffset(1, 1), 5)),
    TileLinkList(TileLink(CellOffset(3, 0), 1)),
    TileLinkList(TileLink(CellOffset(2, 0), 1)),
    TileLinkList(TileLink(CellOffset(2, 0), 1)),
    TileLinkList(TileLink(CellOffset(4, 0), 1), TileLink(CellOffset(1, 1), 5)),
    TileLinkList(TileLink(CellOffset(2, 0), 1), TileLink(CellOffset(1, 3), 5)),
    TileLinkList(),
    TileLinkList(TileLink(CellOffset(0, 0), 6), TileLink(CellOffset(3, 0), 2)),
    TileLinkList(TileLink(CellOffset(0, 0), 6), TileLink(CellOffset(3, 0), 2)),
    TileLinkList(TileLink(CellOffset(0, 0), 6), TileLink(CellOffset(3, 0), 2)),
    TileLinkList(TileLink(CellOffset(0, 0), 6), TileLink(CellOffset(3, 0), 2)),
    TileLinkList(TileLink(CellOffset(0, 0), 6), TileLink(CellOffset(2, 0), 2)),
    TileLinkList(TileLink(CellOffset(0, 0), 6), TileLink(CellOffset(1, 0), 2)),
    TileLinkList(TileLink(CellOffset(0, 0), 6), TileLink(CellOffset(0, 0), 2)),
    TileLinkList(TileLink(CellOffset(0, 0), 6), TileLink(CellOffset(0, 0), 2)),
    TileLinkList(TileLink(CellOffset(0, 0), 6)),
    TileLinkList(TileLink(CellOffset(0, 0), 6)),
    TileLinkList(TileLink(CellOffset(0, 1), 6)),
    TileLinkList(TileLink(CellOffset(2, 0), 2)),
    TileLinkList(TileLink(CellOffset(1, 0), 2)),
    TileLinkList(TileLink(CellOffset(1, 0), 2)),
    TileLinkList(TileLink(CellOffset(0, 0), 6), TileLink(CellOffset(3, 1), 2)),
    TileLinkList(TileLink(CellOffset(0, 1), 6), TileLink(CellOffset(3, 0), 2)),
    TileLinkList(),
    TileLinkList(TileLink(CellOffset(1, 1), 7), TileLink(CellOffset(3, 3), 3)),
    TileLinkList(TileLink(CellOffset(1, 1), 7), TileLink(CellOffset(3, 3), 3)),
    TileLinkList(TileLink(CellOffset(1, 1), 7), TileLink(CellOffset(3, 3), 3)),
    TileLinkList(TileLink(CellOffset(1, 1), 7), TileLink(CellOffset(3, 3), 3)),
    TileLinkList(TileLink(CellOffset(1, 1), 7), TileLink(CellOffset(2, 2), 3)),
    TileLinkList(TileLink(CellOffset(1, 1), 7), TileLink(CellOffset(1, 1), 3)),
    TileLinkList(TileLink(CellOffset(1, 1), 7), TileLink(CellOffset(1, 1), 3)),
    TileLinkList(TileLink(CellOffset(1, 1), 7)),
    TileLinkList(TileLink(CellOffset(1, 1), 7)),
    TileLinkList(TileLink(CellOffset(1, 1), 7)),
    TileLinkList(TileLink(CellOffset(3, 3), 3)),
    TileLinkList(TileLink(CellOffset(1, 2), 3)),
    TileLinkList(TileLink(CellOffset(2, 2), 3)),
    TileLinkList(TileLink(CellOffset(1, 1), 7), TileLink(CellOffset(4, 2), 3)),
    TileLinkList(TileLink(CellOffset(1, 1), 7), TileLink(CellOffset(2, 4), 3)),
    TileLinkList(),
    TileLinkList(TileLink(CellOffset(0, 0), 0), TileLink(CellOffset(0, 3), 4)),
    TileLinkList(TileLink(CellOffset(0, 0), 0), TileLink(CellOffset(0, 3), 4)),
    TileLinkList(TileLink(CellOffset(0, 0), 0), TileLink(CellOffset(0, 3), 4)),
    TileLinkList(TileLink(CellOffset(0, 0), 0), TileLink(CellOffset(0, 3), 4)),
    TileLinkList(TileLink(CellOffset(0, 0), 0), TileLink(CellOffset(0, 2), 4)),
    TileLinkList(TileLink(CellOffset(0, 0), 0), TileLink(CellOffset(0, 1), 4)),
    TileLinkList(TileLink(CellOffset(0, 0), 0), TileLink(CellOffset(0, 0), 4)),
    TileLinkList(TileLink(CellOffset(0, 0), 0), TileLink(CellOffset(0, 0), 4)),
    TileLinkList(TileLink(CellOffset(0, 3), 4)),
    TileLinkList(TileLink(CellOffset(0, 2), 4)),
    TileLinkList(TileLink(CellOffset(0, 2), 4)),
    TileLinkList(TileLink(CellOffset(0, 0), 0)),
    TileLinkList(TileLink(CellOffset(0, 0), 0)),
    TileLinkList(TileLink(CellOffset(0, 0), 0)),
    TileLinkList(TileLink(CellOffset(1, 0), 0), TileLink(CellOffset(0, 3), 4)),
    TileLinkList(TileLink(CellOffset(0, 0), 0), TileLink(CellOffset(1, 3), 4)),
    TileLinkList(),
    TileLinkList(TileLink(CellOffset(0, 0), 6), TileLink(CellOffset(0, 0), 2)),
    TileLinkList(TileLink(CellOffset(0, 0), 6), TileLink(CellOffset(0, 0), 2)),
    TileLinkList(TileLink(CellOffset(0, 0), 0), TileLink(CellOffset(0, 0), 4)),
    TileLinkList(TileLink(CellOffset(0, 0), 0), TileLink(CellOffset(0, 0), 4)),
    TileLinkList(TileLink(CellOffset(0, 0), 6), TileLink(CellOffset(0, 0), 2)),
    TileLinkList(TileLink(CellOffset(0, 0), 6), TileLink(CellOffset(0, 0), 2)),
    TileLinkList(TileLink(CellOffset(0, 0), 0), TileLink(CellOffset(0, 0), 4)),
    TileLinkList(TileLink(CellOffset(0, 0), 0), TileLink(CellOffset(0, 0), 4))
};

// A growable array of dwords, assigned from another (slot 3 releases the old storage).
struct Vec_005AC430 {
    virtual void vf_00(); virtual void vf_01(); virtual void vf_02();
    virtual void Clear();
    int* unknown_04;
    int unknown_08;
    bool unknown_0C;
    bool unknown_0D;
    int unknown_10;
    int unknown_14;
    Vec_005AC430* FUN_005AC430(const Vec_005AC430& other);
};
// FUNCTION: GAMEMD 0x005AC430
Vec_005AC430* Vec_005AC430::FUN_005AC430(const Vec_005AC430& other)
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005ACCC0
// VectorClass<TRect<int>>::operator==
// FUNCTION: GAMEMD 0x005ACD30
// VectorClass<TRect<int>>::SetCapacity
// FUNCTION: GAMEMD 0x005ACE50
// VectorClass<TRect<int>>::FindItemIndex
// FUNCTION: GAMEMD 0x005ACEB0
// VectorClass<TRect<int>>::Slot5
// FUNCTION: GAMEMD 0x005AC570
// VectorClass<TRect<int>>::Slot6
// FUNCTION: GAMEMD 0x005ACED0
// DynamicVectorClass<TRect<int>>::SetCapacity
// FUNCTION: GAMEMD 0x005ACFC0
// DynamicVectorClass<TRect<int>>::FindItemIndex
// FUNCTION: GAMEMD 0x005AC550
// DynamicVectorClass<TRect<int>>::Slot5
// VTABLE: GAMEMD 0x007ED970 -- VectorClass<TRect<int>>.
// VTABLE: GAMEMD 0x007ED99C -- DynamicVectorClass<TRect<int>>.
template class VectorClass<TRect<int> >;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x5AC620
// DynamicVectorClass<double>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x5AD270
// VectorClass<double>::Slot5 (slot 5)
template class VectorClass<double>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005AD0F0
// VectorClass<double>::operator==
// FUNCTION: GAMEMD 0x005AD130
// VectorClass<double>::SetCapacity
// FUNCTION: GAMEMD 0x005AD220
// VectorClass<double>::FindItemIndex
// FUNCTION: GAMEMD 0x005AC640
// VectorClass<double>::Slot6
// FUNCTION: GAMEMD 0x005AD290
// DynamicVectorClass<double>::SetCapacity
// FUNCTION: GAMEMD 0x005AD350
// DynamicVectorClass<double>::FindItemIndex
// VTABLE: GAMEMD 0x007EDA4C -- VectorClass<double>.
// VTABLE: GAMEMD 0x007EDA6C -- DynamicVectorClass<double>.
template class VectorClass<double>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5AD010
bool VectorResizeFamily::FUN_5AD010(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < Count) {
            Count = Length;
        }
        return true;
    }

    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5AD930
bool GrowPairVector::Grow_5AD930(int extra)
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005AD9C0
int __cdecl FUN_005AD9C0(const void* a, const void* b)
{
    if (*(const int*)a == *(const int*)b)
        return 0;
    if (*(const int*)a < *(const int*)b)
        return -1;
    return 1;
}

// FUNCTION: GAMEMD 0x5ADA40
// VectorClass<TRect<int>>::VectorClass(int, TRect<int>*), emitted by the explicit instantiation below.
template class VectorClass<TRect<int> >;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xABDF90
DynamicVectorClass<MapRegionClass*> DAT_00ABDF90;
// GLOBAL: GAMEMD 0xABDFB8
Gbl_00ABDFB8 DAT_00ABDFB8;
// GLOBAL: GAMEMD 0xABDFD0
int DAT_00ABDFD0;
// GLOBAL: GAMEMD 0xABDFD4
int DAT_00ABDFD4;
// GLOBAL: GAMEMD 0xABDFEC
Callback_00595BC0 DAT_00ABDFEC;
// GLOBAL: GAMEMD 0xABE150
Obj_00ABE150* DAT_00ABE150;
// GLOBAL: GAMEMD 0xABEC90
int DAT_00ABEC90;
// GLOBAL: GAMEMD 0xABECD0
int DAT_00ABECD0;
// GLOBAL: GAMEMD 0xABED10
Rec_50* DAT_00ABED10;
// GLOBAL: GAMEMD 0xABED14
int DAT_00ABED14;
// GLOBAL: GAMEMD 0x82AF18
int DAT_0082AF18[9] = {64, 128, 1, 32, 0, 2, 16, 8, 4};
// GLOBAL: GAMEMD 0x7ED6D8
extern const double DAT_007ED6D8 = 5.0;
// GLOBAL: GAMEMD 0x7ED6E0
extern const double DAT_007ED6E0 = 15.0;
// GLOBAL: GAMEMD 0x7ED7C0
extern const double DAT_007ED7C0 = 5.0;
// GLOBAL: GAMEMD 0x7ED7F0
double DAT_007ED7F0 = 0.005;
// GLOBAL: GAMEMD 0x7ED7F8
double DAT_007ED7F8 = 0.001;
// GLOBAL: GAMEMD 0x7ED800
extern const double DAT_007ED800 = 5.0;
// GLOBAL: GAMEMD 0x7ED808
extern const double DAT_007ED808 = 5.0;
// END defined globals
