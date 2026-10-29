// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: FactoryClass default ctor 0x004C98B0 (chains AbstractClass ctor
//   0x00410170 at offset 0; stores the four vptrs 0x7E88D0 / 0x7E88B4 /
//   0x7E88AC / 0x7E88A4 and every member below; QueuedObjects vptr 0x7E8934,
//   capacity increment 10 @0x004C98ED). sizeof 0x74: the member run ends with
//   IsManual @0x71 (ctor MOV byte [ESI+0x71],1 @0x004C98F7).
//   Primary vtable 0x007E88D0 overrides slots 3/5/6/8/10/11/12/13/23.
//
// FactoryClass -- the production queue of one house. Derives AbstractClass.
#ifndef GG_MATCH_LAYOUT_FACTORY_CLASS_H
#define GG_MATCH_LAYOUT_FACTORY_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "stage_class.h"
#include "../core/vector_class.h"

class TechnoClass;
class TechnoTypeClass;
class HouseClass;
class ObjectClass;

// VTABLE: GAMEMD 0x007E88D0  FactoryClass
// VTABLE: GAMEMD 0x007E88B4  FactoryClass::(+0x04)
// VTABLE: GAMEMD 0x007E88AC  FactoryClass::(+0x08)
// VTABLE: GAMEMD 0x007E88A4  FactoryClass::(+0x0C)
class FactoryClass : public AbstractClass
{
public:
    // FUNCTION: GAMEMD 0x4C98B0 (declaration; default constructor)
    FactoryClass();
    virtual ~FactoryClass();                                              // 8   0x4CA770
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3   0x4CA230
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x4CA270
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6   0x4CA3C0
    virtual void vf_10(void* target, bool removed);                       // 10  0x4CA580
    virtual int vf_11();                                                  // 11  0x4CA750
    virtual int vf_12();                                                  // 12  0x4CA760
    virtual void vf_13(Obj_004A1D30* crc);                                // 13  0x4CA430
    virtual void vf_23();                                                 // 23  0x4C9B20

    // Declared ascending by retail address.
    bool HasProgressChanged();                                // 0x4C9C60
    bool Suspend(bool manual);                                // 0x4C9E60
    int  GetBuildTimeFrames() const;                          // 0x4C9FB0
    int  GetProgress() const;                                 // 0x4CA120
    bool IsDone() const;                                      // 0x4CA130
    // FUNCTION: GAMEMD 0x4CA160 (decl; reloc) -- the object being produced.
    ObjectClass* FUN_004CA160();
    bool CompletedProduction();                               // 0x4CA1A0
    void StartProduction();                                   // 0x4CA5A0
    bool RemoveOneFromQueue(TechnoTypeClass const* pItem);    // 0x4CA620
    int  CountTotal(TechnoTypeClass const* pType) const;      // 0x4CA670
    bool IsQueued(TechnoTypeClass* pType) const;              // 0x4CA6B0
    // FUNCTION: GAMEMD 0x4C9E10 -- takes `object` as the item in production, done and suspended.
    void FUN_004C9E10(TechnoClass* object);
    // FUNCTION: GAMEMD 0x4C9FF0 (decl; reloc) -- gives up the current production.
    bool AbandonProduction();
    // FUNCTION: GAMEMD 0x4C9EA0 (decl; reloc) -- resumes a suspended production (defined on the unsuspend view).
    bool Unsuspend(bool manual);

    StageClass   Production;            // +0x24  progress; Value == 0x36 when done
    DynamicVectorClass<TechnoTypeClass const*> QueuedObjects;  // +0x40 ctor vptr 0x7E8934
    TechnoClass* Object;                // +0x58  item currently in production
    bool         OnHold;                // +0x5C
    bool         IsDifferent;           // +0x5D  set when progress changed this frame
    unsigned char _pad_5E[2];           // +0x5E
    int          Balance;               // +0x60
    int          OriginalBalance;       // +0x64
    int          SpecialItem;           // +0x68  special-weapon item; -1 = none
    HouseClass*  Owner;                 // +0x6C
    bool         IsSuspended;           // +0x70
    bool         IsManual;              // +0x71
    unsigned char _pad_72[2];           // +0x72
};
GG_STATIC_ASSERT(offsetof(FactoryClass, Production)       == 0x24);
GG_STATIC_ASSERT(offsetof(FactoryClass, Production.Timer) == 0x2C);
GG_STATIC_ASSERT(offsetof(FactoryClass, Production.Rate)  == 0x38);
GG_STATIC_ASSERT(offsetof(FactoryClass, QueuedObjects)    == 0x40);
GG_STATIC_ASSERT(offsetof(FactoryClass, Object)           == 0x58);
GG_STATIC_ASSERT(offsetof(FactoryClass, OnHold)           == 0x5C);
GG_STATIC_ASSERT(offsetof(FactoryClass, IsDifferent)      == 0x5D);
GG_STATIC_ASSERT(offsetof(FactoryClass, Balance)          == 0x60);
GG_STATIC_ASSERT(offsetof(FactoryClass, OriginalBalance)  == 0x64);
GG_STATIC_ASSERT(offsetof(FactoryClass, SpecialItem)      == 0x68);
GG_STATIC_ASSERT(offsetof(FactoryClass, Owner)            == 0x6C);
GG_STATIC_ASSERT(offsetof(FactoryClass, IsSuspended)      == 0x70);
GG_STATIC_ASSERT(offsetof(FactoryClass, IsManual)         == 0x71);
GG_STATIC_ASSERT(sizeof(FactoryClass)                     == 0x74);

#endif  // GG_MATCH_LAYOUT_FACTORY_CLASS_H
