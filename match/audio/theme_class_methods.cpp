// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp (each
//   offset/global reconfirmed against the user's binary below).
//
// Translation unit: ThemeClass music accessors. Four bounds-checked indexers
// into the Themes vector.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x720940   ThemeClass::GetName    (__thiscall)
//   FUNCTION: GAMEMD 0x7209B0   ThemeClass::GetUIName  (__thiscall)
//   FUNCTION: GAMEMD 0x720E50   ThemeClass::GetLength  (__thiscall)
//   FUNCTION: GAMEMD 0x721270   ThemeClass::GetID      (__thiscall)
//   STRING:   GAMEMD 0x844770   "No theme"  (GetName out-of-range default)
//   STRING:   GAMEMD 0x817694   "none"      (GetID out-of-range default)
//   LIBRARY:  GAMEMD 0x7C5F00   __ftol      (CRT float->long; GetLength cast)

#include "theme_class_methods.h"

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x720940  (__thiscall)
//
// Return the selected theme's ID string (FixedString at ThemeControl+0). The
// unsigned bound check folds index<0 and index>=Count into one JNC; the element
// pointer (== &ID) is returned unmodified.
//   MOV EAX,[ESP+4]; MOV EDX,[ECX+0x24]; CMP EAX,EDX; JNC default
//   MOV ECX,[ECX+0x18]; MOV EAX,[ECX+EAX*4]; RET 4
// ---------------------------------------------------------------------------
const char* ThemeClass::GetName(unsigned int index) const
{
    if (index < (unsigned int)this->Themes.Count)
        return this->Themes.Items[index]->ID;
    return "No theme";
}

// FUNCTION: GAMEMD 0x7209B0  (__thiscall)
// Return the selected theme's localized name (FixedWString at ThemeControl+0x200).
// Same unsigned bound; element pointer + 0x200; out-of-range returns NULL.
//   ... MOV EAX,[ECX+EAX*4]; ADD EAX,0x200; RET 4   /   default: XOR EAX,EAX
const wchar_t* ThemeClass::GetUIName(unsigned int index) const
{
    if (index < (unsigned int)this->Themes.Count)
        return this->Themes.Items[index]->UIName;
    return 0;
}

// FUNCTION: GAMEMD 0x720E50  (__thiscall)
// Return the selected theme's Length (float @ThemeControl+0x284) truncated to
// int via the CRT __ftol helper. Out-of-range returns 0.
//   ... MOV EDX,[ECX+EAX*4]; FLD float[EDX+0x284]; CALL __ftol; RET 4
int ThemeClass::GetLength(unsigned int index) const
{
    if (index < (unsigned int)this->Themes.Count)
        return (int)this->Themes.Items[index]->Length;
    return 0;
}

// FUNCTION: GAMEMD 0x721270  (__thiscall)
// Like GetName but with a *signed* bound check (TEST/JL then CMP/JGE) and the
// "none" default — i.e. negative indices are rejected explicitly.
//   MOV EAX,[ESP+4]; TEST EAX,EAX; JL default; CMP EAX,[ECX+0x24]; JGE default
//   MOV ECX,[ECX+0x18]; MOV EAX,[ECX+EAX*4]; RET 4   /   default: MOV EAX,"none"
const char* ThemeClass::GetID(int index) const
{
    if (index >= 0 && index < this->Themes.Count)
        return this->Themes.Items[index]->ID;
    return "none";
}
