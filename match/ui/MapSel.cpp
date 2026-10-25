// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit MapSel.CPP. The name is the source-file string at 0x82c11c
//   in retail gamemd.exe v1.001, passed by the assert at 0x5add9a inside this object's
//   code range (0x5adb20-0x5ae8ef). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
//   cross-checked against YRpp.
//
// Scalar deleting destructors of two WOL dialog controls and of MapSelect.
// Each runs the destructor inline (own vtable store where the class declares
// a destructor, member destructors in reverse order, then the base), frees
// the object when bit 0 of the flag is set and returns `this`.
//
// RTTI chains: CreateGameDialogControl -> WonlineStringDialogControl ->
// SimpleWonlineDialogControl -> OwnerDraw::SimpleDialogControl ->
// OwnerDraw::DialogControl, and MapSelect -> MSEngine. The DialogControl
// destructor (0x624130) and the MSEngine destructor (0x5D1B30) are out of
// line here; SimpleDialogControl and CreateGameDialogControl have implicit
// destructors (no vtable store of their own). Slot 0 is modelled as an
// ordinary virtual holding the deleting wrapper, as FileClass does in
// match/core/ram_file_class.h, because nothing is constructed in this file.

#include "../_layout/matrix3d.h"

#include "../movement/trivial_tu131_methods.h"

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Out-of-line destructor 0x7B46F0 (a four-byte member: a string handle).
class Member_7B46F0
{
public:
    ~Member_7B46F0();
    void* Data;
};

#include "../_layout/map_stage_list.h"

namespace OwnerDraw {

class DialogControl
{
public:
    ~DialogControl();   // 0x624130
    virtual void* DeletingDtor(unsigned int flags);
    int unknown_04;     // +0x04
    int unknown_08;     // +0x08
};

class SimpleDialogControl : public DialogControl
{
};

}  // namespace OwnerDraw

// VTABLE: GAMEMD 0x7F7624
class SimpleWonlineDialogControl : public OwnerDraw::SimpleDialogControl
{
public:
    ~SimpleWonlineDialogControl() {}
};

// VTABLE: GAMEMD 0x7F7874
class WonlineStringDialogControl : public SimpleWonlineDialogControl
{
public:
    ~WonlineStringDialogControl() {}
    virtual void* DeletingDtor(unsigned int flags);
    Member_7B46F0 String;   // +0x0C
};

class CreateGameDialogControl : public WonlineStringDialogControl
{
public:
    virtual void* DeletingDtor(unsigned int flags);
};

GG_STATIC_ASSERT(offsetof(WonlineStringDialogControl, String) == 0x0C);

class MSEngine
{
public:
    ~MSEngine();   // 0x5D1B30
    virtual void* DeletingDtor(unsigned int flags);
    char unknown_04[0x4C];   // +0x04
};

// Implicit destructor: the members, then the MSEngine one.
class MapSelect : public MSEngine
{
public:
    virtual void* DeletingDtor(unsigned int flags);
    MapStageList Stages;        // +0x50
    char unknown_AC[0x1C];      // +0x51
    Member_7B46F0 Member_C8;    // +0xC8
};

GG_STATIC_ASSERT(offsetof(MapSelect, Stages) == 0x50);
GG_STATIC_ASSERT(offsetof(MapSelect, Member_C8) == 0xC8);

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EDB38
extern const double DAT_007EDB38;
// GLOBAL: GAMEMD 0xABED78
extern double DAT_00ABED78;
// GLOBAL: GAMEMD 0xABEDB0
extern double DAT_00ABEDB0;
// GLOBAL: GAMEMD 0xABEDB8
extern int DAT_00ABEDB8;
// GLOBAL: GAMEMD 0xABEDBC
extern int DAT_00ABEDBC;
// GLOBAL: GAMEMD 0xABEDC0
extern int DAT_00ABEDC0;
// GLOBAL: GAMEMD 0xABEDC8
extern double DAT_00ABEDC8;



#include "../_layout/matrix3d.h"

// FUNCTION: GAMEMD 0x5ADB50
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_005ADB50()
{
    DAT_00ABEDC8 = DAT_00ABED78 / DAT_007EDB38;
}

// FUNCTION: GAMEMD 0x5ADB70
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_005ADB70()
{
    DAT_00ABEDB0 = DAT_007E1718 / DAT_00ABEDC8;
}

// FUNCTION: GAMEMD 0x5ADCF0
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_005ADCF0()
{
    DAT_00ABEDC0 = 0;
    DAT_00ABEDB8 = 0x80;
    DAT_00ABEDBC = 0x80;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5AE4F0
// Returns zero; pops its stack arguments.
int __stdcall FUN_005AE4F0(int a1)
{
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5AE570
// Empty function that pops its stack arguments.
void __stdcall FUN_005AE570(int a1)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5AE580
// Empty function that pops its stack arguments.
void __stdcall FUN_005AE580(int a1)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5AE590
// Empty function that pops its stack arguments. Vtable slot 1 of MSEngine (RTTI) and 2 derived vtable(s).
void Obj_005AE590::FUN_005AE590(int a1)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5AE5A0
void* MapSelect::DeletingDtor(unsigned int flags)
{
    this->~MapSelect();
    if (flags & 1) {
        operator delete(this);
    }
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5AE860  (__thiscall)
// Reset to the identity transform. Retail is fully unrolled: 1.0f's bit
// pattern is hoisted into EDX, 0.0f into EAX, then the 12 cells are stored in
// source order, so the flat assignment list below reproduces it exactly.
void Matrix3D::MakeIdentity()
{
    Row[0][0] = 1.0f; Row[0][1] = 0.0f; Row[0][2] = 0.0f; Row[0][3] = 0.0f;
    Row[1][0] = 0.0f; Row[1][1] = 1.0f; Row[1][2] = 0.0f; Row[1][3] = 0.0f;
    Row[2][0] = 0.0f; Row[2][1] = 0.0f; Row[2][2] = 1.0f; Row[2][3] = 0.0f;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5AE890  (__thiscall)
// Combined translate, fully unrolled x87. Per row the retail add order is
// (y*col1 + z*col2) + x*col0, then += col3.
void Matrix3D::Translate(float x, float y, float z)
{
    Row[0][3] += y * Row[0][1] + z * Row[0][2] + x * Row[0][0];
    Row[1][3] += y * Row[1][1] + z * Row[1][2] + x * Row[1][0];
    Row[2][3] += y * Row[2][1] + z * Row[2][2] + x * Row[2][0];
}
