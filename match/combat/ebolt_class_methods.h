// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x4C2BD0–0x4C2C08), cross-checked
//   against YRpp (reconfirmed
//   numerically here).
//
// EBolt — an electric-bolt visual effect. SetOwner latches the firing unit and
// the weapon slot it was launched from, but only for a live, on-map UnitClass.
#ifndef GG_MATCH_COMBAT_EBOLT_CLASS_METHODS_H
#define GG_MATCH_COMBAT_EBOLT_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The owning game object as SetOwner sees it: a UnitClass (an ObjectClass leaf).
// SetOwner only needs three things from it, all confirmed from the disasm:
//   * a virtual WhatAmI() dispatched through the primary vtable at byte offset
//     0x2C (mov eax,[esi]; call [eax+0x2c]) — i.e. vtable slot 11;
//   * the InLimbo flag byte @0x81;
//   * the IsAlive flag byte @0x90.
// The 11 leading slots stand in for the AbstractClass/COM primary-vtable entries
// (IPersistStream + RTTI) that precede WhatAmI. They are declared but never
// defined or instantiated here, so no vtable is emitted; we dispatch purely
// through the retail object's own vptr. WhatAmI returns the full dword the
// retail compares against 1 (AbstractType::Unit).
struct EBoltOwner
{
    virtual void _vf00();
    virtual void _vf01();
    virtual void _vf02();
    virtual void _vf03();
    virtual void _vf04();
    virtual void _vf05();
    virtual void _vf06();
    virtual void _vf07();
    virtual void _vf08();
    virtual void _vf09();
    virtual void _vf10();
    virtual int  WhatAmI() const;          // slot 11 -> call [eax+0x2c]

    char          _pad04[0x81 - 0x04];     // +0x04 .. +0x80
    unsigned char InLimbo;                 // +0x81  (bool)
    char          _pad82[0x90 - 0x82];     // +0x82 .. +0x8F
    unsigned char IsAlive;                 // +0x90  (bool)
};

GG_STATIC_ASSERT(offsetof(EBoltOwner, InLimbo) == 0x81);
GG_STATIC_ASSERT(offsetof(EBoltOwner, IsAlive) == 0x90);

struct EBolt
{
    void SetOwner(EBoltOwner* pOwner, int idxWeapon);   // GAMEMD 0x4C2BD0

    // Point1/Point2/duration/random precede Owner; their full decomposition is
    // P2. SetOwner only writes Owner @0x20 and WeaponSlot @0x24.
    char        _head[0x20];        // +0x00 .. +0x1F
    EBoltOwner* Owner;              // +0x20  TechnoClass* (a UnitClass)
    int         WeaponSlot;         // +0x24
};

GG_STATIC_ASSERT(offsetof(EBolt, Owner)      == 0x20);
GG_STATIC_ASSERT(offsetof(EBolt, WeaponSlot) == 0x24);

#endif  // GG_MATCH_COMBAT_EBOLT_CLASS_METHODS_H
