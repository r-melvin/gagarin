// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Combo box item-data read, repeated unchanged at three addresses: when the
// index is -1 the current selection (0x147) is queried first, then the item
// data (0x150) at that index is returned. Both messages go through the
// SendDlgItemMessageA import (0x7E1490).

#include <windows.h>

// FUNCTION: GAMEMD 0x004E4E20
int FUN_004E4E20(HWND dialog, int controlId, int index)
{
    if (index == -1)
        index = (int)SendDlgItemMessageA(dialog, controlId, CB_GETCURSEL, 0, 0);
    return (int)SendDlgItemMessageA(dialog, controlId, CB_GETITEMDATA, index, 0);
}

// FUNCTION: GAMEMD 0x004E5900
int FUN_004E5900(HWND dialog, int controlId, int index)
{
    if (index == -1)
        index = (int)SendDlgItemMessageA(dialog, controlId, CB_GETCURSEL, 0, 0);
    return (int)SendDlgItemMessageA(dialog, controlId, CB_GETITEMDATA, index, 0);
}

// FUNCTION: GAMEMD 0x004E6030
int FUN_004E6030(HWND dialog, int controlId, int index)
{
    if (index == -1)
        index = (int)SendDlgItemMessageA(dialog, controlId, CB_GETCURSEL, 0, 0);
    return (int)SendDlgItemMessageA(dialog, controlId, CB_GETITEMDATA, index, 0);
}
