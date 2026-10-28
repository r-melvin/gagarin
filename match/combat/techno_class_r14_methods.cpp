// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, vtable slots and callees read off the user's retail gamemd.exe
//   v1.001 (Ghidra disasm) at the addresses annotated below. Members touched
//   only here carry placeholder names.
//   LIBRARY: GAMEMD 0x7C5F00  __ftol (CRT double->long; reloc)
//
// Address index:
//   0x7013E0  TechnoClass::FUN_007013E0
//   0x70BE50  TechnoClass::FUN_0070BE50
//   0x70D7A0  TechnoClass::FUN_0070D7A0
//   0x70DD20  TechnoClass::FUN_0070DD20
//   0x710590  TechnoClass::FUN_00710590

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct TechnoTypeClass
{
    // FUNCTION: GAMEMD 0x717880 (decl; reloc)
    bool FUN_00717880();
};

struct Rules_0070D690
{
    char   _pad000[0x1700];
    double Threshold;          // +0x1700
};
GG_STATIC_ASSERT(offsetof(Rules_0070D690, Threshold) == 0x1700);
// GLOBAL: GAMEMD 0x8871E0 -- RulesClass::Instance.
extern Rules_0070D690* RulesInstance_0070D690;

struct WeaponTypeBase_r14
{
    char _pad000[0xB4];
    int  Range;                // +0xB4
};
GG_STATIC_ASSERT(offsetof(WeaponTypeBase_r14, Range) == 0xB4);

struct WeaponStruct_r14
{
    WeaponTypeBase_r14* WeaponType;   // +0x00
};

struct LinkedVtbl_r14;
struct LinkedObj_r14
{
    LinkedVtbl_r14* Vtbl;
};
typedef void (LinkedObj_r14::*FnF8_r14)();
struct LinkedVtbl_r14
{
    char     _pad000[0xF8];
    FnF8_r14 At_F8;                   // +0xF8
};

// Interface sub-object living at TechnoClass+4 (COM-style stdcall slot 4).
struct SubIface_r14;
typedef int (__stdcall *FnSub10_r14)(SubIface_r14* self);
struct SubIfaceVtbl_r14
{
    char        _pad000[0x10];
    FnSub10_r14 At_10;                // +0x10
};
struct SubIface_r14
{
    SubIfaceVtbl_r14* Vtbl;
};

// Head of the embedded list at TechnoClass+0x114.
struct ListHead_r14;

struct TechnoVtbl_r14;

// Retail RTTI 0x817B58 establishes the class key.
class TechnoClass
{
public:
    TechnoVtbl_r14* Vtbl;                 // +0x000
    SubIface_r14    Sub;                  // +0x004
    char            _pad008[0x14 - 0x08];
    unsigned char   Flags14;              // +0x014
    char            _pad015[0x30 - 0x15];
    TechnoClass*    Next30;               // +0x030
    char            _pad034[0x114 - 0x34];
    char            ListHeadByte;         // +0x114
    char            _pad115[0x138 - 0x115];
    int             Value138;             // +0x138
    char            _pad13C[0x24C - 0x13C];
    float           Float24C;             // +0x24C
    char            _pad250[0x2B8 - 0x250];
    int             Value2B8;             // +0x2B8
    char            _pad2BC[0x310 - 0x2BC];
    LinkedObj_r14*  Linked310;            // +0x310

    // FUNCTION: GAMEMD 0x5B36B0 (decl; reloc)
    bool FUN_005B36B0();
    // FUNCTION: GAMEMD 0x5F5C60 (decl; reloc) -- health ratio, x87 result.
    double FUN_005F5C60();

    // FUNCTION: GAMEMD 0x7013E0
    bool FUN_007013E0();
    // FUNCTION: GAMEMD 0x70BE50
    int FUN_0070BE50();
    // FUNCTION: GAMEMD 0x70D7A0
    void FUN_0070D7A0();
    // FUNCTION: GAMEMD 0x70DD20
    int FUN_0070DD20();
    // FUNCTION: GAMEMD 0x710590
    int FUN_00710590();
};
GG_STATIC_ASSERT(offsetof(TechnoClass, Sub)       == 0x004);
GG_STATIC_ASSERT(offsetof(TechnoClass, Flags14)   == 0x014);
GG_STATIC_ASSERT(offsetof(TechnoClass, Next30)    == 0x030);
GG_STATIC_ASSERT(offsetof(TechnoClass, ListHeadByte) == 0x114);
GG_STATIC_ASSERT(offsetof(TechnoClass, Value138)  == 0x138);
GG_STATIC_ASSERT(offsetof(TechnoClass, Float24C)  == 0x24C);
GG_STATIC_ASSERT(offsetof(TechnoClass, Value2B8)  == 0x2B8);
GG_STATIC_ASSERT(offsetof(TechnoClass, Linked310) == 0x310);

typedef TechnoTypeClass* (TechnoClass::*FnGetType_r14)();
typedef int              (TechnoClass::*FnInt_r14)();
typedef void             (TechnoClass::*FnVoidInt_r14)(int);
typedef WeaponStruct_r14* (TechnoClass::*FnTurretWeapon_r14)();

struct TechnoVtbl_r14
{
    char               _pad000[0x84];
    FnGetType_r14      GetTechnoType;     // +0x084
    char               _pad088[0x1C8 - 0x88];
    FnInt_r14          At_1C8;            // +0x1C8
    char               _pad1CC[0x3C8 - 0x1CC];
    FnVoidInt_r14      At_3C8;            // +0x3C8
    char               _pad3CC[0x3F4 - 0x3CC];
    FnTurretWeapon_r14 GetTurretWeapon;   // +0x3F4
};
GG_STATIC_ASSERT(offsetof(TechnoVtbl_r14, GetTechnoType)   == 0x84);
GG_STATIC_ASSERT(offsetof(TechnoVtbl_r14, At_1C8)          == 0x1C8);
GG_STATIC_ASSERT(offsetof(TechnoVtbl_r14, At_3C8)          == 0x3C8);
GG_STATIC_ASSERT(offsetof(TechnoVtbl_r14, GetTurretWeapon) == 0x3F4);

// First node of an embedded list head (reads the head's +4 pointer).
struct ListHead_r14
{
    // FUNCTION: GAMEMD 0x473450 (decl; reloc)
    TechnoClass* FUN_00473450();
};

// FUNCTION: GAMEMD 0x7013E0
//
// When the base check passes, dispatch slot 0x3C8 with the +0x2B8 value and
// report success; otherwise report failure.
bool TechnoClass::FUN_007013E0()
{
    if (FUN_005B36B0()) {
        (this->*this->Vtbl->At_3C8)(this->Value2B8);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x70BE50
//
// Frame-phase value: the interface sub-object's slot-4 answer plus the
// truncated +0x24C float, taken modulo 400.
int TechnoClass::FUN_0070BE50()
{
    int a = this->Sub.Vtbl->At_10(&this->Sub);
    return ((int)this->Float24C + a) % 400;
}

// FUNCTION: GAMEMD 0x70D7A0
//
// When the health ratio exceeds the rules threshold, or slot 0x1C8 answers
// below -10, tell the linked object (if any) through its slot 0xF8.
void TechnoClass::FUN_0070D7A0()
{
    if (FUN_005F5C60() > ((Rules_0070D690*)RulesInstance_0070D690)->Threshold
        || (this->*this->Vtbl->At_1C8)() < -10) {
        if (this->Linked310 != 0) {
            (this->Linked310->*this->Linked310->Vtbl->At_F8)();
        }
    }
}

// FUNCTION: GAMEMD 0x70DD20
//
// The +0x138 value when the type's FUN_00717880 holds, else zero.
int TechnoClass::FUN_0070DD20()
{
    if ((this->*this->Vtbl->GetTechnoType)()->FUN_00717880()) {
        return this->Value138;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x710590
//
// Smallest weapon range over the object list headed at +0x114, starting
// from INT_MAX; the walk follows the +0x30 links while the +0x14 flag bit 4
// stays set.
int TechnoClass::FUN_00710590()
{
    int best = 0x7FFFFFFF;
    TechnoClass* node = ((ListHead_r14*)&this->ListHeadByte)->FUN_00473450();
    if (node != 0) {
        do {
            WeaponStruct_r14* w = (node->*node->Vtbl->GetTurretWeapon)();
            if (w->WeaponType != 0 && w->WeaponType->Range < best) {
                best = w->WeaponType->Range;
            }
            node = node->Next30;
        } while (node != 0 && (node->Flags14 & 4) != 0);
    }
    return best;
}
