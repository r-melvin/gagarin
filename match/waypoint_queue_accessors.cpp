// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check | YRpp-cross-check

#include "waypoint_queue_accessors.h"

// FUNCTION: GAMEMD 0x717A30
void WaypointQueue_00717A30::SetHead(int value) { this->Head = value; }

// FUNCTION: GAMEMD 0x717A40
int WaypointQueue_00717A30::GetHead() const { return this->Head; }

// FUNCTION: GAMEMD 0x717A50
//
// A non-positive size is clamped up to one, as it is for the other two
// counters below.
void WaypointQueue_00717A30::SetSize(int value)
{
    if (value <= 0) {
        value = 1;
    }
    this->Size = value;
}

// FUNCTION: GAMEMD 0x717A80
void WaypointQueue_00717A30::SetTail(int value)
{
    if (value <= 0) {
        value = 1;
    }
    this->Tail = value;
}

// FUNCTION: GAMEMD 0x717AA0
int WaypointQueue_00717A30::GetTail() const { return this->Tail; }

// FUNCTION: GAMEMD 0x717AB0
void WaypointQueue_00717A30::SetExtra(int value)
{
    if (value <= 0) {
        value = 1;
    }
    this->Extra = value;
}

// FUNCTION: GAMEMD 0x717AD0
int WaypointQueue_00717A30::GetExtra() const { return this->Extra; }

// FUNCTION: GAMEMD 0x717AE0
//
// Only the head's low byte is tested, which is how retail spells the
// emptiness question on this queue.
bool WaypointQueue_00717A30::IsEmpty() const
{
    return *(const char*)&this->Head == 0;
}
