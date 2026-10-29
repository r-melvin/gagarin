// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm).
//   Names cross-checked against YRpp
//   (each offset reconfirmed against the user's binary below).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4FCE30  HouseClass::GetPowerPercentage (__thiscall)
//   FUNCTION: GAMEMD 0x50BC90  HouseClass::CreatePowerOutage  (__thiscall)
//   FUNCTION: GAMEMD 0x50BCD0  HouseClass::CreateRadarOutage  (__thiscall)

#include "house_class_power_methods.h"

// FUNCTION: GAMEMD 0x4FCE30  HouseClass::GetPowerPercentage (__thiscall)
//   MOV EAX,[ECX+0x53A4]      ; PowerOutput
//   MOV ECX,[ECX+0x53A8]      ; PowerDrain
//   CMP EAX,ECX / spill both / JGE -> 1.0
//   TEST ECX,ECX / JZ -> 1.0  (drain == 0)
//   TEST EAX,EAX / JZ -> 0.0  (output == 0)
//   FILD output / FIDIV drain ; integer divide -> double
double HouseClass::GetPowerPercentage() const
{
    if (this->PowerOutput >= this->PowerDrain || this->PowerDrain == 0)
        return 1.0;
    if (this->PowerOutput != 0)
        return (double)this->PowerOutput / this->PowerDrain;
    return 0.0;
}

// FUNCTION: GAMEMD 0x50BC90  HouseClass::CreatePowerOutage (__thiscall)
//   byte[ECX+0x5778] = 1                       ; RecheckPower
//   PowerBlackoutTimer (12-byte POD copy of a freshly-built timer):
//     [+0x2A4] = Unsorted::CurrentFrame  (StartTime)
//     [+0x2A8] = <uninitialised clock>   (CurrentTime)
//     [+0x2AC] = duration                (TimeLeft)
void HouseClass::CreatePowerOutage(int duration)
{
    this->PowerBlackoutTimer = CDTimerClass(duration);

    this->RecheckPower = true;
}

// FUNCTION: GAMEMD 0x50BCD0  HouseClass::CreateRadarOutage (__thiscall)
//   byte[ECX+0x5779] = 1                       ; RecheckRadar
//   RadarBlackoutTimer 12-byte POD copy:
//     [+0x2B0] = Unsorted::CurrentFrame  (StartTime)
//     [+0x2B4] = <uninitialised clock>   (CurrentTime)
//     [+0x2B8] = duration                (TimeLeft)
void HouseClass::CreateRadarOutage(int duration)
{
    this->RadarBlackoutTimer = CDTimerClass(duration);

    this->RecheckRadar = true;
}
