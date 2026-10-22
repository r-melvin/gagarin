// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x4309D0.

#include "beacon_manager_class_art_methods.h"

// FUNCTION: GAMEMD 0x4309D0  BeaconManagerClass::LoadArt
//
// Load the two beacon shapes: try the loose file first, then the mix
// archives; on success cache the header's width, height and frame count
// (the radar one also keeps frames * 4), otherwise log the failure. The two
// file objects are declared at function scope in that order (beacon high,
// radar low); the fallback is `if (!art) art = Retrieve(); if (art) {...}
// else log` so the read path threads straight to the stores and the log
// block trails.
// STRING: GAMEMD 0x818A5C "PBEACON.SHP"   STRING: GAMEMD 0x818A40
// STRING: GAMEMD 0x818A30 "RDRBEACN.SHP"  STRING: GAMEMD 0x818A10
void BeaconManager_004309D0::LoadArt()
{
    File_004309D0 beacon;
    File_004309D0 radar;

    ((RawBase_004309D0*)&beacon)->Construct("PBEACON.SHP");
    DAT_0089C474 = beacon.ReadWholeFile();
    if (DAT_0089C474 == 0)
        DAT_0089C474 = FUN_005B40B0("PBEACON.SHP", 0);
    if (DAT_0089C474 != 0) {
        BeaconWidth = DAT_0089C474->Width;
        BeaconHeight = DAT_0089C474->Height;
        BeaconFrames = DAT_0089C474->Frames;
    } else {
        FUN_004068E0("Failed to load BeaconArt");
    }

    ((RawBase_004309D0*)&radar)->Construct("RDRBEACN.SHP");
    DAT_0089C478 = radar.ReadWholeFile();
    if (DAT_0089C478 == 0)
        DAT_0089C478 = FUN_005B40B0("RDRBEACN.SHP", 0);
    if (DAT_0089C478 != 0) {
        unknown_70 = DAT_0089C478->Width;
        unknown_74 = DAT_0089C478->Height;
        int frames = DAT_0089C478->Frames;
        RadarFrames = frames;
        RadarFramesX4 = frames << 2;
    } else {
        FUN_004068E0("Failed to load RadarBeaconArt");
    }

    ((RawBase_004309D0*)&radar)->Destruct();
    ((RawBase_004309D0*)&beacon)->Destruct();
}
