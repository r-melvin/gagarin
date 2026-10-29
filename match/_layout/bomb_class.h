// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x4389B0–0x438A8F), cross-checked
//   against YRpp (
//   reconfirmed numerically here).
//
// BombClass — a planted Ivan/time bomb: owner bookkeeping, a target object,
// detonation timing, and an AudioController for the ticking sound.
#ifndef GG_MATCH_LAYOUT_BOMB_CLASS_H
#define GG_MATCH_LAYOUT_BOMB_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "object_class.h"   // canonical AudioController, ObjectClass

class TechnoClass;
class HouseClass;

// Unsorted::CurrentFrame — global frame counter @0x00A8ED84 (read by TimeToExplode).
#include "../core/frame_counter.h"

class BombClass : public AbstractClass
{
public:
    BombClass();                        // GAMEMD 0x4385D0 (declaration; reloc)
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    virtual HRESULT __stdcall Load(IStream* pStm);
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    virtual int vf_11();
    virtual int vf_12();

    void Disarm();                      // GAMEMD 0x4389B0 __thiscall
    int  IsDeathBomb() const;           // GAMEMD 0x4389F0 __thiscall
    bool TimeToExplode() const;         // GAMEMD 0x438A70 __thiscall

    int  GetCurrentFlickerFrame() const; // GAMEMD 0x438A00 __thiscall

    // AbstractClass base occupies [0x00..0x23].
    TechnoClass*      Owner;                // +0x24
    HouseClass*       OwnerHouse;           // +0x28
    ObjectClass*      Target;                     // +0x2C
    int               DeathBomb;            // +0x30
    int               PlantingFrame;        // +0x34
    int               DetonationFrame;      // +0x38
    AudioController   Audio;                // +0x3C (0x14 bytes)
    int               unknown_50;           // +0x50
    int               TickSound;            // +0x54
    unsigned char     Harmless;             // +0x58
};

GG_STATIC_ASSERT(offsetof(BombClass, DeathBomb)       == 0x30);
GG_STATIC_ASSERT(offsetof(BombClass, PlantingFrame)   == 0x34);
GG_STATIC_ASSERT(offsetof(BombClass, DetonationFrame) == 0x38);
GG_STATIC_ASSERT(offsetof(BombClass, unknown_50)      == 0x50);
GG_STATIC_ASSERT(offsetof(BombClass, TickSound)       == 0x54);
GG_STATIC_ASSERT(offsetof(BombClass, Harmless)        == 0x58);
GG_STATIC_ASSERT(sizeof(BombClass)                     == 0x5C);

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(BombClass, Owner)      == 0x24);
GG_STATIC_ASSERT(offsetof(BombClass, OwnerHouse) == 0x28);
GG_STATIC_ASSERT(offsetof(BombClass, Target)     == 0x2C);
GG_STATIC_ASSERT(offsetof(BombClass, Audio)      == 0x3C);
#endif

#endif  // GG_MATCH_LAYOUT_BOMB_CLASS_H
