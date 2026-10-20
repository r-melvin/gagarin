// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm
//   0x708DC0 len 0x3D, 0x709020 len 0x3D, 0x709060 len 0x3D).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x708DC0  TechnoClass::VoiceCapture   (__thiscall)
//   FUNCTION: GAMEMD 0x709020  TechnoClass::VoiceEnter     (__thiscall)
//   FUNCTION: GAMEMD 0x709060  TechnoClass::VoiceHarvest   (__thiscall)
//
// Three near-identical voice-response virtuals. Each asks its own type for a
// voice index; if the type declares one it is queued, otherwise the object
// falls back to a different voice virtual. All three return void — the exit is
// a bare `RET` with nothing written to EAX or AL.

#include "techno_class_voice_methods.h"

// FUNCTION: GAMEMD 0x708DC0  (__thiscall)
// Voice played when this object captures something. Falls back to the
// enter-transport voice (slot +0x358) when the type declares no capture voice.
//
// The GetTechnoType dispatch appears twice in retail and that is literal: the
// guard reads the index and the queued call reads it again. Caching it in a
// local collapses the second dispatch and loses six instructions.
void TechnoClass::VoiceCapture()
{
    if ((this->*this->Vfptr->At_84)()->VoiceCapture != -1) {
        (this->*this->Vfptr->At_354)((this->*this->Vfptr->At_84)()->VoiceCapture);
    } else {
        (this->*this->Vfptr->At_358)();
    }
}

// FUNCTION: GAMEMD 0x709020  (__thiscall)
// Voice played when this object enters a transport or a structure. Falls back
// to the move voice (slot +0x368).
void TechnoClass::VoiceEnter()
{
    if ((this->*this->Vfptr->At_84)()->VoiceEnter != -1) {
        (this->*this->Vfptr->At_354)((this->*this->Vfptr->At_84)()->VoiceEnter);
    } else {
        (this->*this->Vfptr->At_368)();
    }
}

// FUNCTION: GAMEMD 0x709060  (__thiscall)
// Voice played when a harvester is sent to gather. Falls back to the move
// voice (slot +0x368), which is why an ore truck without a harvest voice still
// acknowledges the order.
void TechnoClass::VoiceHarvest()
{
    if ((this->*this->Vfptr->At_84)()->VoiceHarvest != -1) {
        (this->*this->Vfptr->At_354)((this->*this->Vfptr->At_84)()->VoiceHarvest);
    } else {
        (this->*this->Vfptr->At_368)();
    }
}
