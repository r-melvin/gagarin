// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x4294B0 (reads the string at +0x125C of the object behind 0xA8B230).
//
// ApplicationClass slot 6: returns the current scenario's file name as a BSTR.
// Address index: 0x4294B0 ApplicationClass::vf_6.

#include <windows.h>
#include <oleauto.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/application_class.h"


// GLOBAL: GAMEMD 0xA8B230
#include "scenario_class_methods.h"
extern ScenarioClass* DAT_00A8B230;

// FUNCTION: GAMEMD 0x4294B0
HRESULT __stdcall ApplicationClass::vf_6(BSTR* pbstr)
{
    WCHAR wide[32];
    if (pbstr == 0)
        return E_POINTER;
    MultiByteToWideChar(0, MB_PRECOMPOSED, DAT_00A8B230->unknown_125C, -1, wide, 32);
    *pbstr = SysAllocString(wide);
    return S_OK;
}
