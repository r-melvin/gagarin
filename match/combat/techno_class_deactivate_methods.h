// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, slots and offsets read off the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI at 0x70FC90: the byte at +0x418, the probe 0x65AD30
//   (one pushed argument, int result), the cell from slot +0x1BC and the
//   cell's 0x47C520 (returns an object), slots +0x3D0 and +0x150 (zero-arg),
//   AbstractFlags bit 2 with the locomotor at +0x674 and its COM slot +0x5C,
//   Deactivated at +0x1C8, slot +0x84 GetTechnoType and the type's sound at
//   +0x5AC, Location at +0x9C. The twin Reactivate at 0x70FBE0 shares the
//   layout (match/combat/techno_class_reactivate_methods.*). YRpp
//   names Deactivate.
#ifndef GG_MATCH_COMBAT_TECHNO_CLASS_DEACTIVATE_METHODS_H
#define GG_MATCH_COMBAT_TECHNO_CLASS_DEACTIVATE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "../_layout/foot_class.h"   // FootClass : TechnoClass : ... : AbstractClass

GG_STATIC_ASSERT(offsetof(AbstractClass, Flags) == 0x14);
GG_STATIC_ASSERT(offsetof(ObjectClass,   Location)      == 0x9C);
GG_STATIC_ASSERT(offsetof(TechnoClass,   Deactivated)   == 0x1C8);
GG_STATIC_ASSERT(offsetof(FootClass,     Locomotor)     == 0x674);

struct DeactType
{
    char _pad000[0x5AC];
    int  DeactivateSound;   // +0x5AC
};
GG_STATIC_ASSERT(offsetof(DeactType, DeactivateSound) == 0x5AC);

struct ILocomotion;
typedef long (__stdcall* LocoSlot0_0070FC90)(ILocomotion*);
#define LOCO_CALL0_DEACT(p, slot) \
    ((*(LocoSlot0_0070FC90*)(*(char**)(p) + (slot)))(p))

void __stdcall FUN_007DC720(unsigned int hr);
int VocClass_PlayAt(int index, CoordStruct* coords, int volume);

struct DeactVtbl;
struct TechnoDeactivate;

struct DeactCell
{
    // FUNCTION: GAMEMD 0x47C520 (decl; reloc) — the object occupying the cell.
    TechnoDeactivate* FUN_0047C520();
};

struct TechnoDeactivate : TechnoClass
{
    // FUNCTION: GAMEMD 0x70FC90  TechnoClass::Deactivate  (__thiscall)
    void Deactivate();
    // FUNCTION: GAMEMD 0x65AD30 (decl; reloc)
    int FUN_0065AD30(int flag);
};
GG_STATIC_ASSERT(offsetof(TechnoDeactivate, IsTether) == 0x418);

typedef void       (IPersistStream::*Fn3D0_Deact)();
typedef void       (IPersistStream::*Fn150_Deact)();
typedef DeactType* (IPersistStream::*Fn084_Deact)();
typedef DeactCell* (IPersistStream::*Fn1BC_Deact)();

struct DeactVtbl
{
    char        _pad000[0x84];             // +0x0000
    Fn084_Deact GetTechnoType;             // +0x0084
    char        _pad088[0x150 - 0x88];     // +0x0088
    Fn150_Deact At_150;                    // +0x0150
    char        _pad154[0x1BC - 0x154];    // +0x0154
    Fn1BC_Deact GetCell;                   // +0x01BC
    char        _pad1C0[0x3D0 - 0x1C0];    // +0x01C0
    Fn3D0_Deact At_3D0;                    // +0x03D0
};
GG_STATIC_ASSERT(offsetof(DeactVtbl, GetTechnoType) == 0x84);
GG_STATIC_ASSERT(offsetof(DeactVtbl, At_150)        == 0x150);
GG_STATIC_ASSERT(offsetof(DeactVtbl, GetCell)       == 0x1BC);
GG_STATIC_ASSERT(offsetof(DeactVtbl, At_3D0)        == 0x3D0);

#endif  // GG_MATCH_COMBAT_TECHNO_CLASS_DEACTIVATE_METHODS_H
