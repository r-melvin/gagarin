// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// A heap-owning narrow string whose only member is the `char*` at +0x00:
// every recovered body reads or writes [ECX+0x00] alone, allocates with
// operator new 0x7C8E17 and frees with operator delete 0x7C8B3D. strlen,
// strcpy, strcmp and memset are the VC6 inline expansions (REPNE SCASB,
// REP MOVSD/MOVSB, the SBB compare tail, REP STOSD/STOSB); strchr 0x7CAF30,
// strncpy 0x7C91D0 and memmove 0x7CA090 are calls.
// Method names are descriptive or placeholders. sizeof 4: the map stage
// container holds instances at +0x00/+0x04 of MapStage and at +0x28 of its
// list (see match/map/map_stage_list_methods.h).
#ifndef GG_MATCH_CORE_STRING_CLASS_H
#define GG_MATCH_CORE_STRING_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class StringClass
{
public:
    // FUNCTION: GAMEMD 0x7B4690
    StringClass(const StringClass& other);
    // FUNCTION: GAMEMD 0x7B4780
    bool operator==(const StringClass& other) const;
    // FUNCTION: GAMEMD 0x7B4860
    bool operator!=(const StringClass& other) const;
    // FUNCTION: GAMEMD 0x7B50F0
    bool FUN_007B50F0(char ch);
    // FUNCTION: GAMEMD 0x7B51B0
    void FUN_007B51B0();
    // FUNCTION: GAMEMD 0x7B53B0
    void Copy_Padded(char* dest, unsigned int size) const;
    // FUNCTION: GAMEMD 0x7B54B0
    int Length() const;
    // FUNCTION: GAMEMD 0x7B5AB0
    bool FUN_007B5AB0(char ch, unsigned int index);

    // Further members reached from other translation units, declared under
    // their call-site names; no body for them is recovered yet.
    // FUNCTION: GAMEMD 0x7B4620 (decl; reloc) — the empty construction.
    void Init();
    // FUNCTION: GAMEMD 0x7B46F0 (decl; reloc) — release the copy.
    void Destruct();
    // FUNCTION: GAMEMD 0x7B47F0 (decl; reloc) — indexed character.
    char At(int index);
    // FUNCTION: GAMEMD 0x7B5340 (decl; reloc) — drop whatever is held and go
    // back to empty.
    void Reset();
    // FUNCTION: GAMEMD 0x7B5B30 (decl; reloc) — lower-case in place.
    void MakeLower();

    char* Str;   // +0x00
};
GG_STATIC_ASSERT(sizeof(StringClass) == 4
              && offsetof(StringClass, Str) == 0x00);

#endif // GG_MATCH_CORE_STRING_CLASS_H
