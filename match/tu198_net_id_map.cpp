// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail gamemd.exe v1.001, translation unit between Restate.cpp and Scenario.CPP
//   (no source-file string of its own). Each function disassembled from the retail
//   image; names are address placeholders. Methods of the id registry at 0xB052D0,
//   declared in conn_types.h. Ordered ascending by retail address.

#include <windows.h>
#include "connman_class.h"
#include "_layout/elapsed_timer.h"
#include "_layout/house_class.h"
#include "_layout/session_class.h"

// GLOBAL: GAMEMD 0xA83D4C -- the local player's house.
extern HouseClass* DAT_00A83D4C;
// GLOBAL: GAMEMD 0xA8E2CC
extern int DAT_00A8E2CC;
// FUNCTION: GAMEMD 0x48D080 (decl; reloc) -- the yield, no arguments.
void __cdecl FUN_0048D080();

// FUNCTION: GAMEMD 0x663CD0
// The flag byte of the record whose node address matches; 0xFF for a null or broadcast address.
unsigned char NetIdMapRef::FUN_00663CD0(IPXAddressClass* address)
{
    if (!address) return 0xFF;
    if (address->IsBroadcast()) return 0xFF;
    NetworkNumberType network;
    NodeAddressType node;
    unsigned char result = 0;
    address->FUN_0053EDA0(network, node);
    for (int i = 0; i < Count; i++) {
        if (node.Low == Items[i]->Node.Low) {
            result = Items[i]->unknown_28;
            break;
        }
    }
    return result;
}

// FUNCTION: GAMEMD 0x664240
// Store an address's node bytes (low dword) on the record with the given id.
void NetIdMapRef::FUN_00664240(int id, IPXAddressClass* address)
{
    NetworkNumberType network;
    NodeAddressType node;
    address->FUN_0053EDA0(network, node);
    for (int i = 0; i < Count; i++) {
        if (Items[i]->Key == id) {
            Items[i]->Node.Low = node.Low;
            return;
        }
    }
}

// FUNCTION: GAMEMD 0x664440
// Select the active record (the stored id, or the first live unselected one), mark it, and for the local
// player in a larger game pass that player's address to 0x663DB0. Returns the selected id.
int NetIdMapRef::FUN_00664440()
{
    int key = DAT_00A8E2CC;
    if (key == -1) {
        for (int i = 0; i < Count; i++) {
            NetIdEntry* entry = Items[i];
            if (entry->unknown_29 && !entry->unknown_27) {
                key = entry->Key;
                entry->unknown_27 = 1;
            }
        }
    } else {
        for (int i = 0; i < Count; i++) {
            NetIdEntry* entry = Items[i];
            if (entry->Key == key) entry->unknown_27 = 1;
            else entry->unknown_27 = 0;
        }
    }
    if (!Session_00A8B238.FUN_00697E70(0) && key != -1 && key == DAT_00A83D4C->ArrayIndex
        && PlayerCount_00A8DA84 > 2) {
        IPXAddressClass* address = 0;
        for (int j = 0; j < PlayerCount_00A8DA84; j++) {
            if (Players_00A8DA78[j]->unknown_6F == key) {
                address = &Players_00A8DA78[j]->Address;
                break;
            }
        }
        NetworkNumberType network;
        NodeAddressType node;
        address->FUN_0053EDA0(network, node);
        FUN_00663DB0(node.Node);
    }
    return key;
}

// FUNCTION: GAMEMD 0x664530
// Send the shutdown packet to the router and drain its queue for up to 900 ticks.
void NetIdMapRef::FUN_00664530()
{
    char packet[0x152] = {0};
    ScenarioElapsedTimer timer;
    if (unknown_18 && RouterProcess) {
        packet[0] = 3;
        Manager_00A8E9C0.FUN_00541410(packet, 0x152, 1);
        timer = ScenarioElapsedTimer(900);
        while (Manager_00A8E9C0.IPXManagerClass::vf_20() > 0) {
            if (!timer.GetTimeLeft()) break;
            FUN_0048D080();
        }
    }
}

// FUNCTION: GAMEMD 0x664610
// Wait for the router process to exit; with `flag` terminate it when the wait times out.
bool NetIdMapRef::FUN_00664610(int timeout, bool flag)
{
    FUN_004068E0("Wait_For_Router_Shutdown - hRouterProcess = %d\n", RouterProcess);
    if (RouterProcess) {
        if (WaitForMultipleObjects(1, &RouterProcess, 0, timeout) == WAIT_TIMEOUT) {
            if (!flag) return false;
            FUN_004068E0("***Router process still running - shutting it down***\n");
            BOOL ok = TerminateProcess(RouterProcess, 0);
            if (!ok) FUN_004068E0("Failed to shut down router - error code %d - %s\n", GetLastError(), ok);
            else RouterProcess = 0;
            return ok != 0 ? true : false;
        }
        FUN_004068E0("Router not running\n");
        RouterProcess = 0;
    }
    return true;
}
