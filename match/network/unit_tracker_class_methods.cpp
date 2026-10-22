// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | behaviour-confirmed-name
//   Bytes matched against retail gamemd.exe v1.001 at 0x749020 / 0x749060 /
//   0x7490A0 / 0x7490C0 / 0x7490D0 via the local Ghidra disassembly. Layout
//   confirmed numerically (see the header).
//
// UnitTrackerClass — multiplayer unit-production tally. Functions ordered
// ascending by retail address.

#include "unit_tracker_class_methods.h"

// FUNCTION: GAMEMD 0x749020  UnitTrackerClass::IncrementUnitTotal (__thiscall, ret 0x4)
// Note the retail bound check is one-sided (`CMP EAX,EDX; JGE skip`) — a
// negative unit type indexes below the table rather than being rejected.
void UnitTrackerClass::IncrementUnitTotal(int unitType)
{
    if (unitType < UnitCount) {
        UnitTotals[unitType]++;
    }
}

// FUNCTION: GAMEMD 0x749060  UnitTrackerClass::Init (__thiscall, ret 0x4)
// Widen the count to the full table, zero every slot, then narrow it to the
// caller's count. The clear loop is written out here rather than delegating to
// ClearUnitTotal: retail has no call, and it reloads UnitCount each iteration
// exactly as the standalone clear does.
//
// NOTE: `Init` is a descriptive placeholder name — the binary attests no
// name for this address. Retail's constructor is a different, inlined sequence
// at 0x748FD7 (it also zeroes InNetworkFormat and returns `this` in EAX, which
// this does not), so the two are not the same function.
void UnitTrackerClass::Init(int unitCount)
{
    UnitCount = UNIT_TRACKER_MAX_TYPES;
    for (int i = 0; i < UnitCount; i++) {
        UnitTotals[i] = 0;
    }
    UnitCount = unitCount;
}

// FUNCTION: GAMEMD 0x7490A0  UnitTrackerClass::GetTotalOfAll (__thiscall)
int UnitTrackerClass::GetTotalOfAll()
{
    int total = 0;
    for (int i = 0; i < UnitCount; i++) {
        total += UnitTotals[i];
    }
    return total;
}

// FUNCTION: GAMEMD 0x7490C0  UnitTrackerClass::GetAllTotals (__thiscall)
// The table is the object, so this is `MOV EAX,ECX; RET`.
int* UnitTrackerClass::GetAllTotals()
{
    return UnitTotals;
}

// FUNCTION: GAMEMD 0x7490D0  UnitTrackerClass::ClearUnitTotal (__thiscall)
void UnitTrackerClass::ClearUnitTotal()
{
    for (int i = 0; i < UnitCount; i++) {
        UnitTotals[i] = 0;
    }
}
