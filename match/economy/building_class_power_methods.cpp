// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x44E880 (Ghidra disasm).
//
// Translation unit: BuildingClass::GetPowerDrain.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x44E880   BuildingClass::GetPowerDrain   (__thiscall)

#include "building_class_power_methods.h"

// FUNCTION: GAMEMD 0x44E880  (__thiscall)
//
// Retail body (len 0x62), entry ECX = this:
//   56              PUSH ESI
//   8bf1            MOV  ESI, ECX
//   8b06            MOV  EAX, [ESI]            ; vtable
//   ff90d4010000    CALL [EAX+0x1d4]           ; virtual slot 117 (offline?)
//   84c0            TEST AL, AL
//   754f            JNZ  ret0
//   8a8660060000    MOV  AL, [ESI+0x660]       ; HasPower
//   84c0            TEST AL, AL
//   7445            JZ   ret0
//   8b8e20050000    MOV  ECX, [ESI+0x520]      ; Type
//   8a9669060000    MOV  DL, [ESI+0x669]       ; HasExtraPowerDrain
//   84d2            TEST DL, DL
//   8b81e40e0000    MOV  EAX, [ECX+0xee4]      ; Type->PowerDrain
//   7406            JZ   skip_extra
//   0381ec0e0000    ADD  EAX, [ECX+0xeec]      ; + Type->ExtraPowerDrain
// skip_extra:
//   8a8e02070000    MOV  CL, [ESI+0x702]       ; UpgradeLevel
//   84c9            TEST CL, CL
//   7421            JZ   ret_eax
//   8d96ec050000    LEA  EDX, [ESI+0x5ec]      ; &Upgrades[0]
//   be03000000      MOV  ESI, 0x3              ; 3 upgrade slots
// loop:
//   8b0a            MOV  ECX, [EDX]
//   85c9            TEST ECX, ECX
//   7406            JZ   loop_next
//   0381e40e0000    ADD  EAX, [ECX+0xee4]      ; + upgrade->PowerDrain
// loop_next:
//   83c204          ADD  EDX, 0x4
//   4e              DEC  ESI
//   75ee            JNZ  loop
//   5e              POP  ESI
//   c3              RET
// ret0:
//   33c0            XOR  EAX, EAX
// ret_eax:
//   5e              POP  ESI
//   c3              RET
//
// Screened for the inline-assembly signature before conversion and it is
// absent: the prologue is a bare `56 PUSH ESI` with no `PUSH EBP; MOV EBP,ESP`,
// every local lives in a register, and no instruction in the body is outside
// what cl 12.00 generates from a C expression. Retail was compiled from
// ordinary C++ here, so the body below is C++.
int BuildingClass::GetPowerDrain() const
{
    if ((this->*this->Vfptr->At_1D4)() || !this->HasPower) {
        return 0;
    }

    BuildingTypeClass* type = this->Type;
    int drain = type->PowerDrain;

    if (this->HasExtraPowerDrain) {
        drain += type->ExtraPowerDrain;
    }
    if (this->UpgradeLevel) {
        for (int i = 0; i < 3; ++i) {
            BuildingTypeClass* upgrade = this->Upgrades[i];

            if (upgrade != 0) {
                drain += upgrade->PowerDrain;
            }
        }
    }
    return drain;
}
