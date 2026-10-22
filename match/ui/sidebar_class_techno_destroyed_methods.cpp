// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6A5F20.

#include "sidebar_class_techno_destroyed_methods.h"

// SidebarClass::GetObjectTabIdx expanded inline here — the same compare chain
// matched out of line at 0x6ABC60; written as an if-chain in source order,
// because a switch over these values becomes a jump table.
static inline int GetObjectTabIdx_006A5F20(int abs, int idxType)
{
    if (abs == ABS_INFANTRYTYPE_006A5F20 || abs == ABS_UNITTYPE_006A5F20)
        return 2;

    if (abs == ABS_UNIT_006A5F20 || abs == ABS_INFANTRY_006A5F20
        || abs == ABS_AIRCRAFT_006A5F20 || abs == ABS_BUILDING_006A5F20)
        return 3;

    if (abs == ABS_BUILDINGTYPE_006A5F20 || abs == ABS_AIRCRAFTTYPE_006A5F20)
        return IsBuildCat5_006A5F20(abs, idxType) == 5;

    if (abs == ABS_BUILDINGTYPE2_006A5F20 || abs == ABS_ABSTRACTTYPE_006A5F20
        || abs == ABS_SUPERWEAPON_006A5F20)
        return 1;

    return -1;
}

// FUNCTION: GAMEMD 0x6A5F20  SidebarClass::OnTechnoDestroyed (__thiscall, ret 4)
//
// Something the player owned has just gone away. If the sidebar is up and the
// object belongs to the tab currently on show — and losing it costs the player
// that cameo — the tab's strip is flagged for a redraw. A building that is not
// on the current tab still dirties the buildings strip when its owner marks it
// as one that changes what can be built. Either way the sidebar is marked
// dirty and a repaint is asked for, with the repaint deadline pushed two
// frames out when it has already lapsed.
void Sidebar_006A5F20::OnTechnoDestroyed(Techno_006A5F20* obj)
{
    if (this->At_53A5 == 0) {
        return;
    }
    if (obj == 0) {
        return;
    }

    TechnoType_006A5F20* type = (obj->*obj->Vtbl->GetTechnoType)();
    if (PlayerPtr_006A5F20 == 0) {
        return;
    }

    int abs = (obj->*obj->Vtbl->WhatAmI)();
    int tab = GetObjectTabIdx_006A5F20(abs, (obj->*obj->Vtbl->At_40)());

    int active = this->ActiveTabIndex;
    if (tab == active) {
        if (PlayerPtr_006A5F20->FUN_0050B370(type)) {
            this->At_53A6 = 1;
            this->Tabs[this->ActiveTabIndex].At_3C = 1;
            MapInstance_006A5F20.FlagToRedraw(0);
            if (this->At_53A0 <= CurrentFrame) {
                this->At_53A0 = CurrentFrame + 2;
            }
        }
    } else if (abs == ABS_BUILDINGTYPE_006A5F20) {
        if (obj->At_520->At_16CB != 0 && active == 3) {
            this->At_53A6 = 1;
            // Taking the strip's address into a local is what keeps the
            // dirty-byte store above the repaint call's argument setup: with
            // the constant-folded `this->Tabs[3].At_3C = 1;` cl hoists the
            // PUSH/MOV ECX pair above it. The first arm needs no such anchor
            // because its index arithmetic already sits between the two.
            Strip_006A5F20* strip = &this->Tabs[3];
            strip->At_3C = 1;
            MapInstance_006A5F20.FlagToRedraw(0);
            if (this->At_53A0 <= CurrentFrame) {
                this->At_53A0 = CurrentFrame + 2;
            }
        }
    }
}
