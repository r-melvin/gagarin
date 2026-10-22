// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + behaviour derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly @ 0x529560 / 0x5297E0 /
//   0x679F40), cross-checked against YRpp / INIClass (every address + convention reconfirmed below from the disasm).
//
// INIClass uses the shared binary-confirmed layout. CCINIClass::Exists
// preserves the zero-offset base receiver established by retail RTTI;
// its added fields and complete derived size remain outside this view.
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/ini_class.h"


class FileClass;

// VTABLE: GAMEMD 0x7E1AF4
//   sizeof 0x58: `PUSH 0x58; CALL operator new` before the inline
//   construction at 0x5D5BD9. ReadCCFile 0x4741F0 clears and sets +0x40 and
//   writes the SHA result to +0x41.
class CCINIClass : public INIClass
{
public:
    CCINIClass() : DigestValid(false) {}
    // FUNCTION: GAMEMD 0x4741F0 (decl; reloc) -- RET 0xC.
    int ReadCCFile(FileClass* file, bool withDigest, bool flag);
    // FUNCTION: GAMEMD 0x679F40  CCINIClass::Exists         (__thiscall)
    bool Exists(const char* pSection, const char* pKey);

    bool          DigestValid;     // +0x40
    unsigned char Digest[0x14];    // +0x41
};
GG_STATIC_ASSERT(offsetof(CCINIClass, DigestValid) == 0x40);
GG_STATIC_ASSERT(sizeof(CCINIClass) == 0x58);

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_METHODS_H
