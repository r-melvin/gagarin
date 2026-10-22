// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x70FBE0: the foot test `TEST byte ptr [ESI+0x14],4`
//   (AbstractFlags), the locomotor `MOV EAX,[ESI+0x674]` and its COM slot
//   `PUSH EAX; MOV ECX,[EAX]; CALL [ECX+0x58]`, Deactivated `MOV AL,[ESI+0x1C8]`
//   / `MOV byte ptr [ESI+0x1C8],0`, the type virtual `CALL [EDX+0x84]`, the
//   sound index `CMP dword ptr [EAX+0x5A8],-1`, and the coordinate copy from
//   `LEA EAX,[ESI+0x9C]`. Names for the method, the E_POINTER reporter
//   (0x7DC720) and VocClass::PlayAt (0x7509E0) come from YRpp.
//
// TechnoClass::Reactivate — bring a deactivated (EMP'd / powered-down) object
// back: reset via the +0x3D0 virtual, power the locomotor back on if this is a
// FootClass, play the type's ActivateSound at the object, clear Deactivated.
#ifndef GG_MATCH_COMBAT_TECHNO_CLASS_REACTIVATE_METHODS_H
#define GG_MATCH_COMBAT_TECHNO_CLASS_REACTIVATE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "../_layout/foot_class.h"   // FootClass : TechnoClass : ... : AbstractClass

// Re-confirm the spine offsets this TU reads (all from the disasm above).
GG_STATIC_ASSERT(offsetof(AbstractClass, Flags) == 0x14);
GG_STATIC_ASSERT(offsetof(ObjectClass,   Location)      == 0x9C);
GG_STATIC_ASSERT(offsetof(TechnoClass,   Deactivated)   == 0x1C8);
GG_STATIC_ASSERT(offsetof(FootClass,     Locomotor)     == 0x674);

// TechnoTypeClass — only ActivateSound @0x5A8 is read here.
struct ReactType
{
    char _pad000[0x5A8];
    int  ActivateSound;   // +0x5A8
};
GG_STATIC_ASSERT(offsetof(ReactType, ActivateSound) == 0x5A8);

// ILocomotion — reached as `PUSH p; MOV ECX,[p]; CALL [ECX+0x58]`: the receiver
// goes on the stack, the __stdcall COM virtual convention. Slot +0x58 is the
// locomotor's power-on entry.
class ILocomotion;
typedef long (__stdcall* LocoSlot0)(ILocomotion*);
#define LOCO_CALL0(p, slot) \
    ((*(LocoSlot0*)(*(char**)(p) + (slot)))(p))

// __stdcall, one argument. 0x80004003 is E_POINTER — the report the
// smart-pointer dereference emits for a null interface.
// LIBRARY: GAMEMD 0x7DC720 (decl; reloc)
void __stdcall FUN_007DC720(unsigned int hr);

// VocClass::PlayAt — static, __fastcall: ECX = sound index, EDX = coordinate,
// third argument (0 here) pushed.
// FUNCTION: GAMEMD 0x7509E0 (decl; reloc)
int __fastcall VocClass_PlayAt(int index, CoordStruct* coords, int volume);

// Declaration order matters — see match/_rt/gg_vslot.h: the class must be
// complete before the member-function-pointer types.
struct ReactVtbl;

// No-data host over the committed TechnoClass spine; layout identical.
struct TechnoReactivate : TechnoClass
{
    // FUNCTION: GAMEMD 0x70FBE0  TechnoClass::Reactivate  (__thiscall)
    void Reactivate();
};

typedef void       (IPersistStream::*Fn3D0_React)();
typedef ReactType* (IPersistStream::*Fn084_React)();

struct ReactVtbl
{
    char        _pad000[0x84];             // +0x0000
    Fn084_React GetTechnoType;             // +0x0084
    char        _pad088[0x3D0 - 0x88];     // +0x0088
    Fn3D0_React At_3D0;                    // +0x03D0
};
GG_STATIC_ASSERT(offsetof(ReactVtbl, GetTechnoType) == 0x84);
GG_STATIC_ASSERT(offsetof(ReactVtbl, At_3D0)        == 0x3D0);

#endif  // GG_MATCH_COMBAT_TECHNO_CLASS_REACTIVATE_METHODS_H
