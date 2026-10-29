// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Original translation unit netshare.cpp. The name is the source-file string at 0x8317d8
//   in retail gamemd.exe v1.001, passed by the assert at 0x5e3a50 inside this object's
//   code range (0x5e2430-0x5ef18f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   Bytes matched against the user's retail gamemd.exe v1.001 over
//   0x5E8740..0x5E957E. Layout evidence and the retail source-file name are
//   documented in netshare_slot_nodes.h.
//   Three of the bodies here — 0x5E8760, 0x5E93F0 and 0x5E94A0 — are not
//   in the Ghidra function list, and were found by sweeping
//   the address run as raw bytes and reading the twelve-byte 0x90 pads that
//   separate functions. NodeNameType and IPXAddressClass are retail RTTI
//   names; their members sit where the disassembly places them.
//
//   LIBRARY: GAMEMD 0x7CA5D3 wcscmp, 0x7DD0F8 _wcsicmp, 0x7C8D20 _stricmp,
//   0x7C8B3D operator delete (all reloc).

#include "../economy/netshare_slot_nodes.h"
#include "../core/mathtbl_init_shapes.h"

// The playable count as the two release paths want it: one extra slot opens up
// when the extra-slot flag is clear and there is room for it.
static __forceinline int Releasable_Slot_Count()
{
    int playable;
    if (SessionKind == 4) {
        if (Is_005E8AE0_A() && !Is_005E8AE0_B()) {
            playable = 2;
        } else {
            playable = 6;
        }
    } else {
        playable = 8;
    }

    if (NoExtraSlot == 0 && playable < 7) {
        playable++;
    }
    return playable;
}

#include "../economy/trivial_tu161_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EEF18
extern const double DAT_007EEF18;
// GLOBAL: GAMEMD 0xAC0CE8
extern double DAT_00AC0CE8;


// ---- from the former netshare_chat_005e2670.cpp ----
//   Bytes matched against the user's retail gamemd.exe v1.001, 0x5E2670..0x5E2CCF.
//   The unit is netshare.cpp (path string at 0x8317D8). This run is its
//   lobby chat log: a string hash, the formatted append to the chat list
//   control (dialog item 0x53F), the word-wrapper, the one-line list-box
//   append, and the two house counters.
//
//   The chat control is a list box: 0x18B / 0x18E / 0x182 / 0x197 / 0x1A1 are
//   its LB_GETCOUNT / LB_GETTOPINDEX / LB_DELETESTRING / LB_SETCURSEL /
//   LB_GETITEMHEIGHT messages; 0x49D, 0x49E, 0x4A0, 0x498 and 0x4CD are
//   user-range messages whose handlers are not part of this run.
//
//   LIBRARY: GAMEMD 0x7CA858 vswprintf, 0x7CA405 wcslen, 0x7CA422 wcsncpy,
//   0x7CA8C6 wcschr, 0x7DDE13 _wcsdup, 0x7C93E8 free, 0x7CB8E6 iswgraph.

#include "../economy/netshare_win.h"
#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"

// GLOBAL: GAMEMD 0xA8022C -- HouseClass::Array.Items (Count at 0xA80238).
extern HouseClass** DAT_00A8022C;
// GLOBAL: GAMEMD 0xA80238
extern int DAT_00A80238;
// GLOBAL: GAMEMD 0xAC029C -- the 1 KiB scratch line for the list-box append.
extern wchar_t DAT_00AC029C[512];


// Raw PBVMultiMission RTTI identifies const pointer elements and the
// DynamicVectorClass -> VectorClass zero-offset base chain.
// Complete entry-origin spans establish all bound methods. GX emits shorter
// derived deleting wrappers; no GX reproduces the retail 0x49-byte bodies.
// Only the listed constructor is claimed; no TypeList specialization is bound.
// Original TU boundaries,
// final link and complete object sizes remain unestablished.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "../core/vector_class_operations.h"
class MultiMission;

// VTABLE: GAMEMD 0x7EEF50 -- VectorClass<const MultiMission*>.
template class VectorClass<const MultiMission*>;
typedef VectorClass<const MultiMission*> GgMultiMissionVectorClass;
GG_STATIC_ASSERT(offsetof(GgMultiMissionVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMultiMissionVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMultiMissionVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMultiMissionVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EEF70 -- DynamicVectorClass<const MultiMission*>.
template class DynamicVectorClass<const MultiMission*>;
typedef DynamicVectorClass<const MultiMission*> GgMultiMissionDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgMultiMissionDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMultiMissionDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMultiMissionDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMultiMissionDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMultiMissionDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMultiMissionDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(const MultiMission*) == 4);

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5EEBB0
// DynamicVectorClass<const MultiMission*>::Clear

// FUNCTION: GAMEMD 0x5EEBE0
// DynamicVectorClass<const MultiMission*>::Slot5

// FUNCTION: GAMEMD 0x5EEC00
// VectorClass<const MultiMission*>::Slot6

// FUNCTION: GAMEMD 0x5EEC10
// VectorClass<const MultiMission*>::operator==

// FUNCTION: GAMEMD 0x5EEC50
// VectorClass<const MultiMission*>::SetCapacity

// FUNCTION: GAMEMD 0x5EED00
// VectorClass<const MultiMission*>::Clear

// FUNCTION: GAMEMD 0x5EED30
// VectorClass<const MultiMission*>::FindItemIndex

// FUNCTION: GAMEMD 0x5EED70
// VectorClass<const MultiMission*>::Slot5

// FUNCTION: GAMEMD 0x5EED90
// DynamicVectorClass<const MultiMission*>::SetCapacity

// FUNCTION: GAMEMD 0x5EEE90
// DynamicVectorClass<const MultiMission*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x5EEEC0
// VectorClass<const MultiMission*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x5EEF10
// DynamicVectorClass<const MultiMission*>::scalar deleting destructor

// FUNCTION: GAMEMD 0x5EF0B0
// VectorClass<const MultiMission*>::capacity constructor

// FUNCTION: GAMEMD 0x623F60 (decl; reloc) -- __fastcall: read list item
// `index` of the list box into the string.
void FUN_00623F60(HWND window, int index, Obj_007B66D0* out);

// STRING: GAMEMD 0x831774
extern const wchar_t DAT_00831774[];

// ---- from the former netshare_dialogs_005e2cd0.cpp ----
//   Bytes matched against the user's retail gamemd.exe v1.001, 0x5E2CD0..0x5E3004.
//   netshare.cpp (path string at 0x8317D8): the lobby's message-box helper and
//   its dialog procedure, the game-mode name field, the lobby-mode refresh
//   and the "advance" virtual dispatch.
//
//   LIBRARY: GAMEMD 0x7CA405 wcslen; imports GetDlgItem 0x7E14A8,
//   SendMessageA 0x7E14A4, SendDlgItemMessageA 0x7E1490, GetWindowLongA
//   0x7E1474, SetWindowLongA 0x7E1470, ShowWindow 0x7E1498, ValidateRect 0x7E1478.

#include "../economy/netshare_win.h"
#include "multiplayer_game_mode.h"
#include "mp_game_mode_class_get_methods.h"

// GLOBAL: GAMEMD 0xB732F0 -- the dialog factory context handed to 0x775700.
extern void* DAT_00B732F0;
// GLOBAL: GAMEMD 0xB73550 -- the main window.
extern HWND DAT_00B73550;
// GLOBAL: GAMEMD 0xA8B23C -- the live game-mode object, or null.
extern MultiplayerGameMode* DAT_00A8B23C;

// FUNCTION: GAMEMD 0x775700 (decl; reloc) -- __fastcall: create the dialog
// with template `id` under the parent, with the given procedure.
HWND FUN_00775700(void* context, int id, HWND parent, void* proc, int param);

// FUNCTION: GAMEMD 0x622820 (decl; reloc) -- __fastcall: set the dialog up.
void FUN_00622820(HWND dialog, int id);

// FUNCTION: GAMEMD 0x60B350 (decl; reloc) -- __fastcall: mark the control.
void FUN_0060B350(HWND control);

// FUNCTION: GAMEMD 0x7759E0 (decl; reloc) -- __fastcall: run the dialog.
int FUN_007759E0(HWND dialog, void* callback, int a, char b, char c);

// FUNCTION: GAMEMD 0x621E90 (decl; reloc) -- __fastcall on the window.
void FUN_00621E90(HWND window);

// FUNCTION: GAMEMD 0x607FD0 (decl; reloc) -- __fastcall on the window.
void FUN_00607FD0(HWND window);

// FUNCTION: GAMEMD 0x6213A0 (decl; reloc) -- __fastcall on the owner-draw
// item the message carries.
void FUN_006213A0(void* item);

// FUNCTION: GAMEMD 0x7757E0 (decl; reloc) -- __fastcall: end the dialog with
// the command id.
void FUN_007757E0(HWND dialog, int id);

// FUNCTION: GAMEMD 0x5D5E10 (decl; reloc) -- no arguments; reached as a tail jump.
void __cdecl FUN_005D5E10();

// ---- from the former netshare_lobby_open_005e68a0.cpp ----
//   Bytes matched against the user's retail gamemd.exe v1.001, 0x5E68A0..0x5E691F
//   and 0x5E7460..0x5E74DD. netshare.cpp (path string at 0x8317D8): the lobby
//   dialog opener and the pregame setup that publishes the lobby's choices.
//
//   Imports: SendMessageA 0x7E14A4, ShowWindow 0x7E1498.

#include "../economy/netshare_win.h"
#include "../economy/netshare_slot_nodes.h"

// GLOBAL: GAMEMD 0xB732F0 -- the dialog factory context handed to 0x775700.
extern void* DAT_00B732F0;
// GLOBAL: GAMEMD 0xAC0D40 -- the lobby dialog.
extern HWND DAT_00AC0D40;
// GLOBAL: GAMEMD 0xA8B254 -- the selected map's list index.
extern int DAT_00A8B254;
// GLOBAL: GAMEMD 0xA8B54C
extern int DAT_00A8B54C;
// GLOBAL: GAMEMD 0xA8B24C
extern int DAT_00A8B24C;
// GLOBAL: GAMEMD 0xA8ED84 -- Unsorted::CurrentFrame.
extern int DAT_00A8ED84;
// GLOBAL: GAMEMD 0xA8EB60
extern int DAT_00A8EB60;
// GLOBAL: GAMEMD 0xA8B268
extern int DAT_00A8B268;
// GLOBAL: GAMEMD 0xA8B260 / 0xA8B31D -- two lobby option bytes (bit 0 is read).
extern unsigned char DAT_00A8B260;
extern unsigned char DAT_00A8B31D;
// STRING: GAMEMD 0x831A60 "Pregame setup for %d players.\n"
extern const char DAT_00831A60[];

// ScenarioClass::Instance (0xA8B230): only the +0x1254 member is stored here.
struct Obj_00A8B230
{
    char unknown_00[0x1254];  // +0x0000
    int unknown_1254;         // +0x1254
};
GG_STATIC_ASSERT(offsetof(Obj_00A8B230, unknown_1254) == 0x1254);
// GLOBAL: GAMEMD 0xA8B230
extern Obj_00A8B230* DAT_00A8B230;

// The object at 0xA8E960: a flags dword at +0x00, and the empty member 0x6B8B10
// reached as a tail jump with ECX = its address.
struct Obj_00A8E960
{
    unsigned int unknown_00;  // +0x00
    // FUNCTION: GAMEMD 0x6B8B10 (decl; reloc) -- __thiscall, no arguments.
    void FUN_006B8B10();
};
// GLOBAL: GAMEMD 0xA8E960
extern Obj_00A8E960 DAT_00A8E960;

// FUNCTION: GAMEMD 0x52FEC0 (decl; reloc) -- __fastcall (null, flag).
void FUN_0052FEC0(void* unused, unsigned char flag);

// FUNCTION: GAMEMD 0x72D120 (decl; reloc) -- no arguments.
void __cdecl FUN_0072D120();

// FUNCTION: GAMEMD 0x72D170 (decl; reloc) -- no arguments.
void __cdecl FUN_0072D170();

// FUNCTION: GAMEMD 0x775700 (decl; reloc) -- __fastcall: create the dialog with
// template `id` under the parent, with the given procedure.
HWND FUN_00775700(void* context, int id, HWND parent, void* proc, int param);

// FUNCTION: GAMEMD 0x622820 (decl; reloc) -- __fastcall: set the dialog up.
void FUN_00622820(HWND dialog, int id);

// FUNCTION: GAMEMD 0x7759E0 (decl; reloc) -- __fastcall: run the dialog.
int FUN_007759E0(HWND dialog, void* callback, int a, char b, char c);

// FUNCTION: GAMEMD 0x5E6920 (decl; reloc) -- the lobby dialog procedure.
int __stdcall FUN_005E6920(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

// FUNCTION: GAMEMD 0x5E66F0 (decl; reloc) -- the lobby's idle callback.
unsigned int __cdecl FUN_005E66F0();

// ---- from the former netshare_lobby_send_005e35a0.cpp ----
//   Bytes matched against the user's retail gamemd.exe v1.001, 0x5E35A0..0x5E3A9F.
//   netshare.cpp (path string at 0x8317D8): the lobby's broadcast senders. Each
//   builds a NetsharePacket (netshare_common.h) addressed to every remote player
//   (slots 1 .. count-1) through the manager at 0xA8E9C0, or hands the text to
//   the link object at 0xAC116C when there is one.
//
//   LIBRARY: GAMEMD 0x7C91D0 strncpy; strcpy is the inline expansion.

#include "../economy/netshare_common.h"
#include "../economy/netshare_slot_nodes.h"

// GLOBAL: GAMEMD 0xA8DAB0
extern unsigned char DAT_00A8DAB0;

// FUNCTION: GAMEMD 0x7A2750 (decl; reloc) -- no arguments, reached as a tail jump.
void __cdecl FUN_007A2750();

// FUNCTION: GAMEMD 0x5E2340 (decl; reloc) -- no arguments, reached as a tail jump.
void __cdecl FUN_005E2340();

// STRING: GAMEMD 0x831778 "Sending public game options to %s\n"
extern const char DAT_00831778[];
// STRING: GAMEMD 0x83179C "Sending private game options to %ls\n"
extern const char DAT_0083179C[];

static inline int Find_Player_By_Handle(const char* handle)
{
    for (int i = 0; i < PlayerNodes.Count; i++) {
        if (_stricmp(Narrow_007350C0(PlayerNodes.Vector[i]->Name), handle) == 0) {
            return i;
        }
    }
    return -1;
}

// ---- from the former netshare_lobby_sync_005e32d0.cpp ----
//   Bytes matched against the user's retail gamemd.exe v1.001, 0x5E32D0..0x5E359A.
//   netshare.cpp (path string at 0x8317D8): the lobby's change detector. It
//   compares the live lobby options with the shadow copies kept from the last
//   publication and, when anything changed (or one is forced, or enough time has
//   passed), refreshes the shadows and sends the options string.
//
//   LIBRARY: GAMEMD 0x7CA67F time, 0x7DD0F8 _wcsicmp, 0x7C8D20 _stricmp, 0x7CA489
//   wcscpy; strcpy is the inline expansion.

#include "../economy/netshare_common.h"

extern "C" {
// LIBRARY: GAMEMD 0x7CA67F (decl; reloc) -- CRT time.
long __cdecl time(long* timer);
// LIBRARY: GAMEMD 0x7DD0F8 (decl; reloc) -- CRT _wcsicmp.
int __cdecl _wcsicmp(const wchar_t* a, const wchar_t* b);
// LIBRARY: GAMEMD 0x7C8D20 (decl; reloc) -- CRT _stricmp.
int __cdecl _stricmp(const char* a, const char* b);
// LIBRARY: GAMEMD 0x7CA489 (decl; reloc) -- CRT wcscpy.
wchar_t* __cdecl wcscpy(wchar_t* dst, const wchar_t* src);
}

// The live lobby options (read) ...
// GLOBAL: GAMEMD 0xA8B268, 0xA8B25C, 0xA8B270
extern int DAT_00A8B268;
extern int DAT_00A8B25C;
extern int DAT_00A8B270;
// GLOBAL: GAMEMD 0xA8B262, 0xA8B263, 0xA8B264, 0xA8B320, 0xA8B261
extern unsigned char DAT_00A8B262;
extern unsigned char DAT_00A8B263;
extern unsigned char DAT_00A8B264;
extern unsigned char DAT_00A8B320;
extern unsigned char DAT_00A8B261;
// GLOBAL: GAMEMD 0xA8B8E0 / 0xA8BAE2 -- two option strings (narrow).
extern char DAT_00A8B8E0[];
extern char DAT_00A8BAE2[];
// GLOBAL: GAMEMD 0xA8BB04 / 0xA8BB08
extern int DAT_00A8BB04;
extern unsigned char DAT_00A8BB08;

// ... and their shadow copies from the last publication.
// GLOBAL: GAMEMD 0x8316D8, 0x8316DC, 0x8316E0, 0x8316E8
extern int DAT_008316D8;
extern int DAT_008316DC;
extern int DAT_008316E0;
extern int DAT_008316E8;
// GLOBAL: GAMEMD 0x8316E4
extern unsigned char DAT_008316E4;
// GLOBAL: GAMEMD 0xAC11BD, 0xAC11BE, 0xAC11BF, 0xAC11C0, 0xAC11C1
extern unsigned char DAT_00AC11BD;
extern unsigned char DAT_00AC11BE;
extern unsigned char DAT_00AC11BF;
extern unsigned char DAT_00AC11C0;
extern unsigned char DAT_00AC11C1;
// GLOBAL: GAMEMD 0xAC10F0 -- shadow of the wide string at 0xA8B322 (44 characters;
// the code zeroes the last one, 0xAC1146, before comparing).
extern wchar_t DAT_00AC10F0[44];
// GLOBAL: GAMEMD 0xAC0CF0 / 0xAC0D00 -- shadows of the narrow strings at 0xA8B8E0 and
// 0xA8BAE2 (the code zeroes the byte past each, 0xAC0CFD and 0xAC0D20, before comparing).
extern char DAT_00AC0CF0[14];
extern char DAT_00AC0D00[33];
// GLOBAL: GAMEMD 0xAC11B8 -- the time of the last publication.
extern long DAT_00AC11B8;
// GLOBAL: GAMEMD 0xAC11BC -- a publication was asked for during the same second.
extern unsigned char DAT_00AC11BC;

// FUNCTION: GAMEMD 0x77E430 (decl; reloc) -- __fastcall: fill the options string (link form).
void FUN_0077E430(char* buffer);

// FUNCTION: GAMEMD 0x5DBB60 (decl; reloc) -- __fastcall: fill the options string (local form).
void FUN_005DBB60(char* buffer);

// The change detector of 0x5E32D0, inlined with its arguments into 0x5EC290.
static __forceinline void Publish_Options_Inline(char force, char poll)
{
    bool changed = false;
    if (time(0) - DAT_00AC11B8 == 0) {
        if (force) {
            DAT_00AC11BC = 1;
        }
        if (!poll) {
            return;
        }
    }
    if (DAT_00AC11BC) {
        force = 1;
    }
    DAT_00AC11BC = 0;
    if (DAT_00AC116C != 0) {
        if (time(0) - DAT_00AC11B8 >= 5) {
            changed = true;
        }
    } else if (time(0) - DAT_00AC11B8 >= 2) {
        changed = true;
    }
    if (force) {
        changed = true;
    }
    if (DAT_008316D8 != DAT_00A8B268) {
        changed = true;
    }
    if (DAT_008316DC != DAT_00A8B25C) {
        changed = true;
    }
    if (DAT_008316E0 != DAT_00A8B270) {
        changed = true;
    }
    if (DAT_00AC11BD != DAT_00A8B262) {
        changed = true;
    }
    if (DAT_00AC11BE != DAT_00A8B263) {
        changed = true;
    }
    if (DAT_00AC11BF != DAT_00A8B264) {
        changed = true;
    }
    if (DAT_00AC11C0 != DAT_00A8B320) {
        changed = true;
    }
    if (DAT_00AC11C1 != DAT_00A8B261) {
        changed = true;
    }
    DAT_00AC10F0[43] = 0;
    if (_wcsicmp(DAT_00AC10F0, DAT_00A8B322) != 0) {
        changed = true;
    }
    DAT_00AC0CF0[13] = 0;
    if (_stricmp(DAT_00AC0CF0, DAT_00A8B8E0) != 0) {
        changed = true;
    }
    DAT_00AC0D00[32] = 0;
    if (_stricmp(DAT_00AC0D00, DAT_00A8BAE2) != 0) {
        changed = true;
    }
    if (DAT_008316E8 != DAT_00A8BB04) {
        changed = true;
    }
    if (DAT_008316E4 != DAT_00A8BB08 || changed) {
        DAT_00AC11B8 = time(0);
        DAT_008316D8 = DAT_00A8B268;
        DAT_008316DC = DAT_00A8B25C;
        DAT_008316E0 = DAT_00A8B270;
        DAT_00AC11BD = DAT_00A8B262;
        DAT_00AC11BE = DAT_00A8B263;
        DAT_00AC11BF = DAT_00A8B264;
        DAT_00AC11C0 = DAT_00A8B320;
        DAT_00AC11C1 = DAT_00A8B261;
        wcscpy(DAT_00AC10F0, DAT_00A8B322);
        strcpy(DAT_00AC0D00, DAT_00A8BAE2);
        strcpy(DAT_00AC0CF0, DAT_00A8B8E0);
        DAT_008316E8 = DAT_00A8BB04;
        DAT_008316E4 = DAT_00A8BB08;
        char buffer[0x208];
        memset(buffer, 0, sizeof(buffer));
        if (DAT_00AC116C != 0) {
            FUN_0077E430(buffer);
            FUN_005E3720(buffer);
            return;
        }
        FUN_005DBB60(buffer);
        FUN_005E3720(buffer);
    }
}

// ---- from the former netshare_lobby_ui_005ee200.cpp ----
//   Bytes matched against the user's retail gamemd.exe v1.001, 0x5EE200..0x5EE348.
//   netshare.cpp (path string at 0x8317D8): the lobby's observer-mode refresh. The
//   string-table fetches carry this file's path and line numbers (0x1A5F..0x1A70).
//
//   Imports: GetDlgItem 0x7E14A8, SendMessageA 0x7E14A4, InvalidateRect 0x7E149C.

#include "../economy/netshare_slot_inline.h"
#include "../renderer/pcx_get_surface_methods.h"

// GLOBAL: GAMEMD 0xAC10C8 -- nonzero when the local player joins as an observer.
extern int DAT_00AC10C8;
// GLOBAL: GAMEMD 0xAC4848 -- the loaded-PCX table.
extern PCX DAT_00AC4848;

// FUNCTION: GAMEMD 0x603D30 (decl; reloc) -- __fastcall: put a surface on a control.
void FUN_00603D30(HWND control, void* surface);

// FUNCTION: GAMEMD 0x775940 (decl; reloc) -- __fastcall: the open dialog with a template id, or null.
HWND FUN_00775940(int id);

// ---- from the former netshare_slot_controls_005e9950.cpp ----
//   Bytes matched against the user's retail gamemd.exe v1.001, 0x5E9950..0x5EA0CF
//   (the matched functions only). netshare.cpp (path string at 0x8317D8): the
//   lobby's slot controls: control-id inverse, the slot-kind caption, combo-box
//   helpers, and the readers that copy a slot's controls back into the choice
//   tables (and, for the local player's own slot, into the player node).
//
//   The lobby dialogs are combo boxes: 0x146 / 0x147 / 0x150 / 0x14E are
//   CB_GETCOUNT / CB_GETCURSEL / CB_GETITEMDATA / CB_SETCURSEL.

#include "../economy/netshare_win.h"
#include "../economy/netshare_slot_inline.h"

// GLOBAL: GAMEMD 0xA8B27C -- a per-slot choice table (eight ints) cleared with
// the start table when a slot stops being an AI.
extern int DAT_00A8B27C[8];
// GLOBAL: GAMEMD 0xA8B29C -- the start-position choice table (eight ints).
extern int DAT_00A8B29C[8];
// GLOBAL: GAMEMD 0xA8B2FC -- the team-choice table (eight ints).
extern int DAT_00A8B2FC[8];

// STRING: GAMEMD 0x831D34 "STT:PlayerOpen"
extern char PlayerOpenLabel[];
// STRING: GAMEMD 0x831D20 "STT:PlayerClosed"
extern char PlayerClosedLabel[];
// STRING: GAMEMD 0x831D0C "STT:PlayerDumbAI"
extern char PlayerDumbAILabel[];
// STRING: GAMEMD 0x831CF8 "STT:PlayerSmartAI"
extern char PlayerSmartAILabel[];
// STRING: GAMEMD 0x831CE4 "STT:PlayerGeniusAI"
extern char PlayerGeniusAILabel[];
// STRING: GAMEMD 0x831CCC "STT:PlayerOpenObserver"
extern char PlayerOpenObserverLabel[];
// STRING: GAMEMD 0x831CBC "STT:PlayerHuman"
extern char PlayerHumanLabel[];

// FUNCTION: GAMEMD 0x4E4170 (decl; reloc) -- __fastcall: the start-position
// control's value (dialog, control id, default), RET 4.
int FUN_004E4170(HWND dialog, int control, int fallback);

// FUNCTION: GAMEMD 0x4E3830 (decl; reloc) -- __fastcall: the slot a start-position control belongs to.
int FUN_004E3830(int control);

// FUNCTION: GAMEMD 0x775940 (decl; reloc) -- __fastcall: the open dialog with a template id, or null.
HWND FUN_00775940(int id);

// FUNCTION: GAMEMD 0x4E4E20 (decl; reloc) -- __fastcall: the house control's value, RET 4.
int FUN_004E4E20(HWND dialog, int control, int fallback);

// FUNCTION: GAMEMD 0x4E4230 (decl; reloc) -- __fastcall: the slot a house control belongs to.
int FUN_004E4230(int control);

// FUNCTION: GAMEMD 0x4E4C20 (decl; reloc) -- __fastcall (dialog, control).
void FUN_004E4C20(HWND dialog, int control);

// FUNCTION: GAMEMD 0x4E5900 (decl; reloc) -- __fastcall: the colour control's value, RET 4.
int FUN_004E5900(HWND dialog, int control, int fallback);

// FUNCTION: GAMEMD 0x4E4EC0 (decl; reloc) -- __fastcall: the slot a colour control belongs to.
int FUN_004E4EC0(int control);

// FUNCTION: GAMEMD 0x4E5700 (decl; reloc) -- __fastcall (dialog, control).
void FUN_004E5700(HWND dialog, int control);

// FUNCTION: GAMEMD 0x4E6030 (decl; reloc) -- __fastcall: the team control's value, RET 4.
int FUN_004E6030(HWND dialog, int control, int fallback);

// FUNCTION: GAMEMD 0x4E59A0 (decl; reloc) -- __fastcall: the slot a team control belongs to.
int FUN_004E59A0(int control);

// ---- from the former netshare_slot_enable_005e9e70.cpp ----
//   Bytes matched against the user's retail gamemd.exe v1.001, 0x5E9E70..0x5EA3DF
//   (the matched functions only). netshare.cpp (path string at 0x8317D8): the
//   lobby's per-slot control state, the all-slots passes over it, and the slot
//   status pictures.
//
//   Imports: GetDlgItem 0x7E14A8, EnableWindow 0x7E14A0, ShowWindow 0x7E1498.

#include "../economy/netshare_slot_inline.h"
#include "../renderer/pcx_get_surface_methods.h"

// GLOBAL: GAMEMD 0xA8B254 -- the selected map's list index, -1 when none.
extern int DAT_00A8B254;
// GLOBAL: GAMEMD 0xAC4848 -- the loaded-PCX table.
extern PCX DAT_00AC4848;
// GLOBAL: GAMEMD 0x8316CC / 0x8316D0 -- the host and accepted status picture names.
extern const char* DAT_008316CC;
extern const char* DAT_008316D0;

// GLOBAL: GAMEMD 0xA8B27C, 0xA8B29C, 0xA8B2BC -- per-slot choice tables (eight ints each).
extern int DAT_00A8B27C[8];
extern int DAT_00A8B29C[8];
extern int DAT_00A8B2BC[8];

// FUNCTION: GAMEMD 0x5EC9F0 (decl; reloc) -- __fastcall: refresh one slot's kind
// control from a node (dialog, control, node, flag), RET 8.
void FUN_005EC9F0(HWND dialog, int control, NodeNameType* node, int flag);

// FUNCTION: GAMEMD 0x5EB7B0 (decl; reloc) -- __fastcall (dialog, first, count), RET 4.
void FUN_005EB7B0(HWND dialog, int first, int count);

// FUNCTION: GAMEMD 0x5DAFD0 (decl; reloc) -- no arguments.
void __cdecl FUN_005DAFD0();

// FUNCTION: GAMEMD 0x603D30 (decl; reloc) -- __fastcall: put a surface on a control.
void FUN_00603D30(HWND control, void* surface);

// The status-picture control of slot `index` (0x6D2 + index), -1 outside 0..7.
static __forceinline int Slot_Picture_Control(int index)
{
    if (index == 0) {
        return 0x6D2;
    }
    if (index == 1) {
        return 0x6D3;
    }
    if (index == 2) {
        return 0x6D4;
    }
    if (index == 3) {
        return 0x6D5;
    }
    if (index == 4) {
        return 0x6D6;
    }
    if (index == 5) {
        return 0x6D7;
    }
    if (index == 6) {
        return 0x6D8;
    }
    return index == 7 ? 0x6D9 : -1;
}

// ---- from the former netshare_slot_list_005e8dc0.cpp ----
//   Bytes matched against the user's retail gamemd.exe v1.001, 0x5E8DC0..0x5E8E95.
//   netshare.cpp (path string at 0x8317D8): the comma-separated slot list of the
//   lobby options string.
//
//   LIBRARY: GAMEMD 0x7CA45F wcscat.

#include "../economy/netshare_common.h"
#include "../economy/netshare_slot_nodes.h"
#include "../core/string_class.h"

extern "C" {
// LIBRARY: GAMEMD 0x7CA45F (decl; reloc) -- CRT wcscat.
wchar_t* __cdecl wcscat(wchar_t* dst, const wchar_t* src);
}

// FUNCTION: GAMEMD 0x5EDEF0 (decl; reloc) -- the slot-kind token of a node,
// returned through the hidden first argument (netshare_slot_names_005edef0.cpp).
Wstring FUN_005EDEF0(NodeNameType* node);

// FUNCTION: GAMEMD 0x7B7ED0 (decl; reloc) -- the wide copy of a narrow string,
// returned through the hidden first argument.
Obj_007B66D0 FUN_007B7ED0(const Wstring& narrow);

// STRING: GAMEMD 0x8304FC -- L","
extern const wchar_t DAT_008304FC[];

// ---- from the former netshare_slot_misc_005ed270.cpp ----
//   Bytes matched against the user's retail gamemd.exe v1.001, 0x5ED270..0x5EE6EF
//   (the matched functions only). netshare.cpp (path string at 0x8317D8): lobby
//   dialog routines over the slot controls and the player-name edit field.

#include "../economy/netshare_slot_inline.h"

// FUNCTION: GAMEMD 0x5EC9F0 (decl; reloc) -- __fastcall: refresh one slot's
// kind control from a node (dialog, control, node, flag), RET 8.
void FUN_005EC9F0(HWND dialog, int control, NodeNameType* node, int flag);

// FUNCTION: GAMEMD 0x5EE200 (decl; reloc) -- __fastcall on a lobby dialog.
void FUN_005EE200(HWND dialog);

// FUNCTION: GAMEMD 0x775940 (decl; reloc) -- __fastcall: the open dialog with a template id, or null.
HWND FUN_00775940(int id);

// FUNCTION: GAMEMD 0x623EA0 (decl; reloc) -- __fastcall: read a control's text into a string.
int FUN_00623EA0(HWND control, Obj_007B66D0* out);

// FUNCTION: GAMEMD 0x4E5700 (decl; reloc) -- __fastcall (dialog, control).
void FUN_004E5700(HWND dialog, int control);

// FUNCTION: GAMEMD 0x4E5900 (decl; reloc) -- __fastcall: the colour control's value, RET 4.
int FUN_004E5900(HWND dialog, int control, int fallback);

// FUNCTION: GAMEMD 0x5EB7B0 (decl; reloc) -- __fastcall (dialog, first, count), RET 4.
void FUN_005EB7B0(HWND dialog, int first, int count);

// FUNCTION: GAMEMD 0x5EBA00 (decl; reloc) -- __fastcall on the lobby dialog.
void FUN_005EBA00(HWND dialog);

// FUNCTION: GAMEMD 0x5EBC00 (decl; reloc) -- __fastcall (dialog, count).
void FUN_005EBC00(HWND dialog, int count);

// FUNCTION: GAMEMD 0x785360 (decl; reloc) -- no arguments.
void __cdecl FUN_00785360();

// FUNCTION: GAMEMD 0x5DAFD0 (decl; reloc) -- no arguments.
void __cdecl FUN_005DAFD0();

// Declarations of 0x4E37D0 and 0x4E41D0 are in netshare_win.h.
// FUNCTION: GAMEMD 0x4E4170 (decl; reloc) -- __fastcall: the start-position control's value, RET 4.
int FUN_004E4170(HWND dialog, int control, int fallback);

// FUNCTION: GAMEMD 0x4E4E20 (decl; reloc) -- __fastcall: the house control's value, RET 4.
int FUN_004E4E20(HWND dialog, int control, int fallback);

// The selected mode is GameModeOptions.unknown_00 in the shared layout.

// GLOBAL: GAMEMD 0xA8B254 -- the selected map's list index.
extern int DAT_00A8B254;
// GLOBAL: GAMEMD 0xA8B268, 0xA8B25C, 0xA8B270
extern int DAT_00A8B268;
extern int DAT_00A8B25C;
extern int DAT_00A8B270;
// GLOBAL: GAMEMD 0xA8B262, 0xA8B263, 0xA8B264, 0xA8B320, 0xA8B261
extern unsigned char DAT_00A8B262;
extern unsigned char DAT_00A8B263;
extern unsigned char DAT_00A8B264;
extern unsigned char DAT_00A8B320;
extern unsigned char DAT_00A8B261;

// The lobby snapshot 0x5ED400 fills: the mode and map, five option values and,
// for slots 1..7, a kind number and the start and house choices (slot 0's entry
// is not written). Offsets are the displacements the stores use: slot i's kind
// is stored at +0x28 + 12 * (i - 1).
struct LobbySnapshot_005ED400
{
    int unknown_00;               // +0x00  0xA8B250
    int unknown_04;               // +0x04  0xA8B254
    int unknown_08;               // +0x08  0xA8B268
    int unknown_0C;               // +0x0C  0xA8B25C
    int unknown_10;               // +0x10  0xA8B270
    unsigned char unknown_14;     // +0x14  0xA8B262
    unsigned char unknown_15;     // +0x15  0xA8B263
    unsigned char unknown_16;     // +0x16  0xA8B264
    unsigned char unknown_17;     // +0x17  0xA8B320
    unsigned char unknown_18;     // +0x18  0xA8B261
    unsigned char unknown_19[3];  // +0x19
    struct Slot
    {
        int Kind;                 // +0x00
        int Start;                // +0x04
        int House;                // +0x08
    } Slots[8];                   // +0x1C; slot 0's entry is never written
};
GG_STATIC_ASSERT(offsetof(LobbySnapshot_005ED400, unknown_14) == 0x14 &&
                 offsetof(LobbySnapshot_005ED400, unknown_18) == 0x18 &&
                 offsetof(LobbySnapshot_005ED400, Slots) == 0x1C &&
                 sizeof(LobbySnapshot_005ED400) == 0x1C + 8 * 12);
// STRING: GAMEMD 0x831D9C -- a two-character wide set (0x0A, 0x0D).
extern const wchar_t DAT_00831D9C[];

// The item data of a combo-box entry (the current one when `index` is -1),
// CB_ERR reading as 0: the body of 0x5E9B20, inlined here.
static __forceinline int Combo_Item_Data(HWND dialog, int control, int index)
{
    if (index == -1) {
        index = (int)SendDlgItemMessageA(dialog, control, CB_GETCURSEL, 0, 0);
    }
    int data = (int)SendDlgItemMessageA(dialog, control, CB_GETITEMDATA, index, 0);
    return data != CB_ERR ? data : 0;
}

// ---- from the former netshare_slot_names_005edef0.cpp ----
//   Bytes matched against the user's retail gamemd.exe v1.001, 0x5EDEF0..0x5EE1AF
//   (the matched functions only). netshare.cpp (path string at 0x8317D8): the
//   seven slot-kind tokens ("@Open@" ... "@OpenObserver@", seven char pointers
//   at 0x831704..0x83171C) and the conversions between them and the singleton
//   nodes of netshare_slot_nodes.h.

#include "../economy/netshare_common.h"
#include "../economy/netshare_slot_nodes.h"
#include "../core/string_class.h"

// GLOBAL: GAMEMD 0x831704..0x83171C -- char pointers to the slot-kind tokens
// "@Open@", "@Closed@", "@Waiting@", "@EasyAI@", "@MediumAI@", "@HardAI@" and
// "@OpenObserver@" (ghidra memory read).
extern char* DAT_00831704;
extern char* DAT_00831708;
extern char* DAT_0083170C;
extern char* DAT_00831710;
extern char* DAT_00831714;
extern char* DAT_00831718;
extern char* DAT_0083171C;

// FUNCTION: GAMEMD 0x7B7F90 (decl; reloc) -- __fastcall: build the narrow copy
// of a wide string in the object the hidden first argument points at (which it
// also returns).
Wstring FUN_007B7F90(const Obj_007B66D0& text);

// ---- from the former netshare_slot_queries_005e9580.cpp ----
//   Bytes matched against the user's retail gamemd.exe v1.001, 0x5E9580..0x5E9950.
//   netshare.cpp (path string at 0x8317D8): the lobby's slot queries, over the
//   slot array and the seven singleton nodes of netshare_slot_nodes.h.

#include "../economy/netshare_common.h"
#include "../economy/netshare_slot_inline.h"

// STRING: GAMEMD 0x831C8C "Channel full - Session.ScenarioMaxPlayers = %d\n"
extern const char DAT_00831C8C[];

// Is a real (non-singleton) player seated in the slot the extra-slot index
// names, as an observer? The first test of both 0x5E9580 and 0x5E95E0.
static __forceinline bool Observer_At_Extra_Slot()
{
    for (int i = 0; i < 8; i++) {
        NodeNameType* node = Slots[i];
        if (node != 0 && node != OpenNode && node != ClosedNode && node != ObserverNode &&
            node != WaitingNode && i == NoExtraSlot && node->unknown_6B == -1) {
            return true;
        }
    }
    return false;
}

// ---- from the former netshare_slots_005e6440.cpp ----
//   Bytes matched against the user's retail gamemd.exe v1.001, 0x5E6440..0x5E66EF
//   (the matched functions only). netshare.cpp (path string at 0x8317D8): the
//   lobby's slot-count helpers and the selected-map query. The two predicates at
//   0x77D940 / 0x77D970 are the ones netshare_slot_nodes.h declares.

#include "../economy/netshare_win.h"
#include "../economy/netshare_slot_inline.h"
#include "multiplayer_game_mode.h"

// GLOBAL: GAMEMD 0xAC0D40 -- the lobby dialog.
extern HWND DAT_00AC0D40;

// FUNCTION: GAMEMD 0x5E23A0
//
// Send message 0x4DC to the lobby start control (item 0x59F) of the open dialog.
void FUN_005E23A0()
{
    HWND dialog = FUN_00775B10();
    HWND item = GetDlgItem(dialog, 0x59F);
    SendMessageA(item, 0x4DC, 0, 0);
}

// SYNTHETIC: GAMEMD 0x005E2460
// GLOBAL: GAMEMD 0x00AC1160
double DAT_00AC1160 = DAT_00AC0CE8 / DAT_007EEF18;

// SYNTHETIC: GAMEMD 0x005E2480
// GLOBAL: GAMEMD 0x00AC10E8
double DAT_00AC10E8 = DAT_007E1718 / DAT_00AC1160;

// SYNTHETIC: GAMEMD 0x005E2600
// GLOBAL: GAMEMD 0x00AC1148
MathTblCoord DAT_00AC1148;

#include "../core/string_class.h"

// Key hash of a narrow string object: seeded with the length, then for each
// character adds the signed character value and its index and rotates the
// accumulator left by eight bits (__fastcall, string object in ECX).
// FUNCTION: GAMEMD 0x005E2620
unsigned int FUN_005E2620(const Wstring* key)
{
    unsigned int hash = key->Length();
    for (unsigned int i = 0; i < (unsigned int)key->Length(); ++i) {
        hash += key->FUN_007B5400()[i] + i;
        hash = (hash << 8) ^ (hash >> 24);
    }
    return hash;
}

// FUNCTION: GAMEMD 0x5E2670
//
// Hash a wide string: seed with its length, then fold each character plus its
// index in and rotate left by eight.
unsigned int FUN_005E2670(Obj_007B66D0* text)
{
    unsigned int hash = text->FUN_007B71B0();
    for (unsigned int i = 0; i < text->FUN_007B71B0(); i++) {
        hash += text->FUN_007B7100()[i] + i;
        hash = (hash << 8) ^ (hash >> 24);
    }
    return hash;
}

// FUNCTION: GAMEMD 0x5E26C0
//
// Find whichever of the four numbered dialogs is currently open (0xC2, 0xC9, 0xBC, 0xBD).
HWND FUN_005E26C0()
{
    HWND dialog = FUN_00775940(0xC2);
    if (!dialog) {
        dialog = FUN_00775940(0xC9);
        if (!dialog) {
            dialog = FUN_00775940(0xBC);
            if (!dialog) {
                dialog = FUN_00775940(0xBD);
            }
        }
    }
    return dialog;
}

// FUNCTION: GAMEMD 0x5E2700
//
// Format a chat line and append it to the lobby chat list. The list sits in
// the current dialog or in one of its ancestors, so walk up until item 0x53F
// resolves.
void __cdecl FUN_005E2700(int param, const wchar_t* format, ...)
{
    wchar_t buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    va_list args;
    va_start(args, format);
    vswprintf(buffer, format, args);
    if (FUN_00775B10() != 0) {
        HWND dialog = FUN_00775B10();
        HWND list = GetDlgItem(dialog, 0x53F);
        while (list == 0) {
            dialog = FUN_007759B0(dialog);
            if (dialog == 0) {
                return;
            }
            list = GetDlgItem(dialog, 0x53F);
        }
        FUN_005E2820(param, buffer, list);
    }
}

// FUNCTION: GAMEMD 0x5E2790
//
// The same formatted append for the second chat list (dialog item 0x5B5).
void __cdecl FUN_005E2790(int param, const wchar_t* format, ...)
{
    wchar_t buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    va_list args;
    va_start(args, format);
    vswprintf(buffer, format, args);
    if (FUN_00775B10() != 0) {
        HWND dialog = FUN_00775B10();
        HWND list = GetDlgItem(dialog, 0x5B5);
        while (list == 0) {
            dialog = FUN_007759B0(dialog);
            if (dialog == 0) {
                return;
            }
            list = GetDlgItem(dialog, 0x5B5);
        }
        FUN_005E2820(param, buffer, list);
    }
}

// FUNCTION: GAMEMD 0x5E2820
// PARTIAL: best 38.8% positional, 56.8% aligned (79 of 139 instructions). The
// structure matches; the delta is register assignment. Retail keeps the string
// length in EDI and the line text in ESI, rereads the window argument from the
// stack through the loop and caches the SendMessageA import in EBP, where this
// build puts the window in EDI and the length in EBX. Tried: statement order of
// the header setup, one variable for remaining and line length (kept), declaring
// the temporaries at function scope, `for (;;)` and flag-structured forms of the
// back-up loop, and goto-free control flow.
//
// Word-wrap `text` to the list box's width and append each piece through
// 0x5E29A0. A piece is cut at an embedded line feed or at the point where the
// measured width reaches the control's inner width less four, backing up to
// the last printable character first.
void FUN_005E2820(int param, const wchar_t* text, HWND window)
{
    int margin;
    RECT rect;
    int length = (int)wcslen(text);
    margin = 0x12;
    FUN_00775690(window, &rect);
    if (SendMessageA(window, 0x4A0, 0, 0) != 0) {
        margin = 1;
    }
    HDC dc = GetDC(window);
    SendMessageA(window, 0x49E, 0, (LPARAM)dc);

    while (length != 0) {
        if (text != 0) {
            const wchar_t* lineFeed = wcschr(text, 10);
            if (lineFeed != 0) {
                int upTo = (int)(lineFeed - text) + 1;
                if (upTo <= length) {
                    length = upTo;
                }
            }
        }
        wchar_t* copy = _wcsdup(text);
        copy[length] = 0;
        int width;
        int height;
        DAT_0089C4D0->FUN_00433CF0(copy, &width, &height, 0);
        free(copy);

        int inner = (rect.right - rect.left) - margin;
        if (width >= inner - 4) {
            int step;
            if (width / 2 > inner) {
                step = 10;
                length -= 10;
            } else {
                step = 1;
            }
            int i = length - 1;
            if (i > 0) {
                const wchar_t* p = text + i;
                do {
                    if (iswgraph(*p) == 0) {
                        if (i == -1) {
                            length -= step;
                        } else {
                            length = i;
                        }
                        goto next;
                    }
                    i--;
                    p--;
                } while (i > 0);
            }
            length -= step;
        next:;
        } else {
            FUN_005E29A0(window, text, length, param);
            text += length;
            while (*text == 0x20) {
                text++;
            }
            length = (int)wcslen(text);
        }
    }
    ReleaseDC(window, dc);
}

// FUNCTION: GAMEMD 0x5E29A0
//
// Append one line (cut at a CR or LF) to the chat list box, dropping the oldest
// once there are more than 500 and scrolling to the end when the list was
// already showing its last line. The selection state is saved and restored
// around the add through the 0x49D message.
void FUN_005E29A0(HWND window, const wchar_t* text, int length, int param)
{
    memset(DAT_00AC029C, 0, sizeof(DAT_00AC029C));
    wcsncpy(DAT_00AC029C, text, length);
    wchar_t* end = wcschr(DAT_00AC029C, 13);
    if (end == 0) {
        end = wcschr(DAT_00AC029C, 10);
    }
    if (end != 0) {
        *end = 0;
    }

    LRESULT saved = SendMessageA(window, 0x49D, 0, 1);
    int top = (int)SendMessageA(window, 0x18E, 0, 0);
    int count = (int)SendMessageA(window, 0x18B, 0, 0);
    int itemHeight = (int)SendMessageA(window, 0x1A1, top, 0);
    RECT rect;
    GetWindowRect(window, &rect);
    bool showsLast = count - top <= (rect.bottom - rect.top) / itemHeight;
    if (count > 500) {
        SendMessageA(window, 0x182, 0, 0);
        count--;
    }
    int index = (int)SendMessageA(window, 0x4CD, 0, (LPARAM)DAT_00AC029C);
    if (param != -1) {
        SendMessageA(window, 0x498, index, param);
    }
    if (showsLast) {
        SendMessageA(window, 0x197, count, 0);
    }
    SendMessageA(window, 0x49D, 0, saved);
}

// FUNCTION: GAMEMD 0x5E2AC0
//
// Replace the chat list's last line with a continuation of it: read the final
// item back, and either append the marker string to it (when it is short, also
// deleting the item) or replace it, then re-add it through the wrapper.
void FUN_005E2AC0()
{
    if (FUN_00775B10() != 0) {
        HWND dialog = FUN_00775B10();
        HWND list = GetDlgItem(dialog, 0x53F);
        while (list == 0) {
            dialog = FUN_007759B0(dialog);
            if (dialog == 0) {
                return;
            }
            list = GetDlgItem(dialog, 0x53F);
        }
        int count = (int)SendMessageA(list, 0x18B, 0, 0);
        Obj_007B66D0 line;
        if (count > 0) {
            FUN_00623F60(list, count - 1, &line);
        }
        if (line.FUN_007B71B0() < 0x24) {
            SendMessageA(list, 0x182, count - 1, 0);
            line += DAT_00831774;
        } else {
            line = DAT_00831774;
        }
        FUN_005E2820(-1, line.FUN_007B7100(), list);
        InvalidateRect(list, 0, FALSE);
    }
}

// FUNCTION: GAMEMD 0x5E2BA0
//
// Count the other houses that are human-controlled and still in the game.
int FUN_005E2BA0(HouseClass* self)
{
    int count = 0;
    for (int i = 0; i < DAT_00A80238; i++) {
        HouseClass* house = DAT_00A8022C[i];
        if (house != 0 && house->IsHumanPlayer != 0 && house->Defeated == 0 && house != self) {
            count++;
        }
    }
    return count;
}

// FUNCTION: GAMEMD 0x5E2BE0
//
// Count the distinct groups of live, non-passive houses (other than `self`)
// that are allied with each other in both directions: every house that has no
// mutual ally counts as a group of its own, and each mutual-ally cluster counts
// once, at its first member.
int FUN_005E2BE0(HouseClass* self)
{
    int groups = 0;
    for (int i = 0; i < DAT_00A80238; i++) {
        HouseClass* house = DAT_00A8022C[i];
        if (house != 0 && house->Defeated == 0
            && !((HouseTypeClass*)house->Type)->MultiplayPassive && house != self) {
            bool clustered = false;
            for (int j = 0; j < DAT_00A80238; j++) {
                HouseClass* other;
                if (j != i && (other = DAT_00A8022C[j]) != 0 && other->Defeated == 0
                    && !((HouseTypeClass*)other->Type)->MultiplayPassive && other != self
                    && house->IsAlliedWith(other) && other->IsAlliedWith(house)) {
                    if (j > i && !clustered) {
                        groups++;
                    }
                    clustered = true;
                }
            }
            if (!clustered) {
                groups++;
            }
        }
    }
    return groups;
}

// FUNCTION: GAMEMD 0x5E2CD0
// PARTIAL: best 1.4% positional, 68.6% aligned (96 of 140 instructions). Same
// control flow and calls; retail holds the text in EBP and the button set in EBX
// and leaves the flag in memory, this build holds the button set in EBP and the
// flag in BL. Tried: id selection as a chain, a ternary and a switch, the second
// and third button branches with and without a shared tail, and the style update
// as nested calls versus a temporary.
//
// Show a message box built from a dialog template: the template depends on the
// button set (0 = one button, 1 = two, 4 = the second pair) and on the flag, the
// buttons are made visible, the text goes into item 0x5B0, and the dialog is run.
int FUN_005E2CD0(const wchar_t* text, int buttons, void* callback, bool flag)
{
    if (text != 0 && wcslen(text) != 0) {
        int id;
        if (flag) {
            id = 0xFB;
        } else if (buttons == 0) {
            id = 0xD0;
        } else if (buttons == 1) {
            id = 0xFC;
        } else {
            id = buttons == 4 ? 0x126 : 0xFB;
        }
        HWND dialog = FUN_00775700(DAT_00B732F0, id, DAT_00B73550, (void*)FUN_005E2E40, 0);
        FUN_00622820(dialog, id);
        HWND button;
        if (buttons == 0) {
            button = GetDlgItem(dialog, 1);
            SetWindowLongA(button, GWL_STYLE, GetWindowLongA(button, GWL_STYLE) | WS_VISIBLE);
            if (flag) {
                FUN_0060B350(button);
            }
        } else {
            int second;
            if (buttons == 1) {
                button = GetDlgItem(dialog, 1);
                SetWindowLongA(button, GWL_STYLE, GetWindowLongA(button, GWL_STYLE) | WS_VISIBLE);
                second = 2;
            } else if (buttons == 4) {
                button = GetDlgItem(dialog, 6);
                SetWindowLongA(button, GWL_STYLE, GetWindowLongA(button, GWL_STYLE) | WS_VISIBLE);
                second = 7;
            } else {
                goto showText;
            }
            button = GetDlgItem(dialog, second);
            SetWindowLongA(button, GWL_STYLE, GetWindowLongA(button, GWL_STYLE) | WS_VISIBLE);
        }
    showText:
        SendMessageA(GetDlgItem(dialog, 0x5B0), 0x4B2, 0, (LPARAM)text);
        ShowWindow(dialog, 1);
        return FUN_007759E0(dialog, callback, 0, 1, 1);
    }
    return 0;
}

// FUNCTION: GAMEMD 0x5E2E40
//
// The message box's dialog procedure: erase-background and paint, owner-draw
// items, and the four command ids that close it.
int __stdcall FUN_005E2E40(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    switch (message) {
    case 0x14:
        return 1;
    case 0xF:
        FUN_00621E90(window);
        FUN_00607FD0(window);
        ValidateRect(window, 0);
        return 1;
    case 0x2B:
        FUN_006213A0((void*)lparam);
        return 1;
    case 0x111:
        switch (wparam & 0xFFFF) {
        case 1:
        case 2:
        case 6:
        case 7:
            FUN_007757E0(window, wparam & 0xFFFF);
            return 1;
        }
        break;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x5E2EF0
//
// Put a game mode's name into the dialog's name field.
void FUN_005E2EF0(HWND dialog, MultiplayerGameMode* mode)
{
    if (mode != 0) {
        HWND field = GetDlgItem(dialog, 0x6EC);
        SendMessageA(field, 0x4B2, 0, (LPARAM)mode->unknown_20.FUN_007B7140());
    }
}

// FUNCTION: GAMEMD 0x5E2F60
// Calls other functions.
void FUN_005E2F60(HWND dialog)
{
    HWND c0 = GetDlgItem(dialog, 0x5A8);
    SendMessageA(c0, 0x4B2, 0, (LPARAM)DAT_00A8B322);
}

// FUNCTION: GAMEMD 0x5E2F80
//
// If no game mode matches the selected identifier, fall back to the default.
void FUN_005E2F80()
{
    if (MultiplayerGameMode_Get(GameModeOptions.unknown_00) == 0) {
        FUN_005D5E10();
    }
}

// FUNCTION: GAMEMD 0x5E2FA0
// PARTIAL: best 94.7% (36 of 38 instructions). Identical instruction multiset;
// retail schedules the MOV ESI,EAX that captures the dialog before the two
// zero pushes of the first SendDlgItemMessageA, this build after the first.
// Tried: signed and unsigned selection variables, an early-return form, and
// LRESULT temporaries for both messages.
//
// Tell the selected game mode to act on the lobby (slot 37): from the list
// dialog 0x6B, the mode attached to the highlighted entry of list 0x6EB;
// otherwise the live game-mode object.
void FUN_005E2FA0()
{
    if (FUN_00775B20() == 0x6B) {
        HWND dialog = FUN_00775B10();
        WPARAM selected = SendDlgItemMessageA(dialog, 0x6EB, 0x188, 0, 0);
        if (selected != 0xFFFFFFFF) {
            MultiplayerGameMode* mode = (MultiplayerGameMode*)SendDlgItemMessageA(dialog, 0x6EB, 0x199, selected, 0);
            if (mode != 0) {
                mode->vf_37();
            }
        }
    } else if (DAT_00A8B23C != 0) {
        DAT_00A8B23C->vf_37();
    }
}

// FUNCTION: GAMEMD 0x5E32D0
void FUN_005E32D0(char force, char poll)
{
    Publish_Options_Inline(force, poll);
}

// FUNCTION: GAMEMD 0x5E35A0
//
// Send the kind-0x28 message (the local handle only) to every remote player.
void FUN_005E35A0()
{
    NetsharePacket packet;
    memset(&packet, 0, sizeof(packet));
    packet.Command = 0x28;
    strcpy(packet.Name, LocalHandle);
    int count = PlayerNodes.Count;
    for (int i = 1; i < count; i++) {
        Manager_00A8E9C0.FUN_005410F0(&packet, 0x1C7, 1, &PlayerNodes.Vector[i]->Address, 0, 0);
        FUN_0048D080();
    }
}

// FUNCTION: GAMEMD 0x5E3630
//
// The same message, only in session kind 3; in kind 4 the work is done by the
// callee at 0x7A2730.
void FUN_005E3630()
{
    switch (SessionKind) {
    case 3: {
        NetsharePacket packet;
        memset(&packet, 0, sizeof(packet));
        packet.Command = 0x28;
        strcpy(packet.Name, LocalHandle);
        int count = PlayerNodes.Count;
        for (int i = 1; i < count; i++) {
            Manager_00A8E9C0.FUN_005410F0(&packet, 0x1C7, 1, &PlayerNodes.Vector[i]->Address, 0, 0);
            FUN_0048D080();
        }
        break;
    }
    case 4:
        FUN_007A2730();
        break;
    }
}

// FUNCTION: GAMEMD 0x5E36E0
//
// Set the flag and pass control to the link's handler when there is a link,
// else to the local one.
void FUN_005E36E0()
{
    DAT_00A8DAB0 = 1;
    if (DAT_00AC116C != 0) {
        FUN_007A2750();
        return;
    }
    FUN_005E2340();
}

// FUNCTION: GAMEMD 0x5E3700
// Branching.
int FUN_005E3700(Obj_005E3700* a1, int a2)
{
    DAT_00A8DAB0 = 0;
    if (DAT_00AC116C != 0)
    {
        return FUN_007A27D0(a1, a2);
    }
    return FUN_005E23A0(a1, a2);
}

// FUNCTION: GAMEMD 0x5E3720
//
// Broadcast a public game-options string (kind 0x17): through the link when
// there is one, otherwise as a packet to every remote player.
void FUN_005E3720(const char* text)
{
    if (DAT_00AC116C != 0) {
        char line[0x400];
        strncpy(line, text, 0x3FF);
        DAT_00AC116C->Vtbl->At_3C(DAT_00AC116C, line);
        return;
    }
    NetsharePacket packet;
    memset(&packet, 0, sizeof(packet));
    packet.Command = 0x17;
    strcpy(packet.Name, LocalHandle);
    strcpy(packet.Text, text);
    packet.unknown_1BF = DAT_00A8B394;
    packet.unknown_1C3 = FUN_005DAC00(BlankName);
    for (int i = 1; i < PlayerNodes.Count; i++) {
        NodeNameType* node = PlayerNodes.Vector[i];
        FUN_004068E0(DAT_00831778, Narrow_007350C0(node->Name));
        Manager_00A8E9C0.FUN_005410F0(&packet, 0x1C7, 1, &node->Address, 0, 0);
        FUN_0048D080();
    }
}

// FUNCTION: GAMEMD 0x5E3850
//
// Send a private game-options string (kind 0x18) to the one remote player whose
// handle matches `name`, or through the link when there is one.
void FUN_005E3850(const char* name, const char* text)
{
    if (DAT_00AC116C != 0) {
        NetshareLinkMessage message;
        memset(&message, 0, sizeof(message));
        strcpy(message.Name, name);
        DAT_00AC116C->Vtbl->At_38(DAT_00AC116C, &message, text);
        return;
    }
    NetsharePacket packet;
    memset(&packet, 0, sizeof(packet));
    packet.Command = 0x18;
    strcpy(packet.Name, LocalHandle);
    strcpy(packet.Text, text);
    DAT_00A8D638.unknown_1BF = SessionObject_00A8B238.FUN_0069B720();
    DAT_00A8D638.unknown_1C3 = FUN_005DAC00(BlankName);
    for (int i = 1; i < PlayerNodes.Count; i++) {
        if (_stricmp(Narrow_007350C0(PlayerNodes.Vector[i]->Name), name) == 0) {
            FUN_004068E0(DAT_0083179C, PlayerNodes.Vector[i]);
            Manager_00A8E9C0.FUN_005410F0(&packet, 0x1C7, 1, &PlayerNodes.Vector[i]->Address, 0, 0);
            FUN_0048D080();
        }
    }
}

// FUNCTION: GAMEMD 0x5E39C0
//
// Record a remote player's map-transfer state (the node's +0x7F) and post the
// matching lobby chat line: "no map" for 0, "map transfer" for 2. A null handle
// means the local player; the blank handle forces state 1.
void FUN_005E39C0(const char* handle, int state)
{
    if (handle == 0) {
        handle = LocalHandle;
    }
    if (wcscmp(Widen_00735120(handle), BlankName) == 0) {
        state = 1;
    }
    int i = Find_Player_By_Handle(handle);
    if (i != -1) {
        PlayerNodes.Vector[i]->unknown_7F = state;
        if (state == 0) {
            FUN_005E2700(-1, Fetch_String_00734E60(HostNoMapLabel, 0, NetshareFileName, 0x491),
                         PlayerNodes.Vector[i], DAT_00A8B322);
            return;
        }
        if (state == 2) {
            FUN_005E2700(-1, Fetch_String_00734E60(HostMapTransferLabel, 0, NetshareFileName, 0x495),
                         PlayerNodes.Vector[i], DAT_00A8B322);
        }
    }
}

// FUNCTION: GAMEMD 0x5E6440
//
// How many players a session of this kind starts with.
int FUN_005E6440()
{
    if (SessionKind == 4) {
        if (Is_005E8AE0_A() && !Is_005E8AE0_B()) {
            return 2;
        }
        return 6;
    }
    return 8;
}

// FUNCTION: GAMEMD 0x5E6470
//
// The same count, one more when below the session's limit (6 in kind 4, else 8).
int FUN_005E6470()
{
    int count;
    if (SessionKind == 4) {
        if (Is_005E8AE0_A() && !Is_005E8AE0_B()) {
            count = 2;
        } else {
            count = 6;
        }
    } else {
        count = 8;
    }
    if (SessionKind == 4) {
        if (count >= 6) {
            return count;
        }
    } else if (count >= 8) {
        return count;
    }
    return count + 1;
}

// FUNCTION: GAMEMD 0x5E64C0
//
// The player limit for map `index`: the map's own count, capped by the live
// game mode's slot-38 limit; kind 4 then forces an even count (or two when
// the first predicate holds and the second does not).
int FUN_005E64C0(int index)
{
    if (index == -1) {
        return 8;
    }
    return Map_Player_Limit(index);
}

// FUNCTION: GAMEMD 0x5E66D0
//
// The selected entry of the lobby's map list (list item 0x553, LB_GETCURSEL).
int FUN_005E66D0()
{
    return SendDlgItemMessageA(DAT_00AC0D40, 0x553, 0x188, 0, 0);
}

// FUNCTION: GAMEMD 0x5E68A0
// PARTIAL: best 89.2% (33 of 37 instructions). Identical instruction multiset;
// retail loads the template id into EDX before the three stacked argument
// pushes, this build after them. Tried: keeping the created dialog in a local
// before the global store.
//
// Open the lobby dialog (template 0x6B) under `parent`, run it, and answer its
// result.
int FUN_005E68A0(HWND parent)
{
    FUN_0052FEC0(0, 1);
    FUN_0072D120();
    DAT_00AC0D40 = FUN_00775700(DAT_00B732F0, 0x6B, parent, (void*)FUN_005E6920, 0);
    FUN_00622820(DAT_00AC0D40, 0x6B);
    SendMessageA(DAT_00AC0D40, 0x4A9, 0, 1);
    ShowWindow(DAT_00AC0D40, 1);
    int result = FUN_007759E0(DAT_00AC0D40, (void*)FUN_005E66F0, 0, 1, 1);
    FUN_0072D170();
    return result;
}

// FUNCTION: GAMEMD 0x5E7460
//
// Publish the lobby's choices for the match: the selected map into the scenario,
// the player count, and the packed option bits into the flags dword.
void FUN_005E7460()
{
    DAT_00A8B230->unknown_1254 = DAT_00A8B254;
    DAT_00A8ED84 = 0;
    DAT_00A8B54C = PlayerNodes.Count;
    FUN_004068E0(DAT_00831A60, PlayerNodes.Count);
    DAT_00A8EB60 = DAT_00A8B268;
    DAT_00A8B24C = 2;
    DAT_00A8E960.unknown_00 = (((DAT_00A8B260 & 1) << 4 | (DAT_00A8B31D & 1)) << 11) |
                              (DAT_00A8E960.unknown_00 & 0xFFFF77FF) | 0xC0;
    DAT_00A8E960.FUN_006B8B10();
}

// FUNCTION: GAMEMD 0x5E8740
//
// Is the node sitting at `index` in the player vector still unnamed? The
// blank name at 0xA8D610 is the "not filled in yet" sentinel, and the node
// pointer is its own name because Name is the first member.
int Node_Is_Blank_At(int index)
{
    return wcscmp(PlayerNodes.Vector[index]->Name, BlankName) == 0;
}

// FUNCTION: GAMEMD 0x5E8760
//
// The same question about the local player's own handle, which is stored
// ANSI and widened for the comparison.
int Local_Handle_Is_Blank()
{
    wchar_t* handle = Widen_00735120(LocalHandle);
    return wcscmp(handle, BlankName) == 0;
}

// FUNCTION: GAMEMD 0x5E8780
//
// Does an arbitrary wide name belong to the local player?
int Name_Is_Local_Handle(const wchar_t* name)
{
    return wcscmp(name, Widen_00735120(LocalHandle)) == 0;
}

// FUNCTION: GAMEMD 0x5E87A0
//
// Build the seven singleton slot nodes, once. The captions come from the
// string table under their GUI labels, each fetch carrying the source file
// and its own line number, and the first caption doubles as the "already
// built" guard. Each node is then allocated and given its caption as its
// name, so a slot's caption and a player's name are the same kind of string
// everywhere else in this file.
void Build_Slot_Nodes()
{
    if (DAT_00AC117C == 0) {
        DAT_00AC117C = Fetch_String_00734E60(OpenLabel, 0, NetshareFileName, 4078);
        ClosedText = Fetch_String_00734E60(ClosedLabel, 0, NetshareFileName, 4079);
        EasyAIText = Fetch_String_00734E60(EasyAILabel, 0, NetshareFileName, 4080);
        MediumAIText = Fetch_String_00734E60(MediumAILabel, 0, NetshareFileName, 4081);
        HardAIText = Fetch_String_00734E60(HardAILabel, 0, NetshareFileName, 4082);
        WaitingText = Fetch_String_00734E60(WaitingLabel, 0, NetshareFileName, 4083);
        ObserverText = Fetch_String_00734E60(ObserverLabel, 0, NetshareFileName, 4084);
    }

    if (OpenNode == 0) {
        OpenNode = new NodeNameType;
        wcscpy(OpenNode->Name, DAT_00AC117C);
    }
    if (ClosedNode == 0) {
        ClosedNode = new NodeNameType;
        wcscpy(ClosedNode->Name, ClosedText);
    }
    if (EasyAINode == 0) {
        EasyAINode = new NodeNameType;
        wcscpy(EasyAINode->Name, EasyAIText);
    }
    if (MediumAINode == 0) {
        MediumAINode = new NodeNameType;
        wcscpy(MediumAINode->Name, MediumAIText);
    }
    if (HardAINode == 0) {
        HardAINode = new NodeNameType;
        wcscpy(HardAINode->Name, HardAIText);
    }
    if (WaitingNode == 0) {
        WaitingNode = new NodeNameType;
        wcscpy(WaitingNode->Name, WaitingText);
    }
    if (ObserverNode == 0) {
        ObserverNode = new NodeNameType;
        wcscpy(ObserverNode->Name, ObserverText);
    }
}

// FUNCTION: GAMEMD 0x5E8A20
//
// Tear the lobby down: release each of the seven singleton slot nodes, then
// hand the player vector to its own clear-and-delete helper.
void Destroy_Slot_Nodes()
{
    if (OpenNode != 0) {
        delete OpenNode;
        OpenNode = 0;
    }
    if (ClosedNode != 0) {
        delete ClosedNode;
        ClosedNode = 0;
    }
    if (EasyAINode != 0) {
        delete EasyAINode;
        EasyAINode = 0;
    }
    if (MediumAINode != 0) {
        delete MediumAINode;
        MediumAINode = 0;
    }
    if (HardAINode != 0) {
        delete HardAINode;
        HardAINode = 0;
    }
    if (WaitingNode != 0) {
        delete WaitingNode;
        WaitingNode = 0;
    }
    if (ObserverNode != 0) {
        delete ObserverNode;
        ObserverNode = 0;
    }
    Clear_Nodes_005C6120(&PlayerNodes);
}

// FUNCTION: GAMEMD 0x5E8AE0
//
// Put every slot back to its starting state: the playable ones show Open and
// the rest show Closed.
void Reset_Slots()
{
    int playable = Playable_Slot_Count();

    for (int i = 0; i < playable; i++) {
        Slots[i] = OpenNode;
    }
    for (int j = playable; j < 8; j++) {
        Slots[j] = ClosedNode;
    }
}

// FUNCTION: GAMEMD 0x5E8B40
//
// Drop the four lobby redraw flags together.
void Clear_Lobby_Flags()
{
    DirtyFlagA = false;
    DirtyFlagB = false;
    DirtyFlagC = false;
    DirtyFlagD = false;
}

// FUNCTION: GAMEMD 0x5E8B60
//
// The full lobby reset: the slot reset above, then forget which slot the
// local player picked, empty the lobby list and zero the two counters.
void Reset_Lobby()
{
    int playable = Playable_Slot_Count();

    for (int i = 0; i < playable; i++) {
        Slots[i] = OpenNode;
    }
    for (int j = playable; j < 8; j++) {
        Slots[j] = ClosedNode;
    }

    SelectedSlotIndex = -1;
    GameModeOptions.Clear();
    CounterA = 0;
    CounterB = 0;
}

// FUNCTION: GAMEMD 0x5E8BF0
//
// Resolve a wide name to a node: the seven singletons first, in the order
// they were created, then the real players. Case sensitive, unlike the slot
// lookup below.
NodeNameType* Find_Node_By_Name(const wchar_t* name)
{
    if (wcscmp(OpenNode->Name, name) == 0) {
        return OpenNode;
    }
    if (wcscmp(ClosedNode->Name, name) == 0) {
        return ClosedNode;
    }
    if (wcscmp(EasyAINode->Name, name) == 0) {
        return EasyAINode;
    }
    if (wcscmp(MediumAINode->Name, name) == 0) {
        return MediumAINode;
    }
    if (wcscmp(HardAINode->Name, name) == 0) {
        return HardAINode;
    }
    if (wcscmp(WaitingNode->Name, name) == 0) {
        return WaitingNode;
    }
    if (wcscmp(ObserverNode->Name, name) == 0) {
        return ObserverNode;
    }

    int count = PlayerNodes.Count;
    for (int i = 0; i < count; i++) {
        NodeNameType* node = PlayerNodes.Vector[i];
        if (wcscmp(node->Name, name) == 0) {
            return node;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x5E8D00
//
// Which slot currently shows this name? Case insensitive; empty slots are
// skipped rather than compared.
int Find_Slot_By_Name(const wchar_t* name)
{
    return Slot_Showing_Name(name);
}

// FUNCTION: GAMEMD 0x5E8D40
//
// The same search for the local player, who is always the vector's first
// entry. With no players at all there is nothing to find.
int Find_Local_Player_Slot()
{
    if (PlayerNodes.Count == 0) {
        return -1;
    }

    return Slot_Showing_Name(PlayerNodes.Vector[0]->Name);
}

// FUNCTION: GAMEMD 0x5E8D90
//
// Seat a node in a slot.
void Set_Slot_Node(int index, NodeNameType* node)
{
    Slots[index] = node;
}

// FUNCTION: GAMEMD 0x5E8DA0
//
// Move the local player into a slot and remember the choice.
void Select_Slot(int index)
{
    SelectedSlotIndex = index;
    Slots[index] = PlayerNodes.Vector[0];
}

// FUNCTION: GAMEMD 0x5E8DC0
//
// Write each slot as a wide string followed by a comma: a real player by name,
// anything else (empty, closed, AI, waiting, observer) by its slot-kind token.
void FUN_005E8DC0(wchar_t* out)
{
    *out = 0;
    for (int i = 0; i < 8; i++) {
        NodeNameType* node = Slots[i];
        Obj_007B66D0 name;
        if (node == 0 || node == OpenNode || node == ClosedNode || node == WaitingNode ||
            node == ObserverNode || node == EasyAINode || node == MediumAINode ||
            node == HardAINode) {
            Wstring token = FUN_005EDEF0(node);
            name = FUN_007B7ED0(token);
        } else {
            name = node->Name;
        }
        wcscat(out, name.FUN_007B7100());
        wcscat(out, DAT_008304FC);
    }
}

// FUNCTION: GAMEMD 0x5E9240
//
// Find a home for a node and take it. An observer, marked by -1 in the house
// field, wants an observer slot; anyone else wants an open one. Answers the
// slot index, or -1 when the lobby is full.
int Assign_Node_To_Slot(NodeNameType* node)
{
    for (int i = 0; i < 8; i++) {
        NodeNameType* seated = Slots[i];
        if ((seated == OpenNode && node->unknown_6B != -1) ||
            (seated == ObserverNode && node->unknown_6B == -1)) {
            Slots[i] = node;
            return i;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x5E9290
//
// Give back the slot held by a node with this network address. An observer's
// slot goes back to Observer; everyone else's goes back to Open if it is still
// playable and Closed if it is not.
void Release_Slot_By_Address(const IPXAddressClass* address)
{
    int playable = Releasable_Slot_Count();

    for (int i = 0; i < 8; i++) {
        NodeNameType* node = Slots[i];
        if (node->Address.FUN_0053EE70(address)) {
            NodeNameType* seated = Slots[i];
            if (seated->unknown_6B == -1) {
                Slots[i] = ObserverNode;
                return;
            }
            Slots[i] = (i < playable) ? OpenNode : ClosedNode;
            return;
        }
    }
}

// FUNCTION: GAMEMD 0x5E9340
//
// The same release keyed on an ANSI handle rather than an address. The node's
// wide name is narrowed for the comparison, and empty slots are skipped.
void Release_Slot_By_Handle(const char* handle)
{
    int playable = Releasable_Slot_Count();

    for (int i = 0; i < 8; i++) {
        NodeNameType* seated = Slots[i];
        if (seated != 0 && _stricmp(handle, Narrow_007350C0(seated->Name)) == 0) {
            NodeNameType* found = Slots[i];
            if (found->unknown_6B == -1) {
                Slots[i] = ObserverNode;
                return;
            }
            Slots[i] = (i < playable) ? OpenNode : ClosedNode;
            return;
        }
    }
}

// FUNCTION: GAMEMD 0x5E93F0
//
// Is this a real human player rather than one of the seven singletons? Not in
// the Ghidra function list; found by the pad sweep.
int Is_Player_Node(NodeNameType* node)
{
    if (node == 0 || node == OpenNode || node == ClosedNode ||
        node == WaitingNode || node == ObserverNode || node == EasyAINode ||
        node == MediumAINode || node == HardAINode) {
        return 0;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x5E9440
//
// Is this one of the three AI singletons?
int Is_AI_Node(NodeNameType* node)
{
    if (node != 0 &&
        (node == EasyAINode || node == MediumAINode || node == HardAINode)) {
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x5E9470
//
// Does something actually occupy this slot? Open, Closed, Observer and
// Waiting all mean no; the AI singletons and real players mean yes.
int Is_Occupied_Node(NodeNameType* node)
{
    if (node == 0 || node == OpenNode || node == ClosedNode ||
        node == ObserverNode || node == WaitingNode) {
        return 0;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x5E94A0
//
// The difficulty an AI singleton stands for, counting down from Easy, and -1
// for anything that is not an AI. Not in the Ghidra function list; found by the pad sweep.
int AI_Difficulty_Of(NodeNameType* node)
{
    int difficulty = -1;
    if (node == EasyAINode) {
        difficulty = 2;
    } else if (node == MediumAINode) {
        difficulty = 1;
    } else if (node == HardAINode) {
        difficulty = 0;
    }
    return difficulty;
}

// FUNCTION: GAMEMD 0x5E94D0
//
// How many slots the AI holds.
int Count_AI_Slots()
{
    int count = 0;
    for (int i = 0; i < 8; i++) {
        NodeNameType* node = Slots[i];
        if (node != 0 &&
            (node == EasyAINode || node == MediumAINode || node == HardAINode)) {
            count++;
        }
    }
    return count;
}

// FUNCTION: GAMEMD 0x5E9510
//
// Is the lobby full? Only the slots inside the smaller of the map's and the
// session's player limits count, plus the one extra slot when it is available.
bool No_Open_Slot()
{
    // Only the ternary min reaches retail's register pair here: the two
    // if-spellings both hold the limit in the other register and carry the
    // loop index with them, 63.3% against 100%.
    int limit = (MapPlayerLimit < SessionPlayerLimit) ? MapPlayerLimit
                                                     : SessionPlayerLimit;

    for (int i = 0; i < limit; i++) {
        if (Slots[i] == OpenNode) {
            return false;
        }
    }

    if (NoExtraSlot == 0 && limit < 8 && Slots[limit] == OpenNode) {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x5E9560
//
// Is there nowhere left to observe from?
bool No_Observer_Slot()
{
    for (int i = 0; i < 8; i++) {
        if (Slots[i] == ObserverNode) {
            return false;
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x5E9580
// PARTIAL: best 83.8% (31 of 37 instructions). Identical instruction multiset;
// retail hoists the open node, the closed node and the extra-slot index into
// registers and compares the observer and waiting nodes from memory, this build
// hoists the open, closed and observer nodes instead. Matching it needs a
// local copy of the extra-slot index (tried: 100%), which is a redundant alias
// and is not used.
bool FUN_005E9580()
{
    return Observer_At_Extra_Slot();
}

// FUNCTION: GAMEMD 0x5E95E0
// PARTIAL: best 90.0% (54 of 60 instructions). The same register-hoisting
// difference as 0x5E9580. The limit minimum is written as `limit >=
// SessionPlayerLimit` (retail's `CMP map,session; JL` order; the earlier
// `SessionPlayerLimit <= limit` spelling gave 86.7%).
//
// Is the channel over capacity? The limit is the smaller of the map's and the
// session's player limits; the count is the players less one when an observer
// sits in the extra slot. Over capacity logs the session limit.
bool FUN_005E95E0()
{
    int limit = MapPlayerLimit;
    if (limit >= SessionPlayerLimit) {
        limit = SessionPlayerLimit;
    }
    int count = PlayerNodes.Count;
    bool observer = Observer_At_Extra_Slot();
    if (count - observer > limit) {
        FUN_004068E0(DAT_00831C8C, SessionPlayerLimit);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x5E96A0
bool FUN_005E96A0(int choice)
{
    return House_Choice_In_Use(choice);
}

// FUNCTION: GAMEMD 0x5E9720
bool FUN_005E9720(int choice)
{
    return Colour_Choice_In_Use(choice);
}

// FUNCTION: GAMEMD 0x5E97A0
//
// A singleton node's kind number, 2..7; anything else answers 2.
int FUN_005E97A0(NodeNameType* node)
{
    if (node == OpenNode) {
        return 2;
    }
    if (node == ClosedNode) {
        return 3;
    }
    if (node == EasyAINode) {
        return 4;
    }
    if (node == MediumAINode) {
        return 5;
    }
    if (node == HardAINode) {
        return 6;
    }
    return node == ObserverNode ? 7 : 2;
}

// FUNCTION: GAMEMD 0x5E9800
//
// The inverse: the singleton node for a kind number 2..7, or null.
NodeNameType* FUN_005E9800(int kind)
{
    if (kind == 2) {
        return OpenNode;
    }
    if (kind == 3) {
        return ClosedNode;
    }
    if (kind == 4) {
        return EasyAINode;
    }
    if (kind == 5) {
        return MediumAINode;
    }
    if (kind == 6) {
        return HardAINode;
    }
    return kind == 7 ? ObserverNode : 0;
}

// FUNCTION: GAMEMD 0x5E9850
//
// Re-enable the lobby's start control (item 0x59F) in whichever of the four
// lobby dialogs is open (unless the current dialog is template 0xBC), and clear
// the +0x77 flag of every named player.
void FUN_005E9850()
{
    if (FUN_00775B20() != 0xBC) {
        HWND dialog = FUN_00775940(0xC2);
        if (dialog == 0) {
            dialog = FUN_00775940(0xC9);
            if (dialog == 0) {
                dialog = FUN_00775940(0xBC);
                if (dialog == 0) {
                    dialog = FUN_00775940(0xBD);
                }
            }
        }
        EnableWindow(GetDlgItem(dialog, 0x59F), TRUE);
    }
    int count = PlayerNodes.Count;
    for (int i = 0; i < count; i++) {
        if (wcscmp(PlayerNodes.Vector[i]->Name, BlankName) != 0 && PlayerNodes.Vector[i]->unknown_77 != 0) {
            PlayerNodes.Vector[i]->unknown_77 = 0;
        }
    }
}

// FUNCTION: GAMEMD 0x5E98F0
//
// The control id of slot `index` (0x411 + index), or -1 outside 0..7.
int FUN_005E98F0(int index)
{
    if (index == 0) {
        return 0x411;
    }
    if (index == 1) {
        return 0x412;
    }
    if (index == 2) {
        return 0x413;
    }
    if (index == 3) {
        return 0x414;
    }
    if (index == 4) {
        return 0x415;
    }
    if (index == 5) {
        return 0x416;
    }
    if (index == 6) {
        return 0x417;
    }
    return index == 7 ? 0x418 : -1;
}

// FUNCTION: GAMEMD 0x5E9950
//
// The inverse of 0x5E98F0: slot index of a slot control id, or -1.
int FUN_005E9950(int control)
{
    if (control == 0x411) {
        return 0;
    }
    if (control == 0x412) {
        return 1;
    }
    if (control == 0x413) {
        return 2;
    }
    if (control == 0x414) {
        return 3;
    }
    if (control == 0x415) {
        return 4;
    }
    if (control == 0x416) {
        return 5;
    }
    if (control == 0x417) {
        return 6;
    }
    return control == 0x418 ? 7 : -1;
}

// FUNCTION: GAMEMD 0x5E99C0
//
// The caption for a slot node: the six singletons name themselves, and any
// other node is a human player.
wchar_t* FUN_005E99C0(NodeNameType* node)
{
    if (node == OpenNode) {
        return Fetch_String_00734E60(PlayerOpenLabel, 0, NetshareFileName, 0x1354);
    }
    if (node == ClosedNode) {
        return Fetch_String_00734E60(PlayerClosedLabel, 0, NetshareFileName, 0x1356);
    }
    if (node == EasyAINode) {
        return Fetch_String_00734E60(PlayerDumbAILabel, 0, NetshareFileName, 0x1358);
    }
    if (node == MediumAINode) {
        return Fetch_String_00734E60(PlayerSmartAILabel, 0, NetshareFileName, 0x135A);
    }
    if (node == HardAINode) {
        return Fetch_String_00734E60(PlayerGeniusAILabel, 0, NetshareFileName, 0x135C);
    }
    if (node == ObserverNode) {
        return Fetch_String_00734E60(PlayerOpenObserverLabel, 0, NetshareFileName, 0x135E);
    }
    return Fetch_String_00734E60(PlayerHumanLabel, 0, NetshareFileName, 0x1360);
}

// FUNCTION: GAMEMD 0x5E9AA0
//
// Select the combo-box entry whose item data is `data`, with the control hidden
// while it changes.
void FUN_005E9AA0(HWND dialog, int control, int data)
{
    HWND item = GetDlgItem(dialog, control);
    ShowWindow(item, SW_HIDE);
    int count = (int)SendDlgItemMessageA(dialog, control, CB_GETCOUNT, 0, 0);
    for (int i = 0; i < count; i++) {
        if (SendDlgItemMessageA(dialog, control, CB_GETITEMDATA, i, 0) == data) {
            SendDlgItemMessageA(dialog, control, CB_SETCURSEL, i, 0);
            break;
        }
    }
    ShowWindow(item, SW_SHOW);
}

// FUNCTION: GAMEMD 0x5E9B20
//
// The item data of a combo-box entry (the current one when `index` is -1); CB_ERR reads as 0.
int FUN_005E9B20(HWND dialog, int control, int index)
{
    if (index == -1) {
        index = (int)SendDlgItemMessageA(dialog, control, CB_GETCURSEL, 0, 0);
    }
    int data = (int)SendDlgItemMessageA(dialog, control, CB_GETITEMDATA, index, 0);
    return data != CB_ERR ? data : 0;
}

// FUNCTION: GAMEMD 0x5E9B60
//
// Read a slot's start-position control back: for the local player's slot into
// the session and the player node, for an AI slot into the start table, and for
// any other slot clear its choices.
void FUN_005E9B60(HWND dialog, int control)
{
    int value = FUN_004E4170(dialog, control, -1);
    int slot = FUN_004E3830(control);
    if (slot == SelectedSlotIndex) {
        SessionObject_00A8B238.FUN_0069B760(value, false);
        if (PlayerNodes.Count != 0) {
            PlayerNodes.Vector[0]->FUN_00696F90(value);
        }
    } else {
        NodeNameType* node = Slots[slot];
        if (node != 0 && (node == EasyAINode || node == MediumAINode || node == HardAINode)) {
            DAT_00A8B29C[slot] = value;
            return;
        }
        DAT_00A8B29C[slot] = -1;
        DAT_00A8B27C[slot] = -1;
        DAT_00A8B2BC[slot] = -1;
    }
}

// FUNCTION: GAMEMD 0x5E9C00
//
// Read a slot's house control back. For the local player's slot the choice is
// first checked against every other holder and becomes -2 when taken, then
// goes to the session and the player node.
void FUN_005E9C00(HWND dialog, int control)
{
    int value = FUN_004E4E20(dialog, control, -1);
    int slot = FUN_004E4230(control);
    if (slot == SelectedSlotIndex) {
        FUN_004E4C20(dialog, control);
        if (House_Choice_In_Use(value)) {
            value = -2;
        }
        SessionObject_00A8B238.FUN_0069B7E0(value, false);
        if (PlayerNodes.Count != 0) {
            PlayerNodes.Vector[0]->FUN_00696FC0(value);
        }
    } else {
        DAT_00A8B2BC[slot] = value;
    }
}

// FUNCTION: GAMEMD 0x5E9CE0
//
// The same for the colour control, against the colour table.
void FUN_005E9CE0(HWND dialog, int control)
{
    int value = FUN_004E5900(dialog, control, -1);
    int slot = FUN_004E4EC0(control);
    if (slot == SelectedSlotIndex) {
        FUN_004E5700(dialog, control);
        if (Colour_Choice_In_Use(value)) {
            value = -2;
        }
        if (PlayerNodes.Count != 0) {
            PlayerNodes.Vector[0]->FUN_00696FF0(value);
        }
    } else {
        DAT_00A8B2DC[slot] = value;
    }
}

// FUNCTION: GAMEMD 0x5E9DB0
//
// Read a slot's team control back.
void FUN_005E9DB0(HWND dialog, int control)
{
    int value = FUN_004E6030(dialog, control, -1);
    int slot = FUN_004E59A0(control);
    if (slot == SelectedSlotIndex) {
        FUN_004E5ED0(dialog, control, value);
        if (PlayerNodes.Count != 0) {
            PlayerNodes.Vector[0]->FUN_00697020(value);
        }
    } else {
        DAT_00A8B2FC[slot] = value;
    }
}

// FUNCTION: GAMEMD 0x5E9E00
//
// Read all eight team controls back.
void FUN_005E9E00(HWND dialog)
{
    int i = 0;
    do {
        int control = FUN_004E5940(i);
        int value = FUN_004E6030(dialog, control, -1);
        int slot = FUN_004E59A0(control);
        if (slot == SelectedSlotIndex) {
            FUN_004E5ED0(dialog, control, value);
            if (PlayerNodes.Count != 0) {
                PlayerNodes.Vector[0]->FUN_00697020(value);
            }
        } else {
            DAT_00A8B2FC[slot] = value;
        }
        i++;
    } while (i < 8);
}

// FUNCTION: GAMEMD 0x5E9E70
//
// Put one slot's four controls in the state it calls for: enabled and shown for
// a live slot, disabled with its choices reset to -2 otherwise, and all four
// disabled and hidden (start position -3) for an observer sitting in the extra
// slot. Which controls are shown depends on how many slots the map allows.
void FUN_005E9E70(HWND dialog, int slot, unsigned char enable)
{
    int startControl = FUN_004E37D0(slot);
    int houseControl = FUN_004E41D0(slot);
    int colourControl = FUN_004E4E60(slot);
    int teamControl = FUN_004E5940(slot);

    if (NoExtraSlot >= 0 && slot == NoExtraSlot &&
        (Slots[slot] == ObserverNode || slot == 0 || Slots[slot]->unknown_6B == -1)) {
        FUN_004E3F70(dialog, startControl, -3);
        FUN_004E49A0(dialog, houseControl, -2);
        FUN_004E5480(dialog, colourControl, -2);
        FUN_004E5ED0(dialog, teamControl, -2);
        HWND start = GetDlgItem(dialog, startControl);
        EnableWindow(start, FALSE);
        HWND house = GetDlgItem(dialog, houseControl);
        EnableWindow(house, FALSE);
        ShowWindow(house, SW_HIDE);
        HWND colour = GetDlgItem(dialog, colourControl);
        EnableWindow(colour, FALSE);
        ShowWindow(colour, SW_HIDE);
        HWND team = GetDlgItem(dialog, teamControl);
        EnableWindow(team, FALSE);
        ShowWindow(team, SW_HIDE);
        return;
    }

    if (enable == 0) {
        FUN_004E3F70(dialog, startControl, -2);
        FUN_004E49A0(dialog, houseControl, -2);
        FUN_004E5480(dialog, colourControl, -2);
        FUN_004E5ED0(dialog, teamControl, -2);
    }
    HWND start = GetDlgItem(dialog, startControl);
    EnableWindow(start, enable);
    HWND house = GetDlgItem(dialog, houseControl);
    EnableWindow(house, enable);
    HWND colour = GetDlgItem(dialog, colourControl);
    EnableWindow(colour, enable);
    HWND team = GetDlgItem(dialog, teamControl);
    if (enable != 0 && DAT_00A8B23C != 0 && !DAT_00A8B23C->AlliesAllowed) {
        EnableWindow(team, FALSE);
    } else {
        EnableWindow(team, enable);
    }

    int limit;
    if (DAT_00A8B254 == -1) {
        limit = 8;
    } else {
        limit = Map_Player_Limit(DAT_00A8B254);
    }
    if (NoExtraSlot == 0 && limit < 7) {
        limit++;
    }
    if (slot < limit || slot == NoExtraSlot) {
        ShowWindow(house, SW_SHOW);
        ShowWindow(colour, SW_SHOW);
        if (SessionKind != 4 || !Is_005E8AE0_B()) {
            ShowWindow(team, SW_SHOW);
        }
    }
}

// FUNCTION: GAMEMD 0x5EA0D0
//
// Enable every slot's name control and set up all eight slots as disabled,
// then set the chosen slot up as enabled.
void FUN_005EA0D0(HWND dialog, int chosen)
{
    for (int i = 0; i < 8; i++) {
        HWND item = GetDlgItem(dialog, Slot_Control_Id(i));
        EnableWindow(item, TRUE);
        FUN_005E9E70(dialog, i, 0);
    }
    FUN_005E9E70(dialog, chosen, 1);
}

// FUNCTION: GAMEMD 0x5EA180
//
// The same pass with the name controls disabled, and the chosen slot's name
// control enabled at the end.
void FUN_005EA180(HWND dialog, int chosen)
{
    for (int i = 0; i < 8; i++) {
        HWND item = GetDlgItem(dialog, Slot_Control_Id(i));
        EnableWindow(item, FALSE);
        FUN_005E9E70(dialog, i, 0);
    }
    HWND item = GetDlgItem(dialog, Slot_Control_Id(chosen));
    EnableWindow(item, TRUE);
    FUN_005E9E70(dialog, chosen, 1);
}

// FUNCTION: GAMEMD 0x5EA2A0
//
// Show each slot's status picture: the host picture for a named player whose
// name is the blank one, the accepted picture for an AI or a ready human, and
// none otherwise.
void FUN_005EA2A0(HWND dialog)
{
    for (int i = 0; i < 8; i++) {
        HWND control = GetDlgItem(dialog, Slot_Picture_Control(i));
        NodeNameType* node = Slots[i];
        void* image = 0;
        if (node != 0 && node != OpenNode && node != ClosedNode && node != WaitingNode &&
            node != ObserverNode && node != EasyAINode && node != MediumAINode &&
            node != HardAINode && wcscmp(node->Name, BlankName) == 0) {
            image = DAT_00AC4848.GetSurface(DAT_008316CC, 0);
        } else if ((Slots[i] != 0 &&
                    (Slots[i] == EasyAINode || Slots[i] == MediumAINode || Slots[i] == HardAINode)) ||
                   Slots[i]->unknown_77 == 1) {
            image = DAT_00AC4848.GetSurface(DAT_008316D0, 0);
        }
        FUN_00603D30(control, image);
    }
}

// FUNCTION: GAMEMD 0x5EB660
//
// Turn every slot whose kind control currently shows an AI back into open (below
// the playable count) or closed, clearing its choices, and answer whether any did.
unsigned char FUN_005EB660(HWND dialog)
{
    unsigned char changed = 0;
    int playable = Playable_Slot_Count();
    for (int i = 0; i < 8; i++) {
        int control = Slot_Control_Id(i);
        WPARAM selected = SendDlgItemMessageA(dialog, control, CB_GETCURSEL, 0, 0);
        LRESULT data = SendDlgItemMessageA(dialog, control, CB_GETITEMDATA, selected, 0);
        if (data != 0 && (data == (LRESULT)EasyAINode || data == (LRESULT)MediumAINode ||
                          data == (LRESULT)HardAINode)) {
            if (i < playable) {
                Slots[i] = OpenNode;
            } else {
                Slots[i] = ClosedNode;
            }
            FUN_005E9E70(dialog, i, 0);
            DAT_00A8B27C[i] = -1;
            DAT_00A8B29C[i] = -1;
            DAT_00A8B2BC[i] = -1;
            changed = 1;
        }
    }
    return changed;
}

// FUNCTION: GAMEMD 0x5EBDD0
//
// Move the lobby from `from` open slots to `to`, each end clamped by the slot
// count when its game mode is not (vf_16) or the first predicate holds; growing
// opens slots, shrinking closes them, and either way the dialog is refreshed.
void FUN_005EBDD0(HWND dialog, int from, int to, MultiplayerGameMode* mode)
{
    if (DAT_00A8B23C != 0 && !DAT_00A8B23C->vf_16() && !Is_005E8AE0_A()) {
        int playable = Playable_Slot_Count();
        if (from > playable) {
            from = playable;
        }
    }
    if ((mode != 0 && !mode->vf_16()) || Is_005E8AE0_A()) {
        int playable = Playable_Slot_Count();
        if (to > playable) {
            to = playable;
        }
    }
    int change = to - from;
    if (change > 0) {
        FUN_005EB7B0(dialog, from, change);
        FUN_005EBA00(dialog);
        return;
    }
    if (change < 0) {
        FUN_005EBC00(dialog, to);
    }
    FUN_005EBA00(dialog);
}

// FUNCTION: GAMEMD 0x5EBEC0
//
// Refresh `count` slots from `first`: a slot whose kind control shows nothing,
// open, closed, waiting or observer is reset to open or closed by the playable
// count (the extra slot is left alone); any other kind is refreshed as it
// stands. Then redraw the range and publish the options (forced, unthrottled).
void FUN_005EBEC0(HWND dialog, int first, int count)
{
    int end = first + count;
    int playable = Playable_Slot_Count();
    for (int i = first; i < end; i++) {
        int control = Slot_Control_Id(i);
        WPARAM selected = SendDlgItemMessageA(dialog, control, CB_GETCURSEL, 0, 0);
        NodeNameType* data = (NodeNameType*)SendDlgItemMessageA(dialog, control, CB_GETITEMDATA, selected, 0);
        if (data == (NodeNameType*)-1 || data == 0 || data == OpenNode || data == ClosedNode ||
            data == ObserverNode || data == WaitingNode) {
            if (i != NoExtraSlot) {
                if (i < playable) {
                    FUN_005EC9F0(dialog, control, OpenNode, 0);
                } else {
                    FUN_005EC9F0(dialog, control, ClosedNode, 0);
                }
            }
        } else {
            FUN_005EC9F0(dialog, control, data, 0);
        }
    }
    FUN_005EB7B0(dialog, first, count);
    FUN_005DAFD0();
    FUN_005E32D0(1, 0);
}

// FUNCTION: GAMEMD 0x5EC290
//
// From slot `first` on, reset every slot to open (below the playable count) or
// closed, except the extra one, then redraw from `first`, ask the link or the
// local side to refresh, and publish the options (forced, unthrottled).
void FUN_005EC290(HWND dialog, int first)
{
    int playable = Playable_Slot_Count();
    for (int i = first; i < 8; i++) {
        int control = Slot_Control_Id(i);
        if (i < playable) {
            if (i != NoExtraSlot) {
                FUN_005EC9F0(dialog, control, OpenNode, 1);
            }
        } else {
            if (i != NoExtraSlot) {
                FUN_005EC9F0(dialog, control, ClosedNode, 1);
            }
        }
    }
    FUN_005EBC00(dialog, first);
    if (DAT_00AC116C != 0) {
        FUN_00785360();
    } else {
        FUN_005DAFD0();
    }
    FUN_005E32D0(1, 0);
}

// FUNCTION: GAMEMD 0x5ED270
//
// Select the slot-kind entry for kind number 2..7 in a combo box (the item data
// is the singleton node), with the control hidden while it changes, then refresh
// the slot.
void FUN_005ED270(HWND dialog, int control, int kind)
{
    NodeNameType* node = Node_For_Kind(kind);
    HWND item = GetDlgItem(dialog, control);
    ShowWindow(item, SW_HIDE);
    int count = (int)SendDlgItemMessageA(dialog, control, CB_GETCOUNT, 0, 0);
    for (int i = 0; i < count; i++) {
        if (SendDlgItemMessageA(dialog, control, CB_GETITEMDATA, i, 0) == (LRESULT)node) {
            SendDlgItemMessageA(dialog, control, CB_SETCURSEL, i, 0);
            break;
        }
    }
    ShowWindow(item, SW_SHOW);
    FUN_005EC9F0(dialog, control, node, 0);
}

// FUNCTION: GAMEMD 0x5ED400
// PARTIAL: best 4.4% positional, 77.2% aligned (105 of 136 instructions). Same
// control flow and the same int-indexed stores; retail keeps the snapshot pointer
// in EBP across the loop and calls SendDlgItemMessageA through its import slot
// each time, this build spills the snapshot pointer and caches the import in EBP.
// Tried: a struct view of the snapshot with named fields (further from retail),
// and the combo-box read as plain calls instead of the inlined helper.
//
// Snapshot the lobby for the other players into an int array of the layout
// LobbySnapshot_005ED400 describes: the mode and map, then for slots 1 to 7 the
// slot-kind number of the entry its kind control shows (nothing reads as the
// first kind) with the start-position and house choices, then the five option
// values. The stores index the buffer as ints (slot i's triple at element
// 7 + 3 * i) and the option bytes at +0x14..+0x18.
void FUN_005ED400(HWND dialog, int* snapshot)
{
    snapshot[0] = GameModeOptions.unknown_00;
    snapshot[1] = DAT_00A8B254;
    for (int i = 1; i < 8; i++) {
        int control = Slot_Control_Id(i);
        NodeNameType* data = (NodeNameType*)Combo_Item_Data(dialog, control, -1);
        snapshot[i * 3 + 7] = Kind_Of_Node(data);
        snapshot[i * 3 + 8] = FUN_004E4170(dialog, FUN_004E37D0(i), -1);
        snapshot[i * 3 + 9] = FUN_004E4E20(dialog, FUN_004E41D0(i), -1);
    }
    snapshot[2] = DAT_00A8B268;
    snapshot[3] = DAT_00A8B25C;
    snapshot[4] = DAT_00A8B270;
    ((unsigned char*)snapshot)[0x14] = DAT_00A8B262;
    ((unsigned char*)snapshot)[0x15] = DAT_00A8B263;
    ((unsigned char*)snapshot)[0x16] = DAT_00A8B264;
    ((unsigned char*)snapshot)[0x17] = DAT_00A8B320;
    ((unsigned char*)snapshot)[0x18] = DAT_00A8B261;
}

// FUNCTION: GAMEMD 0x5EDD00
//
// Read the player-name edit field: keep at most 0x78 characters when the name
// fits a narrow copy, otherwise cut it at the first character above 0x100 (but
// never below 0x28), write the cut text back, strip the trailing set and return
// a copy.
Obj_007B66D0 FUN_005EDD00(HWND edit)
{
    Obj_007B66D0 text;
    FUN_00623EA0(edit, &text);
    unsigned int limit = 0x78;
    if (!text.FUN_007B7D90()) {
        for (limit = 0; limit < text.FUN_007B71B0(); limit++) {
            if (text.FUN_007B7180(limit) > 0x100) {
                break;
            }
        }
        limit--;
        if (limit <= 0x28) {
            limit = 0x28;
        }
    }
    if (text.FUN_007B71B0() > limit) {
        text.FUN_007B78D0(limit);
        SendMessageA(edit, 0x4B2, 0, (LPARAM)text.FUN_007B7140());
    }
    {
        Obj_007B66D0 set(DAT_00831D9C);
        text.FUN_007B6F40(&set);
    }
    return text;
}

// FUNCTION: GAMEMD 0x5EDDE0
// PARTIAL: best 63.0% (68 of 108 instructions). Retail keeps the dialog in EBP
// and the player name in EBX (so the allies flag is compared straight from
// memory); this build swaps the two and loads the flag into BL. Tried:
// declaration order of the control ids, `== 0` against `!` on the flag, the
// slot search as a helper taking the name.
//
// Enable or disable the four controls of the local player's slot (every slot but
// the extra one); the team control stays off when the game mode forbids allies.
void FUN_005EDDE0(HWND dialog, unsigned char enable)
{
    if (dialog != 0) {
        int slot = Local_Player_Slot();
        if (slot != NoExtraSlot) {
            HWND item = GetDlgItem(dialog, FUN_004E37D0(slot));
            if (item != 0) {
                EnableWindow(item, enable);
            }
            item = GetDlgItem(dialog, FUN_004E41D0(slot));
            if (item != 0) {
                EnableWindow(item, enable);
            }
            item = GetDlgItem(dialog, FUN_004E4E60(slot));
            if (item != 0) {
                EnableWindow(item, enable);
            }
            item = GetDlgItem(dialog, FUN_004E5940(slot));
            if (item != 0) {
                if (enable == 1 && DAT_00A8B23C != 0 && !DAT_00A8B23C->AlliesAllowed) {
                    EnableWindow(item, FALSE);
                    return;
                }
                EnableWindow(item, enable);
            }
        }
    }
}

// FUNCTION: GAMEMD 0x5EDEF0
//
// The token for a slot node: the six singletons name themselves and anything
// else reads as waiting.
Wstring FUN_005EDEF0(NodeNameType* node)
{
    if (node == OpenNode) {
        return Wstring(DAT_00831704);
    }
    if (node == ClosedNode) {
        return Wstring(DAT_00831708);
    }
    if (node == WaitingNode) {
        return Wstring(DAT_0083170C);
    }
    if (node == EasyAINode) {
        return Wstring(DAT_00831710);
    }
    if (node == MediumAINode) {
        return Wstring(DAT_00831714);
    }
    if (node == HardAINode) {
        return Wstring(DAT_00831718);
    }
    if (node == ObserverNode) {
        return Wstring(DAT_0083171C);
    }
    return Wstring(DAT_0083170C);
}

// FUNCTION: GAMEMD 0x5EDFC0
//
// The singleton node a wide token names, or null (also when the token does not
// fit a narrow copy).
NodeNameType* FUN_005EDFC0(Obj_007B66D0* token)
{
    if (token->FUN_007B7D90()) {
        Wstring narrow = FUN_007B7F90(*token);
        if (narrow.FUN_007B4710(DAT_00831704)) {
            NodeNameType* node = OpenNode;
            return node;
        }
        if (narrow.FUN_007B4710(DAT_00831708)) {
            NodeNameType* node = ClosedNode;
            return node;
        }
        if (narrow.FUN_007B4710(DAT_0083170C)) {
            NodeNameType* node = WaitingNode;
            return node;
        }
        if (narrow.FUN_007B4710(DAT_00831710)) {
            NodeNameType* node = EasyAINode;
            return node;
        }
        if (narrow.FUN_007B4710(DAT_00831714)) {
            NodeNameType* node = MediumAINode;
            return node;
        }
        if (narrow.FUN_007B4710(DAT_00831718)) {
            NodeNameType* node = HardAINode;
            return node;
        }
        if (narrow.FUN_007B4710(DAT_0083171C)) {
            NodeNameType* node = ObserverNode;
            return node;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x5EE100
//
// Is this one of the seven slot-kind tokens?
int FUN_005EE100(Wstring* token)
{
    if (token->FUN_007B4710(DAT_00831704) || token->FUN_007B4710(DAT_00831708) ||
        token->FUN_007B4710(DAT_0083170C) || token->FUN_007B4710(DAT_00831710) ||
        token->FUN_007B4710(DAT_00831714) || token->FUN_007B4710(DAT_00831718) ||
        token->FUN_007B4710(DAT_0083171C)) {
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x5EE190
// Calls other functions.
int __cdecl FUN_005EE190()
{
    int c0 = DAT_008870C0.FUN_005276D0(DAT_0082642C, DAT_00831DA4, 0);
    DAT_00AC10C8 = c0;
    return c0;
}

// FUNCTION: GAMEMD 0x5EE200
//
// Redraw the observer-dependent parts of a lobby dialog: the observer check box
// (0x760), its picture (0x75F), and the join / observe captions of buttons 0x6CD
// and 0x62D (the second reads "Join Game" in the dialog with template 0x113).
void FUN_005EE200(HWND dialog)
{
    if (dialog != 0) {
        HWND item = GetDlgItem(dialog, 0x760);
        if (item != 0) {
            SendMessageA(item, 0xF1, DAT_00AC10C8 != 0, 0);
        }
        void* surface;
        if (DAT_00AC10C8 != 0) {
            surface = DAT_00AC4848.GetSurface("wolob.pcx", 0);
        } else {
            surface = DAT_00AC4848.GetSurface("wolnob.pcx", 0);
        }
        HWND image = GetDlgItem(dialog, 0x75F);
        FUN_00603D30(image, surface);
        item = GetDlgItem(dialog, 0x6CD);
        if (item != 0) {
            const wchar_t* caption;
            if (DAT_00AC10C8 != 0) {
                caption = Fetch_String_00734E60("GUI:Observe", 0, NetshareFileName, 0x1A5F);
            } else {
                caption = Fetch_String_00734E60("GUI:Join", 0, NetshareFileName, 0x1A61);
            }
            SendMessageA(item, 0x4B2, 0, (LPARAM)caption);
            InvalidateRect(item, 0, FALSE);
        }
        item = GetDlgItem(dialog, 0x62D);
        if (item != 0) {
            const wchar_t* caption;
            if (DAT_00AC10C8 != 0) {
                caption = Fetch_String_00734E60("GUI:Observe", 0, NetshareFileName, 0x1A6A);
            } else if (FUN_00775940(0x113) == dialog) {
                caption = Fetch_String_00734E60("GUI:JoinGame", 0, NetshareFileName, 0x1A6E);
            } else {
                caption = Fetch_String_00734E60("GUI:Join", 0, NetshareFileName, 0x1A70);
            }
            SendMessageA(item, 0x4B2, 0, (LPARAM)caption);
            InvalidateRect(item, 0, FALSE);
        }
    }
}

// FUNCTION: GAMEMD 0x5EE350
//
// Run the 0x5EE200 refresh on the given dialog and on each of the three other
// lobby dialogs (0x116, 0x113, 0xBB) that is open.
void FUN_005EE350(HWND dialog)
{
    if (dialog != 0) {
        FUN_005EE200(dialog);
    }
    HWND other = FUN_00775940(0x116);
    if (other != 0) {
        FUN_005EE200(other);
    }
    other = FUN_00775940(0x113);
    if (other != 0) {
        FUN_005EE200(other);
    }
    other = FUN_00775940(0xBB);
    if (other != 0) {
        FUN_005EE200(other);
        return;
    }
}

// FUNCTION: GAMEMD 0x5EE6A0
//
// Read every slot's colour control back into its node.
void FUN_005EE6A0(HWND dialog)
{
    if (dialog != 0) {
        for (int i = 0; i < 8; i++) {
            int control = FUN_004E4E60(i);
            FUN_004E5700(dialog, control);
            int value = FUN_004E5900(dialog, control, -1);
            if (Slots[i] != 0) {
                Slots[i]->FUN_00696FF0(value);
            }
        }
    }
}
