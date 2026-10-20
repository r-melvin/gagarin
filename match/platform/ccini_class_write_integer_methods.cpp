// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5275C0.
//
// reccmp annotations:
//   FUNCTION: GAMEMD 0x5275C0  INIClass::WriteInteger (__thiscall)
//   STRING:   GAMEMD 0x00825BAC  "%Xh"
//   STRING:   GAMEMD 0x00825BB0  "$%X"
//   STRING:   GAMEMD 0x00817F6C  "%d"

#include "ccini_class_write_integer_methods.h"

// FUNCTION: GAMEMD 0x5275C0  INIClass::WriteInteger (__thiscall, ret 0x10)
// Render an integer in one of three radix styles and hand it to WriteString.
// The selector is tested with a chain of `DEC EAX; JZ`, which is what VC6 emits
// for a `switch` over *small consecutive* labels — an if/else chain gives
// `CMP EAX,1` / `CMP EAX,2` instead and scores 76.3%. Note this is the opposite
// pull from SidebarClass::GetObjectTabIdx, where a switch over eleven *sparse*
// labels became a jump table and the if-chain was correct: the deciding factor
// is label density, not the source keyword.
bool INIClass::WriteInteger(const char* pSection, const char* pKey, int value, int format)
{
    char buffer[INI_INTEGER_BUFFER];

    switch (format) {
    case 1:
        sprintf(buffer, "%Xh", value);
        break;
    case 2:
        sprintf(buffer, "$%X", value);
        break;
    default:
        sprintf(buffer, "%d", value);
        break;
    }

    return WriteString(pSection, pKey, buffer);
}
