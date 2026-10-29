// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit CampScor.cpp. The name is the source-file string at 0x81b304
//   in retail gamemd.exe v1.001, passed by the assert at 0x46d3da inside this object's
//   code range (0x46d120-0x47153f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// STRING: GAMEMD 0x81B2EC  "TXT_TIME_FORMAT_HOURS"
//
// Campaign score classes: constructors, empty destructors and the compiler-emitted
// scalar deleting destructors (0x471500, 0x471520).

#include "../core/house_index_lookup_methods.h"
#include "../_layout/session_class.h"
#include "../core/mathtbl_init_shapes.h"

#include "../core/small_misc5_methods.h"

#include "../core/small_misc7_methods.h"

#include "../core/trivial_tu043_methods.h"

#include "dialog_enable_methods.h"

#include "format_duration_methods.h"

// VTABLE: GAMEMD 0x7E4AAC
// Campaign score screen state (retail slot 1 is 0x46FC00, not matched).
class CampaignScoreClass
{
public:
    CampaignScoreClass();                 // 0x46D330
    virtual ~CampaignScoreClass();        // 0x46D350 body, 0x471500 scalar deleting
    virtual void Slot1();                 // 0x46FC00

    int Unknown04;                        // +0x04
};
GG_STATIC_ASSERT(offsetof(CampaignScoreClass, Unknown04) == 0x04);

// VTABLE: GAMEMD 0x7E4AB8
// Campaign end score screen state (retail slot 1 is 0x471420, not matched).
class CampaignEndScoreClass
{
public:
    CampaignEndScoreClass();              // 0x470C00
    virtual ~CampaignEndScoreClass();     // 0x470C30 body, 0x471520 scalar deleting
    virtual void Slot1();                 // 0x471420
};

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include <stdlib.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E4A98
extern const double DAT_007E4A98;
// GLOBAL: GAMEMD 0x89DFA8
extern double DAT_0089DFA8;

// SYNTHETIC: GAMEMD 0x0046D150
// dynamic initializer for DAT_0089E040
// GLOBAL: GAMEMD 0x0089E040
double DAT_0089E040 = DAT_0089DFA8 / DAT_007E4A98;

// SYNTHETIC: GAMEMD 0x0046D170
// dynamic initializer for DAT_0089E018
// GLOBAL: GAMEMD 0x0089E018
double DAT_0089E018 = 1.0 / DAT_0089E040;

GG_STATIC_ASSERT(sizeof(DAT_0089E040) == 8);
GG_STATIC_ASSERT(sizeof(DAT_0089E018) == 8);

// SYNTHETIC: GAMEMD 0x0046D2F0
// GLOBAL: GAMEMD 0x0089E028
MathTblCoord DAT_0089E028;

// FUNCTION: GAMEMD 0x46D330
CampaignScoreClass::CampaignScoreClass()
{
    Unknown04 = 0;

    DAT_0089E050 = 0;
    DAT_0081B1E8 = -1;
}

// FUNCTION: GAMEMD 0x46D350
// Empty destructor (stores only the vtable).
CampaignScoreClass::~CampaignScoreClass()
{
}

// SYNTHETIC: GAMEMD 0x471500 -- CampaignScoreClass::`scalar deleting destructor'

// FUNCTION: GAMEMD 0x46D360
//
// Format a duration in seconds as hours, minutes and seconds into the caller's
// buffer, capped at 99:59:59.
//
// The hour count is computed twice — once to test the cap and again after it —
// rather than being clamped in place. Retail emits both divisions (0x46D373 and
// 0x46D390), so the source tests `seconds / 3600` and then recomputes it.
void FUN_0046D360(gg_wchar* buffer, int seconds)
{
    if (buffer == 0) {
        return;
    }

    if (seconds / 3600 > 99) {
        seconds = 359999;
    }

    int hours = seconds / 3600;
    seconds -= hours * 3600;

    int minutes = seconds / 60;
    seconds -= minutes * 60;

    FUN_007CA564(buffer,
                 FUN_00734E60("TXT_TIME_FORMAT_HOURS", 0, DAT_0081B304, 0xA9),
                 hours, minutes, seconds);
}

// FUNCTION: GAMEMD 0x46D480
// Stores its argument in a member.
void FUN_0046D480(Obj_0046D480* a1, int a2)
{
    a1->unknown_89E000 = a2;
}

// FUNCTION: GAMEMD 0x46D490
// Member getter (byte).
unsigned char Obj_0046D490::FUN_0046D490() const
{
    return unknown_89E000;
}

struct Entry_0046DC50
{
    char unknown_00[0x60];
    int unknown_60;           // +0x60  the score the table is ordered by
    char unknown_64[0x0C];
};
GG_STATIC_ASSERT(offsetof(Entry_0046DC50, unknown_60) == 0x60);
GG_STATIC_ASSERT(sizeof(Entry_0046DC50) == 0x70);

// Score ordering comparator for qsort (defined after its user).
int __cdecl FUN_0046DC90(const void* a, const void* b);

// GLOBAL: GAMEMD 0xA8D1FC
extern Entry_0046DC50 DAT_00A8D1FC[];
// GLOBAL: GAMEMD 0x89DF80
extern Entry_0046DC50* DAT_0089DF80[];

// FUNCTION: GAMEMD 0x46DC50
//
// Point the sort table at the filled score entries and order them.
void __cdecl FUN_0046DC50()
{
    int count = DAT_00A8D580;
    for (int i = 0; i < count; i++) {
        DAT_0089DF80[i] = &DAT_00A8D1FC[i];
    }
    if (count > 1) {
        qsort(DAT_0089DF80, count, sizeof(Entry_0046DC50*), FUN_0046DC90);
    }
}

// FUNCTION: GAMEMD 0x46DC90
//
// qsort comparison: higher score first.
int __cdecl FUN_0046DC90(const void* a, const void* b)
{
    const Entry_0046DC50* first = *(Entry_0046DC50* const*)a;
    const Entry_0046DC50* second = *(Entry_0046DC50* const*)b;
    if (first->unknown_60 == second->unknown_60) {
        return 0;
    }
    return first->unknown_60 > second->unknown_60 ? -1 : 1;
}

// FUNCTION: GAMEMD 0x46F810
//
// Each of the four rejections gets its own `POP EDI; MOV EAX,-2; POP ESI; RET`
// in retail - four separate epilogues, so four separate `return -2` statements
// rather than one `||` chain, which would share a tail.
int FUN_0046F810(int index)
{
    Entry_0046F810* entry = DAT_00A8DA90[index];

    if (entry->FUN_005E9440()) {
        return DAT_00A8B2BC[index];
    }

    if (entry == DAT_00AC119C) {
        return -2;
    }

    if (entry == DAT_00AC11A0) {
        return -2;
    }

    if (entry == DAT_00AC11B0) {
        return -2;
    }

    if (entry == DAT_00AC11B4) {
        return -2;
    }

    return entry->FUN_00696F20();
}

// FUNCTION: GAMEMD 0x46F880
//
// The same lookup against the second parallel table. Written out rather than
// shared.
int FUN_0046F880(int index)
{
    Entry_0046F810* entry = DAT_00A8DA90[index];

    if (entry->FUN_005E9440()) {
        return DAT_00A8B2DC[index];
    }

    if (entry == DAT_00AC119C) {
        return -2;
    }

    if (entry == DAT_00AC11A0) {
        return -2;
    }

    if (entry == DAT_00AC11B0) {
        return -2;
    }

    if (entry == DAT_00AC11B4) {
        return -2;
    }

    return entry->FUN_00696F50();
}

// FUNCTION: GAMEMD 0x46FB50
//
// Enable or disable two dialog controls according to how full the list is.
// Below capacity, the first control is disabled and the second enabled; at
// capacity, only the first is touched and its state comes from the current
// slot's own flag.
//
// Both controls are fetched before either is tested, so the second lookup
// happens even on the path that never uses it.
void FUN_0046FB50(HWND_ dlg)
{
    HWND_ first = GetDlgItem(dlg, 0x6D1);
    HWND_ second = GetDlgItem(dlg, 0x5C0);

    if (first == 0) {
        return;
    }

    if (DAT_00A8DA84 < DAT_00A8D580) {
        EnableWindow(first, 0);
        if (second == 0) {
            return;
        }
        EnableWindow(second, 1);
        return;
    }

    if (DAT_0089E000[DAT_00A8DA8C]) {
        EnableWindow(first, 0);
        return;
    }

    EnableWindow(first, 1);
}


struct Obj_0046FBD0;


// FUNCTION: GAMEMD 0x48D080 (decl; reloc)
void FUN_0048D080(Obj_0046FBD0*, int);
// FUNCTION: GAMEMD 0x5DAF20 (decl; reloc)
bool FUN_005DAF20(Obj_0046FBD0*, int);
// FUNCTION: GAMEMD 0x77F900 (decl; reloc)
bool FUN_0077F900(Obj_0046FBD0*, int);

struct Obj_0046FBD0
{
};


// FUNCTION: GAMEMD 0x46FBD0
unsigned char FUN_0046FBD0(Obj_0046FBD0* a1, int a2);

// FUNCTION: GAMEMD 0x46FBD0
// Branching.
unsigned char FUN_0046FBD0(Obj_0046FBD0* a1, int a2)
{
    if (Session_00A8B238.GameMode == 3)
    {
        return FUN_005DAF20(a1, a2);
    }
    if (Session_00A8B238.GameMode == 4)
    {
        return FUN_0077F900(a1, a2);
    }
    FUN_0048D080(a1, a2);
    return 0;
}

// FUNCTION: GAMEMD 0x470C00
CampaignEndScoreClass::CampaignEndScoreClass()
{
    DAT_0089E008 = -1;
    DAT_0089E020 = 0;
    DAT_0089DFD4 = 0;
}

// FUNCTION: GAMEMD 0x470C30
// Empty destructor (stores only the vtable).
CampaignEndScoreClass::~CampaignEndScoreClass()
{
}

// SYNTHETIC: GAMEMD 0x471520 -- CampaignEndScoreClass::`scalar deleting destructor'

// IAT 0x7E14A4: USER32!SendMessageA.
extern "C" __declspec(dllimport) long __stdcall SendMessageA(HWND_ hWnd, unsigned uMsg, unsigned wParam, long lParam);
// 0x7CA564: the CRT swprintf (cdecl, varargs).
extern "C" int __cdecl swprintf(wchar_t* pszBuffer, const wchar_t* pszFormat, ...);

// Formats a number as text and posts it to a dialog control (custom message 0x4B2).
// FUNCTION: GAMEMD 0x00470C40
void FUN_00470C40(HWND_ dialog, int controlId, int value)
{
    wchar_t text[32];
    swprintf(text, L"%d", value);
    HWND_ item = GetDlgItem(dialog, controlId);
    SendMessageA(item, 0x4B2, 0, (long)text);
}

// FUNCTION: GAMEMD 0x470C90
//
// A second copy of the same formatter. The two differ in exactly one constant:
// the line number handed to the label lookup, 0x6EA here against 0xA9 at
// 0x46D360. Same file path in both, so this is the same helper written out twice
// in one source file, at lines 169 and 1770 — which is itself the evidence that
// it was duplicated by hand rather than shared. Written out longhand rather than
// shared: the family rule in the methodology exists because look-alike siblings
// have been caught diverging, and confirming these two are identical is a check,
// not an assumption.
void FUN_00470C90(gg_wchar* buffer, int seconds)
{
    if (buffer == 0) {
        return;
    }

    if (seconds / 3600 > 99) {
        seconds = 359999;
    }

    int hours = seconds / 3600;
    seconds -= hours * 3600;

    int minutes = seconds / 60;
    seconds -= minutes * 60;

    FUN_007CA564(buffer,
                 FUN_00734E60("TXT_TIME_FORMAT_HOURS", 0, DAT_0081B304, 0x6EA),
                 hours, minutes, seconds);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x471400
// Branching.
void __cdecl FUN_00471400()
{
    if (DAT_0089E020 > 1)
    {
        FUN_007C8B48(DAT_0089DFE0, DAT_0089E020, 4, 0x46DC90);
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x89DFD4
int DAT_0089DFD4;
// GLOBAL: GAMEMD 0x89E008
int DAT_0089E008;
// GLOBAL: GAMEMD 0x89E020
int DAT_0089E020;
// GLOBAL: GAMEMD 0x89E050
int DAT_0089E050;
// GLOBAL: GAMEMD 0xA8D580
int DAT_00A8D580;
// GLOBAL: GAMEMD 0x81B1E8
int DAT_0081B1E8 = -1;
// GLOBAL: GAMEMD 0x7E4A98
extern const double DAT_007E4A98 = 60.0;
// END defined globals
