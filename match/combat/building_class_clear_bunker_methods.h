// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x459470: `LEA ECX,[ESI+0x9c]` with three dword loads
//   (the building's CoordStruct), `[ESI+0x2E4]` (BunkerLinkedItem, cleared on
//   both objects), `[ESI+0x520]` (Type) with `ADD EAX,0x127c/0x128c/0x12c0/
//   0x12d0` (Type->Anims[12]/[13] name buffers, base 0xF4C at 0x44 per record
//   per match/economy/building_class_enable_methods.h), `[ESI+0x718]`, the
//   rules globals `[0x8871E0]` `+0x244` (int, -1 = none) and `+0x1700`
//   (double, the FCOMP operand), and the two virtual slots `[EDX+0x274]` and
//   `[EDX+0x1E8]`. YRpp (consult-only, no LICENSE) names ClearBunker,
//   BunkerLinkedItem and the health-ratio callee 0x5F5C60.
#ifndef GG_MATCH_COMBAT_BUILDING_CLASS_CLEAR_BUNKER_METHODS_H
#define GG_MATCH_COMBAT_BUILDING_CLASS_CLEAR_BUNKER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Coord_00459470 { int X; int Y; int Z; };
GG_STATIC_ASSERT(sizeof(Coord_00459470) == 0xC);

struct Rules_00459470
{
    char   _pad0000[0x244];              // +0x0000
    int    BunkerSound;                  // +0x0244  -1 = no sound
    char   _pad0248[0x1700 - 0x248];     // +0x0248
    double ConditionYellow;              // +0x1700
};
GG_STATIC_ASSERT(offsetof(Rules_00459470, BunkerSound)     == 0x244);
GG_STATIC_ASSERT(offsetof(Rules_00459470, ConditionYellow) == 0x1700);

// GLOBAL: GAMEMD 0x8871E0 -- RulesClass::Instance.
extern Rules_00459470* RulesInstance_00459470;

struct AudioHandle_00459470;
struct AudioController_00459470;

// FUNCTION: GAMEMD 0x7509E0 (decl; reloc) -- VocClass::PlayAt.
AudioHandle_00459470* __fastcall VocClass_PlayAt_00459470(
    int index, Coord_00459470* coords, AudioController_00459470* controller);

// One 0x44-byte per-animation record in BuildingTypeClass; only the two name
// buffers are touched here.
struct AnimRecord_00459470
{
    char NameNormal[0x10];       // +0x00
    char NameDamaged[0x10];      // +0x10
    char _pad20[0x44 - 0x20];    // +0x20
};
GG_STATIC_ASSERT(offsetof(AnimRecord_00459470, NameDamaged) == 0x10);
GG_STATIC_ASSERT(sizeof(AnimRecord_00459470) == 0x44);

struct BuildingType_00459470
{
    char                _pad0000[0xF4C];     // +0x0000
    AnimRecord_00459470 Anims[21];           // +0x0F4C
};
GG_STATIC_ASSERT(offsetof(BuildingType_00459470, Anims) == 0xF4C);

struct Vtbl_00459470;

struct Building_00459470
{
    Vtbl_00459470*          Vptr;                        // +0x0000
    char                    _pad0004[0x9C - 0x04];       // +0x0004
    Coord_00459470          Location;                    // +0x009C
    char                    _pad00A8[0x2E4 - 0xA8];      // +0x00A8
    Building_00459470*      BunkerLinkedItem;            // +0x02E4
    char                    _pad02E8[0x520 - 0x2E8];     // +0x02E8
    BuildingType_00459470*  Type;                        // +0x0520
    char                    _pad0524[0x718 - 0x524];     // +0x0524
    int                     unknown_718;                 // +0x0718

    // FUNCTION: GAMEMD 0x451890 (decl; reloc) -- the per-animation worker.
    void PlayAnim(const char* name, int index, int damaged, int a4, int a5);
    // FUNCTION: GAMEMD 0x451E40 (decl; reloc) -- BuildingClass::DestroyNthAnim.
    void DestroyNthAnim(int slot);
    // FUNCTION: GAMEMD 0x5F5C60 (decl; reloc) -- ObjectClass::GetHealthPercentage.
    double GetHealthPercentage() const;

    // FUNCTION: GAMEMD 0x459470 -- BuildingClass::ClearBunker.
    void ClearBunker();
};
GG_STATIC_ASSERT(offsetof(Building_00459470, Location)         == 0x9C);
GG_STATIC_ASSERT(offsetof(Building_00459470, BunkerLinkedItem) == 0x2E4);
GG_STATIC_ASSERT(offsetof(Building_00459470, Type)             == 0x520);
GG_STATIC_ASSERT(offsetof(Building_00459470, unknown_718)      == 0x718);

typedef void (Building_00459470::*Fn1E8_00459470)(int mission, int immediate);
typedef void (Building_00459470::*Fn274_00459470)(int mode);

struct Vtbl_00459470
{
    char _pad000[0x1E8];                 // +0x0000
    Fn1E8_00459470 At_1E8;               // +0x01E8
    char _pad1EC[0x274 - 0x1EC];         // +0x01EC
    Fn274_00459470 At_274;               // +0x0274
};
GG_STATIC_ASSERT(offsetof(Vtbl_00459470, At_1E8) == 0x1E8);
GG_STATIC_ASSERT(offsetof(Vtbl_00459470, At_274) == 0x274);

#endif  // GG_MATCH_COMBAT_BUILDING_CLASS_CLEAR_BUNKER_METHODS_H
