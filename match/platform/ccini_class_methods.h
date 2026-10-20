// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + behaviour derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly @ 0x529560 / 0x5297E0 /
//   0x679F40), cross-checked against YRpp CCINIClass.h / INIClass (consult-only,
//   no LICENSE; every address + convention reconfirmed below from the disasm).
//
// CCINIClass : INIClass — the engine INI parser. The three methods modelled
// here (WriteBool, Write2Integers, Exists) are pure forwarders: NONE of them
// dereferences a `this` member offset. Each is __thiscall (cl emits it for a
// member automatically), keeps the incoming `this` in ECX, and tail-forwards to
// another INIClass helper. Because no member is touched, no class layout/offset
// is asserted — only the calling convention and the forwarded helpers matter.
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// Opaque INIClass / CCINIClass models. We never read a member, so the body is
// intentionally empty; the helper callees are declared (no body) so cl emits a
// __thiscall `call rel32` that the differ reloc-normalises against retail.
// ---------------------------------------------------------------------------
class INIClass
{
public:
    // Retail helpers this TU forwards to (declared only; relocation-normalised):
    //   GetSection  @0x526810  __thiscall(const char*)            -> INISection*
    //   GetEntry    @0x526B10  __thiscall(const char*, const char*) -> INIEntry*
    //   WriteString @0x528660  __thiscall(const char*, const char*, const char*)
    void* GetSection(const char* pSection);
    void* GetEntry(const char* pSection, const char* pKey);
    bool  WriteString(const char* pSection, const char* pKey, const char* pString);

    // FUNCTION: GAMEMD 0x529560  INIClass::WriteBool        (__thiscall)
    bool WriteBool(const char* pSection, const char* pKey, bool bValue);
    // FUNCTION: GAMEMD 0x5297E0  INIClass::Write2Integers   (__thiscall)
    bool Write2Integers(const char* pSection, const char* pKey, int* pValues);
    // FUNCTION: GAMEMD 0x526B00  INIClass::Reset            (__thiscall)
    void Reset();

    // Reset @0x526B00 is the only function here that touches state: it zeroes
    // two dwords at +0x04 and +0x08 (the section-list bookkeeping) and leaves
    // the vptr at +0x00 alone. The members keep placeholder names because the
    // bytes confirm their offsets but not their meaning.
    void* _vtable;      // +0x00
    void* unknown_04;   // +0x04  (XOR EAX,EAX; MOV [ECX+0x4],EAX)
    void* unknown_08;   // +0x08  (MOV [ECX+0x8],EAX)
};

GG_STATIC_ASSERT(offsetof(INIClass, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(INIClass, unknown_08) == 0x08);

class CCINIClass : public INIClass
{
public:
    // FUNCTION: GAMEMD 0x679F40  CCINIClass::Exists         (__thiscall)
    bool Exists(const char* pSection, const char* pKey);
};

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_METHODS_H
