// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x54E4D0.

#include "../_layout/kamikaze_class.h"
#include "../_layout/aircraft_class.h"
#include "../_layout/cell_class.h"

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
                unit->vf_242((int)ahead);
                unit->vf_122(1, 0);
                continue;
            }
            unit->vf_242((int)target);
            unit->vf_122(1, 0);
        }
    }
}
