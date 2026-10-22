// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail constructor 0x725FA0..0x726132 writes this prefix. The allocation
// paths at 0x6E4DE0 and 0x726630 request 0x48 bytes. Raw TypeDescriptor
// 0x842CE8 names ".?AVTriggerClass@@"; primary vtable 0x7F5858 uses COL 0x80C968.
// The explicit base vptr fields preserve the ABI while COM inheritance is pending.
#ifndef GG_MATCH_LAYOUT_TRIGGER_CLASS_H
#define GG_MATCH_LAYOUT_TRIGGER_CLASS_H
#include <stddef.h>
#include "abstract_class.h"
#include "vector_class.h"
#include "../core/frame_counter.h"
class TriggerTypeClass;
class ObjectClass;
struct CellStruct;

// Timer storage as read/written at +0x34 by 0x725FA0 and 0x726400.
// The middle dword is not initialized by either observed value constructor.
struct CDTimer_00726400
{
    int StartTime;
    int unknown_04;
    int TimeLeft;
    CDTimer_00726400() {}
    explicit CDTimer_00726400(int duration)
    {
        StartTime = CurrentFrame;
        TimeLeft = duration;
    }
};
GG_STATIC_ASSERT(offsetof(CDTimer_00726400, StartTime) == 0);
GG_STATIC_ASSERT(offsetof(CDTimer_00726400, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(CDTimer_00726400, TimeLeft) == 8);
GG_STATIC_ASSERT(sizeof(CDTimer_00726400) == 0xC);

class TriggerClass : public AbstractClass
{
public:
    // Overrides of the slots AbstractClass leaves pure (primary table
    // slots 3, 5, 6, 11, 12; declarations only, bodies not modelled here).
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3   0x726820
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x726860
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6   0x7268D0
    virtual int vf_11();                                                  // 11  0x726940
    virtual int vf_12();                                                  // 12  0x726930
    // FUNCTION: GAMEMD 0x725FA0 (constructor declaration)
    TriggerClass(TriggerTypeClass* type);
    // FUNCTION: GAMEMD 0x726250
    bool HasCrossesHorizontalLineEvent() const;
    // FUNCTION: GAMEMD 0x726290
    bool HasCrossesVerticalLineEvent() const;
    // FUNCTION: GAMEMD 0x7262D0
    bool HasZoneEntryByEvent() const;
    // FUNCTION: GAMEMD 0x726310
    bool HasAllowWinAction() const;
    // FUNCTION: GAMEMD 0x726350
    bool HasGlobalSetOrClearedEvent(int index) const;
    // FUNCTION: GAMEMD 0x7263A0
    void NotifyGlobalChanged(int index);
    // FUNCTION: GAMEMD 0x7263D0
    void NotifyLocalChanged(int index);
    // FUNCTION: GAMEMD 0x726400
    void ResetTimers();
    // FUNCTION: GAMEMD 0x7264C0 (decl; reloc) -- RET 0x14.
    bool FUN_007264C0(int event, ObjectClass* object, bool flag, bool persistent, int arg);
    // FUNCTION: GAMEMD 0x7265C0
    bool FireActions(ObjectClass* object, CellStruct location);
    // FUNCTION: GAMEMD 0x726630
    static TriggerClass* __fastcall GetInstance(TriggerTypeClass* type);
    // FUNCTION: GAMEMD 0x726720
    void Destroy();

    TriggerTypeClass* Type;
    // Both existing source names denote the same observed link at +0x28.
    union { TriggerClass* AttachedTrigger; TriggerClass* NextTrigger; };
    void* unknown_2C;
    bool Destroyed;
    unsigned char unknown_31[3];
    CDTimer_00726400 Timer;
    unsigned int OccuredEvents;
    bool Enabled;
    unsigned char unknown_45[3];
    // GLOBAL: GAMEMD 0xA8EAE8
    static DynamicVectorClassLayout Array;
};
GG_STATIC_ASSERT(offsetof(TriggerClass, Type) == 0x24);
GG_STATIC_ASSERT(offsetof(TriggerClass, AttachedTrigger) == 0x28);
GG_STATIC_ASSERT(offsetof(TriggerClass, NextTrigger) == 0x28);
GG_STATIC_ASSERT(offsetof(TriggerClass, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(TriggerClass, Destroyed) == 0x30);
GG_STATIC_ASSERT(offsetof(TriggerClass, Timer) == 0x34);
GG_STATIC_ASSERT(offsetof(TriggerClass, OccuredEvents) == 0x40);
GG_STATIC_ASSERT(offsetof(TriggerClass, Enabled) == 0x44);
GG_STATIC_ASSERT(sizeof(TriggerClass) == 0x48);
#endif
