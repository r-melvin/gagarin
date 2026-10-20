// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x53E3C0 / 0x53E420 via
//   the local Ghidra disassembly. Global addresses confirmed numerically from
//   the absolute operands (see the header).
//
// The registered-window table: add at 0x53E3C0, remove at 0x53E420. Both walk
// the same table under the same guard and differ only in what they do on a hit.
// Functions ordered ascending by retail address.
//
// CORRECTION: 0x53E420 was previously committed as `Streamer_ReleaseHandle` in
// match/audio/streamer_slot_methods.cpp, on the reading that the table held
// audio-streamer handles. The call sites disprove that — see the header for the
// USER32 evidence. The function body is carried over unchanged (it was and
// remains a 100% match); only the names and the file it lives in have moved,
// and its sibling at 0x53E3C0 now sits beside it.

#include "debug_window_list_methods.h"

// FUNCTION: GAMEMD 0x53E3C0
// Insert `window` into the first free slot, unless it is already registered.
// The scan does both jobs in one pass: it remembers the first empty slot it
// walks over (EDI) while still checking every occupied slot for a duplicate,
// so a handle that is already present costs no insert and no count bump. That
// idempotence is relied on at 0x618428, which calls this twice in a row on the
// same handle.
//
// The bound is read straight out of the global in the loop condition rather
// than through a local. That is not a style choice: with a local, VC6 gives it
// EBX and `freeSlot` EDI, which is the exact opposite of retail's assignment
// and costs 8 of 37 instructions. Left as an invariant for the optimiser to
// hoist, the bound becomes a compiler temp and lands in EBX as retail has it.
// The remove path below wants the opposite — same table, same walk, but there
// the *local* form is the one that matches.
void __fastcall FUN_0053E3C0(void* window)
{
    if (DebugWindowListActive == 0 || window == 0) {
        return;
    }

    void** freeSlot = 0;
    void** slot = DebugWindowList;

    for (int i = 1; i < DebugWindowListCapacity; i++, slot++) {
        void* entry = *slot;
        if (entry == 0) {
            if (freeSlot == 0) {
                freeSlot = slot;
            }
        } else if (entry == window) {
            return;
        }
    }

    if (freeSlot != 0) {
        *freeSlot = window;
        DebugWindowListCount++;
    }
}

// FUNCTION: GAMEMD 0x53E420
// Find the slot holding this handle, clear it, and drop the live count. Unlike
// the add path there is no free-slot bookkeeping — the scan stops at the first
// match, and a handle that is not registered leaves the table untouched.
//
// The scan stops one short of the end, and the shape of that is load-bearing:
// retail walks a pointer from slot 0 while a *1-based* counter is compared
// against the slot count. Writing it as `i < count - 1` over an indexed array
// makes VC6 materialise `count - 1` in a register and scores 6.7%; the pointer
// plus 1-based counter scores 92%, and moving `slot++` into the for-increment
// after `i++` orders the two adds the way retail has them for the last 8%.
void __fastcall FUN_0053E420(void* window)
{
    if (!DebugWindowListActive)
        return;

    if (window == 0)
        return;

    int    count = DebugWindowListCapacity;
    void** slot  = DebugWindowList;

    for (int i = 1; i < count; i++, slot++)
    {
        if (*slot == window)
        {
            *slot = 0;
            DebugWindowListCount--;
            return;
        }
    }
}
