// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; entry-origin retail disassembly 0x588C10..0x588D58.
// Subtraction REA evidence: ev_e95cf2963982bb9b62a3858ddc56c09d2586bd20e0f9e3a84f784f5c7e8a9cba.
// Raw instructions and VC6 confirm the hidden value-return pointer; the raw
// import pseudocode leaves that original C++ return convention unresolved.
#include "coordinate_helpers_00588c10.h"
// FUNCTION: GAMEMD 0x588C10
StateRecord_00588C10& StateRecord_00588C10::CopyState(const StateRecord_00588C10& other)
{
    unknown_10 = other.unknown_10;
    unknown_14 = other.unknown_14;
    unknown_18 = other.unknown_18;
    unknown_1C = other.unknown_1C;
    unknown_20 = other.unknown_20;
    return *this;
}
// FUNCTION: GAMEMD 0x588C40
Coordinate_00588C40& Coordinate_00588C40::Add(const Coordinate_00588C40& delta)
{
    X += delta.X;
    Y += delta.Y;
    return *this;
}
// FUNCTION: GAMEMD 0x588C60
Coordinate_00588C40 Coordinate_00588C40::Subtract(const Coordinate_00588C40& delta) const
{
    return Coordinate_00588C40(X - delta.X, Y - delta.Y);
}
// FUNCTION: GAMEMD 0x588CC0
unsigned int BufferIndex_00588CC0::Index8(const void* item) const
{
    if (!Valid) return 0;
    return ((unsigned int)item - (unsigned int)Data) >> 3;
}
// FUNCTION: GAMEMD 0x588D10
unsigned int BufferIndex_00588CC0::Index16(const void* item) const
{
    if (!Valid) return 0;
    return ((unsigned int)item - (unsigned int)Data) >> 4;
}
// FUNCTION: GAMEMD 0x588D30
ValueRecord_00588D30 RecordBuffer_00588D30::Get(int index) const
{
    return Data[index];
}
