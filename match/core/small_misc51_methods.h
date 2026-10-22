// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, the vtable slot and the arithmetic read numerically off the user's
//   retail gamemd.exe v1.001 via the local Ghidra CLI at 0x45F1D0.
//
// Hand back a shape and half its second dimension. A cached shape at +0x14F4
// short-circuits the lookup but still answers *false*, so the caller can tell a
// freshly resolved shape from a remembered one; only a fresh shape that is more
// than six units across answers true, and then the reported value carries a
// +3 bias the cached path does not.
//
// `MOVSX EAX,word ptr [EAX+6]; CDQ; SUB EAX,EDX; SAR EAX,1` is the signed
// divide-by-two idiom on a 16-bit member.
#ifndef GG_MATCH_CORE_SMALL_MISC51_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC51_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Shape_0045F1D0
{
    char  _pad000[0x6];
    short Height;   // +0x0006
};
GG_STATIC_ASSERT(offsetof(Shape_0045F1D0, Height) == 0x6);

struct Obj_0045F1D0
{
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual void vt_00C();
    virtual void vt_010();
    virtual void vt_014();
    virtual void vt_018();
    virtual void vt_01C();
    virtual void vt_020();
    virtual void vt_024();
    virtual void vt_028();
    virtual void vt_02C();
    virtual void vt_030();
    virtual void vt_034();
    virtual void vt_038();
    virtual void vt_03C();
    virtual void vt_040();
    virtual void vt_044();
    virtual void vt_048();
    virtual void vt_04C();
    virtual void vt_050();
    virtual void vt_054();
    virtual void vt_058();
    virtual void vt_05C();
    virtual void vt_060();
    virtual void vt_064();
    virtual void vt_068();
    virtual void vt_06C();
    virtual void vt_070();
    virtual void vt_074();
    virtual void vt_078();
    virtual void vt_07C();
    virtual void vt_080();
    virtual void vt_084();
    virtual void vt_088();
    virtual void vt_08C();
    virtual void vt_090();
    virtual void vt_094();
    virtual void vt_098();
    virtual Shape_0045F1D0* vt_09C();   // +0x009C

    char            _pad004[0x14F4 - 0x04];
    Shape_0045F1D0* Cached;    // +0x14F4
    char            _pad14F8[0x1768 - 0x14F8];
    char            Enabled;   // +0x1768

    // FUNCTION: GAMEMD 0x45F160 — the sibling that reports a bias rather than a
    // measurement: a cached shape answers true with zero, a fresh one wide
    // enough answers true with three, and everything else false.
    bool FUN_0045F160(Shape_0045F1D0** shape, int* bias);
    // FUNCTION: GAMEMD 0x45F1D0
    bool FUN_0045F1D0(Shape_0045F1D0** shape, int* half);
};
GG_STATIC_ASSERT(offsetof(Obj_0045F1D0, Cached) == 0x14F4);
GG_STATIC_ASSERT(offsetof(Obj_0045F1D0, Enabled) == 0x1768);

// ---------------------------------------------------------------------------
// 0x4079C0 — settle the working extent, then publish it.
//
// Two preparation steps run first, then the requested extent at +0xA0 is capped
// by the buffer's own at +0x08 and stored back to +0x90. Retail branches for
// that rather than computing a min branchlessly, and it re-reads +0x38 for each
// use instead of holding it.
// ---------------------------------------------------------------------------
struct Buffer_004079C0
{
    char _pad000[0x4];
    int  Origin;     // +0x0004
    int  Capacity;   // +0x0008
};
GG_STATIC_ASSERT(offsetof(Buffer_004079C0, Capacity) == 0x8);

struct Sub_004079C0
{
    char             _pad000[0x38];
    Buffer_004079C0* Buffer;     // +0x0038
    char             _pad03C[0x90 - 0x3C];
    int              Extent;     // +0x0090
    char             _pad094[0xA0 - 0x94];
    int              Requested;  // +0x00A0
};
GG_STATIC_ASSERT(offsetof(Sub_004079C0, Buffer) == 0x38);
GG_STATIC_ASSERT(offsetof(Sub_004079C0, Extent) == 0x90);
GG_STATIC_ASSERT(offsetof(Sub_004079C0, Requested) == 0xA0);

// FUNCTION: GAMEMD 0x4091C0 / 0x409310 — the two preparation steps.
void __fastcall FUN_004091C0(Buffer_004079C0* buffer, int extent);
void __fastcall FUN_00409310(Buffer_004079C0* buffer);

struct Obj_004079C0
{
    char           _pad000[0xC0];
    Sub_004079C0*  Sub;        // +0x00C0
    char           _pad0C4[0x170 - 0xC4];
    int            Origin;     // +0x0170
    int            ExtentA;    // +0x0174
    int            ExtentB;    // +0x0178
};
GG_STATIC_ASSERT(offsetof(Obj_004079C0, Sub) == 0xC0);
GG_STATIC_ASSERT(offsetof(Obj_004079C0, ExtentB) == 0x178);

// FUNCTION: GAMEMD 0x4079C0
int __fastcall FUN_004079C0(Obj_004079C0* self);

// ---------------------------------------------------------------------------
// 0x408460 — allocate a node and its payload, or clean up and answer null.
//
// The node is zeroed wholesale (`MOV ECX,8; XOR EAX,EAX; REP STOSD` - the
// inline `memset` for 0x20 bytes) and then four of its fields are written to
// zero again. Retail keeps both, so the explicit stores are dead and have to be
// volatile to survive; the zero for them is re-materialised in EDI rather than
// reusing the EAX the `REP STOSD` consumed.
//
// A failed payload allocation frees the node - guarded against null even though
// it was just dereferenced - and answers null.
// ---------------------------------------------------------------------------
extern "C" void* __cdecl FUN_007C8E17(unsigned int size);
extern "C" void  __cdecl FUN_007C8B3D(void* block);
extern "C" void* __cdecl memset(void* destination, int value, unsigned int count);

// FUNCTION: GAMEMD 0x4072C0 — initialises the list header at +0x08.
void __fastcall FUN_004072C0(void* header);

struct Node_00408460
{
    void* Payload;    // +0x0000
    int   Size;       // +0x0004
    char  Header[0x14 - 0x08];   // +0x0008
    int   field_14;   // +0x0014
    int   field_18;   // +0x0018
    char  _pad01C[0x20 - 0x1C];
};
GG_STATIC_ASSERT(sizeof(Node_00408460) == 0x20);

// FUNCTION: GAMEMD 0x408460
Node_00408460* __fastcall FUN_00408460(int size);

// ---------------------------------------------------------------------------
// 0x402790 — adopt a node and cache what it points at.
//
// The node is recorded first and unconditionally. If it resolves to an item the
// three cached values come from the item and the node's first word is cleared;
// otherwise they come from the node itself, re-read through the field just
// stored rather than from the register still holding it.
//
// Both the item and the fallback write the same value to +0x174 and +0x178 from
// a single load, so it is held in a local; written as two reads VC6 loads it
// twice.
// ---------------------------------------------------------------------------
struct Item_00402790
{
    char _pad000[0xC];
    int  First;    // +0x000C
    int  Second;   // +0x0010
};
GG_STATIC_ASSERT(offsetof(Item_00402790, Second) == 0x10);

struct Node_00402790
{
    int First;    // +0x0000
    int Second;   // +0x0004
};

// FUNCTION: GAMEMD 0x408520 — resolve the node to an item, __fastcall.
Item_00402790* __fastcall FUN_00408520(Node_00402790* node);

struct Obj_00402790
{
    char            _pad000[0x168];
    Node_00402790*  Node;      // +0x0168
    Item_00402790*  Item;      // +0x016C
    int             CachedA;   // +0x0170
    int             CachedB;   // +0x0174
    int             CachedC;   // +0x0178
};
GG_STATIC_ASSERT(offsetof(Obj_00402790, Node) == 0x168);
GG_STATIC_ASSERT(offsetof(Obj_00402790, CachedC) == 0x178);

// FUNCTION: GAMEMD 0x402790
void __fastcall FUN_00402790(Obj_00402790* self, Node_00402790* node);

#endif  // GG_MATCH_CORE_SMALL_MISC51_METHODS_H
