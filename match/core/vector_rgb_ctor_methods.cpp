// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail RTTI names VectorClass/DynamicVectorClass over RGBClass (3-byte elements, user-declared
// default constructor that zeroes the three bytes). The body is the DynamicVectorClass constructor
// taking a capacity and optional storage, with the VectorClass constructor expanded inline.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

struct RGBClass { unsigned char R; unsigned char G; unsigned char B; RGBClass() : R(0), G(0), B(0) {} bool operator==(const RGBClass& o) const { return R==o.R && G==o.G && B==o.B; } bool operator!=(const RGBClass& o) const { return !(*this==o); } };

// FUNCTION: GAMEMD 0x00645A70
// Constructor (capacity, optional storage) of the vector of RGBClass colours.
template class DynamicVectorClass<RGBClass>;
