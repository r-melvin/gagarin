// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// SuperClass recharge-state accessors. Functions ordered ascending by retail
// address. Offsets confirmed numerically against the retail disassembly.
#include "super_class_methods.h"

// FUNCTION: GAMEMD 0x6CB820  SuperClass::SetReadiness (__thiscall)
//   mov al,[esp+4]; mov [ecx+0x6f],al; ret 4
void SuperClass::SetReadiness(bool ready)
{
    this->IsReady = ready;
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

// FUNCTION: GAMEMD 0x6CDE90  SuperClass::ShouldDrawProgress (__thiscall)
// Charge-drain weapons always show their sidebar progress overlay; everything
// else shows it only while still charging.
bool SuperClass::ShouldDrawProgress() const
{
    if (Type->UseChargeDrain)
        return true;

    return !IsReady;
}
