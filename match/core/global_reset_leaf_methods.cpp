// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Global-state resets and release loops whose body repeats at two or more
// retail addresses. Each address is compiled and checked on its own; the
// copies differ in the global they touch. Owners that are not modelled
// elsewhere are placeholders `Obj_<ADDR>` declaring only what the body
// touches, with offset asserts.

#include <stddef.h>
#include <new.h>
#include "../_layout/voxel_resource_data.h"
#include "../_rt/gg_static_assert.h"

struct Iface_004C5470 {
    virtual void vf_0();
    virtual void vf_1();
    virtual void vf_2();
    virtual void vf_3();
    virtual void vf_4();
    virtual void vf_5();
    virtual void vf_6();
    virtual void vf_7();
    virtual void vf_8(int flag);
};
extern int DAT_008A3880;
extern Iface_004C5470** DAT_008A3874;
// FUNCTION: GAMEMD 0x004C5470
void FUN_004C5470()
{
    while (DAT_008A3880) {
        Iface_004C5470* object = *DAT_008A3874;
        if (object)
            object->vf_8(1);
    }
}

// FUNCTION: GAMEMD 0x005BD5A0
Obj_005BD5A0::~Obj_005BD5A0()
{
    if (unknown_0C)
        ::operator delete(unknown_0C);
    unknown_0C = 0;
}

// FUNCTION: GAMEMD 0x005BD7C0
void Obj_005BD5A0::FUN_005BD7C0()
{
    if (unknown_0C)
        ::operator delete(unknown_0C);
    unknown_0C = 0;
}

struct Target_00B1CF68 {
    void FUN_007346A0();
};
extern Target_00B1CF68* DAT_00B1CF68;
struct Obj_00734F50;
extern Obj_00734F50* DAT_00B1CF84;
extern Obj_00734F50* DAT_00B1CF60;
struct Obj_00734F50 {
    void FUN_00734D30();
    void FUN_00734F50();
    void FUN_00734F80();
};
// FUNCTION: GAMEMD 0x00734F50
void Obj_00734F50::FUN_00734F50()
{
    if (DAT_00B1CF84 != this) {
        FUN_00734D30();
        DAT_00B1CF84 = this;
        DAT_00B1CF68->FUN_007346A0();
    }
}
// FUNCTION: GAMEMD 0x00734F80
void Obj_00734F50::FUN_00734F80()
{
    if (DAT_00B1CF60 != this) {
        FUN_00734D30();
        DAT_00B1CF60 = this;
        DAT_00B1CF68->FUN_007346A0();
    }
}

extern int DAT_00887398;
extern Iface_004C5470** DAT_0088738C;
// FUNCTION: GAMEMD 0x00749F00
void FUN_00749F00()
{
    while (DAT_00887398) {
        Iface_004C5470* object = *DAT_0088738C;
        if (object)
            object->vf_8(1);
    }
}

extern int DAT_00B1D4D8;
extern int DAT_00B1D480;
// FUNCTION: GAMEMD 0x00753540
void FUN_00753540()
{
    if (DAT_00B1D4D8) {
        if (--DAT_00B1D480 < 0)
            DAT_00B1D480 = 0;
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x88738C
Iface_004C5470** DAT_0088738C;
// GLOBAL: GAMEMD 0x887398
int DAT_00887398;
// GLOBAL: GAMEMD 0x8A3874
Iface_004C5470** DAT_008A3874;
// GLOBAL: GAMEMD 0x8A3880
int DAT_008A3880;
// GLOBAL: GAMEMD 0xB1CF60
Obj_00734F50* DAT_00B1CF60;
// GLOBAL: GAMEMD 0xB1CF68
Target_00B1CF68* DAT_00B1CF68;
// GLOBAL: GAMEMD 0xB1CF84
Obj_00734F50* DAT_00B1CF84;
// GLOBAL: GAMEMD 0xB1D480
int DAT_00B1D480;
// GLOBAL: GAMEMD 0xB1D4D8
int DAT_00B1D4D8;
// END defined globals
