// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below: the keyboard event
//   queue (256-entry ring of shorts at +0x114, tail +0x314, head +0x318) of InputManagerClass
//   and the helpers that push and pull key records.
//
// Address index: 0x54F2F0 0x54F3D0 (constructor 0x54EE60 and 0x54F050/200/450/530 are unmatched)

#include <stdlib.h>
#include "input_manager_class_methods.h"

extern bool DAT_00A8ED9C;

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
