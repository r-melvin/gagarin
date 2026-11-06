// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Retail globals, views and out-of-partition functions the BuildingTypeClass bodies read, bound by
//   address. Nothing here is defined by the module. Everything was read from the retail gamemd.exe v1.001.
#ifndef GG_MATCH_ECONOMY_HOUSE_BUILDING_TYPES_BUILDING_SHARED_H
#define GG_MATCH_ECONOMY_HOUSE_BUILDING_TYPES_BUILDING_SHARED_H

#include "types_building_type_class.h"
#include "ccini_class_methods.h"
#include "_layout/obj_0069e430.h"
#include "_layout/geometry2d.h"
#include "_layout/cell.h"
#include "_layout/cell_offset.h"
#include "display_objects_globals.h"
#include "shared_constants_globals.h"

// The map object (global 0x87F7E8; read-only here). The floor-height lookup ignores its `this`.
class TypesMapView
{
public:
    // FUNCTION: GAMEMD 0x578080 (read-only here) - the floor height under a coordinate.
    int GetFloorHeight(CoordStruct* coord);
};
// GLOBAL: GAMEMD 0x87F7E8
extern TypesMapView TypesMap;

// The element of the function-local static cell list the foundation slot returns. The user-declared
// destructor is what makes VC6 register an atexit stub (a bare RET) for the static.
struct TypesStaticCell : public CellStruct
{
    TypesStaticCell(short x, short y) { X = x; Y = y; }
    ~TypesStaticCell() {}
};
GG_STATIC_ASSERT(sizeof(TypesStaticCell) == 4);

// Builds one static element through a named local returned by value (retail builds it in a temporary
// and copies it as one dword).
inline TypesStaticCell TypesMakeStaticCell(short x, short y)
{
    TypesStaticCell cell(x, y);
    return cell;
}

// GLOBAL: GAMEMD 0x89C8D0 - the all-zero coordinate the constructor copies into the coordinate members
// (its first two dwords also serve as the zero point), and GLOBAL: GAMEMD 0x89C8A0 - the 16-byte object
// copied into +0x1538.
extern CoordStructInit TypesZeroCoord;
extern BuildingTypeQuad TypesZeroQuad;

// GLOBAL: GAMEMD 0x89C900 / 0x89D368 - the per-foundation cell lists (0x78 bytes each, 22 entries) the
// foundation slot and the outside list point into after a load. Defined in tu039_building_type_class.cpp.
extern FoundationCell TypesFoundationCells[22][30];
extern FoundationCell TypesFoundationOutsideCells[22][30];

#include "foundation_dimensions.h"

// The scenario object (global pointer 0xA8B230; read-only here); only the theater index is read.
struct TypesScenarioView
{
    unsigned char unknown_000[0x1258];
    int TheaterIndex;   // +0x1258
};
GG_STATIC_ASSERT(offsetof(TypesScenarioView, TheaterIndex) == 0x1258);
// GLOBAL: GAMEMD 0xA8B230
extern TypesScenarioView* TypesScenario;

extern "C" void __cdecl _makepath(char* path, const char* drive, const char* dir, const char* fname,
                                  const char* ext);
// FUNCTION: GAMEMD 0x5F96B0 (read-only here) - stamps the theater letter into a file name. __fastcall.
void TypesStampTheater(char* name, int theaterIndex);
// FUNCTION: GAMEMD 0x5F9710 (read-only here) - stamps the generic theater letter ('G') into a file name.
// __fastcall (the name in ECX).
void TypesStampGenericTheater(char* name);

// The file object the demand loaders open (CCFileClass-shaped, read-only here; sizeof 0x6C, from the
// frame layout of 0x45F040 and the constructor 0x4739F0). Three levels of destructor are visible in
// the caller: the derived one is expanded inline (it clears +0x64 and destroys the member at +0x58),
// the middle one only resets its vptr (retail stores 0x7E1668) and the base body 0x431B80 is an
// out-of-line call. The constructor, the open and the shape read are out-of-line.
class TypesFileBase
{
public:
    // FUNCTION: GAMEMD 0x431B80 (read-only here) - the base destructor body.
    virtual ~TypesFileBase();
    char unknown_04[0x58 - 4];   // +0x04..+0x57
};

class TypesFileMid : public TypesFileBase
{
public:
    virtual ~TypesFileMid() {}   // vptr 0x7E1668
};

class TypesFileMember
{
public:
    // FUNCTION: GAMEMD 0x43AE50 (read-only here)
    ~TypesFileMember();
    char unknown_00[0xC];
};

class TypesFileView : public TypesFileMid
{
public:
    // FUNCTION: GAMEMD 0x4739F0 (read-only here) - opens the named file; vptr 0x7E16B0.
    TypesFileView(const char* path);
    // FUNCTION: GAMEMD 0x473C50 (read-only here)
    bool Open(int access);
    // FUNCTION: GAMEMD 0x4A3890 (read-only here) - reads the whole file as a shape.
    void* ReadShape();
    virtual ~TypesFileView() { unknown_64 = 0; }

    TypesFileMember unknown_58;   // +0x58
    int             unknown_64;   // +0x64
    int             unknown_68;   // +0x68
};
GG_STATIC_ASSERT(offsetof(TypesFileView, unknown_58) == 0x58);
GG_STATIC_ASSERT(offsetof(TypesFileView, unknown_64) == 0x64);
GG_STATIC_ASSERT(sizeof(TypesFileView) == 0x6C);

// GLOBAL: GAMEMD 0x887180 - the art INI reader (same interface as the rules reader).
extern CCINIClass DAT_00887180;
// FUNCTION: GAMEMD 0x7514D0 (read-only here) - looks up a sound by name, -1 when unknown. __fastcall.
int TypesFindVoc(const char* name);
// FUNCTION: GAMEMD 0x5FEC70 (read-only here) - looks up an overlay type by name. __fastcall.
OverlayTypeClass* TypesFindOverlay(const char* name);
// FUNCTION: GAMEMD 0x466000 (read-only here) - finds or allocates a building type by name in an array.
// __fastcall (name in ECX, array in EDX).
BuildingTypeClass* TypesFindBuildingType(const char* name, void* array);
// FUNCTION: GAMEMD 0x7E14B0 (import) - user32 wsprintfA.
extern "C" __declspec(dllimport) int __cdecl wsprintfA(char* buffer, const char* format, ...);

#endif  // GG_MATCH_ECONOMY_HOUSE_BUILDING_TYPES_BUILDING_SHARED_H
