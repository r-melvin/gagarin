// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001. The translation
//   unit name ownrdraw.cpp is attested by the assert path string
//   "D:\ra2mdpost\ownrdraw.cpp" at 0x833730.
//
//   Every function declared here opens with the same inlined probe of the
//   hash table at 0xAC1B00 (layout in dialog_type_lookup_predicates.h): the
//   key arrives in ECX (or on the stack) and is spilled so its address can be
//   handed to the table's hash function. Convention facts come from the
//   disassembly of each entry: key in ECX with no stack cleanup at the call
//   sites means __fastcall; `RET 8` with no register arguments means a
//   two-argument __stdcall.
//
//   All names are placeholders (FUN_<addr>); the binary attests none of them.
#ifndef GG_MATCH_UI_OWNRDRAW_H
#define GG_MATCH_UI_OWNRDRAW_H

#include <stddef.h>
#include <string.h>
#include "../core/wide_string_class.h"
#include "../core/string_class.h"
#include "../core/hash_table_view.h"
#include "../core/vector_class.h"
#include "dialog_type_lookup_predicates.h"
#include "dialog_control_group_lookup.h"
#include "control_id_predicate_methods.h"
#include "../platform/window_moving_methods.h"
#include "../renderer/surface_class.h"

// IAT 0x7E14A4: USER32!SendMessageA.
extern "C" __declspec(dllimport) long __stdcall SendMessageA(GG_HWND hWnd,
                                                             unsigned uMsg,
                                                             unsigned wParam,
                                                             long lParam);
// IAT 0x7E14A8: USER32!GetDlgItem.
extern "C" __declspec(dllimport) GG_HWND __stdcall GetDlgItem(GG_HWND hDlg, int nID);
// IAT 0x7E146C: USER32!UpdateWindow.
extern "C" __declspec(dllimport) int __stdcall UpdateWindow(GG_HWND hWnd);
// IAT 0x7E14DC: USER32!GetClassNameA.
extern "C" __declspec(dllimport) int __stdcall GetClassNameA(GG_HWND hWnd, char* lpClassName,
                                                             int nMaxCount);
// IAT 0x7E14E8: USER32!IsWindowEnabled.
extern "C" __declspec(dllimport) int __stdcall IsWindowEnabled(GG_HWND hWnd);
// IAT 0x7E14A0: USER32!EnableWindow.
extern "C" __declspec(dllimport) int __stdcall EnableWindow(GG_HWND hWnd, int bEnable);
// IAT 0x7E14EC: USER32!GetParent.
extern "C" __declspec(dllimport) GG_HWND __stdcall GetParent(GG_HWND hWnd);
// IAT 0x7E14E4: USER32!EnumChildWindows.
extern "C" __declspec(dllimport) int __stdcall EnumChildWindows(
    GG_HWND hParent, int (__stdcall* lpEnumFunc)(GG_HWND, long), long lParam);
// IAT 0x7E1474: USER32!GetWindowLongA.
extern "C" __declspec(dllimport) long __stdcall GetWindowLongA(GG_HWND hWnd, int nIndex);
// 0x7CA564: the CRT swprintf (cdecl, varargs).
extern "C" int __cdecl swprintf(wchar_t* pszBuffer, const wchar_t* pszFormat, ...);
struct GG_RECT
{
    long left;
    long top;
    long right;
    long bottom;
};
GG_STATIC_ASSERT(sizeof(GG_RECT) == 0x10);

// IAT 0x7E1398: USER32!MoveWindow.
extern "C" __declspec(dllimport) int __stdcall MoveWindow(GG_HWND hWnd, int x, int y,
                                                          int nWidth, int nHeight,
                                                          int bRepaint);
// IAT 0x7E13BC: USER32!GetWindowRect.
extern "C" __declspec(dllimport) int __stdcall GetWindowRect(GG_HWND hWnd, GG_RECT* lpRect);
// IAT 0x7E14E0: USER32!IsWindowVisible.
extern "C" __declspec(dllimport) int __stdcall IsWindowVisible(GG_HWND hWnd);
// IAT 0x7E149C: USER32!InvalidateRect.
extern "C" __declspec(dllimport) int __stdcall InvalidateRect(GG_HWND hWnd,
                                                              const void* lpRect,
                                                              int bErase);

// IAT 0x7E14C4: USER32!GetClientRect.
extern "C" __declspec(dllimport) int __stdcall GetClientRect(GG_HWND hWnd, GG_RECT* lpRect);

// FUNCTION: GAMEMD 0x775690 (decl; reloc) -- __fastcall: a control's rectangle.
void FUN_00775690(GG_HWND window, GG_RECT* rect);

// The owner-draw notice a parent receives with WM_DRAWITEM (fields at the
// displacements 0x6213A0 reads: type +0x00, state +0x10, window +0x14,
// rectangle +0x1C).
struct DrawItem_006213A0
{
    unsigned CtlType;     // +0x0000
    unsigned CtlID;       // +0x0004
    unsigned itemID;      // +0x0008
    unsigned itemAction;  // +0x000C
    unsigned itemState;   // +0x0010
    GG_HWND  hwndItem;    // +0x0014
    void*    hDC;         // +0x0018
    GG_RECT  rcItem;      // +0x001C
    unsigned itemData;    // +0x002C
};
GG_STATIC_ASSERT(offsetof(DrawItem_006213A0, CtlType) == 0x00);
GG_STATIC_ASSERT(sizeof(DrawItem_006213A0) == 0x30);
GG_STATIC_ASSERT(offsetof(DrawItem_006213A0, itemState) == 0x10);
GG_STATIC_ASSERT(offsetof(DrawItem_006213A0, hwndItem) == 0x14);
GG_STATIC_ASSERT(offsetof(DrawItem_006213A0, rcItem) == 0x1C);

// GLOBAL: GAMEMD 0x887308 / 0x887310 -- two of the display surfaces; owner
// drawing only runs once both exist. 0x610810 restores the tooltip background
// through 0x887308's slot +0x08.
extern Surface* DAT_00887308;
extern void* DAT_00887310;

// Tooltip state used by 0x610810 (placeholders; layout from the stores). One
// object: a single initialiser (0x6107A0) clears all of it, and the members
// are contiguous from 0xAC1CB8 to 0xAC1DD8.
struct TooltipState_00AC1CB8
{
    RectangleStruct unknown_00;      // +0x000 0xAC1CB8 the tooltip rectangle
    Surface*        unknown_10;      // +0x010 0xAC1CC8 the saved background under the tooltip
    wchar_t         unknown_14[0x80]; // +0x014 0xAC1CCC the tooltip text (0x100 bytes)
    int             unknown_114;     // +0x114 0xAC1DCC nonzero while a tooltip is up
    int             unknown_118;     // +0x118 0xAC1DD0 1 once the background has been put back
    int             unknown_11C;     // +0x11C 0xAC1DD4 the caller's third argument to 0x610810
    TooltipState_00AC1CB8()
    {
        unknown_00.X = 0;
        unknown_00.Y = 0;
        unknown_00.Width = 0;
        unknown_00.Height = 0;
        unknown_10 = 0;
        unknown_14[0] = 0;
        unknown_114 = 0;
        unknown_118 = 0;
        unknown_11C = 0;
    }
};
GG_STATIC_ASSERT(offsetof(TooltipState_00AC1CB8, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(TooltipState_00AC1CB8, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(TooltipState_00AC1CB8, unknown_114) == 0x114);
GG_STATIC_ASSERT(offsetof(TooltipState_00AC1CB8, unknown_118) == 0x118);
GG_STATIC_ASSERT(offsetof(TooltipState_00AC1CB8, unknown_11C) == 0x11C);
GG_STATIC_ASSERT(sizeof(TooltipState_00AC1CB8) == 0x120);
// GLOBAL: GAMEMD 0xAC1CB8
extern TooltipState_00AC1CB8 DAT_00AC1CB8;
// GLOBAL: GAMEMD 0xAC48D8 -- time the tooltip was raised.
extern long DAT_00AC48D8;

// LIBRARY: GAMEMD 0x007CA67F
// time
extern "C" long __cdecl time(long* pTimer);
// LIBRARY: GAMEMD 0x007CA489
// wcscpy
extern "C" wchar_t* __cdecl wcscpy(wchar_t* pDest, const wchar_t* pSource);
// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- the string-table fetch (__fastcall,
// label and flags in registers, source file and line on the stack).
wchar_t* FUN_00734E60(const char* pszLabel, int nFlags, const char* pszFile, int nLine);
// FUNCTION: GAMEMD 0x610950 (decl; reloc) -- __fastcall, flag in CL.
void FUN_00610950(bool bFlag);


// GLOBAL: GAMEMD 0xAC1CAC
extern int DAT_00AC1CAC;

// GLOBAL: GAMEMD 0x8A00A4 / 0x8A00A8 -- display mode width and height.
extern int DAT_008A00A4;
extern int DAT_008A00A8;
// GLOBAL: GAMEMD 0xAC48A8 -- window handle recorded by 0x60C4A0.
extern GG_HWND DAT_00AC48A8;
// FUNCTION: GAMEMD 0x602D70 (__fastcall)
bool FUN_00602D70(int nKey, GG_HWND hCtl);
// FUNCTION: GAMEMD 0x602FE0 (__fastcall)
int FUN_00602FE0(int nKey, GG_HWND hCtl);
// FUNCTION: GAMEMD 0x6033F0 (__fastcall)
int FUN_006033F0(int nKey, GG_HWND hCtl);
// FUNCTION: GAMEMD 0x603810 (__fastcall)
int FUN_00603810(int nKey, GG_HWND hCtl);
// FUNCTION: GAMEMD 0x603D30 (__fastcall)
void FUN_00603D30(int nKey, int nValue);
// FUNCTION: GAMEMD 0x603DD0 (__fastcall)
int FUN_00603DD0(GG_HWND hWnd, unsigned char nValue);
// FUNCTION: GAMEMD 0x603E10 (__fastcall)
int FUN_00603E10(GG_HWND hWnd, unsigned short nLow, unsigned short nHigh);
// FUNCTION: GAMEMD 0x603E40 (__fastcall)
void FUN_00603E40(int nKey, int nValue);
// FUNCTION: GAMEMD 0x606740 (__fastcall)
void FUN_00606740(int nKey, bool bValue);
// FUNCTION: GAMEMD 0x6071E0 (decl; reloc) -- body not yet recovered.
void FUN_006071E0(GG_HWND hWnd, bool bFlag);
// FUNCTION: GAMEMD 0x608380 (__fastcall)
void FUN_00608380(int nKey);
// FUNCTION: GAMEMD 0x6083E0 (__fastcall)
void FUN_006083E0(int nKey);
// FUNCTION: GAMEMD 0x608440 (__fastcall)
void FUN_00608440(int nKey);
// FUNCTION: GAMEMD 0x6084A0 (__fastcall)
void FUN_006084A0(int nKey);
// FUNCTION: GAMEMD 0x608CD0 (decl; reloc) -- body not yet recovered.
bool FUN_00608CD0(GG_HWND hParent, GG_HWND hWnd);
// FUNCTION: GAMEMD 0x6096A0 (__fastcall)
bool FUN_006096A0(GG_HWND hParent, GG_HWND hWnd);
// FUNCTION: GAMEMD 0x609730 (decl; reloc) -- body not yet recovered.
bool FUN_00609730(GG_HWND hParent, GG_HWND hWnd);
// FUNCTION: GAMEMD 0x609AA0 (__fastcall)
bool FUN_00609AA0(GG_HWND hParent, GG_HWND hWnd);
// FUNCTION: GAMEMD 0x609B30 (__fastcall)
bool FUN_00609B30(int nKey, GG_HWND hCtl);
// FUNCTION: GAMEMD 0x609BC0 (__fastcall)
bool FUN_00609BC0(GG_HWND hParent, GG_HWND hWnd);
// FUNCTION: GAMEMD 0x609CF0 (__fastcall)
bool FUN_00609CF0(GG_HWND hParent, GG_HWND hWnd);
// FUNCTION: GAMEMD 0x60A100 (__fastcall)
bool FUN_0060A100(int nKey, GG_HWND hCtl);
// FUNCTION: GAMEMD 0x60A180 (__stdcall)
int __stdcall FUN_0060A180(GG_HWND hWnd, int unused);
// FUNCTION: GAMEMD 0x60A250 (__stdcall)
int __stdcall FUN_0060A250(GG_HWND hWnd, long lParam);
// FUNCTION: GAMEMD 0x60A300 (__fastcall)
bool FUN_0060A300(GG_HWND hWnd);
// FUNCTION: GAMEMD 0x60AA60 (__stdcall)
int __stdcall FUN_0060AA60(GG_HWND hWnd, int unused);
// FUNCTION: GAMEMD 0x60B740 (__fastcall)
void FUN_0060B740(GG_HWND hWnd);
// FUNCTION: GAMEMD 0x60B880 (__fastcall)
bool FUN_0060B880(int nKey, GG_HWND hCtl);
// FUNCTION: GAMEMD 0x60C0C0 (decl; reloc) -- enumeration callback, body not yet recovered.
int __stdcall FUN_0060C0C0(GG_HWND hWnd, long lParam);
// FUNCTION: GAMEMD 0x60C4A0 (__fastcall)
void FUN_0060C4A0(GG_HWND hWnd, long lParam);
// FUNCTION: GAMEMD 0x60C4E0 (__fastcall)
int FUN_0060C4E0(int nKey);
// FUNCTION: GAMEMD 0x60C8D0 (__fastcall)
bool FUN_0060C8D0(int nKey);
// FUNCTION: GAMEMD 0x60C9D0 (__fastcall)
void FUN_0060C9D0(int nKey);
// FUNCTION: GAMEMD 0x60CA30 (__fastcall)
void FUN_0060CA30(int nKey);
// FUNCTION: GAMEMD 0x60CA90 (__fastcall)
bool FUN_0060CA90(int nKey);
// FUNCTION: GAMEMD 0x60CBA0 (__fastcall)
void FUN_0060CBA0(int nKey);
// FUNCTION: GAMEMD 0x60CC00 (__fastcall)
void FUN_0060CC00(int nKey);
// FUNCTION: GAMEMD 0x60CC60 (__fastcall)
bool FUN_0060CC60(int nKey);
// FUNCTION: GAMEMD 0x60CD50 (__fastcall)
bool FUN_0060CD50(int nKey);
// FUNCTION: GAMEMD 0x60CE40 (__fastcall)
int FUN_0060CE40(int nKey);
// FUNCTION: GAMEMD 0x60CEA0 (__fastcall)
int FUN_0060CEA0(int nKey);
// FUNCTION: GAMEMD 0x60D2C0 (__fastcall)
void FUN_0060D2C0(int nKey, int nValue);
// FUNCTION: GAMEMD 0x60D320 (__fastcall)
int FUN_0060D320(int nKey);
struct Obj_006107E0
{
    int     unknown_00;        // +0x0000
    int     unknown_04;        // +0x0004
    int     unknown_08;        // +0x0008
    int     unknown_0C;        // +0x000C
    int     unknown_10;        // +0x0010
    wchar_t unknown_14[0x80];  // +0x0014
    int     unknown_114;       // +0x0114
    int     unknown_118;       // +0x0118
    int     unknown_11C;       // +0x011C

    // FUNCTION: GAMEMD 0x6107E0 (__thiscall)
    Obj_006107E0();
};
GG_STATIC_ASSERT(offsetof(Obj_006107E0, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_006107E0, unknown_114) == 0x114);
GG_STATIC_ASSERT(offsetof(Obj_006107E0, unknown_11C) == 0x11C);
// FUNCTION: GAMEMD 0x623310 (__fastcall)
void FUN_00623310(GG_HWND hDlg, long lParam);
struct TextNode_00623420
{
    TextNode_00623420* Next;      // +0x00
    int                unknown_04;  // +0x04
    wchar_t*           Text;      // +0x08
    int                unknown_0C;  // +0x0C
    wchar_t            Buffer[1]; // +0x10
};
GG_STATIC_ASSERT(offsetof(TextNode_00623420, Text) == 0x08);
GG_STATIC_ASSERT(offsetof(TextNode_00623420, Buffer) == 0x10);

class BitFont;
struct Obj_00623420
{
    char               unknown_00[0x28];  // +0x0000
    wchar_t*           Text;              // +0x0028
    char               unknown_2C[0x34 - 0x2C];
    TextNode_00623420* TextList;          // +0x0034
    char               unknown_38[0x3C - 0x38];
    Obj_007B66D0*      unknown_3C;        // +0x003C
    int                unknown_40;        // +0x0040
    char               unknown_44[0x5C - 0x44];
    int                unknown_5C;        // +0x005C
    char               unknown_60[0x64 - 0x60];
    BitFont*           unknown_64;        // +0x0064, ctor623340 copies font89C4D0
    int                unknown_68;        // +0x0068
    char               unknown_6C[0x90 - 0x6C];
    int                unknown_90;        // +0x0090
    char               unknown_94[0x200 - 0x94];

    // FUNCTION: GAMEMD 0x623340 (__thiscall)
    Obj_00623420();
    // FUNCTION: GAMEMD 0x6233A0 (__thiscall)
    ~Obj_00623420();
    // FUNCTION: GAMEMD 0x623420 (__thiscall)
    void FUN_00623420(int nChars);
    // FUNCTION: GAMEMD 0x623460 (__thiscall)
    void FUN_00623460(TextNode_00623420* pNode);
    // FUNCTION: GAMEMD 0x6234B0 (__thiscall)
    void FUN_006234B0(const TextNode_00623420* pSource);
    // FUNCTION: GAMEMD 0x623560 (__thiscall)
    void FUN_00623560(const wchar_t* pszText);
    // FUNCTION: GAMEMD 0x6235B0 (__thiscall)
    void FUN_006235B0(const char* pszText);
    // FUNCTION: GAMEMD 0x623610 (__thiscall)
    Obj_00623420* FUN_00623610(const Obj_00623420& other);
    // FUNCTION: GAMEMD 0x623730 (__thiscall)
    Obj_00623420* FUN_00623730(const Obj_00623420& other);

    // Out-of-line bodies above share these expansions.
    inline void Inline_Unlink(TextNode_00623420* pNode);
    inline void Inline_SetText(const wchar_t* pszText);
    inline void Inline_AddCopy(const TextNode_00623420* pSource);
};
GG_STATIC_ASSERT(offsetof(Obj_00623420, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(Obj_00623420, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(Obj_00623420, unknown_5C) == 0x5C);
GG_STATIC_ASSERT(offsetof(Obj_00623420, unknown_64) == 0x64);
GG_STATIC_ASSERT(offsetof(Obj_00623420, unknown_68) == 0x68);
GG_STATIC_ASSERT(offsetof(Obj_00623420, unknown_90) == 0x90);
GG_STATIC_ASSERT(sizeof(Obj_00623420) == 0x200);
GG_STATIC_ASSERT(offsetof(Obj_00623420, Text) == 0x28);
GG_STATIC_ASSERT(offsetof(Obj_00623420, TextList) == 0x34);
// FUNCTION: GAMEMD 0x623E00 (__fastcall)
int FUN_00623E00(GG_HWND hList);
// FUNCTION: GAMEMD 0x623E40 (__fastcall)
int FUN_00623E40(GG_HWND hWnd, Wstring* pOut);
// FUNCTION: GAMEMD 0x623EA0 (__fastcall)
int FUN_00623EA0(GG_HWND hWnd, Obj_007B66D0* pOut);
// FUNCTION: GAMEMD 0x623F00 (__fastcall)
int FUN_00623F00(GG_HWND hWnd, int nIndex, Wstring* pOut);
// FUNCTION: GAMEMD 0x623F60 (__fastcall)
int FUN_00623F60(GG_HWND hWnd, int nIndex, Obj_007B66D0* pOut);
// FUNCTION: GAMEMD 0x623FC0 (__fastcall)
int FUN_00623FC0(GG_HWND hWnd, int nIndex, Wstring* pOut);
// FUNCTION: GAMEMD 0x624020 (__fastcall)
int FUN_00624020(GG_HWND hWnd, int nIndex, Obj_007B66D0* pOut);
// FUNCTION: GAMEMD 0x6240A0 (__stdcall)
void __stdcall FUN_006240A0(int nKey, int unused);
struct Entry_006244E0
{
    int            unknown_00;  // +0x00
    Obj_007B66D0   unknown_04;  // +0x04
    Obj_007B66D0   unknown_08;  // +0x08
    int            unknown_0C;  // +0x0C
    int            unknown_10;  // +0x10
    int            unknown_14;  // +0x14
};
GG_STATIC_ASSERT(offsetof(Entry_006244E0, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(Entry_006244E0, unknown_08) == 0x08);
GG_STATIC_ASSERT(sizeof(Entry_006244E0) == 0x18);

struct Obj_006244E0
{
    int              Count;       // +0x00
    int              unknown_04;  // +0x04
    Entry_006244E0*  Entries;     // +0x08

    // FUNCTION: GAMEMD 0x6244E0 (__thiscall)
    void FUN_006244E0();
};
GG_STATIC_ASSERT(offsetof(Obj_006244E0, Entries) == 0x08);
// Element type of the pointer vector held by Obj_00626250; its out-of-line
// destructor is at 0x68C8D0.
struct Obj_0068C8D0
{
    // FUNCTION: GAMEMD 0x68C8D0 (decl; reloc)
    ~Obj_0068C8D0();
};

struct Obj_00626250
{
    char                                Name[0x100];   // +0x0000
    DynamicVectorClass<Obj_0068C8D0*>*  unknown_100;   // +0x0100

    // FUNCTION: GAMEMD 0x626250 (__thiscall)
    Obj_00626250(const char* pszName, DynamicVectorClass<Obj_0068C8D0*>* pUnknown);
    // FUNCTION: GAMEMD 0x626290 (__thiscall)
    void FUN_00626290();
    // FUNCTION: GAMEMD 0x6262F0 (__thiscall)
    void FUN_006262F0(DynamicVectorClass<Obj_0068C8D0*>* pUnknown);
    // FUNCTION: GAMEMD 0x626370
    void FUN_00626370();
    // The release body shared by 0x626290 and 0x6262F0, expanded inline in both.
    inline void Inline_Release();
};
GG_STATIC_ASSERT(offsetof(Obj_00626250, unknown_100) == 0x100);
// FUNCTION: GAMEMD 0x626660 (__fastcall)
int FUN_00626660(const char* pszName);
// FUNCTION: GAMEMD 0x626FF0 (__fastcall)
void FUN_00626FF0();

// FUNCTION: GAMEMD 0x606800 (decl; reloc) -- the child-window enumeration callback.
int __stdcall FUN_00606800(GG_HWND hWnd, long lParam);

#endif  // GG_MATCH_UI_OWNRDRAW_H
