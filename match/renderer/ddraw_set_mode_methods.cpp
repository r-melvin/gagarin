// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// Creates the DirectDraw object on first use, sets the cooperative level and
// display mode, records the mode in 0x8A00A4/A8/AC and, for 8-bit modes,
// creates the primary palette (0x89FC90) over the entry table at 0x89FC94.
// DirectDraw failures go to the error callback at 0x8A00B0 when one is set,
// otherwise to a message box. The window argument (ECX) is unused; the
// global main window at 0xB73550 is used throughout.
//
// LIBRARY: IAT 0x7E1460 USER32!MessageBoxA; 0x7C8EF4 sprintf;
//   0x7C89D4 DirectDrawCreate (import thunk).

#include <stddef.h>
#include <stdio.h>
#include "../_rt/gg_static_assert.h"

struct DDrawModeView;

// C-style DirectDraw vtable, through SetDisplayMode.
struct DDrawModeVtbl
{
    void* unknown_00[5];
    long (__stdcall* CreatePalette)(DDrawModeView* self, unsigned long flags, void* entries,
                                    void** palette, void* outer);           // +0x14
    void* unknown_18[14];
    long (__stdcall* SetCooperativeLevel)(DDrawModeView* self, void* window,
                                          unsigned long flags);             // +0x50
    long (__stdcall* SetDisplayMode)(DDrawModeView* self, int width, int height,
                                     int bpp);                              // +0x54
};
GG_STATIC_ASSERT(offsetof(DDrawModeVtbl, CreatePalette) == 0x14);
GG_STATIC_ASSERT(offsetof(DDrawModeVtbl, SetCooperativeLevel) == 0x50);
GG_STATIC_ASSERT(offsetof(DDrawModeVtbl, SetDisplayMode) == 0x54);

struct DDrawModeView
{
    DDrawModeVtbl const* lpVtbl;
};

extern "C" long __stdcall DirectDrawCreate(void* guid, DDrawModeView** out, void* outer);
extern "C" __declspec(dllimport) int __stdcall MessageBoxA(void* window, char const* text,
                                                           char const* caption, unsigned type);

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);
// FUNCTION: GAMEMD 0x4A3E40 (decl; reloc)
void FUN_004a3e40();

// GLOBAL: GAMEMD 0x8A0094 -- the DirectDraw object.
extern DDrawModeView* DAT_008A0094;
// GLOBAL: GAMEMD 0x8A00A4 / 0x8A00A8 / 0x8A00AC -- display mode width, height, depth.
extern int DAT_008A00A4;
extern int DAT_008A00A8;
extern int DAT_008A00AC;
// GLOBAL: GAMEMD 0x8A00B0 -- the DirectDraw error callback.
extern void (* DAT_008A00B0)(long hr);
// GLOBAL: GAMEMD 0xB73550 -- the main window.
extern void* DAT_00B73550;
// GLOBAL: GAMEMD 0x89F978 -- selects the cooperative-level flags.
extern bool DAT_0089F978;
// GLOBAL: GAMEMD 0x89FC90 -- the primary palette object.
extern void* DAT_0089FC90;
// GLOBAL: GAMEMD 0x89FC94 -- the palette entry table.
extern char DAT_0089FC94[];

inline void DDraw_Report(long hr)
{
    if (DAT_008A00B0 != 0)
    {
        DAT_008A00B0(hr);
    }
    else
    {
        char text[0x50];
        sprintf(text, "DDRAW.DLL Error code = %08X", hr);
        MessageBoxA(DAT_00B73550, text, "Direct X", 0x30);
    }
}

// FUNCTION: GAMEMD 0x4A42F0
bool FUN_004a42f0(void* window, int width, int height, int bpp)
{
    FUN_004068E0("Prep direct draw.\n");
    if (DAT_008A0094 == 0)
    {
        long hr = DirectDrawCreate(0, &DAT_008A0094, 0);
        if (hr == 0)
        {
            hr = DAT_008A0094->lpVtbl->SetCooperativeLevel(DAT_008A0094, DAT_00B73550,
                                                           DAT_0089F978 ? 0x8 : 0x11);
            if (hr != 0)
            {
                DDraw_Report(hr);
            }
        }
        else
        {
            DDraw_Report(hr);
            FUN_004068E0("DirectDrawCreate failed!\n");
        }
    }
    FUN_004068E0("SetDisplayMode: %dx%dx%d\n", width, height, bpp);
    if (DAT_008A0094->lpVtbl->SetDisplayMode(DAT_008A0094, width, height, bpp) != 0)
    {
        FUN_004068E0("SetDisplayMode failed\n");
        return false;
    }
    DAT_008A00A4 = width;
    DAT_008A00A8 = height;
    DAT_008A00AC = bpp;
    if (bpp == 8)
    {
        FUN_004068E0("CreatePalette\n");
        long hr = DAT_008A0094->lpVtbl->CreatePalette(DAT_008A0094, 0x44, DAT_0089FC94, &DAT_0089FC90, 0);
        if (hr != 0)
        {
            DDraw_Report(hr);
            FUN_004068E0("CreatePalette failed\n");
            return false;
        }
    }
    FUN_004a3e40();
    FUN_004068E0("Display mode set\n");
    return true;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x8A00A8
int DAT_008A00A8;
// GLOBAL: GAMEMD 0x8A00AC
int DAT_008A00AC;
// END defined globals
