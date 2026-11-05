// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes read from retail gamemd.exe v1.001 at 0x683560 (ScenarioClass::ScenarioClass(const AbstractNoInit&)).
//   PLACEMENT LEAD (inference): retail reaches the capacity constructors of the three TypeList members
//   (0x68C200, 0x477DB0 twice) by a real CALL and then stores the list vptr itself. At /Ob2 cl
//   inlines any body it can see, so the retail calls imply those constructor bodies were not visible
//   where this function was compiled. This file includes scenario_class.h (vector_class.h
//   declarations only), never vector_class_operations.h, so it is a separate object from
//   match/Scenario.cpp; the original file name is not known and is not claimed.
#include "scenario_class.h"
#include "conn_types.h"   // EmptyName_00887734 (GLOBAL: GAMEMD 0x887734)

// STRING: GAMEMD 0x83D838 "D:\ra2mdpost\Scenario.CPP"
extern const char STR_0083D838[];
// FUNCTION: GAMEMD 0x734E60 (decl; reloc)
const wchar_t* __fastcall FUN_00734E60(const char* id, int zero, const char* file, int line);

// TUSPLIT: GAMEMD 0x683560 same-file 0.0% separate 100.0%
// FUNCTION: GAMEMD 0x683560
ScenarioClass::ScenarioClass(const AbstractNoInit& noInit)
    : unknown_0218(0), unknown_0614(noInit), unknown_11F8(noInit)
{
    // The incoming one-word argument is unused in retail; the existing tag
    // expresses the observed selective preservation, not a recovered type name.
    if (unknown_11F8.unknown_00[0])
        unknown_11F4 = FUN_00734E60(unknown_11F8.unknown_00, 0, STR_0083D838, 0x158);
    else
        unknown_11F4 = EmptyName_00887734;
}
