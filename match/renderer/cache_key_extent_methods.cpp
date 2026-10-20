// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x600670 and 0x600680.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x600670  CacheKey_00600670::Extent     (__thiscall)
//   FUNCTION: GAMEMD 0x600680  CacheKey_00600670::operator== (__thiscall)

#include "cache_key_extent_methods.h"

// FUNCTION: GAMEMD 0x600670  CacheKey_00600670::Extent (__thiscall)
// Total cell count spanned by the key — the product of its two extents. Retail
// loads the +4 field into EAX and multiplies by the +0 field in memory, which
// both operand orders reproduce exactly.
int CacheKey_00600670::Extent()
{
    return Height * Width;
}

// FUNCTION: GAMEMD 0x600680  CacheKey_00600670::operator== (__thiscall)
// Key equality, used to confirm a hash-bucket hit before the entry is reused.
//
// The result must reach the return through an explicit `if`, not as a bare
// comparison chain: written as `return other.Height == Height && ...` cl
// materialises the answer in the full EAX (`MOV EAX,1` / `XOR EAX,EAX`) where
// retail uses the byte form (`MOV AL,1` / `XOR AL,AL`), and the body is
// otherwise instruction-for-instruction identical at 73.3%.
bool CacheKey_00600670::operator==(const CacheKey_00600670& other) const
{
    if (other.Height == Height && other.Width == Width)
        return true;

    return false;
}
