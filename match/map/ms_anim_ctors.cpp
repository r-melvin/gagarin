// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x5CB6D0 (MSShapeAnim), 0x5CBD20 (MSFadeAnim) and 0x5CC250 (MSOverlayAnim); the
//   RTTI chain and vtables 0x7EE910 / 0x7EE938 / 0x7EE960; layout in match/_layout/ms_anim.h. Each constructor
//   expands its bases inline and stores its own vtable pointer after the member initialisers.
#include "../FUNCTION.H"

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

// FUNCTION: GAMEMD 0x5CB750
// Hand the decoded buffer back only when this object owns it (the out-of-line body; the scalar deleting
// destructors expand it inline).
MSShapeAnim::~MSShapeAnim()
{
    if (Buffer != 0 && OwnsBuffer) {
        delete Buffer;
        Buffer = 0;
        OwnsBuffer = false;
    }
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

// FUNCTION: GAMEMD 0x5CC690
// Clear the fade state.
void MSFadeAnim::FUN_005CC690()
{
    unknown_40 = 0;
}

// FUNCTION: GAMEMD 0x5CC6A0
// Clear the fade state and jump to the given frame.
void MSFadeAnim::FUN_005CC6A0(int frame)
{
    unknown_40 = 0;
    Frame = frame;
}

// FUNCTION: GAMEMD 0x5CC740
// Slot 7 of the overlay: done when disabled or once the fade has run to its fourth stage.
bool MSOverlayAnim::vf_7()
{
    return !Enabled || unknown_40 >= 4;
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

// Compiler-generated scalar deleting destructors of the four classes above (each expands its destructor and
// the base destructor above inline, as retail's do).
// SYNTHETIC: GAMEMD 0x5CEB60 -- MSAnim::`scalar deleting destructor'
// SYNTHETIC: GAMEMD 0x5CEB80 -- MSShapeAnim::`scalar deleting destructor'
// SYNTHETIC: GAMEMD 0x5CEBD0 -- MSFadeAnim::`scalar deleting destructor'
// SYNTHETIC: GAMEMD 0x5CEC20 -- MSOverlayAnim::`scalar deleting destructor'
