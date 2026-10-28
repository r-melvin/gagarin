// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
//
// The cursor animation timer global at 0xABF2A0 (see MouseCursorTimer in mouse_mouse_class.h):
// start tick at +0, the clock member at +4 (its empty destructor is the only exit work) and
// a zeroed delay at +8. Retail's initialiser is 0x5BD9F0 and its exit stub is 0x5BDA20.
#include "../../core/game_timing_methods.h"

struct MouseTimerValue_00ABF2A0 {
    GameTimerClass Timer;
    int Delay;
    MouseTimerValue_00ABF2A0() : Delay(0) {}
    ~MouseTimerValue_00ABF2A0() {}
};

// A static data member of the owning class: its exit stub tests bit 0 of the guard
// byte 0xABF250 first.
struct MouseTimerHolder_00ABF2A0 {
    // GLOBAL: GAMEMD 0xABF2A0
    static MouseTimerValue_00ABF2A0 MouseTimer;
};

// SYNTHETIC: GAMEMD 0x005BD9F0 -- initialiser of MouseTimer (fused ctor + atexit)
// SYNTHETIC: GAMEMD 0x005BDA20 -- exit-time stub of MouseTimer, guard byte 0x00ABF250 bit 0
MouseTimerValue_00ABF2A0 MouseTimerHolder_00ABF2A0::MouseTimer;
