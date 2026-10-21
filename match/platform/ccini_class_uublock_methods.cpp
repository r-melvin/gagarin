// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x526E80.

#include "ccini_class_uublock_methods.h"

// FUNCTION: GAMEMD 0x526E80
//
// Store a binary block under a section as base64 text: the section is
// cleared, a buffer straw over the block feeds a base64 straw, and each
// 70-character line is written under the keys "1", "2", ... until the straw
// runs dry. A null section or block, or a non-positive length, is refused.
// Both straws are stack objects built and torn down explicitly (banked
// stack-object rule); the chaining call goes through the base64 straw's
// vtable slot, which cl folds to the absolute slot address.
bool CCINI_00526E80::WriteUUBlock(const char* section, const void* block, int length)
{
    if (section == 0 || block == 0 || length < 1) {
        return false;
    }

    Clear(section, 0);

    BufferStraw_00526E80 straw;
    straw.ChainTo   = 0;
    straw.ChainFrom = 0;
    straw.Vtable    = &VT_007E61F0;
    straw.Buffer.Construct(block, length);
    straw.Index     = 0;
    straw.Vtable    = &VT_007E61E0;

    Base64Straw_00526E80 b64;
    b64.ChainTo   = 0;
    b64.ChainFrom = 0;
    b64.Control   = 0;
    b64.Counter   = 0;
    b64.Vtbl      = &VT_007EB764;
    (b64.*b64.Vtbl->At_004)(&straw);

    char line[71];
    char key[32];
    int  counter = 1;
    for (;;) {
        int len = b64.Get(line, sizeof(line) - 1);
        line[len] = 0;
        if (len == 0) {
            break;
        }
        sprintf(key, STR_00817F6C, counter);
        WriteString(section, key, line);
        counter++;
    }

    ((Straw*)&b64)->Straw::~Straw();
    reinterpret_cast<MemoryBuffer*>(&straw.Buffer)->Clear();
    ((Straw*)&straw)->Straw::~Straw();
    return true;
}
