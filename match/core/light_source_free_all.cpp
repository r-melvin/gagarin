// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Body read from the retail function at 0x5549A0 (0xB4 bytes, plain RET).
#include "vector_class_operations.h"
#include "../_layout/light_source_class.h"

// GLOBAL: GAMEMD 0x829AE4 -- latched false while the light lists are being torn down.
extern bool DAT_00829AE4;
// GLOBAL: GAMEMD 0xABCA10 -- the light source registry.
extern DynamicVectorClass<LightSourceClass*> DAT_00ABCA10;
struct StaticVectorHolder_00ABCA40 {
    // GLOBAL: GAMEMD 0x00ABCA40
    static DynamicVectorClass<LightSourceClass::PendingCellClass*> DAT_00ABCA40;
};

// FUNCTION: GAMEMD 0x5549A0
// Destroy every registered light source, then free every queued pending-cell entry.
void FUN_005549A0()
{
    DAT_00829AE4 = false;
    while (DAT_00ABCA10.Count != 0) {
        delete DAT_00ABCA10.Items[0];
        DAT_00ABCA10.Delete(0);
    }
    while (StaticVectorHolder_00ABCA40::DAT_00ABCA40.Count != 0) {
        delete StaticVectorHolder_00ABCA40::DAT_00ABCA40.Items[0];
        StaticVectorHolder_00ABCA40::DAT_00ABCA40.Delete(0);
    }
    DAT_00829AE4 = true;
}
