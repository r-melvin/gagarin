// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check (names only)
//   TerrainClass members read off retail gamemd.exe v1.001 (vtable 0x7F522C), placed beside
//   tu242_terrain_class.cpp so that file's rows are untouched.
//   Address index: 0x71C8E0, 0x71CB90.

#include "terrain_objects/terrain_class.h"

// FUNCTION: GAMEMD 0x71C8E0
// Marks the object for removal once, restarting its stage timer at rate 2 with the value cleared.
void TerrainClass::StartDying()
{
    if (!TimeToDie) {
        TimeToDie = true;
        SetRate(2);
        Value = 0;
    }
}

// ---------------------------------------------------------------------------
// 0x71CB90: writes every live terrain object into the [Terrain] section of a map INI.
struct TerrainIniWriteView
{
    // FUNCTION: GAMEMD 0x5257C0 (decl; reloc) - clears one section (key null) or one key.
    bool Clear(const char* section, const char* key);
    // FUNCTION: GAMEMD 0x528660 (decl; reloc)
    bool WriteString(const char* section, const char* key, const char* value);
};
// GLOBAL: GAMEMD 0x7F51F0 - the pointer to the text "Terrain".
extern const char* DAT_007F51F0;
// FUNCTION: GAMEMD 0x7C8EF4 (decl; reloc)
extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);

// FUNCTION: GAMEMD 0x71CB90
// Each entry is keyed by its cell number (row * 1000 + column) and holds the type's ID.
void __fastcall FUN_0071CB90(TerrainIniWriteView* ini)
{
    ini->Clear(DAT_007F51F0, 0);
    for (int i = 0; i < TerrainArray.Count; i++) {
        TerrainClass* terrain = TerrainArray.Items[i];
        if (terrain && !terrain->InLimbo && terrain->IsAlive) {
            CellStruct cell = terrain->vf_110();
            char key[12];
            sprintf(key, "%d", cell.Y * 1000 + cell.X);
            ini->WriteString(DAT_007F51F0, key, (const char*)&terrain->Type->ID);
        }
    }
}
