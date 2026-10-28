// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//   Small free helpers: name-table lookups and global clears.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x48C630  FUN_0048C630
//   FUNCTION: GAMEMD 0x48E030  FUN_0048E030
//   FUNCTION: GAMEMD 0x4E62B0  FUN_004E62B0

// GLOBAL: GAMEMD 0x81D27C -- three name strings.
extern const char* DAT_0081D27C[3];
// GLOBAL: GAMEMD 0x81DA58 -- eight name strings.
extern const char* DAT_0081DA58[8];
// GLOBAL: GAMEMD 0x822C54 -- nine name strings.
extern const char* DAT_00822C54[9];
// GLOBAL: GAMEMD 0x822CE8 -- the fallback name ("Unknown").
extern char DAT_00822CE8[];
// GLOBAL: GAMEMD 0x817474 -- the fallback name ("<none>").
extern char DAT_00817474[];

// Declaration: GAMEMD 0x4E6190 -- the current index.
int __cdecl FUN_004E6190();

// FUNCTION: GAMEMD 0x48C630
// Name for a 0..2 index, null outside it.
const char* __fastcall FUN_0048C630(int index)
{
    if (index < 0 || index >= 3) {
        return 0;
    }
    return DAT_0081D27C[index];
}

// FUNCTION: GAMEMD 0x48E030
// Name for a 0..7 index, "<none>" outside it.
const char* __fastcall FUN_0048E030(unsigned int index)
{
    if (index < 8) {
        return DAT_0081DA58[index];
    }
    return DAT_00817474;
}

// FUNCTION: GAMEMD 0x4E62B0
// Name for the current index, "Unknown" outside 0..8.
const char* __cdecl FUN_004E62B0()
{
    int index = FUN_004E6190();
    if (index > -1 && index < 9) {
        return DAT_00822C54[index];
    }
    return DAT_00822CE8;
}
