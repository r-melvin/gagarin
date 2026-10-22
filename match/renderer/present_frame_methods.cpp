// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x40A7C0.

#include "present_frame_methods.h"

// FUNCTION: GAMEMD 0x40A7C0
//
// Describe a region and hand it to the active surface: reset, submit, present.
//
// The span is the height divided into eight-row bands times the step, and the
// total is that span — read back through its 16-bit slot, so it is truncated
// before the multiply — times the row count. The division is signed, hence the
// CDQ/AND 7/ADD/SAR sequence rather than a plain shift.
//
// Width is written after Total in the source even though retail's *store* for
// it lands before the multiply. VC6 slots that independent word store into the
// gap while the dependent multiply is still pending, so the emitted order is
// not the source order. Writing Width before Total (the order the stores appear
// in) hoists it to the top of the function instead — 4.3% against 100%.
//
// The global is re-read before each of the last two calls. That is not a
// pessimisation: a call could store to it, so the compiler must reload, and
// only the first use can reuse the register the null test left behind.
void FUN_0040A7C0(int rows, int height, int step)
{
    if (DAT_0087E8A0 != 0) {
        Region_0040A7C0 region;

        region.Kind  = 1;
        region.Step  = (unsigned short)step;
        region.Rows  = rows;
        region.Span  = (unsigned short)(height / 8 * step);
        region.Total = region.Span * rows;
        region.Width = (unsigned short)height;
        region.Tail  = 0;

        DAT_0087E8A0->Vtbl->At_48(DAT_0087E8A0);
        DAT_0087E8A0->Vtbl->At_38(DAT_0087E8A0, &region);
        DAT_0087E8A0->Vtbl->At_30(DAT_0087E8A0, 0, 0, 1);
    }
}

// FUNCTION: GAMEMD 0x40A850
//
// The same reset/submit/present sequence as 0x40A7C0, but describing the current
// mode rather than a caller-supplied region. Nothing happens without both a
// surface and a mode.
//
// PARTIAL (74.0%, 37/50) — identical multiset. Every instruction retail has is
// here; the descriptor sits two bytes higher in the frame. Both frames are
// `SUB ESP,0x14` and both descriptors are 0x12 bytes, but retail places it at
// ESP+4 and VC6 at ESP+6, so every displacement into it differs by two. Forcing
// the struct to 2-byte packing moves it further away (30.0%), so the placement is
// not coming from its alignment.
//
// The descriptor is zero-initialised as an aggregate and then filled, which is
// why every field is stored twice — once by the `{ 0 }` and once with its value.
// VC6 interleaves the two sequences, so the pairs do not appear adjacent. That
// part is exact, including the merging of adjacent 16-bit members into single
// dword zero stores.
//
// The span and width multiplies run on 16-bit values held in 32-bit registers
// with stale upper halves; only the low words are stored, so the garbage never
// escapes. Writing the operands as `unsigned short` reproduces that rather than
// zero-extending them first.
void FUN_0040A850()
{
    Mode_0040A850* mode = FUN_00407010();

    if (DAT_0087E8A0 != 0 && mode != 0) {
        DAT_0087E8A0->Vtbl->At_48(DAT_0087E8A0);

        Region_0040A7C0 region = { 0 };

        region.Step  = mode->Step;
        region.Rows  = mode->Rows;
        region.Kind  = 1;
        region.Span  = (unsigned short)(mode->Bands * mode->Step);
        region.Total = region.Span * region.Rows;
        region.Width = (unsigned short)(mode->Bands * 8);
        region.Tail  = 0;

        DAT_0087E8A0->Vtbl->At_38(DAT_0087E8A0, &region);
        DAT_0087E8A0->Vtbl->At_30(DAT_0087E8A0, 0, 0, 1);
    }
}
