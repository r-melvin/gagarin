// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x54F000 and 0x54F6F0: the
//   key-state array at +0x14 and the 256-entry key queue (ring) at +0x114 whose indices
//   sit at +0x314 and +0x318.
//
// Address index: 0x54F000 0x54F6F0 (the constructor 0x54EE60 is unmatched)

#include <stdlib.h>
#include "input_manager_class_methods.h"


extern bool DAT_00A8ED9C;
extern "C" __declspec(dllimport) int __stdcall GetSystemMetrics(int nIndex);
short FUN_0053EC90(unsigned int key);

// FUNCTION: GAMEMD 0x54F000
// Pumps input when the queue is not full, then returns the oldest queued key without
// removing it (0 when the queue is empty).
unsigned short InputManagerClass::FUN_0054F000()
{
    if ((field_318 + 1) % 256 != field_314)
        FUN_005D4D50();
    if (field_314 == field_318)
        return 0;
    return Ring[field_314];
}

// FUNCTION: GAMEMD 0x54F2F0
// Queues a mouse button record followed by two coordinate words.
bool InputManagerClass::FUN_0054F2F0(int key, unsigned short x, unsigned short y, bool release)
{
    if (DAT_00A8ED9C)
        return true;
    if (256 - abs(field_318 - field_314) >= 3) {
        short k = (short)(key & 0xFF);
        if (k == 1 || k == 4 || k == 2) {
            FUN_0054F200(key, release);
            int next = (field_318 + 1) % 256;
            if (next != field_314) {
                Ring[field_318] = x;
                field_318 = next;
            }
            next = (field_318 + 1) % 256;
            if (next != field_314) {
                Ring[field_318] = y;
                field_318 = next;
            }
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x54F3D0
// Queues a character record followed by its character word.
bool InputManagerClass::FUN_0054F3D0(char ch)
{
    if (DAT_00A8ED9C)
        return true;
    if (256 - abs(field_318 - field_314) >= 2) {
        FUN_0054F200(10, false);
        int next = (field_318 + 1) % 256;
        if (next != field_314) {
            Ring[field_318] = ch & 0xFF;
            field_318 = next;
        }
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x54F5C0  InputManagerClass::IsKeyPressed (__thiscall)
bool InputManagerClass::IsKeyPressed(int key) const
{
    int k = key & 0xff;
    if ((short)k == 1 || (short)k == 2) {
        if (GetSystemMetrics(0x17) == 1) {
            k = ((short)k == 1) ? 2 : 1;
        }
    }
    return FUN_0053EC90((unsigned short)k) != 0;
}

// FUNCTION: GAMEMD 0x54F6F0
// Pumps input when the queue is not full.
void InputManagerClass::FUN_0054F6F0()
{
    if ((field_318 + 1) % 256 != field_314)
        FUN_005D4D50();
}

// FUNCTION: GAMEMD 0x54F720  InputManagerClass::DoSomething (__thiscall)
void InputManagerClass::DoSomething()
{
    if ((this->field_318 + 1) % 256 != this->field_314)
        FUN_005D4D50();
    this->field_314 = this->field_318;
    if ((this->field_318 + 1) % 256 != this->field_318)
        FUN_005D4D50();
    this->field_314 = this->field_318;
}

