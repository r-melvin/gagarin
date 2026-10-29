// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp (every offset
//   and global address reconfirmed against the user's binary below).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4015C0  AudioIDXData::FindSampleIndex      (__fastcall)
//   FUNCTION: GAMEMD 0x401910  AudioIDXData::ClearCurrentSample   (__thiscall)
//   FUNCTION: GAMEMD 0x4060F0  AudioController::SetEvent          (__fastcall)
//   FUNCTION: GAMEMD 0x406130  AudioController::GetEvent          (__thiscall)
//   FUNCTION: GAMEMD 0x406170  AudioController::GetEventType      (__thiscall)
//   FUNCTION: GAMEMD 0x406310  AudioController::GetEventType      (__fastcall, static)
//   GLOBAL:   GAMEMD 0x87E294  AudioIDXData::Instance   (AudioIDXData*)
//   GLOBAL:   GAMEMD 0x87E2A0  g_AudioEnabled           (audio-pool guard ptr)
//   LIBRARY:  GAMEMD 0x7C8D20  _strcmpi   (bsearch comparator; CRT, reloc)
//   LIBRARY:  GAMEMD 0x7C8E25  bsearch    (CRT, reloc)

#include "audio.h"
#include <stdlib.h>   // bsearch
#include <string.h>   // _strcmpi

// GLOBAL: GAMEMD 0x87E294 — the engine's single AudioIDXData instance pointer.
// AudioController::AudioIndex points at this global when its handle is "live".
extern AudioIDXData* AudioIDXData_Instance;

// GLOBAL: GAMEMD 0x87E2A0 — audio-subsystem guard. When null, no controller can
// resolve an event (every getter short-circuits to null).
extern void* g_AudioEnabled;

// Retail stores the timer group address in these seven globals at FUN_00406B10.
// The PE image places each pointer in the zero-filled tail of .data. Only the
// pointer slots are defined here; the pointed-to Obj_00401000 stays incomplete.
struct Obj_00401000;
GG_STATIC_ASSERT(sizeof(Obj_00401000*) == 4);

// GLOBAL: GAMEMD 0x87E73C
Obj_00401000* DAT_0087E73C;
// GLOBAL: GAMEMD 0x87E740
Obj_00401000* DAT_0087E740;
// GLOBAL: GAMEMD 0x87E744
Obj_00401000* DAT_0087E744;
// GLOBAL: GAMEMD 0x87E748
Obj_00401000* DAT_0087E748;
// GLOBAL: GAMEMD 0x87E74C
Obj_00401000* DAT_0087E74C;
// GLOBAL: GAMEMD 0x87E750
Obj_00401000* DAT_0087E750;
// GLOBAL: GAMEMD 0x87E754
Obj_00401000* DAT_0087E754;

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x4015C0  (__fastcall: pThis=ECX, pName=EDX)
//
// Binary-search the (name-sorted) sample table for `pName`; return its index or
// -1. Name lives at offset 0 of each 0x24-byte entry, so the entry pointer is
// also the name pointer and `_strcmpi` serves directly as the comparator.
// ---------------------------------------------------------------------------
int AudioIDXData::FindSampleIndex(const AudioIDXData* pThis, const char* pName)
{
    AudioIDXEntry* found = (AudioIDXEntry*)bsearch(
        pName, pThis->Samples, (size_t)pThis->SampleCount, sizeof(AudioIDXEntry),
        (int (__cdecl*)(const void*, const void*))_strcmpi);
    if (found != 0)
        return (int)((unsigned int)((const char*)found - (const char*)pThis->Samples)
                     / sizeof(AudioIDXEntry));
    return -1;
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x401910  (__thiscall)
//
// Release the currently-streamed sample file (virtual scalar-deleting dtor) and
// reset the size. The outer null-guard lets MSVC elide `delete`'s own inner null
// check, leaving the lean `MOV EAX,[ECX]; PUSH 1; CALL [EAX]` slot-0 call.
// ---------------------------------------------------------------------------
void AudioIDXData::ClearCurrentSample()
{
    this->CurrentSampleSize = 0;
    if (this->CurrentSampleFile != 0)
    {
        delete this->CurrentSampleFile;
        this->CurrentSampleFile = 0;
    }
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x4060F0  (__fastcall: pThis=ECX, event=EDX, eventType=stack)
//
// Bind this controller to a freshly-played audio event. No-op unless the handle
// is live (AudioIndex == &Instance). Records the event, its type, and a freshness
// stamp; if no explicit type was given it adopts the event's own; and back-links
// the event to this controller.
// ---------------------------------------------------------------------------
void AudioController::SetEvent(AudioController* pThis, void* event, VocClass* eventType)
{
    if (pThis->AudioIndex == &AudioIDXData_Instance)
    {
        pThis->Event = event;
        pThis->EventType = eventType;
        if (event != 0)
        {
            pThis->Stamp = *(unsigned int*)((char*)event + 0x138);
            if (eventType == 0)
                pThis->EventType = *(VocClass**)((char*)event + 0x24);
            *(AudioController**)((char*)event + 0x278) = pThis;
        }
    }
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x406130  (__thiscall)
//
// Return this controller's cached event pointer, but only after revalidating it
// against the live pool: the audio subsystem must be up, the handle live, and
// the event still the same one (its type and stamp unchanged). On any mismatch
// the stale pointer is cleared and null returned.
// ---------------------------------------------------------------------------
void* AudioController::GetEvent()
{
    if (g_AudioEnabled != 0 && this->AudioIndex == &AudioIDXData_Instance)
    {
        void* ev = this->Event;
        if (ev != 0)
        {
            if ((void*)this->EventType != *(void**)((char*)ev + 0x24) ||
                this->Stamp != *(unsigned int*)((char*)ev + 0x138))
            {
                ev = 0;
                this->Event = 0;
            }
        }
        return ev;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x406170  (__thiscall)
//
// The controller's bound event type, gated on the subsystem being up and the
// handle being live.
// ---------------------------------------------------------------------------
VocClass* AudioController::GetEventType()
{
    if (g_AudioEnabled != 0 && this->AudioIndex == &AudioIDXData_Instance)
        return this->EventType;
    return 0;
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x406310  (__fastcall: event=ECX)
//
// Read the type (VocClass*) directly out of a raw audio-event object. Not truly
// a controller method; co-located with the controller's event helpers.
// ---------------------------------------------------------------------------
VocClass* AudioController::GetEventType(void* event)
{
    return *(VocClass**)((char*)event + 0x24);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x87E294
AudioIDXData* AudioIDXData_Instance;
// GLOBAL: GAMEMD 0x87E2A0
void* g_AudioEnabled;
// END defined globals
