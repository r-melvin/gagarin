// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x6D20E0 (Ghidra disasm).
//   Cross-checked against YRpp (consult-only, no LICENSE;
//   each address reconfirmed against the user's binary).
//
// Translation unit: TacticalClass::AdjustForZ (the in-game height -> on-screen
// pixel-offset conversion). Free static __fastcall(int) helper (Height in ECX).
#ifndef GG_MATCH_UI_TACTICAL_CLASS_METHODS_H
#define GG_MATCH_UI_TACTICAL_CLASS_METHODS_H

// The owning class. Nothing at this address touches an instance, so no layout
// is recovered here; the struct exists so the routine is spelled as the static
// member it is rather than as a free function, and so the next address on this
// class has somewhere to attach.
struct TacticalClass
{
    // in-game Z height -> on-screen vertical pixel offset.
    //   reccmp: FUNCTION: GAMEMD 0x6D20E0  TacticalClass::AdjustForZ
    //   (static __fastcall: the height arrives in ECX).
    static int __fastcall AdjustForZ(int Height);
};

#endif  // GG_MATCH_UI_TACTICAL_CLASS_METHODS_H
