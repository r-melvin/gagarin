// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x465CC0.
//
// STRING: GAMEMD 0x81AEF0  "ToTile"

#include "tile_link_resolve_methods.h"

// FUNCTION: GAMEMD 0x465CC0
//
// Resolve every entry's ToTile key to a tile index and store the tile it names.
// An unreadable or unknown name leaves the entry's existing value alone, which is
// why the bounds check guards only the store.
//
// The buffer is cleared to an empty string before each read rather than relying
// on the default argument, which is passed as null.
void FUN_00465CC0()
{
    char buffer[0x3C];

    int i = 0;
    while (i < DAT_00A83C78) {
        Entry_00465CC0* entry = DAT_00A83C6C[i];
        buffer[0] = 0;
        DAT_00887048->FUN_00528A10(entry->Name, "ToTile", 0, buffer, 0x3C);

        int tile = FUN_00544CE0(buffer);
        if (tile >= 0 && tile < DAT_00A8ED38) {
            entry->ToTile = DAT_00A8ED2C[tile];
        }
        i++;
    }
}
