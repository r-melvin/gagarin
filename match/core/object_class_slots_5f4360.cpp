// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
// ObjectClass bodies for primary-table (0x7EF060) slots in the block
// 0x5F4360..0x5F6DBA, in retail address order. Slot numbers come from the
// RTTI-located table; names are placeholders (object_class.h). Argument counts
// come from each body's RET n and return types from its EAX/AL use.
#include "../_layout/object_class.h"

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
    // FUNCTION: GAMEMD 0x4F42F0 (declaration) -- flag a redraw.
    void FlagToRedraw(int which);
    // FUNCTION: GAMEMD 0x4AEB10 (declaration) -- the object under focus.
    ObjectClass* FUN_004AEB10();
    // FUNCTION: GAMEMD 0x4AEB30 (declaration) -- set the object under focus.
    void FUN_004AEB30(ObjectClass* object);
};
class MapClass : public DisplayClass
{
public:
    // FUNCTION: GAMEMD 0x565730 (declaration) -- the cell under a coordinate.
    CellClass* FUN_00565730(const CoordStruct* coord);
    // FUNCTION: GAMEMD 0x5657A0 (declaration) -- the cell at a cell position.
    CellClass* FUN_005657A0(const CellStruct* cell);
    // FUNCTION: GAMEMD 0x578080 (declaration) -- the ground height at a coordinate.
    int FUN_00578080(const CoordStruct* coord);
};
// GLOBAL: GAMEMD 0x87F7E8
extern MapClass DAT_0087F7E8;

// The rules object behind the global pointer 0x8871E0 (read-only here).
struct ObjectRulesView_5F4360
{
    char   unknown_0000[0x16F8];
    double unknown_16F8;             // +0x16F8  health ratio threshold for slot 101
};
GG_STATIC_ASSERT(offsetof(ObjectRulesView_5F4360, unknown_16F8) == 0x16F8);
// GLOBAL: GAMEMD 0x8871E0
extern ObjectRulesView_5F4360* DAT_008871E0;

// The pointer fix-up manager at 0xB0C110 (the manager is the first stacked
// argument).
struct Swizzle_5F5E80
{
    // FUNCTION: GAMEMD 0x6CF240 (declaration) -- queue a pointer for fix-up.
    HRESULT __stdcall FUN_006CF240(void** pointer);
};
// GLOBAL: GAMEMD 0xB0C110
extern Swizzle_5F5E80 DAT_00B0C110;

// The audio controller's initialiser (0x405BE0, __thiscall, no arguments),
// rerun over each controller a load brings in.
struct AudioControllerInit
{
    // FUNCTION: GAMEMD 0x405BE0 (declaration)
    void FUN_00405BE0();
};

// FUNCTION: GAMEMD 0x410380 (decl; reloc) -- AbstractClass's Load body.

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

// FUNCTION: GAMEMD 0x40DD70 (decl; reloc) -- the object if it is a techno, else null.
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
    // FUNCTION: GAMEMD 0x556B30 (declaration)
    void FUN_00556B30();
};

// The owning house, as slot 15 returns it.
struct House_5F5280
{
    // FUNCTION: GAMEMD 0x50B6F0 (declaration)
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

// FUNCTION: GAMEMD 0x5F4360
bool ObjectClass::vf_80(int a1, int a2, int a3, int a4)
{
    return false;
}

// FUNCTION: GAMEMD 0x5F4370
void ObjectClass::vf_82(int a1)
{
}

// FUNCTION: GAMEMD 0x5F4380
bool ObjectClass::vf_89(const CoordStruct& coord, int a2)
{
    return false;
}

// FUNCTION: GAMEMD 0x5F4390
int ObjectClass::vf_90(int a1)
{
    return 0;
}

// FUNCTION: GAMEMD 0x5F43A0
void ObjectClass::vf_93(int a1, int a2, int a3)
{
}

// FUNCTION: GAMEMD 0x5F43B0
bool ObjectClass::vf_94()
{
    return false;
}

// FUNCTION: GAMEMD 0x5F43C0
void ObjectClass::vf_95()
{
}

// FUNCTION: GAMEMD 0x5F43D0
int ObjectClass::vf_96()
{
    return 0;
}

// FUNCTION: GAMEMD 0x5F43E0
int ObjectClass::vf_97()
{
    return -1;
}

// FUNCTION: GAMEMD 0x5F43F0
void ObjectClass::vf_103(int a1)
{
}

// FUNCTION: GAMEMD 0x5F4400
void ObjectClass::vf_104(int a1)
{
}

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

// FUNCTION: GAMEMD 0x5F4D10
// Flag this object and the map for a redraw, once.
void ObjectClass::vf_77()
{
    if (!NeedsRedraw) {
        NeedsRedraw = 1;
        DAT_0087F7E8.FlagToRedraw(0);
    }
}

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

// FUNCTION: GAMEMD 0x5F5C20
void ObjectClass::vf_100(bool a1, bool a2)
{
    vf_34()->vf_37(a1, a2, false, (void*)vf_15());
}

// FUNCTION: GAMEMD 0x5F5E80
// The base load, then the pointer fields queued for fix-up, the two audio
// controllers reinitialised and the line trailer dropped.
HRESULT __stdcall ObjectClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (FAILED(hr)) {
        return hr;
    }
    DAT_00B0C110.FUN_006CF240(&NextObject);
    DAT_00B0C110.FUN_006CF240((void**)&AttachedTag);
    DAT_00B0C110.FUN_006CF240(&AttachedBomb);
    DAT_00B0C110.FUN_006CF240((void**)&unknown_18);
    DAT_00B0C110.FUN_006CF240((void**)&Parachute);
    ((AudioControllerInit*)&AmbientSoundController)->FUN_00405BE0();
    ((AudioControllerInit*)&CustomSoundController)->FUN_00405BE0();
    LineTrailer = 0;
    return S_OK;
}

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

// FUNCTION: GAMEMD 0x5F65A0
CoordStruct ObjectClass::vf_18()
{
    return Location;
}

// FUNCTION: GAMEMD 0x5F65D0
void ObjectClass::vf_70(Point2D* point, RectangleStruct* clip)
{
    vf_69(point, clip);
}

// FUNCTION: GAMEMD 0x5F6690
bool ObjectClass::vf_17()
{
    return !IsAlive;
}

// FUNCTION: GAMEMD 0x5F6940
void ObjectClass::vf_109(const CoordStruct& coord)
{
    Location = coord;
}

// FUNCTION: GAMEMD 0x5F6960
// The cell under Location (looked up twice; the first result is unused).
CellClass* ObjectClass::vf_111()
{
    CoordStruct coord = Location;
    DAT_0087F7E8.FUN_00565730(&coord);
    coord = Location;
    return DAT_0087F7E8.FUN_00565730(&coord);
}

// FUNCTION: GAMEMD 0x5F69C0
// The cell under slot 19's coordinate.
CellStruct ObjectClass::vf_112()
{
    return CoordCell(vf_19(0));
}

// FUNCTION: GAMEMD 0x5F6A10
CellClass* ObjectClass::vf_113()
{
    CellStruct cell = CoordCell(vf_19(0));
    return DAT_0087F7E8.FUN_005657A0(&cell);
}

// FUNCTION: GAMEMD 0x5F6A70
// Whether the object at slot 19's coordinate for `a1` counts as on a bridge:
// true when off a bridge but more than three flight levels below Location over
// a bridge cell, false when on a bridge but more than three flight levels
// above it, otherwise the current OnBridge.
bool ObjectClass::vf_47(int a1)
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

// FUNCTION: GAMEMD 0x5F6B50
void ObjectClass::vf_105(int a1, int a2)
{
}

// FUNCTION: GAMEMD 0x5F6BC0
TechnoTypeClass* ObjectClass::vf_33()
{
    return 0;
}

// FUNCTION: GAMEMD 0x5F6C10
// More than 20 leptons below the ground counts as false.
bool ObjectClass::vf_31()
{
    return vf_114() > -20;
}

// FUNCTION: GAMEMD 0x5F6C30
bool ObjectClass::vf_78()
{
    if (vf_50(DAT_00A83D4C) && vf_52(1) == 0) {
        return false;
    }
    return vf_34()->Selectable;
}

// FUNCTION: GAMEMD 0x5F6C70
bool ObjectClass::vf_79()
{
    return vf_78();
}

// FUNCTION: GAMEMD 0x5F6C80
CoordStruct ObjectClass::vf_42(int a1)
{
    return vf_18();
}

// FUNCTION: GAMEMD 0x5F6DA0
// Forget `target` if it is the parachute.
void ObjectClass::vf_24(void* target)
{
    if (target == Parachute) {
        Parachute = 0;
    }
}
