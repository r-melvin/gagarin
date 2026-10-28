// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: SuperClass ctor FUN_0x006CAF90 (chains AbstractClass ctor
//   FUN_0x00410170 at offset 0; sizeof(AbstractClass) == 0x24).
//   sizeof: `PUSH 0x80` before the ctor call at its allocation site.
//   RTTI: 0x007F3FE8 / 0x007F3FCC / 0x007F3FC4 / 0x007F3FBC all resolve to
//   ".?AVSuperClass@@" (stored @0x006CAFF7..0x006CB00A).
//   Cross-read against YRpp: 18 named members claimed, 16
//   confirmed, 1 (SpecialSoundLocation) left in place but never written by the
//   ctor and so recorded as unknown, plus the PROTECTED_PROPERTY paddings.
//
// SuperClass — one super weapon owned by a house. Derives AbstractClass.
#ifndef GG_MATCH_LAYOUT_SUPER_CLASS_H
#define GG_MATCH_LAYOUT_SUPER_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "mission_class.h"   // CDTimerClass
#include "object_class.h"    // CoordStruct
#include "foot_class.h"      // CellStruct

class SuperClass : public AbstractClass
{
public:
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID); // slot3, existing body
    virtual HRESULT __stdcall Load(IStream* pStm);          // slot5  0x6CDEF0
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty); // slot6 existing body
    virtual void vf_10(void* target, bool removed);         // slot10 0x6CDFF0
    virtual int vf_11();                                    // slot11 0x6CE200
    virtual int vf_12();                                    // slot12 0x6CE210
    virtual int __stdcall vf_rtti_3();                      // +4 table slot3 0x6CE1F0
    virtual void vf_13(Obj_004A1D30* crc);                  // slot13 0x6CE020
    int GetRechargeTime() const; // 0x6CC260
    // The stream loader's in-place construction: the base only (retail 0x410170).
    struct LoadTag {};
    SuperClass(LoadTag) {}
    int           CustomChargeTime;      // +0x24 ctor MOV [ESI+0x24],EAX(-1) @0x006CAFA7
    void*         Type;                  // +0x28 SuperWeaponTypeClass*; ctor =arg1 @0x006CAFA4
    void*         Owner;                 // +0x2C HouseClass*; ctor =arg2 @0x006CAFAA
    CDTimerClass  RechargeTimer;         // +0x30 ctor StartTime=[0x00A8ED84] @0x006CAFB5,
                                         //       TimeLeft=0 @0x006CAFB8
    unsigned int  unused_3C;             // +0x3C (PROTECTED_PROPERTY; ctor never writes it)
    unsigned char BlinkState;            // +0x40 ctor @0x006CAFBE
    unsigned char unused_41[7];          // +0x41 (PROTECTED_PROPERTY; BlinkTimer is 8-aligned)
    unsigned int  BlinkTimer_Low;        // +0x48 LARGE_INTEGER low half; ctor @0x006CAFBB
    unsigned int  BlinkTimer_High;       // +0x4C LARGE_INTEGER high half; ctor @0x006CAFC1
    int           SpecialSoundDuration;  // +0x50 ctor MOV [ESI+0x50],EAX(-1) @0x006CAFC4
    CoordStruct   SpecialSoundLocation;  // +0x54 (0xC) never written by the ctor; bounded by
                                         //       SpecialSoundDuration and CanHold
    unsigned char CanHold;               // +0x60 ctor MOV byte [ESI+0x60],1 @0x006CAFC7
    unsigned char unused_61;             // +0x61 (PROTECTED_PROPERTY)
    CellStruct    ChronoMapCoords;       // +0x62 ctor MOV [ESI+0x62],EDX(=[0x00B0C000]) @0x006CAFDA
    unsigned char unused_66[2];          // +0x66 (PROTECTED_PROPERTY)
    void*         Animation;             // +0x68 AnimClass*; ctor @0x006CAFDE
    unsigned char AnimationGotInvalid;   // +0x6C ctor @0x006CAFE1
    unsigned char IsPresent;             // +0x6D ctor @0x006CAFE4
    unsigned char IsOneTime;             // +0x6E ctor @0x006CAFE7
    unsigned char IsReady;               // +0x6F ctor @0x006CAFEA
    unsigned char IsSuspended;           // +0x70 ctor @0x006CAFED
    unsigned char unused_71[3];          // +0x71 (PROTECTED_PROPERTY)
    int           ReadyFrame;            // +0x74 ctor MOV [ESI+0x74],-100 @0x006CAFF0
    int           CameoChargeState;      // +0x78 ctor @0x006CAFD1 (=-1)
    int           ChargeDrainState;      // +0x7C ctor @0x006CAFD4 (=-1); closes the object at 0x80
};

GG_STATIC_ASSERT(offsetof(SuperClass, CustomChargeTime)     == 0x24);
GG_STATIC_ASSERT(offsetof(SuperClass, Type)                 == 0x28);
GG_STATIC_ASSERT(offsetof(SuperClass, Owner)                == 0x2C);
GG_STATIC_ASSERT(offsetof(SuperClass, RechargeTimer)        == 0x30);
GG_STATIC_ASSERT(offsetof(SuperClass, unused_3C)            == 0x3C);
GG_STATIC_ASSERT(offsetof(SuperClass, BlinkState)           == 0x40);
GG_STATIC_ASSERT(offsetof(SuperClass, BlinkTimer_Low)       == 0x48);
GG_STATIC_ASSERT(offsetof(SuperClass, BlinkTimer_High)      == 0x4C);
GG_STATIC_ASSERT(offsetof(SuperClass, SpecialSoundDuration) == 0x50);
GG_STATIC_ASSERT(offsetof(SuperClass, SpecialSoundLocation) == 0x54);
GG_STATIC_ASSERT(offsetof(SuperClass, CanHold)              == 0x60);
GG_STATIC_ASSERT(offsetof(SuperClass, ChronoMapCoords)      == 0x62);
GG_STATIC_ASSERT(offsetof(SuperClass, Animation)            == 0x68);
GG_STATIC_ASSERT(offsetof(SuperClass, AnimationGotInvalid)  == 0x6C);
GG_STATIC_ASSERT(offsetof(SuperClass, IsSuspended)          == 0x70);
GG_STATIC_ASSERT(offsetof(SuperClass, ReadyFrame)           == 0x74);
GG_STATIC_ASSERT(offsetof(SuperClass, CameoChargeState)     == 0x78);
GG_STATIC_ASSERT(offsetof(SuperClass, ChargeDrainState)     == 0x7C);
GG_STATIC_ASSERT(sizeof(SuperClass)                         == 0x80);

// VTABLE: GAMEMD 0x007F3FE8  SuperClass
// VTABLE: GAMEMD 0x007F3FCC  SuperClass::(+0x04)
// VTABLE: GAMEMD 0x007F3FC4  SuperClass::(+0x08)
// VTABLE: GAMEMD 0x007F3FBC  SuperClass::(+0x0C)

#endif  // GG_MATCH_LAYOUT_SUPER_CLASS_H
