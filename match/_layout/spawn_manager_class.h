// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: SpawnManagerClass ctor 0x006B6EA0 (chains AbstractClass ctor
//   0x00410170 at offset 0; stores the four vptrs 0x7F3650 / 0x7F3634 /
//   0x7F362C / 0x7F3624 and the members below; SpawnedNodes vptr 0x7F36B4,
//   capacity increment 10 @0x006B6EC1). sizeof: `PUSH 0x74` before operator
//   new in TClassFactory<SpawnManagerClass>::CreateInstance 0x006C0A10.
//   Primary vtable 0x007F3650 overrides slots 3/5/6/8/11/12/13/23.
//
// SpawnManagerClass -- the carrier's / spawner's launched units. Derives
// AbstractClass.
#ifndef GG_MATCH_LAYOUT_SPAWN_MANAGER_CLASS_H
#define GG_MATCH_LAYOUT_SPAWN_MANAGER_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "frame_timer.h"
#include "../core/vector_class.h"

class TechnoClass;
class AircraftClass;
class AircraftTypeClass;

// VTABLE: GAMEMD 0x007F3650  SpawnManagerClass
// VTABLE: GAMEMD 0x007F3634  SpawnManagerClass::(+0x04)
// VTABLE: GAMEMD 0x007F362C  SpawnManagerClass::(+0x08)
// VTABLE: GAMEMD 0x007F3624  SpawnManagerClass::(+0x0C)
class SpawnManagerClass : public AbstractClass
{
public:
    // One spawned unit of the manager. Only the members the matched bodies
    // read are named; the node's total size is not asserted.
    struct SpawnControl
    {
        AircraftClass* Unit;     // +0x00
        int            Status;   // +0x04 SpawnNodeStatus (Idle=0, Launching=1, 2, Reloading=6, Dead=7)
    };

    virtual ~SpawnManagerClass();                                         // 8   0x6B8140
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3   0x6B7ED0
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x6B7F10
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6   0x6B80B0
    virtual int vf_11();                                                  // 11  0x6B8130
    virtual int vf_12();                                                  // 12  0x6B8120
    virtual void vf_13(Obj_004A1D30* crc);                                // 13  0x6B7DE0
    virtual void vf_23();                                                 // 23  0x6B7230

    // FUNCTION: GAMEMD 0x6B7100 (decl; reloc) -- __thiscall.
    void FUN_006B7100();
    // FUNCTION: GAMEMD 0x6B7B90
    void SetTarget(AbstractClass* pTarget);
    // FUNCTION: GAMEMD 0x6B7BB0 (decl; reloc) -- __thiscall.
    void FUN_006B7BB0();
    // FUNCTION: GAMEMD 0x6B7D30
    int  CountAliveSpawns() const;
    // FUNCTION: GAMEMD 0x6B7D50
    int  CountDockedSpawns() const;
    // FUNCTION: GAMEMD 0x6B7D80
    int  CountLaunchingSpawns() const;

    TechnoClass*       Owner;           // +0x24 ctor 0
    AircraftTypeClass* SpawnType;       // +0x28 ctor 0
    int                SpawnCount;      // +0x2C ctor 0
    int                unknown_30;      // +0x30 never written by the ctor
    int                unknown_34;      // +0x34 never written by the ctor
    DynamicVectorClass<SpawnControl*> SpawnedNodes;  // +0x38 Items@0x3C, Count@0x48
    CDTimerClass       SpawnTimer;      // +0x50 StartTime = CurrentFrame
    CDTimerClass       UpdateTimer;     // +0x5C StartTime = CurrentFrame
    AbstractClass*     Target;          // +0x68 ctor 0
    AbstractClass*     NewTarget;       // +0x6C ctor 0
    int                unknown_70;      // +0x70 ctor 0
};
GG_STATIC_ASSERT(offsetof(SpawnManagerClass::SpawnControl, Unit)   == 0x00);
GG_STATIC_ASSERT(offsetof(SpawnManagerClass::SpawnControl, Status) == 0x04);
GG_STATIC_ASSERT(offsetof(SpawnManagerClass, Owner)        == 0x24);
GG_STATIC_ASSERT(offsetof(SpawnManagerClass, SpawnType)    == 0x28);
GG_STATIC_ASSERT(offsetof(SpawnManagerClass, SpawnCount)   == 0x2C);
GG_STATIC_ASSERT(offsetof(SpawnManagerClass, SpawnedNodes) == 0x38);
GG_STATIC_ASSERT(offsetof(SpawnManagerClass, SpawnTimer)   == 0x50);
GG_STATIC_ASSERT(offsetof(SpawnManagerClass, UpdateTimer)  == 0x5C);
GG_STATIC_ASSERT(offsetof(SpawnManagerClass, Target)       == 0x68);
GG_STATIC_ASSERT(offsetof(SpawnManagerClass, NewTarget)    == 0x6C);
GG_STATIC_ASSERT(offsetof(SpawnManagerClass, unknown_70)   == 0x70);
GG_STATIC_ASSERT(sizeof(SpawnManagerClass)                 == 0x74);

#endif  // GG_MATCH_LAYOUT_SPAWN_MANAGER_CLASS_H
