// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail evidence: the RTTI name ".?AV?$DynamicVectorClass@PAUKamikazeControl@@@@"
//   (vtable 0x7ECE7C) types the node list; the single global instance sits at
//   0xABC5F8 (initialiser 0x54E260 stores the frame counter and 100 into the
//   timer, builds the vector at 0xABC604 and registers the exit stub 0x54E2D0);
//   the constructor body 0x54E360 and destructor body 0x54E690 are the
//   out-of-line copies of what the initialiser and exit stub expand inline.
//   Size 0x24: CDTimerClass (0xC) then the 0x18-byte vector.
//
// Kamikaze -- the suicide-aircraft manager: a frame-counted update timer plus a
// vector of KamikazeControl nodes (one per aircraft and the target it dives at).
#ifndef GG_MATCH_LAYOUT_KAMIKAZE_CLASS_H
#define GG_MATCH_LAYOUT_KAMIKAZE_CLASS_H

#include <stddef.h>
#include <objidl.h>
#include "../_rt/gg_static_assert.h"
#include "frame_timer.h"
#include "../core/vector_class.h"

class AircraftClass;
class AbstractClass;

// One suicide aircraft and its target (null = fly straight ahead): 8 bytes.
struct KamikazeControl
{
    AircraftClass* Item;     // +0x00
    AbstractClass* Target;   // +0x04
};
GG_STATIC_ASSERT(offsetof(KamikazeControl, Target) == 0x04);
GG_STATIC_ASSERT(sizeof(KamikazeControl) == 8);

class Kamikaze
{
public:
    // FUNCTION: GAMEMD 0x54E360 (out-of-line copy; the global's initialiser inlines it)
    Kamikaze();
    // FUNCTION: GAMEMD 0x54E690 (out-of-line copy; the global's exit stub inlines it)
    ~Kamikaze();

    // FUNCTION: GAMEMD 0x54E4D0
    void Update();
    // FUNCTION: GAMEMD 0x54E6F0
    void Clear();
    // FUNCTION: GAMEMD 0x54E750
    HRESULT Save(IStream* pStm);
    // FUNCTION: GAMEMD 0x54E7B0
    HRESULT Load(IStream* pStm);

    CDTimerClass UpdateTimer;                     // +0x00
    DynamicVectorClass<KamikazeControl*> Nodes;   // +0x0C
};
GG_STATIC_ASSERT(offsetof(Kamikaze, UpdateTimer) == 0x00);
GG_STATIC_ASSERT(offsetof(Kamikaze, Nodes) == 0x0C);
GG_STATIC_ASSERT(sizeof(Kamikaze) == 0x24);

// GLOBAL: GAMEMD 0xABC5F8 -- the kamikaze manager instance.
extern Kamikaze DAT_00ABC5F8;

#endif  // GG_MATCH_LAYOUT_KAMIKAZE_CLASS_H
