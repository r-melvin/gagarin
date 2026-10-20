// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes read off the user's retail gamemd.exe v1.001 via the local Ghidra CLI
//   at 0x6ABC60. Signature taken from YRpp SidebarClass.h
//   (`static int __fastcall GetObjectTabIdx(AbstractType, int, int)`,
//   consult-only, no LICENSE) and confirmed by the bytes: the discriminant
//   arrives in ECX and retail cleans four bytes (`RET 4`), which is the
//   three-argument __fastcall shape — ECX, EDX, one stack slot. Neither of the
//   trailing two arguments is read.
#ifndef GG_MATCH_UI_SIDEBAR_CLASS_TAB_METHODS_H
#define GG_MATCH_UI_SIDEBAR_CLASS_TAB_METHODS_H

// AbstractType discriminants this switch tests (YRpp GeneralDefinitions.h).
#define ABS_UNIT           0x01
#define ABS_AIRCRAFT       0x02
#define ABS_BUILDING       0x03   // note: the *type* discriminant, not ABS_BUILDING(6)
#define ABS_BUILDINGTYPE   0x06
#define ABS_AIRCRAFTTYPE   0x07
#define ABS_INFANTRYTYPE   0x0F
#define ABS_UNITTYPE       0x10
#define ABS_SUPERWEAPON    0x1F
#define ABS_ABSTRACTTYPE   0x20
#define ABS_INFANTRY       0x28
#define ABS_BUILDINGTYPE2  0x39

// The current sidebar/production context, at 0x005004E0 — takes no arguments
// (retail pushes nothing and does not set ECX) and returns an int the caller
// compares against 5. Descriptive name; the address carries no confirmed
// Westwood one.
int __fastcall GetCurrentSidebarContext();

struct SidebarClass
{
    // GAMEMD 0x6ABC60
    static int __fastcall GetObjectTabIdx(int abs, int idxType, int unused);
};

#endif  // GG_MATCH_UI_SIDEBAR_CLASS_TAB_METHODS_H
