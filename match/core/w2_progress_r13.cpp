// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x642A30 (ProgressScreenClass destructor body, vtable 0x7F0064): restores the vptr,
//   frees the owned buffer at +0x54 and clears it. The constructor 0x6429E0 is left unmatched.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   Address index: 0x642A30 destructor body.
//   The class is declared locally with only the members these bodies touch.

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

class ProgressScreenClass
{
public:
    virtual ~ProgressScreenClass();

    unsigned char unknown_04[4];
    unsigned char unknown_08[0x40];  // +0x08
    int unknown_48;                  // +0x48
    int unknown_4C;                  // +0x4C
    int unknown_50;                  // +0x50
    void* Buffer;                    // +0x54
    bool BufferOwned;                // +0x58
    int unknown_5C;                  // +0x5C
    bool unknown_60;                 // +0x60
    bool unknown_61;                 // +0x61
    bool unknown_62;                 // +0x62
    int unknown_64;                  // +0x64
    int unknown_68;                  // +0x68
    int unknown_6C;                  // +0x6C
    bool unknown_70;                 // +0x70
    int unknown_74;                  // +0x74
    int unknown_78;                  // +0x78
    int unknown_7C;                  // +0x7C
    int unknown_80;                  // +0x80
};
GG_STATIC_ASSERT(offsetof(ProgressScreenClass, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(ProgressScreenClass, Buffer) == 0x54);
GG_STATIC_ASSERT(offsetof(ProgressScreenClass, unknown_80) == 0x80);

// FUNCTION: GAMEMD 0x642A30
// Destructor body: frees the owned buffer.
ProgressScreenClass::~ProgressScreenClass()
{
    if (BufferOwned) {
        delete Buffer;
        BufferOwned = false;
    }
    Buffer = 0;
}
