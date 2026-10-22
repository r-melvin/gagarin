// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Everything below was read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x673E80:
//     * `MOV EAX,[0x7F0CD8]` — the .data slot holding the "Powerups" section
//       name; `MOV ECX,[ESP+4]` — the single stack parameter used as the INI
//       `this` (the RulesClass `this` in ECX is never read).
//     * `MOV EDX,[EDI*4 + 0x7E523C]` — the key-name pointer table (first
//       entry 0x81DA20).
//     * `PUSH 0x83D4AC` — the ReadString default, the bytes "0,NONE".
//     * the four output arrays: `[EDI*4 + 0x81DA8C]` (int), `[EDI*4 +
//       0x81DAD8]` (int), `[EDI + 0x89ECC0]` (byte — unscaled base+index) and
//       the double array walked by `MOV EBP,0x89EC28` / `FSTP qword ptr
//       [EBP]` / `ADD EBP,8` / `CMP EBP,0x89ECC0`, i.e. 0x98/8 = 19 entries.
//     * `FMUL qword ptr [0x7E3808]` — the bytes 7B14AE47E17A843F = 0.01.
//   CRT/helper callees identified from their call shapes: 0x7C9CC2 strtok
//   (cdecl, ADD ESP,8), 0x7C9BFD atoi, 0x7CAF30 strchr('%'), 0x7C9D66 atof
//   (result in ST(0)), 0x7C8D20 _stricmp (already modelled the same way in
//   match/core/mission_class_methods.cpp), 0x727CF0 a __fastcall in-place
//   leading-whitespace trim (ECX = the string) and 0x422B20 a __fastcall
//   name->index lookup (ECX = the string). The section probe is the
//   CCINIClass::Exists call-site flag form already banked for 0x674550.
//   Names cross-checked against YRpp (RulesClass::Read_Powerups).
#ifndef GG_MATCH_CORE_RULES_CLASS_READ_POWERUPS_METHODS_H
#define GG_MATCH_CORE_RULES_CLASS_READ_POWERUPS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Opaque INI parser; members declared only, so cl emits reloc-normalised
// __thiscall CALLs.
class CCINI_00673E80
{
public:
    // FUNCTION: GAMEMD 0x526810 (decl; reloc)
    void* GetSection(const char* pSection);
    // FUNCTION: GAMEMD 0x526B10 (decl; reloc)
    void* GetEntry(const char* pSection, const char* pKey);
    // FUNCTION: GAMEMD 0x528A10 (decl; reloc)
    int   ReadString(const char* pSection, const char* pKey,
                     const char* pDefault, char* pBuffer, int size);
};

// FUNCTION: GAMEMD 0x727CF0 (decl; reloc) — in-place leading-whitespace trim.
char* __fastcall Strtrim_00727CF0(char* str);
// FUNCTION: GAMEMD 0x422B20 (decl; reloc) — name -> array index lookup.
int   __fastcall FUN_00422B20(char* name);

// CRT helpers (excluded from the match target; declared for the reloc).
// LIBRARY: GAMEMD 0x7C9CC2  strtok
char*  __cdecl P_strtok(char* str, const char* sep);
// LIBRARY: GAMEMD 0x7C9BFD  atoi
int    __cdecl P_atoi(const char* str);
// LIBRARY: GAMEMD 0x7C8D20  _stricmp
int    __cdecl P_stricmp(const char* a, const char* b);
// LIBRARY: GAMEMD 0x7CAF30  strchr
char*  __cdecl P_strchr(const char* str, int ch);
// LIBRARY: GAMEMD 0x7C9D66  atof
double __cdecl P_atof(const char* str);

// GLOBAL: GAMEMD 0x7F0CD8 — pointer to the "Powerups" section name.
extern char* PowerupsSection_007F0CD8;
// GLOBAL: GAMEMD 0x7E523C — the 19 powerup key names.
extern char* PowerupKeyNames_007E523C[19];
// GLOBAL: GAMEMD 0x81DA8C — per-powerup cash value.
extern int   PowerupMoney_0081DA8C[19];
// GLOBAL: GAMEMD 0x81DAD8 — per-powerup animation index.
extern int   PowerupAnim_0081DAD8[19];
// GLOBAL: GAMEMD 0x89EC28 — per-powerup probability weight.
extern double PowerupWeight_0089EC28[19];
// GLOBAL: GAMEMD 0x89ECC0 — per-powerup "one time only" flag (byte array).
extern char  PowerupFlag_0089ECC0[19];

struct Rules_00673E80
{
    // FUNCTION: GAMEMD 0x673E80 — RulesClass::Read_Powerups.
    bool Read_Powerups(CCINI_00673E80* pINI);
};

#endif  // GG_MATCH_CORE_RULES_CLASS_READ_POWERUPS_METHODS_H
