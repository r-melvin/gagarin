// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/convention derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x71F950 / 0x71F9C0), cross-
//   checked against YRpp
//   (the one touched offset reconfirmed below).
//
// TEventClass — a single trigger-event condition slot.  GetStateA / GetStateB
// are pure switch lookups on EventKind (the TriggerEvent enum) at +0x2c that
// classify an event kind into two boolean buckets used by
// TriggerClass::HaveEventsOccured for repeating triggers.  Only EventKind is
// touched; the rest of the layout (ArrayIndex/NextEvent/TeamType/Value/String/
// House) is modelled for offset fidelity and pinned numerically.
#ifndef GG_MATCH_AI_TEVENT_CLASS_METHODS_H
#define GG_MATCH_AI_TEVENT_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include <string.h>
#include "../_layout/abstract_class.h"

// ---------------------------------------------------------------------------
// TEventClass : public AbstractClass
//
// Confirmed from 0x71F950 / 0x71F9C0:
//   MOV ECX, [ECX+0x2c]   -> this->EventKind (the switch value), at +0x2c.
// AbstractClass occupies 0x00..0x23 (sizeof 0x24); TEventClass then adds
// ArrayIndex(+0x24), NextEvent(+0x28), EventKind(+0x2c) ... (YRpp order).
// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x6F0FC0 (decl; reloc) — team type by name (ECX = name).
struct TeamType_0071F4E0;
TeamType_0071F4E0* __fastcall FUN_006F0FC0(const char* name);

// A 24-character name plus terminator. Built from a C string with strncpy
// (or emptied when there is none), and assigned with a self-assignment guard
// that VC6 inlines as `LEA; LEA; CMP; JZ` ahead of the 25-byte REP MOVSD copy
// (0x71F574..0x71F58A).
struct TEventName
{
    struct Raw { char Text[25]; };
    Raw R;                                 // +0x00

    TEventName() {}
    TEventName(const char* text)
    {
        if (text == 0) {
            R.Text[0] = 0;
        } else {
            strncpy(R.Text, text, 24);
            R.Text[24] = 0;
        }
    }
    TEventName& operator=(const TEventName& other)
    {
        if (&other != this)
            R = other.R;
        return *this;
    }
};
GG_STATIC_ASSERT(sizeof(TEventName) == 25);

struct TEventClass : public AbstractClass
{
    // FUNCTION: GAMEMD 0x71F4E0
    void LoadFromINI();
    bool GetStateA() const;   // GAMEMD 0x71F950 __thiscall
    bool GetStateB() const;   // GAMEMD 0x71F9C0 __thiscall

    int   ArrayIndex;   // +0x24
    void* NextEvent;    // +0x28
    int   EventKind;    // +0x2c  (TriggerEvent enum; the switch value)
    TeamType_0071F4E0* TeamType;   // +0x30
    int   Value;        // +0x34
    TEventName String;  // +0x38  (25 bytes)
};

GG_STATIC_ASSERT(offsetof(TEventClass, ArrayIndex) == 0x24);
GG_STATIC_ASSERT(offsetof(TEventClass, NextEvent)  == 0x28);
GG_STATIC_ASSERT(offsetof(TEventClass, EventKind)  == 0x2c);
GG_STATIC_ASSERT(offsetof(TEventClass, TeamType)   == 0x30);
GG_STATIC_ASSERT(offsetof(TEventClass, Value)      == 0x34);
GG_STATIC_ASSERT(offsetof(TEventClass, String)     == 0x38);

#endif  // GG_MATCH_AI_TEVENT_CLASS_METHODS_H
