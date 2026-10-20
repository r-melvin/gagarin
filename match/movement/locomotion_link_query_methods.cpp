// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check

#include "locomotion_link_query_methods.h"

// FUNCTION: GAMEMD 0x70FEB0
//
// Is this object draining another. The twin at 0x70FEC0, already matched in
// match/economy/building_class_drain.cpp, asks the same question of the other
// end of the link.
bool LocoObject_0070FEB0::IsDraining() const
{
    return this->DrainingWhom != 0;
}

// FUNCTION: GAMEMD 0x710460
//
// Release the waypoint buffer if one is held. Retail tail-jumps into the
// release helper with the buffer already in the receiver register.
void LocoObject_0070FEB0::FreeWaypointBuffer()
{
    if (this->WaypointBuffer != 0) {
        FUN_00472140(this->WaypointBuffer);
    }
}

// FUNCTION: GAMEMD 0x710600
//
// May this object fire while on the ground: it must be of the first kind, and
// its type must not carry the blocking flag.
int LocoObject_0070FEB0::CanFireFromGround()
{
    if ((this->*this->Vtbl->WhatAmI)() == 1) {
        if ((this->*this->Vtbl->GetType)()->Flag_D97 == 0) {
            return 1;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x710630
//
// May this object fire at all: the fifteenth kind always may, the first kind
// may only when its type carries the flag, and nothing else may.
//
// MATCHED 100% (23/23) once the two cold tails were spelled as explicit goto
// targets AND written in the order opposite to retail's block layout. cl 8804
// emits the two goto-target blocks in reverse source order, so retail's
// `false` block first / `true` block second comes from writing `yes:` first
// and `no:` second. The same skeleton in retail's own order reads 78.3%
// (blocks transposed, branch polarities inverted with them), and every
// single-exit spelling previously measured here sat at 3.6-4.2%: the nested
// form 42.3%, a short-circuit disjunction 4.2%, a mutated answer variable
// 3.6%, the positive form with a trailing zero return 3.7%, nested positive
// guards 3.7%. The lever is the goto skeleton plus the label transposition;
// neither alone gets there.
int LocoObject_0070FEB0::CanFireAny()
{
    if ((this->*this->Vtbl->WhatAmI)() == 15) goto yes;
    if ((this->*this->Vtbl->WhatAmI)() != 1) goto no;
    if ((this->*this->Vtbl->GetType)()->Flag_D97 == 0) goto no;
yes:
    return 1;
no:
    return 0;
}
