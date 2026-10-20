// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x41C250.

#include "com_create_holder_methods.h"

// FUNCTION: GAMEMD 0x41C250
//
// Replace whatever the holder owns with a freshly created object.
//
// PARTIAL (42.9%, 24/56). Retail emits exactly two instructions we do not, and
// both are slack rather than work. A mnemonic-by-mnemonic comparison of the two
// streams differs only by one `MOV` and one `POP`:
//
//   * Retail saves ESI in the prologue (`PUSH ESI; PUSH EDI`); VC6 shrink-wraps
//     that save into the branch where the register is first needed, because in
//     its codegen the result variable's live range never leaves that branch.
//   * Retail's else branch ends with a dead `MOV ESI,EAX` at 0x41C2D1 — the
//     result variable's home is ESI and the copy is emitted even though EAX
//     already holds the value and the shared epilogue reads EAX. VC6 elides it.
//
// Because the prologue difference lands at instruction one, nothing downstream
// lines up and the score reflects the offset, not the delta. Four shapes were
// tried to pull the save forward — initialising the result to zero, holding the
// existing interface in a local, dropping the inner `return` so both paths reach
// one epilogue, and leaving it as written — and all four produce the identical
// shrink-wrap. See section 4.8.
// Lift pass (2026-09-18): `register long hr;` also produces the identical
// stream (42.9%). The delta is exactly two retail instructions - the prologue
// `PUSH ESI` and the dead `MOV ESI,EAX` at 0x41C2D1 - i.e. cl 8447 commits
// `hr`'s home to ESI for the whole function and emits the store in the else
// arm even though EAX already holds it, while cl 8804 sees the store is dead,
// drops it, and confines the ESI save to the branch that really needs it.
// Recorded as an 8447-vs-8804 shrink-wrap/dead-copy difference.
//
// Two creation paths, chosen by the context bits. The plain path asks
// CoCreateInstance for the wanted interface directly. When the context asks for
// anything out-of-process (the 0x14 bits) the object is created as IUnknown
// first, run with OleRun, and only then queried for the interface — an
// out-of-process server has to be started before its interfaces answer. The
// IUnknown is released either way, including when the query failed.
//
// The `outer` parameter's own stack slot is reused as the out-parameter for the
// first CoCreateInstance (`LEA EDX,[ESP+0x10]` at 0x41C26C is that slot). Its
// incoming value is still read afterwards, which is safe only because VC6 pushes
// arguments right to left: the address goes down first and the value is loaded
// after.
long Holder_0041C250::Create(const void* rclsid, IUnknown_0041C250* outer,
                             unsigned int context)
{
    long hr;

    if (Interface != 0) {
        Interface->Vtbl->Release(Interface);
    }

    if ((context & 0x14) != 0) {
        hr = CoCreateInstance(rclsid, outer, context, riid_00817BC0,
                              (void**)&outer);
        if (hr >= 0) {
            hr = OleRun(outer);
            if (hr >= 0) {
                hr = outer->Vtbl->QueryInterface(outer, riid_00817BB0,
                                                 (void**)this);
            }
            outer->Vtbl->Release(outer);
            return hr;
        }
    } else {
        hr = CoCreateInstance(rclsid, outer, context, riid_00817BB0,
                              (void**)this);
    }

    return hr;
}
