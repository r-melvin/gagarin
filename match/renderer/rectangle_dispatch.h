// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// Retail4D1890 consumes one XYWH rectangle in ECX and returns with RET.
// Caller6D3470 sets ECX to the rectangle itself, without a Tactical receiver.
#ifndef GG_MATCH_RENDERER_RECTANGLE_DISPATCH_H
#define GG_MATCH_RENDERER_RECTANGLE_DISPATCH_H
#include "../_layout/geometry2d.h"
// Declaration: GAMEMD 0x4D1890 -- free /Gr function, ECX rectangle, no stack arguments.
void FUN_004D1890(const RectangleStruct* rectangle);
// Declaration: GAMEMD 0x420F40 -- /Gr ECX point, EDX clip, plain RET.
void FUN_00420F40(const Point2D* point, const RectangleStruct* clip);
#endif
