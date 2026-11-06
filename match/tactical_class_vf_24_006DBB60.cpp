// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes read from retail gamemd.exe v1.001 at 0x6DBB60.
//   PLACEMENT WORKAROUND (not a claim about the original file layout): the binary's file window places
//   this row in Tactical.CPP (window 0x6D1830-0x6DCD70). Retail reaches Pair_006D9F80::FUN_006D1EB0
//   (0x6D1EB0) and Tactical::AdjustForZ (0x6D20E0) by real CALLs, while /Ob2 inlines both when the
//   bodies are visible in the same file (they are defined earlier in Tactical.cpp). No ordinary source
//   shape keeps the calls in the same file, so the row is compiled here, where the callees are only
//   declared.
#include "_layout/tactical.h"
#include "_layout/tactical_viewport.h"
#include "ui_common.h"

extern double AdjustForZ_Factor; // GLOBAL: GAMEMD 0xB0CD48

// TUSPLIT: GAMEMD 0x6DBB60 same-file 1.1% separate 12.6%
// FUNCTION: GAMEMD 0x6DBB60
// PARTIAL: 12.6% -- multiset is retail minus one mov; retail keeps `this` in EDI and the two raw Y
// values in EBX, ours rotates ESI/EDI and spills the first X, so frame size (0x20 vs 0x28) and the
// first-point store order differ.
bool Tactical::vf_24(const CoordStruct* first, const CoordStruct* second,
                     unsigned int color, bool mode)
{
    Pair_006D9F80 firstTemporary;
    Pair_006D9F80 firstRaw = *firstTemporary.FUN_006D1EB0(first->X, first->Y);
    Point2D firstPoint;
    firstPoint.X = firstRaw.unknown_00 / 256;
    firstPoint.Y = firstRaw.unknown_04 / 256 - AdjustForZ(first->Z);
    firstPoint.X -= unknown_B0.unknown_00;
    firstPoint.Y -= unknown_B0.unknown_04;

    Pair_006D9F80 secondTemporary;
    Pair_006D9F80 secondRaw = *secondTemporary.FUN_006D1EB0(second->X, second->Y);
    Point2D secondPoint;
    secondPoint.X = secondRaw.unknown_00 / 256;
    secondPoint.Y = secondRaw.unknown_04 / 256 - AdjustForZ(second->Z);
    secondPoint.X -= unknown_B0.unknown_00;
    secondPoint.Y -= unknown_B0.unknown_04;

    int secondZ = second->Z;
    int secondBias = 0;
    if (secondZ >= 728) {
        secondBias = 1;
    }
    int firstZ = first->Z;
    int firstBias = 0;
    if (firstZ >= 728) {
        firstBias = 1;
    }
    Surface* surface = DAT_00887314;
    int secondDepth = 14 - (int)(secondZ * AdjustForZ_Factor + secondBias + 0.5);
    int firstDepth = 14 - (int)(firstZ * AdjustForZ_Factor + firstBias + 0.5);
    surface->unknown_34(&Viewport_00886FA0, &firstPoint, &secondPoint,
                        color, firstDepth, secondDepth, mode);
    return true; // Native ignores the Surface result and returns AL = 1.
}
