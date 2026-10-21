// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and vtable slots read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x62A8E0: on the target
//   `[ESI+0x81]` InLimbo, `[ESI+0x90]` IsAlive, `[ESI+0x6C]` Health,
//   `[ESI+0x694]` ParasiteEatingMe, `[ESI+0x2E4]` BunkerLinkedItem (the same
//   offsets the committed FootClass spine pins); slots `[EAX+0x84]` (GetTechnoType) and
//   `[EAX+0x1BC]` (GetCell); on the type `[EAX+0xD38]` and `[EAX+0xCCE]`
//   (Naval); on this `[EDI+0x24]` Owner. Method/type names from YRpp
//   ParasiteClass.h / TechnoTypeClass.h / CellClass.h (consult-only).
#ifndef GG_MATCH_COMBAT_PARASITE_CLASS_INFECT_METHODS_H
#define GG_MATCH_COMBAT_PARASITE_CLASS_INFECT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// TechnoTypeClass — only the two booleans this predicate reads.
struct Type_0062A8E0
{
    char          _pad000[0xCCE];             // +0x0000
    unsigned char Naval;                      // +0x0CCE
    char          _padCCF[0xD38 - 0xCCF];     // +0x0CCF
    unsigned char At_D38;                     // +0x0D38 (parasite-able flag)
};
GG_STATIC_ASSERT(offsetof(Type_0062A8E0, Naval)  == 0xCCE);
GG_STATIC_ASSERT(offsetof(Type_0062A8E0, At_D38) == 0xD38);

// CellClass — opaque; only the water-tile predicate is called.
struct Cell_0062A8E0
{
    char opaque[4];

    // FUNCTION: GAMEMD 0x485060 (decl; reloc) — CellClass::Tile_Is_Water.
    bool Tile_Is_Water();
};

// Declaration order matters — see match/_rt/gg_vslot.h: the class must be
// complete before the member-function-pointer types.
struct InfectVtbl;

// The FootClass target uses the address-scoped FootInfect view below.
// Its touched offsets are binary-backed; this is not the complete layout.
// The former mixed class/struct access issue is fixed in the shared spine.
struct FootInfect
{
    InfectVtbl*   Vtbl;                       // +0x0000
    char          _pad004[0x6C - 0x4];        // +0x0004
    int           Health;                     // +0x006C
    char          _pad070[0x81 - 0x70];       // +0x0070
    unsigned char InLimbo;                    // +0x0081
    char          _pad082[0x90 - 0x82];       // +0x0082
    unsigned char IsAlive;                    // +0x0090
    char          _pad091[0x2E4 - 0x91];      // +0x0091
    void*         BunkerLinkedItem;           // +0x02E4
    char          _pad2E8[0x694 - 0x2E8];     // +0x02E8
    void*         ParasiteEatingMe;           // +0x0694
};
GG_STATIC_ASSERT(offsetof(FootInfect, Health)           == 0x6C);
GG_STATIC_ASSERT(offsetof(FootInfect, InLimbo)          == 0x81);
GG_STATIC_ASSERT(offsetof(FootInfect, IsAlive)          == 0x90);
GG_STATIC_ASSERT(offsetof(FootInfect, BunkerLinkedItem) == 0x2E4);
GG_STATIC_ASSERT(offsetof(FootInfect, ParasiteEatingMe) == 0x694);

typedef Type_0062A8E0* (FootInfect::*Fn084_Infect)();
typedef Cell_0062A8E0* (FootInfect::*Fn1BC_Infect)();

struct InfectVtbl
{
    char         _pad000[0x84];               // +0x0000
    Fn084_Infect GetTechnoType;               // +0x0084
    char         _pad088[0x1BC - 0x88];       // +0x0088
    Fn1BC_Infect GetCell;                     // +0x01BC
};
GG_STATIC_ASSERT(offsetof(InfectVtbl, GetTechnoType) == 0x84);
GG_STATIC_ASSERT(offsetof(InfectVtbl, GetCell)       == 0x1BC);

// ParasiteClass — only Owner @0x24 is touched.
struct ParasiteClass_0062A8E0
{
    char        _pad000[0x24];                // +0x0000
    FootInfect* Owner;                        // +0x0024

    // FUNCTION: GAMEMD 0x62A8E0
    bool CanInfect(FootInfect* target);
};
GG_STATIC_ASSERT(offsetof(ParasiteClass_0062A8E0, Owner) == 0x24);

#endif  // GG_MATCH_COMBAT_PARASITE_CLASS_INFECT_METHODS_H
