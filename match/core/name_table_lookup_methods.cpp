// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Linear name lookups over a fixed table of string pointers (CRT case-insensitive
// compare at 0x7C8D20): the index of the first entry equal to the name, with each
// owner's own table and miss value. The tables are named by retail address; the
// entry count is the distance to the loop end in the body. Each address is
// verified separately.

// LIBRARY: GAMEMD 0x7C8D20 -- CRT case-insensitive string compare (cdecl, two pointers).
extern "C" int __cdecl strcmpi(const char* a, const char* b);

extern const char* const DAT_00836EE0[5];
// FUNCTION: GAMEMD 0x00644850
int FUN_00644850(const char* name)
{
    for (int i = 0; i < 5; ++i) {
        if (strcmpi(name, DAT_00836EE0[i]) == 0)
            return i;
    }
    return -1;
}

extern const char* const DAT_008370BC[5];
// FUNCTION: GAMEMD 0x006458D0
int FUN_006458D0(const char* name)
{
    for (int i = 0; i < 5; ++i) {
        if (strcmpi(name, DAT_008370BC[i]) == 0)
            return i;
    }
    return -1;
}

extern const char* const DAT_007F0248[12];
// FUNCTION: GAMEMD 0x00645B60
int FUN_00645B60(const char* name)
{
    for (int i = 0; i < 12; ++i) {
        if (strcmpi(name, DAT_007F0248[i]) == 0)
            return i;
    }
    return 0;
}

extern const char* const DAT_008449F8[3];
// FUNCTION: GAMEMD 0x00727190
int FUN_00727190(const char* name)
{
    for (int i = 0; i < 3; ++i) {
        if (strcmpi(name, DAT_008449F8[i]) == 0)
            return i;
    }
    return 0;
}
