// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and offsets read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x452410. Two callee bindings come from YRpp
//   (consult-only, no LICENSE) and are reconfirmed against the disassembly:
//   0x554A60 = LightSourceClass::Activate (so the pointer at +0x614 is a light
//   source) and 0x4533A0 = BuildingClass::CreateEndPost.
#ifndef GG_MATCH_ECONOMY_BUILDING_CLASS_ENABLE_METHODS_H
#define GG_MATCH_ECONOMY_BUILDING_CLASS_ENABLE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The per-animation record in BuildingTypeClass. Size is fixed by the retail
// loop stride (`ADD ESI,0x44`); the array base is fixed by reading EnableStuff
// and ToggleDamagedAnims together — the former indexes `+0xF8C`, the latter
// `+0xF4C` and `+0xF5C`, all with the same stride, so the array starts at
// **0xF4C** and those are record offsets +0x40, +0x00 and +0x10.
//
// (Until 2026-08-07 this header asserted the base at 0xF8C with the flag at
// record+0x00. The generated address arithmetic is identical either way, which
// is why EnableStuff still matched 100% and the error stayed hidden.)
struct BuildingAnimRecord
{
    char NameNormal[0x10];    // +0x00  read by ToggleDamagedAnims, undamaged
    char NameDamaged[0x10];   // +0x10  read by ToggleDamagedAnims, damaged
    char _pad20[0x40 - 0x20]; // +0x20
    bool unknown_40;          // +0x40  read by EnableStuff
    char _pad41[3];           // +0x41
};
GG_STATIC_ASSERT(offsetof(BuildingAnimRecord, NameDamaged) == 0x10);
GG_STATIC_ASSERT(offsetof(BuildingAnimRecord, unknown_40)  == 0x40);
GG_STATIC_ASSERT(sizeof(BuildingAnimRecord) == 0x44);

// The loop runs while the byte index is below 0x594; at 0x44 per record that is
// 21 animations.
#define BUILDING_ANIM_COUNT 21

struct BuildingTypeClass
{
    char               _pad0000[0xF4C];                  // +0x0000
    BuildingAnimRecord Anims[BUILDING_ANIM_COUNT];       // +0x0F4C
    char               _pad14E0[0x16BE - (0xF4C + BUILDING_ANIM_COUNT * 0x44)];
    bool               unknown_16BE;                     // +0x16BE  gates CreateEndPost
};
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, Anims)        == 0xF4C);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, unknown_16BE) == 0x16BE);

struct AnimClass;
struct LightSourceClass
{
    void Activate(unsigned long zero);   // GAMEMD 0x554A60 __thiscall (declared; reloc)
};

// Per-animation enable helper at 0x425270 — __fastcall with the anim in ECX.
// Descriptive name; the address carries no confirmed Westwood one.
void __fastcall AnimClass_Enable(AnimClass* anim);

struct BuildingClass
{
    char               _pad0000[0x520];                  // +0x0000
    BuildingTypeClass* Type;                             // +0x0520
    char               _pad0524[0x55C - 0x524];          // +0x0524
    AnimClass*         Anims[BUILDING_ANIM_COUNT];       // +0x055C
    char               _pad05B0[0x614 - (0x55C + BUILDING_ANIM_COUNT * 4)];
    LightSourceClass*  LightSource;                      // +0x0614
    char               _pad0618[0x6E6 - 0x618];          // +0x0618
    bool               IsDamagedAnims;                   // +0x06E6  current anim set
    char               _pad06E7[0x6EA - 0x6E7];          // +0x06E7
    bool               unknown_6EA;                      // +0x06EA  raised on enable

    void EnableStuff();                                  // GAMEMD 0x452410 (matched)
    void ToggleDamagedAnims(bool damaged);               // GAMEMD 0x451EE0 (matched)
    void CreateEndPost(bool arg);                        // GAMEMD 0x4533A0 (declared; reloc)
    // The five-argument per-animation worker; declared only (reloc-normalised).
    void PlayAnim(const char* name, int index, bool damaged, int a4, int a5);  // GAMEMD 0x451890
};
GG_STATIC_ASSERT(offsetof(BuildingClass, Type)        == 0x520);
GG_STATIC_ASSERT(offsetof(BuildingClass, Anims)       == 0x55C);
GG_STATIC_ASSERT(offsetof(BuildingClass, LightSource) == 0x614);
GG_STATIC_ASSERT(offsetof(BuildingClass, IsDamagedAnims) == 0x6E6);
GG_STATIC_ASSERT(offsetof(BuildingClass, unknown_6EA) == 0x6EA);

#endif  // GG_MATCH_ECONOMY_BUILDING_CLASS_ENABLE_METHODS_H
