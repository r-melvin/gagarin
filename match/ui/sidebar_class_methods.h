// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Logic + calling convention derived from the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI (disasm at 0x6ABCD0), cross-checked
//   against YRpp SidebarClass.h `GetObjectTabIdx` (consult-only; reconfirmed).
//
// SidebarClass::GetObjectTabIdx — a static __fastcall classifier mapping an
// AbstractType id (+ build category) to a build-tab index. It touches no
// instance members (the args arrive in ECX/EDX + one stack slot), so no
// SidebarClass layout is modelled here.
#ifndef GG_MATCH_UI_SIDEBAR_CLASS_METHODS_H
#define GG_MATCH_UI_SIDEBAR_CLASS_METHODS_H

struct SidebarClass
{
    // GAMEMD 0x6ABC60. Distinct classifier; the original name is unconfirmed.
    // Shares the fastcall ABI, but not the body, of GetObjectTabIdx below.
    static int __fastcall FUN_006ABC60(int abs, int idxType, int unused);

    // GAMEMD 0x6ABCD0  SidebarClass::GetObjectTabIdx (static __fastcall)
    //   abs      -> ECX   (AbstractType id)
    //   buildCat -> EDX   (BuildCat)
    //   isNaval  -> stack  (unused in this overload; RET 0x4 cleans it)
    static int __fastcall GetObjectTabIdx(int abs, int buildCat, int isNaval);
};

#endif  // GG_MATCH_UI_SIDEBAR_CLASS_METHODS_H
