// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
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
    Field04 = 0;
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
void MSEngine::Slot1(int a)
{
}

// FUNCTION: GAMEMD 0x5D26F0
void MSEngine::Slot2()
{
}

// SYNTHETIC: GAMEMD 0x5D2700 -- MSEngine::`scalar deleting destructor'
