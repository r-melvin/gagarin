// Provenance: own-binary-via-Ghidra
//
// Constructor of the eight-way direction dial control (vtable 0x7E5E3C), a
// ControlClass built with flags 7 and sticky. It caches the face centre and
// two rings of eight compass points (outer ring at 0.4 / 0.28 of the size,
// inner ring at 0.3 / 0.21) and the initial direction and its facing.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "control_class.h"

struct DialPoint
{
    int X;   // +0x0
    int Y;   // +0x4
};

// Direction held as the high byte of a 16-bit binary angle; the facing is
// read back through the full dword.
union DialDirection
{
    DialDirection(int dir)
    {
        Raw = (unsigned short)(dir << 8);
    }
    int Facing() const { return (((Value >> 12) + 1) >> 1) & 7; }

    unsigned       Value;
    unsigned short Raw;
};

// VTABLE: GAMEMD 0x7E5E3C
struct DirectionDial_004A53B0 : ControlClass
{
    DirectionDial_004A53B0(int id, int x, int y, int width, int height, int direction);

    virtual int Draw(int forced);
    virtual int Action(unsigned flags, unsigned* key, int modifier);

    int       unknown_2C;           // +0x2C
    int       unknown_30;           // +0x30
    DialPoint OuterPoint[8];   // +0x34
    DialPoint InnerPoint[8];   // +0x74
    int       Direction;       // +0xB4
    int       Facing;          // +0xB8
    int       unknown_BC;       // +0xBC
};
GG_STATIC_ASSERT(offsetof(DirectionDial_004A53B0, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(DirectionDial_004A53B0, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(DirectionDial_004A53B0, OuterPoint) == 0x34);
GG_STATIC_ASSERT(offsetof(DirectionDial_004A53B0, InnerPoint) == 0x74);
GG_STATIC_ASSERT(offsetof(DirectionDial_004A53B0, Direction) == 0xB4);
GG_STATIC_ASSERT(offsetof(DirectionDial_004A53B0, Facing) == 0xB8);
GG_STATIC_ASSERT(offsetof(DirectionDial_004A53B0, unknown_BC) == 0xBC);

// FUNCTION: GAMEMD 0x4A53B0
DirectionDial_004A53B0::DirectionDial_004A53B0(int id, int x, int y, int width, int height, int direction)
    : ControlClass(id, x, y, width, height, 7, 1)
{
    unknown_2C = X + Width / 2;
    unknown_30 = Y + Height / 2;
    Direction = direction;
    Facing = DialDirection(direction).Facing();
    unknown_BC = Facing;

    OuterPoint[0].X = unknown_2C;
    OuterPoint[0].Y = unknown_30 - (height * 8 / 2) / 10;
    OuterPoint[1].X = unknown_2C + (width * 56 / 2) / 100;
    OuterPoint[1].Y = unknown_30 - (height * 56 / 2) / 100;
    OuterPoint[2].X = unknown_2C + (width * 8 / 2) / 10;
    OuterPoint[2].Y = unknown_30;
    OuterPoint[3].X = unknown_2C + (width * 56 / 2) / 100;
    OuterPoint[3].Y = unknown_30 + (height * 56 / 2) / 100;
    OuterPoint[4].X = unknown_2C;
    OuterPoint[4].Y = unknown_30 + (height * 8 / 2) / 10;
    OuterPoint[5].X = unknown_2C - (width * 56 / 2) / 100;
    OuterPoint[5].Y = unknown_30 + (height * 56 / 2) / 100;
    OuterPoint[6].X = unknown_2C - (width * 8 / 2) / 10;
    OuterPoint[6].Y = unknown_30;
    OuterPoint[7].X = unknown_2C - (width * 56 / 2) / 100;
    OuterPoint[7].Y = unknown_30 - (height * 56 / 2) / 100;

    InnerPoint[0].X = unknown_2C;
    InnerPoint[0].Y = unknown_30 - (height * 6 / 2) / 10;
    InnerPoint[1].X = unknown_2C + (width * 42 / 2) / 100;
    InnerPoint[1].Y = unknown_30 - (height * 42 / 2) / 100;
    InnerPoint[2].X = unknown_2C + (width * 6 / 2) / 10;
    InnerPoint[2].Y = unknown_30;
    InnerPoint[3].X = unknown_2C + (width * 42 / 2) / 100;
    InnerPoint[3].Y = unknown_30 + (height * 42 / 2) / 100;
    InnerPoint[4].X = unknown_2C;
    InnerPoint[4].Y = unknown_30 + (height * 6 / 2) / 10;
    InnerPoint[5].X = unknown_2C - (width * 42 / 2) / 100;
    InnerPoint[5].Y = unknown_30 + (height * 42 / 2) / 100;
    InnerPoint[6].X = unknown_2C - (width * 6 / 2) / 10;
    InnerPoint[6].Y = unknown_30;
    InnerPoint[7].X = unknown_2C - (width * 42 / 2) / 100;
    InnerPoint[7].Y = unknown_30 - (height * 42 / 2) / 100;
}
