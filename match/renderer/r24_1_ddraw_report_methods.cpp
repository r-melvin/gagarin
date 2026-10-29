// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below. The
//   error callback (ECX = HRESULT) and the message box strings are the same
//   ones match/renderer/ddraw_set_mode_methods.cpp reports through.
//
// Ordered ascending by retail address.

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

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
        void* unknown_30[8];
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
GG_STATIC_ASSERT(offsetof(IDDrawRelease_004A40C0::Vtbl, SetCooperativeLevel) == 0x50);
GG_STATIC_ASSERT(offsetof(IDDrawRelease_004A40C0::Vtbl, WaitForVerticalBlank) == 0x58);

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

// The driver capability block: size word, the capability flags, then the rest.
struct DDrawCaps_004A4620
{
    unsigned long dwSize;           // +0x0000
    unsigned long dwCaps;           // +0x0004
    char          unknown_08[0x13C - 8];
};
GG_STATIC_ASSERT(sizeof(DDrawCaps_004A4620) == 0x13C);

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
// END defined globals
