// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x750F40 and 0x750FA0.
//   Offsets and callees were read off the retail disassembly with the local
//   Ghidra CLI. Both walk the list of playing sample nodes
//   headed at 0xB1D320.
//
// Address index:
//   0x750F40  FUN_00750F40
//   0x750FA0  FUN_00750FA0

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The sample held by a node (the member at node +0x0C).
struct SampleItem_r21_4
{
    // FUNCTION: GAMEMD 0x405430 (decl; reloc)
    void FUN_00405430();
};

// The handle member at node +0x0C.
struct SampleHandle_r21_4
{
    // FUNCTION: GAMEMD 0x405FD0 (decl; reloc)
    void FUN_00405FD0();
    // FUNCTION: GAMEMD 0x405D40 (decl; reloc)
    void FUN_00405D40();
    // FUNCTION: GAMEMD 0x406130 (decl; reloc)
    SampleItem_r21_4* FUN_00406130();
};

// One playing-sample node.
struct SampleNode_r21_4
{
    char                _pad000[0xC];
    SampleHandle_r21_4  Handle;       // +0x0C
    char                _pad00D[0x20 - 0xD];
    int                 KeyA;         // +0x20
    int                 KeyB;         // +0x24
    int                 KeyC;         // +0x28
    unsigned int        Flags;        // +0x2C
    int                 Remaining;    // +0x30

    // FUNCTION: GAMEMD 0x4073E0 (decl; reloc) -- the next node.
    SampleNode_r21_4* FUN_004073E0();
    // FUNCTION: GAMEMD 0x407450 (decl; reloc)
    void FUN_00407450();
};
GG_STATIC_ASSERT(offsetof(SampleNode_r21_4, Handle) == 0xC);
GG_STATIC_ASSERT(offsetof(SampleNode_r21_4, KeyA) == 0x20);
GG_STATIC_ASSERT(offsetof(SampleNode_r21_4, Flags) == 0x2C);
GG_STATIC_ASSERT(offsetof(SampleNode_r21_4, Remaining) == 0x30);

// The list head at 0xB1D320.
struct SampleList_r21_4
{
    // FUNCTION: GAMEMD 0x4073C0 (decl; reloc) -- the first node.
    SampleNode_r21_4* FUN_004073C0();
};
// GLOBAL: GAMEMD 0xB1D320
extern SampleList_r21_4 DAT_00B1D320_r21_4;

// The node pool at the pointer 0xB1D3A4.
struct SamplePool_r21_4
{
    char _pad000[4];
};
// FUNCTION: GAMEMD 0x407530 (decl; reloc) -- give a node back to the pool.
void __fastcall FUN_00407530(SamplePool_r21_4* pool, SampleNode_r21_4* node);
// GLOBAL: GAMEMD 0xB1D3A4
extern SamplePool_r21_4* DAT_00B1D3A4_r21_4;
// GLOBAL: GAMEMD 0xB1D3A8 -- count of live nodes.
extern int DAT_00B1D3A8_r21_4;

// The three-word key a node is matched on.
struct SampleKey_r21_4
{
    int A;   // +0x00
    int B;   // +0x04
    int C;   // +0x08
};
GG_STATIC_ASSERT(sizeof(SampleKey_r21_4) == 0xC);

// FUNCTION: GAMEMD 0x750F40
//
// For each node whose flags overlap the mask and whose key equals the given
// key, run its handle's 0x405FD0.
void FUN_00750F40(const SampleKey_r21_4* key, unsigned int mask)
{
    for (SampleNode_r21_4* node = DAT_00B1D320_r21_4.FUN_004073C0(); node != 0; node = node->FUN_004073E0()) {
        if ((node->Flags & mask) && node->KeyA == key->A && node->KeyB == key->B && node->KeyC == key->C) {
            node->Handle.FUN_00405FD0();
        }
    }
}

// FUNCTION: GAMEMD 0x750FA0
//
// Tear down every node on the list: finish its handle, release it, give it
// back to the pool and drop the live count.
void FUN_00750FA0()
{
    SampleNode_r21_4* node = DAT_00B1D320_r21_4.FUN_004073C0();
    while (node != 0) {
        SampleNode_r21_4* next = node->FUN_004073E0();
        node->Handle.FUN_00405D40();
        node->FUN_00407450();
        FUN_00407530(DAT_00B1D3A4_r21_4, node);
        DAT_00B1D3A8_r21_4--;
        node = next;
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB1D320
SampleList_r21_4 DAT_00B1D320_r21_4;
// GLOBAL: GAMEMD 0xB1D3A4
SamplePool_r21_4* DAT_00B1D3A4_r21_4;
// GLOBAL: GAMEMD 0xB1D3A8
int DAT_00B1D3A8_r21_4;
// END defined globals
