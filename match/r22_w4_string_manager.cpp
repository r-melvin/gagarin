// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   String-manager lookup read off the user's retail gamemd.exe v1.001 with the local Ghidra CLI.
//   Address index: 0x734E60.

#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <new>

struct StringTableEntry_00734E60
{
    char Label[0x24];   // +0x00, compared case-insensitively
    int Index;          // +0x24
};

struct MissingString_00734E60
{
    MissingString_00734E60* Next;   // +0x00
    wchar_t Text[0x102];            // +0x04
};

// GLOBAL: GAMEMD 0xB1CF74 -- sorted label table (0x28-byte entries).
extern StringTableEntry_00734E60* DAT_00B1CF74;
// GLOBAL: GAMEMD 0xB1CF6C -- number of label entries.
extern int DAT_00B1CF6C;
// GLOBAL: GAMEMD 0xB1CF78 -- text pointers by index.
extern wchar_t** DAT_00B1CF78;
// GLOBAL: GAMEMD 0xB1CF7C -- per-index values.
extern int* DAT_00B1CF7C;
// GLOBAL: GAMEMD 0xB1CF88 -- chain of placeholder strings made for unknown labels.
extern MissingString_00734E60* DAT_00B1CF88;

int __cdecl swprintf(wchar_t* out, const wchar_t* format, ...); // LIBRARY: GAMEMD 0x7CA564
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- debug log.
void __cdecl FUN_004068E0(const char* format, const char* key, const char* file, int line);

// FUNCTION: GAMEMD 0x734E60
// Finds the localised text for a label; an unknown label logs and yields a "MISSING" placeholder.
wchar_t* __fastcall FUN_00734E60(const char* key, int* outValue, const char* file, int line)
{
    if (outValue) {
        *outValue = 0;
    }
    if (!DAT_00B1CF74) {
        return L"***FATAL*** String Manager failed to initilaized properly";
    }
    StringTableEntry_00734E60* found = (StringTableEntry_00734E60*)bsearch(
        key, DAT_00B1CF74, DAT_00B1CF6C, 0x28, (int (__cdecl*)(const void*, const void*))_strcmpi);
    if (found) {
        if (outValue) {
            *outValue = DAT_00B1CF7C[found->Index];
        }
        return DAT_00B1CF78[found->Index];
    }
    MissingString_00734E60* node = new MissingString_00734E60;
    swprintf(node->Text, L"MISSING:'%hs'", key, file, line);
    FUN_004068E0("***NO_STRING*** '%s' -> file:%s line:%d\n", key, file, line);
    node->Next = DAT_00B1CF88;
    DAT_00B1CF88 = node;
    return node->Text;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB1CF6C
int DAT_00B1CF6C;
// GLOBAL: GAMEMD 0xB1CF74
StringTableEntry_00734E60* DAT_00B1CF74;
// GLOBAL: GAMEMD 0xB1CF78
wchar_t** DAT_00B1CF78;
// GLOBAL: GAMEMD 0xB1CF7C
int* DAT_00B1CF7C;
// GLOBAL: GAMEMD 0xB1CF88
MissingString_00734E60* DAT_00B1CF88;
// END defined globals
