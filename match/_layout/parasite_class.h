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

class FootClass;

class ParasiteClass : public AbstractClass
{
public:
    ParasiteClass();
    ParasiteClass(FootClass* owner);
    ParasiteClass(const AbstractNoInit& noInit);
    virtual ~ParasiteClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    // FUNCTION: GAMEMD 0x62A260 (slot 10) -- drop the references held to an object that goes away.
    virtual void vf_10(void* target, bool removed);
    virtual int vf_11();
    virtual int vf_12();
    virtual void vf_13(Obj_004A1D30* crc);

    // FUNCTION: GAMEMD 0x629530 -- the destructor's first half: clears the state words, releases the subject
    // and leaves the registry of parasites that hold a victim.
    void FUN_00629530();
    // FUNCTION: GAMEMD 0x62A4A0 (decl; reloc) -- __thiscall, no stack arguments.
    void FUN_0062A4A0();
    // FUNCTION: GAMEMD 0x62A8E0 (decl; reloc) -- thiscall, one stack argument (RET 4).
    bool CanInfect(FootClass* target);
    // FUNCTION: GAMEMD 0x62A980 (decl; reloc) -- thiscall, one pointer stack argument (RET 4): release the current subject and latch onto the target.
    void FUN_0062A980(FootClass* target);
    // CALLEE: GAMEMD 0x62AC30 -- thiscall, one hidden result pointer (RET 4): a coordinate near the owner.
    CoordStruct FUN_0062AC30();

    FootClass* Owner;     // +0x24
    FootClass* unknown_28;// +0x28 (the object this parasite sits on; its +0x694 points back)
    CDTimerClass TimerA;  // +0x2C
    CDTimerClass TimerB;  // +0x38
    ObjectClass* Subject;     // +0x44
    int unknown_48;       // +0x48
    int unknown_4C;       // +0x4C
    int unknown_50;       // +0x50
    bool unknown_54;      // +0x54
};
GG_STATIC_ASSERT(offsetof(ParasiteClass, Owner) == 0x24);
GG_STATIC_ASSERT(offsetof(ParasiteClass, unknown_28) == 0x28);
GG_STATIC_ASSERT(sizeof(((ParasiteClass*)0)->Owner) == 4);
GG_STATIC_ASSERT(offsetof(ParasiteClass, TimerA) == 0x2C);
GG_STATIC_ASSERT(offsetof(ParasiteClass, TimerB) == 0x38);
GG_STATIC_ASSERT(offsetof(ParasiteClass, Subject) == 0x44);
GG_STATIC_ASSERT(offsetof(ParasiteClass, unknown_54) == 0x54);
GG_STATIC_ASSERT(sizeof(ParasiteClass) == 0x58);

#endif  // GG_MATCH_LAYOUT_PARASITE_CLASS_H
