// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bodies ascending by retail address; bytes diffed against the user's
//   retail gamemd.exe v1.001.
#include "dir16_operator_methods.h"

// `abs` as the CRT intrinsic, not a call: retail's absolute values are the
// inline `CDQ; XOR; SUB` idiom, which is what /O2 + #pragma intrinsic emits.
extern "C" int __cdecl abs(int);
#pragma intrinsic(abs)

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
//
// 100% compiled C++, 18/18 instructions exact. It was a `__declspec(naked)`
// transcription at 16.7% through twenty-seven hand spellings across two
// sessions; the body below was found by decomp-permuter in 3648 iterations
// (about three minutes) and then minimised by hand from its output. See
// docs/permuter_workflow.md.
//
// Two levers, and both are needed — either one alone scores 205 or 520:
//   * the difference is read back through a *pointer alias* (`p`), not from
//     `diff` directly. That is what makes cl take the tolerance's absolute
//     value first, into callee-saved ESI (retail's PUSH/POP pair), leaving the
//     difference as a word in CX until the second `MOVSX`;
//   * the comparison is assigned to a dead `int` on the way out. Returning the
//     comparison directly costs retail's bare `SETGE AL` and pays
//     `XOR EDX,EDX; SETGE DL; MOV AL,DL` instead.
bool Dir16::IsWithin(Dir16 const& target, Dir16 const& tolerance) const
{
    int result;
    short diff = (short)(this->Raw - target.Raw);
    short const* p = &diff;
    int tol = abs((int)tolerance.Raw);

    return result = tol >= abs((int)(*p));
}

// FUNCTION: GAMEMD 0x5B29C0
// Turn this angle toward `target` by at most `rate`, and report whether the
// target was reached. Within one step of the target the angle snaps onto it
// and the answer is true; otherwise it moves one full step in whichever
// direction the wrapped difference points and the answer is false.
//
// STILL A TRANSCRIPTION -- debt, not a match. Same screening result as
// IsWithin: no EBP frame (EBP is used as an ordinary data register holding the
// rate, `MOV BP,word ptr [EDX]`), so this is frame-pointer-omitted compiler
// output, not hand-written assembly.
//
// The equivalent C++ is
//
//   short r = rate.Raw, tgt = target.Raw, cur = Raw;
//   volatile int absRate = abs((int)r);        // retail spills it to the
//   int back = cur - tgt;                      // dead argument slot
//   if (absRate >= abs((int)(short)back)) { Raw = tgt; return true; }
//   int fwd = tgt - cur;
//   if ((short)fwd < 0) { Raw = (short)(cur - r); return false; }
//   Raw = (short)(r + cur);
//   return false;
//
// which reaches 18.4% and reproduces the middle of the body -- the spill of the
// rate's absolute value into the dead argument slot, the reload, the compare
// and the whole snap-to-target arm -- byte for byte. It carries the same
// absolute-value scheduling difference as IsWithin above, plus one consequence
// of it: retail needs four callee-saved registers because the rate stays live
// in EBP across both later arms, and cl manages with three. Spellings measured
// this pass, on top of the earlier sweep that capped at 12.2%: the plain
// abs()-first form (12.2%), the same with the rate's abs volatile (2.0%), a
// single trailing return through a named bool (2.0%), the two differences taken
// as ints and narrowed at the test (18.4%, the best), the same without the
// volatile (12.2%), both differences kept in short arithmetic (2.0%), and the
// last two arms exchanged (2.0%). Solve IsWithin's register-pressure residual
// first; the two share one cause.
__declspec(naked) bool Dir16::StepToward(Dir16 const&, Dir16 const&)
{
    __asm {
        mov     edx, dword ptr [esp+8]
        mov     eax, dword ptr [esp+4]
        push    ebx
        push    ebp
        mov     bp, word ptr [edx]
        push    esi
        push    edi
        mov     di, word ptr [eax]
        mov     si, word ptr [ecx]
        movsx   eax, bp
        cdq
        xor     eax, edx
        mov     ebx, esi
        sub     eax, edx
        sub     ebx, edi
        mov     dword ptr [esp+0x14], eax
        movsx   eax, bx
        cdq
        xor     eax, edx
        sub     eax, edx
        mov     edx, dword ptr [esp+0x14]
        cmp     edx, eax
        jl      L_step
        mov     word ptr [ecx], di
        pop     edi
        pop     esi
        pop     ebp
        mov     al, 1
        pop     ebx
        ret     8
    L_step:
        sub     edi, esi
        test    di, di
        jge     L_forward
        sub     esi, ebp
        pop     edi
        mov     word ptr [ecx], si
        pop     esi
        pop     ebp
        xor     al, al
        pop     ebx
        ret     8
    L_forward:
        add     ebp, esi
        pop     edi
        mov     word ptr [ecx], bp
        pop     esi
        pop     ebp
        xor     al, al
        pop     ebx
        ret     8
    }
}
