// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp UnitClass.h / Interfaces.h (consult-only).
//
//   UnitClass : FootClass (FootClass sizeof = 0x6C0; spine in ../_layout).
//   The occupation / door methods touch:
//     - UnloadTimer       @0x350 (TechnoClass base — start the door transition)
//     - Locomotor         @0x674 (FootClass base — ILocomotion COM smart ptr)
//     - unknown_bool_6AF  @0x6AF (FootClass base)
//     - Type              @0x6C4 (UnitClass-specific; UnitTypeClass*)
//   Mark/Unmark do not use `this` at all — they operate purely on the cell the
//   passed coordinate maps to (Map.GetTargetCell + Map.GetCellFloorHeight).
#ifndef GG_MATCH_MOVEMENT_UNIT_CLASS_OCCUPATION_METHODS_H
#define GG_MATCH_MOVEMENT_UNIT_CLASS_OCCUPATION_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/foot_class.h"   // FootClass spine + CoordStruct + Point2D + TransitionTimer + CellStruct
#include "loco_interfaces.h"

// CellClass — only the two occupation bitfields + the cell Flags dword that the
// (un)mark methods touch are modelled. SubOccupation bit 0x20 = "Units".
struct OccCellClass
{
    char         _pad000[0x124];            // +0x000  AbstractClass + cell terrain block
    unsigned int OccupationFlags;            // +0x124
    unsigned int AltOccupationFlags;         // +0x128
    char         _pad12C[0x140 - 0x12C];     // +0x12C
    unsigned int Flags;                      // +0x140  (bit 0x100 = on-bridge)
};
GG_STATIC_ASSERT(offsetof(OccCellClass, OccupationFlags)    == 0x124);
GG_STATIC_ASSERT(offsetof(OccCellClass, AltOccupationFlags) == 0x128);
GG_STATIC_ASSERT(offsetof(OccCellClass, Flags)              == 0x140);

// MapClass singleton — the two retail helpers the (un)mark methods forward to,
// declared (no body) so cl emits relocatable __thiscall calls. The retail
// singleton object lives at the fixed address 0x0087F7E8.
struct MapClass
{
    OccCellClass* GetTargetCell(CoordStruct const& crd) const;     // 0x565730
    int           GetCellFloorHeight(CoordStruct const& crd) const; // 0x578080
};
#define MapInstance (reinterpret_cast<MapClass*>(0x0087F7E8))

// Bridge cell height delta added to the floor height before the on-bridge test.
#define BridgeCellHeight (*reinterpret_cast<int*>(0x00B1D0AC))

// ILocomotion is the canonical COM interface from loco_interfaces.h; slot 4
// is IsMoving, which this method dispatches through the FootClass member.
// _com_ptr_t<ILocomotion>::operator-> shape: NULL-check that raises E_POINTER,
// then returns the (reloaded) interface pointer. Defined inline so it folds into
// the call site exactly as retail's #import-generated smart pointer does.
extern void __stdcall _com_issue_error(long hr);   // retail 0x7DC720, not matched

struct ILocomotionPtr
{
    ILocomotion* m_pInterface;
    ILocomotion* operator->() const
    {
        if (m_pInterface == 0)
        {
            _com_issue_error(0x80004003);   // E_POINTER
        }
        return m_pInterface;
    }
};

// UnloadTimer::Start(double) — opens/begins the door transition (0x4A51F0,
// __thiscall taking the door angle by value). Declared (no body) so cl emits a
// relocatable __thiscall call.
struct DoorTimer
{
    void Start(double value);   // 0x4A51F0
};

// UnitClass : FootClass — only the UnitClass-specific Type pointer is new; every
// other touched member is reached through the FootClass / TechnoClass base.
struct UnitClass : FootClass
{
    int   CurrentFiringFrame;   // +0x6C0
    void* Type;                 // +0x6C4  (UnitTypeClass*)

    // FUNCTION: GAMEMD 0x740E80  UnitClass::APCOpenDoor             (__thiscall)
    void APCOpenDoor();
    // FUNCTION: GAMEMD 0x7441B0  UnitClass::MarkAllOccupationBits   (__thiscall)
    void MarkAllOccupationBits(CoordStruct const& coords);
    // FUNCTION: GAMEMD 0x744210  UnitClass::UnmarkAllOccupationBits (__thiscall)
    void UnmarkAllOccupationBits(CoordStruct const& coords);
};

GG_STATIC_ASSERT(offsetof(UnitClass, CurrentFiringFrame) == 0x6C0);
GG_STATIC_ASSERT(offsetof(UnitClass, Type)               == 0x6C4);

#endif  // GG_MATCH_MOVEMENT_UNIT_CLASS_OCCUPATION_METHODS_H
