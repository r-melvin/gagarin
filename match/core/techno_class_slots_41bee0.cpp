// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// TechnoClass bodies for primary-table (0x7F4960) slots 49, 50, 88, 161, 167,
// 181-183, 204, 225, 226, 255-258, 266, 269, 282, 284 and 286, emitted together
// at 0x41BEE0..0x41C042 right after the ObjectClass slot bodies at 0x41BDD0.
// Slot numbers come from the RTTI-located table; names are placeholders
// (techno_class.h).
#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"
#include "frame_counter.h"

// FUNCTION: GAMEMD 0x41BEE0
bool TechnoClass::vf_161()
{
    return false;
}

// FUNCTION: GAMEMD 0x41BEF0
bool TechnoClass::vf_167()
{
    return true;
}

// FUNCTION: GAMEMD 0x41BF00
int TechnoClass::vf_181()
{
    return 0;
}

// FUNCTION: GAMEMD 0x41BF10
int TechnoClass::vf_182()
{
    return 0;
}

// FUNCTION: GAMEMD 0x41BF20
int TechnoClass::vf_183()
{
    return 0;
}

// FUNCTION: GAMEMD 0x41BF30
bool TechnoClass::vf_204()
{
    return false;
}

// Time left on a count-down timer, counted against the frame clock once the
// timer has been started.
static inline int TimerLeft(const CDTimerClass& t)
{
    int start = t.StartTime;
    int left = t.TimeLeft;
    if (start != -1) {
        int passed = CurrentFrame - start;
        left = (passed < left) ? left - passed : 0;
    }
    return left;
}

// FUNCTION: GAMEMD 0x41BF40
// Is the iron-curtain timer still running?
// PARTIAL 15%: retail keeps the time left in EAX and builds the bool in CL;
// VC6 swaps the two. Variants tried: straight-line body, inline helper with
// early returns, inline helper with a ternary, an extra bool wrapper.
bool TechnoClass::vf_88()
{
    return TimerLeft(IronCurtainTimer) > 0;
}

// FUNCTION: GAMEMD 0x41BF80
bool TechnoClass::vf_225()
{
    return false;
}

// FUNCTION: GAMEMD 0x41BF90
void TechnoClass::vf_226(int a1)
{
}

// FUNCTION: GAMEMD 0x41BFA0
// One flag of the techno type's 0xC8C bool block (byte 0xCA1).
bool TechnoClass::vf_255()
{
    return vf_33()->bools_C8C[0xCA1 - 0xC8C];
}

// FUNCTION: GAMEMD 0x41BFB0
bool TechnoClass::vf_256()
{
    return false;
}

// FUNCTION: GAMEMD 0x41BFC0
int TechnoClass::vf_257()
{
    return 0;
}

// FUNCTION: GAMEMD 0x41BFD0
int TechnoClass::vf_258()
{
    return 0;
}

// FUNCTION: GAMEMD 0x41BFE0
void TechnoClass::vf_266()
{
}

// FUNCTION: GAMEMD 0x41BFF0
bool TechnoClass::vf_269(int a1)
{
    return false;
}

// FUNCTION: GAMEMD 0x41C000
void TechnoClass::vf_282()
{
}

// FUNCTION: GAMEMD 0x41C010
bool TechnoClass::vf_49()
{
    return Disguised;
}

// FUNCTION: GAMEMD 0x41C020
bool TechnoClass::vf_50(int a1)
{
    return Disguised;
}

// FUNCTION: GAMEMD 0x41C030
void TechnoClass::vf_284()
{
    Disguised = false;
}

// FUNCTION: GAMEMD 0x41C040
bool TechnoClass::vf_286()
{
    return false;
}
