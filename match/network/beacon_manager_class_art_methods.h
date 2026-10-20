// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals and offsets read off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x4309D0: two 0x24-byte file objects on the
//   frame built by 0x65CA80 (name) and torn down by 0x65CA00, read whole
//   through 0x4A3890 (ECX = the object), the
//   MixFileClass::Retrieve fallback 0x5B40B0 (ECX = name, DL = 0), the log
//   sink 0x4068E0, the SHP headers cached at 0x89C474 / 0x89C478 (YRpp
//   BeaconArt / RadarBeaconArt) and the manager's ints at +0x64..+0x7C read
//   from the header's three shorts at +2/+4/+6. YRpp (consult-only, no
//   LICENSE) names LoadArt.
#ifndef GG_MATCH_NETWORK_BEACON_MANAGER_CLASS_ART_METHODS_H
#define GG_MATCH_NETWORK_BEACON_MANAGER_CLASS_ART_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// An SHP header; only the three shorts after the leading word are read.
struct Shp_004309D0
{
    short Unused;   // +0x00
    short Width;    // +0x02
    short Height;   // +0x04
    short Frames;   // +0x06
};
GG_STATIC_ASSERT(offsetof(Shp_004309D0, Frames) == 0x06);

// GLOBAL: GAMEMD 0x89C474 — BeaconManagerClass::BeaconArt.
extern Shp_004309D0* DAT_0089C474;
// GLOBAL: GAMEMD 0x89C478 — BeaconManagerClass::RadarBeaconArt.
extern Shp_004309D0* DAT_0089C478;

// FUNCTION: GAMEMD 0x5B40B0 (decl; reloc) — MixFileClass::Retrieve.
Shp_004309D0* __fastcall FUN_005B40B0(const char* name, char force);
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) — the debug log sink.
void __cdecl FUN_004068E0(const char* text);

// The 0x24-byte file object. Modelled with explicit Construct / Destruct
// calls (a real constructor / destructor pair would bring an EH frame retail
// does not have).
struct File_004309D0
{
    char Body[0x24];         // +0x00

    // FUNCTION: GAMEMD 0x4A3890 (decl; reloc) — read the whole file.
    Shp_004309D0* ReadWholeFile();
};
GG_STATIC_ASSERT(sizeof(File_004309D0) == 0x24);

struct RawBase_004309D0
{
    // FUNCTION: GAMEMD 0x65CA80 (decl; reloc) — RawFileClass(const char*).
    void Construct(const char* name);
    // FUNCTION: GAMEMD 0x65CA00 (decl; reloc) — ~RawFileClass.
    void Destruct();
};

struct BeaconManager_004309D0
{
    char _pad0000[0x64];     // +0x0000
    int BeaconWidth;         // +0x0064
    int BeaconHeight;        // +0x0068
    int BeaconFrames;        // +0x006C
    int RadarWidth;          // +0x0070
    int RadarHeight;         // +0x0074
    int RadarFrames;         // +0x0078
    int RadarFramesX4;       // +0x007C

    // FUNCTION: GAMEMD 0x4309D0 — BeaconManagerClass::LoadArt.
    void LoadArt();
};
GG_STATIC_ASSERT(offsetof(BeaconManager_004309D0, BeaconWidth) == 0x64);
GG_STATIC_ASSERT(offsetof(BeaconManager_004309D0, RadarFramesX4) == 0x7C);

#endif  // GG_MATCH_NETWORK_BEACON_MANAGER_CLASS_ART_METHODS_H
