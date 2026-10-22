// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x4585C0:
//     * the occupant list is an embedded DynamicVectorClass at +0x684 —
//       `MOV EDX,[ESI+0x684]` its vptr, `[ESI+0x688]` Items (indexed
//       `[EAX+EDI*4]`), `[ESI+0x68C]` Capacity (read before Clear and handed
//       straight to Resize), `[ESI+0x694]` Count; `LEA EDI,[ESI+0x684]` is the
//       receiver for slot +0x0C (Clear) and slot +0x08 (Resize, two stack
//       args). `[ESI+0x69C]` is the separate counter zeroed on entry.
//     * `[ESI+0x520]` Type (the same offset already confirmed in
//       match/combat/building_class_fog_methods.h), with the per-occupant
//       8-byte table at Type+0x1588 walked downwards
//       (`LEA EAX,[EDI*8+0x1588]` … `SUB ECX,8`).
//     * 0x6D2070 `<projector>::CoordsToClient(out, in)` on the instance
//       pointer `[0x887324]`, returning the 2-int client point in EAX; the
//       third component of the local coordinate is explicitly zeroed
//       (`MOV dword ptr [ESP+0x20],0`) before this building's slot +0xAC
//       coordinate is added component-wise.
//     * `PUSH 0x1C8; CALL 0x7C8E17` — operator new for an AnimClass,
//       constructed by 0x421EA0 with `(*killer->slot_3F8(...))->[+0x114]`,
//       and `[anim+0x100] = 0xFFFFFF38` (-200) written on the result whether
//       or not the allocation succeeded (retail's own null path).
//     * killer slot +0xE0 takes the occupant; occupant slot +0xF8 takes none.
//   Names cross-checked against YRpp.
#ifndef GG_MATCH_COMBAT_BUILDING_CLASS_KILL_OCCUPANTS_METHODS_H
#define GG_MATCH_COMBAT_BUILDING_CLASS_KILL_OCCUPANTS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Coord_004585C0 { int X; int Y; int Z; };
GG_STATIC_ASSERT(sizeof(Coord_004585C0) == 0xC);

struct Point_004585C0 { int X; int Y; };
GG_STATIC_ASSERT(sizeof(Point_004585C0) == 8);

struct Projector_004585C0
{
    // FUNCTION: GAMEMD 0x6D2070 (decl; reloc) — world -> client projection.
    Point_004585C0* CoordsToClient(Point_004585C0* out, const int* in);
};
// GLOBAL: GAMEMD 0x887324 — the projector instance pointer.
extern Projector_004585C0* DAT_00887324;

// ---------------------------------------------------------------------------
struct AnimType_004585C0;

struct Anim_004585C0
{
    char _pad000[0x100];   // +0x0000
    int  Unknown_100;      // +0x0100

    // FUNCTION: GAMEMD 0x421EA0 (decl; reloc) — the AnimClass constructor body.
    Anim_004585C0* Construct(AnimType_004585C0* type);
};
GG_STATIC_ASSERT(offsetof(Anim_004585C0, Unknown_100) == 0x100);

// The record the killer's slot +0x3F8 hands back a pointer-to-pointer to.
struct Warhead_004585C0
{
    char                 _pad000[0x114];   // +0x0000
    AnimType_004585C0*   AnimType;         // +0x0114
};
GG_STATIC_ASSERT(offsetof(Warhead_004585C0, AnimType) == 0x114);

// ---------------------------------------------------------------------------
struct OccupantVtbl_004585C0;

struct Occupant_004585C0
{
    OccupantVtbl_004585C0* Vptr;   // +0x0000
};

typedef void (Occupant_004585C0::*FnF8_004585C0)();

struct OccupantVtbl_004585C0
{
    char          _pad000[0xF8];   // +0x0000
    FnF8_004585C0 At_F8;           // +0x00F8
};
GG_STATIC_ASSERT(offsetof(OccupantVtbl_004585C0, At_F8) == 0xF8);

// ---------------------------------------------------------------------------
struct KillerVtbl_004585C0;

struct Killer_004585C0
{
    KillerVtbl_004585C0* Vptr;   // +0x0000
};

typedef Warhead_004585C0** (Killer_004585C0::*Fn3F8_004585C0)(
    int a, Coord_004585C0* where, int c, int d, int e, int f, int g);
typedef void (Killer_004585C0::*FnE0_004585C0)(Occupant_004585C0* victim);

struct KillerVtbl_004585C0
{
    char            _pad000[0xE0];            // +0x0000
    FnE0_004585C0   At_E0;                    // +0x00E0
    char            _pad0E4[0x3F8 - 0xE4];    // +0x00E4
    Fn3F8_004585C0  At_3F8;                   // +0x03F8
};
GG_STATIC_ASSERT(offsetof(KillerVtbl_004585C0, At_E0)  == 0xE0);
GG_STATIC_ASSERT(offsetof(KillerVtbl_004585C0, At_3F8) == 0x3F8);

// ---------------------------------------------------------------------------
// The embedded DynamicVectorClass<Occupant*> at BuildingClass+0x684.
struct OccupantVecVtbl_004585C0;

struct OccupantVec_004585C0
{
    OccupantVecVtbl_004585C0* Vptr;             // +0x0000
    Occupant_004585C0**       Items;            // +0x0004
    int                       Capacity;         // +0x0008
    char                      IsInitialized;    // +0x000C
    char                      IsAllocated;      // +0x000D
    char                      _pad00E[2];       // +0x000E
    int                       Count;            // +0x0010
    int                       CapacityIncrement;       // +0x0014
};
GG_STATIC_ASSERT(offsetof(OccupantVec_004585C0, Items)    == 0x04);
GG_STATIC_ASSERT(offsetof(OccupantVec_004585C0, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(OccupantVec_004585C0, Count)    == 0x10);
GG_STATIC_ASSERT(sizeof(OccupantVec_004585C0)             == 0x18);

typedef bool (OccupantVec_004585C0::*FnVec08_004585C0)(int capacity, void* array);
typedef void (OccupantVec_004585C0::*FnVec0C_004585C0)();

struct OccupantVecVtbl_004585C0
{
    char             _pad000[0x8];   // +0x0000
    FnVec08_004585C0 Resize;         // +0x0008
    FnVec0C_004585C0 Clear;          // +0x000C
};
GG_STATIC_ASSERT(offsetof(OccupantVecVtbl_004585C0, Clear) == 0xC);

// ---------------------------------------------------------------------------
// The building's type: only the 8-byte per-occupant table at +0x1588 is used.
struct BuildingType_004585C0
{
    char _pad0000[0x1588];               // +0x0000
    int  OccupantOffsets[1][2];          // +0x1588  (8 bytes per occupant)
};
GG_STATIC_ASSERT(offsetof(BuildingType_004585C0, OccupantOffsets) == 0x1588);

struct BuildingVtbl_004585C0;

struct Building_004585C0
{
    BuildingVtbl_004585C0* Vptr;                       // +0x0000
    char                   _pad0004[0x520 - 0x04];     // +0x0004
    BuildingType_004585C0* Type;                       // +0x0520
    char                   _pad0524[0x684 - 0x524];    // +0x0524
    OccupantVec_004585C0   Occupants;                  // +0x0684
    int                    Unknown_69C;                // +0x069C

    // FUNCTION: GAMEMD 0x70F6E0 (decl; reloc) — apply the recomputed value.
    void FUN_0070F6E0(int value);

    // FUNCTION: GAMEMD 0x4585C0 — BuildingClass::KillOccupants.
    void KillOccupants(Killer_004585C0* killer);
};
GG_STATIC_ASSERT(offsetof(Building_004585C0, Type)        == 0x520);
GG_STATIC_ASSERT(offsetof(Building_004585C0, Occupants)   == 0x684);
GG_STATIC_ASSERT(offsetof(Building_004585C0, Unknown_69C) == 0x69C);

typedef Coord_004585C0* (Building_004585C0::*FnAC_004585C0)(Coord_004585C0* out);
typedef int (Building_004585C0::*Fn1BC_004585C0)();

struct BuildingVtbl_004585C0
{
    char           _pad000[0xAC];             // +0x0000
    FnAC_004585C0  At_AC;                     // +0x00AC
    char           _pad0B0[0x1BC - 0xB0];     // +0x00B0
    Fn1BC_004585C0 At_1BC;                    // +0x01BC
};
GG_STATIC_ASSERT(offsetof(BuildingVtbl_004585C0, At_AC)  == 0xAC);
GG_STATIC_ASSERT(offsetof(BuildingVtbl_004585C0, At_1BC) == 0x1BC);

// LIBRARY: GAMEMD 0x7C8E17 — operator new (excluded from the match target).
void* __cdecl KillOccOperatorNew(unsigned int size);

#endif  // GG_MATCH_COMBAT_BUILDING_CLASS_KILL_OCCUPANTS_METHODS_H
