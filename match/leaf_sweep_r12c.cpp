// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Name lookups over two sound-name registries, read off the user's retail gamemd.exe v1.001 with
//   the local Ghidra CLI at the address in each annotation. The element types are placeholders.
//   Address index: 0x751520, 0x7532D0.

extern "C" int __cdecl _stricmp(const char* a, const char* b);

// ---------------------------------------------------------------------------
// 0x7532D0: the registry entry (a name record starting with its text) matching a name.
// GLOBAL: GAMEMD 0xB1D4A4
extern "C" char** DAT_00B1D4A4;
// GLOBAL: GAMEMD 0xB1D4B0
extern "C" int DAT_00B1D4B0;

// FUNCTION: GAMEMD 0x7532D0
char* __fastcall FUN_007532D0(const char* name)
{
    if (name && _stricmp(name, "<none>") != 0) {
        for (int i = 0; i < DAT_00B1D4B0; i++) {
            if (_stricmp(name, DAT_00B1D4A4[i]) == 0) {
                return DAT_00B1D4A4[i];
            }
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x751520: the registry entry whose name (or the fixed text for an empty one) matches.
struct Named_00751520
{
    // FUNCTION: GAMEMD 0x405170 (decl; reloc)
    const char* FUN_00405170();
};
struct Entry_00751520
{
    Named_00751520* unknown_0;
};
// GLOBAL: GAMEMD 0xB1D37C
extern "C" Entry_00751520** DAT_00B1D37C;
// GLOBAL: GAMEMD 0xB1D388
extern "C" int DAT_00B1D388;
// GLOBAL: GAMEMD 0x846574
extern "C" const char DAT_00846574[];

// FUNCTION: GAMEMD 0x751520
Entry_00751520* __fastcall FUN_00751520(const char* name)
{
    if (name && _stricmp(name, "<none>") != 0) {
        for (int i = 0; i < DAT_00B1D388; i++) {
            Entry_00751520* entry = DAT_00B1D37C[i];
            const char* text;
            if (entry->unknown_0) {
                text = entry->unknown_0->FUN_00405170();
            } else {
                text = DAT_00846574;
            }
            if (_stricmp(name, text) == 0) {
                return DAT_00B1D37C[i];
            }
        }
    }
    return 0;
}
