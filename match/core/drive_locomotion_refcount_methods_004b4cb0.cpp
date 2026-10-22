// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Retail entries 0x004B4CB0/CC0 are 13-byte __stdcall wrappers: each loads
//   its explicit object pointer, pushes it, calls 0x0055A950/970, and returns
//   with RET 4. Their DriveLocomotion persist-vtable slots are +4/+8 at
//   0x007E7F80/84; the vptr 0x007E7F7C is written at object offset zero by
//   constructor 0x004AF5C2. The callees update the object dword at +0x14 via
//   InterlockedIncrement/Decrement and leave the returned LONG in EAX.
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../movement/loco_base.h"

struct DrivePersistRefcountVtable_004B4CB0
{
    void* unknown_00;
    long (__stdcall *AddRef)(LocomotionClass*);
    long (__stdcall *Release)(LocomotionClass*);
};
GG_STATIC_ASSERT(sizeof(void*) == 4);
GG_STATIC_ASSERT(offsetof(LocomotionClass, RefCount) == 0x14);
GG_STATIC_ASSERT(offsetof(DrivePersistRefcountVtable_004B4CB0, AddRef) == 0x04);
GG_STATIC_ASSERT(offsetof(DrivePersistRefcountVtable_004B4CB0, Release) == 0x08);

GG_STATIC_ASSERT(sizeof(DrivePersistRefcountVtable_004B4CB0) == 0xC);

// FUNCTION: GAMEMD 0x004B4CB0
long __stdcall FUN_004B4CB0(LocomotionClass* self)
{
    return self->LocomotionClass::AddRef();
}

// FUNCTION: GAMEMD 0x004B4CC0
long __stdcall FUN_004B4CC0(LocomotionClass* self)
{
    return self->LocomotionClass::Release();
}
