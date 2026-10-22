// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit Tactical.CPP. The name is the source-file string at 0x842a64
//   in retail gamemd.exe v1.001, passed by the assert at 0x6d4ad7 inside this object's
//   code range (0x6d1830-0x6dcd6f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Retail IPersist::GetClassID (slot 3 of each class's primary vtable) copies a
// 16-byte CLSID global to the caller and returns E_POINTER for a null pointer.
// The owning class of each address is read from the RTTI-named vtable that holds
// it in slot 3. Each class is declared here only as far as this one virtual
// (no layout is claimed); the bodies move into the canonical class once it exists.
//
// Retail RTTI names VectorClass/DynamicVectorClass over Cell, BaseNodeClass, TPoint3D<int>, Point2D,
// TRect<int> and DirtyAreaStruct. Element layouts and compare shapes are read from the FindItemIndex,
// Slot5, Slot6 and SetCapacity bodies; field names are placeholders.
//
//   LIBRARY:  GAMEMD 0x7C5F00  __ftol                (referenced; reloc)
//
//   Names cross-checked against YRpp.
//
//   GLOBAL:   GAMEMD 0xB0CD48   double  sin60 * pixelsPerLepton  (runtime-init)
//   GLOBAL:   GAMEMD 0x7E1738   double  0.5  (rounding bias)
//   LIBRARY:  GAMEMD 0x7C5F00   __ftol  (CRT double->long; excluded from match)
//
// Disassembly (0x6D20E0, len 0x3C):
//   SUB ESP,8 ; CMP ECX,0x2D8 ; MOV [ESP+4],ECX ; MOV [ESP],0
//   JL +8     ; MOV [ESP],1                      <- int(Height >= 728)
//   FILD [ESP+4]                                 <- (double)Height
//   FMUL [0xB0CD48]                              <- * const
//   FIADD [ESP]                                  <- + int(Height >= 728)
//   FADD [0x7E1738]                              <- + 0.5
//   CALL __ftol ; ADD ESP,8 ; RET                <- (int) cast
//
// 728 == 0x2D8. The (Height >= 728) flag is added as an INTEGER (FIADD), so it
// must stay an int operand in the expression, then 0.5 folds in as a double.

#include <objidl.h>
#include "../_layout/side_class.h"
#include "../_layout/wave_class.h"

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
// GLOBAL: GAMEMD 0x007E9A30 -- CLSID of DriveLocomotionClass.
extern const CLSID DAT_007E9A30;
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

class AircraftClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class AircraftTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class AirstrikeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class AITriggerTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class AlphaShapeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class AnimClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class AnimTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class NeuronClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class BulletClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class BulletTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class CampaignClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class CellClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class DiskLaserClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class DriveLocomotionClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class EMPulseClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class FactoryClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class FoggedObjectClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class InfantryClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class InfantryTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class IsometricTileClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class IsometricTileTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class JumpjetLocomotionClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class LightSourceClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class ParasiteClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class RadSiteClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class ScriptClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class ScriptTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class ShipLocomotionClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class SlaveManagerClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class SpawnManagerClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class SuperClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class SuperWeaponTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class Tactical {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TActionClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TagClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TagTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TaskForceClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TeamClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TeamTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TeleportLocomotionClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TemporalClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TEventClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TiberiumClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TriggerClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TriggerTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TubeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class TunnelLocomotionClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class UnitClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class UnitTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class VoxelAnimClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class VoxelAnimTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class VeinholeMonsterClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class WalkLocomotionClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class WarheadTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class WaypointPathClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};
class WeaponTypeClass {
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
};

#include "trivial_tu229_methods.h"

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

#include "../renderer/tactical_class_client_to_coords_methods.h"

#include "../renderer/tactical_class_coords_to_screen_methods.h"

// Lepton (x, y) to the un-normalised iso pixel offset, read through a pointer
// to a two-int local. This is the pClient shape of the sibling
// TacticalClass::AdjustForZShapeMove (match/renderer/tactical_class_matrix_
// methods.cpp) and it is what retail inlined here: the address-taken local
// makes VC6 store Y into the temporary's second slot and reload it
// (`MOV [ESP+0x10],EAX; MOV EDI,[ESP+0x10]`), while X is forwarded straight
// into ESI. With plain int arguments, or with a struct passed by value or
// reference, that spill and reload vanish and the Z load and the bias store
// move ahead of the first LEA (9.7%). The struct returned by value is what
// produces the dead X spill into the temporary's first slot, which Z later
// reuses for its FILD.
static inline Point2D_006D1F10 IsoProject(const int* p)
{
    Point2D_006D1F10 r;
    r.X = p[0] * 60 / 2;
    r.Y = p[0] * 30 / 2;
    r.X += p[1] * -60 / 2;
    r.Y += p[1] * 30 / 2;
    return r;
}

// Height in leptons to the rounded pixel lift, (int)(z * scale + bias + 0.5)
// with bias 1 once the height reaches a bridge level (728 leptons). This is
// TacticalClass::AdjustForZ (0x6D20E0, match/ui/tactical_class_methods.cpp)
// inlined; the bias lands in the dead pCoord parameter slot.
static inline int AdjustForZ(int z)
{
    int bias = 0;
    if (z >= 728) {
        bias = 1;
    }
    return (int)(z * DAT_00B0CD48 + bias + 0.5);
}

#include "../ui/tactical_class_methods.h"

// The scaling factor lives at the fixed global address 0xB0CD48 (runtime-init
// double). Referenced as an extern symbol so cl emits a direct memory operand
// `fmul [factor]` (reloc-normalised to the retail `fmul [0xB0CD48]`), rather
// than the register-indirect form a `*(double*)0xB0CD48` pointer literal forces.
extern double AdjustForZ_Factor;   // GLOBAL: GAMEMD 0xB0CD48

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F4180
extern const double DAT_007F4180;
// GLOBAL: GAMEMD 0xB0CD78
extern double DAT_00B0CD78;
// GLOBAL: GAMEMD 0xB0CEA0
extern double DAT_00B0CEA0;
// GLOBAL: GAMEMD 0xB0CEA8
extern int DAT_00B0CEA8;
// GLOBAL: GAMEMD 0xB0CEAC
extern int DAT_00B0CEAC;
// GLOBAL: GAMEMD 0xB0CEB0
extern int DAT_00B0CEB0;
// GLOBAL: GAMEMD 0xB0CEB8
extern double DAT_00B0CEB8;

// FUNCTION: GAMEMD 0x6D1860
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_006D1860()
{
    DAT_00B0CEB8 = DAT_00B0CD78 / DAT_007F4180;
}

// FUNCTION: GAMEMD 0x6D1880
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_006D1880()
{
    DAT_00B0CEA0 = DAT_007E1718 / DAT_00B0CEB8;
}

// FUNCTION: GAMEMD 0x6D1A00
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_006D1A00()
{
    DAT_00B0CEB0 = 0;
    DAT_00B0CEA8 = 0x80;
    DAT_00B0CEAC = 0x80;
}

// FUNCTION: GAMEMD 0x6D1B00
// Empty function.
void __cdecl FUN_006D1B00()
{
}

// FUNCTION: GAMEMD 0x6D1F10
//
// World coordinate to the raw iso screen point: the (x, y) leptons go through
// the 60x30 projection and a signed divide by 256, then the height lift is
// subtracted from Y. Z is read off pCoord only when the lift is computed, which
// keeps pCoord in EBX across the projection and lets Z take over EBX after it.
// The result is stored to pDest as one Point2D and pDest comes back in EAX.
Point2D_006D1F10* Tactical_006D1F10::CoordsToScreen(Point2D_006D1F10* pDest,
                                                     const Coord_006D1F10* pCoord)
{
    int xy[2];
    xy[0] = pCoord->X;
    xy[1] = pCoord->Y;

    Point2D_006D1F10 r = IsoProject(xy);
    r.X /= 256;
    r.Y /= 256;
    r.Y -= AdjustForZ(pCoord->Z);

    *pDest = r;
    return pDest;
}

// FUNCTION: GAMEMD 0x6D20E0  TacticalClass::AdjustForZ (__fastcall)
int __fastcall TacticalClass::AdjustForZ(int Height)
{
    int bias = 0;
    if (Height >= 728) {
        bias = 1;
    }
    return (int)(Height * AdjustForZ_Factor + bias + 0.5);
}

// FUNCTION: GAMEMD 0x6D2280
//
// Client (screen) point to a world coordinate — the inverse of
// TacticalClass::CoordsToScreen. A point outside the view's X/Y extents gets
// the "no coordinate" global. Otherwise the point is shifted by the view
// offset, run through the iso transform matrix at +0xDE4 as a float vector
// (Z taken as 0), and the transformed X/Y are truncated back to ints; Z of
// the result is 0.
//
// Phrasing (each piece load-bearing, 65.6% -> 100%): the shifted point is a
// Point2D local in its own block, so its two int slots are written before
// the first FILD and are then reused by the apply helper's result vector in
// the next block (retail's 0x18-byte frame: r low, v high); the view offset
// is read as one Point2D (`MOV EAX,[ECX+0xB0]; MOV EDX,[ECX+0xB4]` back to
// back), which is also what puts the client X/Y in EDI/ESI and the limits in
// EDX — member-wise reads of the offset give the caller-saved allocation. The
// Y limit is written `DAT_00B0CE34 + DAT_00B0CE2C` so the +0x34 global is
// loaded first. The helper's result is copied back into the input vector (the
// 3-dword copy off the returned pointer) exactly as in
// TacticalClass::ApplyMatrix_Pixel, and the result is stored to pDest as one
// struct so all three stores follow the second conversion.
Coord_006D2280* Tactical_006D2280::ClientToCoords(Coord_006D2280* pDest,
                                                  const Point2D_006D2280* pClient)
{
    if (pClient->X < DAT_00B0CE30 && pClient->Y < DAT_00B0CE34 + DAT_00B0CE2C) {
        Vector3D_006D2280 v;
        {
            Point2D_006D2280 pt;
            Point2D_006D2280 off = this->Offset_B0;
            pt.X = pClient->X + off.X;
            pt.Y = pClient->Y + off.Y;
            v.X = (float)pt.X;
            v.Y = (float)pt.Y;
            v.Z = 0.0f;
        }
        {
            Vector3D_006D2280 r;
            v = *Matrix3D_006D2280::MatrixApply(&r, &this->IsoTransformMatrix, &v);
        }

        Coord_006D2280 c;
        c.X = (int)v.X;
        c.Y = (int)v.Y;
        c.Z = 0;
        *pDest = c;
        return pDest;
    }

    *pDest = DAT_00B0CE08;
    return pDest;
}

// FUNCTION: GAMEMD 0x6D2B50
// Empty function that pops its stack arguments.
void __stdcall FUN_006D2B50(int a1, int a2)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6D4E00
// Stores several members.
void Obj_006D4E00::FUN_006D4E00()
{
    unknown_A4 = -1;
    unknown_24 = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6D6170
// Stores several members; pops its stack arguments.
Arg1_006D6170* Obj_006D6170::FUN_006D6170(Arg1_006D6170* a1)
{
    a1->unknown_00 = unknown_D64;
    a1->unknown_04 = unknown_D68;
    return a1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6D8630
// Empty function.
void __cdecl FUN_006D8630()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6DA350
// Empty function.
void __cdecl FUN_006DA350()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6DA370
// Empty function that pops its stack arguments.
void __stdcall FUN_006DA370(int a1)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x006DBCE0
HRESULT __stdcall Tactical::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9950;
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6DC400
// Empty function.
void __cdecl FUN_006DC400()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6DC410
// Empty function.
void __cdecl FUN_006DC410()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6DC450
// Returns a constant. Vtable slot 11 of Tactical (RTTI).
int Obj_006DC450::FUN_006DC450() const
{
    return 0x38;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6DC460
// Returns a constant. Vtable slot 12 of Tactical (RTTI).
int Obj_006DC460::FUN_006DC460() const
{
    return 0xE18;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x006DC5E0
// VectorClass<DirtyAreaStruct>::operator==
// FUNCTION: GAMEMD 0x006DC660
// VectorClass<DirtyAreaStruct>::SetCapacity
// FUNCTION: GAMEMD 0x006DC7B0
// VectorClass<DirtyAreaStruct>::FindItemIndex
// FUNCTION: GAMEMD 0x006DC820
// VectorClass<DirtyAreaStruct>::Slot5
// FUNCTION: GAMEMD 0x006DC970
// DynamicVectorClass<DirtyAreaStruct>::FindItemIndex
// FUNCTION: GAMEMD 0x006DC510
// DynamicVectorClass<DirtyAreaStruct>::Slot5
template class VectorClass<DirtyAreaStruct>;
