// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Every offset, slot, constant and call target below is read numerically off
//   the user's retail gamemd.exe v1.001 via the local Ghidra CLI at the seven
//   addresses named. None is bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC38_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC38_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void __cdecl FUN_007C8B3D(void* block);


// ---------------------------------------------------------------------------
// 0x41C3F0 — snap an all-zero triple to a default.
//
// Three doubles at +0x00, +0x08 and +0x10 are each compared against the
// constant at 0x7E2800, which `ghidra memory read 0x7E2800 8` shows is eight
// zero bytes, i.e. 0.0. Only when all three are zero is the first one set, and
// the value written is the two dwords 0x00000000 / 0x40590000 - the double
// 100.0.
// ---------------------------------------------------------------------------
struct Triple_0041C3F0
{
    double X;   // +0x0000
    double Y;   // +0x0008
    double Z;   // +0x0010
};
GG_STATIC_ASSERT(offsetof(Triple_0041C3F0, Z) == 0x10);

// FUNCTION: GAMEMD 0x41C3F0
void FUN_0041C3F0(Triple_0041C3F0* self);

// ---------------------------------------------------------------------------
// 0x426750 — install a delegate and prime it.
// ---------------------------------------------------------------------------
struct Delegate_00426750
{
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual void vt_00C();
    virtual void vt_010();
    virtual void vt_014();
    virtual bool vt_018();          // +0x0018
    virtual void vt_01C(int flag);  // +0x001C
    virtual void vt_020();
    virtual int vt_024(void* buffer, int size);   // +0x0024  read
    virtual void vt_028(int position, int whence); // +0x0028  seek
    virtual void vt_02C();
    virtual void vt_030();
    virtual void vt_034();          // +0x0034  reached by the 0x426790 teardown
};

// The teardown at 0x426790 reaches two more slots on the delegate and one on
// the sub-object at +0xE0C.
struct SubObject_00426790
{
    virtual void* vt_000(char flags);   // +0x0000  deleting destructor
};

// CLASS IDENTITY (whole-image RTTI sweep; renamed from
// the raw `Obj_` placeholder). AnimFile's own vtable is 0x7E3584.
//   0x426750 -> AnimFile slot 1 (byte-off 0x4).
//   0x426790 -> AnimFile slot 2 (byte-off 0x8).
// No other table in the image holds them, so the slot is declared on
// AnimFile rather than inherited. The METHOD name is still unknown; only the
// class is proven, so the `FUN_<addr>` member name stays a placeholder.
// The six-byte frame table entry at +0x80E of the file object.
struct AnimFrameEntry_00426990
{
    unsigned short Value;       // +0x00  at most 0x100
    unsigned short unknown_02;
    unsigned short unknown_04;
};
GG_STATIC_ASSERT(sizeof(AnimFrameEntry_00426990) == 6);

struct SlotRgb_00426670
{
    SlotRgb_00426670() : R(0), G(0), B(0) {}
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

// VTABLE: GAMEMD 0x7E35A8
// The abstract base of AnimFile (RTTI). Its destructor is empty and the other seven slots are the
// CRT pure-call stub (0x4C9150). Only the compiler-generated deleting destructor 0x427270 is
// emitted for it, beside the AnimFile constructor that seats its vtable.
class Animate
{
public:
    virtual ~Animate() {}
    virtual bool vf_1(Delegate_00426750* delegate) = 0;
    virtual void vf_2() = 0;
    virtual int vf_3(int arg) = 0;
    virtual SlotRgb_00426670* vf_4() = 0;
    virtual int vf_5() = 0;
    virtual int vf_6() = 0;
    virtual int vf_7() = 0;
};

// VTABLE: GAMEMD 0x7E3584
class AnimFile_00426750 : public Animate
{
public:
    char              _pad004[0x84 - 0x04];
    Delegate_00426750* Delegate;   // +0x0084
    char              Retired;     // +0x0088
    char              Primed;      // +0x0089
    char              unknown_8A[0xA0 - 0x8A];
    unsigned short    unknown_A0;  // native slot 6 at 0x426A72
    unsigned short    unknown_A2;  // native slot 7 at 0x426A82
    char              unknown_A4[2];
    char              unknown_A6;  // native slot 5 at 0x426A50
    char              unknown_A7[0xCC - 0xA7];
    int               unknown_CC;  // native slot 5 at 0x426A56
    char              unknown_D0[0x50C - 0xD0];
    SlotRgb_00426670  Slots[0x100];      // +0x050C
    char              _pad80C[0x80E - 0x80C];
    AnimFrameEntry_00426990 Frames[1];   // +0x080E
    char              _pad814[0xE0C - 0x814];
    SubObject_00426790* Sub;       // +0x0E0C
    void*             Buffer;      // +0x0E10
    int               Mark1;       // +0x0E14
    int               Mark2;       // +0x0E18

    // FUNCTION: GAMEMD 0x426670 -- the constructor.
    AnimFile_00426750();
    // The destructor; the scalar deleting destructor 0x4272A0 is compiler output.
    virtual ~AnimFile_00426750();

    // The teardown shared by the destructor and slot 2.
    void Release();

    // FUNCTION: GAMEMD 0x4267F0 -- declared as a member so the tail position
    // stays a `CALL`.
    bool FUN_004267F0();

    // FUNCTION: GAMEMD 0x426750 -- slot 1
    virtual bool vf_1(Delegate_00426750* delegate);
    // FUNCTION: GAMEMD 0x426790 -- slot 2: the teardown
    virtual void vf_2();
    // Native 0x7E3584 slots 3-7: 426A90, 427290, 426A50, 426A70, 426A80.
    virtual int vf_3(int arg);
    virtual SlotRgb_00426670* vf_4();
    virtual int vf_5();
    virtual int vf_6();
    virtual int vf_7();
    // FUNCTION: GAMEMD 0x426E00 -- position the delegate on a frame and read it.
    bool FUN_00426E00(int frame);
};
GG_STATIC_ASSERT(offsetof(AnimFile_00426750, unknown_A0) == 0xa0);
GG_STATIC_ASSERT(sizeof(((AnimFile_00426750*)0)->unknown_A0) == 2);
GG_STATIC_ASSERT(offsetof(AnimFile_00426750, unknown_A2) == 0xa2);
GG_STATIC_ASSERT(sizeof(((AnimFile_00426750*)0)->unknown_A2) == 2);
GG_STATIC_ASSERT(offsetof(AnimFile_00426750, unknown_A6) == 0xa6);
GG_STATIC_ASSERT(sizeof(((AnimFile_00426750*)0)->unknown_A6) == 1);
GG_STATIC_ASSERT(offsetof(AnimFile_00426750, unknown_CC) == 0xcc);
GG_STATIC_ASSERT(sizeof(((AnimFile_00426750*)0)->unknown_CC) == 4);
GG_STATIC_ASSERT(sizeof(SlotRgb_00426670) == 3);
GG_STATIC_ASSERT(sizeof(((AnimFile_00426750*)0)->Slots) == 0x300);
GG_STATIC_ASSERT(offsetof(AnimFile_00426750, Retired) == 0x88);
GG_STATIC_ASSERT(offsetof(AnimFile_00426750, Sub) == 0xE0C);
GG_STATIC_ASSERT(offsetof(AnimFile_00426750, Buffer) == 0xE10);
GG_STATIC_ASSERT(offsetof(AnimFile_00426750, Delegate) == 0x84);
GG_STATIC_ASSERT(offsetof(AnimFile_00426750, Primed) == 0x89);
GG_STATIC_ASSERT(offsetof(AnimFile_00426750, Slots) == 0x50C);
GG_STATIC_ASSERT(offsetof(AnimFile_00426750, Frames) == 0x80E);
GG_STATIC_ASSERT(offsetof(AnimFile_00426750, Mark1) == 0xE14);
GG_STATIC_ASSERT(offsetof(AnimFile_00426750, Mark2) == 0xE18);

// ---------------------------------------------------------------------------
// 0x43A670 — release every slot of the vector at +0x08, then reset the
// sub-object at +0x04.
// ---------------------------------------------------------------------------
struct Item_0043A670
{
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual void vt_00C();
    virtual void vt_010();
    virtual void vt_014();
    virtual void vt_018();
    virtual void vt_01C();
    virtual void vt_020(int flag);   // +0x0020
};

struct Sub_0043A670
{
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual void vt_00C();           // +0x000C
};

struct Obj_0043A670
{
    char            _pad000[0x4];
    Sub_0043A670    Sub;      // +0x0004  (its vptr, reached as `LEA ECX,[EDI+4]`)
    Item_0043A670** Items;    // +0x0008
    char            _pad00C[0x14 - 0x0C];
    int             Count;    // +0x0014
    char            _pad018[0x1C - 0x18];
    int             field_1C; // +0x001C
    int             field_20; // +0x0020

    // FUNCTION: GAMEMD 0x43A6B0
    void FUN_0043A6B0(int first, int second);
};
GG_STATIC_ASSERT(offsetof(Obj_0043A670, Count) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_0043A670, field_20) == 0x20);
GG_STATIC_ASSERT(offsetof(Obj_0043A670, Sub) == 0x04);
GG_STATIC_ASSERT(offsetof(Obj_0043A670, Items) == 0x08);
GG_STATIC_ASSERT(offsetof(Obj_0043A670, Count) == 0x14);

// FUNCTION: GAMEMD 0x43A670
void FUN_0043A670(Obj_0043A670* self);

// FUNCTION: GAMEMD 0x43A6B0 — the same release, then two stack arguments
// stored at +0x1C and +0x20. `RET 8` with the object in ECX makes it a
// __thiscall member rather than the sibling's __fastcall free function.


#endif  // GG_MATCH_CORE_SMALL_MISC38_METHODS_H
