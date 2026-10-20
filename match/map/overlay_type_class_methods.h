// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference | YRpp-cross-check |
//             private-ref-cross-check
//   Every offset, global and calling convention below was read numerically off
//   the user's retail gamemd.exe v1.001 through the local Ghidra CLI at
//   0x5FE470 / 0x5FE530 / 0x5FE570.
//
//   Class identity came from RTTI rather than from a name guess: the three
//   vtables seated by the constructor at 0x5FC380 (0x7EF3D4, 0x7EF3CC,
//   0x7EF3B0, 0x7EF3A8) each carry a complete-object-locator dword four bytes
//   below them; the locator's +0xC type descriptor's name string (eight bytes
//   into the descriptor) reads ".?AVOverlayClass@@" for all four. So 0x5FC380
//   is OverlayClass::OverlayClass and the three functions here are the
//   OverlayTypeClass factory trio that builds one.
//
//   RA1's OVERLAY.CPP has the same trio (`From_Name`, `Create_And_Place`,
//   `Create_One_Of`) — consulted for shape only, never transcribed; RA2 adds a
//   third constructor argument and passes the cell by reference.
//
//   Disasm-derived facts:
//     * 0x5FE470 takes its only argument in ECX with no stack cleanup, so it is
//       a static __fastcall. It walks [0xA83D90] entries of [0xA83D84] and
//       compares `_stricmp(item + 0x24, pID)`; +0x24 is AbstractTypeClass::ID
//       (the `ADD ECX,0x24` on the element pointer, an array member, not a
//       pointer load). Items 0xA83D84 and Count 0xA83D90 are +0x04 and +0x10 of
//       one DynamicVectorClass, so OverlayTypeClass::Array sits at 0xA83D80
//       (agrees with YRpp's ABSTRACTTYPE_ARRAY constant).
//     * 0x5FE530 is `RET 8` with `MOV ESI,ECX`: __thiscall, two stack
//       arguments, only the first used. It allocates 0xB0 bytes through
//       operator new (0x7C8E17) and constructs an OverlayClass with
//       (this, firstArg, -1).
//     * 0x5FE570 is `RET 4` with the same allocation and constructor, passing
//       the zero-initialised global CellStruct at 0xAC1608 instead; its second
//       argument is unused. It returns the constructed pointer.
//     * sizeof(OverlayClass) == 0xB0 — the `PUSH 0xB0` ahead of operator new.
//
//   0x5FE620 (LoadArt) joins them because it is the same class and the next
//   address in the run, and because it needs a sibling in its translation unit:
//   compiled alone, cl cross-jumps its two identical load-and-retry blocks into
//   one and the function caps at 55.2%; with any second function present in the
//   TU the merge does not happen and it is byte-exact. Its own disasm-derived
//   facts:
//     * The theater index arrives in ECX (`MOV EDI,ECX`) and is scaled by 0x70
//       (`LEA ECX,[EDI*8]; SUB ECX,EDI; SHL ECX,4`) onto 0x7E1BC6, so the
//       theater table base is 0x7E1B78 with Extension at +0x4E — the same
//       record the matched SmudgeTypeClass loader at 0x6B5490 pins, re-derived
//       here so this TU stands alone.
//     * Type offsets, each from an explicit displacement: Image +0xA4,
//       ImageAllocated +0xA8, ImageFile +0x1F8 (the `LEA EDX,[ESI+0x1F8]`
//       handed to _makepath as the file name), Theater +0x22C, NewTheater
//       +0x237, and the skip flag at +0x2AF — YRpp's `ImageLoaded` slot,
//       counted from the Tiberium byte at +0x2A9 that the matched 0x5FDD20 TU
//       pins numerically.
//     * 0x5B40B0 takes the path in ECX and a byte flag in DL and returns the
//       loaded image; 0x5F96B0 is `__fastcall(char*, int)` and rewrites
//       name[1] with the theater letter; 0x5F9710 is `MOV [ECX+1],0x47; RET`,
//       which resets that letter to the generic 'G'. That pair is why a failed
//       load is retried exactly once.
//     * The path buffer is 0x200 bytes: `SUB ESP,0x200` with the buffer at
//       ESP+0x10 behind four callee-saved pushes.
#ifndef GG_MATCH_MAP_OVERLAY_TYPE_CLASS_METHODS_H
#define GG_MATCH_MAP_OVERLAY_TYPE_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector_class.h"

// CRT case-insensitive compare at 0x7C8D20 (__cdecl; `ADD ESP,8` after the
// call). Statically-linked CRT is outside the match target, so it is declared
// and called, never reimplemented.
extern "C" int __cdecl gg_overlay_stricmp(const char* a, const char* b);

// VC6's global operator new (retail 0x7C8E17). Declared so `new` lowers to the
// retail `PUSH size; CALL; ADD ESP,4` sequence.
void* __cdecl operator new(unsigned int cb);

// LIBRARY: GAMEMD 0x7C8B3D — game-heap free (__cdecl, one pointer).
void __cdecl operator delete(void* p);

// FUNCTION: GAMEMD 0x7C9FF0 (decl; reloc) — CRT _makepath, __cdecl.
extern "C" void __cdecl _makepath(char* path, const char* drive, const char* dir,
                                  const char* fname, const char* ext);

struct Image_005FE620;

// FUNCTION: GAMEMD 0x5B40B0 (decl; reloc) — load an image by file name.
Image_005FE620* __fastcall FUN_005B40B0(const char* name, unsigned char flag);
// FUNCTION: GAMEMD 0x5F96B0 (decl; reloc) — stamp the theater letter into
// name[1]; a theater index of -1 leaves the name alone.
void __fastcall FUN_005F96B0(char* name, int idxTheater);
// FUNCTION: GAMEMD 0x5F9710 (decl; reloc) — reset name[1] to the generic 'G'.
void __fastcall FUN_005F9710(char* name);

// STRING: GAMEMD 0x81834C ".SHP"
extern const char STR_0081834C[];

// Theater — one 0x70-byte record of the per-theater table; only Extension is
// read here.
struct Theater_005FE620
{
    char ID[0x10];               // +0x00
    char UIName[0x20];           // +0x10
    char ControlFileName[0xA];   // +0x30
    char ArtFileName[0xA];       // +0x3A
    char PaletteFileName[0xA];   // +0x44
    char Extension[0x4];         // +0x4E
    char _pad52[0x70 - 0x52];
};
GG_STATIC_ASSERT(offsetof(Theater_005FE620, Extension) == 0x4E);
GG_STATIC_ASSERT(sizeof(Theater_005FE620) == 0x70);

// GLOBAL: GAMEMD 0x7E1B78 — the theater table (entry 0's Extension is 0x7E1BC6).
extern Theater_005FE620 DAT_007E1B78[];

class HouseClass;
class ObjectClass;

// The map cell coordinate pair handed to the OverlayClass constructor by
// reference (retail pushes its address).
struct CellStruct_005FE530
{
    short X;   // +0x00
    short Y;   // +0x02
};
GG_STATIC_ASSERT(offsetof(CellStruct_005FE530, Y) == 0x02);
GG_STATIC_ASSERT(sizeof(CellStruct_005FE530) == 0x04);

class OverlayTypeClass;

// OverlayClass — 0xB0 bytes (the operator-new size at both call sites). Only
// the constructor is referenced here; its body is matched elsewhere.
class OverlayClass
{
public:
    // FUNCTION: GAMEMD 0x5FC380 (decl; reloc) — __thiscall, returns `this`.
    OverlayClass(OverlayTypeClass* pType, const CellStruct_005FE530& mapCoord,
                 int nFlag) throw();

private:
    char _storage[0xB0];
};
GG_STATIC_ASSERT(sizeof(OverlayClass) == 0xB0);

// OverlayTypeClass — only AbstractTypeClass::ID at +0x24 is read here.
class OverlayTypeClass
{
public:
    // FUNCTION: GAMEMD 0x5FE470 — the name arrives in ECX, so __fastcall.
    static int __fastcall FindIndex(const char* pID);

    // FUNCTION: GAMEMD 0x5FE530 — vtable slot; `RET 8`.
    bool SpawnAtMapCoords(CellStruct_005FE530* pMapCoords, HouseClass* pOwner);

    // FUNCTION: GAMEMD 0x5FE570 — vtable slot; `RET 4`.
    ObjectClass* CreateObject(HouseClass* pOwner);

    // FUNCTION: GAMEMD 0x5FE620 — the theater index arrives in ECX.
    static void __fastcall LoadArt(int idxTheater);

    char             _pad000[0x24];        // +0x0000
    char             ID[0x18];             // +0x0024  AbstractTypeClass::ID
    char             _pad03C[0xA4 - 0x3C];
    Image_005FE620*  Image;                // +0x00A4
    unsigned char    ImageAllocated;       // +0x00A8
    char             _pad0A9[0x1F8 - 0xA9];
    char             ImageFile[0x19];      // +0x01F8
    char             _pad211[0x22C - 0x211];
    unsigned char    Theater;              // +0x022C
    char             _pad22D[0x237 - 0x22D];
    unsigned char    NewTheater;           // +0x0237
    char             _pad238[0x2AF - 0x238];
    unsigned char    ImageLoaded;          // +0x02AF  set => art comes from elsewhere
};
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, ID)             == 0x24);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, Image)          == 0xA4);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, ImageAllocated) == 0xA8);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, ImageFile)      == 0x1F8);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, Theater)        == 0x22C);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, NewTheater)     == 0x237);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, ImageLoaded)    == 0x2AF);

// GLOBAL: GAMEMD 0xA83D80 — OverlayTypeClass::Array (Items +0x04 = 0xA83D84,
// Count +0x10 = 0xA83D90).
extern DynamicVectorClass OverlayTypeClass_Array;

// GLOBAL: GAMEMD 0xAC1608 — the zero-initialised CellStruct handed to
// CreateObject's OverlayClass.
extern CellStruct_005FE530 DAT_00AC1608;

// GLOBAL: GAMEMD 0xA83D84 — OverlayTypeClass::Array.Items, addressed directly
// by LoadArt (the same +0x04 of the vector above).
extern OverlayTypeClass** DAT_00A83D84;
// GLOBAL: GAMEMD 0xA83D90 — OverlayTypeClass::Array.Count.
extern int DAT_00A83D90;

#endif  // GG_MATCH_MAP_OVERLAY_TYPE_CLASS_METHODS_H
