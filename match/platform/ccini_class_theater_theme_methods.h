// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   The tail of the CCINIClass enumerated-value reader/writer run, read
//   numerically off the user's retail gamemd.exe v1.001 with the local
//   Ghidra CLI (`disasm` / `memory read`). Every address here sits in the
//   contiguous 0x474810..0x475A3D block whose already-matched members live
//   in ccini_class_small_readers_methods.cpp, so the INI plumbing
//   (ReadString 0x528A10, WriteString 0x528660, "" at 0x889F64) is taken
//   from that file's confirmed conventions rather than re-derived.
//
//   Table identities were confirmed by reading the tables themselves, not
//   taken from the seed: 0x7E1B60 holds char* "North"/"East"/"South"/"Air"
//   (the map-edge names) and 0x7E1B78 is a 0x70-stride record array whose
//   first field is the inline name "TEMPERATE" (the theaters). The theme
//   object at 0x00A83D10 is reached as a receiver in ECX by both 0x720940
//   and 0x721210, so it is a real object, not a table.
//
//   The private-reference seed (consult-only, no LICENSE) named this cluster
//   readTheater/writeTheaterByIndex/readTheme/writeThemeByIndex/readEdge/
//   writeEdgeByIndex/readPowerup; its names are shifted by one across the
//   family, so only the three confirmed from table contents are used and
//   the rest keep Ghidra placeholders.
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_THEATER_THEME_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_THEATER_THEME_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// STRING: GAMEMD 0x889F64  ""
extern const char STR_00889F64[];
// STRING: GAMEMD 0x817474  "<none>"
extern const char STR_00817474[];

// Name -> index parsers. Each takes its single argument in ECX with nothing
// pushed and no stack cleanup at the call site, so each is __fastcall.
// FUNCTION: GAMEMD 0x6A46D0 (decl; reloc) — movie name -> index, -1 if absent.
int __fastcall FUN_006A46D0(const char* name);
// FUNCTION: GAMEMD 0x48DF30 (decl; reloc)
int __fastcall FUN_0048DF30(const char* name);
// FUNCTION: GAMEMD 0x48DBE0 (decl; reloc)
int __fastcall FUN_0048DBE0(const char* name);
// FUNCTION: GAMEMD 0x48DB80 (decl; reloc)
int __fastcall FUN_0048DB80(const char* name);
// FUNCTION: GAMEMD 0x48DE70 (decl; reloc)
int __fastcall FUN_0048DE70(const char* name);

// The movie record the 0x4756F0 reader allocates when the name is new:
// `PUSH 0xB4; CALL 0x7C8E17` is operator new of 0xB4 bytes, and the
// constructor takes the name in the pushed slot with `this` in ECX.
class MovieType_006A4550
{
public:
    // The record is 0xB4 bytes wide: that is the constant the reader hands
    // to operator new at 0x475729. Nothing else about it is touched here.
    char _pad000[0xB4];     // +0x0000

    // FUNCTION: GAMEMD 0x6A4550 (decl; reloc) — the name constructor.
    //
    // The no-throw specification is load-bearing under the locked /GX: a
    // new-expression whose constructor may throw gets an unwind funclet that
    // frees the block, which retail has no trace of.
    MovieType_006A4550(const char* name) throw();
};
GG_STATIC_ASSERT(sizeof(MovieType_006A4550) == 0xB4);

// The movie-type registry. Retail reads the count from 0x8B4130 and the item
// array from 0x8B4124, twelve bytes apart, which is the tree's usual
// VectorClass(vtable, Items, Capacity) + DynamicVectorClass(Count) header
// laid out from 0x8B4120.
struct MovieTypeVector
{
    void*                   _vtable;    // +0x0000
    MovieType_006A4550**    Items;      // +0x0004
    int                     Capacity;   // +0x0008
    int                     Count;      // +0x000C
};
GG_STATIC_ASSERT(offsetof(MovieTypeVector, Items) == 0x04 &&
                 offsetof(MovieTypeVector, Count) == 0x0C &&
                 sizeof(MovieTypeVector) == 0x10);

// GLOBAL: GAMEMD 0x8B4120 — the movie-type registry (Items 0x8B4124,
// Count 0x8B4130).
extern MovieTypeVector DAT_008B4120;

// The 0x00ABF394 name table and its count one dword-triple later.
// GLOBAL: GAMEMD 0xABF394 — pointer to an array of name pointers.
extern const char** DAT_00ABF394;
// GLOBAL: GAMEMD 0xABF3A0 — how many entries that array holds.
extern unsigned int DAT_00ABF3A0;

// One theater record. `LEA EDX,[EAX*8]; SUB EDX,EAX; SHL EDX,4` is a stride
// of 0x70, and the name is the record's own first field (inline, not a
// pointer): 0x7E1B78 reads "TEMPERATE" with "Name:Temperate" at +0x10.
struct TheaterData
{
    char Name[0x10];        // +0x0000
    char _pad010[0x60];     // +0x0010
};
GG_STATIC_ASSERT(offsetof(TheaterData, Name) == 0x00 &&
                 sizeof(TheaterData) == 0x70);

// GLOBAL: GAMEMD 0x7E1B78 — the theater record array.
extern TheaterData DAT_007E1B78[];

// GLOBAL: GAMEMD 0x7E1B60 — the map-edge name table ("North", "East", ...).
extern const char* DAT_007E1B60[];

// The theme player. Only its two name/index entry points are modelled.
class ThemeClass_00A83D10
{
public:
    // FUNCTION: GAMEMD 0x720940 (decl; reloc) — index -> theme name.
    const char* GetName(int index);
    // FUNCTION: GAMEMD 0x721210 (decl; reloc) — theme name -> index.
    int         FindName(const char* name);
};

// GLOBAL: GAMEMD 0xA83D10 — the theme player instance.
extern ThemeClass_00A83D10 DAT_00A83D10;

class CCINI_004756F0
{
public:
    // FUNCTION: GAMEMD 0x528A10 (decl; reloc) — INIClass::ReadString.
    int  ReadString(const char* section, const char* key, const char* defaultValue,
                    char* buffer, unsigned int size);
    // FUNCTION: GAMEMD 0x528660 (decl; reloc) — INIClass::WriteString.
    bool WriteString(const char* section, const char* key, const char* value);

    // FUNCTION: GAMEMD 0x4756F0
    int  ReadMovie(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x4757D0
    int  FUN_004757D0(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x475820
    bool FUN_00475820(const char* section, const char* key, unsigned int index);
    // FUNCTION: GAMEMD 0x475870
    int  FUN_00475870(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x4758C0
    bool WriteTheater(const char* section, const char* key, int index);
    // FUNCTION: GAMEMD 0x4758F0
    int  ReadTheme(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x475950
    bool WriteTheme(const char* section, const char* key, int index);
    // FUNCTION: GAMEMD 0x475980
    int  FUN_00475980(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x4759D0
    bool WriteEdge(const char* section, const char* key, int index);
    // FUNCTION: GAMEMD 0x4759F0
    int  FUN_004759F0(const char* section, const char* key, int defaultValue);
};

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_THEATER_THEME_METHODS_H
