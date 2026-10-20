// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x509E00: CALL 0x53A100 (a byte global read, no receiver),
//   `[ESI+0x5600]` compared with -1, the CellStruct at `[ESI+0x54F0]` compared
//   word-wise with the sentinel at 0xA8EF98/0xA8EF9A, `[ESI+0x54EC]` compared
//   with 1 and otherwise passed to 0x50D170 (PickTargetByType) where 0x50CBF0
//   (PickIonCannonTarget) takes only the out buffer, the super-weapon vector
//   at `[ESI+0x254]` whose slot `[EAX+0x10]` (FindItemIndex) receives the
//   *address* of the parameter slot (`LEA EDX,[ESP+0x14]`), and CALL 0x4FAE50
//   (Fire_SW) taking the index and the cell by pointer. Names are YRpp's
//   HouseClass::Fire_LightningStorm / PickIonCannonTarget / PickTargetByType /
//   Fire_SW (names only).
#ifndef GG_MATCH_AI_HOUSE_CLASS_LIGHTNING_STORM_METHODS_H
#define GG_MATCH_AI_HOUSE_CLASS_LIGHTNING_STORM_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Cell_00509E00
{
    short X;   // +0x0000
    short Y;   // +0x0002
};
GG_STATIC_ASSERT(sizeof(Cell_00509E00) == 4);

// GLOBAL: GAMEMD 0xA8EF98 — a "no cell" CellStruct sentinel.
extern Cell_00509E00 DAT_00A8EF98;

// FUNCTION: GAMEMD 0x53A100 (decl; reloc) — a global byte flag, read without a
// receiver (`MOV AL,[0xA9FAB4]; RET`).
bool __cdecl FUN_0053A100();

struct Super_00509E00;

// DynamicVectorClass<SuperClass*>: FindItemIndex is issued through the vptr,
// so the slot run is declared for real (see super_class_lose_methods.h). The
// argument is a reference: retail pushes the address of the parameter slot.
struct SuperVector_00509E00
{
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0C();
    virtual int  FindItemIndex(Super_00509E00* const& item);   // +0x10 (decl; reloc)
};

struct House_00509E00
{
    char                 _pad000[0x254];             // +0x0000
    SuperVector_00509E00 Supers;                     // +0x0254
    char                 _pad258[0x54EC - 0x258];    // +0x0258
    int                  At_54EC;                    // +0x54EC
    Cell_00509E00        At_54F0;                    // +0x54F0
    char                 _pad54F4[0x5600 - 0x54F4];  // +0x54F4
    int                  At_5600;                    // +0x5600

    // FUNCTION: GAMEMD 0x4FAE50 (decl; reloc) — HouseClass::Fire_SW.
    bool Fire_SW(int index, Cell_00509E00 const& cell);
    // FUNCTION: GAMEMD 0x50CBF0 (decl; reloc) — HouseClass::PickIonCannonTarget.
    Cell_00509E00* PickIonCannonTarget(Cell_00509E00* out);
    // FUNCTION: GAMEMD 0x50D170 (decl; reloc) — HouseClass::PickTargetByType.
    Cell_00509E00* PickTargetByType(Cell_00509E00* out, int targetType);

    // FUNCTION: GAMEMD 0x509E00 — HouseClass::Fire_LightningStorm.
    void Fire_LightningStorm(Super_00509E00* pSuper);
};
GG_STATIC_ASSERT(offsetof(House_00509E00, Supers)  == 0x254);
GG_STATIC_ASSERT(offsetof(House_00509E00, At_54EC) == 0x54EC);
GG_STATIC_ASSERT(offsetof(House_00509E00, At_54F0) == 0x54F0);
GG_STATIC_ASSERT(offsetof(House_00509E00, At_5600) == 0x5600);

#endif  // GG_MATCH_AI_HOUSE_CLASS_LIGHTNING_STORM_METHODS_H
