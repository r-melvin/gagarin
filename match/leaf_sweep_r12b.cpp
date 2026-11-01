// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Small functions read off the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. Their owning classes are only partly named, so placeholder
//   names are kept for the receivers.
//   Address index: 0x722AB0, 0x751600, 0x774900.

#include <windows.h>
#include <stddef.h>

// ---------------------------------------------------------------------------
// 0x722AB0: clears one cell's byte in every registered object's per-cell table.
struct CellTable_00722AB0
{
    char unknown_00[0xF8];
    char* Flags;    // +0xF8
};
// GLOBAL: GAMEMD 0xB0F4EC
extern CellTable_00722AB0** DAT_00B0F4EC;
// GLOBAL: GAMEMD 0xB0F4F8
extern int DAT_00B0F4F8;
// FUNCTION: GAMEMD 0x42B1C0 (decl; reloc)
int __fastcall FUN_0042B1C0(short* cell);

// FUNCTION: GAMEMD 0x722AB0
void __fastcall FUN_00722AB0(short* cell)
{
    int index = FUN_0042B1C0(cell);
    for (int i = 0; i < DAT_00B0F4F8; i++) {
        DAT_00B0F4EC[i]->Flags[index] = 0;
    }
}

// ---------------------------------------------------------------------------
// 0x751600: the name of an entry, or a fixed text when the entry is empty.
struct Named_00751600
{
    const char* FUN_00405170();
};
struct Entry_00751600
{
    Named_00751600* unknown_0;
};
// GLOBAL: GAMEMD 0x846574
extern "C" const char DAT_00846574[];

// FUNCTION: GAMEMD 0x751600
const char* __fastcall FUN_00751600(Entry_00751600* entry)
{
    if (entry->unknown_0) {
        return entry->unknown_0->FUN_00405170();
    }
    return DAT_00846574;
}

// ---------------------------------------------------------------------------
// 0x774900: raises or drops a serial control line, logging a failure.
struct Line_00774900
{
    char unknown_00[0x5C];
    HANDLE Port;    // +0x5C
    void FUN_00774900(bool raise);
};
extern "C" void __cdecl FUN_004068E0(const char* format, ...);

// FUNCTION: GAMEMD 0x774900
void Line_00774900::FUN_00774900(bool raise)
{
    if (raise) {
        if (EscapeCommFunction(Port, 5)) {
            return;
        }
    } else {
        if (EscapeCommFunction(Port, 6)) {
            return;
        }
    }
    FUN_004068E0("Set_Serial_DTR - EscapeCommFunction failed with error code %d, %s\n", GetLastError(), 0);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB0F4F8
int DAT_00B0F4F8;
// GLOBAL: GAMEMD 0xB0F4EC
CellTable_00722AB0** DAT_00B0F4EC;
// END defined globals
