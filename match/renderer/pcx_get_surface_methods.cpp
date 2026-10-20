// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6BA140.

#include "pcx_get_surface_methods.h"

// FUNCTION: GAMEMD 0x6BA140
//
// Look a loaded PCX up by file name. The name is wrapped in a string key, the
// key's hash picks a bucket and the chain is walked comparing keys; a hit is
// copied whole into a function-scope static (whose surface is reset to null
// first, so a miss reports null), the palette is copied out when the caller
// asked for it, and the surface pointer is returned.
//
// Statement order is load-bearing twice over: the key is built (explicit
// Construct/Destruct, so no EH frame) *before* the `static` declaration, which
// is where VC6 emits the guard test and the atexit registration; declaring the
// static first put the guard ahead of the key ctor and gave the key its own
// frame slot (`PUSH ECX`) instead of the dead parameter's home slot (0%).
// The hit path re-tests the node and then the address of its payload, which
// is what leaves retail's `TEST ESI,ESI` either side of `ADD ESI,4`.
void* PCX::GetSurface(const char* filename, BytePalette_006BA140* palette)
{
    PCXKey_006BA140 key;
    key.Construct(filename);

    static PCXStatic_006BA140 entry;
    entry.Surface = 0;

    if (this->Count != 0) {
        unsigned int hash = this->Hash(&key);
        PCXNode_006BA140* node = this->Table[hash & ((1 << this->Bits) - 1)];
        while (node != 0) {
            if (node->Key.Equals(&key)) {
                if (node == 0) {
                    break;
                }
                PCXEntry_006BA140* data = &node->Data;
                if (data != 0) {
                    *(PCXEntry_006BA140*)&entry = *data;
                }
                if (palette != 0) {
                    *palette = entry.Palette;
                }
                void* surface = entry.Surface;
                key.Destruct();
                return surface;
            }
            node = node->Next;
        }
    }

    key.Destruct();
    return 0;
}
