// SPDX-License-Identifier: GPL-3.0-or-later
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Provenance: own-binary-via-Ghidra
// Full entry-origin spans establish the accesses; source ownership and names
// remain unknown. The table and pointer result are address-scoped ABI views.
#include <stddef.h>
#include "mathtbl_init_shapes.h"
#include "../_rt/gg_static_assert.h"
GG_STATIC_ASSERT(sizeof(unsigned int) == 4);
GG_STATIC_ASSERT(sizeof(void*) == 4);

struct TableRow_00473940
{
    void* first;
    unsigned char unknown_04[4];
};
GG_STATIC_ASSERT(offsetof(TableRow_00473940, first) == 0);
GG_STATIC_ASSERT(offsetof(TableRow_00473940, unknown_04) == 4);
GG_STATIC_ASSERT(sizeof(TableRow_00473940) == 8);

// GLOBAL: GAMEMD 0x0081B7C8 (observed 11-row prefix, stride 8; first dword read at 0x473945)
extern "C" TableRow_00473940 Table_0081B7C8[11];
// STRING: GAMEMD 0x00817474
extern "C" char STR_00817474[];
// GLOBAL: GAMEMD 0x0089E280 (dword cleared by 0x4739D0)

// FUNCTION: GAMEMD 0x00473940
// ECX carries the index, EAX carries the selected pointer; fastcall is the
// candidate C++ ABI binding, not a claim about the original source declaration.
extern "C" void* FUN_00473940(unsigned int index)
{
    if (index < 11) return Table_0081B7C8[index].first;
    return (void*)STR_00817474;
}

// SYNTHETIC: GAMEMD 0x004739D0
// GLOBAL: GAMEMD 0x0089E280
MathTblZero4 DAT_0089E280;
