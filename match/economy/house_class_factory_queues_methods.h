// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x509140. On the house (EBP): the five factory slots
//   `MOV ESI,[EBP+0x53AC]` (aircraft), `[EBP+0x53B0]` (infantry),
//   `[EBP+0x53B4]` / `[EBP+0x53B8]` (ground and naval units, selected by the
//   second parameter) and `[EBP+0x53BC]` / `[EBP+0x53CC]` (buildings,
//   selected by the third parameter being 5). On the factory (ESI):
//   `MOV EDX,[ESI+0x44]` / `MOV EAX,[ESI+0x50]` (the queue's Items and Count),
//   `MOV ECX,[ESI+0x58]` (the object in production), `MOV AL,[ESI+0x70]` and
//   `MOV AL,[ESI+0x71]`, and the vtable slot `CALL [EAX+0x20]`. The queued
//   items and the produced object's type are asked through slot 0x94 with
//   four pushed arguments (1, 0/1, 1, house); the object itself through slot
//   0x84 (GetTechnoType). The player singleton is the dword global 0xA83D4C
//   compared straight against the house. Conventions off the call sites:
//   0x4C9FF0 and 0x4CA5A0 take only ECX, 0x4C9E60 and 0x4C9EA0 one pushed
//   argument (__thiscall); 0x6ABCD0 sets ECX and EDX with one push
//   (__fastcall); 0x6A60A0 is `MOV ECX,0x87F7E8` plus one push. The switch is
//   a jump table: `ADD EAX,-3; CMP EAX,0x25; JA default;
//   MOV CL,[EAX+0x5092C0]; JMP [ECX*4+0x5092AC]`, with the dword table
//   0x5092AC = {0x50919B, 0x509168, 0x509193, 0x50917F, 0x5092A3} and the
//   0x26-byte index table selecting RTTI 3, 7, 0x10 and 0x28 — the block
//   bodies are laid out in the source order 7, 0x28, 0x10, 3. The FactoryClass
//   offsets agree with match/economy/factory_class_methods.h (Items @0x44,
//   Count @0x50, Object @0x58, IsSuspended @0x70, IsManual @0x71). Names
//   cross-checked against YRpp HouseClass / FactoryClass
//   and re-derived here from the disassembly.
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_FACTORY_QUEUES_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_FACTORY_QUEUES_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "../_layout/map_0087f7e8.h"
#include "../_layout/house_class.h"
#include "../_layout/factory_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/player_ptr_00a83d4c.h"

// FUNCTION: GAMEMD 0x6ABCD0 (decl; reloc) — map the (rtti, build category,
// naval) triple to a sidebar tab. __fastcall: rtti in ECX, category in EDX.
unsigned int FUN_006ABCD0(int rtti, int buildCat, bool isNaval);

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_FACTORY_QUEUES_METHODS_H
