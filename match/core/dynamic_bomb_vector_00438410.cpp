// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Entry bytes, global addresses, RTTI names, table slots and call targets were
// confirmed in the retail gamemd.exe v1.001 by entry-bounded disassembly,
// Ghidra memory reads, raw objdump and focused REA records in /tmp/gagarin_438*.json.
// REA's recovered body for 0x438590 stops early at bad instruction data; its
// remaining bytes were independently disassembled from the entry in retail
// through the RET at 0x4385CA with Ghidra and raw objdump.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// LIBRARY: GAMEMD 0x7C8B3D — statically linked CRT heap release wrapper.
// LIBRARY: GAMEMD 0x7C978A — statically linked CRT on-exit registration.
extern "C" {
    void __cdecl FUN_007C8B3D(void* block);
    int __cdecl FUN_007C978A(void (__cdecl *function)());
}

// FUNCTION: GAMEMD 0x00438590 (decl; reloc)
extern "C" void __cdecl FUN_00438590();

// VTABLE: GAMEMD 0x007E17CC — RTTI TypeDescriptor at 0x00816918 names
// DynamicVectorClass<BombClass*>. The seven function-pointer addresses were
// read directly from 0x7E17CC..0x7E17E4: 40BC10, 40B700, 40B880, 40B640,
// 40B930, 40B670, 40B690.
struct DynamicBombVectorVtable_00438550
{
    void* slot_00;
    void* slot_04;
    void* slot_08;
    void* slot_0C;
    void* slot_10;
    void* slot_14;
    void* slot_18;
};
extern "C" DynamicBombVectorVtable_00438550 VT_007E17CC;

// VTABLE: GAMEMD 0x007E17EC — RTTI TypeDescriptor at 0x008168E8 names
// VectorClass<BombClass*>. The five function-pointer addresses were read
// directly from 0x7E17EC..0x7E17FC: 40BBC0, 40B700, 40B740, 40B7F0, 40B820.
struct BombVectorBaseVtable_00438590
{
    void* slot_00;
    void* slot_04;
    void* slot_08;
    void* slot_0C;
    void* slot_10;
};
extern "C" BombVectorBaseVtable_00438590 VT_007E17EC;

GG_STATIC_ASSERT(offsetof(DynamicBombVectorVtable_00438550, slot_00) == 0x00);
GG_STATIC_ASSERT(offsetof(DynamicBombVectorVtable_00438550, slot_04) == 0x04);
GG_STATIC_ASSERT(offsetof(DynamicBombVectorVtable_00438550, slot_08) == 0x08);
GG_STATIC_ASSERT(offsetof(DynamicBombVectorVtable_00438550, slot_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(DynamicBombVectorVtable_00438550, slot_10) == 0x10);
GG_STATIC_ASSERT(offsetof(DynamicBombVectorVtable_00438550, slot_14) == 0x14);
GG_STATIC_ASSERT(offsetof(DynamicBombVectorVtable_00438550, slot_18) == 0x18);
GG_STATIC_ASSERT(sizeof(DynamicBombVectorVtable_00438550) == 0x1C);
GG_STATIC_ASSERT(offsetof(BombVectorBaseVtable_00438590, slot_00) == 0x00);
GG_STATIC_ASSERT(offsetof(BombVectorBaseVtable_00438590, slot_04) == 0x04);
GG_STATIC_ASSERT(offsetof(BombVectorBaseVtable_00438590, slot_08) == 0x08);
GG_STATIC_ASSERT(offsetof(BombVectorBaseVtable_00438590, slot_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(BombVectorBaseVtable_00438590, slot_10) == 0x10);
GG_STATIC_ASSERT(sizeof(BombVectorBaseVtable_00438590) == 0x14);

struct DynamicBombVectorState_00438550
{
    void* vptr;
    void* unknown_04;
    int unknown_08;
    unsigned char unknown_0C;
    unsigned char unknown_0D;
    unsigned char unknown_0E[2];
    int unknown_10;
    int unknown_14;
};
// GLOBAL: GAMEMD 0x0089C668 — RTTI identifies this object as
// DynamicVectorClass<BombClass*>; accessed fields are pinned below.
extern "C" DynamicBombVectorState_00438550 BombVectorState_0089C668;

GG_STATIC_ASSERT(offsetof(DynamicBombVectorState_00438550, vptr) == 0x00);
GG_STATIC_ASSERT(offsetof(DynamicBombVectorState_00438550, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(DynamicBombVectorState_00438550, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(DynamicBombVectorState_00438550, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(DynamicBombVectorState_00438550, unknown_0D) == 0x0D);
GG_STATIC_ASSERT(offsetof(DynamicBombVectorState_00438550, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(DynamicBombVectorState_00438550, unknown_14) == 0x14);
GG_STATIC_ASSERT(sizeof(DynamicBombVectorState_00438550) == 0x18);


// FUNCTION: GAMEMD 0x00438550
extern "C" void FUN_00438550()
{
    BombVectorState_0089C668.unknown_04 = 0;
    BombVectorState_0089C668.unknown_08 = 0;
    BombVectorState_0089C668.unknown_0C = 1;
    BombVectorState_0089C668.unknown_0D = 0;
    BombVectorState_0089C668.vptr = &VT_007E17CC;
    BombVectorState_0089C668.unknown_14 = 10;
    BombVectorState_0089C668.unknown_10 = 0;
    FUN_007C978A(FUN_00438590);
}

// FUNCTION: GAMEMD 0x00438590
extern "C" void __cdecl FUN_00438590()
{
    BombVectorState_0089C668.vptr = &VT_007E17EC;
    if (BombVectorState_0089C668.unknown_04 != 0 &&
        BombVectorState_0089C668.unknown_0D != 0) {
        FUN_007C8B3D(BombVectorState_0089C668.unknown_04);
        BombVectorState_0089C668.unknown_04 = 0;
    }
    BombVectorState_0089C668.unknown_0D = 0;
    BombVectorState_0089C668.unknown_08 = 0;
}
