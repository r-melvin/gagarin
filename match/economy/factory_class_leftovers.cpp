// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Disassembled from retail gamemd.exe v1.001 at 0x4CA6E0 (offsets read numerically).
//   FUNCTION: GAMEMD 0x4CA6E0   refresh the production rate of one house's factories

#include "../_layout/factory_class.h"
#include "../_layout/techno_class.h"

// GLOBAL: GAMEMD 0xA83E30 -- every FactoryClass in the game (defined in static_vector_init_stubs.cpp).
extern DynamicVectorClass<FactoryClass*> DAT_00A83E30;

// FUNCTION: GAMEMD 0x4CA6E0
// For each factory owned by `house`, recompute its build time in frames (the produced object's
// TimeToBuild() / 54, clamped to [1, 255]) and store it as the production rate when it changed.
void __fastcall FUN_004CA6E0(HouseClass* house)
{
    for (int i = 0; i < DAT_00A83E30.Count; i++)
    {
        FactoryClass* factory = DAT_00A83E30.Items[i];
        if (factory->Owner == house)
        {
            int cost = 0;
            if (factory->Object)
                cost = factory->Object->TimeToBuild();
            int frames = cost / 54;
            if (frames < 1)
                frames = 1;
            else if (frames > 255)
                frames = 255;
            if (frames != factory->Production.Rate)
                factory->Production.Rate = frames;
        }
    }
}
