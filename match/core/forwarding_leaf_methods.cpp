// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Small forwarding bodies that repeat at two or more retail addresses. Each
// address is compiled and checked on its own; the copies differ in the callee
// or the table. Owners that are not modelled elsewhere are placeholders
// `Obj_<ADDR>` declaring only the callees the body uses, which are named by
// address.

const char* FUN_0048E030(unsigned int index);
const char* FUN_0048E090(unsigned int index);

#include "../_layout/obj_00477020.h"
// FUNCTION: GAMEMD 0x00477020
void Obj_00477020::FUN_00477020(int a, int b, unsigned int c)
{
    FUN_00528660(a, b, FUN_0048E030(c));
}

#include "../_layout/obj_004770b0.h"
// FUNCTION: GAMEMD 0x004770B0
void Obj_004770B0::FUN_004770B0(int a, int b, unsigned int c)
{
    FUN_00528660(a, b, FUN_0048E090(c));
}

#include "../_layout/obj_005175e0.h"

#include "../_layout/rec_00549b50.h"
#include "../_layout/obj_00549b50.h"

#include "../_layout/obj_006ea4f0.h"

#include "../_layout/obj_007719c0.h"
// FUNCTION: GAMEMD 0x007719C0
bool Obj_007719C0::FUN_007719C0()
{
    return !FUN_007529E0();
}
