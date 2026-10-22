// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// BuildingClass entries 0x453A70..0x454260 of the "building-b" cluster (views: building_b_views.h).

#include <new.h>
#include "building_b_views.h"

// FUNCTION: GAMEMD 0x453A70
// The shared tail (vf_43 plus the pixel offset) sits inside the first block in retail and is entered by a
// goto from the type-offset path.
HBCoord* BuildingBView::vf_192(HBCoord* out, int a)
{
    HBCoord tmp;
    HBPoint2D* offset;
    int ox;
    int oy;
    if (Type->unknown_157B && vf_258() > 0) {
        HBPoint2D pixel;
        offset = BuildingBTactical->Func_6D2070(&pixel, &Type->OccupyPoints[FiringOccupantIndex]);
        ox = offset->X;
        oy = offset->Y;
tail:
        HBCoord* c = vf_43(&tmp);
        out->X = c->X + ox;
        out->Y = c->Y + oy;
        out->Z = c->Z;
        return out;
    }
    BuildingBTypeView* type = Type;
    if (type->PointE44.X == 0xFFFF && type->PointE44.Y == 0xFFFF) {
        if (type->unknown_16C6) {
            *out = *Func_453BF0(&tmp, a, 0);
            return out;
        }
        HBCoord* c = Func_6F3D60(&tmp, a);
        int x = c->X;
        int y = c->Y;
        int z = c->Z;
        if (Type->unknown_16C5) {
            HBPoint2D q = Type->PointOffset;
            HBPoint2D pixel;
            HBPoint2D* o = BuildingBTactical->Func_6D2070(&pixel, &q);
            x += o->X;
            y += o->Y;
        }
        out->X = x;
        out->Y = y;
        out->Z = z;
        return out;
    }
    HBPoint2D pixel2;
    offset = BuildingBTactical->Func_6D2070(&pixel2, &type->PointE44);
    ox = offset->X;
    oy = offset->Y;
    goto tail;
}

// FUNCTION: GAMEMD 0x453D60
void BuildingBView::vf_60(HBCoord* coord)
{
    HBCell cell = BuildingBCellOf(*coord);
    unsigned int& flags = BuildingBMap.Func_5657A0(&cell)->Flags;
    flags |= 0x80;
}

// FUNCTION: GAMEMD 0x453DC0
void BuildingBView::vf_61(HBCoord* coord)
{
    HBCell cell = BuildingBCellOf(*coord);
    unsigned int& flags = BuildingBMap.Func_5657A0(&cell)->Flags;
    flags &= ~0x80u;
}

// FUNCTION: GAMEMD 0x453E20
HRESULT __stdcall BuildingBView::Load(IStream* pStm)
{
    int id = Rtti.Fetch_ID();
    BuildingBAbstractIndex.RemoveIndex(id);
    HRESULT hr = Func_70BF50(pStm);
    if (hr < 0)
        return hr;
    new (this) BuildingBView(HBNoInit());
    int newId = Rtti.Fetch_ID();
    BuildingBAbstractIndex.AddIndexOutOfLine(newId, this);
    BuildingBSwizzle.Swizzle(&Type);
    BuildingBSwizzle.Swizzle(&Factory);
    BuildingBSwizzle.Swizzle(&C4AppliedBy);
    BuildingBSwizzle.Swizzle(&FirestormAnim);
    BuildingBSwizzle.Swizzle(&PsiWarnAnim);
    BuildingBSwizzle.Swizzle(&Spotlight);
    Audio7.Func_405BE0();
    Audio8.Func_405BE0();
    BuildingBSwizzle.Swizzle(&SecretProduction);
    int count;
    int i;
    HRESULT r = pStm->Read(&count, 4, 0);
    if (r < 0)
        return r;
    for (i = 0; i < count; i++) {
        void* item;
        r = pStm->Read(&item, 4, 0);
        if (r < 0)
            return r;
        Overpowerers.AddItem(item);
    }
    for (i = 0; i < count; i++)
        BuildingBSwizzle.Swizzle(&Overpowerers.Items[i]);
    r = pStm->Read(&count, 4, 0);
    if (r < 0)
        return r;
    for (i = 0; i < count; i++) {
        BuildingBOccupantView* item;
        r = pStm->Read(&item, 4, 0);
        if (r < 0)
            return r;
        Occupants.AddItem(item);
    }
    for (i = 0; i < count; i++)
        BuildingBSwizzle.Swizzle(&Occupants.Items[i]);
    for (i = 0; i < 21; i++)
        BuildingBSwizzle.Swizzle(&Anims[i]);
    for (i = 0; i < 3; i++)
        BuildingBSwizzle.Swizzle(&Upgrades[i]);
    for (i = 0; i < 8; i++)
        BuildingBSwizzle.Swizzle(&DamageFireAnims[i]);
    LightSource = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x454190
HRESULT __stdcall BuildingBView::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = Func_70C250(pStm, fClearDirty);
    if (hr < 0)
        return hr;
    int i;
    int count = Overpowerers.Count;
    HRESULT w = pStm->Write(&count, 4, 0);
    if (w < 0)
        return w;
    for (i = 0; i < count; i++) {
        w = pStm->Write(&Overpowerers.Items[i], 4, 0);
        if (w < 0)
            return w;
    }
    count = Occupants.Count;
    w = pStm->Write(&count, 4, 0);
    if (w < 0)
        return w;
    for (i = 0; i < count; i++) {
        w = pStm->Write(&Occupants.Items[i], 4, 0);
        if (w < 0)
            return w;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x454250
bool BuildingBView::vf_128()
{
    return IsReadyToCommence ? true : false;
}

// FUNCTION: GAMEMD 0x454260
void BuildingBView::vf_13(BuildingBCrcView* crc)
{
    Func_70C270(crc);
    int c4Left = C4Timer.GetTimeLeft();
    crc->AddInt(c4Left);
    int cashLeft = CashProductionTimer.GetTimeLeft();
    crc->AddInt(cashLeft);
    crc->AddInt(BState);
    crc->AddInt(QueueBState);
    crc->AddInt(OwnerCountryIndex);
    if (C4AppliedBy)
        crc->AddInt(C4AppliedBy->Rtti.Fetch_ID());
    crc->AddInt(unknown_544);
    if (FirestormAnim)
        crc->AddInt(FirestormAnim->Rtti.Fetch_ID());
    crc->AddInt(FactoryRetryTimer.GetTimeLeft());
    crc->AddInt(unknown_5FC);
    crc->AddInt(LaserFenceFrame);
    crc->AddInt(FirestormWallFrame);
    crc->AddBool(HasPower);
    crc->AddBool(StuffEnabled);
    crc->AddBool(BeingProduced);
    crc->AddBool(ShouldRebuild);
    crc->AddBool(unknown_6DC);
    crc->AddBool(IsReadyToCommence);
    crc->AddBool(IsBeingRepaired);
    crc->AddBool(NeedsRepairs);
    crc->AddBool(C4Applied);
    crc->AddBool(NoCrew);
    crc->AddBool(unknown_bool_6E1);
    crc->AddBool(unknown_bool_6E2);
    crc->AddBool(HasBeenCaptured);
    crc->AddBool(ActuallyPlacedOnMap);
    crc->AddBool(HasEngineer);
    crc->AddBool(unknown_bool_6E5);
    crc->AddBool(IsDamaged);
    crc->AddInt((unsigned short)unknown_short_700);
    crc->AddByte(UpgradeLevel);
}
