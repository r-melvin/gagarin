// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every displacement, constant and callee below was read off the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI at the address in each annotation.
//   Receivers that are not bound by RTTI keep a placeholder name derived from the
//   address.
//
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
// Small leaves between 0x6B0000 and 0x7C4000, worker s3 sweep. Ordered ascending by
// retail address.
#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"
#include "../platform/center_window_methods.h"
#include "../ui/input_controls/ui_gadget.h"

// ---------------------------------------------------------------------------
// 0x7518A0: fire an audio event for the table entry at an index.
struct AudioController_007518A0;
struct VocEntry_007518A0
{
    void* Event;   // +0x00
};
// GLOBAL: GAMEMD 0xB1D37C
extern "C" VocEntry_007518A0** DAT_00B1D37C;
// GLOBAL: GAMEMD 0xB1D388
extern "C" int DAT_00B1D388;
// FUNCTION: GAMEMD 0x4060F0 (decl; reloc)
void __fastcall FUN_004060F0(AudioController_007518A0* pThis, void* event, void* eventType);

// FUNCTION: GAMEMD 0x7518A0
// Plays the entry at `index` when it is inside the table.
void __fastcall FUN_007518A0(AudioController_007518A0* pThis, int index)
{
    if (index >= 0 && index < DAT_00B1D388) {
        FUN_004060F0(pThis, 0, DAT_00B1D37C[index]->Event);
    }
}

// ---------------------------------------------------------------------------
// 0x734F20: does the current table entry's name match a fixed string.
struct NameSlot_00734F20
{
    const char* Name;   // +0x00
    int unknown_04;
    int unknown_08;
    int unknown_0C;
};
GG_STATIC_ASSERT(sizeof(NameSlot_00734F20) == 0x10);
// GLOBAL: GAMEMD 0x845728
extern int Current_00845728;
// GLOBAL: GAMEMD 0x845684
extern NameSlot_00734F20 Slots_00845684[];
// GLOBAL: GAMEMD 0x8457BC
extern const char Match_008457BC[];
// LIBRARY: GAMEMD 0x7C8D20 -- _stricmp.
extern "C" int __cdecl _stricmp(const char* a, const char* b);

// FUNCTION: GAMEMD 0x734F20
// True when the current slot has no name or its name equals the fixed string.
int __cdecl FUN_00734F20()
{
    const char* name = Slots_00845684[Current_00845728].Name;
    if (name == 0) {
        return 1;
    }
    return _stricmp(name, Match_008457BC) == 0;
}

// ---------------------------------------------------------------------------
// 0x6CE570: look a name up in a twelve-entry string table.
// GLOBAL: GAMEMD 0x8425C0
extern const char* const Names_008425C0[12];

// FUNCTION: GAMEMD 0x6CE570
// Index of the table entry equal to `name` (case-insensitive), or -1.
int __fastcall FUN_006CE570(const char* name)
{
    for (int i = 0; i < 12; ++i) {
        if (_stricmp(Names_008425C0[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

// ---------------------------------------------------------------------------
// 0x777060: centre a window in its owner.
// FUNCTION: GAMEMD 0x777060
// Centres `window` inside its owner window when it has one.
void __fastcall FUN_00777060(HWND window)
{
    HWND owner = (HWND)GetWindowLongA(window, GWL_HWNDPARENT);
    if (owner) {
        Unsorted_CenterWindowIn(window, owner);
    }
}

// ---------------------------------------------------------------------------
// 0x72E820: run two helpers over the shared screen globals.
// GLOBAL: GAMEMD 0xB0FA04
extern int DAT_00B0FA04;
// GLOBAL: GAMEMD 0xB0FB50
extern int DAT_00B0FB50;
// GLOBAL: GAMEMD 0xB0FBCC
extern int DAT_00B0FBCC;
// FUNCTION: GAMEMD 0x72E450 (decl; reloc)
void __stdcall FUN_0072E450(int c);
// FUNCTION: GAMEMD 0x72E730 (decl; reloc)
void __fastcall FUN_0072E730(int a, int b, int x, int y, int z);

// FUNCTION: GAMEMD 0x72E820
// Runs the first helper on `c`, then the second with the three globals.
void __fastcall FUN_0072E820(int a, int b, int c)
{
    FUN_0072E450(c);
    FUN_0072E730(a, b, DAT_00B0FBCC, DAT_00B0FB50, DAT_00B0FA04);
}

// ---------------------------------------------------------------------------
// 0x7767B0: query a control for its child, tell the child to limit text, and
// remember the control and a value.
// GLOBAL: GAMEMD 0xB73080
extern int DAT_00B73080;
// GLOBAL: GAMEMD 0xB730A0
extern HWND DAT_00B730A0;

// FUNCTION: GAMEMD 0x7767B0
// Looks up the control's child (message 0x110F) and sends it 0xC5 with
// `length`; on success records `value` and the control globally.
void __fastcall FUN_007767B0(HWND control, int value, int length)
{
    HWND child = (HWND)SendMessageA(control, 0x110f, 0, 0);
    if (child) {
        SendMessageA(child, 0xc5, length, 0);
        DAT_00B73080 = value;
        DAT_00B730A0 = control;
    }
}

// ---------------------------------------------------------------------------
// 0x776880: show context help for a dialog's window.
struct Dialog_00776880
{
    int unknown_00;
    int unknown_04;
    int unknown_08;
    HWND Window;   // +0x0C
    void FUN_00776880();
};
GG_STATIC_ASSERT(offsetof(Dialog_00776880, Window) == 0xC);
// STRING: GAMEMD 0x849E2C
extern const char HelpFile_00849E2C[];

// FUNCTION: GAMEMD 0x776880
// Opens the help file at the window's context help id (HELP_CONTEXTPOPUP).
void Dialog_00776880::FUN_00776880()
{
    HWND window = Window;
    WinHelpA(window, HelpFile_00849E2C, HELP_CONTEXTPOPUP, GetWindowContextHelpId(window));
}

// ---------------------------------------------------------------------------
// 0x763690: index of a letter name; the inverse of FUN_00763610.
// LIBRARY: GAMEMD 0x007C990E
// isalpha
extern "C" int __cdecl isalpha(int ch);
// LIBRARY: GAMEMD 0x007C97D3
// _toupper
extern "C" int __cdecl toupper(int ch);

// FUNCTION: GAMEMD 0x763690
// "A".."Z" give 0..25, "AA" gives 26 and so on; -1 when the text does not start with a letter.
int __fastcall FUN_00763690(const char* name)
{
    int index = -1;
    if (isalpha(name[0])) {
        index = toupper(name[0]) - 'A';
        if (isalpha(name[1])) {
            return toupper(name[1]) + index * 26 - 39;
        }
    }
    return index;
}

// ---------------------------------------------------------------------------
// 0x727CF0: trim control characters and blanks from both ends of a string.
// FUNCTION: GAMEMD 0x727CF0
// Strips leading and trailing bytes up to 0x20 in place; null stays null.
char* __fastcall FUN_00727CF0(char* text)
{
    if (text) {
        char* start = text;
        while (*start && (unsigned char)*start <= 0x20) {
            start++;
        }
        if (start != text) {
            strcpy(text, start);
        }
        int last = strlen(text) - 1;
        while (last >= 0 && *start && (unsigned char)text[last] <= 0x20) {
            text[last] = 0;
            last--;
        }
    }
    return text;
}

// ---------------------------------------------------------------------------
// 0x71FFB0: default-construct a text button.
// FUNCTION: GAMEMD 0x71FFB0
// A zero-sized toggle with no text and print mode 2.
TextButtonClass::TextButtonClass() : ToggleClass(0, 0, 0, 0, 0)
{
    HasOutline = 0;
    Text = 0;
    unknown_3C = 2;
}

// ---------------------------------------------------------------------------
// 0x70FE50: stop draining power from another object.
struct House_0070FE50
{
    char unknown_0000[0x5778];
    unsigned char RecheckPower;   // +0x5778
};
GG_STATIC_ASSERT(offsetof(House_0070FE50, RecheckPower) == 0x5778);

struct Drained_0070FE50
{
    char unknown_000[0x1D0];
    void* DrainingMe;             // +0x1D0
    char unknown_1D4[0x21C - 0x1D4];
    House_0070FE50* Owner;        // +0x21C
};
GG_STATIC_ASSERT(offsetof(Drained_0070FE50, DrainingMe) == 0x1D0);
GG_STATIC_ASSERT(offsetof(Drained_0070FE50, Owner) == 0x21C);

struct DrainAnim_0070FE50
{
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual void Slot8();
    virtual void Slot9();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16();
    virtual void Slot17();
    virtual void Slot18();
    virtual void Slot19();
    virtual void Slot20();
    virtual void Slot21();
    virtual void Slot22();
    virtual void Slot23();
    virtual void Slot24();
    virtual void Slot25();
    virtual void Slot26();
    virtual void Slot27();
    virtual void Slot28();
    virtual void Slot29();
    virtual void Slot30();
    virtual void Slot31();
    virtual void Slot32();
    virtual void Slot33();
    virtual void Slot34();
    virtual void Slot35();
    virtual void Slot36();
    virtual void Slot37();
    virtual void Slot38();
    virtual void Slot39();
    virtual void Slot40();
    virtual void Slot41();
    virtual void Slot42();
    virtual void Slot43();
    virtual void Slot44();
    virtual void Slot45();
    virtual void Slot46();
    virtual void Slot47();
    virtual void Slot48();
    virtual void Slot49();
    virtual void Slot50();
    virtual void Slot51();
    virtual void Slot52();
    virtual void Slot53();
    virtual void Slot54();
    virtual void Slot55();
    virtual void Slot56();
    virtual void Slot57();
    virtual void Slot58();
    virtual void Slot59();
    virtual void Slot60();
    virtual void Slot61();
    virtual void Release();   // +0xF8
};

struct Techno_0070FE50
{
    char unknown_000[0x1CC];
    Drained_0070FE50* DrainTarget;   // +0x1CC
    void* DrainingMe;                // +0x1D0
    DrainAnim_0070FE50* DrainAnim;   // +0x1D4
    void FUN_0070FE50();
};
GG_STATIC_ASSERT(offsetof(Techno_0070FE50, DrainTarget) == 0x1CC);
GG_STATIC_ASSERT(offsetof(Techno_0070FE50, DrainAnim) == 0x1D4);

// FUNCTION: GAMEMD 0x70FE50
// Releases the drain animation and detaches from the drained object, asking
// its owner to recheck power.
void Techno_0070FE50::FUN_0070FE50()
{
    if (DrainAnim) {
        DrainAnim->Release();
        DrainAnim = 0;
    }
    if (DrainTarget) {
        DrainTarget->DrainingMe = 0;
        if (DrainTarget->Owner) {
            DrainTarget->Owner->RecheckPower = 1;
        }
        DrainTarget = 0;
    }
}

