// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4753F0, 0x475460,
//   0x4754B0, 0x475510, 0x475540 and 0x475610.

#include "ccini_class_armor_house_type_methods.h"
#include "ccini_class_methods.h"

// Find a house-type record's index in the registry. Retail inlined this and
// held the record pointer in the return register across the search, which
// only the free-function form over the global container reproduces — the
// same lever the movie reader needs in
// ccini_class_theater_theme_methods.cpp.
static inline int IndexOfHouseType(HouseType_005113F0* house)
{
    int count = DAT_00A83C98.Count;

    for (int i = 0; i < count; ++i) {
        if (DAT_00A83C98.Items[i] == house) {
            return i;
        }
    }

    return -1;
}

// FUNCTION: GAMEMD 0x4753F0
//
// Read an armour type by name. The caller's default index is spelled as its
// own armour name, so the parse runs unconditionally and there is no
// fallback arm at all.
int CCINI_004753F0::ReadArmor(const char* section, const char* key,
                              int defaultValue)
{
    char buffer[128];

    ReadString(section, key, DAT_007E5210[defaultValue], buffer, sizeof(buffer));

    return FUN_00772A50(buffer);
}

// FUNCTION: GAMEMD 0x475460
//
// Write an armour type out by name, with the all-ones sentinel spelled
// "<none>". The sentinel test is a byte compare on the low byte even though
// the value arrives as a full dword, because the dword is what the name
// lookup wants in ECX on the other arm.
bool CCINI_004753F0::WriteArmor(const char* section, const char* key, int value)
{
    if ((unsigned char)value == 0xFF) {
        return WriteString(section, key, STR_00817474);
    }

    return WriteString(section, key, FUN_00751590(value));
}

// FUNCTION: GAMEMD 0x4754B0
//
// Read a land type by name, the caller's default spelled as its own name.
// An absent key gives the default back, which is why the default is held in
// a callee-saved register across the read.
int CCINI_004753F0::ReadLandType(const char* section, const char* key,
                                 int defaultValue)
{
    char buffer[128];

    if (ReadString(section, key, FUN_0048DFD0(defaultValue), buffer,
                   sizeof(buffer))) {
        return FUN_0048DF80(buffer);
    }

    return defaultValue;
}

// FUNCTION: GAMEMD 0x475510
//
// The matching writer.
bool CCINI_004753F0::WriteLandType(const char* section, const char* key, int value)
{
    return WriteString(section, key, FUN_0048DFD0(value));
}

// FUNCTION: GAMEMD 0x475540
//
// Read a house type by name, through three successively more expensive
// lookups: the pseudo-house codes (<player>, <random> and the like) first,
// then the registered house types by name, and finally registration of a
// name never seen before, whose index is recovered by looking the new
// record's pointer back up in the registry.
int CCINIClass::FUN_00475540(const char* section, const char* key,
                                  int defaultValue)
{
    char buffer[128];

    if (FUN_00528A10(section, key, STR_00889F64, buffer, sizeof(buffer))) {
        int code = FUN_00510FB0(buffer);

        if (FUN_00510F60(code)) {
            return code;
        }

        int index = FUN_005117D0(buffer);

        if (index == -1) {
            HouseType_005113F0* house = new HouseType_005113F0(buffer);

            return IndexOfHouseType(house);
        }

        return index;
    }

    return defaultValue;
}

// FUNCTION: GAMEMD 0x475610
//
// Write a house type back out by name. The buffer starts as "<none>" and is
// overwritten by whichever arm applies; the two "<random>" arms are spelled
// separately because retail emits the copy twice, which a disjunction would
// have folded into one block.
bool CCINIClass::FUN_00475610(const char* section, const char* key, int value)
{
    char name[128];

    strcpy(name, STR_00817474);

    if (FUN_00510F60(value)) {
        FUN_00510E10(value, name, sizeof(name));
    } else if (value == -2) {
        strcpy(name, STR_0081C008);
    } else if (value == -3) {
        strcpy(name, STR_0081C008);
    } else if (value != -1 && value >= 0 && value < DAT_00A83C98.Count) {
        strcpy(name, DAT_00A83C98.Items[value]->ID);
    }

    return WriteString(section, key, name);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x81C008
extern const char STR_0081C008[] = "<random>";
// END defined globals
