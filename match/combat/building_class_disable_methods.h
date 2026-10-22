// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x452480: on the building `[EDI+0x614]` (light
//   source), the bytes `[EDI+0x6EA]`, `[EDI+0x6EB]`, `[EDI+0x6EC]`,
//   `[EDI+0x269]`, `[EDI+0x80]`, the type at `[EDI+0x520]` and the 21
//   animation pointers from `[EDI+0x55C]`; on the type the bytes
//   `[EAX+0x16C7]`, `[EAX+0x1707]`, `[EAX+0xCD1]`, `[EAX+0x16BE]` and the
//   0x44-byte animation records from `[ECX+0xF8C]` (21 of them: the loop
//   stops at 0x594). Slot +0x418 is a zero-argument virtual. Names cross-
//   checked against YRpp: DisableStuff,
//   LightSource, CloakRadius, Type->CloakGenerator/CloakRadiusInCells/
//   GapGenerator; every offset reconfirmed here.
#ifndef GG_MATCH_COMBAT_BUILDING_CLASS_DISABLE_METHODS_H
#define GG_MATCH_COMBAT_BUILDING_CLASS_DISABLE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct LightSource_00452480
{
    // FUNCTION: GAMEMD 0x554A80 (decl; reloc) — switch the light source.
    void FUN_00554A80(char on);
};

struct Anim_00452480
{
    // FUNCTION: GAMEMD 0x425260 (decl; reloc) — halt the animation.
    void FUN_00425260();
};

// One per-slot animation record on the building type (0x44 bytes); only the
// leading enable byte is read here.
struct AnimRecord_00452480
{
    char Enabled;         // +0x00
    char _pad01[0x43];    // +0x01
};
GG_STATIC_ASSERT(sizeof(AnimRecord_00452480) == 0x44);

struct BuildingType_00452480
{
    char _pad0000[0xCD1];                 // +0x0000
    char GapGenerator;                    // +0x0CD1
    char _pad0CD2[0xF8C - 0xCD2];         // +0x0CD2
    AnimRecord_00452480 Anims[21];        // +0x0F8C
    char _pad1520[0x16BE - 0x1520];       // +0x1520
    char At_16BE;                         // +0x16BE
    char _pad16BF[0x16C7 - 0x16BF];       // +0x16BF
    char CloakGenerator;                  // +0x16C7
    char _pad16C8[0x1707 - 0x16C8];       // +0x16C8
    char CloakRadiusInCells;              // +0x1707
};
GG_STATIC_ASSERT(offsetof(BuildingType_00452480, GapGenerator) == 0xCD1);
GG_STATIC_ASSERT(offsetof(BuildingType_00452480, Anims) == 0xF8C);
GG_STATIC_ASSERT(offsetof(BuildingType_00452480, At_16BE) == 0x16BE);
GG_STATIC_ASSERT(offsetof(BuildingType_00452480, CloakGenerator) == 0x16C7);
GG_STATIC_ASSERT(offsetof(BuildingType_00452480, CloakRadiusInCells) == 0x1707);

struct Vtbl_00452480;

struct Building_00452480
{
    Vtbl_00452480* Vptr;                  // +0x0000
    char _pad0004[0x80 - 0x04];           // +0x0004
    char NeedsRedraw;                     // +0x0080
    char _pad0081[0x269 - 0x81];          // +0x0081
    char At_269;                          // +0x0269
    char _pad026A[0x520 - 0x26A];         // +0x026A
    BuildingType_00452480* Type;          // +0x0520
    char _pad0524[0x55C - 0x524];         // +0x0524
    Anim_00452480* Anims[21];             // +0x055C
    char _pad05B0[0x614 - 0x5B0];         // +0x05B0
    LightSource_00452480* LightSource;    // +0x0614
    char _pad0618[0x6EA - 0x618];         // +0x0618
    char At_6EA;                          // +0x06EA
    char At_6EB;                          // +0x06EB
    char CloakRadius;                     // +0x06EC

    // FUNCTION: GAMEMD 0x452480
    void DisableStuff();
    // FUNCTION: GAMEMD 0x4533A0 (decl; reloc)
    void FUN_004533A0(char flag);
};
GG_STATIC_ASSERT(offsetof(Building_00452480, NeedsRedraw) == 0x80);
GG_STATIC_ASSERT(offsetof(Building_00452480, At_269) == 0x269);
GG_STATIC_ASSERT(offsetof(Building_00452480, Type) == 0x520);
GG_STATIC_ASSERT(offsetof(Building_00452480, Anims) == 0x55C);
GG_STATIC_ASSERT(offsetof(Building_00452480, LightSource) == 0x614);
GG_STATIC_ASSERT(offsetof(Building_00452480, At_6EA) == 0x6EA);
GG_STATIC_ASSERT(offsetof(Building_00452480, At_6EB) == 0x6EB);
GG_STATIC_ASSERT(offsetof(Building_00452480, CloakRadius) == 0x6EC);

typedef void (Building_00452480::*Fn418_00452480)();

struct Vtbl_00452480
{
    char _pad000[0x418];         // +0x0000
    Fn418_00452480 At_418;       // +0x0418
};
GG_STATIC_ASSERT(offsetof(Vtbl_00452480, At_418) == 0x418);

#endif  // GG_MATCH_COMBAT_BUILDING_CLASS_DISABLE_METHODS_H
