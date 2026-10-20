// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// RTTI: vtable0x7F5A24 slot+0x38 points to0x729E50; its COL0x80CAE8
// names TunnelLocomotionClass via descriptor0x844AA0 and has object offset4.
// This models the incoming ILoco interface at complete-object+4. Asserted
// member offsets are relative to that interface, not the complete object.
// Entry, field offsets and call conventions confirmed from retail gamemd.exe
// v1.001 instructions. Ghidra omitted case blocks from the entry's function-body
// record; disassembly from 0x729E50 and the table at 0x72A000 recover their
// order and extents through the final RET 4 at 0x729FFA.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Coord_00729E50 { int X; int Y; int Z; };
struct Point_00729E50 { int X; int Y; };
GG_STATIC_ASSERT(offsetof(Coord_00729E50, X) == 0x0);
GG_STATIC_ASSERT(offsetof(Coord_00729E50, Y) == 0x4);
GG_STATIC_ASSERT(offsetof(Coord_00729E50, Z) == 0x8);
GG_STATIC_ASSERT(sizeof(Coord_00729E50) == 0xC);
GG_STATIC_ASSERT(offsetof(Point_00729E50, X) == 0x0);
GG_STATIC_ASSERT(offsetof(Point_00729E50, Y) == 0x4);
GG_STATIC_ASSERT(sizeof(Point_00729E50) == 0x8);

struct DirValue_00729E50 { unsigned int Value; };
GG_STATIC_ASSERT(offsetof(DirValue_00729E50, Value) == 0x0);
GG_STATIC_ASSERT(sizeof(DirValue_00729E50) == 0x4);
struct Facing_00729E50
{
    // 0x4C93D0 reads members at +0x08, +0x10 and +0x14 on this object.
    char unknown_00[0x18];
    // FUNCTION: GAMEMD 0x4C93D0 (decl; reloc)
    DirValue_00729E50* Current(DirValue_00729E50* out);
};
GG_STATIC_ASSERT(sizeof(Facing_00729E50) == 0x18);

struct Base_00729E50
{
    char unknown_00[0x9C];
    Coord_00729E50 Location;
    char unknown_A8[0x388 - 0xA8];
    Facing_00729E50 PrimaryFacing;
};
GG_STATIC_ASSERT(offsetof(Base_00729E50, Location) == 0x9C);
GG_STATIC_ASSERT(offsetof(Base_00729E50, PrimaryFacing) == 0x388);
GG_STATIC_ASSERT(sizeof(Base_00729E50) == 0x3A0);

struct TunnelLocomotionInterface_00729E50
{
    char unknown_00[8];
    Base_00729E50* Base;
    char unknown_0C[0x14 - 0x0C];
    int At_14;
    char unknown_18[0x24 - 0x18];
    int At_24;
    char unknown_28[0x2C - 0x28];
    int At_2C;
    int At_30;
    unsigned char At_34;
};
GG_STATIC_ASSERT(offsetof(TunnelLocomotionInterface_00729E50, Base) == 0x08);
GG_STATIC_ASSERT(offsetof(TunnelLocomotionInterface_00729E50, At_14) == 0x14);
GG_STATIC_ASSERT(offsetof(TunnelLocomotionInterface_00729E50, At_24) == 0x24);
GG_STATIC_ASSERT(offsetof(TunnelLocomotionInterface_00729E50, At_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(TunnelLocomotionInterface_00729E50, At_30) == 0x30);
GG_STATIC_ASSERT(offsetof(TunnelLocomotionInterface_00729E50, At_34) == 0x34);
GG_STATIC_ASSERT(sizeof(TunnelLocomotionInterface_00729E50) == 0x38);

struct Tactical_00729E50
{
    // FUNCTION: GAMEMD 0x6D2140 (decl; reloc)
    bool CoordsToClient(const Coord_00729E50* coord, Point_00729E50* point);
};
struct Map_00729E50
{
    // FUNCTION: GAMEMD 0x578080 (decl; reloc)
    int GetZPos(Coord_00729E50* coord);
};

// GLOBAL: GAMEMD 0x887324 — pointer loaded by the entry before both projections.
extern Tactical_00729E50* DAT_00887324;
// GLOBAL: GAMEMD 0x87F7E8 — map object passed as ECX to GetZPos.
extern Map_00729E50 DAT_0087F7E8;
// GLOBAL: GAMEMD 0xA8ED84 — frame value read by the progress calculation.
#include "../core/frame_counter.h"
// GLOBAL: GAMEMD 0x844A9C — integer scale added in switch cases.
extern int DAT_00844A9C;
// GLOBAL: GAMEMD 0x844A98 — integer scale used by modes 5 and 6.
extern int DAT_00844A98;
// GLOBAL: GAMEMD 0x7E1718 — double constant used by the mode-6 case.
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7E3550 — double threshold used by the mode-2 case.
extern const double DAT_007E3550;

// FUNCTION: GAMEMD 0x55ABA0 (decl; reloc) — one-argument callback that returns zero.
extern "C" int __stdcall FUN_0055ABA0(TunnelLocomotionInterface_00729E50* resource);

// FUNCTION: GAMEMD 0x729E50
// PARTIAL: 31/140 instructions (22.1%) after the unsigned-shift correction.
// The switch cases and their values are recovered from the binary table.
// VC6 still lays out progress calculations, live locals and case blocks
// differently from retail; 109 instruction mismatches remain.
extern "C" int __stdcall FUN_00729E50(TunnelLocomotionInterface_00729E50* resource)
{
    Coord_00729E50 coord = resource->Base->Location;
    Point_00729E50 first;
    DAT_00887324->CoordsToClient(&coord, &first);
    coord.Z = DAT_0087F7E8.GetZPos(&coord);
    Point_00729E50 second;
    DAT_00887324->CoordsToClient(&coord, &second);

    int yDelta = first.Y;
    int total = resource->At_30;
    int secondY = second.Y;
    yDelta -= secondY;
    double progress;
    if (total == 0) {
        progress = 1.0;
    } else {
        int elapsedProgress = resource->At_2C;
        if (resource->At_24 != -1) {
            int elapsed = CurrentFrame - resource->At_24;
            if (elapsed < resource->At_2C) {
                elapsedProgress -= elapsed;
            } else {
                elapsedProgress = 0;
            }
        }
        progress = (double)(total - elapsedProgress) / total;
    }

    DirValue_00729E50 facing;
    DirValue_00729E50* facingValue = resource->Base->PrimaryFacing.Current(&facing);
    int direction = ((facingValue->Value >> 7) + 1) >> 1;
    direction &= 0xFF;

    switch (resource->At_14) {
    case 4:
        return DAT_00844A9C + yDelta;
    case 6:
        return (int)((DAT_007E1718 - progress) * DAT_00844A98 + coord.Z);
    case 2:
        if (progress > DAT_007E3550 && resource->At_34 == 0) {
            resource->At_34 = 1;
        }
        if (direction > 0x46 && direction < 0x8C) {
            return DAT_00844A9C + yDelta;
        }
        return (int)(DAT_00844A9C * progress + coord.Z);
    case 3:
    {
        int result = yDelta;
        result += DAT_00844A9C;
        return result;
    }
    case 5:
    {
        int result = DAT_00844A98;
        result += yDelta;
        return result;
    }
    default:
        return FUN_0055ABA0(resource);
    }
}
