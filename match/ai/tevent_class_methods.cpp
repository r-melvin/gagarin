// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bodies reconstructed from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI disassembly + decompile at 0x71F950 / 0x71F9C0.  Both are dense
//   jump-table switches on EventKind (+0x2c) over the range [1, 0x3b]; the case
//   lists were lifted from the index/jump tables at 0x71F970/0x71F978 (A) and
//   0x71F9E0/0x71F9E8 (B) and reconfirmed against the Ghidra decompiler.
//
// GetStateA: returns true for the listed event kinds, false otherwise.
// GetStateB: returns false for the listed event kinds, true otherwise.
#include <stdlib.h>
#include "tevent_class_methods.h"

// FUNCTION: GAMEMD 0x71F4E0  TEventClass::LoadFromINI
//
// Continue tokenising the trigger's event list (strtok state already set by
// the caller): the event kind, a parameter kind, and one parameter. Kind 0
// stores the parameter as the value, kind 1 looks it up as a team type by
// name, kind 2 stores it and takes a fourth token as the event's name string.
// STRING: GAMEMD 0x817F70 ","
void TEventClass::LoadFromINI()
{
    Value = 0;
    EventKind = atoi(strtok(0, ","));
    int paramKind = atoi(strtok(0, ","));
    char* param = strtok(0, ",");
    int value = atoi(param);
    char* text = 0;
    if (paramKind == 2)
        text = strtok(0, ",");

    switch (paramKind) {
    case 0:
        Value = value;
        break;
    case 1:
        TeamType = FUN_006F0FC0(param);
        break;
    case 2:
        Value = value;
        String = TEventName(text);
        break;
    }
}

// FUNCTION: GAMEMD 0x71F950  TEventClass::GetStateA (__thiscall)
bool TEventClass::GetStateA() const
{
    switch (this->EventKind) {
    case 0x01: case 0x02: case 0x03: case 0x04: case 0x06: case 0x07:
    case 0x12: case 0x13: case 0x14: case 0x15: case 0x16: case 0x17:
    case 0x18: case 0x19: case 0x1a: case 0x1d: case 0x1f: case 0x21:
    case 0x22: case 0x23: case 0x26: case 0x27: case 0x28: case 0x29:
    case 0x2a: case 0x2b: case 0x2c: case 0x30: case 0x31: case 0x32:
    case 0x35: case 0x36: case 0x3b:
        return true;
    default:
        return false;
    }
}

// FUNCTION: GAMEMD 0x71F9C0  TEventClass::GetStateB (__thiscall)
bool TEventClass::GetStateB() const
{
    switch (this->EventKind) {
    case 0x01: case 0x06: case 0x1f: case 0x2c: case 0x3b:
        return false;
    default:
        return true;
    }
}
