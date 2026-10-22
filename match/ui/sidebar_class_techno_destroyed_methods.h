// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x6A5F20. On the sidebar (EDI): `MOV AL,[EDI+0x53A5]`
//   (the "sidebar is up" byte), `MOV ECX,[EDI+0x539C]` (the active tab, the
//   same member as match/ui/sidebar_class_set_tab_methods.h),
//   `MOV byte [EDI+0x53A6],BL`, `MOV ECX,[EDI+0x53A0]` / `MOV [EDI+0x53A0],EAX`
//   (the repaint deadline compared against the frame counter), and the strip
//   flag `MOV byte [EDI+EAX*4+0x1580],BL` with EAX = tab*997 — i.e. the strip
//   array at +0x1544 with stride 0xF94, member +0x3C — whose tab-3 expansion
//   is the constant-folded `MOV byte [EDI+0x443C],BL` (0x1544 + 3*0xF94 + 0x3C
//   == 0x443C). On the object (EBP): the virtual calls `CALL [EAX+0x84]`
//   (GetTechnoType), `CALL [EDX+0x2C]` (WhatAmI) and `CALL [EAX+0x40]` (the
//   object's own array index), plus `MOV EDX,[EBP+0x520]` and the byte
//   `MOV AL,[EDX+0x16CB]`. Globals: the player singleton pointer 0xA83D4C
//   (tested, then used as the ECX of CALL 0x50B370), MapClass::Instance as the
//   immediate 0x87F7E8 feeding `PUSH 0; CALL 0x4F42F0` (FlagToRedraw), and
//   the frame counter 0xA8ED84. The tab classifier is
//   SidebarClass::GetObjectTabIdx expanded inline — the same compare chain
//   already matched out of line at 0x6ABC60 in
//   match/ui/sidebar_class_tab_methods.cpp, including the
//   `CALL 0x5004E0; CMP EAX,5; SETZ` arm — with the literal 1 shared between
//   its `CMP ESI,EBX` test and every byte store. Names cross-checked against
//   YRpp SidebarClass (consult-only, NO LICENSE).
#ifndef GG_MATCH_UI_SIDEBAR_CLASS_TECHNO_DESTROYED_METHODS_H
#define GG_MATCH_UI_SIDEBAR_CLASS_TECHNO_DESTROYED_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// AbstractType discriminants, as in match/ui/sidebar_class_tab_methods.h.
#define ABS_UNIT_006A5F20          0x01
#define ABS_AIRCRAFT_006A5F20      0x02
#define ABS_BUILDING_006A5F20      0x03
#define ABS_BUILDINGTYPE_006A5F20  0x06
#define ABS_AIRCRAFTTYPE_006A5F20  0x07
#define ABS_INFANTRYTYPE_006A5F20  0x0F
#define ABS_UNITTYPE_006A5F20      0x10
#define ABS_SUPERWEAPON_006A5F20   0x1F
#define ABS_ABSTRACTTYPE_006A5F20  0x20
#define ABS_INFANTRY_006A5F20      0x28
#define ABS_BUILDINGTYPE2_006A5F20 0x39

// FUNCTION: GAMEMD 0x5004E0 (decl; reloc) — ObjectTypeClass::IsBuildCat5,
// already matched in match/core/object_type_class.cpp; called here with the
// discriminant in ECX and the index in EDX.
int __fastcall IsBuildCat5_006A5F20(int abs, int idx);

struct TechnoType_006A5F20;

// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame.
#include "../core/frame_counter.h"

// MapClass — only the sidebar repaint request is called, through the
// immediate 0x87F7E8.
struct Map_006A5F20
{
    char _opaque[4];
    // FUNCTION: GAMEMD 0x4F42F0 (decl; reloc) — GScreenClass::FlagToRedraw.
    void FlagToRedraw(int which);
};
// GLOBAL: GAMEMD 0x87F7E8 — the MapClass instance itself.
extern Map_006A5F20 MapInstance_006A5F20;

struct House_006A5F20
{
    char _opaque[4];
    // FUNCTION: GAMEMD 0x50B370 (decl; reloc) — does this house still have a
    // reason to show the cameo of that type?
    bool FUN_0050B370(TechnoType_006A5F20* type);
};
// GLOBAL: GAMEMD 0xA83D4C — HouseClass::CurrentPlayer.
extern House_006A5F20* PlayerPtr_006A5F20;

// The object reached through the techno's +0x520; only its byte at +0x16CB
// is read here.
struct Obj_006A5F20_520
{
    char _pad0000[0x16CB];   // +0x0000
    char At_16CB;            // +0x16CB
};
GG_STATIC_ASSERT(offsetof(Obj_006A5F20_520, At_16CB) == 0x16CB);

struct ObjVtbl_006A5F20;

struct Techno_006A5F20
{
    ObjVtbl_006A5F20*  Vtbl;                    // +0x0000
    char               _pad004[0x520 - 0x4];    // +0x0004
    Obj_006A5F20_520*  At_520;                  // +0x0520
};
GG_STATIC_ASSERT(offsetof(Techno_006A5F20, At_520) == 0x520);

typedef int (Techno_006A5F20::*Fn2C_006A5F20)();
typedef int (Techno_006A5F20::*Fn40_006A5F20)();
typedef TechnoType_006A5F20* (Techno_006A5F20::*Fn84_006A5F20)();

struct ObjVtbl_006A5F20
{
    char            _pad000[0x2C];             // +0x0000
    Fn2C_006A5F20   WhatAmI;                   // +0x002C
    char            _pad030[0x40 - 0x30];      // +0x0030
    Fn40_006A5F20   At_40;                     // +0x0040
    char            _pad044[0x84 - 0x44];      // +0x0044
    Fn84_006A5F20   GetTechnoType;             // +0x0084
};
GG_STATIC_ASSERT(offsetof(ObjVtbl_006A5F20, WhatAmI)       == 0x2C);
GG_STATIC_ASSERT(offsetof(ObjVtbl_006A5F20, At_40)         == 0x40);
GG_STATIC_ASSERT(offsetof(ObjVtbl_006A5F20, GetTechnoType) == 0x84);

// StripClass (sizeof == 0xF94), as in match/ui/sidebar_class_set_tab_methods.h.
struct Strip_006A5F20
{
    char _pad000[0x3C];             // +0x0000
    char At_3C;                     // +0x003C  "this strip needs redrawing"
    char _pad03D[0xF94 - 0x3D];     // +0x003D
};
GG_STATIC_ASSERT(offsetof(Strip_006A5F20, At_3C) == 0x3C);
GG_STATIC_ASSERT(sizeof(Strip_006A5F20) == 0xF94);

struct Sidebar_006A5F20
{
    char           _pad0000[0x1544];            // +0x0000
    Strip_006A5F20 Tabs[4];                     // +0x1544
    char           _pad5394[0x539C - 0x5394];   // +0x5394
    int            ActiveTabIndex;              // +0x539C
    int            At_53A0;                     // +0x53A0  repaint deadline
    char           _pad53A4[1];                 // +0x53A4
    char           At_53A5;                     // +0x53A5  sidebar is up
    char           At_53A6;                     // +0x53A6  sidebar is dirty

    // FUNCTION: GAMEMD 0x6A5F20 — SidebarClass::OnTechnoDestroyed.
    void OnTechnoDestroyed(Techno_006A5F20* obj);
};
GG_STATIC_ASSERT(offsetof(Sidebar_006A5F20, Tabs)           == 0x1544);
GG_STATIC_ASSERT(offsetof(Sidebar_006A5F20, ActiveTabIndex) == 0x539C);
GG_STATIC_ASSERT(offsetof(Sidebar_006A5F20, At_53A0)        == 0x53A0);
GG_STATIC_ASSERT(offsetof(Sidebar_006A5F20, At_53A5)        == 0x53A5);
GG_STATIC_ASSERT(offsetof(Sidebar_006A5F20, At_53A6)        == 0x53A6);

#endif  // GG_MATCH_UI_SIDEBAR_CLASS_TECHNO_DESTROYED_METHODS_H
