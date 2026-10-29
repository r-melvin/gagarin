// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: SuperWeaponTypeClass ctor 0x006CE5B0 (chains AbstractTypeClass ctor
//   0x00410800; stores the four vptrs 0x7F4090 / 0x7F4074 / 0x7F406C / 0x7F4064
//   and every member below). sizeof: `PUSH 0x100` before operator new in
//   TClassFactory<SuperWeaponTypeClass>::CreateInstance 0x006BF510.
//   Primary vtable 0x007F4090 overrides slots 3/5/6/8/11/12/13/16/25.
//
// SuperWeaponTypeClass -- a superweapon type (rules-driven template). Derives
// AbstractTypeClass (sizeof 0x98).
#ifndef GG_MATCH_LAYOUT_SUPER_WEAPON_TYPE_CLASS_H
#define GG_MATCH_LAYOUT_SUPER_WEAPON_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_type_class.h"

// VTABLE: GAMEMD 0x007F4090  SuperWeaponTypeClass
// VTABLE: GAMEMD 0x007F4074  SuperWeaponTypeClass::(+0x04)
// VTABLE: GAMEMD 0x007F406C  SuperWeaponTypeClass::(+0x08)
// VTABLE: GAMEMD 0x007F4064  SuperWeaponTypeClass::(+0x0C)
class SuperWeaponTypeClass : public AbstractTypeClass
{
public:
    // FUNCTION: GAMEMD 0x6CE700 (no-initialisation constructor)
    SuperWeaponTypeClass(const AbstractNoInit& noInit);
    // FUNCTION: GAMEMD 0x6CE740 (destructor; slot 8 = 0x6CEFE0)
    virtual ~SuperWeaponTypeClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3   0x6CE7C0
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x6CE800
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6   0x6CE8D0
    virtual int vf_11();                                                  // 11  0x6CE8F0
    virtual int vf_12();                                                  // 12  0x6CE900
    virtual void vf_13(Obj_004A1D30* crc);                                // 13  0x6CE910
    virtual int vf_16();                                                  // 16  0x6CEA10
    virtual bool vf_25(CCINIClass* ini);                                  // 25  0x6CEA20
    // Slot 27 (vtable 0x7F40FC): the first argument is ignored.
    virtual int vf_27(int unused, AbstractClass* target);                 // 27  0x6CEF80

    // STATIC: GAMEMD 0x6CEEB0  (__fastcall)
    static SuperWeaponTypeClass* FindFirstOfAction(int action);

    int   ArrayIndex;              // +0x98  ctor = Array.Count @0x006CE68C
    void* WeaponType;              // +0x9C  ctor 0 @0x006CE5CB; swizzled by Load
    int   RechargeVoice;           // +0xA0  ctor -1
    int   ChargingVoice;           // +0xA4  ctor -1
    int   ImpatientVoice;          // +0xA8  ctor -1
    int   SuspendVoice;            // +0xAC  ctor -1
    int   RechargeTime;            // +0xB0  ctor 0x1194 @0x006CE5E9
    int   Type;                    // +0xB4  ctor -1
    void* SidebarImage;            // +0xB8  cameo shape; ctor 0, set by Load
    int   Action;                  // +0xBC  ctor 0
    int   SpecialSound;              // +0xC0  ctor -1
    int   StartSound;              // +0xC4  ctor -1
    void* AuxBuilding;              // +0xC8  ctor 0; swizzled by Load
    char  CameoFile[0x19];         // +0xCC  ctor [EDI]=0 @0x006CE617
    bool  UseChargeDrain;          // +0xE5  ctor 0
    bool  IsPowered;              // +0xE6  ctor 1
    bool  DisableableFromShell;              // +0xE7  ctor 0
    int   FlashSidebarTabFrames;   // +0xE8  ctor -1
    bool  AIDefendAgainst;              // +0xEC  ctor 0
    bool  PreClick;              // +0xED  ctor 0
    bool  PostClick;               // +0xEE  ctor 0
    int   PreDependent;          // +0xF0  ctor -1
    bool  ShowTimer;              // +0xF4  ctor 0
    bool  ManualControl;           // +0xF5  ctor 0
    float Range;              // +0xF8  ctor 0; floating range scale (0x6DC1C6)
    int   LineMultiplier;              // +0xFC  ctor 0; radial subdivision count
};
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, ArrayIndex)             == 0x98);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, WeaponType)             == 0x9C);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, RechargeVoice)          == 0xA0);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, ChargingVoice)          == 0xA4);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, ImpatientVoice)         == 0xA8);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, SuspendVoice)           == 0xAC);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, RechargeTime)           == 0xB0);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, Type)                   == 0xB4);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, SidebarImage)           == 0xB8);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, Action)                 == 0xBC);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, SpecialSound)             == 0xC0);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, StartSound)             == 0xC4);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, AuxBuilding)             == 0xC8);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, CameoFile)              == 0xCC);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, UseChargeDrain)         == 0xE5);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, IsPowered)             == 0xE6);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, DisableableFromShell)             == 0xE7);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, FlashSidebarTabFrames)  == 0xE8);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, AIDefendAgainst)             == 0xEC);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, PreClick)             == 0xED);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, PostClick)              == 0xEE);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, PreDependent)         == 0xF0);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, ShowTimer)             == 0xF4);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, ManualControl)          == 0xF5);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, Range)             == 0xF8);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, LineMultiplier)             == 0xFC);
GG_STATIC_ASSERT(sizeof(SuperWeaponTypeClass)                           == 0x100);

#endif  // GG_MATCH_LAYOUT_SUPER_WEAPON_TYPE_CLASS_H
