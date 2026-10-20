// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp HouseClass.h::UnitTrackerClass (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x749060  UnitTrackerClass::PopulateUnitCount (__thiscall)
//   FUNCTION: GAMEMD 0x749100  UnitTrackerClass::ToNetworkFormat   (__thiscall)
//   FUNCTION: GAMEMD 0x749150  UnitTrackerClass::ToPCFormat        (__thiscall)

#include "house_class_net_methods.h"

// FUNCTION: GAMEMD 0x749100  (__thiscall)
// Byte-swap every live counter to network order (host->net), then mark the
// tracker as wire-formatted. Idempotent: a no-op if already in network form.
void UnitTrackerClass::ToNetworkFormat()
{
    if (!this->InNetworkFormat)
    {
        for (int i = 0; i < this->UnitCount; i++)
            this->UnitTotals[i] = htonl(this->UnitTotals[i]);
    }
    this->InNetworkFormat = 1;
}

// FUNCTION: GAMEMD 0x749150  (__thiscall)
// Byte-swap every live counter back to host order (net->host), then clear the
// wire flag. A no-op if the tracker is not currently in network form.
void UnitTrackerClass::ToPCFormat()
{
    if (this->InNetworkFormat)
    {
        for (int i = 0; i < this->UnitCount; i++)
            this->UnitTotals[i] = ntohl(this->UnitTotals[i]);
    }
    this->InNetworkFormat = 0;
}
