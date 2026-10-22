// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Ten consecutive unnamed CCINIClass helpers read numerically off the
//   user's retail gamemd.exe v1.001 via the local Ghidra CLI. Conventions
//   taken off the call sites: 0x5283D0 (ReadDouble, the default pushed as
//   two dwords 0/0xBFF00000 and the result compared in place with
//   `FCOM qword ptr [0x7E4900]`), 0x528A10 (ReadString, five pushed
//   arguments section/key/default/buffer/size with `this` in ECX) and
//   0x528660 (WriteString, three pushed pointers with `this` in ECX) are
//   __thiscall members; the enum<->name helpers 0x473960/0x473980,
//   0x40DCB0/0x40DCE0, 0x45DD20/0x45DD50 and the parsers 0x6CEE60 and
//   0x753250 take their single argument in ECX with nothing pushed, so they
//   are __fastcall free functions. Literals: 0x7E4900 = -1.0 and
//   0x7E1710 = 256.0 (read with `ghidra memory read`), 0x889F64 = "".
//   Globals: 0xB054D4 holds a pointer to an array of object pointers whose
//   name string sits at `[obj+0x304]` (`MOV EDX,[0xB054D4];
//   MOV EAX,[EDX+EAX*4]; MOV EDX,[EAX+0x304]` at 0x474B24..0x474B2D), and
//   0xA8E334 holds a pointer to an array of object pointers whose inline ID
//   text starts at `[obj+0x24]` (`MOV EDX,[0xA8E334];
//   MOV EAX,[EDX+EAX*4]; ADD EAX,0x24` at 0x474F5C..0x474F65).
//   INI method names cross-checked against YRpp (consult-only;
//   NO LICENSE) — the ten functions themselves have no YRpp name and keep
//   their Ghidra placeholders.
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_SMALL_READERS_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_SMALL_READERS_METHODS_H

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x473960 (decl; reloc) — bounds-checked enum -> name.
const char* __fastcall FUN_00473960(unsigned int index);
// FUNCTION: GAMEMD 0x473980 (decl; reloc) — the matching name -> enum.
int __fastcall FUN_00473980(const char* name);
// FUNCTION: GAMEMD 0x40DCB0 (decl; reloc) — a second enum -> name table.
void* __fastcall FUN_0040DCB0(int key);
// FUNCTION: GAMEMD 0x40DCE0 (decl; reloc) — its name -> enum.
int __fastcall FUN_0040DCE0(const char* name);
// FUNCTION: GAMEMD 0x45DD20 (decl; reloc) — a third enum -> name table.
void* __fastcall FUN_0045DD20(int key);
// FUNCTION: GAMEMD 0x45DD50 (decl; reloc) — its name -> enum.
int __fastcall FUN_0045DD50(const char* name);
// FUNCTION: GAMEMD 0x6CEE60 (decl; reloc) — parse a name into an index.
int __fastcall FUN_006CEE60(const char* name);
// FUNCTION: GAMEMD 0x753250 (decl; reloc) — parse a name into an index.
int __fastcall FUN_00753250(const char* name);

// STRING: GAMEMD 0x889F64  ""
extern const char STR_00889F64[];

// The object the 0xB054D4 table points at; only its name is touched.
struct Obj_00474B20
{
    char        _pad000[0x304];   // +0x0000
    const char* Name;             // +0x0304
};
GG_STATIC_ASSERT(offsetof(Obj_00474B20, Name) == 0x304);

// GLOBAL: GAMEMD 0xB054D4 — pointer to the array of those objects.
extern Obj_00474B20** DAT_00B054D4;

// The object the 0xA8E334 table points at; its ID text is inline at +0x24.
struct Obj_00474F50
{
    char _pad000[0x24];   // +0x0000
    char ID[0x18];        // +0x0024
};
GG_STATIC_ASSERT(offsetof(Obj_00474F50, ID) == 0x24);

// GLOBAL: GAMEMD 0xA8E334 — pointer to the array of those objects.
extern Obj_00474F50** DAT_00A8E334;

class CCINI_00474620
{
public:
    // FUNCTION: GAMEMD 0x5283D0 (decl; reloc) — INIClass::ReadDouble.
    double ReadDouble(const char* section, const char* key, double defaultValue);
    // FUNCTION: GAMEMD 0x528A10 (decl; reloc) — INIClass::ReadString.
    int    ReadString(const char* section, const char* key, const char* defaultValue,
                      char* buffer, unsigned int size);
    // FUNCTION: GAMEMD 0x528660 (decl; reloc) — INIClass::WriteString.
    bool   WriteString(const char* section, const char* key, const char* value);

    // FUNCTION: GAMEMD 0x474620
    int  FUN_00474620(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x4749E0
    int  FUN_004749E0(const char* section, const char* key, unsigned int defaultValue);
    // FUNCTION: GAMEMD 0x474A20
    bool FUN_00474A20(const char* section, const char* key, unsigned int value);
    // FUNCTION: GAMEMD 0x474B20
    bool FUN_00474B20(const char* section, const char* key, int index);
    // FUNCTION: GAMEMD 0x474F50
    int  FUN_00474F50(const char* section, const char* key, int index);
    // FUNCTION: GAMEMD 0x474FA0
    int  FUN_00474FA0(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x474FF0
    int  FUN_00474FF0(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x475030
    bool FUN_00475030(const char* section, const char* key, int value);
    // FUNCTION: GAMEMD 0x475060
    int  FUN_00475060(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x4750A0
    bool FUN_004750A0(const char* section, const char* key, int value);
};

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_SMALL_READERS_METHODS_H
