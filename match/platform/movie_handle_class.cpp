// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against the user's retail gamemd.exe v1.001 (Ghidra CLI
//   disassembly from each entry) in the retail block 0x5BF850..0x5C0A6C:
//   the VQ/Bink movie handles and the movie state helpers that sit beside
//   them. Names are the RTTI class names; members and slots are placeholders.
// /Ob2: retail's deleting destructors (0x5C09B0, 0x5C0A30) expand the
// out-of-line destructors (0x5C0490, 0x5C0600, 0x5C0630) in place, which cl
// only does for a non-inline body under automatic inlining.
#include <windows.h>
#include <string.h>
#include "movie_handle_class.h"
#include "ccfile_class.h"

// The draw surface the current VQ state block renders to (+0x08). Only the
// slots the movie code calls are named.
struct Surface_005BF850
{
    virtual void vt_00(); virtual void vt_04(); virtual void vt_08(); virtual void vt_0C();
    virtual void vt_10(); virtual void vt_14(); virtual void vt_18(); virtual void vt_1C();
    virtual void vt_20(); virtual void vt_24(); virtual void vt_28(); virtual void vt_2C();
    virtual void vt_30(); virtual void vt_34(); virtual void vt_38(); virtual void vt_3C();
    virtual void vt_40(); virtual void vt_44(); virtual void vt_48(); virtual void vt_4C();
    virtual void vt_50(); virtual void vt_54(); virtual void vt_58();
    virtual int  vt_5C(Point2D a);
    virtual void vt_60();
    virtual void vt_64(); virtual void vt_68(); virtual void vt_6C();
    virtual int  vt_70();
    virtual int  vt_74(int a);
    virtual void vt_78(); virtual void vt_7C();
    virtual int  vt_80(Point2D at);
};

// GLOBAL: GAMEMD 0xABF3F4 -- the VQ state block being shown, or null.
extern Obj_005C01A0* DAT_00ABF3F4;
// GLOBAL: GAMEMD 0xABF3F8 -- the movie handle being played, or null.
extern MovieHandle* DAT_00ABF3F8;

// The screen surfaces the VQ frames are copied to (0x88730C, 0x887308).
struct Surface_005BF950
{
    virtual void vt_00(); virtual void vt_04();
    virtual bool vt_08(RectangleStruct* dst, void* src, RectangleStruct* srcRect, bool a, bool b);
    virtual void vt_0C(); virtual void vt_10(); virtual void vt_14();
    virtual void vt_18(int a);
    virtual void vt_1C();
    virtual void vt_20(); virtual void vt_24(); virtual void vt_28(); virtual void vt_2C();
    virtual void vt_30(); virtual void vt_34(); virtual void vt_38(); virtual void vt_3C();
    virtual void vt_40(); virtual void vt_44(); virtual void vt_48(); virtual void vt_4C();
    virtual void vt_50(); virtual void vt_54(); virtual void vt_58(); virtual void vt_5C();
    virtual void vt_60(); virtual void vt_64(); virtual void vt_68(); virtual void vt_6C();
    virtual void vt_70(); virtual void vt_74();
    virtual RectangleStruct vt_78();
    virtual int vt_7C();
    virtual int vt_80();
};

// GLOBAL: GAMEMD 0x88730C
extern Surface_005BF950* DAT_0088730C;
// GLOBAL: GAMEMD 0x887308
extern Surface_005BF950* DAT_00887308;
// GLOBAL: GAMEMD 0x887310
extern Surface_005BF950* DAT_00887310;
// GLOBAL: GAMEMD 0xB73550 -- the main window.
extern HWND DAT_00B73550;

// FUNCTION: GAMEMD 0x75A810 (decl; reloc)
bool FUN_0075A810(int key);
// FUNCTION: GAMEMD 0x4F4780 (decl; reloc)
void FUN_004F4780(bool a, void* surface, int b);

// FUNCTION: GAMEMD 0x5BFF60 (decl; reloc)
void FUN_005BFF60(Obj_005C01A0* data, bool a, int b, int c);

// FUNCTION: GAMEMD 0x5BF850
// PARTIAL (86.7%): slot 0x80 takes the rectangle's top-left as a by-value
// point, like slot 0x5C (same two pushes as two ints; 84.4% written that way).
// Remaining: retail loads the surface vptr after the two rectangle fields and
// the player; VC6 loads it first. Tried: nested calls (37.8% with the origin
// as two ints, 15.6%), split statements, a held state-block pointer (84.4%).
int FUN_005BF850()
{
    Surface_005BF850* surface = (Surface_005BF850*)DAT_00ABF3F4->unknown_08;
    Point2D origin;
    origin.X = 0;
    origin.Y = 0;
    int result = surface->vt_5C(origin);
    Obj_00759510* player = DAT_00ABF3F4->Player;
    Point2D at;
    at.X = DAT_00ABF3F4->unknown_24.X;
    at.Y = DAT_00ABF3F4->unknown_24.Y;
    int offset = surface->vt_80(at);
    offset = surface->vt_74(offset);
    int pitch = surface->vt_70();
    player->FUN_00759EB0(0, offset / pitch);
    return result;
}

// FUNCTION: GAMEMD 0x5BF8B0
void FUN_005BF8B0()
{
    ((Surface_005BF850*)DAT_00ABF3F4->unknown_08)->vt_60();
}

// FUNCTION: GAMEMD 0x5BF950
// Frame callback: copy the VQ frame to the screen surface, overlay the
// helper's surface centred at the bottom, then present it in the window.
// PARTIAL (9.3%): one attempt; retail saves EBX/ESI/EDI after the key check
// and keeps a different register assignment throughout.
void FUN_005BF950()
{
    if (FUN_0075A810(0xF))
        return;
    DAT_0088730C->vt_08(&DAT_00ABF3F4->unknown_24, DAT_00ABF3F4->unknown_08,
                        &DAT_00ABF3F4->unknown_24, false, true);
    Obj_006C9AE0* overlay = DAT_00ABF3F4->unknown_48;
    if (overlay != 0 && overlay->unknown_00 != 0) {
        Surface_005BF950* source = (Surface_005BF950*)overlay->unknown_10;
        RectangleStruct from = source->vt_78();
        RectangleStruct to;
        to.X = (DAT_0088730C->vt_7C() - from.Width) / 2;
        to.Y = DAT_0088730C->vt_80() - from.Height;
        to.Width = from.Width;
        to.Height = from.Height;
        DAT_0088730C->vt_08(&to, source, &from, true, true);
    }
    RECT client;
    GetClientRect(DAT_00B73550, &client);
    ClientToScreen(DAT_00B73550, (POINT*)&client);
    RectangleStruct screen;
    screen.X = DAT_00ABF3F4->unknown_34.X + client.left;
    screen.Y = DAT_00ABF3F4->unknown_34.Y + client.top;
    screen.Width = DAT_00ABF3F4->unknown_34.Width;
    screen.Height = DAT_00ABF3F4->unknown_34.Height;
    DAT_00887308->vt_08(&screen, DAT_0088730C, &DAT_00ABF3F4->unknown_24, false, true);
}

// FUNCTION: GAMEMD 0x5BFF00
void FUN_005BFF00(Obj_005C01A0* data)
{
    Release_005BFF00(data);
}

// FUNCTION: GAMEMD 0x5C01A0
Obj_005C01A0::Obj_005C01A0()
{
    Player = 0;
    unknown_04 = -1;
    unknown_08 = 0;
    unknown_0C = 0;
    unknown_10 = 0;
    unknown_14 = 0;
    unknown_18 = 0;
    unknown_1C = 1;
    unknown_20 = 0;
    unknown_24.X = 0;
    unknown_24.Y = 0;
    unknown_24.Width = 0;
    unknown_24.Height = 0;
    unknown_34.X = 0;
    unknown_34.Y = 0;
    unknown_34.Width = 0;
    unknown_34.Height = 0;
    unknown_44 = false;
    unknown_45 = false;
    unknown_48 = 0;
}

// FUNCTION: GAMEMD 0x5C01F0
Obj_005C01A0::~Obj_005C01A0()
{
    if (Player != 0) {
        Player->FUN_00759E60();
        delete Player;
    }
    if (unknown_48 != 0) {
        delete unknown_48;
        unknown_48 = 0;
    }
}

// FUNCTION: GAMEMD 0x5C0240
// PARTIAL (87.5%): retail stores the +0x14 flag ahead of the vptr; cl puts
// the vptr first. Tried: flag first in the body (best), both in the
// mem-initialiser list (81.2%), Data first then flag (81.2%).
VQMovieHandle::VQMovieHandle(Obj_005C01A0* data)
{
    unknown_14 = false;
    Data = data;
    unknown_08 = data->Player->FUN_00759F70();
    unknown_0C = Data->Player->FUN_00759F80();
}

// FUNCTION: GAMEMD 0x5C0280
void VQMovieHandle::vt_entry_0C(bool a)
{
    if (a) {
        if (Data != 0 && Data->Player != 0)
            Data->Player->FUN_00759E10();
    } else {
        if (Data != 0 && Data->Player != 0)
            Data->Player->FUN_00759E50();
    }
}

// FUNCTION: GAMEMD 0x5C02C0
void VQMovieHandle::vt_entry_10()
{
    DAT_00ABF3F8 = this;
    FUN_005BFF60(Data, true, -1, 0);
    DAT_00ABF3F8 = 0;
}

// FUNCTION: GAMEMD 0x5C02E0
bool VQMovieHandle::vt_entry_14()
{
    return unknown_14;
}

// FUNCTION: GAMEMD 0x5C02F0
bool VQMovieHandle::vt_entry_04()
{
    Obj_005C01A0* data = Data;
    if (!data->Player->unknown_550 && data->unknown_45 && DAT_00ABF3F4 == 0) {
        DAT_00ABF3F4 = data;
        bool result = data->Player->FUN_00759C30(&unknown_14);
        DAT_00ABF3F4 = 0;
        return result;
    }
    return false;
}

// FUNCTION: GAMEMD 0x5C0330
void VQMovieHandle::vt_entry_08()
{
}

// FUNCTION: GAMEMD 0x5C0340
void VQMovieHandle::vt_entry_18(int a, int b)
{
    Data->unknown_24.X = a;
    Data->unknown_24.Y = b;
    Data->unknown_34 = Data->unknown_24;
}

// FUNCTION: GAMEMD 0x5C0380
void VQMovieHandle::vt_entry_20(void* a)
{
    Data->unknown_48->FUN_006C9D30(a);
}

// FUNCTION: GAMEMD 0x5C03A0
void VQMovieHandle::vt_entry_1C(int a)
{
    Data->Player->FUN_00759E80();
    Data->Player->FUN_007598D0(a);
}

// FUNCTION: GAMEMD 0x5C03C0
int VQMovieHandle::vt_entry_24()
{
    return 0x21;
}

// FUNCTION: GAMEMD 0x5C03D0
// Present the current VQ frame straight from its own surface.
// PARTIAL (29.3%): retail's frame is 0x20 with the screen point read four
// bytes into the client rectangle, and EBX/ESI/EDI are saved after the key
// check. Tried: the point written over the rectangle (best), a separate
// POINT (27.6%), the rectangle in its own scope (27.6%).
void VQMovieHandle::vt_entry_28()
{
    if (DAT_00ABF3F4 != 0) {
        DAT_00887310->vt_18(0);
        FUN_004F4780(false, DAT_00887310, 0);
        if (!FUN_0075A810(0xF)) {
            RECT client;
            GetClientRect(DAT_00B73550, &client);
            ClientToScreen(DAT_00B73550, (POINT*)&client);
            RectangleStruct screen;
            screen.X = DAT_00ABF3F4->unknown_34.X + client.left;
            screen.Y = DAT_00ABF3F4->unknown_34.Y + client.top;
            screen.Width = DAT_00ABF3F4->unknown_34.Width;
            screen.Height = DAT_00ABF3F4->unknown_34.Height;
            DAT_00887308->vt_08(&screen, DAT_00ABF3F4->unknown_08,
                                &DAT_00ABF3F4->unknown_24, false, true);
        }
    }
}

// FUNCTION: GAMEMD 0x5C0490
VQMovieHandle::~VQMovieHandle()
{
    Release_005BFF00(Data);
}

// FUNCTION: GAMEMD 0x5C0510
BinkMovieHandle::BinkMovieHandle(Obj_00432700* player)
{
    Player = player;
    if (player != 0) {
        unknown_08 = player->Info->unknown_00;
        unknown_0C = player->Info->unknown_04;
    }
}

// FUNCTION: GAMEMD 0x5C0540
void BinkMovieHandle::vt_entry_0C(bool a)
{
    Player->FUN_00432C30(a);
}

// FUNCTION: GAMEMD 0x5C0550
void BinkMovieHandle::vt_entry_10()
{
    DAT_00ABF3F8 = this;
    Player->FUN_00432C70();
    DAT_00ABF3F8 = 0;
}

// FUNCTION: GAMEMD 0x5C0570
bool BinkMovieHandle::vt_entry_14()
{
    return Player->FUN_00432C50();
}

// FUNCTION: GAMEMD 0x5C0580
bool BinkMovieHandle::vt_entry_04()
{
    return Player->FUN_00433040();
}

// FUNCTION: GAMEMD 0x5C0590
void BinkMovieHandle::vt_entry_08()
{
    Player->FUN_00433020();
}

// FUNCTION: GAMEMD 0x5C05A0
void BinkMovieHandle::vt_entry_18(int a, int b)
{
    Player->FUN_00432AB0(a, b);
}

// FUNCTION: GAMEMD 0x5C05C0
void BinkMovieHandle::vt_entry_20(void* a)
{
    Player->FUN_00432C10(a);
}

// FUNCTION: GAMEMD 0x5C05D0
void BinkMovieHandle::vt_entry_1C(int a)
{
    Player->FUN_00432BD0(a);
}

// FUNCTION: GAMEMD 0x5C05E0
int BinkMovieHandle::vt_entry_24()
{
    return Player->FUN_00432BF0();
}

// FUNCTION: GAMEMD 0x5C05F0
void BinkMovieHandle::vt_entry_28()
{
    Player->FUN_00433060();
}

// FUNCTION: GAMEMD 0x5C0600
BinkMovieHandle::~BinkMovieHandle()
{
    delete Player;
}

// FUNCTION: GAMEMD 0x5C0630
MovieHandle::~MovieHandle()
{
}

// LIBRARY: GAMEMD 0x7C8D20 -- _stricmp.
extern "C" int __cdecl _stricmp(const char* a, const char* b);
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- printf-style log sink.
void __cdecl FUN_004068E0(const char* format, ...);

// The options object at 0xA8EB60; 0x5FBF80 is handed the bare movie name.
#include "../_layout/obj_005fbf80.h"
// GLOBAL: GAMEMD 0xA8EB60
extern Obj_005FBF80 DAT_00A8EB60;

// The surface slot 0x5C07D0 reads its default rectangle from.
struct Surface_005C07D0
{
    virtual void vt_00(); virtual void vt_04(); virtual void vt_08(); virtual void vt_0C();
    virtual void vt_10(); virtual void vt_14(); virtual void vt_18(); virtual void vt_1C();
    virtual void vt_20(); virtual void vt_24(); virtual void vt_28(); virtual void vt_2C();
    virtual void vt_30(); virtual void vt_34(); virtual void vt_38(); virtual void vt_3C();
    virtual void vt_40(); virtual void vt_44(); virtual void vt_48(); virtual void vt_4C();
    virtual void vt_50(); virtual void vt_54(); virtual void vt_58(); virtual void vt_5C();
    virtual void vt_60(); virtual void vt_64(); virtual void vt_68(); virtual void vt_6C();
    virtual void vt_70(); virtual void vt_74();
    virtual RectangleStruct vt_78();
};

// FUNCTION: GAMEMD 0x5BFAA0 (decl; reloc)
Obj_005C01A0* FUN_005BFAA0(const char* name, Surface_005C07D0* surface,
                           RectangleStruct a, RectangleStruct b, int c, int d);

// FUNCTION: GAMEMD 0x5C0640
// PARTIAL (71.8%): the .VQA strcpy is scheduled differently. Tried: nested
// ifs (45.1%), one || condition (38.3%), a found flag (best, both forms).
// Strip the extension, tell the options object the bare name, then look for
// NAME.BIK and then NAME.VQA; copy the one found to `out` when given.
bool FUN_005C0640(const char* name, char* out, int unused)
{
    char buffer[200];
    strcpy(buffer, name);
    char* ext = buffer;
    while (*ext != 0 && *ext != '.')
        ext++;
    *ext = 0;
    DAT_00A8EB60.FUN_005FBF80(buffer);
    strcpy(ext, ".BIK");
    bool found = CCFileClass(buffer).Exists(false);
    if (!found) {
        strcpy(ext, ".VQA");
        found = CCFileClass(buffer).Exists(false);
    }
    if (!found)
        return false;
    if (out != 0)
        strcpy(out, buffer);
    return true;
}

// FUNCTION: GAMEMD 0x5C07D0
// PARTIAL (98.6%): only the inlined VQMovieHandle constructor's flag/vptr
// store order differs (see 0x5C0240).
// Open a movie by name on a surface: a Bink handle for .bik files, otherwise
// a VQ handle over a freshly loaded state block.
MovieHandle* FUN_005C07D0(const char* name, Surface_005C07D0* surface, RectangleStruct* rect)
{
    char buffer[200];
    if (surface == 0 || !FUN_005C0640(name, buffer, true))
        return 0;
    RectangleStruct area;
    if (rect != 0)
        area = *rect;
    else
        area = surface->vt_78();
    char* ext = strrchr(buffer, '.');
    if (ext != 0 && _stricmp(ext, ".bik") == 0) {
        FUN_004068E0("Play_Movie() as Bink!\n");
        Obj_00432700* player = new Obj_00432700(buffer, surface);
        return new BinkMovieHandle(player);
    }
    RectangleStruct none;
    none.X = 0;
    none.Y = 0;
    none.Width = 0;
    none.Height = 0;
    Obj_005C01A0* data = FUN_005BFAA0(buffer, surface, none, area, 0xFF, 0);
    if (data == 0)
        return 0;
    return new VQMovieHandle(data);
}

// FUNCTION: GAMEMD 0x5C0980
int FUN_005C0980()
{
    return DAT_00ABF3F4 != 0 || DAT_00ABF3F8 != 0;
}

// FUNCTION: GAMEMD 0x5C09A0
void FUN_005C09A0()
{
    if (DAT_00ABF3F8 != 0)
        DAT_00ABF3F8->vt_entry_28();
}

// SYNTHETIC: GAMEMD 0x5C09B0
// VQMovieHandle::`scalar deleting destructor'

// SYNTHETIC: GAMEMD 0x5C0A30
// BinkMovieHandle::`scalar deleting destructor'

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xABF3F8
MovieHandle* DAT_00ABF3F8;
// GLOBAL: GAMEMD 0xA8EB60
Obj_005FBF80 DAT_00A8EB60;
// GLOBAL: GAMEMD 0xABF3F4
Obj_005C01A0* DAT_00ABF3F4;
// END defined globals
