// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Entry 438B40..438BC1 (RET 8), confirmed from retail and REA evidence
// ev_5c4fe8eab400af7cc468670198a71d2878791ab5b8e4fb5de8875e61d13626dd.
// The constructor and table addresses agree with the 4386F0 initializer.
// Helper ABIs: 410380 stdcall/RET8, 4101C0 thiscall/RET4,
// 405BE0 thiscall/no arguments, 6CF240 stdcall/RET8.
#include "small_misc18_methods.h"
#include "small_misc2_methods.h"
#include "stream_persist_methods.h"
#include "../_layout/swizzle_manager_class.h"
#include "bomb_class_vtables_004386f0.h"

// Standard caller-storage construction; no allocation occurs.
inline void* __cdecl operator new(size_t, void* p) { return p; }
inline void __cdecl operator delete(void*, void*) {}

// Prefix through the fields reset by this load method.
struct BombLoadView_00438B40 {
    void* unknown_00;
    void* unknown_04;
    void* unknown_08;
    void* unknown_0C;
    char unknown_10[0x14];
    void* unknown_24;
    void* unknown_28;
    void* unknown_2C;
    char unknown_30[0xC];
    Obj_00405B00 unknown_3C;
    char unknown_4C[8];
    int unknown_54;
    // Inlined form of constructor 0x004386F0; no separate emitted body.
    inline BombLoadView_00438B40(int arg) {
        ((Obj_004101C0*)this)->FUN_004101C0(arg);
        unknown_00 = (void*)0x7E3D10;
        unknown_04 = (void*)0x7E3CF4;
        unknown_08 = (void*)0x7E3CEC;
        unknown_0C = (void*)0x7E3CE4;
    }
};
GG_STATIC_ASSERT(offsetof(BombLoadView_00438B40, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(BombLoadView_00438B40, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(BombLoadView_00438B40, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(BombLoadView_00438B40, unknown_0C) == 0xC);
GG_STATIC_ASSERT(offsetof(BombLoadView_00438B40, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(BombLoadView_00438B40, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(BombLoadView_00438B40, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(BombLoadView_00438B40, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(BombLoadView_00438B40, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(BombLoadView_00438B40, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(BombLoadView_00438B40, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(BombLoadView_00438B40, unknown_54) == 0x54);
GG_STATIC_ASSERT(sizeof(BombLoadView_00438B40) == 0x58);

// FUNCTION: GAMEMD 0x00438B40
extern "C" long __stdcall FUN_00438B40(BombLoadView_00438B40* self, Stream_00410320* stream) {
    long result = FUN_00410380((Subject_00410320*)self, stream);
    if (result >= 0) {
        new (self) BombLoadView_00438B40((int)&stream);
        self->unknown_3C.FUN_00405BE0();
        self->unknown_54 = 0;
        DAT_00B0C110.SwizzleManagerClass::vf_4(&self->unknown_28);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&self->unknown_24);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&self->unknown_2C);
    }
    return result;
}
