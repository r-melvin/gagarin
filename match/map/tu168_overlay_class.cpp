// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU168 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x5fc170-0x5fe05f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//
// OverlayClass entries (layout and evidence: overlay_class.h).
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).

#include "../FUNCTION.H"
#include "terrain_objects/overlay_class.h"

// Component-wise 16-bit cell addition (the original steps cells through an inline of this shape).
inline MapObjCell OverlayCellAdd(const MapObjCell& a, const MapObjCell& b)
{
    MapObjCell sum;
    sum.X = a.X + b.X;
    sum.Y = a.Y + b.Y;
    return sum;
}

inline MapObjCell OverlayCellAdd(const OverlayStaticCell& a, const MapObjCell& b)
{
    MapObjCell sum;
    sum.X = a.X + b.X;
    sum.Y = a.Y + b.Y;
    return sum;
}

// GLOBAL: GAMEMD 0x7E96B0 - CLSID of OverlayClass (16 bytes read from the image).
extern "C" const CLSID CLSID_Overlay =
    { 0x0E272DC7, 0x9C0F, 0x11D1, { 0xB7, 0x09, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1 } };

//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.



void __cdecl FUN_005FD230();
void __cdecl FUN_005FD240();
void __cdecl FUN_005FD250();
void __cdecl FUN_005FD260();


#include "overlay_class_tiberium_type_methods.h"

// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EF390
extern const double DAT_007EF390;
// GLOBAL: GAMEMD 0xAC1530
extern double DAT_00AC1530;

// SYNTHETIC: GAMEMD 0x5FC1A0
// GLOBAL: GAMEMD 0xAC15D8
double DAT_00AC15D8 = DAT_00AC1530 / DAT_007EF390;

// SYNTHETIC: GAMEMD 0x5FC1C0
// GLOBAL: GAMEMD 0xAC15C0
double DAT_00AC15C0 = DAT_007E1718 / DAT_00AC15D8;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FC380
OverlayClass::OverlayClass(OverlayTypeClass* type, const CellStruct& cell, int arg)
    : Type(type)
{
    AbstractClass::vf_rtti_5();
    MapObjAddItem(&OverlayArray, this);

    if (cell.X != OverlayNoCell.X || cell.Y != OverlayNoCell.Y)
    {
        OverlayPlacementArg = arg;
        CoordStruct where;
        where.Z = 0;
        where.X = cell.X * 256 + 128;
        where.Y = cell.Y * 256 + 128;
        MapObjCellView* mapCell = MapObjMap.GetCellAt(MapObjCoordToCell(where));
        if (mapCell->Func_47C550(0) == 0)
            ObjectClass::vf_54(where, 0);
        OverlayPlacementArg = -1;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FC4D0
// The scalar deleting destructor 0x5FDF70 expands this body; the base body 0x5F3B80 is out of line.
OverlayClass::~OverlayClass()
{
    MapObjAnnouncePointerExpired(this, true);
    OverlayArray.RemoveItem(this);
    if (MapObjRemovalEnabled)
        vf_53();
    Type = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FC570
// CAPPED at 7.4% (863 of 863 instructions, multiset delta: retail has 2 `sub`, 1 `call`, 6 `cmp`, 2 `jne`,
// 1 `lea`, 1 `jmp`, 2 `jle` that cl has as 5 `test`, 1 `je`, 3 `xor`, 1 `add`, 3 `or`, 2 `jge`). Retail keeps
// 0 in EDI and -1 in EBX for the whole body (`XOR EDI,EDI` / `OR EBX,-1`), compares and pushes through them
// and spills `this`; cl 8804 uses immediates, so every register after the prologue is named differently
// and the stream shifts. This is the recorded 8447-vs-8804 constant-materialisation class. Variants
// tried: plain returns (1.6%), abs() for the distances (0.9%), one shared failure exit with abs() (7.4%,
// kept: it is the only form that merges the four `return false` epilogues as retail does).
// Places (markType 1) or changes (markType 3) the overlay on its cell. Most types just stamp the cell;
// the fence-like groups 0x7A-0x7D and 0xE9-0xEC lay a run of three-cell pieces along a facing and then
// fill the stretch back to the far end piece with randomly chosen frames.
bool OverlayClass::vf_73(int markType)
{
    CellStruct cellCoord;
    MapObjCellView* cell;
    int typeIndex;
    if (!ObjectClass::vf_73(markType))
        goto fail;
    if (markType != 1 && markType != 3)
        goto fail;

    cellCoord = vf_110();
    cell = MapObjMap.GetCellAt(cellCoord);
    typeIndex = Type->ArrayIndex;
    if (cell->unknown_11C > 4 && typeIndex != 0xB2)
        goto fail;

    if (typeIndex == 0x18) {
        cell->Func_47E040(0, 1);
    } else if (typeIndex == 0x19) {
        cell->Func_47E040(6, 1);
    } else {
        if (typeIndex == 0xED) {
            cell->Func_47E470(0, 1);
        } else if (typeIndex == 0xEE) {
            cell->Func_47E470(6, 1);
        } else {
            if (typeIndex == 0xA7) {
                if (OverlayVeinholeEligible(&cell->MapCoords)) {
                    for (int i = 0; i < 8; i++) {
                        MapObjCellView* neighbour = cell->GetNeighbour(i);
                        neighbour->OverlayTypeIndex = 0xB2;
                        neighbour->OverlayFrame = 0;
                    }
                    cell->OverlayTypeIndex = 0xA7;
                    cell->OverlayFrame = 0;
                    new OverlayVeinholeView(&cell->MapCoords);
                }
                goto finish;
            }
            if (typeIndex == 0x7E && MapObjMarkGate == 0) {
                cell->Func_485AF0();
                goto finish;
            }
        }
    }

    if (Type->Land == 9) {
        cell->OverlayFrame = 0;
        cell->OverlayTypeIndex = Type->ArrayIndex;
        goto finish;
    }

    if (Type->Wall) {
        if (!cell->Func_47C620(1, 0, 0)) {
            vf_62();
            goto fail;
        }
        cell->OverlayFrame = 0;
        cell->OverlayTypeIndex = Type->ArrayIndex;
        cell->Func_480630(1);
        if (MapObjMarkGate == 0) {
            MapObjMap.Func_56D5A0(&cell->MapCoords);
            MapObjMap.Func_584550(&cell->MapCoords);
        }
        if (OverlayPlacementArg != -1)
            cell->unknown_50 = OverlayParkedValue;
        for (int i = 0; i < 8; i++)
            cell->GetNeighbour(i)->unknown_122++;
        goto finish;
    }

    {
        int index = Type->ArrayIndex;
        short cellX = cellCoord.X;
        short cellY = cellCoord.Y;

        if (index >= 0x7A && index <= 0x7D) {
            int k = index - 0x7A;
            static OverlayStaticCell lead[4] = { OverlayMakeStaticCell(0, -1), OverlayMakeStaticCell(0, -1),
                                                 OverlayMakeStaticCell(-1, 0), OverlayMakeStaticCell(-1, 0) };
            static OverlayStaticCell cross[2][3] = {
                { OverlayMakeStaticCell(-1, 0), OverlayMakeStaticCell(0, 0), OverlayMakeStaticCell(1, 0) },
                { OverlayMakeStaticCell(0, -1), OverlayMakeStaticCell(0, 0), OverlayMakeStaticCell(0, 1) } };

            short leadY = lead[k].Y;
            short leadX = lead[k].X;
            MapObjCell start;
            start.X = cellX + leadX;
            start.Y = cellY + leadY;
            bool clear = true;
            MapObjCell probe = start;
            const MapObjCell* step = &MapObjFacingStep[OverlayFenceFirstFacing[k] & 7];
            for (int n = 3; n != 0; --n) {
                if (MapObjMap.GetCellAt(probe)->OverlayTypeIndex != -1)
                    clear = false;
                probe = OverlayCellAdd(*step, probe);
            }
            if (clear) {
                probe = start;
                for (int j = 0; j < 3; j++) {
                    MapObjCellView* piece = MapObjMap.GetCellAt(probe);
                    piece->OverlayTypeIndex = OverlayFenceRunType[k];
                    piece->OverlayFrame = (unsigned char)j;
                    piece->Func_47D2B0(-1);
                    probe = OverlayCellAdd(probe, *step);
                }
                int facing = OverlayFenceSecondFacing[k];
                bool found = false;
                const MapObjCell* step2 = &MapObjFacingStep[facing & 7];
                MapObjCell edge;
                edge.X = step2->X + cellX;
                edge.Y = step2->Y + cellY;
                int expected = OverlayFenceEndType[facing / 2];
                if (MapObjMap.IsValid(edge)) {
                    do {
                        if (found)
                            goto fenceFill;
                        MapObjCellView* piece = MapObjMap.GetCellAt(edge);
                        if (piece->OverlayTypeIndex == expected && piece->OverlayFrame == 1)
                            found = true;
                        else
                            edge = OverlayCellAdd(*step2, edge);
                    } while (MapObjMap.IsValid(edge));
                    if (found) {
fenceFill:
                        int back = (facing - 4) & 7;
                        const MapObjCell* stepBack = &MapObjFacingStep[back & 7];
                        edge = OverlayCellAdd(edge, *stepBack);
                        int dy = abs(edge.Y - (short)(leadY + cellY));
                        int dx = abs(edge.X - (short)(cellX + leadX));
                        int count = dy;
                        if (count < dx)
                            count = dx;
                        if (count > 0) {
                            int sel = (back % 4) / 2;
                            do {
                                for (int j = 0; j < 3; j++) {
                                    MapObjCell at = OverlayCellAdd(cross[sel][j], edge);
                                    MapObjCellView* piece = MapObjMap.GetCellAt(at);
                                    piece->OverlayTypeIndex = (MapObjScenario->Random.Random() & 3)
                                                              + OverlayFenceFillType[sel];
                                    piece->OverlayFrame = (unsigned char)j;
                                    piece->Func_47D2B0(-1);
                                }
                                edge = OverlayCellAdd(edge, *stepBack);
                                count--;
                            } while (count != 0);
                        }
                    }
                }
            }
            goto finish;
        }

        if (index >= 0xE9 && index <= 0xEC) {
            int k = index - 0xE9;
            static OverlayStaticCell lead[4] = { OverlayMakeStaticCell(0, -1), OverlayMakeStaticCell(0, -1),
                                                 OverlayMakeStaticCell(-1, 0), OverlayMakeStaticCell(-1, 0) };
            static OverlayStaticCell cross[2][3] = {
                { OverlayMakeStaticCell(-1, 0), OverlayMakeStaticCell(0, 0), OverlayMakeStaticCell(1, 0) },
                { OverlayMakeStaticCell(0, -1), OverlayMakeStaticCell(0, 0), OverlayMakeStaticCell(0, 1) } };

            short leadX = lead[k].X;
            short leadY = lead[k].Y;
            MapObjCell start;
            start.X = cellX + leadX;
            start.Y = cellY + leadY;
            bool clear = true;
            MapObjCell probe = start;
            const MapObjCell* step = &MapObjFacingStep[OverlayRoadFirstFacing[k] & 7];
            for (int n = 3; n != 0; --n) {
                if (MapObjMap.GetCellAt(probe)->OverlayTypeIndex != -1)
                    clear = false;
                probe = OverlayCellAdd(*step, probe);
            }
            if (clear) {
                probe = start;
                for (int j = 0; j < 3; j++) {
                    MapObjCellView* piece = MapObjMap.GetCellAt(probe);
                    piece->OverlayTypeIndex = OverlayRoadRunType[k];
                    piece->OverlayFrame = (unsigned char)j;
                    piece->Func_47D2B0(-1);
                    probe = OverlayCellAdd(probe, *step);
                }
                int facing = OverlayRoadSecondFacing[k];
                bool found = false;
                const MapObjCell* step2 = &MapObjFacingStep[facing & 7];
                MapObjCell edge;
                edge.X = step2->X + cellX;
                edge.Y = step2->Y + cellY;
                int expected = OverlayRoadEndType[facing / 2];
                if (MapObjMap.IsValid(edge)) {
                    do {
                        if (found)
                            goto roadFill;
                        MapObjCellView* piece = MapObjMap.GetCellAt(edge);
                        if (piece->OverlayTypeIndex == expected && piece->OverlayFrame == 1)
                            found = true;
                        else
                            edge = OverlayCellAdd(*step2, edge);
                    } while (MapObjMap.IsValid(edge));
                    if (found) {
roadFill:
                        int back = (facing - 4) & 7;
                        const MapObjCell* stepBack = &MapObjFacingStep[back & 7];
                        edge = OverlayCellAdd(edge, *stepBack);
                        int dy = abs(edge.Y - (short)(leadY + cellY));
                        int dx = abs(edge.X - (short)(leadX + cellX));
                        int count = dy;
                        if (count < dx)
                            count = dx;
                        if (count > 0) {
                            int sel = (back % 4) / 2;
                            do {
                                for (int j = 0; j < 3; j++) {
                                    MapObjCell at = OverlayCellAdd(cross[sel][j], edge);
                                    MapObjCellView* piece = MapObjMap.GetCellAt(at);
                                    piece->OverlayTypeIndex = (MapObjScenario->Random.Random() & 3)
                                                              + OverlayRoadFillType[sel];
                                    piece->OverlayFrame = (unsigned char)j;
                                    piece->Func_47D2B0(-1);
                                }
                                edge = OverlayCellAdd(edge, *stepBack);
                                count--;
                            } while (count != 0);
                        }
                    }
                }
            }
            goto finish;
        }
    }

    {
        bool place;
        if (MapObjMarkGate == 0) {
            if (Type == MapObjRules->unknown_100) {
                place = cell->Func_4834A0(5, 0, 0, -1, 0, -1, 1);
            } else if (Type == MapObjRules->unknown_FC || Type == MapObjRules->unknown_F8) {
                place = cell->Func_4834A0(1, 0, 0, -1, 0, -1, 1);
            } else if (typeIndex != 0x18 && typeIndex != 0x19 && typeIndex != 0xED && typeIndex != 0xEE) {
                place = cell->Func_4834A0(1, 1, 1, -1, 0, -1, 1);
                if (typeIndex == 0x66 && cell->unknown_11C > 4)
                    place = false;
            } else {
                place = true;
            }
            if (cell->OverlayTypeIndex != -1 && OverlayTypeArray.Items[cell->OverlayTypeIndex]->Overrides)
                place = false;
        } else {
            place = true;
        }

        if (place) {
            cell->OverlayTypeIndex = Type->ArrayIndex;
            if (typeIndex != 0x18 && typeIndex != 0x19 && typeIndex != 0xED && typeIndex != 0xEE)
                cell->OverlayFrame = 0;
            if (Type->Land == 5) {
                cell->OverlayFrame = 1;
                cell->Func_4818E0(0);
            }
            if (Type->Crate)
                cell->OverlayFrame = 0xFF;
        }
    }

    if (Type->CellAnim) {
        MapObjCoord base = Location;
        int groundHeight = MapObjMap.GetHeight(&base);
        MapObjAnimView* anim = 0;
        void* memory = operator new(sizeof(MapObjAnimView));
        if (memory) {
            MapObjCoord where;
            where.X = Location.X + 0x180;
            where.Y = Location.Y + 0x180;
            where.Z = groundHeight;
            anim = new (memory) MapObjAnimView(Type->CellAnim, where, 0, 1, 0x600, 0, false);
        }
        int tiberiumIndex = cell->Func_485010();
        if (tiberiumIndex != -1) {
            OverlayTiberiumView* tiberium = OverlayTiberiumTypes[tiberiumIndex];
            if (tiberium) {
                anim->Convert = OverlayPalettes[tiberium->PaletteIndex]->Convert;
                anim->unknown_FC = cell->unknown_10A;
            }
        }
    }

finish:
    cell->Func_47D2B0(-1);
    IsOnMap = false;
    InLimbo = true;
    vf_62();
    return true;

fail:
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FD230
// Empty function.
void __cdecl FUN_005FD230()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FD240
// Empty function.
void __cdecl FUN_005FD240()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FD250
// Empty function.
void __cdecl FUN_005FD250()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FD260
// Empty function.
void __cdecl FUN_005FD260()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FD270
bool OverlayClass::vf_54(const CoordStruct& where, int facing)
{
    MapObjCellView* cell = MapObjMap.GetCellAt(MapObjCoordToCell(where));
    if (cell->Func_47C550(0))
        return false;
    return ObjectClass::vf_54(where, facing);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FD8F0
HRESULT __stdcall OverlayClass::Load(IStream* pStm)
{
    HRESULT hr = ObjectClass::Load(pStm);
    if (hr >= 0) {
        new (this) OverlayClass(AbstractNoInit());
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Type);
    }
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FD950
HRESULT __stdcall OverlayClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return AbstractClass::Save(pStm, fClearDirty);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FD970
// PARTIAL 15.6%. The shape drawer's trailing offset is a point passed by value (retail's register
// zeros come from that). Remaining: retail keeps the type array's Count in a register across both
// index searches while reloading Items, and the block layout differs. Earlier variants: a draw call
// per branch through the plain declaration, a reference to Location, a separate local for the
// tiberium shape.
// Draws the overlay. The shape comes from the type; the vertical offset and the colour converter depend
// on the kind of overlay (tiberium, veins, everything else). Each kind ends in its own call to the
// shape drawer; the shared tail (surface load, call, epilogue) is what the compiler merged.
void OverlayClass::vf_70(Point2D* where, RectangleStruct* clip)
{
    void* shape = Type->vf_39();
    const CoordStruct& location = Location;
    MapObjCoord heightCoord = location;
    int height = MapObjHeightScale(MapObjMap.GetHeight(&heightCoord));
    int typeIndex = MapObjFindIndex(&OverlayTypeArray, Type);
    OverlayTypeClass* type = OverlayTypeArray.Items[typeIndex];

    int yAdjust = 0;
    if (type->Tiberium || type->Wall || type->ArrayIndex == 0x7E || type->Crate)
        yAdjust = -12;
    if (type->Land == 9)
        yAdjust--;
    if (typeIndex == 0x7E)
        yAdjust--;

    MapObjPoint point;
    point.X = where->X;
    point.Y = where->Y + yAdjust;
    point.Y += MapObjClipRect.Y;

    if (Type->Tiberium) {
        int index = MapObjFindIndex(&OverlayTypeArray, Type);
        OverlayTiberiumView* tiberium = OverlayTiberiumTypes[OverlayTiberiumIndexOf(index)];
        OverlayPaletteView* palette = OverlayPalettes[tiberium->PaletteIndex];
        void* tiberiumShape = OverlayTypeArray.Items[tiberium->unknown_E0->ArrayIndex]->vf_39();
        if (tiberiumShape == 0 && Type->CellAnim)
            tiberiumShape = Type->CellAnim->vf_39();
        OverlayDrawShapeInline(MapObjSurface, palette->Convert, tiberiumShape, 0, &point, clip, 0xE00, 0,
                               -2 - height, 0, 1000, 0, 0, 0, MapObjPoint(0, 0));
    } else if (Type->IsVeins) {
        if (Type->ArrayIndex == 0xA7)
            point.Y -= 0x26;
        MapObjCoord veinCoord = location;
        OverlayPaletteView* palette = OverlayPalettes[OverlaySession->VeinsPalette];
        OverlayDrawShapeInline(MapObjSurface, palette->Convert, shape, 0, &point, clip, 0xE00, 0,
                               -2 - height, 0, MapObjMap.GetCellAtCoord(veinCoord)->Light, 0, 0, 0, MapObjPoint(0, 0));
    } else {
        MapObjCoord coord = location;
        MapObjCell cell = MapObjCoordToCell(coord);
        MapObjCellView* mapCell;
        if (MapObjMap.IsValid(cell)) {
            mapCell = MapObjMap.GetCellAtCoord(coord);
        } else {
            MapObjCell screenCell;
            if (!MapObjMap.IsValid(*MapObjTactical->FUN_006D6590(&screenCell, &point))) {
                screenCell.X = 1;
                screenCell.Y = MapObjMapEdge;
                mapCell = MapObjMap.GetCellAt(screenCell);
            } else {
                mapCell = MapObjMap.GetCellAt(*MapObjTactical->FUN_006D6590(&screenCell, &point));
            }
        }
        OverlayDrawShapeInline(MapObjSurface, mapCell->Convert, shape, 0, &point, clip, 0xE00, 0,
                               -2 - height, 0, mapCell->Light, 0, 0, 0, MapObjPoint(0, 0));
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FDCC0
// The vertical drawing offset for an overlay type: 12 up for tiberium, walls, crates and the
// special overlay 0x7E, one more up for land type 9 and one more for overlay 0x7E itself.
MapObjPoint* __fastcall FUN_005FDCC0(MapObjPoint* out, int typeIndex)
{
    OverlayTypeClass* type = OverlayTypeArray.Items[typeIndex];
    MapObjPoint p(0, 0);
    if (type->Tiberium || type->Wall || type->ArrayIndex == 0x7E || type->Crate)
        p.Y = -12;
    if (type->Land == 9)
        p.Y--;
    if (typeIndex == 0x7E)
        p.Y--;
    *out = p;
    return out;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FDD20
//
// Map an overlay type index to the tiberium it belongs to. No overlay, or one
// that is not flagged as tiberium, gives -1. Otherwise each tiberium claims two
// consecutive index ranges starting at its image's own index — the flat frames
// and then the slope frames — and the first tiberium whose ranges contain the
// index wins. A flagged overlay that no tiberium claims is logged (the name
// travels by value) and reported as tiberium 0.
int OverlayClass::GetTiberiumType(int idxOverlay)
{
    OverlayType_005FDD20* type;
    if (idxOverlay == -1 || (type = (OverlayType_005FDD20*)DAT_00A83D84[idxOverlay])->Tiberium == 0) {
        return -1;
    }

    for (int i = 0; i < DAT_00B0F4F8; ++i) {
        Tiberium_005FDD20* tiberium = DAT_00B0F4EC[i];
        int first = tiberium->Image->ArrayIndex;
        if (idxOverlay >= first && idxOverlay < first + tiberium->NumImages) {
            return tiberium->ArrayIndex;
        }
        if (idxOverlay >= first + tiberium->NumImages
            && idxOverlay < first + tiberium->NumImages + tiberium->NumSlopes) {
            return tiberium->ArrayIndex;
        }
    }

    FUN_004068E0(STR_00833490, type->Name);
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FDDE0
ObjectTypeClass* OverlayClass::vf_34()
{
    return Type;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FDF00
int OverlayClass::vf_12()
{
    return 0xB0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FDF10
HRESULT __stdcall OverlayClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = CLSID_Overlay;
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FDF50
int OverlayClass::vf_11()
{
    return 0x14;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FDF60
void OverlayClass::vf_69(Point2D* where, RectangleStruct* clip)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x5FDF70 — compiler-generated scalar deleting destructor emitted for the virtual destructor.

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA83D80
DynamicVectorClassLayout OverlayTypeClass_Array;
// GLOBAL: GAMEMD 0xA8EC50
DynamicVectorClass<OverlayClass*> OverlayArray((AbstractNoInit()));
// GLOBAL: GAMEMD 0xAC1528
MapObjCell OverlayNoCell;
// GLOBAL: GAMEMD 0x8333BC
int OverlayPlacementArg = -1;
// GLOBAL: GAMEMD 0x7EF390
extern const double DAT_007EF390 = 60.0;
// GLOBAL: GAMEMD 0x833490
extern const char STR_00833490[] = "Overlay %s not really tiberium\n";
// END defined globals
