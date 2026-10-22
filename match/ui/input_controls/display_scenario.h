// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout, vtable slots and ABI read numerically off the user's retail gamemd.exe v1.001 via the local Ghidra CLI
//   (entry disassembly from 0x4ACE70 and 0x4AE4F0) and the RTTI vtable of DisplayClass (0x7E6114, 50 slots).
//   Address-scoped views: only members these two entries touch are named; every other byte is a gap.
//
// Evidence summary for 0x4AE4F0 (DisplayClass slot 33, thiscall, RET 4, one int argument, returns a wide string):
//   the argument is range checked 500..900 (CMP 0x1F4 / JL, CMP 0x384 / JG); slot 26 (+0x68) of the screen is
//   queried; the mouse singleton 0x887640 slot 13 (+0x34) is called with the address of a local and returns a
//   point pointer; both coordinates are reduced by the tactical origin 0x886FA0/0x886FA4; the map singleton 0x87F7E8
//   is asked (0x692300) for six out values. Strings: 'TXT_SHADOW' 0x82019C, 'D:\ra2mdpost\Display.CPP' 0x8201A8,
//   L"(%d,%d)" 0x8201C4 (UTF-16 bytes read with `ghidra memory read`), the 0x8A0630 text buffer.
#ifndef GG_MATCH_UI_INPUT_CONTROLS_DISPLAY_SCENARIO_H
#define GG_MATCH_UI_INPUT_CONTROLS_DISPLAY_SCENARIO_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "ui_display_chain.h"
#include "mouse_ww_mouse_class.h"

// A lepton coordinate (three dwords: the sprintf arguments are X and Y divided by 256).
struct DisplayScCoord
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08
};
GG_STATIC_ASSERT(sizeof(DisplayScCoord) == 12);

// WWMouseClass::Instance (GLOBAL 0x887640, slot 13 vf_13) is WWMouseClassInstance, mouse_ww_mouse_class.h.

// The cell under the cursor: flags at +0x12C (bit 3), UI name at 0x484FF0, a house query at 0x4870D0.
struct DisplayScTagInstance;
struct DisplayScCellObject
{
    char unknown_000[0x38];    // +0x000
    int  unknown_38;           // +0x038  written with a random ground value
    int  unknown_3C;           // +0x03C  zero until a tag is attached
    char unknown_040[0x11A - 0x40];
    unsigned char unknown_11A; // +0x11A
    unsigned char unknown_11B; // +0x11B  incremented by the map level
    char unknown_11C[0x12C - 0x11C];
    int  Flags;                // +0x12C
    // FUNCTION: GAMEMD 0x485250 (decl; reloc) -- CellClass::ReplaceTag.
    void ReplaceTag(DisplayScTagInstance* tag);
    // FUNCTION: GAMEMD 0x4870D0 (decl; reloc) -- reads a word table at +0x7C indexed by the argument.
    bool FUN_004870D0(int index);
    // FUNCTION: GAMEMD 0x484FF0 (decl; reloc) -- CellClass::GetUIName.
    const wchar_t* FUN_00484FF0();
};
GG_STATIC_ASSERT(offsetof(DisplayScCellObject, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(DisplayScCellObject, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(DisplayScCellObject, unknown_11A) == 0x11A);
GG_STATIC_ASSERT(offsetof(DisplayScCellObject, unknown_11B) == 0x11B);
GG_STATIC_ASSERT(offsetof(DisplayScCellObject, Flags) == 0x12C);

// Something with a house-index field at +0x30 (the current player).
struct DisplayScHouse
{
    char unknown_00[0x30];   // +0x00
    int  Index;              // +0x30
};
GG_STATIC_ASSERT(offsetof(DisplayScHouse, Index) == 0x30);
// GLOBAL: GAMEMD 0xA83D4C -- HouseClass::CurrentPlayer.
extern DisplayScHouse* DisplayScHouse_00A83D4C;

// A game object found under the cursor. Fields: +0x14 bit 0, +0x41A byte, +0x220 dword; slots 18 (+0x48, returns
// a coordinate through a hidden pointer, no other argument), 33 (+0x84, returns a pointer to something with a byte
// at +0xC9A) and 36 (+0x90, returns the wide string this entry hands back).
struct DisplayScOwner
{
    char unknown_00[0xC9A];
    bool Flag_0C9A;   // +0xC9A
};
class DisplayScObject
{
public:
    virtual void vf_00(); virtual void vf_01(); virtual void vf_02(); virtual void vf_03();
    virtual void vf_04(); virtual void vf_05(); virtual void vf_06(); virtual void vf_07();
    virtual void vf_08(); virtual void vf_09(); virtual void vf_10(); virtual void vf_11();
    virtual void vf_12(); virtual void vf_13(); virtual void vf_14(); virtual void vf_15();
    virtual void vf_16(); virtual void vf_17();
    virtual DisplayScCoord vf_18();                   // +0x48
    virtual void vf_19(); virtual void vf_20(); virtual void vf_21(); virtual void vf_22();
    virtual void vf_23(); virtual void vf_24(); virtual void vf_25(); virtual void vf_26();
    virtual void vf_27(); virtual void vf_28(); virtual void vf_29(); virtual void vf_30();
    virtual void vf_31(); virtual void vf_32();
    virtual DisplayScOwner* vf_33();                  // +0x84
    virtual void vf_34(); virtual void vf_35();
    virtual const wchar_t* vf_36();                   // +0x90

    char unknown_04[0x14 - 4];   // +0x04
    unsigned int Flags14;        // +0x14
    char unknown_18[0x220 - 0x18];
    int  Value220;               // +0x220
    char unknown_224[0x41A - 0x224];
    bool Flag41A;                // +0x41A
};
GG_STATIC_ASSERT(offsetof(DisplayScObject, Flags14) == 0x14);
GG_STATIC_ASSERT(offsetof(DisplayScObject, Value220) == 0x220);
GG_STATIC_ASSERT(offsetof(DisplayScObject, Flag41A) == 0x41A);

// The map singleton at 0x87F7E8 (a MouseClass instance): three methods are called on it.
struct DisplayScMap
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x565730 (decl; reloc) -- MapClass::GetTargetCell.
    DisplayScCellObject* FUN_00565730(const DisplayScCoord& where);
    // FUNCTION: GAMEMD 0x692300 (decl; reloc) -- six out parameters (stack, RET 0x18).
    void FUN_00692300(const Point2D& screen, CellStruct* cell, DisplayScCoord* coord,
                      DisplayScObject** object, bool* flagA, bool* flagB);
};
// GLOBAL: GAMEMD 0x87F7E8
extern DisplayScMap DisplayScMap_0087F7E8;

// GLOBAL: GAMEMD 0x886FA0 / 0x886FA4 -- tactical view origin.
extern Point2D DisplayScOrigin_00886FA0;
// GLOBAL: GAMEMD 0xA8F7D8 -- coordinate debug display on.
extern bool DisplayScFlag_00A8F7D8;
// GLOBAL: GAMEMD 0xB73550 -- non-zero while the map draws tile by tile.
extern int DisplayScDrawing_00B73550;
// GLOBAL: GAMEMD 0x8A0630 -- shared text buffer.
extern wchar_t DisplayScText_008A0630[];

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- __fastcall(label ECX, index-out EDX, file, line), RET 8.
const wchar_t* FUN_00734E60(const char* label, int* index, const char* file, int line);
// FUNCTION: GAMEMD 0x7CA564 (decl; reloc) -- LIBRARY _swprintf.
extern "C" int __cdecl _swprintf(wchar_t* buffer, const wchar_t* format, ...);

// ---- 0x4ACE70 evidence -----------------------------------------------------------------------------------------
// DisplayClass slot 32 (thiscall, RET 4): one argument, the INI reader (EDI). Reads [Map] Size / Level / Fill /
// Theater / LocalSize and [CellTags], the five packed sections named by the pointer array at 0x7E6028, and walks the
// scenario waypoints. No value is returned (EAX is not set on the way out).

struct DisplayScGround
{
    int Base;     // random range upper bound (0 for Clear, 3 for Water)
    int Second;   // value added to the roll
};

// A tag instance reached through TagTypeClass::GetInstance (0x6E52A0).
struct DisplayScTagInstance
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x6E5560 (decl; reloc) -- takes the cell pair as one dword.
    void FUN_006E5560(CellStruct cell);
};
struct DisplayScTagType
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x6E52A0 (decl; reloc)
    DisplayScTagInstance* FUN_006E52A0();
};
// FUNCTION: GAMEMD 0x6E6310 (decl; reloc) -- TagTypeClass::FindOrAllocate, __fastcall(name ECX).
DisplayScTagType* FUN_006E6310(const char* name);

// The straw pair the packed sections are fed through (see the UUBlock writer for the same shapes). Flat structs with
// explicit vtable seat stores, the repository convention for the straw classes.
extern char DisplayScVT_007E61F0;   // VTABLE: GAMEMD 0x7E61F0 -- Straw.
extern char DisplayScVT_007E61E0;   // VTABLE: GAMEMD 0x7E61E0 -- the buffer straw.

struct DisplayScBuffer
{
    void*         Data;          // +0x00
    int           Length;        // +0x04
    unsigned char IsAllocated;   // +0x08
    unsigned char _pad009[3];    // +0x09
    // FUNCTION: GAMEMD 0x43AD00 (decl; reloc) -- ctor(buffer, size); a null buffer allocates.
    DisplayScBuffer* Construct(void* buffer, int size);
    // FUNCTION: GAMEMD 0x43AE50 (decl; reloc) -- explicit cleanup.
    void Clear();
};
GG_STATIC_ASSERT(sizeof(DisplayScBuffer) == 0x0C);

struct DisplayScStraw
{
    char* Vtable;      // +0x00
    int   ChainTo;     // +0x04
    int   ChainFrom;   // +0x08
    // FUNCTION: GAMEMD 0x6C9850 (decl; reloc) -- destructor.
    void Destroy();
};
struct DisplayScBufferStraw : DisplayScStraw
{
    DisplayScBuffer Buffer;   // +0x0C
    int             Index;    // +0x18
};
GG_STATIC_ASSERT(offsetof(DisplayScBufferStraw, Buffer) == 0x0C);
GG_STATIC_ASSERT(offsetof(DisplayScBufferStraw, Index) == 0x18);
GG_STATIC_ASSERT(sizeof(DisplayScBufferStraw) == 0x1C);

// The off-screen surface built inline: Surface ctor (0x4AEC60) then the XSurface and BSurface seat stores. Layout:
// +0x00 vtable, +0x04 width, +0x08 height (ctor), +0x0C lock count, +0x10 bytes per pixel, +0x14 pixel buffer.
struct DisplayScSurfaceVtbl;
struct DisplayScSurface
{
    DisplayScSurfaceVtbl* Vtbl;            // +0x00
    int                   Width;           // +0x04
    int                   Height;          // +0x08
    int                   LockCount;       // +0x0C
    int                   BytesPerPixel;   // +0x10
    DisplayScBuffer       Pixels;          // +0x14
    // FUNCTION: GAMEMD 0x4AEC60 (decl; reloc) -- Surface::Surface(width, height), RET 8.
    void Init(int width, int height);
};
GG_STATIC_ASSERT(offsetof(DisplayScSurface, LockCount) == 0x0C);
GG_STATIC_ASSERT(offsetof(DisplayScSurface, BytesPerPixel) == 0x10);
GG_STATIC_ASSERT(offsetof(DisplayScSurface, Pixels) == 0x14);
typedef int (DisplayScSurface::*DisplayScSurfaceFn)();
struct DisplayScSurfaceVtbl
{
    char               _pad000[0x70];   // +0x00
    DisplayScSurfaceFn At_70;           // +0x70  (BSurface: bytes per pixel)
    DisplayScSurfaceFn At_74;           // +0x74  (BSurface: pitch)
};
GG_STATIC_ASSERT(offsetof(DisplayScSurfaceVtbl, At_70) == 0x70);
GG_STATIC_ASSERT(offsetof(DisplayScSurfaceVtbl, At_74) == 0x74);
extern DisplayScSurfaceVtbl DisplayScVT_007E2104;   // VTABLE: GAMEMD 0x7E2104 -- XSurface.
extern DisplayScSurfaceVtbl DisplayScVT_007E2070;   // VTABLE: GAMEMD 0x7E2070 -- BSurface.

// The map singleton's pack readers: each takes the straw by address.
struct DisplayScMapPacks
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x56B5A0 / 0x56B780 / 0x56B8A0 / 0x56B9A0 / 0x56BAC0 (decl; reloc)
    void FUN_0056B5A0(DisplayScBufferStraw* straw);
    void FUN_0056B780(DisplayScBufferStraw* straw);
    void FUN_0056B8A0(DisplayScBufferStraw* straw);
    void FUN_0056B9A0(DisplayScBufferStraw* straw);
    void FUN_0056BAC0(DisplayScBufferStraw* straw);
    // FUNCTION: GAMEMD 0x588990 (decl; reloc)
    void FUN_00588990();
};
// GLOBAL: GAMEMD 0x87F7E8 -- same object as DisplayScMap_0087F7E8.
extern DisplayScMapPacks DisplayScMapPacks_0087F7E8;

// The scenario singleton (0xA8B230): only the touched members.
struct DisplayScRandom
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x65C7E0 (decl; reloc) -- RandomClass::RandomRanged(low, high).
    int FUN_0065C7E0(int low, int high);
};
struct DisplayScScenario
{
    char            unknown_000[0x20C];   // +0x000
    int             Waypoint_20C;         // +0x20C
    int             Waypoint_210;         // +0x210
    int             Value_214;            // +0x214
    DisplayScRandom Random_218;           // +0x218
    char            unknown_21C[0x1258 - 0x21C];
    int             Theater;              // +0x1258
    char            unknown_125C[0x1CB0 - 0x125C];
    unsigned char   Flag_1CB0;            // +0x1CB0
    char            unknown_1CB1[0x348E - 0x1CB1];
    CellStruct   Cells_348E[4];        // +0x348E, +0x3492, +0x3496, +0x349A
    char            unknown_349E[0x34BD - 0x349E];
    unsigned char   Flag_34BD;            // +0x34BD

    // FUNCTION: GAMEMD 0x68BDC0 (decl; reloc) -- reads the waypoint list from the INI.
    void FUN_0068BDC0(struct DisplayScIni* ini);
    // FUNCTION: GAMEMD 0x68BD80 (decl; reloc)
    bool FUN_0068BD80(int waypoint);
    // FUNCTION: GAMEMD 0x68BF50 (decl; reloc)
    void FUN_0068BF50(int waypoint, CellStruct cell);
    // FUNCTION: GAMEMD 0x68BCC0 (decl; reloc) -- fills and returns the cell of a waypoint.
    CellStruct* FUN_0068BCC0(CellStruct* out, int waypoint);
};
GG_STATIC_ASSERT(offsetof(DisplayScScenario, Random_218) == 0x218);
GG_STATIC_ASSERT(offsetof(DisplayScScenario, Theater) == 0x1258);
GG_STATIC_ASSERT(offsetof(DisplayScScenario, Flag_1CB0) == 0x1CB0);
GG_STATIC_ASSERT(offsetof(DisplayScScenario, Cells_348E) == 0x348E);
GG_STATIC_ASSERT(offsetof(DisplayScScenario, Flag_34BD) == 0x34BD);
// GLOBAL: GAMEMD 0xA8B230 -- ScenarioClass::Instance.
extern DisplayScScenario* DisplayScScenario_00A8B230;

// The INI reader (EDI): all methods are thiscall with the callee popping its arguments.
struct DisplayScIni
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x526B00 (decl; reloc)
    void FUN_00526B00();
    // FUNCTION: GAMEMD 0x527CC0 (decl; reloc) -- returns a rectangle through a hidden pointer.
    RectangleStruct FUN_00527CC0(const char* section, const char* key, const RectangleStruct& fallback);
    // FUNCTION: GAMEMD 0x5276D0 (decl; reloc)
    int FUN_005276D0(const char* section, const char* key, int fallback);
    // FUNCTION: GAMEMD 0x528A10 (decl; reloc) -- (section, key, default, buffer, size)
    int FUN_00528A10(const char* section, const char* key, const char* fallback, char* buffer, int size);
    // FUNCTION: GAMEMD 0x475870 (decl; reloc)
    int FUN_00475870(const char* section, const char* key, int fallback);
    // FUNCTION: GAMEMD 0x526960 (decl; reloc) -- INIClass::GetKeyCount
    int FUN_00526960(const char* section);
    // FUNCTION: GAMEMD 0x526CC0 (decl; reloc) -- INIClass::GetKeyName
    const char* FUN_00526CC0(const char* section, int index);
    // FUNCTION: GAMEMD 0x526FB0 (decl; reloc) -- reads a packed section into a buffer; returns the byte count.
    int FUN_00526FB0(const char* section, void* buffer, int size);
};

// GLOBAL: GAMEMD 0x7E6028 -- the five pack section names.
extern const char* const DisplayScPackName_007E6028[5];
// GLOBAL: GAMEMD 0x889F64 -- shared empty default string.
extern char DisplayScEmpty_00889F64[];
// GLOBAL: GAMEMD 0xAA10B0 / 0xAA0738 -- ground values for Clear / Water.
extern int DisplayScGround_00AA10B0;
extern int DisplayScGround_00AA0738;
// GLOBAL: GAMEMD 0xA8ED6B / 0xA8ED5D (bytes) / 0xA8ED7C (int).
extern bool DisplayScFlag_00A8ED6B;
extern bool DisplayScFlag_00A8ED5D;
extern int  DisplayScValue_00A8ED7C;
// GLOBAL: GAMEMD 0x822CF8 -- the theater last loaded.
extern int DisplayScTheater_00822CF8;
// GLOBAL: GAMEMD 0x887324 -- Tactical::Instance.
struct DisplayScTactical
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x6D6070 (decl; reloc) -- Tactical::SetTacticalPosition
    void FUN_006D6070(DisplayScCoord* coord);
};
extern DisplayScTactical* DisplayScTactical_00887324;
// GLOBAL: GAMEMD 0xA8B238 -- SessionClass::Instance (progress report target).
struct DisplayScSession
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x69AE90 (decl; reloc)
    void FUN_0069AE90(int step);
};
extern DisplayScSession DisplayScSession_00A8B238;
// FUNCTION: GAMEMD 0x48D080 (decl; reloc) -- Unsorted::CallBack, no arguments.
void __cdecl FUN_0048D080();
// FUNCTION: GAMEMD 0x71DCA0 / 0x5FE620 / 0x45E970 / 0x427940 / 0x6B5490 (decl; reloc) -- per-theater loaders, ECX.
void FUN_0071DCA0(int theater);
void FUN_005FE620(int theater);
void FUN_0045E970(int theater);
void FUN_00427940(int theater);
void FUN_006B5490(int theater);
// FUNCTION: GAMEMD 0x545150 (decl; reloc) -- __fastcall(unused ECX, flag DL).
void FUN_00545150(int unused, char flag);
// FUNCTION: GAMEMD 0x547110 (decl; reloc)
void __cdecl FUN_00547110();
// FUNCTION: GAMEMD 0x546DA0 (decl; reloc) -- __fastcall(flag CL, value DL).
void FUN_00546DA0(bool flag, unsigned char value);
// LIBRARY: GAMEMD 0x7C8D20 -- strcmp; GAMEMD 0x7C9BFD -- atoi.
extern "C" int __cdecl FUN_007C8D20(const char* a, const char* b);
extern "C" int __cdecl FUN_007C9BFD(const char* s);

// DisplayClass slots 32 / 33, MapClass's MapRect (+0xEC), LocalRect (+0xFC) and the CellTags vector (+0x115C, whose
// AddItem the CellTags loop inlines) are declared in ui_display_chain.h.

#endif  // GG_MATCH_UI_INPUT_CONTROLS_DISPLAY_SCENARIO_H
