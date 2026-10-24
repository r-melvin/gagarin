// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | own-binary-via-REA
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu158_methods.h"
#include "../platform/ccini_class_methods.h"
// GLOBAL: GAMEMD 0x8870C0 -- existing canonical INI owner.
extern CCINIClass DAT_008870C0;
extern const char STR_0082642C[]; // STRING: GAMEMD 0x82642C (decl; reloc)
extern const char STR_00830CC0[]; // STRING: GAMEMD 0x830CC0 (decl; reloc)
extern const char STR_00830CB0[]; // STRING: GAMEMD 0x830CB0 (decl; reloc)

// FUNCTION: GAMEMD 0x5D8FB0
// Stores several members.
Obj_005D8FB0* Obj_005D8FB0::FUN_005D8FB0()
{
    unknown_00 = 0;
    unknown_04 = 0;
    unknown_08 = 0;
    unknown_0C = 0;
    return this;
}

// FUNCTION: GAMEMD 0x5D93D0
void Obj_005D8FB0::FUN_005D93D0()
{
    unknown_04 = DAT_008870C0.FUN_005276D0(STR_0082642C, STR_00830CC0, 0);
    unknown_0C = DAT_008870C0.FUN_005276D0(STR_0082642C, STR_00830CB0, 1);
}
