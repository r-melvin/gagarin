// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Entry-origin retail gamemd.exe v1.001 instructions at 0x004B4C00,
//   0x004B4C10, and 0x004B4C20 show each __stdcall interface method loading
//   its first stack argument and then a dword at interface offsets 0x54, 0x58,
//   and 0x48 respectively, followed by RET 4. The DriveLocomotion ILocomotion
//   vtable at 0x007E7EB0 stores these three entry addresses in slots 47..49
//   (0x007E7F6C..0x007E7F74). Field meanings are supported by the retail
//   constructor/readers cited in match/_layout/drive_locomotion_class.h.
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The argument is the ILocomotion interface subobject pointer, which starts
// four bytes into DriveLocomotionClass; these field offsets are interface-relative.
struct DriveLocomotionInterfaceView_004B4C00
{
    char unknown_00[0x48];
    int SpeedAccum;
    char unknown_4C[0x08];
    int TrackNumber;
    int TrackIndex;
};
GG_STATIC_ASSERT(offsetof(DriveLocomotionInterfaceView_004B4C00, SpeedAccum) == 0x48);
GG_STATIC_ASSERT(offsetof(DriveLocomotionInterfaceView_004B4C00, TrackNumber) == 0x54);
GG_STATIC_ASSERT(offsetof(DriveLocomotionInterfaceView_004B4C00, TrackIndex) == 0x58);
GG_STATIC_ASSERT(sizeof(DriveLocomotionInterfaceView_004B4C00) == 0x5C);
// Vtable prefix view, confirmed by retail RTTI locator 0x7FFDE8 (offset 4).
struct DriveGetterSlots_004B4C00
{
    void* unknown_00[47];
    int (__stdcall* TrackNumber)(DriveLocomotionInterfaceView_004B4C00*);
    int (__stdcall* TrackIndex)(DriveLocomotionInterfaceView_004B4C00*);
    int (__stdcall* SpeedAccum)(DriveLocomotionInterfaceView_004B4C00*);
};
GG_STATIC_ASSERT(offsetof(DriveGetterSlots_004B4C00, TrackNumber) == 0xBC);
GG_STATIC_ASSERT(offsetof(DriveGetterSlots_004B4C00, TrackIndex) == 0xC0);
GG_STATIC_ASSERT(offsetof(DriveGetterSlots_004B4C00, SpeedAccum) == 0xC4);
GG_STATIC_ASSERT(sizeof(DriveGetterSlots_004B4C00) == 0xC8);

// FUNCTION: GAMEMD 0x004B4C00
int __stdcall FUN_004B4C00(DriveLocomotionInterfaceView_004B4C00* self)
{
    return self->TrackNumber;
}

// FUNCTION: GAMEMD 0x004B4C10
int __stdcall FUN_004B4C10(DriveLocomotionInterfaceView_004B4C00* self)
{
    return self->TrackIndex;
}

// FUNCTION: GAMEMD 0x004B4C20
int __stdcall FUN_004B4C20(DriveLocomotionInterfaceView_004B4C00* self)
{
    return self->SpeedAccum;
}
