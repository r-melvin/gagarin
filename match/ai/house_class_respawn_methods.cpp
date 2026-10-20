// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x50D440.

#include "house_class_respawn_methods.h"

// FUNCTION: GAMEMD 0x50D440
//
// Re-create the house's recorded starting forces, last entry first. Each
// entry's type is asked what it is; aircraft, building, unit and infantry
// types create an object for this house, which is kept only when its flag
// byte says it is a techno. The object is then unlimboed at the centre of the
// entry's cell, and torn down again through +0xF8 when that fails.
//
// The two case groups carry the same body twice: retail keeps two copies of
// the create-and-test and cross-jumps only the flag fold. The techno pointer
// is left null for any other kind of type and the unlimbo still dereferences
// it, as retail does. Score with scripts/vc6/raw_match.py: diff_retail.py
// also counts the embedded jump/index tables (19 junk `add`s) as instructions.
//
// PARTIAL (66.0%, 68/103 by diff_retail.py; 64/83 real instructions, mnemonic
// multiset identical). The whole residual is one register swap: retail keeps
// `this` in EBX and the entry pointer in EBP, cl 8804 the other way round, so
// the prologue/epilogue pushes and every use of the two (`MOV EBX,ECX`,
// `[EBX+0x17C]`, `[EBX+0x170]`, `PUSH EBX` x2, `MOV EBP,[ECX+EAX*4]`,
// `[EBP]`, `ADD EBP,4`, `PUSH EBP`) differ by name only; the loop, the
// spilled counter, the jump table, the switch bodies, the map lookup, the
// hidden-pointer GetCoords copy and the unlimbo tail are otherwise exact.
// Tried: a `house = this` alias outside and inside the loop; all locals
// declared at function scope; the entry as a reference, as `const`, or
// re-indexed (`Items[i]->Type` / `&Items[i]->Cell`, which reloads after the
// calls: 43.7%); a named cell pointer before the switch (43.7%); an inlined
// `operator[]` on the vector; per-case block-scoped `obj`; a `default:` arm
// (breaks the table); the create-and-test in a static inline helper and in an
// inline member helper (entry as an inlined parameter); the flag fold and the
// unlimbo tail in inline helpers; swapped case order; a `while` loop. None
// moves the assignment; recorded as an allocation-ranking residual.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply. Retail sinks
// PUSH EBP/ESI/EDI below the empty-vector early-out and our output sinks the
// same three in the same place; both sides jump the early exit straight onto
// the last POP of the staircase epilogue, so the two returns are already as
// split as retail's. Four further spellings measured this pass, all 66.0% and
// byte-identical to the control: the loop body lifted into a free
// `RespawnOne(house, i)` inline helper; the whole loop lifted into a free
// `RespawnAll(house)` inline helper; `this` bound to a named `house` local;
// and the unlimbo tail lifted into its own inline helper. The EBX/EBP
// exchange is unmoved by every function boundary available in this body.
void House_0050D440::RespawnStartingForces()
{
    int i;

    for (i = this->StartingUnits.Count - 1; i >= 0; i--) {
        StartingTechno_0050D440* entry = this->StartingUnits.Items[i];
        Abs_0050D440* type = entry->Type;
        Abs_0050D440* techno = 0;
        Abs_0050D440* obj;

        switch ((type->*type->Vtbl->WhatAmI)()) {
        case 3:
        case 7:
        case 0x28:
            obj = (type->*type->Vtbl->CreateObject)(this);
            if (obj == 0) {
                techno = 0;
            } else {
                techno = (obj->Flags & 1) ? obj : 0;
            }
            break;
        case 0x10:
            obj = (type->*type->Vtbl->CreateObject)(this);
            if (obj == 0) {
                techno = 0;
            } else {
                techno = (obj->Flags & 1) ? obj : 0;
            }
            break;
        }

        Abs_0050D440* cell = MapInstance.GetCellAt(entry->Cell);
        Coord_0050D440 coord = (cell->*cell->Vtbl->GetCoords)();
        if (!(techno->*techno->Vtbl->At_490)(&coord, 0)) {
            (techno->*techno->Vtbl->At_F8)();
        }
    }
}
