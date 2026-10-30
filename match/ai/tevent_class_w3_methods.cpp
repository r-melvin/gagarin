// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   TEventClass stream loading and destruction, read off retail gamemd.exe v1.001
//   (vtable 0x7F5578). The class is a view that carries only the members these bodies
//   touch (offsets from the retail disassembly). Functions are in ascending retail address
//   order. /Ob2: the scalar deleting destructor carries the destructor body inline.

#include <new.h>
#include <stdlib.h>
#include "tevent_class_methods.h"
#include "../_layout/swizzle_manager_class.h"
#include "../core/vector_class_operations.h"

// GLOBAL: GAMEMD 0xB0C110 -- the swizzle manager.
extern SwizzleManagerClass DAT_00B0C110;


// GLOBAL: GAMEMD 0xB0F658 / 0xB0F670 / 0xB0F1A0 -- the registries a TEventClass leaves when destroyed.
extern DynamicVectorClass<TEventClass*> DAT_00B0F658;
extern DynamicVectorClass<TEventClass*> DAT_00B0F670;
extern DynamicVectorClass<TEventClass*> DAT_00B0F1A0;

// FUNCTION: GAMEMD 0x71E830
// Leaves the registries; the scalar deleting destructor 0x71FA80 expands this body in place.
TEventClass::~TEventClass()
{
    AnnounceExpiredPointer(1);
    DAT_00B0F658.RemoveItem(this);
    DAT_00B0F670.RemoveItem(this);
    DAT_00B0F1A0.RemoveItem(this);
}

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

// FUNCTION: GAMEMD 0x71F800
// Drop a pointer that is going away: unlink it from the chain, or forget the team.
void TEventClass::vf_10(void* target, bool removed)
{
    if (NextEvent == target) {
        NextEvent = NextEvent->NextEvent;
    }
    if (TeamType == target) {
        TeamType = 0;
    }
}

// FUNCTION: GAMEMD 0x71F8C0
// Re-establish the object after a stream load and queue its pointers for swizzling.
HRESULT __stdcall TEventClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) TEventClass(AbstractNoInit());
    DAT_00B0C110.SwizzleManagerClass::vf_4(&NextEvent);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&TeamType);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_54);
    return 0;
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

// SYNTHETIC: GAMEMD 0x71FA80
// TEventClass scalar deleting destructor (primary slot 8), the destructor expanded in place.
