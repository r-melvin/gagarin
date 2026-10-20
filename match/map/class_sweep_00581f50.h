// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; gamemd.exe v1.001. Entry Evidence:
// ev_5f49516d7c5adae90c0010abd2a08c5a1910072aacb7868a26397ee9844facba.
// The call to 0x581F90 is confirmed __thiscall with one stack int and RET 4
// by ev_4bd0ea9e1d36e1013ff701356e7575a7088ba838987a18b80e69b6d59b755081.
// Global no-argument call is confirmed at 0x581F7C in entry disassembly.
#ifndef GG_CLASS_SWEEP_00581F50_H
#define GG_CLASS_SWEEP_00581F50_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct CallbackView_00581F50 {
    virtual void unknown_slot_00();
    virtual void unknown_slot_04();
    virtual void unknown_slot_08();
    virtual void unknown_slot_0C();
    char unknown_04[0x14];
};
// Retail proves an indirect call through callback vptr + 0x0C; the three
// preceding virtual slots preserve that slot index. Runtime RTTI/vtable
// identity for these subobjects remains unknown.
GG_STATIC_ASSERT(offsetof(CallbackView_00581F50, unknown_04) == 4);
GG_STATIC_ASSERT(sizeof(CallbackView_00581F50) == 0x18);
struct CallbackSlots_00581F50 {
    void* unknown_00[3];
    void* slot_0C;
};
GG_STATIC_ASSERT(offsetof(CallbackSlots_00581F50, slot_0C) == 0x0C);
GG_STATIC_ASSERT(sizeof(CallbackSlots_00581F50) == 0x10);

struct ClassSweepPrefix_00581F50 {
    char unknown_000[0x8C];
    CallbackView_00581F50 callbacks[3]; // +0x8C, +0xA4, +0xBC
    // FUNCTION: GAMEMD 0x581F90 (decl; reloc), __thiscall(int), RET 4.
    void FUN_00581F90(int index);
    void FUN_00581F50();
};
GG_STATIC_ASSERT(offsetof(ClassSweepPrefix_00581F50, callbacks) == 0x8C);
GG_STATIC_ASSERT(offsetof(ClassSweepPrefix_00581F50, callbacks) +
                 sizeof(CallbackView_00581F50) == 0xA4);
GG_STATIC_ASSERT(offsetof(ClassSweepPrefix_00581F50, callbacks) +
                 2 * sizeof(CallbackView_00581F50) == 0xBC);
GG_STATIC_ASSERT(sizeof(ClassSweepPrefix_00581F50) == 0xD4);

struct GlobalSweep_00581F50 {
    // FUNCTION: GAMEMD 0x42C1C0 (decl; reloc), no stack arguments.
    void FUN_0042C1C0();
};
// GLOBAL: GAMEMD 0x87E8B8
extern GlobalSweep_00581F50 DAT_0087E8B8;
#endif
