// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Two helper calls on a surface-like receiver and a rectangle, then one shape
// draw (0x4AED70: surface in ECX, convert in EDX, fourteen stack words) of a
// global shape file at a position copied from a global point, with flag 0x400
// and z adjust 0x3E8. Two copies at different addresses, each with its own
// globals; each address is verified separately. Receiver and rectangle are
// placeholders.

struct Point_0072E9F0 {
    int unknown_00;
    int unknown_04;
};
struct Surface_0072E9F0;
struct Rect_0072E9F0;
struct Shape_0072E9F0;
struct Convert_0072E9F0;



extern Point_0072E9F0* DAT_00B0FC1C;
extern Shape_0072E9F0* DAT_00B0FB34;
extern Convert_0072E9F0* DAT_00B0FBA8;



extern Shape_0072E9F0* DAT_00B0FB1C;
extern Convert_0072E9F0* DAT_00B0FBB4;


// FUNCTION: GAMEMD 0x4AED70 (decl; reloc) -- shape draw, __fastcall: surface in ECX, convert in EDX, fourteen stack words (RET 0x38).
void FUN_004AED70(Surface_0072E9F0* surface, Convert_0072E9F0* convert, Shape_0072E9F0* shape,
                  int frame, Point_0072E9F0* position, Rect_0072E9F0* clip, int flags,
                  int a6, int a7, int a8, int zAdjust, int a10, int a11, int a12,
                  Point_0072E9F0 offset);

// FUNCTION: GAMEMD 0x72E2D0 (decl; reloc) -- __fastcall, receiver in ECX, rectangle in EDX.
void FUN_0072E2D0(Surface_0072E9F0* self, Rect_0072E9F0* rect);

// FUNCTION: GAMEMD 0x72E450 (decl; reloc) -- __fastcall, receiver in ECX, rectangle in EDX, one stack word.
void FUN_0072E450(Surface_0072E9F0* self, Rect_0072E9F0* rect, int flag);

// FUNCTION: GAMEMD 0x0072E9F0
void FUN_0072E9F0(Surface_0072E9F0* self, Rect_0072E9F0* rect)
{
    FUN_0072E2D0(self, rect);
    FUN_0072E450(self, rect, 0);
    Point_0072E9F0 position = {0, 0};
    position = *DAT_00B0FC1C;
    Point_0072E9F0 offset = {0, 0};
    FUN_004AED70(self, DAT_00B0FBA8, DAT_00B0FB34, 0, &position, rect, 0x400, 0, 0, 0, 0x3E8, 0, 0, 0, offset);
}

// FUNCTION: GAMEMD 0x0072EAD0
void FUN_0072EAD0(Surface_0072E9F0* self, Rect_0072E9F0* rect)
{
    FUN_0072E2D0(self, rect);
    FUN_0072E450(self, rect, 0);
    Point_0072E9F0 position = {0, 0};
    position = *DAT_00B0FC1C;
    Point_0072E9F0 offset = {0, 0};
    FUN_004AED70(self, DAT_00B0FBB4, DAT_00B0FB1C, 0, &position, rect, 0x400, 0, 0, 0, 0x3E8, 0, 0, 0, offset);
}
