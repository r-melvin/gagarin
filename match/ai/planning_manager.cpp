// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The PlanMgr.cpp block (0x633400..0x634798) in retail address order: the
// run-time initialisers of its globals, then the PlanningMemberClass,
// PlanningBranchClass and PlanningNodeClass bodies. The classes are declared
// in planning_manager.h.
//
// The block was built with auto-inlining (/Ob2): small bodies (the member
// constructor 0x633A20, the view-point helper 0x6339E0, the rectangle helper
// 0x634510) appear both out of line and expanded inside other callers, and
// each list initialiser carries its atexit registration inline.
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy

#include "planning_manager.h"

// The tactical view (pointer global 0x887324): world coordinate to view point.
struct PlanningTactical
{
    // FUNCTION: GAMEMD 0x6D2140 (decl; reloc) -- RET 8.
    void FUN_006D2140(const CoordStruct* coord, Point2D* out);
};
// GLOBAL: GAMEMD 0x887324
extern PlanningTactical* DAT_00887324;
// GLOBAL: GAMEMD 0x886FA0 -- the view origin added to every converted point.
extern Point2D DAT_00886FA0;

// ---- Run-time initialised globals ------------------------------------------------------------------------------------
// In __xc order (0x814468..0x8144B4); each definition below produces one compiler-generated initialiser.

// GLOBAL: GAMEMD 0xAC4BE8
extern double DAT_00AC4BE8;
// The two named constants the initialisers read from memory (0x7EFDF0, 0x7EFDF8); literal factors such as 45.0 and
// 60.0 come from the shared constant pool instead.
// GLOBAL: GAMEMD 0x7EFDF0
const double DAT_007EFDF0 = 60.0;
// GLOBAL: GAMEMD 0x7EFDF8
const double DAT_007EFDF8 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// SYNTHETIC: GAMEMD 0x633400
// GLOBAL: GAMEMD 0xAC4CE8
double DAT_00AC4CE8 = DAT_00AC4BE8 / DAT_007EFDF0;
// SYNTHETIC: GAMEMD 0x633420
// GLOBAL: GAMEMD 0xAC4CC0
double DAT_00AC4CC0 = 1.0 / DAT_00AC4CE8;
// SYNTHETIC: GAMEMD 0x633440
// GLOBAL: GAMEMD 0xAC4CB8
double DAT_00AC4CB8 = DAT_007EFDF8 * 45.0;
// SYNTHETIC: GAMEMD 0x633460
// GLOBAL: GAMEMD 0xAC4C10
double DAT_00AC4C10 = DAT_007EFDF8 * 60.0;
// SYNTHETIC: GAMEMD 0x633480
// GLOBAL: GAMEMD 0xAC4B68
double DAT_00AC4B68 = DAT_007EFDF8 * 90.0;
// SYNTHETIC: GAMEMD 0x6334A0
// GLOBAL: GAMEMD 0xAC4CF0
int DAT_00AC4CF0 = (int)(FUN_004CAD50(DAT_00AC4B68 - DAT_00AC4C10) * DAT_00AC4BE8 * 0.5);
// SYNTHETIC: GAMEMD 0x6334E0
// GLOBAL: GAMEMD 0xAC4C30
double DAT_00AC4C30 = FUN_004CADE0(DAT_00AC4CF0 * 0.00390625);
// SYNTHETIC: GAMEMD 0x633510
// GLOBAL: GAMEMD 0xAC4C70
double DAT_00AC4C70 = FUN_004CADE0((DAT_00AC4CF0 * 2) / DAT_00AC4BE8);
// SYNTHETIC: GAMEMD 0x633540
// GLOBAL: GAMEMD 0xAC4CE4
int DAT_00AC4CE4 = (int)(DAT_00AC4CF0 * 4 + 0.5);

// The next four objects are filled at run time: retail's __xc table lists 0x633570, 0x633580, 0x6335A0 and 0x6335C0
// as initialisers that store constants, which VC6 emits only for a constructor call (a brace initialiser would be
// static data). So their types had constructors; the aggregate layout types in this tree have none, and these views
// supply them (stores in the order retail makes them).
struct PlanningCellInit : CellStruct
{
    PlanningCellInit(short x, short y) { X = x; Y = y; }
};
struct PlanningCoordInit : CoordStruct
{
    PlanningCoordInit(int x, int y, int z) { X = x; Y = y; Z = z; }
};
struct PlanningRectInit : RectangleStruct
{
    PlanningRectInit(int x, int y, int w, int h) { X = x; Y = y; Width = w; Height = h; }
};
// SYNTHETIC: GAMEMD 0x633570
// GLOBAL: GAMEMD 0xAC4BE4
PlanningCellInit DAT_00AC4BE4(0, 0);
// SYNTHETIC: GAMEMD 0x633580
// GLOBAL: GAMEMD 0xAC4C58
PlanningCoordInit DAT_00AC4C58(0, 0, 0);
// SYNTHETIC: GAMEMD 0x6335A0
// GLOBAL: GAMEMD 0xAC4CD8
PlanningCoordInit DAT_00AC4CD8(128, 128, 0);
// SYNTHETIC: GAMEMD 0x6335C0
// GLOBAL: GAMEMD 0xAC4B70
PlanningRectInit DAT_00AC4B70(0, 0, 0, 0);

// SYNTHETIC: GAMEMD 0x6335E0 -- initializer: EventClass list, guard byte 0xAC4B61
// SYNTHETIC: GAMEMD 0x633620 -- cleanup callback: EventClass list, guard byte 0xAC4B61
// SYNTHETIC: GAMEMD 0x633680 -- initializer: node list, guard byte 0xAC4B60
// SYNTHETIC: GAMEMD 0x6336C0 -- cleanup callback: node list, guard byte 0xAC4B60
// SYNTHETIC: GAMEMD 0x633720 -- initializer: TechnoClass list, guard byte 0xAC4B63
// SYNTHETIC: GAMEMD 0x633760 -- cleanup callback: TechnoClass list, guard byte 0xAC4B63
// SYNTHETIC: GAMEMD 0x6337C0 -- initializer: node list, guard byte 0xAC4B62 bit 0
// SYNTHETIC: GAMEMD 0x633800 -- cleanup callback: node list, guard byte 0xAC4B62 bit 0
// SYNTHETIC: GAMEMD 0x633860 -- initializer: node list, guard byte 0xAC4B62 bit 1
// SYNTHETIC: GAMEMD 0x6338A0 -- cleanup callback: node list, guard byte 0xAC4B62 bit 1
// SYNTHETIC: GAMEMD 0x633900 -- initializer: token list, guard byte 0xAC4B62 bit 2
// SYNTHETIC: GAMEMD 0x633940 -- cleanup callback: token list, guard byte 0xAC4B62 bit 2
DynamicVectorClass<EventClass*> PlanningLists::DAT_00AC4B48;
DynamicVectorClass<PlanningNodeClass*> PlanningLists::DAT_00AC4C98;
DynamicVectorClass<TechnoClass*> PlanningLists::DAT_00AC4C40;
DynamicVectorClass<PlanningNodeClass*> PlanningLists::DAT_00AC4B30;
DynamicVectorClass<PlanningNodeClass*> PlanningLists::DAT_00AC4C18;
DynamicVectorClass<PlanningTokenClass*> PlanningLists::DAT_00AC4C78;

// A global whose constructor does nothing; retail keeps its empty initialiser (0x6339A0, a lone RET, listed in __xc).
struct PlanningEmptyInit
{
    PlanningEmptyInit() {}
};
// SYNTHETIC: GAMEMD 0x6339A0
PlanningEmptyInit unknown_006339A0;

// FUNCTION: GAMEMD 0x0063ECA0
// FUNCTION: GAMEMD 0x0063ED40
// FUNCTION: GAMEMD 0x0063EF20
// The scalar deleting destructors in slot 0 of DynamicVectorClass<PlanningMemberClass*> (0x7EFEE4, locator 0x808070),
// DynamicVectorClass<PlanningBranchClass*> (0x7EFEC4, locator 0x808008) and DynamicVectorClass<PlanningTokenClass*>
// (0x7EFE84, locator 0x807F70 -> `.?AV?$DynamicVectorClass@PAVPlanningTokenClass@@@@`); this object emits all
// three tables.

// GLOBAL: GAMEMD 0xAC4CCC
extern PlanningNodeClass* DAT_00AC4CCC;
// GLOBAL: GAMEMD 0xAC4C38
extern PlanningNodeClass* DAT_00AC4C38;
// GLOBAL: GAMEMD 0xAC4BF0
extern PlanningNodeClass* DAT_00AC4BF0;

// FUNCTION: GAMEMD 0x6339E0
// The view point of a world coordinate.
Point2D* FUN_006339E0(Point2D* out, const CoordStruct& coord)
{
    Point2D point;
    DAT_00887324->FUN_006D2140(&coord, &point);
    point.X += DAT_00886FA0.X;
    point.Y += DAT_00886FA0.Y;
    *out = point;
    return out;
}

// FUNCTION: GAMEMD 0x633A20
PlanningMemberClass::PlanningMemberClass()
    : Owner(0), Event(0), unknown_08(-1), unknown_0C(false)
{
}

// FUNCTION: GAMEMD 0x633A40
void PlanningMemberClass::FUN_00633A40(TechnoClass* owner)
{
    Owner = owner;
}

// FUNCTION: GAMEMD 0x633A50
void PlanningMemberClass::FUN_00633A50(EventClass* event)
{
    Event = event;
}

// FUNCTION: GAMEMD 0x633A60
void PlanningMemberClass::FUN_00633A60(int branch)
{
    unknown_08 = branch;
}

// FUNCTION: GAMEMD 0x633A70
void PlanningMemberClass::FUN_00633A70(bool flag)
{
    unknown_0C = flag;
}

// FUNCTION: GAMEMD 0x633A80
TechnoClass* PlanningMemberClass::FUN_00633A80()
{
    return Owner;
}

// FUNCTION: GAMEMD 0x633A90
EventClass* PlanningMemberClass::FUN_00633A90()
{
    return Event;
}

// FUNCTION: GAMEMD 0x633AA0
int PlanningMemberClass::FUN_00633AA0()
{
    return unknown_08;
}

// FUNCTION: GAMEMD 0x633AB0
bool PlanningMemberClass::FUN_00633AB0()
{
    return unknown_0C;
}

// FUNCTION: GAMEMD 0x633AC0
PlanningBranchClass::PlanningBranchClass()
    : unknown_70(0), unknown_74(-1)
{
}

// FUNCTION: GAMEMD 0x633AE0
void PlanningBranchClass::FUN_00633AE0(const EventClass* event)
{
    Event = *event;
}

// FUNCTION: GAMEMD 0x633B00
void PlanningBranchClass::FUN_00633B00(int count)
{
    unknown_70 = count;
}

// FUNCTION: GAMEMD 0x633B10
void PlanningBranchClass::FUN_00633B10(int value)
{
    unknown_74 = value;
}

// FUNCTION: GAMEMD 0x633B20
void PlanningBranchClass::FUN_00633B20()
{
    unknown_70 = 0;
}

// FUNCTION: GAMEMD 0x633B30
int PlanningBranchClass::FUN_00633B30()
{
    return ++unknown_70;
}

// FUNCTION: GAMEMD 0x633B40
int PlanningBranchClass::FUN_00633B40()
{
    return --unknown_70;
}

// FUNCTION: GAMEMD 0x633B50
EventClass PlanningBranchClass::FUN_00633B50()
{
    return Event;
}

// FUNCTION: GAMEMD 0x633B70
int PlanningBranchClass::FUN_00633B70()
{
    return unknown_70;
}

// FUNCTION: GAMEMD 0x633B80
int PlanningBranchClass::FUN_00633B80()
{
    return unknown_74;
}

CoordStruct* FUN_00633BC0(CoordStruct* out, const EventClass& event);

// FUNCTION: GAMEMD 0x633B90
CoordStruct PlanningBranchClass::FUN_00633B90()
{
    CoordStruct coord;
    CoordStruct result = *FUN_00633BC0(&coord, Event);
    return result;
}

// FUNCTION: GAMEMD 0x633BC0
// The coordinate a mission event points at: its target, else its follow
// object, else its destination; (-1,-1,-1) when none resolves.
CoordStruct* FUN_00633BC0(CoordStruct* out, const EventClass& event)
{
    if (event.Type == EVENT_MEGAMISSION) {
        TargetAbstract* object;
        if (event.Data.MegaMission.Target.RTTI) {
            object = event.Data.MegaMission.Target.FUN_006E6E20();
            if (object) {
                *out = object->vf_22();
                return out;
            }
        } else if (event.Data.MegaMission.Follow.RTTI) {
            object = event.Data.MegaMission.Follow.FUN_006E6E20();
            if (object) {
                *out = object->vf_22();
                return out;
            }
        } else if (event.Data.MegaMission.Destination.RTTI) {
            object = event.Data.MegaMission.Destination.FUN_006E6E20();
            if (object) {
                *out = object->vf_22();
                return out;
            }
        }
    }
    CoordStruct none = { -1, -1, -1 };
    *out = none;
    return out;
}

// The coordinate of an event as a value (no retail body of its own; it
// expands where callers copy the result of 0x633BC0 into a local).
inline CoordStruct PlanningCoordOf(const EventClass& event)
{
    CoordStruct tmp;
    return *FUN_00633BC0(&tmp, event);
}

// FUNCTION: GAMEMD 0x633C60
Point2D* PlanningBranchClass::FUN_00633C60(Point2D* out)
{
    return FUN_006339E0(out, PlanningCoordOf(Event));
}

// FUNCTION: GAMEMD 0x633CC0
PlanningNodeClass::PlanningNodeClass(int value)
    : unknown_18(value), unknown_1C(false), unknown_38(false),
      unknown_A8(0), unknown_AC(-1), unknown_B0(-1), unknown_B4(-1)
{
}

// FUNCTION: GAMEMD 0x633D30
// PARTIAL: best 10.9%. Retail expands the three list removals unevenly: the
// first two call the out-of-line Delete (0x63E590), the third is inlined in
// full; this build inlines all three. Tried: RemoveItem x3, explicit
// FindItemIndex/Delete pairs (3.2%), a discarded-result form (10.9%).
PlanningNodeClass::~PlanningNodeClass()
{
    FUN_00635120();
    PlanningLists::DAT_00AC4C98.RemoveItem(this);
    PlanningLists::DAT_00AC4B30.RemoveItem(this);
    PlanningLists::DAT_00AC4C18.RemoveItem(this);
    if (DAT_00AC4CCC == this) {
        DAT_00AC4CCC = 0;
    }
    if (DAT_00AC4C38 == this) {
        DAT_00AC4C38 = 0;
    }
    if (DAT_00AC4BF0 == this) {
        DAT_00AC4BF0 = 0;
    }
}

// FUNCTION: GAMEMD 0x633E50
int PlanningNodeClass::FUN_00633E50()
{
    return unknown_18;
}

// FUNCTION: GAMEMD 0x633E60
int PlanningNodeClass::FUN_00633E60()
{
    return Members.Count;
}

// FUNCTION: GAMEMD 0x633E70
// This node's index on `techno`'s token.
int PlanningNodeClass::FUN_00633E70(TechnoClass* techno)
{
    PlanningTokenClass* token = techno->FUN_00705D20();
    return token->Nodes.FindItemIndex(this);
}

// FUNCTION: GAMEMD 0x633EA0
// The node before this one on `techno`'s token (wrapping to the last).
PlanningNodeClass* PlanningNodeClass::FUN_00633EA0(TechnoClass* techno)
{
    PlanningTokenClass* token = techno->FUN_00705D20();
    int index = token->Nodes.FindItemIndex(this);
    if (index == -1) {
        return 0;
    }
    if (token->Nodes.Count == 1) {
        return this;
    }
    index--;
    if (index < 0) {
        index = token->Nodes.Count - 1;
    }
    return token->NodeAt(index);
}

// FUNCTION: GAMEMD 0x633F20
// The node after this one on `techno`'s token (wrapping to the first).
PlanningNodeClass* PlanningNodeClass::FUN_00633F20(TechnoClass* techno)
{
    PlanningTokenClass* token = techno->FUN_00705D20();
    int index = token->Nodes.FindItemIndex(this);
    if (index == -1) {
        return 0;
    }
    if (token->Nodes.Count == 1) {
        return this;
    }
    index++;
    if (index >= token->Nodes.Count) {
        index = 0;
    }
    return token->NodeAt(index);
}

// FUNCTION: GAMEMD 0x633FA0
// Put `techno` on this node with a copy of its order.
void PlanningNodeClass::FUN_00633FA0(TechnoClass* techno, const EventClass* event)
{
    PlanningMemberClass* member = new PlanningMemberClass;
    member->Owner = techno;
    EventClass* copy = new EventClass;
    *copy = *event;
    member->Event = copy;
    Members.AddItem(member);
    PlanningTokenClass* token = techno->FUN_00705D20();
    token->Nodes.AddItem(this);
    if (token->unknown_8C == -1) {
        token->unknown_8C = token->Nodes.Count - 1;
    }
    FUN_00634E10(member);
}

// FUNCTION: GAMEMD 0x6340B0
// Take `techno` off this node; the node deletes itself once empty.
// PARTIAL: best 5.1%. Same inlining split as 0x633D30: retail calls AddItem
// (0x63E540), Delete (0x63E590) and RemoveItem (0x63E5D0) out of line inside
// the expanded destructor, where this build inlines them.
void PlanningNodeClass::FUN_006340B0(TechnoClass* techno)
{
    PlanningMemberClass* member = MemberOf(techno);
    if (member == 0) {
        return;
    }
    if (member->unknown_0C) {
        member->unknown_0C = false;
        if (--unknown_A8 == 0) {
            unknown_B0 = -1;
        }
    }
    if (member->unknown_08 != -1) {
        PlanningBranchClass* branch = Branches.Items[member->unknown_08];
        branch->unknown_74 = -1;
        FUN_00635DB0(0);
        if (--branch->unknown_70 == 0 && this != 0 && !unknown_1C) {
            unknown_1C = true;
            PlanningLists::DAT_00AC4C98.AddItem(this);
        }
    }
    member->unknown_08 = -1;
    delete member->Event;
    Members.RemoveItem(member);
    delete member;
    if (Members.Count == 0 && this != 0) {
        delete this;
    }
}

// FUNCTION: GAMEMD 0x6342D0
TechnoClass* PlanningNodeClass::FUN_006342D0(int index)
{
    return Members.Items[index]->Owner;
}

// FUNCTION: GAMEMD 0x6342E0
EventClass PlanningNodeClass::FUN_006342E0(int index)
{
    return *Members.Items[index]->Event;
}

// FUNCTION: GAMEMD 0x634310
EventClass PlanningNodeClass::FUN_00634310(TechnoClass* techno)
{
    return *MemberOf(techno)->Event;
}

// FUNCTION: GAMEMD 0x634360
bool PlanningNodeClass::FUN_00634360(TechnoClass* techno)
{
    return MemberIndex(techno) != -1;
}

// FUNCTION: GAMEMD 0x6343B0
void* PlanningNodeClass::FUN_006343B0()
{
    return Members.Items[0]->Owner->Owner;
}

// FUNCTION: GAMEMD 0x6343C0
CoordStruct PlanningNodeClass::FUN_006343C0()
{
    return PlanningCoordOf(*Members.Items[0]->Event);
}

// FUNCTION: GAMEMD 0x634400
Point2D* PlanningNodeClass::FUN_00634400(Point2D* out)
{
    return FUN_006339E0(out, PlanningCoordOf(*Members.Items[0]->Event));
}

RectangleStruct* FUN_00634510(RectangleStruct* out, int size, Point2D center);

// FUNCTION: GAMEMD 0x634470
// Whether the view point (x, y) falls on this node's marker.
// PARTIAL: best 24.1%. Retail calls 0x6339E0 and 0x634510 here (frame 0x30)
// although it expands both in 0x6345A0; this build expands them. Tried: the
// expanded-copy helper, pointer results, and the nested-call form below.
int PlanningNodeClass::FUN_00634470(int x, int y)
{
    CoordStruct tmp;
    CoordStruct coord = *FUN_00633BC0(&tmp, *Members.Items[0]->Event);
    Point2D point;
    RectangleStruct rect;
    RectangleStruct bounds = *FUN_00634510(&rect, 8, *FUN_006339E0(&point, coord));
    bounds.X -= 4;
    bounds.Y -= 4;
    bounds.Width += 8;
    bounds.Height += 8;
    return x >= bounds.X && x < bounds.X + bounds.Width && y >= bounds.Y && y < bounds.Y + bounds.Height;
}

// FUNCTION: GAMEMD 0x634510
// A size-by-size rectangle centred on (x, y).
RectangleStruct* FUN_00634510(RectangleStruct* out, int size, Point2D center)
{
    int half = -(size / 2);
    Point2D corner = center;
    corner.X += half;
    corner.Y += half;
    RectangleStruct rect;
    rect.X = corner.X;
    rect.Y = corner.Y;
    rect.Width = size;
    rect.Height = size;
    *out = rect;
    return out;
}

// FUNCTION: GAMEMD 0x634550
bool PlanningNodeClass::FUN_00634550(int x, int y, int z)
{
    CoordStruct coord = PlanningCoordOf(*Members.Items[0]->Event);
    return coord.X == x && coord.Y == y && coord.Z == z;
}

// FUNCTION: GAMEMD 0x6345A0
RectangleStruct PlanningNodeClass::FUN_006345A0()
{
    CoordStruct tmp;
    CoordStruct coord = *FUN_00633BC0(&tmp, *Members.Items[0]->Event);
    Point2D point;
    FUN_006339E0(&point, coord);
    RectangleStruct rect;
    return *FUN_00634510(&rect, 8, point);
}

// FUNCTION: GAMEMD 0x634630
bool PlanningNodeClass::FUN_00634630()
{
    if (Members.Count == 0) {
        return false;
    }
    PlanningTokenClass* token = Members.Items[0]->Owner->FUN_00705D20();
    int index = token->Nodes.FindItemIndex(this);
    return token->unknown_94 != -1 && index >= token->unknown_94;
}

// FUNCTION: GAMEMD 0x634680
void PlanningNodeClass::FUN_00634680()
{
    int count = Members.Count;
    for (int i = 0; i < count; i++) {
        EventClass* event = Members.Items[i]->Event;
        if (event->Data.MegaMission.Mission == 2) {
            event->Data.MegaMission.Mission = 0x1D;
        }
    }
}

// FUNCTION: GAMEMD 0x6346B0
PlanningMemberClass* PlanningNodeClass::FUN_006346B0(TechnoClass* techno)
{
    return MemberOf(techno);
}

// FUNCTION: GAMEMD 0x634700
int PlanningNodeClass::FUN_00634700()
{
    return Branches.Count;
}

// FUNCTION: GAMEMD 0x634710
bool PlanningNodeClass::FUN_00634710()
{
    return unknown_A8 > 0;
}

// FUNCTION: GAMEMD 0x634720
bool PlanningNodeClass::FUN_00634720()
{
    return unknown_A8 > 0 && unknown_B0 == -1;
}

// FUNCTION: GAMEMD 0x634740
TechnoClass* PlanningNodeClass::FUN_00634740(int branch)
{
    for (int i = 0; i < Members.Count; i++) {
        PlanningMemberClass* member = Members.Items[i];
        if (member->unknown_08 == branch) {
            return member->Owner;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x634770
TechnoClass* PlanningNodeClass::FUN_00634770()
{
    for (int i = 0; i < Members.Count; i++) {
        PlanningMemberClass* member = Members.Items[i];
        if (member->unknown_0C) {
            return member->Owner;
        }
    }
    return 0;
}
