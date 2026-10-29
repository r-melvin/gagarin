// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Canonical MSEngine (the map-stage screen engine; base of MapSelect). Read from the retail gamemd.exe v1.001:
//   RTTI .?AVMSEngine@@ (no base), vtable 0x7EEBD4: slot 0 0x5D2700 (scalar deleting destructor), slot 1 0x5AE590,
//   slot 2 0x5D26F0 (empty). Constructor 0x5D1AA0 builds, in order, a VectorClass<TRect<int>> at +0x08 (vtable
//   0x7ED970, then SetCapacity(0x14, 0)), a DynamicVectorClass<MSAnim*> at +0x18 (0x7EEC04, increment 10) and a
//   DynamicVectorClass<MSSfx*> at +0x30 (0x7EEBE4, increment 10), stores the vptr, clears +0x04 and empties both
//   dynamic vectors. Destructor 0x5D1B30 destroys every MSSfx (its destructor 0x5D5850, then operator delete),
//   clears that vector, deletes every MSAnim through its slot-0 deleting destructor, clears that vector and runs
//   the inlined vector destructors. MapSelect (members from +0x50) derives from it, so sizeof(MSEngine) == 0x50.
#ifndef GG_MATCH_LAYOUT_MS_ENGINE_H
#define GG_MATCH_LAYOUT_MS_ENGINE_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/vector_class.h"
#include "geometry2d.h"
#include "ms_anim.h"

// A sound effect owned by the engine; only its out-of-line destructor is attested here.
class MSSfx
{
public:
    // FUNCTION: GAMEMD 0x5D5850 (decl; reloc)
    ~MSSfx();
};

// VTABLE: GAMEMD 0x7EEBD4
class MSEngine
{
public:
    // FUNCTION: GAMEMD 0x5D1AA0
    MSEngine();
    virtual ~MSEngine();            // slot 0, 0x5D2700 (scalar deleting); body 0x5D1B30
    virtual void Slot1(int a);          // slot 1, 0x5AE590 (RET 4)
    virtual void Slot2();               // slot 2, 0x5D26F0 (empty)

    int Field04;                              // +0x04
    VectorClass<TRect<int> > Rects;           // +0x08
    DynamicVectorClass<MSAnim*> Anims;        // +0x18
    DynamicVectorClass<MSSfx*> Sfxs;          // +0x30
    char unknown_48[8];                       // +0x48
};
GG_STATIC_ASSERT(offsetof(MSEngine, Rects) == 0x08
              && offsetof(MSEngine, Anims) == 0x18
              && offsetof(MSEngine, Sfxs) == 0x30
              && sizeof(MSEngine) == 0x50);

#endif  // GG_MATCH_LAYOUT_MS_ENGINE_H
