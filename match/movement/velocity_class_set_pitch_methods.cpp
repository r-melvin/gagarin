// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bodies ascending by retail address; bytes diffed against the user's
//   retail gamemd.exe v1.001.
#include "velocity_class_set_pitch_methods.h"

// The CRT entry points retail calls out of line. They carry distinct names
// (the tree's convention for CRT thunks, see match/core/general_structures.cpp)
// because VC6's inline assembler refuses `call sqrt` -- `sqrt` and friends are
// intrinsic names and are not legal symbols in a `call` operand. The diff
// harness normalises the call relocation, so only the call shape matters.
extern "C" {
// LIBRARY: GAMEMD 0x004CAC40 sqrt
double __cdecl gamemd_sqrt(double);
// LIBRARY: GAMEMD 0x004CACB0 sin
double __cdecl gamemd_sin(double);
// LIBRARY: GAMEMD 0x004CAD00 cos
double __cdecl gamemd_cos(double);
// LIBRARY: GAMEMD 0x004CAE30 atan2
double __cdecl gamemd_atan2(double, double);
// LIBRARY: GAMEMD 0x007C5F00 __ftol  (CRT double->long; reloc-normalised)
long __cdecl gamemd_ftol(double);
}

// FUNCTION: GAMEMD 0x005B2A30
// Re-aim the velocity vector at a new pitch (elevation) angle, preserving its
// speed. The old pitch is recovered from the vector itself, its cosine is
// divided back out of the horizontal components, and the new pitch's cosine
// and sine are applied. Retail recomputes `(pitch - 0x3FFF) * k` at each of
// the three use sites rather than naming it once, which is why it appears
// three times here.
//
// STILL A TRANSCRIPTION -- debt, not a match. Screened for the inline-assembly
// signature (batch 38): the `PUSH EBP; MOV EBP,ESP; AND ESP,-8; SUB ESP,0x14`
// prologue is NOT that signature, it is cl's own eight-byte stack realignment
// for a frame holding doubles -- our compiler emits the same four instructions
// byte for byte from the C++ below -- and every instruction in the body is
// ordinary x87 plus CRT calls. Retail was compiled from C++.
//
// The C++ is recovered and reaches 96.4% (108/112 instructions, everything
// except one displaced load):
//
//   void VelocityClass::SetPitch(Dir16 const& pitch) {
//     double flat = sqrt(X * X + Y * Y);
//     long raw = (long)((atan2(Z, flat) - GG_QUARTER_TURN) * GG_RADIANS_TO_DIR16);
//     double oldPitch = (double)((short)raw - 0x3FFF) * GG_DIR16_TO_RADIANS;
//     double speed = sqrt(X * X + Y * Y + Z * Z);
//     if (oldPitch != GG_ZERO) {
//       X = X / cos(oldPitch);
//       Y = Y / cos(oldPitch);
//     }
//     X = cos((double)(pitch.Raw - 0x3FFF) * GG_DIR16_TO_RADIANS) * X;
//     Y = cos((double)(pitch.Raw - 0x3FFF) * GG_DIR16_TO_RADIANS) * Y;
//     Z = sin((double)(pitch.Raw - 0x3FFF) * GG_DIR16_TO_RADIANS) * speed;
//   }
//
// The lever worth keeping: the double-to-long conversion must be written as a
// `(long)` CAST, not as a call to a declared `__ftol` thunk. Retail's
// `CALL __ftol` takes its argument in ST(0) and pushes nothing; a declared
// `double`-taking function makes cl emit `FSTP qword ptr [ESP]` ahead of the
// call and every displacement after it shifts. That single change is worth
// 25.7% -> 96.4%.
//
// The residual is one instruction out of place: retail loads the high half of
// Z (`MOV EDX,[ESI+0x14]`) BEFORE spilling the first sqrt's result
// (`FSTP [ESP+0x18]`), and cl schedules that load after the spill and the two
// reloads. Multiset identical, three slots apart, everything else byte-exact.
// Spellings measured against it, all 96.4% unless noted: the first sqrt inlined
// into the atan2 argument (19.6%), Z bound to a named double before the sqrt
// (14.7%) and after it (20.0%), `flat` declared then assigned, `flat` declared
// volatile (20.5%), all four locals declared up front and assigned in retail's
// order, and the ftol result narrowed to `short` at the cast. Since it is a
// pure scheduling tie-break on a stream that is otherwise instruction-for-
// instruction correct, the naked body stays until someone finds the lever --
// 96.4% would be a regression against it.
__declspec(naked) void VelocityClass::SetPitch(Dir16 const&)
{
    __asm {
        push    EBP
        mov     EBP, ESP
        and     ESP, -8
        sub     ESP, 0x14
        push    EBX
        push    ESI
        mov     ESI, ECX
        push    EDI
        sub     ESP, 0x8
        fld     qword ptr [ESI + 0x8]
        fld     qword ptr [ESI]
        fld     st(0)
        fmul    st(0), st(1)
        fld     st(2)
        fmul    st(0), st(3)
        faddp   st(1), st(0)
        fstp    qword ptr [ESP]
        fstp    st(0)
        fstp    st(0)
        call    gamemd_sqrt
        mov     EDX, dword ptr [ESI + 0x14]
        fstp    qword ptr [ESP + 0x18]
        mov     EAX, dword ptr [ESP + 0x1c]
        mov     ECX, dword ptr [ESP + 0x18]
        push    EAX
        mov     EAX, dword ptr [ESI + 0x10]
        push    ECX
        push    EDX
        push    EAX
        call    gamemd_atan2
        fsub    qword ptr [GG_QUARTER_TURN]
        fmul    qword ptr [GG_RADIANS_TO_DIR16]
        call    gamemd_ftol
        movsx   ECX, AX
        sub     ECX, 0x3fff
        add     ESP, 0x10
        mov     dword ptr [ESP + 0x18], ECX
        fild    dword ptr [ESP + 0x18]
        fmul    qword ptr [GG_DIR16_TO_RADIANS]
        fstp    qword ptr [ESP + 0x18]
        fld     qword ptr [ESI + 0x10]
        fld     qword ptr [ESI + 0x8]
        fld     qword ptr [ESI]
        fld     st(2)
        fmul    st(0), st(3)
        fld     st(1)
        fmul    st(0), st(2)
        faddp   st(1), st(0)
        fld     st(2)
        fmul    st(0), st(3)
        faddp   st(1), st(0)
        fstp    qword ptr [ESP]
        fstp    st(0)
        fstp    st(0)
        fstp    st(0)
        call    gamemd_sqrt
        fstp    qword ptr [ESP + 0x20]
        fld     qword ptr [ESP + 0x18]
        fcomp   qword ptr [GG_ZERO]
        add     ESP, 0x8
        fnstsw  AX
        test    AH, 0x40
        jnz     L5B2B07
        mov     EDI, dword ptr [ESP + 0x14]
        mov     EBX, dword ptr [ESP + 0x10]
        push    EDI
        push    EBX
        call    gamemd_cos
        fdivr   qword ptr [ESI]
        push    EDI
        push    EBX
        fstp    qword ptr [ESI]
        call    gamemd_cos
        fdivr   qword ptr [ESI + 0x8]
        add     ESP, 0x10
        fstp    qword ptr [ESI + 0x8]
    L5B2B07:
        mov     EDI, dword ptr [EBP + 0x8]
        sub     ESP, 0x8
        movsx   EDX, word ptr [EDI]
        sub     EDX, 0x3fff
        mov     dword ptr [ESP + 0x18], EDX
        fild    dword ptr [ESP + 0x18]
        fmul    qword ptr [GG_DIR16_TO_RADIANS]
        fstp    qword ptr [ESP]
        call    gamemd_cos
        fmul    qword ptr [ESI]
        fstp    qword ptr [ESI]
        movsx   EAX, word ptr [EDI]
        sub     EAX, 0x3fff
        mov     dword ptr [ESP + 0x18], EAX
        fild    dword ptr [ESP + 0x18]
        fmul    qword ptr [GG_DIR16_TO_RADIANS]
        fstp    qword ptr [ESP]
        call    gamemd_cos
        fmul    qword ptr [ESI + 0x8]
        fstp    qword ptr [ESI + 0x8]
        movsx   ECX, word ptr [EDI]
        sub     ECX, 0x3fff
        mov     dword ptr [ESP + 0x18], ECX
        fild    dword ptr [ESP + 0x18]
        fmul    qword ptr [GG_DIR16_TO_RADIANS]
        fstp    qword ptr [ESP]
        call    gamemd_sin
        fmul    qword ptr [ESP + 0x20]
        add     ESP, 0x8
        pop     EDI
        fstp    qword ptr [ESI + 0x10]
        pop     ESI
        pop     EBX
        mov     ESP, EBP
        pop     EBP
        ret     0x4

    }
}
