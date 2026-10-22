// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// ObjectClass bodies for primary-table (0x7EF060) slots 83, 74 and 75
// (0x5F4520, 0x5F4730, 0x5F4870); names are placeholders (object_class.h).
#include "../_layout/object_class.h"
#include "../_layout/geometry2d.h"
#include "../_layout/object_type_class.h"
#include <string.h>

// The tactical view behind the global pointer 0x887324.
class Tactical
{
public:
    // FUNCTION: GAMEMD 0x6D2140 (declaration) -- project a coordinate to a client point.
    bool CoordsToClient(const CoordStruct* coord, Point2D* point);
};
// GLOBAL: GAMEMD 0x887324
extern Tactical* DAT_00887324;

// The shape returned by slot 27.
struct ShapeView_5F4730
{
    // FUNCTION: GAMEMD 0x69E7E0 (declaration) -- a frame's rectangle.
    RectangleStruct FUN_0069E7E0(int frame);

    short unknown_00;
    short Width;                     // +0x02
    short Height;                    // +0x04
    short unknown_06;                // +0x06  frame count
};
GG_STATIC_ASSERT(offsetof(ShapeView_5F4730, Width) == 0x02);
GG_STATIC_ASSERT(offsetof(ShapeView_5F4730, Height) == 0x04);

// GLOBAL: GAMEMD 0x886FA0 -- the tactical view rectangle.
extern RectangleStruct DAT_00886FA0;
// GLOBAL: GAMEMD 0xAC1350 -- the empty rectangle.
extern RectangleStruct DAT_00AC1350;

// GLOBAL: GAMEMD 0xA8ED6B
extern bool DAT_00A8ED6B;

// The object FUN_0040DD70 answers (a techno), seen through its flag at +0x3D4.
struct TechnoView_5F4520 : ObjectClass
{
    char unknown_00AC[0x3D4 - 0xAC];
    bool unknown_3D4;                // +0x3D4
};
GG_STATIC_ASSERT(offsetof(TechnoView_5F4520, unknown_3D4) == 0x3D4);

// FUNCTION: GAMEMD 0x40DD70 (decl; reloc) -- the object if it is a techno, else null.
TechnoView_5F4520* FUN_0040DD70(ObjectClass* object);

// The house slot 15 answers.
struct HouseView_5F4520
{
    // FUNCTION: GAMEMD 0x50B6F0 (declaration) -- controlled by the current player.
    bool FUN_0050B6F0();
};

// The type slot 34 answers, seen through its flag at +0xC9C.
struct TypeView_5F4520
{
    char unknown_0000[0xC9C];
    bool unknown_C9C;                // +0xC9C
};
GG_STATIC_ASSERT(offsetof(TypeView_5F4520, unknown_C9C) == 0xC9C);

// The selected-objects vector at 0xA8ECB8.
class SelectionVector
{
public:
    virtual ~SelectionVector();
    virtual bool vf_1(const SelectionVector& other) const;
    virtual bool vf_2(int capacity, ObjectClass** items);

    bool AddHead(ObjectClass* object)
    {
        if (Count >= Capacity) {
            if ((IsAllocated || !Capacity) && CapacityIncrement > 0) {
                if (!vf_2(Capacity + CapacityIncrement, NULL)) {
                    return false;
                }
            } else {
                return false;
            }
        }
        if (Count) {
            memmove(Items + 1, Items, Count * sizeof(ObjectClass*));
        }
        Items[0] = object;
        Count++;
        return true;
    }
    bool Add(ObjectClass* object)
    {
        if (Count >= Capacity) {
            if ((IsAllocated || !Capacity) && CapacityIncrement > 0) {
                if (!vf_2(CapacityIncrement + Capacity, NULL)) {
                    return false;
                }
            } else {
                return false;
            }
        }
        int index = Count++;
        Items[index] = object;
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

// GLOBAL: GAMEMD 0x880990
extern int DAT_00880990;
// FUNCTION: GAMEMD 0x48DC90 (decl; reloc) -- deselect everything.
void __cdecl FUN_0048DC90();
// FUNCTION: GAMEMD 0x731D00 (decl; reloc)
void FUN_00731D00(int a1);

// FUNCTION: GAMEMD 0x5F4520
// PARTIAL 97.8%: two register pairs swap in the inlined vector adds
// (retail `ADD EAX,ECX; PUSH EAX` in the head-insert path, the reverse in the
// append path). Tried both operand orders of Capacity + CapacityIncrement,
// `Capacity <= Count` and a duplicated tail; permuter candidate.
bool ObjectClass::vf_83()
{
    if (!DAT_00A8ED6B && (InLimbo || IsSelected || !vf_78())) {
        return false;
    }
    TechnoView_5F4520* techno = FUN_0040DD70(this);
    if (!DAT_00A8ED6B && vf_40() && techno != NULL && techno->unknown_3D4) {
        return false;
    }
    if (techno != NULL && techno->vf_117()) {
        return false;
    }
    if (DAT_00880990) {
        return false;
    }
    if (DAT_00A8ECB8.Count > 0) {
        HouseView_5F4520* house = (HouseView_5F4520*)vf_15();
        HouseView_5F4520* first = (HouseView_5F4520*)DAT_00A8ECB8.Items[0]->vf_15();
        if (first->FUN_0050B6F0() != house->FUN_0050B6F0() || !first->FUN_0050B6F0()) {
            FUN_0048DC90();
        }
    }
    bool isTechno = false;
    if (this != NULL) {
        isTechno = Flags.IsTechno;
    }
    if (isTechno && ((TypeView_5F4520*)vf_34())->unknown_C9C) {
        DAT_00A8ECB8.AddHead(this);
    } else {
        DAT_00A8ECB8.Add(this);
    }
    FUN_00731D00(0);
    IsSelected = true;
    return true;
}

// The type of a building, seen through the fields slot 75 reads.
// FUNCTION: GAMEMD 0x5F4730
// PARTIAL 65.2%: register choice only; retail keeps the shape in EDI and
// the view Y in EDI/ESI where cl uses ESI/EDX, and returns the empty rectangle
// inline on the null path. Tried two forms of the X/Y arithmetic.
RectangleStruct ObjectClass::vf_74()
{
    Point2D point;
    DAT_00887324->CoordsToClient(&vf_43(), &point);
    ShapeView_5F4730* shape = (ShapeView_5F4730*)vf_27();
    if (shape == NULL) {
        return DAT_00AC1350;
    }
    RectangleStruct rect = shape->FUN_0069E7E0(0);
    rect.X -= shape->Width / 2;
    rect.X += point.X;
    rect.Y -= shape->Height / 2;
    rect.Y += point.Y;
    int left = DAT_00886FA0.X + rect.X;
    int top = DAT_00886FA0.Y + rect.Y;
    if (DAT_00886FA0.X < left + rect.Width
        && DAT_00886FA0.Y < top + rect.Height
        && DAT_00886FA0.X + DAT_00886FA0.Width > left
        && DAT_00886FA0.Y + DAT_00886FA0.Height > top) {
        return rect;
    }
    return DAT_00AC1350;
}

// GLOBAL: GAMEMD 0xA8ED6B
struct BuildingTypeView_5F4870
{
    char              unknown_0000[0x1518];
    ShapeView_5F4730* unknown_1518;  // +0x1518  an extra shape drawn with the building
    char              unknown_151C[0x16C0 - 0x151C];
    bool              unknown_16C0;  // +0x16C0  frames start at 15
};
GG_STATIC_ASSERT(offsetof(BuildingTypeView_5F4870, unknown_1518) == 0x1518);
GG_STATIC_ASSERT(offsetof(BuildingTypeView_5F4870, unknown_16C0) == 0x16C0);

// A building, seen through its type pointer at +0x520.
struct BuildingView_5F4870 : ObjectClass
{
    char                     unknown_00AC[0x520 - 0xAC];
    BuildingTypeView_5F4870* unknown_520;   // +0x520
};
GG_STATIC_ASSERT(offsetof(BuildingView_5F4870, unknown_520) == 0x520);

// The smallest rectangle holding both, or the other one when the first is
// empty.
static inline RectangleStruct Union(RectangleStruct a, const RectangleStruct& b)
{
    if (a.Width <= 0 || a.Height <= 0) {
        return b;
    }
    if (b.Width > 0 && b.Height > 0) {
        if (a.X > b.X) {
            a.Width += a.X - b.X;
            a.X = b.X;
        }
        if (a.Y > b.Y) {
            a.Height += a.Y - b.Y;
            a.Y = b.Y;
        }
        if (a.X + a.Width < b.X + b.Width) {
            a.Width = b.Width - a.X + b.X + 1;
        }
        if (a.Y + a.Height < b.Y + b.Height) {
            a.Height = b.Height - a.Y + b.Y + 1;
        }
    }
    return a;
}

// FUNCTION: GAMEMD 0x5F4870
// PARTIAL 25.8%: retail keeps both frame rectangles partly in registers in
// a 0x44 frame; cl uses 0x5C, shifting later offsets, and emits two INC where
// retail has LEA [x+y+1]. Tried a direct Union call (8.4%), width/height read
// before the second frame (23.5%) and Union by value (21.0%, 25.5%).
RectangleStruct ObjectClass::vf_75()
{
    Point2D point;
    DAT_00887324->CoordsToClient(&vf_43(), &point);
    ShapeView_5F4730* shape = (ShapeView_5F4730*)vf_34()->vf_39();
    if (shape == NULL) {
        return DAT_00AC1350;
    }
    int frame = 0;
    if (vf_11() == 6 && ((BuildingView_5F4870*)this)->unknown_520->unknown_16C0) {
        frame = 15;
    }
    RectangleStruct rect = shape->FUN_0069E7E0(frame);
    RectangleStruct second = shape->FUN_0069E7E0(shape->unknown_06 / 2 + frame);
    int width = shape->Width;
    int height = shape->Height;
    rect = Union(rect, second);
    if (vf_11() == 6) {
        ShapeView_5F4730* extra = ((BuildingView_5F4870*)this)->unknown_520->unknown_1518;
        if (extra != NULL) {
            rect = Union(rect, extra->FUN_0069E7E0(0));
        }
    }
    rect.X = rect.X - width / 2 + point.X;
    rect.Y = rect.Y - height / 2 + point.Y;
    return rect;
}

// GLOBAL: GAMEMD 0xB73550 -- the main window.
extern void* DAT_00B73550;

// The overlap of two rectangles, or an empty rectangle when they do not meet.
static inline RectangleStruct Intersect(RectangleStruct r, const RectangleStruct& b)
{
    RectangleStruct result = { 0, 0, 0, 0 };
    if (b.Width > 0 && b.Height > 0 && r.Width > 0 && r.Height > 0) {
        if (r.X < b.X) {
            r.Width += r.X - b.X;
            r.X = b.X;
        }
        if (r.Width >= 1) {
            if (r.Y < b.Y) {
                r.Height += r.Y - b.Y;
                r.Y = b.Y;
            }
            if (r.Height >= 1) {
                if (r.X + r.Width > b.X + b.Width) {
                    r.Width = b.X - r.X + b.Width;
                }
                if (r.Width >= 1) {
                    if (r.Y + r.Height > b.Y + b.Height) {
                        r.Height = b.Y + b.Height - r.Y;
                    }
                    if (r.Height >= 1) {
                        result = r;
                    }
                }
            }
        }
    }
    return result;
}

// FUNCTION: GAMEMD 0x5F4B10
// PARTIAL 1.2% (28.5% aligned): retail keeps the clip rectangle's copy on the
// stack and the result in EAX/ECX/EDX/ESI in a 0x20 frame, pushing EBX/EBP/EDI
// only after the early exits; cl zeroes EBX up front and uses a 0x28 frame.
// Tried two separate early-exit tests (0.6%), Intersect over a const& copy
// (0.6%) and a zeroed result rectangle (1.2%, kept).
bool ObjectClass::vf_65(RectangleStruct* a1, bool a2, int a3)
{
    if (!DAT_00A8ED6B && DAT_00B73550 != NULL && ((!a2 && !NeedsRedraw) || InLimbo)) {
        return false;
    }
    NeedsRedraw = false;
    Point2D point;
    if (!DAT_00887324->CoordsToClient(&vf_43(), &point) && vf_11() != 0x18) {
        return false;
    }
    *a1 = Intersect(DAT_00886FA0, *a1);
    if (a1->X > DAT_00886FA0.X) {
        point.X += DAT_00886FA0.X - a1->X;
    }
    if (a1->Y > DAT_00886FA0.Y) {
        point.Y += DAT_00886FA0.Y - a1->Y;
    }
    vf_69(&point, a1);
    return true;
}
