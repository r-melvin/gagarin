// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x5BBEE0; the object is
//   seven consecutive heap pointers at +0x00..+0x18 (0x5BBED0 tail-jumps here).

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A block of seven owned heap buffers (view name; the owning class is unrecovered).
struct OwnedBuffers_005BBEE0
{
    void* Buffer[7];    // +0x00

    // FUNCTION: GAMEMD 0x5BBEE0
    void FreeAll();
};
GG_STATIC_ASSERT(sizeof(OwnedBuffers_005BBEE0) == 0x1C);

// FUNCTION: GAMEMD 0x5BBEE0
// Free every buffer that is still allocated and clear its pointer.
void OwnedBuffers_005BBEE0::FreeAll()
{
    if (Buffer[0]) { delete Buffer[0]; Buffer[0] = 0; }
    if (Buffer[1]) { delete Buffer[1]; Buffer[1] = 0; }
    if (Buffer[2]) { delete Buffer[2]; Buffer[2] = 0; }
    if (Buffer[3]) { delete Buffer[3]; Buffer[3] = 0; }
    if (Buffer[4]) { delete Buffer[4]; Buffer[4] = 0; }
    if (Buffer[5]) { delete Buffer[5]; Buffer[5] = 0; }
    if (Buffer[6]) { delete Buffer[6]; Buffer[6] = 0; }
}
