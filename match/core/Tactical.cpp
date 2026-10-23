// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2 /MT
// /Ob2 inlines the real destructor into the scalar deleting destructor
// at 0x6DC470; /Ob1 leaves a call and scores12.5%. All prior exact rows
// in this TU remain raw-exact under this flag.
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
#include "../_layout/tactical.h"
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

#include "../_layout/cell.h"
// The canonical Cell class uses the same two-short comparison shown by
// the vector element operations; definitions stay inline in this consumer.
inline bool Cell::operator==(const Cell& o) const { return X == o.X && Y == o.Y; }
inline bool Cell::operator!=(const Cell& o) const { return !(*this == o); }

template class DynamicVectorClass<Cell>;

 struct BaseNodeClass { int unknown_00; Cell unknown_04; unsigned char unknown_08; int unknown_0C; BaseNodeClass() {} BaseNodeClass(const BaseNodeClass& o) : unknown_00(o.unknown_00), unknown_04(o.unknown_04), unknown_08(o.unknown_08), unknown_0C(o.unknown_0C) {} bool operator==(const BaseNodeClass& o) const { return unknown_00==o.unknown_00 && unknown_04==o.unknown_04; } bool operator!=(const BaseNodeClass& o) const { return !(*this==o); } };

template class DynamicVectorClass<BaseNodeClass>;

template<class T> struct TPoint3D { T X; T Y; T Z; TPoint3D() {} bool operator==(const TPoint3D<T>& o) const { return X==o.X && Y==o.Y && Z==o.Z; } bool operator!=(const TPoint3D<T>& o) const { return !(*this==o); } };

#include "../_layout/geometry2d.h"
template class DynamicVectorClass<Point2D>;

template class DynamicVectorClass<TRect<int> >;


#include "../_layout/dirty_area.h"
template class DynamicVectorClass<DirtyAreaStruct>;

#include "../renderer/tactical_class_client_to_coords_methods.h"

#include "../renderer/tactical_class_coords_to_screen_methods.h"

// Lepton (x, y) to the un-normalised iso pixel offset, read through a pointer
// to a two-int local. This is the pClient shape of the sibling
// Tactical::AdjustForZShapeMove (match/renderer/tactical_class_matrix_
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
// Tactical::AdjustForZ (0x6D20E0, match/ui/tactical_class_methods.cpp)
// inlined; the bias lands in the dead pCoord parameter slot.
static inline int AdjustForZ(int z)
{
    int bias = 0;
    if (z >= 728) {
        bias = 1;
    }
    return (int)(z * DAT_00B0CD48 + bias + 0.5);
}


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

// GLOBAL: GAMEMD 0x7E1728
extern "C" const double DAT_007E1728;
// GLOBAL: GAMEMD 0xB0CD88
extern double DAT_00B0CD88;
// GLOBAL: GAMEMD 0xB0CE18
extern double DAT_00B0CE18;
// GLOBAL: GAMEMD 0xB0CDD8
extern double DAT_00B0CDD8;
// The existing table-trigonometry call at0x4CACB0 takes a cdecl double.
extern "C" double __cdecl FUN_004CACB0(double angle);

// FUNCTION: GAMEMD 0x6D1B00
// Empty function.
void __cdecl FUN_006D1B00()
{
}

// FUNCTION: GAMEMD 0x6D1BB0
void __cdecl FUN_006D1BB0()
{
    DAT_00B0CE18 = DAT_007E1728 / DAT_00B0CD78;
    DAT_00B0CD48 = FUN_004CACB0(DAT_00B0CD88) * DAT_00B0CE18;
}

// FUNCTION: GAMEMD 0x6D1BF0
void __cdecl FUN_006D1BF0()
{
    DAT_00B0CDD8 = DAT_00B0CD78 / (FUN_004CACB0(DAT_00B0CD88) * DAT_007E1728);
}

#include <string.h>
// GLOBAL: GAMEMD 0xB0CD60
extern int DAT_00B0CD60[4];
// GLOBAL: GAMEMD 0xB0CD88
extern double DAT_00B0CD88;
// GLOBAL: GAMEMD 0xB0CE98
extern double DAT_00B0CE98;
// GLOBAL: GAMEMD 0xB0CD78
extern double DAT_00B0CD78;
// GLOBAL: GAMEMD 0x887324
extern Tactical* DAT_00887324;

// FUNCTION: GAMEMD 0x6D1C20
Tactical::Tactical()
    : unknown_A8(-1), unknown_AC(false), unknown_AD(false),
      unknown_B0(0, 0), unknown_B8(0, 0), unknown_C0(1.0),
      unknown_C8(DAT_00B0CE08.X, DAT_00B0CE08.Y),
      unknown_D0(DAT_00B0CE08.X, DAT_00B0CE08.Y),
      unknown_D8(0.0f), unknown_DC(0.0f), unknown_E0(0),
      unknown_D64(0, 0), unknown_D6C(0, 0), unknown_D74(0, 0),
      unknown_D7C(1), unknown_D7D(false), unknown_D7E(false),
      unknown_D80(DAT_00B0CD60[0]), unknown_D84(DAT_00B0CD60[1]),
      unknown_D88(DAT_00B0CD60[2]), unknown_D8C(DAT_00B0CD60[3]),
      unknown_D90(0, 0), unknown_D98(0, 0), unknown_DA0(0), unknown_DB0(0)
{
    memset(unknown_E4, 0, sizeof unknown_E4);
    unknown_24[0] = 0;
    unknown_A4 = -1;
    unknown_DB4.FUN_005AE860();
    unknown_DB4.FUN_005AEF60((float)DAT_00B0CD88);
    unknown_DB4.FUN_005AF1A0((float)DAT_00B0CE98);
    unknown_DB4.FUN_005AEA10((float)(60.0f / DAT_00B0CD78));
    unknown_DE4.Row[0][0] = 4.26669979095459f;
    unknown_DE4.Row[0][1] = 8.53339958190918f;
    unknown_DE4.Row[0][2] = 0.0f;
    unknown_DE4.Row[0][3] = 0.0f;
    unknown_DE4.Row[1][0] = -4.26669979095459f;
    unknown_DE4.Row[1][1] = 8.53339958190918f;
    unknown_DE4.Row[1][2] = 0.0f;
    unknown_DE4.Row[1][3] = 0.0f;
    unknown_DE4.Row[2][0] = 0.0f;
    unknown_DE4.Row[2][1] = 0.0f;
    unknown_DE4.Row[2][2] = 1.0f;
    unknown_DE4.Row[2][3] = 0.0f;
    DAT_00887324 = this;
}

// GLOBAL: GAMEMD 0x887324
extern Tactical* DAT_00887324;

// FUNCTION: GAMEMD 0x6D1E30
Tactical::Tactical(const AbstractNoInit& noInit)
    : AbstractClass(noInit)
{
}

// FUNCTION: GAMEMD 0x6D1E80
Tactical::~Tactical()
{
    DAT_00887324 = 0;
}

// FUNCTION: GAMEMD 0x6D1EB0
Pair_006D9F80* Pair_006D9F80::FUN_006D1EB0(int x, int y)
{
    int projectedX = x * 60 / 2;
    int projectedY = x * 30 / 2;
    projectedX += y * -60 / 2;
    projectedY += y * 30 / 2;
    unknown_00 = projectedX;
    unknown_04 = projectedY;
    return this;
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

// FUNCTION: GAMEMD 0x6D20E0  Tactical::AdjustForZ (__fastcall)
int Tactical::AdjustForZ(int Height)
{
    int bias = 0;
    if (Height >= 728) {
        bias = 1;
    }
    return (int)(Height * AdjustForZ_Factor + bias + 0.5);
}

// GLOBAL: GAMEMD 0xB0CDD8
extern double DAT_00B0CDD8;

// The table is indexed in 12-byte records; only its first word is read here.
struct Record_00B0CEC8
{
    ObjectClass* unknown_00;
    int unknown_04;
    int unknown_08;
};
GG_STATIC_ASSERT(offsetof(Record_00B0CEC8, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(Record_00B0CEC8, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(Record_00B0CEC8, unknown_08) == 8);
GG_STATIC_ASSERT(sizeof(Record_00B0CEC8) == 12);
// GLOBAL: GAMEMD 0xB0CEC8
extern Record_00B0CEC8 DAT_00B0CEC8[];

// FUNCTION: GAMEMD 0x6D2120
// ECX supplies the integer; FILD, subtract 0.5, scale, and CRT conversion.
int FUN_006D2120(int value)
{
    return (int)((value - 0.5) * DAT_00B0CDD8);
}

// FUNCTION: GAMEMD 0x6D2280
//
// Client (screen) point to a world coordinate — the inverse of
// Tactical::CoordsToScreen. A point outside the view's X/Y extents gets
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
// Tactical::ApplyMatrix_Pixel, and the result is stored to pDest as one
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

// FUNCTION: GAMEMD 0x6D2360
Coord_006D2280* Tactical::FUN_006D2360(Coord_006D2280* out,
                                       const Point2D_006D2280* point)
{
    if (point->X < DAT_00B0CE30 && point->Y < DAT_00B0CE34) {
        Vector3D_006D2280 vector;
        vector.X = (float)point->X;
        vector.Y = (float)point->Y;
        vector.Z = 0.0f;
        {
            Vector3D_006D2280 transformed;
            vector = *Matrix3D_006D2280::MatrixApply(&transformed, &unknown_DE4, &vector);
        }
        Coord_006D2280 coordinate;
        coordinate.X = (int)vector.X;
        coordinate.Y = (int)vector.Y;
        coordinate.Z = 0;
        *out = coordinate;
        return out;
    }
    *out = DAT_00B0CE08;
    return out;
}

// FUNCTION: GAMEMD 0x6D2B50
// Empty function that pops its stack arguments.
void __stdcall FUN_006D2B50(int a1, int a2)
{
}

// LIBRARY: GAMEMD 0x7CA489 -- null-terminated 16-bit string copy.
extern "C" unsigned short* __cdecl FUN_007CA489(unsigned short* destination,
                                              const unsigned short* source);

// FUNCTION: GAMEMD 0x6D4DB0
void Tactical::FUN_006D4DB0(const unsigned short* text, int mode)
{
    if (text == 0) {
        FUN_006D4E00();
    } else {
        FUN_007CA489(unknown_24, text);
    }
    unknown_A4 = mode;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6D4E00
// Stores several members.
void Tactical::FUN_006D4E00()
{
    unknown_A4 = -1;
    unknown_24[0] = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// GLOBAL: GAMEMD 0xA8ED6B
extern unsigned char DAT_00A8ED6B;

// GLOBAL: GAMEMD 0xB0CE28
extern int DAT_00B0CE28;

// FUNCTION: GAMEMD 0x6D5F60
void Tactical::FUN_006D5F60(const TRect<int>* bounds)
{
    DAT_00B0CE28 = bounds->X;
    DAT_00B0CE2C = bounds->Y;
    DAT_00B0CE30 = bounds->Width;
    DAT_00B0CE34 = bounds->Height;
    Pair_006D9F80 checked = unknown_D74;
    int x, y;
    if (FUN_006D8640(&checked) && DAT_00A8ED6B == 0) {
        x = checked.unknown_00;
        y = checked.unknown_04;
    } else {
        x = unknown_D74.unknown_00;
        y = unknown_D74.unknown_04;
    }
    unknown_D64.unknown_00 = unknown_D74.unknown_00 = x;
    unknown_D64.unknown_04 = unknown_D74.unknown_04 = y;
    FUN_006D8B30();
    unknown_D7D = true;
}

// FUNCTION: GAMEMD 0x6D6000
void Tactical::FUN_006D6000(const Pair_006D9F80* point)
{
    Pair_006D9F80 checked = *point;
    unknown_D64 = unknown_D74 =
        FUN_006D8640(&checked) && DAT_00A8ED6B == 0 ? checked : *point;
    FUN_006D8B30();
    unknown_D7D = true;
}

// FUNCTION: GAMEMD 0x6D6170
// Stores several members; pops its stack arguments.
Arg1_006D6170* Obj_006D6170::FUN_006D6170(Arg1_006D6170* a1)
{
    a1->unknown_00 = unknown_D64;
    a1->unknown_04 = unknown_D68;
    return a1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6D6190
Pair_006D9F80 Tactical::FUN_006D6190() const
{
    Pair_006D9F80 position = unknown_D64;
    Pair_006D9F80 offset = unknown_B0;
    position.unknown_00 -= offset.unknown_00;
    position.unknown_04 -= offset.unknown_04;
    return position;
}

// FUNCTION: GAMEMD 0x6D61C0
void FUN_006D61C0(int x, int y, int* outX, int* outY)
{
    *outX = x * 60 / 2;
    *outY = x * 30 / 2;
    *outX += y * -60 / 2;
    *outY += y * 30 / 2;
}

// FUNCTION: GAMEMD 0x6D6220
void FUN_006D6220(int x, int y, int* outX, int* outY)
{
    *outX = (x + 2 * y) * 15 / 576 - 65536;
    *outY = (2 * y - x) * 15 / 576 + 65536;
}

// FUNCTION: GAMEMD 0x6D6280
void __stdcall FUN_006D6280(int x, int y, int* outX, int* outY)
{
    x *= 256;
    y *= 256;
    *outX = (x + 2 * y) * 15 / 576 - 65536;
    *outY = (2 * y - x) * 15 / 576 + 65536;
}

// FUNCTION: GAMEMD 0x6D62E0
void __stdcall FUN_006D62E0(int x, int y, int* outX, int* outY)
{
    *outX = x * 60 / 2;
    *outY = x * 30 / 2;
    *outX += y * -60 / 2;
    *outY += y * 30 / 2;
    *outX /= 256;
    *outY /= 256;
    *outX += 15360;
}

// GLOBAL: GAMEMD 0x842904
extern int DAT_00842904;
// GLOBAL: GAMEMD 0x842908
extern int DAT_00842908;

// FUNCTION: GAMEMD 0x6D6370
void __stdcall FUN_006D6370(int x, int y, int* outX, int* outY)
{
    x *= 256;
    y *= 256;
    int resultX = (x + 2 * y) * 15 / 576 - 65536;
    int resultY = (2 * y - x) * 15 / 576 + 65536;
    if (DAT_00842904 == -1 && DAT_00842908 == -1) {
        DAT_00842908 = 65536;
        DAT_00842904 = -65536;
    }
    resultX -= DAT_00842904;
    resultY -= DAT_00842908;
    *outX = resultX;
    *outY = resultY;
}

// FUNCTION: GAMEMD 0x6D8530
void Tactical::FUN_006D8530(int direction, int distance)
{
// SYNTHETIC: GAMEMD 0x6D8630
// Generated array cleanup, one-byte RET. Guard at0xB0CDE0 is compiler-generated.
// GLOBAL: GAMEMD 0xB0CE38
    static Pair_006D9F80 offsets[8] = {
        Pair_006D9F80(0, -1), Pair_006D9F80(1, -1),
        Pair_006D9F80(1, 0), Pair_006D9F80(1, 1),
        Pair_006D9F80(0, 1), Pair_006D9F80(-1, 1),
        Pair_006D9F80(-1, 0), Pair_006D9F80(-1, -1)
    };
    Pair_006D9F80 old = unknown_D64;
    Pair_006D9F80 next(offsets[direction].unknown_00 * distance + old.unknown_00,
                      offsets[direction].unknown_04 * distance + old.unknown_04);
    if (!(old == next)) {
        unknown_D74.unknown_00 = next.unknown_00 - old.unknown_00 + unknown_D74.unknown_00;
        unknown_D74.unknown_04 = next.unknown_04 - old.unknown_04 + unknown_D74.unknown_04;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// GLOBAL: GAMEMD 0x87F8DC
extern int DAT_0087F8DC;
// GLOBAL: GAMEMD 0x87F8E4
extern int DAT_0087F8E4;
// GLOBAL: GAMEMD 0x87F8E8
extern int DAT_0087F8E8;
// GLOBAL: GAMEMD 0x87F8EC
extern int DAT_0087F8EC;
// GLOBAL: GAMEMD 0x87F8F0
extern int DAT_0087F8F0;
// GLOBAL: GAMEMD 0x886FA8
extern int DAT_00886FA8;
// GLOBAL: GAMEMD 0x886FAC
extern int DAT_00886FAC;

// FUNCTION: GAMEMD 0x6D8640
bool Tactical::FUN_006D8640(Pair_006D9F80* point)
{
    int left = DAT_00886FA8 / 2 + (2 * DAT_0087F8E4 - DAT_0087F8DC) * 30;
    int right = DAT_0087F8EC * 60 - DAT_00886FA8 + left;
    int top = (DAT_0087F8DC - 5 + 2 * DAT_0087F8E8) * 15 + DAT_00886FAC / 2;
    int bottom = (DAT_0087F8F0 * 60 + 270) / 2 - DAT_00886FAC + top;
    bool changed = false;
    if (point->unknown_04 < top) {
        changed = true;
        point->unknown_04 = top;
    } else if (point->unknown_04 > bottom) {
        point->unknown_04 = bottom;
        changed = true;
    }
    if (point->unknown_00 < left) {
        point->unknown_00 = left;
        return true;
    }
    if (point->unknown_00 > right) {
        point->unknown_00 = right;
        return true;
    }
    return changed;
}

GG_STATIC_ASSERT(offsetof(Cell, X) == 0);
GG_STATIC_ASSERT(offsetof(Cell, Y) == 2);
GG_STATIC_ASSERT(sizeof(Cell) == 4);

// FUNCTION: GAMEMD 0x6D8AE0
bool Tactical::FUN_006D8AE0(const Cell* cell) const
{
    int x = cell->X;
    int y = cell->Y;
    if (x >= unknown_D80 && x < unknown_D80 + unknown_D88
        && y >= unknown_D84 && y < unknown_D84 + unknown_D8C)
        return true;
    return false;
}

// FUNCTION: GAMEMD 0x6D8B30
void Tactical::FUN_006D8B30()
{
    Pair_006D9F80 center = unknown_D64;
    unknown_B0 = center;
    unknown_B0.unknown_00 = center.unknown_00 - DAT_00B0CE30 / 2;
    unknown_B0.unknown_04 = center.unknown_04 - DAT_00B0CE34 / 2;
    Vector3D_006D2280 vector;
    vector.X = (float)(unknown_B0.unknown_00 - 60);
    vector.Y = (float)(unknown_B0.unknown_04 - 30);
    vector.Z = 0.0f;
    Vector3D_006D2280 transformed;
    vector = *Matrix3D_006D2280::MatrixApply(&transformed, &unknown_DE4, &vector);
    int x = (int)vector.X;
    int y = (int)vector.Y;
    unknown_D80 = x / 256;
    unknown_D84 = y / 256;
    unknown_D88 = DAT_00B0CE30 / 60 + 2;
    unknown_D8C = DAT_00B0CE34 / 15 + 4;
}

#include "../_layout/object_class.h"

// FUNCTION: GAMEMD 0x6D8C60
void FUN_006D8C60(ObjectClass* object, int argument)
{
    CoordStruct coordinate = object->vf_18();
    int xy[2] = { coordinate.X, coordinate.Y };
    Point2D_006D1F10 projected = IsoProject(xy);
    Pair_006D9F80 point(projected.X / 256,
                        projected.Y / 256 - AdjustForZ(coordinate.Z));
    point.unknown_00 -= DAT_00887324->unknown_B0.unknown_00;
    point.unknown_04 -= DAT_00887324->unknown_B0.unknown_04;
    if (point.unknown_00 >= -360 && point.unknown_00 <= DAT_00B0CE30 + 360 &&
        point.unknown_04 >= -180 && point.unknown_04 <= DAT_00B0CE34 + 180) {
        // 0x6D8D86/0x6D8D97 pass the address of this two-int point.
        // The canonical virtual slots currently use opaque32-bit arguments.
        object->vf_67((int)&point, argument);
        object->vf_68((int)&point, argument);
    }
}

// FUNCTION: GAMEMD 0x6D9F80
void Tactical::FUN_006D9F80(const Pair_006D9F80* value)
{
    if (unknown_D90.unknown_00 == 0 && unknown_D90.unknown_04 == 0) {
        unknown_D90 = *value;
        unknown_D98 = *value;
    }
}

// FUNCTION: GAMEMD 0x6D9FC0
void Tactical::FUN_006D9FC0(const Pair_006D9F80* value)
{
    if (unknown_D90.unknown_00 != 0 || unknown_D90.unknown_04 != 0)
        unknown_D98 = *value;
}

template class TRect<int>;
typedef TRect<int> Rect_006D9FF0;
GG_STATIC_ASSERT(offsetof(Rect_006D9FF0, X) == 0);
GG_STATIC_ASSERT(offsetof(Rect_006D9FF0, Y) == 4);
GG_STATIC_ASSERT(offsetof(Rect_006D9FF0, Width) == 8);
GG_STATIC_ASSERT(offsetof(Rect_006D9FF0, Height) == 12);
GG_STATIC_ASSERT(sizeof(Rect_006D9FF0) == 16);

// FUNCTION: GAMEMD 0x6D9FF0
void Tactical::FUN_006D9FF0(int mode)
{
    if (!(unknown_D90 == Pair_006D9F80(0, 0))) {
        int left = unknown_D90.unknown_00;
        int right = unknown_D98.unknown_00;
        int top = unknown_D90.unknown_04;
        int bottom = unknown_D98.unknown_04;
        if (left > right) {
            int temporary = left;
            left = right;
            right = temporary;
        }
        if (top > bottom) {
            int temporary = top;
            top = bottom;
            bottom = temporary;
        }
        TRect<int> rectangle;
        rectangle.X = left;
        rectangle.Y = top;
        rectangle.Width = right - left + 1;
        rectangle.Height = bottom - top + 1;
        FUN_006DA5C0(&rectangle, mode);
        unknown_D90 = Pair_006D9F80(0, 0);
    }
}

// FUNCTION: GAMEMD 0x6DA080
int Tactical::FUN_006DA080() const
{
    int left = unknown_D90.unknown_00;
    int right = unknown_D98.unknown_00;
    int top = unknown_D90.unknown_04;
    int bottom = unknown_D98.unknown_04;
    if (left > right) {
        int temporary = left;
        left = right;
        right = temporary;
    }
    if (top > bottom) {
        int temporary = top;
        top = bottom;
        bottom = temporary;
    }
    TRect<int> rectangle;
    rectangle.X = left;
    rectangle.Y = top;
    rectangle.Width = right - left + 1;
    rectangle.Height = bottom - top + 1;
    if (rectangle.Width > 0 && rectangle.Height > 0) {
        for (int i = 0; i < unknown_DB0; ++i) {
            if (DAT_00B0CEC8[i].unknown_00 != 0 && DAT_00B0CEC8[i].unknown_00->IsAlive) {
                int x = DAT_00B0CEC8[i].unknown_04 - unknown_B0.unknown_00;
                int y = DAT_00B0CEC8[i].unknown_08 - unknown_B0.unknown_04;
                if (x >= rectangle.X && x < rectangle.X + rectangle.Width
                    && y >= rectangle.Y && y < rectangle.Y + rectangle.Height)
                    return 1;
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6DA160
void Tactical::FUN_006DA160()
{
    Pair_006D9F80 value(0, 0);
    unknown_D90 = value;
    unknown_D98 = value;
}

// GLOBAL: GAMEMD 0x84290C
// Nine signed-offset lookup entries; retail indexes the middle at0x84291C.
extern const int DAT_0084290C[9];

// FUNCTION: GAMEMD 0x6DA230
int Tactical::FUN_006DA230(int direction)
{
// SYNTHETIC: GAMEMD 0x6DA350
// Generated cleanup for this function-local array.
// GLOBAL: GAMEMD 0xB0CD98
    static Pair_006D9F80 offsets[8] = {
        Pair_006D9F80(0, -1), Pair_006D9F80(1, -1),
        Pair_006D9F80(1, 0), Pair_006D9F80(1, 1),
        Pair_006D9F80(0, 1), Pair_006D9F80(-1, 1),
        Pair_006D9F80(-1, 0), Pair_006D9F80(-1, -1)
    };
    Pair_006D9F80 current = unknown_D64;
    Pair_006D9F80 next(offsets[direction].unknown_00 + current.unknown_00,
                      offsets[direction].unknown_04 + current.unknown_04);
    if (!(next == current)) {
        Pair_006D9F80 checked = next;
        if (FUN_006D8640(&checked) && DAT_00A8ED6B == 0)
            next = checked;
        direction = DAT_0084290C[(unknown_D64.unknown_00 - next.unknown_00) +
                                (unknown_D64.unknown_04 - next.unknown_04) * 3 + 4];
    }
    return direction;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6DA370
// Empty function that pops its stack arguments.
void __stdcall FUN_006DA370(int a1)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
#include "../_layout/object_class.h"

// GLOBAL: GAMEMD 0xA8ECBC
extern ObjectClass** DAT_00A8ECBC;
// GLOBAL: GAMEMD 0xA8ECC8
extern int DAT_00A8ECC8;

// FUNCTION: GAMEMD 0x6DA740
void Tactical::FUN_006DA740()
{
    while (DAT_00A8ECC8 != 0)
        DAT_00A8ECBC[0]->vf_84();
    FUN_00731D00(0);
}

// FUNCTION: GAMEMD 0x006DBCE0
HRESULT __stdcall Tactical::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9950;
    return S_OK;
}

#include <new.h>
#include "../_layout/swizzle_manager_class.h"
// GLOBAL: GAMEMD 0xB0C110
extern SwizzleManagerClass DAT_00B0C110;

// FUNCTION: GAMEMD 0x6DBD20
HRESULT __stdcall Tactical::Load(IStream* stream)
{
    HRESULT hr = AbstractClass::Load(stream);
    if (hr < 0) return hr;
    new (this) Tactical(AbstractNoInit());
    unknown_DB0 = 0;
    for (int i = 0; i < unknown_E0; ++i) {
        // 0x6DBD69 pushes the address of each four-byte pointer to6CF240.
        // The canonical placeholder slot takes an opaque32-bit integer;
        // this ABI conversion preserves that binary-proven pointer argument.
        DAT_00B0C110.SwizzleManagerClass::vf_4((int)&unknown_E4[i]);
    }
    Pair_006D9F80 point = unknown_D64;
    if (FUN_006D8640(&point) && !DAT_00A8ED6B) {
        unknown_D64 = point;
        unknown_D74 = point;
    } else {
        unknown_D74 = unknown_D64;
    }
    FUN_006D8B30();
    unknown_D7D = true;
    return 0;
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
// FUNCTION: GAMEMD 0x6DC430
ObjectClass* Tactical::FUN_006DC430(int index)
{
    return DAT_00B0CEC8[index].unknown_00;
}

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
// SYNTHETIC: GAMEMD 0x006DC470
// Tactical::scalar deleting destructor

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
