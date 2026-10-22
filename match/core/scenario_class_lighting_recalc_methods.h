// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Offsets, globals and call shapes read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x53AD00: the __fastcall
//   entry (R in ECX, G in EDX, B and the tint flag on the stack, `RET 8`);
//   the LightConvert registry Items `[0x87F69C]` / Count `[0x87F6A8]` (the
//   vector object at 0x87F698 + 4 / + 0x10) walked with `[EAX+ESI*4]` and
//   `MOV EDX,[ECX]; CALL [EDX+4]` with the four values pushed; the colour
//   scheme registry Items `[0xB054D4]` / Count `[0xB054E0]` (the vector at
//   0xB054D0) whose elements are tested `CMP [EAX+0x310],1` and then
//   dereferenced `[EAX+0x30C]` for the same slot-1 call; a 12-byte iterator
//   local (two dwords and a byte, zeroed) handed in ECX to 0x626690, which
//   returns a vector whose Items sit at +4 and whose count comes from the
//   argument-less 0x626C60; and the tail `MOV ECX,0x87F7E8; CALL 0x4AE4C0`
//   then `PUSH 1; CALL 0x4F42F0`. YRpp names only: ScenarioClass::RecalcLighting, LightConvertClass::Array
//   @0x87F698, ColorScheme::Array @0xB054D0, ColorScheme::LightConvert
//   @+0x30C, ColorScheme::GetPaletteSchemesFromIterator @0x626690,
//   ColorScheme::GetNumberOfSchemes @0x626C60, ScenarioClass::
//   UpdateCellLighting @0x4AE4C0. 0x4F42F0 is GScreenClass::FlagToRedraw,
//   slot 14 of GScreenClass's vtable 0x7EA6FC.
#ifndef GG_MATCH_CORE_SCENARIO_CLASS_LIGHTING_RECALC_METHODS_H
#define GG_MATCH_CORE_SCENARIO_CLASS_LIGHTING_RECALC_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// LightConvertClass — only vtable slot 1 (a four-argument __thiscall) is
// used. Declaration order per match/_rt/gg_vslot.h.
struct LightConvertVtbl_0053AD00;
struct LightConvert_0053AD00
{
    LightConvertVtbl_0053AD00* Vtbl;   // +0x0000
};
typedef void (LightConvert_0053AD00::*FnLC04_0053AD00)(int r, int g, int b, bool tint);
struct LightConvertVtbl_0053AD00
{
    char             _pad00[0x4];   // +0x0000
    FnLC04_0053AD00  At_04;         // +0x0004
};
GG_STATIC_ASSERT(offsetof(LightConvertVtbl_0053AD00, At_04) == 0x4);

// DynamicVectorClass<LightConvertClass*> view: Items @+4, Count @+0x10.
struct LightConvertVec_0053AD00
{
    void*                    _vtable;    // +0x0000
    LightConvert_0053AD00**  Items;      // +0x0004
    int                      Capacity;   // +0x0008
    int                      IsAllocated;// +0x000C
    int                      Count;      // +0x0010
};
GG_STATIC_ASSERT(offsetof(LightConvertVec_0053AD00, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(LightConvertVec_0053AD00, Count) == 0x10);
// GLOBAL: GAMEMD 0x87F698 — LightConvertClass::Array.
extern LightConvertVec_0053AD00 DAT_0087F698;

// ColorScheme view: the LightConvert pointer at +0x30C and the word after it.
struct ColorScheme_0053AD00
{
    char                    _pad000[0x30C];   // +0x0000
    LightConvert_0053AD00*  LightConvert;     // +0x030C
    int                     At_310;           // +0x0310
};
GG_STATIC_ASSERT(offsetof(ColorScheme_0053AD00, LightConvert) == 0x30C);
GG_STATIC_ASSERT(offsetof(ColorScheme_0053AD00, At_310)       == 0x310);

// DynamicVectorClass<ColorScheme*> view: Items @+4, Count @+0x10.
struct ColorSchemeVec_0053AD00
{
    void*                   _vtable;    // +0x0000
    ColorScheme_0053AD00**  Items;      // +0x0004
    int                     Capacity;   // +0x0008
    int                     IsAllocated;// +0x000C
    int                     Count;      // +0x0010
};
GG_STATIC_ASSERT(offsetof(ColorSchemeVec_0053AD00, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(ColorSchemeVec_0053AD00, Count) == 0x10);
// GLOBAL: GAMEMD 0xB054D0 — ColorScheme::Array.
extern ColorSchemeVec_0053AD00 DAT_00B054D0;

// The 12-byte hash-table iterator the palette walk hands to 0x626690.
struct HashIterator_0053AD00
{
    int  At_00;   // +0x0000
    int  At_04;   // +0x0004
    char At_08;   // +0x0008
};
GG_STATIC_ASSERT(offsetof(HashIterator_0053AD00, At_04) == 0x4);
GG_STATIC_ASSERT(offsetof(HashIterator_0053AD00, At_08) == 0x8);
GG_STATIC_ASSERT(sizeof(HashIterator_0053AD00) == 0xC);

// FUNCTION: GAMEMD 0x626690 (decl; reloc) — __fastcall, iterator in ECX;
// returns the next per-palette scheme vector or null.
ColorSchemeVec_0053AD00* FUN_00626690(HashIterator_0053AD00* it);
// FUNCTION: GAMEMD 0x626C60 (decl; reloc) — number of schemes per palette.
int __cdecl FUN_00626C60();

// The map singleton is a static object at 0x87F7E8.
struct Map_0053AD00
{
    // FUNCTION: GAMEMD 0x4AE4C0 (decl; reloc) — the cell lighting sweep.
    void FUN_004AE4C0();
    // FUNCTION: GAMEMD 0x4F42F0 (decl; reloc) — GScreenClass::FlagToRedraw.
    void FlagToRedraw(int mode);
};
// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance.
extern Map_0053AD00 MapInstance;

struct ScenarioClass
{
    // FUNCTION: GAMEMD 0x53AD00
    // The tint flag is a bool: as an int it takes the callee-saved register
    // that retail gives to `b` and the frame slot reuse flips with it.
    static void RecalcLighting(int r, int g, int b, bool tint);
};

#endif  // GG_MATCH_CORE_SCENARIO_CLASS_LIGHTING_RECALC_METHODS_H
