// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. Import identified from the IAT
//   thunk at 0x7E1368 (OLEAUT32 ordinal 2 = SysAllocString). None of these
//   addresses is bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC10_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC10_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "guarded_forward_methods.h"

// OLEAUT32 ordinal 2. dllimport so the call goes indirect through the IAT.
extern "C" __declspec(dllimport) unsigned short* __stdcall
    SysAllocString(const unsigned short* s);

// __stdcall, one argument; called with E_POINTER when a required out-parameter
// is missing.
void __stdcall FUN_007DC720(unsigned int hr);

// GLOBAL: GAMEMD 0xA8B230 — the provider consulted by 0x410230.
struct Provider_00A8B230;
extern Provider_00A8B230* DAT_00A8B230;
int __fastcall FUN_0068BCB0(Provider_00A8B230* self);   // GAMEMD 0x68BCB0

struct Sink_00410230 { char _pad[0xC]; int at0C; };

// FUNCTION: GAMEMD 0x410230 — publish the provider's value, or zero when there
// is no provider.
void __stdcall FUN_00410230(Sink_00410230* sink);

// CLASS IDENTITY (whole-image RTTI sweep; renamed from
// the raw `Obj_`/`Sub_`/`Subject_` placeholder). AircraftClass's own vtable is 0x7E22A4.
//   0x41ADC0 -> AircraftClass slot 30 (byte-off 0x78).
// That table is the only table in the image that holds it, so the slot is
// declared on AircraftClass and not inherited from TechnoClass/ObjectClass above it.
// The METHOD name is still unknown; only the class is proven, so the
// `FUN_<addr>` member name stays as the transitional placeholder.
struct AircraftClass_0041ADC0
{
    char   _pad000[0x674];
    IFace* unknown_674;   // +0x0674

    // FUNCTION: GAMEMD 0x41ADC0
    void FUN_0041ADC0();
};
GG_STATIC_ASSERT(offsetof(AircraftClass_0041ADC0, unknown_674) == 0x674);

// PLACEHOLDER DELIBERATELY KEPT (whole-image RTTI sweep).
// 0x429420 and 0x429450 are slots 3 and 4 (byte-off 0x0C, 0x10) of
// ApplicationClass's own vtable 0x7E36D4, and appear in no other table --
// ApplicationClass : IApplication : IUnknown, and the two interfaces carry no
// locator, so ApplicationClass is where these are declared. They are still
// spelled as free `__stdcall` functions because that IS the retail shape: the
// receiver arrives as the first stack argument and is never touched, so there
// is no object parameter to attach the class to without changing the modelled
// signature. Class recorded here; the symbol stays `FUN_<addr>`.
// Two BSTR name getters. Byte-identical apart from the literal, and written out
// separately per the family rule.
// FUNCTION: GAMEMD 0x429420
long __stdcall FUN_00429420(void* unused, unsigned short** out);
// FUNCTION: GAMEMD 0x429450
long __stdcall FUN_00429450(void* unused, unsigned short** out);

#endif  // GG_MATCH_CORE_SMALL_MISC10_METHODS_H
