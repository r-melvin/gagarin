// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference
//   Bytes matched against retail gamemd.exe v1.001 at 0x43B680.

#include "four_vtable_host_ctor_methods.h"

// FUNCTION: GAMEMD 0x43B680
//
// Construct the host: run the base constructor, stamp the current frame, then
// bring up two empty growable vectors and install the four vtables.
//
// MATCHED (100.0%, 36/36). The residual — cl 8804 clustering the twenty
// stores by which constant register they use, emitting every zero store first
// and sinking the three that take the `1` to the end, where retail keeps
// source order and interleaves them — was the shape of the inlined vector
// bring-up, not a scheduling difference. Written flat in the constructor body
// the stores are one basic block cl is free to cluster; written as a free
// inline helper taking the vector as a pointer parameter, cl keeps each
// vector's seven stores in source order and reproduces retail exactly.
// 58.3% to 100%. Same lever as the inlined vector append at 0x41D300 and
// 0x6CB3A0: a container operation that retail inlined wants to be a function
// taking the container as a parameter.
//
// Variants measured this pass: the helper taking the vector and the three
// shared constants (100%, kept); the same helper materialising the constants
// itself (100%); the base four stores split into a second nested helper
// (100%); the vector parameter as `Vec_0043B680* const&` (100%); and a
// whole-struct assignment from a named `Vec_0043B680` temporary (0.0%, a
// 24-byte block copy). Earlier passes had tried three placements of the
// constants — declared together at the top, declared at first use, and the
// `1` spelled as a literal at each site — all 58.3%.
//
// The three constants are named variables. Retail materialises 0, 10 and 1 once
// each into EAX, EDX and ECX and reuses them across all twenty stores; written as
// literals they become immediates and the register set-up disappears.
//
// The vectors' base constructors are inlined here, not called: their four base
// stores appear literally in initialiser-list order and only then the derived
// vptr, GrowthStep and ActiveCount. Compare 0x412870, where the array entries
// call the base and only the trailing instance has it inlined.
static inline void InitVec_0043B680(Vec_0043B680* vec, int zero, int one, int ten)
{
    vec->Vector = (const void*)zero;
    vec->VectorMax = zero;
    vec->IsValid = (char)one;
    vec->IsAllocated = (char)zero;
    vec->Vptr = VTBL_007E43C8;
    vec->GrowthStep = ten;
    vec->ActiveCount = zero;
}

Host_0043B680* Host_0043B680::Ctor(int arg)
{
    this->BaseCtor(arg);

    int zero = 0;
    int ten = 10;

    this->At_620 = zero;
    this->At_624 = (char)zero;
    int stamp = DAT_00A8ED84;
    this->At_630 = zero;
    this->Stamp = stamp;

    int one = 1;
    this->At_634 = zero;
    this->At_638 = one;

    InitVec_0043B680(&this->FirstVec, zero, one, ten);
    InitVec_0043B680(&this->SecondVec, zero, one, ten);

    this->Vptr0 = VTBL_007E3EBC;
    this->Vptr1 = VTBL_007E3EA0;
    this->Vptr2 = VTBL_007E3E98;
    this->Vptr3 = VTBL_007E3E90;
    return this;
}
