// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x750F40.
//   Offsets and callees were read off the retail disassembly with the local
//   Ghidra CLI. It walks the list of playing sample nodes headed at
//   0xB1D320 (0x750FA0, the teardown walk, lives with VocClass::DeleteAll in
//   voc_class_methods.cpp).
//
// Address index:
//   0x750F40  FUN_00750F40

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/voc_class.h"

// The list head at 0xB1D320.
struct SampleList_r21_4
{
    // FUNCTION: GAMEMD 0x4073C0 (decl; reloc) -- the first node.
    VocVoiceNode* FUN_004073C0();
};
// GLOBAL: GAMEMD 0xB1D320
extern SampleList_r21_4 DAT_00B1D320_r21_4;

// The node pool at the pointer 0xB1D3A4.
struct SamplePool_r21_4
{
    char _pad000[4];
};
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
    for (VocVoiceNode* node = DAT_00B1D320_r21_4.FUN_004073C0(); node != 0; node = node->FUN_004073E0()) {
        if ((node->Flags & mask) && node->Coords.X == key->A && node->Coords.Y == key->B && node->Coords.Z == key->C) {
            node->Handle.FUN_00405FD0();
        }
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
