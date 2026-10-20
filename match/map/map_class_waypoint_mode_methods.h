// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4AC700: the selected flag byte is `[ESI+0x11B3]`
//   (seed read `MOV CL,[ESI+0x11B3]` and the compare `CMP BL,CL`), the other
//   four cleared in the order `+0x11B0`, `+0x11B1`, `+0x11B2`, `+0x11B4`, the
//   refusal word `[ESI+0x11A8]`, the stored pointer `[ESI+0x11BC]` and the
//   12-byte record at `LEA ECX,[ESI+0x11C0]` copied through it; the local
//   player is `[0xA83D4C]`, its word `[EDX+0x20C]`, and its no-argument
//   __thiscall 0x5090A0 returns the waypoint slot. Vtable slot `[EAX+0x50]`
//   is the same one the other mode setters use (match/map/map_class_mode_methods);
//   the mouse singleton `[0x887640]` is shown via slot +0x10. Names
//   cross-checked against YRpp MapClass::SetWaypointMode (consult-only).
#ifndef GG_MATCH_MAP_MAP_CLASS_WAYPOINT_MODE_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_WAYPOINT_MODE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct House_004AC700
{
    char _pad000[0x20C];   // +0x0000
    int  At_20C;           // +0x020C  waypoint slot remembered on the player

    // FUNCTION: GAMEMD 0x5090A0 (decl; reloc) — free/current waypoint slot, -1 if none.
    int FUN_005090A0();
};
GG_STATIC_ASSERT(offsetof(House_004AC700, At_20C) == 0x20C);

// GLOBAL: GAMEMD 0xA83D4C — HouseClass::CurrentPlayer.
extern House_004AC700* CurrentPlayer_004AC700;

// WWMouseClass: only slot +0x10 (show) is dispatched.
struct MouseVtbl_004AC700;
struct Mouse_004AC700
{
    MouseVtbl_004AC700* Vtbl;     // +0x0000
};
typedef void (Mouse_004AC700::*FnMouse_004AC700)();
struct MouseVtbl_004AC700
{
    char _pad000[0x10];           // +0x0000
    FnMouse_004AC700 At_10;       // +0x0010
};
GG_STATIC_ASSERT(offsetof(MouseVtbl_004AC700, At_10) == 0x10);
// GLOBAL: GAMEMD 0x887640 — WWMouseClass::Instance.
extern Mouse_004AC700* DAT_00887640;

// FUNCTION: GAMEMD 0x48DC90 (decl; reloc) — the no-argument notify run after a
// mode is entered (the same call the other mode setters make).
void ModeEntered_004AC700();

// The 12-byte record parked at +0x11C0 and handed back through +0x11BC.
struct Coord_004AC700
{
    int X;                        // +0x0000
    int Y;                        // +0x0004
    int Z;                        // +0x0008
};
GG_STATIC_ASSERT(sizeof(Coord_004AC700) == 0xC);

struct Map_004AC700
{
#include "map_class_mode_slots.inc"

    char _padVtbl[0x11A8 - 4];    // +0x0004  (vptr occupies +0x0000)
    int  unknown_11A8;            // +0x11A8  a mode change is refused when set
    char _pad11AC[0x11B0 - 0x11AC];
    bool RepairMode;              // +0x11B0
    bool SellMode;                // +0x11B1
    bool TogglePowerMode;         // +0x11B2
    bool WaypointMode;            // +0x11B3
    bool PlaceBeaconMode;         // +0x11B4
    char _pad11B5[0x11BC - 0x11B5];
    Coord_004AC700* At_11BC;      // +0x11BC  receiver for the parked record
    Coord_004AC700  At_11C0;      // +0x11C0  the parked record

    // FUNCTION: GAMEMD 0x4AC700
    void SetWaypointMode(int mode, bool somebool);
};
GG_STATIC_ASSERT(offsetof(Map_004AC700, unknown_11A8)    == 0x11A8);
GG_STATIC_ASSERT(offsetof(Map_004AC700, RepairMode)      == 0x11B0);
GG_STATIC_ASSERT(offsetof(Map_004AC700, SellMode)        == 0x11B1);
GG_STATIC_ASSERT(offsetof(Map_004AC700, TogglePowerMode) == 0x11B2);
GG_STATIC_ASSERT(offsetof(Map_004AC700, WaypointMode)    == 0x11B3);
GG_STATIC_ASSERT(offsetof(Map_004AC700, PlaceBeaconMode) == 0x11B4);
GG_STATIC_ASSERT(offsetof(Map_004AC700, At_11BC)         == 0x11BC);
GG_STATIC_ASSERT(offsetof(Map_004AC700, At_11C0)         == 0x11C0);

#endif  // GG_MATCH_MAP_MAP_CLASS_WAYPOINT_MODE_METHODS_H
