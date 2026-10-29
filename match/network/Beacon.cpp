// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit Beacon.CPP. The name is the source-file string at 0x818ad8
//   in retail gamemd.exe v1.001, passed by the assert at 0x430d11 inside this object's
//   code range (0x42ffa0-0x431b7f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// A small timing accumulator. Its neighbour at 0x4319D0 stores a start stamp
// at +0x00/+0x04 and adds an elapsed span into +0x08 while bumping +0x0C and
// +0x10; the two leaves below read and clear exactly those three dwords.
// The class name and member names are descriptive; no allocation site was
// found, so the object size is not asserted.
//
//   Names cross-checked against YRpp.
//
//   cross-checked against YRpp.

#include "../ai/slot_grid_find_methods.h"
#include "../core/mathtbl_init_shapes.h"

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class BenchTimer
{
public:
    void Reset();
    unsigned int Average();
    BenchTimer* FUN_004318F0();
    void FUN_00431930(int reset);
    void FUN_004319D0();

    unsigned int StartLo;   // +0x00
    unsigned int StartHi;   // +0x04
    unsigned int Total;     // +0x08
    unsigned int Count;     // +0x0C
    unsigned int Samples;   // +0x10
};
GG_STATIC_ASSERT(offsetof(BenchTimer, StartLo) == 0x00);
GG_STATIC_ASSERT(offsetof(BenchTimer, StartHi) == 0x04);
GG_STATIC_ASSERT(offsetof(BenchTimer, Total)   == 0x08);
GG_STATIC_ASSERT(offsetof(BenchTimer, Count)   == 0x0C);
GG_STATIC_ASSERT(offsetof(BenchTimer, Samples) == 0x10);

#include "../core/ctor_431b20_methods.h"

#include "../core/small_misc14_methods.h"

#include "beacon_class_methods.h"

#include "beacon_manager_class.h"

// Game memory free (cdecl, single pointer arg) @0x7C8B3D — `push p; call; add
// esp,4`. Declared (no body) so the harness reloc-normalises the call.
extern "C" void __cdecl GameDelete(void* pMem);

#include "beacon_manager_class_art_methods.h"
#include "../platform/ccfile_class.h"

#include "beacon_manager_class_draw_methods.h"

#include "trivial_tu029_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E3A18
extern const double DAT_007E3A18;
// GLOBAL: GAMEMD 0x89C398
extern double DAT_0089C398;

// SYNTHETIC: GAMEMD 0x0042FFD0
// dynamic initializer for DAT_0089C468
// GLOBAL: GAMEMD 0x0089C468
double DAT_0089C468 = DAT_0089C398 / DAT_007E3A18;

// SYNTHETIC: GAMEMD 0x0042FFF0
// dynamic initializer for DAT_0089C450
// GLOBAL: GAMEMD 0x0089C450
double DAT_0089C450 = 1.0 / DAT_0089C468;

GG_STATIC_ASSERT(sizeof(DAT_0089C468) == 8);
GG_STATIC_ASSERT(sizeof(DAT_0089C450) == 8);

// SYNTHETIC: GAMEMD 0x00430170
// dynamic initializer for DAT_0089C458
// GLOBAL: GAMEMD 0x0089C458
MathTblCoord DAT_0089C458;
GG_STATIC_ASSERT(sizeof(DAT_0089C458) == 0xC);

// FUNCTION: GAMEMD 0x430580
// Empty function that pops its stack arguments.
void __stdcall FUN_00430580(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
}

// FUNCTION: GAMEMD 0x430600
// Empty function.
void __cdecl FUN_00430600()
{
}

// FUNCTION: GAMEMD 0x430610
// Updates one member in place.
void Obj_00430610::FUN_00430610()
{
    unknown_0C &= 0xFE;
}

// FUNCTION: GAMEMD 0x4308B0  (__thiscall)
// Visible iff the beacon's bit-0 flag is set, the local player is allied with
// the beacon's owning house (by index), that house is allied back with the
// player, and the house's +0x1F5 flag is clear. Each link short-circuits to a
// false return; the trailing flag is reloaded through the Array global because
// the intervening alliance call may alias it.
bool BeaconClass::VisibleToPlayer() const
{
    if (this->Bitfield & 1) {
        if (HouseClass_CurrentPlayer->IsAlliedWith(this->HouseID)) {
            if (HouseClass_ArrayItems[this->HouseID]->IsAlliedWith(HouseClass_CurrentPlayer)) {
                if (HouseClass_ArrayItems[this->HouseID]->Defeated == 0)
                    return true;
            }
        }
    }
    return false;
}

// Free every live beacon pointer and zero the count; skipped entirely when no
// beacons are allocated. Expanded into both the destructor and Reset.
static __forceinline void ReleaseBeacons(BeaconManagerClass* manager)
{
    if (manager->AllocatedCount != 0)
    {
        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (manager->Beacons[i][j] != 0)
                {
                    GameDelete(manager->Beacons[i][j]);
                    manager->Beacons[i][j] = 0;
                }
            }
        }
        manager->AllocatedCount = 0;
    }
}

// FUNCTION: GAMEMD 0x430930
BeaconManagerClass::~BeaconManagerClass()
{
    ReleaseBeacons(this);
}

// The constructor is expanded into the instance's initialiser (0x430190).
inline BeaconManagerClass::BeaconManagerClass()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            Beacons[i][j] = 0;
        }
    }
    AllocatedCount = 0;
    RadarBeaconAnimPeriod = 0;
}

// SYNTHETIC: GAMEMD 0x430190
// SYNTHETIC: GAMEMD 0x4301C0 -- exit-time destructor stub
// GLOBAL: GAMEMD 0x89C3B0
BeaconManagerClass DAT_0089C3B0;

// FUNCTION: GAMEMD 0x430980  (__thiscall)
void BeaconManagerClass::Reset()
{
    ReleaseBeacons(this);
}

// FUNCTION: GAMEMD 0x4309D0  BeaconManagerClass::LoadArt
//
// Load the two beacon shapes: try the loose file first, then the mix
// archives; on success cache the header's width, height and frame count
// (the radar one also keeps frames * 4), otherwise log the failure. The two
// RawFileClass objects are declared in that order (beacon high,
// radar low); the fallback is `if (!art) art = Retrieve(); if (art) {...}
// else log` so the read path threads straight to the stores and the log
// block trails.
// STRING: GAMEMD 0x818A5C "PBEACON.SHP"   STRING: GAMEMD 0x818A40
// STRING: GAMEMD 0x818A30 "RDRBEACN.SHP"  STRING: GAMEMD 0x818A10
void BeaconManager_004309D0::LoadArt()
{
    RawFileClass beacon("PBEACON.SHP");
    DAT_0089C474 = (Shp_004309D0*)beacon.ReadWholeFile();
    if (DAT_0089C474 == 0)
        DAT_0089C474 = FUN_005B40B0("PBEACON.SHP", 0);
    if (DAT_0089C474 != 0) {
        BeaconWidth = DAT_0089C474->Width;
        BeaconHeight = DAT_0089C474->Height;
        BeaconFrames = DAT_0089C474->Frames;
    } else {
        FUN_004068E0("Failed to load BeaconArt");
    }

    RawFileClass radar("RDRBEACN.SHP");
    DAT_0089C478 = (Shp_004309D0*)radar.ReadWholeFile();
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
}

// FUNCTION: GAMEMD 0x430AC0  BeaconManagerClass::Draw
//
// Draw every placed beacon whose owning house the current player is allied
// with (both ways) and which is not in the +0x1F5 state. Nothing is drawn
// while no beacon is allocated. The loops are plain counted-up indexes into
// the 8x3 table: VC6 strength-reduces them into one walking pointer kept in
// the `this` register and two down-counters on the frame. An explicit
// walking pointer gets a caller-saved register and a spill (14.9%).
void BeaconManager_00430AC0::Draw(Surface_00430AC0* surface, Rect_00430AC0 bounds)
{
    if (AllocatedCount != 0) {
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 3; ++col) {
                Beacon_00430AC0* beacon = Beacons[row][col];
                if (beacon != 0 && (beacon->Flags & 1)
                    && DAT_00A83D4C->IsAlliedWith(beacon->HouseIndex)
                    && DAT_00A8022C[beacon->HouseIndex]->IsAlliedWith(DAT_00A83D4C)
                    && DAT_00A8022C[beacon->HouseIndex]->Defeated == 0) {
                    beacon->Draw(surface, bounds);
                }
            }
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x431060
// Clear bit 1 on every live slot - eight groups of three, walked as one
// pointer. The whole sweep is skipped unless the field at +0x60 is set.
void Obj_00431060::FUN_00431060()
{
    if (unknown_60 == 0) {
        return;
    }

    Flagged_00431060** slot = Slots;

    for (int group = 8; group != 0; group--) {
        for (int i = 3; i != 0; i--) {
            if (*slot) {
                (*slot)->at0C &= ~2;
            }

            slot++;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x431170
//
// Find the first eligible entry in the grid, optionally matching a key. A key of
// -1 means "any", which is why that test short-circuits ahead of the comparison
// against the entry's own key.
//
// The whole search is skipped when +0x60 is clear — the guard is on the object,
// not on the grid contents, so an empty grid is not the same as a disabled one.
Entry_00431170* Grid_00431170::FUN_00431170(int key)
{
    if (this->At_60 == 0) {
        return 0;
    }

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 3; col++) {
            Entry_00431170* entry = this->Slots[row][col];
            if (entry != 0 && (entry->Flags & 2)
                && (key == -1 || key == entry->Key)) {
                return entry;
            }
        }
    }

    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// FUNCTION: GAMEMD 0x7C6064 (decl; reloc) -- RDTSC helper: returns the low half, stores the high half.
unsigned int __cdecl FUN_007C6064(unsigned int* high);

// FUNCTION: GAMEMD 0x4318F0
// Stamps the start time (counter shifted right by 4) and clears the totals.
BenchTimer* BenchTimer::FUN_004318F0()
{
    unsigned int hi;
    StartLo = FUN_007C6064(&hi) >> 4 | hi << 28;
    Total = 0;
    Count = 0;
    Samples = 0;
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x431920
void BenchTimer::Reset()
{
    Total = 0;
    Count = 0;
    Samples = 0;
}

// FUNCTION: GAMEMD 0x431930
// Stamps the start time, optionally clearing the totals first.
void BenchTimer::FUN_00431930(int reset)
{
    unsigned __int64 stale;
    if ((char)reset) {
        Total = 0;
        Count = 0;
        Samples = 0;
    }
    unsigned int lo = FUN_007C6064((unsigned int*)&reset);
    StartLo = lo >> 4 | reset << 28;
    StartHi = (unsigned int)(stale >> 32);
}

// FUNCTION: GAMEMD 0x4319D0
// Adds the time since the start stamp to the total and bumps both counters.
void BenchTimer::FUN_004319D0()
{
    unsigned int hi;
    unsigned int lo = FUN_007C6064(&hi);
    Total += (lo >> 4 | hi << 28) - StartLo;
    Count++;
    Samples++;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x431A10
unsigned int BenchTimer::Average()
{
    if (Count != 0) {
        return Total / Count;
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x431B20
Obj_00431B20* Obj_00431B20::FUN_00431B20()
{
    field_04 = 0;
    field_08 = 1;
    field_0C = 0;
    field_10 = -1;
    field_14 = -1;
    field_18 = 0;
    field_1C = 0;
    field_1E = 0;
    field_20 = 0;
    field_24 = 0;
    field_25 = 0;
    field_26 = 0;
    field_27 = 0;
    field_28 = 0;
    field_29 = 0;
    field_2C = 0;
    field_30 = 0;
    field_34 = 0;
    field_38 = 0;
    field_3C = 0;
    field_40 = -1;
    field_44 = -1;
    field_48 = 0;
    field_4C = 0;
    field_50 = 0;

    Vtable = &VT_007E3A2C;

    return this;
}
