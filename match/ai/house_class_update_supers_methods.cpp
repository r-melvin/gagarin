// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read numerically off retail gamemd.exe v1.001 at 0x4F9370: the super weapon vector
//   at house +0x254 (Items +0x258, Count +0x264), SuperClass Type +0x28, the type's slot 16
//   (+0x40), the UI-string builder 0x6ABC60 and the sidebar/map call 0x6A60A0 on 0x87F7E8.

#include "../_layout/house_class.h"
#include "../_layout/super_class.h"
#include "../_layout/super_weapon_type_class.h"

// GLOBAL: GAMEMD 0xA83D4C
extern HouseClass* CurrentPlayer;

// FUNCTION: GAMEMD 0x6ABC60 (decl; reloc)
int FUN_006ABC60(int a, int b, int c);

// The object at 0x87F7E8 as this call sees it.
struct SidebarView_004F9370
{
    // FUNCTION: GAMEMD 0x6A60A0 (decl; reloc)
    void FUN_006A60A0(int a);
};
// GLOBAL: GAMEMD 0x87F7E8
extern SidebarView_004F9370 Sidebar_0087F7E8_004F9370;

// FUNCTION: GAMEMD 0x4F9370
// Update every super weapon of the house. For the local player's house, a weapon that
// reports it just became ready is announced through the sidebar.
void HouseClass::FUN_004F9370()
{
    for (int i = 0; i < Supers.Count; i++) {
        SuperClass* super = Supers.Items[i];
        if (super->FUN_006CBCA0(this == CurrentPlayer) && this == CurrentPlayer) {
            int name = super->Type->vf_16();
            Sidebar_0087F7E8_004F9370.FUN_006A60A0(FUN_006ABC60(0x39, name, 0));
        }
    }
}
