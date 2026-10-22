// Provenance: own-binary-via-Ghidra
//   Bytes read off the user's retail gamemd.exe v1.001 via the local Ghidra
//   CLI at 0x7ACA00, 0x7AD790, 0x7ADB00 and 0x7AE5D0: four out-of-line copies
//   of one growable-array Insert (__thiscall, `RET 8`: item reference, index)
//   for element sizes 0x6C, 0x10C, 4 and a 4-byte class whose copy
//   constructor is 0x7B4690. The same grow-by-doubling (minimum 10) body is
//   inlined into 0x775DB0.
//
// This is not the VectorClass/DynamicVectorClass family: no vtable, the
// layout is {count, capacity, data}.
// No /GX: with it VC6 wraps the placement copy-construction of the handle
// instance (0x7AE5D0) in an unwind frame retail does not have.
#include "grow_list.h"
#include "../_rt/gg_static_assert.h"

// The two plain record element types (copied with REP MOVSD).
struct GrowListRecord6C
{
    int unknown_00[0x1B];
};
struct GrowListRecord10C
{
    int unknown_00[0x43];
};

// FUNCTION: GAMEMD 0x7ACA00
template struct GrowList<GrowListRecord6C>;
// FUNCTION: GAMEMD 0x7AD790
template struct GrowList<GrowListRecord10C>;
// FUNCTION: GAMEMD 0x7ADB00
template struct GrowList<int>;
// FUNCTION: GAMEMD 0x7AE5D0
template struct GrowList<GrowListHandle>;
