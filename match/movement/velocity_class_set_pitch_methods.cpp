// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bodies ascending by retail address; bytes diffed against the user's
//   retail gamemd.exe v1.001.
#include "velocity_class_set_pitch_methods.h"

// The CRT entry points retail calls out of line. They carry distinct names
// (the tree's convention for CRT thunks) so that /O2 does not expand `sqrt`
// and friends as intrinsics. The diff harness normalises the call relocation,
// so only the call shape matters.
extern "C" {
// LIBRARY: GAMEMD 0x004CAC40 sqrt
double __cdecl gamemd_sqrt(double);
// LIBRARY: GAMEMD 0x004CACB0 sin
double __cdecl gamemd_sin(double);
// LIBRARY: GAMEMD 0x004CAD00 cos
double __cdecl gamemd_cos(double);
// LIBRARY: GAMEMD 0x004CAE30 atan2
double __cdecl gamemd_atan2(double, double);
}

// FUNCTION: GAMEMD 0x005B2A30
// Re-aim the velocity vector at a new pitch (elevation) angle, preserving its
// speed. The old pitch is recovered from the vector itself, its cosine is
// divided back out of the horizontal components, and the new pitch's cosine
// and sine are applied. Retail recomputes `(pitch - 0x3FFF) * k` at each of
// the three use sites rather than naming it once, which is why it appears
// three times here.
//
// PARTIAL, 96.4% (108/112, multiset identical). The double-to-long conversion
// is a `(long)` cast, not a call to a declared thunk: retail's `CALL __ftol`
// takes its argument in ST(0). The residual is one load out of place: retail
// loads the high half of Z (`MOV EDX,[ESI+0x14]`) before spilling the first
// sqrt result (`FSTP [ESP+0x18]`); cl issues it after the spill and the two
// reloads. Other natural spellings scored lower: the first sqrt inlined into
// the atan2 argument with the old pitch held as a Dir16 and compound
// assignments (19.6%), and Z bound to a named local first (14.7%).
void VelocityClass::SetPitch(Dir16 const& pitch)
{
    double flat = gamemd_sqrt(X * X + Y * Y);
    long raw = (long)((gamemd_atan2(Z, flat) - GG_QUARTER_TURN) * GG_RADIANS_TO_DIR16);
    double oldPitch = (double)((short)raw - 0x3FFF) * GG_DIR16_TO_RADIANS;
    double speed = gamemd_sqrt(X * X + Y * Y + Z * Z);
    if (oldPitch != GG_ZERO) {
        X = X / gamemd_cos(oldPitch);
        Y = Y / gamemd_cos(oldPitch);
    }
    X = gamemd_cos((double)(pitch.Raw - 0x3FFF) * GG_DIR16_TO_RADIANS) * X;
    Y = gamemd_cos((double)(pitch.Raw - 0x3FFF) * GG_DIR16_TO_RADIANS) * Y;
    Z = gamemd_sin((double)(pitch.Raw - 0x3FFF) * GG_DIR16_TO_RADIANS) * speed;
}
