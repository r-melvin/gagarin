// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bodies ascending by retail address; bytes diffed against the user's
//   retail gamemd.exe v1.001.
#include "dir16_operator_methods.h"

// `abs` as the CRT intrinsic, not a call: retail's absolute values are the
// inline `CDQ; XOR; SUB` idiom, which is what /O2 + #pragma intrinsic emits.
extern "C" int __cdecl abs(int);

// FUNCTION: GAMEMD 0x5B2930
// Dir16 + Dir16. The sum wraps in sixteen bits, which is the whole point of a
// binary angle; the spare half of the returned temporary is left as it was.
Dir16 Dir16::Add(Dir16 const& other) const
{
    Dir16 result;

    result.Raw = other.Raw + this->Raw;
    return result;
}

// FUNCTION: GAMEMD 0x5B2950
// Dir16 - Dir16, with the same wrap and the same uninitialised spare half.
Dir16 Dir16::Sub(Dir16 const& other) const
{
    Dir16 result;

    result.Raw = this->Raw - other.Raw;
    return result;
}

// FUNCTION: GAMEMD 0x5B2970
// Dir16 / int. The angle is sign-extended to 32 bits and divided by a full
// integer, so the quotient is a signed division (`MOVSX` + `CDQ` + `IDIV`),
// then truncated back to sixteen bits.
Dir16 Dir16::Div(int divisor) const
{
    Dir16 result;

    result.Raw = (short)(this->Raw / divisor);
    return result;
}

// FUNCTION: GAMEMD 0x5B2990
// True when this angle is within `tolerance` of `target`: the wrapped signed
// difference, in absolute value, is no larger than the absolute tolerance.
// An explicit true/false return gives retail's bare `SETGE AL`; returning the
// comparison itself zero-extends through another register first.
bool Dir16::IsWithin(Dir16 const& target, Dir16 const& tolerance) const
{
    Dir16 diff = *this - target;
    if (abs(tolerance.Raw) >= abs(diff.Raw)) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x5B29C0
// Turn this angle toward `target` by at most `rate`, and report whether the
// target was reached. Within one step of the target the angle snaps onto it
// and the answer is true; otherwise it moves one full step in whichever
// direction the wrapped difference points and the answer is false.
//
// MATCHED (100%, 49/49) as plain C++. The lever is taking both differences
// through the inline Dir16 operator- (as IsWithin does) and giving the
// backward-step arm its own `return false`.
bool Dir16::StepToward(Dir16 const& target, Dir16 const& rate)
{
    Dir16 diff = *this - target;
    if (abs(rate.Raw) >= abs(diff.Raw)) {
        Raw = target.Raw;
        return true;
    }
    Dir16 ahead = target - *this;
    if (ahead.Raw < 0) {
        Raw -= rate.Raw;
        return false;
    }
    Raw += rate.Raw;
    return false;
}
