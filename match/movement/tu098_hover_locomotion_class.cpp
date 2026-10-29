// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Placement lead: this file regresses under the project /Ob2 default, so a
// definition it can see probably lived in another original file.
//   Original translation unit TU098 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x513a10-0x51783f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   Provenance note: retail gamemd.exe v1.001, confirmed from entry-origin instructions and pinned PE data.
// No /GX: none of the matched bodies unwinds (confirmed with a paired /GX probe).
//
// HoverLocomotionClass (leaf of the locomotion module): the hovercraft locomotor.
// Layout, tables and evidence are in hover_locomotion_class.h.
//
// Three unsigned bytes at +0x00/+0x01/+0x02, read and written byte-wise by
// 0x517360 and 0x5173F0. The class and component names are descriptive (the
// target list labels this area HSV); no size is asserted.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.
//
// Small forwarding bodies that repeat at two or more retail addresses. Each
// address is compiled and checked on its own; the copies differ in the callee
// or the table. Owners that are not modelled elsewhere are placeholders
// `Obj_<ADDR>` declaring only the callees the body uses, which are named by
// address.
//
// Three-byte hue/saturation/value colour converted to a three-byte RGB colour,
// a __thiscall member returning the triple through the hidden pointer
// (`RET 4`). Byte reads at [ECX+0..2] fix the field order. The six sector
// values sit in a local table and each output channel steps two entries
// further round it. 21 callers (scheme tint lookups among them).

#include <math.h>
#include <stdlib.h>
#include <new.h>
#include "hover_locomotion_class.h"

// GLOBAL: GAMEMD 0x7E9A40 - CLSID of HoverLocomotionClass (16 bytes read from the image)
extern "C" const CLSID CLSID_HoverLocomotion =
    { 0x4A582742, 0x9839, 0x11D1, { 0xB7, 0x09, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1 } };

// True when any component differs from the empty coordinate DAT_00A8F180.
static inline bool IsCoordSet(const LocoCoord& c)
{
    return c.X != DAT_00A8F180.X || c.Y != DAT_00A8F180.Y || c.Z != DAT_00A8F180.Z;
}

// Cell containing a world coordinate (256 leptons per cell, rounding toward zero).
static inline HoverCellCoord CellOf(const LocoCoord& coord)
{
    HoverCellCoord cell;
    cell.X = (short)(coord.X / 256);
    cell.Y = (short)(coord.Y / 256);
    return cell;
}

static inline HoverCellCoord AddCell(const HoverCellCoord& a, const CellStruct& b)
{
    HoverCellCoord sum;
    sum.X = a.X + b.X;
    sum.Y = a.Y + b.Y;
    return sum;
}

static inline LocoCoord CellCenter(const HoverCellCoord& cell)
{
    LocoCoord center;
    center.X = (cell.X << 8) + 0x80;
    center.Y = (cell.Y << 8) + 0x80;
    center.Z = 0;
    return center;
}

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class HSVColour
{
public:
    // FUNCTION: GAMEMD 0x517360
    void Adjust(unsigned char ratio, const HSVColour& other);
    // FUNCTION: GAMEMD 0x5173F0
    int Difference(const HSVColour& other) const;

    unsigned char Hue;          // +0x00
    unsigned char Saturation;   // +0x01
    unsigned char Value;        // +0x02
};
GG_STATIC_ASSERT(offsetof(HSVColour, Hue)        == 0x00);
GG_STATIC_ASSERT(offsetof(HSVColour, Saturation) == 0x01);
GG_STATIC_ASSERT(offsetof(HSVColour, Value)      == 0x02);

#include "../core/deleting_dtor_sweep.h"
#include "../network/transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

const char* FUN_0048E030(unsigned int index);
const char* FUN_0048E090(unsigned int index);

#include "../_layout/obj_00477020.h"

#include "../_layout/obj_004770b0.h"

#include "../_layout/obj_005175e0.h"

struct Obj_005176A0 {
    unsigned int Bits;
    bool FUN_005176A0() const;
    bool FUN_005176B0() const;
    bool FUN_005176C0() const;
};

#include "../_layout/rec_00549b50.h"
#include "../_layout/obj_00549b50.h"

#include "../_layout/obj_006ea4f0.h"

#include "../_layout/obj_007719c0.h"

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct RGBTripleValue
{
    unsigned char Red;    // +0x00
    unsigned char Green;  // +0x01
    unsigned char Blue;   // +0x02
};
GG_STATIC_ASSERT(offsetof(RGBTripleValue, Blue) == 2);

class HSVTriple
{
public:
    unsigned char Hue;          // +0x00
    unsigned char Saturation;   // +0x01
    unsigned char Value;        // +0x02

    RGBTripleValue FUN_00517440() const;
};
GG_STATIC_ASSERT(offsetof(HSVTriple, Hue) == 0);
GG_STATIC_ASSERT(offsetof(HSVTriple, Saturation) == 1);
GG_STATIC_ASSERT(offsetof(HSVTriple, Value) == 2);

//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Arg1_00517560;
struct Obj_00517560;

struct Arg1_00517560
{
    bool unknown_00;   // +0x0000
    bool unknown_01;   // +0x0001
    bool unknown_02;   // +0x0002
};
GG_STATIC_ASSERT(offsetof(Arg1_00517560, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Arg1_00517560, unknown_01) == 0x1);
GG_STATIC_ASSERT(offsetof(Arg1_00517560, unknown_02) == 0x2);

struct Obj_00517560
{
    bool unknown_00;   // +0x0000
    bool unknown_01;   // +0x0001
    bool unknown_02;   // +0x0002
    // FUNCTION: GAMEMD 0x517560
    int FUN_00517560(Arg1_00517560* a1);
    // FUNCTION: GAMEMD 0x517590
    bool FUN_00517590(Arg1_00517560* a1);
    bool IsSame(Arg1_00517560* a1) { return unknown_00 == a1->unknown_00 && unknown_01 == a1->unknown_01 && unknown_02 == a1->unknown_02; }
};
GG_STATIC_ASSERT(offsetof(Obj_00517560, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_00517560, unknown_01) == 0x1);
GG_STATIC_ASSERT(offsetof(Obj_00517560, unknown_02) == 0x2);


// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EACE8
extern const double DAT_007EACE8;
// GLOBAL: GAMEMD 0xA8F168
extern double DAT_00A8F168;

// GLOBAL: GAMEMD 0xA8F1B8
extern double DAT_00A8F1B8;

// GLOBAL: GAMEMD 0xA8F1A0
extern double DAT_00A8F1A0;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x513C20
HoverLocomotionClass::HoverLocomotionClass()
    : Destination_(DAT_00A8F180), HeadTo(DAT_00A8F180), Facing(0),
      Speed(0.0), SpeedFactor(0.0), Field_58(1.0), Field_60(0.0),
      IsRocking(false), RockAmount(0), Blocked(false)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x513CB0
HRESULT __stdcall HoverLocomotionClass::LinkToObject(FootClass* object)
{
    HRESULT hr = LocomotionClass::LinkToObject(object);
    HoverFacingView facing(HoverFoot(LinkedTo)->Slot_084()->unknown_71C << 1);
    Facing = facing;
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x513F40
Matrix3D __stdcall HoverLocomotionClass::DrawMatrix(unsigned int* key)
{
    if (fabs(HoverFoot(LinkedTo)->AngleSideways) < 0.005 && fabs(HoverFoot(LinkedTo)->AngleForwards) < 0.005) {
        if (!IsPowered()) {
            LocoCoord location = HoverFoot(LinkedTo)->Location;
            int slope = HoverMap().GetCellAt(&location)->SlopeIndex;
            Matrix3D m = FUN_007559B0(slope);
            m.RotateZ((float)(((int)((((HoverFoot(LinkedTo)->PrimaryFacing.Current().Raw >> 10) + 1) >> 1) & 0x1F) - 8)
                              * -0.19634954084936207));
            if (key != 0 && *key != 0xFFFFFFFF) {
                *key = ((*key << 6) + slope) << 5;
                *key |= (((HoverFoot(LinkedTo)->PrimaryFacing.Current().Raw >> 10) + 1) >> 1) & 0x1F;
            }
            return m;
        }
        return LocomotionClass::DrawMatrix(key);
    }
    if (key != 0)
        *key = 0xFFFFFFFF;
    Matrix3D lift;
    lift.MakeIdentity();
    Matrix3D tilt;
    tilt.MakeIdentity();
    float t0 = (float)HoverFoot(LinkedTo)->Slot_084()->unknown_360;
    float t1 = (float)HoverFoot(LinkedTo)->Slot_084()->unknown_368;
    float cos32 = (float)HoverCos(HoverFoot(LinkedTo)->AngleForwards);
    float sin32 = (float)HoverSin(HoverFoot(LinkedTo)->AngleForwards);
    float cos28 = (float)HoverCos(HoverFoot(LinkedTo)->AngleSideways);
    int lift_z = (int)(fabs(HoverSin(HoverFoot(LinkedTo)->AngleSideways)) * t0 + fabs(sin32) * t1);
    int sideX = (int)(cos32 * t1);
    int dx = (int)(t1 - sideX);
    int sideY = (int)(cos28 * t0);
    int dy = (int)(t0 - sideY);
    if (HoverFoot(LinkedTo)->AngleForwards < 0.0f)
        dx = -dx;
    if (HoverFoot(LinkedTo)->AngleSideways > 0.0f)
        dy = -dy;
    lift.TranslateZ((float)lift_z);
    tilt.TranslateX((float)dx);
    tilt.TranslateY((float)dy);
    tilt.RotateX(HoverFoot(LinkedTo)->AngleSideways);
    tilt.RotateY(HoverFoot(LinkedTo)->AngleForwards);
    Matrix3D base;
    base.FUN_005AE610(LocomotionClass::DrawMatrix(key));
    return FUN_005AF980(FUN_005AF980(lift, base), tilt);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5142A0
Matrix3D __stdcall HoverLocomotionClass::ShadowMatrix(unsigned int* key)
{
    HoverFootView* foot = HoverFoot(LinkedTo);
    if (!(fabs(foot->AngleSideways) < 0.005 && fabs(foot->AngleForwards) < 0.005)) {
        if (key != 0)
            *key = 0xFFFFFFFF;
    }
    return LocomotionClass::ShadowMatrix(key);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x514310
// Retail returns small status values in AL (0, 7 or IsMoving()); the foundation declares the
// slot as bool, so the `return 7` exits can only be written as `return true` here.
bool __stdcall HoverLocomotionClass::Process()
{
    if (IsMoving() && IsMoving()) {
        Fun_00515ED0();
        if (!HoverFoot(LinkedTo)->unknown_090)
            return false;
        int slotValue = HoverFoot(LinkedTo)->Slot_1D0();
        int reach = (int)(HoverFoot(LinkedTo)->Slot_538() * SpeedFactor);
        HoverCoordView buffer;
        HoverCoordView* here = HoverUnitCoord(HoverFoot(LinkedTo), &buffer);
        here->Fun_00517310(&HeadTo);
        short heading = (short)(int)((HoverAtan2((double)(here->Y - HeadTo.Y), (double)(HeadTo.X - here->X))
                                      - 1.5707963267948966) * -10430.378350470453);
        if (reach == 0) {
            if (abs(0) >= abs((short)((short)Facing.Current().Raw - heading))) {
                bool atCell;
                if (!IsCoordSet(HeadTo)) {
                    atCell = true;
                } else {
                    HoverCellCoord headCell;
                    HeadTo.Fun_00413A30(&headCell);
                    HoverCellCoord buf;
                    atCell = HoverFoot(LinkedTo)->Slot_1B8(&buf)->FUN_0050E470(&headCell);
                }
                Speed = 1.0;
                HoverFoot(LinkedTo)->Slot_544(1.0);
                Fun_005164D0(0);
                if (atCell)
                    Fun_00514F70(1);
                reach = (int)(HoverFoot(LinkedTo)->Slot_538() * SpeedFactor);
            }
        }
        LocoCoord* location = &HoverFoot(LinkedTo)->Location;
        int dx = location->X - HeadTo.X;
        int dy = location->Y - HeadTo.Y;
        int distance = (int)HoverSqrt((double)dx * dx + (double)dy * dy);
        if (reach >= distance) {
            HoverFoot(LinkedTo)->unknown_6B6 = 1;
            HoverFoot(LinkedTo)->unknown_6B7 = 0;
            Blocked = false;
            Fun_005164D0(0);
            if (HoverFoot(LinkedTo)->PathDirection0 == -1 && !IsCoordSet(Destination_)) {
                HeadTo.X = DAT_00A8F180.X;
                HeadTo.Y = DAT_00A8F180.Y;
                HeadTo.Z = DAT_00A8F180.Z;
            }
            HoverCellCoord cell = DAT_00A8F160;
            HoverObjectView* transport = HoverFoot(LinkedTo)->FUN_0065AD30(0);
            if (transport != 0) {
                HoverCoordView out;
                LocoCoord* where = transport->Slot_04C(&out, LinkedTo);
                cell = CellOf(*where);
            }
            HoverCellCoord buf2;
            HoverCellCoord* footCell = HoverFoot(LinkedTo)->Slot_1B8(&buf2);
            bool sameCell = footCell->X == cell.X && footCell->Y == cell.Y;
            if (IsCoordSet(Destination_) || sameCell) {
                int result = Fun_00514F70(1);
                if (!HoverFoot(LinkedTo)->unknown_090 || HoverFoot(LinkedTo)->unknown_081 || HoverFoot(LinkedTo)->unknown_08D)
                    return true;
                if (result == 0 && !IsCoordSet(HeadTo)) {
                    LocoCoord here2 = HoverFoot(LinkedTo)->Location;
                    HoverFoot(LinkedTo)->Slot_0F0(&here2);
                    HoverFoot(LinkedTo)->Slot_18C(2);
                    if (!HoverFoot(LinkedTo)->unknown_090 || HoverFoot(LinkedTo)->unknown_081 || HoverFoot(LinkedTo)->unknown_08D)
                        return false;
                }
                if (result == 7) {
                    if (HoverFoot(LinkedTo)->unknown_684 >= 0)
                        return false;
                    HoverFoot(LinkedTo)->Slot_480(0, 1);
                    Speed = 0.0;
                    SpeedFactor = 0.0;
                    HoverFoot(LinkedTo)->Slot_544(0.0);
                } else if (result != 0) {
                    Speed = 0.0;
                    SpeedFactor = 0.0;
                    HoverFoot(LinkedTo)->Slot_544(0.0);
                    if (IsCoordSet(HeadTo)) {
                        HoverFoot(LinkedTo)->Slot_0F4(&HeadTo);
                        HeadTo.X = DAT_00A8F180.X;
                        HeadTo.Y = DAT_00A8F180.Y;
                        HeadTo.Z = DAT_00A8F180.Z;
                    }
                    goto finish;
                }
            }
        }
        if (reach > 0) {
            LocoCoord target;
            target = HoverFoot(LinkedTo)->Location;
            if (HoverFoot(LinkedTo)->Slot_0C0()) {
                if (IsCoordSet(HeadTo)) {
                    LocoCoord current = HoverFoot(LinkedTo)->Location;
                    HoverFoot(LinkedTo)->Slot_0F4(&current);
                    HoverFoot(LinkedTo)->unknown_6B6 = 0;
                    HoverFoot(LinkedTo)->unknown_6B7 = 0;
                }
            }
            double theta = ((short)Facing.Current().Raw - 0x3FFF) * -9.587379924285257e-05;
            int newY = (int)(target.Y - HoverSin(theta) * reach);
            int newX = (int)(HoverCos(theta) * reach + target.X);
            target.X = newX;
            target.Y = newY;
            LocoCoord old = HoverFoot(LinkedTo)->Location;
            if (CellOf(target) == CellOf(old)) {
                unsigned char saved = HoverFoot(LinkedTo)->unknown_074;
                HoverFoot(LinkedTo)->unknown_074 = 0;
                HoverFoot(LinkedTo)->Slot_1B4(&target);
                HoverFoot(LinkedTo)->FUN_005F6060(slotValue);
                HoverFoot(LinkedTo)->unknown_074 = saved;
            } else {
                HoverFoot(LinkedTo)->Slot_124(0);
                HoverFoot(LinkedTo)->Slot_1B4(&target);
                HoverFoot(LinkedTo)->FUN_005F6060(slotValue);
                HoverObjectView* cellView = HoverMap().GetCellAt(&target);
                if (!HoverFoot(LinkedTo)->unknown_08C && (cellView->Flags & 0x100)) {
                    if (HoverFoot(LinkedTo)->Slot_1C8() >= DAT_00A8F1B4)
                        HoverFoot(LinkedTo)->unknown_08C = 1;
                }
                if (HoverFoot(LinkedTo)->unknown_08C == 1 && !(cellView->Flags & 0x100))
                    HoverFoot(LinkedTo)->unknown_08C = 0;
                HoverFoot(LinkedTo)->Slot_124(1);
            }
        }
    }
finish:
    if (IsMovingNow()) {
        if (DAT_00A8ED84 % 10 == 0 && !HoverFoot(LinkedTo)->unknown_08C
            && HoverFoot(LinkedTo)->Slot_1BC()->unknown_0EC == 2 && DAT_008871E0->unknown_094 != 0) {
            LocoCoord at = HoverFoot(LinkedTo)->Location;
            new HoverAnimView(DAT_008871E0->unknown_094, &at, 1, 0x600, 0, 0, 0);
        }
    }
    Fun_00513D20();
    if (IsRocking) {
        if (IsPowered()) {
            HoverDirView direction;
            direction.Raw = (RockAmount << 8) + HoverFoot(LinkedTo)->PrimaryFacing.Current().Raw;
            HoverFoot(LinkedTo)->PrimaryFacing.Set(&direction);
            int step = abs(RockAmount);
            if (step >= 1)
                step = 1;
            if (RockAmount >= 0)
                RockAmount -= step;
            else
                RockAmount += step;
            if (RockAmount == 0)
                IsRocking = false;
        } else {
            IsRocking = false;
        }
        if (!IsRocking) {
            LocoCoord loc = HoverFoot(LinkedTo)->Location;
            HoverMap().GetCellAt(&loc)->FUN_00486920();
            LocoCoord loc2 = HoverFoot(LinkedTo)->Location;
            if (HoverMap().GetCellAt(&loc2)->unknown_0EC == 2) {
                LocoCoord loc3 = HoverFoot(LinkedTo)->Location;
                if (loc3.Z < HoverMap().GetHeightAt(&loc3) + DAT_00A8F1C0)
                    HoverFoot(LinkedTo)->Slot_0EC();
            }
        }
    }
    return IsMoving();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x514C30
bool __stdcall HoverLocomotionClass::IsMoving()
{
    return IsCoordSet(Destination_) || IsCoordSet(HeadTo);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x514C80
bool __stdcall HoverLocomotionClass::IsMovingNow()
{
    return IsMoving() && Speed != 0.0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x514CB0
LocoCoord __stdcall HoverLocomotionClass::Destination()
{
    LocoCoord coord;
    if (IsCoordSet(Destination_)) {
        coord.X = Destination_.X; coord.Y = Destination_.Y; coord.Z = Destination_.Z;
        return coord;
    }
    coord.X = DAT_00A8F180.X; coord.Y = DAT_00A8F180.Y; coord.Z = DAT_00A8F180.Z;
    return coord;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x514D10
LocoCoord __stdcall HoverLocomotionClass::HeadToCoord()
{
    LocoCoord coord;
    if (IsCoordSet(HeadTo)) {
        coord.X = HeadTo.X; coord.Y = HeadTo.Y; coord.Z = HeadTo.Z;
        return coord;
    }
    LocoCoord location = HoverFoot(LinkedTo)->Location;
    coord.X = location.X; coord.Y = location.Y; coord.Z = location.Z;
    return coord;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x514D90
void __stdcall HoverLocomotionClass::MoveTo(LocoCoord to)
{
    Destination_ = to;
    if (HoverFoot(LinkedTo)->Slot_380())
        return;
    if (IsPowered() && IsIonSensitive()) {
        if (HoverFoot(LinkedTo)->House->IonSensitivesShouldBeOffline())
            PowerOff();
    }
    Destination_.Z = HoverMap().GetHeightAt(&Destination_);
    LocoCoord target;
    target.X = to.X;
    target.Y = to.Y;
    target.Z = to.Z;
    if (HoverMap().GetCellAt(&target)->Flags & 0x100)
        Destination_.Z += DAT_00A8F1B4;
    if (to.X == DAT_00A8F180.X && to.Y == DAT_00A8F180.Y && to.Z == DAT_00A8F180.Z)
        return;
    if (!IsPowered())
        return;
    if (!IsMovingNow()) {
        HoverFoot(LinkedTo)->Slot_544(1.0);
        Fun_005164D0(0);
        Fun_00514F70(1);
        return;
    }
    if (IsCoordSet(HeadTo))
        return;
    bool atCell;
    if (IsCoordSet(HeadTo)) {
        HoverCellCoord buffer;
        short headX = (short)(HeadTo.X / 256);
        short headY = (short)(HeadTo.Y / 256);
        HoverCellCoord* footCell = HoverFoot(LinkedTo)->Slot_1B8(&buffer);
        atCell = footCell->X == headX && footCell->Y == headY;
    } else {
        atCell = true;
    }
    Speed = 1.0;
    HoverFoot(LinkedTo)->Slot_544(1.0);
    Fun_005164D0(0);
    if (atCell)
        Fun_00514F70(1);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x516320
void __stdcall HoverLocomotionClass::StopMoving()
{
    if (Destination_.X != HeadTo.X || Destination_.Y != HeadTo.Y || Destination_.Z != HeadTo.Z) {
        Destination_.X = DAT_00A8F180.X;
        Destination_.Y = DAT_00A8F180.Y;
        Destination_.Z = DAT_00A8F180.Z;
        HoverFoot(LinkedTo)->PathDirection0 = -1;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5163A0
// Unreferenced wrapper returning the virtual IsMoving() result.
bool HoverLocomotionClass::Fun_005163A0()
{
    return IsMoving() ? true : false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5163B0
// PARTIAL: 95.7% - final return path schedules `mov al,1` before `pop esi` (4 instructions differ).
// While moving, clears the path-direction slot that matches the distance (in cells) from
// the foot to the destination, or the first slot when the foot's other target accepts it.
bool HoverLocomotionClass::Fun_005163B0()
{
    if (!IsMoving())
        return false;
    if (HoverFoot(LinkedTo)->PathDirection0 == -1)
        return false;
    if ((HoverFoot(LinkedTo)->unknown_5A4 && HoverFoot(LinkedTo)->unknown_5A4->Slot_02C() == 1) ||
        (HoverFoot(LinkedTo)->unknown_5A4 && HoverFoot(LinkedTo)->unknown_5A4->Slot_02C() == 15)) {
        int d[3];
        HoverCoordView buffer;
        HoverCoordView* here = HoverUnitCoord(HoverFoot(LinkedTo), &buffer);
        d[0] = here->X - Destination_.X;
        d[1] = here->Y - Destination_.Y;
        d[2] = here->Z - Destination_.Z;
        int index = (int)HoverSqrt((double)d[0] * d[0] + (double)d[1] * d[1] + (double)d[2] * d[2]) / 256;
        if (index < 24) {
            (&HoverFoot(LinkedTo)->PathDirection0)[index] = -1;
            return true;
        }
    }
    if (HoverFoot(LinkedTo)->unknown_2B4) {
        if (HoverFoot(LinkedTo)->Slot_3AC(HoverFoot(LinkedTo)->unknown_2B4)) {
            HoverFoot(LinkedTo)->PathDirection0 = -1;
            return true;
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x516370
void __stdcall HoverLocomotionClass::DoTurn(unsigned long dir)
{
    HoverDirView d;
    d.Raw = dir;
    HoverFoot(LinkedTo)->PrimaryFacing.SetDesired(&d);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x516BF0
bool __stdcall HoverLocomotionClass::PowerOff()
{
    if (IsPowered()) {
        int state = HoverFoot(LinkedTo)->unknown_0AC;
        if (state != 0 && state != 7) {
            IsRocking = true;
            RockAmount = DAT_00A8B230->unknown_0218.RandomRanged(20, 30);
            if (DAT_00A8B230->unknown_0218.RandomRanged(0, 99) < 50)
                RockAmount = -RockAmount;
        }
    }
    if (IsMoving())
        StopMoving();
    return LocomotionClass::PowerOff();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x516C70
bool __stdcall HoverLocomotionClass::IsPowered()
{
    if (LocomotionClass::IsPowered() || HoverFoot(LinkedTo)->Slot_1C8() > 0)
        return true;
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x516CA0
bool __stdcall HoverLocomotionClass::IsIonSensitive()
{
    if (HoverFoot(LinkedTo)->FUN_0065AE30()) {
        if (HoverFoot(LinkedTo)->FUN_0065AD30(0)->Slot_02C() == 6) {
            if (HoverFoot(LinkedTo)->FUN_0065AD30(0)->unknown_520->unknown_16BD)
                return false;
        }
    }
    HoverObjectView* building;
    {
        LocoCoord location = HoverFoot(LinkedTo)->Location;
        building = HoverMap().GetCellAt(&location)->FUN_0047C520();
    }
    if (building != 0 && building->unknown_520->unknown_16BD) {
        LocoCoord buildingLocation = building->Location;
        HoverCellCoord buildingCell = CellOf(buildingLocation);
        LocoCoord footLocation = HoverFoot(LinkedTo)->Location;
        HoverCellCoord footCell = CellOf(footLocation);
        short dx = footCell.X - buildingCell.X;
        short dy = footCell.Y - buildingCell.Y;
        if (dx == 0) {
            if (dy == 1)
                return false;
        } else if (dx == 2) {
            if (dy == 1)
                return false;
        } else if (dx == 3) {
            if (dy == 1)
                return false;
        }
    }
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x516E10
// PARTIAL: 87.7% -- register naming differs; instruction multiset identical.
bool __stdcall HoverLocomotionClass::Push(unsigned long dir)
{
    if (IsPowered() && !Blocked) {
        HoverCellCoord buffer;
        HoverCellCoord* current = HoverFoot(LinkedTo)->Slot_1B8(&buffer);
        HoverCellCoord next = AddCell(*current, DAT_0089F688[((dir >> 12) + 1 >> 1) & 7]);
        if (HoverFoot(LinkedTo)->Slot_1AC(HoverMap().GetCellAtCell(&next), -1, -1, 0, 1) == 0) {
            Blocked = true;
            if (IsMoving()) {
                HoverFoot(LinkedTo)->PathDirection0 = -1;
                if (!(HeadTo.X == DAT_00A8F180.X && HeadTo.Y == DAT_00A8F180.Y && HeadTo.Z == DAT_00A8F180.Z))
                    HoverFoot(LinkedTo)->Slot_0F4(&HeadTo);
                HeadTo = CellCenter(next);
                HeadTo.Z = HoverMap().GetHeightAt(&HeadTo);
                LocoCoord location = HoverFoot(LinkedTo)->Location;
                if (location.Z >= HeadTo.Z + DAT_00A8F1C0 * 3)
                    HeadTo.Z += DAT_00A8F1B4;
                HoverFoot(LinkedTo)->Slot_0F0(&HeadTo);
                return true;
            }
            MoveTo(CellCenter(next));
            return true;
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x516FC0
bool __stdcall HoverLocomotionClass::Shove(unsigned long dir)
{
    if (Push(dir)) {
        IsRocking = true;
        RockAmount = DAT_00A8B230->unknown_0218.RandomRanged(20, 30);
        if (DAT_00A8B230->unknown_0218.RandomRanged(0, 99) < 50)
            RockAmount = -RockAmount;
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x515E30
// Zeroes both speed doubles after telling the linked unit to stop its movement state.
void HoverLocomotionClass::ClearSpeed()
{
    HoverFoot(LinkedTo)->Slot_480(0, 1);
    SpeedFactor = 0.0;
    Speed = 0.0;
    HoverFoot(LinkedTo)->Slot_544(0.0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x515E60
// Zeroes both speed doubles and, when a heading target is set, hands it to the linked unit and clears it.
void HoverLocomotionClass::ClearSpeedAndHeading()
{
    SpeedFactor = 0.0;
    Speed = 0.0;
    HoverFoot(LinkedTo)->Slot_544(0.0);
    if (IsCoordSet(HeadTo)) {
        HoverFoot(LinkedTo)->Slot_0F4(&HeadTo);
        HeadTo = DAT_00A8F180;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x517020
// Starts the rocking wobble: random amplitude 20..30, negated half of the time.
void HoverLocomotionClass::StartRocking()
{
    IsRocking = true;
    RockAmount = DAT_00A8B230->unknown_0218.RandomRanged(20, 30);
    if (DAT_00A8B230->unknown_0218.RandomRanged(0, 99) < 50)
        RockAmount = -RockAmount;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x517070
HRESULT __stdcall HoverLocomotionClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = CLSID_HoverLocomotion;
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5170B0
HRESULT __stdcall HoverLocomotionClass::Load(IStream* pStm)
{
    HRESULT hr = LocomotionClass::Load(pStm);
    if (hr >= 0)
        new (this) HoverLocomotionClass(0);
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x517100
int __stdcall HoverLocomotionClass::InWhichLayer()
{
    return 2;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x517110
// Starts moving: speed becomes 1.0 and the linked unit is told; when it already stands on the
// target cell (or no target is set) the arrival hook runs.
void HoverLocomotionClass::StartMoving()
{
    HoverCellCoord headCell;
    HoverCellCoord buf;
    HoverCellCoord* cur;
    bool atCell = !IsCoordSet(HeadTo) ||
        (headCell = CellOf(HeadTo), cur = HoverFoot(LinkedTo)->Slot_1B8(&buf),
         cur->X == headCell.X && cur->Y == headCell.Y);
    Speed = 1.0;
    HoverFoot(LinkedTo)->Slot_544(1.0);
    Fun_005164D0(0);
    if (atCell)
        Fun_00514F70(1);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5171C0
void __stdcall HoverLocomotionClass::MarkAllOccupationBits(int mark)
{
    if (mark == 0) {
        LocoCoord coord = HeadToCoord();
        HoverFoot(LinkedTo)->Slot_0F4(&coord);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x517210
bool __stdcall HoverLocomotionClass::IsMovingHere(LocoCoord to)
{
    LocoCoord head = HeadToCoord();
    HoverCellCoord toCell = CellOf(to);
    HoverCellCoord headCell = CellOf(head);
    if (headCell == toCell && abs(head.Z - to.Z) <= DAT_00A8F1C0)
        return true;
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5172B0
int HoverLocomotionClass::Size()
{
    return sizeof(HoverLocomotionClass);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x5172C0
// Compiler-generated scalar deleting destructor from the native declaration.

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x517360
void HSVColour::Adjust(unsigned char ratio, const HSVColour& other)
{
    Value = (unsigned char)(Value + ((other.Value - Value) * ratio) / 256);
    Saturation = (unsigned char)(Saturation + ((other.Saturation - Saturation) * ratio) / 256);
    Hue = (unsigned char)(Hue + ((other.Hue - Hue) * ratio) / 256);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5173F0
int HSVColour::Difference(const HSVColour& other) const
{
    int hue = Hue - other.Hue;
    if (hue < 0) {
        hue = -hue;
    }
    int saturation = Saturation - other.Saturation;
    if (saturation < 0) {
        saturation = -saturation;
    }
    int value = Value - other.Value;
    if (value < 0) {
        value = -value;
    }
    return value * value + saturation * saturation + hue * hue;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x517440
RGBTripleValue HSVTriple::FUN_00517440() const
{
    int values[7];
    int hue = Hue;
    int sat = Saturation;
    int val = Value;

    int scaled = hue * 6;
    unsigned int frac = scaled % 255;

    values[2] = val;
    values[1] = val;
    values[3] = ((255 - (frac * sat) / 255) * val) / 255;
    values[5] = ((255 - sat) * val) / 255;
    values[4] = values[5];
    values[6] = ((255 - ((255 - frac) * sat) / 255) * val) / 255;

    RGBTripleValue rgb;
    unsigned int index = scaled / 255;
    index += (index > 4) ? -4 : 2;
    rgb.Red = (unsigned char)values[index];
    index += (index > 4) ? -4 : 2;
    rgb.Blue = (unsigned char)values[index];
    index += (index > 4) ? -4 : 2;
    rgb.Green = (unsigned char)values[index];
    return rgb;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x517560
// Branching.
int Obj_00517560::FUN_00517560(Arg1_00517560* a1)
{
    return unknown_00 == a1->unknown_00 && unknown_01 == a1->unknown_01 && unknown_02 == a1->unknown_02;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x517590
// Inequality of two three-byte values (negation of the 0x517560 comparison).
bool Obj_00517560::FUN_00517590(Arg1_00517560* a1)
{
    return !IsSame(a1);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005175E0
bool Obj_005175E0::FUN_005175E0()
{
    return !FUN_005175D0();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5176A0
// True when bit 0 of the flag dword is clear.
bool Obj_005176A0::FUN_005176A0() const
{
    unsigned int t = Bits;
    bool r = !(t & 1);
    return r;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5176B0
// True when bit 1 of the flag dword is clear.
bool Obj_005176A0::FUN_005176B0() const
{
    unsigned int t = Bits;
    unsigned char c = ~t;
    c >>= 1;
    bool r = c & 1;
    return r;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5176C0
// True when bit 2 of the flag dword is clear.
bool Obj_005176A0::FUN_005176C0() const
{
    unsigned int t = Bits;
    unsigned char c = ~t;
    c >>= 2;
    bool r = c & 1;
    return r;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x517310
// True when the X and Y components of both coordinates are equal.
bool HoverCoordView::Fun_00517310(const LocoCoord* other)
{
    return X == other->X && Y == other->Y;
}

// SYNTHETIC: GAMEMD 0x5172F0 -- LocomotionClass scalar deleting destructor, emitted by the compiler from the
// virtual destructor where this TU seats the vtable.
