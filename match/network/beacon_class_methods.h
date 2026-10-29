// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x4308B0), cross-checked against
//   YRpp (reconfirmed numerically
//   from the disassembly here).
//
// BeaconClass — a single map/radar beacon dropped by a player. VisibleToPlayer
// gates display on the beacon's bit-0 flag and a two-way alliance check between
// the local player and the beacon's owning house.
#ifndef GG_MATCH_NETWORK_BEACON_CLASS_METHODS_H
#define GG_MATCH_NETWORK_BEACON_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/coord_struct.h"
#include "../_layout/house_class.h"

// ---------------------------------------------------------------------------
// HouseClass — only the bits VisibleToPlayer touches are modelled here. Both
// IsAlliedWith overloads are the retail callees at 0x4F9A10 / 0x4F9A50 (declared
// without bodies so cl emits a normalised call reloc).


#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(HouseClass, Defeated) == 0x1F5);
#endif

// Retail globals (absolute-address reads; the diff harness normalises the
// relocations). 0xA83D4C is the local player; 0xA8022C is the live Items[]
// pointer of HouseClass::Array (read then indexed by house id).
extern HouseClass*  HouseClass_CurrentPlayer;   // [0x00A83D4C]
extern HouseClass** HouseClass_ArrayItems;      // [0x00A8022C]

// ---------------------------------------------------------------------------
// BeaconClass. The bitfield at +0xC and the owning house id at +0x110 are the
// only members VisibleToPlayer reads; the rest of the layout (Coord, Text[128])
// is padded and decomposed in P2.
struct BeaconClass
{
    bool VisibleToPlayer() const;          // GAMEMD 0x4308B0 __thiscall
    BeaconClass();                         // GAMEMD 0x430210 __thiscall

    CoordStruct   Coord;                   // +0x00
    unsigned char Bitfield;                // +0x0C  (bit 0 = active/visible)
    char          _gap0D[0x110 - 0x0D];    // [0x0D..0x10F] (Text[128] etc.) — P2
    int           HouseID;                 // +0x110
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(BeaconClass, Bitfield) == 0x0C);
GG_STATIC_ASSERT(offsetof(BeaconClass, HouseID)  == 0x110);
#endif

#endif  // GG_MATCH_NETWORK_BEACON_CLASS_METHODS_H
