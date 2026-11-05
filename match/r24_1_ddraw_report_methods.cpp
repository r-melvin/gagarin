// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below. The
//   error callback (ECX = HRESULT) and the message box strings are the same
//   ones match/ddraw_set_mode_methods.cpp reports through.
//
// Ordered ascending by retail address.

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "_rt/gg_static_assert.h"
#include "dsurface_class.h"

extern "C" __declspec(dllimport) int __stdcall MessageBoxA(void* window, char const* text,
                                                           char const* caption, unsigned type);

// STRING: GAMEMD 0x81FC70 -- "Direct X"
extern const char STR_0081FC70[];
// STRING: GAMEMD 0x81FC7C -- "DDRAW.DLL Error code = %08X"
extern const char STR_0081FC7C[];
// STRING: GAMEMD 0x81FC98 -- "Direct Draw operation processed without error"
extern const char STR_0081FC98[];
// STRING: GAMEMD 0x81FCC8 -- "Note"
extern const char STR_0081FCC8[];

// GLOBAL: GAMEMD 0x8A00B0 -- the DirectDraw error callback.
extern void (* DAT_008A00B0)(long hr);
// GLOBAL: GAMEMD 0xB73550 -- the main window.
extern void* DAT_00B73550;

struct IDDrawRelease_004A40C0;
// GLOBAL: GAMEMD 0x8A0094 -- the DirectDraw object.
extern IDDrawRelease_004A40C0* DAT_008A0094;

// DirectDraw object seen through the Release (+0x8), GetCaps (+0x2C),
// SetCooperativeLevel (+0x50) and WaitForVerticalBlank (+0x58) slots only.
struct IDDrawRelease_004A40C0
{
    struct Vtbl
    {
        void* unknown_00[2];
        long (__stdcall* Release)(IDDrawRelease_004A40C0* self);                       // +0x08
        void* unknown_0C[8];
        long (__stdcall* GetCaps)(IDDrawRelease_004A40C0* self, void* driverCaps,
                                  void* helCaps);                                      // +0x2C
        long (__stdcall* GetDisplayMode)(IDDrawRelease_004A40C0* self, void* desc);   // +0x30
        void* unknown_34[7];
        long (__stdcall* SetCooperativeLevel)(IDDrawRelease_004A40C0* self, void* window,
                                              unsigned long flags);                    // +0x50
        void* unknown_54;
        long (__stdcall* WaitForVerticalBlank)(IDDrawRelease_004A40C0* self,
                                               unsigned long flags, void* event);      // +0x58
    };
    Vtbl const* lpVtbl;
};
GG_STATIC_ASSERT(offsetof(IDDrawRelease_004A40C0::Vtbl, Release) == 0x08);
GG_STATIC_ASSERT(offsetof(IDDrawRelease_004A40C0::Vtbl, GetCaps) == 0x2C);
GG_STATIC_ASSERT(offsetof(IDDrawRelease_004A40C0::Vtbl, GetDisplayMode) == 0x30);
GG_STATIC_ASSERT(offsetof(IDDrawRelease_004A40C0::Vtbl, SetCooperativeLevel) == 0x50);
GG_STATIC_ASSERT(offsetof(IDDrawRelease_004A40C0::Vtbl, WaitForVerticalBlank) == 0x58);

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- printf-style log sink, caller cleans the stack.
extern "C" int __cdecl FUN_004068E0(const char* fmt, ...);
// FUNCTION: GAMEMD 0x4A4AC0 (decl; reloc) -- variadic progress logger, caller cleans the stack.
extern "C" void __cdecl FUN_004A4AC0(const char* fmt, ...);

// GLOBAL: GAMEMD 0x8205D5 -- the overlapped-blit probe verdict.
extern "C" unsigned char DAT_008205D5;

// GLOBAL: GAMEMD 0x81FC6C -- cleared once the driver reports the vertical-blank wait unimplemented.
extern bool DAT_0081FC6C;

// FUNCTION: GAMEMD 0x4A3DD0
//
// Report a DirectDraw result: a failure goes to the error callback when one is
// set, otherwise to a message box; a success only gets a note when asked for.
void __fastcall FUN_004a3dd0(long hr, int notifyOk)
{
    if (hr == 0)
    {
        if (notifyOk != 0)
        {
            MessageBoxA(DAT_00B73550, STR_0081FC98, STR_0081FCC8, 0);
        }
    }
    else if (DAT_008A00B0 != 0)
    {
        DAT_008A00B0(hr);
    }
    else
    {
        char text[0x50];
        sprintf(text, STR_0081FC7C, hr);
        MessageBoxA(DAT_00B73550, text, STR_0081FC70, 0x30);
    }
}

// FUNCTION: GAMEMD 0x4A3E40
//
// Probe two blitter features on a scratch 64x64 surface and log the verdicts: a region fill
// (a pixel written by Fill must read back as the filler) and an overlapped copy (a pixel
// copied one row down must land there).
void FUN_004a3e40()
{
    DSurface surface(0x40, 0x40, false, false);
    FUN_004068E0("Checking hardware region fill capability... ");
    DAT_008205D4 = 1;
    surface.Fill(0);
    {
        Point2D probe;
        probe.X = 5;
        probe.Y = 5;
        if (surface.GetPixel(&probe) != 0)
        {
            DAT_008205D4 = 0;
        }
        else
        {
            surface.Fill(1);
            probe.X = 5;
            probe.Y = 5;
            if (surface.GetPixel(&probe) != 1)
            {
                DAT_008205D4 = 0;
            }
        }
    }
    FUN_004A4AC0("%s\n", DAT_008205D4 != 0 ? "OK" : "Failed!");
    FUN_004068E0("Checking overlapped blit capability... ");
    DAT_008205D5 = 1;
    surface.Fill(0);
    {
        Point2D corner;
        corner.X = 0;
        corner.Y = 0;
        surface.PutPixel(&corner, 0xFF);
    }
    {
        RectangleStruct from;
        RectangleStruct to;
        from.X = 0;
        from.Y = 0;
        from.Width = 0x40;
        from.Height = 0x3F;
        to.X = 0;
        to.Y = 1;
        to.Width = 0x40;
        to.Height = 0x3F;
        surface.CopyFromPart(&to, &surface, &from, false, false);
    }
    {
        Point2D landed;
        landed.X = 0;
        landed.Y = 5;
        if (surface.GetPixel(&landed) != 0)
        {
            FUN_004A4AC0("Failed!\n");
            DAT_008205D5 = 0;
            return;
        }
    }
    FUN_004A4AC0("OK\n");
}

// FUNCTION: GAMEMD 0x4A40C0
//
// Release the DirectDraw object if there is one, reporting a nonzero result
// through the error callback or a message box, and clear the global.
void FUN_004a40c0()
{
    if (DAT_008A0094 != 0)
    {
        long hr = DAT_008A0094->lpVtbl->Release(DAT_008A0094);
        if (hr != 0)
        {
            if (DAT_008A00B0 != 0)
            {
                DAT_008A00B0(hr);
                DAT_008A0094 = 0;
                return;
            }
            char text[0x50];
            sprintf(text, STR_0081FC7C, hr);
            MessageBoxA(DAT_00B73550, text, STR_0081FC70, 0x30);
        }
        DAT_008A0094 = 0;
    }
}

// The driver capability block: size word, the capability flags, the video memory total, then the rest.
struct DDrawCaps_004A4620
{
    unsigned long dwSize;           // +0x0000
    unsigned long dwCaps;           // +0x0004
    char          unknown_08[0x3C - 8];
    unsigned long dwVidMemTotal;    // +0x003C
    char          unknown_40[0x13C - 0x40];
};
GG_STATIC_ASSERT(offsetof(DDrawCaps_004A4620, dwVidMemTotal) == 0x3C);
GG_STATIC_ASSERT(sizeof(DDrawCaps_004A4620) == 0x13C);

// The display-mode descriptor (0x6C bytes) the display-mode query fills.
struct DDrawModeDesc_004A4130
{
    unsigned long dwSize;           // +0x00
    char          unknown_04[4];
    unsigned long dwHeight;         // +0x08
    unsigned long dwWidth;          // +0x0C
    long          lPitch;           // +0x10
    char          unknown_14[0x54 - 0x14];
    unsigned long dwRGBBitCount;    // +0x54
    char          unknown_58[0x6C - 0x58];
};
GG_STATIC_ASSERT(offsetof(DDrawModeDesc_004A4130, lPitch) == 0x10);
GG_STATIC_ASSERT(offsetof(DDrawModeDesc_004A4130, dwRGBBitCount) == 0x54);
GG_STATIC_ASSERT(sizeof(DDrawModeDesc_004A4130) == 0x6C);

extern "C" long __stdcall DirectDrawCreate(void* guid, IDDrawRelease_004A40C0** out, void* outer);

// The nonzero result of a DirectDraw call goes to the error callback or a message box.
inline bool DDrawResultOk_004A4130(long hr)
{
    if (hr == 0)
    {
        return true;
    }
    if (DAT_008A00B0 != 0)
    {
        DAT_008A00B0(hr);
        return false;
    }
    char text[0x50];
    sprintf(text, STR_0081FC7C, hr);
    MessageBoxA(DAT_00B73550, text, STR_0081FC70, 0x30);
    return false;
}

// FUNCTION: GAMEMD 0x4A4130
//
// Size the video memory: create the DirectDraw object when there is none, ask the
// driver for its total, add the current display mode's frame, round up to a whole
// megabyte, then release an object this call created.
unsigned FUN_004a4130()
{
    DDrawCaps_004A4620 caps;
    DDrawModeDesc_004A4130 mode;
    bool created = false;
    if (DAT_008A0094 == 0)
    {
        if (DDrawResultOk_004A4130(DirectDrawCreate(0, &DAT_008A0094, 0)))
        {
            created = true;
        }
        else
        {
            DAT_008A0094 = 0;
        }
    }
    unsigned vram = 0;
    if (DAT_008A0094 != 0)
    {
        caps.dwSize = 0x13C;
        if (DAT_008A0094->lpVtbl->GetCaps(DAT_008A0094, &caps, 0) == 0)
        {
            vram = caps.dwVidMemTotal;
            FUN_004068E0("DDraw returnded actual VRAM of %d bytes (%dMb)\n", vram, vram >> 20);
            memset(&mode, 0, sizeof(mode));
            mode.dwSize = 0x6C;
            if (DAT_008A0094->lpVtbl->GetDisplayMode(DAT_008A0094, &mode) == 0)
            {
                FUN_004068E0("Current display size is %dx%dx%d. Pitch is %d\n", mode.dwWidth, mode.dwHeight,
                             mode.dwRGBBitCount, mode.lPitch);
                vram += (mode.dwRGBBitCount >> 3) * mode.dwWidth * mode.dwHeight;
            }
            vram = (vram + 0x20000) & 0xFFF00000;
            FUN_004068E0("Adjusted VRAM size is %d bytes (%dMb)\n", vram, vram >> 20);
        }
    }
    if (created && DAT_008A0094 != 0)
    {
        DDrawResultOk_004A4130(DAT_008A0094->lpVtbl->Release(DAT_008A0094));
        DAT_008A0094 = 0;
    }
    return vram;
}

// FUNCTION: GAMEMD 0x4A4620
//
// Query the DirectDraw driver's capabilities and fold seven of them into a
// small bit mask; 0 when there is no driver or the query fails.
int FUN_004a4620()
{
    if (DAT_008A0094 == 0)
        return 0;
    DDrawCaps_004A4620 caps;
    memset(&caps, 0, sizeof(caps));
    caps.dwSize = 0x13C;
    long hr = DAT_008A0094->lpVtbl->GetCaps(DAT_008A0094, &caps, 0);
    if (hr != 0)
    {
        if (DAT_008A00B0 != 0)
        {
            DAT_008A00B0(hr);
            return 0;
        }
        char text[0x50];
        sprintf(text, STR_0081FC7C, hr);
        MessageBoxA(DAT_00B73550, text, STR_0081FC70, 0x30);
        return 0;
    }
    int mask = 0;
    if (caps.dwCaps & 0x40)
        mask = 1;
    if (caps.dwCaps & 0x80)
        mask |= 2;
    if (caps.dwCaps & 0x10000)
        mask |= 4;
    if (caps.dwCaps & 0x8000000)
        mask |= 8;
    if (caps.dwCaps & 0x4000000)
        mask |= 0x10;
    if (caps.dwCaps & 0x2000000)
        mask |= 0x20;
    if (caps.dwCaps & 0x200)
        mask |= 0x40;
    return mask;
}

// FUNCTION: GAMEMD 0x4A4700
//
// Wait for the vertical blank while the wait is still supported. A driver that
// reports it unimplemented turns the wait off; any other failure is reported
// through the error callback or a message box.
void FUN_004a4700()
{
    if (DAT_0081FC6C)
    {
        long hr = DAT_008A0094->lpVtbl->WaitForVerticalBlank(DAT_008A0094, 1, 0);
        if (hr == 0x80004001L)
        {
            DAT_0081FC6C = false;
            return;
        }
        if (hr != 0)
        {
            if (DAT_008A00B0 != 0)
            {
                DAT_008A00B0(hr);
                return;
            }
            char text[0x50];
            sprintf(text, STR_0081FC7C, hr);
            MessageBoxA(DAT_00B73550, text, STR_0081FC70, 0x30);
        }
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x81FC6C
bool DAT_0081FC6C = true;
// GLOBAL: GAMEMD 0x81FC70
extern const char STR_0081FC70[] = "Direct X";
// GLOBAL: GAMEMD 0x81FC7C
extern const char STR_0081FC7C[] = "DDRAW.DLL Error code = %08X";
// GLOBAL: GAMEMD 0x81FC98
extern const char STR_0081FC98[] = "Direct Draw operation processed without error";
// GLOBAL: GAMEMD 0x81FCC8
extern const char STR_0081FCC8[] = "Note";
// GLOBAL: GAMEMD 0x8A0094
IDDrawRelease_004A40C0* DAT_008A0094;
// END defined globals
