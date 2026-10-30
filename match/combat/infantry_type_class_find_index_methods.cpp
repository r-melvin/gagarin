// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail 0x523C90: the name is tested against "<none>" (0x817474) and "none" (0x817694) with
//   _strcmpi (0x7C8D20), then compared with the ID (+0x24) of each entry of the infantry type
//   array at 0xA8E348 (Items +4, Count +0x10).

#include "../_layout/infantry_type_class.h"
#include "../_layout/rules_class.h"
#include "../core/vector_class.h"
#include "../core/header_init_shapes.h"

// LIBRARY: GAMEMD 0x7C8D20 -- CRT _strcmpi.
extern "C" int __cdecl _strcmpi(const char*, const char*);

// GLOBAL: GAMEMD 0xA8E348 -- every InfantryTypeClass.
extern DynamicVectorClass<InfantryTypeClass*> DAT_00A8E348;

// Two cell values: an empty cell and the 0x7FFF "no cell" marker.
struct CellPairStatic_00A8F28C
{
    CellStruct First;
    CellStruct Second;
    CellPairStatic_00A8F28C()
    {
        First = HeaderCellInit(0, 0);
        Second = HeaderCellInit(0x7FFF, 0x7FFF);
    }
    ~CellPairStatic_00A8F28C() {}
};

// FUNCTION: GAMEMD 0x523C20
// SYNTHETIC: GAMEMD 0x523C80 -- exit-time destructor stub of the static below
// GLOBAL: GAMEMD 0xA8F28C
// Return the lazily constructed pair; the argument is ignored.
CellStruct* InfantryTypeClass::vf_36(int)
{
    static CellPairStatic_00A8F28C instance;
    return &instance.First;
}

// FUNCTION: GAMEMD 0x523C90
int InfantryTypeClass::FUN_00523C90(const char* name)
{
    if (_strcmpi(name, "<none>") != 0 && _strcmpi(name, "none") != 0) {
        for (int i = 0; i < DAT_00A8E348.Count; i++) {
            if (_strcmpi(DAT_00A8E348.Items[i]->ID, name) == 0) {
                return i;
            }
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x524790
int InfantryTypeClass::vf_45()
{
    return RulesInstance->IRepairStep;
}
