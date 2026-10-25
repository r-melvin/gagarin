// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU242 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x71b5a0-0x71d38f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//
// TerrainClass entries (layout and evidence: terrain_class.h).

#include <new.h>
#include "../_layout/swizzle_manager_class.h"
#include <stdlib.h>
#include "terrain_objects/terrain_class.h"
#include "terrain_objects/overlay_type_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/obj_004a1d30.h"
#include "../_layout/rectangle_operations.h"
#include "../_layout/tactical.h"
#include "../_layout/tactical_viewport.h"
// GLOBAL: GAMEMD 0x887324
extern Tactical* DAT_00887324;

// ObjectClass slot 110 returns CellStruct by value (0x41BEA0). The native
// Terrain callers use the compiler return temporary. Foreign map/animation/shape
// APIs below still declare legacy records: ABI casts preserve the original
// buffer or complete-object address. Object RTTI places ObjectClass at offset 0;
// coordinate/cell/rectangle field offsets and sizes are asserted in the shared headers.

// GLOBAL: GAMEMD 0x7E9740 - CLSID of TerrainClass (16 bytes read from the image).
extern "C" const CLSID CLSID_Terrain =
    { 0x0E272DCE, 0x9C0F, 0x11D1, { 0xB7, 0x09, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1 } };

// The anim spawn point: the object's coordinate raised by 0x50 leptons.
static inline MapObjCoord TerrainRaised(const CoordStruct& coord)
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
int TerrainClass::vf_91(int* damage, int distance, void* warhead, void* source, bool a5, bool a6,
                        void* house)
{
    int result = 0;
    if (warhead == 0)
        return result;
    if (static_cast<MapObjWarheadView*>(warhead)->unknown_147 && !Type->Immune) {
        result = ObjectClass::vf_91(damage, distance, warhead, source, a5, a6, house);
        if (result == 5)
            return result;
        if (result == 4) {
            if (Type->SpawnsTiberium) {
                new MapObjAnimView(
                    TerrainPickAnimType(100, MapObjRules->unknown_FA8,
                                        MapObjMap.GetCellAtCoord(MapObjCoord(Location.X, Location.Y, Location.Z))->unknown_EC,
                                        MapObjCoord(Location.X, Location.Y, Location.Z)),
                    MapObjCoord(Location.X, Location.Y, Location.Z), 0, 1, 0x2600, TerrainFunc_48ACE0(MapObjCoord(Location.X, Location.Y, Location.Z)), 0);
                TerrainFunc_489280(MapObjCoord(Location.X, Location.Y, Location.Z), 100, 0, MapObjRules->unknown_FA8, 1, 0);
                CellStruct cell = vf_110();
                reinterpret_cast<MapObjCellRef*>(&cell)->Func_489270();
            } else if (IsBurning) {
                TerrainFunc_422B80(this);
            } else if (!TimeToDie) {
                TimeToDie = true;
                SetRate(2);
                Value = 0;
            }
            DAT_00887324->FUN_006D2790(vf_75(), false);
            vf_55(1);
            vf_62();
        }
    }
    return result;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71BB90
TerrainClass::TerrainClass(TerrainTypeClass* type, const CellStruct* cell)
    : Type(type), IsBurning(false), TimeToDie(false), unknown_D0(0), unknown_D4(0), ScreenPos(0, 0)
{
    AbstractClass::vf_rtti_5();
    Health = Type->Strength;
    if (cell->X != TerrainEmptyCellValue.X || cell->Y != TerrainEmptyCellValue.Y) {
        CoordStruct coord = { (cell->X << 8) + 0x80, (cell->Y << 8) + 0x80, 0 };
        if (!vf_54(coord, 0))
            ObjectClass::vf_62();
    }
    SetRate(0);
    TerrainArray.AddItem(this);
    int id = vf_rtti_4();
    TerrainAbstractIndex.AddIndexInline(id, this);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71BDF0
TerrainClass::TerrainClass()
    : Type(0), IsBurning(false), TimeToDie(false), unknown_D0(0), unknown_D4(0), ScreenPos(0, 0)
{
    TerrainArray.AddItem(this);
    int id = vf_rtti_4();
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
bool TerrainClass::vf_73(int arg)
{
    if (ObjectClass::vf_73(arg)) {
        CellStruct cell = vf_110();
        switch (arg) {
        case 0:
            MapObjMap.Func_5687F0(reinterpret_cast<const MapObjCell*>(&cell), reinterpret_cast<MapObjClassView*>(this));
            break;
        case 1:
        case 3: {
            MapObjMap.Func_5683C0(reinterpret_cast<const MapObjCell*>(&cell), reinterpret_cast<MapObjClassView*>(this));
            CoordStruct coordinate = vf_43();
            DAT_00887324->FUN_006D2140(&coordinate, &ScreenPos);
            Point2D off(DAT_00887324->unknown_B0.unknown_00, DAT_00887324->unknown_B0.unknown_04);
            Point2D cur = ScreenPos;
            ScreenPos = Point2D(cur.X + off.X, cur.Y + off.Y);
            break;
        }
        }
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71C070
void TerrainClass::vf_61(CoordStruct* where)
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
void TerrainClass::vf_60(CoordStruct* where)
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
void TerrainClass::vf_69(Point2D* where, RectangleStruct* clip)
{
    CellStruct cell = vf_110();
    MapObjCellView* cellView = MapObjMap.GetCellAt(MapObjCell(cell.X, cell.Y));
    MapObjShapeView* image = (MapObjShapeView*)vf_27();
    if (image != 0) {
        int frame = 0;
        if (Type->IsAnimated)
            frame = Value;
        else if (TimeToDie)
            frame = Value + TimeToDie;
        else if (Health < 2)
            frame = 1;
        MapObjPoint point(where->X, where->Y);
        int z = -MapObjHeightScale(FUN_005F5F30());
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
        MapObjDrawShape(MapObjSurface, context, image, frame, &point, reinterpret_cast<MapObjRect*>(clip), flags, 0, z - 12, 2, tint, 0, 0,
                         0, MapObjPoint(0, 0));
        if (TerrainShadowsEnabled)
            MapObjDrawShape(MapObjSurface, cellView->Convert, image, frame + image->FrameCount / 2, &point,
                             reinterpret_cast<MapObjRect*>(clip), flags | 1, 0, z - 3, 0, 1000, 0, 0, 0, MapObjPoint(0, 0));
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71C360
// PARTIAL 74.8% (multiset: retail-only `sub`, cl-only `add`). By-value offset as in vf_69, and
// `frame` defaults to 0 before the TimeToDie test (retail has no else arm). Remaining: the same
// Y adjustment as vf_69, and the scheduling of the second call's frame sum.
void TerrainClass::vf_70(Point2D* where, RectangleStruct* clip)
{
    CellStruct cell = vf_110();
    MapObjCellView* cellView = MapObjMap.GetCellAt(MapObjCell(cell.X, cell.Y));
    MapObjShapeView* image = (MapObjShapeView*)vf_27();
    if (image != 0) {
        int frame = 0;
        if (TimeToDie)
            frame = Value + TimeToDie;
        MapObjPoint point(where->X, where->Y);
        int z = -MapObjHeightScale(FUN_005F5F30());
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
        MapObjDrawShape(MapObjSurface, context, image, frame, &point, reinterpret_cast<MapObjRect*>(clip), 0xE00, 0, z - 4, 2, tint, 0, 0, 0, MapObjPoint(0, 0));
        if (TerrainShadowsEnabled)
            MapObjDrawShape(MapObjSurface, cellView->Convert, image, frame + image->FrameCount / 2, &point,
                             reinterpret_cast<MapObjRect*>(clip), 0x601, 0, z - 2, 0, 1000, 0, 0, 0, MapObjPoint(0, 0));
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71C4D0
// CAPPED at 94.5% (multiset identical). Retail lays the `return 7` epilogue before the `return 0` one;
// cl emits them in the other order. Variants tried: while loop (kept), for(;;) with the end test first,
// a result variable with break.
int TerrainClass::vf_107(CellClass* who, int a2, int a3, int a4, int a5)
{
    MapObjCell* list = static_cast<MapObjCell*>(vf_66(0));
    MapObjCell origin(who->MapCoords.X, who->MapCoords.Y);
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
    if (TimeToDie || IsBurning || Type->Armor != 6 || Type->SpawnsTiberium)
        return false;
    int roll = MapObjScenario->Random.Random();
    MapObjAnimView* anim = new MapObjAnimView(
        MapObjRules->unknown_B94[roll & 1], TerrainRaised(vf_18()), 0, 0xFF, 0x600, 0, 0);
    if (anim != 0)
        anim->Func_424B50(reinterpret_cast<MapObjClassView*>(this));
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
        if (!dying && Health == 0) {
            vf_55(1);
            vf_73(2);
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
// Shared CDTimerClass query now inlines; the manifest records the current structural score.
// Historical comparison residual: retail-only 1 `fxch`,1 `je`; compiled-only 1 `mov`,1 `jne`.
// Retail compares the scaled roll with the probability as `FXCH; FCOMPP; TEST AH,1; JE`, cl as
// `FCOMPP; TEST AH,0x41; JNE`; the one-instruction shift costs the positional score for the rest of the
// body (every later instruction lines up). Variants tried: roll * K < p (kept), p > roll * K,
// !(roll * K >= p), a named double.
void TerrainClass::vf_23()
{
    ObjectClass::vf_23();
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
                vf_62();
                return;
            }
        }
        if (Type->SpawnsTiberium && Type->IsAnimated) {
            if (Value == ((MapObjShapeView*)Type->vf_39())->FrameCount / 2) {
                Value = 0;
                SetRate(0);
                MapObjMap.GetCellAtCoord(MapObjCoord(Location.X, Location.Y, Location.Z))->Func_483780(true);
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
    if (!InLimbo) {
        CellStruct cell = vf_110();
        for (int i = 0; i < 8; i++) {
            MapObjCell neighbour((short)(cell.X + MapObjFacingStep[i & 7].X), (short)(cell.Y + MapObjFacingStep[i & 7].Y));
            MapObjCellView* nc = MapObjMap.GetCellAt(neighbour);
            nc->unknown_122 = nc->unknown_122 - 1;
        }
        unsigned int& flags = MapObjMap.GetCellAtCoord(MapObjCoord(Location.X, Location.Y, Location.Z))->Flags;
        flags &= ~0x40u;
    }
    CellStruct cell2 = vf_110();
    bool result = ObjectClass::vf_53();
    MapObjMap.GetCellAt(MapObjCell(cell2.X, cell2.Y))->Func_47D2B0(-1);
    if (!MapObjMarkGate) {
        MapObjMap.Func_56D460(reinterpret_cast<const MapObjCell*>(&cell2));
        MapObjMap.Func_584550(reinterpret_cast<const MapObjCell*>(&cell2));
        MapObjMap.Func_6551C0(reinterpret_cast<const MapObjCell*>(&cell2));
    }
    return result;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71CC50
// CAPPED at 89.7% (multiset identical; was 84.5%). The frame now equals retail (0x18): the Intersect temporary
// is scoped to its own block so its slot is shared with the vf_75 temporary. The residual is register naming
// of the world rectangle (clip origin loaded in EBX/EBP in retail). Variants tried: separate rectangles (kept), one shared temporary, a work variable assigned
// from the by-value vf_75, scalar left/top/width/height locals.
bool TerrainClass::vf_65(RectangleStruct* rect, bool force, int unused)
{
    if (!MapObjMarkGateFlag && TerrainFlag_B73550) {
        if (!((force || NeedsRedraw) && IsOnMap && !InLimbo))
            return false;
    }
    NeedsRedraw = 0;
    {
        RectangleStruct clipped;
        *rect = *FUN_00421B60(&clipped, rect, &Viewport_00886FA0, 0, 0);
    }
    RectangleStruct world = vf_75();
    world.X += Viewport_00886FA0.X;
    world.Y += Viewport_00886FA0.Y;
    if (rect->X < world.X + world.Width && rect->Y < world.Y + world.Height && rect->X + rect->Width > world.X &&
        rect->Y + rect->Height > world.Y) {
        Point2D point;
        CoordStruct coordinate = vf_43();
        DAT_00887324->FUN_006D2140(&coordinate, &point);
        if (rect->X > Viewport_00886FA0.X)
            point.X += Viewport_00886FA0.X - rect->X;
        if (rect->Y > Viewport_00886FA0.Y)
            point.Y += Viewport_00886FA0.Y - rect->Y;
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
    TerrainAbstractIndex.RemoveIndex(vf_rtti_4());
    HRESULT hr = ObjectClass::Load(pStm);
    if (hr >= 0) {
        new (this) TerrainClass(AbstractNoInit());
        int id = vf_rtti_4();
        TerrainAbstractIndex.AddIndexOutOfLine(id, this);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Type);
    }
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71CF30
HRESULT __stdcall TerrainClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return AbstractClass::Save(pStm, fClearDirty);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71CF50
void TerrainClass::vf_13(Obj_004A1D30* crc)
{
    ObjectClass::vf_13(crc);
    crc->FUN_004A1D50(Type->vf_11());
    crc->FUN_004A1D50(Type->vf_rtti_4());
    crc->FUN_004A1CA0(IsBurning);
    crc->FUN_004A1CA0(TimeToDie);
    crc->FUN_004A1D50(unknown_D0);
    crc->FUN_004A1D50(unknown_D4);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71CFD0
void TerrainClass::vf_10(void* ptr, bool removed)
{
    ObjectClass::vf_10(ptr, removed);
    if (Type == ptr)
        Type = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71D000
// CAPPED at 91.1% (multiset identical). The ScreenPos + Offset sum is held in EBX/EDI in retail
// (position first, offset second) and in EAX/ECX here, and retail pushes the next lookup's arguments
// before the stores. Variants tried: operator+ free, member (kept), int locals.
bool TerrainClass::vf_54(const CoordStruct& where, int facing)
{
    if (ObjectClass::vf_54(where, facing)) {
        int cx = where.X / 256;
        int cy = where.Y / 256;
        for (int i = 0; i < 8; i++) {
            MapObjCell neighbour = MapObjCellShifted(MapObjFacingStep[i & 7], cx, cy);
            MapObjCellView* nc = MapObjMap.GetCellAt(neighbour);
            nc->unknown_122 = nc->unknown_122 + 1;
        }
        CoordStruct coordinate = vf_43();
            DAT_00887324->FUN_006D2140(&coordinate, &ScreenPos);
        ScreenPos = ScreenPos + Point2D(DAT_00887324->unknown_B0.unknown_00, DAT_00887324->unknown_B0.unknown_04);
        if (MapObjMap.GetCellAtCoord(reinterpret_cast<const MapObjCoord&>(where))->OverlayTypeIndex != -1) {
            if (OverlayTypeItems[MapObjMap.GetCellAtCoord(reinterpret_cast<const MapObjCoord&>(where))->OverlayTypeIndex]->Tiberium) {
                MapObjMap.GetCellAtCoord(reinterpret_cast<const MapObjCoord&>(where))->OverlayTypeIndex = -1;
                MapObjMap.GetCellAtCoord(reinterpret_cast<const MapObjCoord&>(where))->OverlayFrame = 0;
            }
        }
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71D150
ObjectTypeClass* TerrainClass::vf_34()
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
RectangleStruct TerrainClass::vf_75()
{
    Point2D offset(DAT_00887324->unknown_B0.unknown_00, DAT_00887324->unknown_B0.unknown_04);
    int dx = ScreenPos.X - offset.X;
    int dy = ScreenPos.Y - offset.Y;
    MapObjShapeView* image = (MapObjShapeView*)ObjectClass::vf_27();
    if (image == 0)
        { RectangleStruct empty = { TerrainEmptyRect.X, TerrainEmptyRect.Y, TerrainEmptyRect.Width, TerrainEmptyRect.Height }; return empty; }
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
    RectangleStruct result;
    result.X = x - imageWidth / 2 + dx;
    result.Y = y - imageHeight / 2 + dy;
    result.Width = w;
    result.Height = h;
    return result;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71D2F0
int TerrainClass::vf_12()
{
    return 0xE0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71D300
int TerrainClass::vf_11()
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
