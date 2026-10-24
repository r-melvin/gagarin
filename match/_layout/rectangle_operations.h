// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// Native rectangle helpers read XYWH at0/4/8/C. ECX=result, EDX=first;
// second and optional offset pointers are stacked. Original type name unproved.
#ifndef GG_MATCH_LAYOUT_RECTANGLE_OPERATIONS_H
#define GG_MATCH_LAYOUT_RECTANGLE_OPERATIONS_H
#include "geometry2d.h"
// Declaration: GAMEMD 0x421B60 -- RET0xC.
RectangleStruct* __fastcall FUN_00421B60(RectangleStruct* output,
    const RectangleStruct* first, const RectangleStruct* second, int* dx, int* dy);
// Declaration: GAMEMD 0x487F40 -- RET4.
RectangleStruct* __fastcall FUN_00487F40(RectangleStruct* output,
    const RectangleStruct* first, const RectangleStruct* second);
#endif
