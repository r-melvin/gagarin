// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: 0x5FE3F0 stores four vtable pointers, announces the expired pointer, removes the
//   object from the class-wide array and falls into the ObjectTypeClass body; 0x5FC4D0 is the
//   same shape over ObjectClass.
//   Address index: 0x5FC4D0 ~OverlayClass, 0x5FE3F0 ~OverlayTypeClass.

#include "../_layout/object_type_class.h"
#include "../_layout/abstract_class.h"
#include "../_layout/object_class.h"
#include "../_rt/gg_static_assert.h"
#include "vector_class_operations.h"

class OverlayTypeClass : public ObjectTypeClass
{
public:
    OverlayTypeClass(const AbstractNoInit& noInit);
    virtual ~OverlayTypeClass();
};

class OverlayClass : public ObjectClass
{
public:
    OverlayClass(const AbstractNoInit& noInit);
    virtual ~OverlayClass();
    void* Type; // +0xAC
};
GG_STATIC_ASSERT(offsetof(OverlayClass, Type) == 0xAC);

// GLOBAL: GAMEMD 0xA8EC50 -- the overlay registry.
extern DynamicVectorClass<OverlayClass*> DAT_00A8EC50;
// GLOBAL: GAMEMD 0xA8E9A0 -- map-removal enable flag.
extern bool DAT_00A8E9A0;

// GLOBAL: GAMEMD 0xA83D80 -- the overlay type registry.
extern DynamicVectorClass<OverlayTypeClass*> DAT_00A83D80;

// FUNCTION: GAMEMD 0x5FC4D0
OverlayClass::~OverlayClass()
{
    AnnounceExpiredPointer(1);
    DAT_00A8EC50.RemoveItem(this);
    if (DAT_00A8E9A0)
        vf_53();
    Type = 0;
}

// FUNCTION: GAMEMD 0x5FE3F0
OverlayTypeClass::~OverlayTypeClass()
{
    AnnounceExpiredPointer(1);
    DAT_00A83D80.RemoveItem(this);
}
