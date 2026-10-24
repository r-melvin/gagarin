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
#include "../../_layout/side_class.h"
#include "../../_layout/wave_class.h"

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
#include "../../combat/airstrike_class_methods.h"
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
#include "../../_layout/cell_class.h"
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
#include "../../_layout/super_class.h"
#include "../../combat/super_weapon_type_class_methods.h"
#include "../../_layout/tactical.h"
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

#include "../../core/trivial_tu229_methods.h"

#include "../../core/vector_class_operations.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "../../_layout/cell.h"
// The canonical Cell class uses the same two-short comparison shown by
// the vector element operations; definitions stay inline in this consumer.
inline bool Cell::operator==(const Cell& o) const { return X == o.X && Y == o.Y; }
inline bool Cell::operator!=(const Cell& o) const { return !(*this == o); }

template class DynamicVectorClass<Cell>;

 struct BaseNodeClass { int unknown_00; Cell unknown_04; unsigned char unknown_08; int unknown_0C; BaseNodeClass() {} BaseNodeClass(const BaseNodeClass& o) : unknown_00(o.unknown_00), unknown_04(o.unknown_04), unknown_08(o.unknown_08), unknown_0C(o.unknown_0C) {} bool operator==(const BaseNodeClass& o) const { return unknown_00==o.unknown_00 && unknown_04==o.unknown_04; } bool operator!=(const BaseNodeClass& o) const { return !(*this==o); } };

template class DynamicVectorClass<BaseNodeClass>;

template<class T> struct TPoint3D { T X; T Y; T Z; TPoint3D() {} bool operator==(const TPoint3D<T>& o) const { return X==o.X && Y==o.Y && Z==o.Z; } bool operator!=(const TPoint3D<T>& o) const { return !(*this==o); } };

#include "../../_layout/geometry2d.h"
template class DynamicVectorClass<Point2D>;

template class DynamicVectorClass<TRect<int> >;


#include "../../_layout/dirty_area.h"
template class DynamicVectorClass<DirtyAreaStruct>;

#include "../../renderer/tactical_class_client_to_coords_methods.h"

#include "../../renderer/tactical_class_coords_to_screen_methods.h"

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
static inline Point2D IsoProject(const int* p)
{
    Point2D r;
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
#include "../../_rt/gg_static_assert.h"

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
    unknown_DB4.MakeIdentity();
    unknown_DB4.RotateX((float)DAT_00B0CD88);
    unknown_DB4.RotateZ((float)DAT_00B0CE98);
    unknown_DB4.Scale((float)(60.0f / DAT_00B0CD78));
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
// Point2D returns through the MSVC6 hidden stack result pointer; EAX returns
// that pointer. The value-return form preserves the exact200-byte body.
Point2D Tactical::CoordsToScreen(const CoordStruct* pCoord)
{
    int xy[2];
    xy[0] = pCoord->X;
    xy[1] = pCoord->Y;

    Point2D r = IsoProject(xy);
    r.X /= 256;
    r.Y /= 256;
    r.Y -= AdjustForZ(pCoord->Z);

    return r;
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
        Vector3D v;
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
            Vector3D r;
            v = *Matrix3D::MatrixApply(&r, &this->IsoTransformMatrix, &v);
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
        Vector3D vector;
        vector.X = (float)point->X;
        vector.Y = (float)point->Y;
        vector.Z = 0.0f;
        {
            Vector3D transformed;
            vector = *Matrix3D::MatrixApply(&transformed, &unknown_DE4, &vector);
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

#include "../../_layout/rules_class.h"
#include "../../core/frame_counter.h"
#include "../../core/game_state_flags.h"
extern unsigned char DAT_00A8ED6B; // GLOBAL: GAMEMD 0xA8ED6B (decl; reloc)
// FUNCTION: GAMEMD 0x6D2540
void Tactical::vf_23()
{
    if (DAT_00A8D5F8 & 2) return;
    bool moved = false;
    if (unknown_A8 != CurrentFrame) {
        if (DAT_00A8ED5C &&
            (unknown_D0.unknown_00 != DAT_00B0CE08.X ||
             unknown_D0.unknown_04 != DAT_00B0CE08.Y) && unknown_D8 != 0.0f) {
            unknown_DC += unknown_D8;
            if (unknown_DC > 1.0) unknown_DC = 1.0f;
            Pair_006D9F80 temporary;
            Pair_006D9F80 next = *FUN_0075F5C0(&temporary, &unknown_C8,
                                                   &unknown_D0, unknown_DC);
            if (unknown_DC >= 1.0) {
                unknown_D0 = Pair_006D9F80(0, 0);
                unknown_C8 = Pair_006D9F80(0, 0);
                unknown_D8 = 0.0f;
                unknown_DC = 0.0f;
            }
            Pair_006D9F80 adjusted = next;
            int x, y;
            if (FUN_006D8640(&adjusted) && !DAT_00A8ED6B) {
                x = adjusted.unknown_00;
                y = adjusted.unknown_04;
            } else {
                x = next.unknown_00;
                y = next.unknown_04;
            }
            unknown_D64.unknown_00 = unknown_D74.unknown_00 = x;
            unknown_D64.unknown_04 = unknown_D74.unknown_04 = y;
            FUN_006D8B30();
            unknown_D7D = true;
            moved = true;
        }
        if (unknown_DA4.GetTimeLeft() == 0) {
            unknown_DA4 = ScenarioElapsedTimer(Rules->unknown_050);
            ++unknown_DA0;
        }
    }
    unknown_A8 = CurrentFrame;
    if (!(unknown_D74 == unknown_D64) && !moved) {
        Pair_006D9F80 next = unknown_D74;
        Pair_006D9F80 adjusted = next;
        int x, y;
        if (FUN_006D8640(&adjusted) && !DAT_00A8ED6B) {
            x = adjusted.unknown_00;
            y = adjusted.unknown_04;
        } else {
            x = next.unknown_00;
            y = next.unknown_04;
        }
        unknown_D64.unknown_00 = unknown_D74.unknown_00 = x;
        unknown_D64.unknown_04 = unknown_D74.unknown_04 = y;
        FUN_006D8B30();
        unknown_D7D = true;
    }
}

#include "../../_layout/rectangle_operations.h"
extern DynamicVectorClass<DirtyAreaStruct> DAT_00B0CE78; // GLOBAL: GAMEMD 0xB0CE78 (decl; reloc)
GG_STATIC_ASSERT(sizeof(RectangleStruct) == 16);
GG_STATIC_ASSERT(offsetof(RectangleStruct, X) == 0);
GG_STATIC_ASSERT(offsetof(RectangleStruct, Y) == 4);
GG_STATIC_ASSERT(offsetof(RectangleStruct, Width) == 8);
GG_STATIC_ASSERT(offsetof(RectangleStruct, Height) == 12);
GG_STATIC_ASSERT(sizeof(DirtyAreaStruct) == 20);
GG_STATIC_ASSERT(offsetof(DirtyAreaStruct, Rect) == 0);
GG_STATIC_ASSERT(offsetof(DirtyAreaStruct, unknown_10) == 16);
typedef DynamicVectorClass<DirtyAreaStruct> TacticalDirtyVector;
GG_STATIC_ASSERT(sizeof(TacticalDirtyVector) == 24);
GG_STATIC_ASSERT(offsetof(TacticalDirtyVector, Items) == 4);
GG_STATIC_ASSERT(offsetof(TacticalDirtyVector, Capacity) == 8);
GG_STATIC_ASSERT(offsetof(TacticalDirtyVector, IsAllocated) == 13);
GG_STATIC_ASSERT(offsetof(TacticalDirtyVector, Count) == 16);
GG_STATIC_ASSERT(offsetof(TacticalDirtyVector, CapacityIncrement) == 20);


// FUNCTION: GAMEMD 0x6D2790
void Tactical::FUN_006D2790(RectangleStruct requested, bool flag)
{
    int best = -1;
    int bestArea = 0x7FFFFFFF;
    for (int index = 0; index < DAT_00B0CE78.Count; ++index) {
        RectangleStruct current = { DAT_00B0CE78.Items[index].Rect.X,
            DAT_00B0CE78.Items[index].Rect.Y, DAT_00B0CE78.Items[index].Rect.Width,
            DAT_00B0CE78.Items[index].Rect.Height };
        RectangleStruct temporary;
        RectangleStruct overlap = *FUN_00421B60(&temporary, &current, &requested, 0, 0);
        RectangleStruct united;
        if (current.Width <= 0 || current.Height <= 0) {
            united = requested;
        } else if (requested.Width <= 0 || requested.Height <= 0) {
            united = current;
        } else {
            united = current;
            if (united.X > requested.X) {
                united.Width += united.X - requested.X;
                united.X = requested.X;
            }
            if (united.Y > requested.Y) {
                united.Height += united.Y - requested.Y;
                united.Y = requested.Y;
            }
            if (united.X + united.Width < requested.X + requested.Width)
                united.Width = requested.Width - united.X + 1 + requested.X;
            if (united.Y + united.Height < requested.Y + requested.Height)
                united.Height = requested.Y - united.Y + 1 + requested.Height;
        }
        if (overlap.Width > 0 && overlap.Height > 0) {
            if (overlap.X == requested.X && overlap.Y == requested.Y &&
                overlap.Width == requested.Width && overlap.Height == requested.Height) {
                if (!flag || DAT_00B0CE78.Items[index].unknown_10)
                    return;
            } else if (overlap.X == current.X && overlap.Y == current.Y &&
                       overlap.Width == current.Width && overlap.Height == current.Height) {
                if (flag || !DAT_00B0CE78.Items[index].unknown_10) {
                    DAT_00B0CE78.Delete(index);
                    --index;
                }
            } else {
                int area = united.Width * united.Height;
                if (area < requested.Width * requested.Height + current.Height * current.Width &&
                    area < bestArea) {
                    best = index;
                    bestArea = area;
                }
            }
        }
    }
    if (best != -1) {
        // Native leaves a previously recorded best index unchanged when an
        // earlier vector element is deleted. Preserve that observed behavior.
        bool combinedFlag = flag || DAT_00B0CE78.Items[best].unknown_10;
        RectangleStruct temporary;
        DirtyAreaStruct merged;
        RectangleStruct selected = { DAT_00B0CE78.Items[best].Rect.X,
            DAT_00B0CE78.Items[best].Rect.Y, DAT_00B0CE78.Items[best].Rect.Width,
            DAT_00B0CE78.Items[best].Rect.Height };
        RectangleStruct result = *FUN_00487F40(&temporary, &requested, &selected);
        merged.Rect.X = result.X;
        merged.Rect.Y = result.Y;
        merged.Rect.Width = result.Width;
        merged.Rect.Height = result.Height;
        merged.unknown_10 = combinedFlag;
        DAT_00B0CE78.Items[best] = merged;
        return;
    }
    DirtyAreaStruct appended;
    appended.Rect.X = requested.X;
    appended.Rect.Y = requested.Y;
    appended.Rect.Width = requested.Width;
    appended.Rect.Height = requested.Height;
    appended.unknown_10 = flag;
    DAT_00B0CE78.AddItem(appended);
}

// FUNCTION: GAMEMD 0x6D2B50
// Empty function that pops its stack arguments.
void __stdcall FUN_006D2B50(int a1, int a2)
{
}

// LIBRARY: GAMEMD 0x7CA489 -- null-terminated 16-bit string copy.
extern "C" unsigned short* __cdecl FUN_007CA489(unsigned short* destination,
                                              const unsigned short* source);

#include "../../_layout/tactical_viewport.h"
#include "../../_layout/cell_class.h"
#include "../../renderer/zbuffer_class_methods.h"
extern void* DAT_00B73550; // GLOBAL: GAMEMD 0xB73550 (decl; reloc)

// FUNCTION: GAMEMD 0x6D2B60
void Tactical::FUN_006D2B60(bool fullScreen, int dx, int dy,
                           const RectangleStruct* clip)
{
    if (!fullScreen) {
        int count = DAT_00B0CE78.Count;
        if (count != 0) {
            for (int index = count - 1; index >= 0; --index) {
                RectangleStruct moved;
                moved.X = DAT_00B0CE78.Items[index].Rect.X;
                moved.Y = DAT_00B0CE78.Items[index].Rect.Y;
                moved.Width = DAT_00B0CE78.Items[index].Rect.Width;
                moved.Height = DAT_00B0CE78.Items[index].Rect.Height;
                moved.X += dx;
                moved.Y += dy;

                // Both Point2D values contain the same viewport-origin read.
                // Native calls487F20 rather than substituting a constant zero.
                Point2D viewportOrigin(Viewport_00886FA0.X, Viewport_00886FA0.Y);
                Point2D windowOrigin = viewportOrigin;
                int width = Viewport_00886FA0.Width;
                int height = Viewport_00886FA0.Height;
                Point2D relative = windowOrigin - viewportOrigin;
                RectangleStruct builder;
                RectangleStruct bounds = *builder.FromPointSize(&relative, width, height);
                RectangleStruct temporary;
                moved = *FUN_00421B60(&temporary, &bounds, &moved, 0, 0);

                // Reload Items after callbacks. Write only first16bytes;
                // existing dirty flag+10 and padding are left untouched here.
                DAT_00B0CE78.Items[index].Rect.X = moved.X;
                DAT_00B0CE78.Items[index].Rect.Y = moved.Y;
                DAT_00B0CE78.Items[index].Rect.Width = moved.Width;
                DAT_00B0CE78.Items[index].Rect.Height = moved.Height;
                if (moved.Width <= 0 || moved.Height <= 0) {
                    if (index < DAT_00B0CE78.Count) {
                        --DAT_00B0CE78.Count;
                        // Native REP5DWORD copies the complete20-byte record,
                        // including flag/padding; emitted assignment needs QA.
                        for (int next = index; next < DAT_00B0CE78.Count; ++next)
                            DAT_00B0CE78.Items[next] = DAT_00B0CE78.Items[next + 1];
                    }
                } else {
                    ZBuffer_00887644->FUN_007BCFB0(moved);
                }
            }
        }
    }
    if (unknown_E0 > 0 && !fullScreen) {
        for (int index = 0; index < unknown_E0; ++index) {
            CellClass* cell = unknown_E4[index];
            CoordStruct temporary;
            CoordStruct coordinate = *cell->GetCellCoords(&temporary);
            coordinate.Z = 0;
            Point2D projected = CoordsToScreen(&coordinate);
            Point2D location(projected.X - unknown_B0.unknown_00 - 30 + Viewport_00886FA0.X,
                             projected.Y - unknown_B0.unknown_04 - 15 + Viewport_00886FA0.Y);
            if (DAT_00B73550 != 0) {
                CellClass* currentCell = unknown_E4[index];
                currentCell->FUN_00480180(&location, clip);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x6D2DE0
void Tactical::FUN_006D2DE0(const RectangleStruct* first,
                           const RectangleStruct* second, bool fullScreen)
{
    if (fullScreen) {
        FUN_006D7560(&Viewport_00886FA0, &Viewport_00886FA0);
    } else {
        if (first->Width > 0 && first->Height > 0)
            FUN_006D7560(first, first);
        if (second->Width > 0 && second->Height > 0)
            FUN_006D7560(second, second);
    }
    if (unknown_E0 > 0 && !fullScreen) {
        for (int index = 0; index < unknown_E0; ++index) {
            // The writer6DA949 stores CellClass pointers; MapCoords is at+24.
            CellClass* cell = unknown_E4[index];
            int x = (cell->MapCoords.X * 256 + 128) / 256 * 256;
            int y = (cell->MapCoords.Y * 256 + 128) / 256 * 256;
            CoordStruct coordinate;
            coordinate.FUN_0041C230(x, y, 0);
            CoordStruct copiedCoordinate = coordinate;
            Point2D projected = CoordsToScreen(&copiedCoordinate);
            RectangleStruct view;
            view.X = projected.X - unknown_B0.unknown_00 - 30;
            view.Y = projected.Y - unknown_B0.unknown_04 + Viewport_00886FA0.Y;
            view.Width = 60;
            view.Height = 30;
            // Clipping is eligibility only: render receives original view,
            // not the clipped rectangle. Reload the array entry after callback.
            RectangleStruct temporary;
            RectangleStruct clipped = *FUN_00421B60(&temporary, &Viewport_00886FA0,
                                                       &view, 0, 0);
            if (clipped.Width > 0 && clipped.Height > 0) {
                CellStruct cellCoordinate =
                    unknown_E4[index]->MapCoords;
                FUN_006D7F20(&cellCoordinate, &view);
            }
        }
    }
    // Count is captured once; array base and viewport Y reload after every
    // callback. No erasure, flag filter or clear occurs in these two functions.
    int count = DAT_00B0CE78.Count;
    if (count != 0 && !fullScreen) {
        for (int index = count - 1; index >= 0; --index) {
            RectangleStruct view;
            view.X = DAT_00B0CE78.Items[index].Rect.X;
            view.Y = DAT_00B0CE78.Items[index].Rect.Y + Viewport_00886FA0.Y;
            view.Width = DAT_00B0CE78.Items[index].Rect.Width;
            view.Height = DAT_00B0CE78.Items[index].Rect.Height;
            RectangleStruct temporary;
            view = *FUN_00421B60(&temporary, &Viewport_00886FA0, &view, 0, 0);
            if (view.Width > 0 && view.Height > 0)
                FUN_006D7560(&view, &view);
        }
    }
}

// FUNCTION: GAMEMD 0x6D3040
void Tactical::FUN_006D3040(const RectangleStruct* first,
                           const RectangleStruct* second, bool fullScreen)
{
    if (fullScreen) {
        FUN_006D7C00(&Viewport_00886FA0, &Viewport_00886FA0);
    } else {
        if (first->Width > 0 && first->Height > 0)
            FUN_006D7C00(first, first);
        if (second->Width > 0 && second->Height > 0)
            FUN_006D7C00(second, second);
    }
    if (unknown_E0 > 0 && !fullScreen) {
        for (int index = 0; index < unknown_E0; ++index) {
            // The writer6DA949 stores CellClass pointers; MapCoords is at+24.
            CellClass* cell = unknown_E4[index];
            int x = (cell->MapCoords.X * 256 + 128) / 256 * 256;
            int y = (cell->MapCoords.Y * 256 + 128) / 256 * 256;
            CoordStruct coordinate;
            coordinate.FUN_0041C230(x, y, 0);
            CoordStruct copiedCoordinate = coordinate;
            Point2D projected = CoordsToScreen(&copiedCoordinate);
            RectangleStruct view;
            view.X = projected.X - unknown_B0.unknown_00 - 30;
            view.Y = projected.Y - unknown_B0.unknown_04 + Viewport_00886FA0.Y;
            view.Width = 60;
            view.Height = 30;
            // Native keeps projected rectangle separate from the clipped
            // result, then passes the same clipped pointer in BOTH positions.
            RectangleStruct temporary;
            RectangleStruct clipped = *FUN_00421B60(&temporary, &Viewport_00886FA0,
                                                       &view, 0, 0);
            if (clipped.Width > 0 && clipped.Height > 0)
                FUN_006D7C00(&clipped, &clipped);
        }
    }
    // Count is captured once; array base and viewport Y reload after every
    // callback. No erasure, flag filter or clear occurs in these two functions.
    int count = DAT_00B0CE78.Count;
    if (count != 0) {
        for (int index = count - 1; index >= 0; --index) {
            RectangleStruct view;
            view.X = DAT_00B0CE78.Items[index].Rect.X;
            view.Y = DAT_00B0CE78.Items[index].Rect.Y + Viewport_00886FA0.Y;
            view.Width = DAT_00B0CE78.Items[index].Rect.Width;
            view.Height = DAT_00B0CE78.Items[index].Rect.Height;
            RectangleStruct temporary;
            view = *FUN_00421B60(&temporary, &Viewport_00886FA0, &view, 0, 0);
            if (view.Width > 0 && view.Height > 0)
                FUN_006D7C00(&view, &view);
        }
    }
}

#include "../../renderer/rectangle_dispatch.h"

// FUNCTION: GAMEMD 0x6D3290
void Tactical::FUN_006D3290(const RectangleStruct* first,
                           const RectangleStruct* second, bool fullScreen)
{
    if (fullScreen) {
        FUN_006D6D10(&Viewport_00886FA0);
    } else {
        if (first->Width > 0 && first->Height > 0)
            FUN_006D6D10(first);
        if (second->Width > 0 && second->Height > 0)
            FUN_006D6D10(second);
    }
    if (unknown_E0 > 0 && !fullScreen) {
        for (int index = 0; index < unknown_E0; ++index) {
            // The writer6DA949 stores CellClass pointers; MapCoords is at+24.
            CellClass* cell = unknown_E4[index];
            int x = (cell->MapCoords.X * 256 + 128) / 256 * 256;
            int y = (cell->MapCoords.Y * 256 + 128) / 256 * 256;
            CoordStruct coordinate = { x, y, 0 };
            Point2D projected = CoordsToScreen(&coordinate);
            RectangleStruct view;
            view.X = projected.X - unknown_B0.unknown_00 - 30;
            view.Y = projected.Y - unknown_B0.unknown_04 + Viewport_00886FA0.Y;
            view.Width = 60;
            view.Height = 30;
            FUN_006D6D10(&view);
        }
    }
    // Count is captured once; array base and viewport Y reload after every
    // callback. No erasure, flag filter or clear occurs in these two functions.
    int count = DAT_00B0CE78.Count;
    if (count != 0) {
        for (int index = count - 1; index >= 0; --index) {
            RectangleStruct view;
            view.X = DAT_00B0CE78.Items[index].Rect.X;
            view.Y = DAT_00B0CE78.Items[index].Rect.Y + Viewport_00886FA0.Y;
            view.Width = DAT_00B0CE78.Items[index].Rect.Width;
            view.Height = DAT_00B0CE78.Items[index].Rect.Height;
            RectangleStruct temporary;
            view = *FUN_00421B60(&temporary, &Viewport_00886FA0, &view, 0, 0);
            if (view.Width > 0 && view.Height > 0)
                FUN_006D6D10(&view);
        }
    }
}

// FUNCTION: GAMEMD 0x6D3470
void Tactical::FUN_006D3470(const RectangleStruct* first,
                           const RectangleStruct* second, bool fullScreen)
{
    if (fullScreen) {
        FUN_004D1890(&Viewport_00886FA0);
    } else {
        if (first->Width > 0 && first->Height > 0)
            FUN_004D1890(first);
        if (second->Width > 0 && second->Height > 0)
            FUN_004D1890(second);
    }
    if (!fullScreen) {
        for (int index = 0; index < unknown_E0; ++index) {
            // The writer6DA949 stores CellClass pointers; MapCoords is at+24.
            CellClass* cell = unknown_E4[index];
            int x = (cell->MapCoords.X * 256 + 128) / 256 * 256;
            int y = (cell->MapCoords.Y * 256 + 128) / 256 * 256;
            CoordStruct coordinate;
            coordinate.FUN_0041C230(x, y, 0);
            CoordStruct copiedCoordinate = coordinate;
            Point2D projected = CoordsToScreen(&copiedCoordinate);
            RectangleStruct view;
            view.X = projected.X - unknown_B0.unknown_00 - 30;
            view.Y = projected.Y - unknown_B0.unknown_04 + Viewport_00886FA0.Y;
            view.Width = 60;
            view.Height = 30;
            FUN_004D1890(&view);
        }
    }
    // Count is captured once; array base and viewport Y reload after every
    // callback. No erasure, flag filter or clear occurs in these two functions.
    int count = DAT_00B0CE78.Count;
    if (count != 0) {
        for (int index = count - 1; index >= 0; --index) {
            RectangleStruct view;
            view.X = DAT_00B0CE78.Items[index].Rect.X;
            view.Y = DAT_00B0CE78.Items[index].Rect.Y + Viewport_00886FA0.Y;
            view.Width = DAT_00B0CE78.Items[index].Rect.Width;
            view.Height = DAT_00B0CE78.Items[index].Rect.Height;
            RectangleStruct temporary;
            view = *FUN_00421B60(&temporary, &Viewport_00886FA0, &view, 0, 0);
            if (view.Width > 0 && view.Height > 0)
                FUN_004D1890(&view);
        }
    }
}

#include "../../renderer/drawing.h"

// FUNCTION: GAMEMD 0x6D3660
void Tactical::FUN_006D3660(const RectangleStruct* first,
                           const RectangleStruct* second,
                           const RectangleStruct* clip, bool fullScreen)
{
    if (unknown_E0 > 0 && !fullScreen) {
        for (int index = 0; index < unknown_E0; ++index) {
            CellClass* cell = unknown_E4[index];
            CoordStruct temporary;
            CoordStruct coordinate = *cell->GetCellCoords(&temporary);
            coordinate.Z = 0;
            Point2D projected = CoordsToScreen(&coordinate);
            Point2D location(projected.X - unknown_B0.unknown_00 - 30 + Viewport_00886FA0.X,
                             projected.Y - unknown_B0.unknown_04 - 15 + Viewport_00886FA0.Y);
            if (DAT_00B73550 != 0) {
                // Native reloads array entry after480A30/projection callbacks.
                CellClass* currentCell = unknown_E4[index];
                currentCell->FUN_004801F0(&location, clip);
            }
            // ECX=&location,EDX=clip; call occurs whether or not B73550 is on.
            FUN_00420F40(&location, clip);
        }
    }
    if (fullScreen)
        FUN_006D71E0(&Viewport_00886FA0);
    // Native reads dimensions even in full mode, then tests fullScreen.
    if (first->Width > 0 && first->Height > 0 && !fullScreen)
        FUN_006D71E0(first);
    if (second->Width > 0 && second->Height > 0 && !fullScreen)
        FUN_006D71E0(second);

    // Forward scan with live count, including full mode. Items base reloaded
    // after intersection, and after render callbacks, rather than snapshotted.
    for (int index = 0; index < DAT_00B0CE78.Count; ++index) {
        RectangleStruct view;
        view.X = DAT_00B0CE78.Items[index].Rect.X + Viewport_00886FA0.X;
        view.Y = DAT_00B0CE78.Items[index].Rect.Y + Viewport_00886FA0.Y;
        view.Width = DAT_00B0CE78.Items[index].Rect.Width;
        view.Height = DAT_00B0CE78.Items[index].Rect.Height;
        RectangleStruct temporary;
        RectangleStruct clipped = *FUN_00421B60(&temporary, &view, clip, 0, 0);
        if (DAT_00B0CE78.Items[index].unknown_10 != 0) {
            // No positive-size test: native invokes both calls even if the
            // intersection is empty.411330 consumes a16-byte byvalue XYWH.
            ABuffer_0087E8A4->FUN_00411330(clipped);
            FUN_006D71E0(&clipped);
        }
    }
}

// FUNCTION: GAMEMD 0x6D3870
void Tactical::FUN_006D3870(const RectangleStruct* first, const RectangleStruct* second,
                          bool fullScreen)
{
    for (int index = 0; index < unknown_E0; ++index) {
        CellClass* cell = unknown_E4[index];
        int x = (cell->MapCoords.X * 256 + 128) / 256 * 256;
        int y = (cell->MapCoords.Y * 256 + 128) / 256 * 256;
        CoordStruct coordinate;
        coordinate.FUN_0041C230(x, y, 0);
        CoordStruct copiedCoordinate = coordinate;
        Point2D projected = CoordsToScreen(&copiedCoordinate);
        RectangleStruct view;
        view.X = projected.X - unknown_B0.unknown_00 - 30;
        view.Y = projected.Y - unknown_B0.unknown_04 + Viewport_00886FA0.Y;
        view.Width = 60;
        view.Height = 30;
        RectangleStruct clip = view;
        FUN_006D9920(true, &view, &clip);
    }
    // Native captures count once, then reloads the array base after callbacks.
    int dirtyCount = DAT_00B0CE78.Count;
    if (dirtyCount != 0) {
        for (int dirtyIndex = dirtyCount - 1; dirtyIndex >= 0; --dirtyIndex) {
            RectangleStruct view;
            view.X = DAT_00B0CE78.Items[dirtyIndex].Rect.X;
            view.Y = DAT_00B0CE78.Items[dirtyIndex].Rect.Y + Viewport_00886FA0.Y;
            view.Width = DAT_00B0CE78.Items[dirtyIndex].Rect.Width;
            view.Height = DAT_00B0CE78.Items[dirtyIndex].Rect.Height;
            RectangleStruct temporary;
            view = *FUN_00421B60(&temporary, &Viewport_00886FA0, &view, 0, 0);
            if (view.Width > 0 && view.Height > 0) {
                RectangleStruct clip = view;
                FUN_006D9920(true, &view, &clip);
            }
        }
    }
    if (fullScreen) {
        FUN_006D9920(true, &Viewport_00886FA0, &Viewport_00886FA0);
        return;
    }
    if (first->Width > 0 && first->Height > 0)
        FUN_006D9920(true, first, first);
    if (second->Width > 0 && second->Height > 0)
        FUN_006D9920(true, second, second);
}

// FUNCTION: GAMEMD 0x6D3AC0
void Tactical::FUN_006D3AC0(const RectangleStruct* first, const RectangleStruct* second,
                          bool fullScreen)
{
    for (int index = 0; index < unknown_E0; ++index) {
        CellClass* cell = unknown_E4[index];
        int x = (cell->MapCoords.X * 256 + 128) / 256 * 256;
        int y = (cell->MapCoords.Y * 256 + 128) / 256 * 256;
        CoordStruct coordinate;
        coordinate.FUN_0041C230(x, y, 0);
        CoordStruct copiedCoordinate = coordinate;
        Point2D projected = CoordsToScreen(&copiedCoordinate);
        RectangleStruct view;
        view.X = projected.X - unknown_B0.unknown_00 - 30;
        view.Y = projected.Y - unknown_B0.unknown_04 + Viewport_00886FA0.Y;
        view.Width = 60;
        view.Height = 30;
        RectangleStruct clip = view;
        FUN_006D97D0(true, &view, &clip);
    }
    // Native captures count once, then reloads the array base after callbacks.
    int dirtyCount = DAT_00B0CE78.Count;
    if (dirtyCount != 0) {
        for (int dirtyIndex = dirtyCount - 1; dirtyIndex >= 0; --dirtyIndex) {
            RectangleStruct view;
            view.X = DAT_00B0CE78.Items[dirtyIndex].Rect.X;
            view.Y = DAT_00B0CE78.Items[dirtyIndex].Rect.Y + Viewport_00886FA0.Y;
            view.Width = DAT_00B0CE78.Items[dirtyIndex].Rect.Width;
            view.Height = DAT_00B0CE78.Items[dirtyIndex].Rect.Height;
            RectangleStruct temporary;
            view = *FUN_00421B60(&temporary, &Viewport_00886FA0, &view, 0, 0);
            if (view.Width > 0 && view.Height > 0) {
                RectangleStruct clip = view;
                FUN_006D97D0(true, &view, &clip);
            }
        }
    }
    if (fullScreen) {
        FUN_006D97D0(true, &Viewport_00886FA0, &Viewport_00886FA0);
        return;
    }
    if (first->Width > 0 && first->Height > 0)
        FUN_006D97D0(true, first, first);
    if (second->Width > 0 && second->Height > 0)
        FUN_006D97D0(true, second, second);
}


#include "../../_layout/house_class.h"
#include "../../_layout/capture_manager_class.h"
#include "../../_layout/super_class.h"
#include "../../_layout/session_class.h"
#include "../../combat/airstrike_class_methods.h"
#include "../../combat/super_weapon_type_class_methods.h"
#include "../../renderer/color_scheme_find_methods.h"
#include "../../core/scenario_class_methods.h"
#include "../../network/beacon_manager_class.h"
#include <mmsystem.h>

// GLOBAL: GAMEMD 0xB0CE28
extern int DAT_00B0CE28;
// GLOBAL: GAMEMD 0x887314
extern Surface* DAT_00887314;
// GLOBAL: GAMEMD 0x88731C
extern Surface* DAT_0088731C;
// GLOBAL: GAMEMD 0x8872FC
extern Surface* DAT_008872FC;
// GLOBAL: GAMEMD 0xB0E63C
extern bool DAT_00B0E63C;
// GLOBAL: GAMEMD 0xA8EC78
extern DynamicVectorClass<TechnoClass*> DAT_00A8EC78;
// GLOBAL: GAMEMD 0xA83D50
extern DynamicVectorClass<SuperClass*> DAT_00A83D50;
// GLOBAL: GAMEMD 0x89C3B0
extern BeaconManagerClass BeaconManagerInstance;
// GLOBAL: GAMEMD 0xA8B230
extern ScenarioClass* ScenarioInstance;
// GLOBAL: GAMEMD 0xA83D4C
extern HouseClass* CurrentPlayer;
// GLOBAL: GAMEMD 0xA8022C
extern HouseClass** HouseClass_ArrayItems;
// GLOBAL: GAMEMD 0xA80238
extern int HouseClass_ArrayCount;
// GLOBAL: GAMEMD 0x843108
extern bool DAT_00843108;
// GLOBAL: GAMEMD 0x842900
extern int DAT_00842900;
// GLOBAL: GAMEMD 0x7ECE60
extern const double DAT_007ECE60;
// GLOBAL: GAMEMD 0x7F43B0
extern const double DAT_007F43B0;
// Declaration: STRING GAMEMD 0x842A50
extern const char STR_00842A50[];
// Declaration: STRING GAMEMD 0x842A64
extern const char STR_00842A64[];
// Declaration: GAMEMD 0x006D4B50 (decl; reloc)
void FUN_006D4B50(int row, ColorScheme* color, int seconds, const wchar_t* label, unsigned int* blinkClock, unsigned char* blinkState);
// Declaration: GAMEMD 0x00705860 (decl; reloc)
void __stdcall FUN_00705860(CoordStruct start, CoordStruct end);
// Declaration: GAMEMD 0x004CACB0 (decl; reloc)
extern "C" double __cdecl FUN_004CACB0(double value);
// Declaration: GAMEMD 0x004CAD00 (decl; reloc)
extern "C" double __cdecl FUN_004CAD00(double value);
// Declaration: GAMEMD 0x00734E60 (decl; reloc)
const wchar_t* FUN_00734E60(const char*, int*, const char*, int);
// Declaration: GAMEMD 0x0053D850 (decl; reloc)
void FUN_0053D850();
// Declaration: GAMEMD 0x005FFFA0 (decl; reloc)
void FUN_005FFFA0();
// Declaration: GAMEMD 0x00550240 (decl; reloc)
void FUN_00550240();
// Declaration: GAMEMD 0x004C2830 (decl; reloc)
void FUN_004C2830();
// Declaration: GAMEMD 0x00556D40 (decl; reloc)
void FUN_00556D40();
// Declaration: GAMEMD 0x006591B0 (decl; reloc)
void FUN_006591B0();
// Declaration: GAMEMD 0x00637AA0 (decl; reloc)
char FUN_00637AA0();
// Declaration: GAMEMD 0x0063B0A0 (decl; reloc)
void FUN_0063B0A0();
// Declaration: GAMEMD 0x0063B150 (decl; reloc)
void FUN_0063B150();
// Declaration: GAMEMD 0x0063B2F0 (decl; reloc)
void FUN_0063B2F0();

GG_STATIC_ASSERT(offsetof(TechnoClass, CaptureManager) == 0x2BC);
GG_STATIC_ASSERT(offsetof(TechnoClass, Airstrike) == 0x294);
GG_STATIC_ASSERT(offsetof(HouseClass, PowerBlackoutTimer) == 0x2A4);
GG_STATIC_ASSERT(offsetof(ObjectClass, IsSelected) == 0x83);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<TechnoClass*>) == 0x18);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<TechnoClass*>, Items) == 4);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<TechnoClass*>, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<SuperClass*>) == 0x18);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<SuperClass*>, Items) == 4);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<SuperClass*>, Count) == 0x10);

// FUNCTION: GAMEMD 0x6D3D10
void Tactical::FUN_006D3D10(Surface* surface, bool full, int mode)
{
    unknown_DB0 = 0;
    // Native reserves/stores a complete16-byte rectangle argument, RET16.
    bool buildingChanged = FUN_006D9B50(Viewport_00886FA0);
    int dx = unknown_B8.unknown_00 - unknown_B0.unknown_00;
    int dy = unknown_B8.unknown_04 - unknown_B0.unknown_04;
    if (mode == 0) {
        int absX = dx < 0 ? -dx : dx;
        int absY = dy < 0 ? -dy : dy;
        if (absX >= Viewport_00886FA0.Width || absY >= Viewport_00886FA0.Height) {
            full = true;
            DAT_00B0E63C = true;
        } else {
            DAT_00B0E63C = false;
        }
    } else if (DAT_00B0E63C) {
        full = true;
    }
    if (full) { dx = 0; dy = 0; }

    // These nested tests retain both distinct native early exits. D7C is
    // not an unconditional redraw request when buildingChanged is false.
    bool update = true;
    if (!full && !buildingChanged) {
        if (!unknown_D7C && DAT_00B0CE78.Count == 0 && !unknown_D7D &&
            unknown_D64 == unknown_D6C) {
            update = false;
        } else if (!unknown_D7D && DAT_00B0CE78.Count == 0 && unknown_B0 == unknown_B8) {
            update = false;
        }
    }
    if (mode != 2 && update) {
        int absX = dx < 0 ? -dx : dx;
        int absY = dy < 0 ? -dy : dy;
        RectangleStruct source = { DAT_00B0CE28 + (dx < 0 ? -dx : 0),
                                   DAT_00B0CE2C + (dy < 0 ? -dy : 0),
                                   DAT_00B0CE30 - absX, DAT_00B0CE34 - absY };
        RectangleStruct destination = { DAT_00B0CE28 + (dx > 0 ? dx : 0),
                                        DAT_00B0CE2C + (dy > 0 ? dy : 0),
                                        source.Width, source.Height };
        if (dx == 0 && dy == 0) {
            if (full && (mode == 0 || mode == 3)) {
                ZBuffer_00887644->Fill(0xFFFF);
                ABuffer_0087E8A4->Fill(0x7F);
            }
        } else {
            if (mode == 0 || mode == 3)
                DAT_0088731C->CopyFromPart(&destination, DAT_008872FC, &source, false, true);
            if (mode == 0 || mode == 3)
                ZBuffer_00887644->FUN_007BCB50(-dx, -dy, 0xFFFF); // dependency: existing buffer owner
            if (mode == 0 || mode == 3)
                ABuffer_0087E8A4->FUN_00410ED0(-dx, -dy, 0x7F); // dependency: existing buffer owner
            if (mode == 0 || mode == 3) {
                Surface* previous = DAT_0088731C;
                DAT_0088731C = DAT_008872FC;
                DAT_008872FC = previous;
                surface = DAT_0088731C;
                DAT_00887314 = surface;
            }
        }
        // Native mode0 returns here, before synchronizing B8/D6C below.
        if (mode == 0) return;
        if (!DAT_00A8ED6B) {
            RectangleStruct expanded = { Viewport_00886FA0.X - 64, Viewport_00886FA0.Y - 64,
                                         Viewport_00886FA0.Width + 128, Viewport_00886FA0.Height + 128 };
            FUN_006D9A50(expanded); // same16-byte by-value rectangle proposal
        }
        Surface* previous = DAT_00887314;
        DAT_00887314 = DAT_008872FC;
        DAT_008872FC->Lock(Point2D(0, 0));
        if (mode == 1 || mode == 3) {
            bool right = unknown_B0.unknown_00 < unknown_B8.unknown_00;
            bool left = unknown_B8.unknown_00 < unknown_B0.unknown_00;
            bool down = unknown_B0.unknown_04 < unknown_B8.unknown_04;
            bool up = unknown_B8.unknown_04 < unknown_B0.unknown_04;
            RectangleStruct stripLeft = { Viewport_00886FA0.X, Viewport_00886FA0.Y, absX, Viewport_00886FA0.Height };
            RectangleStruct stripRight = { Viewport_00886FA0.X - absX + Viewport_00886FA0.Width,
                                           Viewport_00886FA0.Y, absX, Viewport_00886FA0.Height };
            RectangleStruct clippedLeft, clippedRight;
            FUN_00421B60(&clippedLeft, &stripLeft, &Viewport_00886FA0, 0, 0);
            FUN_00421B60(&clippedRight, &stripRight, &Viewport_00886FA0, 0, 0);
            int horizontalX = Viewport_00886FA0.X + (right ? absX : 0);
            int horizontalWidth = Viewport_00886FA0.Width - ((right || left) ? absX : 0);
            RectangleStruct stripTop = { horizontalX, Viewport_00886FA0.Y, horizontalWidth, absY };
            RectangleStruct stripBottom = { horizontalX, Viewport_00886FA0.Y - absY + Viewport_00886FA0.Height,
                                            horizontalWidth, absY };
            RectangleStruct clippedTop, clippedBottom;
            FUN_00421B60(&clippedTop, &stripTop, &Viewport_00886FA0, 0, 0);
            FUN_00421B60(&clippedBottom, &stripBottom, &Viewport_00886FA0, 0, 0);
            RectangleStruct overlap = { Viewport_00886FA0.X + (right ? absX : 0),
                                        Viewport_00886FA0.Y + (down ? absY : 0),
                                        Viewport_00886FA0.Width - absX, Viewport_00886FA0.Height - absY };
            RectangleStruct horizontal = { 0, 0, 0, 0 };
            RectangleStruct vertical = { 0, 0, 0, 0 };
            if (right) horizontal = clippedLeft;
            else if (left) horizontal = clippedRight;
            if (down) vertical = clippedTop;
            else if (up) vertical = clippedBottom;
            // Native dispatch order6D4471..6D44F7.
            FUN_006D2B60(full, dx, dy, &overlap);
            FUN_006D3660(&horizontal, &vertical, &overlap, full);
            FUN_006D2DE0(&horizontal, &vertical, full);
            FUN_006D3470(&horizontal, &vertical, full);
            FUN_006D3290(&horizontal, &vertical, full);
            FUN_006D3AC0(&horizontal, &vertical, full);
            FUN_006D3040(&horizontal, &vertical, full);
            FUN_006D3870(&horizontal, &vertical, full);
            // Native reverse removal decrementsCount and shifts remaining
            //20-byte entries; do not replace this with an assumed Clear().
            for (int index = DAT_00B0CE78.Count - 1; index >= 0; --index) {
                if (index < DAT_00B0CE78.Count) {
                    --DAT_00B0CE78.Count;
                    for (int next = index; next < DAT_00B0CE78.Count; ++next)
                        DAT_00B0CE78.Items[next] = DAT_00B0CE78.Items[next + 1];
                }
            }
            DAT_00887314->Unlock();
            DAT_00887314 = previous;
            unknown_E0 = 0;
        }
        // Modes other than1/3 deliberately do not unlock/restore in native.
    }

    unknown_D6C = unknown_D64;
    unknown_B8 = unknown_B0;
    if (mode == 1 || mode == 3) {
        DAT_00887314->CopyFromPart(&Viewport_00886FA0, DAT_008872FC, &Viewport_00886FA0, false, true);
        if (mode == 1) return;
    }
    if (mode != 2 && mode != 3) return;
    // 6D45F2..461A reloads XYWH after the virtual blit callback.
    FUN_006D9CE0(Viewport_00886FA0.X, Viewport_00886FA0.Y, Viewport_00886FA0.Width, Viewport_00886FA0.Height);
    surface->Lock(Point2D(0, 0));
    Surface* previous = DAT_00887314;
    DAT_00887314 = surface;
    FUN_006DAD60(false);
    FUN_006DA9D0(false);
    FUN_006D5030(false);
    FUN_0053D850();
    FUN_006D8DB0(true);
    FUN_005FFFA0();
    FUN_00550240();
    FUN_004C2830();
    FUN_00556D40();
    FUN_006591B0();
    FUN_006DBE20();
    // Native reserves XYWH16, then pushes Surface*: first parameter is Surface*.
    BeaconManagerInstance.Draw(DAT_00887314, Viewport_00886FA0);
    FUN_006DA180();
    FUN_006DAD60(true);
    FUN_006DA9D0(true);
    FUN_006D5030(true);
    bool special = FUN_00637AA0() != 0;
    if (special) { FUN_0063B0A0(); FUN_0063B150(); }
    const int count = DAT_00A8EC78.Count;
    for (int index = 0; index < count; ++index) {
        TechnoClass* techno = DAT_00A8EC78.Items[index];
        if (techno->Owner->IsControlledByCurrentPlayer()) {
            if (special) continue;
            if (techno->IsSelected && DAT_00843108) techno->vf_270(0, 0);
        } else {
            // Address placeholders retain the observed ECX/AL and ECX/RET ABI;
            // original source-level method names remain unrecovered.
            if (techno->FUN_0043B150() && techno && techno->Flags.IsFoot && !techno->InLimbo)
                techno->FUN_004DC340();
            if (special) continue;
        }
        if (techno->Health != 0) {
            CaptureManagerClass* manager = static_cast<CaptureManagerClass*>(techno->CaptureManager);
            if (manager && manager->NeedsToDrawLinks())
                static_cast<CaptureManagerClass*>(techno->CaptureManager)->DrawLinks();
            if (techno->Health != 0 && techno->MindControlledBy) {
                TechnoClass* controller = static_cast<TechnoClass*>(techno->MindControlledBy);
                CaptureManagerClass* controllerManager = static_cast<CaptureManagerClass*>(controller->CaptureManager);
                if (controllerManager && controllerManager->NeedsToDrawLinks())
                    static_cast<CaptureManagerClass*>(static_cast<TechnoClass*>(techno->MindControlledBy)->CaptureManager)->DrawLinks();
            }
        }
        AirstrikeClass* airstrike = static_cast<AirstrikeClass*>(techno->Airstrike);
        if (airstrike && airstrike->unknown_4C == techno) {
            // Native preserves Target across vf11 and timeGetTime callbacks.
            ObjectClass* targetObject = airstrike->Target;
            if (targetObject && targetObject->vf_11() == 6) {
            unsigned int phaseBits = timeGetTime() >> (DAT_00842900 & 31);
            CoordStruct target = targetObject->vf_18();
            double phase = (double)phaseBits;
            CoordStruct endpoint;
            endpoint.Z = (int)(FUN_004CACB0(phase) * DAT_007ECE60 + target.Z);
            endpoint.X = (int)(FUN_004CAD00(phase * DAT_007F43B0) * DAT_007ECE60 + target.X);
            endpoint.Y = target.Y;
            // Slot44 takes four DWORD arguments plus a hidden result.
            // The endpoint is already built when its virtual callback runs.
            FUN_00705860(techno->vf_44(0, 0, 0, 0), endpoint);
            }
        }
    }
    if (special) FUN_0063B2F0();
    // 6D491F..492B passes the live GLOBAL address twice after overlay calls.
    FUN_006D7840(&Viewport_00886FA0, &Viewport_00886FA0);
    DAT_00887314 = previous;
    surface->Unlock();

    int row = 0;
    if (ScenarioInstance->Timer_11E8.IsOn()) {
        FUN_006D4B50(row, ColorSchemeArray.Items[CurrentPlayer->ColorSchemeIndex],
                     ScenarioInstance->Timer_11E8.GetTimeLeft() / 15,
                     ScenarioInstance->unknown_11F4, 0, 0);
        ++row;
    }
    const int superCount = DAT_00A83D50.Count;
    for (int superIndex = 0; superIndex < superCount; ++superIndex) {
        SuperClass* super = DAT_00A83D50.Items[superIndex];
        if (super->IsSuspended && Session_00A8B238.GameMode == 0 &&
            super->RechargeTimer.GetTimeLeft() == super->GetRechargeTime())
            continue;
        // Native6D4A08 reloads Items after GetRechargeTime can alter globals.
        super = DAT_00A83D50.Items[superIndex];
        // Keep the native timer reread after GetRechargeTime's call.
        FUN_006D4B50(row,
                     ColorSchemeArray.Items[static_cast<HouseClass*>(super->Owner)->ColorSchemeIndex],
                     super->RechargeTimer.GetTimeLeft() / 15,
                     static_cast<SuperWeaponTypeClass*>(super->Type)->UIName,
                     &super->BlinkTimer_Low, &super->BlinkState);
        ++row;
    }
    const int houseCount = HouseClass_ArrayCount;
    for (int houseIndex = 0; houseIndex < houseCount; ++houseIndex) {
        HouseClass* house = HouseClass_ArrayItems[houseIndex];
        int remaining = house->PowerBlackoutTimer.GetTimeLeft();
        if (remaining > 0) {
            // ECXstringID, EDX0, stackfile+line; label bytes not invented.
            // 6D4AE1 captures the color ENTRY address before localization;
            // 6D4B06 loads its value after the callback.
            ColorScheme** colorEntry = &ColorSchemeArray.Items[house->ColorSchemeIndex];
            const wchar_t* label = FUN_00734E60(STR_00842A50, 0, STR_00842A64, 0x1C4);
            FUN_006D4B50(row, *colorEntry, remaining / 15, label, 0, 0);
            ++row;
        }
    }
    FUN_006D4E20(unknown_24);
    unknown_D7C = 0;
    unknown_D7D = false;
}

#include "../../renderer/bit_font.h"
#include "../../core/spin_wait_methods.h"
// Declaration: GAMEMD 0x4A60D0; flags in ECX are unused by this retail getter.
BitFont* FUN_004A60D0(int flags);
// Declaration: GAMEMD 0x4A61C0; caller-cleaned hidden result then fixed args.
Point2D __cdecl FUN_004A61C0(const unsigned short* text, Surface* surface,
    RectangleStruct* clip, Point2D* position, ColorScheme* scheme,
    int background, int flags, ...);
// Declaration: LIBRARY GAMEMD 0x7CA564, CRT source out of scope
extern "C" int __cdecl FUN_007CA564(unsigned short*, const unsigned short*, ...);
// Declaration: STRING GAMEMD 0x842A80
extern const unsigned short STR_00842A80[];
// Declaration: STRING GAMEMD 0x842A94
extern const unsigned short STR_00842A94[];
// Declaration: STRING GAMEMD 0x842AB0
extern const unsigned short STR_00842AB0[];
// Declaration: STRING GAMEMD 0x842ACC
extern const unsigned short STR_00842ACC[];
// Declaration: STRING GAMEMD 0x842AD8
extern const unsigned short STR_00842AD8[];

// FUNCTION: GAMEMD 0x6D4B50
void __fastcall FUN_006D4B50(int row, ColorScheme* scheme, int seconds,
                            const unsigned short* label,
                            unsigned int* blinkClock,
                            unsigned char* blinkState)
{
    BitFont* font = FUN_004A60D0(0x4618);
    int hours = (seconds / 60) / 60;
    int minutes = (seconds / 60) % 60;
    int remainder = seconds % 60;
    unsigned short combined[256];
    unsigned short labelText[256];
    unsigned short timeText[256];
    // All three formatting calls exist in each native branch, including the
    // combined string that this function does not subsequently draw.
    if (hours != 0) {
        FUN_007CA564(combined, STR_00842AD8, label, hours, minutes, remainder);
        FUN_007CA564(labelText, STR_00842ACC, label);
        FUN_007CA564(timeText, STR_00842AB0, hours, minutes, remainder);
    } else {
        FUN_007CA564(combined, STR_00842A94, label, minutes, remainder);
        FUN_007CA564(labelText, STR_00842ACC, label);
        FUN_007CA564(timeText, STR_00842A80, minutes, remainder);
    }
    int timeWidth = 0;
    font->FUN_00433CF0(timeText, &timeWidth, 0, Viewport_00886FA0.Width);
    ColorScheme* timeScheme = scheme;
    if (seconds == 0 && blinkClock != 0 && blinkState != 0) {
        // Native compares high then low DWORD unsigned, and samples again
        // when writing a deadline; do not reuse the first clock sample.
        unsigned __int64 now = FUN_004093B0();
        unsigned __int64 deadline = ((unsigned __int64)blinkClock[1] << 32) | blinkClock[0];
        if (deadline <= now) {
            deadline = FUN_004093B0() + 1000;
            blinkClock[0] = (unsigned int)deadline;
            blinkClock[1] = (unsigned int)(deadline >> 32);
            *blinkState = (*blinkState == 0);
        }
        if (*blinkState != 0)
            timeScheme = ColorSchemeArray.Items[5];
    }
    int rowNumber = row + 1;
    Point2D labelPosition(Viewport_00886FA0.Width - timeWidth - 3,
                          Viewport_00886FA0.Height - (font->unknown_1C + 2) * rowNumber);
    // +78 is canonical GetRect(): only its hidden result is popped by the
    // virtual call. Remaining stack arguments belong to the cdecl print.
    RectangleStruct labelClip = DAT_0088731C->GetRect();
    FUN_004A61C0(labelText, DAT_0088731C, &labelClip,
                  &labelPosition, scheme, 0, 0x4618);

    // Native rereads font line advance, viewport dimensions and surface
    // after the first GetRect/print callbacks. Do not retain their values.
    Point2D timePosition(Viewport_00886FA0.Width - 3,
                         Viewport_00886FA0.Height - (font->unknown_1C + 2) * rowNumber);
    RectangleStruct timeClip = DAT_0088731C->GetRect();
    FUN_004A61C0(timeText, DAT_0088731C, &timeClip,
                  &timePosition, timeScheme, 0, 0x4618);
}

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

// GLOBAL: GAMEMD 0xB0CE28
extern int DAT_00B0CE28;

#include "../../ui/shape_header.h"
#include "../../renderer/pixel_shift_view.h"
struct ColorConvert;
// GLOBAL: GAMEMD 0xA8F794 (declaration)
extern ShapeHeader* DAT_00A8F794;
// GLOBAL: GAMEMD 0xA8F798 (declaration)
extern ColorConvert* DAT_00A8F798;
// GLOBAL: GAMEMD 0x89C4D0 (declaration)
extern BitFont* DAT_0089C4D0;
// Declaration: LIBRARY GAMEMD 0x7CA405, CRT wcslen
unsigned int __cdecl FUN_007CA405(const unsigned short* text);
// Declaration: GAMEMD 0x434B90, seven stack words, RET28
int __stdcall FUN_00434B90(BitFont* font, Surface* surface, const unsigned short* text,
    int x, int y, int a, int b);
// Declaration: GAMEMD 0x4AED70, ECXsurface/EDXconvert, RET56
void FUN_004AED70(Surface* surface, ColorConvert* convert, ShapeHeader* shape,
    int frame, Point2D* position, RectangleStruct* clip, int flags,
    int a8, int a9, int a10, int a11, int a12, int a13, int a14, Point2D offset);

// FUNCTION: GAMEMD 0x6D4E20
void Tactical::FUN_006D4E20(const unsigned short* text)
{
    if (DAT_00A8ED6B) return;
    if ((!text || !FUN_007CA405(text)) && unknown_A4 == -1) return;
    if (!DAT_0088731C->unknown_84()) return;

    int frame = unknown_A4;
    if (frame != -1 && DAT_00A8F798 && DAT_00A8F794 &&
        frame < DAT_00A8F794->Frames) {
        Point2D centered((Viewport_00886FA0.Width - DAT_00A8F794->Width) / 2,
                         (Viewport_00886FA0.Height - DAT_00A8F794->Height) / 2);
        Point2D offset(0, 0);
        FUN_004AED70(DAT_0088731C, DAT_00A8F798, DAT_00A8F794,
                      frame, &centered, &Viewport_00886FA0,
                      0, 0, 0, 0, 1000, 0, 0, 0, offset);
        return;
    }
    if (!text || !FUN_007CA405(text)) return;

    BitFont* font = DAT_0089C4D0;
    int viewportX = Viewport_00886FA0.X;
    int viewportY = Viewport_00886FA0.Y;
    int viewportWidth = Viewport_00886FA0.Width;
    int viewportHeight = Viewport_00886FA0.Height;
    int textWidth;
    int textHeight;
    const BTranslucentPixelFormat& pixel = gg_b_translucent_pixel_format;
    unsigned int white = ((255 >> pixel.loss2) << pixel.pos2) |
                         ((255 >> pixel.loss1) << pixel.pos1) |
                         ((255 >> pixel.loss0) << pixel.pos0);
    font->FUN_00433CF0(text, &textWidth, &textHeight, viewportWidth);
    BitFontBounds bounds = {viewportX, viewportY,
                         viewportX + viewportWidth, viewportY + viewportHeight};
    int x = viewportX + (viewportWidth - textWidth) / 2;
    int y = viewportY + (viewportHeight - textHeight) / 2;
    font->FUN_00433C90(1);
    font->FUN_00433CA0(&bounds);
    font->FUN_00433C70((unsigned short)white);
    FUN_00434B90(font, DAT_0088731C, text, x, y, 0, 0);
}


#include "../../_layout/building_class.h"
#include "../../_layout/placement_object.h"
// GLOBAL: GAMEMD 0x89F688 (declaration; native6D576D)
extern CellStruct DAT_0089F688[];
// GLOBAL: GAMEMD 0x87F6C4 (declaration)
extern ColorConvert* DAT_0087F6C4;
// GLOBAL: GAMEMD 0x8A03FC (declaration)
extern ShapeHeader* DisplayPlaceShape_008A03FC;
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, GuardRange) == 0x5B8);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, bools_16A4) + (0x16BE - 0x16A4) == 0x16BE);

// FUNCTION: GAMEMD 0x6D5730
void Tactical::FUN_006D5730(unsigned char mode, CellStruct origin)
{
    for (int direction = 0; direction < 8; direction += 2) {
        CellStruct current = origin;
        int count = 0;
        // Caller6D53E7..6D544B checks placement slot11 == 6.
        BuildingClass* placement = static_cast<BuildingClass*>(PlacementObject_0088098C);
        int range = placement->Type->GuardRange >> 8;
        if (range <= 0)
            continue;
        // Native keeps this entry address and reloads it after draw callbacks.
        const CellStruct& step = DAT_0089F688[direction & 7];
        BuildingClass* building = 0;
        while (count < range) {
            current.X += step.X;
            current.Y += step.Y;
            building = MapInstance.FUN_005657A0(&current)->GetBuilding();
            if (building)
                break; // ANY building ends this scan, even an unsuitable one.
            CellClass* cell = MapInstance.FUN_005657A0(&current);
            if (cell->FUN_0047C550(0) || cell->SlopeIndex > 0 || cell->Passability != 0)
                break;
            ++count;
        }
        if (!building || !building->Type->bools_16A4[0x16BE - 0x16A4] ||
            !building->Owner->IsControlledByCurrentPlayer() || count <= 0)
            continue;
        unsigned int flags = mode ? 0x10606 : 0x20606;
        CellStruct draw;
        draw.X = origin.X + step.X;
        draw.Y = origin.Y + step.Y;
        for (int index = 0; index < count; ++index) {
            int firstLevel = MapInstance.FUN_005657A0(&draw)->Level;
            int firstY = -1 - firstLevel * 15;
            int secondLevel = MapInstance.FUN_005657A0(&draw)->Level;
            int z = -2 - secondLevel * 15;
            CoordStruct center;
            center.X = (draw.X * 256 + 128) / 256 * 256;
            center.Y = (draw.Y * 256 + 128) / 256 * 256;
            center.Z = 0;
            Point2D projected = CoordsToScreen(&center);
            Point2D marker(projected.X - unknown_B0.unknown_00,
                           projected.Y - unknown_B0.unknown_04 + firstY);
            FUN_004AED70(DAT_00887314, DAT_0087F6C4,
                         DisplayPlaceShape_008A03FC, 0, &marker,
                         &Viewport_00886FA0, flags, 0, z, 0, 1000,
                         0, 0, 0, Point2D(0, 0));
            draw.X += step.X;
            draw.Y += step.Y;
        }
    }
}


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
    Vector3D vector;
    vector.X = (float)(unknown_B0.unknown_00 - 60);
    vector.Y = (float)(unknown_B0.unknown_04 - 30);
    vector.Z = 0.0f;
    Vector3D transformed;
    vector = *Matrix3D::MatrixApply(&transformed, &unknown_DE4, &vector);
    int x = (int)vector.X;
    int y = (int)vector.Y;
    unknown_D80 = x / 256;
    unknown_D84 = y / 256;
    unknown_D88 = DAT_00B0CE30 / 60 + 2;
    unknown_D8C = DAT_00B0CE34 / 15 + 4;
}

#include "../../_layout/object_class.h"

// FUNCTION: GAMEMD 0x6D8C60
void FUN_006D8C60(ObjectClass* object, int argument)
{
    CoordStruct coordinate = object->vf_18();
    int xy[2] = { coordinate.X, coordinate.Y };
    Point2D projected = IsoProject(xy);
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

#include "../../_layout/building_class.h"
#include "../../_layout/layer_class.h"

#include "../../map/terrain_objects/terrain_class.h"

// FUNCTION: GAMEMD 0x6D97D0
void Tactical::FUN_006D97D0(bool force, const RectangleStruct* view, const RectangleStruct* clip)
{
    RectangleStruct temporary;
    RectangleStruct bounds = *FUN_00421B60(&temporary, view, clip, 0, 0);
    for (int index = DisplayLayers[2].Count - 1; index >= 0; --index) {
        ObjectClass* object = DisplayLayers[2].Items[index];
        if (object->vf_11() != 0x24 || object->vf_17())
            continue;
        // Terrain table7F522C slot11 returns24; RTTI ObjectClass base is at0
        // (COL80C3E0, base descriptor7FB3D0). Existing TerrainClass retains
        // its legacy C++ base; this is a proven layout boundary for its fields.
        TerrainClass* terrain = reinterpret_cast<TerrainClass*>(object);
        if (terrain->Type->IsAnimated || terrain->TimeToDie)
            continue;
        int originX = Viewport_00886FA0.X;
        int originY = Viewport_00886FA0.Y;
        RectangleStruct objectBounds = object->vf_75();
        int left = objectBounds.X + originX;
        int top = objectBounds.Y + originY;
        if (left >= bounds.X + bounds.Width ||
            top >= bounds.Y + bounds.Height ||
            left + objectBounds.Width <= bounds.X ||
            top + objectBounds.Height <= bounds.Y)
            continue;
        RectangleStruct originalClip = *clip;
        object->vf_65(&originalClip, force, 0);
        object->NeedsRedraw = false;
    }
}

// FUNCTION: GAMEMD 0x6D9920
void Tactical::FUN_006D9920(bool force, const RectangleStruct* view, const RectangleStruct* clip)
{
    RectangleStruct temporary;
    RectangleStruct bounds = *FUN_00421B60(&temporary, view, clip, 0, 0);
    for (int index = 0; index < DisplayLayers[2].Count; ++index) {
        ObjectClass* object = DisplayLayers[2].Items[index];
        if (object->vf_11() != 6)
            continue;
        BuildingClass* building = static_cast<BuildingClass*>(object);
        if (building->IsFogged && !DAT_00A8ED6B)
            continue;
        int originX = Viewport_00886FA0.X;
        int originY = Viewport_00886FA0.Y;
        RectangleStruct objectBounds = object->vf_75();
        objectBounds.X += originX;
        objectBounds.Y += originY;
        if (objectBounds.X >= bounds.X + bounds.Width ||
            objectBounds.Y >= bounds.Y + bounds.Height ||
            objectBounds.X + objectBounds.Width <= bounds.X ||
            objectBounds.Y + objectBounds.Height <= bounds.Y)
            continue;
        RectangleStruct originalClip = *clip;
        object->vf_65(&originalClip, force, 0);
        object->NeedsRedraw = false;
    }
}

// FUNCTION: GAMEMD 0x6D9A50
void Tactical::FUN_006D9A50(RectangleStruct viewport)
{
    for (int index = 0; index < DisplayLayers[2].Count; ++index) {
        ObjectClass* object = DisplayLayers[2].Items[index];
        if (object->vf_11() == 6 && object->NeedsRedraw) {
            RectangleStruct bounds = object->vf_75();
            int left = bounds.X + Viewport_00886FA0.X;
            int top = bounds.Y + Viewport_00886FA0.Y;
            if (viewport.X < left + bounds.Width &&
                viewport.Y < top + bounds.Height &&
                left < viewport.X + viewport.Width &&
                top < viewport.Y + viewport.Height) {
                // 6D9AF4..6D9B15 forwards the original bounds, untranslated.
                FUN_006D2790(bounds, false);
                object->NeedsRedraw = false;
            }
        }
    }
}

#include "../../_layout/building_array.h"

GG_STATIC_ASSERT(offsetof(BuildingTypeClass, bools_1700) + sizeof(bool) == 0x1701);

// FUNCTION: GAMEMD 0x6D9B50
bool Tactical::FUN_006D9B50(RectangleStruct viewport)
{
    const int left = unknown_B0.unknown_00 + viewport.X;
    const int top = unknown_B0.unknown_04 + viewport.Y;
    const int right = unknown_B0.unknown_00 + viewport.Width + viewport.X;
    const int bottom = unknown_B0.unknown_04 + viewport.Height + viewport.Y;
    for (int index = 0; index < DAT_00A8EB40.Count; ++index) {
        BuildingClass* building = DAT_00A8EB40.Items[index];
        // Native byte tests at 0x6D9BAB/+0x90,0x6D9BB9/+0x80,0x6D9BC7/+0x74.
        // The canonical ObjectClass header already asserts all three offsets.
        if (building->IsAlive && building->NeedsRedraw && building->IsOnMap) {
            CoordStruct coordinate = building->vf_43();
            Point2D projected;
            projected.X = coordinate.X * 60 / 2;
            projected.Y = coordinate.X * 30 / 2;
            projected.X += coordinate.Y * -60 / 2;
            projected.Y += coordinate.Y * 30 / 2;
            const int screenX = projected.X / 256;
            const int screenY = projected.Y / 256 - AdjustForZ(coordinate.Z);
            if (screenX >= left && screenX <= right && screenY >= top && screenY <= bottom)
                return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x6D9CE0
void Tactical::FUN_006D9CE0(int x, int y, int width, int height)
{
    int left = unknown_B0.unknown_00 + x;
    int top = unknown_B0.unknown_04 + y;
    int right = unknown_B0.unknown_00 + width + x;
    int bottom = unknown_B0.unknown_04 + height + y;
    for (int index = 0; index < DAT_00A8EB40.Count; ++index) {
        BuildingClass* building = DAT_00A8EB40.Items[index];
        if (building->IsAlive && building->IsOnMap && !building->Type->bools_1700[1]) {
            // Native reads Location directly; do not replace with vf43.
            CoordStruct coordinate = building->Location;
            Point2D projected;
            projected.X = coordinate.X * 60 / 2;
            projected.Y = coordinate.X * 30 / 2;
            projected.X += coordinate.Y * -60 / 2;
            projected.Y += coordinate.Y * 30 / 2;
            int screenX = projected.X / 256;
            int screenY = projected.Y / 256 - AdjustForZ(coordinate.Z);
            if (screenX >= left && screenX <= right && screenY >= top && screenY <= bottom) {
                int clientX = screenX - unknown_B0.unknown_00;
                int clientY = screenY - unknown_B0.unknown_04;
                if (unknown_DB0 != 500 && clientX >= -32 && clientX <= Viewport_00886FA0.Width + 32 &&
                    clientY >= -32 && clientY <= Viewport_00886FA0.Height + 32) {
                    DAT_00B0CEC8[unknown_DB0].unknown_00 = building;
                    int originX = unknown_B0.unknown_00;
                    int originY = unknown_B0.unknown_04;
                    // Native6D9EA4 captures one index for both coordinate stores.
                    int recordIndex = unknown_DB0;
                    DAT_00B0CEC8[recordIndex].unknown_04 = originX + clientX;
                    DAT_00B0CEC8[recordIndex].unknown_08 = originY + clientY;
                    ++unknown_DB0;
                }
            }
        }
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
#include "../../_layout/object_class.h"

#include "display_command.h"
GG_STATIC_ASSERT(offsetof(DisplayClass, SavedPending) == 0x1190);
GG_STATIC_ASSERT(offsetof(DisplayClass, SavedType) == 0x1194);
GG_STATIC_ASSERT(offsetof(DisplayClass, SavedField) == 0x1198);

// FUNCTION: GAMEMD 0x6DA560
void Tactical::vf_10(void* target, bool removed)
{
    for (int index = 0; index < 500; ++index) {
        if (DAT_00B0CEC8[index].unknown_00 == target)
            DAT_00B0CEC8[index].unknown_00 = 0;
    }
    if (target == Map_0087F7E8.SavedPending) {
        DisplayCmdMap_0087F7E8.FUN_004A8D50(0);
        Map_0087F7E8.SavedPending = 0;
        Map_0087F7E8.SavedType = 0;
        Map_0087F7E8.SavedField = -1;
    }
}

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
#include "../../_layout/swizzle_manager_class.h"
// GLOBAL: GAMEMD 0x87F7F4 (declaration)
extern int DAT_0087F7F4;

// FUNCTION: GAMEMD 0x6DA7D0
void Tactical::FUN_006DA7D0(CellClass* cell)
{
    if (DAT_0087F7F4 != 0 || cell->unknown_5C == CurrentFrame ||
        (!(cell->AltFlags & 8) && !cell->VisibilityChanged))
        return;
    cell->unknown_5C = CurrentFrame;
    CoordStruct coordinate;
    cell->GetCellCoords(&coordinate);
    Point2D projected;
    projected.X = coordinate.X * 60 / 2;
    projected.Y = coordinate.X * 30 / 2;
    projected.X += coordinate.Y * -60 / 2;
    projected.Y += coordinate.Y * 30 / 2;
    // Native both AltFlags8/10 branches have identical XY projection and
    // explicitly pass zero to AdjustForZ; do not substitute coordinate.Z.
    int screenX = projected.X / 256;
    int screenY = projected.Y / 256 - AdjustForZ(0);
    screenX -= unknown_B0.unknown_00;
    screenY -= unknown_B0.unknown_04;
    if (screenX >= Viewport_00886FA0.X - 30 && screenY >= -30 &&
        screenX <= Viewport_00886FA0.Width + Viewport_00886FA0.X + 30 &&
        screenY <= Viewport_00886FA0.Height + Viewport_00886FA0.Y + 15) {
        if (unknown_E0 < 799) {
            unknown_E4[unknown_E0] = cell;
            ++unknown_E0;
        }
        // Native clears/sets these even when the queue is full.
        cell->VisibilityChanged = 0;
        unknown_D7D = true;
    }
}

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

GG_STATIC_ASSERT(offsetof(VectorClass<DirtyAreaStruct>, Items) == 4);
GG_STATIC_ASSERT(sizeof(((VectorClass<DirtyAreaStruct>*)0)->Items) == 4);

// FUNCTION: GAMEMD 0x006DC510
// DynamicVectorClass<DirtyAreaStruct>::Slot5
// FUNCTION: GAMEMD 0x6DC540
// VectorClass<DirtyAreaStruct>::Slot6
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
template class VectorClass<DirtyAreaStruct>;
