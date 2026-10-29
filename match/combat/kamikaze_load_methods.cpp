// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x54E7B0.

#include "../_layout/kamikaze_class.h"
#include "../_layout/swizzle_manager_class.h"
#include "../core/vector_add_item_free.h"

// FUNCTION: GAMEMD 0x54E7B0
//
// Restore the kamikaze node list from a save stream: a node count, then one
// raw 8-byte node per entry, each allocated fresh, its two object pointers
// queued with the swizzle manager for fix-up and the node appended through
// the inlined DynamicVectorClass::AddItem. Any negative HRESULT from the
// stream ends the load with that code; otherwise the last read's code is
// returned.
HRESULT Kamikaze::Load(IStream* stream)
{
    int  count;
    HRESULT hr = stream->Read(&count, 4, 0);
    if (hr < 0) {
        return hr;
    }

    for (int i = 0; i < count; ++i) {
        KamikazeControl* node = (KamikazeControl*)operator new(sizeof(KamikazeControl));
        hr = stream->Read(node, sizeof(KamikazeControl), 0);
        if (hr < 0) {
            return hr;
        }
        DAT_00B0C110.SwizzleManagerClass::vf_4(&node->Item);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&node->Target);
        DynamicVectorAddItemFree(&this->Nodes, node);
    }

    return hr;
}
