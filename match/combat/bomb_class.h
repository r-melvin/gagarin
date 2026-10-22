// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x4389B0–0x438A8F), cross-checked
//   against YRpp (
//   reconfirmed numerically here).
//
// BombClass — a planted Ivan/time bomb: owner bookkeeping, a target object,
// detonation timing, and an AudioController for the ticking sound.
#ifndef GG_MATCH_COMBAT_BOMB_CLASS_H
#define GG_MATCH_COMBAT_BOMB_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class TechnoClass;
class HouseClass;

// Unsorted::CurrentFrame — global frame counter @0x00A8ED84 (read by TimeToExplode).
#include "../core/frame_counter.h"

// The Target object: Disarm clears two of its members (an int @0x38 and a
// flag byte @0x68 — the back-link/attached-bomb flag). Only these are modelled.
struct BombTargetObject
{
    char          _pad0[0x38];          // +0x00
    int           AttachedField;        // +0x38  cleared by Disarm
    char          _pad1[0x68 - 0x3C];   // +0x3C
    unsigned char AttachedFlag;         // +0x68  cleared by Disarm (byte)
};

// AudioController — opaque 0x18-byte controller; Disarm calls End() @0x405FD0
// (lea ecx,[this+0x3c]; call End). Full decomposition is out of scope here.
struct AudioController
{
    void End();                         // GAMEMD 0x405FD0 __thiscall (declared; reloc)
    char _storage[0x18];
};

class BombClass
{
public:
    void Disarm();                      // GAMEMD 0x4389B0 __thiscall
    int  IsDeathBomb() const;           // GAMEMD 0x4389F0 __thiscall
    bool TimeToExplode() const;         // GAMEMD 0x438A70 __thiscall

    // AbstractClass base (COM IPersistStream + members) occupies [0x00..0x23];
    // its full decomposition is P2.
    char              _abstract_base[0x24]; // +0x00
    TechnoClass*      Owner;                // +0x24
    HouseClass*       OwnerHouse;           // +0x28
    BombTargetObject* Target;               // +0x2C
    int               DeathBomb;            // +0x30
    int               PlantingFrame;        // +0x34
    int               DetonationFrame;      // +0x38
    AudioController   Audio;                // +0x3C (0x18 bytes)
    int               TickSound;            // +0x54
    unsigned char     Harmless;             // +0x58
};

GG_STATIC_ASSERT(offsetof(BombClass, DeathBomb)       == 0x30);
GG_STATIC_ASSERT(offsetof(BombClass, PlantingFrame)   == 0x34);
GG_STATIC_ASSERT(offsetof(BombClass, DetonationFrame) == 0x38);
GG_STATIC_ASSERT(offsetof(BombClass, TickSound)       == 0x54);
GG_STATIC_ASSERT(offsetof(BombClass, Harmless)        == 0x58);
GG_STATIC_ASSERT(offsetof(BombTargetObject, AttachedField) == 0x38);
GG_STATIC_ASSERT(offsetof(BombTargetObject, AttachedFlag)  == 0x68);

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(BombClass, Owner)      == 0x24);
GG_STATIC_ASSERT(offsetof(BombClass, OwnerHouse) == 0x28);
GG_STATIC_ASSERT(offsetof(BombClass, Target)     == 0x2C);
GG_STATIC_ASSERT(offsetof(BombClass, Audio)      == 0x3C);
#endif

#endif  // GG_MATCH_COMBAT_BOMB_CLASS_H
