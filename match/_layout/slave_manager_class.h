// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: SlaveManagerClass ctor 0x006AF1A0 (chains AbstractClass ctor
//   0x00410170 at offset 0; stores the four vptrs 0x7F31C8 / 0x7F31AC /
//   0x7F31A4 / 0x7F319C and every member below; SlaveNodes vptr 0x7F322C,
//   capacity increment 10 @0x006AF1C9). sizeof: `PUSH 0x64` before operator
//   new in TClassFactory<SlaveManagerClass>::CreateInstance 0x006C0B90.
//   Primary vtable 0x007F31C8 overrides slots 3/5/6/8/11/12/13/23.
//
// SlaveManagerClass -- the slave-miner's owned slaves. Derives AbstractClass.
#ifndef GG_MATCH_LAYOUT_SLAVE_MANAGER_CLASS_H
#define GG_MATCH_LAYOUT_SLAVE_MANAGER_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "frame_timer.h"
#include "../core/vector_class.h"

class TechnoClass;
class InfantryClass;
class InfantryTypeClass;
struct SlaveObject;

// VTABLE: GAMEMD 0x007F31C8  SlaveManagerClass
// VTABLE: GAMEMD 0x007F31AC  SlaveManagerClass::(+0x04)
// VTABLE: GAMEMD 0x007F31A4  SlaveManagerClass::(+0x08)
// VTABLE: GAMEMD 0x007F319C  SlaveManagerClass::(+0x0C)
class SlaveManagerClass : public AbstractClass
{
public:
    // One slave of the manager (a 0x14-byte heap node, CreateSlave 0x6AF650).
    struct SlaveControl
    {
        InfantryClass* Slave;          // +0x00 ctor 0
        int            State;          // +0x04 SlaveControlStatus
        CDTimerClass   RespawnTimer;   // +0x08 StartTime = CurrentFrame, TimeLeft 0
    };

    // FUNCTION: GAMEMD 0x6AF1A0 (declaration; constructor)
    SlaveManagerClass(TechnoClass* owner, InfantryTypeClass* slaveType,
                      int slaveCount, int regenRate, int reloadRate);
    // FUNCTION: GAMEMD 0x6AF360 -- default constructor (registers in the slave manager array).
    SlaveManagerClass();
    // FUNCTION: GAMEMD 0x6AF440 -- NoInit constructor (load path).
    SlaveManagerClass(const AbstractNoInit& noInit);
    virtual ~SlaveManagerClass();                                         // 8   0x6B1390
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3   0x6B1130
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x6B1170
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6   0x6B1300
    virtual int vf_11();                                                  // 11  0x6B1380
    virtual int vf_12();                                                  // 12  0x6B1370
    virtual void vf_13(Obj_004A1D30* crc);                                // 13  0x6B10F0
    virtual void vf_23();                                                 // 23  0x6AF5F0

    TechnoClass*       Owner;           // +0x24 ctor arg1
    InfantryTypeClass* SlaveType;       // +0x28 ctor arg2
    int                SlaveCount;      // +0x2C ctor arg3
    int                RegenRate;       // +0x30 ctor arg4; respawn delay of a node
    int                ReloadRate;      // +0x34 ctor arg5
    DynamicVectorClass<SlaveControl*> SlaveNodes;  // +0x38 Items@0x3C, Count@0x48
    CDTimerClass       RespawnTimer;    // +0x50 ctor StartTime=CurrentFrame
    int                State;           // +0x5C SlaveManagerStatus
    int                LastScanFrame;   // +0x60

    // Members recovered in r19_5 (match/combat/slave_manager_r19_5.cpp).
    // FUNCTION: GAMEMD 0x6AF6C0 (decl; reloc)
    void FUN_006AF6C0();
    // FUNCTION: GAMEMD 0x6AFD60 (decl; reloc)
    void FUN_006AFD60();
    // FUNCTION: GAMEMD 0x6AF650 -- creates and initializes one slave.
    void CreateSlave(SlaveControl* node);
    // FUNCTION: GAMEMD 0x6B0490 -- orders every live slave to Guard.
    void GuardAllSlaves();
    // FUNCTION: GAMEMD 0x6B0A20 -- detaches a lost slave and restarts its timer.
    void LostSlave(SlaveObject* slave);
    // Order every live slave to go idle and set State = 1 / 4 (0x6B0CC0 / 0x6B0D10).
    void SetStateIdle1();
    void SetStateIdle4();
};
GG_STATIC_ASSERT(offsetof(SlaveManagerClass::SlaveControl, Slave)        == 0x00);
GG_STATIC_ASSERT(offsetof(SlaveManagerClass::SlaveControl, State)        == 0x04);
GG_STATIC_ASSERT(offsetof(SlaveManagerClass::SlaveControl, RespawnTimer) == 0x08);
GG_STATIC_ASSERT(sizeof(InfantryClass*)                                   == 0x04);
GG_STATIC_ASSERT(sizeof(int)                                              == 0x04);
GG_STATIC_ASSERT(sizeof(CDTimerClass)                                     == 0x0C);
GG_STATIC_ASSERT(sizeof(SlaveManagerClass::SlaveControl)                 == 0x14);
GG_STATIC_ASSERT(offsetof(SlaveManagerClass, Owner)         == 0x24);
GG_STATIC_ASSERT(offsetof(SlaveManagerClass, SlaveType)     == 0x28);
GG_STATIC_ASSERT(offsetof(SlaveManagerClass, SlaveCount)    == 0x2C);
GG_STATIC_ASSERT(offsetof(SlaveManagerClass, RegenRate)     == 0x30);
GG_STATIC_ASSERT(offsetof(SlaveManagerClass, ReloadRate)    == 0x34);
GG_STATIC_ASSERT(offsetof(SlaveManagerClass, SlaveNodes)    == 0x38);
GG_STATIC_ASSERT(offsetof(SlaveManagerClass, RespawnTimer)  == 0x50);
GG_STATIC_ASSERT(offsetof(SlaveManagerClass, State)         == 0x5C);
GG_STATIC_ASSERT(offsetof(SlaveManagerClass, LastScanFrame) == 0x60);
GG_STATIC_ASSERT(sizeof(SlaveManagerClass)                  == 0x64);

#endif  // GG_MATCH_LAYOUT_SLAVE_MANAGER_CLASS_H
