// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU084 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x4cc790-0x4d055f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   The leaf half of FlyLocomotionClass. Bytes diffed against the user's
//   retail gamemd.exe v1.001; bodies ordered ascending by retail address.
//   Every entry point here came out of a raw-byte sweep of 0x4CC100-0x4D0600
//   for NOP runs ending on a four-byte boundary, not out of the Ghidra
//   function list, which under-segments this region badly.
//
//   The two ILocomotion matrix slots of FlyLocomotionClass. Bytes diffed
//   against the user's retail gamemd.exe v1.001; bodies ordered ascending by
//   retail address.
//
//   The two __thiscall members of FlyLocomotionClass that drive the touchdown
//   spin and the landing switch. Bytes diffed against the user's retail
//   gamemd.exe v1.001; bodies ordered ascending by retail address.
//
//   Measured, exactly as in fly_locomotion_draw_offset_methods.cpp: the
//   queried interface is held by a scope object whose destructor is the
//   release, and under /GX cl wraps the scope in an unwind frame
//   retail's bare `SUB ESP,0x1C` prologue rules out.
//   The flyer's approach steering. Bytes diffed against the user's retail
//   gamemd.exe v1.001.
//
//   Measured: the holder is a scope object whose destructor is the release,
//   and under /GX cl wraps the scope in an unwind frame retail has
//   no trace of (0% against a body that is otherwise instruction-for-
//   instruction correct). Without /GX the prologue is retail's bare four
//   pushes. Same category as match/platform/ccini_class_type_list_methods.cpp.
//   The flyer's per-frame draw offset. Bytes diffed against the user's retail
//   gamemd.exe v1.001.
//
//   The flyer's take-off switch. Bytes diffed against the user's retail
//   gamemd.exe v1.001.
// VC6FLAGS: /nologo /c /O2 /Gr /GR /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).

#include "fly_locomotion_leaf_methods.h"
#include "loco_base.h"
#include "../_layout/fly_locomotion_class.h"
#include "../_layout/foot_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/com_interfaces.h"
#include "../_layout/aircraft_class.h"
#include "../_layout/aircraft_type_class.h"

// Native DrawMatrix fields: 0x4CF610 entry-origin instruction offsets.
GG_STATIC_ASSERT(offsetof(TechnoClass, AngleRotatedSideways) == 0x328);
GG_STATIC_ASSERT(offsetof(TechnoClass, AngleRotatedForwards) == 0x32C);
GG_STATIC_ASSERT(offsetof(TechnoClass, IsCrashing) == 0x425);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, RollAngle) == 0x3A0);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, PitchSpeed) == 0x3A8);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, PitchAngle) == 0x3B0);

// Native DrawPoint 0x4CF8CB tests type +0xC95.
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, bools_C8C) + 9 == 0xC95);
GG_STATIC_ASSERT(sizeof(IID) == 16);

// VTABLE: GAMEMD 0x7E89F4 — the locomotor interface vtable (base offset 4).
// VTABLE: GAMEMD 0x7E8AC0 — the persist vtable (base offset 0).
// GLOBAL: GAMEMD 0x8B3C78 — the engine's unset coordinate.
// GLOBAL: GAMEMD 0xA8B230 — the scenario object.

#include "../_layout/matrix3d.h"
#include "locomotion_rotation_step.h"

// VTABLE: GAMEMD 0x7E89F4 — the locomotor interface vtable (base offset 4).
// GLOBAL: GAMEMD 0x87F7E8 — the map.
// Reads global 0x7E4408: double -pi/16, the per-facing rotation step.
// GLOBAL: GAMEMD 0x7E2800 — double 0.0, the two rate comparisons.

#include <stdlib.h>
#include "fly_locomotion_spin_methods.h"

// VTABLE: GAMEMD 0x7E89F4 — the locomotor interface vtable (base offset 4).
// GLOBAL: GAMEMD 0x87F7E8 — the map.

#include "fly_locomotion_approach_methods.h"

// VTABLE: GAMEMD 0x7E89F4 — the locomotor interface vtable (base offset 4).
// GLOBAL: GAMEMD 0x87F7E8 — the map.
// GLOBAL: GAMEMD 0x8B3CAC — the bridge height.
// GLOBAL: GAMEMD 0x822410 — the queried interface id.
// GLOBAL: GAMEMD 0x7E2820 — double pi/2.
// GLOBAL: GAMEMD 0x7E2818 — double -10430.060040584269, the angle scale.

#include "fly_locomotion_draw_offset_methods.h"

// VTABLE: GAMEMD 0x7E89F4 — the locomotor interface vtable (base offset 4).
// GLOBAL: GAMEMD 0x822410 — the queried interface id.
// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame.
// GLOBAL: GAMEMD 0x7E8AF0 — double pi/10, one bob cycle per twenty frames.
// GLOBAL: GAMEMD 0x7E48F0 — double 1.5, the bob amplitude.
// GLOBAL: GAMEMD 0x7E1738 — double 0.5, the rounding bias.

#include "fly_locomotion_takeoff_methods.h"

// VTABLE: GAMEMD 0x7E89F4 — the locomotor interface vtable (base offset 4).
// GLOBAL: GAMEMD 0x8B3C58 — the engine's unset cell.
// GLOBAL: GAMEMD 0x887888 — the list a cell-less client is registered with.

//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7E89C8
extern const double DAT_007E89C8;
// GLOBAL: GAMEMD 0x8B3C60
extern double DAT_008B3C60;

// SYNTHETIC: GAMEMD 0x4CC7C0
// GLOBAL: GAMEMD 0x8B3CB0
double DAT_008B3CB0 = DAT_008B3C60 / DAT_007E89C8;

// SYNTHETIC: GAMEMD 0x4CC7E0
// GLOBAL: GAMEMD 0x8B3C98
double DAT_008B3C98 = DAT_007E1718 / DAT_008B3CB0;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// ILocomotion slot +0x0C — bind the locomotor to a client. The base does the
// binding; this override then records the aircraft type airport-bound flag.
// FUNCTION: GAMEMD 0x4CCA20
HRESULT __stdcall FlyLocomotionClass::LinkToObject(FootClass* object)
{
    HRESULT hr = LocomotionClass::LinkToObject(object);
    if (hr == 0) {
        // Native kind 2 gates the AircraftClass +0x6C4 type access (0x4CCA42).
        if (object != 0 && object->vf_11() == 2 &&
            static_cast<AircraftClass*>(object)->Type->AirportBound != 0) {
            AirportBound = 1;
        } else {
            AirportBound = 0;
        }
    }
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// The destructor: re-seat both of this class's vtables over the base's, then
// tail into the base destructor. cl turns the trailing call into the bare
// jump retail has.
// FUNCTION: GAMEMD 0x4CCA70
void FlyLocoObject::Destroy()
{
    PersistVptr = (void*)0x7E8AC0;
    LocomotorVptr = (void*)0x7E89F4;
    ((LocoBase_0055A6F0*)this)->Destroy();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// ILocomotion slot +0x10 — tests HasMoveOrder or the client float at +0x2E8.
// FUNCTION: GAMEMD 0x4CCA90
bool __stdcall FlyLocomotionClass::IsMoving()
{
    return !(HasMoveOrder == 0 && LinkedTo->PitchAngle <= 0.0f);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// ILocomotion slot +0x80 — tests CurrentSpeed against zero.
// FUNCTION: GAMEMD 0x4CCAC0
bool __stdcall FlyLocomotionClass::IsMovingNow()
{
    if (CurrentSpeed == 0.0) {
        return 0;
    }
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// ILocomotion slot +0x14 — where the flyer is headed: its own destination
// when IsMoving is true, and the engine's unset coordinate otherwise.
// FUNCTION: GAMEMD 0x4CCAE0
LocoCoord __stdcall FlyLocomotionClass::Destination()
{
    LocoCoord result;
    if (IsMoving()) {
        result.X = Destination_.X;
        result.Y = Destination_.Y;
        result.Z = Destination_.Z;
        return result;
    }
    result.X = UnsetCoord_008B3C78.X;
    result.Y = UnsetCoord_008B3C78.Y;
    result.Z = UnsetCoord_008B3C78.Z;
    return result;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// MATCHED (second look): the earlier residual was the destination of the
// spin/facing addition. Reading the facing first into a named local and forming
// `base + unknown_54 * 256` as a separate int keeps the sum in 32 bits (the
// inlined form narrowed to 16-bit operations), and the negative-rate decay arm
// must re-read `unknown_54` (`unknown_54 = unknown_54 + step`) rather than reuse the
// `rate` local to get retail's `ADD ECX,EAX`.
//
// One frame of the touchdown spin: while the spin is running and the client
// still has travel left, either step the shared move and, once it reports
// arrival, stop spinning and touch the cell under the client, or turn the
// client by the current spin rate and decay that rate one step toward zero.
// FUNCTION: GAMEMD 0x4CE5A0
void FlyLocoSpin::ProcessSpin()
{
    if (IsSpinning == 0) {
        return;
    }
    if (LinkedTo->Remaining <= 0) {
        return;
    }

    if (((ILoco_004CE5A0*)&LocomotorVptr)->MoveStep() == 0) {
        DirValue_004C93D0 current;
        int base = LinkedTo->Facing.Current(&current)->Value;
        int turn = base + unknown_54 * 256;
        Facing_004C9300 turned;
        turned.Raw = (short)turn;
        Facing_004C9300 passed = turned;
        LinkedTo->Facing.Assign(&passed);

        int rate = unknown_54;
        int step = abs(rate);
        if (step >= 1) {
            step = 1;
        }
        if (rate < 0) {
            unknown_54 = unknown_54 + step;
            return;
        }
        unknown_54 = rate - step;
        return;
    }

    IsSpinning = 0;
    Coord_004CE5A0 where = LinkedTo->Location;
    Map_0087F7E8.GetCellAt(&where)->Touch();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// ILocomotion slot +0x24 — the draw matrix for a flyer: identity rotated
// about Z by the client's secondary facing reduced to 32 steps and re-based
// so that facing 8 is zero, then, while the client still has travel left,
// pitched and rolled by its type's own angles. The voxel index key collects
// the facing and, on each tilt arm, the bit that names it.
// FUNCTION: GAMEMD 0x4CF610
Matrix3D __stdcall FlyLocomotionClass::DrawMatrix(unsigned int* key)
{
    Matrix3D m;
    m.MakeIdentity();

    if (key != 0) {
        *key |= ((((this->LinkedTo->SecondaryFacing.FUN_004C93D0().Whole >> 10) + 1) >> 1) & 0x1F) * 8;
    }

    m.RotateZ((float)(((int)((((this->LinkedTo->SecondaryFacing.FUN_004C93D0().Whole >> 10) + 1) >> 1) & 0x1F) - 8)
                      * gg_locomotion_facing_step));

    if (this->LinkedTo->vf_114() > 0) {
        if (this->LinkedTo->IsCrashing != 0) {
            m.RotateX(this->LinkedTo->AngleRotatedSideways);
            if (this->CurrentSpeed > this->LinkedTo->vf_33()->PitchSpeed) {
                m.RotateY((float)(this->LinkedTo->AngleRotatedForwards +
                                  this->LinkedTo->vf_33()->PitchAngle));
            } else {
                m.RotateY(this->LinkedTo->AngleRotatedForwards);
            }
            if (key != 0) {
                *key = -1;
            }
        } else if (this->CurrentSpeed > this->LinkedTo->vf_33()->PitchSpeed) {
            if (this->LinkedTo->vf_33()->PitchAngle != 0.0) {
                if (key != 0) {
                    *key |= 4;
                }
                m.RotateY((float)this->LinkedTo->vf_33()->PitchAngle);
            }
            if (this->LinkedTo->vf_33()->RollAngle != 0.0) {
                double roll;
                if (this->LinkedTo->SecondaryFacing.IsRotatingCW()) {
                    if (key != 0) {
                        *key |= 1;
                    }
                    roll = this->LinkedTo->vf_33()->RollAngle;
                } else {
                    if (!this->LinkedTo->SecondaryFacing.IsRotatingCCW()) {
                        goto done;
                    }
                    if (key != 0) {
                        *key |= 2;
                    }
                    roll = -this->LinkedTo->vf_33()->RollAngle;
                }
                m.RotateX((float)roll);
            }
        }
    }

done:
    return m;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// ILocomotion slot +0x2C — the draw offset for a flyer. A flyer that is
// neither a ground-hugging type nor landing nor taking off, and that is
// higher above the ground than the interface it aggregates says it needs to
// be, bobs on a twenty-frame sine; everything else sits still. The X
// component is always zero.
//
// Three levers, measured in this order from a 72.3% first draft whose
// instruction multiset was already identical to retail's. The release written
// as an explicit statement before the return lets cl sink both component
// stores past it (72.3%); making it the holder's destructor puts them where
// retail has them but emits the destructor out of line (74.5%); defining that
// destructor in-class expands it (88.3%). The last eleven instructions were a
// two-slot frame exchange - retail keeps the holder in the dead receiver's
// home slot and the query's out-parameter in the frame's one real slot, cl
// the other way round - and it is decided by where the holder is declared
// relative to the receiver read: after it, 100%; before it, 88.3%; with the
// out-parameter hoisted to function scope ahead of it, 84.0%.
// FUNCTION: GAMEMD 0x4CF830
LocoPoint2D __stdcall FlyLocomotionClass::DrawPoint()
{
    int bob = 0;
    FootClass* client = this->LinkedTo;
    FlyDrawInterfaceHolder held;
    held.Held = 0;

    if (client != 0) {
        IFlyControl* got;
        long hr = client->QueryInterface(IID_00822410,
                                              (void**)&got);
        if (hr < 0) {
            held.Release();
            held.Held = 0;
        } else {
            IFlyControl* taken = got;
            held.Release();
            held.Held = taken;
        }
        if (hr < 0 && hr != 0x80004002) {
            FUN_007DC720(hr);
        }
    }

    int clearance = 0;
    if (held.Held != 0) {
        clearance = held.Held->vf_03();
    }

    if (this->LinkedTo->vf_33()->bools_C8C[9] == 0 &&
        this->IsLanding == 0 && this->IsTakingOff == 0 &&
        this->LinkedTo->vf_114() > clearance) {
        bob = (int)(FUN_004CACB0((double)(CurrentFrame % 20)
                                 * 0.3141592653589793) * 1.5 + 0.5);
    }

    LocoPoint2D result;
    result.X = 0;
    result.Y = bob;
    return result;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// ILocomotion slot +0x30 — a flyer contributes no voxel shadow offset.
// FUNCTION: GAMEMD 0x4CF940
LocoPoint2D __stdcall FlyLocomotionClass::ShadowPoint()
{
    LocoPoint2D zero;
    zero.X = 0;
    zero.Y = 0;
    return zero;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Put the flyer into its take-off state. Four gates on the client can refuse
// it outright; past them the landing flag clears, the take-off flag sets, a
// client that is standing on no cell is registered, the cruising speed is
// taken from the type, a client with no travel left is turned to face where
// it wants to face, and the type's take-off sound plays where it stands.
// Two levers. The cell test reads both components off one returned hidden
// pointer, so it has to be a whole-cell comparison; two component
// comparisons written out call the slot twice (22.1%). And the sound's
// coordinate is copied into a frame local whose address is then passed: with
// that copy as its own statement cl schedules it before the argument push and
// re-derives the address at the call (74.7%, one instruction short and every
// byte after it shifted), while writing it inside the argument list puts it
// where right-to-left evaluation does - after the last argument's push, before
// the first argument's own call - and retail then holds the address in the
// dead receiver's register across that call. Naming the address as a local,
// copying through it, and copy-constructing a temporary into a reference
// parameter were all measured at 74.7%.
// FUNCTION: GAMEMD 0x4CF950
void FlyLocoTakeOff::BeginTakeOff()
{
    Foot_004CF950* a = this->LinkedTo;
    if ((a->*a->Vtbl->At_37C)() != 0) {
        return;
    }
    Foot_004CF950* b = this->LinkedTo;
    if ((b->*b->Vtbl->At_380)() != 0) {
        return;
    }
    Foot_004CF950* c = this->LinkedTo;
    if ((c->*c->Vtbl->At_1D4)() != 0) {
        return;
    }
    Foot_004CF950* d = this->LinkedTo;
    if ((d->*d->Vtbl->At_1D8)() != 0) {
        return;
    }

    Foot_004CF950* client = this->LinkedTo;
    this->IsLanding = 0;
    this->IsTakingOff = 1;
    if ((client->*client->Vtbl->At_2F4)() == UnsetCell_008B3C58) {
        Registry_00887888_Instance.Add(this->LinkedTo);
    }

    Foot_004CF950* e = this->LinkedTo;
    FootType_004CF950* type = (e->*e->Vtbl->At_84)();
    this->Speed = (type->*type->Vtbl->At_BC)();

    Foot_004CF950* f = this->LinkedTo;
    if ((f->*f->Vtbl->At_1C8)() == 0) {
        Dir_004CF950 wanted;
        this->LinkedTo->PrimaryFacing.Assign(
            this->LinkedTo->SecondaryFacing.Desired(&wanted));
    }

    Foot_004CF950* g = this->LinkedTo;
    Coord_004CF950 where;
    VocClass_PlayAt_004CF950((g->*g->Vtbl->At_84)()->TakeOffSound,
                             (where = g->Location, &where), 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Switch the locomotor into its landing state. A client that is not a
// building-like object, or whose type does not carry the gate byte, or that
// is already standing on an occupied cell, simply flips the three flags and
// clears the travel; the one that passes every test is told to park instead.
// FUNCTION: GAMEMD 0x4CFA70
void FlyLocoSpin::BeginLanding()
{
    if ((LinkedTo->*LinkedTo->Vtbl->At_184)() == 7 ||
        ((FootGate_00705D60*)LinkedTo)->IsCarryingSomething() == 0) {
        if ((LinkedTo->*LinkedTo->Vtbl->At_2C)() == 2) {
            Foot_004CFA70* linked = LinkedTo;
            if (linked->Type->At_E0D != 0) {
                void* here = (linked->*linked->Vtbl->At_1BC)();
                void* cell = ((CellFinder_0047C520*)here)->ToCell();
                if (((FootOccupier_0065AD50*)LinkedTo)->IsOccupied(cell) == 0) {
                    (linked->*linked->Vtbl->At_484)(0, 1);
                    return;
                }
            }
        }

        IsTakingOff = 0;
        IsLanding = 1;
        Unknown52 = 0;
        FlightLevel = 0;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// ILocomotion slot +0x4C — hand the client's own target slot the object it
// should aim at. Retail copies the parameter over itself and passes that
// slot's address, which is what taking the address of a by-value handle does.
// FUNCTION: GAMEMD 0x4CFC10
void __stdcall FlyLocoAssignTarget_004CFC10(FlyLocoIface* self, void* target)
{
    void* handle = target;
    self->LinkedTo->TargetSlot.Assign(&handle);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Start the touchdown spin at a random rate, half the time in the opposite
// direction. The out-of-line form of the block 0x4CFD20 has inlined.
// FUNCTION: GAMEMD 0x4CFDD0
void FlyLocoObject::StartSpin()
{
    IsSpinning = 1;
    unknown_54 = DAT_00A8B230->unknown_0218.RandomRanged(0x14, 0x1E);
    if (DAT_00A8B230->unknown_0218.RandomRanged(0, 0x63) < 0x32) {
        unknown_54 = -unknown_54;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// ILocomotion slot +0x84 — type Speed scaled by CurrentSpeed and truncated.
// FUNCTION: GAMEMD 0x4CFE20
int __stdcall FlyLocomotionClass::ApparentSpeed()
{
    TechnoTypeClass* type = LinkedTo->vf_33();
    return (int)(type->Speed * CurrentSpeed);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// ILocomotion slot +0x90 — one while landing, zero while taking off,
// and otherwise two or three according to IsMoving.
// FUNCTION: GAMEMD 0x4CFE50
int __stdcall FlyLocomotionClass::GetStatus()
{
    if (IsLanding != 0) {
        return 1;
    }
    if (IsTakingOff != 0) {
        return 0;
    }
    return IsMoving() ? 2 : 3;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x4D0390
// Returns a constant. Vtable slot 9 of FlyLocomotionClass (RTTI).
int FlyLocomotionClass::Size()
{
    return 0x60;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7E89C8
extern const double DAT_007E89C8 = 60.0;
// END defined globals
