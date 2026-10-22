// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and slots read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x468430: `[ESI+0x10C]` (the target
//   pointer, read before each virtual call and stored at the end), the target
//   slots `[EAX+0x48]` (GetCoords, out-buffer pushed, pointer returned) and
//   `[EDX+0x54]` (IsInAir, no arguments, AL), the int global `[0xA8E7AC]`,
//   the word pair `[0x89DDF0]` / `[0x89DDF2]` (a CellStruct, bytes 00 00 00
//   00) and `MOV ECX,0x87F7E8` feeding CALL 0x5657A0 (MapClass::GetCellAt
//   on the static map object) with `LEA EDX,[ESP+4]` pushed. The slot names
//   come from the vtable layout (0x48 getCoords) and the
//   YRpp method map (0x5F6B90 ObjectClass::IsInAir, read out of the leaf
//   vftable at 0x7F4960+0x54); YRpp also names 0xA8E7AC (ScenarioInit) and
//   the function (BulletClass::LoseTarget).
#ifndef GG_MATCH_COMBAT_BULLET_CLASS_LOSE_TARGET_METHODS_H
#define GG_MATCH_COMBAT_BULLET_CLASS_LOSE_TARGET_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct CoordStruct
{
    int X;   // +0x0
    int Y;   // +0x4
    int Z;   // +0x8
};
GG_STATIC_ASSERT(sizeof(CoordStruct) == 0xC);

// CellStruct — a packed map cell coordinate. The user-declared constructor
// makes VC6 return it through a hidden pointer, which is the temporary retail
// builds at [ESP+8] before copying it into the named local at [ESP+4].
struct CellStruct
{
    short X;   // +0x0
    short Y;   // +0x2

    CellStruct() { }
};
GG_STATIC_ASSERT(sizeof(CellStruct) == 0x4);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct AbsVtbl_00468430;

// The bullet's target: any AbstractClass. Only two slots are dispatched.
struct Abs_00468430
{
    AbsVtbl_00468430* Vtbl;   // +0x0000
};

typedef CoordStruct* (Abs_00468430::*FnCoords_00468430)(CoordStruct* out);
typedef bool (Abs_00468430::*FnInAir_00468430)();

struct AbsVtbl_00468430
{
    char _pad000[0x48];             // +0x0000
    FnCoords_00468430 At_48;        // +0x0048  GetCoords
    char _pad04C[0x54 - 0x4C];      // +0x004C
    FnInAir_00468430 At_54;         // +0x0054  IsInAir
};
GG_STATIC_ASSERT(offsetof(AbsVtbl_00468430, At_48) == 0x48);
GG_STATIC_ASSERT(offsetof(AbsVtbl_00468430, At_54) == 0x54);

// The map singleton is a static object at 0x87F7E8 (`MOV ECX,0x87F7E8`).
struct Map_00468430
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) — MapClass::GetCellAt.
    Abs_00468430* GetCellAt(const CellStruct& cell);
};
// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance.
extern Map_00468430 MapInstance;

// GLOBAL: GAMEMD 0xA8E7AC — nonzero while the scenario is being set up.
extern int DAT_00A8E7AC;
// GLOBAL: GAMEMD 0x89DDF0 — the "no cell" sentinel the target cell is compared to.
extern CellStruct DAT_0089DDF0;

// BulletClass : ObjectClass — only Target is reached here.
struct BulletClass
{
    char           _pad000[0x10C];   // +0x0000
    Abs_00468430*  Target;           // +0x010C

    // FUNCTION: GAMEMD 0x468430
    void LoseTarget();
};
GG_STATIC_ASSERT(offsetof(BulletClass, Target) == 0x10C);

#endif  // GG_MATCH_COMBAT_BULLET_CLASS_LOSE_TARGET_METHODS_H
