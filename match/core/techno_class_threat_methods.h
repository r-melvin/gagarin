// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets + control flow derived from the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI (member-access disassembly at 0x70F6E0-0x70F72E,
//   len 0x4F). Names cross-checked against YRpp
//   (UpdateThreatInCell @0x70F6E0; ThreatPosed @0x508; consult-only, no LICENSE;
//   every offset/vtable slot reconfirmed numerically from the disasm below).
//   ThreatPosed @0x508 agrees with the committed spine
//   match/_layout/techno_class.h.
//
// TechnoClass::UpdateThreatInCell — re-stamp this object's threat contribution
// into a cell's per-house threat map: first subtract the old ThreatPosed
// (Cell->AddThreat(GetOwningHouse(), -ThreatPosed)), zero ThreatPosed, recompute
// it via the threat-evaluation virtual (vtable slot +0x2C0), store the new
// value, then add it back (Cell->AddThreat(GetOwningHouse(), ThreatPosed)).
// GetOwningHouse() is the const virtual at primary-vtable slot +0x38.
#ifndef GG_MATCH_CORE_TECHNO_CLASS_THREAT_METHODS_H
#define GG_MATCH_CORE_TECHNO_CLASS_THREAT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class TechnoClass;
class HouseClass;
struct TechnoVtbl;

// Retail helper @0x481870 — the per-house threat-map mutator invoked through the
// cell. It is a direct CALL with the cell in ECX and no stack cleanup after it,
// so it is an ordinary __thiscall member taking two pushed arguments; the
// compiler rejects the receiver convention on a free function, so it is
// declared (never defined) as a member of the cell.
class CellClass
{
public:
    // FUNCTION: GAMEMD 0x481870 (decl; reloc) — CellClass::AddThreat
    void AddThreat(HouseClass* pHouse, int threat);
};

// ---------------------------------------------------------------------------
// TechnoClass — minimal offset-pinned model for UpdateThreatInCell. The pad gap
// stands in for the full RadioClass/MissionClass/ObjectClass/TechnoClass spine
// (match/_layout/techno_class.h); only the primary vptr and ThreatPosed @0x508
// are modelled. The two virtual dispatches (slots +0x38 / +0x2C0) are written as
// ordinary member-pointer calls through the modelled vtable struct.
// ---------------------------------------------------------------------------
class TechnoClass
{
public:
    // FUNCTION: GAMEMD 0x70F6E0  (__thiscall)
    void UpdateThreatInCell(CellClass* Cell);

    TechnoVtbl*  Vfptr;                   // +0x000
    char         _pad_004[0x508 - 0x004]; // +0x004 .. +0x507
    int          ThreatPosed;             // +0x508
};

GG_STATIC_ASSERT(offsetof(TechnoClass, Vfptr)       == 0x000);
GG_STATIC_ASSERT(offsetof(TechnoClass, ThreatPosed) == 0x508);

// The class has to be complete before these typedefs, or VC6 falls back to the
// multiple-inheritance member-pointer form and emits a `this` adjustment.
typedef HouseClass* (TechnoClass::*GetOwningHouseFn)();
typedef int         (TechnoClass::*CalculateThreatFn)();

// Primary vtable slots reached from this TU.
//   +0x038  GetOwningHouse()   no arguments, the owning house
//   +0x2C0  CalculateThreat()  no arguments, the recomputed threat value
struct TechnoVtbl
{
    char              _pad_000[0x038];          // 0x000
    GetOwningHouseFn  At_38;                    // 0x038
    char              _pad_03C[0x2C0 - 0x03C];  // 0x03C
    CalculateThreatFn At_2C0;                   // 0x2C0
};
GG_STATIC_ASSERT(offsetof(TechnoVtbl, At_38)  == 0x038);
GG_STATIC_ASSERT(offsetof(TechnoVtbl, At_2C0) == 0x2C0);

#endif  // GG_MATCH_CORE_TECHNO_CLASS_THREAT_METHODS_H
