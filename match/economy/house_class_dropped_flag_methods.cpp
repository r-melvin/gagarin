// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4FBF60.

#include "house_class_dropped_flag_methods.h"

// FUNCTION: GAMEMD 0x4FBF60  HouseClass::DroppedFlag (__thiscall, ret 8)
//
// A carrier drops this house's flag on a cell. Off-map cells are refused
// outright. Otherwise the flag bookkeeping is updated and the cell is asked
// to take the flag; if it will not, the nearest free 1x1 spot is searched
// for and tried instead (the "no cell" sentinel means nothing was found).
// Whichever cell accepted becomes the flag's location.
//
// PARTIAL (23.9%, 22/92). Frame, slots and call sequence agree (the cell
// copy in the first parameter's home slot, the zeroed close-to cell in the
// second's, the NearByLocation out buffer as the one real local, every
// callee and its argument order); the residual is retail's operand
// materialisation for the fifteen NearByLocation arguments and its
// callee-saved placement. Retail keeps the repeated constant 1 in EAX (with
// a copy in ECX for SpaceSizeY) and the zeros in EDX, pushes registers, and
// so needs EBP for the close-to address, saved and restored around that
// call; it also sinks the PUSH EBX for `ok` past the map-bounds check. cl
// 8804 pushes the four 1s as immediates (it materialises only the zero,
// which the two word stores force into a register), never needs EBP, and
// saves EBX in the prologue. Every other retail NearByLocation call site
// (0x41A2C0 with 3s, 0x4D6CE1) shows the same register-materialised
// constants, so this is the compiler build, not the phrasing. Variants
// tried: the explicit out-pointer call with early returns and with the body
// nested under the bounds check; `1`/`0` literals for the bool arguments;
// `char` for the flag; the by-value wrapper inlined (both `return *ptr` and
// `return outBuffer`, identical output); an aggregate-initialised close-to;
// and the whole post-check body as an inline member (which costs the
// parameter-slot reuse for the cell copy, 25.0% but structurally further).
// Recorded as a candidate for the 8447-vs-8804 list.
// Lift pass 2 (2026-09-18): confirmed as that class rather than a phrasing
// problem. A flag bisection on the sibling site 0x74D490 (/O1, /O2 /Os, /Ox,
// /O2 /Gs) never makes cl 8804 materialise a repeated push constant into a
// register, so no switch reaches retail's shape. Best form kept at 23.9%.
bool House_004FBF60::DroppedFlag(const Cell_004FBF60& cell, unsigned long dwUnk)
{
    if (DAT_0087F7E8.CoordinatesLegal(cell)) {
    this->UpdateFlagCoords(this->FlagLocation, dwUnk);

    Cell_004FBF60 c = cell;
    bool ok = DAT_0087F7E8.GetCellAt(c)->FUN_00483410(this->Type->ColorSchemeIndex);
    if (!ok) {
        Cell_004FBF60 closeTo;
        closeTo.X = 0;
        closeTo.Y = 0;
        c = DAT_0087F7E8.NearByLocation(cell, 1, -1, 0, false, 1, 1,
                                         false, false, false, true, closeTo,
                                         false, false);
        if (c.X == DAT_00A8EF98.X && c.Y == DAT_00A8EF98.Y)
            return ok;
        ok = DAT_0087F7E8.GetCellAt(c)->FUN_00483410(this->Type->ColorSchemeIndex);
        if (!ok)
            return ok;
    }

    this->FlagLocation = DAT_0087F7E8.GetCellAt(c);
    return ok;
    }
    return false;
}
