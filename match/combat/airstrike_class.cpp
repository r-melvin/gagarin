// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The AirstrikeClass block of retail .text (0x41D070..0x41DDDF): three of the
// unit's run-time initialisers, the no-initialisation constructor, the
// destructor, two small state helpers and the primary-table slots 5, 8, 11, 12
// and 23, in retail address order. AirstrikeClass is declared in
// airstrike_class_methods.h.

#include "../FUNCTION.H"
#include "airstrike_class_methods.h"
#include "../core/vector_class_operations.h"
#include "../core/frame_counter.h"
#include "../movement/locomotion_load_support.h"
#include "../core/header_tuning_globals.h"

// ---- run-time initialised copies of the shared tuning globals -----------------------------------------------------

// GLOBAL: GAMEMD 0x889F88
extern double DAT_00889F88;
// GLOBAL: GAMEMD 0x7E2928
const double DAT_007E2928 = 60.0;

// SYNTHETIC: GAMEMD 0x41D0A0
// GLOBAL: GAMEMD 0x889FF0
double DAT_00889FF0 = DAT_00889F88 / DAT_007E2928;
// SYNTHETIC: GAMEMD 0x41D0C0
// GLOBAL: GAMEMD 0x889FD8
double DAT_00889FD8 = 1.0 / DAT_00889FF0;
// SYNTHETIC: GAMEMD 0x41D240
// GLOBAL: GAMEMD 0x889FE0
TuningCoordInit DAT_00889FE0(128, 128, 0);

// FUNCTION: GAMEMD 0x41D490
AirstrikeClass::AirstrikeClass(const AbstractNoInit& noInit) : AbstractClass(noInit)
{
}

// FUNCTION: GAMEMD 0x41D4C0
AirstrikeClass::~AirstrikeClass()
{
    Array.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x41D6F0
HRESULT __stdcall AirstrikeClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr >= 0) {
        new (this) AirstrikeClass(AbstractNoInit());
        DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_4C);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Target);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_54);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_58);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_5C);
    }
    return hr;
}

// FUNCTION: GAMEMD 0x41DC50
void AirstrikeClass::vf_23()
{
}

// FUNCTION: GAMEMD 0x41DC60
void AirstrikeClass::FUN_0041DC60()
{
    if (++unknown_34 >= unknown_30) {
        unknown_3D = false;
    }
}

// FUNCTION: GAMEMD 0x41DD10
void AirstrikeClass::FUN_0041DD10()
{
    unknown_40 = CurrentFrame;
    unknown_3C = false;
    unknown_3D = false;
}

// FUNCTION: GAMEMD 0x41DD30
int AirstrikeClass::vf_12()
{
    return sizeof(AirstrikeClass);
}

// FUNCTION: GAMEMD 0x41DD40
int AirstrikeClass::vf_11()
{
    return 0x47;
}

// FUNCTION: GAMEMD 0x41DD50
// The scalar deleting destructor the compiler emits for ~AirstrikeClass (slot 8).
