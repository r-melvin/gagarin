// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Every offset below was read numerically off the user's retail gamemd.exe
//   v1.001 with the local Ghidra CLI, inside 0x471FF0:
//     [EDI+0x28] / [EDI+0x34]   ControlNodes Items / Count   (0x472015, 0x47200A)
//     [EBP+0x00] / [EBP+0x04]   ControlNode Unit / OriginalOwner (0x47201F, 0x4720D0)
//     [ESI+0x9C]                TechnoClass coords triple     (0x47205B, 0x4720A5)
//     [ESI+0x2C0]               MindControlledBy              (0x4720E8)
//     [ESI+0x2C8]               MindControlRingAnim           (0x472028, 0x47203A)
//     [EAX+0x5B0]               TechnoTypeClass sound index   (0x47204E, 0x472085)
//     [EAX+0x264] off 0x8871E0  RulesClass fallback sound     (0x47209D)
//     vtable slots [EAX+0x84], [EDX+0x3D4] on the unit and [EDX+0xF8] on the
//     ring animation.
//   Names (FreeUnit, MindControlRingAnim, VocClass::PlayAt) cross-checked
//   against YRpp; no YRpp text copied.
#ifndef GG_MATCH_COMBAT_CAPTURE_MANAGER_FREE_UNIT_METHODS_H
#define GG_MATCH_COMBAT_CAPTURE_MANAGER_FREE_UNIT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// CoordStruct — the 12-byte world coordinate triple at TechnoClass+0x9C.
// The user-declared empty constructor is what makes the by-value getter below
// store its temporary *after* the argument pushes, as retail does.
struct Coord_00471FF0
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08
    Coord_00471FF0() {}
};
GG_STATIC_ASSERT(offsetof(Coord_00471FF0, X) == 0x00);
GG_STATIC_ASSERT(offsetof(Coord_00471FF0, Y) == 0x04);
GG_STATIC_ASSERT(offsetof(Coord_00471FF0, Z) == 0x08);
GG_STATIC_ASSERT(sizeof(Coord_00471FF0) == 0x0C);

// FUNCTION: GAMEMD 0x7C8B3D (decl; reloc) -- YR game-heap free (operator
// delete); __cdecl, one pointer argument, caller pops.
void __cdecl GameDelete_00471FF0(void* block);

struct Rules_00471FF0
{
    char _pad000[0x264];   // +0x0000
    int  At_264;           // +0x0264  fallback "mind control lost" sound index
};
GG_STATIC_ASSERT(offsetof(Rules_00471FF0, At_264) == 0x264);

// GLOBAL: GAMEMD 0x8871E0 -- RulesClass::Instance.
extern Rules_00471FF0* RulesInstance_00471FF0;

struct TechnoType_00471FF0
{
    char _pad000[0x5B0];   // +0x0000
    int  At_5B0;           // +0x05B0  per-type "mind control lost" sound index
};
GG_STATIC_ASSERT(offsetof(TechnoType_00471FF0, At_5B0) == 0x5B0);

// The mind-control ring animation. Only its slot 0xF8 (no arguments) is used.
struct AnimVtbl_00471FF0;
struct Anim_00471FF0
{
    AnimVtbl_00471FF0* Vtbl;   // +0x0000
};
typedef void (Anim_00471FF0::*FnF8_00471FF0)();
struct AnimVtbl_00471FF0
{
    char          _pad000[0xF8];   // +0x0000
    FnF8_00471FF0 At_F8;           // +0x00F8
};
GG_STATIC_ASSERT(offsetof(Anim_00471FF0, Vtbl) == 0x00);
GG_STATIC_ASSERT(offsetof(AnimVtbl_00471FF0, At_F8) == 0xF8);

struct Vtbl_00471FF0;

// The controlled TechnoClass.
struct Techno_00471FF0
{
    Vtbl_00471FF0* Vtbl;                 // +0x0000
    char           _pad004[0x9C - 0x04]; // +0x0004
    Coord_00471FF0 Location;             // +0x009C
    char           _pad0A8[0x2C0 - 0xA8];// +0x00A8
    void*          MindControlledBy;     // +0x02C0
    char           _pad2C4[0x04];        // +0x02C4
    Anim_00471FF0* MindControlRingAnim;  // +0x02C8

    // By-value coordinate getter; see the CoordStruct note above.
    Coord_00471FF0 GetCoords() const
    {
        Coord_00471FF0 r = this->Location;
        return r;
    }
};
GG_STATIC_ASSERT(offsetof(Techno_00471FF0, Vtbl) == 0x00);
GG_STATIC_ASSERT(offsetof(Techno_00471FF0, Location)            == 0x9C);
GG_STATIC_ASSERT(offsetof(Techno_00471FF0, MindControlledBy)    == 0x2C0);
GG_STATIC_ASSERT(offsetof(Techno_00471FF0, MindControlRingAnim) == 0x2C8);

// Declared only after Techno_00471FF0 is complete -- see match/_rt/gg_vslot.h.
typedef TechnoType_00471FF0* (Techno_00471FF0::*Fn84_00471FF0)();
typedef void (Techno_00471FF0::*Fn3D4_00471FF0)(void* house, int announce);

struct Vtbl_00471FF0
{
    char           _pad000[0x84];             // +0x0000
    Fn84_00471FF0  At_84;                     // +0x0084  GetTechnoType()
    char           _pad088[0x3D4 - 0x88];     // +0x0088
    Fn3D4_00471FF0 At_3D4;                    // +0x03D4  SetOwningHouse(house, announce)
};
GG_STATIC_ASSERT(offsetof(Vtbl_00471FF0, At_84)  == 0x84);
GG_STATIC_ASSERT(offsetof(Vtbl_00471FF0, At_3D4) == 0x3D4);

// FUNCTION: GAMEMD 0x7509E0 (decl; reloc) -- VocClass::PlayAt(index, coords,
// controller). __fastcall: index in ECX, the coordinate address in EDX.
void* __fastcall VocClass_PlayAt_00471FF0(
    int index, const Coord_00471FF0& coords, void* controller);

// Shared control-node record: Unit +0, OriginalOwner +4.
#include "../_layout/control_node.h"

// Canonical CaptureManagerClass receiver layout.
#include "../_layout/capture_manager_class.h"

#endif  // GG_MATCH_COMBAT_CAPTURE_MANAGER_FREE_UNIT_METHODS_H
