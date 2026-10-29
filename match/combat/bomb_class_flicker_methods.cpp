// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x438A00 via the local
//   Ghidra disassembly. Offsets and globals confirmed numerically (see header).
//
// reccmp annotations:
//   FUNCTION: GAMEMD 0x438A00   BombClass::GetCurrentFlickerFrame (__thiscall)
//   GLOBAL:   GAMEMD 0xA8ED84   CurrentFrame
//   GLOBAL:   GAMEMD 0x8871E0   RulesClass::Instance pointer

#include "bomb_class_flicker_methods.h"

// FUNCTION: GAMEMD 0x438A00  BombClass::GetCurrentFlickerFrame (__thiscall)
//
// Two independent clocks combine into one frame index. How far through its life
// the bomb is picks the even frames, and a free-running flicker off the global
// frame counter adds one on the "lit" half of each cycle. The result is clamped
// so the last frame repeats rather than running off the end of the animation.
//
// The division by six is a literal `/ 6` in the source, not a shift: retail
// reaches it through the signed-constant-division idiom `MOV EAX,0x2AAAAAAB;
// IMUL ECX` at 0x438A2B, taking the high half of the product and correcting the
// sign with `SHR EAX,0x1F; ADD ECX,EAX`. That sequence is what VC6 emits for a
// signed divide by six and is how the constant was read back — note 0x2AAAAAAB
// is the /6 magic, half the 0x55555556 that VC6 emits for /3, which is what a
// first reading of it as a divide by three produced.
int BombClass::GetCurrentFlickerFrame() const
{
    if (DeathBomb == 1) {
        return 12;
    }

    const RulesClass* rules = Rules;
    int planted = PlantingFrame;
    int flickerHalf = rules->IvanIconFlickerRate;
    int period = rules->IvanTimedDelay;
    int now = CurrentFrame;

    int frame = ((now - planted) / (period / 6)) * 2;

    if (now % (flickerHalf * 2) >= flickerHalf) {
        frame++;
    }

    if (frame >= 12) {
        frame = 11;
    }

    return frame;
}
