// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read off the user's retail gamemd.exe v1.001: the dialog at 0x6956D0 and its callers in PhoneEd.cpp.
//   Every name is a placeholder.
#ifndef GG_MATCH_SERIAL_ED_DIALOG_H
#define GG_MATCH_SERIAL_ED_DIALOG_H

#include <stddef.h>
#include <windows.h>
#include "_rt/gg_static_assert.h"

// The serial settings block: 0x70 bytes, at +0x88 of the dialog object and at the head of a phone-book entry.
struct SerialSettings_006956D0
{
    int Port;                       // +0x00 zero = not set
    int unknown_04;                 // +0x04 -1 = not set
    int Baud;                       // +0x08 -1 = not set
    int unknown_0C;                 // +0x0C
    int unknown_10;                 // +0x10
    int unknown_14;                 // +0x14
    int unknown_18[2];              // +0x18
    unsigned char unknown_20;       // +0x20
    unsigned char pad_21[3];
    int unknown_24[0x13];           // +0x24
};
GG_STATIC_ASSERT(sizeof(SerialSettings_006956D0) == 0x70);
GG_STATIC_ASSERT(offsetof(SerialSettings_006956D0, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(SerialSettings_006956D0, unknown_20) == 0x20);

// The serial-port editor dialog object (0x374 bytes, from the stack local of its caller in PhoneEd.cpp).
struct SerialEdDialog_006956D0
{
    HWND Window;                            // +0x00
    int Result;                             // +0x04
    unsigned char unknown_08[0x80];         // +0x08
    SerialSettings_006956D0 Settings;       // +0x88
    unsigned char unknown_F8[0x374 - 0xF8]; // +0xF8
    // FUNCTION: GAMEMD 0x695FD0 (decl; reloc) -- fill the controls from the settings.
    void FUN_00695FD0(SerialSettings_006956D0* settings);
    // FUNCTION: GAMEMD 0x6956D0
    bool FUN_006956D0(SerialSettings_006956D0* settings);
};
GG_STATIC_ASSERT(offsetof(SerialEdDialog_006956D0, Result) == 0x4);
GG_STATIC_ASSERT(offsetof(SerialEdDialog_006956D0, Settings) == 0x88);
GG_STATIC_ASSERT(sizeof(SerialEdDialog_006956D0) == 0x374);

#endif  // GG_MATCH_SERIAL_ED_DIALOG_H
