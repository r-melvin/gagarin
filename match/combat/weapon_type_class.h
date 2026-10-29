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
class WeaponTypeClass : public AbstractTypeClass
{
public:
    // CALLEE: GAMEMD 0x00771C70 (decl; reloc) -- constructor as the class factory calls it.
    WeaponTypeClass(int unknown_arg0 = 0);
    virtual int vf_11();   // 11  0x7730E0
    virtual int vf_12();   // 12  0x7730D0
    virtual void vf_13(Obj_004A1D30* crc);   // 13  0x772AE0
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
    unsigned int      unknown_B8;             // +0xB8
    DynamicVectorClass<int> Reports;           // +0xBC (items +0xC0, count +0xCC)
    char              _tail[0xDC - 0xD4];    // +0xD4..+0xDB
    int*              unknown_DC;            // +0xDC; third counted dword list saved by Save (count at +0xE8)
    char              _tail_E0[0xE8 - 0xE0]; // +0xE0..+0xE7
    int               unknown_E8;            // +0xE8; entry count of the +0xDC list
    char              _tail_EC[0xF8 - 0xEC]; // +0xEC..+0xF7
    int*              unknown_F8;            // +0xF8; first counted dword list saved by Save (count at +0x104)
    char              _tail_FC[0x104 - 0xFC]; // +0xFC..+0x103
    int               unknown_104;           // +0x104; entry count of the +0xF8 list
    char              _tail_108[0x129 - 0x108]; // +0x108..+0x128
    bool              unknown_129;            // +0x129
    bool              unknown_12A;            // +0x12A
    bool              unknown_12B;            // +0x12B
    bool              unknown_12C;            // +0x12C
    bool              unknown_12D;            // +0x12D
    bool              unknown_12E;            // +0x12E
    bool              unknown_12F;            // +0x12F; byte load at Bullet 0x46A515/0x46A985
    bool              unknown_130;            // +0x130
    char              _tail_131[0x145 - 0x131]; // +0x131..+0x144
    bool              unknown_145;            // +0x145
    bool              unknown_146;            // +0x146
    bool              unknown_147;            // +0x147
    bool              unknown_148;            // +0x148
    bool              unknown_149;            // +0x149; byte loads at Bullet 0x46A887/0x46AD3E
    char              _tail_14A[0x14C - 0x14A]; // +0x14A..+0x14B
    bool              unknown_14C;            // +0x14C
    bool              unknown_14D;            // +0x14D
    unsigned char     unknown_14E;            // +0x14E
    char              _tail_14F[0x150 - 0x14F]; // +0x14F
    bool              unknown_150;            // +0x150 (bool; read by TechnoClass slot 248 @0x70DD50)
    unsigned char     unknown_151;            // +0x151; byte loads at Bullet 0x46A8B1/0x46AD86
    char              _tail2[0x158 - 0x152];  // +0x152..+0x157
    int               unknown_158;            // +0x158 (signed test at 0x46913E)
    char              _tail3[0x160 - 0x15C];  // +0x15C..+0x15F
};

GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Projectile) == 0xA0);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Burst)      == 0x9C);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->Burst)  == 4);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Damage)     == 0xA4);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->Damage) == 4);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Speed)      == 0xA8);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Range)      == 0xB4);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->Range) == 4);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Reports)    == 0xBC);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Reports) + 0x04 == 0xC0);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, Reports) + 0x10 == 0xCC);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_DC) == 0xDC);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_E8) == 0xE8);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_F8) == 0xF8);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_104) == 0x104);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_129) == 0x129);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_12E) == 0x12E);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_130) == 0x130);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_145) == 0x145);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_14C) == 0x14C);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_14E) == 0x14E);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_12F) == 0x12F);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->unknown_12F) == 1);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_149) == 0x149);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->unknown_149) == 1);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_151) == 0x151);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->unknown_151) == 1);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_150) == 0x150);
GG_STATIC_ASSERT(offsetof(WeaponTypeClass, unknown_158) == 0x158);
GG_STATIC_ASSERT(sizeof(((WeaponTypeClass*)0)->unknown_158) == 4);
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
