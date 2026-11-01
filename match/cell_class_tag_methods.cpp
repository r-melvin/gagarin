// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x485250.

#include "cell_class_tag_methods.h"

// FUNCTION: GAMEMD 0x485250
//
// Swap the tag attached to this cell. The old tag (if any) loses one instance,
// the new one gains one, and the cell's coordinate is appended to the global
// tagged-cell vector so the trigger scan can find it again.
//
// The append is DynamicVectorClass::AddItem, which VC6 inlines here (the body
// lives in the header): grow first when full (only if the storage is owned or
// still empty, and the step is positive), then post-increment Count and store.
// The vector's answer is discarded — the new tag is counted whether or not the
// coordinate was recorded — and the tag re-read for the INC comes from the
// member (`MOV ESI,[ESI+0x3C]`), not the argument.
void CellClass::ReplaceTag(TagClass* tag)
{
    if (this->AttachedTag != 0) {
        this->AttachedTag->InstanceCount--;
    }

    this->AttachedTag = tag;

    if (tag != 0) {
        DAT_00880944.AddItem(this->MapCoords);
        this->AttachedTag->InstanceCount++;
    }
}
