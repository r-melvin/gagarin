// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x40A260.

#include <string.h>
#include "aux_block_attach_methods.h"

#pragma intrinsic(memset)

// FUNCTION: GAMEMD 0x40A260
//
// Attach a freshly zeroed auxiliary block to the host, link it both ways, set
// the two size constants, and prime it from the block 0x44 into +0xAC.
//
// MATCHED (100.0%, 29/29). The lone residual — retail reloads the
// back-pointer (`MOV ECX,[EDX]` at 0x40A2B8) *after* the four zero stores
// where cl 8804 hoisted that load above them — was the by-value/by-reference
// parameter lever, not a scheduling difference. Priming is its own routine in
// the retail source, and taking its block argument as `Aux_0040A260* const&`
// rather than by value keeps cl from materialising the pointer's dereference
// early: the load lands between the last zero store and the call, exactly as
// retail has it. 75.9% to 100%.
//
// Variants measured this pass, all 75.9% (the old score) unless noted: the
// prime call left flat with the back-pointer read twice; the same read once
// into a named local; the prime call lifted into an inline helper taking the
// block **by value**; the four zero stores folded into that helper alongside
// the call; and the helper taking the block as `Aux_0040A260* const&`
// (100.0%, kept). Only the reference form moves the load.
//
// The final call goes through the block's own back-pointer rather than through
// `self` — retail reads `[EDX]` at 0x40A2B8 to get the host back — so the
// round trip is in the source, not an artifact.
static inline int Prime_0040A260(Aux_0040A260* const& aux)
{
    return FUN_00402800(aux->Host, (const int*)(aux->Host->field_AC + 0x44));
}

int FUN_0040A260(Host_0040A260* self)
{
    Aux_0040A260* aux = (Aux_0040A260*)FUN_007C8E17(sizeof(Aux_0040A260));
    memset(aux, 0, sizeof(Aux_0040A260));

    self->Aux  = aux;
    aux->Host  = self;

    self->field_1A8 = 0x108;
    self->field_1B0 = 0x420;
    self->field_1AC = 0;
    self->field_1B4 = 0;

    aux->field_B0 = 0;
    aux->field_7C = 0;
    aux->field_90 = 0;
    aux->field_A8 = 0;

    Prime_0040A260(aux);
    return 0;
}
