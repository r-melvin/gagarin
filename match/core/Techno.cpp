// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | private-ref-cross-check
//   Original translation unit Techno.CPP. The name is the source-file string at 0x843178
//   in retail gamemd.exe v1.001, passed by the assert at 0x70aad3 inside this object's
//   code range (0x6f28a0-0x7108df). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Leaf bodies that repeat at several addresses: the integer sort comparator
// (the same shape as IndexClass::Comparator, bound to other tables), release
// and replace of one global heap block, a 64 KiB global buffer clear, and
// three constant or global tests. Each address was verified separately.
//
// Six key/value-vector Grow instances, ordered ascending by retail address.
//
// Grow the vector by `extra` slots: allocate, copy the live elements across
// field by field, free the old block, and invalidate the cached lookup slot. A
// negative request and a failed allocation both report false without touching
// anything.
//
// The phrasing is the one already driven to 100% at 0x41C500 and is reproduced
// unchanged. The two details that matter are recorded there and hold here: the
// allocation is `new GrowPair[total]`, whose elided vector-constructor-iterator
// setup is retail's `DEC`/spill pair after the null check, and the copy is a
// whole-struct assignment through an explicit byte offset, which is what moves
// the pair as two dwords sharing one address computation and keeps the index a
// plain register. Count and Items are re-read every iteration rather than
// hoisted.
//
// The nine tail-jump thunks, ordered ascending by retail address.
//
//   Names cross-checked against YRpp (RecoilData::Fire,
//   JMP_THIS(0x70ECE0)) — each offset reconfirmed
//   against the user's binary.
//
// Disassembly skeleton (0x70ECE0..0x70ED0B, len 0x2C):
//   PUSH ECX                ; reserve 4-byte stack slot for the cached Travel
//   MOV  EAX,[ECX]          ; travel = Turret.Travel
//   TEST EAX,EAX
//   MOV  [ESP],EAX          ; spill travel
//   JZ   end
//   MOV  EAX,[ECX+4]        ; CompressFrames
//   MOV  EDX,1
//   CMP  EAX,EDX
//   MOV  [ECX+0x18],EDX     ; State = 1
//   MOV  [ECX+0x1c],EAX     ; TravelFramesLeft = CompressFrames
//   JGE  skip               ; (CompressFrames >= 1)
//   MOV  [ECX+0x1c],EDX     ; TravelFramesLeft = 1
//  skip:
//   FILD  [ESP]             ; (float)travel
//   FIDIV [ECX+0x1c]        ;  / TravelFramesLeft  (integer divisor)
//   FSTP  [ECX+0x10]        ; TravelPerFrame = ...
//  end:
//   POP  ECX
//   RET
//
//   len 0x20, 0x7010D0 len 0x45, 0x701120 len 0x1A, 0x70C5A0 len 0xC,
//   0x70EFD0 len 0xE, 0x70F090 len 0x12, 0x70F850 len 0x33).
//
// Seven adjacent TechnoClass virtual-slot bases. They share a receiver and a
// shape: read one member or one slot, and report a decision.
//
//   Every displacement, constant, table bound and callee below was read off
//   the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. None of the owning classes is bound by RTTI or
//   a binary string here, so all keep placeholder names. The imports are named
//   by the PE import table (CloseHandle 0x7E11E0; ImmAssociateContext through
//   its thunk at 0x7C8A1C).
//
// Small leaves (64 bytes or less) between 0x6B0000 and 0x7B0000 that other
// translation units already declared as callees but nothing defined.

#include "../combat/techno_class_combat_damage_methods.h"

#include "../combat/techno_class_gattling_rate_methods.h"

#include "../combat/techno_class_nearby_location_methods.h"

#include "../combat/techno_class_passive_acquire_methods.h"

#include "../combat/techno_class_reloading_methods.h"

#include "abstract_class_untargetable_methods.h"

#include <string.h>

// LIBRARY: GAMEMD 0x7C8B3D -- CRT free.
extern "C" void __cdecl gg_free(void*);

extern int DAT_00A9FABC;
extern void* DAT_00ABF3F4;
extern int DAT_00B2FF78[0x4000];
extern int DAT_00B1D5E0[0x4000];
extern void* DAT_00B77F54;
extern void* DAT_00B77F60;

#include "member_setter_family_methods.h"

#include "pair_vector_grow_sweep.h"

#include "tail_jmp_thunk_sweep.h"



#include "trivial_tu237_methods.h"

#include <windows.h>
#include <imm.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" int __cdecl _stricmp(const char* a, const char* b);

// ---------------------------------------------------------------------------

struct Quad_006C95E0
{
    int unknown_0;
    int unknown_4;
    int unknown_8;
    int unknown_C;

    Quad_006C95E0();
};

// GLOBAL: GAMEMD 0x00B0CB78
extern "C" int DAT_00B0CB78[];

struct Rect_006CFDB0
{
    int unknown_0;
    int unknown_4;
    int unknown_8;
    int unknown_C;
};

// GLOBAL: GAMEMD 0x00B0FC60
extern "C" Rect_006CFDB0* DAT_00B0FC60;
// GLOBAL: GAMEMD 0x00B0FC68
extern "C" Rect_006CFDB0* DAT_00B0FC68;
// GLOBAL: GAMEMD 0x00B0FC6C
extern "C" Rect_006CFDB0* DAT_00B0FC6C;
// GLOBAL: GAMEMD 0x00B0CB54
extern "C" int DAT_00B0CB54;
// GLOBAL: GAMEMD 0x00B0CC2C
extern "C" int DAT_00B0CC2C;

struct Link_006EF5F0
{
    char Pad_00[0xF0];
    int unknown_F0;
    char Pad_F4[0x5D8 - 0xF4];
    Link_006EF5F0* unknown_5D8;
};
GG_STATIC_ASSERT(offsetof(Link_006EF5F0, unknown_F0) == 0xF0);
GG_STATIC_ASSERT(offsetof(Link_006EF5F0, unknown_5D8) == 0x5D8);

struct Obj_006EF5F0
{
    char Pad_00[0x54];
    Link_006EF5F0* unknown_54;

    void FUN_006EF5F0(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_006EF5F0, unknown_54) == 0x54);

struct Obj_00705D20
{
    char Pad_00[0x514];
    int unknown_514;
};
GG_STATIC_ASSERT(offsetof(Obj_00705D20, unknown_514) == 0x514);

// GLOBAL: GAMEMD 0x00843108
extern "C" char DAT_00843108;

struct Obj_00711EB0
{
    char Pad_00[0x610];
    int unknown_610;
};
GG_STATIC_ASSERT(offsetof(Obj_00711EB0, unknown_610) == 0x610);

struct Obj_00717880
{
    char Pad_00[0x808];
    int unknown_808;
};
GG_STATIC_ASSERT(offsetof(Obj_00717880, unknown_808) == 0x808);

struct Obj_00726910
{
    char Pad_00[0x2C];
    int unknown_2C;
};
GG_STATIC_ASSERT(offsetof(Obj_00726910, unknown_2C) == 0x2C);

// GLOBAL: GAMEMD 0x00B0FE54
extern "C" int DAT_00B0FE54;
// GLOBAL: GAMEMD 0x00B0FE58
extern "C" char DAT_00B0FE58;

// GLOBAL: GAMEMD 0x008463B8 (eighteen string pointers)
extern "C" const char* const DAT_008463B8[18];

struct Item_00751040
{
    void FUN_004053E0();
};

struct Holder_00751040
{
    Item_00751040* FUN_00406130();
};

struct Node_00751040
{
    char Pad_00[0x0C];
    Holder_00751040 unknown_C;
    char Pad_0D[0x30 - 0x0D];
    int unknown_30;

    Node_00751040* FUN_004073E0();
};
GG_STATIC_ASSERT(offsetof(Node_00751040, unknown_30) == 0x30);

struct List_00751040
{
    Node_00751040* FUN_004073C0();
};

// GLOBAL: GAMEMD 0x00B1D320
extern "C" List_00751040 DAT_00B1D320;

struct Named_00751590
{
    const char* FUN_00405170();
};

struct Entry_00751590
{
    Named_00751590* unknown_0;
};

// GLOBAL: GAMEMD 0x00B1D37C
extern "C" Entry_00751590** DAT_00B1D37C;
// GLOBAL: GAMEMD 0x00B1D388
extern "C" int DAT_00B1D388;
// GLOBAL: GAMEMD 0x00846574
extern "C" const char DAT_00846574[];
// GLOBAL: GAMEMD 0x00817474
extern "C" const char DAT_00817474[];

struct Obj_00753510
{
    void FUN_00407FB0();
    void FUN_00408000();
};

// GLOBAL: GAMEMD 0x00B1D4D8
extern "C" Obj_00753510* DAT_00B1D4D8;
// GLOBAL: GAMEMD 0x00B1D4CC
extern "C" Obj_00753510* DAT_00B1D4CC;
// GLOBAL: GAMEMD 0x00B1D428
extern "C" int DAT_00B1D428;

struct Record_007559B0
{
    int unknown_0[12];
};

// GLOBAL: GAMEMD 0x00B45188 (48-byte records)
extern "C" Record_007559B0 DAT_00B45188[];

// GLOBAL: GAMEMD 0x007E5210 (eleven string pointers)
extern "C" const char* const DAT_007E5210[11];

// GLOBAL: GAMEMD 0x008497A4
extern "C" const char DAT_008497A4[];

// 0x4068E0: cdecl text sink taking a format string (callee only).
void __cdecl FUN_004068E0(const char* format, ...);

struct Obj_00774950
{
    char Pad_00[0x5C];
    HANDLE unknown_5C;
};
GG_STATIC_ASSERT(offsetof(Obj_00774950, unknown_5C) == 0x5C);

// GLOBAL: GAMEMD 0x00B73550
extern "C" HWND DAT_00B73550;
// GLOBAL: GAMEMD 0x00B7355C
extern "C" HIMC DAT_00B7355C;

// GLOBAL: GAMEMD 0x00A8B238
extern "C" int DAT_00A8B238;
// GLOBAL: GAMEMD 0x00B76B24
extern "C" int DAT_00B76B24;
struct Flags_0077D940
{
    unsigned int unknown_0 : 8;
    unsigned int unknown_8 : 1;
};

// GLOBAL: GAMEMD 0x00B76B30
extern "C" Flags_0077D940 DAT_00B76B30;

#include "../movement/locomotion_begin_drain_methods.h"

#include "../movement/locomotion_com_helpers.h"

#include "../movement/locomotion_forget_pointer_methods.h"

#include "../movement/locomotion_link_query_methods.h"

#include "../movement/locomotion_velocity_methods.h"

#include "../movement/techno_class_release_locomotor_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F4880
extern const double DAT_007F4880;
// GLOBAL: GAMEMD 0xB0EA58
extern double DAT_00B0EA58;
// GLOBAL: GAMEMD 0xB0EB10
extern double DAT_00B0EB10;
// GLOBAL: GAMEMD 0xB0EB18
extern int DAT_00B0EB18;
// GLOBAL: GAMEMD 0xB0EB1C
extern int DAT_00B0EB1C;
// GLOBAL: GAMEMD 0xB0EB20
extern int DAT_00B0EB20;
// GLOBAL: GAMEMD 0xB0EB28
extern double DAT_00B0EB28;


// ---- from the former Techno.cpp ----
//   CLI (disasm from each entry point). Original TU: Techno.CPP, attested by the
//   __FILE__ assert string at 0x843178 (pushed at 0x70AAD3, 0x70ABFD, 0x70AC33);
//   the TU spans 0x6F28A0-0x7108DF. Class layout and vtable slots come from the committed
//   spine match/_layout/techno_class.h. Slot numbers are RTTI-derived
//   (TechnoClass vtable 0x7F4960); the vf_N names are placeholders.

#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"
#include "../combat/weapon_type_class.h"
#include "frame_counter.h"
#include "../_layout/cell_class.h"
#include "../_layout/house_class.h"

// Offsets this TU relies on, each read from an instruction in the matched bodies.
GG_STATIC_ASSERT(offsetof(TechnoClass, CurrentTurretNumber)       == 0x124);  // 0x70DD00
GG_STATIC_ASSERT(offsetof(TechnoClass, unknown_int_128)           == 0x128);  // 0x70DD00
GG_STATIC_ASSERT(offsetof(TechnoClass, GattlingValue)             == 0x144);  // 0x70DE40
GG_STATIC_ASSERT(offsetof(TechnoClass, AirstrikeTimer)            == 0x1A8);  // 0x70E340
GG_STATIC_ASSERT(offsetof(TechnoClass, LastTarget)                == 0x2B8);  // 0x7013A0
GG_STATIC_ASSERT(offsetof(TechnoClass, IsOwnedByCurrentPlayer)    == 0x41A);  // 0x7018C0
GG_STATIC_ASSERT(offsetof(TechnoClass, DiscoveredByCurrentPlayer) == 0x41B);  // 0x6F4A40
GG_STATIC_ASSERT(offsetof(TechnoClass, IsRadarTracked)            == 0x423);  // 0x70CC90
GG_STATIC_ASSERT(offsetof(TechnoClass, QueuedVoiceIndex)          == 0x4F0);  // 0x708D90
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Drainable)             == 0x5EF);  // 0x70FED0
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Speed)                 == 0x678);  // 0x70EFE0
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, SprayAttack)           == 0x691);  // 0x70DD70
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, HasTurretTooltips)     == 0x806);  // 0x70DC50
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, WeaponCount)           == 0x80C);  // 0x70E1E0

// The map singleton (GAMEMD 0x87F7E8). Only the cell lookup is reached here; it
// reads the X and Y words of the coordinate it is handed.
class MapClass
{
public:
    // FUNCTION: GAMEMD 0x565730 (decl; reloc) -- the cell under a coordinate.
    CellClass* GetTargetCell(const CoordStruct& where);
    // FUNCTION: GAMEMD 0x655560 (decl; reloc) -- takes the unit and its RadarPosition.
    void FUN_00655560(TechnoClass* unit, Point2D position);
    // FUNCTION: GAMEMD 0x655740 (decl; reloc) -- takes the unit and its RadarPosition.
    void FUN_00655740(TechnoClass* unit, Point2D position);
};

// GLOBAL: GAMEMD 0x87F7E8
extern MapClass MapClass_Instance;
// GLOBAL: GAMEMD 0xB0EA80 -- a frame timer restarted by 0x70D150.
extern CDTimerClass DAT_00B0EA80;
// GLOBAL: GAMEMD 0x822CF2
extern bool DAT_00822CF2;
// GLOBAL: GAMEMD 0xA83D4C -- the local player's house.
extern HouseClass* CurrentPlayer;

static inline CellStruct CoordToCell(const CoordStruct& coord)
{
    CellStruct cell;
    cell.X = (short)(coord.X / 256);
    cell.Y = (short)(coord.Y / 256);
    return cell;
}


// TechnoClass bodies for primary-table (0x7F4960) slots 25, 186, 180 and 102
// (0x6F32D0..0x6F4A3E). Slot numbers come from the RTTI-located table; names
// are placeholders (techno_class.h).

// Translation unit: BuildingClass::IsBeingDrained.

//   member offsets derived directly from the disassembly.


#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/house_class.h"
#include "../_layout/tag_class.h"

// GLOBAL: GAMEMD 0xA83D4C
extern HouseClass* CurrentPlayer;
// GLOBAL: GAMEMD 0xA8E7AC
extern int DAT_00A8E7AC;
// GLOBAL: GAMEMD 0xB0EA50
extern CellStruct DAT_00B0EA50;

#include "techno_class_kill_passengers_methods.h"

// The null-safe FootClass cast retail inlined at the loop's back edge: null
// stays null, anything without the AbstractClass foot bit (+0x14, mask 4)
// becomes null, so the walk stops at the first non-foot link. Written as a
// ternary the `object != 0` test lands as `CMP EAX,ECX; JZ ret` and the flag
// test as `TEST byte ptr [EAX+0x14],DL` (0x7104E0..0x7104E7).
static __inline FootClass* foot_cast_007104C0(void* object)
{
    return (object != 0 && ((AbstractClass*)object)->Flags.IsFoot)
               ? (FootClass*)object
               : 0;
}

#include "../combat/techno_class_ability_methods.h"

#include "../combat/techno_class_deactivate_methods.h"

#include "../combat/techno_class_reactivate_methods.h"

#include "../combat/techno_class_update_methods.h"

#include "../economy/building_class_drain.h"

#include "../_layout/foot_class.h"

#ifndef NULL
#define NULL 0
#endif

#include "../_layout/unit_class.h"

#include "../renderer/techno_class_drawer_methods.h"

// GLOBAL: GAMEMD 0xA83D4C
House_00705D70* DAT_00A83D4C;
// GLOBAL: GAMEMD 0xB054D0
ColorSchemeVec_00705D70 DAT_00B054D0;

// FUNCTION: GAMEMD 0x6F28D0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_006F28D0()
{
    DAT_00B0EB28 = DAT_00B0EA58 / DAT_007F4880;
}

// FUNCTION: GAMEMD 0x6F28F0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_006F28F0()
{
    DAT_00B0EB10 = DAT_007E1718 / DAT_00B0EB28;
}

// FUNCTION: GAMEMD 0x6F2A70
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_006F2A70()
{
    DAT_00B0EB20 = 0;
    DAT_00B0EB18 = 0x80;
    DAT_00B0EB1C = 0x80;
}

// FUNCTION: GAMEMD 0x6F32D0
// Alive, out of limbo, in the playfield, not of kind 6, discovered by the
// current player, of a selectable type, and owned by the current player.
bool TechnoClass::vf_25()
{
    return Health > 0 && !InLimbo && IsInPlayfield && vf_11() != 6
        && DiscoveredByCurrentPlayer && vf_33()->Selectable
        && Owner->IsControlledByCurrentPlayer();
}

// FUNCTION: GAMEMD 0x6F3820
// -1, 0 or 1 for another techno, by this type's NavalTargeting mode and the
// other type's Underwater, SpeedType and two other flags. -1 when the other
// object is missing or not a techno.
int TechnoClass::vf_186(TechnoClass* other)
{
    if (other == 0 || !other->Flags.IsTechno) {
        return -1;
    }
    bool underwater = other->vf_33()->Underwater;
    bool flag_D97 = other->vf_33()->bools_D94[0xD97 - 0xD94];
    bool speed3 = other->vf_33()->SpeedType == 3;
    bool unnatural = other->vf_33()->Unnatural;

    switch (vf_33()->NavalTargeting) {
    case 0:
        if (underwater && other->CloakState != 0) {
            return -1;
        }
        break;
    case 1:
        return underwater != 0;
    case 2:
        return underwater ? 0 : -1;
    case 3:
        if (flag_D97 || unnatural) {
            return 1;
        }
        break;
    case 4:
        if (!speed3 && !flag_D97) {
            return 1;
        }
        break;
    case 5:
        return 0;
    case 6:
        return -1;
    case 7:
        return 0;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6F3950
int TechnoClass::vf_180()
{
    return vf_33()->Crewed != 0;
}

// FUNCTION: GAMEMD 0x6F3970
//
// The damage one weapon does, or, asked about no weapon in particular, the
// average over the weapons this object actually carries. A burst-firing
// type that is not itself a gattling reports only the weapon its current
// stage selects.
//
// PARTIAL (24.4%, up from 6.5%; 120 instructions against retail's 123).
// The lever was block placement, not phrasing: retail tests `which != -1`
// and jumps AWAY to the single-weapon path, so the all-weapons body is the
// fallthrough and the single-weapon body sits at the end of the function.
// Writing the guard the other way round (`if (which != -1) { ...; return
// total; }` first) puts the short arm inline and shifts all 120 instructions.
// Inverting it to `if (which == -1) { ...big...} ` with the single-weapon
// tail trailing reproduces retail's own layout and every call, guard and
// accumulation lines up.
//
// Residual, and it is two separate 8447-vs-8804 backend differences:
//   * retail DUPLICATES the averaging tail into the burst arm and divides by
//     a register holding one (`MOV EBX,1; ... CDQ; IDIV EBX`); cl 8804
//     propagates the constant into the division and deletes it. Measured:
//     a per-arm `return total / count;` costs an extra zero-return block and
//     scores 23.4%; one shared tail keeps 24.4% and is kept.
//   * retail reaches the zero return with `TEST EBX,EBX; JLE` backwards to a
//     shared `XOR EAX,EAX` block placed inline in the burst arm; cl inlines
//     its own zero return at the test and jumps over it with `JG`. Routing
//     both zero exits through one `goto zero;` label makes cl merge the burst
//     arm's two zero blocks as well and loses three more instructions
//     (21.1% / 22.0% over three label placements), so the guards stay
//     separate.
int Techno_006F3970::CombatDamage(int which)
{
    int total = 0;

    if (which == -1) {
        int count = 0;
        if (FUN_00717880((this->*Vptr->GetTechnoType)())
            && (this->*Vptr->GetTechnoType)()->IsGattling == 0) {
            Weapon_006F3970* weapon = (this->*Vptr->GetWeapon)(GattlingStage);
            if (weapon == 0) {
                return 0;
            }
            WeaponType_006F3970* type = weapon->Type;
            if (type == 0) {
                return 0;
            }
            total = type->Damage + type->At_98;
            count = 1;
        } else {
            if ((this->*Vptr->GetWeapon)(0)->Type != 0) {
                total = (this->*Vptr->GetWeapon)(0)->Type->Damage;
                count = 1;
                total += (this->*Vptr->GetWeapon)(0)->Type->At_98;
            }
            if ((this->*Vptr->GetWeapon)(1)->Type != 0) {
                total += (this->*Vptr->GetWeapon)(1)->Type->Damage;
                total += (this->*Vptr->GetWeapon)(1)->Type->At_98;
                count++;
            }
            if (count <= 0) {
                return 0;
            }
        }
        return total / count;
    }

    if ((this->*Vptr->GetWeapon)(which)->Type != 0) {
        total = (this->*Vptr->GetWeapon)(which)->Type->Damage;
        total += (this->*Vptr->GetWeapon)(which)->Type->At_98;
    }
    return total;
}

// FUNCTION: GAMEMD 0x6F4960
// Mark this object discovered by a house. Returns false when it already was
// or the base refuses; a computer house's discovery can switch a mission 14
// object to mission 15, and the current player's fires tag event 4 and flags
// the owner's power and radar for a recheck.
bool TechnoClass::vf_102(HouseClass* house)
{
    if (house == CurrentPlayer) {
        if (DiscoveredByCurrentPlayer) {
            return false;
        }
    } else {
        if (DiscoveredByComputer) {
            return false;
        }
        DiscoveredByComputer = true;
    }
    if (!ObjectClass::vf_102(house)) {
        return false;
    }
    if (!house->IsControlledByHuman() && vf_97() == 14) {
        vf_122(15, false);
    }
    if (house == CurrentPlayer) {
        DiscoveredByCurrentPlayer = true;
        Owner->RecheckPower = true;
        Owner->RecheckRadar = true;
        if (!IsOwnedByCurrentPlayer) {
            if (!DAT_00A8E7AC && AttachedTag) {
                AttachedTag->FUN_006E53A0(4, this, DAT_00B0EA50, false, 0);
            }
            Owner->DiscoveredByPlayer = true;
        }
    } else {
        DiscoveredByComputer = true;
    }
    return true;
}

// FUNCTION: GAMEMD 0x6F4A40
void TechnoClass::vf_71()
{
    if (this->DiscoveredByCurrentPlayer) {
        if (!this->Owner->IsControlledByHuman()) {
            this->DiscoveredByCurrentPlayer = false;
        }
    }
}

// FUNCTION: GAMEMD 0x6F60C0
// Empty function that pops its stack arguments. Vtable slot 274 of TechnoClass (RTTI) and 5 derived vtable(s).
void Obj_006F60C0::FUN_006F60C0(int a1, int a2)
{
}

// FUNCTION: GAMEMD 0x6F7780  (__thiscall)
// Is the target inside the range of the weapon this object would pick for it?
// One weapon selection feeding one range test, both on the same cached vtable.
bool TechnoClass::IsCloseEnoughToAttack(AbstractClass* target)
{
    return vf_234(target, vf_185(target));
}

// FUNCTION: GAMEMD 0x6F7930
void TechnoClass::vf_236(CoordStruct* a1)
{
    CellClass* cell = MapClass_Instance.GetTargetCell(*a1);
    this->vf_234(cell, this->vf_185(cell));
}

// FUNCTION: GAMEMD 0x6F9DB0
// Member getter (dword). Vtable slot 14 of TechnoClass (RTTI) and 5 derived vtable(s).
int Obj_006F9DB0::FUN_006F9DB0() const
{
    return unknown_21C->unknown_30;
}

// FUNCTION: GAMEMD 0x6F9DC0
// Member getter (dword). Vtable slot 15 of TechnoClass (RTTI) and 5 derived vtable(s).
int Obj_006F9DC0::FUN_006F9DC0() const
{
    return unknown_21C;
}

// FUNCTION: GAMEMD 0x6FB080
//
// (Re)arm the reload countdown when the clip is not full. An empty clip with a
// distinct EmptyReload uses that; otherwise the delay is Reload plus
// ReloadIncrement scaled by the square of how many pip-wraps are loaded (one
// when the type does not wrap).
//
// The type is fetched through the virtual before every read, as retail does,
// and the timer is rewritten as a whole-struct copy of a fresh temporary, so
// the clock slot in the middle carries an uninitialised stack dword.
//
// Two named locals are load-bearing: the type's Ammo is bound before the
// compare so the techno's Ammo is read after the call (a single expression
// hoists the member load above the call into EDI and adds a push/pop pair),
// and the increment product is bound before the sum so the add lands in the
// Reload register (`ADD EAX,EDI`) rather than the product's.
void Techno_006FB080::StartReloading()
{
    int full = (this->*this->Vtbl->GetTechnoType)()->Ammo;
    if (this->Ammo < full) {
        if (this->Ammo == 0
            && (this->*this->Vtbl->GetTechnoType)()->EmptyReload != -1) {
            this->ReloadTimer =
                CDTimer_006FB080((this->*this->Vtbl->GetTechnoType)()->EmptyReload);
            return;
        }

        int wraps;
        if ((this->*this->Vtbl->GetTechnoType)()->PipWrap == 0) {
            wraps = 1;
        } else {
            wraps = this->Ammo / (this->*this->Vtbl->GetTechnoType)()->PipWrap;
        }

        int extra = (this->*this->Vtbl->GetTechnoType)()->ReloadIncrement * wraps * wraps;
        this->ReloadTimer = CDTimer_006FB080(
            (this->*this->Vtbl->GetTechnoType)()->Reload + extra);
    }
}

// FUNCTION: GAMEMD 0x6FC090
// Calls other functions. Vtable slot 239 of TechnoClass (RTTI) and 5 derived vtable(s).
void Obj_006FC090::FUN_006FC090(int a1, int a2)
{
    vf_240(a1, a2, 0);
}

// FUNCTION: GAMEMD 0x6FF950
// Empty function.
void __cdecl FUN_006FF950()
{
}

// FUNCTION: GAMEMD 0x7010D0  (__thiscall)
// Is this object sitting on guard with a usable weapon, for the local player?
// Four gates: not switched off, owned by the house the human is playing,
// holding a turret weapon with a real WeaponType behind it, and not currently
// EMP-locked.
//
// The exit is `MOV AL,0x1` / `XOR AL,AL`, so the return type is bool.
//
// LEVER: the gates have to be NESTED with `return false` as the function's
// trailing fall-through, not written as four early `return false`s. Spelled as
// early returns the last gate folds into `TEST AL,AL; SETE AL` and the
// materialised `MOV AL,0x1` disappears (59.3%); inverting only the last gate
// does not help, because cl folds whichever negated test ends the function.
bool TechnoClass::vf_39()
{
    if (!this->Deactivated) {
        if (this->Owner->IsControlledByCurrentPlayer()) {
            WeaponStruct* weapon = GetPrimaryWeapon();
            if (weapon != 0 && weapon->WeaponType != 0) {
                if (!IsUnderEMP()) {
                    return true;
                }
            }
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x701120  (__thiscall)
// Does this object have a weapon at all? The turret-weapon slot has to hand
// back a record, and the record has to name a WeaponType.
//
// The exit is `MOV EAX,0x1` / `XOR EAX,EAX` — five-byte immediate into the full
// register — so the return type is int, not bool. See the header note: the
// vtable map calls this slot `-> bool`, and the bytes say otherwise.
int TechnoClass::IsArmed()
{
    WeaponStruct* weapon = GetPrimaryWeapon();

    if (weapon != 0 && weapon->WeaponType != 0) {
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x701190
// Returns a constant boolean. Vtable slot 212 of TechnoClass (RTTI) and 4 derived vtable(s).
bool Obj_00701190::FUN_00701190() const
{
    return false;
}

// FUNCTION: GAMEMD 0x7013A0
void TechnoClass::vf_125(int mission, int a2, int a3)
{
    this->LastTarget = this->Target;
    MissionClass::vf_125(mission, a2, a3);
    this->vf_242(a2);
}

// FUNCTION: GAMEMD 0x7018C0
void TechnoClass::FUN_007018C0(HouseClass* house)
{
    this->Owner = house;
    this->IsOwnedByCurrentPlayer = (house == CurrentPlayer && CurrentPlayer != 0);
}

// FUNCTION: GAMEMD 0x703590
//
// A free cell near an object (or near this techno when none is given) that
// this techno's speed and movement zone can use. Amphibious speed is treated
// as wheeled; the zone type is looked up first, or -1 when the type has no
// zone.
//
// PARTIAL (52.9%, 55/104). The body between the speed test and the zone
// lookup is byte-exact once the cell comes from a by-value inline helper
// (two copies of the divide, each ending in a dword load of the temporary
// in the parameter slot, one shared store to the named cell). The residual
// is retail's constant handling in the final call: it keeps zero in EBP
// from the object null test (`XOR EBP,EBP; CMP ECX,EBP`) and spends it on
// the two trailing bool pushes and the word stores of the close-to cell
// (built late, in the parameter slot, as the thirteenth argument), then
// holds the repeated 1 in ECX/EDX (`MOV ECX,1; MOV EDX,ECX`) and pushes
// the registers; cl 8804 tests the pointer against itself, stores the zero
// words as immediates and pushes every constant as an immediate, which
// also drops the EBP save. The same materialised-constant shape appears at
// every retail NearByLocation call site (0x4FBF60, 0x41A2C0) and is
// recorded as a suspected 8447-vs-8804 difference. Tried: close-to cell
// declared at the top (kept), after the cell, after the zone lookup; as a
// two-argument constructor temporary and as an inline zero helper in the
// argument list; the by-value NearByLocation wrapper (homes the bool
// argument in a byte slot and reloads it as a dword); bool member passed
// with and without `!= 0`.
Cell_00703590 Obj_00703590::NearbyLocation(Obj_00703590* object)
{
    int speed = (this->*Vptr->GetTechnoType)()->SpeedType;
    if (speed == 4) {
        speed = 1;
    }
    Cell_00703590 closeTo;
    closeTo.X = 0;
    closeTo.Y = 0;

    Cell_00703590 cell;
    Coord_00703590 buf;
    if (object != 0) {
        cell = CoordToCell_00703590((object->*object->Vptr->GetCoords)(&buf));
    } else {
        cell = CoordToCell_00703590((this->*Vptr->GetCoords)(&buf));
    }

    int zone = (this->*Vptr->GetTechnoType)()->MovementZone;
    int zoneType;
    if (zone != -1) {
        zoneType = MapInstance_00703590.GetMovementZoneType(cell, zone, OnBridge);
    } else {
        zoneType = -1;
    }

    Cell_00703590 out;
    return *MapInstance_00703590.NearByLocation(&out, cell, speed, zoneType, zone,
                                                OnBridge, 1, 1, false, false,
                                                false, true, closeTo, false, false);
}

// FUNCTION: GAMEMD 0x703850
// Calls other functions. Vtable slot 63 of TechnoClass (RTTI) and 5 derived vtable(s).
void Obj_00703850::FUN_00703850()
{
    vf_279(0);
}

// FUNCTION: GAMEMD 0x705CA0
CoordStruct TechnoClass::vf_267()
{
    if (this->vf_97() == 1 && this->Target != 0) {
        return this->Target->vf_22();
    }
    return this->Location;
}

// FUNCTION: GAMEMD 0x00705D10
//
// Store the argument into the member at +0x514.
void Setter_00487C70::FUN_00705D10(int value)
{
    *(int*)(Bytes + 0x514) = value;
}

// FUNCTION: GAMEMD 0x00705D20
int FUN_00705D20(Obj_00705D20* self)
{
    return self->unknown_514;
}

// FUNCTION: GAMEMD 0x705D30
// Branching.
unsigned char Obj_00705D30::FUN_00705D30()
{
    if (unknown_514 == 0)
    {
        return 0;
    }
    return (unknown_514->FUN_00636DC0() > 0) ? true : false;
}

// FUNCTION: GAMEMD 0x705D50
// Calls other functions. Vtable slot 268 of TechnoClass (RTTI) and 4 derived vtable(s).
bool Obj_00705D50::FUN_00705D50()
{
    return (vf_118() == 0) ? true : false;
}

// FUNCTION: GAMEMD 0x705D60
void FUN_00705D60(void* self)
{
    FUN_006385C0(self);
}

// FUNCTION: GAMEMD 0x705D70
//
// Which house-colour remap table draws this object. A type with its own
// Palette= list supplies one ColorScheme per house, indexed by the owner's
// colour-scheme index. Otherwise the global ColorScheme array is used — for the
// owner, unless the local player cannot see through a disguise and the object
// is disguised as some house, in which case that house's colours are drawn.
// The disguise house is fetched twice rather than cached, as retail does.
LightConvertClass* Techno_00705D70::GetDrawer()
{
    TechnoType_00705D70* type = (this->*(*(Vtbl_00705D70**)this)->At_084)();
    int index = ((House_00705D70*)this->Owner)->ColorSchemeIndex;

    if (type->Palette != 0) {
        return (*type->Palette)[index]->LightConvert;
    }

    if (!(this->*(*(Vtbl_00705D70**)this)->At_440)(DAT_00A83D4C)) {
        if ((this->*(*(Vtbl_00705D70**)this)->At_0D0)(1) != 0) {
            return DAT_00B054D0[(this->*(*(Vtbl_00705D70**)this)->At_0D0)(1)->ColorSchemeIndex]->LightConvert;
        }
    }

    return DAT_00B054D0[index]->LightConvert;
}

// FUNCTION: GAMEMD 0x707CB0  TechnoClass::KillPassengers (__thiscall, ret 0x4)
// Empty a transport by killing everything inside it. Each passenger is first
// released from its team, then unlinked, then recursively emptied itself — a
// transport carrying a transport unwinds all the way down — before being
// destroyed through its own two virtuals.
//
// The empty check is hoisted out and the body is a do/while: retail tests
// FirstPassenger (+0x118, the list head) once up front and again at the bottom
// of the loop, with the loop head at the GetFirstPassenger call rather than at
// the test.
void TechnoClass::KillPassengers(TechnoClass* source)
{
    if (Passengers.FirstPassenger == 0)
        return;

    do
    {
        FootClass* first = Passengers.GetFirstPassenger();
        if (first->Team != 0)
            first->Team->LiberateMember(first, -1, 0);

        FootClass* passenger = Passengers.RemoveFirstPassenger();
        if (passenger != 0)
        {
            // Retail passes the passenger itself here, not `source`
            // (`PUSH ESI; MOV ECX,ESI; CALL 0x707CB0`); only the outer
            // virtual at +0xE0 receives the original killer.
            passenger->KillPassengers(passenger);
            passenger->vf_56(source);
            passenger->vf_62();
        }
    }
    while (Passengers.FirstPassenger != 0);
}

// FUNCTION: GAMEMD 0x708D70
DirStruct TechnoClass::vf_194()
{
    return this->vf_170();
}

// FUNCTION: GAMEMD 0x708D90
void TechnoClass::vf_213(int a1)
{
    if (DAT_00822CF2 && a1 != -1 && this->Owner->IsControlledByCurrentPlayer()) {
        this->QueuedVoiceIndex = a1;
    }
}

// FUNCTION: GAMEMD 0x7091D0
//
// Whether this object may pick up targets of its own accord. A chain of
// rejections: while warping something out, while enslaved, when the type
// forbids it, when an occupiable building has no occupants, when a human-owned
// object of the kind that defers to the player, when captured beyond control;
// then only an armed object says yes.
//
// Written as one &&-chained precondition with the ||-chained building exemption
// nested inside and a single trailing `return false`: that is what gives retail
// its one shared `XOR AL,AL` tail. A ladder of `if (...) return false;` gives
// every rejection its own pop/xor/ret block (7.3%). The captured flag is a
// named bool (BL) computed before the ownership test.
bool Obj_007091D0::CanPassiveAcquireTargets()
{
    if (!(this->*this->Vtbl->At_1DC)()
        && this->SlaveOwner == 0
        && (this->*this->Vtbl->GetTechnoType)()->At_D99 != 0
        && ((this->*this->Vtbl->WhatAmI)() != 6
            || this->BuildingType->At_157B == 0
            || (this->*this->Vtbl->At_408)() != 0))
    {
        bool captured = this->CaptureManager != 0
                        && this->CaptureManager->CannotControlAnyMore();

        if ((!(this->*this->Vtbl->At_330)() || !this->Owner->IsControlledByHuman())
            && !captured
            && (this->*this->Vtbl->At_2AC)())
        {
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x709460
// Branching.
int __stdcall FUN_00709460(int a1)
{
    return a1 != 5 && a1 != 6 && a1 != 8;
}

// FUNCTION: GAMEMD 0x7094E0
// Branching.
int Obj_007094E0::FUN_007094E0()
{
    return unknown_AC == 2 || unknown_AC == 0xA || unknown_AC == 5;
}

// FUNCTION: GAMEMD 0x709500
int TechnoClass::FUN_00709500()
{
    int mission = this->CurrentMission;
    if (mission == 0 || mission == 7 || mission == 13 || mission == 14 || mission == 16
        || mission == 18 || mission == 19 || mission == 20 || mission == 22 || mission == 23
        || mission == 28 || mission == 24) {
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x709800
// Branching.
int __stdcall FUN_00709800(int a1)
{
    return a1 != 5 && a1 != 6;
}

// FUNCTION: GAMEMD 0x7099D0
// Returns zero; pops its stack arguments. Vtable slot 64 of TechnoClass (RTTI) and 3 derived vtable(s).
int Obj_007099D0::FUN_007099D0(int a1, int a2) const
{
    return 0;
}

// FUNCTION: GAMEMD 0x709A20
// Empty function that pops its stack arguments. Vtable slot 287 of TechnoClass (RTTI) and 1 derived vtable(s).
void Obj_00709A20::FUN_00709A20(int a1)
{
}

// FUNCTION: GAMEMD 0x70AD50
CellStruct TechnoClass::vf_191(AbstractClass* a1, int a2)
{
    return CoordToCell(this->vf_42(a1));
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70C5A0  (__thiscall)
// Can this object cloak? The flag is a byte, and the `TEST AL,AL; SETNZ AL`
// normalisation is the char-to-bool conversion — a member already declared
// bool would return with a bare `MOV AL,[..]; RET`, which is exactly what the
// neighbouring accessor at 0x70C5B0 does.
//
// LEVER, measured over nine spellings in one probe compile: `return C != 0;`,
// the same through a named `unsigned char` local, a `char` member, an `int`
// member, and `char`/`int` return types ALL emit `MOV DL,[..]; XOR EAX,EAX;
// TEST DL,DL; SETNE AL` — five instructions against retail's four, because cl
// takes a fresh register and zeroes EAX. Only the two branching forms —
// `C ? true : false` and the explicit `if` below — reuse AL and reach retail's
// exact four. This is the concrete case behind the "never write
// `return a == b;`" rule: the bare comparison costs the zeroing instruction.
bool TechnoClass::IsCloakable()
{
    if (this->Cloakable) {
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70C5B0
// Member getter (byte). Vtable slot 117 of TechnoClass (RTTI) and 5 derived vtable(s).
unsigned char Obj_0070C5B0::FUN_0070C5B0() const
{
    return unknown_270;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70C5C0
// Member getter (byte). Vtable slot 118 of TechnoClass (RTTI) and 5 derived vtable(s).
unsigned char Obj_0070C5C0::FUN_0070C5C0() const
{
    return unknown_271;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70C5D0
// Branching. Vtable slot 119 of TechnoClass (RTTI) and 5 derived vtable(s).
bool Obj_0070C5D0::FUN_0070C5D0()
{
    if (unknown_274 == 0 || unknown_274->unknown_28 == 0)
    {
        return false;
    }
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70C5F0
// Branching. Vtable slot 120 of TechnoClass (RTTI) and 5 derived vtable(s).
bool Obj_0070C5F0::FUN_0070C5F0()
{
    if (unknown_270 != 0 || unknown_271 != 0)
    {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x70CC90
void TechnoClass::vf_293()
{
    MapClass_Instance.FUN_00655560(this, this->RadarPosition);
    this->IsRadarTracked = true;
}

// FUNCTION: GAMEMD 0x70CCC0
void TechnoClass::vf_294()
{
    MapClass_Instance.FUN_00655740(this, this->RadarPosition);
    this->IsRadarTracked = false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70CCF0
// Calls other functions. Vtable slot 295 of TechnoClass (RTTI) and 4 derived vtable(s).
void FUN_0070CCF0(int a1, int a2)
{
    FUN_006562D0(DAT_0087F7E8, a2, a1 + 0x208);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70D0D0
//
// Does this object currently enjoy the given veteran/elite ability? Nothing
// below veteran rank has any. A veteran has the ability when its type grants it
// at the veteran tier; an elite has it when the type grants it at either tier
// (elite is a superset). The type is fetched through the GetTechnoType virtual
// only once a rank test has passed.
bool Techno_0070D0D0::HasAbility(int ability)
{
    VeterancyStruct* vet = &this->Veterancy;

    if (FUN_0074FF90(vet) || FUN_00750010(vet)) {
        TechnoType_0070D0D0* type = (this->*(*(Vtbl_0070D0D0**)this)->At_084)();

        if (FUN_0074FF90(vet) && type->VeteranAbilities[ability]) {
            return true;
        }
        if (FUN_00750010(vet)
            && (type->VeteranAbilities[ability] || type->EliteAbilities[ability])) {
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x70D150
void FUN_0070D150()
{
    CDTimerClass timer;
    timer.StartTime = CurrentFrame;
    timer.TimeLeft = 25;
    DAT_00B0EA80 = timer;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0070D180
void FUN_0070D180(char value)
{
    DAT_00843108 = value;
}

// FUNCTION: GAMEMD 0x70D190
int TechnoClass::vf_281(int a1)
{
    if ((this->DurationRemaining & 2) == 2) {
        return (a1 > 1500) ? 500 : 2000;
    }
    return a1;
}

// FUNCTION: GAMEMD 0x70D420
bool TechnoClass::vf_202()
{
    if (CurrentPlayer != 0) {
        CellClass* cell = MapClass_Instance.GetTargetCell(this->vf_18());
        return cell->FUN_004870D0(CurrentPlayer->ArrayIndex);
    }
    return false;
}

// FUNCTION: GAMEMD 0x70D460
bool TechnoClass::vf_203(HouseClass* a1)
{
    if (a1 != 0) {
        CellClass* cell = MapClass_Instance.GetTargetCell(this->vf_18());
        return cell->FUN_004870D0(a1->ArrayIndex);
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70D4A0  AbstractClass::BecomeUntargetable
//
// Nothing may keep pointing at this object. Every techno targeting it drops
// the target (an infantry mid-mission 0x19 also loses its sub-state), unless
// this is a live techno whose +0x294 link is owned by that techno. Then the
// two references in the second array are cleared. The null-safe techno view
// is an if/else with the null case first (retail's fall-through), then the
// branchless flag mask; `self = 0; if (this) ...` puts the XOR first (1.2%).
void Abstract_0070D4A0::BecomeUntargetable()
{
    Techno_0070D4A0* self;
    if (this == 0)
        self = 0;
    else
        self = (AbstractFlags & 1) ? (Techno_0070D4A0*)this : 0;

    for (int i = DAT_00A8EC88 - 1; i >= 0; --i) {
        Techno_0070D4A0* techno = DAT_00A8EC7C[i];
        bool drop = true;
        if (self != 0 && techno->At_294 != 0 && techno->At_294->At_50 == this
            && self->Health > 0 && self->At_90 != 0)
            drop = false;
        if (techno->Target == this && drop) {
            (techno->*techno->Vptr->At_1F8)();
            if ((techno->*techno->Vptr->WhatAmI)() == 2 && techno->CurrentMission == 0x19) {
                techno->At_BC = 0;
                techno->At_6D2 = 0;
            }
            if (techno->Target == this)
                (techno->*techno->Vptr->At_3C8)(0);
        }
    }

    for (int j = DAT_008B40F8 - 1; j >= 0; --j) {
        Ref_0070D4A0* ref = DAT_008B40EC[j];
        if (ref->At_3C == this)
            ref->At_3C = 0;
        if (ref->At_40 == this)
            ref->At_40 = 0;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70D670
// Branching. Vtable slot 228 of TechnoClass (RTTI) and 4 derived vtable(s).
int Obj_0070D670::FUN_0070D670()
{
    int t1 = unknown_2FC;
    if (t1 > 0)
    {
        unknown_2FC = t1 - 1;
        return t1 - 1;
    }
    return t1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70D980
// Empty function. Vtable slot 184 of TechnoClass (RTTI) and 4 derived vtable(s).
void Obj_0070D980::FUN_0070D980()
{
}

// FUNCTION: GAMEMD 0x70DC50
bool TechnoClass::FUN_0070DC50()
{
    return this->vf_33()->HasTurretTooltips;
}

// FUNCTION: GAMEMD 0x70DC60
bool TechnoClass::FUN_0070DC60()
{
    return this->vf_33()->FUN_00717880();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70DCE0
// Returns a comparison result.
bool Obj_0070DCE0::FUN_0070DCE0() const
{
    return unknown_124 != -1;
}

// FUNCTION: GAMEMD 0x70DD00
int TechnoClass::FUN_0070DD00()
{
    int changed = this->CurrentTurretNumber != this->unknown_int_128;
    this->unknown_int_128 = this->CurrentTurretNumber;
    return changed;
}

// FUNCTION: GAMEMD 0x70DD50
// The weapon-type byte at +0x150 of the weapon in slot 252, false when there is
// no weapon record or it names no type.
bool TechnoClass::vf_248()
{
    WeaponStruct* weapon = this->vf_252();
    if (weapon != 0 && weapon->WeaponType != 0) {
        return weapon->WeaponType->unknown_150;
    }
    return false;
}

// FUNCTION: GAMEMD 0x70DD70
int TechnoClass::vf_249()
{
    return !this->vf_33()->SprayAttack;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70DD90
// Returns a constant. Vtable slot 250 of TechnoClass (RTTI) and 5 derived vtable(s).
int Obj_0070DD90::FUN_0070DD90() const
{
    return 1;
}

// FUNCTION: GAMEMD 0x70DDA0
int TechnoClass::vf_251()
{
    return !this->vf_33()->SprayAttack;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70DE20
// Updates one member in place.
void Obj_0070DE20::FUN_0070DE20(int a1)
{
    unknown_144 += a1;
}

// FUNCTION: GAMEMD 0x70DE40
void TechnoClass::FUN_0070DE40(int a1)
{
    this->GattlingValue -= a1;
    if (this->GattlingValue < 0 || a1 == 0) {
        this->GattlingValue = 0;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70E000
//
// Spin the gattling gun down. The value drops by RateDown per tick and is
// clamped at zero; once both value and stage are zero any still-playing
// spin sounds are stopped. Otherwise the weapon for the current stage is
// re-selected and, when the value has fallen below the stage's threshold
// (elite or normal table), the stage steps down and the spin-down sound
// stops.
void Techno_0070E000::GattlingRateDown(int rate)
{
    GattlingSoundController.EndLooping();
    IsGattlingSoundPlaying = 0;

    int step = (this->*Vptr->GetTechnoType)()->RateDown * rate;
    GattlingValue -= step;
    if (GattlingValue < 0 || step == 0) {
        GattlingValue = 0;
    }

    int value = GattlingValue;
    int stage = CurrentGattlingStage;
    if (value == 0 && stage == 0) {
        if (IsUnusedGattlingSoundPlaying || IsGattlingSoundPlaying) {
            GattlingSoundController.FUN_00405D40();
            UnusedGattlingSoundController.FUN_00405D40();
            IsUnusedGattlingSoundPlaying = 0;
            IsGattlingSoundPlaying = 0;
        }
    } else {
        (this->*Vptr->GetWeapon)(stage * 2);
        if (stage > 0) {
            int threshold;
            if (FUN_00750010(&Veterancy)) {
                threshold = (this->*Vptr->GetTechnoType)()->EliteStage[stage - 1];
            } else {
                threshold = (this->*Vptr->GetTechnoType)()->WeaponStage[stage - 1];
            }
            if (value < threshold) {
                stage--;
                if (stage >= 0) {
                    CurrentGattlingStage = stage;
                }
                (this->*Vptr->GetWeapon)(stage * 2);
                UnusedGattlingSoundController.FUN_00405D40();
                IsUnusedGattlingSoundPlaying = 0;
            }
        }
    }
}

// FUNCTION: GAMEMD 0x70E120
WeaponStruct* TechnoClass::vf_252()
{
    return this->vf_254(this->vf_249());
}

// FUNCTION: GAMEMD 0x70E140
WeaponStruct* TechnoClass::vf_254(int a1)
{
    if (a1 == -1) {
        return 0;
    }
    if (this->Veterancy.FUN_00750010()) {
        WeaponStruct* weapon = this->vf_33()->GetEliteWeapon(a1);
        if (weapon != 0 && weapon->WeaponType != 0) {
            return weapon;
        }
    }
    return this->vf_33()->GetWeapon(a1);
}

// FUNCTION: GAMEMD 0x70E1E0
int TechnoClass::FUN_0070E1E0(int a1)
{
    bool low = a1 < 2;
    bool inRange = this->vf_33()->FUN_00717880() && a1 < this->vf_33()->WeaponCount;
    if (a1 >= -1 && (low || inRange)) {
        return 1;
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0070E240
// True when `slot` is non-null and holds a non-zero value.
int __stdcall FUN_0070E240(const int* slot)
{
    if (slot != NULL && *slot != 0) {
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x70E260
int TechnoClass::FUN_0070E260()
{
    WeaponStruct* weapon = this->GetPrimaryWeapon();
    if (weapon != 0 && weapon->WeaponType != 0) {
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x70E340
void TechnoClass::vf_86()
{
    CDTimerClass timer;
    timer.StartTime = CurrentFrame;
    timer.TimeLeft = 0;
    this->AirstrikeTimer = timer;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70ECE0  RecoilData::Fire  (__thiscall)
void RecoilData::Fire()
{
    int travel = this->Turret.Travel;
    if (travel != 0) {
        this->State = 1;
        this->TravelFramesLeft = this->Turret.CompressFrames;
        if (this->Turret.CompressFrames < 1) {
            this->TravelFramesLeft = 1;
        }
        this->TravelPerFrame = (float)travel / (float)this->TravelFramesLeft;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70ED10
//
// One frame of turret/barrel recoil. While a recoil is in progress the travel
// accumulates by the per-frame step and the frame countdown ticks; when it
// expires the state machine advances Compressing(1) -> Holding(2) ->
// Recovering(3) -> Inactive(0). Entering Holding zeroes the step and loads the
// hold count (a hold of <= 1 frame drops straight into Recovering); entering
// Recovering loads the recover count (clamped to at least 1) and sets the step
// to walk the full travel back over that many frames.
void RecoilData_0070ED10::Update()
{
    unsigned int state = this->State;

    if (state != 0) {
        this->TravelSoFar = this->TravelPerFrame + this->TravelSoFar;
        this->TravelFramesLeft = this->TravelFramesLeft - 1;

        if (this->TravelFramesLeft <= 0) {
            switch (state) {
            case 1:
                this->State = 2;
                this->TravelFramesLeft = this->Turret.HoldFrames;
                this->TravelPerFrame = 0.0f;
                if (this->TravelFramesLeft > 1) {
                    break;
                }
                // fall through
            case 2:
                this->State = 3;
                this->TravelFramesLeft = this->Turret.RecoverFrames;
                if (this->TravelFramesLeft < 1) {
                    this->TravelFramesLeft = 1;
                }
                this->TravelPerFrame = -((float)this->Turret.Travel / (float)this->TravelFramesLeft);
                break;
            case 3:
                this->State = 0;
                this->TravelSoFar = 0.0f;
                break;
            }
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70EFD0  (__thiscall)
// Is an EMP still holding this object down? `SETG` is the signed test, so the
// remaining-lock counter is a signed int.
bool TechnoClass::IsUnderEMP()
{
    return this->EMPLockRemaining > 0;
}

// FUNCTION: GAMEMD 0x70EFE0
int TechnoClass::vf_227()
{
    TechnoTypeClass* type = this->vf_33();
    if (type != 0) {
        return type->Speed;
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F000
// Member getter (byte sx); pops its stack arguments. Vtable slot 297 of TechnoClass (RTTI) and 1 derived vtable(s).
int Obj_0070F000::FUN_0070F000(Arg1_0070F000* a1) const
{
    return a1->unknown_0C;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F010
// Empty function. Vtable slot 298 of TechnoClass (RTTI) and 1 derived vtable(s).
void Obj_0070F010::FUN_0070F010()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F020
// Returns a constant boolean. Vtable slot 299 of TechnoClass (RTTI) and 1 derived vtable(s).
bool Obj_0070F020::FUN_0070F020() const
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F030
// Returns a constant boolean. Vtable slot 300 of TechnoClass (RTTI) and 1 derived vtable(s).
bool Obj_0070F030::FUN_0070F030() const
{
    return false;
}

// FUNCTION: GAMEMD 0x70F040
int TechnoClass::vf_301()
{
    return -1;
}

// FUNCTION: GAMEMD 0x70F050
CoordStruct TechnoClass::vf_302()
{
    CoordStruct coord;
    coord.X = -1;
    coord.Y = -1;
    coord.Z = -1;
    return coord;
}

// FUNCTION: GAMEMD 0x70F070
bool TechnoClass::vf_303()
{
    return this->vf_33()->vf_40();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F090  (__thiscall)
// Forwarded wholesale to the type: the object asks what it is, then asks the
// type whether that kind of thing may fire while moving. Retail tail-jumps
// (`JMP [EDX+0xa4]`) rather than calling, which is what cl emits when the
// dispatch is the whole return expression.
bool TechnoClass::CanAttackOnTheMove()
{
    TechnoTypeClass* type = vf_33();

    return type->vf_41();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F0B0
//
// Map a locomotor kind onto its expansion replacement. Only two kinds are
// remapped, and only while the expansion's rule set is active; everything
// else is handed back unchanged.
int FUN_0070F0B0(int kind, int, int)
{
    bool expansion = FUN_00731BF0();
    if (kind == 1) {
        if (expansion) {
            return 0x3E;
        }
    } else if (kind == 5) {
        if (expansion) {
            return 0x3F;
        }
    }
    return kind;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F0E0
// Returns a constant boolean. Vtable slot 305 of TechnoClass (RTTI) and 1 derived vtable(s).
bool Obj_0070F0E0::FUN_0070F0E0() const
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F0F0
// Returns a constant boolean. Vtable slot 306 of TechnoClass (RTTI) and 1 derived vtable(s).
bool Obj_0070F0F0::FUN_0070F0F0() const
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F100
// Empty function. Vtable slot 307 of TechnoClass (RTTI) and 1 derived vtable(s).
void Obj_0070F100::FUN_0070F100()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F110
// Returns a constant boolean. Vtable slot 308 of TechnoClass (RTTI) and 1 derived vtable(s).
bool Obj_0070F110::FUN_0070F110() const
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F670
//
// Add this object's current contribution to the mover, remembering what was
// contributed so the undo below can take exactly that much back out.
void VelocitySource_0070F670::ApplyVelocity(Mover_0070F670* mover)
{
    if (mover != 0) {
        int amount = (this->*this->Vtbl->CurrentContribution)();
        this->Contribution = amount;
        mover->Accumulate((this->*this->Vtbl->Convert)(amount));
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F6A0
//
// Take the remembered contribution back out of the mover and forget it.
void VelocitySource_0070F670::RemoveVelocity(Mover_0070F670* mover)
{
    if (mover != 0) {
        int amount = -this->Contribution;
        mover->Accumulate((this->*this->Vtbl->Convert)(amount));
        this->Contribution = 0;
    }
}

// FUNCTION: GAMEMD 0x70F740
void TechnoClass::FUN_0070F740(int a1)
{
    CDTimerClass timer;
    timer.StartTime = CurrentFrame;
    timer.TimeLeft = a1;
    this->TargetingTimer = timer;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70F850  (__thiscall)
// Drop everything and go idle: clear the movement destination, clear the combat
// target, forget the archived target, and force the object into mission 5.
void TechnoClass::CancelAndGoIdle()
{
    SetDestination(0, true);
    vf_242(0);
    this->ArchiveTarget = 0;
    vf_124(5);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// The redraw is ObjectClass primary slot 73 (vtable offset 0x124), called with 2.
// FUNCTION: GAMEMD 0x70FBD0  (__thiscall)
// Retail loads the raw bool byte straight into AL with no 0/1 normalisation, so
// read it as a bool lvalue (`mov al,[ecx+0x1c8]; ret`), not via the unsigned-char
// member (which would force a `test`/`setne`).
bool UnitClass::IsDeactivated() const
{
    return *(const bool*)&Deactivated;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70FBE0
//
// Reset through the +0x3D0 virtual first. If this object is a FootClass
// (AbstractFlags bit 2), power its locomotor back on through the COM slot at
// +0x58 — the null check and E_POINTER report are the smart-pointer dereference
// inlined. Then, if it was deactivated and its type names an ActivateSound,
// play that sound at the object's own location; finally clear Deactivated.
//
// Two phrasings matter. The Deactivated test and the sound-index test are one
// `&&` condition: split into nested `if`s VC6 loads the GetTechnoType() vtable
// pointer into EAX where retail has EDX (and shifts the coordinate-copy
// registers with it) — a pure register-naming diff at 76.5%. And the vtable
// pointer is re-read at every virtual call rather than held in a local;
// GetTechnoType() is called twice (once to test, once to fetch), as retail does.
// These casts express the binary's zero-offset AbstractClass/ObjectClass views.
// The shared spine models public inheritance; these casts do not establish
// any additional hierarchy.
void TechnoReactivate::Reactivate()
{
    (this->*(*(ReactVtbl**)this)->At_3D0)();

    if (this != 0 && (((AbstractClass*)(void*)this)->Flags.IsFoot))
    {
        FootClass* foot = (FootClass*)this;
        if (foot->Locomotor == 0)
            FUN_007DC720(0x80004003);
        LOCO_CALL0((ILocomotion*)foot->Locomotor, 0x58);
    }

    if (this->Deactivated
        && (this->*(*(ReactVtbl**)this)->GetTechnoType)()->ActivateSound != -1)
    {
        CoordStruct crd = ((ObjectClass*)(void*)this)->Location;
        VocClass_PlayAt((this->*(*(ReactVtbl**)this)->GetTechnoType)()->ActivateSound, &crd, 0);
    }

    this->Deactivated = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70FC90
//
// Power the object down. When the +0x418 flag is set and the probe agrees,
// an object sitting on this cell that is the probe's own answer means there
// is nothing to do. Otherwise go through the +0x3D0 and +0x150 virtuals, cut a
// FootClass's locomotor through its COM slot +0x5C (smart-pointer null check
// and E_POINTER inlined), play the type's deactivate sound at the object's
// location if it was not already off, and set Deactivated.
void TechnoDeactivate::Deactivate()
{
    if (this->IsTether && this->FUN_0065AD30(0)) {
        TechnoDeactivate* occupant = (this->*(*(DeactVtbl**)this)->GetCell)()->FUN_0047C520();
        if (occupant == (TechnoDeactivate*)this->FUN_0065AD30(0))
            return;
    }

    (this->*(*(DeactVtbl**)this)->At_3D0)();
    (this->*(*(DeactVtbl**)this)->At_150)();

    if (this != 0 && (((AbstractClass*)(void*)this)->Flags.IsFoot))
    {
        FootClass* foot = (FootClass*)this;
        if (foot->Locomotor == 0)
            FUN_007DC720(0x80004003);
        LOCO_CALL0_DEACT((ILocomotion*)foot->Locomotor, 0x5C);
    }

    if (!this->Deactivated
        && (this->*(*(DeactVtbl**)this)->GetTechnoType)()->DeactivateSound != -1)
    {
        CoordStruct crd = ((ObjectClass*)(void*)this)->Location;
        VocClass_PlayAt((this->*(*(DeactVtbl**)this)->GetTechnoType)()->DeactivateSound, &crd, 0);
    }

    this->Deactivated = 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70FD70
//
// Begin draining the given target: link the two objects together, mark the
// target's owner, release whatever the target was holding, spawn the drain
// animation and attach it, then refresh this object's display.
//
// The display refresh is a thiscall: retail loads the display pointer from
// this+0x5D4 into ECX and passes owner, -1 and 1 on the stack. Modelling it
// as a free stdcall function omitted the display receiver.
void Drainer_0070FD70::BeginDraining(Target_0070FD70* target)
{
    if (target == 0) {
        return;
    }
    if (FUN_0047C520((this->*this->Vtbl->OccupiedCell)()) != target) {
        return;
    }

    target->DrainedBy = this;
    this->DrainingWhom = target;
    target->Owner->IsDraining = 1;

    if (target->Buffer != 0) {
        FUN_00472140(target->Buffer);
    }

    void* raw = gg_operator_new(0x1C8);
    Anim_0070FD70* anim;
    if (raw != 0) {
        anim = ((Anim_0070FD70*)raw)->Construct(
            RulesInstance->DrainAnim,
            (this->*this->Vtbl->BuildCoord)(0, 1, 0x600, 0, 0));
    } else {
        anim = 0;
    }

    this->DrainAnim = anim;
    if (anim != 0) {
        anim->Attach(this);
    }

    if (this != 0 && (this->Flags & 4) != 0) {
        Display_0070FD70* display = this->Display;
        if (display != 0) {
            display->Refresh(this, -1, 1);
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70FE40
// Stores its argument in a member; pops its stack arguments.
void Obj_0070FE40::FUN_0070FE40(int a1)
{
    unknown_1D0 = a1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70FEB0
//
// Is this object draining another. The twin at 0x70FEC0, already matched in
// match/economy/building_class_drain.cpp, asks the same question of the other
// end of the link.
bool LocoObject_0070FEB0::IsDraining() const
{
    return this->DrainingWhom != 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70FEC0  (__thiscall)
//
// Retail body (len 0xE):
//   MOV  EDX,[ECX+0x1d0]   ; DrainingMe
//   XOR  EAX,EAX
//   TEST EDX,EDX
//   SETNZ AL
//   RET
//
// i.e. `return DrainingMe != 0;` — boolean of a pointer null test, which cl
// lowers to the xor/test/setnz tail above.
bool BuildingClass::IsBeingDrained() const
{
    return this->DrainingMe != 0;
}

// FUNCTION: GAMEMD 0x70FED0
bool TechnoClass::FUN_0070FED0()
{
    return this->vf_33()->Drainable;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x70FEE0
//
// Drop the object this techno's locomotor is carrying. A carried foot unit
// still in the air is marked crashing and manipulated by this techno's
// owner, told to forget its target and destination; one on the ground is
// simply let go. Either way the link is cleared and, on request, so is
// this techno's own target.
void Techno_0070FEE0::ReleaseLocomotor(bool clearTarget)
{
    if (LocomotorTarget != 0) {
        LocomotorTarget->LocomotorSource = 0;
        if (LocomotorTarget != 0 && (LocomotorTarget->AbstractFlags & 4)) {
            if ((LocomotorTarget->*LocomotorTarget->Vptr->GetHeight)() > 0) {
                LocomotorTarget->IsCrashing = 1;
                LocomotorTarget->IsBeingManipulated = 1;
                LocomotorTarget->BeingManipulatedBy = this;
                LocomotorTarget->ChronoWarpedByHouse = Owner;
                (LocomotorTarget->*LocomotorTarget->Vptr->At_3A0)();
                (LocomotorTarget->*LocomotorTarget->Vptr->SetDestination)(0, true);
                LocomotorTarget = 0;
                if (clearTarget) {
                    (this->*Vptr->SetTarget)(0);
                }
                return;
            }
            (LocomotorTarget->*LocomotorTarget->Vptr->SetDestination)(0, true);
            Techno_0070FEE0* foot;
            if (LocomotorTarget == 0) {
                foot = 0;
            } else {
                foot = (LocomotorTarget->AbstractFlags & 4) ? LocomotorTarget : 0;
            }
            foot->IsLetGoByLocomotor = 1;
            (LocomotorTarget->*LocomotorTarget->Vptr->SetDestination)(0, true);
        }
        LocomotorTarget = 0;
        if (clearTarget) {
            (this->*Vptr->SetTarget)(0);
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x710410
//
// Forget the item wherever this holder still refers to it, then pass it on to
// the shared release helper.
void Holder_00710410::FUN_00710410(void* item)
{
    if (item == this->RefA) {
        this->RefA = 0;
    }
    if (item == this->RefB) {
        this->RefB = 0;
    }
    if (item == this->RefC) {
        this->RefC = 0;
    }
    if (item == this->RefD) {
        this->RefD = 0;
    }
    FUN_005F6DA0(item);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x710460
//
// Release the waypoint buffer if one is held. Retail tail-jumps into the
// release helper with the buffer already in the receiver register.
void LocoObject_0070FEB0::FreeWaypointBuffer()
{
    if (this->WaypointBuffer != 0) {
        FUN_00472140(this->WaypointBuffer);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7104C0  TechnoClass::MarkPassengersAsExited (__thiscall)
// Walk the cargo chain clearing the open-topped flag, stopping at the first
// link that is not a foot-class object (the +0x14 flag word, mask 4). The chain
// is the shared object list, so the type test is what bounds it.
//
// The loop is a top-tested `while (passenger != 0)` whose body guards the
// store with its own `if (passenger != 0)` and advances through the checked
// cast. Retail keeps the body's guard (`CMP EAX,ECX; JZ 0x7104DD`) even
// though the cast has just proved it; VC6 keeps it too once the advance is
// the ternary cast above — the earlier do/while spellings with the null test
// in the loop condition let the optimiser delete it (33.3%).
void TechnoClass::MarkPassengersAsExited()
{
    FootClass* passenger = Passengers.GetFirstPassenger();
    while (passenger != 0)
    {
        if (passenger != 0)
            passenger->InOpenToppedTransport = false;
        passenger = foot_cast_007104C0(passenger->NextObject);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7104F0  (__thiscall)
// Snap every passenger's Location to the transport's own Location. Walks the
// passenger linked list (first via Passengers.GetFirstPassenger, thereafter via
// NextObject) while each node carries AbstractFlags bit 0x4.
//   CALL 0x473450 ; copy this->Location -> stack coord ; CALL [vtbl+0x1B4] per node
void FootClass::UpdatePassengerCoords()
{
    ObjectClass* p = this->Passengers.GetFirstPassenger();
    CoordStruct crd = this->Location;
    if (p != NULL)
    {
        do
        {
            p->vf_109(crd);
            p = (ObjectClass*)p->NextObject;
        }
        while (p != NULL && p->Flags.IsFoot);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x710600
//
// May this object fire while on the ground: it must be of the first kind, and
// its type must not carry the blocking flag.
int LocoObject_0070FEB0::CanFireFromGround()
{
    if ((this->*this->Vtbl->WhatAmI)() == 1) {
        if ((this->*this->Vtbl->GetType)()->Flag_D97 == 0) {
            return 1;
        }
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x710630
//
// May this object fire at all: the fifteenth kind always may, the first kind
// may only when its type carries the flag, and nothing else may.
//
// MATCHED 100% (23/23) once the two cold tails were spelled as explicit goto
// targets AND written in the order opposite to retail's block layout. cl 8804
// emits the two goto-target blocks in reverse source order, so retail's
// `false` block first / `true` block second comes from writing `yes:` first
// and `no:` second. The same skeleton in retail's own order reads 78.3%
// (blocks transposed, branch polarities inverted with them), and every
// single-exit spelling previously measured here sat at 3.6-4.2%: the nested
// form 42.3%, a short-circuit disjunction 4.2%, a mutated answer variable
// 3.6%, the positive form with a trailing zero return 3.7%, nested positive
// guards 3.7%. The lever is the goto skeleton plus the label transposition;
// neither alone gets there.
int LocoObject_0070FEB0::CanFireAny()
{
    if ((this->*this->Vtbl->WhatAmI)() == 15) goto yes;
    if ((this->*this->Vtbl->WhatAmI)() != 1) goto no;
    if ((this->*this->Vtbl->GetType)()->Flag_D97 == 0) goto no;
yes:
    return 1;
no:
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x710750
bool GrowPairVector::Grow_710750(int extra)
{
    GrowPair* grown;
    int total;
    int i;

    if (extra < 0) goto fail;

    total = Capacity + extra;
    grown = new GrowPair[total];
    if (grown == 0) goto fail;

    for (i = 0; i < Count; i++) {
        int off = i * 8;
        GrowPair* src = (GrowPair*)((char*)Items + off);
        *(GrowPair*)((char*)grown + off) = *src;
    }

    delete[] Items;

    Items    = grown;
    Capacity = Capacity + extra;
    Cached   = 0;
    return true;

fail:
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x00710860
int __cdecl FUN_00710860(const void* a, const void* b)
{
    if (*(const int*)a == *(const int*)b)
        return 0;
    if (*(const int*)a < *(const int*)b)
        return -1;
    return 1;
}
