// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The flyer's Stop_Moving. Bytes diffed against the user's retail
//   gamemd.exe v1.001.
#include "fly_locomotion_stop_moving_methods.h"

// VTABLE: GAMEMD 0x7E89F4 — the locomotor interface vtable (base offset 4).
// GLOBAL: GAMEMD 0x87F7E8 — the map.
// GLOBAL: GAMEMD 0x8871E0 — the rules object.
// GLOBAL: GAMEMD 0x8B3C58 — the unset cell.
// GLOBAL: GAMEMD 0x8B3C78 — the unset coordinate.
// GLOBAL: GAMEMD 0x8B3CAC — the bridge height.

// NOT the receiver's-home frame class. Screened explicitly against the frame
// signature that 0x4CCC80 turned out to have: this body's prologue is
// `SUB ESP,0x18` on BOTH sides, the first nine instructions are byte-exact,
// and every stack displacement agrees. It has one dead parameter home (the
// receiver's, at `[ESP+0x20]`) and neither build spends it. The frame lever
// recorded in fly_locomotion_move_to_methods.cpp - the twelve-byte aggregate
// hoisted to function scope, the long-lived holder scoped into a block -
// therefore has nothing to act on here, and the residual below (retail's
// dead-store elimination in the location copy, plus the constant-register
// push idiom) is a separate class that survives it.
//
// PARTIAL -- 9.0% by the offset-aligned differ, but the instruction multiset
// is 223 against 223 and only three mnemonics differ: retail has one more
// PUSH, one JE where cl emits JNE, and one XOR where cl emits a POP; cl has
// one more MOV. Everything that follows reads as different because the
// divergence starts at instruction eleven, in the client's location copy:
// retail keeps X and Y in EAX and EDI, where the cell conversion consumes
// them, and commits ONLY Z to the frame, while cl 8804 commits all three and
// needs an extra base copy to do it. Both X and Y are overwritten later in
// the only block that reads the coordinate, so those are dead stores retail's
// build eliminates and ours keeps - and the three extra bytes push every
// later displacement out of alignment.
//
// Variants measured: the location copied whole (223 against 223, the spelling
// kept here, 9.0%); only Z assigned with the two components read as direct
// member expressions (218 against 223, 5.4%); the same through a named
// pointer to the location (5.4%); the same through a reference (5.4%) - each
// of those drops the base LEA retail has as well as the two stores, so they
// are further away, not closer. The nearby-cell test was also written both
// ways round: with the equal arm first (the spelling kept here, which is what
// retail's JNZ-then-JZ pair says) and with the unequal arm first; no
// difference in the multiset, and neither reaches retail's layout, which
// falls through into the work block and jumps forward to the idle one. The
// cell conversion was also tried taking a reference to the client's location
// rather than two ints, to force the base LEA retail makes: cl folds it away
// either way. The remaining PUSH/MOV pair is the constant
// register idiom in the fifteen-argument map call: retail materialises
// `MOV EAX,0x1` once and pushes EAX and a copy in ECX for three of the ones,
// where cl pushes the immediate.
//
// ILocomotion slot +0x48 — stop the flyer. A flyer still above the ground
// picks the cell under its client, nudges that to a usable one when the
// client is not allowed to sit where it is, and then either parks an aircraft
// on it or, for everything else, looks for a free cell nearby and settles the
// client onto the cell that answers.
// FUNCTION: GAMEMD 0x4CCFD0
void __stdcall FlyLocoStop::StopMoving()
{
    if (GG_FLY_SELF_B(this, 0x10) == 0) {
        return;
    }

    Foot_004CCFD0* client = this->LinkedTo;
    // Only Z reaches the frame: retail leaves X and Y in the registers the
    // cell conversion consumes and overwrites the coordinate's X and Y later,
    // so a whole-struct copy of the location stores one component too many.
    Coord_004CCFD0 coord = client->Location;
    Cell_004CCFD0 cell = CellOf_004CCFD0(coord.X, coord.Y);

    if (client->At_3D4 == 0) {
        if (MapInstance_004CCFD0.At_578460(&cell, 1) == 0) {
            if ((client->*client->Vtbl->At_4DC)() == 0) {
                Cell_004CCFD0 nudged;
                cell = *MapInstance_004CCFD0.At_586AC0(&nudged, &cell, 1);
            }
        }
    }

    Foot_004CCFD0* flyer = this->LinkedTo;
    if (flyer != 0 && (flyer->*flyer->Vtbl->At_2C)() == 2) {
        if (cell.X == UnsetCell_008B3C58.X &&
            cell.Y == UnsetCell_008B3C58.Y) {
            Foot_004CCFD0* idle = this->LinkedTo;
            (idle->*idle->Vtbl->At_16C)(&idle->At_6C, 0,
                                        Rules_008871E0_Instance->At_FA8,
                                        0, 1, 1, 0);
        } else {
            Foot_004CCFD0* state = this->LinkedTo;
            if ((state->*state->Vtbl->At_184)() == 1) {
                CellClass_004CCFD0* own = flyer->FUN_0041A160();
                Foot_004CCFD0* park = this->LinkedTo;
                (park->*park->Vtbl->At_480)(own);
                return;
            }
            CellClass_004CCFD0* picked =
                flyer->FUN_00418E20(MapInstance_004CCFD0.GetCell(&cell));
            Foot_004CCFD0* park = this->LinkedTo;
            (park->*park->Vtbl->At_480)(picked);
            return;
        }
    } else {
        Cell_004CCFD0 nearby;
        Cell_004CCFD0 buffer;
        nearby.X = 0;
        nearby.Y = 0;
        Cell_004CCFD0 found =
            *MapInstance_004CCFD0.NearByLocation(&buffer, &cell, 1, -1, 9, 0,
                                                 1, 1, 0, 0, 0, 1, &nearby,
                                                 0, 0);

        if (found.X != UnsetCell_008B3C58.X ||
            found.Y != UnsetCell_008B3C58.Y) {
            coord.X = found.X * 256 + 128;
            coord.Y = found.Y * 256 + 128;
            coord.Z = 0;
            coord.Z = MapInstance_004CCFD0.GetZHeightAt(coord);
            if ((MapInstance_004CCFD0.GetCell(&found)->Flags & 0x100) != 0) {
                coord.Z = coord.Z + BridgeHeight_008B3CAC;
            }

            Foot_004CCFD0* settle = this->LinkedTo;
            FootVtbl_004CCFD0* vt = settle->Vtbl;
            (settle->*vt->At_480)(
                MapInstance_004CCFD0.GetCellAt(&coord, 1));

            if (this->IsLanding != 0) {
                return;
            }

            Foot_004CCFD0* again = this->LinkedTo;
            FootVtbl_004CCFD0* vt2 = again->Vtbl;
            (again->*vt2->At_480)(
                MapInstance_004CCFD0.GetCellAt(&coord, 1));
            return;
        } else {
            Foot_004CCFD0* idle = this->LinkedTo;
            if (idle->At_6C <= 0) {
                return;
            }
            (idle->*idle->Vtbl->At_16C)(&idle->At_6C, 0,
                                        Rules_008871E0_Instance->At_FA8,
                                        0, 1, 1, 0);
        }
    }

    this->Destination = UnsetCoord_008B3C78;
}
