// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit Unit.CPP. The name is the source-file string at 0x845964
//   in retail gamemd.exe v1.001, passed by the assert at 0x746bd4 inside this object's
//   code range (0x735180-0x746edf). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.
//
// The four remaining identity tests, ordered ascending by retail address.
//
// The two conditions have to sit in one `&&` with the `true` inline: split
// into two early-return `if`s the failure block is duplicated and the score
// drops to 18.2%.
//
//   cross-checked against YRpp.

#include "../combat/unit_class_should_crash_methods.h"

#include "../core/deleting_dtor_sweep.h"
#include "../network/transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

#include "../core/same_object_test_sweep.h"

#include "trivial_tu258_methods.h"

#include <stdlib.h>
#include "unit_class_astar_attempt_methods.h"

#include "unit_class_occupation_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F5C28
extern const double DAT_007F5C28;
// GLOBAL: GAMEMD 0xB1CFD0
extern double DAT_00B1CFD0;
// GLOBAL: GAMEMD 0xB1D008
extern double DAT_00B1D008;
// GLOBAL: GAMEMD 0xB1D0A0
extern int DAT_00B1D0A0;
// GLOBAL: GAMEMD 0xB1D0A4
extern int DAT_00B1D0A4;
// GLOBAL: GAMEMD 0xB1D0A8
extern int DAT_00B1D0A8;
// GLOBAL: GAMEMD 0xB1D0B0
extern double DAT_00B1D0B0;

// FUNCTION: GAMEMD 0x7351B0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_007351B0()
{
    DAT_00B1D0B0 = DAT_00B1CFD0 / DAT_007F5C28;
}

// FUNCTION: GAMEMD 0x7351D0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_007351D0()
{
    DAT_00B1D008 = DAT_007E1718 / DAT_00B1D0B0;
}

// FUNCTION: GAMEMD 0x735350
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_00735350()
{
    DAT_00B1D0A8 = 0;
    DAT_00B1D0A0 = 0x80;
    DAT_00B1D0A4 = 0x80;
}

// FUNCTION: GAMEMD 0x7393B0
// Empty function.
void __cdecl FUN_007393B0()
{
}

// FUNCTION: GAMEMD 0x740E50
// Tail-forwards to another function. Vtable slot 174 of UnitClass (RTTI).
void FUN_00740E50(Obj_00740E50* a1, int a2)
{
    FUN_00708C30(a1, a2);
}

// FUNCTION: GAMEMD 0x740E80  (__thiscall)
// If the unit is not in motion (per its locomotor) and the door-pending flag is
// clear, begin the door transition by handing the unit type's door-open angle to
// the unload timer. The locomotor is a COM smart pointer, so the dereference
// carries the inlined NULL-guard that raises E_POINTER.
void UnitClass::APCOpenDoor()
{
    ILocomotionPtr* loco = reinterpret_cast<ILocomotionPtr*>(&this->Locomotor);
    if (!(*loco)->IsMoving() && !this->unknown_bool_6AF)
    {
        reinterpret_cast<DoorTimer*>(&this->UnloadTimer)->Start(
            *reinterpret_cast<double*>(reinterpret_cast<char*>(this->Type) + 0x3C8));
    }
}

// FUNCTION: GAMEMD 0x740EE0
// Tail-forwards to another function. Vtable slot 195 of UnitClass (RTTI).
void FUN_00740EE0(Obj_00740EE0* a1, int a2)
{
    FUN_00707D20(a1, a2);
}

// FUNCTION: GAMEMD 0x741490
// Member getter (dword). Vtable slot 34 of UnitClass (RTTI).
int Obj_00741490::FUN_00741490() const
{
    return unknown_6C4;
}

// FUNCTION: GAMEMD 0x7438F0
//
// MATCHED (100.0%, 108/108). Retail's per-operand store/FILD interleave
// (store Y, compute Z, FILD Y, store Z, FILD Z) comes from binding each
// component of the CoordStruct difference to its own `double` local
// immediately after that component's store, and then writing the sum over the
// doubles; writing the casts inside the sum expression lets cl 12.00.8804
// batch both int stores and then both FILDs. Variants tried: the difference as
// three separate ints (84.3%), as a `volatile` CoordStruct (28.7% — volatile
// also breaks the FMUL/FLD duplication), and the casts inline (95.4%). The
// final compare needed the slot-0xC8 result bound to a `char` local and then to
// a named bool: spelled inline as `call(...) == 0` cl emits NEG/SBB/INC instead
// of retail's TEST AL,AL / SETZ AL (84.4%).
//
// UnitClass::ShouldCrashIt — decide whether this unit may run the candidate
// over. The unit's house type must allow crushing outright or the unit must
// answer capability 0x11; the candidate must exist and accept the unit; the
// straight-line distance between the two coordinate triples (taken through the
// by-value coordinate slot 0x48 of each) must be inside the rules limit; and
// the owning house must pass three further checks — a human/AI split crossed
// with the rules flag and the house type's second byte, a house state that is
// not 2, and a minimum count for AI houses. Only then is the candidate's own
// veto slot 0xC8 asked, and its answer is inverted into the result.
bool Obj_007438F0::ShouldCrashIt(Obj_007438F0* victim)
{
    if (this->At_6C4->At_D28 == 0 && !this->FUN_0070D0D0(0x11)) {
        return false;
    }

    if (victim != 0 && victim->FUN_005F6CD0(this)) {
        Coord_007438F0 there;
        Coord_007438F0 here;
        Coord_007438F0* a = (victim->*victim->Vtbl->At_048)(&there);
        Coord_007438F0* b = (this->*this->Vtbl->At_048)(&here);

        Coord_007438F0 d;
        d.X = b->X - a->X;
        d.Y = b->Y - a->Y;
        double dy = (double)d.Y;
        d.Z = b->Z - a->Z;
        double dz = (double)d.Z;
        double dx = (double)d.X;

        double dist = Sqrt_004CAC40(dx * dx + dz * dz + dy * dy);

        if ((int)dist <= RulesInstance_007438F0->At_1728) {
            if (this->At_21C->FUN_0050B730()
                && RulesInstance_007438F0->At_17EB == 0
                && this->At_6C4->At_D2D == 0) {
                return false;
            }
            if (this->At_21C->At_184 == 2) {
                return false;
            }
            if (!this->At_21C->FUN_0050B730()
                && this->At_21C->At_24C < RulesInstance_007438F0->At_1448) {
                return false;
            }
            char veto = (victim->*victim->Vtbl->At_0C8)(this->At_21C);
            bool ok = (veto == 0);
            return ok;
        }
    }

    return false;
}

// FUNCTION: GAMEMD 0x7441B0  (__thiscall)
// Set the "Units" occupation bit (0x20) for the cell the coordinate maps to.
// When the coordinate sits at or below the cell floor and the cell is a bridge
// cell, the bit goes into the alternate (on-bridge) occupation set instead.
void UnitClass::MarkAllOccupationBits(CoordStruct const& coords)
{
    OccCellClass* cell = MapInstance->GetTargetCell(coords);
    if (MapInstance->GetCellFloorHeight(coords) + BridgeCellHeight <= coords.Z
        && (cell->Flags & 0x100))
    {
        cell->AltOccupationFlags |= 0x20;
        return;
    }
    cell->OccupationFlags |= 0x20;
}

// FUNCTION: GAMEMD 0x744210  (__thiscall)
// Clear the "Units" occupation bit (0x20) the mirror of MarkAllOccupationBits;
// unlike the mark path the unmark always clears the alternate set on the
// at-or-below-floor branch with no bridge-flag test.
void UnitClass::UnmarkAllOccupationBits(CoordStruct const& coords)
{
    OccCellClass* cell = MapInstance->GetTargetCell(coords);
    if (MapInstance->GetCellFloorHeight(coords) + BridgeCellHeight <= coords.Z)
    {
        cell->AltOccupationFlags &= ~0x20;
        return;
    }
    cell->OccupationFlags &= ~0x20;
}

// FUNCTION: GAMEMD 0x7447A0
// Tail-forwards to another function. Vtable slot 132 of UnitClass (RTTI).
void FUN_007447A0(Obj_007447A0* a1, int a2)
{
    FUN_004D4DC0(a1, a2);
}

// FUNCTION: GAMEMD 0x746000
//
// Should a short hop between two cells be handed to the A* search? A unit
// below ground, a failed pre-check, a far hop (twelve cells or more) or an
// off-map endpoint all say yes; the same cell or an adjacent one says no.
// In between, the search is run for real and only a long result counts.
//
// Every `return true` is the one fall-through tail: the guards are nested
// (`&&` chains) rather than early returns, which is what makes retail jump
// forward to a single MOV AL,1 block while the false returns stay inline.
// The flag word is unsigned so the level bit comes out with SHR.
bool Unit_00746000::AStarAttempt(const Cell_00746000* from, const Cell_00746000* to)
{
    if ((this->*Vptr->GetHeight)() >= 0
        && MapInstance_00746000.FUN_0056D100(from, to, 0, 0, 0, 0)) {
        if (from->X == to->X && from->Y == to->Y) {
            return false;
        }

        int dy = abs(to->Y - from->Y);
        int dx = abs(to->X - from->X);
        int dist = dx > dy ? dx : dy;
        if (dist == 1) {
            return false;
        }
        if (dist < 12
            && MapInstance_00746000.IsWithinUsableArea(from, true)
            && MapInstance_00746000.IsWithinUsableArea(to, true)) {
            int steps = DAT_0087E8B8.AttemptPath(
                from, to, this, false,
                (MapInstance_00746000.GetCellAt(to)->Flags >> 8) & 1, 0);
            return steps > 15;
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x746400
// Returns a comparison result. Vtable slot 32 of UnitClass (RTTI).
unsigned char Obj_00746400::FUN_00746400() const
{
    return unknown_6C4->unknown_E1B == 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x746CB0
// Tail-forwards to another function. Vtable slot 303 of UnitClass (RTTI).
void FUN_00746CB0(Obj_00746CB0* a1, int a2)
{
    FUN_0070F070(a1, a2);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x746CC0
// Tail-forwards to another function. Vtable slot 304 of UnitClass (RTTI).
void FUN_00746CC0(Obj_00746CC0* a1, int a2)
{
    FUN_0070F090(a1, a2);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x746D00
// Member getter (byte).
unsigned char Obj_00746D00::FUN_00746D00() const
{
    return unknown_6C4->unknown_6AC;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x746D60
// Calls other functions. Vtable slot 92 of UnitClass (RTTI).
void FUN_00746D60(Obj_00746D60* a1, int a2)
{
    FUN_00738680(a1, a2);
    a1->FUN_00710460();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x746D80
// Member getter (byte).
unsigned char Obj_00746D80::FUN_00746D80() const
{
    return unknown_6E0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x746D90
// Branching.
int Obj_00746D90::FUN_00746D90()
{
    return unknown_6E0 != 0 || unknown_6E1 != 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x746DD0
// Returns a constant. Vtable slot 12 of UnitClass (RTTI).
int Obj_00746DD0::FUN_00746DD0() const
{
    return 0x8E8;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x746E20
// Returns a constant. Vtable slot 11 of UnitClass (RTTI).
int Obj_00746E20::FUN_00746E20() const
{
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x746E80
void* Obj_746E80::FUN_746E80(unsigned int flags)
{
    FUN_00735780(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x746EA0
bool HandleHolder::FUN_00746EA0(void** other)
{
    if (this->Held != 0 && *this->Held == *other) {
        return true;
    }

    return false;
}
