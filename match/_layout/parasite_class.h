// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   ParasiteClass (retail RTTI .?AVParasiteClass@@) : AbstractClass. Layout read from the constructors at
//   0x629210 / 0x6292B0 / 0x629390 (two timers restarted at +0x2C and +0x38, state words at +0x28..+0x54),
//   the checksum at 0x6294D0 and the Load at 0x6295B0. Only members those bodies touch are named.
#ifndef GG_MATCH_LAYOUT_PARASITE_CLASS_H
#define GG_MATCH_LAYOUT_PARASITE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "frame_timer.h"
#include "obj_004a1d30.h"
#include "object_class.h"

class ParasiteClass : public AbstractClass
{
public:
    ParasiteClass();
    ParasiteClass(void* owner);
    ParasiteClass(const AbstractNoInit& noInit);
    virtual ~ParasiteClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();
    virtual void vf_13(Obj_004A1D30* crc);

    void* Owner;          // +0x24
    int unknown_28;       // +0x28
    CDTimerClass TimerA;  // +0x2C
    CDTimerClass TimerB;  // +0x38
    ObjectClass* Subject;     // +0x44
    int unknown_48;       // +0x48
    int unknown_4C;       // +0x4C
    int unknown_50;       // +0x50
    bool unknown_54;      // +0x54
};
GG_STATIC_ASSERT(offsetof(ParasiteClass, Owner) == 0x24);
GG_STATIC_ASSERT(offsetof(ParasiteClass, TimerA) == 0x2C);
GG_STATIC_ASSERT(offsetof(ParasiteClass, TimerB) == 0x38);
GG_STATIC_ASSERT(offsetof(ParasiteClass, Subject) == 0x44);
GG_STATIC_ASSERT(offsetof(ParasiteClass, unknown_54) == 0x54);
GG_STATIC_ASSERT(sizeof(ParasiteClass) == 0x58);

#endif  // GG_MATCH_LAYOUT_PARASITE_CLASS_H
