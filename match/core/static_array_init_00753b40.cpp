// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The __xc initialiser at 0x753B40 (entry 0x815690, the first one of the
//   block that follows): 64 records of 0x48 bytes at 0xB3FF84, each opening
//   with four 12-byte members whose constructor 0x754900 is out of line and
//   empty. Retail's loop pushes (0x754900, 4, 0xC, record) and calls the vector
//   constructor iterator 0x4068F0 once per record (ESI += 0x48, EDI = 0x40).
//   No name is attested for the array or its types; placeholders only.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Item_00754900
{
    // FUNCTION: GAMEMD 0x754900 (decl; reloc) - the empty constructor.
    Item_00754900();

    int unknown_00[3];
};
GG_STATIC_ASSERT(sizeof(Item_00754900) == 0xC);

struct Record_00753B40
{
    Item_00754900 Items[4];     // +0x00
    char unknown_30[0x18];      // +0x30
};
GG_STATIC_ASSERT(sizeof(Record_00753B40) == 0x48);

// SYNTHETIC: GAMEMD 0x753B40
// GLOBAL: GAMEMD 0xB3FF84
Record_00753B40 DAT_00B3FF84[64];
