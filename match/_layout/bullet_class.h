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
//     * 0x120..0x127: BulletClass::vf_23 proves this is a double accumulator:
//       FADD/FSTP qword [EBP+0x120] at 0x466FCA/0x466FD0 and FLD qword at
//       0x466FD8. The ctor's two dword zero stores at 0x4663AA/0x4663E9
//       initialize both halves. (`FLD float [EAX+0x124]` @0x469180 is not
//       evidence for this member: EAX is BulletTypeClass at that site.)
//     * 0x15C: YRpp calls it `int Range`. No access found.
//
//   Cross-read against YRpp: 28 named members claimed, 24
//   confirmed, 4 recorded as unknown_XX (above).
//
// BulletClass — a projectile in flight. Derives ObjectClass at offset 0.
#ifndef GG_MATCH_LAYOUT_BULLET_CLASS_H
#define GG_MATCH_LAYOUT_BULLET_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "object_class.h"     // ObjectClass spine + CoordStruct
#include "foot_class.h"       // CellStruct
#include "../core/small_struct_ctor_methods.h"

class BulletTypeClass;
class WarheadTypeClass;
class TechnoClass;
class WeaponTypeClass;
class AnimClass;
struct Matrix3D;
struct Point2D;
struct RectangleStruct;
struct VoxelStruct;

// BulletData — the flight-state block embedded at BulletClass+0xB8. Size 0x28,
// proven by closure: the ctor takes ECX = this+0xB8 and calls its constructor
// FUN_0x004E1100 (@0x0046638B/0x004663A3); the next confirmed member (Bright)
// is at 0xE0 == 0xB8 + 0x28. Field names are NOT established.
#ifndef GG_MATCH_LAYOUT_BULLETDATA_DEFINED
#define GG_MATCH_LAYOUT_BULLETDATA_DEFINED
struct BulletData
{
    Obj_0046B600 unknown_00;          // +0x00..+0x0B, frame/time-left block
    Obj_0046B600 unknown_0C;          // +0x0C..+0x17, frame/time-left block
    unsigned int unknown_18;
    unsigned int unknown_1C;
    unsigned int unknown_20;
    unsigned int unknown_24;

    BulletData();
    BulletData(const AbstractNoInit&) : unknown_00(0), unknown_0C(0) {}
    // FUNCTION: GAMEMD 0x4E1130 (decl; reloc)
    void FUN_004E1130(const CoordStruct& from, const CoordStruct& to,
                      int value, int limit);
    // Binary contract at 0x4E11F0: ECX receiver, CoordStruct reference.
    int FUN_004E11F0(const CoordStruct& where);
};
GG_STATIC_ASSERT(offsetof(BulletData, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(BulletData, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(BulletData, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(BulletData, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(BulletData, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(BulletData, unknown_24) == 0x24);
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
GG_STATIC_ASSERT(offsetof(BulletVelocity, X) == 0x00);
GG_STATIC_ASSERT(sizeof(BulletVelocity)      == 0x18);
#endif

// VTABLE: GAMEMD 0x007E46E4  BulletClass            (COL base 0)
// VTABLE: GAMEMD 0x007E46C8  BulletClass::(+0x04)
// VTABLE: GAMEMD 0x007E46C0  BulletClass::(+0x08)
// VTABLE: GAMEMD 0x007E46B8  BulletClass::(+0x0C)
class BulletClass : public ObjectClass
{
public:
    // CALLEE: GAMEMD 0x466380 -- default constructor, implemented below in the Bullet TU.
    BulletClass();

    // No separate entry: Load's placement construction starts the native
    // ObjectClass no-init chain and invokes the two embedded timer writers.
    BulletClass(const AbstractNoInit& noInit)
        : ObjectClass(noInit), Data(noInit) {}

    // Native primary table 0x7E46E4, 125 entries; slot changes are based on
    // the complete native slot census and their entry bodies.
    virtual ULONG __stdcall AddRef();                               // 1  0x46AFD0
    virtual ULONG __stdcall Release();                              // 2  0x46AFF0
    virtual HRESULT __stdcall GetClassID(CLSID* id);                // 3  0x46B560
    virtual HRESULT __stdcall Load(IStream* stream);                // 5  0x46AE70
    virtual HRESULT __stdcall Save(IStream* stream, BOOL clearDirty); // 6  0x46AFB0
    virtual ~BulletClass();                                         // 8  body 0x466560; deleting 0x46B5C0
    virtual void vf_10(void* expired, bool removed);                // 10 0x4684E0
    virtual int vf_11();                                            // 11 0x46B550
    virtual int vf_12();                                            // 12 0x46B540
    virtual void vf_23();                                           // 23 0x4666E0
    virtual int vf_30();                                            // 30 0x468B90
    virtual ObjectTypeClass* vf_34();                               // 34 0x46B5B0
    virtual void* vf_66(int a1);                                    // 66 0x466660
    virtual void vf_69(Point2D* point, RectangleStruct* clip);      // 69 0x468090
    virtual bool vf_73(int a1);                                     // 73 0x4666C0
    virtual int vf_122();                                           // 122 0x468000
    virtual void vf_123(int a1);                                    // 123 0x46B5A0
    virtual bool vf_124(const CoordStruct& source,
                        const BulletVelocity& velocity);            // 124 0x468670

    // FUNCTION: GAMEMD 0x46B0C0 (decl; reloc), BulletClass receiver, RET 0x1C.
    void FUN_0046B0C0(const VoxelStruct* voxel, const Matrix3D& matrix,
                      Point2D* point, RectangleStruct* clip,
                      int frame, int flags, int tint);
    // Native setter implemented at the address-marked definition in the Bullet TU.
    void FUN_004664C0(BulletTypeClass* type, AbstractClass* target,
                      TechnoClass* owner, int health, WarheadTypeClass* warhead,
                      int speed, unsigned char bright);
    // Binary contract at 0x468BB0: one coordinate pointer.
    bool FUN_00468BB0(CoordStruct* where);
    // Binary contract at 0x468D80: one stack int.
    void FUN_00468D80(int impact);
    // Native helper call: this in ECX, coordinate pointer on the stack.
    void FUN_004690B0(const CoordStruct* position);
    // Native caller contract (GAMEMD 0x46A310): ECX Bullet receiver, no stack args.
    void FUN_0046A310();
    // Native caller contract (GAMEMD 0x46B310): ECX Bullet receiver, no stack args.
    // Body recovery is held; this adds only the observed caller contract.
    void FUN_0046B310();

    BulletTypeClass* Type;               // +0xAC; ctor @0x00466391
    TechnoClass*   Owner;               // +0xB0 TechnoClass*;     ctor @0x00466397
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
    AbstractClass* Target;              // +0x10C AbstractClass*; ctor @0x004663D1;
                                        //   setter MOV [ECX+0x10C],EDX @0x004664C8
    int            Speed;               // +0x110 ctor @0x004663D7; setter @0x004664D2
    int            InheritedColor;      // +0x114 ctor @0x004663DD (=-1); also @0x00466533
    unsigned int   unknown_118;         // +0x118 ctor @0x004663E3
    unsigned int   unknown_11C;         // +0x11C NOT confirmed — see header note
    double         unknown_120;         // +0x120..+0x127, FLD/FSTP qword in vf_23
    void*          WH;                  // +0x128 WarheadTypeClass*; ctor @0x004663EF;
                                        //   setter MOV [ECX+0x128],EDX @0x004664DC
    unsigned char  AnimFrame;           // +0x12C ctor @0x004663F5; also @0x00466507
    unsigned char  AnimRateCounter;     // +0x12D ctor @0x004663FB; also @0x00466513
    unsigned char  align_12E[2];        // +0x12E
    WeaponTypeClass* WeaponType;          // +0x130 WeaponTypeClass*; ctor @0x00466401
    CoordStruct    SourceCoords;        // +0x134 (0xC) ctor @0x00466444/0x0046644A/0x00466450
    CoordStruct    TargetCoords;        // +0x140 (0xC) ctor @0x00466456/0x0046645C/0x00466462
    CellStruct     LastMapCoords;       // +0x14C (4) ctor two word stores @0x00466407/0x0046640E
    int            DamageMultiplier;    // +0x150 read at 0x004697FC and IMUL'd against
                                        //   ObjectClass::Health [ESI+0x6C] — same receiver, so this
                                        //   really is a damage scale on the bullet
    AnimClass*     NextAnim;            // +0x154 AnimClass*; ctor @0x00466419
    unsigned char  SpawnNextAnim;       // +0x158 ctor @0x0046641F
    unsigned char  align_159[3];        // +0x159
    int            unknown_15C;         // +0x15C NOT confirmed (YRpp calls it Range); closes at 0x160
};

GG_STATIC_ASSERT(offsetof(BulletClass, Type)              == 0xAC);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->Type)           == 4);
GG_STATIC_ASSERT(offsetof(BulletClass, Owner)             == 0xB0);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->Owner)          == 4);
GG_STATIC_ASSERT(offsetof(BulletClass, unknown_B4)        == 0xB4);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->unknown_B4)     == 1);
GG_STATIC_ASSERT(offsetof(BulletClass, Data)              == 0xB8);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->Data)            == 0x28);
GG_STATIC_ASSERT(offsetof(BulletClass, Bright)            == 0xE0);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->Bright)          == 1);
GG_STATIC_ASSERT(offsetof(BulletClass, unknown_E4)        == 0xE4);
GG_STATIC_ASSERT(offsetof(BulletClass, Velocity)          == 0xE8);
GG_STATIC_ASSERT(offsetof(BulletClass, unknown_100)       == 0x100);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->unknown_100)    == 4);
GG_STATIC_ASSERT(offsetof(BulletClass, unknown_104)       == 0x104);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->unknown_104)    == 1);
GG_STATIC_ASSERT(offsetof(BulletClass, CourseLock)        == 0x105);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->CourseLock)     == 1);
GG_STATIC_ASSERT(offsetof(BulletClass, CourseLockCounter) == 0x108);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->CourseLockCounter) == 4);
GG_STATIC_ASSERT(offsetof(BulletClass, Target)            == 0x10C);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->Target)          == 4);
GG_STATIC_ASSERT(offsetof(BulletClass, Speed)             == 0x110);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->Speed)           == 4);
GG_STATIC_ASSERT(offsetof(BulletClass, InheritedColor)    == 0x114);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->InheritedColor) == 4);
GG_STATIC_ASSERT(offsetof(BulletClass, unknown_118)       == 0x118);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->unknown_118)   == 4);
GG_STATIC_ASSERT(offsetof(BulletClass, unknown_11C)       == 0x11C);
GG_STATIC_ASSERT(offsetof(BulletClass, unknown_120)       == 0x120);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->unknown_120)    == 8);
GG_STATIC_ASSERT(offsetof(BulletClass, WH)                == 0x128);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->WH)             == 4);
GG_STATIC_ASSERT(offsetof(BulletClass, AnimFrame)         == 0x12C);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->AnimFrame)      == 1);
GG_STATIC_ASSERT(offsetof(BulletClass, AnimRateCounter)   == 0x12D);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->AnimRateCounter) == 1);
GG_STATIC_ASSERT(offsetof(BulletClass, WeaponType)        == 0x130);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->WeaponType)     == 4);
GG_STATIC_ASSERT(offsetof(BulletClass, SourceCoords)      == 0x134);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->SourceCoords)   == 0x0C);
GG_STATIC_ASSERT(offsetof(BulletClass, TargetCoords)      == 0x140);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->TargetCoords)   == 0x0C);
GG_STATIC_ASSERT(offsetof(BulletClass, LastMapCoords)     == 0x14C);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->LastMapCoords)  == 4);
GG_STATIC_ASSERT(offsetof(BulletClass, DamageMultiplier)  == 0x150);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->DamageMultiplier) == 4);
GG_STATIC_ASSERT(offsetof(BulletClass, NextAnim)          == 0x154);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->NextAnim)       == 4);
GG_STATIC_ASSERT(offsetof(BulletClass, SpawnNextAnim)     == 0x158);
GG_STATIC_ASSERT(sizeof(((BulletClass*)0)->SpawnNextAnim) == 1);
GG_STATIC_ASSERT(offsetof(BulletClass, unknown_15C)       == 0x15C);
GG_STATIC_ASSERT(sizeof(BulletClass)                      == 0x160);

#endif  // GG_MATCH_LAYOUT_BULLET_CLASS_H
