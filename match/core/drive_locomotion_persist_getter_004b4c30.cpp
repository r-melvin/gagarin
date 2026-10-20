// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Entry-origin instructions at 0x004B4C30 load the explicit stack argument,
//   test the byte at interface offset 0x11, return its zero-test as HRESULT (S_OK/S_FALSE),
//   and clean the one dword with RET 4. DriveLocomotionClass constructor
//   0x004AF5C2 stores vptr 0x007E7F7C at object offset 0; the retail pointer at
//   0x007E7F8C (vptr + 0x10) names this function. The field offset is confirmed
//   by match/_layout/locomotion_class.h and by the entry instruction itself.
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/drive_locomotion_class.h"

struct DriveLocomotionPersistVtableView_004B4C30
{
    void* unknown_00;
    void* unknown_04;
    void* unknown_08;
    void* unknown_0C;
    long (__stdcall *IsDirty)(LocomotionClass*);
};
GG_STATIC_ASSERT(sizeof(void*) == 4);
GG_STATIC_ASSERT(offsetof(DriveLocomotionPersistVtableView_004B4C30, IsDirty) == 0x10);

GG_STATIC_ASSERT(sizeof(DriveLocomotionPersistVtableView_004B4C30) == 0x14);

// FUNCTION: GAMEMD 0x004B4C30
long __stdcall FUN_004B4C30(LocomotionClass* self)
{
    return self->Dirty == 0;
}
