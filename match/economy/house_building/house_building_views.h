// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Sparse views of retail objects outside the module that more than one house/building cluster reads,
//   declared once with the union of the members the clusters use. Every field is a [reg+disp] operand
//   read from the retail gamemd.exe v1.001; the views are NOT the canonical classes.
//
//   The COM secondary bases live in house_building_com_bases.h (they need the SDK headers, which the
//   BuildingClass clusters do not include).
//
//   Kept separate on purpose (each cluster header says so at the type):
//   - The five BuildingClass views (BuildingAView, BA2Building, BuildingA3View, BA4Building, BuildingBView)
//     and their neighbour views (object / techno / type / house). Their member offsets agree (each view
//     asserts them against house_building_layout.h), but 48 primary-table slots are declared with
//     different signatures (a hidden-pointer return spelled as a by-value return, a pointer parameter
//     typed as another cluster's view, void against int returns). One merged class would need one
//     signature per slot, and the right one is the canonical TechnoClass declaration, which is
//     not yet in the tree; choosing now would rewrite the call sites of every capped body.
//   - building-a2's facing (BA2Dir): unsigned 16-bit half (MOVZX against MOVSX).
//   - building-a2's random generator (BA2Counter): FUN_0065C780 returns unsigned char there, unsigned int
//     in HBCounterView (a different return type is a different call-site extension).
//   - The cluster timers (BA2Timer, BA3Timer, BuildingBTimer, HouseTimer): different constructors and
//     inline GetTimeLeft bodies that the bodies depend on.
//   - The target references and events (BATargetRef, BA3TargetRef, BA4TargetRef, BAEvent, BA3Event,
//     BAEventQueue, BA3EventQueue): their constructors take the cluster's own BuildingClass view.
//   - TypesPoint2D (types): its constructors change how an 8-byte value is returned (EDX:EAX against a
//     hidden pointer), so it is not HBPoint2D.
//   - HBCoordPod (common types): building-a4 needs the constructor-less coordinate.
#ifndef GG_MATCH_ECONOMY_HOUSE_BUILDING_HOUSE_BUILDING_VIEWS_H
#define GG_MATCH_ECONOMY_HOUSE_BUILDING_HOUSE_BUILDING_VIEWS_H

#include "house_building_common_types.h"

// The random generator embedded in the source object at +0x218 (partial).
struct HBCounterView
{
    // FUNCTION: GAMEMD 0x65C7E0 (read-only here) - a value in [low, high].
    int FUN_0065C7E0(int low, int high);
    // FUNCTION: GAMEMD 0x65C780 (read-only here)
    unsigned int FUN_0065C780();
};

// Object behind the global at 0xA8B230 (partial).
struct HBSourceView
{
    char _pad_0000[0x218];   // +0x0000
    HBCounterView Counter;   // +0x0218
};
GG_STATIC_ASSERT(offsetof(HBSourceView, Counter) == 0x218);

// What FUN_005B3A00 returns (partial).
struct HBPriceView
{
    char _pad_0000[0x10];   // +0x0000
    double unknown_10;      // +0x0010
    double unknown_18;      // +0x0018
};
GG_STATIC_ASSERT(offsetof(HBPriceView, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(HBPriceView, unknown_18) == 0x18);

// Third link of the index chain (entry of 0xA83CBC -> +0x28 -> +0xC8 -> +0xDF8).
struct HBIdx3View
{
    char _pad_0000[0xDF8];   // +0x0000
    int unknown_DF8;         // +0x0DF8
};
GG_STATIC_ASSERT(offsetof(HBIdx3View, unknown_DF8) == 0xDF8);

// Second link of the index chain (partial).
struct HBIdx2View
{
    char _pad_0000[0xC8];    // +0x0000
    HBIdx3View* unknown_C8;  // +0x00C8
};
GG_STATIC_ASSERT(offsetof(HBIdx2View, unknown_C8) == 0xC8);

// Entry of the global index array at 0xA83CBC (partial).
struct HBIdxView
{
    char _pad_0000[0x28];    // +0x0000
    HBIdx2View* unknown_28;  // +0x0028
};
GG_STATIC_ASSERT(offsetof(HBIdxView, unknown_28) == 0x28);

// Member of the owning house at +0x5550 (partial).
struct HBListView
{
    // FUNCTION: GAMEMD 0x49FAE0 (read-only here)
    int FUN_0049FAE0(int value);
};

// An object whose method turns one pair into another (the global at 0x887324 is a pointer to it).
struct HBPairXformView
{
    // FUNCTION: GAMEMD 0x6D2070 (read-only here)
    HBPoint2D* FUN_006D2070(HBPoint2D* out, HBPoint2D* in);
};

#endif
