// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU242 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x71b5a0-0x71d38f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//
// TerrainClass entries (layout and evidence: terrain_class.h).

#include <new.h>
#include <stdlib.h>
#include "terrain_objects/terrain_class.h"
#include "terrain_objects/overlay_type_class.h"

// Slot 110 (the cell the object stands on) is read by value as `*vf_110(MapObjCell().Address())`: the
// returned cell is copied out of a compiler temporary, as in the original (see terrain_common_views.h).

// GLOBAL: GAMEMD 0x7E9740 - CLSID of TerrainClass (16 bytes read from the image).
extern "C" const CLSID CLSID_Terrain =
    { 0x0E272DCE, 0x9C0F, 0x11D1, { 0xB7, 0x09, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1 } };

// The anim spawn point: the object's coordinate raised by 0x50 leptons.
static inline MapObjCoord TerrainRaised(const MapObjCoord& coord)
{
    return MapObjCoord(coord.X, coord.Y, coord.Z + 0x50);
}

// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F51E0
extern const double DAT_007F51E0;
// GLOBAL: GAMEMD 0xB0ECF8
extern double DAT_00B0ECF8;

// SYNTHETIC: GAMEMD 0x71B5D0
// GLOBAL: GAMEMD 0xB0ED48
double DAT_00B0ED48 = DAT_00B0ECF8 / DAT_007F51E0;

// SYNTHETIC: GAMEMD 0x71B5F0
// GLOBAL: GAMEMD 0xB0ED30
double DAT_00B0ED30 = DAT_007E1718 / DAT_00B0ED48;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71B920
// CAPPED at 2.6% (184 of 189 instructions; retail-only: 3 `mov`, 1 `push`, 3 `pop`; cl-only: 1 `xor`, 1 `add`).
// Retail keeps `result` in a stack slot ([ESP+0x10]) and holds the first Location copy in EDI/EBX/EBP (four
// callee-saved pushes, frame 0x2C); cl keeps `result` in EBX (three pushes, frame 0x34), so every
// instruction after the prologue is named or placed differently. Variants tried: the plain form kept here,
// a hand-split operator new + placement new with the first copy in a named local, flat early-return guards.
int TerrainClass::vf_91(int* damage, int distance, MapObjWarheadView* warhead, void* source, bool a5, bool a6,
                        void* house)
{
    int result = 0;
    if (warhead == 0)
        return result;
    if (warhead->unknown_147 && !Type->unknown_233) {
        result = MapObjClassView::vf_91(damage, distance, warhead, source, a5, a6, house);
        if (result == 5)
            return result;
        if (result == 4) {
            if (Type->SpawnsTiberium) {
                new MapObjAnimView(
                    TerrainPickAnimType(100, MapObjRules->unknown_FA8,
                                        MapObjMap.GetCellAtCoord(CurrentLocation())->unknown_EC,
                                        CurrentLocation()),
                    CurrentLocation(), 0, 1, 0x2600, TerrainFunc_48ACE0(CurrentLocation()), 0);
                TerrainFunc_489280(CurrentLocation(), 100, 0, MapObjRules->unknown_FA8, 1, 0);
                ((MapObjCellRef*)vf_110(MapObjCell().Address()))->Func_489270();
            } else if (IsBurning) {
                TerrainFunc_422B80(this);
            } else if (!TimeToDie) {
                TimeToDie = true;
                SetRate(2);
                Value = 0;
            }
            MapObjTactical->Func_6D2790(vf_75(), 0);
            vf_55(1);
            UnInit();
        }
    }
    return result;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71BB90
TerrainClass::TerrainClass(TerrainTypeClass* type, const MapObjCell* cell)
    : Type(type), IsBurning(false), TimeToDie(false), unknown_D0(0), unknown_D4(0), ScreenPos(0, 0)
{
    MapObjRttiBase::Create_ID();
    unknown_6C = Type->unknown_A0;
    if (cell->X != TerrainEmptyCellValue.X || cell->Y != TerrainEmptyCellValue.Y) {
        MapObjCoord coord((cell->X << 8) + 0x80, (cell->Y << 8) + 0x80, 0);
        if (!Unlimbo(&coord, 0))
            MapObjClassView::UnInit();
    }
    SetRate(0);
    TerrainArray.AddItem(this);
    int id = Fetch_ID();
    TerrainAbstractIndex.AddIndexInline(id, this);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71BDF0
TerrainClass::TerrainClass()
    : Type(0), IsBurning(false), TimeToDie(false), unknown_D0(0), unknown_D4(0), ScreenPos(0, 0)
{
    TerrainArray.AddItem(this);
    int id = Fetch_ID();
    TerrainAbstractIndex.AddIndexInline(id, this);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71BFB0
// CAPPED at 91.0% (multiset identical, 67 of 67; was 80.6% with the sum written in one expression). Lever:
// the tactical offset and the current position are copied into locals first, then the sum is built from
// them. The residual is the schedule of the ScreenPos.Y load (retail loads it after the X add) and the
// register naming of the
// ScreenPos + Offset sum (retail: tactical pointer in EAX, reused for Offset.Y; cl: EDX plus EDI). Variants
// tried: free and member operator+, swapped operand order, int locals, a named sum temporary, `+=`.
bool TerrainClass::Mark(int arg)
{
    if (MapObjClassView::Mark(arg)) {
        MapObjCell cell = *vf_110(MapObjCell().Address());
        switch (arg) {
        case 0:
            MapObjMap.Func_5687F0(&cell, this);
            break;
        case 1:
        case 3: {
            MapObjMap.Func_5683C0(&cell, this);
            MapObjTactical->CoordsToClient(vf_43(), &ScreenPos);
            MapObjPoint off = MapObjTactical->Offset;
            MapObjPoint cur = ScreenPos;
            ScreenPos = MapObjPoint(cur.X + off.X, cur.Y + off.Y);
            break;
        }
        }
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71C070
void TerrainClass::vf_61(MapObjCoord* where)
{
    int bits = MapObjScenario->TheaterIndex != 1 ? Type->TemperateOccupationBits : Type->SnowOccupationBits;
    MapObjCell cell = MapObjCoordToCell(*where);
    MapObjCellView* c = MapObjMap.GetCellAt(cell);
    if (bits & 1)
        c->FlagBytes[0] &= 0xFB;
    if (bits & 2)
        c->FlagBytes[0] &= 0xF7;
    if (bits & 4)
        c->FlagBytes[0] &= 0xEF;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71C110
void TerrainClass::vf_60(MapObjCoord* where)
{
    int bits = MapObjScenario->TheaterIndex != 1 ? Type->TemperateOccupationBits : Type->SnowOccupationBits;
    MapObjCell cell = MapObjCoordToCell(*where);
    MapObjCellView* c = MapObjMap.GetCellAt(cell);
    if (bits & 1)
        c->FlagBytes[0] |= 0x04;
    if (bits & 2)
        c->FlagBytes[0] |= 0x08;
    if (bits & 4)
        c->FlagBytes[0] |= 0x10;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71C1B0
// PARTIAL 89.2% (multiset: retail-only `sub`, `jmp`; cl-only `mov`, `add`). The shape drawer's
// trailing offset is a point passed by value, which is what makes retail zero ECX/EAX and push the
// zero arguments from them. Remaining: retail subtracts 0x10 from the point with `SUB` where cl folds
// an `ADD -16` (tried `point -= `, a by-value operator- and a copy-then-subtract operator: all worse),
// and retail selects the draw flags with a branch where cl if-converts (ternary and if/else alike).
void TerrainClass::vf_69(MapObjPoint* where, MapObjRect* clip)
{
    MapObjCell cell = *vf_110(MapObjCell().Address());
    MapObjCellView* cellView = MapObjMap.GetCellAt(cell);
    MapObjShapeView* image = (MapObjShapeView*)GetImage();
    if (image != 0) {
        int frame = 0;
        if (Type->IsAnimated)
            frame = Value;
        else if (TimeToDie)
            frame = Value + TimeToDie;
        else if (unknown_6C < 2)
            frame = 1;
        MapObjPoint point = *where;
        int z = -MapObjHeightScale(vf_116());
        if (cellView->Convert == 0)
            cellView->Func_483E30(0, 0x10000, 0, 1000, 1000, 1000);
        void* context;
        int tint;
        if (Type->SpawnsTiberium) {
            context = TerrainDrawContext;
            tint = cellView->unknown_10A;
            point = point - MapObjPoint(0, 0x10);
        } else {
            context = cellView->Convert;
            tint = cellView->Light;
        }
        int flags = (Type->IsAnimated || TimeToDie) ? 0x2E00 : 0x4E00;
        MapObjDrawShape(MapObjSurface, context, image, frame, &point, clip, flags, 0, z - 12, 2, tint, 0, 0,
                         0, MapObjPoint(0, 0));
        if (TerrainShadowsEnabled)
            MapObjDrawShape(MapObjSurface, cellView->Convert, image, frame + image->FrameCount / 2, &point,
                             clip, flags | 1, 0, z - 3, 0, 1000, 0, 0, 0, MapObjPoint(0, 0));
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71C360
// PARTIAL 74.8% (multiset: retail-only `sub`, cl-only `add`). By-value offset as in vf_69, and
// `frame` defaults to 0 before the TimeToDie test (retail has no else arm). Remaining: the same
// Y adjustment as vf_69, and the scheduling of the second call's frame sum.
void TerrainClass::vf_70(MapObjPoint* where, MapObjRect* clip)
{
    MapObjCell cell = *vf_110(MapObjCell().Address());
    MapObjCellView* cellView = MapObjMap.GetCellAt(cell);
    MapObjShapeView* image = (MapObjShapeView*)GetImage();
    if (image != 0) {
        int frame = 0;
        if (TimeToDie)
            frame = Value + TimeToDie;
        MapObjPoint point = *where;
        int z = -MapObjHeightScale(vf_116());
        if (cellView->Convert == 0)
            cellView->Func_483E30(0, 0x10000, 0, 1000, 1000, 1000);
        void* context;
        int tint;
        if (Type->SpawnsTiberium) {
            context = TerrainDrawContext;
            tint = cellView->unknown_10A;
            point = point - MapObjPoint(0, 0x10);
        } else {
            context = cellView->Convert;
            tint = cellView->Light;
        }
        MapObjDrawShape(MapObjSurface, context, image, frame, &point, clip, 0xE00, 0, z - 4, 2, tint, 0, 0, 0, MapObjPoint(0, 0));
        if (TerrainShadowsEnabled)
            MapObjDrawShape(MapObjSurface, cellView->Convert, image, frame + image->FrameCount / 2, &point,
                             clip, 0x601, 0, z - 2, 0, 1000, 0, 0, 0, MapObjPoint(0, 0));
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71C4D0
// CAPPED at 94.5% (multiset identical). Retail lays the `return 7` epilogue before the `return 0` one;
// cl emits them in the other order. Variants tried: while loop (kept), for(;;) with the end test first,
// a result variable with break.
int TerrainClass::vf_107(MapObjOccupierView* who, int a2, int a3, int a4, int a5)
{
    MapObjCell* list = vf_66(0);
    MapObjCell origin = who->Cell;
    while (!(list->X == 0x7FFF && list->Y == 0x7FFF)) {
        if (Type->WaterBound) {
            MapObjCell cell = *list++ + origin;
            if (!MapObjMap.GetCellAt(cell)->Func_47C620(5, 0, 0))
                return 7;
        } else {
            MapObjCell cell = *list++ + origin;
            if (!MapObjMap.GetCellAt(cell)->Func_47C620(1, 0, 0))
                return 7;
        }
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71C5B0
bool TerrainClass::vf_94()
{
    if (TimeToDie || IsBurning || Type->unknown_9C != 6 || Type->SpawnsTiberium)
        return false;
    int roll = MapObjScenario->Random.Random();
    MapObjAnimView* anim = new MapObjAnimView(
        MapObjRules->unknown_B94[roll & 1], TerrainRaised(GetCoords()), 0, 0xFF, 0x600, 0, 0);
    if (anim != 0)
        anim->Func_424B50(this);
    anim->unknown_100 -= 0x14;
    IsBurning = true;
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71C6B0
void TerrainClass::vf_95()
{
    if (IsBurning) {
        bool dying = TimeToDie;
        IsBurning = false;
        if (!dying && unknown_6C == 0) {
            vf_55(1);
            Mark(2);
            if (!TimeToDie) {
                TimeToDie = true;
                SetRate(2);
                Value = 0;
            }
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71C730
// Prior timer interface capped at 31.5% (124 of 124 instructions).
// Shared CDTimerClass query now inlines: partial 3.2% (124 native,126 compiled).
// Historical comparison residual: retail-only 1 `fxch`,1 `je`; compiled-only 1 `mov`,1 `jne`.
// Retail compares the scaled roll with the probability as `FXCH; FCOMPP; TEST AH,1; JE`, cl as
// `FCOMPP; TEST AH,0x41; JNE`; the one-instruction shift costs the positional score for the rest of the
// body (every later instruction lines up). Variants tried: roll * K < p (kept), p > roll * K,
// !(roll * K >= p), a named double.
void TerrainClass::Update()
{
    MapObjClassView::Update();
    if (Type->IsAnimated && Rate == 0) {
        int roll = abs(MapObjScenario->Random.Random()) % 1000000;
        if (roll * TerrainMillionth < Type->AnimationProbability) {
            Value = 0;
            SetRate(Type->AnimationRate);
        }
    }
    if (Timer.GetTimeLeft() == 0 && Rate != 0) {
        HasChanged = true;
        Value += Step;
        Timer = CDTimerClass(Rate);
        if (TimeToDie) {
            if (Value == ((MapObjShapeView*)Type->vf_39())->FrameCount - 1) {
                UnInit();
                return;
            }
        }
        if (Type->SpawnsTiberium && Type->IsAnimated) {
            if (Value == ((MapObjShapeView*)Type->vf_39())->FrameCount / 2) {
                Value = 0;
                SetRate(0);
                MapObjMap.GetCellAtCoord(CurrentLocation())->Func_483780(true);
            }
        }
    } else {
        HasChanged = false;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71C930
// CAPPED at 92.5% (multiset identical). Residual: the neighbour sum is `MOV CX,BX; ADD CX,[adj]` in
// retail and `MOV CX,[adj]; ADD CX,BX` here. Variants tried: operator+ on cells (kept), a helper taking the
// base coordinates as ints, swapped operand order, shorts; separate locals vs the cell as the hidden-return
// buffer (cl drops the self copy); by-value hidden-return vf_110 (kept, +8.6%).
bool TerrainClass::vf_53()
{
    if (!unknown_81) {
        MapObjCell cell = *vf_110(MapObjCell().Address());
        for (int i = 0; i < 8; i++) {
            MapObjCell neighbour = cell + MapObjFacingStep[i & 7];
            MapObjCellView* nc = MapObjMap.GetCellAt(neighbour);
            nc->unknown_122 = nc->unknown_122 - 1;
        }
        unsigned int& flags = MapObjMap.GetCellAtCoord(CurrentLocation())->Flags;
        flags &= ~0x40u;
    }
    MapObjCell cell2 = *vf_110(MapObjCell().Address());
    bool result = MapObjClassView::vf_53();
    MapObjMap.GetCellAt(cell2)->Func_47D2B0(-1);
    if (!MapObjMarkGate) {
        MapObjMap.Func_56D460(&cell2);
        MapObjMap.Func_584550(&cell2);
        MapObjMap.Func_6551C0(&cell2);
    }
    return result;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71CC50
// CAPPED at 89.7% (multiset identical; was 84.5%). The frame now equals retail (0x18): the Intersect temporary
// is scoped to its own block so its slot is shared with the vf_75 temporary. The residual is register naming
// of the world rectangle (clip origin loaded in EBX/EBP in retail). Variants tried: separate rectangles (kept), one shared temporary, a work variable assigned
// from the by-value vf_75, scalar left/top/width/height locals.
bool TerrainClass::vf_65(MapObjRect* rect, bool force, int unused)
{
    if (!MapObjMarkGateFlag && TerrainFlag_B73550) {
        if (!((force || unknown_80) && unknown_74 && !unknown_81))
            return false;
    }
    unknown_80 = 0;
    {
        MapObjRect clipped;
        *rect = *TerrainIntersect(&clipped, rect, &MapObjClipRect, 0, 0);
    }
    MapObjRect world = MapObjRectShifted(vf_75(), MapObjClipRect.X, MapObjClipRect.Y);
    if (rect->X < world.X + world.Width && rect->Y < world.Y + world.Height && rect->X + rect->Width > world.X &&
        rect->Y + rect->Height > world.Y) {
        MapObjPoint point;
        MapObjTactical->CoordsToClient(vf_43(), &point);
        if (rect->X > MapObjClipRect.X)
            point.X += MapObjClipRect.X - rect->X;
        if (rect->Y > MapObjClipRect.Y)
            point.Y += MapObjClipRect.Y - rect->Y;
        vf_69(&point, rect);
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71CDA0
// CAPPED at 19.1% (115 vs 113 instructions; retail-only: 1 `sub`, 2 `lea`, 6 `test`, 1 `add`, 1 `xor`;
// cl-only: 1 `push`, 6 `cmp`, 1 `inc`, 1 `pop`). Retail runs the whole body on EBP/ESI/EDI with no zero
// register and immediate zero stores; cl hoists a zero into EBX (whenever five zero stores exist) so every
// compare against 0 becomes `CMP reg,EBX` and the stream shifts. The register assignment of this, this+4
// and the id now equals retail's. Variants tried: by-value ids, every permutation of the three tail
// stores, dropping single stores (probe only), a zeroed-node struct assignment.
HRESULT __stdcall TerrainClass::Load(IStream* pStm)
{
    TerrainAbstractIndex.RemoveIndex(Fetch_ID());
    HRESULT hr = MapObjClassView::Load(pStm);
    if (hr >= 0) {
        new (this) TerrainClass(MapObjNoInit());
        int id = Fetch_ID();
        TerrainAbstractIndex.AddIndexOutOfLine(id, this);
        MapObjSwizzle.Swizzle((void**)&Type);
    }
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71CF30
HRESULT __stdcall TerrainClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return MapObjClassView::Save(pStm, fClearDirty);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71CF50
void TerrainClass::ComputeCRC(MapObjCrcView& crc)
{
    MapObjClassView::ComputeCRC(crc);
    crc.AddInt(Type->WhatAmI());
    crc.AddInt(Type->Fetch_ID());
    crc.AddBool(IsBurning);
    crc.AddBool(TimeToDie);
    crc.AddInt(unknown_D0);
    crc.AddInt(unknown_D4);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71CFD0
void TerrainClass::PointerExpired(void* ptr, bool removed)
{
    MapObjClassView::PointerExpired(ptr, removed);
    if (Type == ptr)
        Type = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71D000
// CAPPED at 91.1% (multiset identical). The ScreenPos + Offset sum is held in EBX/EDI in retail
// (position first, offset second) and in EAX/ECX here, and retail pushes the next lookup's arguments
// before the stores. Variants tried: operator+ free, member (kept), int locals.
bool TerrainClass::Unlimbo(const MapObjCoord* where, int facing)
{
    if (MapObjClassView::Unlimbo(where, facing)) {
        int cx = where->X / 256;
        int cy = where->Y / 256;
        for (int i = 0; i < 8; i++) {
            MapObjCell neighbour = MapObjCellShifted(MapObjFacingStep[i & 7], cx, cy);
            MapObjCellView* nc = MapObjMap.GetCellAt(neighbour);
            nc->unknown_122 = nc->unknown_122 + 1;
        }
        MapObjTactical->CoordsToClient(vf_43(), &ScreenPos);
        ScreenPos = ScreenPos + MapObjTactical->Offset;
        if (MapObjMap.GetCellAtCoord(*where)->OverlayTypeIndex != -1) {
            if (OverlayTypeItems[MapObjMap.GetCellAtCoord(*where)->OverlayTypeIndex]->Tiberium) {
                MapObjMap.GetCellAtCoord(*where)->OverlayTypeIndex = -1;
                MapObjMap.GetCellAtCoord(*where)->OverlayFrame = 0;
            }
        }
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71D150
MapObjTypeClassView* TerrainClass::GetType()
{
    return Type;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71D160
// CAPPED at 23.4% (was 12.8%; lever: the tactical offset is copied to a local before the position sums)
// (140 of 141 instructions). Retail pushes only ESI in the prologue and the other
// callee-saved registers after the empty-image early return (frame 0x40 against 0x44), keeps the image in
// ESI where cl uses EDI/EBX, and loads the offsets before the screen position. Variants tried: struct copies
// of the two bounds, a rectangle temporary for the union, scalar locals (kept), a MapObjPoint offset
// from operator-.
MapObjRect TerrainClass::vf_75()
{
    MapObjPoint offset = MapObjTactical->Offset;
    int dx = ScreenPos.X - offset.X;
    int dy = ScreenPos.Y - offset.Y;
    MapObjShapeView* image = (MapObjShapeView*)MapObjClassView::GetImage();
    if (image == 0)
        return TerrainEmptyRect;
    MapObjRect t1;
    MapObjRect* b1 = image->GetBounds(&t1, 0);
    int x1 = b1->X;
    int y1 = b1->Y;
    int w1 = b1->Width;
    int h1 = b1->Height;
    MapObjRect t2;
    MapObjRect* b2 = image->GetBounds(&t2, image->FrameCount / 2);
    int x2 = b2->X;
    int y2 = b2->Y;
    int w2 = b2->Width;
    int h2 = b2->Height;
    int imageWidth = image->Width;
    int imageHeight = image->Height;
    int x, y, w, h;
    if (w1 > 0 && h1 > 0) {
        if (w2 > 0 && h2 > 0) {
            x = x1;
            w = w1;
            y = y1;
            h = h1;
            if (x1 > x2) {
                w = x1 - x2 + w1;
                x = x2;
            }
            if (y1 > y2) {
                h = h1 + (y1 - y2);
                y = y2;
            }
            if (x + w < x2 + w2)
                w = w2 - x + x2 + 1;
            if (y + h < y2 + h2)
                h = y2 - y + h2 + 1;
        } else {
            x = x1;
            y = y1;
            w = w1;
            h = h1;
        }
    } else {
        x = x2;
        y = y2;
        w = w2;
        h = h2;
    }
    MapObjRect result;
    result.X = x - imageWidth / 2 + dx;
    result.Y = y - imageHeight / 2 + dy;
    result.Width = w;
    result.Height = h;
    return result;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71D2F0
int TerrainClass::Size()
{
    return 0xE0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71D300
int TerrainClass::WhatAmI()
{
    return 0x24;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71D310
HRESULT __stdcall TerrainClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = CLSID_Terrain;
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71D350
// migrated from match/core/deleting_dtor_sweep.cpp; integrator retires the old row
// The scalar deleting destructor of TerrainClass is compiler output (`virtual ~TerrainClass();` in
// terrain_class.h, declared without a body here): it calls the destructor body at 0x71B7B0 (outside this
// partition, bound by address; expansion candidate) and frees the block with the game heap's delete
// (0x7C8B3D) when bit 0 of the flags is set.
