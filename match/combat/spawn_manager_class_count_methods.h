// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access + virtual-call disassembly at 0x6B7D80),
//   cross-checked against YRpp (
//   every offset reconfirmed numerically here).
//
// SpawnManagerClass::CountLaunchingSpawns — walk the SpawnedNodes vector and
// count spawn nodes that are mid-launch: either node Status == 1 (TakeOff), or
// node Status == 2 (CoolDown) whose live Unit is not flagged at +0x81 and whose
// type (vtable slot 33, +0x84) carries the launch flag at type +0xD68.
#ifndef GG_MATCH_COMBAT_SPAWN_MANAGER_CLASS_COUNT_METHODS_H
#define GG_MATCH_COMBAT_SPAWN_MANAGER_CLASS_COUNT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#ifndef NULL
#define NULL 0
#endif

// SpawnUnitType (the spawned unit's TechnoTypeClass). Only the launch flag byte
// at +0xD68 is read (MOV CL,[EAX+0xD68]); full layout is P2.
struct SpawnUnitType
{
    char          _pad_d68[0xD68];   // +0x0000 .. +0x0D67
    unsigned char Flag_d68;          // +0x0D68
};

GG_STATIC_ASSERT(offsetof(SpawnUnitType, Flag_d68) == 0xD68);

// SpawnUnit (the spawned object, an AircraftClass/TechnoClass). CountLaunching
// touches its vptr (vtable slot 33, +0x84 — GetType()) and the bool byte at
// +0x81. The 33 leading virtuals only pin GetType to slot +0x84; none are
// defined and SpawnUnit is never constructed, so no vtable is emitted here.
struct SpawnUnit
{
    virtual void _vt_00();  virtual void _vt_01();  virtual void _vt_02();
    virtual void _vt_03();  virtual void _vt_04();  virtual void _vt_05();
    virtual void _vt_06();  virtual void _vt_07();  virtual void _vt_08();
    virtual void _vt_09();  virtual void _vt_10();  virtual void _vt_11();
    virtual void _vt_12();  virtual void _vt_13();  virtual void _vt_14();
    virtual void _vt_15();  virtual void _vt_16();  virtual void _vt_17();
    virtual void _vt_18();  virtual void _vt_19();  virtual void _vt_20();
    virtual void _vt_21();  virtual void _vt_22();  virtual void _vt_23();
    virtual void _vt_24();  virtual void _vt_25();  virtual void _vt_26();
    virtual void _vt_27();  virtual void _vt_28();  virtual void _vt_29();
    virtual void _vt_30();  virtual void _vt_31();  virtual void _vt_32();
    virtual SpawnUnitType* GetType() const;          // slot 33 -> +0x84

    char          _pad_04[0x81 - 0x04];   // +0x04 .. +0x80
    unsigned char Flag81;                 // +0x81
};

GG_STATIC_ASSERT(offsetof(SpawnUnit, Flag81) == 0x81);

#include "../_layout/spawn_manager_class.h"

#endif  // GG_MATCH_COMBAT_SPAWN_MANAGER_CLASS_COUNT_METHODS_H
