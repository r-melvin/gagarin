// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x659110: `PUSH 0xC8` into operator new (the object
//   size), `FSTP qword [EDI+0x18]` (the double written after allocation), and
//   the global vector at 0xB04A60 read as `[0xB04A68]` capacity, `[0xB04A6D]`
//   byte allocated flag, `[0xB04A70]` count, `[0xB04A74]` increment,
//   `[0xB04A64]` items, with its slot +0x08 reached through
//   `MOV EAX,[0xB04A60]; CALL [EAX+8]`. The method name and the vector's
//   identity (RadBeam::Array) are cross-checked against YRpp.
#ifndef GG_MATCH_COMBAT_RAD_BEAM_ALLOCATE_METHODS_H
#define GG_MATCH_COMBAT_RAD_BEAM_ALLOCATE_METHODS_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "_layout/coord_struct.h"
#include "_layout/components.h"
#include "_layout/techno_class.h"

struct RadBeam;

// DynamicVectorClass<RadBeam*> — the live-beam list. Slot +0x08 is
// Resize(newCapacity, array): two stack arguments, `this` in ECX, a byte
// result tested with `TEST AL,AL`.
struct RadBeamVector
{
    virtual void vt_000();
    virtual void vt_004();
    virtual bool Resize(int newCapacity, void* array);   // +0x0008

    RadBeam** Items;           // +0x0004
    int   Capacity;            // +0x0008
    char  _pad0C[0x1];
    char  IsAllocated;         // +0x000D
    char  _pad0E[0x10 - 0x0E];
    int   Count;               // +0x0010
    int   CapacityIncrement;   // +0x0014

    // DynamicVectorClass::AddItem, expanded inline by VC6 at the Allocate call
    // site. Same phrasing as match/cell_class_tag_methods.h (0x485250):
    // Capacity bound to a local so the vtable load stays ahead of the argument
    // pushes, and `Count++` bound to an index so the increment is sequenced
    // before the store.
    bool AddItem(RadBeam* item)
    {
        int cap = Capacity;
        if (Count < cap
            || ((IsAllocated || cap == 0)
                && CapacityIncrement > 0
                && Resize(cap + CapacityIncrement, 0))) {
            int index = Count++;
            Items[index] = item;
            return true;
        }
        return false;
    }
};
GG_STATIC_ASSERT(offsetof(RadBeamVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(RadBeamVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(RadBeamVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(RadBeamVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(RadBeamVector, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(RadBeamVector) == 0x18);

// GLOBAL: GAMEMD 0xB04A60 — RadBeam::Array (an object, not a pointer: retail
// loads its address as the immediate `MOV ECX,0xB04A60`).
extern RadBeamVector DAT_00B04A60;

// RadBeam — 0xC8 bytes (the operator new size). No vtable: the constructor
// zeroes the first dword. Members are placeholders named by offset, except
// At_18 which Allocate seeds.
struct RadBeam
{
    TechnoClass*   unknown_00;    // +0x0000  firing object; its +0x510 points back here
    AbstractClass* unknown_04;    // +0x0004  target; its flag byte +0x14 is tested
    unsigned char  unknown_08;    // +0x0008
    unsigned char  unknown_09;    // +0x0009
    int            unknown_0C;    // +0x000C  height offset of the drawn line
    int            unknown_10;    // +0x0010  beam type (1 or 2)
    char           _pad014[0x18 - 0x14];
    double         At_18;         // +0x0018  10 for type 1, 20 otherwise
    ColorStruct    unknown_20;    // +0x0020
    char           _pad023;
    CoordStruct    unknown_24;    // +0x0024
    CoordStruct    unknown_30;    // +0x0030
    int            unknown_3C;    // +0x003C
    double         unknown_40;    // +0x0040
    double         unknown_48;    // +0x0048
    int            unknown_50;    // +0x0050
    int            unknown_54;    // +0x0054
    unsigned char  unknown_58;    // +0x0058
    char           _pad059[0x5C - 0x59];
    CoordStruct    unknown_5C;    // +0x005C
    double         unknown_68;    // +0x0068
    CoordStruct    unknown_70;    // +0x0070
    int            unknown_7C;    // +0x007C
    double         unknown_80;    // +0x0080
    int            unknown_88;    // +0x0088
    int            unknown_8C;    // +0x008C
    CoordStruct    unknown_90;    // +0x0090
    CoordStruct    unknown_9C;    // +0x009C
    CoordStruct    unknown_A8;    // +0x00A8
    double         unknown_B8;    // +0x00B8
    ColorStruct    unknown_C0;    // +0x00C0
    char           _padC3[0xC8 - 0xC3];

    // FUNCTION: GAMEMD 0x6593F0 (decl; reloc) — the constructor, one stack
    // argument (the beam type).
    RadBeam(int type) throw();

    // FUNCTION: GAMEMD 0x659110
    static RadBeam* Allocate(int type);

    // 0x659590 — draws one line between two world points.
    void FUN_00659590(const CoordStruct* from, const CoordStruct* to, short color);
    // 0x659A30
    void FUN_00659A30();
    // 0x659CA0
    bool FUN_00659CA0();
    // 0x659EE0
    void FUN_00659EE0();
    // FUNCTION: GAMEMD 0x659FF0 (decl; reloc) -- the per-step endpoint update
    void FUN_00659FF0();

    // FUNCTION: GAMEMD 0x659650 (decl; reloc) -- the step for beam type 1
    bool FUN_00659650();
    // FUNCTION: GAMEMD 0x659E30 (decl; reloc) -- first-step setup
    void FUN_00659E30();
};
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_09) == 0x09);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(RadBeam, At_18) == 0x18);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_48) == 0x48);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_50) == 0x50);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_54) == 0x54);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_58) == 0x58);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_5C) == 0x5C);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_68) == 0x68);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_70) == 0x70);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_7C) == 0x7C);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_80) == 0x80);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_88) == 0x88);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_8C) == 0x8C);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_90) == 0x90);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_9C) == 0x9C);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_A8) == 0xA8);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_B8) == 0xB8);
GG_STATIC_ASSERT(offsetof(RadBeam, unknown_C0) == 0xC0);
GG_STATIC_ASSERT(sizeof(RadBeam) == 0xC8);

#endif  // GG_MATCH_COMBAT_RAD_BEAM_ALLOCATE_METHODS_H
