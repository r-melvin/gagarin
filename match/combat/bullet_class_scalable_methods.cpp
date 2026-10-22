// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x46B280. Method name
//   from YRpp (name only).

#include "bullet_class_scalable_methods.h"

// FUNCTION: GAMEMD 0x46B280
//
// Registers this bullet in the global ScalableBullets list (an inlined
// AddItem, growing the vector through its virtual SetCapacity when full) and
// then derives the type's scaled spawn delay from the list population: the
// base SpawnDelay plus one frame for every three bullets beyond the fifth.
void BulletClass::InitScalable()
{
    ScalableBullets.AddItem(this);

    int extra = ScalableBullets.Count - 5;
    if (extra < 0)
        extra = 0;

    this->Type->SetScaledSpawnDelay(this->Type->SpawnDelay + extra / 3);
}
