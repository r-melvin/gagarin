// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x690530 in the user's gamemd.exe v1.001.
//
// Address index: 0x690530
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2

extern "C" int __cdecl _stricmp(const char*, const char*);

// FUNCTION: GAMEMD 0x407000 (decl; reloc) -- true once the session object exists.
int SessionExists();

struct NamedEntry_00690530 {
    const char* Name;   // +0x00
};

struct NameList_00690530 {
    char unknown_00[0x38];
    NamedEntry_00690530** Items;   // +0x38
    char unknown_3C[8];
    int Count;                     // +0x44

    // FUNCTION: GAMEMD 0x690530 (__thiscall)
    void Find(const char* name, int unused);
};

// FUNCTION: GAMEMD 0x690530
// Walk the entry list comparing names case-insensitively until one matches.
void NameList_00690530::Find(const char* name, int unused)
{
    if (name != 0 && SessionExists()) {
        for (int i = 0; i < Count; i++) {
            const char* entry = Items[i]->Name;
            if (_stricmp(name, entry) == 0)
                break;
        }
    }
}
