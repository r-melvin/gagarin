// SPDX-License-Identifier: GPL-3.0-or-later
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Provenance: own-binary-via-Ghidra
//   Original translation unit netdlg2.cpp. The name is the source-file string at 0x831288
//   in retail gamemd.exe v1.001, passed by the assert at 0x5db257 inside this object's
//   code range (0x5dacf0-0x5e242f). Functions are in ascending retail address order.
//
//   Reads the product serial from the registry and unscrambles it with the
//   bytes of the local key file.

#include "trivial_tu160_methods.h"
#include "mathtbl_init_shapes.h"

#include "netshare_win.h"
#include "netshare_slot_nodes.h"
#include "vector_class.h"
#include "connman_class.h"
#include <stdio.h>
#include <string.h>

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EEF08
extern const double DAT_007EEF08;
// GLOBAL: GAMEMD 0xAC01C0
extern double DAT_00AC01C0;

// SYNTHETIC: GAMEMD 0x005DAD20
// GLOBAL: GAMEMD 0x00AC0250
double DAT_00AC0250 = DAT_00AC01C0 / DAT_007EEF08;

// SYNTHETIC: GAMEMD 0x005DAD40
// GLOBAL: GAMEMD 0x00AC0218
double DAT_00AC0218 = DAT_007E1718 / DAT_00AC0250;

// SYNTHETIC: GAMEMD 0x005DAEC0
// GLOBAL: GAMEMD 0x00AC0240
MathTblCoord DAT_00AC0240;

// FUNCTION: GAMEMD 0x5DAF10
// Empty function.
void __cdecl FUN_005DAF10()
{
}


// The lobby list of players announcing a game (0xA8DA5C). Its element record starts with the 0x34
// bytes a node has (name, then the address at +0x28).
#pragma pack(push, 1)
struct Obj_00A8DA60
{
    wchar_t Name[20];            // +0x00
    IPXAddressClass Address;     // +0x28
    char unknown_34;             // +0x34
    int unknown_35;              // +0x35
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(Obj_00A8DA60, Address) == 0x28 && offsetof(Obj_00A8DA60, unknown_34) == 0x34 &&
                 offsetof(Obj_00A8DA60, unknown_35) == 0x35);

// GLOBAL: GAMEMD 0xA8DA5C -- Items at 0xA8DA60, Count at 0xA8DA6C.
extern DynamicVectorClass<Obj_00A8DA60*> DAT_00A8DA5C;
// GLOBAL: GAMEMD 0xAC0260 -- the highlighted row of the game list.
extern int DAT_00AC0260;
// FUNCTION: GAMEMD 0x5DF9E0 (decl; reloc) -- __fastcall (a, b), then two stacked values.
void FUN_005DF9E0(int a, int b, int c, int d);
extern "C" int __cdecl swprintf(wchar_t* buffer, const wchar_t* format, ...);

// FUNCTION: GAMEMD 0x5E8DC0 (decl; reloc) -- __fastcall: writes the slots as a wide string.
void FUN_005E8DC0(wchar_t* out);

// FUNCTION: GAMEMD 0x5DAF30
// Send the kind-0x16 message (the local handle and the slot list) to every remote player.
void FUN_005DAF30()
{
    NetsharePacket packet;
    memset(&packet, 0, sizeof(packet));
    packet.Command = 0x16;
    strcpy(packet.Name, LocalHandle);
    FUN_005E8DC0((wchar_t*)packet.Text);
    int count = PlayerNodes.Count;
    for (int i = 1; i < count; i++) {
        Manager_00A8E9C0.FUN_005410F0(&packet, 0x1C7, 1, &PlayerNodes.Vector[i]->Address, 0, 0);
        FUN_0048D080();
    }
}

// FUNCTION: GAMEMD 0x5DAFD0
// Tail-calls a method on a global object.
void FUN_005DAFD0(int a1, int a2)
{
    FUN_005DAFE0(0);
}

// FUNCTION: GAMEMD 0x5DB9B0
//
// Refill the games list (control 0x549) of the lobby dialog 0xBB: clamp the highlighted row,
// then add the lobby caption followed by one line per announced game, keeping the scroll
// position and the highlight.
void FUN_005DB9B0()
{
    if (FUN_00775B20() == 0xBB) {
        HWND dialog = FUN_00775B10();
        HWND list = GetDlgItem(dialog, 0x549);
        if (DAT_00AC0260 >= DAT_00A8DA5C.Count) {
            DAT_00AC0260 = DAT_00A8DA5C.Count - 1;
            FUN_005DF9E0(0, 1, 0, 0);
        }
        if (DAT_00AC0260 < 0) {
            DAT_00AC0260 = 0;
        }
        WPARAM top = SendDlgItemMessageA(dialog, 0x549, 0x18E, 0, 0);
        SendDlgItemMessageA(dialog, 0x549, 0x49D, 0, 1);
        SendMessageA(list, 0x184, 0, 0);
        SendMessageA(list, 0x4CD, 0, (LPARAM)Fetch_String_00734E60("TXT_LOBBY", 0, "D:\\ra2mdpost\\netdlg2.cpp", 0x1FC));
        for (int i = 1; i < DAT_00A8DA5C.Count; i++) {
            wchar_t line[80];
            if (DAT_00A8DA5C.Items[i]->unknown_34 != 0) {
                swprintf(line, Fetch_String_00734E60("TXT_THATGUYS_GAME", 0, "D:\\ra2mdpost\\netdlg2.cpp", 0x202),
                         DAT_00A8DA5C.Items[i]);
            } else {
                swprintf(line, Fetch_String_00734E60("TXT_THATGUYS_GAME_BRACKET", 0, "D:\\ra2mdpost\\netdlg2.cpp", 0x204),
                         DAT_00A8DA5C.Items[i]);
            }
            SendMessageA(list, 0x4CD, 0, (LPARAM)line);
        }
        SendDlgItemMessageA(dialog, 0x549, 0x186, DAT_00AC0260, 0);
        SendDlgItemMessageA(dialog, 0x549, 0x197, top, 0);
        SendDlgItemMessageA(dialog, 0x549, 0x49D, 0, 0);
        HWND control = GetDlgItem(dialog, 0x549);
        InvalidateRect(control, 0, 0);
        UpdateWindow(control);
    }
}

// GLOBAL: GAMEMD 0xAC0268 -- set while the lobby dialog is being torn down.
extern char DAT_00AC0268;
// GLOBAL: GAMEMD 0xA8B258
extern char DAT_00A8B258;
// GLOBAL: GAMEMD 0xA8B260, 0xA8B261, 0xA8B262, 0xA8B263, 0xA8B264, 0xA8B320 -- the lobby option bytes.
extern unsigned char DAT_00A8B260;
extern unsigned char DAT_00A8B261;
extern unsigned char DAT_00A8B262;
extern unsigned char DAT_00A8B263;
extern unsigned char DAT_00A8B264;
extern unsigned char DAT_00A8B320;
// GLOBAL: GAMEMD 0xA8B268, 0xA8B25C, 0xA8B270 -- the three slider options.
extern int DAT_00A8B268;
extern int DAT_00A8B25C;
extern int DAT_00A8B270;
// FUNCTION: GAMEMD 0x775940 (decl; reloc) -- __fastcall: the dialog window of an id.
HWND FUN_00775940(int id);
// FUNCTION: GAMEMD 0x5EDDE0 (decl; reloc) -- __fastcall: enable or disable the local slot's controls.
void FUN_005EDDE0(HWND dialog, unsigned char enable);

static inline int Find_Player_By_Handle(const char* handle)
{
    for (int i = 0; i < PlayerNodes.Count; i++) {
        if (_stricmp(Narrow_007350C0(PlayerNodes.Vector[i]->Name), handle) == 0) {
            return i;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x5DBE20
// Flag a lobby player (the node's +0x77); a null handle means the local player.
void FUN_005DBE20(const char* handle, int value)
{
    if (handle == 0) {
        handle = LocalHandle;
        if (value == 0) {
            HWND dialog = FUN_00775940(0xBD);
            FUN_005EDDE0(dialog, 1);
        }
    }
    if (wcscmp(Widen_00735120(handle), BlankName) == 0) {
        value = 1;
    }
    int i = Find_Player_By_Handle(handle);
    if (i != -1) {
        PlayerNodes.Vector[i]->unknown_77 = value;
    }
    FUN_005DAFE0(0);
}

// FUNCTION: GAMEMD 0x005dc170
// Copies the decoded serial into out.
// out receives an all-zero default first; returns false when the key file
// cannot be opened.
bool FUN_005dc170(char* out)
{
    char serial[128];
    memset(serial, '0', 22);
    serial[22] = '\0';
    strcpy(out, serial);
    memset(serial, 0, sizeof(serial));
    const char* keyPath = "SOFTWARE\\Westwood\\Yuri's Revenge";
    if (keyPath != 0 && strlen(keyPath) != 0) {
        char path[256];
        HKEY key;
        strcpy(path, keyPath);
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, path, 0, KEY_READ, &key) == ERROR_SUCCESS) {
            DWORD type;
            DWORD size = sizeof(serial);
            RegQueryValueExA(key, "Serial", 0, &type, (LPBYTE)serial, &size);
            RegCloseKey(key);
        }
    }
    serial[22] = '\0';
    strcpy(out, serial);
    unsigned int i = 0;
    FILE* file = fopen("woldata.key", "r");
    if (file == 0) {
        return false;
    }
    int c;
    while ((c = fgetc(file)) != EOF) {
        serial[i] = ((serial[i] - '0') % 10 - c + 1000) % 10 + '0';
        i++;
        if (i == strlen(serial)) {
            i = 0;
        }
    }
    fclose(file);
    strcpy(out, serial);
    return true;
}

// FUNCTION: GAMEMD 0x5E3010 (decl; reloc) -- __fastcall (dialog, mode).
void FUN_005E3010(HWND dialog, int mode);

// FUNCTION: GAMEMD 0x5DF180
//
// Dialog procedure of the lobby's options page: a checkbox click copies that box into its
// option byte, a slider scroll copies the slider position, and message 0x497 asks for the
// options to be published. Nothing is handled once the dialog is closing.
int __stdcall FUN_005DF180(HWND dialog, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (DAT_00AC0268 == 0) {
        switch (message) {
        case WM_COMMAND:
            switch (LOWORD(wparam)) {
            case 0x624:
                DAT_00A8B260 = 0;
                if (SendDlgItemMessageA(dialog, 0x624, 0xF0, 0, 0) == 1) {
                    DAT_00A8B260 = 1;
                    return 0;
                }
                break;
            case 1000:
                DAT_00A8B320 = 0;
                if (SendDlgItemMessageA(dialog, 1000, 0xF0, 0, 0) == 1) {
                    DAT_00A8B320 = 1;
                    return 0;
                }
                break;
            case 0x54D:
                DAT_00A8B261 = 0;
                if (SendDlgItemMessageA(dialog, 0x54D, 0xF0, 0, 0) == 1) {
                    DAT_00A8B261 = 1;
                    return 0;
                }
                break;
            case 0x54E:
                DAT_00A8B262 = 0;
                if (SendDlgItemMessageA(dialog, 0x54E, 0xF0, 0, 0) == 1) {
                    DAT_00A8B262 = 1;
                    if (DAT_00A8B258 == 0) {
                        DAT_00A8B258 = 1;
                        SendDlgItemMessageA(dialog, 0x54B, 0xF1, 1, 0);
                        return 0;
                    }
                }
                break;
            case 0x69A:
                DAT_00A8B263 = 0;
                if (SendDlgItemMessageA(dialog, 0x69A, 0xF0, 0, 0) == 1) {
                    DAT_00A8B263 = 1;
                }
                break;
            case 0x69D:
                DAT_00A8B264 = 0;
                if (SendDlgItemMessageA(dialog, 0x69D, 0xF0, 0, 0) == 1) {
                    DAT_00A8B264 = 1;
                    return 0;
                }
                break;
            }
            break;
        case WM_HSCROLL:
            if (GetDlgItem(dialog, 0x529) == (HWND)lparam) {
                DAT_00A8B268 = 6 - SendDlgItemMessageA(dialog, 0x529, 0x400, 0, 0);
            }
            if (GetDlgItem(dialog, 0x402) == (HWND)lparam) {
                DAT_00A8B25C = SendDlgItemMessageA(dialog, 0x402, 0x400, 0, 0);
            }
            if (GetDlgItem(dialog, 0x54F) == (HWND)lparam) {
                DAT_00A8B270 = SendDlgItemMessageA(dialog, 0x54F, 0x400, 0, 0);
                return 0;
            }
            break;
        case 0x497:
            FUN_005E3010(dialog, 1);
            return 0;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x5DFDD0
// Empty function.
void __cdecl FUN_005DFDD0()
{
}

// FUNCTION: GAMEMD 0x5DFDE0
// Empty function.
void __cdecl FUN_005DFDE0()
{
}

// FUNCTION: GAMEMD 0x5DFDF0
// Empty function.
void __cdecl FUN_005DFDF0()
{
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7EEF08
extern const double DAT_007EEF08 = 60.0;
// END defined globals
