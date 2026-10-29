// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4C2A60.

#include "ebolt_fire_methods.h"
#include "../core/vector_class_operations.h"
#include "../core/vector_add_item_free.h"

// FUNCTION: GAMEMD 0x4C2A60
//
// Arm an electric bolt between two points: the endpoints and the colour index
// are stored, a random phase in [0, 0x100] is drawn, the bolt is appended to
// the global bolt list (inlined DynamicVectorClass::AddItem) and a particle
// system of the rules-supplied type is spawned at the far end.
void EBolt::Fire(CoordStruct from, CoordStruct to, int color)
{
    this->Point1 = from;
    this->Point2 = to;
    this->Color  = color;
    this->Phase  = DAT_00886B88.RandomRanged(0, 0x100);

    DynamicVectorAddItemFree(&DAT_008A0E88, this);

    ParticleSystem_004C2A60* ps =
        (ParticleSystem_004C2A60*)operator new(sizeof(ParticleSystem_004C2A60));
    if (ps != 0) {
        ps->Construct(DAT_008871E0->unknown_1020, &to, 0, 0, &DAT_008A0E50, 0);
    }
}
