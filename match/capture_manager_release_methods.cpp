// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Complete retail body 0x4729C0..0x472A75 (0xB6), REA evidence
// ev_1a5aba8e115edbbdf23b9901dd549edebbe82f9b5166cd0bd9651c8e7b3e0918.
//   /Ob2 inlines the destructor into the scalar deleting destructor 0x4729C0.
#include "FUNCTION.H"
#include "vector_add_item_free.h"

extern "C" void __cdecl gg_free(void*); // LIBRARY: GAMEMD 0x7C8B3D
// GLOBAL: GAMEMD 0x0089E0F0 — RTTI identifies DynamicVectorClass<CaptureManagerClass*>.
extern DynamicVectorClass<CaptureManagerClass*> DAT_0089E0F0;

GG_STATIC_ASSERT(offsetof(DynamicVectorClassLayout, _vtable) == 0x00);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, ControlNodes) == 0x24);
GG_STATIC_ASSERT(offsetof(DynamicVectorClassLayout, Items) + 0x24 == 0x28);
GG_STATIC_ASSERT(offsetof(DynamicVectorClassLayout, Capacity) + 0x24 == 0x2C);
GG_STATIC_ASSERT(offsetof(DynamicVectorClassLayout, unknown_0C) + 0x24 == 0x30);
GG_STATIC_ASSERT(offsetof(DynamicVectorClassLayout, unknown_0C) + 0x25 == 0x31);

// FUNCTION: GAMEMD 0x4719A0
CaptureManagerClass::~CaptureManagerClass()
{
    DAT_0089E0F0.RemoveItem(this);

    ControlNodes._vtable = (void*)0x7E4BC4;
    if (ControlNodes.Items != 0
        && ((unsigned char*)&ControlNodes.unknown_0C)[1] != 0) {
        gg_free(ControlNodes.Items);
        ControlNodes.Items = 0;
    }
    ((unsigned char*)&ControlNodes.unknown_0C)[1] = 0;
    ControlNodes.Capacity = 0;
}

// FUNCTION: GAMEMD 0x471950
// No-initialisation constructor: the base's no-init constructor, the member
// vector's inline constructor, then the class tables.
CaptureManagerClass::CaptureManagerClass(const AbstractNoInit& noInit)
    : AbstractClass(noInit)
{
}

// FUNCTION: GAMEMD 0x4717D0
// Builds the control-node vector in place and registers the manager. Compiling
// it here emits the class tables and so the scalar deleting destructor.
CaptureManagerClass::CaptureManagerClass(void* owner, int maxControlNodes,
                                         bool infiniteMindControl)
{
    Owner = (TechnoClass*)owner;
    MaxControlNodes = maxControlNodes;
    InfiniteMindControl = infiniteMindControl;
    OverloadDeathSoundPlayed = 0;
    OverloadDamageDelay = 30;
    OverloadPipState = 0;

    DynamicVectorAddItemFree(&DAT_0089E0F0, this);
}

// SYNTHETIC: GAMEMD 0x4729C0 -- compiler-generated scalar deleting destructor.
