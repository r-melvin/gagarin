// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | behaviour-confirmed-name
//   Original translation unit TU165 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x5f36f0-0x5f6ddf,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// ObjectClass bodies for primary-table (0x7EF060) slots in the block
// 0x5F4360..0x5F6DBA, in retail address order. Slot numbers come from the
// RTTI-located table; names are placeholders (object_class.h). Argument counts
// come from each body's RET n and return types from its EAX/AL use.
//
// Retail entry-origin byte evidence: AttachTrigger reads ObjectClass+0x34 and
// TagClass+0x2C, with RET 4 at 0x5F5B7E; SetHealthPercentage reads Health+0x6C,
// dispatches virtual slot +0x88, reads returned ObjectTypeClass+0xA0 and ends
// with RET 8 spanning 0x5F5CC5..0x5F5CC7; IsRedHP reads the same health/type fields and the
// RulesInstance pointer at 0x8871E0 / ConditionRed+0x1708, with RET at 0x5F5D19.
// At 0x5F5B4C are four NOPs; current Ghidra analysis records no function
// entry or xrefs there. Only the evidenced 0x5F5B50 entry is bound here.
// Method names remain hypotheses, confirmed only as far as the
// observed operations permit.
//
//   0x5F6B90 via the local Ghidra disassembly. Offsets and vtable slots
//   confirmed numerically (see the header).
//
// ObjectClass height/level leaves. Functions ordered ascending by retail
// address.
//
//   Entry-origin bytes at 0x5F5F30 load the dword at ObjectClass+0xA4 and
//   return. ObjectClass::Location is at +0x9C and CoordStruct::Z at +8.
//
//   Method roles are confirmed by the retail operations described below.
//
//   FUN_005F6220 is the complete 0x26-byte entry-origin body at the pinned
//   retail address. It calls each object's primary-vtable slot +0xB8 with that
//   object in ECX, saves the argument object's EAX result, then compares the
//   receiver result against it with signed SETG. The caller at 0x551ADB tests
//   AL directly, confirming a bool result. The declarations below model only
//   this dispatch slot; they do not assert the original virtual's name or its
//   declaring class.
//
// Retail 0x5F6BD0 calls the primary coordinate slot +0xAC twice, then sums
// Y from the first result and X from the second. The method name is a
// naming hypothesis. This uses the shared explicit-vptr layout;
// the slot-call view does not establish the original virtual declaring class.

#include "../_layout/object_class.h"
#include "../_layout/swizzle_manager_class.h"

// CellStruct — 2D short cell coordinate (sizeof = 4). Self-guarded for reuse.
#include "../_layout/cell.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

#include "../_layout/object_type_class.h"
#include "../_layout/tag_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/obj_004a1d30.h"
#include "flight_level.h"

// The map object at 0x87F7E8 (only the entry points used here).
class DisplayClass
{
public:
    // CALLEE: GAMEMD 0x4F42F0 (declaration) -- flag a redraw.
    void FlagToRedraw(int which);
    // CALLEE: GAMEMD 0x4AEB10 (declaration) -- the object under focus.
    ObjectClass* FUN_004AEB10();
    // CALLEE: GAMEMD 0x4AEB30 (declaration) -- set the object under focus.
    void FUN_004AEB30(ObjectClass* object);
};
class MapView_565730_5 : public DisplayClass
{
public:
    // CALLEE: GAMEMD 0x565730 (declaration) -- the cell under a coordinate.
    CellClass* FUN_00565730(const CoordStruct* coord);
    // CALLEE: GAMEMD 0x5657A0 (declaration) -- the cell at a cell position.
    CellClass* FUN_005657A0(const CellStruct* cell);
    // CALLEE: GAMEMD 0x578080 (declaration) -- the ground height at a coordinate.
    int FUN_00578080(const CoordStruct* coord);
};
// GLOBAL: GAMEMD 0x87F7E8
extern MapView_565730_5 DAT_0087F7E8;

// The rules object behind the global pointer 0x8871E0 (read-only here).
struct ObjectRulesView_5F4360
{
    char   unknown_0000[0x16F8];
    double unknown_16F8;             // +0x16F8  health ratio threshold for slot 101
};
GG_STATIC_ASSERT(offsetof(ObjectRulesView_5F4360, unknown_16F8) == 0x16F8);
// GLOBAL: GAMEMD 0x8871E0
extern ObjectRulesView_5F4360* DAT_008871E0;

// The audio controller's initialiser (0x405BE0, __thiscall, no arguments),
// rerun over each controller a load brings in.
struct AudioControllerInit
{
    // CALLEE: GAMEMD 0x405BE0 (declaration)
    void FUN_00405BE0();
};

// CALLEE: GAMEMD 0x410380 (decl; reloc) -- AbstractClass's Load body.

// One lepton offset per facing (0x89F6D8, eight X/Y pairs).
struct FacingOffset
{
    int X;
    int Y;
};

// GLOBAL: GAMEMD 0x89F6D8
extern FacingOffset DAT_0089F6D8[8];

// The selected-objects vector at 0xA8ECB8, seen through the slot it calls
// (slot 4 finds an item's index), its Items/Count fields and the inlined
// removal.
class SelectionVector
{
public:
    virtual ~SelectionVector();
    virtual bool vf_1(const SelectionVector& other) const;
    virtual bool vf_2(int capacity, ObjectClass** items);
    virtual void vf_3();
    virtual int vf_4(ObjectClass* const& item) const;

    // Remove `item`, closing the gap (inlined into its callers).
    bool Remove(ObjectClass* const& item)
    {
        int index = vf_4(item);
        if (index == -1 || index >= Count) {
            return false;
        }
        Count--;
        for (; index < Count; index++) {
            Items[index] = Items[index + 1];
        }
        return true;
    }

    ObjectClass** Items;             // +0x04
    int           Capacity;          // +0x08
    bool          IsInitialized;     // +0x0C
    bool          IsAllocated;       // +0x0D
    int           Count;             // +0x10
    int           CapacityIncrement; // +0x14
};
GG_STATIC_ASSERT(offsetof(SelectionVector, Count) == 0x10);
// GLOBAL: GAMEMD 0xA8ECB8
extern SelectionVector DAT_00A8ECB8;

// The TechnoClass-family object 0x40DD70 hands back (a checked downcast that
// keeps WhatAmI 1, 2, 6 and 15), seen through the two slots slot 73 calls.
// Slot 55 also asks this object's own slot 202 once it knows it is a techno.
// Declaration order follows match/_rt/gg_vslot.h.
struct TechnoVtbl_5F5850;
struct Techno_5F5850
{
    TechnoVtbl_5F5850* Vtbl;
};
typedef int (Techno_5F5850::*TechnoFn_5F5850)();
typedef bool (Techno_5F5850::*TechnoTest_5F5850)();
struct TechnoVtbl_5F5850
{
    char            unknown_000[0x38];
    TechnoFn_5F5850 At_038;          // slot 14
    char            unknown_03C[0x2C0 - 0x3C];
    TechnoFn_5F5850 At_2C0;          // slot 176
    char            unknown_2C4[0x328 - 0x2C4];
    TechnoTest_5F5850 At_328;        // slot 202
};
GG_STATIC_ASSERT(offsetof(TechnoVtbl_5F5850, At_2C0) == 0x2C0);

// CALLEE: GAMEMD 0x40DD70 (decl; reloc) -- the object if it is a techno, else null.
Techno_5F5850* FUN_0040DD70(ObjectClass* object);

// A building's type pointer and the type's flag at +0xE58 (read-only here).
struct BuildingType_5F5850
{
    char unknown_000[0xE58];
    int  unknown_E58;
};
struct Building_5F5850 : ObjectClass
{
    char                 unknown_0AC[0x520 - 0xAC];
    BuildingType_5F5850* Type;       // +0x520
};
GG_STATIC_ASSERT(offsetof(Building_5F5850, Type) == 0x520);

// The line trailer slot 55 detaches (0x556B30, __thiscall, no arguments).
struct LineTrail_5F5280
{
    // CALLEE: GAMEMD 0x556B30 (declaration)
    void FUN_00556B30();
};

// The owning house, as slot 15 returns it.
struct House_5F5280
{
    // CALLEE: GAMEMD 0x50B6F0 (declaration)
    bool IsControlledByCurrentPlayer() const;
};

// GLOBAL: GAMEMD 0xA83D4C -- the player's house (a pointer, passed to slot 50).
extern HouseClass* DAT_00A83D4C;
// GLOBAL: GAMEMD 0xA8B238 -- the session game mode (0 is a campaign).
extern int DAT_00A8B238;
// GLOBAL: GAMEMD 0xAC13BC -- the height a bridge adds.
extern int DAT_00AC13BC;

// A lepton coordinate's cell: each axis divided by 256.
static inline CellStruct CoordCell(const CoordStruct& coord)
{
    CellStruct cell;
    cell.X = (short)(coord.X / 256);
    cell.Y = (short)(coord.Y / 256);
    return cell;
}

// A cell-sized pair with a user-declared destructor; slot 66's fallback is a
// function-local static of it, so retail registers its (empty) destructor with
// atexit (0x5F5C10).
struct CellPair_5F5B90
{
    short X;
    short Y;

    ~CellPair_5F5B90() {}
};

static inline CellPair_5F5B90 CellPairOf(short x, short y)
{
    CellPair_5F5B90 pair;
    pair.X = x;
    pair.Y = y;
    return pair;
}

// CALLEE: GAMEMD 0x7C5F00 -- __ftol, used by SetHealthPercentage.
#include "../_layout/object_class.h"
#include "rules_class.h"
#include "../_layout/object_type_class.h"

struct ObjectTagRefCountView
{
    char unknown_00[0x2C];
    int InstanceCount;
};
GG_STATIC_ASSERT(offsetof(ObjectTagRefCountView, InstanceCount) == 0x2C);
GG_STATIC_ASSERT(sizeof(ObjectTagRefCountView) == 0x30);

typedef ObjectTypeClass* (* ObjectHealthGetType)(const ObjectClass*);
struct ObjectHealthVtablePrefix
{
    char unknown_00[0x88];
    ObjectHealthGetType GetType;
};
GG_STATIC_ASSERT(offsetof(ObjectClass, AttachedTag) == 0x34);
GG_STATIC_ASSERT(offsetof(ObjectClass, Health) == 0x6C);
GG_STATIC_ASSERT(offsetof(ObjectHealthVtablePrefix, GetType) == 0x88);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Strength) == 0xA0);
GG_STATIC_ASSERT(offsetof(RulesClass, ConditionRed) == 0x1708);
GG_STATIC_ASSERT(sizeof(ObjectHealthGetType) == 4);

#include "object_class_level_methods.h"

#include "trivial_tu165_methods.h"

#include "abstract_class_distance3d_methods.h"

#include "abstract_class_distance_methods.h"

#include "abstract_class_target_direction_methods.h"

#include <stddef.h>
#include "../_layout/object_class.h"

GG_STATIC_ASSERT(offsetof(ObjectClass, Location) == 0x9C);
GG_STATIC_ASSERT(offsetof(CoordStruct, Z) == 0x08);
typedef int (IPersistStream::*ObjectCellGetter)() const;
GG_STATIC_ASSERT(sizeof(ObjectCellGetter) == 4);

#include "object_class_crushable_methods.h"

// /O1 changes register staging (four bytes); /O2 matches. Both /GX modes
// match under /O2, so this function does not identify the exception flag.
#include "../_layout/object_class.h"

// Minimal primary-vtable call view: the observed target is entry 46 (+0xB8),
// with no stack arguments and an int in EAX. This abstract view is never
// instantiated; it only lets ordinary C++ express the retail indirect call.
// Typed member-pointer and ECX-only fastcall prefix calls each differed in
// four register-staging bytes. This call view retains the exact instruction
// order; no complete hierarchy or concrete vtable is claimed.
struct ObjectClassSortCallView
{
#define GG_OBJECT_SORT_SLOT(n) virtual void unknown_##n() = 0;
    GG_OBJECT_SORT_SLOT(00) GG_OBJECT_SORT_SLOT(01)
    GG_OBJECT_SORT_SLOT(02) GG_OBJECT_SORT_SLOT(03)
    GG_OBJECT_SORT_SLOT(04) GG_OBJECT_SORT_SLOT(05)
    GG_OBJECT_SORT_SLOT(06) GG_OBJECT_SORT_SLOT(07)
    GG_OBJECT_SORT_SLOT(08) GG_OBJECT_SORT_SLOT(09)
    GG_OBJECT_SORT_SLOT(10) GG_OBJECT_SORT_SLOT(11)
    GG_OBJECT_SORT_SLOT(12) GG_OBJECT_SORT_SLOT(13)
    GG_OBJECT_SORT_SLOT(14) GG_OBJECT_SORT_SLOT(15)
    GG_OBJECT_SORT_SLOT(16) GG_OBJECT_SORT_SLOT(17)
    GG_OBJECT_SORT_SLOT(18) GG_OBJECT_SORT_SLOT(19)
    GG_OBJECT_SORT_SLOT(20) GG_OBJECT_SORT_SLOT(21)
    GG_OBJECT_SORT_SLOT(22) GG_OBJECT_SORT_SLOT(23)
    GG_OBJECT_SORT_SLOT(24) GG_OBJECT_SORT_SLOT(25)
    GG_OBJECT_SORT_SLOT(26) GG_OBJECT_SORT_SLOT(27)
    GG_OBJECT_SORT_SLOT(28) GG_OBJECT_SORT_SLOT(29)
    GG_OBJECT_SORT_SLOT(30) GG_OBJECT_SORT_SLOT(31)
    GG_OBJECT_SORT_SLOT(32) GG_OBJECT_SORT_SLOT(33)
    GG_OBJECT_SORT_SLOT(34) GG_OBJECT_SORT_SLOT(35)
    GG_OBJECT_SORT_SLOT(36) GG_OBJECT_SORT_SLOT(37)
    GG_OBJECT_SORT_SLOT(38) GG_OBJECT_SORT_SLOT(39)
    GG_OBJECT_SORT_SLOT(40) GG_OBJECT_SORT_SLOT(41)
    GG_OBJECT_SORT_SLOT(42) GG_OBJECT_SORT_SLOT(43)
    GG_OBJECT_SORT_SLOT(44) GG_OBJECT_SORT_SLOT(45)
#undef GG_OBJECT_SORT_SLOT
    virtual int unknown_B8() = 0; // slot 46 => 46 * 4 == 0xB8
};

// Typed vtable-prefix evidence, independent of the call-view declaration.
// The original virtual name and declaring class remain unknown.
struct ObjectClassPrimaryVtablePrefix
{
    void* unknown_00[46];
    int (IPersistStream::*unknown_B8)();
};
typedef int (IPersistStream::*ObjectClassSortKeyMember)();
GG_STATIC_ASSERT(offsetof(ObjectClassPrimaryVtablePrefix, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(ObjectClassPrimaryVtablePrefix, unknown_B8) == 0xB8);
GG_STATIC_ASSERT(sizeof(ObjectClassPrimaryVtablePrefix) == 0xBC);
GG_STATIC_ASSERT(sizeof(ObjectClassSortKeyMember) == 4);
GG_STATIC_ASSERT(sizeof(void*) == 4);

#include "object_class_uninit_methods.h"

#include "../_layout/object_class.h"

typedef CoordStruct* (IPersistStream::*ObjectYSortGetCoords)(CoordStruct*) const;
struct ObjectYSortVtablePrefix
{
    char unknown_00[0xAC];
    ObjectYSortGetCoords GetTargetCoords;
};
GG_STATIC_ASSERT(offsetof(ObjectYSortVtablePrefix, GetTargetCoords) == 0xAC);
GG_STATIC_ASSERT(sizeof(ObjectYSortGetCoords) == 4);
GG_STATIC_ASSERT(offsetof(CoordStruct, X) == 0);
GG_STATIC_ASSERT(offsetof(CoordStruct, Y) == 4);
GG_STATIC_ASSERT(sizeof(CoordStruct) == 12);

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F3B50
ObjectClass::ObjectClass(const AbstractNoInit& noInit)
    : AbstractClass(noInit)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F3D90
// Branching.
void Obj_005F3D90::FUN_005F3D90()
{
    if (unknown_A8 != 0)
    {
        unknown_A8->FUN_00556B30();
        unknown_A8 = 0;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F3DB0
//
// The facing from this object to another, as a binary angle. Both positions
// come through the GetCoords slot into stack buffers; the differences are
// taken on the FPU (`FILD`/`FISUB`) with the Y difference running self-to-
// target and the X difference target-to-self, then the same pi/2 shift and
// scale as 0x4265B0. The result is copied out as a dword through the buffer
// argument, which is also returned.
//
// The X halves go through int locals and the Y halves do not: retail loads
// both X values into registers and spills them (`MOV ECX,[EDI]; MOV EDX,[EAX];
// MOV [ESP+0x2C],ECX; MOV [ESP+8],EDX`) before the `FILD`/`FISUB`, while the Y
// pair is read straight off the pointers. Reading X straight off the pointers
// too drops the four moves and shrinks the frame to 0x18 (30.0%); declaring
// the locals target-first swaps ECX/EDX (90.0%); self-first is exact. The
// target's X lands in the dead `target` parameter slot.
Dir_005F3DB0* Obj_005F3DB0::FUN_005F3DB0(Dir_005F3DB0* result,
                                         Obj_005F3DB0* target)
{
    Coord_005F3DB0 targetBuf;
    Coord_005F3DB0 selfBuf;

    Coord_005F3DB0* t = (target->*target->Vtbl->At_48)(&targetBuf);
    Coord_005F3DB0* s = (this->*this->Vtbl->At_48)(&selfBuf);

    int sx = s->X;
    int tx = t->X;

    double radians = FUN_004CAE30((double)s->Y - t->Y,
                                  (double)tx - sx);

    Dir_005F3DB0 dir;

    dir.Value = (short)((radians - 1.5707963267948966) * -10430.060040584269);

    *result = dir;

    return result;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F4360
bool ObjectClass::vf_80(int a1, int a2, int a3, int a4)
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F4370
void ObjectClass::vf_82(int a1)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F4380
bool ObjectClass::vf_89(const CoordStruct& coord, int a2)
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F4390
int ObjectClass::vf_90(int a1)
{
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F43A0
void ObjectClass::vf_93(int a1, int a2, int a3)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F43B0
bool ObjectClass::vf_94()
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F43C0
void ObjectClass::vf_95()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F43D0
int ObjectClass::vf_96()
{
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F43E0
int ObjectClass::vf_97()
{
    return -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F43F0
void ObjectClass::vf_103(int a1)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F4400
void ObjectClass::vf_104(int a1)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F4410
// PARTIAL 35.8%: retail pushes slot 107's constant arguments first and builds
// the stepped coordinate between those pushes, through EDI/EBX/EBP, keeping
// facing in EBP; cl builds it before any push. Tried the body below (35.8%),
// an inline coordinate-stepping helper returning by value (3.8%), the step
// assigned inside the call argument (3.8%) and a copy-then-add helper (18.5%).
// Step Location one cell toward `facing`: off the map, ask slot 107 about the
// cell there and, if it says nothing (0), move through slot 109, then back on.
void ObjectClass::vf_106(int facing)
{
    vf_73(0);
    CoordStruct coord = Location;
    coord.X += DAT_0089F6D8[facing & 7].X;
    coord.Y += DAT_0089F6D8[facing & 7].Y;
    if (vf_107(DAT_0087F7E8.FUN_00565730(&coord), facing, -1, 0, 1) == 0) {
        vf_109(coord);
    }
    vf_73(1);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F44A0
// Deselect: drop this object from the selected-objects vector, clear
// IsSelected and release the map's focus if it is on this object.
void ObjectClass::vf_84()
{
    if (IsSelected) {
        DAT_00A8ECB8.Remove(this);
        IsSelected = false;
        if (DAT_0087F7E8.FUN_004AEB10() == this) {
            DAT_0087F7E8.FUN_004AEB30(0);
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F4D10
// Flag this object and the map for a redraw, once.
void ObjectClass::vf_77()
{
    if (!NeedsRedraw) {
        NeedsRedraw = 1;
        DAT_0087F7E8.FlagToRedraw(0);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F5230
// Forget `target` wherever this object holds it: the attached tag (dropping
// its instance count), the next object in the chain when `removed`, and the
// parachute.
void ObjectClass::vf_10(void* target, bool removed)
{
    if (AttachedTag == target && AttachedTag != 0) {
        ((TagClass*)AttachedTag)->InstanceCount--;
        AttachedTag = 0;
    }
    if (removed && target == NextObject && target != 0) {
        NextObject = ((ObjectClass*)NextObject)->NextObject;
    }
    if (target == Parachute) {
        Parachute = 0;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F5280
// PARTIAL 1.8% positional (82.1% aligned): retail keeps a one-byte stack copy
// of the techno bit (`PUSH ECX` frame, `AND CL,1; MOV [ESP+0xF],CL`) that cl
// tests in place (`TEST byte ptr [ESI+0x14],1`), shifting every offset. Tried
// the plain test below, the bit assigned to a bool local inside the condition
// and an inline techno-cast helper (0.0%).
// Detach the line trailer; deselect unless this object is neither `removed`
// nor (owned by the player's side or a techno whose slot 202 holds); drop the
// map's focus if it is on this object; announce the expiring pointer.
void ObjectClass::vf_55(bool removed)
{
    if (LineTrailer != 0) {
        ((LineTrail_5F5280*)LineTrailer)->FUN_00556B30();
        LineTrailer = 0;
    }
    House_5F5280* house = (House_5F5280*)vf_15();
    bool keep = false;
    if (!removed) {
        if (this != 0 && Flags.IsTechno) {
            Techno_5F5850* techno = (Techno_5F5850*)this;
            if ((techno->*techno->Vtbl->At_328)()) {
                keep = true;
            }
        }
    }
    if (removed || !((house != 0 && house->IsControlledByCurrentPlayer()) || keep)) {
        vf_84();
    }
    if (DAT_0087F7E8.FUN_004AEB10() == this) {
        DAT_0087F7E8.FUN_004AEB30(0);
    }
    AnnounceExpiredPointer(removed);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F5320
// Event 13 runs slot 73 with 2 and reports 1; event 34 reports 1 below the
// rules health ratio and 10 at or above it; anything else reports 0.
int ObjectClass::vf_101(int a1, int event, int a3)
{
    switch (event) {
    case 13:
        vf_73(2);
        break;
    case 34:
        if ((double)Health / vf_34()->Strength >= DAT_008871E0->unknown_16F8) {
            return 10;
        }
        break;
    default:
        return 0;
    }
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F5850
// The map-presence step: mode 2 redraws an object already on the map; modes 1
// and 3 put it on the map, mode 0 takes it off. Every mode but 2 first nudges
// a techno (slots 176 and 14, then this object's cell), except a mode-0 call
// for a building whose type sets +0xE58. Returns whether anything changed.
bool ObjectClass::vf_73(int mode)
{
    if (InLimbo) {
        return false;
    }
    if (mode == 2) {
        if (NeedsRedraw || !IsOnMap) {
            return false;
        }
        vf_77();
        return true;
    }
    if (vf_11() != 6 || ((Building_5F5850*)this)->Type->unknown_E58 == 0 || mode != 0) {
        Techno_5F5850* techno = FUN_0040DD70(this);
        if (techno != 0) {
            (techno->*techno->Vtbl->At_2C0)();
            (techno->*techno->Vtbl->At_038)();
            vf_110();
        }
    }
    if ((mode == 1 || mode == 3) && !IsOnMap) {
        IsOnMap = true;
        vf_77();
        return true;
    }
    if (mode == 0 && IsOnMap) {
        IsOnMap = false;
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F5B50
bool ObjectClass::AttachTrigger(TagClass* tag)
{
    if (this->AttachedTag) {
        --((ObjectTagRefCountView*)this->AttachedTag)->InstanceCount;
        this->AttachedTag = 0;
    }
    if (tag) {
        this->AttachedTag = tag;
        ++((ObjectTagRefCountView*)tag)->InstanceCount;
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F5B90
// The type's slot 36 answer for `a1`, or (7FFF, 7FFF) without a type.
void* ObjectClass::vf_66(int a1)
{
    static CellPair_5F5B90 none = CellPairOf(0x7FFF, 0x7FFF);
    if (vf_34() == 0) {
        return &none;
    }
    return vf_34()->vf_36(a1);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F5C10
// Empty function.
void __cdecl FUN_005F5C10()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F5C20
void ObjectClass::vf_100(bool a1, bool a2)
{
    vf_34()->vf_37(a1, a2, false, (void*)vf_15());
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F5C80
void ObjectClass::SetHealthPercentage(double percentage)
{
    if (percentage > 0.0) {
        this->Health = (int)(
            (static_cast<const ObjectHealthVtablePrefix*>(
                 this->PrimaryVTable())->GetType(this)->Strength)
            * percentage);
        if (this->Health == 0)
            this->Health = 1;
    } else {
        this->Health = 0;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F5CD0
bool ObjectClass::IsRedHP() const
{
    return (double)this->Health
                 / (double)(static_cast<const ObjectHealthVtablePrefix*>(
                               this->PrimaryVTable())->GetType(this)->Strength)
               <= RulesInstance->ConditionRed
           && this->Health > 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F5E80
// The base load, then the pointer fields queued for fix-up, the two audio
// controllers reinitialised and the line trailer dropped.
HRESULT __stdcall ObjectClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (FAILED(hr)) {
        return hr;
    }
    DAT_00B0C110.SwizzleManagerClass::vf_4(&NextObject);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&AttachedTag);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&AttachedBomb);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_18);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Parachute);
    ((AudioControllerInit*)&AmbientSoundController)->FUN_00405BE0();
    ((AudioControllerInit*)&CustomSoundController)->FUN_00405BE0();
    LineTrailer = 0;
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F5F00  ObjectClass::GetCellLevel (__thiscall)
// The cell's own terrain level, raised by a bridge deck when the object is on
// one. Retail materialises the bridge bonus with the VC6 borrow idiom
// (`NEG CL; SBB ECX,ECX; AND ECX,4`), which is what `OnBridge ? 4 : 0` emits.
int ObjectClass::GetCellLevel() const
{
    CellClass* cell = static_cast<const ObjectLevelVtablePrefix*>(
        PrimaryVTable())->GetCell(this);
    return cell->Level + (OnBridge ? 4 : 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F5F30
int ObjectClass::FUN_005F5F30() const
{
    return Location.Z;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F5F40
// Height above the ground under Location, less the bridge height on a bridge.
int ObjectClass::vf_114()
{
    CoordStruct coord = Location;
    int height = Location.Z - DAT_0087F7E8.FUN_00578080(&coord);
    if (OnBridge) {
        height -= DAT_00AC13BC;
    }
    return height;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F5FA0
// Put Location at `height` above the ground (plus the bridge height on a
// bridge), taking the object off and back onto the map around the move.
void ObjectClass::vf_115(int height)
{
    if (OnBridge) {
        height += DAT_00AC13BC;
    }
    if (IsOnMap) {
        vf_73(0);
        CoordStruct coord = Location;
        Location.Z = DAT_0087F7E8.FUN_00578080(&coord) + height;
        vf_73(1);
    } else {
        CoordStruct coord = Location;
        Location.Z = DAT_0087F7E8.FUN_00578080(&coord) + height;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F6060
// Set Location.Z, taking the object off the map (slot 73 with 0) and back on (with 1) around the
// change while it is on the map.
void ObjectClass::FUN_005F6060(int z)
{
    if (IsOnMap) {
        vf_73(0);
        Location.Z = z;
        vf_73(1);
    } else {
        Location.Z = z;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F60A0
// Set bit 6 of the cell's occupation word: the bridge word when the
// coordinate is at bridge height over a bridge cell, else the ground word.
void ObjectClass::vf_60(CoordStruct* coord)
{
    if (DAT_0087F7E8.FUN_00578080(coord) + DAT_00AC13BC <= coord->Z
        && (DAT_0087F7E8.FUN_00565730(coord)->Flags & 0x100)) {
        DAT_0087F7E8.FUN_00565730(coord)->AltOccupationFlags |= 0x40;
    } else {
        DAT_0087F7E8.FUN_00565730(coord)->OccupationFlags |= 0x40;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F6120
// Clear the bit slot 60 sets.
void ObjectClass::vf_61(CoordStruct* coord)
{
    if (DAT_0087F7E8.FUN_00578080(coord) + DAT_00AC13BC <= coord->Z
        && (DAT_0087F7E8.FUN_00565730(coord)->Flags & 0x100)) {
        DAT_0087F7E8.FUN_00565730(coord)->AltOccupationFlags &= ~0x40;
    } else {
        DAT_0087F7E8.FUN_00565730(coord)->OccupationFlags &= ~0x40;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F61F0
// Sibling of FUN_005F6220 with the comparison reversed.
bool ObjectClass::FUN_005F61F0(ObjectClass* other)
{
    ObjectClassSortCallView* otherView = (ObjectClassSortCallView*)other;
    int otherValue = otherView->unknown_B8();
    ObjectClassSortCallView* thisView = (ObjectClassSortCallView*)this;
    int thisValue = thisView->unknown_B8();
    return thisValue < otherValue;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F6220
bool ObjectClass::FUN_005F6220(ObjectClass* other)
{
    ObjectClassSortCallView* otherView = (ObjectClassSortCallView*)other;
    int otherValue = otherView->unknown_B8();
    ObjectClassSortCallView* thisView = (ObjectClassSortCallView*)this;
    int thisValue = thisView->unknown_B8();
    if (thisValue > otherValue)
        return true;
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F6250
// Feed the base fields, the IDs of the next object and the attached tag,
// Health, IsOnMap, (in campaign or mode 5) NeedsRedraw and IsSelected, the
// state bytes and Location to the checksum sink.
void ObjectClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
    if (NextObject != 0) {
        crc->FUN_004A1D50(((ObjectClass*)NextObject)->vf_rtti_4());
    }
    if (AttachedTag != 0) {
        crc->FUN_004A1D50(((TagClass*)AttachedTag)->vf_rtti_4());
    }
    crc->FUN_004A1D50(Health);
    crc->FUN_004A1CA0(IsOnMap);
    if (DAT_00A8B238 == 0 || DAT_00A8B238 == 5) {
        crc->FUN_004A1CA0(NeedsRedraw);
        crc->FUN_004A1CA0(IsSelected);
    }
    crc->FUN_004A1CA0(InLimbo);
    crc->FUN_004A1CA0(HasParachute);
    crc->FUN_004A1CA0(OnBridge);
    crc->FUN_004A1CA0(IsFallingDown);
    crc->FUN_004A1CA0(IsABomb);
    crc->FUN_004A1CA0(IsAlive);
    crc->FUN_004A1D50(Location.X);
    crc->FUN_004A1D50(Location.Y);
    crc->FUN_004A1D50(Location.Z);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F6360
//
// Full three-axis lepton distance between this object and another. As in the
// planar twin, a building is measured to its footprint: the foundation's
// height plus width, in cells, comes off and the result is clamped at zero.
//
// PARTIAL (92.9%, 78/84; mnemonic multiset identical). Retail forms the Y
// difference before the Z difference (`SUB EDX,ECX; SUB EAX,EBX` and the two
// spill stores in that order); VC6 schedules Z first. Source order of the
// three differences, the 2D twin's copy-then-decrement form, named locals for
// the other object's coordinates and all six orderings of the sum of squares
// leave it unchanged — a scheduling tie-break, not a phrasing.
//
// FLOAT-CONSISTENCY FLAG (/Op): measured this pass and REFUTED for this
// function. /Op rounds every double-typed intermediate through memory, which
// is the shape retail sometimes shows, but adding it to this TU's flag line
// makes the score collapse rather than close: the five float-heavy partials
// were swept together under `/nologo /c /O2 /DNDEBUG /Gy /GX /Op` (the flags
// then in force, before /Gr and the removal of /GX) and scored
// GetYRotation 58.3%->8.0%, MatrixApply 72.1%->72.1%, FromAxis 85.9%->3.3%,
// FromQuaternion 19.8%->1.1% and DistanceFrom3D 92.9%->67.9%. Retail's x87
// code in this family is *not* /Op code; do not re-test the flag here.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply here.
// Retail's callee-saved pushes sit exactly where ours do (prologue EBX, EDI
// plus one sunk push on both sides), the
// number of epilogues agrees, and the compiled block order already matches,
// so there are no merged return blocks to split. The residual is register
// naming downstream of that, not a prologue hoist.
int Obj_005F6360::DistanceFrom3D(Obj_005F6360* that)
{
    if (that == 0) {
        return 0;
    }

    Coord_005F6360 thatBuf;
    Coord_005F6360* thatCoords = (that->*that->Vtbl->GetCoords)(&thatBuf);

    Coord_005F6360 thisBuf;
    Coord_005F6360* thisCoords = (this->*this->Vtbl->GetCoords)(&thisBuf);

    Coord_005F6360 d;
    d.X = thisCoords->X - thatCoords->X;
    d.Y = thisCoords->Y - thatCoords->Y;
    d.Z = thisCoords->Z - thatCoords->Z;

    int distance = (int)FUN_004CAC40((double)d.X * d.X + (double)d.Z * d.Z + (double)d.Y * d.Y);

    Obj_005F6360* building = ((that->*that->Vtbl->WhatAmI)() == 6) ? that : 0;
    if (building != 0) {
        distance += (building->Type->GetFoundationHeight(0)
                     + building->Type->GetFoundationWidth()) * -64;
        if (distance < 0) {
            distance = 0;
        }
    }

    return distance;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F6440
//
// Planar (X/Y) lepton distance between this object and another. When the other
// object is a building the distance is measured to its footprint rather than
// its centre: the foundation's height plus width, in cells, is taken off and
// the result clamped at zero.
//
// Two phrasings are load-bearing. The difference is an 8-byte aggregate that is
// first *copied* from this object's coordinate and then decremented member by
// member (`d.X = c->X; d.Y = c->Y; d.X -= tx; d.Y -= ty;`): written as two
// subtractions (`d.X = c->X - tx;`) VC6 reads Y before X into EDX and copies the
// __ftol result into EBX eagerly, where retail reads X into ECX, Y into the dying
// pointer register EAX, and only parks EAX in EBX after loading the WhatAmI
// vtable. The foundation sum stays inside the multiply; naming the two calls
// moves the accumulator from EDI to EAX.
int Obj_005F6440::DistanceFrom(Obj_005F6440* that)
{
    if (that == 0) {
        return 0;
    }

    Coord_005F6440 thatBuf;
    Coord_005F6440* thatCoords = (that->*that->Vtbl->GetCoords)(&thatBuf);
    int thatX = thatCoords->X;
    int thatY = thatCoords->Y;

    Coord_005F6440 thisBuf;
    Coord_005F6440* thisCoords = (this->*this->Vtbl->GetCoords)(&thisBuf);

    Point_005F6440 d;
    d.X = thisCoords->X;
    d.Y = thisCoords->Y;
    d.X -= thatX;
    d.Y -= thatY;

    int distance = (int)FUN_004CAC40((double)d.Y * d.Y + (double)d.X * d.X);

    // A building, or null: retail folds the type test into the pointer
    // (`SUB ESI,6; NEG; SBB; NOT; AND ESI,EDI`) rather than branching.
    Obj_005F6440* building = ((that->*that->Vtbl->WhatAmI)() == 6) ? that : 0;
    if (building != 0) {
        distance += (building->Type->GetFoundationHeight(0)
                     + building->Type->GetFoundationWidth()) * -64;
        if (distance < 0) {
            distance = 0;
        }
    }

    return distance;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F65A0
CoordStruct ObjectClass::vf_18()
{
    return Location;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F65D0
void ObjectClass::vf_70(Point2D* point, RectangleStruct* clip)
{
    vf_69(point, clip);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F65F0
//
// Retire the object. Disarm an attached bomb; if this is a TechnoClass
// (AbstractFlags bit 0) kill its passengers with no killer; announce the
// pointer as expired so everything referencing it lets go; limbo it through
// slot 53; mark it dead; and queue it on the pending-delete vector, whose
// AddItem (with its virtual SetCapacity growth path) is inlined into the tail.
void ObjectClass::vf_62()
{
    if (this->AttachedBomb != 0)
        ((UnInitBomb*)this->AttachedBomb)->Disarm();

    if (this != 0 && this->Flags.IsTechno)
        ((TechnoClass*)this)->KillPassengers(0);

    this->AnnounceExpiredPointer(1);
    this->vf_53();
    this->IsAlive = 0;

    reinterpret_cast<UnInitVector*>(&DAT_00B0F698)->AddItem(this);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F6690
bool ObjectClass::vf_17()
{
    return !IsAlive;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F6940
void ObjectClass::vf_109(const CoordStruct& coord)
{
    Location = coord;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F6960
// The cell under Location (looked up twice; the first result is unused).
CellClass* ObjectClass::vf_111()
{
    CoordStruct coord = Location;
    DAT_0087F7E8.FUN_00565730(&coord);
    coord = Location;
    return DAT_0087F7E8.FUN_00565730(&coord);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F69C0
// The cell under slot 19's coordinate.
CellStruct ObjectClass::vf_112()
{
    return CoordCell(vf_19(0));
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F6A10
CellClass* ObjectClass::vf_113()
{
    CellStruct cell = CoordCell(vf_19(0));
    return DAT_0087F7E8.FUN_005657A0(&cell);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F6A70
// Whether the object at slot 19's coordinate for `a1` counts as on a bridge:
// true when off a bridge but more than three flight levels below Location over
// a bridge cell, false when on a bridge but more than three flight levels
// above it, otherwise the current OnBridge.
bool ObjectClass::vf_47(AbstractClass* a1)
{
    bool onBridge = OnBridge;
    CoordStruct coord = vf_19(a1);
    int targetZ = DAT_0087F7E8.FUN_00578080(&coord);
    int hereZ;
    {
        CoordStruct here = Location;
        hereZ = DAT_0087F7E8.FUN_00578080(&here);
    }
    if (!OnBridge && hereZ - targetZ > FlightLevel * 3
        && (DAT_0087F7E8.FUN_00565730(&coord)->Flags & 0x100)) {
        return true;
    }
    if (OnBridge && targetZ - hereZ > FlightLevel * 3) {
        return false;
    }
    return onBridge;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F6B50
void ObjectClass::vf_105(int a1, int a2)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F6B60  ObjectClass::IsOnFloor (__thiscall)
// An off-map object is neither on the floor nor in the air.
bool ObjectClass::IsOnFloor() const
{
    if (IsOnMap) {
        if (static_cast<const ObjectLevelVtablePrefix*>(
                PrimaryVTable())->GetHeight(this) < FlightLevel * 2)
            return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F6B90  ObjectClass::IsInAir (__thiscall)
// The exact complement of IsOnFloor above the same boundary — retail differs
// from it by a single flipped condition code (JGE vs JL).
bool ObjectClass::IsInAir() const
{
    if (IsOnMap) {
        if (static_cast<const ObjectLevelVtablePrefix*>(
                PrimaryVTable())->GetHeight(this) >= FlightLevel * 2)
            return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F6BC0
TechnoTypeClass* ObjectClass::vf_33()
{
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F6BD0
int ObjectClass::GetYSort() const
{
    CoordStruct coord1;
    CoordStruct coord2;
    return (this->*static_cast<const ObjectYSortVtablePrefix*>(
                PrimaryVTable())->GetTargetCoords)(&coord1)->Y
        + (this->*static_cast<const ObjectYSortVtablePrefix*>(
                PrimaryVTable())->GetTargetCoords)(&coord2)->X;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F6C10
// More than 20 leptons below the ground counts as false.
bool ObjectClass::vf_31()
{
    return vf_114() > -20;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F6C30
bool ObjectClass::vf_78()
{
    if (vf_50(DAT_00A83D4C) && vf_52(1) == 0) {
        return false;
    }
    return vf_34()->Selectable;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F6C70
bool ObjectClass::vf_79()
{
    return vf_78();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F6C80
CoordStruct ObjectClass::vf_42(AbstractClass* a1)
{
    return vf_18();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F6CB0
// Branching.
void FUN_005F6CB0(Obj_005F6CB0* a1, int a2, int a3)
{
    a1->unknown_64 = a3;
    if (a3 == -1)
    {
        FUN_00405FD0(&a1->unknown_50, a2);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F6CD0  ObjectClass::IsCrushable (__thiscall, ret 0x4)
//
// May `crusher` run this object over? Two routes say yes. An omni-crusher
// flattens any techno (other than a building) whose type is not
// omni-crush-resistant. Otherwise the object's type must be crushable and the
// object itself not flagged uncrushable. Both routes also require the crusher's
// house not to be allied with the object and the +0x160 predicate to be false.
bool ObjectClass::IsCrushable(ObjectClass* crusher)
{
    if (crusher != 0
        && (crusher->*static_cast<const Vtbl_005F6CD0*>(
                crusher->PrimaryVTable())->GetTechnoType)()->OmniCrusher
        && IsTechno_005F6CD0(this)
        && !(this->*static_cast<const Vtbl_005F6CD0*>(
                PrimaryVTable())->GetTechnoType)()->OmniCrushResistant
        && (this->*static_cast<const Vtbl_005F6CD0*>(
                PrimaryVTable())->WhatAmI)() != 6
        && !CrushTechno(crusher)->Owner->IsAlliedWith(this)
        && !(this->*static_cast<const Vtbl_005F6CD0*>(
                PrimaryVTable())->At_160)()) {
        return true;
    }

    if ((this->*static_cast<const Vtbl_005F6CD0*>(
                PrimaryVTable())->GetType)()->Crushable
        && IsTechno_005F6CD0(this)
        && !CrushTechno(this)->Uncrushable
        && !CrushTechno(crusher)->Owner->IsAlliedWith(this)
        && !(this->*static_cast<const Vtbl_005F6CD0*>(
                PrimaryVTable())->At_160)()) {
        return true;
    }

    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5F6DA0
// Forget `target` if it is the parachute.
void ObjectClass::vf_24(void* target)
{
    if (target == Parachute) {
        Parachute = 0;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x5F6DC0 -- compiler-generated scalar deleting destructor.
