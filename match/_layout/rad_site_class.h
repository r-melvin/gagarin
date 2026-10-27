// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: RadSiteClass default ctor FUN_0x0065B1E0 (chains AbstractClass ctor
//   FUN_0x00410170 at offset 0).
//   sizeof: `PUSH 0x74` before the ctor call at both allocation sites.
//   RTTI: 0x007F0810 / 0x007F07F4 (and the +8/+0xC tables) resolve to
//   ".?AVRadSiteClass@@" (stored @0x0065B228..0x0065B23C).
//   Cross-read against YRpp: 13 named members claimed, 12
//   confirmed; Tint is bounded but never written.
//
// RadSiteClass — a radiation field centred on a cell. Derives AbstractClass.
#ifndef GG_MATCH_LAYOUT_RAD_SITE_CLASS_H
#define GG_MATCH_LAYOUT_RAD_SITE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "mission_class.h"   // CDTimerClass
#include "foot_class.h"      // CellStruct

// TintStruct — 0xC, bounded by Intensity @0x54 and IntensitySteps @0x64 in
// RadSiteClass; the ctor never writes it, so its fields are not named here.
#ifndef GG_MATCH_LAYOUT_TINTSTRUCT_DEFINED
#define GG_MATCH_LAYOUT_TINTSTRUCT_DEFINED
struct TintStruct { unsigned char unknown_00[0xC]; };
GG_STATIC_ASSERT(sizeof(TintStruct) == 0xC);
#endif

class RadSiteClass : public AbstractClass
{
public:
    // The primary retail table at 0x7F0810 points to these addresses for the
    // listed slots. Each target is a table entry; this comment does not bind
    // an otherwise unimplemented member body to that address.
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID); // 0x65B470, slot 3
    virtual HRESULT __stdcall Load(IStream* pStm);         // 0x65B3D0, slot 5
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL clearDirty); // 0x65B450, slot 6
    // Slot 8 points to the native deleting-destructor entry at 0x65BED0.
    // The ordinary destructor body has not been separately identified.
    virtual ~RadSiteClass();
    virtual int vf_11();                                   // 0x65B3C0
    virtual int vf_12();                                   // 0x65B3A0
    virtual void vf_13(Obj_004A1D30* crc);                 // 0x65B3B0
    virtual void vf_23();                                  // 0x65B800

    // Native default constructor is 0x65B1E0 (thiscall, no stack arguments).
    RadSiteClass();

    // Native call contracts used by BulletClass::FUN_004690B0.
    void SetBaseCell(CellStruct* cell);  // target 0x65B4C0, thiscall RET 4
    void SetSpread(int spread);          // target 0x65B4D0, thiscall RET 4
    void SetRadLevel(int level);         // target 0x65B4F0, thiscall RET 4
    void Add(int level);                 // target 0x65B530, thiscall RET 4
    void Activate();                     // target 0x65B580, thiscall RET 0

    void*        LightSource;         // +0x24 LightSourceClass*; ctor @0x0065B1EA
    CDTimerClass RadLevelTimer;       // +0x28 ctor StartTime=[0x00A8ED84] @0x0065B1F3, TimeLeft @0x0065B1F6
    CDTimerClass RadLightTimer;       // +0x34 ctor StartTime=[0x00A8ED84] @0x0065B202, TimeLeft @0x0065B1FF
    CellStruct   BaseCell;            // +0x40 ctor word stores @0x0065B205/0x0065B209
    int          Spread;              // +0x44 ctor @0x0065B20D
    int          SpreadInLeptons;     // +0x48 ctor @0x0065B210
    int          RadLevel;            // +0x4C ctor @0x0065B213
    int          LevelSteps;          // +0x50 ctor @0x0065B216
    int          Intensity;           // +0x54 ctor @0x0065B219
    TintStruct   Tint;                // +0x58 (0xC) bounded, never written by the ctor
    int          IntensitySteps;      // +0x64 ctor @0x0065B21C
    int          IntensityDecrement;  // +0x68 ctor @0x0065B21F
    int          RadDuration;         // +0x6C ctor @0x0065B222
    int          RadTimeLeft;         // +0x70 ctor @0x0065B225; closes the object at 0x74
};

GG_STATIC_ASSERT(offsetof(RadSiteClass, LightSource)        == 0x24);
GG_STATIC_ASSERT(offsetof(RadSiteClass, RadLevelTimer)      == 0x28);
GG_STATIC_ASSERT(offsetof(RadSiteClass, RadLightTimer)      == 0x34);
GG_STATIC_ASSERT(offsetof(RadSiteClass, BaseCell)           == 0x40);
GG_STATIC_ASSERT(offsetof(RadSiteClass, Spread)             == 0x44);
GG_STATIC_ASSERT(offsetof(RadSiteClass, SpreadInLeptons)    == 0x48);
GG_STATIC_ASSERT(offsetof(RadSiteClass, RadLevel)           == 0x4C);
GG_STATIC_ASSERT(offsetof(RadSiteClass, LevelSteps)         == 0x50);
GG_STATIC_ASSERT(offsetof(RadSiteClass, Intensity)          == 0x54);
GG_STATIC_ASSERT(offsetof(RadSiteClass, Tint)               == 0x58);
GG_STATIC_ASSERT(offsetof(RadSiteClass, IntensitySteps)     == 0x64);
GG_STATIC_ASSERT(offsetof(RadSiteClass, IntensityDecrement) == 0x68);
GG_STATIC_ASSERT(offsetof(RadSiteClass, RadDuration)        == 0x6C);
GG_STATIC_ASSERT(offsetof(RadSiteClass, RadTimeLeft)        == 0x70);
GG_STATIC_ASSERT(sizeof(RadSiteClass)                       == 0x74);

// VTABLE: GAMEMD 0x007F0810  RadSiteClass
// VTABLE: GAMEMD 0x007F07F4  RadSiteClass::(+0x04)
// VTABLE: GAMEMD 0x007F07EC  RadSiteClass::(+0x08)
// VTABLE: GAMEMD 0x007F07E4  RadSiteClass::(+0x0C)

#endif  // GG_MATCH_LAYOUT_RAD_SITE_CLASS_H
