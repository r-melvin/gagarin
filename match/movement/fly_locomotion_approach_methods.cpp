// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
//   Measured, exactly as in fly_locomotion_draw_offset_methods.cpp: the
//   queried interface is held by a scope object whose destructor is the
//   release, and under /GX cl wraps the scope in an unwind frame
//   retail's bare `SUB ESP,0x1C` prologue rules out.
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The flyer's approach steering. Bytes diffed against the user's retail
//   gamemd.exe v1.001.
#include "fly_locomotion_approach_methods.h"

// VTABLE: GAMEMD 0x7E89F4 — the locomotor interface vtable (base offset 4).
// GLOBAL: GAMEMD 0x87F7E8 — the map.
// GLOBAL: GAMEMD 0x8B3CAC — the bridge height.
// GLOBAL: GAMEMD 0x822410 — the queried interface id.
// GLOBAL: GAMEMD 0x7E2820 — double pi/2.
// GLOBAL: GAMEMD 0x7E2818 — double -10430.060040584269, the angle scale.

// PARTIAL -- 19.0% by the offset-aligned differ, but the instruction multiset
// is IDENTICAL (142 against 142) and the residual is one instruction's
// placement: retail saves EBX in the prologue with the other three callee-saved
// registers and pops it last, after the result byte is set, while cl sinks the
// save into the query block (`PUSH EBX` at +0x67, `POP EBX` at +0xB7). That
// costs four bytes of frame base to every stack displacement before the sink
// point, so the whole body reads as different while every instruction is the
// one retail has, in retail's order, with retail's registers.
//
// Six spellings measured against the labelled control, all 19.0%: the status
// hoisted to function scope, the same initialised to zero, the same with a
// default assigned on an else arm (the banked single-exit lever), the holder
// declared at the top of the function, the whole query block moved into a
// forced-inline helper taking the holder by reference (the flattened-boundary
// lever), and the control itself. Three earlier findings did fire and are kept:
// the client's aiming slot takes its buffer as an explicit out-parameter and
// hands it back, so both components are read off the returned register rather
// than copied into a local first (16.0% to 19.0% and the frame from 0x20 down
// to retail's 0x1C); the X difference's two operands are named ints, which is
// what spills them for the FILD/FISUB pair while the Y difference stays
// direct; and the release is the holder's in-class destructor under a dropped
// exception flag, exactly as in fly_locomotion_draw_offset_methods.cpp.
//
// Steer the approach. The travel still to run is measured against the ground
// clearance the client's own interface asks for, and against the leg's total
// length: through the first third the client keeps turning to the heading it
// wants, through the next sixth it turns towards the destination itself and
// the ramp goes to full, and past that nothing is steered at all. A client
// standing over a bridge deck discounts the bridge height from its travel.
// FUNCTION: GAMEMD 0x4CE680
char FlyLocoApproach::Approach()
{
    Foot_004CE680* first = this->LinkedTo;
    int travel = (first->*first->Vtbl->At_1C8)();

    Foot_004CE680* client = this->LinkedTo;
    if (client->IsOnBridgeDeck == 0) {
        Coord_004CE680 here = client->Location;
        if ((MapInstance_004CE680.GetCellAt(here)->Flags & 0x100) != 0) {
            int bridge = BridgeHeight_008B3CAC;
            if (travel >= bridge) {
                travel -= bridge;
            }
        }
    }

    Holder_004CE680 held;
    held.Held = 0;

    Foot_004CE680* aggregate = this->LinkedTo;
    if (aggregate != 0) {
        IFace_004CE680* got;
        long hr = aggregate->Vtbl->QueryInterface(aggregate, riid_00822410,
                                                  (void**)&got);
        if (hr < 0) {
            FUN_004D0430(&held);
            held.Held = 0;
        } else {
            IFace_004CE680* taken = got;
            FUN_004D0430(&held);
            held.Held = taken;
        }
        if (hr < 0 && hr != 0x80004002) {
            FUN_007DC720(hr);
        }
    }

    int clearance = 0;
    if (held.Held != 0) {
        clearance = held.Held->Vtbl->GetGroundClearance(held.Held);
    }

    int total = this->FlightLevel - clearance;
    travel -= clearance;
    this->IsTakingOff = 0;
    this->IsLanding = 0;

    if (travel > total - total / 3) {
        Dir_004CE680 wanted;
        this->LinkedTo->SecondaryFacing.SetDesired(
            this->LinkedTo->PrimaryFacing.Desired(&wanted));
    } else if (travel > total / 2) {
        Foot_004CE680* aiming = this->LinkedTo;
        Coord_004CE680 buffer;
        Coord_004CE680* target = (aiming->*aiming->Vtbl->At_48)(&buffer);

        int fromX = this->Destination.X;
        int toX = target->X;
        double radians = FUN_004CAE30((double)target->Y - this->Destination.Y,
                                      (double)fromX - toX);

        Dir_004CE680 turned;
        turned.Raw = (short)((radians - 1.5707963267948966)
                             * -10430.060040584269);
        Dir_004CE680 passed = turned;
        this->LinkedTo->PrimaryFacing.SetDesired(&passed);

        this->Ramp = 1.0;
    }

    return 1;
}
