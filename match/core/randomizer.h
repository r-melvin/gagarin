// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly), cross-checked against YRpp
//   Randomizer.h `class Randomizer` (consult-only, no LICENSE; reconfirmed
//   here from the 0x65C780 / 0x65C7E0 disassembly).
//
// Randomizer — Westwood XOR lagged-table PRNG (250-entry table, two indices).
// Used for RMG / out-of-match randomness. Random() advances the table and
// returns one value; RandomRanged() does rejection sampling into [min,max].
#ifndef GG_MATCH_CORE_RANDOMIZER_H
#define GG_MATCH_CORE_RANDOMIZER_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// Randomizer
//
// Confirmed from 0x65C780 (Random):
//   CMP byte [ECX+0x00] ........ unknown_00 (disabled flag, 1 byte)
//   MOV [ECX+0x04] ............. Next1  (table read/write cursor 1)
//   MOV [ECX+0x08] ............. Next2  (table read/write cursor 2)
//   [ECX + idx*4 + 0x0C] ....... Table[idx]  (DWORD[250]; INC wraps at 0xFA=250)
// ---------------------------------------------------------------------------
class Randomizer
{
public:
    int Random();                     // GAMEMD 0x65C780 __thiscall
    int RandomRanged(int min, int max); // GAMEMD 0x65C7E0 __thiscall

    // The same generator step as Random(), as the in-class inline that retail
    // expands into RandomRanged. It has to be a genuine inlined call, not a
    // hand-expanded body: the inline's return value is materialised in EAX
    // (`MOV EAX,ESI` at the join, `XOR EAX,EAX` on the disabled arm), which is
    // what evicts `lo` to EBX and gives the masked pick its `AND EAX,EBP;
    // CMP EAX,EDI` shape and the final `ADD EAX,EBX`. The out-of-line
    // Random() above keeps its own body so the 0x65C780 symbol still exists.
    int RandomStep()
    {
        if (this->unknown_00)
            return 0;
        this->Table[this->Next1] ^= this->Table[this->Next2];
        int next1 = this->Next1;
        int next2 = this->Next2;
        int result = this->Table[next1];
        ++next1;
        ++next2;
        this->Next1 = next1;
        this->Next2 = next2;
        if (next1 >= 250)
            this->Next1 = 0;
        if (next2 >= 250)
            this->Next2 = 0;
        return result;
    }

    bool          unknown_00;  // +0x00
    int           Next1;       // +0x04
    int           Next2;       // +0x08
    unsigned int  Table[250];  // +0x0C  (250 == 0xFA)
};

GG_STATIC_ASSERT(offsetof(Randomizer, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(Randomizer, Next1)      == 0x04);
GG_STATIC_ASSERT(offsetof(Randomizer, Next2)      == 0x08);
GG_STATIC_ASSERT(offsetof(Randomizer, Table)      == 0x0C);

#endif  // GG_MATCH_CORE_RANDOMIZER_H
