// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Small leaf routines read off retail gamemd.exe v1.001 with the local Ghidra CLI.

#include "../ui/input_controls/mouse_ww_mouse_class.h"
#include "../_layout/rgb_class.h"
#include "../network/transport/winsock_interface_class.h"

// GLOBAL: GAMEMD 0xA8E960
extern unsigned char DAT_00A8E960;

// FUNCTION: GAMEMD 0x5BED40 (decl; reloc) - plays a movie by name.
void Play_Movie(const char* name, int x, int a, int b, int c, int d);
// FUNCTION: GAMEMD 0x52FEC0 (decl; reloc)
void FUN_0052FEC0(void* a, unsigned char b);
// FUNCTION: GAMEMD 0x48D080 (decl; reloc)
void FUN_0048D080();

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) - the engine's square root, __cdecl, double in and out.
extern "C" double __cdecl FUN_004CAC40(double value);

// FUNCTION: GAMEMD 0x50B920
// Rescale a colour triple held as three doubles so that its length is 240, clamping each channel
// at 255. A zero-length colour becomes (255, 255, 255).
void __fastcall FUN_0050B920(double* r, double* g, double* b)
{
    double length = FUN_004CAC40(*g * *g + *b * *b + *r * *r);
    if (length == 0.0) {
        *b = 255.0;
        *g = 255.0;
        *r = 255.0;
        return;
    }
    *r = *r * 240.0 / length;
    if (*r > 255.0) {
        *r = 255.0;
    }
    *g = *g * 240.0 / length;
    if (*g > 255.0) {
        *g = 255.0;
    }
    *b = *b * 240.0 / length;
    if (*b > 255.0) {
        *b = 255.0;
    }
}

// FUNCTION: GAMEMD 0x52CB50
// When bit 2 of the option byte is set, play the 0x82618C movie, then run the
// 0x52FEC0 step with (0, 1) and tail into the 0x48D080 callback.
void FUN_0052CB50()
{
    if (DAT_00A8E960 & 4)
        Play_Movie("A00_F00E", -1, 1, 1, 1, 0);
    FUN_0052FEC0(0, 1);
    FUN_0048D080();
}


// GLOBAL: GAMEMD 0x88730C -- the primary surface.
extern MouseSurfaceView* DAT_0088730C;
// GLOBAL: GAMEMD 0x8A00A0
extern bool DAT_008A00A0;
// GLOBAL: GAMEMD 0x886080 -- the 256-entry colour table.
extern RGBClass DAT_00886080[256];

// FUNCTION: GAMEMD 0x4F4780 (decl; reloc)
void __fastcall FUN_004F4780(bool value, void* surface, int unused);
// FUNCTION: GAMEMD 0x778210 (decl; reloc) - loads the named picture onto the surface with a palette.
void __fastcall FUN_00778210(const char* name, MouseSurfaceView* surface, RGBClass* palette);

// FUNCTION: GAMEMD 0x52FF90
// Clear the primary surface, load the named picture onto it with the default colour table and,
// when asked, refresh the display.
void __fastcall FUN_0052FF90(const char* name, bool refresh)
{
    DAT_0088730C->vf_06(0);
    FUN_00778210(name, DAT_0088730C, DAT_00886080);
    if (refresh) {
        FUN_004F4780(true, DAT_0088730C, 0);
    }
}

// FUNCTION: GAMEMD 0x52FFD0
// Clear the primary surface and, when asked, refresh the display.
void __fastcall FUN_0052FFD0(bool refresh)
{
    DAT_0088730C->vf_06(0);
    if (refresh) {
        FUN_004F4780(true, DAT_0088730C, 0);
    }
}

// FUNCTION: GAMEMD 0x532100
// When the pending flag is set (or forced), clear it, run the 0x52FEC0 step with (0, 1) and
// refresh the display with the "off" value.
void __fastcall FUN_00532100(bool force)
{
    if (DAT_008A00A0 || force) {
        DAT_008A00A0 = false;
        FUN_0052FEC0(0, 1);
        FUN_004F4780(false, DAT_0088730C, 0);
    }
}

// GLOBAL: GAMEMD 0xA8EBB4
extern int DAT_00A8EBB4;
// GLOBAL: GAMEMD 0xAA05A8
extern int DAT_00AA05A8;

// FUNCTION: GAMEMD 0x53F5F0
// Hand the network interface the configured value, then open it on the given socket number
// and remember whether that worked.
void __fastcall FUN_0053F5F0(int socketNumber)
{
    Interface_00887628->Slot20(DAT_00A8EBB4);
    DAT_00AA05A8 = Interface_00887628->Init(socketNumber & 0xFFFF);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x8A00A0
bool DAT_008A00A0;
// GLOBAL: GAMEMD 0xA8EBB4
int DAT_00A8EBB4;
// GLOBAL: GAMEMD 0xAA05A8
int DAT_00AA05A8;
// END defined globals
