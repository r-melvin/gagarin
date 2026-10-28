// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, vtable slots and callees read off the user's retail gamemd.exe
//   v1.001 (Ghidra disasm) at the addresses annotated below. Methods live on
//   the canonical TechnoClass (match/_layout/techno_class.h).
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
#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"

struct Rules_0070D7A0
{
    char   _pad000[0x1700];
    double Threshold;          // +0x1700
};
GG_STATIC_ASSERT(offsetof(Rules_0070D7A0, Threshold) == 0x1700);
// GLOBAL: GAMEMD 0x8871E0 -- RulesClass::Instance.
extern Rules_0070D7A0* RulesInstance_0070D7A0;

struct WeaponTypeBase_r14
{
    char _pad000[0xB4];
    int  Range;                // +0xB4
};
GG_STATIC_ASSERT(offsetof(WeaponTypeBase_r14, Range) == 0xB4);

// The linked object at TechnoClass+0x310 (DamageParticleSystem slot): only
// its vtable slot 0xF8 is used here.
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
        vf_242((int)this->LastTarget);
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
    SubIface_r14* sub = (SubIface_r14*)((char*)this + 4);
    int a = sub->Vtbl->At_10(sub);
    return ((int)this->WarpFactor + a) % 400;
}

// FUNCTION: GAMEMD 0x70D7A0
//
// When the health ratio exceeds the rules threshold, or slot 0x1C8 answers
// below -10, tell the linked object (if any) through its slot 0xF8.
void TechnoClass::FUN_0070D7A0()
{
    if (FUN_005F5C60() > RulesInstance_0070D7A0->Threshold
        || vf_114() < -10) {
        LinkedObj_r14* linked = (LinkedObj_r14*)this->DamageParticleSystem;
        if (linked != 0) {
            (linked->*linked->Vtbl->At_F8)();
        }
    }
}

// FUNCTION: GAMEMD 0x70DD20
//
// The +0x138 value when the type's FUN_00717880 holds, else zero.
int TechnoClass::FUN_0070DD20()
{
    if (vf_33()->FUN_00717880()) {
        return this->CurrentWeaponNumber;
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
    TechnoClass* node = ((ListHead_r14*)&this->Passengers)->FUN_00473450();
    if (node != 0) {
        do {
            WeaponStruct* w = node->GetPrimaryWeapon();
            WeaponTypeBase_r14* wt = (WeaponTypeBase_r14*)w->WeaponType;
            if (wt != 0 && wt->Range < best) {
                best = wt->Range;
            }
            node = (TechnoClass*)node->NextObject;
        } while (node != 0 && node->Flags.IsFoot);
    }
    return best;
}
