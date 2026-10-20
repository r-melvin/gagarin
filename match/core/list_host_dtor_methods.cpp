// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x40E3E0 and 0x40E4C0.

#include "list_host_dtor_methods.h"

// FUNCTION: GAMEMD 0x40E3E0
//
// The scalar deleting destructor: drain the list hanging off the first embedded
// node, then destroy the two nodes in reverse declaration order, then free the
// object itself only if bit 0 of the flags is set.
//
// The drain loop is written as `while (1) { if (!(guard)) break; body }`, with
// the negation wrapping the WHOLE conjunction. That is what gives retail's
// unconditional `JMP` back to the memory test at the top. A plain
// `while (guard)` over the same three clauses rotates — cl duplicates the
// reload and one test at the bottom — and scores 25.7%; so do the `goto`
// spelling and the per-clause `for (;;) { if (a) break; if (b) break; ... }`
// form. Earlier attempts on the rotation that changed nothing or made it
// worse: `__forceinline` on Unlink/Dtor (no change), a volatile first clause
// (11.3%), and `/O1` and `/Ox /Os` (both outline the helpers). Same lever as
// 0x5B46E0 in match/ui/ui_list_node_methods.cpp.
//
// The guard is deliberately written as three reads of `this->A.Next` rather
// than through a local. Holding the first element in a local lets VC6 merge
// the guard's tests with the ones inside Unlink, dropping three comparisons
// retail emits and taking the score to 4.4%. Retail evaluates both sets.
// Routing the body's unlink through an out-of-line twin instead of the inline
// member collapses the guard entirely.
//
// Draining unlinks the *first* element each time and the guard re-reads it,
// because that is what retail does — `[EDI+8]` is reloaded at the top of every
// iteration (0x40E3EC). Unlink re-tests all three pointers the guard has just
// tested; both copies are retail's.
Host_0040E3E0* Host_0040E3E0::Destroy(int flags)
{
    this->Vptr = VTBL_007E1B04;

    while (1) {
        if (!(this->A.Next != 0 && this->A.Next->Next != 0
              && this->A.Next->Prev != 0)) {
            break;
        }
        this->A.Next->Unlink();
    }

    this->B.Dtor();
    this->A.Dtor();

    if (flags & 1) {
        FUN_007C8B3D(this);
    }
    return this;
}

// FUNCTION: GAMEMD 0x40E4C0
//
// The second instantiation, written out longhand rather than shared with the
// one above.
Host_0040E4C0* Host_0040E4C0::Destroy(int flags)
{
    this->Vptr = VTBL_007E1B04;

    while (1) {
        if (!(this->A.Next != 0 && this->A.Next->Next != 0
              && this->A.Next->Prev != 0)) {
            break;
        }
        this->A.Next->Unlink();
    }

    this->B.Dtor();
    this->A.Dtor();

    if (flags & 1) {
        FUN_007C8B3D(this);
    }
    return this;
}
