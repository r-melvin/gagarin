// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x74DE90. (`ghidra function get` reports 287 bytes for this
//   entry; the body actually runs to the `RET` at 0x74E0F7, so the real length
//   is 0x268.)
//     * `MOV BL,CL` — the single __fastcall flag parameter.
//     * `CALL 0x42B1F0` with no argument set up — the vein-growth buffer size,
//       kept in EDI and spilled to [ESP+0x10].
//     * the monster array: `[0xB1D2A0]` count, `[0xB1D294]` items
//       (`MOV ECX,[ECX+ESI*4]`); `[0xB1D2F0]` the shared growth buffer
//       (freed with 0x7C8B3D, re-allocated with 0x7C8E17, memset inline).
//     * `MOV EAX,[0x8871E0]; MOV ESI,[EAX+0xDC]` — RulesClass::Instance and
//       the element count both array allocations are sized from.
//     * per monster: `[m+0xB4] = new Pair[n]` (`LEA ECX,[ESI*8+0]`, then the
//       array-new counter preamble `DEC ESI; MOV [ESP+0x14],ESI` with no ctor
//       loop), `[m+0xB0] = new Stack(0x14)` whose body writes `[+0xC]=0`,
//       `[+4]=n`, `[+0x10]=-1`, `[+0]=0`, `[+8]=new int[n+1]`
//       (`LEA EAX,[EAX*4+4]`) and zeroes `[+8][0..[+4]]`, `[m+0xC4] =
//       new char[size]` memset to 0, and finally the same stack cleared
//       through `[m+0xB0]` (`for i <= [+0]` then `[+0] = 0`).
//     * `MOV AL,byte ptr [ECX+0x100]` selects 0x74E6B0 / 0x74E1C0 per monster.
//     * the map object iterator `MOV ECX,0x87F7E8; CALL 0x578350` (reset) /
//       `CALL 0x578290` (next), the flag mask `MOV EBX,0xFFFF7FFF` applied to
//       `[o+0x140]`, the overlay index `[o+0x44]` compared with 0x7E and set
//       to -1, and `LEA ECX,[ESI+0x24]; CALL 0x42B1C0` indexing the growth
//       buffer by the returned cell index. `[o+0x44]`/`0x7E` is the same
//       overlay-index pair already confirmed in
//       match/map/veinhole_monster_recalculate_methods.h.
//   YRpp names VeinholeMonsterClass and
//   RecalculateSpread @0x74E6B0; every offset is reconfirmed above.
#ifndef GG_MATCH_MAP_VEINHOLE_INIT_GROWTH_METHODS_H
#define GG_MATCH_MAP_VEINHOLE_INIT_GROWTH_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/cell.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);


// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance (a pointer).
#include "../_layout/rules_class.h"
extern RulesClass* DAT_008871E0;

// One 8-byte per-cell growth record; the user-declared empty constructor is
// what makes `new Pair[n]` emit retail's array-new counter preamble.
struct Pair_0074DE90
{
    int A;   // +0x00
    int B;   // +0x04
    Pair_0074DE90() {}
};
GG_STATIC_ASSERT(sizeof(Pair_0074DE90) == 8);

// The per-monster index stack at monster+0xB0.
struct Stack_0074DE90
{
    int  Count;         // +0x00
    int  Capacity;      // +0x04
    int* Items;         // +0x08
    int  Unknown_0C;    // +0x0C
    int  Unknown_10;    // +0x10

    // The constructor body, expanded by hand: under /GX a real `new T` wraps
    // the allocation in an exception frame retail does not have (the banked
    // rule, see match/core/campaign_class.cpp).
    __forceinline Stack_0074DE90* Construct()
    {
        int n = DAT_008871E0->MaxVeinholeGrowth;
        this->Unknown_0C = 0;
        this->Capacity   = n;
        this->Unknown_10 = -1;
        this->Count      = 0;
        this->Items      = new int[n + 1];
        for (int i = 0; i <= this->Capacity; i++) {
            this->Items[i] = 0;
        }
        return this;
    }

    __forceinline void Clear()
    {
        for (int i = 0; i <= this->Count; i++) {
            this->Items[i] = 0;
        }
        this->Count = 0;
    }
};
GG_STATIC_ASSERT(offsetof(Stack_0074DE90, Items)      == 0x08);
GG_STATIC_ASSERT(offsetof(Stack_0074DE90, Unknown_10) == 0x10);
GG_STATIC_ASSERT(sizeof(Stack_0074DE90)               == 0x14);

struct Veinhole_0074DE90
{
    char            _pad000[0xB0];             // +0x0000
    Stack_0074DE90* Cells;                     // +0x00B0
    Pair_0074DE90*  Growth;                    // +0x00B4
    char            _pad0B8[0xC4 - 0xB8];      // +0x00B8
    char*           GrowthFlags;               // +0x00C4
    char            _pad0C8[0x100 - 0xC8];     // +0x00C8
    char            Initialised;               // +0x0100
};
GG_STATIC_ASSERT(offsetof(Veinhole_0074DE90, Cells)       == 0xB0);
GG_STATIC_ASSERT(offsetof(Veinhole_0074DE90, Growth)      == 0xB4);
GG_STATIC_ASSERT(offsetof(Veinhole_0074DE90, GrowthFlags) == 0xC4);
GG_STATIC_ASSERT(offsetof(Veinhole_0074DE90, Initialised) == 0x100);

// GLOBAL: GAMEMD 0xB1D294 — VeinholeMonsterClass::Array items.
extern Veinhole_0074DE90** DAT_00B1D294;
// GLOBAL: GAMEMD 0xB1D2A0 — VeinholeMonsterClass::Array count.
extern int                 DAT_00B1D2A0;
// GLOBAL: GAMEMD 0xB1D2F0 — the shared vein-growth flag buffer.
extern char*               DAT_00B1D2F0;

// A map object walked by the iterator: the overlay index and the flag word.
struct Obj_0074DE90
{
    char       _pad000[0x24];             // +0x0000
    CellStruct MapCoords;                 // +0x0024
    char       _pad028[0x44 - 0x28];      // +0x0028
    int        OverlayTypeIndex;          // +0x0044
    char       _pad048[0x140 - 0x48];     // +0x0048
    unsigned   Flags;                     // +0x0140
};
GG_STATIC_ASSERT(offsetof(Obj_0074DE90, MapCoords)        == 0x24);
GG_STATIC_ASSERT(offsetof(Obj_0074DE90, OverlayTypeIndex) == 0x44);
GG_STATIC_ASSERT(offsetof(Obj_0074DE90, Flags)            == 0x140);

struct Map_0074DE90
{
    // FUNCTION: GAMEMD 0x578350 (decl; reloc) — restart the object iterator.
    void          FUN_00578350();
    // FUNCTION: GAMEMD 0x578290 (decl; reloc) — the iterator's next object.
    Obj_0074DE90* FUN_00578290();
};

// FUNCTION: GAMEMD 0x42B1F0 (decl; reloc) — the growth buffer's byte size.
unsigned int FUN_0042B1F0(void);
// FUNCTION: GAMEMD 0x42B1C0 (decl; reloc) — flat cell index of a coordinate.
int  FUN_0042B1C0(CellStruct* cell);
// FUNCTION: GAMEMD 0x74E1C0 (decl; reloc) — first-time vein growth seeding.
void FUN_0074E1C0(Veinhole_0074DE90* monster);
// FUNCTION: GAMEMD 0x74E6B0 (decl; reloc) — VeinholeMonsterClass::RecalculateSpread.
void FUN_0074E6B0(Veinhole_0074DE90* monster);
// FUNCTION: GAMEMD 0x74E8A0 (decl; reloc) — release one monster's growth data.
void FUN_0074E8A0(Veinhole_0074DE90* monster);

// LIBRARY: GAMEMD 0x7C8B3D — free (excluded from the match target).
void  __cdecl VeinFree(void* block);
// LIBRARY: GAMEMD 0x7C8E17 — operator new (excluded from the match target).
void* __cdecl VeinOperatorNew(unsigned int size);

// FUNCTION: GAMEMD 0x74DE90 — VeinholeMonsterClass::InitVeinGrowthData.
void InitVeinGrowthData(bool rebuild);

#endif  // GG_MATCH_MAP_VEINHOLE_INIT_GROWTH_METHODS_H
