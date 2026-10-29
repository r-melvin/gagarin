// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | behaviour-confirmed-name
// ObjectClass bodies for primary-table (0x7EF060) slots 53, 54 and 58
// (0x5F4D30, 0x5F4EC0, 0x5F5940); names are placeholders (object_class.h).
#include "../_layout/object_class.h"
#include "../_layout/session_class.h"
#include "../_layout/object_type_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/anim_class.h"


// The logic object list at 0x87F778.
#include "logicview_87f778.h"
#include "../_layout/map_0087f7e8.h"
// GLOBAL: GAMEMD 0x87F778
extern LogicView_87F778 DAT_0087F778;

struct Point2DView
{
    int X;
    int Y;
    Point2DView& operator+=(Point2DView other)
    {
        X += other.X;
        Y += other.Y;
        return *this;
    }
    Point2DView& operator-=(const Point2DView& other)
    {
        X -= other.X;
        Y -= other.Y;
        return *this;
    }
};
struct RectView
{
    RectView(int x, int y, int width, int height) : X(x), Y(y), Width(width), Height(height) {}
    int X;
    int Y;
    int Width;
    int Height;
};
// The shape header behind ObjectTypeClass::AlphaImage.
struct ShapeView
{
    short unknown_0;
    short Width;                     // +0x2
    short Height;                    // +0x4
};
GG_STATIC_ASSERT(offsetof(ShapeView, Height) == 0x4);

// The tactical view behind the pointer 0x887324.
struct TacticalView_887324
{
    char        unknown_0000[0xB0];
    Point2DView unknown_B0;          // +0xB0  the view offset
    // FUNCTION: GAMEMD 0x6D2140 (declaration) -- a coordinate's client position.
    bool FUN_006D2140(const CoordStruct* coord, Point2DView* point);
    // FUNCTION: GAMEMD 0x6D2790 (declaration) -- register a dirty rectangle.
    void FUN_006D2790(RectView rect, bool a2);
};
// GLOBAL: GAMEMD 0x887324
extern TacticalView_887324* DAT_00887324;

// CellClass and AnimClass entry points not declared in their layout headers.
struct CellCallView
{
    // FUNCTION: GAMEMD 0x4834A0 (declaration) -- whether a cell is clear to move into.
    bool FUN_004834A0(int speedType, bool ignoreInfantry, bool ignoreVehicles,
                      int zone, int movementZone, int level, bool onBridge);
};
struct AnimCallView
{
    // FUNCTION: GAMEMD 0x424B50 (declaration) -- set the anim's owner object.
    void FUN_00424B50(ObjectClass* owner);
};

// The TechnoTypeClass fields read here (techno_type_class.h and techno_class.h
// both define TurretControl, so they cannot share this unit).
struct TechnoTypeView_5F5940
{
    char unknown_0000[0x5B4];
    int  MovementZone;               // +0x5B4
    char unknown_05B8[0x67C - 0x5B8];
    int  SpeedType;                  // +0x67C
};
GG_STATIC_ASSERT(offsetof(TechnoTypeView_5F5940, SpeedType) == 0x67C);

// GLOBAL: GAMEMD 0x8871E0
#include "../_layout/rules_class.h"
extern RulesClass* DAT_008871E0;

// A lepton coordinate's cell: each axis divided by 256.
static inline CellStruct CoordCell(const CoordStruct& coord)
{
    CellStruct cell;
    cell.X = (short)(coord.X / 256);
    cell.Y = (short)(coord.Y / 256);
    return cell;
}

// The subclass type field tested when slot 11 reports 0x24.
struct TypeView_5F4EC0
{
    char unknown_0000[0x2B1];
    bool unknown_2B1;                // +0x2B1
};
GG_STATIC_ASSERT(offsetof(TypeView_5F4EC0, unknown_2B1) == 0x2B1);

// The 0x40-byte object 0x5F4EC0 creates for a type with an AlphaImage.
struct Obj_00420960
{
    // FUNCTION: GAMEMD 0x420960 (declaration) -- constructor.
    Obj_00420960(ObjectClass* owner, int x, int y);
    char unknown_00[0x40];
};

// The line trail fields used here (match/renderer/line_trail.h models Color
// as a byte array).
struct LineTrailView
{
    // FUNCTION: GAMEMD 0x556A20 (declaration) -- constructor.
    LineTrailView();
    // FUNCTION: GAMEMD 0x556B50 (declaration) -- set the colour decrement.
    void FUN_00556B50(int decrement);
    ColorStruct  Color;              // +0x00
    ObjectClass* Owner;              // +0x04
    char         unknown_08[0x210 - 0x8];
};
GG_STATIC_ASSERT(offsetof(LineTrailView, Owner) == 0x4);
GG_STATIC_ASSERT(sizeof(LineTrailView) == 0x210);

// GLOBAL: GAMEMD 0xAC1380 -- the invalid coordinate.
extern CoordStruct DAT_00AC1380;
// GLOBAL: GAMEMD 0xA8E7AC
extern int DAT_00A8E7AC;

// GLOBAL: GAMEMD 0xA8E9A0
extern bool DAT_00A8E9A0;

// FUNCTION: GAMEMD 0x5F4D30
bool ObjectClass::vf_53()
{
    if (!DAT_00A8E9A0 || InLimbo) {
        return false;
    }
    vf_84();
    vf_55(1);
    vf_73(0);
    DAT_0087F7E8.FUN_004A9770(this);
    AmbientSoundController.FUN_00405D40();
    CustomSoundController.FUN_00405FD0();
    if (vf_34() != 0 && vf_34()->IsLogic) {
        if (Session_00A8B238.GameMode == 0 || Session_00A8B238.GameMode == 5 || vf_rtti_4() != -2) {
            DAT_0087F778.FUN_0055BAE0(this);
        }
    }
    if (vf_34() != 0 && vf_34()->AlphaImage != 0) {
        CoordStruct coord = vf_18();
        Point2DView point;
        DAT_00887324->FUN_006D2140(&coord, &point);
        ShapeView* image = (ShapeView*)vf_34()->AlphaImage;
        Point2DView half;
        half.X = image->Width / 2;
        half.Y = image->Height / 2;
        point -= half;
        DAT_00887324->FUN_006D2790(RectView(point.X, point.Y, image->Width, image->Height), true);
    }
    vf_71();
    InLimbo = true;
    NeedsRedraw = false;
    return true;
}

// FUNCTION: GAMEMD 0x5F4EC0
// PARTIAL 83.4%: in the black-rules branch retail loads LineTrailer into EDX
// before forming the colour address and copies through ECX; cl copies from EAX,
// which swaps registers through the SetDecrement and Owner stores. Tried
// split `+=`, operator+, a ternary colour, a local trail pointer and a helper.
bool ObjectClass::vf_54(const CoordStruct& coord, int a2)
{
    if (coord.X == DAT_00AC1380.X && coord.Y == DAT_00AC1380.Y && coord.Z == DAT_00AC1380.Z) {
        return false;
    }
    if (!DAT_00A8E9A0 || !InLimbo || IsOnMap) {
        return false;
    }
    if (DAT_00A8E7AC == 0 && vf_107(DAT_0087F7E8.FUN_00565730(&coord), -1, -1, 0, 0) != 0) {
        return false;
    }
    InLimbo = false;
    NeedsRedraw = false;
    ObjectTypeClass* type = vf_34();
    CoordStruct where = coord;
    if (type != 0) {
        where = type->vf_27(coord);
    }
    vf_109(where);
    if (vf_73(1)) {
        if (IsAlive) {
            if (vf_30() != -1) {
                DAT_0087F7E8.FUN_004A9720(this);
            }
            if (type != 0) {
                if (type->IsLogic) {
                    if (vf_11() != 0x24 || (vf_11() == 0x24 && ((TypeView_5F4EC0*)type)->unknown_2B1)) {
                        if (Session_00A8B238.GameMode == 0 || Session_00A8B238.GameMode == 5 || vf_rtti_4() != -2) {
                            DAT_0087F778.FUN_0055BAA0(this, false);
                        }
                    }
                }
                if (type->AlphaImage != 0) {
                    CoordStruct center = vf_18();
                    Point2DView point;
                    DAT_00887324->FUN_006D2140(&center, &point);
                    point += DAT_00887324->unknown_B0;
                    ShapeView* image = (ShapeView*)vf_34()->AlphaImage;
                    Point2DView half;
                    half.X = image->Width / 2;
                    half.Y = image->Height / 2;
                    point -= half;
                    new Obj_00420960(this, point.X, point.Y);
                    if (DAT_00A8E7AC == 0) {
                        DAT_00887324->FUN_006D2790(RectView(point.X - DAT_00887324->unknown_B0.X,
                                                            point.Y - DAT_00887324->unknown_B0.Y,
                                                            image->Width, image->Height), true);
                    }
                }
            }
            if (vf_34()->UseLineTrail) {
                LineTrailer = new LineTrailView;
                if (LineTrailer != 0) {
                    ColorStruct color = DAT_008871E0->unknown_1863;
                    if (color.R == 0 && color.G == 0 && color.B == 0) {
                        ((LineTrailView*)LineTrailer)->Color = vf_34()->LineTrailColor;
                    } else {
                        ((LineTrailView*)LineTrailer)->Color = DAT_008871E0->unknown_1863;
                    }
                    ((LineTrailView*)LineTrailer)->FUN_00556B50(vf_34()->LineTrailColorDecrement);
                    ((LineTrailView*)LineTrailer)->Owner = this;
                }
            }
        }
        return true;
    }
    InLimbo = true;
    return false;
}

// FUNCTION: GAMEMD 0x5F5940
bool ObjectClass::vf_58(const CoordStruct& coord)
{
    if (DAT_0087F7E8.FUN_005785F0(coord)) {
        IsFallingDown = true;
        CellClass* cell = DAT_0087F7E8.FUN_00565730(&coord);
        if (cell != 0) {
            if (cell->Flags & 0x100) {
                OnBridge = true;
                if (!(cell->Flags & 0x200)) {
                    return false;
                }
            }
            bool isTechno = false;
            if (this != 0) {
                isTechno = Flags.IsTechno;
            }
            if (isTechno) {
                int movementZone = ((TechnoTypeView_5F5940*)vf_33())->MovementZone;
                if (!((CellCallView*)cell)->FUN_004834A0(((TechnoTypeView_5F5940*)vf_33())->SpeedType, false, false,
                        DAT_0087F7E8.FUN_0056D230(CoordCell(coord), movementZone, OnBridge),
                        movementZone, -1, true)) {
                    return false;
                }
            }
            if (vf_54(coord, 0x80)) {
                vf_109(coord);
                AnimClass* anim;
                if (vf_11() == 8) {
                    anim = new AnimClass(DAT_008871E0->BombParachute, coord, 0, 1, 0x600, 0, false);
                } else {
                    CoordStruct where = coord;
                    where.Z += 0x4B;
                    anim = new AnimClass(DAT_008871E0->Parachute, where, 0, 1, 0x600, 0, false);
                    Parachute = anim;
                }
                if (anim != 0) {
                    ((AnimCallView*)anim)->FUN_00424B50(this);
                    if (vf_11() != 8) {
                        anim->LightConvert = vf_121();
                        anim->TintColor = (short)vf_111()->Intensity_Normal;
                    }
                }
                return true;
            }
        }
    }
    return false;
}
