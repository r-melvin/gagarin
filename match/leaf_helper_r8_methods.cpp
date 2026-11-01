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

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x81D288
extern const char STR_0081D288[] = "ACK";
// GLOBAL: GAMEMD 0x81D28C
extern const char STR_0081D28C[] = "NDATA";
// GLOBAL: GAMEMD 0x81D294
extern const char STR_0081D294[] = "ADATA";
// GLOBAL: GAMEMD 0x822C78
extern const char STR_00822C78[] = "Cyrix";
// GLOBAL: GAMEMD 0x822C80
extern const char STR_00822C80[] = "AMD";
// GLOBAL: GAMEMD 0x822C84
extern const char STR_00822C84[] = "Pentium 4";
// GLOBAL: GAMEMD 0x822C90
extern const char STR_00822C90[] = "Celeron";
// GLOBAL: GAMEMD 0x822C98
extern const char STR_00822C98[] = "Pentium III";
// GLOBAL: GAMEMD 0x822CA4
extern const char STR_00822CA4[] = "Pentium II";
// GLOBAL: GAMEMD 0x822CB0
extern const char STR_00822CB0[] = "Pentium Pro";
// GLOBAL: GAMEMD 0x822CBC
extern const char STR_00822CBC[] = "Pentium";
// GLOBAL: GAMEMD 0x822CC4
extern const char STR_00822CC4[] = "486";
// GLOBAL: GAMEMD 0x81D27C
extern const char* DAT_0081D27C[3] = {STR_0081D294, STR_0081D28C, STR_0081D288};
// GLOBAL: GAMEMD 0x822C54
extern const char* DAT_00822C54[9] = {STR_00822CC4, STR_00822CBC, STR_00822CB0, STR_00822CA4, STR_00822C98, STR_00822C90, STR_00822C84, STR_00822C80, STR_00822C78};
// END defined globals
