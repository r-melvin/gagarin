// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x7729F0 / 0x772A90 / 0x772FA0),
//   cross-checked against YRpp (
//   every offset and address reconfirmed numerically below).
//
// WeaponTypeClass — a weapon *type* (rules-driven template). Derives the shared
// AbstractTypeClass layout-spine (ID @0x24, sizeof 0x98). Only the members the
// three methods in this TU touch are named here; the remainder of the class is
// padded so `operator new` emits the exact retail `push 0x160` allocation seen
// in FindOrAllocate. Full per-field layout is P2.
#ifndef GG_MATCH_COMBAT_WEAPON_TYPE_CLASS_H
#define GG_MATCH_COMBAT_WEAPON_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/abstract_type_class.h"
#include "../_layout/obj_004a1d30.h"
#include "bullet_type_class.h"
#include "../core/vector_class.h"
#include "../core/type_list.h"
#include "../_layout/color_struct.h"

class WarheadTypeClass;  // Warhead member is only stored as a pointer here.
class AnimTypeClass;
class ParticleSystemTypeClass;

// ---------------------------------------------------------------------------
// WeaponTypeClass  (sizeof = 0x160; confirmed by `PUSH 0x160` before the
// FindOrAllocate operator-new). Members appended after the 0x98-byte
// AbstractTypeClass spine, in confirmed retail order:
//   Projectile @0xA0  — `MOV EAX,[ESI+0xA0]` (CalculateSpeed) / `[ECX+0xA0]`
//                       (AllowedThreats).
//   Speed      @0xA8  — `MOV [ESI+0xA8],EAX` (CalculateSpeed writes the result).
//   Range      @0xB4  — `MOV ECX,[ESI+0xB4]` (CalculateSpeed, passed to 0x48AB90).
// ---------------------------------------------------------------------------
class WeaponTypeClass : public AbstractTypeClass
{
public:
    // CALLEE: GAMEMD 0x00771C70 (decl; reloc) -- constructor as the class factory calls it.
    WeaponTypeClass(int unknown_arg0 = 0);
    virtual int vf_11();   // 11  0x7730E0
    virtual int vf_12();   // 12  0x7730D0
    virtual void vf_13(Obj_004A1D30* crc);   // 13  0x772AE0
    virtual bool vf_25(CCINIClass* ini);   // 25  0x772080
    // STATIC: GAMEMD 0x772FA0  (__fastcall)
    static WeaponTypeClass* FindOrAllocate(const char* id);
    // FUNCTION: GAMEMD 0x7729F0  (__thiscall)
    void CalculateSpeed();
    // FUNCTION: GAMEMD 0x772A90  (__thiscall)
    int AllowedThreats();

    // GAMEMD 0x771C70  WeaponTypeClass::WeaponTypeClass(const char*) (__thiscall;
    // returns `this` in EAX). Declared (no body) so FindOrAllocate emits the
    // reloc'd construct call; matched in its own TU.
    WeaponTypeClass* Construct(const char* id);

    // IPersist::GetClassID (slot 3), 0x772C90; body in core/persist_class_id_methods.cpp.
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);                      // 5   0x772CD0
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);    // 6   0x772EB0

    int               AmbientDamage;          // +0x98
    int               Burst;                  // +0x9C
    BulletTypeClass*  Projectile;             // +0xA0
    int               Damage;                 // +0xA4
    int               Speed;                  // +0xA8
    WarheadTypeClass* Warhead;                // +0xAC
    int               ROF;                    // +0xB0
    int               Range;                  // +0xB4
    int               MinimumRange;           // +0xB8
    TypeList<int>     Reports;                // +0xBC (items +0xC0, count +0xCC)
    TypeList<int>     DownReport;             // +0xD8 (items +0xDC, count +0xE8)
    TypeList<const AnimTypeClass*> Anim;      // +0xF4 (items +0xF8, count +0x104)
    const AnimTypeClass* OccupantAnim;        // +0x110
    const AnimTypeClass* AssaultAnim;         // +0x114
    const AnimTypeClass* OpenToppedAnim;      // +0x118
    ParticleSystemTypeClass* AttachedParticleSystem; // +0x11C
    ColorStruct       LaserInnerColor;        // +0x120
    ColorStruct       LaserOuterColor;        // +0x123
    ColorStruct       LaserOuterSpread;       // +0x126
    bool              UseFireParticles;       // +0x129
    bool              UseSparkParticles;      // +0x12A
    bool              OmniFire;               // +0x12B
    bool              DistributedWeaponFire;  // +0x12C
    bool              IsRailgun;              // +0x12D
    bool              Lobber;                 // +0x12E
    bool              Bright;                 // +0x12F; byte load at Bullet 0x46A515/0x46A985
    bool              IsSonic;                // +0x130
    bool              Spawner;                // +0x131
    bool              LimboLaunch;            // +0x132
    bool              DecloakToFire;          // +0x133
    bool              CellRangefinding;       // +0x134
    bool              FireOnce;               // +0x135
    bool              NeverUse;               // +0x136
    bool              RevealOnFire;           // +0x137
    bool              TerrainFire;            // +0x138
    bool              SabotageCursor;         // +0x139
    bool              MigAttackCursor;        // +0x13A
    bool              DisguiseFireOnly;       // +0x13B
    int               DisguiseFakeBlinkTime;  // +0x13C
    bool              InfiniteMindControl;    // +0x140
    bool              FireWhileMoving;        // +0x141
    bool              DrainWeapon;            // +0x142
    bool              FireInTransport;        // +0x143
    bool              Suicide;                // +0x144
    bool              TurboBoost;             // +0x145
    bool              Supress;                // +0x146
    bool              Camera;                 // +0x147
    bool              Charges;                // +0x148
    bool              IsLaser;                // +0x149; byte loads at Bullet 0x46A887/0x46AD3E
    bool              DiskLaser;              // +0x14A
    bool              IsLine;                 // +0x14B
    bool              IsBigLaser;             // +0x14C
    bool              IsHouseColor;           // +0x14D
    char              LaserDuration;          // +0x14E
    bool              IonSensitive;           // +0x14F
    bool              AreaFire;               // +0x150 (read by TechnoClass slot 248 @0x70DD50)
    bool              IsElectricBolt;         // +0x151; byte loads at Bullet 0x46A8B1/0x46AD86
    bool              DrawBoltAsLaser;        // +0x152
    bool              IsAlternateColor;       // +0x153
    bool              IsRadBeam;              // +0x154
    bool              IsRadEruption;          // +0x155
    char              _tail2[0x158 - 0x156];  // +0x156..+0x157
    int               RadLevel;               // +0x158 (signed test at 0x46913E)
    bool              IsMagBeam;              // +0x15C
    char              _tail3[0x160 - 0x15D];  // +0x15D..+0x15F
};

GG_STATIC_ASSERT(offsetof(WeaponTypeClass, AmbientDamage) == 0x98);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Burst) == 0x9C);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Projectile) == 0xA0);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Damage) == 0xA4);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Speed) == 0xA8);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Warhead) == 0xAC);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, ROF) == 0xB0);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Range) == 0xB4);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, MinimumRange) == 0xB8);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Reports) == 0xBC);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, DownReport) == 0xD8);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Anim) == 0xF4);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, OccupantAnim) == 0x110);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, AssaultAnim) == 0x114);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, OpenToppedAnim) == 0x118);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, AttachedParticleSystem) == 0x11C);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, LaserInnerColor) == 0x120);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, LaserOuterColor) == 0x123);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, LaserOuterSpread) == 0x126);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, UseFireParticles) == 0x129);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, UseSparkParticles) == 0x12A);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, OmniFire) == 0x12B);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, DistributedWeaponFire) == 0x12C);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, IsRailgun) == 0x12D);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Lobber) == 0x12E);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Bright) == 0x12F);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, IsSonic) == 0x130);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Spawner) == 0x131);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, LimboLaunch) == 0x132);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, DecloakToFire) == 0x133);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, CellRangefinding) == 0x134);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, FireOnce) == 0x135);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, NeverUse) == 0x136);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, RevealOnFire) == 0x137);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, TerrainFire) == 0x138);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, SabotageCursor) == 0x139);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, MigAttackCursor) == 0x13A);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, DisguiseFireOnly) == 0x13B);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, DisguiseFakeBlinkTime) == 0x13C);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, InfiniteMindControl) == 0x140);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, FireWhileMoving) == 0x141);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, DrainWeapon) == 0x142);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, FireInTransport) == 0x143);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Suicide) == 0x144);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, TurboBoost) == 0x145);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Supress) == 0x146);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Camera) == 0x147);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Charges) == 0x148);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, IsLaser) == 0x149);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, DiskLaser) == 0x14A);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, IsLine) == 0x14B);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, IsBigLaser) == 0x14C);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, IsHouseColor) == 0x14D);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, LaserDuration) == 0x14E);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, IonSensitive) == 0x14F);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, AreaFire) == 0x150);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, IsElectricBolt) == 0x151);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, DrawBoltAsLaser) == 0x152);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, IsAlternateColor) == 0x153);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, IsRadBeam) == 0x154);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, IsRadEruption) == 0x155);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, RadLevel) == 0x158);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, IsMagBeam) == 0x15C);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Reports) + 0x04 == 0xC0);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Reports) + 0x10 == 0xCC);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, DownReport) + 0x04 == 0xDC);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, DownReport) + 0x10 == 0xE8);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Anim) + 0x04 == 0xF8);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Anim) + 0x10 == 0x104);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->Reports) == 0x1C);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->Burst) == 4);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->Damage) == 4);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->Range) == 4);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->Bright) == 1);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->IsLaser) == 1);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->IsElectricBolt) == 1);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->RadLevel) == 4);
GG_STATIC_ASSERT(sizeof(WeaponTypeClass)               == 0x160);

// VectorClass head for WeaponTypeClass::Array (DynamicVectorClass of pointers).
//   Array @0x887568  =>  &Items == 0x88756C, &Count == 0x887578 (both confirmed
//   by the absolute loads in FindOrAllocate).
struct WeaponTypeVector
{
    void*              vtable;        // +0x00
    WeaponTypeClass**  Items;        // +0x04
    int                Capacity;     // +0x08
    int                IsAllocated;  // +0x0C
    int                Count;        // +0x10
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(WeaponTypeVector, Items) == 0x04);  // pointer-width-sensitive
GG_STATIC_ASSERT(offsetof(WeaponTypeVector, Count) == 0x10);
#endif

// GLOBAL: GAMEMD 0x887568 — WeaponTypeClass::Array.
extern WeaponTypeVector WeaponTypeClass_Array;

// ---------------------------------------------------------------------------
// Externals touched by CalculateSpeed (declared, no body — calls become relocs):
//   GameRulesPtr   GLOBAL 0x8871E0  — pointer to the rules/game object whose
//                  int field @0x16B8 is FILD'd as the gravity baseline.
//   Func_0048ACF0  GAMEMD 0x48ACF0  — nullary, returns a double in ST0.
//   Func_0048AB90  GAMEMD 0x48AB90  — __fastcall(int, double) -> __int64.
// ---------------------------------------------------------------------------
struct RulesData
{
    char _pad[0x16B8];   // +0x0000
    int  Field16B8;      // +0x16B8
};

GG_STATIC_ASSERT(offsetof(RulesData, Field16B8) == 0x16B8);

extern RulesData* GameRulesPtr;                                  // GLOBAL 0x8871E0
double           Func_0048ACF0();                                // GAMEMD 0x48ACF0
__int64 Func_0048AB90(int range, double value);       // GAMEMD 0x48AB90

#endif  // GG_MATCH_COMBAT_WEAPON_TYPE_CLASS_H
