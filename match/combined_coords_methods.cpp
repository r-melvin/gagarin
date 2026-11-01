// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x422BE0.

#include "combined_coords_methods.h"

// FUNCTION: GAMEMD 0x422BE0
//
// This object's coordinate, offset by whatever it is attached to. With nothing
// attached the object's own coordinate is returned unchanged.
//
// PARTIAL (36.5%, 19/52). One instruction of ours retail lacks, plus a stack
// slot and some register naming.
//
// The slot difference is the interesting part. Retail gives the two coordinate
// temporaries separate slots (+0x8 and +0x14); VC6 merges them into one and
// spends the freed slot on the result temporary. It can do that because it does
// not see that the pointer each helper returns aliases the local just passed in —
// once the call returns, the local looks dead. Retail's build keeps them apart.
// Swapping the declaration order moves which one wins but does not unmerge them,
// and reading the results through the locals by name instead of the returned
// pointers would contradict retail, which reads through EAX and ESI.
//
// The extra instruction is the return value: retail loads the hidden buffer
// pointer into EAX and copies it to EDI, so EAX already holds the return; VC6
// loads it into ESI and adds a `MOV EAX,ESI` at the end.
//
// Lift pass (2026-09-18): the X sum was written `b->X + a->X` and is now
// `a->X + b->X`, which makes retail's `MOV ECX,[EAX]; MOV EDX,[ESI]` pair exact
// (the vcall result is loaded first). Y and Z are NOT source-selectable - both
// operand orders emit the identical commutative add with the roles swapped
// against retail, the same class as the banked inlined-AddItem growth add.
// Also rejected this pass: a 3-argument constructor return
// (`return Coord_00422BE0(a->X + b->X, ...)`), which removes the `result` local
// and its slot but loses the X ordering and still lands the two coordinate
// temporaries at +0x14/+0x8 instead of +0x8/+0x14 (32.7%); and swapping the
// declaration order of `mine`/`theirs`, which changes nothing at all. Net 36.5%
// either way, with the X pair now structurally right.
//
// Both helpers are declared as returning a pointer into a caller-supplied buffer
// rather than returning the struct by value. Retail passes the address of a local
// and then uses the returned pointer directly; a by-value declaration would make
// VC6 generate its own temporary and copy out of it.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply here.
// Retail's callee-saved pushes sit exactly where ours do (prologue ESI, EDI on
// both sides, none sunk), the
// number of epilogues agrees, and the compiled block order already matches,
// so there are no merged return blocks to split. The residual is register
// naming downstream of that, not a prologue hoist.
Coord_00422BE0 AnimClass_00422BE0::FUN_00422BE0()
{
    Coord_00422BE0 mine;
    Coord_00422BE0 theirs;
    Coord_00422BE0 result;

    if (this->Attach != 0) {
        Coord_00422BE0* a = this->FUN_005F65A0(&mine);
        Coord_00422BE0* b = (this->Attach->*this->Attach->Vptr->At_48)(&theirs);

        result.X = a->X + b->X;
        result.Y = a->Y + b->Y;
        result.Z = a->Z + b->Z;
        return result;
    }

    Coord_00422BE0* own = this->FUN_005F65A0(&theirs);
    return *own;
}
