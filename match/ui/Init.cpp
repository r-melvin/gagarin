// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit Init.CPP. The name is the source-file string at 0x825fb8
//   in retail gamemd.exe v1.001, passed by the assert at 0x52c52d inside this object's
//   code range (0x52b7c0-0x53910f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Six key/value-vector Grow instances, ordered ascending by retail address.
//
// Grow the vector by `extra` slots: allocate, copy the live elements across
// field by field, free the old block, and invalidate the cached lookup slot. A
// negative request and a failed allocation both report false without touching
// anything.
//
// The phrasing is the one already driven to 100% at 0x41C500 and is reproduced
// unchanged. The two details that matter are recorded there and hold here: the
// allocation is `new GrowPair[total]`, whose elided vector-constructor-iterator
// setup is retail's `DEC`/spill pair after the null check, and the copy is a
// whole-struct assignment through an explicit byte offset, which is what moves
// the pair as two dwords sharing one address computation and keeps the index a
// plain register. Count and Items are re-read every iteration rather than
// hoisted.
//
// The seven vtable-seating base destructors, ordered ascending by address.
//
//   addresses below). Names cross-checked against YRpp
//   (every offset/slot reconfirmed here).
//
//                                                        ECX=name, DL=forceCache)
//
//   Read off retail gamemd.exe v1.001 at 0x538D40 (no arguments, plain RET):
//   the source palette pointer in the dword at 0xA8F918 read three bytes per
//   colour, the 256x256 byte table at 0xA8F91C filled row by row (row pointer
//   compared with 0xA9F91C), the 500000 (0x7A120) starting distance and the
//   byte at 0xA9F91C cleared on exit.
//
// CommandClass and its keyboard-command subclasses: every slot body between
// 0x535BD0 and 0x5384BD, in retail address order. The classes are declared in
// command_class.h.
//
// The deleting destructors share one 32-byte shape:
//
//     MOV AL,[ESP+4]; PUSH ESI; MOV ESI,ECX; TEST AL,1; MOV [ESI],<vtable>
//     JZ +9; PUSH ESI; CALL 0x7C8B3D; ADD ESP,4; MOV EAX,ESI; POP ESI; RET 4
//
// The text slots pass the __FILE__/__LINE__ pair of the original source to the
// string-table loader (0x734E60, __fastcall: label in ECX, null in EDX, file
// and line pushed); the line numbers are the retail immediates.

#include "../core/empty_function_family_methods.h"
#include "../_layout/session_class.h"

#include "../core/pair_vector_grow_sweep.h"

#include "../core/seat_vtable_tail_dtor_sweep.h"

#include "../core/trivial_tu102_methods.h"

#include "../platform/mix_file_class.h"
#include "../_layout/memory_buffer.h"
#include <stdio.h>   // sprintf
#include <string.h>  // strcpy, _strlwr, strstr

// LIBRARY: GAMEMD 0x007C8E17
// FUN_007C8E17
extern "C" void* __cdecl FUN_007C8E17(unsigned int size);

// GLOBAL: GAMEMD 0xA8F918
extern unsigned char* DAT_00A8F918;
// GLOBAL: GAMEMD 0xA8F91C
extern unsigned char DAT_00A8F91C[256][256];
// GLOBAL: GAMEMD 0xA9F91C
extern unsigned char DAT_00A9F91C;

#include "command_class.h"
#include "../core/vector_class_operations.h"
#include "input_controls/ui_display_chain.h"
#include "input_controls/display_command.h"
#include "../platform/ccfile_class.h"

// The source-file string every text load passes (0x825FB8).
#define INIT_CPP "D:\\ra2mdpost\\Init.CPP"

// SYNTHETIC: GAMEMD 0x535CD0 -- CreateTeamCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x535D00 -- CommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x536090 -- SelectTeamCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x536180 -- AddTeamCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x536270 -- CenterTeamCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x536580 -- TauntCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x537FA0 -- MultiplayerDebugCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x537FC0 -- MultiplayerSyncCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x537FE0 -- FollowCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538000 -- View1CommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538020 -- View2CommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538040 -- View3CommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538060 -- View4CommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538080 -- SetView1CommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x5380A0 -- SetView2CommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x5380C0 -- SetView3CommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x5380E0 -- SetView4CommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538100 -- OptionsCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538120 -- SidebarUpCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538140 -- SidebarDownCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538160 -- CenterREventCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538180 -- BeaconPlacementCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x5381A0 -- ToggleSellCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x5381C0 -- ToggleRepairCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x5381E0 -- AllianceCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538200 -- CenterBaseCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538220 -- CenterViewCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538240 -- ScatterCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538260 -- GuardCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538280 -- StopCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x5382A0 -- AllToCheerCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x5382C0 -- DeployCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x5382E0 -- PrevObjectCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538300 -- NextObjectCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538320 -- PlanningModeCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538340 -- CombatantSelectCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538360 -- TypeSelectCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538380 -- HealthNavCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x5383A0 -- VeterancyNavCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x5383C0 -- SetStructureTabCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x5383E0 -- SetDefenseTabCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538400 -- SetUnitTabCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538420 -- SetInfantryTabCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538440 -- ScreenCaptureCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538460 -- PageUserCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x538480 -- CursorPositionCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// SYNTHETIC: GAMEMD 0x5384A0 -- DeleteCommandClass scalar deleting destructor, emitted by the compiler from the virtual destructor
// FUNCTION: GAMEMD 0x734E60 (decl; reloc)
wchar_t* StringTable_LoadString(const char* label, int* out,
                                const char* file, int line);

// LIBRARY: GAMEMD 0x7C8EF4 -- CRT sprintf.
extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);
// LIBRARY: GAMEMD 0x7CA564 -- CRT swprintf.
extern "C" int __cdecl swprintf(wchar_t* buffer, const wchar_t* format, ...);

// GLOBAL: GAMEMD 0xA8F5B4 -- the shared narrow name buffer of the team commands.
extern char DAT_00A8F5B4[];
// GLOBAL: GAMEMD 0xA8F654 -- the shared wide text buffer of the team commands.
extern wchar_t DAT_00A8F654[];
// GLOBAL: GAMEMD 0xA8B8B4
extern bool DAT_00A8B8B4;
// GLOBAL: GAMEMD 0xA8B8B5
extern bool DAT_00A8B8B5;
// GLOBAL: GAMEMD 0xB04880
extern bool DAT_00B04880;
// GLOBAL: GAMEMD 0xA8F7D8
extern bool DAT_00A8F7D8;
// GLOBAL: GAMEMD 0xA8F2F8
extern char DAT_00A8F2F8[];

// The message list at 0xA8BC60 (used as an immediate `this`).
struct CommandMessageList
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x5D3BA0 (decl; reloc) -- seven stacked arguments.
    void FUN_005D3BA0(int a1, int a2, const wchar_t* text, int a4, int a5, int a6, int a7);
};
// GLOBAL: GAMEMD 0xA8BC60
extern CommandMessageList DAT_00A8BC60;

// The scenario object (pointer global 0xA8B230): the four stored view cells.
struct CommandScenario
{
    char unknown_0000[0x348E];        // +0x0000
    CellStruct Views[4];              // +0x348E
};
GG_STATIC_ASSERT(offsetof(CommandScenario, Views) == 0x348E);
// GLOBAL: GAMEMD 0xA8B230
extern CommandScenario* DAT_00A8B230;

// FUNCTION: GAMEMD 0x647040 (decl; reloc)
void FUN_00647040();

// FUNCTION: GAMEMD 0x6470F0 (decl; reloc)
void FUN_006470F0();

// FUNCTION: GAMEMD 0x730AF0 (decl; reloc)
void FUN_00730AF0();

// FUNCTION: GAMEMD 0x730D60 (decl; reloc)
void FUN_00730D60();

// FUNCTION: GAMEMD 0x730EA0 (decl; reloc)
void FUN_00730EA0();

// FUNCTION: GAMEMD 0x730F30 (decl; reloc)
void FUN_00730F30();

// FUNCTION: GAMEMD 0x730FE0 (decl; reloc)
void FUN_00730FE0();

// FUNCTION: GAMEMD 0x731060 (decl; reloc)
void FUN_00731060(int team);

// FUNCTION: GAMEMD 0x7311C0 (decl; reloc)
void FUN_007311C0(int team);

// FUNCTION: GAMEMD 0x7313A0 (decl; reloc)
void FUN_007313A0(int team);

// FUNCTION: GAMEMD 0x7314C0 (decl; reloc)
void FUN_007314C0(int team);

// FUNCTION: GAMEMD 0x7315A0 (decl; reloc)
void FUN_007315A0();

// FUNCTION: GAMEMD 0x7318F0 (decl; reloc)
void FUN_007318F0();

// FUNCTION: GAMEMD 0x731A10 (decl; reloc)
void FUN_00731A10();

// FUNCTION: GAMEMD 0x731A30 (decl; reloc)
void FUN_00731A30();

// FUNCTION: GAMEMD 0x731A50 (decl; reloc)
void FUN_00731A50(bool flag);

// FUNCTION: GAMEMD 0x731A70 (decl; reloc)
void FUN_00731A70(bool flag);

// FUNCTION: GAMEMD 0x732280 (decl; reloc)
void FUN_00732280(bool flag);

// FUNCTION: GAMEMD 0x732CA0 (decl; reloc)
void FUN_00732CA0();

// FUNCTION: GAMEMD 0x732CC0 (decl; reloc)
void FUN_00732CC0();

// FUNCTION: GAMEMD 0x733380 (decl; reloc)
void FUN_00733380(bool flag);

// FUNCTION: GAMEMD 0x7336C0 (decl; reloc)
void FUN_007336C0(bool flag);

// FUNCTION: GAMEMD 0x734120 (decl; reloc)
void FUN_00734120();

// FUNCTION: GAMEMD 0x7342A0 (decl; reloc)
DisplayCmdObject* FUN_007342A0();

// FUNCTION: GAMEMD 0x7342B0 (decl; reloc)
DisplayCmdObject* FUN_007342B0();

// FUNCTION: GAMEMD 0x735120 (decl; reloc)
const wchar_t* FUN_00735120(const char* text);

// ---- Taunt support (0x536350) ----
#include "../network/command_packet_layouts.h"

// A session node (the list at 0xA8DA78): name source, colour byte +0x4B and
// the address block at +0x28.
struct CommandNode
{
    char unknown_00[0x28];               // +0x00
    char unknown_28[0x4B - 0x28];        // +0x28
    unsigned char unknown_4B;            // +0x4B
    // FUNCTION: GAMEMD 0x7350C0 (decl; reloc)
    const char* FUN_007350C0();
};
GG_STATIC_ASSERT(offsetof(CommandNode, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(CommandNode, unknown_4B) == 0x4B);
// GLOBAL: GAMEMD 0xA8DA78
extern CommandNode** DAT_00A8DA78;

struct CommandHouseType
{
    char unknown_000[0x1A5];             // +0x000
    bool unknown_1A5;                    // +0x1A5
};
GG_STATIC_ASSERT(offsetof(CommandHouseType, unknown_1A5) == 0x1A5);
struct CommandHouse
{
    char unknown_00000[0x34];            // +0x00000
    CommandHouseType* Type;              // +0x00034
    char unknown_00038[0x1602A - 0x38];  // +0x00038
    char unknown_1602A[1];               // +0x1602A
};
GG_STATIC_ASSERT(offsetof(CommandHouse, Type) == 0x34);
GG_STATIC_ASSERT(offsetof(CommandHouse, unknown_1602A) == 0x1602A);
// GLOBAL: GAMEMD 0xA8022C -- the house list's items.
extern CommandHouse** DAT_00A8022C;
// GLOBAL: GAMEMD 0xA80238 -- the house list's count.
extern int DAT_00A80238;

// The connection manager at 0xA8E9C0 (an immediate `this`).
struct CommandConnections
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x540F90 (decl; reloc)
    int FUN_00540F90();
    // FUNCTION: GAMEMD 0x540FA0 (decl; reloc)
    int FUN_00540FA0(int index);
    // FUNCTION: GAMEMD 0x540FC0 (decl; reloc)
    const char* FUN_00540FC0(int id);
    // FUNCTION: GAMEMD 0x541000 (decl; reloc)
    int FUN_00541000(int id);
    // FUNCTION: GAMEMD 0x5410F0 (decl; reloc)
    void FUN_005410F0(void* packet, int length, int a3, int address, int a5, int a6);
    // FUNCTION: GAMEMD 0x541820 (decl; reloc)
    void FUN_00541820();
};
// GLOBAL: GAMEMD 0xA8E9C0
extern CommandConnections DAT_00A8E9C0;
struct CommandRelay
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x663D60 (decl; reloc)
    bool FUN_00663D60(int id);
};
// GLOBAL: GAMEMD 0xB052D0
extern CommandRelay DAT_00B052D0;
struct CommandFrameSource
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x5DAC00 (decl; reloc)
    int FUN_005DAC00();
};
// GLOBAL: GAMEMD 0xA8D610
extern CommandFrameSource DAT_00A8D610;
// GLOBAL: GAMEMD 0xA8B538
extern int DAT_00A8B538;
// GLOBAL: GAMEMD 0x825C88 -- the last taunt time (-1 = never).
extern int DAT_00825C88;
// GLOBAL: GAMEMD 0xA8D110
extern bool DAT_00A8D110;
// GLOBAL: GAMEMD 0xA8D111
extern bool DAT_00A8D111;
// GLOBAL: GAMEMD 0xA8B394
extern int DAT_00A8B394;
// GLOBAL: GAMEMD 0xA8D108
extern bool DAT_00A8D108[];
// GLOBAL: GAMEMD 0xA8DBA0
extern bool DAT_00A8DBA0;

// FUNCTION: GAMEMD 0x752B70 (decl; reloc)
void FUN_00752B70();

// LIBRARY: GAMEMD 0x7C8D20 -- CRT _stricmp (0x7CA5D3 is the wide wcscmp: it compares words).
extern "C" int __cdecl _stricmp(const char* a, const char* b);
extern "C" char* __cdecl strcpy(char* dst, const char* src);

// Jump the tactical view to stored view `view` (the View1..4 commands): the
// cell's centre in leptons, its height from the map, then a redraw request
// when 0x880990 is set.
inline void CommandJumpToView(int view)
{
    DisplayCmdVec3 coord;
    coord.Set(DAT_00A8B230->Views[view].X * 256 + 128, DAT_00A8B230->Views[view].Y * 256 + 128, 0);
    coord.Z = DisplayCmdMap_0087F7E8.GetZPos_00578080(&coord);
    DisplayCmdTactical_00887324->FUN_006D6070(&coord);
    if (DisplayCmdValue_00880990) {
        CellStruct cell;
        Map_0087F7E8.FUN_004A91B0(&cell, DAT_00A8F2F8);
    }
}

// Store the tactical view's current cell as view `view` (SetView1..4).
inline void CommandStoreView(int view)
{
    Point2D where;
    {
        Point2D out;
        where = *DisplayCmdTactical_00887324->FUN_006D6190(&out);
    }
    {
        CellStruct cell;
        DAT_00A8B230->Views[view] = *DisplayCmdTactical_00887324->FUN_006D6590(&cell, &where);
    }
}

// The surfaces and the mouse ScreenCapture drives. Only the slots it calls are
// named; the rest pin their indices.
struct CaptureSurface
{
    virtual void vf_00();
    virtual void vf_04();
    virtual bool Blit(RectangleStruct* dest, CaptureSurface* source,
                      RectangleStruct* sourceRect, bool a, bool b);   // +0x08
    virtual void vf_0C();  virtual void vf_10();  virtual void vf_14();
    virtual void vf_18();  virtual void vf_1C();  virtual void vf_20();
    virtual void vf_24();  virtual void vf_28();  virtual void vf_2C();
    virtual void vf_30();  virtual void vf_34();  virtual void vf_38();
    virtual void vf_3C();  virtual void vf_40();  virtual void vf_44();
    virtual void vf_48();  virtual void vf_4C();  virtual void vf_50();
    virtual void vf_54();  virtual void vf_58();  virtual void vf_5C();
    virtual void vf_60();  virtual void vf_64();  virtual void vf_68();
    virtual void vf_6C();  virtual void vf_70();  virtual void vf_74();
    virtual void vf_78();
    virtual int GetWidth();    // +0x7C
    virtual int GetHeight();   // +0x80
};
struct CaptureMouse
{
    virtual void vf_00();
    virtual void vf_04();
    virtual void vf_08();
    virtual void HideCursor();   // +0x0C
    virtual void ShowCursor();   // +0x10
};
// GLOBAL: GAMEMD 0x88730C
extern CaptureSurface* DAT_0088730C;
// GLOBAL: GAMEMD 0x887308
extern CaptureSurface* DAT_00887308;
// GLOBAL: GAMEMD 0x887640
extern CaptureMouse* DAT_00887640;
// GLOBAL: GAMEMD 0xB73550 -- the main window.
extern HWND DAT_00B73550;
// GLOBAL: GAMEMD 0x885780 -- the palette written with the capture.
extern char DAT_00885780[];
// User32 imports through IAT slots 0x7E14C4 and 0x7E14B8.
// GetClientRect and ClientToScreen use their SDK declarations.

// FUNCTION: GAMEMD 0x7B05C0 (decl; reloc) -- write a surface to a PCX file;
// __fastcall: file in ECX, surface in EDX, palette pushed.
int FUN_007B05C0(FileClass* file, CaptureSurface* surface, void* palette);

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EB7F8
extern const double DAT_007EB7F8;
// GLOBAL: GAMEMD 0xA8F418
extern double DAT_00A8F418;
// GLOBAL: GAMEMD 0xA8F760
extern double DAT_00A8F760;
// GLOBAL: GAMEMD 0xA8F768
extern int DAT_00A8F768;
// GLOBAL: GAMEMD 0xA8F76C
extern int DAT_00A8F76C;
// GLOBAL: GAMEMD 0xA8F770
extern int DAT_00A8F770;
// GLOBAL: GAMEMD 0xA8F778
extern double DAT_00A8F778;

// FUNCTION: GAMEMD 0x0052CB80
void FUN_0052CB80()
{
}

// FUNCTION: GAMEMD 0x52D610
// Empty function.
void __cdecl FUN_0052D610()
{
}

// FUNCTION: GAMEMD 0x52D620
// Empty function.
void __cdecl FUN_0052D620()
{
}

// FUNCTION: GAMEMD 0x52D630
// Empty function.
void __cdecl FUN_0052D630()
{
}

// FUNCTION: GAMEMD 0x52F610
// Stores, then tail-calls.
void Obj_0052F610::FUN_0052F610()
{
    FUN_0075A790();
    FUN_0075A7D0(0);
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x5301A0   MixFileClass::Bootstrap
//
// Mount EXPANDMD99.MIX .. EXPANDMD00.MIX (any that exist) into the global Array,
// then the fixed set RA2MD / RA2 / CACHEMD / CACHE / LOCALMD / LOCAL, caching
// the CACHE* archives. Restores the file-search mode on success.
//
// Exact. Three levers, all structural:
//
//   * The scratch name buffer is `char name[64]`, and the stack probe is 0x24
//     bytes (`sizeof(RawFileClass) == 0x24`). Retail's frame is `SUB ESP,0x68`; with
//     the four callee-saved pushes live it addresses the probe as `[ESP+0x14]`
//     and the buffer as `[ESP+0x38]`, i.e. in-frame +0x04 and +0x28, so the
//     buffer runs +0x28..+0x68, exactly 0x40.
//   * The append is spelled as the free `DynamicVectorClass_Mix_AddItem(&v, x)`
//     rather than `v.AddItem(x)` (the inlined grow path's register order).
//   * The probe is a temporary, `RawFileClass(name).Exists(false)`, and 0x65CA00
//     is its destructor: retail calls Exists through the constructor's
//     returned `this` (`MOV EDX,[EAX]; MOV ECX,EAX`) and destroys the
//     temporary at the end of the full expression.
// ---------------------------------------------------------------------------
bool MixFileClass_Bootstrap()
{
    int saved = g_FileSearchMode;
    SetFileSearchMode(-2);

    for (int i = 99; i >= 0; --i)
    {
        char name[64];
        sprintf(name, "EXPANDMD%02d.MIX", i);

        char avail = RawFileClass(name).Exists(false);
        if (avail)
        {
            MixFileClass* mix = new MixFileClass(name);
            if (mix)
            {
                DynamicVectorClass_Mix_AddItem(&MixArray, mix);
                Log_4a4ac0(" %s", name);
            }
        }
    }

    // Nested success-chain: every failure falls through to the single shared
    // `return false` epilogue (matches retail's converged 0x5302E4 exit).
    g_RA2MD = new MixFileClass("RA2MD.MIX");
    if (g_RA2MD)
    {
        g_RA2 = new MixFileClass("RA2.MIX");
        if (g_RA2)
        {
            Log_4a4ac0(" CACHE.MIX");
            g_CACHEMD = new MixFileClass("CACHEMD.MIX");
            if (g_CACHEMD && MixCache("CACHEMD.MIX", 0))
            {
                Log_4a4ac0(" CACHE.MIX");
                g_CACHE = new MixFileClass("CACHE.MIX");
                if (g_CACHE && MixCache("CACHE.MIX", 0))
                {
                    Log_4a4ac0(" CACHE.MIX");
                    g_LOCALMD = new MixFileClass("LOCALMD.MIX");
                    if (g_LOCALMD)
                    {
                        g_LOCAL = new MixFileClass("LOCAL.MIX");
                        if (g_LOCAL)
                        {
                            Log_4a4ac0(" LOCAL.MIX");
                            SetFileSearchMode(saved);
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x00532130
void FUN_00532130()
{
}

// FUNCTION: GAMEMD 0x532140
// Empty function.
void __cdecl FUN_00532140()
{
}

// FUNCTION: GAMEMD 0x5355C0
// Calls other functions.
void FUN_005355C0(int a1, int a2)
{
    FUN_00721210(DAT_00A83D10, a2, DAT_008263A8);
}

// FUNCTION: GAMEMD 0x535A60
// VTABLE: GAMEMD 0x7E1668
void FUN_00535A60(SeatDtorObject* self)
{
    self->Vtbl = VTABLE_007E1668;
    FUN_00431B80(self);
}

// FUNCTION: GAMEMD 0x535BD0 -- CommandClass slot 5
bool CommandClass::vf_5(int key)
{
    return false;
}

// FUNCTION: GAMEMD 0x535BE0 -- CommandClass slot 6
bool CommandClass::vf_6(int key)
{
    return (key & 0x800) == 0;
}

// FUNCTION: GAMEMD 0x535BF0 -- CommandClass slot 7
bool CommandClass::vf_7(int key)
{
    return false;
}

// SYNTHETIC: GAMEMD 0x535C00 -- CreateTeamCommandClass constructor, defined inline in command_class.h; emitted out-of-line here

// FUNCTION: GAMEMD 0x535C20 -- CreateTeamCommandClass slot 1
const char* CreateTeamCommandClass::vf_1() const
{
    sprintf(DAT_00A8F5B4, "TeamCreate_%d", unknown_04);
    return DAT_00A8F5B4;
}

// FUNCTION: GAMEMD 0x535C40 -- CreateTeamCommandClass slot 2
const wchar_t* CreateTeamCommandClass::vf_2()
{
    swprintf(DAT_00A8F654, StringTable_LoadString("TXT_CREATE_TEAM", 0, INIT_CPP, 0x1815), unknown_04);
    return DAT_00A8F654;
}

// FUNCTION: GAMEMD 0x535C70 -- CreateTeamCommandClass slot 3
const wchar_t* CreateTeamCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_TEAM", 0, INIT_CPP, 0x1817);
}

// FUNCTION: GAMEMD 0x535C90 -- CreateTeamCommandClass slot 4
const wchar_t* CreateTeamCommandClass::vf_4()
{
    swprintf(DAT_00A8F654, StringTable_LoadString("TXT_CREATE_TEAM_DESC", 0, INIT_CPP, 0x1819), unknown_04);
    return DAT_00A8F654;
}

// FUNCTION: GAMEMD 0x535CC0 -- CreateTeamCommandClass slot 8
void CreateTeamCommandClass::vf_8(int key) const
{
    FUN_00731060(unknown_04);
}

// FUNCTION: GAMEMD 0x535CF0 -- CommandClass slot 2
const wchar_t* CommandClass::vf_2()
{
    return vf_4();
}

// FUNCTION: GAMEMD 0x535D20 -- SetStructureTabCommandClass slot 1
const char* SetStructureTabCommandClass::vf_1() const
{
    return "StructureTab";
}

// FUNCTION: GAMEMD 0x535D30 -- SetStructureTabCommandClass slot 2
const wchar_t* SetStructureTabCommandClass::vf_2()
{
    return StringTable_LoadString("TXT_STRUCTURE_TAB", 0, INIT_CPP, 0x182A);
}

// FUNCTION: GAMEMD 0x535D50 -- SetStructureTabCommandClass slot 3
const wchar_t* SetStructureTabCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_INTERFACE", 0, INIT_CPP, 0x182C);
}

// FUNCTION: GAMEMD 0x535D70 -- SetStructureTabCommandClass slot 4
const wchar_t* SetStructureTabCommandClass::vf_4()
{
    return StringTable_LoadString("TXT_STRUCTURE_TAB_DESC", 0, INIT_CPP, 0x182E);
}

// FUNCTION: GAMEMD 0x535D90 -- SetStructureTabCommandClass slot 8
void SetStructureTabCommandClass::vf_8(int key) const
{
    if (Map_0087F7E8.Strips[0].FUN_006ABAC0()) {
        Map_0087F7E8.SetTab(0);
        DisplayCmdObject* object = FUN_007342A0();
        if (object) {
            DisplayCmdPlayer_00A83D4C->FUN_004FB840(object->vf_100(0, 0), object);
        }
    }
}

// FUNCTION: GAMEMD 0x535DE0 -- SetDefenseTabCommandClass slot 1
const char* SetDefenseTabCommandClass::vf_1() const
{
    return "DefenseTab";
}

// FUNCTION: GAMEMD 0x535DF0 -- SetDefenseTabCommandClass slot 2
const wchar_t* SetDefenseTabCommandClass::vf_2()
{
    return StringTable_LoadString("TXT_DEFENSE_TAB", 0, INIT_CPP, 0x1844);
}

// FUNCTION: GAMEMD 0x535E10 -- SetDefenseTabCommandClass slot 3
const wchar_t* SetDefenseTabCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_INTERFACE", 0, INIT_CPP, 0x1846);
}

// FUNCTION: GAMEMD 0x535E30 -- SetDefenseTabCommandClass slot 4
const wchar_t* SetDefenseTabCommandClass::vf_4()
{
    return StringTable_LoadString("TXT_DEFENSE_TAB_DESC", 0, INIT_CPP, 0x1848);
}

// FUNCTION: GAMEMD 0x535E50 -- SetDefenseTabCommandClass slot 8
void SetDefenseTabCommandClass::vf_8(int key) const
{
    if (Map_0087F7E8.Strips[1].FUN_006ABAC0()) {
        Map_0087F7E8.SetTab(1);
        DisplayCmdObject* object = FUN_007342B0();
        if (object) {
            DisplayCmdPlayer_00A83D4C->FUN_004FB840(object->vf_100(0, 0), object);
        }
    }
}

// FUNCTION: GAMEMD 0x535EA0 -- SetInfantryTabCommandClass slot 1
const char* SetInfantryTabCommandClass::vf_1() const
{
    return "InfantryTab";
}

// FUNCTION: GAMEMD 0x535EB0 -- SetInfantryTabCommandClass slot 2
const wchar_t* SetInfantryTabCommandClass::vf_2()
{
    return StringTable_LoadString("TXT_INFANTRY_TAB", 0, INIT_CPP, 0x185E);
}

// FUNCTION: GAMEMD 0x535ED0 -- SetInfantryTabCommandClass slot 3
const wchar_t* SetInfantryTabCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_INTERFACE", 0, INIT_CPP, 0x1860);
}

// FUNCTION: GAMEMD 0x535EF0 -- SetInfantryTabCommandClass slot 4
const wchar_t* SetInfantryTabCommandClass::vf_4()
{
    return StringTable_LoadString("TXT_INFANTRY_TAB_DESC", 0, INIT_CPP, 0x1862);
}

// FUNCTION: GAMEMD 0x535F10 -- SetInfantryTabCommandClass slot 8
void SetInfantryTabCommandClass::vf_8(int key) const
{
    if (Map_0087F7E8.Strips[2].FUN_006ABAC0()) {
        Map_0087F7E8.SetTab(2);
    }
}

// FUNCTION: GAMEMD 0x535F30 -- SetUnitTabCommandClass slot 1
const char* SetUnitTabCommandClass::vf_1() const
{
    return "UnitTab";
}

// FUNCTION: GAMEMD 0x535F40 -- SetUnitTabCommandClass slot 2
const wchar_t* SetUnitTabCommandClass::vf_2()
{
    return StringTable_LoadString("TXT_UNIT_TAB", 0, INIT_CPP, 0x1873);
}

// FUNCTION: GAMEMD 0x535F60 -- SetUnitTabCommandClass slot 3
const wchar_t* SetUnitTabCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_INTERFACE", 0, INIT_CPP, 0x1875);
}

// FUNCTION: GAMEMD 0x535F80 -- SetUnitTabCommandClass slot 4
const wchar_t* SetUnitTabCommandClass::vf_4()
{
    return StringTable_LoadString("TXT_UNIT_TAB_DESC", 0, INIT_CPP, 0x1877);
}

// FUNCTION: GAMEMD 0x535FA0 -- SetUnitTabCommandClass slot 8
void SetUnitTabCommandClass::vf_8(int key) const
{
    if (Map_0087F7E8.Strips[3].FUN_006ABAC0()) {
        Map_0087F7E8.SetTab(3);
    }
}

// SYNTHETIC: GAMEMD 0x535FC0 -- SelectTeamCommandClass constructor, defined inline in command_class.h; emitted out-of-line here

// FUNCTION: GAMEMD 0x535FE0 -- SelectTeamCommandClass slot 1
const char* SelectTeamCommandClass::vf_1() const
{
    sprintf(DAT_00A8F5B4, "TeamSelect_%d", unknown_04);
    return DAT_00A8F5B4;
}

// FUNCTION: GAMEMD 0x536000 -- SelectTeamCommandClass slot 2
const wchar_t* SelectTeamCommandClass::vf_2()
{
    swprintf(DAT_00A8F654, StringTable_LoadString("TXT_SELECT_TEAM", 0, INIT_CPP, 0x1894), unknown_04);
    return DAT_00A8F654;
}

// FUNCTION: GAMEMD 0x536030 -- SelectTeamCommandClass slot 3
const wchar_t* SelectTeamCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_TEAM", 0, INIT_CPP, 0x1896);
}

// FUNCTION: GAMEMD 0x536050 -- SelectTeamCommandClass slot 4
const wchar_t* SelectTeamCommandClass::vf_4()
{
    swprintf(DAT_00A8F654, StringTable_LoadString("TXT_SELECT_TEAM_DESC", 0, INIT_CPP, 0x1898), unknown_04);
    return DAT_00A8F654;
}

// FUNCTION: GAMEMD 0x536080 -- SelectTeamCommandClass slot 8
void SelectTeamCommandClass::vf_8(int key) const
{
    FUN_007311C0(unknown_04);
}

// SYNTHETIC: GAMEMD 0x5360B0 -- AddTeamCommandClass constructor, defined inline in command_class.h; emitted out-of-line here

// FUNCTION: GAMEMD 0x5360D0 -- AddTeamCommandClass slot 1
const char* AddTeamCommandClass::vf_1() const
{
    sprintf(DAT_00A8F5B4, "TeamAddSelect_%d", unknown_04);
    return DAT_00A8F5B4;
}

// FUNCTION: GAMEMD 0x5360F0 -- AddTeamCommandClass slot 2
const wchar_t* AddTeamCommandClass::vf_2()
{
    swprintf(DAT_00A8F654, StringTable_LoadString("TXT_ADD_SELECT_TEAM", 0, INIT_CPP, 0x18B6), unknown_04);
    return DAT_00A8F654;
}

// FUNCTION: GAMEMD 0x536120 -- AddTeamCommandClass slot 3
const wchar_t* AddTeamCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_TEAM", 0, INIT_CPP, 0x18B8);
}

// FUNCTION: GAMEMD 0x536140 -- AddTeamCommandClass slot 4
const wchar_t* AddTeamCommandClass::vf_4()
{
    swprintf(DAT_00A8F654, StringTable_LoadString("TXT_ADD_SELECT_TEAM_DESC", 0, INIT_CPP, 0x18BA), unknown_04);
    return DAT_00A8F654;
}

// FUNCTION: GAMEMD 0x536170 -- AddTeamCommandClass slot 8
void AddTeamCommandClass::vf_8(int key) const
{
    FUN_007314C0(unknown_04);
}

// SYNTHETIC: GAMEMD 0x5361A0 -- CenterTeamCommandClass constructor, defined inline in command_class.h; emitted out-of-line here

// FUNCTION: GAMEMD 0x5361C0 -- CenterTeamCommandClass slot 1
const char* CenterTeamCommandClass::vf_1() const
{
    sprintf(DAT_00A8F5B4, "TeamCenter_%d", unknown_04);
    return DAT_00A8F5B4;
}

// FUNCTION: GAMEMD 0x5361E0 -- CenterTeamCommandClass slot 2
const wchar_t* CenterTeamCommandClass::vf_2()
{
    swprintf(DAT_00A8F654, StringTable_LoadString("TXT_CENTER_TEAM", 0, INIT_CPP, 0x18D9), unknown_04);
    return DAT_00A8F654;
}

// FUNCTION: GAMEMD 0x536210 -- CenterTeamCommandClass slot 3
const wchar_t* CenterTeamCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_TEAM", 0, INIT_CPP, 0x18DB);
}

// FUNCTION: GAMEMD 0x536230 -- CenterTeamCommandClass slot 4
const wchar_t* CenterTeamCommandClass::vf_4()
{
    swprintf(DAT_00A8F654, StringTable_LoadString("TXT_CENTER_TEAM_DESC", 0, INIT_CPP, 0x18DD), unknown_04);
    return DAT_00A8F654;
}

// FUNCTION: GAMEMD 0x536260 -- CenterTeamCommandClass slot 8
void CenterTeamCommandClass::vf_8(int key) const
{
    FUN_007313A0(unknown_04);
}

// SYNTHETIC: GAMEMD 0x536290 -- TauntCommandClass constructor, defined inline in command_class.h; emitted out-of-line here

// FUNCTION: GAMEMD 0x5362B0 -- TauntCommandClass slot 1
const char* TauntCommandClass::vf_1() const
{
    sprintf(DAT_00A8F5B4, "Taunt_%d", unknown_04);
    return DAT_00A8F5B4;
}

// FUNCTION: GAMEMD 0x5362D0 -- TauntCommandClass slot 2
const wchar_t* TauntCommandClass::vf_2()
{
    swprintf(DAT_00A8F654, StringTable_LoadString("TXT_TAUNT_NUMBER", 0, INIT_CPP, 0x1900), unknown_04);
    return DAT_00A8F654;
}

// FUNCTION: GAMEMD 0x536300 -- TauntCommandClass slot 3
const wchar_t* TauntCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_TAUNT", 0, INIT_CPP, 0x1905);
}

// FUNCTION: GAMEMD 0x536320 -- TauntCommandClass slot 4
const wchar_t* TauntCommandClass::vf_4()
{
    swprintf(DAT_00A8F654, StringTable_LoadString("TXT_TAUNT_DESC", 0, INIT_CPP, 0x1909), unknown_04);
    return DAT_00A8F654;
}

// FUNCTION: GAMEMD 0x536350 -- TauntCommandClass slot 8
// PARTIAL: best 31.5%. The packet's nibble pair is stored by one merged byte
// write in retail (taunt index low, colour high), and the house loop keeps
// its pointers in different registers. Tried: nibble order swapped, int and
// short bit-field units.
void TauntCommandClass::vf_8(int key) const
{
    if ((Session_00A8B238.GameMode == 3 || Session_00A8B238.GameMode == 4) && DAT_00A8B538 == 0) {
        int now = timeGetTime();
        if (DAT_00825C88 == -1 || now - DAT_00825C88 > 5000) {
            if ((DAT_00A8D110 && Session_00A8B238.GameMode == 3) || (DAT_00A8D111 && Session_00A8B238.GameMode == 4)) {
                DAT_00825C88 = now;
                CommandTauntPacket packet;
                packet.Command = 0x1D;
                strcpy(packet.Name, DAT_00A8DA78[0]->FUN_007350C0());
                packet.unknown_31 = DAT_00A8B394;
                packet.unknown_35 = DAT_00A8D610.FUN_005DAC00();
                packet.Colour = DAT_00A8DA78[0]->unknown_4B;
                packet.Taunt = unknown_04;
                FUN_00752B70();
                packet.unknown_2F = false;
                for (int i = 0; i < DAT_00A80238; i++) {
                    CommandHouse* house = DAT_00A8022C[i];
                    if (house && house->Type->unknown_1A5 && DAT_00A8D108[i]) {
                        int count = DAT_00A8E9C0.FUN_00540F90();
                        for (int j = 0; j < count; j++) {
                            int id = DAT_00A8E9C0.FUN_00540FA0(j);
                            if (!_stricmp(house->unknown_1602A, DAT_00A8E9C0.FUN_00540FC0(id))) {
                                int address = DAT_00A8E9C0.FUN_00541000(id);
                                if (DAT_00A8DBA0) {
                                    packet.unknown_2F |= DAT_00B052D0.FUN_00663D60(id);
                                } else {
                                    DAT_00A8E9C0.FUN_005410F0(&packet, 0x1C7, 1, address, 0, 0);
                                    DAT_00A8E9C0.FUN_00541820();
                                }
                            }
                        }
                    }
                }
                if (DAT_00A8DBA0 && packet.unknown_2F) {
                    DAT_00A8E9C0.FUN_005410F0(&packet, 0x1C7, 1, (int)&DAT_00A8DA78[0]->unknown_28, 0, 0);
                    DAT_00A8E9C0.FUN_00541820();
                }
            }
        }
    }
}

// FUNCTION: GAMEMD 0x5365A0 -- NextObjectCommandClass slot 1
const char* NextObjectCommandClass::vf_1() const
{
    return "NextObject";
}

// FUNCTION: GAMEMD 0x5365B0 -- NextObjectCommandClass slot 2
const wchar_t* NextObjectCommandClass::vf_2()
{
    return StringTable_LoadString("TXT_NEXT_OBJECT", 0, INIT_CPP, 0x197E);
}

// FUNCTION: GAMEMD 0x5365D0 -- NextObjectCommandClass slot 3
const wchar_t* NextObjectCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_SELECTION", 0, INIT_CPP, 0x1980);
}

// FUNCTION: GAMEMD 0x5365F0 -- NextObjectCommandClass slot 4
const wchar_t* NextObjectCommandClass::vf_4()
{
    return StringTable_LoadString("TXT_NEXT_OBJECT_DESC", 0, INIT_CPP, 0x1982);
}

// FUNCTION: GAMEMD 0x536610 -- NextObjectCommandClass slot 8
void NextObjectCommandClass::vf_8(int key) const
{
    Map_0087F7E8.SetPowerMode_004AC820(0);
    Map_0087F7E8.SetWaypointMode_004AC700(0, 0);
    Map_0087F7E8.SetRepairMode_004AC8C0(0);
    Map_0087F7E8.SetSellMode_004AC660(0);
    DisplayCmdObject* object = Map_0087F7E8.FUN_004AA2B0(
        DisplayCmdSelCount_00A8ECC8 ? DisplayCmdSelItems_00A8ECBC[0] : 0);
    if (object) {
        UnselectAll_0048DC90();
        object->vf_83();
        Map_0087F7E8.FUN_004AE290();
        Map_0087F7E8.FlagToRedraw(1);
    }
}

// FUNCTION: GAMEMD 0x5366A0 -- PlanningModeCommandClass slot 1
const char* PlanningModeCommandClass::vf_1() const
{
    return "PlanningMode";
}

// FUNCTION: GAMEMD 0x5366B0 -- PlanningModeCommandClass slot 2
const wchar_t* PlanningModeCommandClass::vf_2()
{
    return StringTable_LoadString("Cmnd:PlanningMode", 0, INIT_CPP, 0x19B4);
}

// FUNCTION: GAMEMD 0x5366D0 -- PlanningModeCommandClass slot 3
const wchar_t* PlanningModeCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_CONTROL", 0, INIT_CPP, 0x19B6);
}

// FUNCTION: GAMEMD 0x5366F0 -- PlanningModeCommandClass slot 4
const wchar_t* PlanningModeCommandClass::vf_4()
{
    return StringTable_LoadString("Cmnd:PlanningModeDesc", 0, INIT_CPP, 0x19B8);
}

// FUNCTION: GAMEMD 0x536710 -- PlanningModeCommandClass slot 5
bool PlanningModeCommandClass::vf_5(int key)
{
    return (key & 0x100) || (key & 0x200) || (key & 0x400);
}

// FUNCTION: GAMEMD 0x536730 -- PlanningModeCommandClass slot 6
bool PlanningModeCommandClass::vf_6(int key)
{
    return true;
}

// FUNCTION: GAMEMD 0x536740 -- PlanningModeCommandClass slot 7
bool PlanningModeCommandClass::vf_7(int key)
{
    return (key & 0x800) == 0;
}

// FUNCTION: GAMEMD 0x536750 -- PlanningModeCommandClass slot 8
void PlanningModeCommandClass::vf_8(int key) const
{
    if (key & 0x800) {
        FUN_00731A70(false);
    } else {
        FUN_00731A50(false);
    }
}

// FUNCTION: GAMEMD 0x536770 -- CombatantSelectCommandClass slot 1
const char* CombatantSelectCommandClass::vf_1() const
{
    return "CombatantSelect";
}

// FUNCTION: GAMEMD 0x536780 -- CombatantSelectCommandClass slot 2
const wchar_t* CombatantSelectCommandClass::vf_2()
{
    return StringTable_LoadString("Cmnd:CombatantSelect", 0, INIT_CPP, 0x1A08);
}

// FUNCTION: GAMEMD 0x5367A0 -- CombatantSelectCommandClass slot 3
const wchar_t* CombatantSelectCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_SELECTION", 0, INIT_CPP, 0x1A0A);
}

// FUNCTION: GAMEMD 0x5367C0 -- CombatantSelectCommandClass slot 4
const wchar_t* CombatantSelectCommandClass::vf_4()
{
    return StringTable_LoadString("Cmnd:CombatantSelectDesc", 0, INIT_CPP, 0x1A0C);
}

// FUNCTION: GAMEMD 0x5367E0 -- CombatantSelectCommandClass slot 5
bool CombatantSelectCommandClass::vf_5(int key)
{
    return (key & 0x100) != 0;
}

// FUNCTION: GAMEMD 0x5367F0 -- CombatantSelectCommandClass slot 8
void CombatantSelectCommandClass::vf_8(int key) const
{
    FUN_00732280((key & 0x100) == 0);
}

// FUNCTION: GAMEMD 0x536810 -- TypeSelectCommandClass slot 1
const char* TypeSelectCommandClass::vf_1() const
{
    return "TypeSelect";
}

// FUNCTION: GAMEMD 0x536820 -- TypeSelectCommandClass slot 2
const wchar_t* TypeSelectCommandClass::vf_2()
{
    return StringTable_LoadString("Cmnd:TypeSelect", 0, INIT_CPP, 0x1A22);
}

// FUNCTION: GAMEMD 0x536840 -- TypeSelectCommandClass slot 3
const wchar_t* TypeSelectCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_SELECTION", 0, INIT_CPP, 0x1A24);
}

// FUNCTION: GAMEMD 0x536860 -- TypeSelectCommandClass slot 4
const wchar_t* TypeSelectCommandClass::vf_4()
{
    return StringTable_LoadString("Cmnd:TypeSelectDesc", 0, INIT_CPP, 0x1A26);
}

// FUNCTION: GAMEMD 0x536880 -- TypeSelectCommandClass slot 5
bool TypeSelectCommandClass::vf_5(int key)
{
    return (key & 0x100) != 0;
}

// FUNCTION: GAMEMD 0x536890 -- TypeSelectCommandClass slot 6
bool TypeSelectCommandClass::vf_6(int key)
{
    return true;
}

// FUNCTION: GAMEMD 0x5368A0 -- TypeSelectCommandClass slot 7
bool TypeSelectCommandClass::vf_7(int key)
{
    return (key & 0x800) == 0;
}

// FUNCTION: GAMEMD 0x5368B0 -- TypeSelectCommandClass slot 8
void TypeSelectCommandClass::vf_8(int key) const
{
    if (key & 0x800) {
        FUN_00732CC0();
    } else {
        FUN_00732CA0();
    }
}

// FUNCTION: GAMEMD 0x5368D0 -- HealthNavCommandClass slot 1
const char* HealthNavCommandClass::vf_1() const
{
    return "HealthNav";
}

// FUNCTION: GAMEMD 0x5368E0 -- HealthNavCommandClass slot 2
const wchar_t* HealthNavCommandClass::vf_2()
{
    return StringTable_LoadString("Cmnd:HealthNavigation", 0, INIT_CPP, 0x1A48);
}

// FUNCTION: GAMEMD 0x536900 -- HealthNavCommandClass slot 3
const wchar_t* HealthNavCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_SELECTION", 0, INIT_CPP, 0x1A4A);
}

// FUNCTION: GAMEMD 0x536920 -- HealthNavCommandClass slot 4
const wchar_t* HealthNavCommandClass::vf_4()
{
    return StringTable_LoadString("Cmnd:HealthNavigationDesc", 0, INIT_CPP, 0x1A4C);
}

// FUNCTION: GAMEMD 0x536940 -- HealthNavCommandClass slot 5
bool HealthNavCommandClass::vf_5(int key)
{
    return (key & 0x100) != 0;
}

// FUNCTION: GAMEMD 0x536950 -- HealthNavCommandClass slot 8
void HealthNavCommandClass::vf_8(int key) const
{
    FUN_00733380((key & 0x100) == 0);
}

// FUNCTION: GAMEMD 0x536970 -- VeterancyNavCommandClass slot 1
const char* VeterancyNavCommandClass::vf_1() const
{
    return "VeterancyNav";
}

// FUNCTION: GAMEMD 0x536980 -- VeterancyNavCommandClass slot 2
const wchar_t* VeterancyNavCommandClass::vf_2()
{
    return StringTable_LoadString("Cmnd:VetNavigation", 0, INIT_CPP, 0x1A62);
}

// FUNCTION: GAMEMD 0x5369A0 -- VeterancyNavCommandClass slot 3
const wchar_t* VeterancyNavCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_SELECTION", 0, INIT_CPP, 0x1A64);
}

// FUNCTION: GAMEMD 0x5369C0 -- VeterancyNavCommandClass slot 4
const wchar_t* VeterancyNavCommandClass::vf_4()
{
    return StringTable_LoadString("Cmnd:VetNavigationDesc", 0, INIT_CPP, 0x1A66);
}

// FUNCTION: GAMEMD 0x5369E0 -- VeterancyNavCommandClass slot 5
bool VeterancyNavCommandClass::vf_5(int key)
{
    return (key & 0x100) != 0;
}

// FUNCTION: GAMEMD 0x5369F0 -- VeterancyNavCommandClass slot 8
void VeterancyNavCommandClass::vf_8(int key) const
{
    FUN_007336C0((key & 0x100) == 0);
}

// FUNCTION: GAMEMD 0x536A10 -- PrevObjectCommandClass slot 1
const char* PrevObjectCommandClass::vf_1() const
{
    return "PreviousObject";
}

// FUNCTION: GAMEMD 0x536A20 -- PrevObjectCommandClass slot 2
const wchar_t* PrevObjectCommandClass::vf_2()
{
    return StringTable_LoadString("TXT_PREV_OBJECT", 0, INIT_CPP, 0x1AA1);
}

// FUNCTION: GAMEMD 0x536A40 -- PrevObjectCommandClass slot 3
const wchar_t* PrevObjectCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_SELECTION", 0, INIT_CPP, 0x1AA3);
}

// FUNCTION: GAMEMD 0x536A60 -- PrevObjectCommandClass slot 4
const wchar_t* PrevObjectCommandClass::vf_4()
{
    return StringTable_LoadString("TXT_PREV_OBJECT_DESC", 0, INIT_CPP, 0x1AA5);
}

// FUNCTION: GAMEMD 0x536A80 -- PrevObjectCommandClass slot 8
void PrevObjectCommandClass::vf_8(int key) const
{
    Map_0087F7E8.SetPowerMode_004AC820(0);
    Map_0087F7E8.SetWaypointMode_004AC700(0, 0);
    Map_0087F7E8.SetRepairMode_004AC8C0(0);
    Map_0087F7E8.SetSellMode_004AC660(0);
    DisplayCmdObject* object = Map_0087F7E8.FUN_004AA380(
        DisplayCmdSelCount_00A8ECC8 ? DisplayCmdSelItems_00A8ECBC[0] : 0);
    if (object) {
        UnselectAll_0048DC90();
        object->vf_83();
        Map_0087F7E8.FUN_004AE290();
        Map_0087F7E8.FlagToRedraw(1);
    }
}

// FUNCTION: GAMEMD 0x536B10 -- StopCommandClass slot 1
const char* StopCommandClass::vf_1() const
{
    return "StopObject";
}

// FUNCTION: GAMEMD 0x536B20 -- StopCommandClass slot 2
const wchar_t* StopCommandClass::vf_2()
{
    return StringTable_LoadString("TXT_STOP_OBJECT", 0, INIT_CPP, 0x1ACA);
}

// FUNCTION: GAMEMD 0x536B40 -- StopCommandClass slot 3
const wchar_t* StopCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_CONTROL", 0, INIT_CPP, 0x1ACC);
}

// FUNCTION: GAMEMD 0x536B60 -- StopCommandClass slot 4
const wchar_t* StopCommandClass::vf_4()
{
    return StringTable_LoadString("TXT_STOP_OBJECT_DESC", 0, INIT_CPP, 0x1ACE);
}

// FUNCTION: GAMEMD 0x536B80 -- StopCommandClass slot 8
void StopCommandClass::vf_8(int key) const
{
    FUN_00730EA0();
}

// FUNCTION: GAMEMD 0x536B90 -- AllToCheerCommandClass slot 1
const char* AllToCheerCommandClass::vf_1() const
{
    return "AllToCheer";
}

// FUNCTION: GAMEMD 0x536BA0 -- AllToCheerCommandClass slot 2
const wchar_t* AllToCheerCommandClass::vf_2()
{
    return StringTable_LoadString("Cmnd:AllCheer", 0, INIT_CPP, 0x1ADC);
}

// FUNCTION: GAMEMD 0x536BC0 -- AllToCheerCommandClass slot 3
const wchar_t* AllToCheerCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_CONTROL", 0, INIT_CPP, 0x1ADE);
}

// FUNCTION: GAMEMD 0x536BE0 -- AllToCheerCommandClass slot 4
const wchar_t* AllToCheerCommandClass::vf_4()
{
    return StringTable_LoadString("Cmnd:AllCheerDesc", 0, INIT_CPP, 0x1AE0);
}

// FUNCTION: GAMEMD 0x536C00 -- AllToCheerCommandClass slot 8
void AllToCheerCommandClass::vf_8(int key) const
{
    FUN_00730F30();
}

// FUNCTION: GAMEMD 0x536C10 -- DeployCommandClass slot 1
const char* DeployCommandClass::vf_1() const
{
    return "DeployObject";
}

// FUNCTION: GAMEMD 0x536C20 -- DeployCommandClass slot 2
const wchar_t* DeployCommandClass::vf_2()
{
    return StringTable_LoadString("TXT_DEPLOY_OBJECT", 0, INIT_CPP, 0x1AF7);
}

// FUNCTION: GAMEMD 0x536C40 -- DeployCommandClass slot 3
const wchar_t* DeployCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_CONTROL", 0, INIT_CPP, 0x1AF9);
}

// FUNCTION: GAMEMD 0x536C60 -- DeployCommandClass slot 4
const wchar_t* DeployCommandClass::vf_4()
{
    return StringTable_LoadString("TXT_DEPLOY_OBJECT_DESC", 0, INIT_CPP, 0x1AFB);
}

// FUNCTION: GAMEMD 0x536C80 -- DeployCommandClass slot 8
void DeployCommandClass::vf_8(int key) const
{
    FUN_00730AF0();
}

// FUNCTION: GAMEMD 0x536C90 -- GuardCommandClass slot 1
const char* GuardCommandClass::vf_1() const
{
    return "GuardObject";
}

// FUNCTION: GAMEMD 0x536CA0 -- GuardCommandClass slot 2
const wchar_t* GuardCommandClass::vf_2()
{
    return StringTable_LoadString("TXT_GUARD", 0, INIT_CPP, 0x1B13);
}

// FUNCTION: GAMEMD 0x536CC0 -- GuardCommandClass slot 3
const wchar_t* GuardCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_CONTROL", 0, INIT_CPP, 0x1B15);
}

// FUNCTION: GAMEMD 0x536CE0 -- GuardCommandClass slot 4
const wchar_t* GuardCommandClass::vf_4()
{
    return StringTable_LoadString("TXT_GUARD_DESC", 0, INIT_CPP, 0x1B17);
}

// FUNCTION: GAMEMD 0x536D00 -- GuardCommandClass slot 8
void GuardCommandClass::vf_8(int key) const
{
    FUN_00730D60();
}

// FUNCTION: GAMEMD 0x536D10 -- ScatterCommandClass slot 1
const char* ScatterCommandClass::vf_1() const
{
    return "ScatterObject";
}

// FUNCTION: GAMEMD 0x536D20 -- ScatterCommandClass slot 2
const wchar_t* ScatterCommandClass::vf_2()
{
    return StringTable_LoadString("TXT_SCATTER", 0, INIT_CPP, 0x1B30);
}

// FUNCTION: GAMEMD 0x536D40 -- ScatterCommandClass slot 3
const wchar_t* ScatterCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_CONTROL", 0, INIT_CPP, 0x1B32);
}

// FUNCTION: GAMEMD 0x536D60 -- ScatterCommandClass slot 4
const wchar_t* ScatterCommandClass::vf_4()
{
    return StringTable_LoadString("TXT_SCATTER_DESC", 0, INIT_CPP, 0x1B34);
}

// FUNCTION: GAMEMD 0x536D80 -- ScatterCommandClass slot 8
void ScatterCommandClass::vf_8(int key) const
{
    FUN_00730FE0();
}

// FUNCTION: GAMEMD 0x536D90 -- CenterViewCommandClass slot 1
const char* CenterViewCommandClass::vf_1() const
{
    return "CenterView";
}

// FUNCTION: GAMEMD 0x536DA0 -- CenterViewCommandClass slot 2
const wchar_t* CenterViewCommandClass::vf_2()
{
    return StringTable_LoadString("TXT_CENTER_VIEW", 0, INIT_CPP, 0x1B4B);
}

// FUNCTION: GAMEMD 0x536DC0 -- CenterViewCommandClass slot 3
const wchar_t* CenterViewCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_SELECTION", 0, INIT_CPP, 0x1B4D);
}

// FUNCTION: GAMEMD 0x536DE0 -- CenterViewCommandClass slot 4
const wchar_t* CenterViewCommandClass::vf_4()
{
    return StringTable_LoadString("TXT_CENTER_VIEW_DESC", 0, INIT_CPP, 0x1B4F);
}

// FUNCTION: GAMEMD 0x536E00 -- CenterViewCommandClass slot 8
void CenterViewCommandClass::vf_8(int key) const
{
    if (DisplayCmdSelCount_00A8ECC8 > 0) {
        Map_0087F7E8.FUN_004AE290();
        Map_0087F7E8.FlagToRedraw(1);
    }
}

// FUNCTION: GAMEMD 0x536E30 -- CenterBaseCommandClass slot 1
const char* CenterBaseCommandClass::vf_1() const
{
    return "CenterBase";
}

// FUNCTION: GAMEMD 0x536E40 -- CenterBaseCommandClass slot 2
const wchar_t* CenterBaseCommandClass::vf_2()
{
    return StringTable_LoadString("TXT_CENTER_BASE", 0, INIT_CPP, 0x1B6A);
}

// FUNCTION: GAMEMD 0x536E60 -- CenterBaseCommandClass slot 3
const wchar_t* CenterBaseCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_SELECTION", 0, INIT_CPP, 0x1B6C);
}

// FUNCTION: GAMEMD 0x536E80 -- CenterBaseCommandClass slot 4
const wchar_t* CenterBaseCommandClass::vf_4()
{
    return StringTable_LoadString("TXT_CENTER_BASE_DESC", 0, INIT_CPP, 0x1B6E);
}

// FUNCTION: GAMEMD 0x536EA0 -- CenterBaseCommandClass slot 8
void CenterBaseCommandClass::vf_8(int key) const
{
    FUN_007315A0();
}

// FUNCTION: GAMEMD 0x536EB0 -- AllianceCommandClass slot 1
const char* AllianceCommandClass::vf_1() const
{
    return "ToggleAlliance";
}

// FUNCTION: GAMEMD 0x536EC0 -- AllianceCommandClass slot 2
const wchar_t* AllianceCommandClass::vf_2()
{
    return StringTable_LoadString("TXT_ALLIANCE", 0, INIT_CPP, 0x1B85);
}

// FUNCTION: GAMEMD 0x536EE0 -- AllianceCommandClass slot 3
const wchar_t* AllianceCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_CONTROL", 0, INIT_CPP, 0x1B87);
}

// FUNCTION: GAMEMD 0x536F00 -- AllianceCommandClass slot 4
const wchar_t* AllianceCommandClass::vf_4()
{
    return StringTable_LoadString("TXT_ALLIANCE_DESC", 0, INIT_CPP, 0x1B89);
}

// FUNCTION: GAMEMD 0x536F20 -- AllianceCommandClass slot 8
void AllianceCommandClass::vf_8(int key) const
{
    FUN_007318F0();
}

// FUNCTION: GAMEMD 0x536F30 -- ToggleRepairCommandClass slot 1
const char* ToggleRepairCommandClass::vf_1() const
{
    return "ToggleRepair";
}

// FUNCTION: GAMEMD 0x536F40 -- ToggleRepairCommandClass slot 2
const wchar_t* ToggleRepairCommandClass::vf_2()
{
    return StringTable_LoadString("TXT_REPAIR_MODE", 0, INIT_CPP, 0x1BBF);
}

// FUNCTION: GAMEMD 0x536F60 -- ToggleRepairCommandClass slot 3
const wchar_t* ToggleRepairCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_INTERFACE", 0, INIT_CPP, 0x1BC1);
}

// FUNCTION: GAMEMD 0x536F80 -- ToggleRepairCommandClass slot 4
const wchar_t* ToggleRepairCommandClass::vf_4()
{
    return StringTable_LoadString("TXT_REPAIR_MODE_DESC", 0, INIT_CPP, 0x1BC3);
}

// FUNCTION: GAMEMD 0x536FA0 -- ToggleRepairCommandClass slot 8
void ToggleRepairCommandClass::vf_8(int key) const
{
    Map_0087F7E8.SetRepairMode_004AC8C0(-1);
}

// FUNCTION: GAMEMD 0x536FB0 -- ToggleSellCommandClass slot 1
const char* ToggleSellCommandClass::vf_1() const
{
    return "ToggleSell";
}

// FUNCTION: GAMEMD 0x536FC0 -- ToggleSellCommandClass slot 2
const wchar_t* ToggleSellCommandClass::vf_2()
{
    return StringTable_LoadString("TXT_SELL_MODE", 0, INIT_CPP, 0x1BD9);
}

// FUNCTION: GAMEMD 0x536FE0 -- ToggleSellCommandClass slot 3
const wchar_t* ToggleSellCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_INTERFACE", 0, INIT_CPP, 0x1BDB);
}

// FUNCTION: GAMEMD 0x537000 -- ToggleSellCommandClass slot 4
const wchar_t* ToggleSellCommandClass::vf_4()
{
    return StringTable_LoadString("TXT_SELL_MODE_DESC", 0, INIT_CPP, 0x1BDD);
}

// FUNCTION: GAMEMD 0x537020 -- ToggleSellCommandClass slot 8
void ToggleSellCommandClass::vf_8(int key) const
{
    Map_0087F7E8.SetSellMode_004AC660(-1);
}

// FUNCTION: GAMEMD 0x537030 -- BeaconPlacementCommandClass slot 1
const char* BeaconPlacementCommandClass::vf_1() const
{
    return "PlaceBeacon";
}

// FUNCTION: GAMEMD 0x537040 -- BeaconPlacementCommandClass slot 2
const wchar_t* BeaconPlacementCommandClass::vf_2()
{
    return StringTable_LoadString("TXT_PLACE_BEACON", 0, INIT_CPP, 0x1C04);
}

// FUNCTION: GAMEMD 0x537060 -- BeaconPlacementCommandClass slot 3
const wchar_t* BeaconPlacementCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_INTERFACE", 0, INIT_CPP, 0x1C06);
}

// FUNCTION: GAMEMD 0x537080 -- BeaconPlacementCommandClass slot 4
const wchar_t* BeaconPlacementCommandClass::vf_4()
{
    return StringTable_LoadString("TXT_PLACE_BEACON_DESC", 0, INIT_CPP, 0x1C08);
}

// FUNCTION: GAMEMD 0x5370A0 -- BeaconPlacementCommandClass slot 8
void BeaconPlacementCommandClass::vf_8(int key) const
{
    if (Session_00A8B238.GameMode != 0 && Session_00A8B238.GameMode != 5) {
        FUN_00731A30();
    }
}

// FUNCTION: GAMEMD 0x5370C0 -- CenterREventCommandClass slot 1
const char* CenterREventCommandClass::vf_1() const
{
    return "CenterOnRadarEvent";
}

// FUNCTION: GAMEMD 0x5370D0 -- CenterREventCommandClass slot 2
const wchar_t* CenterREventCommandClass::vf_2()
{
    return StringTable_LoadString("TXT_RADAR_EVENT", 0, INIT_CPP, 0x1C1B);
}

// FUNCTION: GAMEMD 0x5370F0 -- CenterREventCommandClass slot 3
const wchar_t* CenterREventCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_INTERFACE", 0, INIT_CPP, 0x1C1D);
}

// FUNCTION: GAMEMD 0x537110 -- CenterREventCommandClass slot 4
const wchar_t* CenterREventCommandClass::vf_4()
{
    return StringTable_LoadString("TXT_RADAR_EVENT_DESC", 0, INIT_CPP, 0x1C1F);
}

// FUNCTION: GAMEMD 0x537130 -- CenterREventCommandClass slot 8
void CenterREventCommandClass::vf_8(int key) const
{
    FUN_00734120();
}

// FUNCTION: GAMEMD 0x537140 -- SidebarUpCommandClass slot 1
const char* SidebarUpCommandClass::vf_1() const
{
    return "SidebarUp";
}

// FUNCTION: GAMEMD 0x537150 -- SidebarUpCommandClass slot 2
const wchar_t* SidebarUpCommandClass::vf_2()
{
    return StringTable_LoadString("TXT_SIDEBAR_UP", 0, INIT_CPP, 0x1C51);
}

// FUNCTION: GAMEMD 0x537170 -- SidebarUpCommandClass slot 3
const wchar_t* SidebarUpCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_INTERFACE", 0, INIT_CPP, 0x1C53);
}

// FUNCTION: GAMEMD 0x537190 -- SidebarUpCommandClass slot 4
const wchar_t* SidebarUpCommandClass::vf_4()
{
    return StringTable_LoadString("TXT_SIDEBAR_UP_DESC", 0, INIT_CPP, 0x1C55);
}

// FUNCTION: GAMEMD 0x5371B0 -- SidebarUpCommandClass slot 8
void SidebarUpCommandClass::vf_8(int key) const
{
    Map_0087F7E8.Scroll(true, -1);
}

// FUNCTION: GAMEMD 0x5371D0 -- SidebarDownCommandClass slot 1
const char* SidebarDownCommandClass::vf_1() const
{
    return "SidebarDown";
}

// FUNCTION: GAMEMD 0x5371E0 -- SidebarDownCommandClass slot 2
const wchar_t* SidebarDownCommandClass::vf_2()
{
    return StringTable_LoadString("TXT_SIDEBAR_DOWN", 0, INIT_CPP, 0x1CDD);
}

// FUNCTION: GAMEMD 0x537200 -- SidebarDownCommandClass slot 3
const wchar_t* SidebarDownCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_INTERFACE", 0, INIT_CPP, 0x1CDF);
}

// FUNCTION: GAMEMD 0x537220 -- SidebarDownCommandClass slot 4
const wchar_t* SidebarDownCommandClass::vf_4()
{
    return StringTable_LoadString("TXT_SIDEBAR_DOWN_DESC", 0, INIT_CPP, 0x1CE1);
}

// FUNCTION: GAMEMD 0x537240 -- SidebarDownCommandClass slot 8
void SidebarDownCommandClass::vf_8(int key) const
{
    Map_0087F7E8.Scroll(false, -1);
}

// FUNCTION: GAMEMD 0x537260 -- OptionsCommandClass slot 1
const char* OptionsCommandClass::vf_1() const
{
    return "Options";
}

// FUNCTION: GAMEMD 0x537270 -- OptionsCommandClass slot 2
const wchar_t* OptionsCommandClass::vf_2()
{
    return StringTable_LoadString("TXT_OPTIONS", 0, INIT_CPP, 0x1D6A);
}

// FUNCTION: GAMEMD 0x537290 -- OptionsCommandClass slot 3
const wchar_t* OptionsCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_INTERFACE", 0, INIT_CPP, 0x1D6C);
}

// FUNCTION: GAMEMD 0x5372B0 -- OptionsCommandClass slot 4
const wchar_t* OptionsCommandClass::vf_4()
{
    return StringTable_LoadString("TXT_OPTIONS_DESC", 0, INIT_CPP, 0x1D6E);
}

// FUNCTION: GAMEMD 0x5372D0 -- OptionsCommandClass slot 8
void OptionsCommandClass::vf_8(int key) const
{
    FUN_00647040();
}

// FUNCTION: GAMEMD 0x5372E0 -- View1CommandClass slot 1
const char* View1CommandClass::vf_1() const
{
    return "View1";
}

// FUNCTION: GAMEMD 0x5372F0 -- View1CommandClass slot 2
const wchar_t* View1CommandClass::vf_2()
{
    return StringTable_LoadString("TXT_VIEW_BOOKMARK1", 0, INIT_CPP, 0x1E1B);
}

// FUNCTION: GAMEMD 0x537310 -- View1CommandClass slot 3
const wchar_t* View1CommandClass::vf_3()
{
    return StringTable_LoadString("TXT_INTERFACE", 0, INIT_CPP, 0x1E1D);
}

// FUNCTION: GAMEMD 0x537330 -- View1CommandClass slot 4
const wchar_t* View1CommandClass::vf_4()
{
    return StringTable_LoadString("TXT_VIEW_BOOKMARK1_DESC", 0, INIT_CPP, 0x1E1F);
}

// FUNCTION: GAMEMD 0x537350 -- View1CommandClass slot 8
void View1CommandClass::vf_8(int key) const
{
    CommandJumpToView(0);
}

// FUNCTION: GAMEMD 0x5373D0 -- View2CommandClass slot 1
const char* View2CommandClass::vf_1() const
{
    return "View2";
}

// FUNCTION: GAMEMD 0x5373E0 -- View2CommandClass slot 2
const wchar_t* View2CommandClass::vf_2()
{
    return StringTable_LoadString("TXT_VIEW_BOOKMARK2", 0, INIT_CPP, 0x1E3F);
}

// FUNCTION: GAMEMD 0x537400 -- View2CommandClass slot 3
const wchar_t* View2CommandClass::vf_3()
{
    return StringTable_LoadString("TXT_INTERFACE", 0, INIT_CPP, 0x1E41);
}

// FUNCTION: GAMEMD 0x537420 -- View2CommandClass slot 4
const wchar_t* View2CommandClass::vf_4()
{
    return StringTable_LoadString("TXT_VIEW_BOOKMARK2_DESC", 0, INIT_CPP, 0x1E43);
}

// FUNCTION: GAMEMD 0x537440 -- View2CommandClass slot 8
void View2CommandClass::vf_8(int key) const
{
    CommandJumpToView(1);
}

// FUNCTION: GAMEMD 0x5374C0 -- View3CommandClass slot 1
const char* View3CommandClass::vf_1() const
{
    return "View3";
}

// FUNCTION: GAMEMD 0x5374D0 -- View3CommandClass slot 2
const wchar_t* View3CommandClass::vf_2()
{
    return StringTable_LoadString("TXT_VIEW_BOOKMARK3", 0, INIT_CPP, 0x1E63);
}

// FUNCTION: GAMEMD 0x5374F0 -- View3CommandClass slot 3
const wchar_t* View3CommandClass::vf_3()
{
    return StringTable_LoadString("TXT_INTERFACE", 0, INIT_CPP, 0x1E65);
}

// FUNCTION: GAMEMD 0x537510 -- View3CommandClass slot 4
const wchar_t* View3CommandClass::vf_4()
{
    return StringTable_LoadString("TXT_VIEW_BOOKMARK3_DESC", 0, INIT_CPP, 0x1E67);
}

// FUNCTION: GAMEMD 0x537530 -- View3CommandClass slot 8
void View3CommandClass::vf_8(int key) const
{
    CommandJumpToView(2);
}

// FUNCTION: GAMEMD 0x5375B0 -- View4CommandClass slot 1
const char* View4CommandClass::vf_1() const
{
    return "View4";
}

// FUNCTION: GAMEMD 0x5375C0 -- View4CommandClass slot 2
const wchar_t* View4CommandClass::vf_2()
{
    return StringTable_LoadString("TXT_VIEW_BOOKMARK4", 0, INIT_CPP, 0x1E87);
}

// FUNCTION: GAMEMD 0x5375E0 -- View4CommandClass slot 3
const wchar_t* View4CommandClass::vf_3()
{
    return StringTable_LoadString("TXT_INTERFACE", 0, INIT_CPP, 0x1E89);
}

// FUNCTION: GAMEMD 0x537600 -- View4CommandClass slot 4
const wchar_t* View4CommandClass::vf_4()
{
    return StringTable_LoadString("TXT_VIEW_BOOKMARK4_DESC", 0, INIT_CPP, 0x1E8B);
}

// FUNCTION: GAMEMD 0x537620 -- View4CommandClass slot 8
void View4CommandClass::vf_8(int key) const
{
    CommandJumpToView(3);
}

// FUNCTION: GAMEMD 0x5376A0 -- SetView1CommandClass slot 1
const char* SetView1CommandClass::vf_1() const
{
    return "SetView1";
}

// FUNCTION: GAMEMD 0x5376B0 -- SetView1CommandClass slot 2
const wchar_t* SetView1CommandClass::vf_2()
{
    return StringTable_LoadString("TXT_SET_BOOKMARK1", 0, INIT_CPP, 0x1EAB);
}

// FUNCTION: GAMEMD 0x5376D0 -- SetView1CommandClass slot 3
const wchar_t* SetView1CommandClass::vf_3()
{
    return StringTable_LoadString("TXT_INTERFACE", 0, INIT_CPP, 0x1EAD);
}

// FUNCTION: GAMEMD 0x5376F0 -- SetView1CommandClass slot 4
const wchar_t* SetView1CommandClass::vf_4()
{
    return StringTable_LoadString("TXT_SET_BOOKMARK1_DESC", 0, INIT_CPP, 0x1EAF);
}

// FUNCTION: GAMEMD 0x537710 -- SetView1CommandClass slot 8
void SetView1CommandClass::vf_8(int key) const
{
    CommandStoreView(0);
}

// FUNCTION: GAMEMD 0x537760 -- SetView2CommandClass slot 1
const char* SetView2CommandClass::vf_1() const
{
    return "SetView2";
}

// FUNCTION: GAMEMD 0x537770 -- SetView2CommandClass slot 2
const wchar_t* SetView2CommandClass::vf_2()
{
    return StringTable_LoadString("TXT_SET_BOOKMARK2", 0, INIT_CPP, 0x1EC6);
}

// FUNCTION: GAMEMD 0x537790 -- SetView2CommandClass slot 3
const wchar_t* SetView2CommandClass::vf_3()
{
    return StringTable_LoadString("TXT_INTERFACE", 0, INIT_CPP, 0x1EC8);
}

// FUNCTION: GAMEMD 0x5377B0 -- SetView2CommandClass slot 4
const wchar_t* SetView2CommandClass::vf_4()
{
    return StringTable_LoadString("TXT_SET_BOOKMARK2_DESC", 0, INIT_CPP, 0x1ECA);
}

// FUNCTION: GAMEMD 0x5377D0 -- SetView2CommandClass slot 8
void SetView2CommandClass::vf_8(int key) const
{
    CommandStoreView(1);
}

// FUNCTION: GAMEMD 0x537820 -- SetView3CommandClass slot 1
const char* SetView3CommandClass::vf_1() const
{
    return "SetView3";
}

// FUNCTION: GAMEMD 0x537830 -- SetView3CommandClass slot 2
const wchar_t* SetView3CommandClass::vf_2()
{
    return StringTable_LoadString("TXT_SET_BOOKMARK3", 0, INIT_CPP, 0x1EE1);
}

// FUNCTION: GAMEMD 0x537850 -- SetView3CommandClass slot 3
const wchar_t* SetView3CommandClass::vf_3()
{
    return StringTable_LoadString("TXT_INTERFACE", 0, INIT_CPP, 0x1EE3);
}

// FUNCTION: GAMEMD 0x537870 -- SetView3CommandClass slot 4
const wchar_t* SetView3CommandClass::vf_4()
{
    return StringTable_LoadString("TXT_SET_BOOKMARK3_DESC", 0, INIT_CPP, 0x1EE5);
}

// FUNCTION: GAMEMD 0x537890 -- SetView3CommandClass slot 8
void SetView3CommandClass::vf_8(int key) const
{
    CommandStoreView(2);
}

// FUNCTION: GAMEMD 0x5378E0 -- SetView4CommandClass slot 1
const char* SetView4CommandClass::vf_1() const
{
    return "SetView4";
}

// FUNCTION: GAMEMD 0x5378F0 -- SetView4CommandClass slot 2
const wchar_t* SetView4CommandClass::vf_2()
{
    return StringTable_LoadString("TXT_SET_BOOKMARK4", 0, INIT_CPP, 0x1EFC);
}

// FUNCTION: GAMEMD 0x537910 -- SetView4CommandClass slot 3
const wchar_t* SetView4CommandClass::vf_3()
{
    return StringTable_LoadString("TXT_INTERFACE", 0, INIT_CPP, 0x1EFE);
}

// FUNCTION: GAMEMD 0x537930 -- SetView4CommandClass slot 4
const wchar_t* SetView4CommandClass::vf_4()
{
    return StringTable_LoadString("TXT_SET_BOOKMARK4_DESC", 0, INIT_CPP, 0x1F00);
}

// FUNCTION: GAMEMD 0x537950 -- SetView4CommandClass slot 8
void SetView4CommandClass::vf_8(int key) const
{
    CommandStoreView(3);
}

// FUNCTION: GAMEMD 0x5379A0 -- FollowCommandClass slot 1
const char* FollowCommandClass::vf_1() const
{
    return "Follow";
}

// FUNCTION: GAMEMD 0x5379B0 -- FollowCommandClass slot 2
const wchar_t* FollowCommandClass::vf_2()
{
    return StringTable_LoadString("TXT_FOLLOW", 0, INIT_CPP, 0x1F17);
}

// FUNCTION: GAMEMD 0x5379D0 -- FollowCommandClass slot 3
const wchar_t* FollowCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_INTERFACE", 0, INIT_CPP, 0x1F19);
}

// FUNCTION: GAMEMD 0x5379F0 -- FollowCommandClass slot 4
const wchar_t* FollowCommandClass::vf_4()
{
    return StringTable_LoadString("TXT_FOLLOW_DESC", 0, INIT_CPP, 0x1F1B);
}

// FUNCTION: GAMEMD 0x537A10 -- FollowCommandClass slot 8
void FollowCommandClass::vf_8(int key) const
{
    if (DisplayCmdSelCount_00A8ECC8 && !Map_0087F7E8.FUN_004AEB10()) {
        Map_0087F7E8.FUN_004AEB30(DisplayCmdSelItems_00A8ECBC[0]);
        return;
    }
    Map_0087F7E8.FUN_004AEB30(0);
}

// FUNCTION: GAMEMD 0x537A50 -- MultiplayerDebugCommandClass slot 1
const char* MultiplayerDebugCommandClass::vf_1() const
{
    return "MultiplayerDebug";
}

// FUNCTION: GAMEMD 0x537A60 -- MultiplayerDebugCommandClass slot 3
const wchar_t* MultiplayerDebugCommandClass::vf_3()
{
    return L"Debug";
}

// FUNCTION: GAMEMD 0x537A70 -- MultiplayerDebugCommandClass slot 2
const wchar_t* MultiplayerDebugCommandClass::vf_2()
{
    return L"Multiplayer debug info";
}

// FUNCTION: GAMEMD 0x537A80 -- MultiplayerDebugCommandClass slot 4
const wchar_t* MultiplayerDebugCommandClass::vf_4()
{
    return L"Turns multiplayer debug on or off.";
}

// FUNCTION: GAMEMD 0x537A90 -- MultiplayerDebugCommandClass slot 8
void MultiplayerDebugCommandClass::vf_8(int key) const
{
    if (DAT_00A8B8B4) {
        DAT_00A8B8B5 = !DAT_00A8B8B5;
    }
}

// FUNCTION: GAMEMD 0x537AB0 -- MultiplayerSyncCommandClass slot 1
const char* MultiplayerSyncCommandClass::vf_1() const
{
    return "ExtraSyncChecking";
}

// FUNCTION: GAMEMD 0x537AC0 -- MultiplayerSyncCommandClass slot 3
const wchar_t* MultiplayerSyncCommandClass::vf_3()
{
    return L"Debug";
}

// FUNCTION: GAMEMD 0x537AD0 -- MultiplayerSyncCommandClass slot 2
const wchar_t* MultiplayerSyncCommandClass::vf_2()
{
    return L"Game sync logging";
}

// FUNCTION: GAMEMD 0x537AE0 -- MultiplayerSyncCommandClass slot 4
const wchar_t* MultiplayerSyncCommandClass::vf_4()
{
    return L"Turns extra game sync logging on or off.";
}

// FUNCTION: GAMEMD 0x537AF0 -- MultiplayerSyncCommandClass slot 8
void MultiplayerSyncCommandClass::vf_8(int key) const
{
    DAT_00B04880 = !DAT_00B04880;
    if (DAT_00B04880) {
        DAT_00A8BC60.FUN_005D3BA0(0, 0, FUN_00735120("Extra sync info ON"), 3, 0x4046, 0x96, 0);
    } else {
        DAT_00A8BC60.FUN_005D3BA0(0, 0, FUN_00735120("Extra sync info OFF"), 3, 0x4046, 0x96, 0);
    }
}

// SYNTHETIC: GAMEMD 0x537B40 -- ScreenCaptureCommandClass constructor, defined inline in command_class.h; emitted out-of-line here

// FUNCTION: GAMEMD 0x537B50 -- ScreenCaptureCommandClass slot 1
const char* ScreenCaptureCommandClass::vf_1() const
{
    return "ScreenCapture";
}

// FUNCTION: GAMEMD 0x537B60 -- ScreenCaptureCommandClass slot 3
const wchar_t* ScreenCaptureCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_INTERFACE", 0, INIT_CPP, 0x1F87);
}

// FUNCTION: GAMEMD 0x537B80 -- ScreenCaptureCommandClass slot 2
const wchar_t* ScreenCaptureCommandClass::vf_2()
{
    return StringTable_LoadString("TXT_SCRNCAP", 0, INIT_CPP, 0x1F88);
}

// FUNCTION: GAMEMD 0x537BA0 -- ScreenCaptureCommandClass slot 4
const wchar_t* ScreenCaptureCommandClass::vf_4()
{
    return StringTable_LoadString("TXT_SCRNCAP_DESC", 0, INIT_CPP, 0x1F89);
}

// FUNCTION: GAMEMD 0x537BC0 -- ScreenCaptureCommandClass slot 8
// STRING: GAMEMD 0x827A48 -- "SCRN%04d.pcx"
// Copy the window's client area into the surface at 0x88730C, then write it to
// the first free SCRNnnnn.pcx.
void ScreenCaptureCommandClass::vf_8(int key) const
{
    RECT client;
    if (!GetClientRect(DAT_00B73550, &client)) {
        return;
    }
    POINT topLeft;
    topLeft.x = client.left;
    topLeft.y = client.top;
    if (!ClientToScreen(DAT_00B73550, &topLeft)) {
        return;
    }
    POINT bottomRight;
    bottomRight.x = client.right;
    bottomRight.y = client.bottom;
    if (!ClientToScreen(DAT_00B73550, &bottomRight)) {
        return;
    }

    RectangleStruct source;
    source.X = topLeft.x;
    source.Y = topLeft.y;
    source.Width = client.right + 1;
    source.Height = client.bottom + 1;
    if (source.Width >= DAT_0088730C->GetWidth()) {
        source.Width = DAT_0088730C->GetWidth();
    }
    if (source.Height >= DAT_0088730C->GetHeight()) {
        source.Height = DAT_0088730C->GetHeight();
    }

    DAT_00887640->HideCursor();
    int width = DAT_0088730C->GetWidth();
    int height = DAT_0088730C->GetHeight();
    RectangleStruct dest = {0, 0, width, height};
    DAT_0088730C->Blit(&dest, DAT_00887308, &source, false, true);
    DAT_00887640->ShowCursor();

    char name[128];
    int index = -1;
    do {
        ++index;
        sprintf(name, "SCRN%04d.pcx", index);
    } while (CCFileClass(name).Exists(false));

    CCFileClass file(name);
    FUN_007B05C0(&file, DAT_0088730C, DAT_00885780);
}

// SYNTHETIC: GAMEMD 0x537DD0 -- PageUserCommandClass constructor, defined inline in command_class.h; emitted out-of-line here

// FUNCTION: GAMEMD 0x537DE0 -- PageUserCommandClass slot 1
const char* PageUserCommandClass::vf_1() const
{
    return "PageUser";
}

// FUNCTION: GAMEMD 0x537DF0 -- PageUserCommandClass slot 2
const wchar_t* PageUserCommandClass::vf_2()
{
    return StringTable_LoadString("TXT_PAGEUSER", 0, INIT_CPP, 0x1D8B);
}

// FUNCTION: GAMEMD 0x537E10 -- PageUserCommandClass slot 3
const wchar_t* PageUserCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_INTERFACE", 0, INIT_CPP, 0x1D8D);
}

// FUNCTION: GAMEMD 0x537E30 -- PageUserCommandClass slot 4
const wchar_t* PageUserCommandClass::vf_4()
{
    return StringTable_LoadString("TXT_PAGEUSER_DESC", 0, INIT_CPP, 0x1D8F);
}

// FUNCTION: GAMEMD 0x537E50 -- PageUserCommandClass slot 8
void PageUserCommandClass::vf_8(int key) const
{
    if (Session_00A8B238.GameMode == 4) {
        FUN_006470F0();
    }
}

// SYNTHETIC: GAMEMD 0x537E70 -- CursorPositionCommandClass constructor, defined inline in command_class.h; emitted out-of-line here

// FUNCTION: GAMEMD 0x537E80 -- CursorPositionCommandClass slot 1
const char* CursorPositionCommandClass::vf_1() const
{
    return "CursorCheat";
}

// FUNCTION: GAMEMD 0x537E90 -- CursorPositionCommandClass slot 2
const wchar_t* CursorPositionCommandClass::vf_2()
{
    return StringTable_LoadString("GUI:CursorCheat", 0, INIT_CPP, 0x2027);
}

// FUNCTION: GAMEMD 0x537EB0 -- CursorPositionCommandClass slot 3
const wchar_t* CursorPositionCommandClass::vf_3()
{
    return StringTable_LoadString("GUI:Debug", 0, INIT_CPP, 0x2028);
}

// FUNCTION: GAMEMD 0x537ED0 -- CursorPositionCommandClass slot 4
const wchar_t* CursorPositionCommandClass::vf_4()
{
    return StringTable_LoadString("DESC:CursorCheat", 0, INIT_CPP, 0x2029);
}

// FUNCTION: GAMEMD 0x537EF0 -- CursorPositionCommandClass slot 8
void CursorPositionCommandClass::vf_8(int key) const
{
    DAT_00A8F7D8 = !DAT_00A8F7D8;
}

// SYNTHETIC: GAMEMD 0x537F10 -- DeleteCommandClass constructor, defined inline in command_class.h; emitted out-of-line here

// FUNCTION: GAMEMD 0x537F20 -- DeleteCommandClass slot 1
const char* DeleteCommandClass::vf_1() const
{
    return "Delete";
}

// FUNCTION: GAMEMD 0x537F30 -- DeleteCommandClass slot 2
const wchar_t* DeleteCommandClass::vf_2()
{
    return StringTable_LoadString("Cmnd:Delete", 0, INIT_CPP, 0x199F);
}

// FUNCTION: GAMEMD 0x537F50 -- DeleteCommandClass slot 3
const wchar_t* DeleteCommandClass::vf_3()
{
    return StringTable_LoadString("TXT_INTERFACE", 0, INIT_CPP, 0x19A1);
}

// FUNCTION: GAMEMD 0x537F70 -- DeleteCommandClass slot 4
const wchar_t* DeleteCommandClass::vf_4()
{
    return StringTable_LoadString("Cmnd:DeleteDesc", 0, INIT_CPP, 0x19A3);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x537F90 -- DeleteCommandClass slot 8
void DeleteCommandClass::vf_8(int key) const
{
    FUN_00731A10();
}

// LIBRARY: GAMEMD 0x7C8B3D -- CRT free.
extern "C" void __cdecl FUN_007C8B3D(void* block);
// LIBRARY: GAMEMD 0x7C8B48 -- CRT qsort.
extern "C" void __cdecl FUN_007C8B48(void* base, unsigned int num, unsigned int width,
                                     int (__cdecl* compare)(const void*, const void*));

// The third retail instantiation of the {ID, Data} index (see Ini.cpp for the
// first two): same layout and bodies, its own comparator (0x48BC20, declared
// here only so the sort call is a relocatable reference).
class IndexClassC
{
public:
    struct NodeElement
    {
        int   ID;
        void* Data;
        NodeElement() throw() {}
        static void* operator new[](unsigned int size) { return FUN_007C8E17(size); }
    };

    // FUNCTION: GAMEMD 0x5387D0
    bool AddIndex(const int& id, void* const& data);
    // FUNCTION: GAMEMD 0x5388A0
    bool RemoveIndex(const int& id);
    // FUNCTION: GAMEMD 0x538980
    bool IsPresent(const int& id) const;

    // FUNCTION: GAMEMD 0x48BC20 (decl; reloc)
    static int __cdecl Comparator(const void* ptr1, const void* ptr2);

    __forceinline bool IncreaseTableSize(int amount);
    __forceinline NodeElement* SearchForNode(const int& id) const;
    __forceinline bool IsPresentImpl(const int& id) const;

    NodeElement* IndexTable;   // +0x00
    int          IndexCount;   // +0x04
    int          IndexSize;    // +0x08
    bool         IsSorted;     // +0x0C
    NodeElement* Archive;      // +0x10
};
GG_STATIC_ASSERT(offsetof(IndexClassC, Archive) == 0x10 && sizeof(IndexClassC) == 0x14);

// GLOBAL: GAMEMD 0x87F680 -- the key-to-command index (typed here as the third {ID, Data} index).
extern IndexClassC DAT_0087F680;
// GLOBAL: GAMEMD 0x87F658 -- every registered keyboard command.
extern DynamicVectorClass<const CommandClass*> DAT_0087F658;
// FUNCTION: GAMEMD 0x533D20 (decl; reloc)
void FUN_00533D20();

// FUNCTION: GAMEMD 0x532150
// PARTIAL: 61% -- the compiler inlines the sixth CreateTeam constructor and its list append where retail
// calls 0x535C00 and 0x538780 (one extra inlined append, 19 instructions), and every inlined append
// computes the grown capacity into EAX and loads the vtable pointer after the pushes where retail
// computes it into ECX and loads the vtable pointer first. Its job here is to instantiate the command
// classes so the compiler emits their tables, constructors and scalar deleting destructors.
// Registers every keyboard command in the global command list, then binds the
// delete, escape and space keys to their commands.
void FUN_00532150()
{
    const CommandClass* options;
    const CommandClass* centerREvent;
    const CommandClass* del;

    if (DAT_00A8B8B4) {
        DAT_0087F658.AddItem(new MultiplayerDebugCommandClass);
        DAT_0087F658.AddItem(new MultiplayerSyncCommandClass);
    }
    DAT_0087F658.AddItem(new FollowCommandClass);
    DAT_0087F658.AddItem(new View1CommandClass);
    DAT_0087F658.AddItem(new View2CommandClass);
    DAT_0087F658.AddItem(new View3CommandClass);
    DAT_0087F658.AddItem(new View4CommandClass);
    DAT_0087F658.AddItem(new SetView1CommandClass);
    DAT_0087F658.AddItem(new SetView2CommandClass);
    DAT_0087F658.AddItem(new SetView3CommandClass);
    DAT_0087F658.AddItem(new SetView4CommandClass);
    options = new OptionsCommandClass;
    DAT_0087F658.AddItem(options);
    DAT_0087F658.AddItem(new SidebarUpCommandClass);
    DAT_0087F658.AddItem(new SidebarDownCommandClass);
    centerREvent = new CenterREventCommandClass;
    DAT_0087F658.AddItem(centerREvent);
    DAT_0087F658.AddItem(new BeaconPlacementCommandClass);
    DAT_0087F658.AddItem(new ToggleSellCommandClass);
    DAT_0087F658.AddItem(new ToggleRepairCommandClass);
    DAT_0087F658.AddItem(new AllianceCommandClass);
    DAT_0087F658.AddItem(new CenterBaseCommandClass);
    DAT_0087F658.AddItem(new CenterViewCommandClass);
    DAT_0087F658.AddItem(new ScatterCommandClass);
    DAT_0087F658.AddItem(new GuardCommandClass);
    DAT_0087F658.AddItem(new StopCommandClass);
    DAT_0087F658.AddItem(new AllToCheerCommandClass);
    DAT_0087F658.AddItem(new DeployCommandClass);
    DAT_0087F658.AddItem(new PrevObjectCommandClass);
    DAT_0087F658.AddItem(new NextObjectCommandClass);
    DAT_0087F658.AddItem(new PlanningModeCommandClass);
    DAT_0087F658.AddItem(new CombatantSelectCommandClass);
    DAT_0087F658.AddItem(new TypeSelectCommandClass);
    DAT_0087F658.AddItem(new HealthNavCommandClass);
    DAT_0087F658.AddItem(new VeterancyNavCommandClass);
    DAT_0087F658.AddItem(new SetStructureTabCommandClass);
    DAT_0087F658.AddItem(new SetDefenseTabCommandClass);
    DAT_0087F658.AddItem(new SetUnitTabCommandClass);
    DAT_0087F658.AddItem(new SetInfantryTabCommandClass);
    DAT_0087F658.AddItem(new CreateTeamCommandClass(1));
    DAT_0087F658.AddItem(new CreateTeamCommandClass(2));
    DAT_0087F658.AddItem(new CreateTeamCommandClass(3));
    DAT_0087F658.AddItem(new CreateTeamCommandClass(4));
    DAT_0087F658.AddItem(new CreateTeamCommandClass(5));
    DAT_0087F658.AddItem(new CreateTeamCommandClass(6));
    DAT_0087F658.AddItem(new CreateTeamCommandClass(7));
    DAT_0087F658.AddItem(new CreateTeamCommandClass(8));
    DAT_0087F658.AddItem(new CreateTeamCommandClass(9));
    DAT_0087F658.AddItem(new CreateTeamCommandClass(10));
    DAT_0087F658.AddItem(new SelectTeamCommandClass(1));
    DAT_0087F658.AddItem(new SelectTeamCommandClass(2));
    DAT_0087F658.AddItem(new SelectTeamCommandClass(3));
    DAT_0087F658.AddItem(new SelectTeamCommandClass(4));
    DAT_0087F658.AddItem(new SelectTeamCommandClass(5));
    DAT_0087F658.AddItem(new SelectTeamCommandClass(6));
    DAT_0087F658.AddItem(new SelectTeamCommandClass(7));
    DAT_0087F658.AddItem(new SelectTeamCommandClass(8));
    DAT_0087F658.AddItem(new SelectTeamCommandClass(9));
    DAT_0087F658.AddItem(new SelectTeamCommandClass(10));
    DAT_0087F658.AddItem(new AddTeamCommandClass(1));
    DAT_0087F658.AddItem(new AddTeamCommandClass(2));
    DAT_0087F658.AddItem(new AddTeamCommandClass(3));
    DAT_0087F658.AddItem(new AddTeamCommandClass(4));
    DAT_0087F658.AddItem(new AddTeamCommandClass(5));
    DAT_0087F658.AddItem(new AddTeamCommandClass(6));
    DAT_0087F658.AddItem(new AddTeamCommandClass(7));
    DAT_0087F658.AddItem(new AddTeamCommandClass(8));
    DAT_0087F658.AddItem(new AddTeamCommandClass(9));
    DAT_0087F658.AddItem(new AddTeamCommandClass(10));
    DAT_0087F658.AddItem(new CenterTeamCommandClass(1));
    DAT_0087F658.AddItem(new CenterTeamCommandClass(2));
    DAT_0087F658.AddItem(new CenterTeamCommandClass(3));
    DAT_0087F658.AddItem(new CenterTeamCommandClass(4));
    DAT_0087F658.AddItem(new CenterTeamCommandClass(5));
    DAT_0087F658.AddItem(new CenterTeamCommandClass(6));
    DAT_0087F658.AddItem(new CenterTeamCommandClass(7));
    DAT_0087F658.AddItem(new CenterTeamCommandClass(8));
    DAT_0087F658.AddItem(new CenterTeamCommandClass(9));
    DAT_0087F658.AddItem(new CenterTeamCommandClass(10));
    DAT_0087F658.AddItem(new TauntCommandClass(1));
    DAT_0087F658.AddItem(new TauntCommandClass(2));
    DAT_0087F658.AddItem(new TauntCommandClass(3));
    DAT_0087F658.AddItem(new TauntCommandClass(4));
    DAT_0087F658.AddItem(new TauntCommandClass(5));
    DAT_0087F658.AddItem(new TauntCommandClass(6));
    DAT_0087F658.AddItem(new TauntCommandClass(7));
    DAT_0087F658.AddItem(new TauntCommandClass(8));
    DAT_0087F658.AddItem(new ScreenCaptureCommandClass);
    DAT_0087F658.AddItem(new PageUserCommandClass);
    DAT_0087F658.AddItem(new CursorPositionCommandClass);
    del = new DeleteCommandClass;
    DAT_0087F658.AddItem(del);
    FUN_00533D20();
    if (DAT_0087F680.IsPresent(0x2E)) {
        DAT_0087F680.RemoveIndex(0x2E);
    }
    DAT_0087F680.AddIndex(0x2E, (void* const&)del);
    if (DAT_0087F680.IsPresent(0x1B)) {
        DAT_0087F680.RemoveIndex(0x1B);
    }
    DAT_0087F680.AddIndex(0x1B, (void* const&)options);
    if (DAT_0087F680.IsPresent(0x20)) {
        DAT_0087F680.RemoveIndex(0x20);
    }
    DAT_0087F680.AddIndex(0x20, (void* const&)centerREvent);
}

__forceinline bool IndexClassC::IncreaseTableSize(int amount)
{
    if (amount < 0) return false;

    int total = IndexSize + amount;
    NodeElement* table = new NodeElement[total];
    if (table != 0) {

        for (int index = 0; index < IndexCount; index++) {
            table[index] = IndexTable[index];
        }

        FUN_007C8B3D(IndexTable);
        IndexTable = table;
        IndexSize += amount;
        Archive = 0;

        return true;
    }

    return false;
}

__forceinline IndexClassC::NodeElement* IndexClassC::SearchForNode(const int& id) const
{
    if (!IsSorted) {
        FUN_007C8B48(IndexTable, IndexCount, sizeof(NodeElement), &Comparator);
        ((IndexClassC*)this)->Archive = 0;
        ((IndexClassC*)this)->IsSorted = true;
    }

    int num = IndexCount;
    int key = id;
    NodeElement* base = IndexTable;

    while (num > 0) {
        int half = num / 2;
        NodeElement* mid = &base[half];

        if (mid->ID > key) {
            num = half;
        } else {
            if (mid->ID == key) {
                return mid;
            }
            base = mid + 1;
            num += -1 - half;
        }
    }

    return 0;
}

__forceinline bool IndexClassC::IsPresentImpl(const int& id) const
{
    if (IndexCount == 0) {
        return false;
    }

    if (Archive != 0 && Archive->ID == id) {
        return true;
    }

    NodeElement* nodeptr = SearchForNode(id);

    if (nodeptr != 0) {
        ((IndexClassC*)this)->Archive = nodeptr;
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x5387D0
bool IndexClassC::AddIndex(const int& id, void* const& data)
{
    if (IndexCount + 1 > IndexSize) {
        if (!IncreaseTableSize(IndexSize == 0 ? 10 : IndexSize)) {
            return false;
        }
    }

    IndexTable[IndexCount].ID = id;
    IndexTable[IndexCount].Data = data;
    IndexCount++;
    IsSorted = false;

    return true;
}

// FUNCTION: GAMEMD 0x5388A0
bool IndexClassC::RemoveIndex(const int& id)
{
    NodeElement* nodeptr = 0;

    if (IndexCount != 0) {
        if (!IsSorted) {
            FUN_007C8B48(IndexTable, IndexCount, sizeof(NodeElement), &Comparator);
            Archive = 0;
            IsSorted = true;
        }

        int num = IndexCount;
        NodeElement elem;
        elem.ID = id;
        NodeElement* base = IndexTable;

        while (num > 0) {
            int half = num / 2;
            NodeElement* mid = &base[half];

            if (elem.ID < mid->ID) {
                num = half;
            } else {
                if (mid->ID == elem.ID) {
                    nodeptr = mid;
                    break;
                }
                base = mid + 1;
                num += -1 - half;
            }
        }

        if (nodeptr != 0) {
            int found_index = nodeptr - IndexTable;

            if (found_index != -1) {

                for (int index = found_index + 1; index < IndexCount; index++) {
                    IndexTable[index - 1] = IndexTable[index];
                }

                IndexCount--;
                NodeElement zero;
                zero.ID = 0;
                zero.Data = 0;
                IndexTable[IndexCount] = zero;
                Archive = 0;

                return true;
            }
        }
    }

    return false;
}

// FUNCTION: GAMEMD 0x538980
bool IndexClassC::IsPresent(const int& id) const
{
    return IsPresentImpl(id);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x538B80
bool GrowPairVector::Grow_538B80(int extra)
{
    GrowPair* grown;
    int total;
    int i;

    if (extra < 0) goto fail;

    total = Capacity + extra;
    grown = new GrowPair[total];
    if (grown == 0) goto fail;

    for (i = 0; i < Count; i++) {
        int off = i * 8;
        GrowPair* src = (GrowPair*)((char*)Items + off);
        *(GrowPair*)((char*)grown + off) = *src;
    }

    delete[] Items;

    Items    = grown;
    Capacity = Capacity + extra;
    Cached   = 0;
    return true;

fail:
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x538D40
// For every pair of palette colours, store the index of the palette colour
// nearest (squared RGB distance) to their average.
void __cdecl FUN_00538D40(void)
{
    const unsigned char* src = DAT_00A8F918;
    for (int i = 0; i < 256; i++) {
        int r0 = *src++;
        int g0 = *src++;
        int b0 = *src++;
        const unsigned char* other = DAT_00A8F918;
        for (int j = 0; j < 256; j++) {
            int r = (*other++ + r0) >> 1;
            int g = (*other++ + g0) >> 1;
            int b = (*other++ + b0) >> 1;
            int best = 0;
            int bestdist = 500000;
            const unsigned char* pal = DAT_00A8F918;
            for (int k = 0; k < 256; k++) {
                int dr = *pal++ - r;
                int dg = *pal++ - g;
                int db = *pal++ - b;
                int dist = dr * dr + dg * dg + db * db;
                if (dist < bestdist) {
                    bestdist = dist;
                    best = k;
                }
            }
            DAT_00A8F91C[i][j] = best;
        }
    }
    DAT_00A9F91C = 0;
}
