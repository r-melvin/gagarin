// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp (each
//   address/convention reconfirmed against the user's binary below).
//
// Translation unit: three CCINIClass/INIClass INI writers/queries, all pure
// __thiscall forwarders that touch NO member offset of `this` (confirmed: every
// referenced register is an incoming stack arg or the preserved `this` in ECX).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x529560   INIClass::WriteBool        (__thiscall)
//   FUNCTION: GAMEMD 0x5297E0   INIClass::Write2Integers   (__thiscall)
//   FUNCTION: GAMEMD 0x679F40   CCINIClass::Exists         (__thiscall)
//   FUNCTION: GAMEMD 0x528660   INIClass::WriteString      (forwarded callee)
//   FUNCTION: GAMEMD 0x526810   INIClass::GetSection       (forwarded callee)
//   FUNCTION: GAMEMD 0x526B10   INIClass::GetEntry         (forwarded callee)
//   DATA:     GAMEMD 0x825BF8   "yes"   (WriteBool true literal)
//   DATA:     GAMEMD 0x825BF4   "no"    (WriteBool false literal)
//   DATA:     GAMEMD 0x81C000   "%d,%d" (Write2Integers format)
//   LIBRARY:  GAMEMD 0x7C8EF4   sprintf (CRT; cdecl; excluded from match target)

#include "ccini_class_methods.h"

// CRT sprintf: cdecl variadic, 4-arg call cleaned by the caller (ADD ESP,0x10).
extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);


// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x679F40
// 0x679F40  CCINIClass::Exists
//   If pKey is null only the section is probed (GetSection != null); otherwise
//   the entry is probed (GetEntry != null). The nonzero-test is materialised as
//   VC6's NEG/SBB/NEG 0-or-1 boolean.
// ---------------------------------------------------------------------------
bool CCINIClass::Exists(const char* pSection, const char* pKey)
{
    if (pKey == 0) {
        return GetSection(pSection) != 0;
    }
    return GetEntry(pSection, pKey) != 0;
}

