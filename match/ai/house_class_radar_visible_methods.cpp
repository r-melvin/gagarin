// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read numerically off retail gamemd.exe v1.001 at 0x5092F0: RadarVisibleTo at +0x54E4
//   (see house_class.h), HouseTypeClass index at +0xB8, ObjectClass InLimbo/Location at
//   +0x81/+0x9C, TechnoClass Owner at +0x21C, TechnoTypeClass Sight at +0x5E8, vtable slot 33,
//   the technos array at 0xA8EC78 and the current player at 0xA83D4C.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT

#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"
#include "../_layout/techno_type_class.h"
#include "../core/vector_class.h"

// GLOBAL: GAMEMD 0xA83D4C
extern HouseClass* CurrentPlayer;
// GLOBAL: GAMEMD 0xA8EC78
extern DynamicVectorClass<TechnoClass*> DAT_00A8EC78;

// The map instance (0x87F7E8) as the two calls here see it.
struct MapView_005092F0
{
    // FUNCTION: GAMEMD 0x5673A0 (decl; reloc)
    void FUN_005673A0(CoordStruct* where, int sight, HouseClass* house, int a, int b, int c, int d, int e);
    // FUNCTION: GAMEMD 0x4F42F0 (decl; reloc)
    void FUN_004F42F0(int mode);
};
// GLOBAL: GAMEMD 0x87F7E8
extern MapView_005092F0 MapInstance_0087F7E8;

// FUNCTION: GAMEMD 0x5092F0
// Mark the radar as visible to `house`. When that is the local player, every live,
// on-map techno of this house reveals the area around it (using its type's sight
// range) and the map is then refreshed.
void HouseClass::FUN_005092F0(HouseClass* house)
{
    RadarVisibleTo |= 1 << house->Type->ArrayIndex2;
    if (house == CurrentPlayer) {
        for (int i = 0; i < DAT_00A8EC78.Count; i++) {
            TechnoClass* techno = DAT_00A8EC78.Items[i];
            if (techno != 0 && !techno->InLimbo && techno->Owner == this) {
                CoordStruct where = techno->Location;
                MapInstance_0087F7E8.FUN_005673A0(&where, techno->vf_33()->Sight, this, 0, 0, 0, 1, 1);
            }
        }
        MapInstance_0087F7E8.FUN_004F42F0(2);
    }
}
