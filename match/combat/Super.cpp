// SPDX-License-Identifier: GPL-3.0-or-later
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit Super.CPP. The name is the source-file string at 0x842510
//   in retail gamemd.exe v1.001, passed by the assert at 0x6cc2de inside this object's
//   code range (0x6cac10-0x6ce37f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// SuperClass recharge-state accessors. Functions ordered ascending by retail
// address. Offsets confirmed numerically against the retail disassembly.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.

#include "super_class_methods.h"
#include "../core/mathtbl_init_shapes.h"

#include "trivial_tu225_methods.h"

#include "../core/deleting_dtor_sweep.h"
#include "../network/transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

#include "../core/empty_function_family_methods.h"

#include "../core/vector_remove_item_family_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F3FA8
extern const double DAT_007F3FA8;
// GLOBAL: GAMEMD 0xB0C008
extern double DAT_00B0C008;

// SYNTHETIC: GAMEMD 0x006CAC40
// GLOBAL: GAMEMD 0x00B0C080
double DAT_00B0C080 = DAT_00B0C008 / DAT_007F3FA8;

// SYNTHETIC: GAMEMD 0x006CAC60
// GLOBAL: GAMEMD 0x00B0C068
double DAT_00B0C068 = DAT_007E1718 / DAT_00B0C080;

// SYNTHETIC: GAMEMD 0x006CADE0
// GLOBAL: GAMEMD 0x00B0C070
MathTblCoord DAT_00B0C070;

// FUNCTION: GAMEMD 0x6CB820  SuperClass::SetReadiness (__thiscall)
//   mov al,[esp+4]; mov [ecx+0x6f],al; ret 4
void SuperClass::SetReadiness(bool ready)
{
    this->IsReady = ready;
}

// FUNCTION: GAMEMD 0x006CC070
void FUN_006CC070()
{
}

// FUNCTION: GAMEMD 0x6CC260  SuperClass::GetRechargeTime (__thiscall)
//   mov eax,[ecx+0x24]; cmp eax,-1; jnz ret; mov eax,[ecx+0x28]; mov eax,[eax+0xb0]; ret
int SuperClass::GetRechargeTime() const
{
    if (this->CustomChargeTime != -1)
        return this->CustomChargeTime;
    return this->Type->RechargeTime;
}

// FUNCTION: GAMEMD 0x6CC280  SuperClass::SetRechargeTime (__thiscall)
//   mov eax,[esp+4]; mov [ecx+0x24],eax; ret 4
void SuperClass::SetRechargeTime(int time)
{
    this->CustomChargeTime = time;
}

// FUNCTION: GAMEMD 0x6CC290  SuperClass::ResetRechargeTime (__thiscall)
//   mov dword [ecx+0x24],0xffffffff; ret
void SuperClass::ResetRechargeTime()
{
    this->CustomChargeTime = -1;
}

// FUNCTION: GAMEMD 0x6CC2A0
// Member getter (byte).
unsigned char Obj_006CC2A0::FUN_006CC2A0() const
{
    return unknown_28->unknown_E6;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6CC360  SuperClass::CanFire (__thiscall)
// A suspended superweapon can never fire. For charge-drain weapons readiness is
// the drain state machine rather than the plain ready flag.
bool SuperClass::CanFire() const
{
    if (!IsSuspended) {
        if (Type->UseChargeDrain) {
            // The temporary is load-bearing: `return ChargeDrainState != 0;`
            // makes VC6 build an int 0/1 (XOR EAX,EAX + SETNE), whereas retail
            // materialises the bool in AL alone (MOV EAX,[+0x7C]; TEST EAX,EAX;
            // SETNZ AL). Binding it to a bool local first reproduces that.
            bool draining = ChargeDrainState != 0;
            return draining;
        }
        return IsReady;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6CDE80
// Empty function that pops its stack arguments.
void __stdcall FUN_006CDE80(int a1, int a2)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6CDE90  SuperClass::ShouldDrawProgress (__thiscall)
// Charge-drain weapons always show their sidebar progress overlay; everything
// else shows it only while still charging.
bool SuperClass::ShouldDrawProgress() const
{
    if (Type->UseChargeDrain)
        return true;

    return !IsReady;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6CE200
// Returns a constant. Vtable slot 11 of SuperClass (RTTI).
int Obj_006CE200::FUN_006CE200() const
{
    return 0x39;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6CE210
// Returns a constant. Vtable slot 12 of SuperClass (RTTI).
int Obj_006CE210::FUN_006CE210() const
{
    return 0x80;
}

// Take a reference on the held interface, if there is one.
struct Obj_006CE270 {
    IUnknown* unknown_00;
    void FUN_006CE270();
};
GG_STATIC_ASSERT(offsetof(Obj_006CE270, unknown_00) == 0x00);
// FUNCTION: GAMEMD 0x006CE270
void Obj_006CE270::FUN_006CE270()
{
    if (unknown_00 != 0) {
        unknown_00->AddRef();
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x006CE2D0
//
// Remove the given element: ask the vector where it is, then shift the tail
// down one slot over it.
bool ItemVector_0063DFD0::FUN_00006CE2D0(int item)
{
    int index = (this->*this->Vtbl->IndexOf)(item);
    if (index != -1) {
        if (index < this->Count) {
            this->Count = this->Count - 1;
            for (int i = index; i < this->Count; i++) {
                this->Items[i] = this->Items[i + 1];
            }
            return true;
        }
    }
    return false;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7F3FA8
extern const double DAT_007F3FA8 = 60.0;
// END defined globals
