// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp BeaconManagerClass.h (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x430980  BeaconManagerClass::Reset            (__thiscall)
//   FUNCTION: GAMEMD 0x430F30  BeaconManagerClass::CanPlaceBeacon   (__thiscall)
//   FUNCTION: GAMEMD 0x431410  BeaconManagerClass::DeleteAllBeacons (__thiscall)

#include "beacon_manager_class.h"

// Game memory free (cdecl, single pointer arg) @0x7C8B3D — `push p; call; add
// esp,4`. Declared (no body) so the harness reloc-normalises the call.
extern "C" void __cdecl GameDelete(void* pMem);

// FUNCTION: GAMEMD 0x430980  (__thiscall)
// Free every live beacon pointer and zero the count. Skips entirely when no
// beacons are allocated.
void BeaconManagerClass::Reset()
{
    if (AllocatedCount != 0)
    {
        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (Beacons[i][j] != 0)
                {
                    GameDelete(Beacons[i][j]);
                    Beacons[i][j] = 0;
                }
            }
        }
        AllocatedCount = 0;
    }
}

// FUNCTION: GAMEMD 0x430F30  (__thiscall)
// True if the house has a free beacon slot (one of its three is empty).
bool BeaconManagerClass::CanPlaceBeacon(int houseId)
{
    for (int i = 0; i < 3; ++i)
    {
        if (Beacons[houseId][i] == 0)
        {
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x431410  (__thiscall)
// Delete all three beacons owned by a house. Skips when nothing is allocated.
void BeaconManagerClass::DeleteAllBeacons(int houseId)
{
    if (AllocatedCount != 0)
    {
        for (int i = 0; i < 3; ++i)
        {
            if (Beacons[houseId][i] != 0)
            {
                DeleteBeacon(houseId, i);
            }
        }
    }
}
