// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail 0x721A50 (TiberiumClass override of AbstractTypeClass::vf_25, the INI reader) reads
// Spread, SpreadPercentage, Growth, GrowthPercentage, Value, Power, Color, Debris and Image.
#include "../_layout/tiberium_class.h"
#include "../platform/ccini_class_methods.h"
#include "rules_class_ini_support.h"

// GLOBAL: GAMEMD 0xA83D84 -- object whose four dwords the Image key selects between.
struct TiberiumImageSource_00A83D84
{
    char unknown_00[0x6C];
    int  unknown_6C;
    char unknown_70[0x198 - 0x70];
    int  unknown_198;
    char unknown_19C[0x1FC - 0x19C];
    int  unknown_1FC;
    char unknown_200[0x24C - 0x200];
    int  unknown_24C;
};
extern TiberiumImageSource_00A83D84* DAT_00A83D84;

inline TypeList<const AnimTypeClass*> BuildL(char* buffer)
{
    TypeList<const AnimTypeClass*> list(0, 0);
    for (char* token = strtok(buffer, STR_00817F70); token && *token; token = strtok(0, STR_00817F70)) {
        const AnimTypeClass* type = AnimType_FindPtr(token);
        if (type)
            list.AddItem(type);
    }
    return list;
}
inline TypeList<const AnimTypeClass*> ReadL(CCINIClass* ini, const char* section,
    const char* key, const TypeList<const AnimTypeClass*>& defaultValue, char* buffer)
{
    if (ini->ReadString(section, key, STR_00889F64, buffer, 0x80))
        return BuildL(buffer);
    return defaultValue;
}

// FUNCTION: GAMEMD 0x721A50
bool TiberiumClass::vf_25(CCINIClass* ini)
{
    char buffer[0x80];
    ini->Reset();
    if (AbstractTypeClass::vf_25(ini)) {
        unknown_9C = ini->ReadInteger(ID, "Spread", unknown_9C);
        SpreadPercentage = ini->ReadDouble(ID, "SpreadPercentage", SpreadPercentage);
        unknown_A8 = ini->ReadInteger(ID, "Growth", unknown_A8);
        GrowthPercentage = ini->ReadDouble(ID, "GrowthPercentage", GrowthPercentage);
        Value = ini->ReadInteger(ID, "Value", Value);
        Power = ini->ReadInteger(ID, "Power", Power);
        Color = ini->ReadColorScheme(ID, "Color", Color);
        Debris = ReadL(ini, ID, "Debris", Debris, buffer);
        switch (ini->ReadInteger(ID, "Image", -1)) {
        case -1:
            break;
        case 2:
            unknown_E0 = DAT_00A83D84->unknown_6C;
            unknown_E4 = 12;
            unknown_E8 = 12;
            break;
        case 3:
            unknown_E0 = DAT_00A83D84->unknown_1FC;
            unknown_E4 = 12;
            unknown_E8 = 12;
            unknown_EC = 8;
            break;
        case 4:
            unknown_E0 = DAT_00A83D84->unknown_24C;
            unknown_E4 = 12;
            unknown_E8 = 12;
            unknown_EC = 8;
            break;
        default:
            unknown_E0 = DAT_00A83D84->unknown_198;
            unknown_E4 = 12;
            unknown_E8 = 12;
            unknown_EC = 8;
            break;
        }
        return true;
    }
    return false;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA83D84
TiberiumImageSource_00A83D84* DAT_00A83D84;
// END defined globals
