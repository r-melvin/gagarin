// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. Small and medium bodies
//   from the 0x54E000-0x6ABD00 range; receivers are placeholder views of the members touched.
//
// Address index: 0x558860 0x5E70D0 0x631300 0x642BB0 0x660BE0 0x6A76F0 0x696590 0x696610 0x696740 0x696950 0x6966D0 0x6ABAD0 0x6ACBC0 0x6ACC20

#include <stddef.h>
#include <windows.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00558860
{
    char unknown_00[0x18];
    int result;     // +0x18
};
GG_STATIC_ASSERT(offsetof(Obj_00558860, result) == 0x18);

// FUNCTION: GAMEMD 0x558860
// Dialog item handler: record which button or list action ended the dialog.
void __fastcall FUN_00558860(HWND hWnd, int id, HWND hItem, int notify)
{
    Obj_00558860* o = (Obj_00558860*)GetWindowLongA(hWnd, 8);
    switch (id) {
    case 0x40F:
        if (notify == 0) {
            o->result = 0x40F;
        }
        break;
    case 0x525:
        if (notify == 2) {
            if (SendMessageA(hItem, 0x18B, 0, 0) > 0) {
                o->result = 0x40F;
                return;
            }
        }
        break;
    case 0x686:
        o->result = 2;
        return;
    }
}

// FUNCTION: GAMEMD 0x5E70D0
// Select the list entry in control 0x553 whose item data equals the given value.
unsigned int __fastcall FUN_005E70D0(HWND hDlg, int value)
{
    if (value == 0) {
        return 0xFFFFFFFF;
    }
    unsigned int index = 0;
    LRESULT count = SendDlgItemMessageA(hDlg, 0x553, 0x18B, 0, 0);
    unsigned int i = 0;
    if (count > 0) {
        do {
            if (SendDlgItemMessageA(hDlg, 0x553, 0x199, i, 0) == value) {
                index = i;
            }
            i++;
        } while ((int)i < count);
    }
    SendDlgItemMessageA(hDlg, 0x553, 0x186, index, 0);
    SendDlgItemMessageA(hDlg, 0x553, 0x197, index, 0);
    return index;
}

struct CellXY_00660BE0
{
    short X;
    short Y;
    bool operator==(const CellXY_00660BE0& o) const { return X == o.X && Y == o.Y; }
};

// GLOBAL: GAMEMD 0xB04D48
extern CellXY_00660BE0 DAT_00B04D48[8];
// GLOBAL: GAMEMD 0xB04D68
extern CellXY_00660BE0 DAT_00B04D68;
// GLOBAL: GAMEMD 0xB04D88
extern int DAT_00B04D88;
// GLOBAL: GAMEMD 0xB04DD8
extern int DAT_00B04DD8;

// FUNCTION: GAMEMD 0x660BE0
// Step back one entry in the 8-slot position history; return the entry now current.
CellXY_00660BE0* __fastcall FUN_00660BE0(CellXY_00660BE0* out)
{
    if (DAT_00B04D88 == -1) {
        *out = DAT_00B04D68;
        return out;
    }
    int i = DAT_00B04DD8 - 1;
    if (i < 0) {
        i += 8;
    }
    if (DAT_00B04D48[i] == DAT_00B04D68) {
        CellXY_00660BE0 v = DAT_00B04D48[DAT_00B04D88];
        DAT_00B04DD8 = DAT_00B04D88;
        *out = v;
        return out;
    }
    CellXY_00660BE0 v = DAT_00B04D48[i];
    DAT_00B04DD8 = i;
    *out = v;
    return out;
}

// The game session object: its first field is the game mode (3 and 4 are the skirmish-like modes).
struct Session_00642BB0
{
    int GameMode;       // +0x00
    char unknown_04[0x1C];
    // FUNCTION: GAMEMD 0x69A310 (decl; reloc)
    unsigned int FUN_0069A310(unsigned int index);
};
// GLOBAL: GAMEMD 0xA8B238
extern Session_00642BB0 DAT_00A8B238;

// A player slot: only the colour index at +0x6B is read here.
#pragma pack(push, 1)
struct Player_00642BB0
{
    char unknown_00[0x6B];
    int ColorIndex;     // +0x6B
    // FUNCTION: GAMEMD 0x696F20 (decl; reloc)
    int FUN_00696F20();
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(Player_00642BB0, ColorIndex) == 0x6B);

// GLOBAL: GAMEMD 0xA8DA78
extern Player_00642BB0** DAT_00A8DA78;
// GLOBAL: GAMEMD 0xB054D4
extern int* DAT_00B054D4;

// FUNCTION: GAMEMD 0x642BB0
// The packed colour for a player slot's chosen colour (random picks resolve through the session).
int __stdcall FUN_00642BB0(int slot)
{
    int result = 0;
    if ((DAT_00A8B238.GameMode == 3 || DAT_00A8B238.GameMode == 4) && DAT_00A8DA78[slot]->ColorIndex == -1) {
        unsigned int index = DAT_00A8B238.FUN_0069A310(0xFFFFFFFE);
        return DAT_00B054D4[index];
    }
    if (slot >= 0 && slot < 8) {
        unsigned int index = DAT_00A8B238.FUN_0069A310(DAT_00A8DA78[slot]->FUN_00696F20());
        result = DAT_00B054D4[index];
    }
    return result;
}

// One 0x60-byte sidebar strip slot; the animation setter takes a period, a phase and a parity flag.
struct StripSlot_006A76F0
{
    char unknown_00[0x60];
    // FUNCTION: GAMEMD 0x69DFC0 (decl; reloc)
    void FUN_0069DFC0(int period, int phase, bool parity);
};
GG_STATIC_ASSERT(sizeof(StripSlot_006A76F0) == 0x60);

// The tactical map object: only the redraw request at 0x4F42F0 is called.
struct Map_006A76F0
{
    // FUNCTION: GAMEMD 0x4F42F0 (decl; reloc)
    void FUN_004F42F0(int flag);
};

// GLOBAL: GAMEMD 0xB07C48
extern StripSlot_006A76F0 DAT_00B07C48[];
// GLOBAL: GAMEMD 0xA8ED84 -- the frame counter.
extern int DAT_00A8ED84;
// GLOBAL: GAMEMD 0x884B8F
extern unsigned char DAT_00884B8F;
// GLOBAL: GAMEMD 0x87F7E8
extern Map_006A76F0 DAT_0087F7E8;

// FUNCTION: GAMEMD 0x6A76F0
// Restart a strip slot's animation aligned to the next 10-frame boundary and request a redraw.
void __stdcall FUN_006A76F0(int slot)
{
    int remaining = 10 - DAT_00A8ED84 % 10;
    DAT_00B07C48[slot].FUN_0069DFC0(10, remaining, (DAT_00A8ED84 + remaining) / 10 % 2 == 0);
    DAT_00884B8F = 1;
    DAT_0087F7E8.FUN_004F42F0(0);
}

// One sidebar tab's strip: 0xF94 bytes, entered through 0x6ABB60.
struct Strip_006ABAD0
{
    char unknown_00[0xF94];
    // FUNCTION: GAMEMD 0x6ABB60 (decl; reloc)
    void FUN_006ABB60(unsigned int arg);
};
GG_STATIC_ASSERT(sizeof(Strip_006ABAD0) == 0xF94);

// FUNCTION: GAMEMD 0x5004E0 (decl; reloc)
int __fastcall FUN_005004E0(int a, int b);

struct SidebarView_006ABAD0
{
    char unknown_0000[0x1544];
    Strip_006ABAD0 Strips[4];       // +0x1544
    // FUNCTION: GAMEMD 0x6ABAD0
    void FUN_006ABAD0(int kind, int arg, unsigned int param);
};
GG_STATIC_ASSERT(offsetof(SidebarView_006ABAD0, Strips) == 0x1544);

// FUNCTION: GAMEMD 0x6ABAD0
// Route an object kind to its sidebar strip (-1 when it has none) and hand the strip the request.
void SidebarView_006ABAD0::FUN_006ABAD0(int kind, int arg, unsigned int param)
{
    int strip;
    if (kind == 0xF || kind == 0x10) {
        strip = 2;
    } else if (kind == 1 || kind == 0x28 || kind == 2 || kind == 3) {
        strip = 3;
    } else if (kind == 6 || kind == 7) {
        strip = FUN_005004E0(kind, arg) == 5;
    } else if (kind == 0x39 || kind == 0x20 || kind == 0x1F) {
        strip = 1;
    } else {
        strip = -1;
    }
    Strips[strip].FUN_006ABB60(param);
}

// FUNCTION: GAMEMD 0x6ACBC0
// Map a skirmish dialog control id to its slot index (-1 when the id is not one of the seven).
int __fastcall FUN_006ACBC0(int id)
{
    if (id == 0x50B) {
        return 0;
    }
    if (id == 0x50E) {
        return 1;
    }
    if (id == 0x516) {
        return 2;
    }
    if (id == 0x51A) {
        return 3;
    }
    if (id == 0x51B) {
        return 4;
    }
    if (id == 0x51C) {
        return 5;
    }
    return id == 0x51D ? 6 : -1;
}

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- resolve a label to its localised text (label, 0, file, line).
const wchar_t* FUN_00734E60(const char* label, int flags, const char* file, int line);

// FUNCTION: GAMEMD 0x6ACC20
// The localised name of a computer-player difficulty (-1 none, 0 genius, 1 smart, 2 dumb).
const wchar_t* __fastcall FUN_006ACC20(int difficulty)
{
    if (difficulty == -1) {
        return FUN_00734E60("STT:PlayerNone", 0, "D:\\ra2mdpost\\Skirmish.cpp", 0x87);
    }
    if (difficulty == 2) {
        return FUN_00734E60("STT:PlayerDumbAI", 0, "D:\\ra2mdpost\\Skirmish.cpp", 0x89);
    }
    if (difficulty == 1) {
        return FUN_00734E60("STT:PlayerSmartAI", 0, "D:\\ra2mdpost\\Skirmish.cpp", 0x8B);
    }
    if (difficulty == 0) {
        return FUN_00734E60("STT:PlayerGeniusAI", 0, "D:\\ra2mdpost\\Skirmish.cpp", 0x8D);
    }
    return 0;
}

// A dialog window object: the window handle is first, and a mode selector sits at +0x94.
struct Dlg_006966D0
{
    HWND Window;            // +0x00
    char unknown_04[4];
    char Text[16];          // +0x08 the entered text (a name, optionally with a '-' suffix part)
    char unknown_18[0x7C];
    int Mode;               // +0x94
    int unknown_98;
    int Selection;          // +0x9C
    // FUNCTION: GAMEMD 0x696590
    void FUN_00696590();
    // FUNCTION: GAMEMD 0x696610
    void FUN_00696610();
    // FUNCTION: GAMEMD 0x6966D0
    void FUN_006966D0();
    // FUNCTION: GAMEMD 0x696740
    void FUN_00696740(int id);
    // FUNCTION: GAMEMD 0x696950
    void FUN_00696950();
    // FUNCTION: GAMEMD 0x6969C0 (decl; reloc)
    void FUN_006969C0(int id, int a, char* text);
};
GG_STATIC_ASSERT(offsetof(Dlg_006966D0, Text) == 0x08);
GG_STATIC_ASSERT(offsetof(Dlg_006966D0, Mode) == 0x94);
GG_STATIC_ASSERT(offsetof(Dlg_006966D0, Selection) == 0x9C);

// FUNCTION: GAMEMD 0x7CAF30 (decl; reloc) -- find a character in a string (C runtime).
extern "C" char* __cdecl FUN_007CAF30(char* s, int c);
// FUNCTION: GAMEMD 0x7DCFC4 (decl; reloc)
extern "C" void __cdecl FUN_007DCFC4(char* s);
// FUNCTION: GAMEMD 0x727CF0 (decl; reloc) -- normalise a text field in place.
struct TextField_00727CF0
{
    void FUN_00727CF0();
};
// FUNCTION: GAMEMD 0x776E10 (decl; reloc) -- find the list entry whose data matches (window in ECX, -1 in EDX).
int __fastcall FUN_00776E10(HWND list, int start, int data);
// GLOBAL: GAMEMD 0xA8DB68 -- the four entries offered by the list.
extern int* DAT_00A8DB68;
// GLOBAL: GAMEMD 0x889F64 -- the empty string.
extern char DAT_00889F64[];

// GLOBAL: GAMEMD 0xA8DB50 -- the item data of the entries the list offers.
extern int* DAT_00A8DB50;
// GLOBAL: GAMEMD 0xA8DB5C -- how many entries.
extern int DAT_00A8DB5C;

// FUNCTION: GAMEMD 0x696610
// Refill the list control (id 0x65E) from the global entries, then keep the remembered
// selection when it is still in range and otherwise reset it.
void Dlg_006966D0::FUN_00696610()
{
    HWND list = GetDlgItem(Window, 0x65E);
    if (list) {
        SendMessageA(list, 0x184, 0, 0);
        for (int i = 0; i < DAT_00A8DB5C; i++) {
            SendMessageA(list, 0x4C8, 0, DAT_00A8DB50[i]);
        }
        if (SendMessageA(list, 0x18B, 0, 0) == 0 || unknown_98 < -1) {
            unknown_98 = -1;
        } else if (unknown_98 >= SendMessageA(list, 0x18B, 0, 0)) {
            unknown_98 = 0;
        }
        if (unknown_98 != -1) {
            SendMessageA(list, 0x186, unknown_98, 0);
        }
    }
}

// FUNCTION: GAMEMD 0x6966D0
// Set the two radio buttons (0x65C, 0x65B) from the mode selector: 0 selects the first, anything else the second.
void Dlg_006966D0::FUN_006966D0()
{
    bool first = Mode == 0;
    HWND button = GetDlgItem(Window, 0x65C);
    if (button) {
        SendMessageA(button, 0xF1, first == 1, 0);
    }
    button = GetDlgItem(Window, 0x65B);
    if (button) {
        SendMessageA(button, 0xF1, !first, 0);
    }
}

// Dialog window object: only the window handle (+0x00) is read.
struct Dlg_00631300
{
    HWND Window;    // +0x00
    char unknown_04[4];
    bool Changed;   // +0x08
    // FUNCTION: GAMEMD 0x631300
    void FUN_00631300();
    // FUNCTION: GAMEMD 0x631060 (decl; reloc) -- fill the controls.
    void FUN_00631060();
    // FUNCTION: GAMEMD 0x631640
    void FUN_00631640();
};
GG_STATIC_ASSERT(offsetof(Dlg_00631300, Changed) == 0x8);

// GLOBAL: GAMEMD 0xA8DABC -- the list index the user picked.
extern int DAT_00A8DABC;
// GLOBAL: GAMEMD 0xA8DB38 -- the table of entries behind the list (a text field sits at +0x9A of each).
struct Entry_00631300
{
    char unknown_00[0x9A];
    char Name[1];       // +0x9A
};
extern Entry_00631300** DAT_00A8DB38;
// GLOBAL: GAMEMD 0xA8DB44 -- the number of entries in the table.
extern int DAT_00A8DB44;

// FUNCTION: GAMEMD 0x631300
// PARTIAL: 98.0%. One swapped base/index register pair in the table lookup; retail loads the table
// pointer first. Tried: local temporaries, pointer arithmetic order, int*/char*/struct element types.
// Remember the selected list entry, copy its text into the edit control and focus it.
void Dlg_00631300::FUN_00631300()
{
    HWND list = GetDlgItem(Window, 0x5E0);
    if (list) {
        if (SendMessageA(list, 0x18B, 0, 0) > 0) {
            DAT_00A8DABC = SendMessageA(list, 0x188, 0, 0);
            if (DAT_00A8DABC > -1) {
                HWND edit = GetDlgItem(Window, 0x5E5);
                SendMessageA(edit, 0x4B4, 0, (LPARAM)DAT_00A8DB38[DAT_00A8DABC]->Name);
                SetFocus(edit);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x696740
// Show and enable a text control, filling it with the part of the entered text after the '-'.
void Dlg_006966D0::FUN_00696740(int id)
{
    HWND control = GetDlgItem(Window, id);
    if (control) {
        ShowWindow(control, 5);
        EnableWindow(control, 1);
        char* suffix = FUN_007CAF30(Text, '-');
        if (suffix) {
            suffix++;
            ((TextField_00727CF0*)suffix)->FUN_00727CF0();
        } else {
            suffix = DAT_00889F64;
        }
        SendMessageA(control, 0x4B4, 0, (LPARAM)suffix);
        SetFocus(control);
    }
}

// FUNCTION: GAMEMD 0x696950
// Hide and disable the text control, read its text back into the entered text and refresh the list.
void Dlg_006966D0::FUN_00696950()
{
    HWND control = GetDlgItem(Window, 0x65A);
    if (control) {
        ShowWindow(control, 0);
        EnableWindow(control, 0);
        char* text = Text;
        SendMessageA(control, 0x4B5, 0x10, (LPARAM)text);
        Text[15] = 0;
        ((TextField_00727CF0*)text)->FUN_00727CF0();
        FUN_007DCFC4(text);
        FUN_006969C0(0x659, 3, text);
    }
}

// FUNCTION: GAMEMD 0x696590
// PARTIAL: 87.8%. Same instructions; retail loads the stack argument into EDX before setting EDX to -1.
// Tried: local temporary, unsigned -1 literal.
// Fill the four-entry list control and select the entry that matches the current selection.
void Dlg_006966D0::FUN_00696590()
{
    HWND list = GetDlgItem(Window, 0x659);
    if (list) {
        SendMessageA(list, 0x14B, 0, 0);
        int i = 0;
        do {
            WPARAM added = SendMessageA(list, 0x4C2, 0, DAT_00A8DB68[i]);
            SendMessageA(list, 0x151, added, i);
            i++;
        } while (i < 4);
        WPARAM found = FUN_00776E10(list, 0xFFFFFFFF, Selection);
        SendMessageA(list, 0x14E, found, 0);
    }
}

// FUNCTION: GAMEMD 0x631640
// Remove the selected list entry from the table, mark the dialog changed and refill
// the controls; when nothing is selected afterwards, blank the text box.
void Dlg_00631300::FUN_00631640()
{
    HWND list = GetDlgItem(Window, 0x5E0);
    if (list) {
        DAT_00A8DABC = SendMessageA(list, 0x188, 0, 0);
        if (DAT_00A8DABC > -1) {
            int i = DAT_00A8DABC;
            if (i < DAT_00A8DB44) {
                DAT_00A8DB44--;
                while (i < DAT_00A8DB44) {
                    i++;
                    DAT_00A8DB38[i - 1] = DAT_00A8DB38[i];
                }
            }
            Changed = true;
            FUN_00631060();
            if (DAT_00A8DABC == -1) {
                HWND edit = GetDlgItem(Window, 0x5E5);
                if (edit) {
                    SendMessageA(edit, 0x4B4, 0, (LPARAM)DAT_00889F64);
                }
            }
        }
    }
}
