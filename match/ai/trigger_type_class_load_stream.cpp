// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x727BF0 (same shape as TagTypeClass::Load).
//
// TriggerTypeClass slot 5: load from a stream, rebuild the object and queue its four
// pointer fields for swizzling.
// Address index: 0x727BF0 Load.

#include <new.h>
#include "../_layout/trigger_type_class.h"
#include "../_layout/swizzle_manager_class.h"

// FUNCTION: GAMEMD 0x727BF0
HRESULT __stdcall TriggerTypeClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0)
        return hr;
    new (this) TriggerTypeClass(AbstractNoInit());
    DAT_00B0C110.SwizzleManagerClass::vf_4(&NextTrigger);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&FirstEvent);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&FirstAction);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&House);
    return 0;
}

// SYNTHETIC: GAMEMD 0x727CD0 -- TriggerTypeClass scalar deleting destructor, emitted by the compiler from the virtual destructor
