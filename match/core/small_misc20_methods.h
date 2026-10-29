// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC20_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC20_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "intrusive_list_methods.h"
#include "guarded_forward_methods.h"

void __stdcall FUN_007DC720(unsigned int hr);

// A COM slot taking three arguments.
typedef long (__stdcall* Slot3)(IFace*, int, int, int);
#define IFACE_CALL3(p, slot, x, y, z) \
    ((*(Slot3*)(*(char**)(p) + (slot)))(p, x, y, z))

// GLOBAL: GAMEMD 0x87E81C — the gate; 0x87E810 is the list header itself.
extern int      DAT_0087E81C;
extern ListNode DAT_0087E810;

struct Counted_00408200 { char _pad[0x88]; int at88; };

// FUNCTION: GAMEMD 0x408200 — bump a counter on every live list entry.
void __cdecl FUN_00408200();

// The same walk, driving a helper on each entry's sub-object instead.
struct Holder_00408390 { char _pad[0x14]; char* at14; };
void FUN_00407170b(void* self, int arg);   // GAMEMD 0x407170

// FUNCTION: GAMEMD 0x408390
void __cdecl FUN_00408390();
// FUNCTION: GAMEMD 0x4083D0 — the same walk with a different argument.
void __cdecl FUN_004083D0();

#endif  // GG_MATCH_CORE_SMALL_MISC20_METHODS_H
