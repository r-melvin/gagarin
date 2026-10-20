// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, globals and slots read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x43B5E0: `CALL 0x427CB0`
//   with the name in ECX (AnimTypeClass::FindIndex), `MOV ECX,[0x8B4154]` /
//   `MOV EDI,[ECX+EAX*4]` (AnimTypeClass::Array.Items, base 0x8B4150),
//   `CALL [EDX+0x48]` on the target with a 12-byte out buffer (GetCoords,
//   by-value CoordStruct), `PUSH 0x1C8` / `CALL 0x7C8E17` / `CALL 0x421EA0`
//   (sizeof(AnimClass) + its 7-arg ctor), `CALL 0x424C90` / `CALL 0x424CA0`
//   (two one-arg AnimClass setters) and `MOV BYTE [ESI+0x19D],1`.  Names from
//   YRpp HouseClass.h / AnimClass.h (consult-only; reconfirmed here).
#ifndef GG_MATCH_AI_HOUSE_CLASS_PSI_WARN_METHODS_H
#define GG_MATCH_AI_HOUSE_CLASS_PSI_WARN_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector_class.h"

struct CoordStruct
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08
};
GG_STATIC_ASSERT(sizeof(CoordStruct) == 0xC);

struct AnimTypeClass;   // opaque — only ever passed through
struct BulletClass;     // opaque
struct HouseClass;

// The warn target: only its vtable+0x48 GetCoords (by-value CoordStruct
// return, hence the hidden out-pointer push) is used.  Never instantiated.
struct CellClass
{
    virtual void vf00() = 0;   // vtable+0x00
    virtual void vf04() = 0;   // vtable+0x04
    virtual void vf08() = 0;   // vtable+0x08
    virtual void vf0C() = 0;   // vtable+0x0C
    virtual void vf10() = 0;   // vtable+0x10
    virtual void vf14() = 0;   // vtable+0x14
    virtual void vf18() = 0;   // vtable+0x18
    virtual void vf1C() = 0;   // vtable+0x1C
    virtual void vf20() = 0;   // vtable+0x20
    virtual void vf24() = 0;   // vtable+0x24
    virtual void vf28() = 0;   // vtable+0x28
    virtual void vf2C() = 0;   // vtable+0x2C
    virtual void vf30() = 0;   // vtable+0x30
    virtual void vf34() = 0;   // vtable+0x34
    virtual void vf38() = 0;   // vtable+0x38
    virtual void vf3C() = 0;   // vtable+0x3C
    virtual void vf40() = 0;   // vtable+0x40
    virtual void vf44() = 0;   // vtable+0x44
    virtual CoordStruct GetCoords() const = 0;   // vtable+0x48
};

// AnimClass — sizeof 0x1C8; ctor + two setters are body-less (reloc CALLs).
struct AnimClass
{
    // FUNCTION: GAMEMD 0x421EA0 (decl; reloc)
    AnimClass(AnimTypeClass* type, const CoordStruct& coords, int loopDelay,
              int loopCount, unsigned int flags, int forceZAdjust,
              bool reverse) throw();

    // FUNCTION: GAMEMD 0x424C90 (decl; reloc) — stores at +0x17C.
    void FUN_00424C90(BulletClass* bullet);
    // FUNCTION: GAMEMD 0x424CA0 (decl; reloc) — stores at +0x180.
    void FUN_00424CA0(HouseClass* house);

    char _pad000[0x19D];    // +0x0000
    char At_19D;            // +0x019D
    char _pad19E[0x1C8 - 0x19E];
};
GG_STATIC_ASSERT(offsetof(AnimClass, At_19D) == 0x19D);
GG_STATIC_ASSERT(sizeof(AnimClass) == 0x1C8);

// FUNCTION: GAMEMD 0x427CB0 (decl; reloc) — AnimTypeClass::FindIndex(name).
int __fastcall AnimType_FindIndex(const char* name);

// GLOBAL: GAMEMD 0x8B4150 — AnimTypeClass::Array.
extern DynamicVectorClassLayout AnimTypeArray;

struct HouseClass
{
    // FUNCTION: GAMEMD 0x43B5E0
    AnimClass* __fastcall PsiWarn(CellClass* target, BulletClass* bullet,
                                  const char* animName);
};

#endif  // GG_MATCH_AI_HOUSE_CLASS_PSI_WARN_METHODS_H
