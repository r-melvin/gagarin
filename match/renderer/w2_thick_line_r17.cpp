// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x63D810, 0x63D910 and 0x63D960. A line is
//   drawn through DAT_0088731C (DSurface, slot +0x30 DrawLine or +0x48 DrawDottedLine) after being
//   shifted sideways and clipped to the viewport rectangle at 0x886FA0; the two wrappers draw a
//   band of such lines for a given width.
//
// Address index: 0x63D810 0x63D960

#include <stdlib.h>
#include "dsurface_class.h"
#include "composite_surface.h"
#include "../_layout/tactical_viewport.h"

// WinMM import: GAMEMD 0x007E1530 (timeGetTime).
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

// GLOBAL: GAMEMD 0x836880 -- the 16-entry dot pattern.
extern unsigned char DAT_00836880[16];

// FUNCTION: GAMEMD 0x63D810
// Draw one line, offset sideways by `shift` (in Y for a mostly horizontal line, otherwise in X),
// clipped to the viewport; dotted lines animate with the clock.
void __fastcall FUN_0063D810(unsigned int shift, unsigned int color, Point2D a, Point2D b,
                             char dotted)
{
    bool xm = abs(b.X - a.X) > abs(b.Y - a.Y);
    unsigned int dx = (xm ? 0 : shift);
    unsigned int dy = (xm ? shift : 0);
    unsigned int phase;
    a.X += dx;
    a.Y += dy;
    b.X += dx;
    b.Y += dy;
    RectangleStruct clip = Viewport_00886FA0;
    if (ClipLine(&a, &b, &clip)) {
        if (dotted) {
            phase = (int)-(int)timeGetTime() >> 5 & 0xF;
            DAT_0088731C->DrawDottedLine(&a, &b, color, DAT_00836880, phase);
            return;
        }
        DAT_0088731C->DrawLine(&a, &b, color);
    }
}

// FUNCTION: GAMEMD 0x63D960
// PARTIAL: 79.1% -- the same instruction multiset as retail; retail loads and pushes the four
// coordinate words one at a time through EAX, the compiler hoists two into ECX/EDX first.
// Draw a dotted band two lines narrower than `width`.
void __fastcall FUN_0063D960(int width, unsigned int color, Point2D a, Point2D b)
{
    int inner = width - 2;
    int half;
    int i;
    if (inner <= 0) {
        i = 0;
        half = 0;
    } else {
        half = inner / 2;
        i = half - inner + 1;
    }
    for (; i <= half; i++) {
        FUN_0063D810(i, color, a, b, 1);
    }
}
