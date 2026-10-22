// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// 0x5B3C00: a __cdecl two-pointer comparator (both arguments dereferenced as
// dwords; -1 / 0 / 1 result), the qsort shape. Name descriptive.

// FUNCTION: GAMEMD 0x5B3C00
int __cdecl FUN_005B3C00(const void* a, const void* b)
{
    int left = *(const int*)a;
    int right = *(const int*)b;
    if (left < right) {
        return -1;
    }
    return left > right;
}
