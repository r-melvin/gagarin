// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Slot 2 of WorldDominationTour::Voices::Anim (vtable 0x7F7354): the same
// timer pause as MSAnim::PauseTimer (0x5CEAD0). When the start time is set,
// bank what is left of the interval (the inline reader tests the start time a
// second time) and clear the start time. The owner is a placeholder
// `Obj_<ADDR>` that declares only the timer fields the body touches.

struct Clock_00771900
{
    int unknown_00;
    int FUN_006C8C40();
};

// The animation's interval timer: start time, clock, banked remainder.
struct Timer_00771900
{
    int StartTime;          // +0x00
    Clock_00771900 Clock;   // +0x04
    int Remaining;          // +0x08

    // The time still on the clock (ordinary inline reader).
    int TimeLeft()
    {
        int left = Remaining;
        if (StartTime != -1) {
            int elapsed = Clock.FUN_006C8C40() - StartTime;
            if (elapsed < left)
                left -= elapsed;
            else
                left = 0;
        }
        return left;
    }
};

struct Obj_00771900
{
    char unknown_00[0x10];
    Timer_00771900 Timer;   // +0x10
    void FUN_00771900();
};

// FUNCTION: GAMEMD 0x771900
// Slot 2 of WorldDominationTour::Voices::Anim.
void Obj_00771900::FUN_00771900()
{
    if (Timer.StartTime != -1) {
        Timer.Remaining = Timer.TimeLeft();
        Timer.StartTime = -1;
    }
}
