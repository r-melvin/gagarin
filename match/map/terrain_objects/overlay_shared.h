// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail globals, out-of-partition functions and small views only the overlay half of the
//   terrain-objects module (OverlayClass, OverlayTypeClass) reads, bound by address. Nothing here is
//   defined by the module (see overlay_class.rows.tsv and overlay_type_class.rows.tsv for the
//   bindings). Everything the three families share (coordinates, the ObjectClass / ObjectTypeClass base
//   views, the map / cell / scenario / tactical views and their globals) lives in terrain_common_*.h.
#ifndef GG_MATCH_MAP_TERRAIN_OBJECTS_OVERLAY_SHARED_H
#define GG_MATCH_MAP_TERRAIN_OBJECTS_OVERLAY_SHARED_H

#include "terrain_common_types.h"
#include "../../_layout/cell.h"
#include "terrain_common_vectors.h"
#include "terrain_common_views.h"
#include "../../_layout/vector_class.h"
#include "../../_layout/geometry2d.h"

// The element of the function-local static offset tables (the user-declared destructor is what makes
// VC6 register an atexit stub, a bare RET, for each static). It derives from the cell so that
// OverlayTypeClass::vf_36 can return it through the shared slot (MapObjCell*), as TerrainTypeClass does
// with its own static-cell element.
//
// The atexit stubs are compiler output named by a per-translation-unit counter (`_$E2`, `_$E3`, ...):
// overlay_class.cpp emits `_$E2.._$E5` (the four static tables of OverlayClass::Mark, retail
// 0x5FD260 .. 0x5FD230) and overlay_type_class.cpp emits its own `_$E2` (the static list of
// OverlayTypeClass::vf_36, retail 0x5FE520). The same name therefore stands for different retail
// addresses in the two translation units, which is why the module keeps one rows file per overlay
// translation unit (overlay_class.rows.tsv, overlay_type_class.rows.tsv), each with its own `bind _$E2`
// row. Smudge and Terrain each have one rows file for their two translation units and no clash
// (terrain_type_class.cpp emits `_$E3`, retail 0x71DE90).
struct OverlayStaticCell : public CellStruct
{
    OverlayStaticCell(short x, short y) { X = x; Y = y; }
    ~OverlayStaticCell() {}
};
GG_STATIC_ASSERT(sizeof(OverlayStaticCell) == 4);

// Builds one table element. Initialising the static tables from this inline (a named local returned by
// value) is what reproduces retail's temporary-then-dword-copy sequence; a direct constructor call per
// element compiles to in-place 16-bit stores instead.
inline OverlayStaticCell OverlayMakeStaticCell(short x, short y)
{
    OverlayStaticCell cell(x, y);
    return cell;
}

// GLOBAL: GAMEMD 0xA8EC50 - OverlayClass::Array, every live overlay (DynamicVectorClass; read-only here).
extern DynamicVectorClass<OverlayClass*> OverlayArray;
// GLOBAL: GAMEMD 0xA83D80 - existing OverlayTypeClass_Array object; this typed view adds vector helpers.
extern DynamicVectorClassLayout OverlayTypeClass_Array;
#define OverlayTypeArray (*((DynamicVectorClass<OverlayTypeClass*>*)&OverlayTypeClass_Array))
// GLOBAL: GAMEMD 0xA83D84 - retain the established direct Items-symbol view.
extern OverlayTypeClass** DAT_00A83D84;
#define OverlayTypeItems DAT_00A83D84

// GLOBAL: GAMEMD 0xAC1528 - the "no cell" sentinel the constructor compares its cell against.
extern MapObjCell OverlayNoCell;
// GLOBAL: GAMEMD 0xAC1608 - the zero cell CreateObject passes to the constructor.
extern MapObjCell OverlayZeroCell;
// GLOBAL: GAMEMD 0x8333BC - the constructor's third argument, parked while Unlimbo runs.
extern int OverlayPlacementArg;

// STRING: GAMEMD 0x81834C ".SHP"
extern const char OverlayShpExtension[];

// FUNCTION: GAMEMD 0x5F96B0 (decl; reloc) - stamps the theater letter into name[1]; a theater
// index of -1 leaves the name alone. __fastcall: the name in ECX, the index in EDX.
void OverlayStampTheater(char* name, int idxTheater);

// GLOBAL: GAMEMD 0x87F6B8 - the context handed to the shape drawer.
extern void* OverlayDrawContext;

// STRING: GAMEMD 0x818668 "Demand loading image for %s\n"
extern const char OverlayDemandLoadFormat[];
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) - the debug trace print, __cdecl (the caller pops 8).
void __cdecl OverlayTrace(const char* format, const char* name);

// The file object the demand loader opens (CCFileClass-shaped, read-only here; sizeof 0x6C, from the
// frame layout of 0x5FEDE0 and the constructor 0x4739F0). Three levels of destructor are visible in
// the caller: the derived one is expanded inline (it clears +0x64 and destroys the member at +0x58),
// the middle one only resets its vptr (retail stores 0x7E1668) and the base body 0x431B80 is an
// out-of-line call. The constructor and the shape read are out-of-line.
class OverlayFileBase
{
public:
    // FUNCTION: GAMEMD 0x431B80 (decl; reloc) - the base destructor body.
    virtual ~OverlayFileBase();
    char unknown_04[0x58 - 4];   // +0x04..+0x57
};

class OverlayFileMid : public OverlayFileBase
{
public:
    virtual ~OverlayFileMid() {}   // vptr 0x7E1668
};

class OverlayFileMember
{
public:
    // FUNCTION: GAMEMD 0x43AE50 (decl; reloc)
    ~OverlayFileMember();
    char unknown_00[0xC];
};

class OverlayFileView : public OverlayFileMid
{
public:
    // FUNCTION: GAMEMD 0x4739F0 (decl; reloc) - opens the named file; vptr 0x7E16B0.
    OverlayFileView(const char* path);
    // FUNCTION: GAMEMD 0x4A3890 (decl; reloc) - reads the whole file as a shape.
    void* ReadShape();
    virtual ~OverlayFileView() { unknown_64 = 0; }

    OverlayFileMember unknown_58;   // +0x58
    int               unknown_64;   // +0x64
    int               unknown_68;   // +0x68
};
GG_STATIC_ASSERT(offsetof(OverlayFileView, unknown_58) == 0x58);
GG_STATIC_ASSERT(offsetof(OverlayFileView, unknown_64) == 0x64);
GG_STATIC_ASSERT(sizeof(OverlayFileView) == 0x6C);

// GLOBAL: GAMEMD 0x889F64 - the shared empty string the readers use as their text default.
extern const char OverlayEmptyText[];
// FUNCTION: GAMEMD 0x428B80 (decl; reloc) - finds the animation type of that name. __fastcall: the
// name in ECX.

// The shape drawer through the inline the originals call it by: the arguments are evaluated into
// the call sequence after the surrounding code instead of being hoisted above it.
inline void OverlayDrawShapeInline(MapObjSurfaceView* surface, void* context, void* shape, int frame,
                                   MapObjPoint* where, RectangleStruct* clip, int flags, int a6,
                                   int zAdjust, int a8, int a9, int a10, int a11, int a12,
                                   MapObjPoint offset)
{
    MapObjDrawShape(surface, context, shape, frame, where, clip, flags, a6, zAdjust, a8, a9, a10, a11,
                     a12, offset);
}

// A colour palette object; only the converter at +0x30C is read.
struct OverlayPaletteView
{
    char  unknown_00[0x30C];
    void* Convert;          // +0x30C
};
GG_STATIC_ASSERT(offsetof(OverlayPaletteView, Convert) == 0x30C);
// GLOBAL: GAMEMD 0xB054D4 - the palette array (a pointer to the array; read-only here).
extern OverlayPaletteView** OverlayPalettes;

// The session object (global pointer 0xA83D4C); only the palette index of the veins is read.
struct OverlaySessionView
{
    char unknown_00[0x16054];
    int  VeinsPalette;      // +0x16054
};
GG_STATIC_ASSERT(offsetof(OverlaySessionView, VeinsPalette) == 0x16054);
// GLOBAL: GAMEMD 0xA83D4C
extern OverlaySessionView* OverlaySession;

// A tiberium type (partial; read-only here).
struct OverlayTiberiumView
{
    char unknown_00[0xC0];
    int  PaletteIndex;      // +0xC0
    char unknown_C4[0xE0 - 0xC4];
    OverlayTypeClass* unknown_E0;   // +0xE0
};
GG_STATIC_ASSERT(offsetof(OverlayTiberiumView, PaletteIndex) == 0xC0);
GG_STATIC_ASSERT(offsetof(OverlayTiberiumView, unknown_E0) == 0xE0);
// GLOBAL: GAMEMD 0xB0F4EC - the tiberium type array (a pointer to the array; read-only here).
extern OverlayTiberiumView** OverlayTiberiumTypes;
// FUNCTION: GAMEMD 0x5FDD20 (read-only here, matched elsewhere) - the tiberium type index of an overlay
// type index. __fastcall (ECX).
int OverlayTiberiumIndexOf(int overlayIndex);

// ---- bindings used by OverlayClass::Mark (0x5FC570) -------------------------------------------------

// GLOBAL: GAMEMD 0x880994 - a value copied into cell +0x50 while a placement argument is parked.
extern int OverlayParkedValue;

// The wall / fence tables Mark reads (read-only here): for each of the four types of a group, the
// first facing, the type to place on the run, the second facing, and for each of the four facings
// the type that ends the run; and the pair of (random-fill base types) per axis.
// GLOBAL: GAMEMD 0x8333C0 / 0x8333D0 / 0x8333E0 / 0x8333F0 / 0x8333F8   (types 0x7A-0x7D)
extern const int OverlayFenceFirstFacing[4];
extern const int OverlayFenceRunType[4];
extern const int OverlayFenceSecondFacing[4];
extern const int OverlayFenceFillType[2];
extern const int OverlayFenceEndType[4];
// GLOBAL: GAMEMD 0x833408 / 0x833418 / 0x833428 / 0x833438 / 0x833440 (types 0xE9-0xEC)
extern const int OverlayRoadFirstFacing[4];
extern const int OverlayRoadRunType[4];
extern const int OverlayRoadSecondFacing[4];
extern const int OverlayRoadFillType[2];
extern const int OverlayRoadEndType[4];

// A veinhole monster (opaque storage; the constructor takes the cell coordinate).
class OverlayVeinholeView
{
public:
    // FUNCTION: GAMEMD 0x74C5B0 (decl; reloc)
    OverlayVeinholeView(MapObjCell* cell);
    char storage[0x108];
};
GG_STATIC_ASSERT(sizeof(OverlayVeinholeView) == 0x108);
// FUNCTION: GAMEMD 0x74D670 (decl; reloc) - whether a veinhole may stand on that cell. __fastcall
// shape (the coordinate in ECX).
bool OverlayVeinholeEligible(MapObjCell* cell);

#endif  // GG_MATCH_MAP_TERRAIN_OBJECTS_OVERLAY_SHARED_H
