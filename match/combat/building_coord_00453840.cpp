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
    TypeView_00453840* type = At_520;

    if (type->At_157B && (this->*Vtbl->At_408)() > 0) {
        Point_00453840 projected;
        const Point_00453840* offset = &type->At_1588 + At_69C;
        Point_00453840* client = DAT_00887324->CoordsToClient(
            &projected, &offset->X);

        Coord_00453840 origin;
        Coord_00453840* base = (this->*Vtbl->At_AC)(&origin);
        out->X = base->X + client->X;
        out->Y = base->Y + client->Y;
        out->Z = base->Z;
        return out;
    }

    if (type->At_E44 == 0xFFFF && type->At_E48 == 0xFFFF) {
        if (type->At_16C6) {
            Coord_00453840 coord;
            Coord_00453840* result = FUN_00453BF0(&coord, mode, 1);
        out->X = result->X;
        out->Y = result->Y;
        out->Z = result->Z;
            return out;
        }

        Coord_00453840 zero = { 0, 0, 0 };
        Coord_00453840 baseResult;
        Coord_00453840* base = FUN_006F3AD0(&baseResult, mode, zero);
        int x = base->X;
        int y = base->Y;
        int z = base->Z;

        if (type->At_16C5) {
            Point_00453840 offset;
            offset.X = type->At_11E0;
            offset.Y = type->At_11E4;
            Point_00453840 projected;
            Point_00453840* client = DAT_00887324->CoordsToClient(
                &projected, &offset.X);
            x += client->X;
            y += client->Y;
        }

        out->X = x;
        out->Y = y;
        out->Z = z;
        return out;
    }

    Point_00453840 projected;
    Point_00453840* client = DAT_00887324->CoordsToClient(
        &projected, &type->At_E44);

    if (type->At_1764) {
        Coord_00453840 zero = { 0, 0, 0 };
        Coord_00453840 baseResult;
        Coord_00453840* base = FUN_006F3AD0(&baseResult, mode, zero);
        out->X = base->X + client->X;
        out->Y = base->Y + client->Y;
        out->Z = base->Z;
        return out;
    }

    Coord_00453840 origin;
    Coord_00453840* base = (this->*Vtbl->At_AC)(&origin);
    out->X = base->X + client->X;
    out->Y = base->Y + client->Y;
    out->Z = base->Z;
    return out;
}
