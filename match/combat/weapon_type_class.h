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
#include "../core/vector_class.h"

// ---------------------------------------------------------------------------
// BulletTypeClass — partial model of the Projectile pointee (only the members
// the weapon methods touch). Confirmed numerically:
//   * Flag295  @0x295  — `MOV CL,[EAX+0x295]` in CalculateSpeed (gates the
//                        Func_0048ACF0 path vs the gravity baseline).
//   * Flag2A4  @0x2A4  — `MOV DL,[ECX+0x2A4]` in AllowedThreats.
//   * Flag2A5  @0x2A5  — `MOV DL,[ECX+0x2A5]` in AllowedThreats.
//   * Field2DC @0x2DC  — `MOV ECX,[EAX+0x2DC]; TEST; JNZ` gate in CalculateSpeed.
// ---------------------------------------------------------------------------
struct BulletTypeClass
{
    char          _pad0[0x295];          // +0x000
    unsigned char Flag295;               // +0x295
    char          _pad1[0x2A4 - 0x296];  // +0x296
    unsigned char Flag2A4;               // +0x2A4
    unsigned char Flag2A5;               // +0x2A5
    char          _pad2[0x2DC - 0x2A6];  // +0x2A6
    int           Field2DC;              // +0x2DC
};

GG_STATIC_ASSERT(offsetof(BulletTypeClass, Flag295)  == 0x295);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Flag2A4)  == 0x2A4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Flag2A5)  == 0x2A5);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, Field2DC) == 0x2DC);

class WarheadTypeClass;  // Warhead member is only stored as a pointer here.

// ---------------------------------------------------------------------------
// WeaponTypeClass  (sizeof = 0x160; confirmed by `PUSH 0x160` before the
// FindOrAllocate operator-new). Members appended after the 0x98-byte
// AbstractTypeClass spine, in confirmed retail order:
//   Projectile @0xA0  — `MOV EAX,[ESI+0xA0]` (CalculateSpeed) / `[ECX+0xA0]`
//                       (AllowedThreats).
//   Speed      @0xA8  — `MOV [ESI+0xA8],EAX` (CalculateSpeed writes the result).
//   Range      @0xB4  — `MOV ECX,[ESI+0xB4]` (CalculateSpeed, passed to 0x48AB90).
// ---------------------------------------------------------------------------
struct WeaponTypeClass : AbstractTypeClass
{
    // STATIC: GAMEMD 0x772FA0  (__fastcall)
    static WeaponTypeClass* __fastcall FindOrAllocate(const char* id);
    // FUNCTION: GAMEMD 0x7729F0  (__thiscall)
    void CalculateSpeed();
    // FUNCTION: GAMEMD 0x772A90  (__thiscall)
    int AllowedThreats();

    // GAMEMD 0x771C70  WeaponTypeClass::WeaponTypeClass(const char*) (__thiscall;
    // returns `this` in EAX). Declared (no body) so FindOrAllocate emits the
    // reloc'd construct call; matched in its own TU.
    WeaponTypeClass* Construct(const char* id);

    int               AmbientDamage;          // +0x98
    int               Burst;                  // +0x9C
    BulletTypeClass*  Projectile;             // +0xA0
    int               Damage;                 // +0xA4
    int               Speed;                  // +0xA8
    WarheadTypeClass* Warhead;                // +0xAC
    int               ROF;                    // +0xB0
    int               Range;                  // +0xB4
    unsigned int      unknown_B8;             // +0xB8
    DynamicVectorClass<int> Reports;           // +0xBC (items +0xC0, count +0xCC)
    char              _tail[0x160 - 0xD4];    // +0xD4  remaining Rules fields (P2)
};

GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Projectile) == 0xA0);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Speed)      == 0xA8);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Range)      == 0xB4);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Reports)    == 0xBC);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Reports) + 0x04 == 0xC0);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Reports) + 0x10 == 0xCC);
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
__int64 __fastcall Func_0048AB90(int range, double value);       // GAMEMD 0x48AB90

#endif  // GG_MATCH_COMBAT_WEAPON_TYPE_CLASS_H
