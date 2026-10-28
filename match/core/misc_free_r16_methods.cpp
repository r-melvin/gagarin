// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Small free functions read off retail gamemd.exe v1.001, round 16. Free functions use the
//   project's default __fastcall convention.
//   Address index: 0x6B9370 0x758E10 0x763610 0x775690.

#include <stddef.h>
#include <windows.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x8A0DD0..0x8A0DE4 -- the display's colour shift operands.
extern int DAT_008A0DD0;
extern int DAT_008A0DD4;
extern int DAT_008A0DD8;
extern int DAT_008A0DDC;
extern int DAT_008A0DE0;
extern int DAT_008A0DE4;

// FUNCTION: GAMEMD 0x6B9370
// Pack a colour into the display format; the middle channel is brightened by half, capped at 255.
unsigned int __fastcall FUN_006B9370(int first, int second, int third)
{
    int boosted = (second * 15) / 10;
    int middle = boosted > 255 ? 255 : boosted;
    boosted = DAT_008A0DD0;
    return ((third / 4) >> DAT_008A0DDC << DAT_008A0DD8) | ((first >> DAT_008A0DE4) << DAT_008A0DE0) |
           ((middle >> DAT_008A0DD4) << boosted);
}

// GLOBAL: GAMEMD 0xB72654 -- the shared name buffer.
extern char DAT_00B72654[];
// GLOBAL: GAMEMD 0x847F3C / 0x847F44 -- "%c%c" and "%c".
extern const char STR_00847F3C[];
extern const char STR_00847F44[];

// FUNCTION: GAMEMD 0x763610
// The letter name of an index: A-Z, then AA, AB and so on; -1 is empty.
char* __fastcall FUN_00763610(int index)
{
    if (index == -1) {
        DAT_00B72654[0] = 0;
        return DAT_00B72654;
    }
    if (index < 26) {
        wsprintfA(DAT_00B72654, STR_00847F44, index + 'A');
        return DAT_00B72654;
    }
    wsprintfA(DAT_00B72654, STR_00847F3C, index / 26 + '@', index % 26 + 'A');
    return DAT_00B72654;
}

// GLOBAL: GAMEMD 0xB73550 -- the game window.
extern HWND DAT_00B73550;

// FUNCTION: GAMEMD 0x775690
// The window's rectangle, relative to the client area's origin on screen.
BOOL __fastcall FUN_00775690(HWND window, RECT* rect)
{
    BOOL ok = GetWindowRect(window, rect);
    if (ok == 0) {
        return 0;
    }
    RECT client;
    GetClientRect(DAT_00B73550, &client);
    ClientToScreen(DAT_00B73550, (LPPOINT)&client);
    rect->left = rect->left - client.left;
    rect->right = rect->right - client.left;
    rect->top = rect->top - client.top;
    rect->bottom = rect->bottom - client.top;
    return ok;
}

// A palette, as far as its table of RGB byte triples.
struct PaletteView_r16
{
    unsigned char FUN_00758E10(float red, float green, float blue);

    char unknown_00[0x10];
    unsigned char* Entries;   // +0x10 256 RGB triples
};

// FUNCTION: GAMEMD 0x758E10
// The palette index whose colour is closest to the given one (smallest squared distance).
unsigned char PaletteView_r16::FUN_00758E10(float red, float green, float blue)
{
    float bestDistance = 100000.0f;
    int best = 0;
    int i = 0;
    unsigned char* entry = Entries;
    do {
        float dr = red - (float)entry[0];
        float dg = green - (float)entry[1];
        float db = blue - (float)entry[2];
        float distance = dr * dr + dg * dg + db * db;
        if (distance < bestDistance) {
            best = i;
            bestDistance = distance;
        }
        i++;
        entry += 3;
    } while (i < 256);
    return (unsigned char)best;
}
