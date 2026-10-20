// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x46B280. Method name
//   from the consult-only YRpp BulletClass.h (name only).

#include "bullet_class_scalable_methods.h"

// FUNCTION: GAMEMD 0x46B280
//
// Registers this bullet in the global ScalableBullets list (an inlined
// AddItem, growing the vector through its virtual SetCapacity when full) and
// then derives the type's scaled spawn delay from the list population: the
// base SpawnDelay plus one frame for every three bullets beyond the fifth.
//
// The vector is reached through a pointer local rather than the global
// directly: with `&ScalableBullets` bound as AddItem's `this`, cl computes the
// grown capacity into ECX and loads the vtable into EAX before the pushes
// (`ADD ECX,EAX; MOV EAX,[vtbl]; PUSH 0; PUSH ECX`), which is the retail
// order; naming the global directly puts the sum in EAX and the vtable load
// after the pushes.
void BulletClass::InitScalable()
{
    DynVec_ScalableBullets* vec = &ScalableBullets;
    vec->AddItem(this);

    int extra = vec->Count - 5;
    if (extra < 0)
        extra = 0;

    this->Type->SetScaledSpawnDelay(this->Type->SpawnDelay + extra / 3);
}
