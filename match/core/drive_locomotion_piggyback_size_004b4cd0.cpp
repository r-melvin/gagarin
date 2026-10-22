// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   0x004B4CD0 is an IPiggyback interface __stdcall entry. Its sole load is
//   [argument+0x50] @0x004B4CD6 and it returns that dword's nonzero test with
//   RET 4 @0x004B4CDE. DriveLocomotionClass stores its IPiggyback vptr at +0x18
//   (constructor 0x004AF5CF); the interface field therefore aliases object+0x68,
//   the Piggybackee member independently asserted in the retail-backed layout.
//   Vtable 0x007E7E8C contains this entry at slot 7 (+0x1C).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/drive_locomotion_class.h"

struct DrivePiggybackInterfaceView_004B4CD0
{
    char unknown_00[0x50];
    void* Piggybackee;
};
GG_STATIC_ASSERT(offsetof(DrivePiggybackInterfaceView_004B4CD0, Piggybackee) == 0x50);
GG_STATIC_ASSERT(offsetof(DriveLocomotionClass, Piggybackee) - 0x18 == 0x50);
GG_STATIC_ASSERT(sizeof(DrivePiggybackInterfaceView_004B4CD0) == 0x54);
GG_STATIC_ASSERT(sizeof(void*) == 4);

struct DrivePiggybackVtable_004B4CD0
{
    void* unknown_00[7];
    bool (__stdcall* unknown_1C)(DrivePiggybackInterfaceView_004B4CD0*);
};
GG_STATIC_ASSERT(offsetof(DrivePiggybackVtable_004B4CD0, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(sizeof(DrivePiggybackVtable_004B4CD0) == 0x20);

// FUNCTION: GAMEMD 0x004B4CD0
bool __stdcall FUN_004B4CD0(DrivePiggybackInterfaceView_004B4CD0* self)
{
    return self->Piggybackee != 0;
}

struct DriveLocomotionClassSizeMethodView_004B4CF0
{
    int Size();
};

struct DriveLocomotionSizeVtable_004B4CF0
{
    void* unknown_00[9];
    void* Size;
};
GG_STATIC_ASSERT(offsetof(DriveLocomotionSizeVtable_004B4CF0, Size) == 0x24);
GG_STATIC_ASSERT(sizeof(DriveLocomotionSizeVtable_004B4CF0) == 0x28);
GG_STATIC_ASSERT(sizeof(void*) == 4);

// FUNCTION: GAMEMD 0x004B4CF0
int DriveLocomotionClassSizeMethodView_004B4CF0::Size()
{
    return 0x70;
}
