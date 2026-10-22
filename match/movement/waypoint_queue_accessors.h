// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI over the run 0x717A30..0x717AE0: the head at +0x00, then
//   three counters at +0x04, +0x08 and +0x0C whose setters all clamp a
//   non-positive argument up to one (`TEST EAX,EAX; JG; MOV EAX,1`). The
//   emptiness test reads only the low byte of the head, which is why the head
//   is reached twice at two widths. Every offset and
//   convention is derived here.
#ifndef GG_MATCH_MOVEMENT_WAYPOINT_QUEUE_ACCESSORS_H
#define GG_MATCH_MOVEMENT_WAYPOINT_QUEUE_ACCESSORS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct WaypointQueue_00717A30
{
    int Head;    // +0x0000
    int Size;    // +0x0004
    int Tail;    // +0x0008
    int Extra;   // +0x000C

    // FUNCTION: GAMEMD 0x717A30
    void SetHead(int value);
    // FUNCTION: GAMEMD 0x717A40
    int GetHead() const;
    // FUNCTION: GAMEMD 0x717A50
    void SetSize(int value);
    // FUNCTION: GAMEMD 0x717A80
    void SetTail(int value);
    // FUNCTION: GAMEMD 0x717AA0
    int GetTail() const;
    // FUNCTION: GAMEMD 0x717AB0
    void SetExtra(int value);
    // FUNCTION: GAMEMD 0x717AD0
    int GetExtra() const;
    // FUNCTION: GAMEMD 0x717AE0
    bool IsEmpty() const;
};
GG_STATIC_ASSERT(offsetof(WaypointQueue_00717A30, Head)  == 0x0);
GG_STATIC_ASSERT(offsetof(WaypointQueue_00717A30, Size)  == 0x4);
GG_STATIC_ASSERT(offsetof(WaypointQueue_00717A30, Tail)  == 0x8);
GG_STATIC_ASSERT(offsetof(WaypointQueue_00717A30, Extra) == 0xC);

#endif  // GG_MATCH_MOVEMENT_WAYPOINT_QUEUE_ACCESSORS_H
