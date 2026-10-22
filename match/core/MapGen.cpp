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

#include "deleting_dtor_sweep.h"
#include "../network/transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

#include "global_getter_family_methods.h"

#include <string.h>

// LIBRARY: GAMEMD 0x7C8B3D -- CRT free.
extern "C" void __cdecl gg_free(void*);

extern int DAT_00A9FABC;
extern void* DAT_00ABF3F4;
extern int DAT_00B2FF78[0x4000];
extern int DAT_00B1D5E0[0x4000];
extern void* DAT_00B77F54;
extern void* DAT_00B77F60;

#include "pair_vector_grow_sweep.h"

#include "trivial_tu130_methods.h"

#include "vector_class_operations.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

struct Cell { short X; short Y; Cell() {} bool operator==(const Cell& o) const { return X==o.X && Y==o.Y; } bool operator!=(const Cell& o) const { return !(*this==o); } };

template class DynamicVectorClass<Cell>;

 struct BaseNodeClass { int unknown_00; Cell unknown_04; unsigned char unknown_08; int unknown_0C; BaseNodeClass() {} BaseNodeClass(const BaseNodeClass& o) : unknown_00(o.unknown_00), unknown_04(o.unknown_04), unknown_08(o.unknown_08), unknown_0C(o.unknown_0C) {} bool operator==(const BaseNodeClass& o) const { return unknown_00==o.unknown_00 && unknown_04==o.unknown_04; } bool operator!=(const BaseNodeClass& o) const { return !(*this==o); } };

template class DynamicVectorClass<BaseNodeClass>;

template<class T> struct TPoint3D { T X; T Y; T Z; TPoint3D() {} bool operator==(const TPoint3D<T>& o) const { return X==o.X && Y==o.Y && Z==o.Z; } bool operator!=(const TPoint3D<T>& o) const { return !(*this==o); } };

struct Point2D { int X; int Y; Point2D() {} bool operator==(const Point2D& o) const { return X==o.X && Y==o.Y; } bool operator!=(const Point2D& o) const { return !(*this==o); } };

template class DynamicVectorClass<Point2D>;

template<class T> struct TRect { T X; T Y; T Width; T Height; TRect() {} bool operator==(const TRect<T>& o) const { return X==o.X && Y==o.Y && Width==o.Width && Height==o.Height; } bool operator!=(const TRect<T>& o) const { return !(*this==o); } };

template class DynamicVectorClass<TRect<int> >;

struct DirtyAreaStruct { int unknown_00; int unknown_04; int unknown_08; int unknown_0C; unsigned char unknown_10; DirtyAreaStruct() : unknown_00(0), unknown_04(0), unknown_08(0), unknown_0C(0), unknown_10(0) {} DirtyAreaStruct(const DirtyAreaStruct& o) : unknown_00(o.unknown_00), unknown_04(o.unknown_04), unknown_08(o.unknown_08), unknown_0C(o.unknown_0C), unknown_10(o.unknown_10) {} bool operator==(const DirtyAreaStruct& o) const { return unknown_10==o.unknown_10 && unknown_00==o.unknown_00 && unknown_04==o.unknown_04 && unknown_08==o.unknown_08 && unknown_0C==o.unknown_0C; } bool operator!=(const DirtyAreaStruct& o) const { return !(*this==o); } };

template class DynamicVectorClass<DirtyAreaStruct>;

#include "vector_class_operations.h"

template class DynamicVectorClass<double>;

GG_STATIC_ASSERT(sizeof(double) == 8);
GG_STATIC_ASSERT(sizeof(VectorClass<double >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<double >) == 0x18);

#include "vector_resize_family_methods.h"

#include "vector_class_operations.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

template class DynamicVectorClass<unsigned short>;


template class DynamicVectorClass<bool>;

template class DynamicVectorClass<double>;

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class PairHolder_005A9BF0
{
public:
    // FUNCTION: GAMEMD 0x5A9BF0
    PairHolder_005A9BF0();

    void* unknown_00;   // +0x00
    void* unknown_04;   // +0x04
};
GG_STATIC_ASSERT(offsetof(PairHolder_005A9BF0, unknown_04) == 0x04);

class Triple_007636F0
{
public:
    // FUNCTION: GAMEMD 0x7636F0
    Triple_007636F0();

    int unknown_00;   // +0x00
    int unknown_04;   // +0x04
    int unknown_08;   // +0x08
};
GG_STATIC_ASSERT(offsetof(Triple_007636F0, unknown_08) == 0x08);

class Triple_00769480
{
public:
    // FUNCTION: GAMEMD 0x769480
    Triple_00769480();

    int unknown_00;   // +0x00
    int unknown_04;   // +0x04
    int unknown_08;   // +0x08
};
GG_STATIC_ASSERT(offsetof(Triple_00769480, unknown_08) == 0x08);

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

struct Map_005A7250
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc)
    Cell_005A7250* GetCell(const CellStruct_005A7250& cell);
};

// GLOBAL: GAMEMD 0x87F7E8
extern Map_005A7250 DAT_0087F7E8;
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

#include "../map/tile_link_table_methods.h"

// GLOBAL: GAMEMD 0xABE370 — the 101-slot tile-link table (0xC per slot).
// GLOBAL: GAMEMD 0xABE834 — the 8-slot continuation of the same table.

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7ED620
extern const double DAT_007ED620;
// GLOBAL: GAMEMD 0xABE368
extern double DAT_00ABE368;
// GLOBAL: GAMEMD 0xABECE0
extern double DAT_00ABECE0;
// GLOBAL: GAMEMD 0xABECE8
extern int DAT_00ABECE8;
// GLOBAL: GAMEMD 0xABECEC
extern int DAT_00ABECEC;
// GLOBAL: GAMEMD 0xABECF0
extern int DAT_00ABECF0;
// GLOBAL: GAMEMD 0xABECF8
extern double DAT_00ABECF8;

// FUNCTION: GAMEMD 0x58B560
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_0058B560()
{
    DAT_00ABECF8 = DAT_00ABE368 / DAT_007ED620;
}

// FUNCTION: GAMEMD 0x58B580
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_0058B580()
{
    DAT_00ABECE0 = DAT_007E1718 / DAT_00ABECF8;
}

// FUNCTION: GAMEMD 0x58B700
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_0058B700()
{
    DAT_00ABECF0 = 0;
    DAT_00ABECE8 = 0x80;
    DAT_00ABECEC = 0x80;
}

// FUNCTION: GAMEMD 0x58B760
// Tail-calls a method on a global object.
void FUN_0058B760(int a1, int a2)
{
    FUN_005958E0(DAT_00ABDFD8, a2);
}

// FUNCTION: GAMEMD 0x58B770
// Calls other functions.
void __cdecl FUN_0058B770()
{
    DAT_00ABE890.FUN_0065C6D0(0);
}

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
int __fastcall FUN_0058B7D0()
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

// FUNCTION: GAMEMD 0x58BCD0
// Branching.
int FUN_0058BCD0(int a1)
{
    return a1 == 1 || a1 == 3 || a1 == 4;
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

// FUNCTION: GAMEMD 0x597D40
// Tail-forwards to another function.
void Obj_00597D40::FUN_00597D40()
{
    FUN_00558840();
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5A7250
// True when all four corners lie on the map and every cell of the rectangle
// passes: cells of the first kind need `allow_first`, of the second kind
// `allow_second`, anything else one of the three remaining predicates.
bool __fastcall FUN_005A7250(const Rect_005A7250* rect, bool allow_first, bool allow_second)
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Build a link from a cell offset and a facing.
// FUNCTION: GAMEMD 0x5A9920
TileLink::TileLink(const LinkCell& cell, int facing) throw()
    : Cell(cell), Facing(facing)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Default link: the cell offset zeroed by LinkCell's own constructor and no
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
TileLinkStep::TileLinkStep(int fromTile, const LinkCell& fromCell, int toTile,
                           const LinkCell& toCell, int index) throw()
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
    : FromTile(0xFFFF), FromCell(LinkCell()), ToTile(0xFFFF),
      ToCell(LinkCell()), Index(-1)
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5A9C20
// Calls other functions.
void FUN_005A9C20(Obj_005A9C20* a1, int a2)
{
    FUN_005A9C40(a1, a2);
    FUN_007C978A(0x5AC190);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5AC270
void* Obj_5AC270::FUN_5AC270(unsigned int flags)
{
    FUN_00558790(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

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
