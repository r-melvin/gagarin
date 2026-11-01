// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// One-argument members that pass their argument to another member of the same
// object (ECX untouched, so the callee takes the same `this`) and return what
// that call leaves behind. 0x770E60 forwards to 0x7B4940. The owner is not
// modelled elsewhere, so it is a placeholder `Obj_<ADDR>` that declares the
// callee (bound by address) and nothing else.

struct Obj_00770E60
{
    void FUN_007B4940(int);
    void FUN_00770E60(int a1);
};

// FUNCTION: GAMEMD 0x770E60
void Obj_00770E60::FUN_00770E60(int a1)
{
    FUN_007B4940(a1);
}
