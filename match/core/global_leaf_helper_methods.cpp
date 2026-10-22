// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Leaf bodies that repeat at several addresses: the integer sort comparator
// (the same shape as IndexClass::Comparator, bound to other tables), release
// and replace of one global heap block, a 64 KiB global buffer clear, and
// three constant or global tests. Each address was verified separately.

#include <string.h>

// LIBRARY: GAMEMD 0x7C8B3D -- CRT free.
extern "C" void __cdecl gg_free(void*);

extern int DAT_00A9FABC;
extern void* DAT_00ABF3F4;
extern int DAT_00B2FF78[0x4000];
extern int DAT_00B1D5E0[0x4000];
extern void* DAT_00B77F54;
extern void* DAT_00B77F60;

// FUNCTION: GAMEMD 0x0041C610
int __cdecl FUN_0041C610(const void* a, const void* b)
{
    if (*(const int*)a == *(const int*)b)
        return 0;
    if (*(const int*)a < *(const int*)b)
        return -1;
    return 1;
}

// FUNCTION: GAMEMD 0x004D2ED0
int __cdecl FUN_004D2ED0(const void* a, const void* b)
{
    if (*(const int*)a == *(const int*)b)
        return 0;
    if (*(const int*)a < *(const int*)b)
        return -1;
    return 1;
}


// FUNCTION: GAMEMD 0x005C00B0
int FUN_005C00B0()
{
    return DAT_00ABF3F4 != 0;
}


// FUNCTION: GAMEMD 0x006CF320
int __cdecl FUN_006CF320(const void* a, const void* b)
{
    if (*(const int*)a == *(const int*)b)
        return 0;
    if (*(const int*)a < *(const int*)b)
        return -1;
    return 1;
}

// FUNCTION: GAMEMD 0x00710860
int __cdecl FUN_00710860(const void* a, const void* b)
{
    if (*(const int*)a == *(const int*)b)
        return 0;
    if (*(const int*)a < *(const int*)b)
        return -1;
    return 1;
}

// FUNCTION: GAMEMD 0x00754720
void FUN_00754720()
{
    memset(DAT_00B2FF78, 0, sizeof(DAT_00B2FF78));
}

// FUNCTION: GAMEMD 0x00754840
void FUN_00754840()
{
    memset(DAT_00B1D5E0, 0, sizeof(DAT_00B2FF78));
}

// FUNCTION: GAMEMD 0x007B00B0
void FUN_007B00B0()
{
    if (DAT_00B77F54 != 0) {
        gg_free(DAT_00B77F54);
        DAT_00B77F54 = 0;
    }
}

// FUNCTION: GAMEMD 0x007B00F0
void FUN_007B00F0()
{
    if (DAT_00B77F60 != 0) {
        gg_free(DAT_00B77F60);
        DAT_00B77F60 = 0;
    }
}

// FUNCTION: GAMEMD 0x007B0320
void FUN_007B0320(void* replacement)
{
    if (DAT_00B77F54 != 0)
        gg_free(DAT_00B77F54);
    DAT_00B77F54 = replacement;
}

// FUNCTION: GAMEMD 0x007B0350
void FUN_007B0350(void* replacement)
{
    if (DAT_00B77F60 != 0)
        gg_free(DAT_00B77F60);
    DAT_00B77F60 = replacement;
}
