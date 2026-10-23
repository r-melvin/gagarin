// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001, confirmed from entry-origin instructions and pinned PE data. | YRpp-cross-check | behaviour-confirmed-name
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// No /GX: none of the matched bodies unwinds (confirmed with a paired /GX probe).
//
// HoverLocomotionClass (leaf of the locomotion module): the hovercraft locomotor.
// Layout, tables and evidence are in hover_locomotion_class.h.

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

static inline HoverCellCoord AddCell(const HoverCellCoord& a, const Pair_0042D490& b)
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

// FUNCTION: GAMEMD 0x513C20
HoverLocomotionClass::HoverLocomotionClass()
    : Destination_(DAT_00A8F180), HeadTo(DAT_00A8F180), Facing(0),
      Speed(0.0), SpeedFactor(0.0), Field_58(1.0), Field_60(0.0),
      IsRocking(false), RockAmount(0), Blocked(false)
{
}

// FUNCTION: GAMEMD 0x513CB0
HRESULT __stdcall HoverLocomotionClass::LinkToObject(FootClass* object)
{
    HRESULT hr = LocomotionClass::LinkToObject(object);
    HoverFacingView facing(HoverFoot(LinkedTo)->Slot_084()->unknown_71C << 1);
    Facing = facing;
    return hr;
}

// FUNCTION: GAMEMD 0x513F40
Matrix3D __stdcall HoverLocomotionClass::DrawMatrix(unsigned int* key)
{
    if (fabs(HoverFoot(LinkedTo)->AngleSideways) < 0.005 && fabs(HoverFoot(LinkedTo)->AngleForwards) < 0.005) {
        if (!IsPowered()) {
            LocoCoord location = HoverFoot(LinkedTo)->Location;
            int slope = HoverMap().GetCellAt(&location)->SlopeIndex;
            Matrix3D m = HoverSlopeMatrix(slope);
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
    HoverMatrixView lift;
    lift.MakeIdentity();
    HoverMatrixView tilt;
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
    HoverMatrixView base;
    base = LocomotionClass::DrawMatrix(key);
    return HoverMatrixMultiply(&HoverMatrixMultiply(&lift, &base), &tilt);
}

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

// FUNCTION: GAMEMD 0x514C30
bool __stdcall HoverLocomotionClass::IsMoving()
{
    return IsCoordSet(Destination_) || IsCoordSet(HeadTo);
}

// FUNCTION: GAMEMD 0x514C80
bool __stdcall HoverLocomotionClass::IsMovingNow()
{
    return IsMoving() && Speed != 0.0;
}

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

// FUNCTION: GAMEMD 0x516370
void __stdcall HoverLocomotionClass::DoTurn(unsigned long dir)
{
    HoverDirView d;
    d.Raw = dir;
    HoverFoot(LinkedTo)->PrimaryFacing.SetDesired(&d);
}

// FUNCTION: GAMEMD 0x516BF0
bool __stdcall HoverLocomotionClass::PowerOff()
{
    if (IsPowered()) {
        int state = HoverFoot(LinkedTo)->unknown_0AC;
        if (state != 0 && state != 7) {
            IsRocking = true;
            RockAmount = DAT_00A8B230->Random.RandomRanged(20, 30);
            if (DAT_00A8B230->Random.RandomRanged(0, 99) < 50)
                RockAmount = -RockAmount;
        }
    }
    if (IsMoving())
        StopMoving();
    return LocomotionClass::PowerOff();
}

// FUNCTION: GAMEMD 0x516C70
bool __stdcall HoverLocomotionClass::IsPowered()
{
    if (LocomotionClass::IsPowered() || HoverFoot(LinkedTo)->Slot_1C8() > 0)
        return true;
    return false;
}

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

// FUNCTION: GAMEMD 0x516E10
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
                LocoCoord* head = &HeadTo;
                if (!(head->X == DAT_00A8F180.X && head->Y == DAT_00A8F180.Y && head->Z == DAT_00A8F180.Z))
                    HoverFoot(LinkedTo)->Slot_0F4(head);
                *head = CellCenter(next);
                HeadTo.Z = HoverMap().GetHeightAt(head);
                LocoCoord location = HoverFoot(LinkedTo)->Location;
                if (location.Z >= HeadTo.Z + DAT_00A8F1C0 * 3)
                    HeadTo.Z += DAT_00A8F1B4;
                HoverFoot(LinkedTo)->Slot_0F0(head);
                return true;
            }
            MoveTo(CellCenter(next));
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x516FC0
bool __stdcall HoverLocomotionClass::Shove(unsigned long dir)
{
    if (Push(dir)) {
        IsRocking = true;
        RockAmount = DAT_00A8B230->Random.RandomRanged(20, 30);
        if (DAT_00A8B230->Random.RandomRanged(0, 99) < 50)
            RockAmount = -RockAmount;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x517070
HRESULT __stdcall HoverLocomotionClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = CLSID_HoverLocomotion;
    return S_OK;
}

// FUNCTION: GAMEMD 0x5170B0
HRESULT __stdcall HoverLocomotionClass::Load(IStream* pStm)
{
    HRESULT hr = LocomotionClass::Load(pStm);
    if (hr >= 0)
        new (this) HoverLocomotionClass(0);
    return hr;
}

// FUNCTION: GAMEMD 0x517100
int __stdcall HoverLocomotionClass::InWhichLayer()
{
    return 2;
}

// FUNCTION: GAMEMD 0x5171C0
void __stdcall HoverLocomotionClass::MarkAllOccupationBits(int mark)
{
    if (mark == 0) {
        LocoCoord coord = HeadToCoord();
        HoverFoot(LinkedTo)->Slot_0F4(&coord);
    }
}

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
// FUNCTION: GAMEMD 0x5172B0
int HoverLocomotionClass::Size()
{
    return sizeof(HoverLocomotionClass);
}


// SYNTHETIC: GAMEMD 0x5172C0
// Compiler-generated scalar deleting destructor from the native declaration.
