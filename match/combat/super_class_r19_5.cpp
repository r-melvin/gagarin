// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 (vtable 0x7F3FE8).
//   Implemented on the canonical SuperClass.
//   Address index: 0x6CAEC0.

#include "../_layout/super_class.h"
#include "../core/vector_class_operations.h"

// GLOBAL: GAMEMD 0xA83CB8 -- the super weapon array (defined in core/static_vector_init_stubs.cpp).
extern DynamicVectorClass<SuperClass*> DAT_00A83CB8;
// GLOBAL: GAMEMD 0xB0C000 -- the "no cell" sentinel.
extern CellStruct DAT_00B0C000;

// FUNCTION: GAMEMD 0x6CAEC0
// Default constructor: an unowned, untyped super weapon with no charge, then
// registered in the global array.
SuperClass::SuperClass()
    : CustomChargeTime(-1), Type(0), Owner(0), RechargeTimer(0), BlinkState(0), BlinkTimer_Low(0),
      BlinkTimer_High(0), SpecialSoundDuration(-1), CanHold(true), ChronoMapCoords(DAT_00B0C000),
      Animation(0), AnimationGotInvalid(false), IsPresent(false), IsOneTime(false), IsReady(false),
      IsSuspended(false), ChargeDrainState(-1)
{
    DAT_00A83CB8.AddItem(this);
}

// SYNTHETIC: GAMEMD 0x6CE220 -- SuperClass scalar deleting destructor, emitted by the compiler from the
// virtual destructor where this TU seats the vtable.
