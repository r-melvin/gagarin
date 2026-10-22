// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + behaviour derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly @ 0x529560 / 0x5297E0 /
//   0x679F40), cross-checked against YRpp / INIClass (consult-only,
//   no LICENSE; every address + convention reconfirmed below from the disasm).
//
// INIClass uses the shared binary-confirmed layout. CCINIClass::Exists
// preserves the zero-offset base receiver established by retail RTTI;
// its added fields and complete derived size remain outside this view.
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/ini_class.h"


class CCINIClass : public INIClass
{
public:
    // FUNCTION: GAMEMD 0x679F40  CCINIClass::Exists         (__thiscall)
    bool Exists(const char* pSection, const char* pKey);
};

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_METHODS_H
