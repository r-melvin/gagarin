// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x44ABD0: `PUSH 0x5C; CALL 0x7C8E17` (operator new,
//   sizeof LaserDrawClass), the 12-argument __thiscall constructor 0x54FE60
//   whose pushes are (right to left) 0.0f, 1.0f, 1, 0, `[[0x8871E0]+0x4A8]`,
//   three 3-byte colours (two copies of a zeroed local, one from
//   `[ESI+0x21C]+0x56FC` on the building type), 1, 0, the 12-byte target
//   coordinate from the parameter slots and the 12-byte result of vtable slot
//   `[EDX+0xB0]` (GetFLH: hidden result pointer, 0, zero coordinate by
//   value); on the new laser `[EAX+0x1C]` = 3 and byte `[EAX+0x20]` = 1;
//   on the building `[ESI+0x664]` = 0 and the timer at `LEA EDX,[ESI+0x2EC]`
//   stamped from `[0xA8ED84]` (CurrentFrame) with `[[0x8871E0]+0x4A4]`.
//   Names cross-checked against YRpp
//   and used as names only.
#ifndef GG_MATCH_COMBAT_BUILDING_CLASS_FIRE_LASER_METHODS_H
#define GG_MATCH_COMBAT_BUILDING_CLASS_FIRE_LASER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// FUNCTION: GAMEMD 0x7C8E17 (decl; reloc) — operator new.
void* __cdecl operator new(unsigned int size);

// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame.
#include "../core/frame_counter.h"

struct Coord_0044ABD0
{
    int X;                    // +0x0000
    int Y;                    // +0x0004
    int Z;                    // +0x0008

    Coord_0044ABD0() {}
    Coord_0044ABD0(int x, int y, int z) : X(x), Y(y), Z(z) {}
};
GG_STATIC_ASSERT(sizeof(Coord_0044ABD0) == 0xC);

struct Color_0044ABD0
{
    unsigned char R;          // +0x0000
    unsigned char G;          // +0x0001
    unsigned char B;          // +0x0002
};
GG_STATIC_ASSERT(sizeof(Color_0044ABD0) == 3);

// RulesClass — the two prism-support words.
struct Rules_0044ABD0
{
    char _pad000[0x4A4];      // +0x0000
    int  At_4A4;              // +0x04A4  timer length
    int  At_4A8;              // +0x04A8  laser duration
};
GG_STATIC_ASSERT(offsetof(Rules_0044ABD0, At_4A4) == 0x4A4);
GG_STATIC_ASSERT(offsetof(Rules_0044ABD0, At_4A8) == 0x4A8);
// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance.
extern Rules_0044ABD0* DAT_008871E0;

// BuildingTypeClass — only the laser colour at +0x56FC.
struct BuildingType_0044ABD0
{
    char _pad000[0x56FC];     // +0x0000
    Color_0044ABD0 At_56FC;   // +0x56FC
};
GG_STATIC_ASSERT(offsetof(BuildingType_0044ABD0, At_56FC) == 0x56FC);

// LaserDrawClass (0x5C bytes): StageClass Progress, Thickness, IsHouseColor.
struct LaserDraw_0044ABD0
{
    char _pad000[0x1C];       // +0x0000  StageClass Progress
    int  Thickness;           // +0x001C
    bool IsHouseColor;        // +0x0020
    char _pad021[0x5C - 0x21];// +0x0021

    // FUNCTION: GAMEMD 0x54FE60 (decl; reloc) — the constructor, called
    // explicitly on the raw block (returns `this`). A real `new T(...)` would
    // either wrap the argument evaluation in an EH frame (/GX) or, with the
    // ctor declared throw(), crash cl 12.00.8804 (C1001 msc1.cpp:1794) on the
    // struct-returning slot call nested in the argument list.
    LaserDraw_0044ABD0* Construct(Coord_0044ABD0 source, Coord_0044ABD0 target, int zAdjust,
                                  unsigned char unknown, Color_0044ABD0 inner,
                                  Color_0044ABD0 outer, Color_0044ABD0 outerSpread,
                                  int duration, bool blinks, bool fades,
                                  float startIntensity, float endIntensity);
};
GG_STATIC_ASSERT(offsetof(LaserDraw_0044ABD0, Thickness) == 0x1C);
GG_STATIC_ASSERT(offsetof(LaserDraw_0044ABD0, IsHouseColor) == 0x20);
GG_STATIC_ASSERT(sizeof(LaserDraw_0044ABD0) == 0x5C);

// FrameTimer — empty clock policy whose value is CurrentFrame.
struct FrameTimer_0044ABD0
{
    operator int() const { return CurrentFrame; }
};

// CDTimerClass<FrameTimer> (0xC bytes); CurrentTime is never written by the
// ctor and is copied through as the `[ESP+0x28]` load.
struct CDTimer_0044ABD0
{
    int                 StartTime;   // +0x0000
    FrameTimer_0044ABD0 CurrentTime; // +0x0004
    int                 TimeLeft;    // +0x0008

    CDTimer_0044ABD0(int duration)
    {
        this->StartTime = this->CurrentTime;
        this->TimeLeft = duration;
    }
};
GG_STATIC_ASSERT(sizeof(CDTimer_0044ABD0) == 0xC);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct BuildingVtbl_0044ABD0;
struct Building_0044ABD0
{
    BuildingVtbl_0044ABD0* Vtbl;      // +0x0000
    char _pad004[0x21C - 4];          // +0x0004
    BuildingType_0044ABD0* Type;      // +0x021C
    char _pad220[0x2EC - 0x220];      // +0x0220
    CDTimer_0044ABD0 At_2EC;          // +0x02EC  support-beam timer
    char _pad2F8[0x664 - 0x2F8];      // +0x02F8
    int  At_664;                      // +0x0664

    // FUNCTION: GAMEMD 0x44ABD0 — BuildingClass::FireLaser.
    void FireLaser(Coord_0044ABD0 target);
};
GG_STATIC_ASSERT(offsetof(Building_0044ABD0, Type) == 0x21C);
GG_STATIC_ASSERT(offsetof(Building_0044ABD0, At_2EC) == 0x2EC);
GG_STATIC_ASSERT(offsetof(Building_0044ABD0, At_664) == 0x664);

// GetFLH's hidden result pointer is spelled out as the first argument; the
// named `flh` local it fills is what keeps the temporary in the frame (retail
// `LEA EAX,[ESP+0x5C]`) instead of the dead parameter slot.
typedef Coord_0044ABD0* (Building_0044ABD0::*FnB0_0044ABD0)(Coord_0044ABD0* out, int weaponIndex, Coord_0044ABD0 base);
struct BuildingVtbl_0044ABD0
{
    char _pad000[0xB0];               // +0x0000
    FnB0_0044ABD0 GetFLH;             // +0x00B0
};
GG_STATIC_ASSERT(offsetof(BuildingVtbl_0044ABD0, GetFLH) == 0xB0);

#endif  // GG_MATCH_COMBAT_BUILDING_CLASS_FIRE_LASER_METHODS_H
