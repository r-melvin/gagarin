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

#include "../_layout/waypoint_class.h"
#include "../core/vector_class.h"

// WaypointPathClass : AbstractClass (COM base 0x00..0x23).
class WaypointPathClass : public AbstractClass
{
public:
    explicit WaypointPathClass(int index) throw(); // GAMEMD 0x763810, RET4
    WaypointPathClass(const AbstractNoInit& noInit) throw(); // GAMEMD 0x7637D0, RET4
    // Native primary table7F6E70 overrides; declarations only.
    virtual HRESULT __stdcall GetClassID(CLSID* id); // slot3,763C30
    virtual HRESULT __stdcall Load(IStream* stream); // slot5,763C70
    virtual HRESULT __stdcall Save(IStream* stream, BOOL clearDirty); // slot6,763D90
    virtual ~WaypointPathClass(); // slot8 deleting target763E20
    virtual int vf_11(); // slot11,763E10
    virtual int vf_12(); // slot12,763E00
    virtual void vf_13(Obj_004A1D30* crc); // slot13,763C00
    WaypointClass* GetWaypoint(int idx) const;                     // 0x763980
    WaypointClass* GetWaypointAfter(WaypointClass* pWaypoint) const;// 0x763BA0
    void SetWaypoint(int idx, const WaypointClass* pWaypoint);     // 0x763AF0
    void RemoveWaypoint(int idx);                                  // 0x763B30
    void ClearWaypoints();                                         // 0x763BE0
    bool SelectWaypointAt(const WaypointClass* pWaypoint);         // 0x763A50 (decl; reloc)
    WaypointPathClass();                                           // 0x763730 (decl; reloc)
    void AddWaypoint(const WaypointClass* pWaypoint);              // 0x7639A0 (decl; reloc)

    int            CurrentWaypointIndex; // +0x24
    DynamicVectorClass<WaypointClass> Waypoints;            // +0x28
};
GG_STATIC_ASSERT(offsetof(WaypointPathClass, CurrentWaypointIndex) == 0x24);
GG_STATIC_ASSERT(offsetof(WaypointPathClass, Waypoints)            == 0x28);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<WaypointClass>, Items) == 4);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<WaypointClass>, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<WaypointClass>) == 0x18);
GG_STATIC_ASSERT(sizeof(WaypointPathClass) == 0x40);

#endif  // GG_MATCH_MOVEMENT_WAYPOINT_PATH_CLASS_H
