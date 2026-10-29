// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Leaf bodies that repeat at several addresses: the integer sort comparator
// (the same shape as IndexClass::Comparator, bound to other tables), release
// and replace of one global heap block, a 64 KiB global buffer clear, and
// three constant or global tests. Each address was verified separately.

#include <string.h>

// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).

// LIBRARY: GAMEMD 0x7C8B3D -- CRT free.
extern "C" void __cdecl gg_free(void*);

// An owned heap block: null at start-up, freed (and cleared) at exit.
struct OwnedBlock {
    void* ptr;
    OwnedBlock() : ptr(0) {}
    ~OwnedBlock()
    {
        if (ptr != 0) {
            gg_free(ptr);
            ptr = 0;
        }
    }
};

extern int DAT_00A9FABC;
extern void* DAT_00ABF3F4;
extern int DAT_00B2FF78[0x4000];
extern int DAT_00B1D5E0[0x4000];

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

// SYNTHETIC: GAMEMD 0x007B0090 -- initialiser of DAT_00B77F54, registers the exit stub
// SYNTHETIC: GAMEMD 0x007B00B0 -- exit stub of DAT_00B77F54 (destructor)
// GLOBAL: GAMEMD 0xB77F54
OwnedBlock DAT_00B77F54;

// SYNTHETIC: GAMEMD 0x007B00D0 -- initialiser of DAT_00B77F60, registers the exit stub
// SYNTHETIC: GAMEMD 0x007B00F0 -- exit stub of DAT_00B77F60 (destructor)
// GLOBAL: GAMEMD 0xB77F60
OwnedBlock DAT_00B77F60;

// FUNCTION: GAMEMD 0x007B0320
void FUN_007B0320(void* replacement)
{
    if (DAT_00B77F54.ptr != 0)
        gg_free(DAT_00B77F54.ptr);
    DAT_00B77F54.ptr = replacement;
}

// FUNCTION: GAMEMD 0x007B0350
void FUN_007B0350(void* replacement)
{
    if (DAT_00B77F60.ptr != 0)
        gg_free(DAT_00B77F60.ptr);
    DAT_00B77F60.ptr = replacement;
}
