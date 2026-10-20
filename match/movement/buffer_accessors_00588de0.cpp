// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; entry disassembly and raw bytes 0x588DE0..0x589054.
// Record-return REA evidence: ev_56624f5f12f8709047e85d1dabbdd02d835b9f85688de97ccbd7886f1952deb1.
// Index routines subtract addresses as unsigned values, then divide by the
// element stride. Value returns preserve the retail copy widths and RET 8.
#include "buffer_accessors_00588de0.h"
// FUNCTION: GAMEMD 0x588DE0
unsigned int BufferAccessors_00588DE0::Index36(const void* item) const
{
    if (!Valid) return 0;
    return ((unsigned int)item - (unsigned int)Data) / 36;
}
// FUNCTION: GAMEMD 0x588EF0
unsigned int BufferAccessors_00588DE0::FUN_00588EF0(int index) const
{
    return Data[index];
}
// FUNCTION: GAMEMD 0x588F30
unsigned int BufferAccessors_00588DE0::Index4(const void* item) const
{
    if (!Valid) return 0;
    return ((unsigned int)item - (unsigned int)Data) / 4;
}
// FUNCTION: GAMEMD 0x588F50
unsigned int BufferAccessors_00588DE0::FUN_00588F50(int index) const
{
    return Data[index];
}
// FUNCTION: GAMEMD 0x588F90
unsigned int BufferAccessors_00588DE0::Index8(const void* item) const
{
    if (!Valid) return 0;
    return ((unsigned int)item - (unsigned int)Data) / 8;
}
// FUNCTION: GAMEMD 0x588FB0
BufferPair_00588FB0 BufferAccessors_00588DE0::GetPair(int index) const
{
    return ((BufferPair_00588FB0*)Data)[index];
}
// FUNCTION: GAMEMD 0x589000
unsigned int BufferAccessors_00588DE0::Index12(const void* item) const
{
    if (!Valid) return 0;
    return ((unsigned int)item - (unsigned int)Data) / 12;
}
// FUNCTION: GAMEMD 0x589030
BufferTriple_00589030 BufferAccessors_00588DE0::GetTriple(int index) const
{
    return ((BufferTriple_00589030*)Data)[index];
}
