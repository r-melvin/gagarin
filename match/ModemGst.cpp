// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | private-ref-cross-check
//   Original translation unit ModemGst.cpp. The name is the source-file string at 0x82c534
//   in retail gamemd.exe v1.001, passed by the assert at 0x5b4f73 inside this object's
//   code range (0x5b47c0-0x5b75ef). Functions are in ascending retail address order.

#include "wol_scenario_color_methods.h"
#include "wol_request_queue.h"
#include "netshare_common.h"
#include <string.h>
#include "house_type_class_find_methods.h"
#include "message_list_class_manage_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "shared_constants_globals.h"
#include "scenario_session_globals.h"
#include "_layout/node_name_type.h"
#include "scenario_class_methods.h"
#include "vector_class.h"
#include "vector_class_operations.h"
#include "vector_add_item_free.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EDF58
extern const double DAT_007EDF58;
// GLOBAL: GAMEMD 0xABF030
extern double DAT_00ABF030;
// GLOBAL: GAMEMD 0xABF068
extern double DAT_00ABF068;
// GLOBAL: GAMEMD 0xABF070
extern int DAT_00ABF070;
// GLOBAL: GAMEMD 0xABF074
extern int DAT_00ABF074;
// GLOBAL: GAMEMD 0xABF078
extern int DAT_00ABF078;
// GLOBAL: GAMEMD 0xABF080
extern double DAT_00ABF080;

// FUNCTION: GAMEMD 0x727D60 (decl; reloc) -- __fastcall, the wide text buffer in ECX.
void __fastcall FUN_00727D60(unsigned short* text);
// FUNCTION: GAMEMD 0x5E2820 (decl; reloc) -- appends a coloured line to a text control.
void FUN_005E2820(int color, const wchar_t* text, HWND_ window);
// FUNCTION: GAMEMD 0x735120 (decl; reloc)
const wchar_t* FUN_00735120(const char* text);
struct Obj_005B6DA0 {
    HWND_ unknown_00;
    void FUN_005B6DA0(const wchar_t* text);
};


// GLOBAL: GAMEMD 0xA8B3AC -- the value the list control at 0x667 hands back for its selection.
extern int DAT_00A8B3AC;

// FUNCTION: GAMEMD 0x735090 (decl; reloc) -- __fastcall, narrow output in ECX, wide input in EDX.
void __fastcall FUN_00735090(char* output, const unsigned short* input, int maximum);
// GLOBAL: GAMEMD 0xA8B380 -- the local player's handle, ANSI.
extern char DAT_00A8B380[];
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- the debug log printf.
extern "C" int __cdecl FUN_004068E0(const char* format, ...);

// FUNCTION: GAMEMD 0x5B56F0
//
// Read the dialog back into the globals: the handle from the edit control 0x5C1 (a 20-character
// buffer filled by a private message), the colour from combo 0x405 and the list value from 0x667.
// Each step is logged.
void WolScenarioColorDlgClass::FUN_005B56F0()
{
    FUN_004068E0("ModemGuest.ReadDialog(enter)\n");
    HWND_ control = GetDlgItem(this->Dialog, 0x5C1);
    if (control != 0) {
        unsigned short text[20];
        SendMessageA(control, 0x4B3, 0x14, (long)text);
        FUN_00735090(DAT_00A8B380, text, -1);
    }
    FUN_004068E0("Name: %s\n", DAT_00A8B380);
    control = GetDlgItem(this->Dialog, 0x405);
    if (control != 0) {
        PlayerColor = SendMessageA(control, GG_CB_GETCURSEL, 0, 0);
    }
    FUN_004068E0("Color: %d\n", PlayerColor);
    control = GetDlgItem(this->Dialog, 0x667);
    if (control != 0) {
        unsigned int selection = SendMessageA(control, GG_CB_GETCURSEL, 0, 0);
        DAT_00A8B3AC = SendMessageA(control, GG_CB_GETITEMDATA, selection, 0);
    }
    FUN_004068E0("ModemGuest.ReadDialog(exit)\n");
}

// FUNCTION: GAMEMD 0x5B5960
//
// The list at control 0x667 changed: take the data value of its selected row and publish it,
// marking the dialog dirty. No control, or no selection, changes nothing.
void WolScenarioColorDlgClass::FUN_005B5960()
{
    HWND_ control = GetDlgItem(this->Dialog, 0x667);
    if (control != 0) {
        unsigned int selection = SendMessageA(control, GG_CB_GETCURSEL, 0, 0);
        if (selection != 0xFFFFFFFF) {
            DAT_00A8B3AC = SendMessageA(control, GG_CB_GETITEMDATA, selection, 0);
            this->OptionsChanged = true;
            this->unknown_08 = true;
        }
    }
}

extern "C" __declspec(dllimport) int __stdcall EnableWindow(HWND_ window, int enable);

// FUNCTION: GAMEMD 0x5B5E90
//
// Grey out the dialog's default button (control 1) and queue a request with code 0x74.
void WolScenarioColorDlgClass::FUN_005B5E90()
{
    HWND_ button = GetDlgItem(this->Dialog, 1);
    if (button != 0) {
        EnableWindow(button, 0);
    }
    WolRequestBlock_005B5E90 block;
    memset(&block, 0, 0xFA);
    block.Code = 0x74;
    DAT_00A8EA70.FUN_005F1BF0(&block, 0xFA, 1);
}

// FUNCTION: GAMEMD 0x5B5A50
//
// Take the text of the edit control 0x5C1 (a 22-character buffer filled by a private message),
// run it through the 0x727D60 filter, write the filtered text back to the control unless the
// caller asked to leave it alone, and store it as the local player's handle. Marks the dialog dirty.
void WolScenarioColorDlgClass::FUN_005B5A50(char mode)
{
    HWND_ control = GetDlgItem(this->Dialog, 0x5C1);
    if (control != 0) {
        unsigned short text[22];
        SendMessageA(control, 0x4B3, 0x15, (long)text);
        FUN_00727D60(text);
        if (mode == 0) {
            SendMessageA(control, 0x4B2, 0, (long)text);
        }
        FUN_00735090(DAT_00A8B380, text, -1);
        this->OptionsChanged = true;
        this->unknown_08 = true;
    }
}

// FUNCTION: GAMEMD 0x5B59B0
//
// Reconcile the colour combo with the colour this slot already holds. If the
// selection still points at the slot's own colour it is advanced by one, wrapped
// past the last of the eight, and written back into the combo; otherwise the
// selection stands. Either way the resulting index is published and the combo is
// repainted in its colour, falling back to the default RGB when the index is out
// of range.
//
// EXACT (63/63 instructions, raw bytes identical apart from relocation slots).
// Flat early returns plus the repaint colour chosen into one local before a
// single SendMessage reproduce retail's register naming (receiver in EDI,
// control handle in EBX).
void WolScenarioColorDlgClass::FUN_005B59B0()
{
    HWND_ dialog = this->Dialog;
    HWND_ control = GetDlgItem(dialog, 0x405);
    if (control == 0) return;
    int selection = SendMessageA(control, GG_CB_GETCURSEL, 0, 0);
    if (selection == -1) return;
    if (selection == this->ColorIndex) {
        selection = this->ColorIndex + 1;
        if (selection > 7) selection = 0;
        SendMessageA(control, GG_CB_SETCURSEL, selection, 0);
    }
    PlayerColor = selection;
    this->OptionsChanged = true;
    this->unknown_08 = true;
    unsigned color = (selection >= 0 && selection < 8) ? DAT_008316A8[selection] : DefaultSchemeColor;
    SendMessageA(control, GG_CBM_SETCOLOR, 0, color);
}

// LIBRARY: GAMEMD 0x7CA489 (decl; reloc) -- CRT wcscpy, cdecl.
extern "C" wchar_t* __cdecl wcscpy(wchar_t* dst, const wchar_t* src);
// LIBRARY: GAMEMD 0x7CA564 (decl; reloc) -- CRT swprintf, cdecl.
extern "C" int __cdecl swprintf(wchar_t* buffer, const wchar_t* format, ...);

// FUNCTION: GAMEMD 0x5B5AD0
//
// Record a slot's handle, colour and index, then repaint its label. If the colour combo's
// selection is the colour just assigned, advance the selection first. The label (control 0x668)
// shows "handle [house name]" in the slot's colour.
void WolScenarioColorDlgClass::FUN_005B5AD0(const wchar_t* handle, int color, int slot)
{
    wcscpy(Handle, handle);
    ColorIndex = color;
    HWND_ combo = GetDlgItem(Dialog, 0x405);
    if (combo != 0) {
        int selection = SendMessageA(combo, GG_CB_GETCURSEL, 0, 0);
        if (selection != -1 && selection == ColorIndex) {
            FUN_005B59B0();
        }
    }
    SlotIndex = slot;
    HWND_ label = GetDlgItem(Dialog, 0x668);
    if (label != 0) {
        wchar_t line[80];
        swprintf(line, L"%s [%s]", handle, HouseTypeArray.Items[slot]->UIName);
        SendMessageA(label, GG_CBM_SETTEXT, 0, (long)line);
        unsigned long rgb = (color >= 0 && color < 8) ? DAT_008316A8[color] : DefaultSchemeColor;
        SendMessageA(label, GG_CBM_SETCOLOR, 0, rgb);
    }
}

// FUNCTION: GAMEMD 0x5B5EF0
//
// Per-tick service of the dialog: flush the request queue; when the dirty byte is set and more
// than 30 ticks passed since the last send, or the caller forces it, send the status request
// and restart that interval; then, at most every 40 ticks, send a keep-alive (code 0x69).
void WolScenarioColorDlgClass::FUN_005B5EF0(bool force)
{
    DAT_00A8EA70.FUN_005F1C60();
    if ((OptionsChanged == 1 && (unsigned)(MessageTimer.GetValue() - LastSendTime) > 0x1E) || force == 1) {
        FUN_005B6CD0();
        LastSendTime = MessageTimer.GetValue();
        OptionsChanged = 0;
    }
    if ((unsigned)(MessageTimer.GetValue() - LastPingTime) > 0x28) {
        WolRequest_005B5EF0 request;
        memset(&request, 0, 0xFA);
        request.Code = 0x69;
        request.unknown_9A = DAT_00A8EA70.FUN_005F1EE0();
        request.unknown_18 = (char)DAT_00A8DB30;
        DAT_00A8EA70.FUN_005F1BF0(&request, 0xFA, 0);
        LastPingTime = MessageTimer.GetValue();
    }
}

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- resolve a label to its localised text.
const wchar_t* FUN_00734E60(const char* label, int* index, const char* file, int line);
// FUNCTION: GAMEMD 0x623230 (decl; reloc) -- open the wait dialog; each text line goes out as an LPARAM.
void* FUN_00623230(long line1, long line2, long user);
// FUNCTION: GAMEMD 0x622800 (decl; reloc)
void UI_FocusOnWindow(HWND_ window);
// FUNCTION: GAMEMD 0x622720 (decl; reloc)
void UI_EndDialog(void* window);
// FUNCTION: GAMEMD 0x48D080 (decl; reloc)
void __cdecl Unsorted_CallBack();
// FUNCTION: GAMEMD 0x5D4D50 (decl; reloc)
void __cdecl FUN_005D4D50();
// FUNCTION: GAMEMD 0x5F0040 (decl; reloc)
void __cdecl FUN_005F0040();
struct Obj_005B6F30 {
    void FUN_005B6F30();
};

// FUNCTION: GAMEMD 0x5B6DA0
//
// Send a chat line: queue a 0x68 request carrying the local handle, colour and text, flush the
// queue, and echo the line into the dialog's text control as "[handle] text" in the colour.
void Obj_005B6DA0::FUN_005B6DA0(const wchar_t* text)
{
    if (text != 0) {
        WolChatRequest_005B6DA0 request;
        memset(&request, 0, 0xFA);
        request.Code = 0x68;
        strcpy(request.Handle, DAT_00A8B380);
        request.Color = (char)PlayerColor;
        wcscpy(request.Text, text);
        DAT_00A8EA70.FUN_005F1BF0(&request, 0xFA, 1);
        DAT_00A8EA70.FUN_005F1C60();
        const wchar_t* handle = FUN_00735120(DAT_00A8B380);
        int color = PlayerColor;
        HWND_ control = GetDlgItem(unknown_00, 0x53F);
        if (control != 0) {
            unsigned long rgb = (color >= 0 && color < 8) ? DAT_008316A8[color] : DefaultSchemeColor;
            wchar_t line[256];
            swprintf(line, L"[%s] %s", handle, text);
            FUN_005E2820(rgb, line, control);
        }
    }
}

// Prints a coloured line into the dialog's text control (id 0x53F): the line is
// "[name] text" built into a 256-wide-character buffer, and the colour is looked
// up by index in the table of eight colours at 0x8316A8 (the default scheme
// colour when the index is out of range).
// FUNCTION: GAMEMD 0x5E2820 (decl; reloc) -- appends a coloured line to a text control.
void FUN_005E2820(int color, const wchar_t* text, HWND_ window);
struct Obj_005B6EB0 {
    HWND_ unknown_00;
    void FUN_005B6EB0(const wchar_t* name, int index, const wchar_t* text);
};
// FUNCTION: GAMEMD 0x005B6EB0
void Obj_005B6EB0::FUN_005B6EB0(const wchar_t* name, int index, const wchar_t* text)
{
    wchar_t line[256];
    if (text != 0) {
        HWND_ control = GetDlgItem(unknown_00, 0x53F);
        if (control != 0) {
            int color = (index >= 0 && index < 8) ? DAT_008316A8[index] : DefaultSchemeColor;
            swprintf(line, L"[%s] %s", name, text);
            FUN_005E2820(color, line, control);
        }
    }
}

// FUNCTION: GAMEMD 0x5B6F30
//
// Send the sign-off request (code 0x66), show the "signing off" wait dialog and pump the queue
// until the matching reply arrives or 300 ticks pass, then close the dialog.
void Obj_005B6F30::FUN_005B6F30()
{
    WolReply_005B6F30 reply;
    WolRequest_005B6F30 request;
    int length;
    memset(&request, 0, 0xFA);
    request.Code = 0x66;
    request.Color = (char)PlayerColor;
    request.unknown_18 = (char)DAT_00A8DB30;
    DAT_00A8EA70.FUN_005F1BF0(&request, 0xFA, 1);
    HWND_ dialog = (HWND_)FUN_00623230((long)FUN_00734E60("TXT_SIGNING_OFF", 0, "D:\\ra2mdpost\\ModemGst.cpp", 0x693), 0, 0);
    if (dialog != 0) {
        UI_FocusOnWindow(dialog);
    }
    unsigned int start = MessageTimer.GetValue();
    if (DAT_00A8EA70.FUN_005F1EA0() != 0) {
        do {
            if ((unsigned int)(MessageTimer.GetValue() - start) >= 0x12C) {
                break;
            }
            if (DAT_00A8EA70.FUN_005F1C30(&reply, &length) > 0 && reply.Code == 0x66 &&
                (reply.Value & 0xFF) == DAT_00A8DB30) {
                break;
            }
            Unsorted_CallBack();
            FUN_005D4D50();
            DAT_00A8EA70.FUN_005F1C60();
        } while (DAT_00A8EA70.FUN_005F1EA0() != 0);
    }
    FUN_005F0040();
    if (dialog != 0) {
        UI_EndDialog(dialog);
    }
}

// FUNCTION: GAMEMD 0x735060 (decl; reloc) -- __fastcall: narrow text to a wide name.
void FUN_00735060(wchar_t* out, const char* text, int length);
// GLOBAL: GAMEMD 0xA8DA74 -- the lobby's node vector (DynamicVectorClass<NodeNameType*>, vtable 0x7EE370).
extern DynamicVectorClass<NodeNameType*> DAT_00A8DA74;
// GLOBAL: GAMEMD 0xA8B54C -- the number of nodes mirrored.
extern int DAT_00A8B54C;
// GLOBAL: GAMEMD 0xA8B230 -- ScenarioClass::Instance.
extern ScenarioClass* DAT_00A8B230;
// GLOBAL: GAMEMD 0xA8B254 -- the selected entry index.
extern int DAT_00A8B254;
// GLOBAL: GAMEMD 0xA8B260 / 0xA8B31D -- two lobby option bytes (bit 0 is read).
extern unsigned char DAT_00A8B260;
extern unsigned char DAT_00A8B31D;
// GLOBAL: GAMEMD 0xA8ED84
extern int DAT_00A8ED84;
// GLOBAL: GAMEMD 0xA8B24C
extern int DAT_00A8B24C;
// The object at 0xA8E960: a flags dword at +0x00 and the empty member 0x6B8B10.
// FUNCTION: GAMEMD 0x5B7090
// PARTIAL: best 98.5% (197 of 200 instructions). Identical instruction multiset; retail loads the scenario pointer
// before the selected-map index for the +0x1254 store, this build loads the index first. Tried: the stores in
// the opposite order (91.0%).
//
// The guest presses go: read the dialog, put the local player's node and the dialog's own node
// into the lobby vector, then wait up to 60 ticks for the queue to drain (at least 0x708 ticks
// of waiting while it is busy), publish the match options and start. Returns false when the
// argument is 1 or when the two nodes did not both get in.
bool WolScenarioColorDlgClass::FUN_005B7090(char skip)
{
    if (skip == 1) {
        return false;
    }
    FUN_005B56F0();
    DAT_00A8B54C = 0;
    NodeNameType* local = new NodeNameType;
    if (local != 0) {
        FUN_00735060(local->Name, DAT_00A8B380, -1);
        local->unknown_4B = DAT_00A8B3AC;
        local->unknown_53 = PlayerColor;
        local->unknown_73 = -1;
        DynamicVectorAddItemFree(&DAT_00A8DA74, local);
        DAT_00A8B54C++;
    }
    NodeNameType* own = new NodeNameType;
    if (own != 0) {
        wcscpy(own->Name, this->Handle);
        own->unknown_4B = this->SlotIndex;
        own->unknown_53 = this->ColorIndex;
        own->unknown_73 = -1;
        DynamicVectorAddItemFree(&DAT_00A8DA74, own);
        DAT_00A8B54C++;
    }
    if (DAT_00A8B54C != 2) {
        return false;
    }
    HWND_ dialog = (HWND_)FUN_00623230((long)FUN_00734E60("TXT_SENDING_GO_ACK", 0, "D:\\ra2mdpost\\ModemGst.cpp", 0x6F3), 0, 0);
    if (dialog != 0) {
        UI_FocusOnWindow(dialog);
    }
    unsigned int start = MessageTimer.GetValue();
    while (true) {
        if (DAT_00A8EA70.FUN_005F1EA0() == 0 || (unsigned int)(MessageTimer.GetValue() - start) >= 0x708) {
            if ((unsigned int)(MessageTimer.GetValue() - start) >= 0x3C) {
                break;
            }
        }
        Unsorted_CallBack();
        FUN_005D4D50();
        DAT_00A8EA70.FUN_005F1C60();
    }
    if (dialog != 0) {
        UI_EndDialog(dialog);
    }
    DAT_00A8EA70.FUN_005F19C0();
    InhibitFlag = 0;
    DAT_00A8B230->unknown_1254 = DAT_00A8B254;
    DAT_00A8ED84 = 0;
    DAT_00A8B54C = DAT_00A8DA74.Count;
    DAT_00A8B24C = 2;
    DAT_00A8E960.unknown_00 = (((DAT_00A8B260 & 1) << 4 | (DAT_00A8B31D & 1)) << 11) |
                              (DAT_00A8E960.unknown_00 & 0xFFFF77FF) | 0xC0;
    DAT_00A8E960.FUN_006B8B10();
    return true;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA8B3AC
int DAT_00A8B3AC;
// GLOBAL: GAMEMD 0x8316A8
extern const unsigned long DAT_008316A8[8] = {0xDE2DD, 0x1919FF, 0xE2742A, 0x2ED13E, 0x19A0FF, 0xE6D732, 0xBD2895, 0xEB9AFF};
// GLOBAL: GAMEMD 0x7EEF44
extern const unsigned long DefaultSchemeColor = 0x40FFFF;
// GLOBAL: GAMEMD 0xA8B394
int PlayerColor;
// END defined globals
