// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Found by sweeping 0x70F600..0x710700 as raw bytes; the Ghidra analysis
//   does not list this entry. Read numerically at 0x70FD70: the drain link is
//   the pair at +0x1CC on this object and +0x1D0 on the target, matching the
//   two already-matched predicates at 0x70FEB0 and 0x70FEC0. The target's
//   owner at +0x21C gets a byte set at +0x5778; the target's buffer at +0x2BC
//   is released through 0x472140; an animation of 0x1C8 bytes is allocated,
//   built from a coordinate produced by vtable slot +0x48 and a rules field
//   at +0x31C, stored at +0x1D4 and then attached back to this object.
#ifndef GG_MATCH_MOVEMENT_LOCOMOTION_BEGIN_DRAIN_METHODS_H
#define GG_MATCH_MOVEMENT_LOCOMOTION_BEGIN_DRAIN_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// FUNCTION: GAMEMD 0x7C8E17 (decl; reloc) — operator new.
extern "C" void* __cdecl gg_operator_new(unsigned int size);
// FUNCTION: GAMEMD 0x47C520 (decl; reloc) — the cell's occupying building.
void* __fastcall FUN_0047C520(void* cell);
// FUNCTION: GAMEMD 0x472140 (decl; reloc) — release the target's buffer.
void __fastcall FUN_00472140(void* buffer);
// FUNCTION: GAMEMD 0x6EA870 (decl; reloc) — refresh this object's display.
void __stdcall FUN_006EA870(void* self, int a, int b);

struct Coord_0070FD70
{
    int X;   // +0x0000
    int Y;   // +0x0004
    int Z;   // +0x0008
};

struct Anim_0070FD70
{
    // FUNCTION: GAMEMD 0x421EA0 (decl; reloc) — build the animation.
    Anim_0070FD70* Construct(int type, const Coord_0070FD70& where);
    // FUNCTION: GAMEMD 0x424B50 (decl; reloc) — attach it to its owner.
    void Attach(void* owner);
};

struct Rules_0070FD70
{
    char _pad000[0x31C];   // +0x0000
    int  DrainAnim;        // +0x031C
};
GG_STATIC_ASSERT(offsetof(Rules_0070FD70, DrainAnim) == 0x31C);
// GLOBAL: GAMEMD 0x8871E0
extern Rules_0070FD70* RulesInstance;

struct Owner_0070FD70
{
    char _pad000[0x5778];  // +0x0000
    char IsDraining;       // +0x5778
};
GG_STATIC_ASSERT(offsetof(Owner_0070FD70, IsDraining) == 0x5778);

struct Target_0070FD70
{
    char            _pad000[0x1D0];        // +0x0000
    void*           DrainedBy;             // +0x01D0
    char            _pad1D4[0x21C - 0x1D4];
    Owner_0070FD70* Owner;                 // +0x021C
    char            _pad220[0x2BC - 0x220];
    void*           Buffer;                // +0x02BC
};
GG_STATIC_ASSERT(offsetof(Target_0070FD70, DrainedBy) == 0x1D0);
GG_STATIC_ASSERT(offsetof(Target_0070FD70, Owner)     == 0x21C);
GG_STATIC_ASSERT(offsetof(Target_0070FD70, Buffer)    == 0x2BC);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_0070FD70;

struct Drainer_0070FD70
{
    Vtbl_0070FD70*  Vtbl;                  // +0x0000
    char            _pad004[0x14 - 0x04];
    int             Flags;                 // +0x0014
    char            _pad018[0x1CC - 0x18];
    Target_0070FD70* DrainingWhom;         // +0x01CC
    void*           DrainingMe;            // +0x01D0
    Anim_0070FD70*  DrainAnim;             // +0x01D4
    char            _pad1D8[0x5D4 - 0x1D8];
    void*           Display;               // +0x05D4

    // FUNCTION: GAMEMD 0x70FD70
    void BeginDraining(Target_0070FD70* target);
};
GG_STATIC_ASSERT(offsetof(Drainer_0070FD70, Flags)        == 0x14);
GG_STATIC_ASSERT(offsetof(Drainer_0070FD70, DrainingWhom) == 0x1CC);
GG_STATIC_ASSERT(offsetof(Drainer_0070FD70, DrainingMe)   == 0x1D0);
GG_STATIC_ASSERT(offsetof(Drainer_0070FD70, DrainAnim)    == 0x1D4);
GG_STATIC_ASSERT(offsetof(Drainer_0070FD70, Display)      == 0x5D4);

typedef void*            (Drainer_0070FD70::*Fn1BC_0070FD70)();
typedef Coord_0070FD70   (Drainer_0070FD70::*Fn48_0070FD70)(int a, int b, int c, int d, int e);

struct Vtbl_0070FD70
{
    char            _pad000[0x48];           // +0x0000
    Fn48_0070FD70   BuildCoord;              // +0x0048
    char            _pad04C[0x1BC - 0x4C];   // +0x004C
    Fn1BC_0070FD70  OccupiedCell;            // +0x01BC
};
GG_STATIC_ASSERT(offsetof(Vtbl_0070FD70, BuildCoord)   == 0x48);
GG_STATIC_ASSERT(offsetof(Vtbl_0070FD70, OccupiedCell) == 0x1BC);

#endif  // GG_MATCH_MOVEMENT_LOCOMOTION_BEGIN_DRAIN_METHODS_H
