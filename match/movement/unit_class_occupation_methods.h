// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
//   UnitClass : FootClass (FootClass sizeof = 0x6C0; spine in../_layout).
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
#include "../_layout/unit_class.h"   // canonical UnitClass (FootClass spine, CoordStruct, CellStruct)
#include "loco_interfaces.h"
#include "loco_com.h"

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

// Address-local implementation view used only by the occupation methods below;
// this placeholder is not a recovered original class name. The two retail
// helpers are declared without bodies so cl emits relocatable __thiscall calls.
class UnitOccupationMapView
{
public:
    OccCellClass* GetTargetCell(CoordStruct const& crd) const;     // 0x565730
    int           GetCellFloorHeight(CoordStruct const& crd) const; // 0x578080
};
#define MapInstance (reinterpret_cast<UnitOccupationMapView*>(0x0087F7E8))

// Bridge cell height delta added to the floor height before the on-bridge test.
#define BridgeCellHeight (*reinterpret_cast<int*>(0x00B1D0AC))

// ILocomotionPtr is the canonical _com_ptr_t from loco_com.h; its operator-> carries the
// NULL-check that raises E_POINTER through retail 0x7DC720. Slot 4 is IsMoving, which
// this method dispatches through the FootClass member.
// UnloadTimer::Start(double) — opens/begins the door transition (0x4A51F0,
// __thiscall taking the door angle by value). Declared (no body) so cl emits a
// relocatable __thiscall call.
struct DoorTimer
{
    void Start(double value);   // 0x4A51F0
};

#endif  // GG_MATCH_MOVEMENT_UNIT_CLASS_OCCUPATION_METHODS_H
