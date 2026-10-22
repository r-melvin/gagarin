// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4389B0  BombClass::Disarm        (__thiscall)
//   FUNCTION: GAMEMD 0x4389F0  BombClass::IsDeathBomb   (__thiscall)
//   FUNCTION: GAMEMD 0x438A70  BombClass::TimeToExplode (__thiscall)
//   FUNCTION: GAMEMD 0x405FD0  AudioController::End      (referenced; matched elsewhere)

#include "bomb_class.h"

// FUNCTION: GAMEMD 0x4389B0  (__thiscall)
// Defuse the bomb: detach it from its target, clear the owner/house/target
// links, end the ticking audio, and mark it harmless.
void BombClass::Disarm()
{
    if (Target)
    {
        Target->AttachedField = 0;
        Target->AttachedFlag = 0;
    }
    Harmless = 1;
    Owner = 0;
    Target = 0;
    OwnerHouse = 0;
    Audio.End();
    TickSound = 0;
}

// FUNCTION: GAMEMD 0x4389F0  (__thiscall)
int BombClass::IsDeathBomb() const
{
    return DeathBomb;
}

// FUNCTION: GAMEMD 0x438A70  (__thiscall)
// A time bomb is ready when it is not a death bomb, the detonation frame has
// passed, and it has not been made harmless.
bool BombClass::TimeToExplode() const
{
    // The retail bool is materialised in AL via `mov al,1` / `xor al,al`.
    // The bare `return <&& chain>;` form makes our SP6 cl emit the 32-bit
    // `mov eax,1` / `xor eax,eax` tail (which shifts the jump displacements);
    // binding the result to a `bool` local first reproduces the AL tail exactly.
    bool ready = DeathBomb == 0
              && CurrentFrame > DetonationFrame
              && Harmless == 0;
    return ready;
}
