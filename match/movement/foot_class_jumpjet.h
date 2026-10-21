// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at 0x4135A0).
//   Name cross-checked vs YRpp AircraftTrackerClass.h (consult-only):
//     bool IsJumpjet(TechnoClass* entry)  JMP_THIS(0x4135A0)
//   The function ignores its own `this` (ECX) and works purely on `entry`.
#ifndef GG_MATCH_MOVEMENT_FOOT_CLASS_JUMPJET_H
#define GG_MATCH_MOVEMENT_FOOT_CLASS_JUMPJET_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Minimal CellClass model: only the Jumpjet occupant pointer at +0xE0 is
// touched (disasm: `MOV EAX,[EAX+0xE0]`).  GetCell() returns one of these.
struct CellClass
{
    char    _pad_0xE0[0xE0];   // +0x000
    void*   Jumpjet;           // +0x0E0  FootClass* occupying this cell
};
GG_STATIC_ASSERT(offsetof(CellClass, Jumpjet) == 0xE0);

// Minimal TechnoClass model used only to reproduce the virtual dispatch.  The
// retail call is `CALL [EAX+0x1BC]` (vtable byte-offset 0x1BC = slot 111), with
// ECX = entry.  111 placeholder virtuals push GetCell to that slot; only its
// vtable position matters (never defined / instantiated here).
// Retail RTTI 0x817B58 establishes the class key; public access preserves this ABI view.
class TechnoClass
{
public:
    virtual void vslot_0();
    virtual void vslot_1();
    virtual void vslot_2();
    virtual void vslot_3();
    virtual void vslot_4();
    virtual void vslot_5();
    virtual void vslot_6();
    virtual void vslot_7();
    virtual void vslot_8();
    virtual void vslot_9();
    virtual void vslot_10();
    virtual void vslot_11();
    virtual void vslot_12();
    virtual void vslot_13();
    virtual void vslot_14();
    virtual void vslot_15();
    virtual void vslot_16();
    virtual void vslot_17();
    virtual void vslot_18();
    virtual void vslot_19();
    virtual void vslot_20();
    virtual void vslot_21();
    virtual void vslot_22();
    virtual void vslot_23();
    virtual void vslot_24();
    virtual void vslot_25();
    virtual void vslot_26();
    virtual void vslot_27();
    virtual void vslot_28();
    virtual void vslot_29();
    virtual void vslot_30();
    virtual void vslot_31();
    virtual void vslot_32();
    virtual void vslot_33();
    virtual void vslot_34();
    virtual void vslot_35();
    virtual void vslot_36();
    virtual void vslot_37();
    virtual void vslot_38();
    virtual void vslot_39();
    virtual void vslot_40();
    virtual void vslot_41();
    virtual void vslot_42();
    virtual void vslot_43();
    virtual void vslot_44();
    virtual void vslot_45();
    virtual void vslot_46();
    virtual void vslot_47();
    virtual void vslot_48();
    virtual void vslot_49();
    virtual void vslot_50();
    virtual void vslot_51();
    virtual void vslot_52();
    virtual void vslot_53();
    virtual void vslot_54();
    virtual void vslot_55();
    virtual void vslot_56();
    virtual void vslot_57();
    virtual void vslot_58();
    virtual void vslot_59();
    virtual void vslot_60();
    virtual void vslot_61();
    virtual void vslot_62();
    virtual void vslot_63();
    virtual void vslot_64();
    virtual void vslot_65();
    virtual void vslot_66();
    virtual void vslot_67();
    virtual void vslot_68();
    virtual void vslot_69();
    virtual void vslot_70();
    virtual void vslot_71();
    virtual void vslot_72();
    virtual void vslot_73();
    virtual void vslot_74();
    virtual void vslot_75();
    virtual void vslot_76();
    virtual void vslot_77();
    virtual void vslot_78();
    virtual void vslot_79();
    virtual void vslot_80();
    virtual void vslot_81();
    virtual void vslot_82();
    virtual void vslot_83();
    virtual void vslot_84();
    virtual void vslot_85();
    virtual void vslot_86();
    virtual void vslot_87();
    virtual void vslot_88();
    virtual void vslot_89();
    virtual void vslot_90();
    virtual void vslot_91();
    virtual void vslot_92();
    virtual void vslot_93();
    virtual void vslot_94();
    virtual void vslot_95();
    virtual void vslot_96();
    virtual void vslot_97();
    virtual void vslot_98();
    virtual void vslot_99();
    virtual void vslot_100();
    virtual void vslot_101();
    virtual void vslot_102();
    virtual void vslot_103();
    virtual void vslot_104();
    virtual void vslot_105();
    virtual void vslot_106();
    virtual void vslot_107();
    virtual void vslot_108();
    virtual void vslot_109();
    virtual void vslot_110();
    virtual CellClass* GetCell();   // slot 111  ->  vtable offset 0x1BC
};

// AircraftTrackerClass — only the one matched accessor is modelled.
struct AircraftTrackerClass
{
    // FUNCTION: GAMEMD 0x4135A0  AircraftTrackerClass::IsJumpjet (__thiscall)
    bool IsJumpjet(TechnoClass* entry);
};

#endif  // GG_MATCH_MOVEMENT_FOOT_CLASS_JUMPJET_H
