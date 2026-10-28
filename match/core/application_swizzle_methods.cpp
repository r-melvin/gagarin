// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x429550 (pushes 0xB0C110, the id at 0x7E9B20 and its argument, calls 0x6CF430).
//
// ApplicationClass slot 8: hands out the swizzle interface of the global swizzle manager.
// Address index: 0x429550 ApplicationClass::vf_8.

#include "../_layout/application_class.h"
#include "../_layout/swizzle_manager_class.h"

// GLOBAL: GAMEMD 0x7E9B20
extern const GUID DAT_007E9B20;

// FUNCTION: GAMEMD 0x429550
HRESULT __stdcall ApplicationClass::vf_8(void** ppv)
{
    return DAT_00B0C110.SwizzleManagerClass::QueryInterface(DAT_007E9B20, ppv);
}
