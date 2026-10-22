// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Complete bodies are confirmed from each retail entry. The reset uses four
// absolute dword stores; the remaining routines are x87 qword loads, arithmetic
// and stores, with calls only where the retail instructions show them.
#include "periodic_state_updates_00439480.h"

// FUNCTION: GAMEMD 0x004CAD50 (decl; reloc)
extern "C" double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x004CADE0 (decl; reloc)
extern "C" double __cdecl FUN_004CADE0(double value);
// LIBRARY: GAMEMD 0x007C5F00 — VC6 __ftol runtime
// VC6 emits this retail x87-control-word rounding helper for __int64 conversion.

// FUNCTION: GAMEMD 0x00439480
void __stdcall FUN_00439480()
{
    DAT_0089C708 = 0;
    DAT_0089C70C = 0;
    DAT_0089C710 = 0;
    DAT_0089C714 = 0;
}

// FUNCTION: GAMEMD 0x004394D0
void __stdcall FUN_004394D0()
{
    DAT_0089C770 = DAT_0089C720 / DAT_007E3D70;
}

// FUNCTION: GAMEMD 0x004394F0
void __stdcall FUN_004394F0()
{
    DAT_0089C758 = DAT_007E1718 / DAT_0089C770;
}

// FUNCTION: GAMEMD 0x00439510
void __stdcall FUN_00439510()
{
    DAT_0089C750 = DAT_007E1720 * DAT_007E3D78;
}

// FUNCTION: GAMEMD 0x00439530
void __stdcall FUN_00439530()
{
    DAT_0089C728 = DAT_007E1728 * DAT_007E3D78;
}

// FUNCTION: GAMEMD 0x00439550
void __stdcall FUN_00439550()
{
    DAT_0089C700 = DAT_007E1730 * DAT_007E3D78;
}

// FUNCTION: GAMEMD 0x00439570
void __stdcall FUN_00439570()
{
    DAT_0089C778 = static_cast<int>(static_cast<__int64>(
        FUN_004CAD50(DAT_0089C700 - DAT_0089C728) * DAT_007E1738 * DAT_0089C720));
}

// FUNCTION: GAMEMD 0x004395B0
void __stdcall FUN_004395B0()
{
    DAT_0089C730 = FUN_004CADE0(
        static_cast<double>(DAT_0089C778) * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x004395E0
void __stdcall FUN_004395E0()
{
    DAT_0089C748 = FUN_004CADE0(
        static_cast<double>(DAT_0089C778 * 2) / DAT_0089C720);
}
