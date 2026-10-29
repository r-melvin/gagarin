// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access + virtual-call disassembly). Names
//   cross-checked against YRpp
//   (every offset reconfirmed numerically below).
//
// This TU matches the passenger-list helpers (PassengersClass, the embedded
// transport cargo list) plus TechnoView_004598A0::IsAbsorbAllowed. Only the members the
// matched bodies touch are modelled; the full layouts are P2.
#ifndef GG_MATCH_CORE_TECHNO_CLASS_H
#define GG_MATCH_CORE_TECHNO_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#ifndef NULL
#define NULL 0
#endif

class TechnoTypeView_00473460;

// ---------------------------------------------------------------------------
// FootView_00473460 (passenger node). The matched code touches:
//   * vtable slot 33 (+0x84) GetTechnoType()  -> CALL [EAX+0x84]  (GetTotalSize)
//   * byte [+0x14]  (IndexOf bit-4 test)
//   * FootView_00473460* NextObject [+0x30]  (ObjectClass::NextObject, the cargo list)
// The 33 leading virtuals only pin GetTechnoType to slot +0x84; none are
// defined and FootView_00473460 is never constructed, so no vtable is emitted here.
// ---------------------------------------------------------------------------
class FootView_00473460
{
public:
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
    virtual TechnoTypeView_00473460* GetTechnoType() const;   // slot 33 -> +0x84

    char          _pad_04[0x10];   // +0x04 .. +0x13
    unsigned char Field14;         // +0x14  (IndexOf: TEST byte[EDX+0x14],0x4)
    char          _pad_15[0x1B];   // +0x15 .. +0x2F
    FootView_00473460*    NextObject;      // +0x30
};

// ---------------------------------------------------------------------------
// TechnoTypeView_00473460 — only Size (+0x380) and the two adjacent absorb flag bytes
// (+0x16AE / +0x16AF) are needed here.
// ---------------------------------------------------------------------------
class TechnoTypeView_00473460
{
public:
    char          _pad_to_380[0x380];           // +0x0000 .. +0x037F
    double        Size;                         // +0x0380  (FADD [type+0x380])
    char          _pad_to_16AE[0x16AE - 0x388]; // +0x0388 .. +0x16AD
    unsigned char unknown_byte_16AE;            // +0x16AE
    unsigned char unknown_byte_16AF;            // +0x16AF
};

// ---------------------------------------------------------------------------
// PassengersClass — { int NumPassengers; FootView_00473460* FirstPassenger; } singly
// linked through FootView_00473460::NextObject.
// ---------------------------------------------------------------------------
class PassengersClass
{
public:
    FootView_00473460* RemoveFirstPassenger();              // GAMEMD 0x473430 __thiscall
    int        GetTotalSize() const;                // GAMEMD 0x473460 __thiscall
    void       RemovePassenger(FootView_00473460* pPassenger); // GAMEMD 0x4734B0 __thiscall
    int        IndexOf(FootView_00473460* candidate) const; // GAMEMD 0x473500 __thiscall

    int        NumPassengers;    // +0x00
    FootView_00473460* FirstPassenger;   // +0x04
};

// ---------------------------------------------------------------------------
// TechnoView_004598A0 — only the cached type pointer at +0x520 is needed by
// IsAbsorbAllowed.  (sizeof(TechnoView_004598A0)==0x520, so +0x520 is the first
// derived-class member; confirmed numerically from MOV EAX,[ECX+0x520].)
// ---------------------------------------------------------------------------
class TechnoView_004598A0
{
public:
    bool IsAbsorbAllowed() const;   // GAMEMD 0x4598A0 __thiscall

    char             _pad_to_520[0x520];  // +0x000 .. +0x51F
    TechnoTypeView_00473460* Type;                // +0x520
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(FootView_00473460, Field14)             == 0x14);
GG_STATIC_ASSERT(offsetof(FootView_00473460, NextObject)          == 0x30);
GG_STATIC_ASSERT(offsetof(TechnoTypeView_00473460, Size)          == 0x380);
GG_STATIC_ASSERT(offsetof(TechnoTypeView_00473460, unknown_byte_16AE) == 0x16AE);
GG_STATIC_ASSERT(offsetof(TechnoTypeView_00473460, unknown_byte_16AF) == 0x16AF);
GG_STATIC_ASSERT(offsetof(PassengersClass, NumPassengers)  == 0x00);
GG_STATIC_ASSERT(offsetof(PassengersClass, FirstPassenger) == 0x04);
GG_STATIC_ASSERT(offsetof(TechnoView_004598A0, Type)               == 0x520);
#endif

#endif  // GG_MATCH_CORE_TECHNO_CLASS_H
