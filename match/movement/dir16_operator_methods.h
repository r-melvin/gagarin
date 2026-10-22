// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Target bytes: the user's retail gamemd.exe v1.001 through the local Ghidra
//   CLI at 0x5B2930 / 0x5B2950 / 0x5B2970 / 0x5B2990 / 0x5B29C0. The run
//   carried no name in any worklist and seats no vtable, so there is no runtime
//   type information to read; it was isolated by address clustering (five
//   consecutive leaf bodies, every one of them called only from the single
//   function at 0x5B20F0) and typed from the instructions alone.
//
// Dir16 -- a 16-bit binary-angle value with a four-byte footprint. Two facts
// from the disassembly pin the layout:
//   * every body reads and writes its value as a word at offset 0
//     (`MOV DX,[EAX]`, `ADD DX,[ECX]`, `MOV [ECX],SI`), so the value is a
//     `short` at +0x00;
//   * the three arithmetic bodies return through a hidden pointer and copy the
//     result with one 32-bit move (`MOV ECX,[ESP+8]; MOV [EAX],ECX`), so the
//     returned object is four bytes wide, not two. The second half is never
//     written -- the temporary is built in the (now dead) argument slot and
//     copied out whole, second half and all -- which is retail's own shape and
//     is reproduced by leaving the spare member uninitialised.
//
// The comparison and the step routine are the angle pair's "is the difference
// within this much" and "turn toward this by at most this much" primitives.
#ifndef GG_MATCH_MOVEMENT_DIR16_OPERATOR_METHODS_H
#define GG_MATCH_MOVEMENT_DIR16_OPERATOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Dir16
{
    short Raw;    // +0x00  the binary angle itself
    short Spare;  // +0x02  never written; exists because the return copy is a
                  //        single dword move, so the object is four bytes

    // Inline wrapped difference; IsWithin uses it in place of the out-of-line Sub.
    Dir16 operator-(Dir16 const& other) const
    {
        Dir16 result;
        result.Raw = (short)(Raw - other.Raw);
        return result;
    }

    // FUNCTION: GAMEMD 0x5B2930
    Dir16 Add(Dir16 const& other) const;
    // FUNCTION: GAMEMD 0x5B2950
    Dir16 Sub(Dir16 const& other) const;
    // FUNCTION: GAMEMD 0x5B2970
    Dir16 Div(int divisor) const;
    // FUNCTION: GAMEMD 0x5B2990
    bool IsWithin(Dir16 const& target, Dir16 const& tolerance) const;
    // FUNCTION: GAMEMD 0x5B29C0
    bool StepToward(Dir16 const& target, Dir16 const& rate);
};

GG_STATIC_ASSERT(offsetof(Dir16, Raw)   == 0x00);
GG_STATIC_ASSERT(offsetof(Dir16, Spare) == 0x02);
GG_STATIC_ASSERT(sizeof(Dir16)          == 4);

#endif  // GG_MATCH_MOVEMENT_DIR16_OPERATOR_METHODS_H
