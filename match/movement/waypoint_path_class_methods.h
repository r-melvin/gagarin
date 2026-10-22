// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe via the local Ghidra CLI
//   (member-access disassembly at 0x763980 / 0x763BA0), cross-checked against
//   YRpp (every offset and
//   vtable slot reconfirmed numerically from the disasm here).
//
// WaypointPathClass — a mouse-placed "planning mode" waypoint path: a
// CurrentWaypointIndex plus a DynamicVectorClass<WaypointClass> of path nodes.
// The two accessors here both bounds-check an index into that vector and return
// a pointer to the element (or null).
#ifndef GG_MATCH_MOVEMENT_WAYPOINT_PATH_CLASS_H
#define GG_MATCH_MOVEMENT_WAYPOINT_PATH_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/abstract_class.h"

// WaypointClass — a single path node. The array stride is 0xC (the retail
// element address math is `Items + idx*3*4`, i.e. sizeof == 12). Two signed
// fixed-point cell coordinates + a trailing dword. Only the size is load-bearing
// for the matched methods; the fields are modelled for faithfulness.
struct WaypointClass
{
    int          X;        // +0x00
    int          Y;        // +0x04
    unsigned int unknown;  // +0x08
};
GG_STATIC_ASSERT(sizeof(WaypointClass) == 0xC);

// DynamicVectorClass<WaypointClass> as embedded at WaypointPathClass+0x28.
// Modelled with REAL virtuals so GetWaypointAfter's vtable dispatch
// `call [vptr+0x14]` (the 6th virtual, GetItemIndex) reproduces byte-for-byte.
// Virtual slot order matches retail VectorClass:
//   0x00 ~dtor, 0x04 operator==, 0x08 SetCapacity, 0x0C Clear,
//   0x10 FindItemIndex, 0x14 GetItemIndex.
struct WaypointVector
{
    virtual ~WaypointVector();                                     // +0x00
    virtual bool operator==(const WaypointVector& other) const;    // +0x04
    virtual bool SetCapacity(int capacity, WaypointClass* pMem);   // +0x08
    virtual void Clear();                                          // +0x0C
    virtual int  FindItemIndex(const WaypointClass& item) const;   // +0x10
    virtual int  GetItemIndex(const WaypointClass* pItem) const;   // +0x14

    void* Items;             // +0x04  (T** base; vptr occupies +0x00)
    int   Capacity;          // +0x08
    int   IsAllocated;       // +0x0C  (bool + 3 pad; one 4-byte cell)
    int   Count;             // +0x10
    int   CapacityIncrement; // +0x14
};
GG_STATIC_ASSERT(offsetof(WaypointVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(WaypointVector, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(WaypointVector)          == 0x18);

// WaypointPathClass : AbstractClass (COM base 0x00..0x23).
class WaypointPathClass : public AbstractClass
{
public:
    WaypointClass* GetWaypoint(int idx) const;                     // 0x763980
    WaypointClass* GetWaypointAfter(WaypointClass* pWaypoint) const;// 0x763BA0

    int            CurrentWaypointIndex; // +0x24
    WaypointVector Waypoints;            // +0x28
};
GG_STATIC_ASSERT(offsetof(WaypointPathClass, CurrentWaypointIndex) == 0x24);
GG_STATIC_ASSERT(offsetof(WaypointPathClass, Waypoints)            == 0x28);

#endif  // GG_MATCH_MOVEMENT_WAYPOINT_PATH_CLASS_H
