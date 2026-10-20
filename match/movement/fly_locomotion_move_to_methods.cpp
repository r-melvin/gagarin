// SPDX-License-Identifier: GPL-3.0-or-later
//   No VC6FLAGS line: measured identical with and without /GX, because every
//   holder operation here is called out of line, so no destructor body ever
//   expands into a scope cl would want to protect. That is the difference
//   from fly_locomotion_draw_offset_methods.cpp, which does need the flag.
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The flyer's Move_To. Bytes diffed against the user's retail gamemd.exe
//   v1.001.
#include "fly_locomotion_move_to_methods.h"

// VTABLE: GAMEMD 0x7E89F4 — the locomotor interface vtable (base offset 4).
// GLOBAL: GAMEMD 0x87F7E8 — the map.
// GLOBAL: GAMEMD 0x8B3C78 — the unset coordinate.

// PARTIAL -- 47.7% (133 of 279 retail instructions, 119 exact). The frame now
// MATCHES retail exactly: `SUB ESP,0xC` holding the twelve-byte coordinate the
// map lookup takes the address of, the two live interface holders parked in the
// two dead parameter home slots (`[ESP+0x20]` the receiver's home, `[ESP+0x24]`
// the first coordinate component's), and every stack displacement equal to
// retail's. The instruction multiset is identical, 279 against 279. The whole
// residual is now a double callee-saved register exchange: retail names `this`
// EBX and the first component EBP where cl swaps them, and names the clearance
// ESI and `&LinkedTo` EDI where cl swaps those too.
//
// THE FRAME LEVER (general; see the slot-allocation note below). cl 8804 fills
// the sixteen dead parameter home bytes greedily with NAMED FUNCTION-SCOPE
// locals and spills the remainder into the reserve. Which local wins the homes
// is decided by SCOPE, not by declaration order, first use, type, size class or
// any compiler flag. Two edits, together, put retail's choice in the homes:
//
//   1. hoist the twelve-byte coordinate to FUNCTION scope (out of the bridge
//      -deck `if`), which stops cl overlaying it on the three coordinate homes;
//   2. scope the long-lived holder into its own BLOCK covering the tail, which
//      is what lets cl put it in the first argument's home rather than the
//      reserve.
//
// Either edit alone is worse than both: (1) alone reserves 0x10 with no home
// reuse (42.7%), (2) alone packs all three locals into the homes with no
// reserve at all (6.8%).
//
// Variants measured and eliminated, so no one repeats them. FLAGS: a 47-arm
// grid changed the frame in NO arm - /Oy, /Oy-, /Gs, /GZ, /Zp1 /Zp2 /Zp4 /Zp8
// /Zp16, /O1 /O2 /Ox /Og /Os /Ot /Oa /Ow /Oi /Oi- /Op /Ob0 /Ob1 /Ob2, /Gd /Gr
// /Gz /Gy- /Gf /GB /G5 /G6 /Gi /Gh /Gm /GR, /GX on and off, /Z7 /Zd /Za /Ze
// /Zl, /J /vd0 /vd1 /W4. Only /Oy- (forces an EBP frame) and /O1 /Og /Os /Ob0
// /Gh changed anything, all of them far worse. CODE GENERATOR: compiling
// through the toolchain's other backend, c2.dll 12.00.9044 (the Processor Pack
// build shipped as `c2.dll.sp3bak`) instead of the retail-matching 12.00.8447,
// reproduced the 44.4% frame byte for byte - the backend build is not the
// lever. RECEIVER SHAPE: rewriting the body as a free `__stdcall` function
// taking the object as an explicit first parameter emits IDENTICAL bytes to the
// member spelling (and the `__cdecl` form only changes the return), so cl draws
// no distinction between a member's `this` home and an ordinary parameter's -
// the receiver's home was never the obstacle. SOURCE SHAPE, all no change from
// 44.4%: all six declaration-order permutations of the three locals at function
// scope; the coordinate given a distinct twelve-byte struct type; the
// coordinate `volatile`; a doubly nested block around it; the long-lived
// holder's first store hoisted (cl sinks it again); three separate block-scope
// holders (cl packs the two disjoint ones itself, as the note below says).
// Changed the frame but for the worse: the coordinate at sixteen bytes and an
// extra four-byte memory local both abandon home reuse entirely (0x10/0x14
// reserve); the coordinate as a three-integer constructed argument temporary
// reaches retail's `SUB ESP,0xC` but costs five reloads, because a temporary
// does not force the two high components into registers the way the named local
// does (14.8%). Earlier expression-level arms: the cell comparison through a
// coordinate reference (3.9%, cl materialises `&Destination`) against two loose
// ints; the destination store field-wise (costs a retail `LEA`) against
// whole-struct; the map lookup's argument as a named copy of the parameter or
// of the destination member; the two short-lived holders merged, by reference
// and by name. On top of the applied fix, a single function-scope clearance,
// dropping the `gate` alias, and reversing the cell comparison's operands all
// hold at 47.7% and do not touch the register exchange.
//
// ILocomotion slot +0x44 — hand the flyer a new destination. A repeat of the
// cell it is already landing on is ignored, and so is any client that is
// locked, tethered or otherwise refusing to be steered. An unset coordinate
// means "stop": the flyer either parks over the client and lands, or clears
// its destination outright. A real coordinate is adopted, lifted to the
// bridge deck the client is under when there is one, and then the flyer
// starts elevating, takes off if it still has travel to run, and records
// whether the leg has to be flown high.
// FUNCTION: GAMEMD 0x4CCC80
void __stdcall FlyLocoMoveTo::MoveTo(Coord_004CCC80 to)
{
    // The twelve-byte coordinate has to be a FUNCTION-SCOPE named local
    // and the second holder has to be BLOCK-scoped, or cl lays the frame
    // out differently - see the frame note above.
    Coord_004CCC80 where;
    // One holder object serves the stop path and the high-leg probe: retail
    // gives both the same frame slot (`[ESP+0x20]`, the dead receiver's home),
    // and two separate declarations cost a fourth slot cl spends out of the
    // reserve instead.
    Holder_004CCC80 held;

    if (CellOf_004CCC80(to.X, to.Y) ==
            CellOf_004CCC80(this->Destination.X, this->Destination.Y) &&
        this->IsLanding != 0) {
        return;
    }

    Foot_004CCC80* gate = this->LinkedTo;
    if ((gate->*gate->Vtbl->At_37C)() != 0) {
        return;
    }
    if ((this->LinkedTo->*this->LinkedTo->Vtbl->At_380)() != 0) {
        return;
    }
    if ((this->LinkedTo->*this->LinkedTo->Vtbl->At_1D4)() != 0) {
        return;
    }
    if ((this->LinkedTo->*this->LinkedTo->Vtbl->At_1D8)() != 0) {
        return;
    }
    if (GG_FLY_SELF_B(this, 0x60) == 0) {
        return;
    }

    if (to.X == UnsetCoord_008B3C78.X && to.Y == UnsetCoord_008B3C78.Y &&
        to.Z == UnsetCoord_008B3C78.Z) {
        held.Held = 0;
        int clearance = 0;
        if (this->LinkedTo != 0) {
            long hr = held.QueryFrom(&this->LinkedTo);
            if (hr < 0 && hr != 0x80004002) {
                FUN_007DC720(hr);
            }
            if (held.Held != 0) {
                clearance = held.Held->Vtbl->GetGroundClearance(held.Held);
            }
        }

        if (((this->LinkedTo->*this->LinkedTo->Vtbl->At_1C8)() > clearance ||
             this->IsTakingOff != 0) && this->IsLanding == 0) {
            this->Destination = this->LinkedTo->Location;
            ((FlyLocoObj_004CCC80*)((char*)this - 4))->BeginLanding();
        } else {
            this->Destination = UnsetCoord_008B3C78;
        }

        this->unknown_58 = 0;
        if (held.Held != 0) {
            held.Held->Vtbl->Release(held.Held);
        }
        return;
    }

    this->Destination = to;

    Foot_004CCC80* deck = this->LinkedTo;
    if (deck->At_2B4 != 0 && deck->At_2FC != 0) {
        where.X = to.X;
        where.Y = to.Y;
        where.Z = to.Z;
        FootType_004CCC80* type = (deck->*deck->Vtbl->At_84)();
        this->Destination.Z = MapInstance_004CCC80.GetZHeightAt(where) +
                              (type->*type->Vtbl->At_BC)();
    }

    {
        Holder_004CCC80 kept;
        kept.Held = 0;
        if (this->LinkedTo != 0) {
            long hr = kept.QueryFrom(&this->LinkedTo);
            if (hr < 0 && hr != 0x80004002) {
                FUN_007DC720(hr);
            }
        }
        int clearance = 0;
        if (kept.Held != 0) {
            clearance = kept.Held->Vtbl->GetGroundClearance(kept.Held);
        }

        this->HasMoveOrder = 1;

        Foot_004CCC80* mover = this->LinkedTo;
        if (mover->Remaining > 0 && this->IsTakingOff == 0) {
            if (this->IsLanding != 0 ||
                (mover->*mover->Vtbl->At_1C8)() <= clearance) {
                ((FlyLocoObj_004CCC80*)((char*)this - 4))->BeginTakeOff();
            }
        }

        char high;
        if (this->Destination.Z >
            MapInstance_004CCC80.GetZHeightAt(this->Destination) + 0x78) {
            high = 1;
        } else {
            Foot_004CCC80* over = this->LinkedTo;
            if (over->At_2B4 != 0 && over->At_2FC != 0) {
                high = 1;
            } else {
                held.Held = 0;
                if (this->LinkedTo != 0) {
                    long hr = held.QueryFrom(&this->LinkedTo);
                    if (hr < 0 && hr != 0x80004002) {
                        FUN_007DC720(hr);
                    }
                }
                if (!(held == 0) && held->Vtbl->At_20(held.Held) != 0) {
                    held.Release();
                    high = 1;
                } else {
                    held.Release();
                    high = 0;
                }
            }
        }
        this->unknown_58 = high;

        Foot_004CCC80* kind = this->LinkedTo;
        if ((kind->*kind->Vtbl->At_2C)() == 2) {
            if (this->LinkedTo->Type->At_E0A == 0) {
                this->unknown_58 = 1;
            }
        }

        if (kept.Held != 0) {
            kept.Held->Vtbl->Release(kept.Held);
        }
    }
}
