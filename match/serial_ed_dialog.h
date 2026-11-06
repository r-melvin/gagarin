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
    char Text[0x80];                        // +0x08 the entered text (WM_GETTEXT with 0x80 at 0x696AE0, 0x40 at 0x6967B0)
    SerialSettings_006956D0 Settings;       // +0x88
    unsigned char unknown_F8[0x374 - 0xF8]; // +0xF8
    // FUNCTION: GAMEMD 0x6956D0
    bool FUN_006956D0(SerialSettings_006956D0* settings);
    // FUNCTION: GAMEMD 0x695FD0 -- fill the controls from the settings.
    void FUN_00695FD0(SerialSettings_006956D0* settings);
    // FUNCTION: GAMEMD 0x696200 (decl; reloc) -- fill the port combo.
    void FUN_00696200();
    // FUNCTION: GAMEMD 0x6964C0 -- fill the baud combo.
    void FUN_006964C0();
    // FUNCTION: GAMEMD 0x696590 -- fill the four-entry combo and select the matching entry.
    void FUN_00696590();
    // FUNCTION: GAMEMD 0x696610 -- refill the list control from the global entries.
    void FUN_00696610();
    // FUNCTION: GAMEMD 0x6966D0 -- set the two radio buttons from the mode selector.
    void FUN_006966D0();
    // FUNCTION: GAMEMD 0x696740 -- show and enable a text control, filling it with the part after the '-'.
    void FUN_00696740(int id);
    // FUNCTION: GAMEMD 0x6967B0 -- take the typed port text and select its combo entry.
    void FUN_006967B0();
    // FUNCTION: GAMEMD 0x696950 -- hide the text control and read its text back.
    void FUN_00696950();
    // FUNCTION: GAMEMD 0x6969C0 -- label a combo entry as custom when its text differs.
    void FUN_006969C0(int id, int data, char* text);
    // FUNCTION: GAMEMD 0x696AE0 -- take the typed list text and select or add its entry.
    void FUN_00696AE0();
};
GG_STATIC_ASSERT(offsetof(SerialEdDialog_006956D0, Result) == 0x4);
GG_STATIC_ASSERT(offsetof(SerialEdDialog_006956D0, Settings) == 0x88);
GG_STATIC_ASSERT(offsetof(SerialEdDialog_006956D0, Text) == 0x8);
GG_STATIC_ASSERT(sizeof(SerialEdDialog_006956D0) == 0x374);

#endif  // GG_MATCH_SERIAL_ED_DIALOG_H
