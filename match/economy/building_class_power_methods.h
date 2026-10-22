// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x44E880), cross-checked against
//   YRpp
//   (every offset reconfirmed numerically from the disasm below).
//
// BuildingClass::GetPowerDrain — the structure's per-frame power consumption.
// The retail body is:
//   * an early-out virtual call through vtable slot @+0x1D4 (returns drain 0
//     when the building is offline / suppressed),
//   * a HasPower @+0x660 gate (drain 0 while unpowered),
//   * base drain   = Type->PowerDrain        ([Type+0xEE4]),
//   * + Type->ExtraPowerDrain ([Type+0xEEC]) when HasExtraPowerDrain @+0x669,
//   * + each populated Upgrades[0..2]->PowerDrain ([up+0xEE4]) when
//     UpgradeLevel @+0x702 is non-zero (a fixed 3-iteration loop over the
//     Upgrades[3] pointer array @+0x5EC).
//
// The leading dispatch is a virtual call at vtable byte offset 0x1D4
// (slot 117), written as an ordinary member-pointer call through the modelled
// vtable struct below. Retail's prologue is a bare `PUSH ESI` with no frame
// pointer, which is what /O2 emits for this shape and carries none of the
// inline-assembly signature (no `PUSH EBP; MOV EBP,ESP`, no stack-homed locals,
// no instruction outside cl's repertoire), so the retail source was ordinary
// C++ and so is this.
#ifndef GG_MATCH_ECONOMY_BUILDING_CLASS_POWER_METHODS_H
#define GG_MATCH_ECONOMY_BUILDING_CLASS_POWER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// BuildingTypeClass — only the two drain ints this method reads are modelled.
//   +0xEE4 PowerDrain        (base drain)
//   +0xEEC ExtraPowerDrain   (added when the instance has the extra-drain flag)
// (ExtraPowerBonus sits between them at +0xEE8; not touched here.)
// ---------------------------------------------------------------------------
class BuildingTypeClass
{
public:
    char _pad_0000[0xEE4];               // +0x0000  (full layout is P2)
    int  PowerDrain;                     // +0x0EE4
    int  ExtraPowerBonus;                // +0x0EE8
    int  ExtraPowerDrain;                // +0x0EEC
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, PowerDrain)      == 0xEE4);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, ExtraPowerDrain) == 0xEEC);
#endif

// ---------------------------------------------------------------------------
// BuildingClass — padded to each touched offset; full TechnoClass-derived
// layout is P2.  The leading word at +0x000 is the first COM vtable pointer
// (read as `mov eax,[esi]` for the slot-117 dispatch).
//   +0x520 Type (BuildingTypeClass*)
//   +0x5EC Upgrades[0x3] (BuildingTypeClass*)
//   +0x660 HasPower            (bool gate)
//   +0x669 HasExtraPowerDrain  (bool — add Type->ExtraPowerDrain)
//   +0x702 UpgradeLevel        (bool/byte — run the upgrades drain loop)
// ---------------------------------------------------------------------------
struct BuildingVtbl;

class BuildingClass
{
public:
    int  GetPowerDrain() const;          // GAMEMD 0x44E880 __thiscall

    BuildingVtbl*      Vfptr;                            // +0x0000
    char               _pad_0004[0x520 - 4];             // +0x0004
    BuildingTypeClass* Type;                             // +0x0520
    char               _pad_0524[0x5EC - 0x524];         // +0x0524
    BuildingTypeClass* Upgrades[0x3];                    // +0x05EC
    char               _pad_05F8[0x660 - 0x5F8];         // +0x05F8
    unsigned char      HasPower;                         // +0x0660
    char               _pad_0661[0x669 - 0x661];         // +0x0661
    unsigned char      HasExtraPowerDrain;               // +0x0669
    char               _pad_066A[0x702 - 0x66A];         // +0x066A
    unsigned char      UpgradeLevel;                     // +0x0702
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(BuildingClass, Vfptr)              == 0x000);
GG_STATIC_ASSERT(offsetof(BuildingClass, Type)               == 0x520);
GG_STATIC_ASSERT(offsetof(BuildingClass, Upgrades)           == 0x5EC);
GG_STATIC_ASSERT(offsetof(BuildingClass, HasPower)           == 0x660);
GG_STATIC_ASSERT(offsetof(BuildingClass, HasExtraPowerDrain) == 0x669);
GG_STATIC_ASSERT(offsetof(BuildingClass, UpgradeLevel)       == 0x702);
#endif

// The class has to be complete before the typedef, or VC6 falls back to the
// multiple-inheritance member-pointer form and emits a `this` adjustment.
// Slot +0x1D4 takes no arguments and is tested as a byte, so it returns bool.
typedef bool (BuildingClass::*IsDrainSuppressedFn)() const;

struct BuildingVtbl
{
    char                _pad_0000[0x1D4];   // 0x0000
    IsDrainSuppressedFn At_1D4;             // 0x01D4
};
GG_STATIC_ASSERT(offsetof(BuildingVtbl, At_1D4) == 0x1D4);

#endif  // GG_MATCH_ECONOMY_BUILDING_CLASS_POWER_METHODS_H
