// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Body read from the retail function at 0x531F60 (0x19F bytes, RET 0x10). The version string comes
//   from the VersionClass instance at 0xA8ECE0 (0x74FAE0 returns its VersionName).
#include <windows.h>
#include <stddef.h>
#include "../_layout/version_class.h"

// FUNCTION: GAMEMD 0x622B50 (decl; reloc) -- the shared dialog handler.
int __fastcall FUN_00622B50(HWND h, UINT msg, WPARAM w, LPARAM l);
// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- localised string lookup(label, index, file, line).
const wchar_t* FUN_00734E60(const char* label, int index, const char* file, int line);
// FUNCTION: GAMEMD 0x735120 (decl; reloc) -- ANSI to wide, ECX = text.
const wchar_t* FUN_00735120(const char* text);
// LIBRARY: GAMEMD 0x7CA564 -- CRT swprintf.
int __cdecl swprintf(wchar_t* out, const wchar_t* format, ...);

// GLOBAL: GAMEMD 0xA8ECE0 -- the network-protocol version record.
extern VersionClass DAT_00A8ECE0;
// GLOBAL: GAMEMD 0x825FB8 -- "D:\ra2mdpost\Init.CPP"
extern char DAT_00825FB8[];
// GLOBAL: GAMEMD 0x82696C -- "GUI:Version"
extern char DAT_0082696C[];

// STRING: GAMEMD 0x826960 -- L"%s %s"
// FUNCTION: GAMEMD 0x531F60
// Dialog procedure for the title screen: on init print the localised "Version" label and the game
// version into the version caption, and on a button command store its result code through the
// window's user data.
int __stdcall FUN_00531F60(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    int r = FUN_00622B50(h, msg, w, l);
    if (r == 0) {
        int* data = (int*)GetWindowLongA(h, 8);
        switch (msg) {
        case 0x111: {
            int id = w & 0xFFFF;
            switch (id) {
            case 0x683:
                *data = 1;
                return 0;
            case 0x684:
                *data = 2;
                return 0;
            case 0x686:
                *data = 4;
                return 0;
            case 0x3EE:
                *data = 6;
                return 0;
            case 0x55C:
                *data = 5;
                return 0;
            case 0x578:
                *data = 3;
                return 0;
            }
            break;
        }
        case 0xF: {
            HWND item = GetDlgItem(h, 0x71A);
            SendMessageA(item, 0x4F0, 0, 0);
            break;
        }
        case 0x497: {
            HWND caption = GetDlgItem(h, 0x71D);
            wchar_t text[0x80];
            swprintf(text, L"%s %s", FUN_00734E60(DAT_0082696C, 0, DAT_00825FB8, 0x1757),
                     FUN_00735120(DAT_00A8ECE0.FUN_0074FAE0()));
            SendMessageA(caption, 0x4B2, 0, (LPARAM)text);
            return 0;
        }
        }
        r = 0;
    }
    return r;
}
