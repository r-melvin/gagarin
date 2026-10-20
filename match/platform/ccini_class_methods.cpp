// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp CCINIClass.h (consult-only, no LICENSE; each
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
// FUNCTION: GAMEMD 0x529560
// 0x529560  INIClass::WriteBool
//   Forwards to WriteString(pSection, pKey, bValue ? "yes" : "no"); the
//   incoming `this` stays in ECX (no reload), so cl emits a bare CALL.
// ---------------------------------------------------------------------------
bool INIClass::WriteBool(const char* pSection, const char* pKey, bool bValue)
{
    if (bValue) {
        return WriteString(pSection, pKey, "yes");
    }
    return WriteString(pSection, pKey, "no");
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x5297E0
// 0x5297E0  INIClass::Write2Integers
//   sprintf(buffer, "%d,%d", pValues[0], pValues[1]); then forwards the buffer
//   to WriteString. `this` is spilled to ESI across the cdecl sprintf call.
//   Frame: SUB ESP,0x38 == one 56-byte scratch buffer.
// ---------------------------------------------------------------------------
bool INIClass::Write2Integers(const char* pSection, const char* pKey, int* pValues)
{
    char buffer[56];
    sprintf(buffer, "%d,%d", pValues[0], pValues[1]);
    return WriteString(pSection, pKey, buffer);
}

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

// FUNCTION: GAMEMD 0x526B00  INIClass::Reset (__thiscall)
// Drop the parsed section bookkeeping. Retail zeroes both dwords from a single
// XOR'd register and never touches the vptr.
void INIClass::Reset()
{
    unknown_04 = 0;
    unknown_08 = 0;
}
