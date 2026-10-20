// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x71F390.

#include <windows.h>
#include <string.h>
#include "tevent_class_prepare_save_methods.h"

// FUNCTION: GAMEMD 0x71F390  TEventClass::PrepareSaveToINI (__thiscall, ret 4)
//
// Append this event to a trigger's event list text. The event kind is first
// classified into its parameter kind (a dense jump-table switch over
// [1, 0x3D]); then one of three shapes is printed after whatever is already in
// the buffer: an event bound to a team type writes "kind,1,teamID", a kind
// whose parameter class is 0x2B writes "kind,2,value,name", and everything
// else writes "kind,0,value". strlen is the inlined REPNE SCASB.
// STRING: GAMEMD 0x844714 "%d,%d,%s"
// STRING: GAMEMD 0x8258DC "%d,%d,%d,%s"
// STRING: GAMEMD 0x8189B0 "%d,%d,%d"
void TEvent_0071F390::PrepareSaveToINI(char* buffer)
{
    int kind  = this->EventKind;
    int value = this->Value;
    int paramKind;

    switch (kind) {
    case 0x01: case 0x03: case 0x05: case 0x09: case 0x0A: case 0x0B:
    case 0x18: case 0x19: case 0x1A: case 0x1E: case 0x2C: case 0x35:
    case 0x37: case 0x38: case 0x3A: case 0x3B:
        paramKind = 0x0D;
        break;
    case 0x0C: case 0x0D: case 0x0F: case 0x10: case 0x2D: case 0x2E:
    case 0x2F: case 0x33: case 0x34:
        paramKind = 0x0A;
        break;
    case 0x1B: case 0x1C:
        paramKind = 0x16;
        break;
    case 0x24: case 0x25:
        paramKind = 0x1D;
        break;
    case 0x13: case 0x20: case 0x39:
        paramKind = 0x08;
        break;
    case 0x14:
        paramKind = 0x06;
        break;
    case 0x15: case 0x36:
        paramKind = 0x05;
        break;
    case 0x16:
        paramKind = 0x07;
        break;
    case 0x17:
        paramKind = 0x0C;
        break;
    case 0x22:
        paramKind = 0x09;
        break;
    case 0x3C: case 0x3D:
        paramKind = 0x2B;
        break;
    default:
        paramKind = 0;
        break;
    }

    if (this->TeamType != 0) {
        wsprintfA(buffer + strlen(buffer), "%d,%d,%s", kind, 1, this->TeamType->ID);
    } else if (paramKind == 0x2B) {
        wsprintfA(buffer + strlen(buffer), "%d,%d,%d,%s", kind, 2, value, this->String);
    } else {
        wsprintfA(buffer + strlen(buffer), "%d,%d,%d", kind, 0, value);
    }
}
