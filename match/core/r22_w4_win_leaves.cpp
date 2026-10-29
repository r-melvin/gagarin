// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Small window-system and math leaves read off the user's retail gamemd.exe v1.001 with the
//   local Ghidra CLI at the address in each annotation.
//   Address index: 0x75F540, 0x775BA0, 0x776D40, 0x776E70, 0x777E00, 0x7BD210, 0x7AD440, 0x7AD460.

#include <windows.h>
#include <stdio.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/coord_struct.h"
#include "../ui/input_controls/ui_common.h"

HWND __cdecl FUN_00775B10();
BOOL __stdcall FUN_00775BC0(HWND window, LPARAM param);

// GLOBAL: GAMEMD 0xB73060
extern char DAT_00B73060[];
// GLOBAL: GAMEMD 0xB730EC / 0xB73318 / 0xB73564 / 0xB73568 / 0xB7356C / 0xB7355C -- IME composition state.
extern short DAT_00B730EC;
extern short DAT_00B73318;
extern int DAT_00B73564;
extern int DAT_00B73568;
extern int DAT_00B7356C;
extern int DAT_00B7355C;

// LIBRARY: GAMEMD 0x7C8A28 (declaration) -- import thunk for ImmNotifyIME.
int __stdcall FUN_007C8A28(int himc, int action, int index, int value);

// FUNCTION: GAMEMD 0x75F540
// Blends two coordinates: out = a * t + b * (1 - t), each axis truncated to int.
CoordStruct* __fastcall FUN_0075F540(CoordStruct* out, const CoordStruct* b, const CoordStruct* a, float t)
{
    double u = 1.0 - t;
    CoordStruct r;
    r.X = (int)(a->X * t + b->X * u);
    r.Y = (int)(a->Y * t + b->Y * u);
    r.Z = (int)(a->Z * t + b->Z * u);
    *out = r;
    return out;
}

// FUNCTION: GAMEMD 0x775BA0
// Runs the child-window callback over every child with 1, then over the window itself with 0.
void __fastcall FUN_00775BA0(HWND window)
{
    EnumChildWindows(window, (WNDENUMPROC)FUN_00775BC0, 1);
    FUN_00775BC0(window, 0);
}

// FUNCTION: GAMEMD 0x776D40
// Formats an optional prefix plus a number into the shared text buffer.
char* __fastcall FUN_00776D40(const char* prefix, int number)
{
    if (prefix) {
        wsprintfA(DAT_00B73060, "%s%d", prefix, number);
        return DAT_00B73060;
    }
    wsprintfA(DAT_00B73060, "%d", number);
    return DAT_00B73060;
}

// FUNCTION: GAMEMD 0x776E70
// Shows or hides the cursor through the mouse singleton; showing also redraws the window.
void __fastcall FUN_00776E70(HWND window, short show)
{
    if (DAT_00887640) {
        if (show == 0) {
            DAT_00887640->vf_18();
            return;
        }
        DAT_00887640->vf_14();
        RedrawWindow(window, 0, 0, 0x587);
    }
}

// FUNCTION: GAMEMD 0x777E00
// Clears the IME composition state and cancels any composition in progress.
void __cdecl FUN_00777E00()
{
    DAT_00B73318 = 0;
    DAT_00B73564 = 0;
    DAT_00B73568 = 0;
    DAT_00B7356C = 0;
    DAT_00B730EC = 0;
    if (DAT_00B7355C != 0) {
        FUN_007C8A28(DAT_00B7355C, 0x15, 4, 0);
    }
}

// Movie stream object: a callback pointer at +0x58 and a flag word at +0x7BC.
struct MovieStream_007BD210
{
    char unknown_000[0x58];
    void (__cdecl* Callback)(MovieStream_007BD210* self, int op, int a, int b);   // +0x58
    char unknown_05C[0x760];
    unsigned int Flags;                                                            // +0x7BC
};
GG_STATIC_ASSERT(offsetof(MovieStream_007BD210, Callback) == 0x58);
GG_STATIC_ASSERT(offsetof(MovieStream_007BD210, Flags) == 0x7BC);

// FUNCTION: GAMEMD 0x7BD210
// Stops the stream: ends a running playback (op 7) first, then issues op 3 and clears the top flag.
void __fastcall FUN_007BD210(MovieStream_007BD210* self)
{
    if (self->Flags & 0x40) {
        self->Callback(self, 7, 0, 0);
        self->Flags &= ~0x40;
    }
    self->Callback(self, 3, 0, 0);
    if ((self->Flags & 0x80000000) == 1) {
        self->Flags &= 0x7FFFFFFF;
    }
}

// FUNCTION: GAMEMD 0x7AD440
// Posts message 0x5F4 to the current dialog window; returns 0.
int __stdcall FUN_007AD440(void* self)
{
    SendMessageA((HWND)FUN_00775B10(), 0x5F4, 0, 0);
    return 0;
}

// FUNCTION: GAMEMD 0x7AD460
// Sends message 0x5F5 with the given lParam to the current dialog window; returns 0.
int __stdcall FUN_007AD460(void* self, LPARAM lParam)
{
    SendMessageA((HWND)FUN_00775B10(), 0x5F5, 0, lParam);
    return 0;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB730EC
short DAT_00B730EC;
// GLOBAL: GAMEMD 0xB73318
short DAT_00B73318;
// GLOBAL: GAMEMD 0xB7355C
int DAT_00B7355C;
// GLOBAL: GAMEMD 0xB73564
int DAT_00B73564;
// GLOBAL: GAMEMD 0xB73568
int DAT_00B73568;
// GLOBAL: GAMEMD 0xB7356C
int DAT_00B7356C;
// END defined globals
