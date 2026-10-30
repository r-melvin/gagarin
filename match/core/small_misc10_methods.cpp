// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc10_methods.h"

// FUNCTION: GAMEMD 0x410230
// The value comes from an inlined helper rather than being assigned directly:
// retail materialises the zero into a register before storing
// (`XOR EAX,EAX; MOV [ECX+0xC],EAX`), which is the inlined-return shape, where
// a plain `sink->at0C = 0;` stores the immediate.
static inline int ProviderValue_00410230()
{
    if (DAT_00A8B230 == 0) {
        return 0;
    }

    return FUN_0068BCB0(DAT_00A8B230);
}

void __stdcall FUN_00410230(Sink_00410230* sink)
{
    sink->at0C = ProviderValue_00410230();
}

// FUNCTION: GAMEMD 0x41ADC0
// The pointer is reloaded after the complaint rather than reused, so a null
// interface still gets dispatched on - the report is advisory and the crash
// that follows is the original behaviour.
void AircraftClass_0041ADC0::FUN_0041ADC0()
{
    if (unknown_674 == 0) {
        FUN_007DC720(0x80004003);
    }

    IFACE_CALL(unknown_674, 0x74);
}

// FUNCTION: GAMEMD 0x429420
// STRING: GAMEMD 0x8186E8  L"Tiberian Sun"
long __stdcall FUN_00429420(void*, unsigned short** out)
{
    if (out == 0) {
        return 0x80004003;
    }

    *out = SysAllocString((const unsigned short*)L"Tiberian Sun");

    return 0;
}

// FUNCTION: GAMEMD 0x429450
// STRING: GAMEMD 0x818704  L"Sun"
long __stdcall FUN_00429450(void*, unsigned short** out)
{
    if (out == 0) {
        return 0x80004003;
    }

    *out = SysAllocString((const unsigned short*)L"Sun");

    return 0;
}
