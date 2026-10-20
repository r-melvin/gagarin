// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: BulletClass ctor FUN_0x00466380 (chains ObjectClass ctor
//   FUN_0x005F3900 at offset 0; sizeof(ObjectClass) == 0xAC). Secondary
//   sources: the small setter at 0x004664C0 (writes Target 0x10C, Speed 0x110,
//   WH 0x128) and the seven BulletClass-bound addresses in the YRpp method map.
//
//   sizeof: `PUSH 0x160` precedes the ctor call at its allocation site.
//
//   RTTI (read from the binary): the four vptrs stored at 0x00466425..0x00466438
//   (0x007E46E4 / 0x007E46C8 / 0x007E46C0 / 0x007E46B8) all resolve to
//   ".?AVBulletClass@@".
//
//   Two widths the binary settles that the ctor alone would not:
//     * BulletVelocity is three doubles at 0xE8/0xF0/0xF8 — `LEA EDI,[EBX+0xE8]`
//       @0x00468694, `MOV dword [EBX+0xEC],0x40590000` @0x004689D1 (the high
//       half of 100.0), `FLD double [EBX+0xF0]` @0x004689A5 and
//       `FLD double [EBX+0xF8]` @0x004689B8. Size 0x18, ending at 0x100.
//     * LastMapCoords is a CellStruct (two shorts) at 0x14C: the ctor stores
//       `MOV word [ESI+0x14C],AX` and `MOV word [ESI+0x14E],AX` (AX = 0xFFFF)
//       @0x00466407/0x0046640E.
//
//   NOT CONFIRMED — these go in as unknown_XX rather than on YRpp's say-so:
//     * 0xE4: YRpp calls it a DWORD. The ctor never writes it and the only
//       [reg+0xE4] in BulletClass code (@0x0046A3E0) is taken off a virtual
//       call's return value, not off the bullet.
//     * 0x11C: YRpp claims a DWORD. No store or load found anywhere.
//     * 0x120..0x127: YRpp claims a single `double unknown_120`. The ctor
//       zeroes 0x120 (@0x004663AA) and 0x124 (@0x004663E9) as two separate
//       dword stores, 0x3F bytes apart in the instruction stream — which is
//       how VC6 would zero two ints, not how it zeroes a double. We record two
//       unnamed dwords; the offsets are identical either way, so no matching
//       attempt is blocked by the ambiguity. (`FLD float [EAX+0x124]`
//       @0x00469180 is NOT evidence for a float here: EAX is loaded from
//       [ECX+0xAC], i.e. it is the BulletTypeClass, not the bullet.)
//     * 0x15C: YRpp calls it `int Range`. No access found.
//
//   Cross-read against YRpp BulletClass.h: 28 named members claimed, 24
//   confirmed, 4 recorded as unknown_XX (above).
//
// BulletClass — a projectile in flight. Derives ObjectClass at offset 0.
#ifndef GG_MATCH_LAYOUT_BULLET_CLASS_H
#define GG_MATCH_LAYOUT_BULLET_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "object_class.h"     // ObjectClass spine + CoordStruct
#include "foot_class.h"       // CellStruct

// BulletData — the flight-state block embedded at BulletClass+0xB8. Size 0x28,
// proven by closure: the ctor takes ECX = this+0xB8 and calls its constructor
// FUN_0x004E1100 (@0x0046638B/0x004663A3); the next confirmed member (Bright)
// is at 0xE0 == 0xB8 + 0x28. Field names are NOT established.
#ifndef GG_MATCH_LAYOUT_BULLETDATA_DEFINED
#define GG_MATCH_LAYOUT_BULLETDATA_DEFINED
struct BulletData
{
    unsigned char unknown_00[0x28];   // +0x00 .. 0x27
};
GG_STATIC_ASSERT(sizeof(BulletData) == 0x28);
#endif

// BulletVelocity — three doubles (X, Y, Z). See header note for the FLD sites.
#ifndef GG_MATCH_LAYOUT_BULLETVELOCITY_DEFINED
#define GG_MATCH_LAYOUT_BULLETVELOCITY_DEFINED
struct BulletVelocity
{
    double X;   // +0x00
    double Y;   // +0x08
    double Z;   // +0x10
};
GG_STATIC_ASSERT(offsetof(BulletVelocity, Y) == 0x08);
GG_STATIC_ASSERT(offsetof(BulletVelocity, Z) == 0x10);
GG_STATIC_ASSERT(sizeof(BulletVelocity)      == 0x18);
#endif

struct BulletClass : ObjectClass
{
    void*          Type;                // +0xAC BulletTypeClass*; ctor @0x00466391
    void*          Owner;               // +0xB0 TechnoClass*;     ctor @0x00466397
    unsigned char  unknown_B4;          // +0xB4 ctor MOV byte [ESI+0xB4],BL @0x0046639D
    unsigned char  align_B5[3];         // +0xB5
    BulletData     Data;                // +0xB8 (0x28) ctor LEA ECX,[ESI+0xB8]; CALL 0x004E1100
    unsigned char  Bright;              // +0xE0 ctor @0x004663BF
    unsigned char  align_E1[3];         // +0xE1
    unsigned int   unknown_E4;          // +0xE4 NOT confirmed — see header note
    BulletVelocity Velocity;            // +0xE8 (0x18) see header note
    unsigned int   unknown_100;         // +0x100 ctor @0x004663C5
    unsigned char  unknown_104;         // +0x104 ctor MOV byte [ESI+0x104],AL(=1) @0x004663B0
    unsigned char  CourseLock;          // +0x105 ctor MOV byte [ESI+0x105],AL(=1) @0x004663B6
    unsigned char  align_106[2];        // +0x106
    int            CourseLockCounter;   // +0x108 ctor @0x004663CB
    void*          Target;              // +0x10C AbstractClass*; ctor @0x004663D1;
                                        //   setter MOV [ECX+0x10C],EDX @0x004664C8
    int            Speed;               // +0x110 ctor @0x004663D7; setter @0x004664D2
    int            InheritedColor;      // +0x114 ctor @0x004663DD (=-1); also @0x00466533
    unsigned int   unknown_118;         // +0x118 ctor @0x004663E3
    unsigned int   unknown_11C;         // +0x11C NOT confirmed — see header note
    unsigned int   unknown_120;         // +0x120 ctor @0x004663AA (=0)
    unsigned int   unknown_124;         // +0x124 ctor @0x004663E9 (=0)
    void*          WH;                  // +0x128 WarheadTypeClass*; ctor @0x004663EF;
                                        //   setter MOV [ECX+0x128],EDX @0x004664DC
    unsigned char  AnimFrame;           // +0x12C ctor @0x004663F5; also @0x00466507
    unsigned char  AnimRateCounter;     // +0x12D ctor @0x004663FB; also @0x00466513
    unsigned char  align_12E[2];        // +0x12E
    void*          WeaponType;          // +0x130 WeaponTypeClass*; ctor @0x00466401
    CoordStruct    SourceCoords;        // +0x134 (0xC) ctor @0x00466444/0x0046644A/0x00466450
    CoordStruct    TargetCoords;        // +0x140 (0xC) ctor @0x00466456/0x0046645C/0x00466462
    CellStruct     LastMapCoords;       // +0x14C (4) ctor two word stores @0x00466407/0x0046640E
    int            DamageMultiplier;    // +0x150 read at 0x004697FC and IMUL'd against
                                        //   ObjectClass::Health [ESI+0x6C] — same receiver, so this
                                        //   really is a damage scale on the bullet
    void*          NextAnim;            // +0x154 AnimClass*; ctor @0x00466419
    unsigned char  SpawnNextAnim;       // +0x158 ctor @0x0046641F
    unsigned char  align_159[3];        // +0x159
    int            unknown_15C;         // +0x15C NOT confirmed (YRpp calls it Range); closes at 0x160
};

GG_STATIC_ASSERT(offsetof(BulletClass, Type)              == 0xAC);
GG_STATIC_ASSERT(offsetof(BulletClass, Owner)             == 0xB0);
GG_STATIC_ASSERT(offsetof(BulletClass, unknown_B4)        == 0xB4);
GG_STATIC_ASSERT(offsetof(BulletClass, Data)              == 0xB8);
GG_STATIC_ASSERT(offsetof(BulletClass, Bright)            == 0xE0);
GG_STATIC_ASSERT(offsetof(BulletClass, unknown_E4)        == 0xE4);
GG_STATIC_ASSERT(offsetof(BulletClass, Velocity)          == 0xE8);
GG_STATIC_ASSERT(offsetof(BulletClass, unknown_100)       == 0x100);
GG_STATIC_ASSERT(offsetof(BulletClass, unknown_104)       == 0x104);
GG_STATIC_ASSERT(offsetof(BulletClass, CourseLock)        == 0x105);
GG_STATIC_ASSERT(offsetof(BulletClass, CourseLockCounter) == 0x108);
GG_STATIC_ASSERT(offsetof(BulletClass, Target)            == 0x10C);
GG_STATIC_ASSERT(offsetof(BulletClass, Speed)             == 0x110);
GG_STATIC_ASSERT(offsetof(BulletClass, InheritedColor)    == 0x114);
GG_STATIC_ASSERT(offsetof(BulletClass, unknown_118)       == 0x118);
GG_STATIC_ASSERT(offsetof(BulletClass, unknown_11C)       == 0x11C);
GG_STATIC_ASSERT(offsetof(BulletClass, unknown_120)       == 0x120);
GG_STATIC_ASSERT(offsetof(BulletClass, unknown_124)       == 0x124);
GG_STATIC_ASSERT(offsetof(BulletClass, WH)                == 0x128);
GG_STATIC_ASSERT(offsetof(BulletClass, AnimFrame)         == 0x12C);
GG_STATIC_ASSERT(offsetof(BulletClass, AnimRateCounter)   == 0x12D);
GG_STATIC_ASSERT(offsetof(BulletClass, WeaponType)        == 0x130);
GG_STATIC_ASSERT(offsetof(BulletClass, SourceCoords)      == 0x134);
GG_STATIC_ASSERT(offsetof(BulletClass, TargetCoords)      == 0x140);
GG_STATIC_ASSERT(offsetof(BulletClass, LastMapCoords)     == 0x14C);
GG_STATIC_ASSERT(offsetof(BulletClass, DamageMultiplier)  == 0x150);
GG_STATIC_ASSERT(offsetof(BulletClass, NextAnim)          == 0x154);
GG_STATIC_ASSERT(offsetof(BulletClass, SpawnNextAnim)     == 0x158);
GG_STATIC_ASSERT(offsetof(BulletClass, unknown_15C)       == 0x15C);
GG_STATIC_ASSERT(sizeof(BulletClass)                      == 0x160);

// VTABLE: GAMEMD 0x007E46E4  BulletClass            (COL base 0)
// VTABLE: GAMEMD 0x007E46C8  BulletClass::(+0x04)
// VTABLE: GAMEMD 0x007E46C0  BulletClass::(+0x08)
// VTABLE: GAMEMD 0x007E46B8  BulletClass::(+0x0C)

#endif  // GG_MATCH_LAYOUT_BULLET_CLASS_H
