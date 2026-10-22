// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x6CE1A0), cross-checked against
//   YRpp (every offset
//   reconfirmed numerically here).
//
// SuperClass::ShouldFlashTab — sidebar tab flash logic for a per-house
// superweapon instance. Self-contained binding (re-derives the same SuperClass
// layout as super_class_methods.h, extended to the members this method reads).
#ifndef GG_MATCH_COMBAT_SUPER_CLASS_MORE_METHODS_H
#define GG_MATCH_COMBAT_SUPER_CLASS_MORE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Unsorted::CurrentFrame — global frame counter @0x00A8ED84.
#include "../core/frame_counter.h"

// SuperWeaponTypeClass — only the three members read by ShouldFlashTab:
//   UseChargeDrain @0xE5 (mov dl,[eax+0xE5]),
//   FlashSidebarTabFrames @0xE8 (mov eax,[eax+0xE8]).
struct SuperWeaponTypeClass
{
    char          _pad0[0xE5];             // +0x00
    unsigned char UseChargeDrain;          // +0xE5
    char          _padE6[0xE8 - 0xE6];     // +0xE6
    int           FlashSidebarTabFrames;   // +0xE8
};
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, UseChargeDrain) == 0xE5);
GG_STATIC_ASSERT(offsetof(SuperWeaponTypeClass, FlashSidebarTabFrames) == 0xE8);

// SuperClass : AbstractClass. Members touched by ShouldFlashTab:
//   Type @0x28, IsReady @0x6F, IsSuspended @0x70, ReadyFrame @0x74,
//   ChargeDrainState @0x7C.
struct SuperClass
{
    char                  _base[0x28];         // +0x00  AbstractClass + CustomChargeTime
    SuperWeaponTypeClass* Type;                // +0x28
    char                  _pad2[0x6F - 0x2C];  // +0x2C
    unsigned char         IsReady;             // +0x6F
    unsigned char         IsSuspended;         // +0x70
    char                  _pad3[0x74 - 0x71];  // +0x71
    int                   ReadyFrame;          // +0x74
    char                  _pad4[0x7C - 0x78];  // +0x78
    int                   ChargeDrainState;    // +0x7C

    bool ShouldFlashTab() const;               // GAMEMD 0x6CE1A0 __thiscall
};
GG_STATIC_ASSERT(offsetof(SuperClass, Type) == 0x28);
GG_STATIC_ASSERT(offsetof(SuperClass, IsReady) == 0x6F);
GG_STATIC_ASSERT(offsetof(SuperClass, IsSuspended) == 0x70);
GG_STATIC_ASSERT(offsetof(SuperClass, ReadyFrame) == 0x74);
GG_STATIC_ASSERT(offsetof(SuperClass, ChargeDrainState) == 0x7C);

#endif  // GG_MATCH_COMBAT_SUPER_CLASS_MORE_METHODS_H
