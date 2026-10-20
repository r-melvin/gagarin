// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra (gamemd.exe v1.001 stack ABI, relative field reads and vtable slot targets).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/droppod_locomotion_class.h"

// The incoming interface is the complete object's +4 subobject. Reuse the
// shared complete-object layout instead of defining another object prefix.
GG_STATIC_ASSERT(offsetof(DropPodLocomotionClass, LocomotorVptr) == 4);
GG_STATIC_ASSERT(offsetof(DropPodLocomotionClass, Destination) -
                 offsetof(DropPodLocomotionClass, LocomotorVptr) == 0x1C);
GG_STATIC_ASSERT(offsetof(CoordStruct, X) == 0);
GG_STATIC_ASSERT(offsetof(CoordStruct, Y) == 4);
GG_STATIC_ASSERT(offsetof(CoordStruct, Z) == 8);

// VTABLE: GAMEMD 0x007E8278 — touched prefix of the ILocomotion table.
struct DropPodInterfaceSlots_004B5B30 {
    void* slot00;
    void* slot04;
    void* slot08;
    void* slot0C;
    unsigned char (__stdcall* slot10)(void*);
    CoordStruct* (__stdcall* slot14)(const void*, CoordStruct*);
};
GG_STATIC_ASSERT(offsetof(DropPodInterfaceSlots_004B5B30, slot00) == 0);
GG_STATIC_ASSERT(offsetof(DropPodInterfaceSlots_004B5B30, slot04) == 4);
GG_STATIC_ASSERT(offsetof(DropPodInterfaceSlots_004B5B30, slot08) == 8);
GG_STATIC_ASSERT(offsetof(DropPodInterfaceSlots_004B5B30, slot0C) == 0xC);
GG_STATIC_ASSERT(offsetof(DropPodInterfaceSlots_004B5B30, slot10) == 0x10);
GG_STATIC_ASSERT(offsetof(DropPodInterfaceSlots_004B5B30, slot14) == 0x14);
GG_STATIC_ASSERT(sizeof(DropPodInterfaceSlots_004B5B30) == 0x18);

// Retail ILocomotion vtable 0x007E8278 stores these methods in slots 4 and 5;
// raw pointer bytes at 0x007E8288 and 0x007E828C are 0x004B5B30/0x004B5B40.
// FUNCTION: GAMEMD 0x004B5B30
extern "C" unsigned char __stdcall FUN_004B5B30(void* locomotionInterface)
{
    (void)locomotionInterface;
    return 1;
}

// FUNCTION: GAMEMD 0x004B5B40
extern "C" CoordStruct* __stdcall FUN_004B5B40(
    const void* locomotionInterface,
    CoordStruct* destination)
{
    const DropPodLocomotionClass* self =
        reinterpret_cast<const DropPodLocomotionClass*>(
            static_cast<const char*>(locomotionInterface) -
            offsetof(DropPodLocomotionClass, LocomotorVptr));
    CoordStruct value;
    value.X = self->Destination.X;
    value.Y = self->Destination.Y;
    value.Z = self->Destination.Z;
    *destination = value;
    return destination;
}
