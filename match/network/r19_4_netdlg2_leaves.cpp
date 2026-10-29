// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Placement lead: this file regresses under the project /Ob2 default, so a
// definition it can see probably lived in another original file.
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. Helpers of the
//   netdlg2.cpp object (source-file string 0x831288, code range 0x5DACF0..0x5E242F).
//
// Address index: 0x5DB600 0x5DB680 0x5DBEC0 0x5E2340

#define NO_STRICT
#define LocalHandle LocalHandle_Win32
#include <windows.h>
#include "../_layout/session_class.h"
#undef LocalHandle
#include <string.h>
#include "../_rt/gg_static_assert.h"
#include "../economy/netshare_common.h"
#include "../_layout/node_name_type.h"
#include "transport/connman_class.h"
#include "../core/init_misc_methods.h"
#include "../economy/netshare_slot_nodes.h"

// FUNCTION: GAMEMD 0x775B10 (decl; reloc) -- the current dialog window.
HWND __cdecl FUN_00775B10();
// FUNCTION: GAMEMD 0x5DBEC0 (decl; reloc) -- slot of the player named by the argument (NULL: local).
int __fastcall FUN_005DBEC0(const char* name);
// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- string-table fetch; label in ECX, file and line on the stack.
extern "C" wchar_t* __fastcall Fetch_String_00734E60(const char* label, int flag, const char* file, int line);
// FUNCTION: GAMEMD 0x5E2700 (decl; reloc) -- append a formatted line to the lobby chat list.
void __cdecl FUN_005E2700(int param, const wchar_t* format, ...);

// STRING: GAMEMD 0x83168C  "GUI:HostGameStartJoiner"
extern char HostGameStartJoinerLabel_0083168C[];
// STRING: GAMEMD 0x831288  source-file string of this object
extern char NetDlg2FileName_00831288[];

// FUNCTION: GAMEMD 0x5E2340
// PARTIAL: 84.6% -- same instructions as retail; retail loads the fastcall register arguments
// (xor edx / mov ecx) before pushing the line and file, cl pushes first.
// When the local player is not the first slot, grey the start control and post the
// "host start joiner" text to the chat list.
void __cdecl FUN_005E2340()
{
    HWND dialog = FUN_00775B10();
    HWND item = GetDlgItem(dialog, 0x59F);
    if (FUN_005DBEC0(0) != 1) {
        SendMessageA(item, 0x4DC, 0, 1);
        FUN_005E2700(-1, Fetch_String_00734E60(HostGameStartJoinerLabel_0083168C, 0,
                                               NetDlg2FileName_00831288, 0x14B4));
    }
}

// The shared message buffer as the kind-8 message sees it: the payload at +0x2F is one dword.
#pragma pack(push, 1)
struct NetshareKind8Packet_00A8D638
{
    int  Command;              // +0x00
    char Name[0x2B];           // +0x04
    int  Value;                // +0x2F
    char unknown_33[0x1C7 - 0x33];
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(NetshareKind8Packet_00A8D638, Value) == 0x2F &&
                 sizeof(NetshareKind8Packet_00A8D638) == 0x1C7);
// GLOBAL: GAMEMD 0xA8D638 -- the same buffer as DAT_00A8D638 in netshare_common.h.
extern NetshareKind8Packet_00A8D638 Kind8Packet_00A8D638;

// GLOBAL: GAMEMD 0xA8D610 -- the local player's wide name.
extern wchar_t LocalWideName_00A8D610[];

// FUNCTION: GAMEMD 0x5DB600
// Send the kind-8 message (payload 4) to one player node.
void __fastcall FUN_005DB600(NodeNameType* node)
{
    memset(&Kind8Packet_00A8D638, 0, sizeof(Kind8Packet_00A8D638));
    Kind8Packet_00A8D638.Command = 8;
    Kind8Packet_00A8D638.Value = 4;
    Manager_00A8E9C0.FUN_005410F0(&Kind8Packet_00A8D638, 0x1C7, 1, &node->Address, 0, 0);
}

// Network bring-up for a dialog: as FUN_005DA6C0, then rebuild the lobby state.
// FUNCTION: GAMEMD 0x5DB680
bool __cdecl FUN_005DB680()
{
    int            first;
    Rec6_005DA6C0  rest;

    if (Manager_00A8E9C0.Init() == 0) {
        return false;
    }

    if (Session_00A8B238.GameMode != 4 && DAT_00A8D5FC != 0) {
        DAT_00A8D600.FUN_0053EDA0(&first, &rest);
        Manager_00A8E9C0.FUN_00542FC0(&first);
    }

    Build_Slot_Nodes();
    Clear_Lobby_Flags();
    Reset_Lobby();
    return true;
}

// FUNCTION: GAMEMD 0x5DBEC0
// Look a player up by name: 1 for the local player (a null name means the local handle),
// otherwise that player's +0x77 field, or -1 when no player has the name.
int __fastcall FUN_005DBEC0(const char* name)
{
    if (name == 0) {
        name = LocalHandle;
    }
    if (wcscmp(Widen_00735120(name), LocalWideName_00A8D610) == 0) {
        return 1;
    }
    int found = -1;
    for (int i = 0; i < PlayerCount_00A8DA84; i++) {
        if (_stricmp(Narrow_007350C0(Players_00A8DA78[i]->Name), name) == 0) {
            found = i;
        }
    }
    if (found != -1) {
        return Players_00A8DA78[found]->unknown_77;
    }
    return -1;
}
