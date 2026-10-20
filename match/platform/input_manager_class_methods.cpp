// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Byte-for-byte matching decomp of InputManagerClass::IsKeyPressed (0x54F5C0)
//   and InputManagerClass::DoSomething (0x54F720) from the user's retail
//   gamemd.exe v1.001, disassembled with the local Ghidra CLI. YRpp
//   InputManagerClass.h consulted only; every offset reconfirmed from disasm.
#include "input_manager_class_methods.h"

// GetSystemMetrics(SM_SWAPBUTTON=0x17) via the IAT (indirect call, normalised).
extern "C" __declspec(dllimport) int __stdcall GetSystemMetrics(int nIndex);

// Retail callees we do NOT match here; declared only so cl emits direct/indirect
// calls (reloc-normalised by the differ).
//   0x53EC90 — low-level key-state probe; key passed in ECX (__fastcall).
short __fastcall InputManager_KeyState(unsigned int key);   // 0x53EC90
//   0x5D4D50 — message-pump pulse; no arguments.
void InputManager_Pump();                                   // 0x5D4D50

// FUNCTION: GAMEMD 0x54F5C0  InputManagerClass::IsKeyPressed (__thiscall)
bool InputManagerClass::IsKeyPressed(int key) const
{
    int k = key & 0xff;
    if ((short)k == 1 || (short)k == 2) {
        if (GetSystemMetrics(0x17) == 1) {
            k = ((short)k == 1) ? 2 : 1;
        }
    }
    return InputManager_KeyState((unsigned short)k) != 0;
}

// FUNCTION: GAMEMD 0x54F720  InputManagerClass::DoSomething (__thiscall)
void InputManagerClass::DoSomething()
{
    if ((this->field_318 + 1) % 256 != this->field_314)
        InputManager_Pump();
    this->field_314 = this->field_318;
    if ((this->field_318 + 1) % 256 != this->field_318)
        InputManager_Pump();
    this->field_314 = this->field_318;
}
