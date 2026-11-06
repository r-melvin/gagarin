// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x54F000 and 0x54F6F0: the
//   key-state array at +0x14 and the 256-entry key queue (ring) at +0x114 whose indices
//   sit at +0x314 and +0x318.
//
// Address index: 0x54F000 0x54F200 0x54F450 0x54F6F0

#include <stdlib.h>
#include "input_manager_class_methods.h"
#include "scenario_session_globals.h"


extern "C" __declspec(dllimport) int __stdcall GetSystemMetrics(int nIndex);
short FUN_0053EC90(unsigned int key);
bool __cdecl FUN_0053BAD0();
void __fastcall FUN_0053EC40(int vk, bool pressed);
short __fastcall FUN_0053EC70(int vk);
extern "C" __declspec(dllimport) int __stdcall ToAscii(unsigned int vk, unsigned int scan, unsigned char* state, unsigned short* out, unsigned int flags);
extern "C" __declspec(dllimport) unsigned int __stdcall MapVirtualKeyA(unsigned int code, unsigned int type);

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

// FUNCTION: GAMEMD 0x54F200
// Queues a key record with its modifier bits; false when the ring is full.
bool InputManagerClass::FUN_0054F200(int key, bool release)
{
    if (FUN_0053BAD0())
        return true;
    if (DAT_00A8ED9C && (short)key != 0x1B)
        return true;
    FUN_0053EC40(key & 0xFFFF, release);
    if ((short)(key & 0xFF) != 1 && (short)(key & 0xFF) != 4 && (short)(key & 0xFF) != 2 && (short)(key & 0xFF) != 10) {
        if (FUN_0053EC70(0x10) & 0x8000)
            key |= 0x100;
        if (FUN_0053EC70(0x11) & 0x8000)
            key |= 0x200;
        if (FUN_0053EC70(0x12) & 0x8000) {
            if ((short)key == 9)
                return true;
            key |= 0x400;
        }
    }
    if (release)
        key |= 0x800;
    int next = (field_318 + 1) % 256;
    if (next == field_314)
        return false;
    Ring[field_318] = key;
    field_318 = next;
    return true;
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

// FUNCTION: GAMEMD 0x54F450
// Translates a key code to its character through the system keyboard layout (0 for a release
// or when no single character results).
char InputManagerClass::FUN_0054F450(int key)
{
    if (key & 0x800)
        return 0;
    if ((short)(key & 0xFF) == 0x24)
        return 8;
    if ((short)(key & 0xFF) == 0x23)
        return 0x5C;
    unsigned short shift = key & 0x100;
    if (shift)
        KeyState[0x10] = 0x80;
    unsigned short ctrl = key & 0x200;
    if (ctrl)
        KeyState[0x11] = 0x80;
    unsigned short alt = key & 0x400;
    if (alt)
        KeyState[0x12] = 0x80;
    unsigned short out[6];
    unsigned int scan = MapVirtualKeyA(key & 0xFFFF, 0);
    int n = ToAscii(key & 0xFFFF, scan, KeyState, out, 0);
    if (shift)
        KeyState[0x10] = 0;
    if (ctrl)
        KeyState[0x11] = 0;
    if (alt)
        KeyState[0x12] = 0;
    if (n == 1)
        return out[0];
    return 0;
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

