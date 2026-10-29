// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x5CB6D0 (MSShapeAnim), 0x5CBD20 (MSFadeAnim) and 0x5CC250 (MSOverlayAnim); the
//   RTTI chain and vtables 0x7EE910 / 0x7EE938 / 0x7EE960; layout in match/_layout/ms_anim.h. Each constructor
//   expands its bases inline and stores its own vtable pointer after the member initialisers.
#include "../_layout/ms_anim.h"

// FUNCTION: GAMEMD 0x5CB6C0
// The base destructor: nothing but the vtable pointer seat (defined here so the derived destructors in this
// unit expand it inline, as retail's do).
MSAnim::~MSAnim()
{
}

// FUNCTION: GAMEMD 0x5CB6D0
// Load the shape, start at frame zero and remember the last frame.
MSShapeAnim::MSShapeAnim(const char* name, int x, int y, int field20, int field24, bool field34,
                         unsigned int flags)
    : MSAnim(x, y), Field20(field20), Field24(field24), Frame(0), Field34(field34), Flags(flags), OwnsBuffer(false)
{
    Buffer = MSLoadShape(name, &OwnsBuffer);
    Field2C = 0;
    LastFrame = Buffer->Frames - 1;
}

// FUNCTION: GAMEMD 0x5CBD20
// A shape animation with two extra numbers.
MSFadeAnim::MSFadeAnim(const char* name, int x, int y, int field20, int field24, int field38, int field44)
    : MSShapeAnim(name, x, y, field20, field24, false, field38), unknown_40(0), unknown_44(field44)
{
}

// FUNCTION: GAMEMD 0x5CC250
// A fade animation with a type byte, a start frame and a "quick" switch.
MSOverlayAnim::MSOverlayAnim(const char* name, int x, int y, int field20, int field24, int field44,
                             unsigned char field48, int frame, bool quick)
    : MSFadeAnim(name, x, y, field20, field24, 0, field44)
{
    unknown_48 = field48;
    Frame = frame;
    if (!quick)
        unknown_40 = 4;
}

// FUNCTION: GAMEMD 0x5CEAC0
// Slot 1, shared by all nine classes: enable or disable the animation.
void MSAnim::SetEnabled(bool on)
{
    Enabled = on;
}

// FUNCTION: GAMEMD 0x5CEAD0
// Slot 2: freeze the animation's clock, banking whatever is left of the current interval.
void MSAnim::PauseTimer()
{
    if (Timer.StartTime != -1) {
        Timer.Remaining = Timer.TimeLeft();
        Timer.StartTime = -1;
    }
}

// FUNCTION: GAMEMD 0x5CEB20
// Slot 3: restart the clock, but only from a genuinely paused state.
void MSAnim::ResumeTimer()
{
    if (Timer.StartTime == -1) {
        Timer.StartTime = Timer.Clock.GetTime();
    }
}

// FUNCTION: GAMEMD 0x5CEB40
// Slot 7 of the base: an animation with no completion notion never finishes.
bool MSAnim::vf_7()
{
    return false;
}

// FUNCTION: GAMEMD 0x5CEB50
// Slot 8 of the base: an empty hook.
void MSAnim::Attach(void* target)
{
}

// Two out-of-line copies of the shape animation's destructor (seat the vtable, release the decoded buffer
// when owned, seat the base vtable), sitting in neighbouring translation units far from the family's own run.
// FUNCTION: GAMEMD 0x5CB750
void MSShapeAnim_DestroyAtA(MSShapeAnim* self)
{
    self->MSShapeAnim::~MSShapeAnim();
}

// FUNCTION: GAMEMD 0x5CC2F0
void MSShapeAnim_DestroyAtB(MSShapeAnim* self)
{
    self->MSShapeAnim::~MSShapeAnim();
}

// Compiler-generated scalar deleting destructors of the four classes above (each expands its destructor and
// the base destructor above inline, as retail's do).
// SYNTHETIC: GAMEMD 0x5CEB60 -- MSAnim::`scalar deleting destructor'
// SYNTHETIC: GAMEMD 0x5CEB80 -- MSShapeAnim::`scalar deleting destructor'
// SYNTHETIC: GAMEMD 0x5CEBD0 -- MSFadeAnim::`scalar deleting destructor'
// SYNTHETIC: GAMEMD 0x5CEC20 -- MSOverlayAnim::`scalar deleting destructor'
