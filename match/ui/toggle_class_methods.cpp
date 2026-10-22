// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x723EA0  ToggleClass::TurnOn  (__thiscall)
//   FUNCTION: GAMEMD 0x723EB0  ToggleClass::TurnOff (__thiscall)

#include "toggle_class_methods.h"

// FUNCTION: GAMEMD 0x723E60
ToggleClass::ToggleClass(int id, int x, int y, int width, int height)
    : ControlClass(id, x, y, width, height, 5, 1),
      unknown_2C(0), IsOn(0), unknown_30(0)
{
}

// FUNCTION: GAMEMD 0x723EA0  (__thiscall)
// Set the toggle ON, then tail-call the redraw virtual:
//   mov eax,[ecx]; mov byte [ecx+2d],1; jmp [eax+0x48]
void ToggleClass::TurnOn()
{
    IsOn = true;
    MarkRedraw();
}

// FUNCTION: GAMEMD 0x723EB0  (__thiscall)
// Set the toggle OFF, then tail-call the redraw virtual:
//   mov eax,[ecx]; mov byte [ecx+2d],0; jmp [eax+0x48]
void ToggleClass::TurnOff()
{
    IsOn = false;
    MarkRedraw();
}
