// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x771850 (0x31 bytes); RTTI .?AVAnim@Voices@WorldDominationTour@@ (vtable
//   0x7F7354, base MSAnim); layout in match/_layout/ms_anim.h.
#include "../_layout/ms_anim.h"

// FUNCTION: GAMEMD 0x7529E0 (decl; reloc) -- the scenario-side check slot 7 negates.
bool FUN_007529E0();

// FUNCTION: GAMEMD 0x7529A0 (decl; reloc)
void FUN_007529A0(bool flag);

// FUNCTION: GAMEMD 0x771850
// A voice animation starts disabled at the origin and remembers its owner.
WorldDominationTour::Voices::Anim::Anim(Obj_00771620* owner) : Owner(owner)
{
}

// FUNCTION: GAMEMD 0x771890
// The out-of-line destructor: seats the vtable and runs the base destructor 0x5CB6C0.
WorldDominationTour::Voices::Anim::~Anim()
{
}

// FUNCTION: GAMEMD 0x7718A0
// Slot 1: switching off also winds the owner's side down and restarts its stopwatch.
void WorldDominationTour::Voices::Anim::SetEnabled(bool on)
{
    Enabled = on;
    if (!on) {
        Obj_00771620* owner = Owner;
        if (owner->Count > 0) {
            FUN_007529A0(true);
            owner->Sub3C0.Slot03();
        }
        owner->Stopwatch = MSTimer();
    }
}

// FUNCTION: GAMEMD 0x771900
// Slot 2: the same timer pause as MSAnim::PauseTimer. Bank what is left of the interval, then stop the clock.
void WorldDominationTour::Voices::Anim::PauseTimer()
{
    if (Timer.StartTime != -1) {
        Timer.Remaining = Timer.TimeLeft();
        Timer.StartTime = -1;
    }
}

// FUNCTION: GAMEMD 0x771950
// Slot 3: restart the clock, but only from a paused state.
void WorldDominationTour::Voices::Anim::ResumeTimer()
{
    if (Timer.StartTime == -1) {
        Timer.StartTime = Timer.Clock.GetTime();
    }
}

// FUNCTION: GAMEMD 0x771970
// Slot 4: run the owner's helper; the animation never reports a change.
bool WorldDominationTour::Voices::Anim::Update(int context, MSRect* out)
{
    Owner->FUN_00771620();
    return false;
}

// FUNCTION: GAMEMD 0x771980
// Slot 5: run the owner's helper.
void WorldDominationTour::Voices::Anim::Draw(int context, MSRect* area)
{
    Owner->FUN_00771620();
}

// FUNCTION: GAMEMD 0x771990
// Slot 6: hands back a rectangle it never fills in.
MSRect WorldDominationTour::Voices::Anim::GetRect()
{
    MSRect rect;
    return rect;
}

// FUNCTION: GAMEMD 0x7719C0
// Slot 7: finished when the scenario check fails.
bool WorldDominationTour::Voices::Anim::vf_7()
{
    return !FUN_007529E0();
}

// FUNCTION: GAMEMD 0x7719D0
// Slot 8: run the owner's helper.
void WorldDominationTour::Voices::Anim::Attach(void* target)
{
    Owner->FUN_00771620();
}

// SYNTHETIC: GAMEMD 0x771A30 -- Anim::`scalar deleting destructor' (seats its vtable, calls the base
// destructor 0x5CB6C0 out of line, frees).
