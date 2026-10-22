// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Full 0x226-byte function at 0x453840 confirmed from retail gamemd.exe
//   v1.001 disassembly and focused REA evidence.

#include "building_coord_00453840.h"

// Partial: after correcting the base call to pass Coord by value,
// 7/194 instructions (3.6%) match. Frame layout and temporary lifetimes differ.
// FUNCTION: GAMEMD 0x453840
Coord_00453840* BuildingClass_00453840::FUN_00453840(
    Coord_00453840* out, int mode, int, int, int)
{
    Point_00453840 projected;
    Coord_00453840 tmp;

    if (At_520->At_157B && (this->*Vtbl->At_408)() > 0) {
        const Point_00453840* offset = &At_520->At_1588 + At_69C;
        Point_00453840* client = DAT_00887324->CoordsToClient(
            &projected, &offset->X);
        int cx = client->X;
        int cy = client->Y;
        Coord_00453840* base = (this->*Vtbl->At_AC)(&tmp);
        return out->Set(base->X + cx, base->Y + cy, base->Z);
    }

    if (At_520->At_E44 != 0xFFFF || At_520->At_E48 != 0xFFFF) {
        Point_00453840* client = DAT_00887324->CoordsToClient(
            &projected, &At_520->At_E44);
        int cx = client->X;
        int cy = client->Y;
        if (At_520->At_1764) {
            Coord_00453840 zero = { 0, 0, 0 };
            Coord_00453840* base = FUN_006F3AD0(&tmp, mode, zero);
            return out->Set(base->X + cx, base->Y + cy, base->Z);
        }
        Coord_00453840* base = (this->*Vtbl->At_AC)(&tmp);
        return out->Set(base->X + cx, base->Y + cy, base->Z);
    }

    if (At_520->At_16C6) {
        Coord_00453840* result = FUN_00453BF0(&tmp, mode, 1);
        return out->Set(result->X, result->Y, result->Z);
    }

    Coord_00453840 zero = { 0, 0, 0 };
    Coord_00453840* base = FUN_006F3AD0(&tmp, mode, zero);
    int x = base->X;
    int y = base->Y;
    int z = base->Z;

    if (At_520->At_16C5) {
        Point_00453840 offset;
        offset.X = At_520->At_11E0;
        offset.Y = At_520->At_11E4;
        Point_00453840* client = DAT_00887324->CoordsToClient(
            &projected, &offset.X);
        x += client->X;
        y += client->Y;
    }

    return out->Set(x, y, z);
}
