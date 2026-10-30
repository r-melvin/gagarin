// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x54E7B0.

#include "../_layout/kamikaze_class.h"
#include "../_layout/aircraft_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/swizzle_manager_class.h"
#include "../core/vector_add_item_free.h"

// FUNCTION: GAMEMD 0x54E4D0
//
// Periodic re-arm of every kamikaze aircraft. Once the update timer has run
// out it is re-wound to 30 frames and each node's aircraft is given one round
// of ammo, re-targeted — on its registered target, or failing that on the
// cell straight ahead of its current facing — and told to attack.
//
// The two SetTarget/QueueMission tails are written out per arm with a
// `continue`: retail carries `MOV EDX,[ESI]; PUSH reg` in each arm and
// cross-jumps only from `MOV ECX,ESI` onward. Folding the target into one
// variable puts it in EAX and merges the push; an if/else with the compute
// arm first gives the second arm's vtable EAX and no merge at all. The 3-bit
// facing is taken straight off the Current() temporary so it is evaluated
// (into EDI) before the GetCell call rather than pushed early or sunk after.
void Kamikaze::Update()
{
    if (this->UpdateTimer.GetTimeLeft() == 0) {
        this->UpdateTimer = CDTimerClass(30);

        for (int i = 0; i < this->Nodes.Count; ++i) {
            KamikazeControl* node = this->Nodes.Items[i];
            AbstractClass* target = node->Target;
            AircraftClass* unit = node->Item;
            unit->Ammo = 1;

            if (target == 0) {
                int facing = ((unit->PrimaryFacing.FUN_004C93D0().Whole >> 12) + 1 >> 1) & 7;
                CellClass* cell = unit->vf_111();
                CellClass* ahead = cell->GetNeighbourCell(facing);
                unit->vf_242(ahead);
                unit->vf_122(1, 0);
                continue;
            }
            unit->vf_242(target);
            unit->vf_122(1, 0);
        }
    }
}

// FUNCTION: GAMEMD 0x54E750  (__thiscall)
// Serialise the node vector: first the node count, then each 8-byte node.
// Returns the last IStream::Write HRESULT (kept in EAX); a failed write breaks
// out early and is returned verbatim.
HRESULT Kamikaze::Save(IStream* pStm)
{
    int count = Nodes.Count;
    HRESULT hr = pStm->Write(&count, 4, 0);
    if (hr >= 0)
    {
        for (int i = 0; i < count; ++i)
        {
            hr = pStm->Write(Nodes.Items[i], 8, 0);
            if (hr < 0)
                break;
        }
    }
    return hr;
}

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
