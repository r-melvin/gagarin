// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x509CD0: `[ESI+0x5600]` compared with -1 and otherwise
//   indexing the Items pointer at 0xA8022C (`MOV ECX,[ECX+EAX*4]`), the
//   CellStruct at `[ESI+0x54F0]` compared word-wise with the sentinel at
//   0xA8EF98/0xA8EF9A, `[ESI+0x54EC]` compared with 1 and otherwise passed
//   to 0x50D170 (PickTargetByType) with a stack out buffer; on the chosen
//   house `[ECX+0x5494]` compared word-wise with the sentinel and either it
//   or `[ECX+0x5490]` copied into the cell local; the map object 0x87F7E8
//   receiving CALL 0x56DC20 (NearByLocation) with fifteen pushed arguments
//   (out buffer, &cell, 0, -1, 0, 0, 5, 5, 0, 0, 0, 1, &zero cell, 0, 0)
//   whose result gets `ADD word ptr,2` on both halves; the super-weapon
//   vector at `[ESI+0x254]` whose slot `[EAX+0x10]` (FindItemIndex) receives
//   the *address* of the parameter slot, and CALL 0x4FAE50 (Fire_SW) taking
//   the index and the cell by pointer. Names are YRpp's HouseClass::
//   Fire_ParaDrop / GetBaseCenter / BaseSpawnCell / BaseCenter /
//   PreferredTargetType / PreferredTargetCell / EnemyHouseIndex /
//   PickTargetByType / Fire_SW and MapClass::NearByLocation (names only).
#ifndef GG_MATCH_AI_HOUSE_CLASS_PARADROP_METHODS_H
#define GG_MATCH_AI_HOUSE_CLASS_PARADROP_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Cell_00509CD0
{
    short X;   // +0x0000
    short Y;   // +0x0002
};
GG_STATIC_ASSERT(sizeof(Cell_00509CD0) == 4);

// GLOBAL: GAMEMD 0xA8EF98 — a "no cell" CellStruct sentinel.
extern Cell_00509CD0 DAT_00A8EF98;

struct Super_00509CD0;
struct House_00509CD0;

// GLOBAL: GAMEMD 0xA8022C — HouseClass::Array.Items.
extern House_00509CD0** DAT_00A8022C;

// DynamicVectorClass<SuperClass*>: FindItemIndex is issued through the vptr,
// so the slot run is declared for real (see super_class_lose_methods.h). The
// argument is a reference: retail pushes the address of the parameter slot.
struct SuperVector_00509CD0
{
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0C();
    virtual int  FindItemIndex(Super_00509CD0* const& item);   // +0x10 (decl; reloc)
};

// MapClass — only the nearby-cell search is reached.
struct Map_00509CD0
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x56DC20 (decl; reloc) — MapClass::NearByLocation.
    Cell_00509CD0* NearByLocation(Cell_00509CD0* out, const Cell_00509CD0& position,
                                  int speedType, int a4, int movementZone, bool alt,
                                  int spaceSizeX, int spaceSizeY, bool a9, bool a10,
                                  bool a11, bool ignoreOccupied,
                                  const Cell_00509CD0& closeTo, bool a14, bool buildable);
};
// GLOBAL: GAMEMD 0x87F7E8 — the map instance.
extern Map_00509CD0 MapInstance_00509CD0;

struct House_00509CD0
{
    char                 _pad000[0x254];             // +0x0000
    SuperVector_00509CD0 Supers;                     // +0x0254
    char                 _pad258[0x5490 - 0x258];    // +0x0258
    Cell_00509CD0        BaseSpawnCell;              // +0x5490
    Cell_00509CD0        BaseCenter;                 // +0x5494
    char                 _pad5498[0x54EC - 0x5498];  // +0x5498
    int                  PreferredTargetType;        // +0x54EC
    Cell_00509CD0        PreferredTargetCell;        // +0x54F0
    char                 _pad54F4[0x5600 - 0x54F4];  // +0x54F4
    int                  EnemyHouseIndex;            // +0x5600

    // FUNCTION: GAMEMD 0x4FAE50 (decl; reloc) — HouseClass::Fire_SW.
    bool Fire_SW(int index, Cell_00509CD0 const& cell);
    // FUNCTION: GAMEMD 0x50D170 (decl; reloc) — HouseClass::PickTargetByType.
    Cell_00509CD0* PickTargetByType(Cell_00509CD0* out, int targetType);

    // Inlined by retail: BaseCenter when set, otherwise BaseSpawnCell.
    Cell_00509CD0 GetBaseCenter() const
    {
        if (this->BaseCenter.X != DAT_00A8EF98.X || this->BaseCenter.Y != DAT_00A8EF98.Y) {
            return this->BaseCenter;
        }
        return this->BaseSpawnCell;
    }

    // FUNCTION: GAMEMD 0x509CD0 — HouseClass::Fire_ParaDrop.
    void Fire_ParaDrop(Super_00509CD0* pSuper);
};
GG_STATIC_ASSERT(offsetof(House_00509CD0, Supers)              == 0x254);
GG_STATIC_ASSERT(offsetof(House_00509CD0, BaseSpawnCell)       == 0x5490);
GG_STATIC_ASSERT(offsetof(House_00509CD0, BaseCenter)          == 0x5494);
GG_STATIC_ASSERT(offsetof(House_00509CD0, PreferredTargetType) == 0x54EC);
GG_STATIC_ASSERT(offsetof(House_00509CD0, PreferredTargetCell) == 0x54F0);
GG_STATIC_ASSERT(offsetof(House_00509CD0, EnemyHouseIndex)     == 0x5600);

#endif  // GG_MATCH_AI_HOUSE_CLASS_PARADROP_METHODS_H
