// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x750E20 / 0x7531A0.
//   Names from YRpp.

#include "vox_class_play_methods.h"

// FUNCTION: GAMEMD 0x750E20
//
// Spawn a positional EVA voice. A block is popped off the free pool, its link
// and sample handle are reset, the position and caller word are copied in, the
// sample is started through VocClass::PlayAt, and the node is spliced onto the
// live list. The live count and its high-water mark are bumped afterwards.
// Returns the play token, or 0 for a negative index / exhausted pool.
//
// PARTIAL (91.4%, 53/58): the only delta is scheduling inside the block after
// the 0x4072D0 call. Retail orders `MOV [ESI+0x30],0; MOV ECX,[EDI]; LEA
// EDX,[ESI+0x20]; PUSH EBX; MOV EAX,EDX`; cl 12.00 hoists the CSE'd `LEA EDX`
// above the At_30 store and sinks `PUSH EBX` below `MOV EAX,EDX` (same
// multiset, same registers). Tried: all six orderings of the At_30 / Coords /
// At_2C statements (copy-first drops to 86.2%, unk-first to 77.6%); the copy
// destination through a local pointer and through a reference; the source
// through a const reference; named locals for the PlayAt arguments; the copy
// folded into the PlayAt argument (77.6%); member-wise field copies (51.7%);
// an inline CoordStruct::operator= (53.4%); a placement-new constructor doing
// the Link re-arm and field fills (91.4%). The store-first statement order
// kept here is the highest-scoring and structurally the retail order.
// This pass added six more, all 91.4%: the three arm statements lifted into a
// free inline `ArmNode(node, coords, unk)` helper; the same with the node
// parameter as `VoxPlayNode* const&`; the coordinate copy alone in an inline
// helper; the PlayAt call in an inline helper taking the node; the arm and the
// call together in one inline helper; and the flat control spelling. The free
// inline helper taking the object as a pointer parameter — the lever that
// resolved 0x41D300, 0x6CB3A0 and 0x43B680 this pass — does not reach this
// scheduler decision.
void* VoxClass::PlayAtPos(int index, CoordStruct* coords, int unk)
{
    if (index < 0)
        return 0;

    VoxPlayNode* node = (VoxPlayNode*)DAT_00B1D3A4->FUN_00407520();
    if (node == 0)
        return 0;

    node->Handle.FUN_00405BE0();
    FUN_004072D0(&node->Link);
    node->At_30 = 0;
    node->Coords = *coords;
    node->At_2C = unk;

    void* result = VocClass::PlayAt(index, &node->Coords, &node->Handle);
    (&DAT_00B1D320)->FUN_00407420(&node->Link);

    DAT_00B1D3A8++;
    if (DAT_00B1D3A8 > DAT_00B1D3AC)
        DAT_00B1D3AC = DAT_00B1D3A8;

    return result;
}

// FUNCTION: GAMEMD 0x7531A0
//
// Shutdown: silence the current event, stop the streamer, drop the queue, then
// delete every table entry. Each `delete` expands the inline destructor, which
// unregisters the entry from DAT_00B1D4A0 (virtual FindItemIndex + inlined RemoveItem)
// before the block is freed; the loop runs until the table is empty.
void VoxClass::DeleteAll()
{
    if (DAT_00B1D4C4 != 0) {
        DAT_00B1D4C4->State = 2;
        DAT_00B1D4C4 = 0;
    }

    if (DAT_00B1D4CC != 0)
        DAT_00B1D4CC->FUN_00407F40();

    FUN_00752370();

    while (DAT_00B1D4A0.Count > 0) {
        delete DAT_00B1D4A0.Items[0];
    }
}
