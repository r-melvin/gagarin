// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: AnimClass ctor FUN_0x00421EA0 (chains ObjectClass ctor
//   FUN_0x005F3900 at offset 0; sizeof(ObjectClass) == 0xAC, already asserted
//   in object_class.h). The ctor writes every member in the 0xAC..0x1C7 span;
//   each member carries the address of its initialising store.
//
//   sizeof: `PUSH 0x1C8` precedes the ctor call at the allocation sites found
//   by `ghidra x-ref to 0x421EA0`. (Beware when repeating that measurement:
//   the most common constant pushed near this ctor is 0x600, which is the
//   *default argument* for the `flags` parameter, not an allocation size.)
//
//   RTTI (read from the binary): the four vptrs stored at 0x0042201C..0x00422030
//   (0x007E3354 / 0x007E3338 / 0x007E3330 / 0x007E3328) all resolve to
//   ".?AVAnimClass@@", COL base-offset 0 / 4 / 8 / 12.
//
//   Three structural facts the ctor settles outright:
//     * Animation is a StageClass at 0xAC — Value 0xAC, HasChanged 0xB0,
//       Timer.StartTime 0xB4, Timer.TimeLeft 0xBC, Rate 0xC0, Step 0xC4(=1).
//       Exactly the StageClass shape already proven in techno_class.h.
//     * Accum really does default to 1.0: the ctor stores 0 to 0x188 and
//       0x3FF00000 to 0x18C, which is the IEEE-754 double 1.0.
//     * SkipProcessOnce (0x19C) and RemainingIterations (0x195) are the only
//       two fields in the 0x194..0x19E bool run set to 1.
//
//   Cross-read against YRpp AnimClass.h: 37 named members claimed, 37
//   confirmed. No disagreement found.
//
// AnimClass — a playing animation. Derives ObjectClass at offset 0.
#ifndef GG_MATCH_LAYOUT_ANIM_CLASS_H
#define GG_MATCH_LAYOUT_ANIM_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "object_class.h"     // ObjectClass spine + CoordStruct + AudioController
#include "techno_class.h"     // StageClass

struct AnimTypeClass;

// BounceClass — the projectile-bounce physics block embedded in AnimClass at
// 0x128. Size 0x50, proven by closure: the ctor takes EDI = this+0x128, stores
// through [EDI+0x04]/[EDI+0x08]/[EDI+0x0C]/[EDI+0x10]/[EDI+0x14]
// (@0x00421F73..0x00421F86) and runs FUN_0x00645C30 on [EDI+0x30] and
// [EDI+0x40] (@0x00421F7A..0x00421F96); the next member the ctor touches is at
// 0x178 == 0x128 + 0x50. Individual field names are NOT established, so the
// block goes in as opaque storage rather than as named members.
#ifndef GG_MATCH_LAYOUT_BOUNCECLASS_DEFINED
#define GG_MATCH_LAYOUT_BOUNCECLASS_DEFINED
struct BounceClass
{
    unsigned char unknown_00[0x50];   // +0x00 .. 0x4F
};
GG_STATIC_ASSERT(sizeof(BounceClass) == 0x50);
#endif

struct AnimClass : ObjectClass
{
    // FUNCTION: GAMEMD 0x421EA0 (declaration; constructor, RET 0x1C)
    AnimClass(AnimTypeClass* type, const CoordStruct& coord, int loopDelay, int loopCount,
              unsigned int flags, int forceZ, bool reverse);
    // Overrides of the pure base slots (declarations; bodies not recovered here).
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();

    StageClass      Animation;             // +0xAC (0x1C) ctor @0x00421EB8..0x00421EDB
    void*           Type;                  // +0xC8 AnimTypeClass*; ctor MOV [ESI+0xC8],ECX(=arg1) @0x00421EE5
    void*           OwnerObject;           // +0xCC ObjectClass*; ctor @0x00421EEE
    unsigned int    unknown_D0;            // +0xD0 ctor @0x00421EF4
    void*           LightConvert;          // +0xD4 LightConvertClass*; ctor @0x00421EFA
    int             LightConvertIndex;     // +0xD8 ctor @0x00421F00
    char            PaletteName[0x20];     // +0xDC .. 0xFB  ctor zeroes the first byte
                                           //   (MOV byte [ESI+0xDC],BL @0x00422037); width is fixed by
                                           //   the next confirmed member at 0xFC
    int             TintColor;             // +0xFC ctor MOV [ESI+0xFC],0x3E8 @0x00421F06
    int             ZAdjust;               // +0x100 ctor @0x00421F10
    int             YSortAdjust;           // +0x104 ctor @0x00421F16
    CoordStruct     FlamingGuyCoords;      // +0x108 (0xC) ctor LEA EDX,[ESI+0x108] @0x00421F21
    int             FlamingGuyRetries;     // +0x114 ctor @0x00421F53
    unsigned char   IsBuildingAnim;        // +0x118 ctor @0x00421F44
    unsigned char   UnderTemporal;         // +0x119 ctor @0x00421F4A
    unsigned char   Paused;                // +0x11A ctor @0x00421F59
    unsigned char   Unpaused;              // +0x11B ctor @0x00421F5F
    int             PausedAnimFrame;       // +0x11C ctor @0x00421F65
    unsigned char   Reverse;               // +0x120 ctor @0x00421F6B
    unsigned char   padding_121[7];        // +0x121 (PROTECTED_PROPERTY; Bounce is 8-aligned)
    BounceClass     Bounce;                // +0x128 (0x50) ctor via EDI = this+0x128 @0x00421F27
    unsigned char   TranslucencyLevel;     // +0x178 ctor @0x00421FAA
    unsigned char   TimeToDie;             // +0x179 ctor @0x00421FB0
    unsigned char   align_17A[2];          // +0x17A
    void*           AttachedBullet;        // +0x17C BulletClass*; ctor @0x00421FB6
    void*           Owner;                 // +0x180 HouseClass*; ctor @0x00421FBC
    int             LoopDelay;             // +0x184 ctor MOV [ESI+0x184],ECX(=arg LoopDelay) @0x00421FC2
    double          Accum;                 // +0x188 (8) ctor stores 0 @0x00421FA4 and 0x3FF00000
                                           //   @0x00421FC8 — the double 1.0
    unsigned int    AnimFlags;             // +0x190 BlitterFlags; ctor MOV [ESI+0x190],EDX(=arg flags) @0x00421FD2
    unsigned char   HasExtras;             // +0x194 ctor @0x00421FD8
    unsigned char   RemainingIterations;   // +0x195 ctor MOV byte [ESI+0x195],1 @0x00421FDE
    unsigned char   UseCellLightConvert;   // +0x196 ctor @0x00421FE5
    unsigned char   DeleteOnMapCleanup;    // +0x197 ctor @0x00421FEB
    unsigned char   IsInert;               // +0x198 ctor @0x00421FF1
    unsigned char   IsFogged;              // +0x199 ctor @0x00421FF7
    unsigned char   FlamingGuyExpire;      // +0x19A ctor @0x00421FFD
    unsigned char   UnableToContinue;      // +0x19B ctor @0x00422003
    unsigned char   SkipProcessOnce;       // +0x19C ctor MOV byte [ESI+0x19C],1 @0x00422009
    unsigned char   Invisible;             // +0x19D ctor @0x00422010
    unsigned char   PowerOff;              // +0x19E ctor @0x00422016
    unsigned char   unused_19F;            // +0x19F (PROTECTED_PROPERTY)
    AudioController StartSoundAudioController; // +0x1A0 (0x14) ctor LEA ECX,[ESI+0x1A0];
                                               //   CALL 0x00405BE0 @0x00422042
    AudioController StopSoundAudioController;  // +0x1B4 (0x14) ctor LEA ECX,[ESI+0x1B4];
                                               //   CALL 0x00405BE0 @0x0042204D; closes the object at 0x1C8
};

GG_STATIC_ASSERT(offsetof(AnimClass, Animation)                 == 0xAC);
GG_STATIC_ASSERT(offsetof(AnimClass, Type)                      == 0xC8);
GG_STATIC_ASSERT(offsetof(AnimClass, OwnerObject)               == 0xCC);
GG_STATIC_ASSERT(offsetof(AnimClass, unknown_D0)                == 0xD0);
GG_STATIC_ASSERT(offsetof(AnimClass, LightConvert)              == 0xD4);
GG_STATIC_ASSERT(offsetof(AnimClass, LightConvertIndex)         == 0xD8);
GG_STATIC_ASSERT(offsetof(AnimClass, PaletteName)               == 0xDC);
GG_STATIC_ASSERT(offsetof(AnimClass, TintColor)                 == 0xFC);
GG_STATIC_ASSERT(offsetof(AnimClass, ZAdjust)                   == 0x100);
GG_STATIC_ASSERT(offsetof(AnimClass, YSortAdjust)               == 0x104);
GG_STATIC_ASSERT(offsetof(AnimClass, FlamingGuyCoords)          == 0x108);
GG_STATIC_ASSERT(offsetof(AnimClass, FlamingGuyRetries)         == 0x114);
GG_STATIC_ASSERT(offsetof(AnimClass, IsBuildingAnim)            == 0x118);
GG_STATIC_ASSERT(offsetof(AnimClass, UnderTemporal)             == 0x119);
GG_STATIC_ASSERT(offsetof(AnimClass, Paused)                    == 0x11A);
GG_STATIC_ASSERT(offsetof(AnimClass, Unpaused)                  == 0x11B);
GG_STATIC_ASSERT(offsetof(AnimClass, PausedAnimFrame)           == 0x11C);
GG_STATIC_ASSERT(offsetof(AnimClass, Reverse)                   == 0x120);
GG_STATIC_ASSERT(offsetof(AnimClass, Bounce)                    == 0x128);
GG_STATIC_ASSERT(offsetof(AnimClass, TranslucencyLevel)         == 0x178);
GG_STATIC_ASSERT(offsetof(AnimClass, TimeToDie)                 == 0x179);
GG_STATIC_ASSERT(offsetof(AnimClass, AttachedBullet)            == 0x17C);
GG_STATIC_ASSERT(offsetof(AnimClass, Owner)                     == 0x180);
GG_STATIC_ASSERT(offsetof(AnimClass, LoopDelay)                 == 0x184);
GG_STATIC_ASSERT(offsetof(AnimClass, Accum)                     == 0x188);
GG_STATIC_ASSERT(offsetof(AnimClass, AnimFlags)                 == 0x190);
GG_STATIC_ASSERT(offsetof(AnimClass, HasExtras)                 == 0x194);
GG_STATIC_ASSERT(offsetof(AnimClass, RemainingIterations)       == 0x195);
GG_STATIC_ASSERT(offsetof(AnimClass, UseCellLightConvert)       == 0x196);
GG_STATIC_ASSERT(offsetof(AnimClass, DeleteOnMapCleanup)        == 0x197);
GG_STATIC_ASSERT(offsetof(AnimClass, IsInert)                   == 0x198);
GG_STATIC_ASSERT(offsetof(AnimClass, IsFogged)                  == 0x199);
GG_STATIC_ASSERT(offsetof(AnimClass, FlamingGuyExpire)          == 0x19A);
GG_STATIC_ASSERT(offsetof(AnimClass, UnableToContinue)          == 0x19B);
GG_STATIC_ASSERT(offsetof(AnimClass, SkipProcessOnce)           == 0x19C);
GG_STATIC_ASSERT(offsetof(AnimClass, Invisible)                 == 0x19D);
GG_STATIC_ASSERT(offsetof(AnimClass, PowerOff)                  == 0x19E);
GG_STATIC_ASSERT(offsetof(AnimClass, StartSoundAudioController) == 0x1A0);
GG_STATIC_ASSERT(offsetof(AnimClass, StopSoundAudioController)  == 0x1B4);
GG_STATIC_ASSERT(sizeof(AnimClass)                              == 0x1C8);

// VTABLE: GAMEMD 0x007E3354  AnimClass            (COL base 0)
// VTABLE: GAMEMD 0x007E3338  AnimClass::(+0x04)   (COL base 4)
// VTABLE: GAMEMD 0x007E3330  AnimClass::(+0x08)   (COL base 8)
// VTABLE: GAMEMD 0x007E3328  AnimClass::(+0x0C)   (COL base 12)

#endif  // GG_MATCH_LAYOUT_ANIM_CLASS_H
