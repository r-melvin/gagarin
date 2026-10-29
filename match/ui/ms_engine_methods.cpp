// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x5D1AA0 (constructor), 0x5D1B30 (destructor) and 0x5D2700 (scalar deleting
//   destructor); RTTI .?AVMSEngine@@ (vtable 0x7EEBD4); layout in match/_layout/ms_engine.h.
#include "../core/vector_class_operations.h"
#include "../_layout/ms_engine.h"

// FUNCTION: GAMEMD 0x5D1AA0
// Reserve room for twenty rectangles and start with no animations or sound effects.
MSEngine::MSEngine()
{
    DirtyRectCount = 0;
    Rects.SetCapacity(0x14, 0);
    Anims.Clear();
    Sfxs.Clear();
}

// FUNCTION: GAMEMD 0x5D1B30
// PARTIAL: 96.7% -- same instructions as retail; cl stores the vtable pointer after loading the first vector's
// count and pushing EDI, where retail stores it first (the same swap as LoadOptionsClass::~LoadOptionsClass).
// Destroy every sound effect, then every animation, then the vectors themselves.
MSEngine::~MSEngine()
{
    for (int i = 0; i < Sfxs.Count; ++i)
        delete Sfxs.Items[i];
    Sfxs.Clear();
    for (int j = 0; j < Anims.Count; ++j)
        delete Anims.Items[j];
    Anims.Clear();
    Rects.Clear();
}

// FUNCTION: GAMEMD 0x5AE590
void MSEngine::OnRedraw(MouseSurfaceView* surface)
{
}

// FUNCTION: GAMEMD 0x5D26F0
void MSEngine::Process()
{
}

// SYNTHETIC: GAMEMD 0x5D2700 -- MSEngine::`scalar deleting destructor'

// Retail 5D1B3F/47/BAB/B9/CD read Count, Items, ownership and Capacity.
GG_STATIC_ASSERT(offsetof(MSEngine, Sfxs.Items) == 0x34);
GG_STATIC_ASSERT(offsetof(MSEngine, Sfxs.Capacity) == 0x38);
GG_STATIC_ASSERT(offsetof(MSEngine, Sfxs.IsAllocated) == 0x3D);
GG_STATIC_ASSERT(offsetof(MSEngine, Sfxs.Count) == 0x40);
GG_STATIC_ASSERT(sizeof(((MSEngine*)0)->Sfxs) == 0x18);
// Retail 5D1B74/7D/D0/DD/F1 reads the corresponding animation vector fields.
GG_STATIC_ASSERT(offsetof(MSEngine, Anims.Items) == 0x1C);
GG_STATIC_ASSERT(offsetof(MSEngine, Anims.Capacity) == 0x20);
GG_STATIC_ASSERT(offsetof(MSEngine, Anims.IsAllocated) == 0x25);
GG_STATIC_ASSERT(offsetof(MSEngine, Anims.Count) == 0x28);
GG_STATIC_ASSERT(sizeof(((MSEngine*)0)->Anims) == 0x18);
// Retail 5D1BF4/C01/C15 reads Items, ownership and Capacity of Rects.
GG_STATIC_ASSERT(offsetof(MSEngine, Rects.Items) == 0x0C);
GG_STATIC_ASSERT(offsetof(MSEngine, Rects.Capacity) == 0x10);
GG_STATIC_ASSERT(offsetof(MSEngine, Rects.IsAllocated) == 0x15);
GG_STATIC_ASSERT(sizeof(((MSEngine*)0)->Rects) == 0x10);
