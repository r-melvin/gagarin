// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   Kamikaze's constructor 0x54E360 and destructor 0x54E690 are called by
//   nothing: the global's initialiser 0x54E260 and its exit stub 0x54E2D0 carry
//   the same bodies inline (/Ob2 expands the out-of-line functions into them).

#include "../_layout/kamikaze_class.h"
#include "../core/vector_class_operations.h"

// FUNCTION: GAMEMD 0x54E360
//
// A fresh manager: the update timer set to 100 frames and an empty node list.
Kamikaze::Kamikaze()
    : UpdateTimer(0)
{
    UpdateTimer = CDTimerClass(100);
}

// FUNCTION: GAMEMD 0x54E690
//
// Free every node back-to-front and release the node list's storage.
//
// PARTIAL: 73.2% -- retail keeps `this` in EDI and the loop counter in ESI; ours
// swaps the two (the same delta as Kamikaze::Clear). A local `Nodes` pointer
// alias reaches 100% but is steering, so the plain form is kept.
Kamikaze::~Kamikaze()
{
    for (int i = Nodes.Count - 1; i >= 0; --i)
        delete Nodes.Items[i];
    int cap = Nodes.Capacity;
    Nodes.Clear();
    Nodes.SetCapacity(cap, 0);
}

// SYNTHETIC: GAMEMD 0x54E260 -- run-time initialiser of DAT_00ABC5F8
// SYNTHETIC: GAMEMD 0x54E2D0 -- exit-time destructor stub of DAT_00ABC5F8
// GLOBAL: GAMEMD 0xABC5F8
Kamikaze DAT_00ABC5F8;

// Retail 54E695/69B/B5/C6/D3/E7 read Count, Items, Capacity and ownership.
GG_STATIC_ASSERT(offsetof(Kamikaze, Nodes.Items) == 0x10);
GG_STATIC_ASSERT(offsetof(Kamikaze, Nodes.Capacity) == 0x14);
GG_STATIC_ASSERT(offsetof(Kamikaze, Nodes.IsAllocated) == 0x19);
GG_STATIC_ASSERT(offsetof(Kamikaze, Nodes.Count) == 0x1C);
GG_STATIC_ASSERT(sizeof(((Kamikaze*)0)->Nodes) == 0x18);
