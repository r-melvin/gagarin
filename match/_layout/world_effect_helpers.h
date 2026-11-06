// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Free engine helpers that the animation, bomb and capture bodies call. Signatures read off the
//   retail call sites: 0x489280 is called with a coordinate pointer in ECX and the damage in EDX plus four stack
//   words (RET 0x10, so the area-damage routine); 0x48A4F0 with the damage in ECX, the warhead in EDX and two stack
//   words (RET 8); 0x48ACE0 takes a coordinate by value on the stack (RET 0xC) and returns the constant -15;
//   0x750D40 takes the coordinate in ECX and an audio controller in EDX. Names are placeholders.
#ifndef GG_MATCH_LAYOUT_WORLD_EFFECT_HELPERS_H
#define GG_MATCH_LAYOUT_WORLD_EFFECT_HELPERS_H

#include "coord_struct.h"
#include "audio_controller.h"

class AnimTypeClass;
class TechnoClass;
class WarheadTypeClass;

// FUNCTION: GAMEMD 0x489280 (decl; reloc) -- area damage around a coordinate: damage, source, warhead, two flags.
void __fastcall FUN_00489280(CoordStruct* where, int damage, TechnoClass* source, WarheadTypeClass* warhead,
                             bool flagA, bool flagB);
// FUNCTION: GAMEMD 0x48A4F0 (decl; reloc) -- the impact animation type for a damage, a warhead, a land type and a spot.
AnimTypeClass* __fastcall FUN_0048A4F0(int damage, WarheadTypeClass* warhead, int landType, const CoordStruct* where);
// FUNCTION: GAMEMD 0x48ACE0 (decl; reloc) -- the height adjustment for an impact at a coordinate (always -15).
int __stdcall FUN_0048ACE0(CoordStruct where);
// FUNCTION: GAMEMD 0x750D40 (decl; reloc) -- play or stop the sound of an audio controller at a coordinate.
void __fastcall FUN_00750D40(const CoordStruct* where, AudioController* controller);

#endif  // GG_MATCH_LAYOUT_WORLD_EFFECT_HELPERS_H
