// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra (gamemd.exe v1.001 stack ABI, relative field reads and vtable slot targets).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/droppod_locomotion_class.h"
#include "locomotion_class_load_methods.h"
#include "loco_interfaces.h"

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
    void* unknown_18[12];
    void (__stdcall* Unknown_48)(void*);
};
GG_STATIC_ASSERT(offsetof(DropPodInterfaceSlots_004B5B30, slot00) == 0);
GG_STATIC_ASSERT(offsetof(DropPodInterfaceSlots_004B5B30, slot04) == 4);
GG_STATIC_ASSERT(offsetof(DropPodInterfaceSlots_004B5B30, slot08) == 8);
GG_STATIC_ASSERT(offsetof(DropPodInterfaceSlots_004B5B30, slot0C) == 0xC);
GG_STATIC_ASSERT(offsetof(DropPodInterfaceSlots_004B5B30, slot10) == 0x10);
GG_STATIC_ASSERT(offsetof(DropPodInterfaceSlots_004B5B30, slot14) == 0x14);
GG_STATIC_ASSERT(offsetof(DropPodInterfaceSlots_004B5B30, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(DropPodInterfaceSlots_004B5B30, Unknown_48) == 0x48);
GG_STATIC_ASSERT(sizeof(DropPodInterfaceSlots_004B5B30) == 0x4C);

// The Load body dispatches IStream::Read at slot 3 and releases an existing
// locomotion object through IUnknown::Release at slot 2.
struct IStreamReadVtable_004B6240 {
    void* QueryInterface;
    void* AddRef;
    void* Release;
    long (__stdcall* Read)(void*, void*, unsigned long, unsigned long*);
};
GG_STATIC_ASSERT(offsetof(IStreamReadVtable_004B6240, QueryInterface) == 0x00);
GG_STATIC_ASSERT(offsetof(IStreamReadVtable_004B6240, AddRef) == 0x04);
GG_STATIC_ASSERT(offsetof(IStreamReadVtable_004B6240, Release) == 0x08);
GG_STATIC_ASSERT(offsetof(IStreamReadVtable_004B6240, Read) == 0x0C);
GG_STATIC_ASSERT(sizeof(IStreamReadVtable_004B6240) == 0x10);
GG_STATIC_ASSERT(sizeof(IStream_0055AAC0) == 4);

struct IUnknownReleaseVtable_004B6240 {
    void* QueryInterface;
    void* AddRef;
    unsigned long (__stdcall* Release)(void*);
};
GG_STATIC_ASSERT(offsetof(IUnknownReleaseVtable_004B6240, QueryInterface) == 0x00);
GG_STATIC_ASSERT(offsetof(IUnknownReleaseVtable_004B6240, AddRef) == 0x04);
GG_STATIC_ASSERT(offsetof(IUnknownReleaseVtable_004B6240, Release) == 0x08);
GG_STATIC_ASSERT(sizeof(IUnknownReleaseVtable_004B6240) == 0x0C);
GG_STATIC_ASSERT(sizeof(ILocomotion) == 4);

// VTABLE: GAMEMD 0x007E8344 — slot 5 (+0x14) points to 0x004B6240.
GG_STATIC_ASSERT(offsetof(DropPodPersistVtable, Load) == 0x14);

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

// FUNCTION: GAMEMD 0x004B6200 — DropPod IPersist::GetClassID, vtable slot 3.
// The COM stdcall ABI places the receiver and output pointer on the stack;
// RET 8 is confirmed at both return paths in the retail body.
long __stdcall DropPodLocomotionClass::GetClassID(
    GuidWords* outGuid)
{
    if (outGuid == 0) {
        return (long)0x80004003;
    }

    outGuid->unknown_00 = DAT_007E9A70;
    outGuid->unknown_04 = DAT_007E9A74;
    outGuid->unknown_08 = DAT_007E9A78;
    outGuid->unknown_0C = DAT_007E9A7C;
    return 0;
}

// LIBRARY: OLE32!OleLoadFromStream, imported at GAMEMD IAT 0x007E15F8.
// FUNCTION: GAMEMD 0x004B6240 — IPersistStream::Load, slot 5.
long __stdcall DropPodLocomotionClass::Load(IStream_0055AAC0* stream)
{
    long result = FUN_0055AAC0((Loco_0055AAC0*)this, stream);
    if (result >= 0) {
        if (this != 0) {
            this->Piggybackee = 0;
            this->PersistVptr = (void*)0x007E8344;
            this->LocomotorVptr = (void*)0x007E8278;
            this->PiggybackVptr = (void*)0x007E8254;
        }

        unsigned char hasPiggyback;
        stream->Read(&hasPiggyback, 1, 0);
        if (hasPiggyback != 0) {
            if (this->Piggybackee != 0) {
                ((ILocomotion*)this->Piggybackee)->Release();
            }
            this->Piggybackee = 0;
            result = OleLoadFromStream((IStream*)stream, *(const IID*)&IID_ILocomotion,
                                       (void**)&this->Piggybackee);
        }
    }
    return result;
}

// FUNCTION: GAMEMD 0x004B63A0
// VTABLE: GAMEMD 0x007E8278 — slot 18 (+0x48) targets this entry. The
// complete object's constructor stores this table at +0x04, so the physical
// receiver passed on the stack is the ILocomotion subobject at complete+4.
// The body is only RET 4: no behavior or method name beyond this slot is
// established by the retail bytes.
void __stdcall DropPodILocomotionView_007E8278::Unknown_48()
{
}
