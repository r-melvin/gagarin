// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x6D20E0 (Ghidra disasm).
//   Names cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x6D20E0   TacticalClass::AdjustForZ  (__fastcall)
//   GLOBAL:   GAMEMD 0xB0CD48   double  sin60 * pixelsPerLepton  (runtime-init)
//   GLOBAL:   GAMEMD 0x7E1738   double  0.5  (rounding bias)
//   LIBRARY:  GAMEMD 0x7C5F00   __ftol  (CRT double->long; excluded from match)
//
// Disassembly (0x6D20E0, len 0x3C):
//   SUB ESP,8 ; CMP ECX,0x2D8 ; MOV [ESP+4],ECX ; MOV [ESP],0
//   JL +8     ; MOV [ESP],1                      <- int(Height >= 728)
//   FILD [ESP+4]                                 <- (double)Height
//   FMUL [0xB0CD48]                              <- * const
//   FIADD [ESP]                                  <- + int(Height >= 728)
//   FADD [0x7E1738]                              <- + 0.5
//   CALL __ftol ; ADD ESP,8 ; RET                <- (int) cast
//
// 728 == 0x2D8. The (Height >= 728) flag is added as an INTEGER (FIADD), so it
// must stay an int operand in the expression, then 0.5 folds in as a double.

#include "tactical_class_methods.h"

// The scaling factor lives at the fixed global address 0xB0CD48 (runtime-init
// double). Referenced as an extern symbol so cl emits a direct memory operand
// `fmul [factor]` (reloc-normalised to the retail `fmul [0xB0CD48]`), rather
// than the register-indirect form a `*(double*)0xB0CD48` pointer literal forces.
extern double AdjustForZ_Factor;   // GLOBAL: GAMEMD 0xB0CD48

// FUNCTION: GAMEMD 0x6D20E0  TacticalClass::AdjustForZ (__fastcall)
int __fastcall TacticalClass::AdjustForZ(int Height)
{
    int bias = 0;
    if (Height >= 728) {
        bias = 1;
    }
    return (int)(Height * AdjustForZ_Factor + bias + 0.5);
}
