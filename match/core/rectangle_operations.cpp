// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// Binary-derived XYWH clipping and enclosing bounds. No original TU claim.
#include "../_layout/rectangle_operations.h"
// FUNCTION: GAMEMD 0x421B60
RectangleStruct* __fastcall FUN_00421B60(RectangleStruct* output,
    const RectangleStruct* first, const RectangleStruct* second, int* dx, int* dy)
{
    RectangleStruct result = *second;
    if (first->Width <= 0 || first->Height <= 0 || second->Width <= 0 || second->Height <= 0)
        goto empty;
    if (result.X < first->X) {
        result.Width += result.X - first->X;
        result.X = first->X;
    }
    if (result.Width < 1) goto empty;
    if (result.Y < first->Y) {
        result.Height += result.Y - first->Y;
        result.Y = first->Y;
    }
    if (result.Height < 1) goto empty;
    if (result.X + result.Width > first->X + first->Width)
        result.Width = first->X - result.X + first->Width;
    if (result.Width < 1) goto empty;
    if (result.Y + result.Height > first->Y + first->Height)
        result.Height = first->Y + first->Height - result.Y;
    if (result.Height < 1) goto empty;
    if (dx) *dx += second->X - result.X;
    if (dy) *dy += second->Y - result.Y;
    *output = result;
    return output;
empty:
    output->X = 0;
    output->Y = 0;
    output->Width = 0;
    output->Height = 0;
    return output;
}

// FUNCTION: GAMEMD 0x487F40
RectangleStruct* __fastcall FUN_00487F40(RectangleStruct* output,
    const RectangleStruct* first, const RectangleStruct* second)
{
    if (first->Width <= 0 || first->Height <= 0) {
        *output = *second;
        return output;
    }
    if (second->Width <= 0 || second->Height <= 0) {
        *output = *first;
        return output;
    }
    RectangleStruct result = *first;
    if (result.X > second->X) {
        result.Width += result.X - second->X;
        result.X = second->X;
    }
    if (result.Y > second->Y) {
        result.Height += result.Y - second->Y;
        result.Y = second->Y;
    }
    if (result.X + result.Width < second->X + second->Width)
        result.Width = second->X - result.X + 1 + second->Width;
    if (result.Y + result.Height < second->Y + second->Height)
        result.Height = second->Y + second->Height - result.Y + 1;
    *output = result;
    return output;
}
