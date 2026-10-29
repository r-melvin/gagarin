// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every displacement, constant and callee below was read off the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI at the address in each annotation.
//   The owning classes are not bound by RTTI or a binary string at these addresses,
//   so each receiver keeps a placeholder name derived from its address.
//
// Round 25 small unowned leaves. Address index: 0x46D400, 0x4F2640, 0x53F540.
#include <windows.h>
#include <string.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../network/transport/winsock_interface_class.h"

extern char DAT_0089E000[8];

// FUNCTION: GAMEMD 0x46D400
// Sets all eight slot flags, then clears the first `count` bytes.
void __fastcall FUN_0046D400(int count)
{
    memset(DAT_0089E000, 1, 8);
    if (count > 0)
        memset(DAT_0089E000, 0, count);
}

// Sub-object at +0x04 of Obj_004F2640 with two member helpers (0x5D1C20 / 0x5D1C90).
struct Sub_005D1C20
{
    void FUN_005D1C20(int item);
    void FUN_005D1C90(int old, int item);
};

struct Obj_004F2640
{
    char         Pad_00[0x04];
    Sub_005D1C20 Sub;          // +0x04
    char         Pad_05[0x54 - 0x05];
    int          Current;      // +0x54
    // FUNCTION: GAMEMD 0x4F2640
    void FUN_004F2640(int item);
};
GG_STATIC_ASSERT(offsetof(Obj_004F2640, Sub) == 0x04);
GG_STATIC_ASSERT(offsetof(Obj_004F2640, Current) == 0x54);

// FUNCTION: GAMEMD 0x4F2640
// Replaces the current entry: updates through one helper when set, adds through the other when empty.
void Obj_004F2640::FUN_004F2640(int item)
{
    if (Current)
        Sub.FUN_005D1C90(Current, item);
    else
        Sub.FUN_005D1C20(item);
    Current = item;
}

// GLOBAL: GAMEMD 0xA8EBB4
extern int DAT_00A8EBB4;
// GLOBAL: GAMEMD 0xAA0568
extern int DAT_00AA0568;
// GLOBAL: GAMEMD 0xAA05A8
extern int DAT_00AA05A8;
// GLOBAL: GAMEMD 0xAA05AC
extern int DAT_00AA05AC;

// FUNCTION: GAMEMD 0x53F540
// Configures the network interface and opens it on the saved socket number; keeps it open only
// if it then starts listening.
int FUN_0053F540()
{
    int socketNumber = DAT_00AA0568;
    Interface_00887628->Slot20(DAT_00A8EBB4);
    DAT_00AA05A8 = Interface_00887628->Init(socketNumber & 0xFFFF);
    if (DAT_00AA05A8)
    {
        if (Interface_00887628->StartListening())
        {
            DAT_00AA05AC = 1;
            return 1;
        }
        Interface_00887628->vf_1();
        DAT_00AA05A8 = 0;
    }
    return 0;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xAA0568
int DAT_00AA0568;
// GLOBAL: GAMEMD 0xAA05AC
int DAT_00AA05AC;
// END defined globals
