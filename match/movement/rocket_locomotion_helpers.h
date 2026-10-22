// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; entry addresses and call ABIs from Rocket callers.
#ifndef GG_MATCH_MOVEMENT_ROCKET_LOCOMOTION_HELPERS_H
#define GG_MATCH_MOVEMENT_ROCKET_LOCOMOTION_HELPERS_H
#include "loco_interfaces.h"
// FUNCTION: GAMEMD 0x427CB0 (decl; reloc), __fastcall, name in ECX.
int LocoAnimTypeFindIndex(const char* name);
// FUNCTION: GAMEMD 0x7509E0 (decl; reloc), __fastcall, sample in ECX, coordinate in EDX, RET 4.
void LocoPlaySample(void* sample,LocoCoord* where,int zero);
#endif
