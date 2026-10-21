// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, literals and the frame read off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x5275C0. 0x007C8EF4 is the CRT `sprintf`
//   (cdecl, three pushes then `ADD ESP,0xC`) and 0x00528660 is
//   INIClass::WriteString, already bound in ccini_class_methods.h.
//
// Format selector, read straight off the `DEC EAX; JZ` chain:
//   1 -> "%Xh" (0x00825BAC)   2 -> "$%X" (0x00825BB0)   else "%d" (0x00817F6C)
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_WRITE_INTEGER_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_WRITE_INTEGER_METHODS_H

// The scratch buffer is 0x200 bytes — the function opens with `SUB ESP,0x200`
// and hands `[ESP+4]` to sprintf.
#define INI_INTEGER_BUFFER 0x200

extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);

#include "../_layout/ini_class.h"


#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_WRITE_INTEGER_METHODS_H
