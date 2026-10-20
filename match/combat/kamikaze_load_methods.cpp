// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x54E7B0.

#include "kamikaze_load_methods.h"

// FUNCTION: GAMEMD 0x54E7B0
//
// Restore the kamikaze node list from a save stream: a node count, then one
// raw 8-byte node per entry, each allocated fresh, its two object pointers
// queued with the swizzle manager for fix-up and the node appended through
// the inlined DynamicVectorClass::AddItem. Any negative HRESULT from the
// stream ends the load with that code; otherwise the last read's code is
// returned.
long Kamikaze::Load(IStream_0054E7B0* stream)
{
    int  count;
    long hr = stream->Read(&count, 4, 0);
    if (hr < 0) {
        return hr;
    }

    for (int i = 0; i < count; ++i) {
        KamikazeControl_0054E7B0* node =
            (KamikazeControl_0054E7B0*)operator new(sizeof(KamikazeControl_0054E7B0));
        hr = stream->Read(node, sizeof(KamikazeControl_0054E7B0), 0);
        if (hr < 0) {
            return hr;
        }
        DAT_00B0C110.FUN_006CF240(&node->Item);
        DAT_00B0C110.FUN_006CF240(&node->Target);
        this->Nodes.AddItem(node);
    }

    return hr;
}
