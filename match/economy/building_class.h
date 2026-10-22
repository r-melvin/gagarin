// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x451E40, 0x4521C0, 0x452210,
//   0x4525F0, 0x457630, 0x457690), cross-checked against YRpp
//   (every offset
//   reconfirmed numerically against the user's binary below).
//
// BuildingClass — a placed structure. This TU models only the members the six
// matched methods touch (the full TechnoClass-derived layout is P2):
//   +0x21C Owner (HouseClass*), +0x350 a sub-object (IsTraversable helper),
//   +0x520 Type (BuildingTypeClass*), +0x55C Anims[0x15] (AnimClass*),
//   +0x660 the temporal-targeting flag byte.
#ifndef GG_MATCH_ECONOMY_BUILDING_CLASS_H
#define GG_MATCH_ECONOMY_BUILDING_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// HouseClass — only the super-weapon-slots sub-object at +0x5550 is modelled
// (First/SecondActiveSWIdx call `lea ecx,[Owner+0x5550]; call 0x49FAE0(arg)`).
struct SWSlotsClass
{
    int IsActive_49FAE0(int swType);     // GAMEMD 0x49FAE0 __thiscall (declared; reloc)
};
class HouseClass
{
public:
    char         _pad_0000[0x5550];      // +0x0000  (full layout is P2)
    SWSlotsClass SWSlots;                // +0x5550
};
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(HouseClass, SWSlots) == 0x5550);
#endif

// ---------------------------------------------------------------------------
// AnimClass — only the members the temporal/destroy paths touch are modelled.
//   +0x00  vtable. DestroyNthAnim issues an indirect __thiscall through vtable
//          slot 8 (offset 0x20) passing a flag of 1 (`mov [vtbl]; push 1;
//          call [vtbl+0x20]`). The slot-8 virtual is modelled below as
//          VtblSlot8(int) so VC6 emits exactly that indirect call (VC6 has no
//          usable explicit __thiscall keyword, so a real virtual is the only
//          way to reproduce the vtable call). The COM-base slot 8 nominally
//          holds What_Am_I, but the live call takes an arg, so we keep the name
//          neutral — the byte-level slot is what is being matched.
//   +0xAC  current animation frame value (saved into PausedAnimFrame).
//   +0x119 UnderTemporal (bool)   +0x11A Paused (bool)
//   +0x11B Unpaused (bool)        +0x11C PausedAnimFrame (int)
// ---------------------------------------------------------------------------
class AnimClass
{
public:
    // Slots 0..7 of the COM/IPersistStream + abstract base; modelled as pure
    // padding virtuals purely so VtblSlot8 lands at vtable offset 0x20.
    virtual void VtblSlot0() = 0; virtual void VtblSlot1() = 0;
    virtual void VtblSlot2() = 0; virtual void VtblSlot3() = 0;
    virtual void VtblSlot4() = 0; virtual void VtblSlot5() = 0;
    virtual void VtblSlot6() = 0; virtual void VtblSlot7() = 0;
    virtual void VtblSlot8(int flag) = 0;   // +0x20  (the destroy/free path)

    char          _pad_004[0xAC - 0x04]; // +0x004  (after the vptr@0x00)
    int           AnimationValue;        // +0x0AC
    char          _pad_0B0[0x119 - 0xB0];// +0x0B0
    unsigned char UnderTemporal;         // +0x119
    unsigned char Paused;                // +0x11A
    unsigned char Unpaused;              // +0x11B
    int           PausedAnimFrame;       // +0x11C
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(AnimClass, AnimationValue)  == 0xAC);
GG_STATIC_ASSERT(offsetof(AnimClass, UnderTemporal)   == 0x119);
GG_STATIC_ASSERT(offsetof(AnimClass, Paused)          == 0x11A);
GG_STATIC_ASSERT(offsetof(AnimClass, Unpaused)        == 0x11B);
GG_STATIC_ASSERT(offsetof(AnimClass, PausedAnimFrame) == 0x11C);
#endif

// ---------------------------------------------------------------------------
// BuildingTypeClass — only three fields are read:
//   +0x16B7 NonTraversable flag (IsTraversable), +0x16F0 FirstSWIdx,
//   +0x16F4 SecondSWIdx.
// ---------------------------------------------------------------------------
class BuildingTypeClass
{
public:
    char          _pad_0000[0x16B7];     // +0x0000
    unsigned char NonTraversable;        // +0x16B7
    char          _pad_16B8[0x16F0 - 0x16B8];
    int           FirstSWIdx;            // +0x16F0
    int           SecondSWIdx;           // +0x16F4
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, NonTraversable) == 0x16B7);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, FirstSWIdx)     == 0x16F0);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, SecondSWIdx)    == 0x16F4);
#endif

// IsTraversable sub-object at +0x350: `lea ecx,[this+0x350]; call 0x4A51B0`.
// A __thiscall predicate; only its calling shape matters here (reloc-normalised).
struct BuildingTraverseHelper
{
    bool Check_4A51B0();                 // GAMEMD 0x4A51B0 __thiscall (declared; reloc)
};

// SuperWeapon chain reached by First/SecondActiveSWIdx, via the global array at
// 0x00A83CBC (a SWTypeClass** array). node->[0x28]->[0xC8]->[0xDF8].
struct SWChainC8 { char _p[0xDF8]; int field_DF8; };          // +0xDF8
struct SWChain28 { char _p[0xC8];  SWChainC8* field_C8; };    // +0xC8
struct SWChainNode { char _p[0x28]; SWChain28* field_28; };   // +0x28

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(SWChainNode, field_28) == 0x28);
GG_STATIC_ASSERT(offsetof(SWChain28,  field_C8) == 0xC8);
GG_STATIC_ASSERT(offsetof(SWChainC8,  field_DF8) == 0xDF8);
#endif

// GLOBAL: GAMEMD 0x00A83CBC — pointer to the SWTypeClass* array (Items).
extern SWChainNode** g_SWArray;

// ---------------------------------------------------------------------------
// BuildingClass — padded to each touched offset. Full layout is P2.
// ---------------------------------------------------------------------------
class BuildingClass
{
public:
    void DestroyNthAnim(int slot);       // GAMEMD 0x451E40 __thiscall
    void DisableTemporal();              // GAMEMD 0x4521C0 __thiscall
    void EnableTemporal();               // GAMEMD 0x452210 __thiscall
    bool IsTraversable();                // GAMEMD 0x4525F0 __thiscall
    int  FirstActiveSWIdx();             // GAMEMD 0x457630 __thiscall
    int  SecondActiveSWIdx();            // GAMEMD 0x457690 __thiscall

    char                   _pad_0000[0x21C];          // +0x0000
    HouseClass*            Owner;                      // +0x021C
    char                   _pad_0220[0x350 - 0x220];  // +0x0220
    BuildingTraverseHelper TraverseHelper;            // +0x0350 (sizeof 1)
    char                   _pad_0351[0x520 - 0x351];  // +0x0351
    BuildingTypeClass*     Type;                       // +0x0520
    char                   _pad_0524[0x55C - 0x524];  // +0x0524
    AnimClass*             Anims[0x15];               // +0x055C
    char                   _pad_05B0[0x660 - 0x5B0];  // +0x05B0
    unsigned char          BeingTemporal;             // +0x0660
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(BuildingClass, Owner)         == 0x21C);
GG_STATIC_ASSERT(offsetof(BuildingClass, TraverseHelper)== 0x350);
GG_STATIC_ASSERT(offsetof(BuildingClass, Type)          == 0x520);
GG_STATIC_ASSERT(offsetof(BuildingClass, Anims)         == 0x55C);
GG_STATIC_ASSERT(offsetof(BuildingClass, BeingTemporal) == 0x660);
#endif

#endif  // GG_MATCH_ECONOMY_BUILDING_CLASS_H
