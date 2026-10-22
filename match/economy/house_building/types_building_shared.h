// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail globals, views and out-of-partition functions the BuildingTypeClass bodies read, bound by
//   address. Nothing here is defined by the module. Everything was read from the retail gamemd.exe v1.001.
#ifndef GG_MATCH_ECONOMY_HOUSE_BUILDING_TYPES_BUILDING_SHARED_H
#define GG_MATCH_ECONOMY_HOUSE_BUILDING_TYPES_BUILDING_SHARED_H

#include "types_building_type_class.h"

// The map object (global 0x87F7E8; read-only here). The floor-height lookup ignores its `this`.
class TypesMapView
{
public:
    // FUNCTION: GAMEMD 0x578080 (read-only here) - the floor height under a coordinate.
    int GetFloorHeight(HBCoord* coord);
};
// GLOBAL: GAMEMD 0x87F7E8
extern TypesMapView TypesMap;

// The element of the function-local static cell list the foundation slot returns. The user-declared
// destructor is what makes VC6 register an atexit stub (a bare RET) for the static.
struct TypesStaticCell
{
    short X;   // +0x00
    short Y;   // +0x02
    TypesStaticCell(short x, short y) : X(x), Y(y) {}
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

// The bounds of one shape frame (four dwords), as the shape bounds query fills them in.
struct TypesFrameRect
{
    int X;   // +0x00
    int Y;   // +0x04
    int W;   // +0x08
    int H;   // +0x0C
};
GG_STATIC_ASSERT(sizeof(TypesFrameRect) == 0x10);

// A loaded shape (read-only view).
class TypesShapeView
{
public:
    // FUNCTION: GAMEMD 0x69E7E0 (read-only here) - fills and returns the bounds of one frame, or 0.
    TypesFrameRect* GetFrameRect(TypesFrameRect* out, int frame);
};

// GLOBAL: GAMEMD 0x89C8D0 - the all-zero coordinate the constructor copies into the coordinate members
// (its first two dwords also serve as the zero point), and GLOBAL: GAMEMD 0x89C8A0 - the 16-byte object
// copied into +0x1538.
extern HBCoord TypesZeroCoord;
extern TypesQuad TypesZeroQuad;

// GLOBAL: GAMEMD 0x89C900 / 0x89D368 - the per-foundation cell lists (0x78 bytes each, 22 entries) the
// foundation slot and the outside list point into after a load.
struct TypesFoundationEntry
{
    unsigned char data[0x78];
};
GG_STATIC_ASSERT(sizeof(TypesFoundationEntry) == 0x78);
extern TypesFoundationEntry TypesFoundationCells[22];
extern TypesFoundationEntry TypesFoundationOutsideCells[22];

// GLOBAL: GAMEMD 0x8192B8 / 0x819310 - the width and height, in cells, of each of the 22 foundations.
extern const int TypesFoundationWidth[22];
extern const int TypesFoundationHeight[22];
// GLOBAL: GAMEMD 0x89DDB8 - the height of one level in leptons.
extern int TypesLevelHeight;

// A type object whose cost slot (33, +0x84) the cost query calls, with the dock list's item pointer.
class TypesCostTypeView
{
public:
    virtual ~TypesCostTypeView();
    virtual void vf_1();
    virtual void vf_2();
    virtual void vf_3();
    virtual void vf_4();
    virtual void vf_5();
    virtual void vf_6();
    virtual void vf_7();
    virtual void vf_8();
    virtual void vf_9();
    virtual void vf_10();
    virtual void vf_11();
    virtual void vf_12();
    virtual void vf_13();
    virtual void vf_14();
    virtual void vf_15();
    virtual void vf_16();
    virtual void vf_17();
    virtual void vf_18();
    virtual void vf_19();
    virtual void vf_20();
    virtual void vf_21();
    virtual void vf_22();
    virtual void vf_23();
    virtual void vf_24();
    virtual void vf_25();
    virtual void vf_26();
    virtual void vf_27();
    virtual void vf_28();
    virtual void vf_29();
    virtual void vf_30();
    virtual void vf_31();
    virtual void vf_32();
    virtual int GetCost(int house);   // slot 33 (+0x84)

    unsigned char unknown_04[0x3EC - 4];   // +0x04..+0x3EB
    BuildingTypeClass** DockItems;         // +0x3EC  (Items of the TypeList at +0x3E8)
};
GG_STATIC_ASSERT(offsetof(TypesCostTypeView, DockItems) == 0x3EC);

// The rules object (global pointer 0x8871E0; read-only here; only the members read are named).
struct TypesRulesView
{
    unsigned char unknown_000[0xB5C];
    TypesCostTypeView** PadAircraft;   // +0xB5C Items of the PadAircraft type list at +0xB58 (rules key 0x83C748, read at 0x66F9D8)
    unsigned char unknown_B60[0x1518 - 0xB60];
    double unknown_1518;                  // +0x1518
    unsigned char unknown_1520[0x17D0 - 0x1520];
    int  unknown_17D0;                    // +0x17D0
    unsigned char unknown_17D4[0x17E8 - 0x17D4];
    bool unknown_17E8;                    // +0x17E8
};
GG_STATIC_ASSERT(offsetof(TypesRulesView, PadAircraft) == 0xB5C);
GG_STATIC_ASSERT(offsetof(TypesRulesView, unknown_1518) == 0x1518);
GG_STATIC_ASSERT(offsetof(TypesRulesView, unknown_17D0) == 0x17D0);
GG_STATIC_ASSERT(offsetof(TypesRulesView, unknown_17E8) == 0x17E8);
// GLOBAL: GAMEMD 0x8871E0
extern TypesRulesView* TypesRules;

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
// STRING: GAMEMD 0x81834C ".SHP"
extern const char TypesShpExtension[];
// FUNCTION: GAMEMD 0x5F96B0 (read-only here) - stamps the theater letter into a file name. __fastcall.
void __fastcall TypesStampTheater(char* name, int theaterIndex);
// FUNCTION: GAMEMD 0x5F9710 (read-only here) - stamps the generic theater letter ('G') into a file name.
// __fastcall (the name in ECX).
void __fastcall TypesStampGenericTheater(char* name);

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
extern TypesIniView TypesArtIni;
// FUNCTION: GAMEMD 0x7514D0 (read-only here) - looks up a sound by name, -1 when unknown. __fastcall.
int __fastcall TypesFindVoc(const char* name);
// FUNCTION: GAMEMD 0x5FEC70 (read-only here) - looks up an overlay type by name. __fastcall.
void* __fastcall TypesFindOverlay(const char* name);
// FUNCTION: GAMEMD 0x466000 (read-only here) - finds or allocates a building type by name in an array.
// __fastcall (name in ECX, array in EDX).
void* __fastcall TypesFindBuildingType(const char* name, void* array);
// FUNCTION: GAMEMD 0x7E14B0 (import) - user32 wsprintfA.
extern "C" __declspec(dllimport) int __cdecl wsprintfA(char* buffer, const char* format, ...);

#endif  // GG_MATCH_ECONOMY_HOUSE_BUILDING_TYPES_BUILDING_SHARED_H
